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
#include <CCore/inc/Task.h>
#include <CCore/inc/sys/SysTime.h>
 
//#define CCORE_TASK_EVENT_ENABLE

#define CCORE_TASK_EVENT_ENABLE_SYNC
#define CCORE_TASK_EVENT_ENABLE_PROTO
#define CCORE_TASK_EVENT_ENABLE_DEV

namespace CCore {

/* classes */

struct TaskEventAlgo;

class TaskEventHostType;

class TickTask;

/* struct TaskEventAlgo */

struct TaskEventAlgo
 {
  static const ulen RecordAlign = 4 ;
  
  static const uint64 TimeFreq = 0 ; // meaningless value

  class AllocPos : FastMutexBase
   {
     ulen off;
     
    public:
    
     AllocPos() : off(0) {}
     
     ~AllocPos() {}
     
     operator ulen() const { return off; }
     
     EventRecordPos alloc(ulen len)
      {
       Lock lock(*this);
       
       EventRecordPos ret;
       
       ret.pos=off;
       ret.time=(EventTimeType)Sys::GetClockTime();
       
       off+=len;
       
       return ret;
      }
     
     void back(ulen len)
      {
       Lock lock(*this);
       
       off-=len;
      }
   };
 };

/* types */

typedef EventRecorder<TaskEventAlgo> TaskEventRecorder;

/* class TaskEventHostType */

#ifdef CCORE_TASK_EVENT_ENABLE

class TaskEventHostType : public EventRecorderHost<TaskEventRecorder>
 {
  public:
 
#ifdef CCORE_TASK_EVENT_ENABLE_SYNC
 
   template <class T,class ... SS>
   void addSync(SS && ... ss)
    {
     add<T>( std::forward<SS>(ss)... );
    }
 
#else
 
   template <class T,class ... SS>
   void addSync(SS && ...)
    {
     // do nothing 
    }
 
#endif 
 
#ifdef CCORE_TASK_EVENT_ENABLE_PROTO
   
   template <class T,class ... SS>
   void addProto(SS && ... ss)
    {
     add<T>( std::forward<SS>(ss)... );
    }
 
#else
 
   template <class T,class ... SS>
   void addProto(SS && ...)
    {
     // do nothing 
    }
 
#endif
 
#ifdef CCORE_TASK_EVENT_ENABLE_DEV
   
   template <class T,class ... SS>
   void addDev(SS && ... ss)
    {
     add<T>( std::forward<SS>(ss)... );
    }
 
#else
 
   template <class T,class ... SS>
   void addDev(SS && ...)
    {
     // do nothing 
    }
 
#endif
 };

#else

class TaskEventHostType
 {
  public:
  
   class StartStop : NoCopy
    {
     public: 
      
      StartStop(TaskEventHostType &,TaskEventRecorder *obj) 
       {
        EventTypeIdNode::Register(*obj);
      
        EventIdNode::Register(*obj,TaskEventRecorder::RecordAlign);
       } 
    };
   
   template <class T,class ... SS>
   void add(SS && ...)
    {
     // do nothing 
    }
   
   template <class T,class ... SS>
   void addSync(SS && ...)
    {
     // do nothing 
    }
 
   template <class T,class ... SS>
   void addProto(SS && ...)
    {
     // do nothing 
    }
 
   template <class T,class ... SS>
   void addDev(SS && ...)
    {
     // do nothing 
    }
 
   void tick()
    {
     // do nothing
    }
 };

#endif

/* global TaskEventHost */

extern TaskEventHostType TaskEventHost;

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
 

