/* TaskInternal.cpp */ 
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

#include <CCore/inc/task/Atomic.h>
#include <CCore/inc/task/Sem.h>
#include <CCore/inc/task/AntiSem.h>
#include <CCore/inc/task/TaskEvent.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/CompletePacket.h>
#include <CCore/inc/PacketPool.h>

#include <CCore/inc/sys/SysLog.h>
#include <CCore/inc/sys/SysCon.h>
 
namespace CCore {

/* class Task::Internal */ 

template <class ... TT> 
void Task::Internal::Log(const char *format,const TT & ... tt)
 {
  Sys::Log(Sys::LogSourceTask|Sys::LogEvent,format,tt...);
 }
 
void Task::Internal::EntryTask(void *task)
 {
  Task::Entry(static_cast<Task *>(task));
 }
  
/* class Task::Internal::MainTask */ 
 
class Task::Internal::MainTask : public Task
 {
  public:
  
   MainTask() : Task(MainTaskCtor) {}
   
   virtual ~MainTask() {}
 };
 
/* class Task::Internal::ExitTask */  

class Task::Internal::ExitTask : public Task
 {
   TaskList list;
   Atomic stop_flag;
   Sem sem;
   Sem stop_sem;
   
  private:
  
   void put(Task *task)
    {
     Dev::IntLock lock;
      
     task->setDead();
     
     list.put(task);
    }
    
   TaskBase * get()
    {
     Dev::IntLock lock;
        
     return list.get();
    } 
 
  public:
  
   ExitTask()
    : Task("!ExitTask",ExitTaskPriority),
      sem("!ExitTask.sem"),
      stop_sem("!ExitTask.stop_sem")
    { 
    }
  
   virtual ~ExitTask() {}
   
   virtual void entry()
    {
     for(;;)
       {
        sem.take();
        
        TaskBase *task=get();
        
        if( task ) 
          {
           Exit(UpCast(task));
          }
        else 
          {
           if( stop_flag ) break;
          }
       }
    }
   
   void add(Task *task)
    {
     if( task==this ) 
       {
        {
         Dev::IntLock lock;
         
         task->setDead();
        }
        
        stop_sem.give();  
       }
     else
       {
        put(task);
     
        sem.give();
       }
    }
    
   void stop()
    {
     stop_flag=1;
     
     sem.give();
     
     stop_sem.take();
     
     Exit(this);
    } 
 };
 
/* class Task::Internal::IdleTask */  

class Task::Internal::IdleTask : public Task
 {
   Atomic run_flag;
   Sem stop_sem;
 
  public:
  
   IdleTask()
    : Task("!IdleTask",IdleTaskPriority,MinStackLen),
      stop_sem("!IdleTask.stop_sem") 
    { 
     run_flag=1; 
    }
  
   virtual ~IdleTask() {}
   
   virtual void entry()
    {
     while( run_flag );
    }
    
   virtual void exit()
    {
     stop_sem.give();
    } 
    
   void stop()
    {
     run_flag=0;
     
     stop_sem.take();
    } 
 };
 
/* class Task::Internal::CompleteTask */     

class Task::Internal::CompleteTask : public Task
 {
   PacketList list;
   Atomic stop_flag;
   Sem sem;
   Sem stop_sem;
   
  private:
  
   PacketHeader * get()
    {
     Dev::IntLock lock;
     
     return list.get();
    }
 
  public:
  
   CompleteTask()
    : Task("!CompleteTask",CompleteTaskPriority),
      sem("!CompleteTask.sem"),
      stop_sem("!CompleteTask.stop_sem")
    {
    }
   
   virtual ~CompleteTask() {}
   
   virtual void entry()
    {
     for(;;)
       {
        sem.take();
        
        if( stop_flag ) return;
        
        if( PacketHeader *packet=get() ) packet->complete();
       }
    }
    
   virtual void exit()
    {
     stop_sem.give();
    } 
    
   void put_int(PacketHeader *packet)
    {
     list.put(packet);
     
     sem.give_int();
    }
    
   void stop()
    {
     stop_flag=1;
     
     sem.give();
     
     stop_sem.take();
    } 
    
   void complete()
    {
     while( PacketHeader *packet=get() ) packet->complete();
    }
 };
 
/* GetPlanInitNode_...() */ 

namespace Private_TaskInternal {

/* class Relax */

class Relax
 {
   unsigned period;
   unsigned tick;
   TaskPriority priority;
     
  public:
    
   Relax()
    {
     period=0;
     tick=0;
     priority=ExitTaskPriority;
    }
      
   TaskPriority getPriority() const { return priority; }
      
   void set(unsigned period_,TaskPriority priority_) 
    {
     period=period_;
     tick=1;
     priority=priority_;
    }
      
   bool do_tick()
    {
     if( !tick ) return false;
       
     if( !--tick && period )
       {
        tick=period;
             
        return true;
       }
         
     return false;  
    }
 };

/* struct Core */

struct Core
 {
  Task::Internal::MainTask main_task;
  
