/* ResSem.cpp */ 
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
 
#include <CCore/inc/task/ResSem.h>
 
#include <CCore/inc/task/TaskCore.h>

#include <CCore/inc/sys/SysLog.h>

#include <CCore/inc/Abort.h>

namespace CCore {

/* struct ResSemNumber */

EventIdType ResSemNumber::Register(EventMetaInfo &info)
 {
  return info.addEnum_uint16("ResSemNumber")
             .setAppendFunc(EventEnumValue<ResSemNumber>::Append)
             .getId();
 }

/* struct ResSemEvent */

void ResSemEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Type=info.addEnum_uint8("ResSemEventType")
                   .addValueName(Give,"Give")
                   .getId();
  
  auto id=info.addStruct("ResSemEvent")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint16(EventTypeId<ResSemNumber>::GetId(),"rsem",Offset_rsem)
              .addField_enum_uint8(id_Type,"type",Offset_type)
              .getId();
  
  desc.setStructId(info,id);
 }

/* struct ResSemEvent_task */

void ResSemEvent_task::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Type=info.addEnum_uint8("ResSemEventTaskType")
                   .addValueName(ToTask,"ToTask")
                   .addValueName(Wait,"Wait")
                   .addValueName(Pass,"Pass")
                   .addValueName(Block,"Block")
                   .addValueName(Take,"Take")
                   .getId();
  
  auto id=info.addStruct("ResSemEventTask")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint16(EventTypeId<TaskNumber>::GetId(),"task",Offset_task)
              .addField_enum_uint16(EventTypeId<ResSemNumber>::GetId(),"rsem",Offset_rsem)
              .addField_enum_uint8(id_Type,"type",Offset_type)
              .getId();
  
  desc.setStructId(info,id);
 }

/* class ResSem */ 

AutoTextNameType ResSem::ObjName="ResSem";
 
void ResSem::event(TaskBase *task,ResSemEvent_task::Type type)
 {
  TaskEventHost.addSync<ResSemEvent_task>(task->getTaskNumber(),rsem_number,type);
 }
 
void ResSem::event(ResSemEvent::Type type)
 {
  TaskEventHost.addSync<ResSemEvent>(rsem_number,type);
 }

template <class ... TT> 
void ResSem::Log(const char *format,const TT & ... tt)
 {
  Sys::Log(Sys::LogSourceResSem|Sys::LogEvent,format,tt...);
 }
 
void ResSem::init(ulen max_count_)
 {
  if( max_count_==0 ) Abort("Fatal error : CCore::ResSem initialization");
 
  count=0;
  max_count=max_count_;
 }
 
template <class T,class F,class FL>
void ResSem::give_locked(T cur,F Release,FL ReleaseList)
 {
  if( count==0 ) Abort("Fatal error : CCore::ResSem underflow");
  
  if( count<max_count )  
    {
     count--;
     
     event(ResSemEvent::Give);
     
     Log("#; is given by #;",name,GetTaskName(cur));
    }
  else
    {
     if( TaskBase *task=take_list.get() )  
       {
        event(task,ResSemEvent_task::ToTask);
       
        Log("#; is given by #; to #;",name,GetTaskName(cur),task->getName());
       
        Release(task,Release_Ok);
        
        return; // count == max_count , !=0
       }
     else
       {
        count--;
        
        event(ResSemEvent::Give);
        
        Log("#; is given by #;",name,GetTaskName(cur));
       }
    }  
    
  if( count==0 )  
    {
     ReleaseList(wait_list,Release_Ok,name);
    }
 }

bool ResSem::take_locked(MSec timeout)
 {
  if( count<max_count )
    {
     count++;
     
     event(Task::GetCurrent(),ResSemEvent_task::Take);
     
     Log("#; is taken by #;",name,GetTaskName(CurTaskContext));
    
     return true;
    }
  else
    {
     event(Task::GetCurrent(),ResSemEvent_task::Block);
     
     Log("#; is blocked on #; timed = #;",GetTaskName(CurTaskContext),name,timeout);
    
     return Task::Internal::BlockTask_task(take_list,timeout)==Release_Ok;
    }  
 }

