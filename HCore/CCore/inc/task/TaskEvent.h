/* TaskEvent.h */ 
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
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_task_TaskEvent_h
#define CCore_inc_task_TaskEvent_h

#include <CCore/inc/EventRecorder.h>
#include <CCore/inc/sys/SysTime.h>
 
#define CCORE_TASK_EVENT_ENABLE

namespace CCore {

/* classes */

struct TaskEventAlgo;

struct NoTaskEventHostType;

class TickTask;

/* struct TaskEventAlgo */

struct TaskEventAlgo
 {
  static const ulen RecordAlign = 4 ;
  
  static const uint64 TimeFreq = 1000000000 ; // meaningless value
  
  static EventTimeType GetTime() { return (EventTimeType)Sys::GetClockTime(); }
 };

/* types */

typedef EventRecorder<TaskEventAlgo> TaskEventRecorder;

typedef EventRecorderHost<TaskEventRecorder> TaskEventHostType;

/* struct NoTaskEventHostType */

struct NoTaskEventHostType
 {
  class StartStop : NoCopy
   {
    public: 
     
     template <class T>
     StartStop(T &,TaskEventRecorder *) 
      {
      } 
   };
  
  template <class T,class ... SS>
  void add(SS && ...)
   {
    // do nothing 
   }
  
  void tick()
   {
    // do nothing
   }
 };

/* global TaskEventHost */

#ifdef CCORE_TASK_EVENT_ENABLE

extern TaskEventHostType TaskEventHost;

#else

extern NoTaskEventHostType TaskEventHost;

#endif

/* class TickTask */

class TickTask : public Funchor_nocopy
 {
   Event stop;
   Event wait_stop;
   
  private:
   
   void task();
   
   Function<void (void)> function_task() { return FunctionOf(this,&TickTask::task); }
  
  public: 
  
   TickTask();
   
   ~TickTask();
 };

} // namespace CCore
 
#endif
 

