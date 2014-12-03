/* SysCon.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysCon.h>
#include <CCore/inc/sys/SysConHost.h>

#include <CCore/inc/dev/DevPlanInit.h>

#include <CCore/inc/BlockFifo.h>

#include <__std_init.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

namespace Private_SysCon {

/* class ImpCon */

class ImpCon : public ConBase
 {
   SingleHost<Video::VideoConsole> host;
   
   class Fifo : NoCopy
    {
      static const ulen Len = 4_KByte ;
     
      BlockFifoBuf<char,Len> fifo;
      
     private: 
     
      PtrLen<const char> get(char temp[Len])
       {
        Dev::IntLock lock;
        
        ulen ret=fifo.get(Range(temp,Len));
        
        return Range_const(temp,ret);
       }
      
      void put_full(PtrLen<const char> str) // str.len <= Len
       {
        Dev::IntLock lock;

        fifo.reset();
        fifo.put(str);
       }
      
      void put_short(PtrLen<const char> str) // str.len < Len
       {
        Dev::IntLock lock;

        ulen len=Len-str.len;
        ulen count=fifo.getCount();
        
        if( count>len )
          {
           count-=len;
           
           fifo.get(count, [] (char *,ulen) {} );
          }
        
        fifo.put(str);
       }
      
     public:
     
      Fifo() {}
      
      void put(PtrLen<const char> str)
       {
        if( str.len>=Len )
          {
           put_full(str.suffix(Len));
          }
        else
          {
           put_short(str);
          }
       }
      
      template <class Dev>
      void get(Dev &dev)
       {
        char temp[Len];
        
        dev.print(get(temp));
       }
    };
   
   Fifo fifo;
  
  private:
   
   void print(PtrLen<const char> str)
    {
     SingleHook<Video::VideoConsole> hook(host);
    
     if( +hook ) 
       {
        fifo.get(*hook);
       
        hook->print(str);
       }
     else
       {
        fifo.put(str);
       }
    }
   
   virtual void attachDefaultInput(ConInputFunction)
    {
     // no input
    }
   
   virtual void detachDefaultInput()
    {
    }
   
   virtual void defaultOutput(NanoPacket<char> packet)
    {
     if( !packet ) return;

     print(Range_const(packet.getRange()));
     
     packet.free();
    }
   
   virtual void enablePacket()
    {
    }
   
   virtual void disablePacket()
    {
    }
   
   virtual void showStat()
    {
    }
   
  public:
   
   ImpCon(TextLabel name,void *mem,ulen max_data_len,ulen count)
    : ConBase(name,mem,max_data_len,count),
      host("!VideoConsole")
    {
    }
   
   ~ImpCon()
    {
    }
   
   void debug_print(PtrLen<const char> str)
    {
     if( Dev::IsIntContext() )
       {
        fifo.put(str);
       }
     else
       {
        print(str);
       }
    }
   
   SingleHost<Video::VideoConsole> & getHost()
    {
     return host;
    }
 };

/* class DefaultCon */

class DefaultCon : NoCopy
 {
   static const ulen MaxDataLen = 512 ;
   static const ulen Count   = 100 ;
   static const ulen MemLen  = ConBase::MemLen(MaxDataLen,Count) ;
   
  private: 
 
   InitStorage<MemLen> storage;
   
   ImpCon dev;
   
  public:
  
   DefaultCon() : dev("!SysCon",storage.getMem(),MaxDataLen,Count) {}
   
   ~DefaultCon() {}
   
   ConBase * getBase() { return &dev; }
   
   void debug_print(PtrLen<const char> str)
    {
     dev.debug_print(str);
    }
   
   SingleHost<Video::VideoConsole> & getHost()
    {
     return dev.getHost();
    }
   
   static const char * GetTag() { return "SysCon"; }
 };
 
PlanInitObject<DefaultCon,PlanInitReq<Dev::GetPlanInitNode_Dev>
                         ,PlanInitReq<GetPlanInitNode_TaskCore> > Object CCORE_INITPRI_1 ;

void DebugPrint(PtrLen<const char> str)
 {
  if( !Object ) return;
  
  Object->debug_print(str);
 }

} // namespace Private_SysCon
 
using namespace Private_SysCon; 
 
PlanInitNode * GetPlanInitNode_SysCon() { return &Object; }
 
/* class ConBase */

ConBase * ConBase::GetObject() { return Object->getBase(); }

/* GetConHost() */

SingleHost<Video::VideoConsole> & GetConHost()
 {
  return Object->getHost(); 
 }

} // namespace Sys
} // namespace CCore
 
#if 1

using namespace CCore;

void __std_debug_init(void)
 {
 }

void __std_debug(const char *zstr)
 {
  Sys::DebugPrint(StrLen(zstr));
 }

void __std_debug2(const char *ptr,__std_len_t len)
 {
  Sys::DebugPrint(Range(ptr,len));
 }

void __std_debug_console(const char *ptr,__std_len_t len)
 {
  Sys::DebugPrint(Range(ptr,len));
 }

#include <CCore/inc/dev/AM3359.h>

void __std_debug_trap(unsigned LR,unsigned trap)
 {
  if( trap==0 ) return;
  
  using namespace AM3359::CP15;
  
  char buf[TextBufLen];
  
  PrintBuf out(Range(buf));
  
  switch( trap )
    {
     case 1 : // Undefined
      {
       Printf(out,"Undefined PC = #9.hi;",LR-4);
      }
     break; 
    
     case 3 : // Prefetch
      {
       Printf(out,"Prefetch PC = #9.hi; #; #9.hi;",LR-4,GetInstructionFaultStatus(),GetInstructionFaultAddress());
      }
     break;
     
     case 4 : // Data
      {
       Printf(out,"Data PC = #9.hi; #; #9.hi;",LR-8,GetDataFaultStatus(),GetDataFaultAddress());
      }
     break;
     
     default:
      {
       Printf(out,"LR = #9.hi; trap = #;",LR,trap);
      }
    }
  
  Sys::DebugPrint(out.close());
 }

#endif


