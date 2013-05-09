/* test3006.Time.cpp */ 
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

#include <CCore/inc/Timer.h>

namespace App {

namespace Private_3006 {


} // namespace Private_3006
 
using namespace Private_3006; 
 
/* Testit<3006> */ 

template<>
const char *const Testit<3006>::Name="Test3006 Time";

template<>
bool Testit<3006>::Main() 
 {
  ClockDiffTimer::ValueType buf[20];
  
  ClockDiffTimer timer;
  
  for(auto &t : buf ) t=timer.get();
  
  for(auto t : buf ) Printf(Con,"#;\n",t);
  
  return true;
 }
 
} // namespace App
 