  AntiSem task_count;
  TaskList running_list;
  
  bool enable;
  Relax relax; 
  
  Core()
   : task_count("!TaskCount",3)
   {
    enable=false;
   }
   
  ~Core()
   {
   }
   
  void guardRun() 
   {
    if( !enable ) Abort("Fatal error : task run is not permitted");
    
    task_count.inc();
   }
   
  TaskBase * cycle(TaskBase *task)
   {
    running_list.put(task);
    
    return running_list.get();
   }
   
  TaskBase * cycle_tick(TaskBase *task,bool relax_on)
   {
    running_list.put(task);
     
    if( relax_on )
      {
       if( TaskBase *ret=running_list.get_relaxed(relax.getPriority()) ) return ret;
      } 
      
    return running_list.get();
   }
   
  static const char * GetTag() { return "TaskCore"; } 
 };
 
PlanInitObject<Core,PlanInitReq<GetPlanInitNode_TlsBuf>
                   ,PlanInitReq<GetPlanInitNode_Tick>
                   ,PlanInitReq<Sys::GetPlanInitNode_SysLog>
                   > Object CCORE_INITPRI_1 ;

/* struct CoreExt */
                   
struct CoreExt
 {
  Task::Internal::ExitTask exit_task;
  Task::Internal::IdleTask idle_task;
  Task::Internal::CompleteTask complete_task;
  
  CoreExt()
   {
   }
   
  ~CoreExt()
   {
   }
   
  void guardRun() 
   {
    Task *cur=Task::GetCurrent();
    
    if( cur==&exit_task ) Abort("Fatal error : ExitTask is not permitted to run another task");
    
    if( cur==&complete_task ) Abort("Fatal error : CompleteTask is not permitted to run another task"); 
   }
   
  void run()
   {
    if( !exit_task.run_or_exit() ) Abort("Fatal error : ExitTask is not ready");
    if( !idle_task.run_or_exit() ) Abort("Fatal error : IdleTask is not ready");
    if( !complete_task.run_or_exit() ) Abort("Fatal error : CompleteTask is not ready");
   }
   
  void stop()
   {
    complete_task.stop();
    idle_task.stop();
    exit_task.stop();
   }
   
  static const char * GetTag() { return "TaskCoreExt"; } 
 };
 
PlanInitObject<CoreExt,PlanInitReq<GetPlanInitNode_PacketPool> > ObjectExt CCORE_INITPRI_1 ;
                   
} // namespace Private_TaskInternal
 
using namespace Private_TaskInternal; 
 
PlanInitNode * GetPlanInitNode_TaskCore() { return &Object; }
 
PlanInitNode * GetPlanInitNode_TaskCoreExt() { return &ObjectExt; }
 
/* functions */ 

void CompletePacket_int(PacketHeader *packet)
 {
  ObjectExt->complete_task.put_int(packet);
 }
 
/* class Task::Internal */ 

void Task::Internal::GuardRun()
 {
  ObjectExt->guardRun();
  
  Object->guardRun();
 }
 
void Task::Internal::Stop(Task *task)
 {
  ObjectExt->exit_task.add(task);
  
  //
  // Dead task cannot be switched out in interrupt context. 
  //
  // It looses CPU forever in ReleaseTask_task above giving sem to Exit task or in loop below. 
  //
  
  for(;;)
    {
     Dev::IntLock lock;

     if( TaskBase *new_task=Object->running_list.get() )
       {
        SwitchTask_task(UpCast(new_task)); 
       } 
    }
 }
 
void Task::Internal::Exit(Task *task)
 {
  Log("exit #;",task->getName());
          
  task->exit();
           
  Object->task_count.dec();
 }
 
 // timer input
 
void Task::Internal::Tick_int()
 {
  TaskEventHost.tick();
  
  TickJob::Internal::RunJobs_int();
  
  bool relax_on=Object->relax.do_tick();
  
  Task *cur=Current;
  
  if( cur->state==Task_Dead ) return; 
  
  TaskBase *task=Object->cycle_tick(cur,relax_on);
  
  SwitchTask_int(UpCast(task));
 }
 
 // Enable/Disable
 
void Task::Internal::Enable()
 {
  Dev::IntLock::Internal::Enable();
  
  Object->enable=true;
  
  ObjectExt->run();
  
  Sys::EnablePacketCon();
 }
   
void Task::Internal::Disable()
 {
  Log("waiting for tasks completion");
  
  Object->task_count.wait();

  Sys::DisablePacketCon();
  
  ObjectExt->stop();

  Object->enable=false;
  
  Dev::IntLock::Internal::Disable();
  
  ObjectExt->complete_task.complete();
 }
  
