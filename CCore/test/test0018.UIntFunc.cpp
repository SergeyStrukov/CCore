/* test0018.UIntFunc.cpp */ 
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

namespace App {

namespace Private_0018 {

/* functions */

template <class UInt>
void show(UInt value)
 {
  typedef UIntFunc<UInt> Func;
  
  Printf(Con,"\nvalue = #.h;\n",value);
  Printf(Con,"Neg(value) = #.h;\n",Func::Neg(value));
  Printf(Con,"IsNegative(value) = #.h;\n",Func::IsNegative(value));
  Printf(Con,"NotNegative(value) = #.h;\n",Func::NotNegative(value));
  Printf(Con,"IsPositive(value) = #.h;\n",Func::IsPositive(value));
  Printf(Con,"NotPositive(value) = #.h;\n",Func::NotPositive(value));
 }
 
template <class UInt>
void test(const char *name)
 {
  typedef UIntFunc<UInt> Func;
  
  Printf(Con,"#;\n\n",Title(name));
 
  Printf(Con,"MSBit = #.h;\n",+Func::MSBit);
  Printf(Con,"MaxPositive = #.h;\n",+Func::MaxPositive);
  Printf(Con,"MinNegative = #.h;\n",+Func::MinNegative);
  
  show<UInt>(Func::MinNegative);
  show<UInt>(Func::MinNegative+Func::MaxPositive/2);
  show<UInt>(0);
  show<UInt>(Func::MaxPositive/2);
  show<UInt>(Func::MaxPositive);
  
  Printf(Con,"\n#;\n\n",TextDivider());
 }
 
} // namespace Private_0018
 
using namespace Private_0018; 
 
/* Testit<18> */ 

template<>
const char *const Testit<18>::Name="Test18 UIntFunc";

template<>
bool Testit<18>::Main() 
 { 
  test<unsigned short>("unsigned short");
  test<unsigned>("unsigned");
  test<unsigned long long>("unsigned long long");
 
  return true;
 }
 
} // namespace App
 
