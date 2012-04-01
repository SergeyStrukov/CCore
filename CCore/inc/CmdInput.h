/* CmdInput.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_CmdInput_h
#define CCore_inc_CmdInput_h

#include <CCore/inc/Cmp.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/CharProp.h>
 
namespace CCore {

/* classes */ 

class CmdInput;

template <class ReadCon,ulen MaxArgLen=80> class CmdInputCon;

/* class CmdInput */ 

class CmdInput : NoCopy
 {
  public:
  
   struct Target 
    {
     virtual void buildCmdList(CmdInput &input)=0;
     
     template <class T>
     void addCommand(CmdInput &input,StrLen cmd,void (T::*method)(StrLen arg)) // cmd must be persistent for CmdInput life-time
      {
       input.add(cmd,static_cast<TargetMethod>(method));
      }
    };
   
   typedef void (Target::*TargetMethod)(StrLen arg);
  
  private:
  
   Target &target;
   
   struct Rec
    {
     StrLen cmd;
     TargetMethod method;
     
     // constructors
     
     Rec(StrLen cmd_,TargetMethod method_) : cmd(cmd_),method(method_) {}
     
     // methods
     
     bool operator < (const Rec &obj) const { return StrLess(cmd,obj.cmd); }
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
   
   DynArray<Rec> list;
   bool locked;
   
   struct Frame
    {
     ulen ind;
     ulen lim;
     
     // constructors
     
     Frame() : ind(0),lim(0) {}
     
     Frame(NothingType) : ind(0),lim(0) {}
     
     explicit Frame(ulen lim_) : ind(0),lim(lim_) {}
     
     Frame(ulen ind_,ulen lim_) : ind(ind_),lim(lim_) {}
     
     // methods
     
     bool operator + () const { return ind<lim; }
     
     bool operator ! () const { return ind>=lim; }
     
     ulen getCount() const { return lim-ind; }
     
     ulen getMed() const { return ind+(lim-ind)/2; }
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
 
   DynArray<Frame> frame_list;
   ulen off;
   
  private:
  
   void add(StrLen cmd,TargetMethod method);
   
   Frame getCur() const;
   
   CmpResult cmp(ulen ind,char ch) const;
   
   ulen findMin(Frame cur,char ch) const;
   
   ulen findMax(Frame cur,char ch) const;
   
   Frame find(Frame cur,char ch) const;
   
   Frame find(Frame cur) const;
   
  public:
   
   // constructors
  
   explicit CmdInput(Target &target);
   
   ~CmdInput();
   
   // methods
   
   void start() { off=0; }
  
   bool put(char ch);
   
   void put(StrLen str) { for(; +str ;++str) put(*str); }
   
   bool back()
    {
     if( off ) 
       {
        off--;
       
        return true;
       }
      
     return false;  
    }
   
   struct CompleteResult
    {
     ulen count;
     StrLen str;
     
     // constructors
     
     CompleteResult(NothingType) : count(0) {}
     
     CompleteResult(ulen count_) : count(count_) {}
     
     CompleteResult(PtrLen<const char> str_) : count(1),str(str_) {}
    };
   
   CompleteResult complete() const;
   
   struct FinishResult
    {
     Target *target;
     TargetMethod method;
     
     // constructors
     
     FinishResult(NothingType) : target(0),method(0) {}
     
     FinishResult(Target &target_,TargetMethod method_) : target(&target_),method(method_) {}
     
     // methods
     
     bool operator + () const { return target!=0; }
     
     bool operator ! () const { return target==0; }
     
     void operator () (StrLen arg) { (target->*method)(arg); }
     
     template <class Report>
     void operator () (StrLen arg,Report &report) 
      {
       try
         {
          (target->*method)(arg);
          
          report.guard();
         }
       catch(CatchType)
         {
          report.clear();
         }
      }
    };
   
   FinishResult finish();
 };
 
/* class CmdInputCon<ReadCon,ulen MaxArgLen> */  

template <class ReadCon,ulen MaxArgLen> 
class CmdInputCon : NoCopy
 {
   CmdInput input;
   
   StrLen prompt_str;
   char bad_char;
   
   ReadCon con;
   
   char arg[MaxArgLen];
   ulen arg_len;
   
  private: 
   
   bool inputArg();
   
  public: 
  
   template <class ... SS>
   CmdInputCon(CmdInput::Target &target,StrLen prompt_str,SS && ... ss); // prompt_str must be persistent for CmdInputCon life-time
   
   ~CmdInputCon();
   
   void setBadChar(char bad_char_) { bad_char=bad_char_; }

   template <class ... SS>
   void command(SS && ... ss);
 };
 
template <class ReadCon,ulen MaxArgLen> 
bool CmdInputCon<ReadCon,MaxArgLen>::inputArg()
 {
  arg_len=0;
     
  for(;;)
    {
     switch( char ch=con.get() )
       {
        case '\b' :
         {
          if( arg_len>0 )
            {
             arg_len--;
                
             con.put("\b \b",3);
            }
          else
            {
             con.put('\b');
                
             return false;
            }  
         }
        break;
           
        case '\n' : case '\r' :
         {
          con.put("\r\n",2);
             
          return true;
         }
        break;
           
        default:
         {
          if( CharIsPrintable(ch) && arg_len<MaxArgLen )
            {
             arg[arg_len++]=ch;
                
             con.put(ch);
            }
         }
       }
    }
 }
    
template <class ReadCon,ulen MaxArgLen> 
template <class ... SS>
CmdInputCon<ReadCon,MaxArgLen>::CmdInputCon(CmdInput::Target &target,StrLen prompt_str_,SS && ... ss)
 : input(target),
   prompt_str(prompt_str_),
   bad_char('?'),
   con( std::forward<SS>(ss)... )
 {
 }
   
template <class ReadCon,ulen MaxArgLen> 
CmdInputCon<ReadCon,MaxArgLen>::~CmdInputCon()
 {
 }
 
template <class ReadCon,ulen MaxArgLen> 
template <class ... SS>
void CmdInputCon<ReadCon,MaxArgLen>::command(SS && ... ss)
 {
  con.put(prompt_str);
    
  input.start();
    
  for(;;)
    {
     switch( char ch=con.get() )
       {
        case ' ' :
         {
          auto result=input.finish();
             
          if( +result )
            {
             con.put(' ');
                
             if( inputArg() )
               {
                result(StrLen(arg,arg_len), std::forward<SS>(ss)... );
                
                return;
               }
             else
               {
                // do nothing
               }
            }
          else
            {
             // do nothing
            }
         }
        break;
          
        case '\r' : case '\n' :
         {
          auto result=input.finish();
             
          if( +result )
            {
             con.put("\r\n",2);
                
             result(StrLen(), std::forward<SS>(ss)... );
                
             return;
            }
          else
            {
             // do nothing
            }
         }
        break;
              
        case '\t' :
         {
          auto result=input.complete();
                
          if( result.count==1 )
            {
             con.put(result.str);
             input.put(result.str);   
            }
         }
        break;
             
        case '\b' :
         {
          if( input.back() )
            {
             con.put("\b \b",3);
            }
         }
        break;
             
        default:
         {
          if( input.put(ch) )
            con.put(ch);
          else
            con.put(bad_char);
         }
       }
    }      
 }

} // namespace CCore
 
#endif
 

