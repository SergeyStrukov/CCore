/* test2010.TaskMonitor.cpp */ 
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

namespace Private_2010 {

/* class Data */

class Data : public Funchor_nocopy
 {
   static const ulen Num = 10 ;
  
   Atomic run_flag;
   
  private: 
   
   void loop()
    {
     while( run_flag );
    }
   
   void stop()
    {
     run_flag=0;
    }
 
   Function<void (void)> function_loop() { return FunctionOf(this,&Data::loop); }
   
   Function<void (void)> function_stop() { return FunctionOf(this,&Data::stop); }
   
  public: 
  
   Data() { run_flag=1; }
 
   void run()
    {
     RunTasks run(function_stop());
     
     Task::RelaxPriority(3);
     
     run(Num,function_loop(),"Hi",TaskPriority(20000));
    
     run(Num,function_loop(),"Lo",TaskPriority(20001));
     
     Task::Sleep(3_sec);  
    }
 };
 
} // namespace Private_2010
 
using namespace Private_2010; 
 
/* Testit<2010> */ 

template<>
const char *const Testit<2010>::Name="Test2010 TaskMonitor";

template<>
bool Testit<2010>::Main() 
 { 
  Data data;
  
  TaskMonitor_CPU monitor;
  
  TaskMonitor::StartStop start_stop(monitor);
  
  data.run();
  
  start_stop.stop();
  
  Printf(Con,"#;\n",monitor);
 
  return true;
 }
 
} // namespace App
 
