/* TaskPriority.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_task_TaskPriority_h
#define CCore_inc_task_TaskPriority_h

#include <CCore/inc/Printf.h>
 
namespace CCore {

/* classes */

//enum TaskPriority;

struct PrintTaskPriority;

/* enum TaskPriority */ 

enum TaskPriority : unsigned
 {
  ExitTaskPriority     = 0,                   // highest
  CompleteTaskPriority = 1,
  
  DefaultTaskPriority  = 10000,               // default
  MainTaskPriority     = DefaultTaskPriority,       
  
  IdleTaskPriority     = unsigned(-1)         // lowest
 };
 
inline bool Preempt(TaskPriority a,TaskPriority b) { return a<b; }

/* struct PrintTaskPriority */

struct PrintTaskPriority
 {
  TaskPriority priority;
  
  explicit PrintTaskPriority(TaskPriority priority_) : priority(priority_) {}
  
  enum PriAlign
   {
    PriAlignLeft,
    PriAlignRight,
    
    PriAlignDefault = PriAlignRight
   };
  
  template <class Dev>
  static void Parse_empty(Dev &dev,PriAlign &ret)
   {
    typename Dev::Peek peek(dev);
    
    if( !peek )
      {
       ret=PriAlignDefault;
      }
    else
      {
       switch( *peek )
         {
          case 'l' : case 'L' : ret=PriAlignLeft;  ++dev; break;
          case 'r' : case 'R' : ret=PriAlignRight; ++dev; break;
          
          default: ret=PriAlignDefault;
         }
      }
   }
  
  struct PrintOptType
   {
    ulen width;
    PriAlign align;
    
    void setDefault()
     {
      width=0;
      align=PriAlignDefault;
     }
    
    PrintOptType() { setDefault(); }
    
    PrintOptType(const char *ptr,const char *lim);
    
    //
    // [width=0][l|L|r|R=R]
    //
    
    IntAlign getIntAlign() const
     {
      switch( align )
        {
         case PriAlignLeft  : return IntAlignLeft;
         case PriAlignRight : return IntAlignRight;
         
         default: return IntAlignDefault;
        }
     }
    
    StrAlign getStrAlign() const
     {
      switch( align )
        {
         case PriAlignLeft  : return StrAlignLeft;
         case PriAlignRight : return StrAlignRight;
         
         default: return StrAlignDefault;
        }
     }
   };
  
  template <class P>
  static void PrintStr(StrLen value,P &out,PrintOptType opt)
   {
    StrPrintOpt str_opt;
    
    str_opt.width=opt.width;
    str_opt.align=opt.getStrAlign();
    
    Putobj(out,BindOpt(str_opt,value)); 
   }
  
  template <class P>
  static void PrintInt(unsigned value,P &out,PrintOptType opt)
   {
    IntPrintOpt int_opt;
    
    int_opt.width=opt.width;
    int_opt.align=opt.getIntAlign();
    
    Putobj(out,BindOpt(int_opt,value)); 
   }
  
  template <class P>
  void print(P &out,PrintOptType opt) const
   {
    switch( priority )
      {
       case ExitTaskPriority : PrintStr("Exit",out,opt); break;
       
       case CompleteTaskPriority : PrintStr("Complete",out,opt); break;
        
       case DefaultTaskPriority : PrintStr("Default",out,opt); break;
       
       case IdleTaskPriority : PrintStr("Idle",out,opt); break;
        
       default: PrintInt(priority,out,opt);
      }
   }
 };

/* functions */

inline PrintTaskPriority GetTextDesc(TaskPriority priority) { return PrintTaskPriority(priority); }

} // namespace CCore
 
#endif
 