bool ResSem::wait_locked(MSec timeout)
 {
  if( count==0 )
    {
     event(Task::GetCurrent(),ResSemEvent_task::Pass);
     
     Log("#; don't block #;",name,GetTaskName(CurTaskContext));
     
     return true;
    }
  else
    {
     event(Task::GetCurrent(),ResSemEvent_task::Wait);
     
     Log("#; block #; timed = #;",name,GetTaskName(CurTaskContext),timeout);
     
     return Task::Internal::BlockTask_task(wait_list,timeout)==Release_Ok;
    }
 }

ResSem::ResSem(ulen max_count)
 : name(GetAutoText<ObjName>()),
   rsem_number(name)
 {
  init(max_count);
 }
   
ResSem::ResSem(TextLabel name_,ulen max_count)
 : name(name_),
   rsem_number(name)
 {
  init(max_count);
 }
 
ResSem::~ResSem()
 {
 }
 
void ResSem::give()
 {
  Dev::IntLock lock;
  
  give_locked(CurTaskContext,Task::Internal::ReleaseTask_task,Task::Internal::ReleaseTaskList_task);
 }
  
void ResSem::give_int()
 {
  give_locked(InterruptContext,Task::Internal::ReleaseTask_int,Task::Internal::ReleaseTaskList_int);
 }

void ResSem::give_any()
 {
  if( Dev::IsIntContext() )
    give_int();
  else
    give();
 }

bool ResSem::try_take()
 {
  Dev::IntLock lock;
  
  if( count<max_count )
    {
     count++;
     
     event(Task::GetCurrent(),ResSemEvent_task::Take);
     
     Log("#; is taken by #;",name,GetTaskName(CurTaskContext));
    
     return true;
    }
  else
    {
     return false;
    }  
 }
  
void ResSem::take()
 {
  Dev::IntLock lock;
  
  if( count<max_count )
    {
     count++;
     
     event(Task::GetCurrent(),ResSemEvent_task::Take);
     
     Log("#; is taken by #;",name,GetTaskName(CurTaskContext));
    }
  else
    {
     event(Task::GetCurrent(),ResSemEvent_task::Block);
     
     Log("#; is blocked on #;",GetTaskName(CurTaskContext),name);
    
     Task::Internal::BlockTask_task(take_list);
    }  
 }
  
bool ResSem::take(MSec timeout)
 {
  Dev::IntLock lock;
  
  return take_locked(timeout);
 }
  
bool ResSem::take(TimeScope time_scope)
 {
  Dev::IntLock lock;
  
  auto timeout=time_scope.get();
  
  if( !timeout ) return false;
  
  return take_locked(timeout);
 }
   
bool ResSem::try_wait()
 {
  Dev::IntLock lock;
  
  if( count==0 )
    {
     event(Task::GetCurrent(),ResSemEvent_task::Pass);
    
     Log("#; don't block #;",name,GetTaskName(CurTaskContext));
     
     return true;
    }
  else
    {
     return false;
    }
 }

void ResSem::wait()
 {
  Dev::IntLock lock;
  
  if( count==0 )
    {
     event(Task::GetCurrent(),ResSemEvent_task::Pass);
    
     Log("#; don't block #;",name,GetTaskName(CurTaskContext));
    }
  else
    {
     event(Task::GetCurrent(),ResSemEvent_task::Wait);
    
     Log("#; block #;",name,GetTaskName(CurTaskContext));
     
     Task::Internal::BlockTask_task(wait_list);
    }
 }
  
bool ResSem::wait(MSec timeout)
 {
  Dev::IntLock lock;
  
  return wait_locked(timeout);
 }
   
bool ResSem::wait(TimeScope time_scope)
 {
  Dev::IntLock lock;
  
  auto timeout=time_scope.get();
  
  if( !timeout ) return false;
  
  return wait_locked(timeout);
 }
   
} // namespace CCore
 

