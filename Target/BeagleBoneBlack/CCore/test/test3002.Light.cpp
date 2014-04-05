/* test3002.Light.cpp */
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

#include <CCore/inc/Timer.h>

#include <CCore/inc/dev/DevLight.h>

namespace App {

namespace Private_3002 {

void Delay(unsigned tsec)
 {
  for(SecTimer timer; timer.less(tsec) ;);
 }

} // namespace Private_3002
 
using namespace Private_3002; 
 
/* Testit<3002> */ 

template<>
const char *const Testit<3002>::Name="Test3002 Light";

template<>
bool Testit<3002>::Main() 
 {
  Dev::LightSet(15);
  
  Delay(5);
  
  for(unsigned cnt=10; cnt ;cnt--)
    {
     Printf(Con,"cnt = #;\n",cnt);
    
     Dev::LightOff(5);
    
     Delay(5);
    
     Dev::LightOn(5);
    
     Delay(5);
    }
  
  return true;
 }
 
} // namespace App
 
