/* test3008.PerfCount.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Timer.h>

#include <CCore/inc/dev/DevPerfCount.h>
#include <CCore/inc/dev/AM3359.PRCM.h>

namespace App {

namespace Private_3008 {

void CPUClock()
 {
  using namespace AM3359::PRCM;
  
  BarWKUP bar;
  
  Printf(Con,"idle = #;\n",bar.get_MPUIdleStatus());
  Printf(Con,"clk = #;\n",bar.get_MPUClockSelect());
  Printf(Con,"M2 = #;\n",bar.get_MPUDivM2());
  Printf(Con,"mode = #;\n\n",bar.get_MPUClockMode());
 }

} // namespace Private_3008
 
using namespace Private_3008; 
 
/* Testit<3008> */ 

template<>
const char *const Testit<3008>::Name="Test3008 PerfCount";

template<>
bool Testit<3008>::Main() 
 {
  CPUClock();
  
  Dev::PerfCount pcnt;
  
  Printf(Con,"counters = #;\n\n",pcnt.getNumberOfCounters());
  
  pcnt.prepare(0,Dev::PerfEvent_CmdExec);
  pcnt.prepare(1,Dev::PerfEvent_ExceptionTaken);
  pcnt.prepare(2,Dev::PerfEvent_DataRead);
  pcnt.prepare(3,Dev::PerfEvent_DataWrite);
  
  pcnt.start(true,0,1,2,3);
  
  Task::Sleep(10_sec);
  
  pcnt.stop(true,0,1,2,3);
  
  Printf(Con,"cmds = #;\n",pcnt.get(0));
  Printf(Con,"exceptions = #;\n",pcnt.get(1));
  Printf(Con,"reads = #;\n",pcnt.get(2));
  Printf(Con,"writes = #;\n",pcnt.get(3));
  Printf(Con,"clocks = #;\n",pcnt.get_clock());
  
  return true;
 }
 
} // namespace App
 
