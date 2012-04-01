/* test1005.Task.cpp */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Task.h>

namespace App {

namespace Private_1005 {

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
     Task *task_=Task::GetCurrent();
     
     if( TestTask *task=dynamic_cast<TestTask *>(task_) ) task->show();
    }
   
   virtual void exit()
    {
     exit_function();
     
     delete this;
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
 
/* class Run2 */
 
class Run2 : NoCopy
 {
   AntiSem asem;
   
  public:
  
   Run2() {}
   
   ~Run2() { asem.wait(); }
   
   void run(ulen count)
    {
     for(ulen i=1; i<=count ;i++)
       {
        asem.inc();

        RunFuncTask( [=] () { Printf(Con,"i = #;\n",i); } ,asem.function_dec());
       }
    }
 };
 
/* class Run3 */
 
class Run3 : NoCopy
 {
   AntiSem asem;
   
  private:
  
   struct Init
    {
     ulen index;
     
     explicit Init(ulen index_) : index(index_) {}
     
     Init(const Init &obj) : index(obj.index) 
      {
       if( index==10 ) Printf(Exception,"test");
      }
     
     struct FunctorType
      {
       ulen index;
       
       explicit FunctorType(const Init &init) : index(init.index) {}
       
       void operator () ()
        {
         Printf(Con,"index = #;\n",index);
        };
      };
    };
 
  public:
  
   Run3() {}
   
   ~Run3() { asem.wait(); }
   
   void run(ulen count)
    {
     for(ulen i=1; i<=count ;i++)
       {
        asem.inc();
        
        Init init(i);

        RunFuncTask(init,asem.function_dec());
       }
    }
 };
 
} // namespace Private_1005
 
using namespace Private_1005; 
 
/* Testit<1005> */ 

template<>
const char *const Testit<1005>::Name="Test1005 Task";

template<>
bool Testit<1005>::Main() 
 { 
  {
   Run run;
  
   run.run(9);
  }
 
  {
   Run2 run2;
  
   run2.run(10);
  }
  
  {
   Run3 run3;
  
   run3.run(9);
  }
  
  return true;
 }
 
} // namespace App
 
