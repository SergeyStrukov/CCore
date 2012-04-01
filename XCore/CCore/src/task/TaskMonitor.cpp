/* TaskMonitor.cpp */ 
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
 
#include <CCore/inc/task/TaskMonitor.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/task/TaskCore.h>

#include <CCore/inc/dev/DevInt.h>

namespace CCore {

/* class TaskMonitor::Link */ 

void TaskMonitor::Link::init()
 {
  record=0;
  monitor=0;
 }
   
auto TaskMonitor::Link::get(TaskMonitor *monitor_) -> Record *
 {
  if( record ) return record;
  
  record=monitor_->alloc(name,priority);
  
  monitor=monitor_;
  
  monitor_->top.ins(this);
  
  return record;
 }
 
TaskMonitor::Link::Link(TextLabel name_,TaskPriority priority_)
 : name(name_),
   priority(priority_)
 {
  init(); 
 }

TaskMonitor::Link::~Link()
 {
  Dev::IntLock lock;
  
  if( monitor ) monitor->top.del(this);
 }
   
/* class TaskMonitor */ 

TaskMonitor * TaskMonitor::Active=0;

void TaskMonitor::start()
 {
  prepare();
  
  bool ok;
  
  {
   Dev::IntLock lock;
  
   if( Active )
     {
      ok=false;
     }
   else
     {
      ok=true;
      
      Active=this;
      
      Record *record=GetCurrent()->get(this);
      
      record->begin();
     } 
  } 
  
  if( !ok ) 
    {
     Printf(Exception,"CCore::TaskMonitor::start() : some TaskMonitor is already active");
    }
 }
   
void TaskMonitor::stop()
 {
  bool ok;
  
  {
   Dev::IntLock lock;
  
   if( Active!=this )
     {
      ok=false;
     }
   else
     {
      ok=true;
      
      Active=0;
      
      Record *record=GetCurrent()->get(this);
      
      record->end();
      
      while( Link *obj=top.del() ) obj->init();
     } 
  } 
  
  if( !ok ) 
    {
     Printf(NoException,"CCore::Sys::TaskMonitor::stop() : is not active");
    }
    
  complete();  
 }
  
auto TaskMonitor::GetCurrent() -> Link *
 {
  return Task::GetCurrent();
 }
 
void TaskMonitor::guardStopped() const
 {
  Dev::IntLock lock;
   
  if( Active==this ) Abort("Fatal error : TaskMonitor is not stopped");
 }
 
TaskMonitor::TaskMonitor()
 {
 }
   
TaskMonitor::~TaskMonitor()
 {
  guardStopped();
 }
 
/* struct TaskMonitor::Internal */

void TaskMonitor::Internal::Transit(Link *from,Link *to)
 {
  if( TaskMonitor *active=Active )
    {
     Record *from_record=from->get(active);
     Record *to_record=to->get(active);

     from_record->transit(from_record,to_record);
    }
 }
 
void TaskMonitor::Internal::BeginInt()
 {
  if( TaskMonitor *active=Active )
    {
     Link *from=GetCurrent();
  
     Record *from_record=from->get(active);
     Record *to_record=active->getInt();

     from_record->transit(from_record,to_record);
    }
 }
   
void TaskMonitor::Internal::EndInt()
 {
  if( TaskMonitor *active=Active )
    {
     Link *to=GetCurrent();
  
     Record *from_record=active->getInt();
     Record *to_record=to->get(active);

     from_record->transit(from_record,to_record);
    }
 }
 
/* class TaskMonitor_CPU::Record_CPU */ 

void TaskMonitor_CPU::Record_CPU::init()
 {
  start_time=0;
  run_time=0;
  percent=0;
 }

void TaskMonitor_CPU::Record_CPU::start(ClockTimer::ValueType t)
 {
  start_time=t;
 }
      
void TaskMonitor_CPU::Record_CPU::stop(ClockTimer::ValueType t)
 {
  run_time+=(t-start_time);
 }
 
void TaskMonitor_CPU::Record_CPU::transit(Record *from_,Record *to_)
 {
  ClockTimer::ValueType t=ClockTimer::Get();
  
  if( from_ )
    {
     Record_CPU *from=static_cast<Record_CPU *>(from_);
     
     from->stop(t);
    }

  if( to_ )  
    {
     Record_CPU *to=static_cast<Record_CPU *>(to_);
 
     to->start(t);
    }
 }
      
TaskMonitor_CPU::Record_CPU::Record_CPU() 
 { 
  priority=IdleTaskPriority;
  
  type=Type_None;
  
  init(); 
 }

void TaskMonitor_CPU::Record_CPU::init(TextLabel name_,TaskPriority priority_) 
 { 
  name=name_;
  priority=priority_;
  
  type=Type_Task;
   
  init(); 
 }

void TaskMonitor_CPU::Record_CPU::init_int()
 {
  name="Int";
  priority=IdleTaskPriority;
  
  type=Type_Int;
  
  init(); 
 }

void TaskMonitor_CPU::Record_CPU::init_other()
 {
  name="Other";
  priority=IdleTaskPriority;
  
  type=Type_Other;
  
  init(); 
 }

/* class TaskMonitor_CPU */

void TaskMonitor_CPU::prepare()
 {
  len=2;
  
  buf[0].init_int();
  buf[1].init_other();
 }
   
void TaskMonitor_CPU::complete()
 {
  uint64 total=0;
  
  for(auto r=getRange(); +r ;++r) total+=r->getRunTime();
  
  if( total )
    {
     for(auto r=getRange(); +r ;++r) r->setPercent(total);
    }
 }
 
auto TaskMonitor_CPU::alloc(TextLabel name,TaskPriority priority) -> Record *
 {
  if( len<buf.getLen() )
    {
     auto ret=buf.getPtr()+(len++);
     
     ret->init(name,priority);
     
     return ret;
    }
    
  return &buf[1];  
 }
   
auto TaskMonitor_CPU::getInt() -> Record *
 {
  return &buf[0];
 }
   
TaskMonitor_CPU::TaskMonitor_CPU(ulen buf_len)
 : buf(Max(DefaultBufLen,buf_len))
 {
  prepare();
 }
   
TaskMonitor_CPU::~TaskMonitor_CPU()
 {
  guardStopped();
 }
 
} // namespace CCore
 

