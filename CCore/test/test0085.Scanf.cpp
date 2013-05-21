/* test0085.Scanf.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Scanf.h>

namespace App {

namespace Private_0085 {

/* test1() */

void test1()
 {
  ScanString scan("line1\rline2\nline3\r\nline4\n\r\n\r");
  
  for(; +scan ;++scan)
    Printf(Con,"#; #;\n",CharCode(*scan),scan.getTextPos());
 }

/* test2() */

void test2()
 {
  ScanString scan("");
  
 }

} // namespace Private_0085
 
using namespace Private_0085; 
 
/* Testit<85> */ 

template<>
const char *const Testit<85>::Name="Test85 Scanf";

template<>
bool Testit<85>::Main() 
 {
  test1();
  test2();
  
  return true;
 }
 
} // namespace App
 
