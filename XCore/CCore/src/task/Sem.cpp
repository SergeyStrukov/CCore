/* Sem.cpp */ 
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
 
#include <CCore/inc/task/Sem.h>

#include <CCore/inc/task/TaskCore.h>

#include <CCore/inc/sys/SysLog.h>

#include <CCore/inc/Abort.h>

namespace CCore {

/* struct SemNumber */

EventIdType SemNumber::Register(EventMetaInfo &info)
 {
  return info.addEnum_uint16("SemNumber")
             .setAppendFunc(EventEnumValue<SemNumber>::Append)
             .getId();
 }

/* struct SemEvent */

void SemEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Type=info.addEnum_uint8("SemEventType")
                   .addValueName(ToTaskList,"ToTaskList")
                   .addValueName(Inc,"Inc")
                   .addValueName(Add,"Add")
                   .getId();
  
  auto id=info.addStruct("SemEvent")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint16(EventTypeId<SemNumber>::GetId(),"sem",Offset_sem)
              .addField_enum_uint8(id_Type,"type",Offset_type)
              .getId();
  
  desc.setStructId(info,id);
 }

/* struct SemEvent_task */

void SemEvent_task::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Type=info.addEnum_uint8("SemEventTaskType")
                   .addValueName(ToTask,"ToTask")
                   .addValueName(Dec,"Dec")
                   .addValueName(Block,"Block")
                   .getId();
  
  auto id=info.addStruct("SemEventTask")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint16(EventTypeId<TaskNumber>::GetId(),"task",Offset_task)
              .addField_enum_uint16(EventTypeId<SemNumber>::GetId(),"sem",Offset_sem)
              .addField_enum_uint8(id_Type,"type",Offset_type)
              .getId();
  
  desc.setStructId(info,id);
 }

/* class Sem */ 

AutoTextNameType Sem::ObjName="Sem";

void Sem::event(TaskBase *task,SemEvent_task::Type type)
 {
  TaskEventHost.addSync<SemEvent_task>(task->getTaskNumber(),sem_number,type);
 }

void Sem::event(SemEvent::Type type)
 {
  TaskEventHost.addSync<SemEvent>(sem_number,type);
 }

template <class ... TT> 
void Sem::Log(const char *format,const TT & ... tt)
 {
  Sys::Log(Sys::LogSourceSem|Sys::LogEvent,format,tt...);
 }
 
void Sem::init(ulen count_)
 {
  count=count_;
 }
   
void Sem::inc()
 {
  if( UIntInc(count) ) Abort("Fatal error : CCore::Sem counter inc overflow");
 }
 
void Sem::add(ulen dcount)
 {
  if( UIntAdd(count,dcount) ) Abort("Fatal error : CCore::Sem counter add overflow");
 }
 
template <class T,class F>
void Sem::give_locked(T cur,F Release)
 {
  if( count )
    {
     event(SemEvent::Inc);
    
     Log("#; is given by #;",name,GetTaskName(cur));
     
     inc();
    } 
  else
    {
     TaskBase *task=list.get();
     
     if( task )
       {
        event(task,SemEvent_task::ToTask);
        
        Log("#; is given by #; to #;",name,GetTaskName(cur),task->getName());
     
        Release(task,Release_Ok);
       }
     else
       {
        count=1;
        
        event(SemEvent::Inc);
        
        Log("#; is given by #;",name,GetTaskName(cur));
       }
    }  
 }

template <class T,class F>
void Sem::give_many_locked(T cur,F Release,ulen dcount)
 {
  if( count )
    {
     event(SemEvent::Add);
    
     Log("#; is given by #; #; times",name,GetTaskName(cur),dcount);
     
     add(dcount);
    } 
  else
    {
     if( +list )
       {
        TaskList temp(list,dcount);
       
        count=dcount;
           
        event(SemEvent::ToTaskList);
       
        Log("#; is given by #; #; times",name,GetTaskName(cur),dcount);
     
        Release(temp,Release_Ok,name);
       }
     else
       {
        count=dcount;
        
        event(SemEvent::Add);
       
        Log("#; is given by #; #; times",name,GetTaskName(cur),dcount);
       }
    }  
 }

bool Sem::take_locked(MSec timeout)
 {
  if( count )
    {
     count--;
     
     event(Task::GetCurrent(),SemEvent_task::Dec);
     
     Log("#; is taken by #;",name,GetTaskName(CurTaskContext));
       
     return true;
    }
  else
    {
     event(Task::GetCurrent(),SemEvent_task::Block);
     
     Log("#; is blocked on #; timed = #;",GetTaskName(CurTaskContext),name,timeout);
       
     return Task::Internal::BlockTask_task(list,timeout)==Release_Ok;
    }
 }

Sem::Sem(ulen count)
 : name(GetAutoText<ObjName>()),
   sem_number(name)
 {
  init(count);
 }
 
Sem::Sem(TextLabel name_,ulen count)
 : name(name_),
   sem_number(name)
 {
  init(count);
 }
 
Sem::~Sem()
 {
 }
 
void Sem::give()
 {
  Dev::IntLock lock;
  
  give_locked(CurTaskContext,Task::Internal::ReleaseTask_task);
 }
   
void Sem::give_int()
 {
  give_locked(InterruptContext,Task::Internal::ReleaseTask_int);
 }
   
void Sem::give_any()
 {
  if( Dev::IsIntContext() )
    give_int();
  else
    give();
 }
   
void Sem::give_many(ulen dcount)
 {
  Dev::IntLock lock;
  
  give_many_locked(CurTaskContext,Task::Internal::ReleaseTaskList_task,dcount);
 }
   
void Sem::give_many_int(ulen dcount)
 {
  give_many_locked(InterruptContext,Task::Internal::ReleaseTaskList_int,dcount);
 }
   
void Sem::give_many_any(ulen dcount)
 {
  if( Dev::IsIntContext() )
    give_many_int(dcount);
  else
    give_many(dcount);
 }
   
bool Sem::try_take()
 {
  Dev::IntLock lock;
  
  if( count )
    {
     count--;
     
     event(Task::GetCurrent(),SemEvent_task::Dec);
     
     Log("#; is taken by #;",name,GetTaskName(CurTaskContext));
       
     return true;
    }
  else
    {
     return false;
    }
 }
   
void Sem::take()
 {
  Dev::IntLock lock;
  
  if( count )
    {
     count--;
     
     event(Task::GetCurrent(),SemEvent_task::Dec);
     
     Log("#; is taken by #;",name,GetTaskName(CurTaskContext));
    }
  else
    {
     event(Task::GetCurrent(),SemEvent_task::Block);
     
     Log("#; is blocked on #;",GetTaskName(CurTaskContext),name);
       
     Task::Internal::BlockTask_task(list);
    }
 }
   
bool Sem::take(MSec timeout)
 {
  Dev::IntLock lock;
  
  return take_locked(timeout);
 }
   
bool Sem::take(TimeScope time_scope)
 {
  Dev::IntLock lock;
  
  auto timeout=time_scope.get();
  
  if( !timeout ) return false;
  
  return take_locked(timeout);
 }
 
} // namespace CCore
 

