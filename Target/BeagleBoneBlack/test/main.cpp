/* main.cpp */ 
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

#include <CCore/inc/MemBase.h>
#include <CCore/inc/PacketPool.h>

namespace App {

/* Testit<0> */ 

template<>
const char *const Testit<0>::Name="Test0 empty";
   
template<>
bool Testit<0>::Main() { return false; }
 
} // namespace App
 
/* main() */ 

using namespace App;

int main(int argc,const char *argv[])
 {
  Used(argc);
  Used(argv);
  
  //Testit<0>().run();
  //Testit<1>().run();
  //Testit<2>().run();
  //Testit<3>().run();
  //Testit<4>().run();
  //Testit<5>().run();
  //Testit<6>().run();
  //Testit<7>().run();
  //Testit<8>().run();
  //Testit<9>().run();
  //Testit<10>().run();
  //Testit<11>().run();
  //Testit<12>().run();
  //Testit<13>().run();
  //Testit<14>().run();
  //Testit<15>().run();
  //Testit<16>().run();
  //Testit<17>().run();
  //Testit<18>().run();
  //Testit<19>().run();
  //Testit<20>().run();
  //Testit<21>().run();
  //Testit<22>().run();
  //Testit<23>().run();
  //Testit<24>().run();
  //Testit<25>().run();
  //Testit<26>().run();
  //Testit<27>().run();
  //Testit<28>().run();
  //Testit<29>().run();
  //Testit<30>().run();
  //Testit<31>().run();
  //Testit<32>().run();
  //Testit<33>().run();
  //Testit<34>().run();
  //Testit<35>().run();
  //Testit<36>().run();
  //Testit<37>().run();
  //Testit<38>().run();
  //Testit<39>().run();
  //Testit<40>().run();
  //Testit<41>().run();
  //Testit<42>().run();
  //Testit<43>().run();
  //Testit<44>().run();
  //Testit<45>().run();
  //Testit<46>().run();
  //Testit<47>().run();
  //Testit<48>().run();
  //Testit<49>().run();
  //Testit<50>().run();
  //Testit<51>().run();
  //Testit<52>().run();
  //Testit<53>().run();
  //Testit<54>().run();
  //Testit<55>().run();
  //Testit<56>().run();
  //Testit<57>().run();
  //Testit<58>().run();
  //Testit<59>().run();
  //Testit<60>().run();
  //Testit<61>().run();
  //Testit<62>().run();
  //Testit<63>().run();
  //Testit<64>().run();
  //Testit<65>().run();
  //Testit<66>().run();
  //Testit<67>().run();
  //Testit<68>().run();
  //Testit<69>().run();
  //Testit<70>().run();
  //Testit<71>().run();
  //Testit<72>().run();
  //Testit<73>().run();
  //Testit<74>().run();
  //Testit<75>().run();
  //Testit<76>().run();
  //Testit<77>().run();
  //Testit<78>().run();
  //Testit<79>().run();
  //Testit<80>().run();
  //Testit<81>().run();
  //Testit<82>().run();
  //Testit<83>().run();
  //Testit<84>().run();
  //Testit<85>().run();
  //Testit<86>().run();
  //Testit<87>().run();
  //Testit<88>().run();
  //Testit<89>().run();
  //Testit<90>().run();
  //Testit<91>().run();
  //Testit<92>().run();
  //Testit<93>().run();
  //Testit<94>().run();
  //Testit<95>().run();
  //Testit<96>().run();
  //Testit<97>().run();
  //Testit<98>().run();
  
  //Testit<100>().run();
  //Testit<101>().run();
  //Testit<102>().run();
  //Testit<103>().run();
  //Testit<104>().run();
  //Testit<105>().run();
  //Testit<106>().run();
  //Testit<107>().run();
  //Testit<108>().run();
  
  //Testit<200>().run();
  
  //Testit<300>().run();
  
  //Testit<2001>().run();
  //Testit<2002>().run();
  //Testit<2003>().run();
  //Testit<2004>().run();
  //Testit<2005>().run();
  //Testit<2006>().run();
  //Testit<2007>().run();
  //Testit<2008>().run();
  //Testit<2009>().run();
  //Testit<2010>().run();
  //Testit<2011>().run();
  //Testit<2012>().run();
  //Testit<2013>().run();
  //Testit<2014>().run();
  //Testit<2015>().run();
  //Testit<2016>().run();
  
  //Testit<3001>().run();
  //Testit<3002>().run();
  //Testit<3003>().run();
  //Testit<3004>().run();
  //Testit<3005>().run();
  //Testit<3006>().run();
  //Testit<3007>().run();
  //Testit<3008>().run();
  //Testit<3009>().run();
  //Testit<3010>().run();
  //Testit<3011>().run();
  //Testit<3012>().run();
  //Testit<3013>().run();
  
  Printf(Con,"\nPeak memory usage #;\n\n",MemPeak());  
    
  return 0;
 }

