/* test2012.TimedTrigger.cpp */ 
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

namespace App {

namespace Private_2012 {

/* class Source */

class Source : public Funchor_nocopy
 {
   TimedTrigger &trigger;
   Atomic run_flag;
   
  public: 
  
   explicit Source(TimedTrigger &trigger_) : trigger(trigger_) { run_flag=1; }
  
   void src()
    {
     while( run_flag )
       {
        trigger.trigger();
        
        Task::Sleep(10_msec);
       }
    }
    
   void stop()
    {
     run_flag=0;
    } 
    
   Function<void (void)> function_src() { return FunctionOf(this,&Source::src); }
 };
 
/* Func() */

void Func()
 {
  SecTimer timer;
  Event event;
  TimedTrigger trigger(event.function_trigger_int(),2_sec);
  
  Event stop_event;
  Source source(trigger);
  
  RunFuncTask(source.function_src(),stop_event.function_trigger());
  
  for(ulen cnt=10; cnt ;cnt--)
    {
     event.wait();
     
     Printf(Con,"timer = #; sec\n",timer.get());
    }
    
  source.stop();  
    
  stop_event.wait();  
 }
 
} // namespace Private_2012
 
using namespace Private_2012; 
 
/* Testit<2012> */ 

template<>
const char *const Testit<2012>::Name="Test2012 TimedTrigger";

template<>
bool Testit<2012>::Main() 
 { 
  Event stop_event;
  
  RunFuncTask(Function<void (void)>(Func),stop_event.function_trigger());
  
  stop_event.wait();
 
  return true;
 }
 
} // namespace App
 
