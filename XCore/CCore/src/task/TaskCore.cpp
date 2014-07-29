/* TaskCore.cpp */ 
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
 
#include <CCore/inc/task/TaskCore.h>

#include <CCore/inc/Abort.h>

#include <CCore/inc/sys/SysLog.h>
#include <CCore/inc/PerTask.h>
 
namespace CCore {

/* class Task */ 

AutoTextNameType Task::ObjName="Task";
 
Task * Task::Current=0;

void Task::entry() {}
   
void Task::exit() {}
 
void Task::tick()
 {
  if( ticks.tick() )
    {
     delList();
 
     Internal::ReleaseTask_int(this,Release_Timeout);
    }
 }
   
void Task::setTimer(MSec timeout)
 {
  ticks.set(+timeout);
  
  job.start();
 }
   
void Task::stopTimer()
 {
  job.stop();
 }
 
void Task::release(ReleaseCode code)
 {
  state=Task_Running;
  release_code=code;
  
  stopTimer();
 }
 
void Task::setForcedTimeout_task()
 {
  forced_timeout=true;
  
  if( state==Task_Blocked && job.isActive() )
    {
     delList();
 
     Internal::ReleaseTask_task(this,Release_Timeout);
    }
 }
   
void Task::setForcedTimeout_int()
 {
  forced_timeout=true;
  
  if( state==Task_Blocked && job.isActive() )
    {
     delList();
 
     Internal::ReleaseTask_int(this,Release_Timeout);
    }
 }
   
bool Task::clearForcedTimeout()
 {
  return Replace(forced_timeout,false);
 }
 
void Task::abort_wait()
 {
  Dev::IntLock lock;
  
  setForcedTimeout_task();
 }
    
void Task::abort_wait_int()
 {
  setForcedTimeout_int();
 }
   
void Task::abort_wait_any()
 {
  if( Dev::IsIntContext() )
    abort_wait_int();
  else
    abort_wait();
 }
 
Task::Task(MainTaskCtorType)
 : TaskBase("!MainTask",MainTaskPriority),
   job(function_tick())
 {
  if( Current ) Abort("Fatal error : main task initialization");
  
  stack=0;
  context=Internal::GetContext();
  
  state=Task_Running;
  release_code=Release_Ok;
  
  forced_timeout=false;
  
  Current=this;
 }
 
void Task::init(ulen stack_len)
 {
  release_code=Release_Ok;
  
  forced_timeout=false;
  
  stack_len=AlignDown(Max(stack_len,MinStackLen));
  
  stack=TryMemAlloc(stack_len);
  context=TryMemAlloc(Internal::GetContextLen());
     
  if( stack && context )
    {
     Internal::ContextInit(context,stack,stack_len,this);
     
     state=Task_Ready;
    }
  else
    {
     MemFree(stack);
     MemFree(context);
     
     stack=0;
     context=0;
     
     state=Task_NotReady;
    }
 }
  
bool Task::run() 
 {
  Dev::IntLock lock;
  
  switch( state )
    {
     case Task_Ready :
      {
       Internal::GuardRun();
       
       state=Task_Blocked;
    
       Internal::ReleaseTask_task(this,Release_Ok);
      }
     return true;
        
     case Task_NotReady : 
      {
       state=Task_Dead;
      }
     return false;
        
     default: 
      {
       Abort("Fatal error : task rerun"); 
      }
     return false;
    }
 }
 
void Task::guardStopped()
 {
  Dev::IntLock lock;
      
  if( state!=Task_Dead && state!=Task_Ready ) Abort("Fatal error : task is not stopped");
 }
 
void Task::Entry(Task *task)
 {
  try
    {
     DestroyPerTask dpt;
   
     task->entry();
    }
  catch(...)
    {
     Sys::Log(Sys::LogSourceTask|Sys::LogAlert,"task #; finished with exception",task->getName());
    }
    
  Internal::Stop(task);  
 }
 
Task::Task(TaskPriority priority,ulen stack_len)
 : TaskBase(GetAutoText<ObjName>(),priority),
   job(function_tick())
 {
  init(stack_len);
 }
   
Task::Task(TextLabel name,TaskPriority priority,ulen stack_len)
 : TaskBase(name,priority),
   job(function_tick())
 {
  init(stack_len);
 }
 
Task::~Task() 
 {  
  guardList();
  
  if( context )
    {
     if( stack )
       {
        guardStopped();
        
        MemFree(stack);
        MemFree(context);
       }
     else // main task
       {
        Dev::IntLock lock;
        
        Current=0;
       }
    }
 }
   
bool Task::run_or_exit()
 {
  if( run() ) return true;
  
  exit();
  
  return false;
 }
  
/* class ForcedTimeout */  

bool ForcedTimeout::clear()
 {
  Dev::IntLock lock;
  
  return task->clearForcedTimeout();
 }
 
} // namespace CCore
 

