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

/* class Sem */ 

AutoTextNameType Sem::ObjName="Sem";

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
     Log("#; is given by #;",name,GetTaskName(cur));
     
     inc();
    } 
  else
    {
     TaskBase *task=list.get();
     
     if( task )
       {
        Log("#; is given by #; to #;",name,GetTaskName(cur),task->getName());
     
        Release(task,Release_Ok);
       }
     else
       {
        count=1;
        
        Log("#; is given by #;",name,GetTaskName(cur));
       }
    }  
 }

template <class T,class F>
void Sem::give_many_locked(T cur,F Release,ulen dcount)
 {
  if( count )
    {
     Log("#; is given by #; #; times",name,GetTaskName(cur),dcount);
     
     add(dcount);
    } 
  else
    {
     if( +list )
       {
        TaskList temp(list,dcount);
       
        count=dcount;
           
        Log("#; is given by #; #; times",name,GetTaskName(cur),dcount);
     
        Release(temp,Release_Ok,name);
       }
     else
       {
        count=dcount;
        
        Log("#; is given by #; #; times",name,GetTaskName(cur),dcount);
       }
    }  
 }

bool Sem::take_locked(MSec timeout)
 {
  if( count )
    {
     count--;
     
     Log("#; is taken by #;",name,GetTaskName(CurTaskContext));
       
     return true;
    }
  else
    {
     Log("#; is blocked on #; timed = #;",GetTaskName(CurTaskContext),name,timeout);
       
     return Task::Internal::BlockTask_task(list,timeout)==Release_Ok;
    }
 }

Sem::Sem(ulen count)
 : name(GetAutoText<ObjName>())
 {
  init(count);
 }
 
Sem::Sem(TextLabel name_,ulen count)
 : name(name_)
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
     
     Log("#; is taken by #;",name,GetTaskName(CurTaskContext));
    }
  else
    {
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
 

