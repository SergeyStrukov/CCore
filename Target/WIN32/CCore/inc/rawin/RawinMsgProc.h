/* RawingMsgProc.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_rawin_RawingMsgProc_h
#define CCore_inc_rawin_RawingMsgProc_h

#include <CCore/inc/rawin/RawinMsg.h>

#include <CCore/inc/Print.h>
 
namespace CCore {
namespace Rawin {

/* classes */ 

struct ProcMsgBase;

template <class W> struct ProcMsg;

class TraceMsg;

class NoTraceMsg;

/* struct ProcMsgBase */ 

struct ProcMsgBase
 {
  Win32::HWindow hWnd;
  Win32::MsgCode message;
  Win32::MsgWParam wParam;
  Win32::MsgLParam lParam;
  
  Win32::MsgResult result;
  
  ProcMsgBase(Win32::HWindow hWnd_,Win32::MsgCode message_,Win32::MsgWParam wParam_,Win32::MsgLParam lParam_)
   : hWnd(hWnd_),
     message(message_),
     wParam(wParam_),
     lParam(lParam_),
     result(0) 
   {
   }
  
  void defProc()
   { 
    result=Win32::DefWindowProcA(hWnd,message,wParam,lParam); 
   } 
 };
 
/* namespace DispatchEngine */ 
  
namespace DispatchEngine {

 // detect

template <class ProbeSet,class T>
struct Detect
 {
  enum ProbeArgType { ProbeArg };

  template <class S>
  static constexpr bool Probe(int) { return false; }

  template <class S,class C=typename ProbeSet::template Condition<S> >
  static constexpr bool Probe(ProbeArgType) { return true; }

  enum RetType { Ret = Probe<T>(ProbeArg) };
 };

struct Utils
 {
  template <class T> static T & GetObj();

  static ProcMsgBase * GetPtr();
 };

template <class W,class M>
struct ProbeSet_handle
 {
  template <class T,class S=decltype( Utils::GetObj<T>().handle(Utils::GetPtr(),Utils::GetObj<M>()) )> struct Condition;
 };

template <class W,class M> 
struct Has_handle : Detect<ProbeSet_handle<W,M>,W> {};

 // range props
 
template <bool Switch,class W,Win32::MsgCode Min,Win32::MsgCode Max> struct RangeProps;

template <class W,Win32::MsgCode Min,Win32::MsgCode Max> struct RangeProp;
 
template <class W,Win32::MsgCode Min,Win32::MsgCode Max> 
struct RangeProps<true,W,Min,Max>
 {
  static const Win32::MsgCode Med = Min+(Max-Min)/2 ;
  
  static const Win32::MsgCode LoCount = RangeProp<W,Min,Med>::Count ;
  
  static const Win32::MsgCode HiCount = RangeProp<W,Med,Max>::Count ;
  
  static const Win32::MsgCode Count = LoCount+HiCount ;
 
  static const Win32::MsgCode Code = LoCount ? RangeProp<W,Min,Med>::Code : RangeProp<W,Med,Max>::Code ;
  
  static const Win32::MsgCode HowMany = (Count>2)?2:Count ; 
 };
 
template <class W,Win32::MsgCode Min,Win32::MsgCode Max> 
struct RangeProps<false,W,Min,Max>
 {
  static const Win32::MsgCode Code = Min ;
  
  static const Win32::MsgCode Count = Has_handle<W,Msg<Code> >::Ret ;
  
  static const Win32::MsgCode HowMany = Count ;
 };
 
template <class W,Win32::MsgCode Min,Win32::MsgCode Max> 
struct RangeProp : RangeProps<(Max-Min>1),W,Min,Max> {};
 
 // dispatch
  
template <bool Switch,class W> struct Dispatch_others;

template <class W> struct Dispatch_other;
  
template <Win32::MsgCode Switch,class W,Win32::MsgCode Min,Win32::MsgCode Max> struct Dispatchs;

template <class W,Win32::MsgCode Min,Win32::MsgCode Max> struct Dispatch;
 
template <class W>
struct Dispatch_others<true,W>
 {
  template <class PMsg>
  static void Do(PMsg *ptr)
   { 
    MsgOther msg(ptr->message,ptr->wParam,ptr->lParam);
    
    ptr->obj->handle(ptr,msg);
   }
 };
 
template <class W>
struct Dispatch_others<false,W>
 {
  template <class PMsg>
  static void Do(PMsg *ptr)
   {
    ptr->defProc();
   }
 };
 
template <class W> 
struct Dispatch_other : Dispatch_others<Has_handle<W,MsgOther>::Ret,W> {};
 
template <class W,Win32::MsgCode Min,Win32::MsgCode Max>
struct Dispatchs<0,W,Min,Max>
 {
  template <class PMsg>
  static void Do(Win32::MsgCode,PMsg *ptr)
   { 
    Dispatch_other<W>::Do(ptr);
   }
 };
 
template <class W,Win32::MsgCode Min,Win32::MsgCode Max>
struct Dispatchs<1,W,Min,Max>
 {
  static const Win32::MsgCode Code = RangeProp<W,Min,Max>::Code ;
  
