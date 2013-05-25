/* test1028.ScanFile.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: HCore 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Scan.h>

namespace App {

namespace Private_1028 {


} // namespace Private_1028
 
using namespace Private_1028; 
 
/* Testit<1028> */ 

template<>
const char *const Testit<1028>::Name="Test1028 ScanFile";

template<>
bool Testit<1028>::Main() 
 {
  ScanFile scan("Makefile");
  PrintFile out("test1028.txt");
  
  for(; +scan ;++scan)
    Printf(out,"#; #;\n",CharCode(*scan),scan.getTextPos());
  
  scan.close();
  
  scan.open("Makefile",true);
  
  for(; +scan ;++scan)
    Printf(out,"#; #;\n",CharCode(*scan),scan.getTextPos());
  
  return true;
 }
 
} // namespace App
 
