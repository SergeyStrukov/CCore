/* TaskList.cpp */ 
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
 
#include <CCore/inc/task/TaskList.h>

#include <CCore/inc/task/TaskEvent.h>

#include <CCore/inc/PrintAbort.h>
 
#include <CCore/inc/sys/SysLog.h>

namespace CCore {

/* class TaskBase */ 

template <class ... TT> 
void TaskBase::Log(const char *format,const TT & ... tt)
 {
  Sys::Log(Sys::LogSourceTask|Sys::LogEvent,format,tt...);
 }
 
void TaskBase::changePriority(TaskPriority old_pri,TaskPriority new_pri)
 {
  if( list )
    {
     list->changePriority(this,old_pri,new_pri);
    }
  else
    {
     actual_priority=new_pri;
    }  
 }

TaskBase * TaskBase::burst_step(TaskPriority pri)
 {
  TaskPriority old_pri=actual_priority;
  
  if( Preempt(pri,old_pri) )
    {
     changePriority(old_pri,pri);
     
     Log("burst task #; from #; to #;",getName(),old_pri,pri);
     
     if( list && list->owner && Preempt(pri,list->priority) )
       {
        list->priority=pri;
        
        return list->owner;
       }
    }
    
  return 0;  
 }
   
void TaskBase::burst(TaskPriority pri)
 {
  TaskBase *task=this;
  
  do
    {
     task=task->burst_step(pri);
    }
  while( task );  
 }
 
TaskPriority TaskBase::calcPriority()
 {
  return TaskList::CalcPriority(owned_list,getPriority());
 }
 
TaskBase * TaskBase::relieve_step()
 {
  TaskPriority old_pri=actual_priority;
  
  TaskPriority pri=calcPriority();
 
  if( Preempt(old_pri,pri) )
    {
     changePriority(old_pri,pri);
     
     Log("relieve task #; from #; to #;",getName(),old_pri,pri);

     if( list && list->owner && !Preempt(list->priority,old_pri) )
       {
        if( list->recalcPriority() ) return list->owner;
       }
    }
 
  return 0;
 }
   
void TaskBase::relieve()
 {
  TaskBase *task=this;
  
  do
    {
     task=task->relieve_step();
    }
  while( task );  
 }
 
void TaskBase::delList()
 {
  if( list ) list->do_del(this);
 }
 
void TaskBase::guardList()
 {
  Dev::IntLock lock;
   
  if( list ) Abort("Fatal error : guard task is in list");
     
  if( owned_list ) Abort("Fatal error : guard task owns list");
 }

TaskBase::TaskBase(TextLabel name,TaskPriority priority)
 : TaskMonitor::Link(name,priority),
   actual_priority(priority)
 {
  list=0;
  owned_list=0;
  
  task_number=EventEnumValue<TaskSwitchEvent::TaskNumber>(name);
 }
 
/* struct TaskList::FindResult */

struct TaskList::FindResult
 {
  TaskBase *task;
  TaskPriority priority;
  
  // constructors
 
  FindResult(NothingType) : task(0),priority(IdleTaskPriority) {}
  
  explicit FindResult(TaskPriority priority_) : task(0),priority(priority_) {}
 
  explicit FindResult(TaskBase *task_) : task(task_),priority(task_->actual_priority) {}
  
  // methods
  