/* before_main() */

#include <CCore/inc/I2CDevice.h>
#include <CCore/inc/video/VideoControl.h>
#include <CCore/inc/sys/SysConHost.h>

#include <CCore/inc/dev/DevEth.h>
#include <CCore/inc/net/NanoIPDevice.h>
#include <CCore/inc/net/PTPClientDevice.h>
#include <CCore/inc/net/HFSClientDevice.h>
#include <CCore/inc/net/HFSFileSystemDevice.h>
#include <CCore/inc/net/PTPConDevice.h>
#include <CCore/inc/RedirectPTPCon.h>

#include <stdio.h>

void before_main()
 {
  using namespace CCore;
  
  MemScope mem_scope;
  
#if 1
   
  I2CDevice i2c(Dev::I2C_0);
  
  ObjMaster i2c_master(i2c,"i2c[0]");

  Video::VideoControl vctrl("i2c[0]");
  
  ObjMaster vctrl_master(vctrl,"video");
  
#endif
  
#if 1  
  
  Video::VideoConsole vcon("video");
  
  vcon.waitOpen();
  
  SingleMaster<Video::VideoConsole> vcon_master(Sys::GetConHost(),"!VideoConsoleMaster",vcon);
  
#endif  

#if 1
  
  Dev::EthDevice eth;
  
  ObjMaster eth_master(eth,"eth");
  
  Net::NanoIPDevice ip("eth",Net::IPAddress(192,168,99,10),Net::IPAddress(255,255,255,0));
  
  Dev::EthDevice::StartStop start_stop(eth,TaskPriority(5000));
  
  ObjMaster ip_master(ip,"ip");
  
  Net::NanoUDPEndpointDevice udp_ptp("ip",Net::PTPClientUDPort,true,Net::UDPoint(192,168,99,1,Net::PTPServerUDPort));
  
  ObjMaster udp_ptp_master(udp_ptp,"udp_ptp");
  
  Net::PTP::ClientDevice ptp("udp_ptp");

  ptp.support_guarded(10_sec);
  
  ObjMaster ptp_master(ptp,"ptp");
  
  Net::HFS::ClientDevice hfs("ptp");
  
  ObjMaster hfs_master(hfs,"hfs");
  
  Net::HFS::FileSystemDevice host("hfs");
  
  ObjMaster host_master(host,"host");
  
  Net::PTPCon::ClientDevice ptpcon("ptp");
  
  ObjMaster ptpcon_master(ptpcon,"ptpcon");
  
  Net::PTPCon::Cfg cfg(Net::PTPCon::TriggerAll);
  
  RedirectPTPCon redirect("ptpcon","Beagle",cfg);
  
#endif  
  
  const char *argv[]={"main",0};
 
  int ret=main(1,argv);
  
  fflush(stdout);
  
  Printf(Con,"main() return #;\n",ret);
  
  DetachPacketBufs();
 }


 


