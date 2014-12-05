/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: BeagleBootServer 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/I2CDevice.h>
#include <CCore/inc/video/VideoControl.h>
#include <CCore/inc/sys/SysConHost.h>

#include <CCore/inc/dev/DevEth.h>
#include <CCore/inc/net/NanoIPDevice.h>
#include <CCore/inc/net/PTPServerDevice.h>

#include <CCore/inc/Boot.h>

namespace App {

using namespace CCore;

/* GetBootInfo() */  

void GetBootInfo(Boot &boot,Net::IPAddress ip_address,Net::IPAddress net_mask)
 {
  // Video
  
  I2CDevice i2c(Dev::I2C_0);
  
  ObjMaster i2c_master(i2c,"i2c[0]");

  Video::VideoControl vctrl("i2c[0]");
  
  vctrl.stopOnExit();
  
  ObjMaster vctrl_master(vctrl,"video");
  
  Video::VideoConsole vcon("video");
  
  vcon.waitOpen(1_sec);
  
  SingleMaster<Video::VideoConsole> vcon_master(Sys::GetConHost(),"!VideoConsoleMaster",vcon);
  
  Printf(Con,"*** BeagleBoot #; #; ***\n\n",__DATE__,__TIME__);
  
  // Ethernet

  Dev::EthDevice eth;
  
  ObjMaster eth_master(eth,"eth");
   
  Net::NanoIPDevice ip("eth",ip_address,net_mask);
   
  ObjMaster ip_master(ip,"ip");
   
  Dev::EthDevice::StartStop start_stop(eth,TaskPriority(5000));
  
  Net::NanoUDPMultipointDevice udp("ip",Net::PTPServerUDPort,true);
   
  ObjMaster udp_master(udp,"udp");
 
  Net::PTP::ServerDevice ptp("udp");
  
  ObjMaster ptp_master(ptp,"ptp");
  
  boot.get("ptp",1_msec);
  
  boot.show();
  
  boot.prepareBoot();
 }
 
/* Main() */ 

int Main()
 {
  Boot boot;
 
  GetBootInfo(boot,Net::IPAddress(192,168,99,10),Net::IPAddress(255,255,255,0));
  
  boot.commitBoot();
  
  return 0;
 }
 
} // namespace App
 
/* main() */ 

using namespace App;

int main()
 {
  int ret=0;

  try
    {
     ReportException report;
     
     {
      ret=App::Main();
     }

     report.guard();
    }
  catch(CatchType)
    {
     return 1;
    }

  return ret;
 }
 
/* before_main() */

#include <stdio.h>

void before_main()
 {
  main();
  
  fflush(stdout);
 }

