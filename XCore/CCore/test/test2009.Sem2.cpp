/* test2009.Sem2.cpp */ 
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
#include <CCore/test/testRun.h>

#include <CCore/inc/sys/SysLog.h>

namespace App {

namespace Private_2009 {

/* class Test */

class Test : public Funchor_nocopy
 {
   Sem sem;
   
  private:
  
   void give3() 
    { 
     Task::Sleep(3_sec);
     
     sem.give_many(3); 
     
     Printf(Con,"give3()\n");
    }
    
   void take()
    {
     sem.take();
     
     Printf(Con,"take()\n");
    }
   
   Function<void (void)> function_give3() { return FunctionOf(this,&Test::give3); }
   
   Function<void (void)> function_take() { return FunctionOf(this,&Test::take); }
   
  public: 
  
   Test() : sem("TestSem") {}
   
   ~Test() {}
    
   void run()
    {
     RunTasks run;
     
     run(function_give3());
     
     run(ulen(3),function_take());
    }
 };
 
} // namespace Private_2009
 
using namespace Private_2009; 
 
/* Testit<2009> */ 

template<>
const char *const Testit<2009>::Name="Test2009 Sem2";

template<>
bool Testit<2009>::Main() 
 { 
  Test test;
  
  test.run();
  
  Putobj(Con,Sys::PrintLog(200));
  
  return true;
 }
 
} // namespace App
 
