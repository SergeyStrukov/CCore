/* FuncTask.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_task_FuncTask_h
#define CCore_inc_task_FuncTask_h

#include <CCore/inc/task/TaskCore.h>

#include <CCore/inc/FunctorType.h>
 
namespace CCore {

/* functions */ 

void GuardRunFuncTaskFailed();

/* classes */ 

template <class FuncInit> class FuncTask;

class TaskExitGuard;

/* class FuncTask<FuncInit> */ 
 
template <class FuncInit> 
class FuncTask : public Task
 {
   FuncInit func_init;
   Function<void (void)> exit_function;
   
  private: 
  
   virtual void entry()
    {
     FunctorTypeOf<FuncInit> func(func_init);
    
     func();
    }
   
   virtual void exit()
    {
     auto func=exit_function;
     
     delete this;
     
     func();
    }
   
  public: 
  
   template <class ... TT>
   explicit FuncTask(const FuncInit &func_init_,TT ... tt)
    : Task(tt...),
      func_init(func_init_) 
    {
    }
   
   template <class ... TT>
   FuncTask(const FuncInit &func_init_,Function<void (void)> exit_function_,TT ... tt) 
    : Task(tt...),
      func_init(func_init_),
      exit_function(exit_function_) 
    {
    }
   
   virtual ~FuncTask() {}
 };
 
/* class TaskExitGuard */

class TaskExitGuard : NoCopy
 {
   Function<void (void)> exit_function;
   bool armed;
   
  public: 
  
   explicit TaskExitGuard(Function<void (void)> exit_function_) : exit_function(exit_function_),armed(true) {}
  
   ~TaskExitGuard() { if( armed ) exit_function(); }
  
   void disarm() { armed=false; }
 };

/* RunFuncTask() */ 

template <class FuncInit,class ... TT> 
void RunFuncTask(const FuncInit &func_init,TT ... tt)
 {
  FuncTask<FuncInit> *task=new FuncTask<FuncInit>(func_init,tt...);
  
  if( !task->run_or_exit() ) GuardRunFuncTaskFailed();
 }
 
template <class FuncInit,class ... TT> 
void RunFuncTask(const FuncInit &func_init,Function<void (void)> exit_function,TT ... tt)
 {
  TaskExitGuard guard(exit_function);
   
  FuncTask<FuncInit> *task=new FuncTask<FuncInit>(func_init,exit_function,tt...);
  
  guard.disarm();
 
  if( !task->run_or_exit() ) GuardRunFuncTaskFailed();
 }
 
} // namespace CCore
 
#endif
 

