/* test3001.SysError.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/PrintError.h>

namespace App {

namespace Private_3001 {


} // namespace Private_3001
 
using namespace Private_3001; 
 
/* Testit<3001> */ 

template<>
const char *const Testit<3001>::Name="Test3001 SysError";

template<>
bool Testit<3001>::Main() 
 {
  for(int e=1; e<100 ;e++) Printf(Con,"#;\n",PrintError(Sys::ErrorType(e)));
  
  return true;
 }
 
} // namespace App
 
