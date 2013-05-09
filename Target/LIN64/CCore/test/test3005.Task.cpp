/* test3005.Task.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/inc/Task.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_3005 {


} // namespace Private_3005
 
using namespace Private_3005; 
 
/* Testit<3005> */ 

template<>
const char *const Testit<3005>::Name="Test3005 Task";

template<>
bool Testit<3005>::Main() 
 {
  MSecDiffTimer timer1;
  ClockDiffTimer timer2;
  
  for(ulen cnt=10; cnt ;cnt--)
    {
     Task::Sleep(10_msec);
     
     Printf(Con,"MSec = #; Clock = #;\n",timer1.get(),timer2.get());
    }
  
  for(ulen cnt=10; cnt ;cnt--)
    {
     SlowSem sem;
     
     sem.take(10_msec);
     
     Printf(Con,"MSec = #; Clock = #;\n",timer1.get(),timer2.get());
    }
  
  return true;
 }
 
} // namespace App
 
