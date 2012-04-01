/* test3003.IntegerSpeed.cpp */ 
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
#include <CCore/test/testIntSpeed.h>

#include <CCore/inc/math/IntegerSlowAlgo.h>
#include <CCore/inc/math/IntegerFastAlgo.h>

namespace App {

namespace Private_3003 {

/* types */

typedef Math::IntegerFastAlgo Fast;

typedef Math::IntegerSlowAlgo<Fast::Unit> Slow;

} // namespace Private_3003
 
using namespace Private_3003; 
 
/* Testit<3003> */ 

template<>
const char *const Testit<3003>::Name="Test3003 Integer speed";

template<>
bool Testit<3003>::Main() 
 {
  PrintFile out("test3003.txt");
  
  TestIntegerSpeed<Fast>::Run(out,"Fast");
  TestIntegerSpeed<Slow>::Run(out,"Slow");
  
  return true;
 }
 
} // namespace App
 
