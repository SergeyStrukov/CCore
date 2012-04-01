/* test0023.RandomFill.cpp */ 
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

namespace App {

namespace Private_0023 {

/* class Gen */

class Gen
 {
   unsigned count;
 
  public:
  
   Gen() { count=0; } 
   
   unsigned getCount() const { return count; }
  
   typedef uint8 UnitType;
  
   UnitType next() { count++; return 0xFF; }
 };

/* functions */
 
template <class UInt> 
unsigned Fill(UInt &ret)
 {
  Gen gen;
 
  ret=RandomFill_gen<UInt>::Do(gen);
  
  return gen.getCount();
 }
 
template <class UInt> 
void test()
 {
  UInt a;
  unsigned count=Fill(a);
  
  Printf(Con,"a = #.h; count = #;\n",a,count);
 }
  
} // namespace Private_0023
 
using namespace Private_0023; 
 
/* Testit<23> */ 

template<>
const char *const Testit<23>::Name="Test23 RandomFill";

template<>
bool Testit<23>::Main() 
 { 
  test<uint8>();
  test<uint16>();
  test<uint32>();
  test<uint64>();
 
  return true;
 }
 
} // namespace App
 
