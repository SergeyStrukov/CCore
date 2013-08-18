/* test3003.Blank.cpp */ 
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

#include <CCore/inc/math/IntegerFastAlgo.h>

namespace App {

namespace Private_3003 {


} // namespace Private_3003
 
using namespace Private_3003; 
 
/* Testit<3003> */ 

template<>
const char *const Testit<3003>::Name="Test3003 Blank";

template<>
bool Testit<3003>::Main() 
 {
  Printf(Con,"#;\n",+Math::IntegerFastAlgo::UnitBits);
  
  return true;
 }
 
} // namespace App
 
