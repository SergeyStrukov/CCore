/* test1027.Time.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: HCore 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Timer.h>

namespace App {

namespace Private_1027 {


} // namespace Private_1027
 
using namespace Private_1027; 
 
/* Testit<1027> */ 

template<>
const char *const Testit<1027>::Name="Test1027 Time";

template<>
bool Testit<1027>::Main() 
 {
  ClockDiffTimer::ValueType buf[20];
  
  ClockDiffTimer timer;
  
  for(auto &t : buf ) t=timer.get();
  
  for(auto t : buf ) Printf(Con,"#;\n",t);
  
  return true;
 }
 
} // namespace App
 
