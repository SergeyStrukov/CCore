/* test4004.IntegerSpeed.cpp */ 
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
#include <CCore/test/testIntSpeed.h>

#include <CCore/inc/math/IntegerSlowAlgo.h>
#include <CCore/inc/math/IntegerFastAlgo.h>

namespace App {

namespace Private_4004 {

/* types */

typedef Math::IntegerFastAlgo Fast;

typedef Math::IntegerSlowAlgo<Fast::Unit> Slow;

} // namespace Private_4004
 
using namespace Private_4004; 
 
/* Testit<4004> */ 

template<>
const char *const Testit<4004>::Name="Test4004 Integer speed";

template<>
bool Testit<4004>::Main() 
 {
  PrintFile out("test4004.txt");
  
  TestIntegerSpeed<Fast>::Run(out,"Fast");
  TestIntegerSpeed<Slow>::Run(out,"Slow");
  
  return true;
 }
 
} // namespace App
 
