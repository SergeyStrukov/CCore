/* test3006.exec.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/FileSystem.h>

namespace App {

namespace Private_3006 {


} // namespace Private_3006
 
using namespace Private_3006; 
 
/* Testit<3006> */ 

template<>
const char *const Testit<3006>::Name="Test3006 exec";

template<>
bool Testit<3006>::Main() 
 {
  FileSystem fs;
  
  fs.exec(".","../../../tools/exectest/exectest.exe","1 2 '3 4 5' \"6 7 8\"");
  
  return true;
 }
 
} // namespace App
 
