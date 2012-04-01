/* test1022.PTPServer.cpp */ 
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
#include <CCore/test/testNet.h>

#include <CCore/inc/net/UDPDevice.h>
#include <CCore/inc/net/AsyncUDPDevice.h>

namespace App {

namespace Private_1022 {

//typedef Net::UDPEndpointDevice Device;
typedef Net::AsyncUDPEndpointDevice Device;

} // namespace Private_1022
 
using namespace Private_1022; 
 
/* Testit<1022> */ 

template<>
const char *const Testit<1022>::Name="Test1022 PTPServer";

template<>
bool Testit<1022>::Main() 
 {
  Device udp(Net::PTPClientUDPort,Net::UDPoint(127,0,0,1,Net::PTPServerUDPort));
  
  ObjMaster udp_master(udp,"udp");
  
  Net::PTP::ClientDevice ptp("udp");
  
  ObjMaster ptp_master(ptp,"ptp");
  
  Device::StartStop start_stop(udp);
  
  ptp.support_guarded();
  
  // engine
  
  PTPServerTest engine;
  
  engine.run();
  
  ShowStat(ptp,"PTPClient");
  
  ShowStat(udp,"UDP");
  
  return true;
 }
 
} // namespace App
 
