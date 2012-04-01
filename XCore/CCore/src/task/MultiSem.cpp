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

/* class MultiSemBase */ 

AutoTextNameType MultiSemBase::ObjName="MultiSem";
 
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
     
     Log("#;:#; is given by #; to #;",name,index,GetTaskName(cur),task->getName());
     
     Release(task,Release_Custom+index);
    }
  else
    {
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
        
        Log("#;:#; is taken by #;",name,index,GetTaskName(CurTaskContext));
        
        return index;
       }
    }
  
  return 0;
 }

ulen MultiSemBase::take_locked(MSec timeout)
 {
  if( ulen index=try_take_locked() ) return index;
     
  Log("#; is blocked on #; timed = #;",GetTaskName(CurTaskContext),name,timeout);
       
  if( ReleaseCode code=Task::Internal::BlockTask_task(list,timeout) ) return code-Release_Custom;
    
  return 0;  
 }

MultiSemBase::MultiSemBase(PtrLen<ulen> counts)
 : name(GetAutoText<ObjName>())
 {
  init(counts);
 }
   
MultiSemBase::MultiSemBase(TextLabel name_,PtrLen<ulen> counts)
 : name(name_)
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
 