 // *_task() IntLocked
 
ReleaseCode Task::Internal::BlockTask_task(TaskList &list) 
 {
  Task *cur=Current;
 
  if( cur->state==Task_Dead ) Abort("Fatal error : dead task blocking");
 
  TaskBase *task=Object->running_list.get();

  if( task )
    {
     cur->state=Task_Blocked;
    
     list.put(cur);
     
     SwitchTask_task(UpCast(task));
    }
  else
    {
     Abort("Fatal error : no running tasks");
    }
  
  return cur->release_code;
 }
   
ReleaseCode Task::Internal::BlockTask_task(TaskList &list,MSec timeout)
 {
  if( Current->forced_timeout ) return Release_Timeout;
 
  Current->setTimer(timeout);
  
  return BlockTask_task(list);
 }
  
void Task::Internal::ReleaseTask_task(TaskBase *task_,ReleaseCode code)
 {
  Task *cur=Current;
  Task *task=UpCast(task_);
 
  if( task->state!=Task_Blocked ) Abort("Fatal error : cannot release task (1)");
 
  task->release(code);
    
  if( task->preempt(cur) )
    {   
     if( cur->state!=Task_Dead ) Object->running_list.put(cur);
    
     SwitchTask_task(task);
    }
  else
    {
     Log("task activate #;",task->getName());
     
     Object->running_list.put(task);
    }
 }
  
void Task::Internal::ReleaseTaskList_task(TaskList &list,ReleaseCode code,TextLabel name)
 {
  Task *cur=Current;
  TaskBase *task_top=list.get_preempt(cur);
 
  while( TaskBase *task_=list.get_first() )
    {
     Task *task=UpCast(task_);
     
     if( task->state!=Task_Blocked ) Abort("Fatal error : cannot release task (2)");
 
     task->release(code);
    
     Log("task #; is released by #;",task->getName(),name);
     
     Object->running_list.put(task);
    }
  
  if( task_top )
    {
     Task *task=UpCast(task_top);
    
     if( task->state!=Task_Blocked ) Abort("Fatal error : cannot release task (3)");
 
     task->release(code);
    
     if( cur->state!=Task_Dead ) Object->running_list.put(cur);
    
     Log("task #; is released by #;",task_top->getName(),name);
     
     SwitchTask_task(task);
    }    
 }
 
void Task::Internal::SwitchTask_task(Task *task)
 {
  Task *cur=Current;
 
  if( task==cur ) return;
  
  task->event();
 
  Log("task switch from #; to #;",cur->getName(),task->getName());
  
  TaskMonitor::Internal::Transit(cur,task);
 
  Current=task;
  
  SwitchContext_task(task->context);
 }
 
 // *_int()
   
void Task::Internal::ReleaseTask_int(TaskBase *task_,ReleaseCode code)
 {
  Task *cur=Current;
  Task *task=UpCast(task_);
  
  if( task->state!=Task_Blocked ) Abort("Fatal error : cannot release task (4)");
    
  task->release(code);  
    
  if( task->preempt(cur) && cur->state!=Task_Dead )
    {   
     Object->running_list.put(cur);
    
     SwitchTask_int(task);
    }
  else
    {
     Log("interrupt activate #;",task->getName());
 
     Object->running_list.put(task_);
    }
 }
  
void Task::Internal::ReleaseTaskList_int(TaskList &list,ReleaseCode code,TextLabel name)
 {
  Task *cur=Current;
  TaskBase *task_top=0;
  
  if( cur->state!=Task_Dead ) task_top=list.get_preempt(cur);
 
  while( TaskBase *task_=list.get_first() )
    {
     Task *task=UpCast(task_);
     
     if( task->state!=Task_Blocked ) Abort("Fatal error : cannot release task (5)");
 
     task->release(code);
    
     Log("task #; is released by #;",task->getName(),name);
     
     Object->running_list.put(task_);
    }
  
  if( task_top )
    {
     Task *task=UpCast(task_top);
    
     if( task->state!=Task_Blocked ) Abort("Fatal error : cannot release task (6)");
 
     task->release(code);
    
     Object->running_list.put(cur);
    
     Log("task #; is released by #;",task_top->getName(),name);
     
     SwitchTask_int(task);
    }    
 }
 
void Task::Internal::SwitchTask_int(Task *task)
 {
  Task *cur=Current;
 
  if( task==cur ) return;
  
  task->event();
  
  Log("interrupt switch from #; to #;",cur->getName(),task->getName());
 
  Current=task;
  
  SwitchContext_int(task->context);
 }
 
/* class Task */ 

void Task::Yield()
 {
  Dev::IntLock lock;
  
  Task *cur=GetCurrent();
  
  if( cur->state==Task_Dead ) Abort("Fatal error : dead task yield");
  
  TaskBase *task=Object->cycle(cur);
  
  Internal::SwitchTask_task(Internal::UpCast(task));
 }
   
void Task::Sleep(MSec time)
 {
  TaskList list;
  
  Dev::IntLock lock; 

  Internal::BlockTask_task(list,time);
 }
  
void Task::RelaxPriority(unsigned period_tick,TaskPriority priority)
 {
  Dev::IntLock lock;
  
  Object->relax.set(period_tick,priority);
 }
   
} // namespace CCore
 