  void trySet(TaskBase *task_)
   {
    TaskPriority pri=task_->actual_priority;
    
    if( Preempt(pri,priority) )
      {
       task=task_;
       priority=pri;
      }
   }
 };

/* class TaskList */  

TaskBase * TaskList::getTopOwner()
 {
  TaskBase *ret=owner;
  
  while( ret )
    {
     if( TaskList *list=ret->list )
       {
        if( TaskBase *up=list->owner ) ret=up; else break;
       }
     else
       {
        break;
       }
    }
  
  return ret;
 }

auto TaskList::find() -> FindResult
 {
  auto cur=top.start();
  
  if( !cur ) return Nothing;
  
  FindResult ret(cur.ptr);
  
  for(++cur; +cur ;++cur) ret.trySet(cur.ptr);
    
  return ret; 
 }
  
auto TaskList::find_preempt(TaskPriority priority) -> FindResult
 {
  FindResult ret(priority);
  
  for(auto cur=top.start(); +cur ;++cur) ret.trySet(cur.ptr);
    
  return ret; 
 }

TaskBase * TaskList::find_relaxed(TaskPriority priority)
 {
  for(auto cur=top.start(); +cur ;++cur) if( Preempt(cur->actual_priority,priority) ) return cur.ptr;
 
  return 0;
 }
  
void TaskList::do_del(TaskBase *task)
 {
  if( task->list!=this ) Abort("Fatal error: task is in different list");

  top.del(task);  

  task->list=0;
  
  if( owner )
    {
     TaskPriority pri=task->actual_priority;

     if( !Preempt(priority,pri) )
       {
        if( recalcPriority() ) owner->relieve();
       }
    }
 }
 
TaskBase * TaskList::del(TaskBase *task)
 {
  if( task ) do_del(task);
  
  return task;
 }
 
void TaskList::changePriority(TaskBase *task,TaskPriority,TaskPriority new_priority)
 {
  task->actual_priority=new_priority;
 }
  
TaskPriority TaskList::calcPriority()
 {
  return priority=find().priority;
 }
  
bool TaskList::recalcPriority()
 {
  TaskPriority pri=find().priority;
  
  if( pri!=priority )
    {
     priority=pri;
     
     return true;
    }
   
  return false; 
 }

TaskPriority TaskList::CalcPriority(TaskList *list,TaskPriority priority)
 {
  for(Algo::Cur cur(list); +cur ;++cur)
    {
     TaskPriority pri=cur->priority;
     
     if( Preempt(pri,priority) ) priority=pri;
    }
    
  return priority;  
 }
 
TaskList::TaskList()
 {
  owner=0;
 }
   
TaskList::~TaskList()
 {
  Dev::IntLock lock;
  
  if( +top ) Abort("Fatal error : task list is not empty on exit");
    
  if( owner ) Abort("Fatal error : task list is owned on exit");
 }
  
TaskList::TaskList(TaskList &list,ulen &count_)
 {
  owner=0;
  
  ulen count=count_;
 
  for(TaskBase *task; count && (task=list.get()) ;count--) put(task);
  
  count_=count;
 }
 
void TaskList::setOwner(TaskBase *task)
 {
  if( owner ) Abort("Fatal error: task list is owned");
 
  owner=task; 
  
  task->owned_list=Algo::InsTopFirst(task->owned_list,this);
  
  task->burst(calcPriority());
 }
  
void TaskList::clearOwner(TaskBase *task)
 {
  if( task!=owner ) Abort("Fatal error: task list has another owner");
 
  owner=0; 
  
  task->owned_list=Algo::DelTop(task->owned_list,this);
  
  task->relieve();
 }
  
void TaskList::put(TaskBase *task)
 {
  if( task->list ) Abort("Fatal error : task is in another list");
  
  if( task==getTopOwner() )
    {
     PrintAbort("Fatal error : deadlock, task = #.q;",task->getName());
    }
   
  task->list=this;
  
  top.ins_last(task);
  
  if( owner )
    {
     TaskPriority pri=task->actual_priority;
     
     if( Preempt(pri,priority) )
       {
        priority=pri;
        
        owner->burst(pri);
       }
    }
 }
  
TaskBase * TaskList::get()
 {
  return del(find().task);
 }
  
TaskBase * TaskList::get_relaxed(TaskPriority priority)
 {
  return del(find_relaxed(priority));
 }
  
TaskBase * TaskList::get_first()
 {
  return del(top.top);
 }
  
TaskBase * TaskList::get_preempt(TaskPriority priority)
 {
  return del(find_preempt(priority).task);
 }
 
} // namespace CCore
 

