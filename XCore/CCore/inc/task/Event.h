/* Event.h */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_task_Event_h
#define CCore_inc_task_Event_h
 
#include <CCore/inc/task/TaskList.h>

namespace CCore {

/* classes */ 

class Event;

/* class Event */ 

class Event : public Funchor_nocopy
 {
   TextLabel name;
   bool flag;
   TaskList list;
   
  private:
  
   static AutoTextNameType ObjName;
    
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
   
   void init(bool flag); 
   
   template <class T,class F>
   bool trigger_locked(T cur,F Release);
   
   bool wait_locked(MSec timeout);
   
  public: 
   
   // constructors
  
   explicit Event(bool flag=false);
   
   explicit Event(TextLabel name,bool flag=false);
   
   ~Event();
   
   TextLabel getName() const { return name; }
   
   // trigger
   
   bool trigger();
   
   bool trigger_int();
   
   bool trigger_any();
   
   // wait
   
   bool try_wait();
   
   void wait();
   
   bool wait(MSec timeout);
   
   bool wait(TimeScope time_scope);
   
   // functions
   
   void trigger_void() { trigger(); }
   
   void trigger_int_void() { trigger_int(); }
   
   void trigger_any_void() { trigger_any(); }
   
   Function<void (void)> function_trigger() { return FunctionOf(this,&Event::trigger_void); }
   
   Function<void (void)> function_trigger_int() { return FunctionOf(this,&Event::trigger_int_void); }
   
   Function<void (void)> function_trigger_any() { return FunctionOf(this,&Event::trigger_any_void); }
 };
 
} // namespace CCore
 
#endif
 

