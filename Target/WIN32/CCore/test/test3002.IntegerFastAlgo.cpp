/* test3002.IntegerFastAlgo.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/WIN32
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

namespace Private_3002 {

/* types */

typedef Math::IntegerFastAlgo Fast;

typedef Math::IntegerSlowAlgo<Fast::Unit> Slow;

} // namespace Private_3002
 
using namespace Private_3002; 
 
/* Testit<3002> */ 

template<>
const char *const Testit<3002>::Name="Test3002 IntegerFastAlgo";

template<>
bool Testit<3002>::Main() 
 {
  TestIntegerAlgo<Fast>().run(100000);
  
  TestIntegerAlgo2<Fast,Slow>().run(100000);
  
  TestInteger<Fast>().run(100000);
  
  return true;
 }
 
} // namespace App
 
