/* test3012.Eth.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/dev/DevEth.h>

namespace App {

namespace Private_3012 {

/* test1() */

void test1()
 {
  Dev::EthControl dev;
  
  
 }

} // namespace Private_3012
 
using namespace Private_3012; 
 
/* Testit<3012> */ 

template<>
const char *const Testit<3012>::Name="Test3012 Eth";

template<>
bool Testit<3012>::Main() 
 {
  test1();
  
  return true;
 }
 
} // namespace App
 
