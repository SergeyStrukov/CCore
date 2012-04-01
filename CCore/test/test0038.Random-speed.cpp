/* test0038.Random-speed.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Random.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_0038 {


} // namespace Private_0038
 
using namespace Private_0038; 
 
/* Testit<38> */ 

template<>
const char *const Testit<38>::Name="Test38 Random speed";

template<>
bool Testit<38>::Main() 
 { 
  Random random;
  uint8 sum=0;
  
  SecTimer timer;
  
  for(ulen cnt=1000; cnt ;cnt--) 
    for(ulen cnt=1000000; cnt ;cnt--)
      sum+=random.next8();
  
  auto time=timer.get();
  
  Printf(Con,"time = #; sec\n",time,sum);
 
  return true;
 }
 
} // namespace App
 
