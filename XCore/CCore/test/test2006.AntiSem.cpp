/* test2006.AntiSem.cpp */ 
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

namespace App {

namespace Private_2006 {

/* class Test */

class Test : public Funchor_nocopy
 {
   AntiSem asem;
   
  private:
  
   void dec()
    { 
     Task::Sleep(3_sec);
     
     asem.dec(); 
     
     Printf(Con,"dec()\n");
    }
    
   void wait()
    {
     asem.wait();
     
     Printf(Con,"wait()\n");
    }
   
  public: 
  
   Test() 
    : asem("testASem")
    {
     asem.inc();
    }
    
   Function<void (void)> function_dec() { return FunctionOf(this,&Test::dec); }
   
   Function<void (void)> function_wait() { return FunctionOf(this,&Test::wait); }
   
   void run()
    {
     RunTasks run;
     
     run(function_dec());
     run(function_wait());
     run(function_wait());
     run(function_wait());
    }
 };
 
} // namespace Private_2006
 
using namespace Private_2006; 
 
/* Testit<2006> */ 

template<>
const char *const Testit<2006>::Name="Test2006 AntiSem";

template<>
bool Testit<2006>::Main() 
 { 
  Test test;
  
  test.run();
  
  return true;
 }
 
} // namespace App
 
