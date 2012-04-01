/* SysTask.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vasnilla-H
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysTask.h>
 
namespace CCore {
namespace Sys {

/* functions */ 

void YieldTask() noexcept 
 { 
  // TODO
 }
 
void SleepTask(MSec /*time*/) noexcept 
 { 
  // TODO
 }
 
TaskIdType GetTaskId() noexcept 
 { 
  // TODO

  return 0;
 }
 
/* struct TaskEntry */

void TaskEntry::init(TaskEntryFunc /*entry*/) noexcept
 {
  // TODO
 }

ErrorType TaskEntry::create() noexcept
 {
  // TODO
  
  return NoError;
 }
  
} // namespace Sys
} // namespace CCore
 

