/* MultiSem.cpp */ 
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
 
#include <CCore/inc/task/MultiSem.h>
 
#include <CCore/inc/task/TaskCore.h>

#include <CCore/inc/sys/SysLog.h>

#include <CCore/inc/Abort.h>

namespace CCore {

/* struct MultiSemNumber */

EventIdType MultiSemNumber::Register(EventMetaInfo &info)
 {
  return info.addEnum_uint16("MultiSemNumber")
             .setAppendFunc(EventEnumValue<MultiSemNumber>::Append)
             .getId();
 }

/* struct MultiSemEvent */

void MultiSemEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Type=info.addEnum_uint8("MultiSemEventType")
                   .addValueName(Give,"Give",EventMarker_Up)
                   .getId();
  
  auto id=info.addStruct("MultiSemEvent")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint16(EventTypeId<MultiSemNumber>::GetId(),"msem",Offset_msem)
              .addField_enum_uint8(id_Type,"type",Offset_type)
              .addField_uint8("index",Offset_index)
              .getId();
  
  desc.setStructId(info,id);
 }

/* struct MultiSemEvent_task */

void MultiSemEvent_task::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Type=info.addEnum_uint8("MultiSemEventTaskType")
                   .addValueName(ToTask,"ToTask",EventMarker_UpPush)
                   .addValueName(Take,"Take",EventMarker_Down)
                   .addValueName(Block,"Block",EventMarker_DownBlock)
                   .getId();
  
  auto id=info.addStruct("MultiSemEventTask")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint16(EventTypeId<TaskNumber>::GetId(),"task",Offset_task)
              .addField_enum_uint16(EventTypeId<MultiSemNumber>::GetId(),"msem",Offset_msem)
              .addField_enum_uint8(id_Type,"type",Offset_type)
              .addField_uint8("index",Offset_index)
              .getId();
  
  desc.classId<MultiSemEvent>();
  
  desc.setStructId(info,id);
 }

/* class MultiSemBase */ 

AutoTextNameType MultiSemBase::ObjName="MultiSem";
 
void MultiSemBase::event(TaskBase *task,MultiSemEvent_task::Type type,ulen index)
 {
  TaskEventHost.addSync<MultiSemEvent_task>(task->getTaskNumber(),msem_number,type,index);
 }

void MultiSemBase::event(MultiSemEvent::Type type,ulen index)
 {
  TaskEventHost.addSync<MultiSemEvent>(msem_number,type,index);
 }
 
template <class ... TT> 
void MultiSemBase::Log(const char *format,const TT & ... tt)
 {
  Sys::Log(Sys::LogSourceMultiSem|Sys::LogEvent,format,tt...);
 }
 
void MultiSemBase::init(PtrLen<ulen> counts_)
 {
  counts=counts_;
  base=0;
  
  counts_.set_null();
 }
 
void MultiSemBase::putIndex(ulen index)
 {
  if( UIntInc(counts[index-1]) ) Abort("Fatal error : CCore::MultiSem counter overflow");
 }
   
template <class T,class F>
void MultiSemBase::give_locked(T cur,F Release,ulen index)
 {
  if( TaskBase *task=list.get() )
    {
     base=nextIndex(base);
     
     event(task,MultiSemEvent_task::ToTask,index);
     
     Log("#;:#; is given by #; to #;",name,index,GetTaskName(cur),task->getName());
     
     Release(task,Release_Custom+index);
    }
  else
    {
     event(MultiSemEvent::Give,index);
     
     Log("#;:#; is given by #;",name,index,GetTaskName(cur));
     
     putIndex(index);
    }  
 }

ulen MultiSemBase::try_take_locked()
 {
  ulen index=base;
     
  for(ulen cnt=counts.len; cnt ;cnt--,index=nextIndex(index))
    {
     if( counts[index] )
       {
        counts[index]--;
        
        base=nextIndex(base);
        
        index++;
        
        event(Task::GetCurrent(),MultiSemEvent_task::Take,index);
        
        Log("#;:#; is taken by #;",name,index,GetTaskName(CurTaskContext));
        
        return index;
       }
    }
  
  return 0;
 }

ulen MultiSemBase::take_locked(MSec timeout)
 {
  if( ulen index=try_take_locked() ) return index;
  
  event(Task::GetCurrent(),MultiSemEvent_task::Block);
     
  Log("#; is blocked on #; timed = #;",GetTaskName(CurTaskContext),name,timeout);
       
  if( ReleaseCode code=Task::Internal::BlockTask_task(list,timeout) ) return code-Release_Custom;
    
  return 0;  
 }

MultiSemBase::MultiSemBase(PtrLen<ulen> counts)
 : name(GetAutoText<ObjName>()),
   msem_number(name)
 {
  init(counts);
 }
   
MultiSemBase::MultiSemBase(TextLabel name_,PtrLen<ulen> counts)
 : name(name_),
   msem_number(name)
 {
  init(counts);
 }
 
MultiSemBase::~MultiSemBase()
 {
 }
 
void MultiSemBase::give(ulen index)
 {
  if( index==0 || index>counts.len ) Abort("Fatal error : CCore::MultiSem bad index");
 
  Dev::IntLock lock;
  
  return give_locked(CurTaskContext,Task::Internal::ReleaseTask_task,index);
 }
   
void MultiSemBase::give_int(ulen index)
 {
  if( index==0 || index>counts.len ) Abort("Fatal error : CCore::MultiSem bad index");
  
  return give_locked(InterruptContext,Task::Internal::ReleaseTask_int,index);
 }
   
void MultiSemBase::give_any(ulen index)
 {
  if( Dev::IsIntContext() )
    give_int(index);
  else
    give(index);
 }
   
ulen MultiSemBase::try_take()
 {
  Dev::IntLock lock;
  
  return try_take_locked();
 }

ulen MultiSemBase::take()
 {
  Dev::IntLock lock;
  
  if( ulen index=try_take_locked() ) return index;
  
  event(Task::GetCurrent(),MultiSemEvent_task::Block);
  
  Log("#; is blocked on #;",GetTaskName(CurTaskContext),name);
       
  return Task::Internal::BlockTask_task(list)-Release_Custom;
 }
   
ulen MultiSemBase::take(MSec timeout)
 {
  Dev::IntLock lock;
  
  return take_locked(timeout);
 }
   
ulen MultiSemBase::take(TimeScope time_scope)
 {
  Dev::IntLock lock;
  
  auto timeout=time_scope.get();
  
  if( !timeout ) return 0;
  
  return take_locked(timeout);
 }
 
} // namespace CCore
 

