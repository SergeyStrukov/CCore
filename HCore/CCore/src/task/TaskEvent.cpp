/* TaskEvent.cpp */ 
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
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/task/TaskEvent.h>
 
namespace CCore {

/* global TaskEventHost */

TaskEventHostType TaskEventHost;

/* class TickTask */

void TickTask::task()
 {
  for(;;)
    {
     if( stop.wait(100_msec) )
       {
        return;
       }
     else
       {
        TaskEventHost.tick();
       }
    } 
 }
  
TickTask::TickTask()
 {
  RunFuncTask(function_task(),wait_stop.function_trigger());
 }
   
TickTask::~TickTask()
 {
  stop.trigger();
  
  wait_stop.wait();
 }

} // namespace CCore
 

