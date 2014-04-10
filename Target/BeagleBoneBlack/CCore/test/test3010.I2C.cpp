/* test3010.I2C.cpp */ 
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

#include <CCore/inc/dev/DevI2C.h>
#include <CCore/inc/dev/AM3359.CONTROL.h>

namespace App {

namespace Private_3010 {


} // namespace Private_3010
 
using namespace Private_3010; 
 
/* Testit<3010> */ 

template<>
const char *const Testit<3010>::Name="Test3010 I2C";

template<>
bool Testit<3010>::Main() 
 {
  Dev::I2C dev(Dev::I2C_0);
  
  dev.enable();
  
  dev.reset();
  
  {
   using namespace AM3359::CONTROL;
   
   Bar bar;
   
   Printf(Con,"Conf_I2C0_SDA = #;\n\n",bar.get_Conf_I2C0_SDA());
   Printf(Con,"Conf_I2C0_SCL = #;\n\n",bar.get_Conf_I2C0_SCL());
  }
  
  dev.init_fast();
  
  return true;
 }
 
} // namespace App
 
