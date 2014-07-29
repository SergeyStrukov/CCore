/* TaskCore.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/task/TaskCore.h>
 
#include <CCore/inc/Abort.h>
#include <CCore/inc/TlsSlot.h>
#include <CCore/inc/PerTask.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

namespace Private_Task {

struct Slot : TlsSlot
 {
  Slot() : TlsSlot("Task") {}
 };
 
Slot Object CCORE_INITPRI_1 ;

} // namespace Private_Task
 
using namespace Private_Task; 
 
PlanInitNode * GetPlanInitNode_Task() { return &Object; }
 
/* class Task */ 

void Task::EntryFunc(Sys::TaskEntry *obj)
 {
  Task *task=static_cast<Task *>(obj);
  
  Object.set(task);
  
  try
    {
     DestroyPerTask dpt;
    
     task->entry();
    }
  catch(...)  
    {
     // normally entry() should catch exceptions itself
    }
     
  task->exit();
 }
  
void Task::entry() {}
   
void Task::exit() {}
  
Task::Task() { init(EntryFunc); }
   
Task::~Task() {}
   
bool Task::run_or_exit()
 {
  if( (run_flag++)!=0 )
    {
     Abort("Fatal error : task rerun");
     
     return false;
    }
 
  if( create() ) 
    {
     exit();
    
     return false;
    }
    
  return true;
 }
 
Task * Task::GetCurrent()
 {
  return static_cast<Task *>(Object.get());
 }
 
} // namespace CCore
 

