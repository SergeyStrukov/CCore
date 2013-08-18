/* test3004.IntegerFastAlgo.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testInt.h>
#include <CCore/test/testIntAlgo.h>

#include <CCore/inc/math/IntegerFastAlgo.h>

namespace App {

namespace Private_3004 {

/* types */

typedef Math::IntegerFastAlgo Fast;

typedef Math::IntegerSlowAlgo<Fast::Unit> Slow;

} // namespace Private_3004
 
using namespace Private_3004; 
 
/* Testit<3004> */ 

template<>
const char *const Testit<3004>::Name="Test3004 IntegerFastAlgo";

template<>
bool Testit<3004>::Main() 
 {
  TestIntegerAlgo<Fast>().run(10000);
  
  TestIntegerAlgo2<Fast,Slow>().run(10000);
  
  TestInteger<Fast>().run(10000);
  
  return true;
 }
 
} // namespace App
 
