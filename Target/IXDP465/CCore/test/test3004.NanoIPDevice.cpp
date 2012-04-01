/* test3004.NanoIPDevice.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>

#include <CCore/testip/testip.h>

namespace App {

namespace Private_3004 {

/* class TestFunc */

class TestFunc
 {
   StrLen dev_name;
   
  public: 
  
   explicit TestFunc(StrLen dev_name_) : dev_name(dev_name_) {}
  
   void operator () ()
    {
     PacketEchoTest test(dev_name);

     test.run(10,10000);
    }
 };

} // namespace Private_3004
 
using namespace Private_3004; 
 
/* Testit<3004> */ 

template<>
const char *const Testit<3004>::Name="Test3004 NanoIPDevice";

template<>
bool Testit<3004>::Main() 
 { 
  IPEngine ip_engine;
  
  ip_engine.ping(10_sec);
  
  Net::NanoUDPEndpointDevice udp1("IP",55000,false,Net::UDPoint(192,168,1,1,Net::EchoUDPort));
  
  ObjMaster udp_master1(udp1,"udp[1]");
  
  Net::NanoUDPEndpointDevice udp2("IP",55001,false,Net::UDPoint(192,168,1,1,Net::EchoUDPort));
  
  ObjMaster udp_master2(udp2,"udp[2]");
  
  Net::NanoUDPEndpointDevice udp3("IP",55002,false,Net::UDPoint(192,168,1,1,Net::EchoUDPort));
  
  ObjMaster udp_master3(udp3,"udp[3]");
  
  {
   RunTasks run;
   
   run(TestFunc("udp[1]"));
   run(TestFunc("udp[2]"));
   run(TestFunc("udp[3]"));
  }
  
  ip_engine.showStat();
 
  return true;
 }
 
} // namespace App
 
