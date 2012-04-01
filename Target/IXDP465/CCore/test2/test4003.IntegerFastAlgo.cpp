/* test4003.IntegerFastAlgo.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testInt.h>
#include <CCore/test/testIntAlgo.h>

#include <CCore/inc/math/IntegerFastAlgo.h>

namespace App {

namespace Private_4003 {

/* types */

typedef Math::IntegerFastAlgo Fast;

typedef Math::IntegerSlowAlgo<Fast::Unit> Slow;

} // namespace Private_4003
 
using namespace Private_4003; 
 
/* Testit<4003> */ 

template<>
const char *const Testit<4003>::Name="Test4003 IntegerFastAlgo";

template<>
bool Testit<4003>::Main() 
 {
  TestIntegerAlgo<Fast>().run(10000);
  
  TestIntegerAlgo2<Fast,Slow>().run(10000);
  
  TestInteger<Fast>().run(10000);
  
  return true;
 }
 
} // namespace App
 
