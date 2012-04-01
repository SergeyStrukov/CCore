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

/* class Mutex */ 

AutoTextNameType Mutex::ObjName="Mutex";
 
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
 : name(GetAutoText<ObjName>())
 {
  init();
 }
   
Mutex::Mutex(TextLabel name_)
 : name(name_)
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
       }
     else
       {
        Log("#; is blocked on #;",cur->getName(),name);
        
        Task::Internal::BlockTask_task(list);
       }  
    }
  else
    {
     count=1;
     
     list.setOwner(cur);
        
     Log("#; is locked by #;",name,cur->getName());
    }
 }
  
void Mutex::unlock()
 {
  Dev::IntLock lock;

  if( !--count )
    {
     TaskBase *cur=Task::GetCurrent();
    
     list.clearOwner(cur);
     
     TaskBase *task=list.get();

     if( task )
       {
        count=1;
        
        list.setOwner(task);
        
        Log("#; is relocked by #;",name,task->getName());
        
        Task::Internal::ReleaseTask_task(task,Release_Ok);
       }
     else
       {
        Log("#; is unlocked by #;",name,cur->getName());
       } 
    }
 }
 
} // namespace CCore
 

