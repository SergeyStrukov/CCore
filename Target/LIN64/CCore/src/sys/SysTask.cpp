/* SysTask.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysTask.h>
#include <CCore/inc/sys/SysAbort.h>
 
#include <pthread.h>
#include <time.h>

namespace CCore {
namespace Sys {

/* functions */ 

static_assert( std::is_same<pthread_t,TaskIdType>::value ,"CCore::Sys::TaskIdType != pthread_t");

void YieldTask() noexcept 
 { 
  AbortIfError( pthread_yield() ,"CCore::Sys::YieldTask()");
 }
 
void SleepTask(MSec time) noexcept 
 {
  struct timespec reqtime;
  
  reqtime.tv_sec=(+time/1000);
  reqtime.tv_nsec=(+time%1000)*1000000;
  
  AbortIf( nanosleep(&reqtime,NULL)!=0 ,"CCore::Sys::SleepTask()");
 }
 
TaskIdType GetTaskId() noexcept 
 { 
  return pthread_self();
 }
 
/* struct TaskEntry */

void * TaskEntry::Entry(void *obj_)
 {
  TaskEntry *obj=static_cast<TaskEntry *>(obj_);
  
  obj->entry(obj);
  
  return 0;
 }

ErrorType TaskEntry::create() noexcept
 {
  pthread_t tid;

  return ErrorType( pthread_create(&tid,0,Entry,this) );
 }
  
} // namespace Sys
} // namespace CCore
 

