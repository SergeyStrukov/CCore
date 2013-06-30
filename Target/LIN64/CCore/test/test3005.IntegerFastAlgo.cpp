/* test3002.IntegerFastAlgo.cpp */ 
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
#include <CCore/test/testInt.h>
#include <CCore/test/testIntAlgo.h>

#include <CCore/inc/math/IntegerFastAlgo.h>

namespace App {

namespace Private_3005 {

/* types */

typedef Math::IntegerFastAlgo Fast;

typedef Math::IntegerSlowAlgo<Fast::Unit> Slow;

} // namespace Private_3005
 
using namespace Private_3005; 
 
/* Testit<3005> */ 

template<>
const char *const Testit<3005>::Name="Test3005 IntegerFastAlgo";

template<>
bool Testit<3005>::Main() 
 {
  TestIntegerAlgo<Fast>().run(100);
  
  TestIntegerAlgo2<Fast,Slow>().run(100);
  
  TestInteger<Fast>().run(100);
  
  return true;
 }
 
} // namespace App
 
