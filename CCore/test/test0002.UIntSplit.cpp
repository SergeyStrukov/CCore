/* test0002.UIntSplit.cpp */ 
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

#include <CCore/inc/UIntSplit.h>

namespace App {

namespace Private_0002 {

/* functions */

void test1(uint32 value) CCORE_NOINLINE;

void test2(uint64 value) CCORE_NOINLINE;

/* test1() */

void test1(uint32 value)
 {
  Printf(Con,"#.16;\n",value);
 
  UIntSplit<uint32,uint8> split;
  
  split.set(value);
   
  Printf(Con,"#.16; #.16; #.16; #.16;\n",split[0],split[1],split[2],split[3]);
   
  Printf(Con,"#.16;\n",split.get());
 }
 
/* test2() */

void test2(uint64 value)
 {
  Printf(Con,"#.16;\n",value);
 
  UIntSplit<uint64,uint32> split;
  
  split.set(value);
   
  Printf(Con,"#.16; #.16;\n",split[0],split[1]);
   
  Printf(Con,"#.16;\n",split.get());
 }
 
} // namespace Private_0002
 
using namespace Private_0002; 
 
/* Testit<2> */ 

template<>
const char *const Testit<2>::Name="Test2 UIntSplit";

template<>
bool Testit<2>::Main() 
 { 
  test1(0x91827364);
  test2(0x8765432123456789);
 
  return true;
 }
 
} // namespace App
 
