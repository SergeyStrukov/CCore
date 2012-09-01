/* Mutex.cpp */ 
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
 
#include <CCore/inc/task/Mutex.h>

#include <CCore/inc/task/TaskCore.h>

#include <CCore/inc/sys/SysLog.h>

namespace CCore {

/* struct MutexNumber */

EventIdType MutexNumber::Register(EventMetaInfo &info)
 {
  return info.addEnum_uint16("MutexNumber")
             .setAppendFunc(EventEnumValue<MutexNumber>::Append)
             .getId();
 }

/* struct MutexEvent */

void MutexEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Type=info.addEnum_uint8("MutexEventType")
                   .addValueName(Lock,"Lock")
                   .addValueName(Unlock,"Unlock")
                   .addValueName(IncLock,"IncLock")
                   .addValueName(DecLock,"DecLock")
                   .addValueName(Block,"Block")
                   .getId();
  
  auto id=info.addStruct("MutexEvent")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint16(EventTypeId<TaskNumber>::GetId(),"task",Offset_task)
              .addField_enum_uint16(EventTypeId<MutexNumber>::GetId(),"mutex",Offset_mutex)
              .addField_enum_uint8(id_Type,"type",Offset_type)
              .getId();
  
  desc.setStructId(info,id);
 }

/* class Mutex */ 

AutoTextNameType Mutex::ObjName="Mutex";
 
void Mutex::event(TaskBase *task,MutexEvent::Type type)
 {
  TaskEventHost.addSync<MutexEvent>(task->getTaskNumber(),mutex_number,type);
 }

template <class ... TT> 
void Mutex::Log(const char *format,const TT & ... tt)
 {
  Sys::Log(Sys::LogSourceMutex|Sys::LogEvent,format,tt...);
 }
 
void Mutex::init()
 {
  count=0;
 }
 
Mutex::Mutex()
 : name(GetAutoText<ObjName>()),
   mutex_number(name)
 {
  init();
 }
   
Mutex::Mutex(TextLabel name_)
 : name(name_),
   mutex_number(name)
 {
  init();
 }
  
Mutex::~Mutex()
 {
 }
 
void Mutex::lock()
 {
  Dev::IntLock lock;

  TaskBase *cur=Task::GetCurrent();
     
  if( count )
    {
     if( list.getOwner()==cur )
       {
        count++;
        
        event(cur,MutexEvent::IncLock);
       }
     else
       {
        event(cur,MutexEvent::Block);
        
        Log("#; is blocked on #;",cur->getName(),name);
        
        Task::Internal::BlockTask_task(list);
       }  
    }
  else
    {
     count=1;
     
     list.setOwner(cur);
     
     event(cur,MutexEvent::Lock);
        
     Log("#; is locked by #;",name,cur->getName());
    }
 }
  
void Mutex::unlock()
 {
  Dev::IntLock lock;

  TaskBase *cur=Task::GetCurrent();
 
  if( !--count )
    {
     list.clearOwner(cur);

     event(cur,MutexEvent::Unlock);
     
     TaskBase *task=list.get();

     if( task )
       {
        count=1;
        
        list.setOwner(task);

        event(task,MutexEvent::Lock);
        
        Log("#; is relocked by #;",name,task->getName());
        
        Task::Internal::ReleaseTask_task(task,Release_Ok);
       }
     else
       {
        Log("#; is unlocked by #;",name,cur->getName());
       } 
    }
  else
    {
     event(cur,MutexEvent::DecLock);
    }
 }
 
} // namespace CCore
 

