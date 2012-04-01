/* test0200.Blank.cpp */ 
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

namespace Private_0200 {


} // namespace Private_0200
 
using namespace Private_0200; 
 
/* Testit<200> */ 

template<>
const char *const Testit<200>::Name="Test200 Blank";

template<>
bool Testit<200>::Main() 
 { 
 
  return true;
 }
 
} // namespace App
 