  template <class PMsg>
  static void Do(Win32::MsgCode message,PMsg *ptr)
   { 
    if( message==Code )
      {
       Msg<Code> msg(ptr->wParam,ptr->lParam);
       
       ptr->obj->handle(ptr,msg);
      }
    else
      {
       Dispatch_other<W>::Do(ptr);
      }
   }
 };
 
template <class W,Win32::MsgCode Min,Win32::MsgCode Max>
struct Dispatchs<2,W,Min,Max>
 {
  static const Win32::MsgCode Med = Min+(Max-Min)/2 ;
  
  template <class PMsg>
  static void Do(Win32::MsgCode message,PMsg *ptr)
   { 
    if( message<Med )
      {
       Dispatch<W,Min,Med>::Do(message,ptr);
      }
    else
      {
       Dispatch<W,Med,Max>::Do(message,ptr);
      }
   }
 };
 
template <class W,Win32::MsgCode Min,Win32::MsgCode Max> 
struct Dispatch : Dispatchs<RangeProp<W,Min,Max>::HowMany,W,Min,Max> {};
 
} // namespace DispatchEngine 
 
/* struct ProcMsg<W> */  

template <class W>
struct ProcMsg : ProcMsgBase
 {
  W *obj;
  
  ProcMsg(Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam,W *obj_)
   : ProcMsgBase(hWnd,message,wParam,lParam),
     obj(obj_)
   {
   }
   
  ProcMsg(const ProcMsgBase &proc,W *obj_)
   : ProcMsgBase(proc),
     obj(obj_)
   {
   }
   
  Win32::MsgResult handle(); 
 };
 
template <class W>
Win32::MsgResult ProcMsg<W>::handle()
 {
  if( message>=1 && message<Win32::WM_Lim )
    {
     DispatchEngine::Dispatch<W,1,Win32::WM_Lim>::Do(message,this);
    }
  else
    {
     DispatchEngine::Dispatch_other<W>::Do(this);
    }
    
  return result;  
 }
 
/* class TraceMsg */  

class TraceMsg : NoCopy
 {
   PrintFile out;
   ulen level;
   
  private: 
  
   void indent() { out.put(' ',4*level); }
   
   void endLine()
    {
     out.put('\n');
     
     if( level==0 ) out.put('\n');
    }
   
   using PrintResultFunc = void (*)(PrintBase &out,const ProcMsgBase &proc) ;
   
   template <class M>
   static void PrintResult(PrintBase &out,const ProcMsgBase &proc)
    { 
     M msg(proc.message,proc.wParam,proc.lParam);
    
     msg.printResult(out,proc.result); 
    }
 
   template <class M>
   PrintResultFunc trace(const M &msg)
    {
     indent();
    
     Printf(out,"#;\n",msg);
    
     level++;
     
     return PrintResult<M>;
    }
   
   PrintResultFunc begin_trace(const ProcMsgBase &proc);
   
   void end_trace(const ProcMsgBase &proc,PrintResultFunc func);
    
  public: 
 
   explicit TraceMsg(StrLen file_name) : out(file_name),level(0) {}
   
   ~TraceMsg() {}
   
   template <class ... TT>
   void printLine(const char *format,const TT && ... tt)
    {
     indent();
     
     Printf(out,format,tt...);
     
     endLine();
    }
   
   struct BeginTrace;
   
   class Op : NoCopy
    {
      TraceMsg &trace;
      const ProcMsgBase &proc;
      
      PrintResultFunc func;
   
     public:
    
      Op(TraceMsg &trace,const ProcMsgBase &proc,bool enable); 
     
      ~Op();
    };
 };
 
/* class NoTraceMsg */  

class NoTraceMsg : NoCopy
 {
  public:
  
   explicit NoTraceMsg(StrLen /* file_name */) {}
   
   class Op
    {
     public:
    
      Op(NoTraceMsg &,const ProcMsgBase &,bool) {}
    };
 };
 
} // namespace Rawin
} // namespace CCore
 
#endif
 

