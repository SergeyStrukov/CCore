/* test3002.SysError.cpp */ 
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

#include <CCore/inc/PrintError.h>

namespace App {

namespace Private_3002 {


} // namespace Private_3002
 
using namespace Private_3002; 
 
/* Testit<3002> */ 

template<>
const char *const Testit<3002>::Name="Test3002 SysError";

template<>
bool Testit<3002>::Main() 
 {
  for(int e=1; e<100 ;e++) Printf(Con,"#;\n",PrintError(Sys::ErrorType(e)));
  
  return true;
 }
 
} // namespace App
 
