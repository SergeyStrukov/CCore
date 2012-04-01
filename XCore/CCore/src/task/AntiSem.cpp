/* AntiSem.cpp */ 
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
 
#include <CCore/inc/task/AntiSem.h>
 
#include <CCore/inc/task/TaskCore.h>

#include <CCore/inc/sys/SysLog.h>

#include <CCore/inc/Abort.h>

namespace CCore {

/* class AntiSem */ 

AutoTextNameType AntiSem::ObjName="AntiSem";

template <class ... TT> 
void AntiSem::Log(const char *format,const TT & ... tt)
 {
  Sys::Log(Sys::LogSourceAntiSem|Sys::LogEvent,format,tt...);
 }
 
void AntiSem::init(ulen level_)
 {
  count=0;
  level=level_;
 }
 
void AntiSem::add_count(ulen dcount)
 {
  if( UIntAdd(count,dcount) ) Abort("Fatal error: CCore::AntiSem counter overflow");
 }
   
void AntiSem::sub_count(ulen dcount)
 {
  if( UIntSub(count,dcount) ) Abort("Fatal error: CCore::AntiSem counter underflow");
 }
 
template <class T>
void AntiSem::add_locked(T cur,ulen dcount)
 {
  Log("#; (#;) += #; by #;",name,count,dcount,GetTaskName(cur));
  
  add_count(dcount);
 }

template <class T,class F>
void AntiSem::sub_locked(T cur,F Release,ulen dcount)
 {
  Log("#; (#;) -= #; by #;",name,count,dcount,GetTaskName(cur));
  
  sub_count(dcount);
    
  if( count<=level )
    {
     Release(list,Release_Ok,name);
    }
 }

bool AntiSem::wait_locked(MSec timeout)
 {
  if( count<=level )
    {
     Log("#; don't block #;",name,GetTaskName(CurTaskContext));
     
     return true;
    }
  else
    {
     Log("#; block #; timed = #;",name,GetTaskName(CurTaskContext),timeout);
     
     return Task::Internal::BlockTask_task(list,timeout)==Release_Ok;
    }
 }

AntiSem::AntiSem(ulen level)
 : name(GetAutoText<ObjName>())
 {
  init(level);
 }
   
AntiSem::AntiSem(TextLabel name_,ulen level)
 : name(name_)
 {
  init(level);
 }
 
AntiSem::~AntiSem()
 {
 }
 
void AntiSem::add(ulen dcount)
 {
  Dev::IntLock lock;
  
  add_locked(CurTaskContext,dcount);
 }
   
void AntiSem::sub(ulen dcount)
 {
  Dev::IntLock lock;
  
  sub_locked(CurTaskContext,Task::Internal::ReleaseTaskList_task,dcount);
 }
   
void AntiSem::add_int(ulen dcount)
 {
  add_locked(InterruptContext,dcount);
 }
   
void AntiSem::sub_int(ulen dcount)
 {
  sub_locked(InterruptContext,Task::Internal::ReleaseTaskList_int,dcount);
 }
   
void AntiSem::add_any(ulen dcount)
 {
  if( Dev::IsIntContext() )
    add_int(dcount);
  else
    add(dcount);
 }
   
void AntiSem::sub_any(ulen dcount)
 {
  if( Dev::IsIntContext() )
    sub_int(dcount);
  else
    sub(dcount);
 }
   
bool AntiSem::try_wait()
 {
  Dev::IntLock lock;
  
  if( count<=level )
    {
     Log("#; don't block #;",name,GetTaskName(CurTaskContext));
     
     return true;
    }
  else
    {
     return false;
    }
 }

void AntiSem::wait()
 {
  Dev::IntLock lock;
  
  if( count<=level )
    {
     Log("#; don't block #;",name,GetTaskName(CurTaskContext));
    }
  else
    {
     Log("#; block #;",name,GetTaskName(CurTaskContext));
     
     Task::Internal::BlockTask_task(list);
    }
 }
   
bool AntiSem::wait(MSec timeout)
 {
  Dev::IntLock lock;
  
  return wait_locked(timeout);
 }
   
bool AntiSem::wait(TimeScope time_scope)
 {
  Dev::IntLock lock;
  
  auto timeout=time_scope.get();
  
  if( !timeout ) return false;
  
  return wait_locked(timeout);
 }
   
} // namespace CCore
 

