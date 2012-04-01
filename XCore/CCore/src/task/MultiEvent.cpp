/* MultiEvent.cpp */ 
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
 
#include <CCore/inc/task/MultiEvent.h>
 
#include <CCore/inc/task/TaskCore.h>

#include <CCore/inc/sys/SysLog.h>

#include <CCore/inc/Abort.h>

namespace CCore {

/* class MultiEventBase */ 

AutoTextNameType MultiEventBase::ObjName="MultiEvent";
 
template <class ... TT> 
void MultiEventBase::Log(const char *format,const TT & ... tt)
 {
  Sys::Log(Sys::LogSourceMultiEvent|Sys::LogEvent,format,tt...);
 }
 
void MultiEventBase::init(PtrLen<bool> flags_)
 {
  flags=flags_;
  base=0;
  
  flags_.set_null();
 }
 
template <class T,class F>
bool MultiEventBase::trigger_locked(T cur,F Release,ulen index)
 {
  if( TaskBase *task=list.get() )
    {
     base=nextIndex(base);
     
     Log("#;:#; is triggered by #; to #;",name,index,GetTaskName(cur),task->getName());
     
     Release(task,Release_Custom+index);
     
     return true;
    }
  else
    {
     if( flags[index-1] ) return false;
    
     flags[index-1]=true;
     
     Log("#;:#; is triggered by #;",name,index,GetTaskName(cur));
     
     return true;
    }  
 }

ulen MultiEventBase::try_wait_locked()
 {
  ulen index=base;
     
  for(ulen cnt=flags.len; cnt ;cnt--,index=nextIndex(index))
    {
     if( flags[index] )
       {
        flags[index]=false;
        
        base=nextIndex(base);
        
        index++;
        
        Log("#;:#; is consumed by #;",name,index,GetTaskName(CurTaskContext));
        
        return index;
       }
    }
  
  return 0;
 }

ulen MultiEventBase::wait_locked(MSec timeout)
 {
  if( ulen index=try_wait_locked() ) return index;
  
  Log("#; is blocked on #; timed = #;",GetTaskName(CurTaskContext),name,timeout);
       
  if( ReleaseCode code=Task::Internal::BlockTask_task(list,timeout) ) return code-Release_Custom;
    
  return 0;  
 }

MultiEventBase::MultiEventBase(PtrLen<bool> flags)
 : name(GetAutoText<ObjName>())
 {
  init(flags);
 }
   
MultiEventBase::MultiEventBase(TextLabel name_,PtrLen<bool> flags)
 : name(name_)
 {
  init(flags);
 }
 
MultiEventBase::~MultiEventBase()
 {
 }
 
bool MultiEventBase::trigger(ulen index)
 {
  if( index==0 || index>flags.len ) Abort("Fatal error : CCore::MultiEvent bad index");
 
  Dev::IntLock lock;
  
  return trigger_locked(CurTaskContext,Task::Internal::ReleaseTask_task,index);
 }
   
bool MultiEventBase::trigger_int(ulen index)
 {
  if( index==0 || index>flags.len ) Abort("Fatal error : CCore::MultiEvent bad index");
  
  return trigger_locked(InterruptContext,Task::Internal::ReleaseTask_int,index);
 }
   
bool MultiEventBase::trigger_any(ulen index)
 {
  if( Dev::IsIntContext() )
    return trigger_int(index);
  else
    return trigger(index);
 }

ulen MultiEventBase::try_wait()
 {
  Dev::IntLock lock;
  
  return try_wait_locked();
 }
   
ulen MultiEventBase::wait()
 {
  Dev::IntLock lock;
  
  if( ulen index=try_wait_locked() ) return index;
     
  Log("#; is blocked on #;",GetTaskName(CurTaskContext),name);
       
  return Task::Internal::BlockTask_task(list)-Release_Custom;
 }
   
ulen MultiEventBase::wait(MSec timeout)
 {
  Dev::IntLock lock;

  return wait_locked(timeout);
 }
   
ulen MultiEventBase::wait(TimeScope time_scope)
 {
  Dev::IntLock lock;
  
  auto timeout=time_scope.get();
  
  if( !timeout ) return 0;

  return wait_locked(timeout);
 }
   
} // namespace CCore
 

