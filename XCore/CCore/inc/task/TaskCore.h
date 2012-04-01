/* TaskCore.h */ 
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

#ifndef CCore_inc_task_TaskCore_h
#define CCore_inc_task_TaskCore_h

#include <CCore/inc/PlanInit.h>
#include <CCore/inc/MemBase.h>

#include <CCore/inc/task/TaskList.h>
#include <CCore/inc/task/TlsBuf.h>
#include <CCore/inc/task/Tick.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_TaskCore();

PlanInitNode * GetPlanInitNode_TaskCoreExt();

/* words */

enum CurTaskContextType { CurTaskContext };

enum InterruptContextType { InterruptContext };

/* classes */ 

//enum TaskState;

//enum ReleaseCode;

class Task;

class ForcedTimeout;

/* enum TaskState */ 
 
enum TaskState
 {
  Task_Dead = 0,
  
  Task_NotReady,
  Task_Ready,
  
  Task_Running,
  Task_Blocked
 };
 
/* enum ReleaseCode */ 
 
enum ReleaseCode : ulen
 {
  Release_Timeout = 0,
  Release_Ok,
  
  Release_Custom
 };
 
inline ReleaseCode operator + (ReleaseCode base,ulen off) { return ReleaseCode(ulen(base)+off); }
 
/* class Task */ 

class Task : public TaskBase , public MemBase_nocopy , public Funchor
 {
   void *stack;   // == 0 for main task
   void *context; // != 0 for good task
  
   TaskState state;
   ReleaseCode release_code;
  
   TickCount ticks;
   bool forced_timeout;
   
   TickJob job;
   
  private: 
  
   static AutoTextNameType ObjName;
   
   static Task * Current;
  
  private: 
   
   virtual void entry();
   
   virtual void exit();
   
   void tick();
   
   Function<void (void)> function_tick() { return FunctionOf(this,&Task::tick); }
   
  private:
  
   // IntLocked
   
   void setTimer(MSec timeout); 
   
   void stopTimer();
   
   void release(ReleaseCode code); 
   
   void setForcedTimeout_task();
   
   void setForcedTimeout_int();
   
   bool clearForcedTimeout();
   
   void setDead()
    {
     state=Task_Dead;
     
     setIdlePriority();
    }
    
  private:
  
   friend class ForcedTimeout; 
   
   void abort_wait(); 
    
   void abort_wait_int(); 
   
   void abort_wait_any(); 
   
  private: 
   
   enum MainTaskCtorType { MainTaskCtor };
   
   Task(MainTaskCtorType unused);
   
   void init(ulen stack_len);
   
   bool run();
   
   void guardStopped();
   
   static void Entry(Task *task);
   
  public:
  
   TlsBuf tls;
   
   explicit Task(TaskPriority priority=DefaultTaskPriority,
                 ulen stack_len=DefaultStackLen);
   
   explicit Task(TextLabel name,
                 TaskPriority priority=DefaultTaskPriority,
                 ulen stack_len=DefaultStackLen);
    
   virtual ~Task();
   
   bool run_or_exit();
   
   // task control
   
   static void Yield();
   
   static void Sleep(MSec time);
  
   static void RelaxPriority(unsigned period_tick,TaskPriority priority=IdleTaskPriority);
  
   static Task * GetCurrent() { return Current; }
   
   class Internal;
 };
 
/* functions */

inline TextLabel GetTaskName(CurTaskContextType) { return Task::GetCurrent()->getName(); }

inline const char * GetTaskName(InterruptContextType) { return "interrupt"; }

/* class Task::Internal */ 

class Task::Internal
 {
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
  
   // context -- implemented in platform
  
   static void ContextInit(void *context,void *stack,ulen stack_len,void *task);
  
   static void * GetContext();
  
   static ulen GetContextLen();
  
   static void SwitchContext_int(void *context);
  
   static void SwitchContext_task(void *context);
   
   // start/stop
   
   static void GuardRun();
  
   static void Stop(Task *task);
  
   static void Exit(Task *task);
   
   friend class Task;
  
  public:
  
   static void EntryTask(void *task);
  
   static Task * UpCast(TaskBase *task) { return static_cast<Task *>(task); }
 
   // task classes
   
   class MainTask;
   class ExitTask;
   class IdleTask;
   class CompleteTask;
  
   // timer input
  
   static void Tick_int();
  
   // Enable/Disable
 
   static void Enable();
   
   static void Disable();
  
   // *_task() IntLocked
  
   static ReleaseCode BlockTask_task(TaskList &list);
   
   static ReleaseCode BlockTask_task(TaskList &list,MSec timeout_msec);
  
   static void ReleaseTask_task(TaskBase *task,ReleaseCode code);
  
   static void ReleaseTaskList_task(TaskList &list,ReleaseCode code,TextLabel name);
  
   static void SwitchTask_task(Task *task);
  
   // *_int()
   
   static void ReleaseTask_int(TaskBase *task,ReleaseCode code);
  
   static void ReleaseTaskList_int(TaskList &list,ReleaseCode code,TextLabel name);
  
   static void SwitchTask_int(Task *task);
 };
 
/* class ForcedTimeout */  

class ForcedTimeout : NoCopy
 {
   Task *task;
   
  public:
  
   ForcedTimeout() { task=Task::GetCurrent(); }
   
   ~ForcedTimeout() { clear(); }
   
   bool clear();
   
   // functions
   
   Function<void (void)> function_abort() { return Funchor::FunctionOf(task,&Task::abort_wait); }
   
   Function<void (void)> function_abort_int() { return Funchor::FunctionOf(task,&Task::abort_wait_int); }
   
   Function<void (void)> function_abort_any() { return Funchor::FunctionOf(task,&Task::abort_wait_any); }
 };
 
} // namespace CCore
 
#endif
 

