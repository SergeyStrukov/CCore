/* test3013.Video.cpp */ 
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

#include <CCore/inc/I2CDevice.h>
#include <CCore/inc/video/VideoControl.h>
#include <CCore/inc/sys/SysConHost.h>

namespace App {

namespace Private_3013 {

/* test() */

void test()
 {
  I2CDevice i2c(Dev::I2C_0);
  
  ObjMaster i2c_master(i2c,"i2c[0]");

  Video::VideoControl vctrl("i2c[0]");
  
  vctrl.stopOnExit();
  
  ObjMaster vctrl_master(vctrl,"video");
  
  Video::VideoConsole vcon("video");
  
  vcon.waitOpen();
  
  SingleMaster<Video::VideoConsole> vcon_master(Sys::GetConHost(),"!VideoConsoleMaster",vcon);
  
  Printf(Con,"test() done\n");
  
  Task::Sleep(10_sec);
 }

} // namespace Private_3013
 
using namespace Private_3013; 
 
/* Testit<3013> */ 

template<>
const char *const Testit<3013>::Name="Test3013 Video";

template<>
bool Testit<3013>::Main() 
 {
  Printf(Con,"before test()\n");
  
  test();
  
  Printf(Con,"middle\n");
  
  test();
  
  Printf(Con,"after test()\n");
  
  return true;
 }
 
} // namespace App
 
