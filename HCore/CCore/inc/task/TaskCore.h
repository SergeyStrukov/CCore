/* TaskCore.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_task_TaskCore_h
#define CCore_inc_task_TaskCore_h
 
#include <CCore/inc/PlanInit.h>
#include <CCore/inc/MemBase.h>
#include <CCore/inc/task/Atomic.h>

#include <CCore/inc/sys/SysTask.h>

namespace CCore {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_Task();

/* classes */ 

class Task;

/* class Task */ 

class Task : public MemBase_nocopy , Sys::TaskEntry
 {
   Atomic run_flag;
 
  private:
   
   static void EntryFunc(Sys::TaskEntry *obj);
   
  private:
  
   virtual void entry();
   
   virtual void exit();
  
  public:
  
   Task();
   
   virtual ~Task();
   
   bool run_or_exit();
   
   // task control
   
   static void Yield() { Sys::YieldTask(); }
   
   static void Sleep(MSec time) { Sys::SleepTask(time); }
   
   static Task * GetCurrent();
 };
 
} // namespace CCore
 
#endif
 

