/* test2001.Task.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/Task.h>
#include <CCore/inc/sys/SysLog.h>

namespace App {

namespace Private_2001 {

/* class TestTask */

class TestTask : public Task
 {
   ulen index;
   Function<void (void)> exit_function;
 
  private:
  
   void show()
    {
     Printf(Con,"TestTask(#;)\n",index);
    }
  
   virtual void entry()
    {
     Task::Sleep(1_sec);
     
     Task *task_=Task::GetCurrent();
     
     if( TestTask *task=dynamic_cast<TestTask *>(task_) ) task->show();
    }
   
   virtual void exit()
    {
     Function<void (void)> func=exit_function;
     
     delete this;
     
     func();
    }
   
  public:
  
   TestTask(ulen index_,Function<void (void)> exit_function_)
    : index(index_),exit_function(exit_function_) 
    {
     if( index==10 )
       {
        Printf(Exception,"test");
       }
    }
   
   virtual ~TestTask() {}
 };

/* class Run */
 
class Run : NoCopy
 {
   AntiSem asem;
   
  public:
  
   Run() {}
   
   ~Run() { asem.wait(); }
   
   void run(ulen count)
    {
     for(ulen i=1; i<=count ;i++)
       {
        TestTask *task=new TestTask(i,asem.function_dec());
        
        asem.inc();
        
        task->run_or_exit();
       }
    }
 };
 
} // namespace Private_2001
 
using namespace Private_2001; 
 
/* Testit<2001> */ 

template<>
const char *const Testit<2001>::Name="Test2001 Task";

template<>
bool Testit<2001>::Main() 
 { 
  ReportException report;
  
  try
    {
     Run run;
     
     run.run(10);
     
     Putobj(Con,Sys::PrintLog(100));
    }
  catch(CatchType) {}
 
  return true;
 }
 
} // namespace App
 
