/* test0056.IntegerSlowAlgo.cpp */ 
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testIntAlgo.h>

namespace App {

namespace Private_0056 {

/* types */

typedef Math::IntegerSlowAlgo<uint8> Algo8;

typedef Math::IntegerSlowAlgo<unsigned> Algou;

} // namespace Private_0056
 
using namespace Private_0056; 
 
/* Testit<56> */ 

template<>
const char *const Testit<56>::Name="Test56 IntegerSlowAlgo";

template<>
bool Testit<56>::Main() 
 {
  TestIntegerAlgo<Algo8>().run(100000);
  TestIntegerAlgo<Algou>().run(100000);
  
  TestIntegerAlgo2<Algo8,Algo8>().run(10000);
  
  return true;
 }
 
} // namespace App
 
