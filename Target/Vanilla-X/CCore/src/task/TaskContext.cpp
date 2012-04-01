/* TaskContext.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/task/TaskCore.h>

#include <__std_init.h>
 
namespace CCore {

/* class Task::Internal */ 

extern "C" {

static void __std_Entry(void *task)
 {
  Task::Internal::EntryTask(task);
 }
 
}
  
void Task::Internal::ContextInit(void *context,void *stack,ulen stack_len,void *task)
 {
  __std_context_init(context,stack,stack_len,__std_Entry,task);
 }
 
void * Task::Internal::GetContext()
 {
  return __std_context;
 }
  
ulen Task::Internal::GetContextLen()
 {
  return __std_context_len();
 }
  
void Task::Internal::SwitchContext_int(void *context)
 {
  __std_context=context;
 }
  
void Task::Internal::SwitchContext_task(void *context)
 {
  __std_switch(context);
 }
 
} // namespace CCore
 

