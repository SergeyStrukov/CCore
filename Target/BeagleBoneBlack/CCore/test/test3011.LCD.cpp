/* test3011.LCD.cpp */ 
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

namespace App {

namespace Private_3011 {


} // namespace Private_3011
 
using namespace Private_3011; 
 
/* Testit<3011> */ 

template<>
const char *const Testit<3011>::Name="Test3011 LCD";

template<>
bool Testit<3011>::Main() 
 {
  for(ulen cnt=100; cnt ;cnt--)
    {
     Printf(Con,"cnt = #;\n",cnt);
     
     Task::Sleep(1_sec);
    }
  
  return true;
 }
 
} // namespace App
 
