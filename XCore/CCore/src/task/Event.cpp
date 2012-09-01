/* Event.cpp */ 
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
 
#include <CCore/inc/task/Event.h>
 
#include <CCore/inc/task/TaskCore.h>

#include <CCore/inc/sys/SysLog.h>

namespace CCore {

/* struct EventNumber */

EventIdType EventNumber::Register(EventMetaInfo &info)
 {
  return info.addEnum_uint16("EventNumber")
             .setAppendFunc(EventEnumValue<EventNumber>::Append)
             .getId();
 }

/* struct EventEvent */

void EventEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Type=info.addEnum_uint8("EventEventType")
                   .addValueName(Trigger,"Trigger")
                   .getId();
  
  auto id=info.addStruct("EventEvent")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint16(EventTypeId<EventNumber>::GetId(),"event",Offset_event)
              .addField_enum_uint8(id_Type,"type",Offset_type)
              .getId();
  
  desc.setStructId(info,id);
 }

/* struct EventEvent_task */

void EventEvent_task::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Type=info.addEnum_uint8("EventEventTaskType")
                   .addValueName(ToTask,"ToTask")
                   .addValueName(Consume,"Consume")
                   .addValueName(Block,"Block")
                   .getId();
  
  auto id=info.addStruct("EventEventTask")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint16(EventTypeId<TaskNumber>::GetId(),"task",Offset_task)
              .addField_enum_uint16(EventTypeId<EventNumber>::GetId(),"event",Offset_event)
              .addField_enum_uint8(id_Type,"type",Offset_type)
              .getId();
  
  desc.setStructId(info,id);
 }

/* class Event */ 

AutoTextNameType Event::ObjName="Event";

void Event::event(TaskBase *task,EventEvent_task::Type type)
 {
  TaskEventHost.addSync<EventEvent_task>(task->getTaskNumber(),event_number,type);
 }

void Event::event(EventEvent::Type type)
 {
  TaskEventHost.addSync<EventEvent>(event_number,type);
 }

template <class ... TT> 
void Event::Log(const char *format,const TT & ... tt)
 {
  Sys::Log(Sys::LogSourceEvent|Sys::LogEvent,format,tt...);
 }
 
void Event::init(bool flag_)
 {
  flag=flag_;
 }
 
template <class T,class F>
bool Event::trigger_locked(T cur,F Release)
 {
  if( !flag )
    {
     TaskBase *task=list.get();
     
     if( task )
       {
        event(task,EventEvent_task::ToTask);
        
        Log("#; is triggered by #; to #;",name,GetTaskName(cur),task->getName());
        
        Release(task,Release_Ok);
       }
     else
       {
        flag=true;
        
        event(EventEvent::Trigger);
        
        Log("#; is triggered by #;",name,GetTaskName(cur));
       }
       
     return true;  
    }  
    
  return false;  
 }

bool Event::wait_locked(MSec timeout)
 {
  if( flag )
    {
     flag=false;
     
     event(Task::GetCurrent(),EventEvent_task::Consume);
     
     Log("#; is consumed by #;",name,GetTaskName(CurTaskContext));
       
     return true;
    }
  else
    {
     event(Task::GetCurrent(),EventEvent_task::Block);
     
     Log("#; is blocked on #; timed = #;",GetTaskName(CurTaskContext),name,timeout);
       
     return Task::Internal::BlockTask_task(list,timeout)==Release_Ok;
    }
 }

Event::Event(bool flag)
 : name(GetAutoText<ObjName>()),
   event_number(name) 
 {
  init(flag);
 }
   
Event::Event(TextLabel name_,bool flag)
 : name(name_),
   event_number(name)
 {
  init(flag);
 }
 
Event::~Event()
 {
 }
 
bool Event::trigger()
 {
  Dev::IntLock lock;
  
  return trigger_locked(CurTaskContext,Task::Internal::ReleaseTask_task);
 }
   
bool Event::trigger_int()
 {
  return trigger_locked(InterruptContext,Task::Internal::ReleaseTask_int);
 }
   
bool Event::trigger_any()
 {
  if( Dev::IsIntContext() )
    return trigger_int();
  else
    return trigger();
 }
   
bool Event::try_wait()
 {
  Dev::IntLock lock;
  
  if( flag )
    {
     flag=false;
     
     event(Task::GetCurrent(),EventEvent_task::Consume);
     
     Log("#; is consumed by #;",name,GetTaskName(CurTaskContext));
       
     return true;
    }
  else
    {
     return false;
    }
 }

void Event::wait()
 {
  Dev::IntLock lock;
  
  if( flag )
    {
     flag=false;
     
     event(Task::GetCurrent(),EventEvent_task::Consume);
     
     Log("#; is consumed by #;",name,GetTaskName(CurTaskContext));
    }
  else
    {
     event(Task::GetCurrent(),EventEvent_task::Block);
    
     Log("#; is blocked on #;",GetTaskName(CurTaskContext),name);
       
     Task::Internal::BlockTask_task(list);
    }
 }
   
bool Event::wait(MSec timeout)
 {
  Dev::IntLock lock;

  return wait_locked(timeout);
 }
   
bool Event::wait(TimeScope time_scope)
 {
  Dev::IntLock lock;
  
  auto timeout=time_scope.get();
  
  if( !timeout ) return false;
  
  return wait_locked(timeout);
 }
  
} // namespace CCore
 

