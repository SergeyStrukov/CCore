/* test1029.ScanAsyncFile.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: HCore 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Scan.h>

#include <CCore/inc/net/AsyncUDPDevice.h>
#include <CCore/inc/net/PTPClientDevice.h>
#include <CCore/inc/net/HFSClientDevice.h>
#include <CCore/inc/net/HFSFileSystemDevice.h>

namespace App {

namespace Private_1029 {

/* test1() */

void test1()
 {
  ScanAsyncFile scan("host:/NameList.txt");
  PrintAsyncFile out("host:/Scan.txt");
  
  for(; +scan ;++scan)
    Printf(out,"#; #;\n",CharCode(*scan),scan.getTextPos());
 }

} // namespace Private_1029
 
using namespace Private_1029; 
 
/* Testit<1029> */ 

template<>
const char *const Testit<1029>::Name="Test1029 ScanAsyncFile";

template<>
bool Testit<1029>::Main() 
 {
  Net::AsyncUDPEndpointDevice udp(Net::PTPClientUDPort,Net::UDPoint(127,0,0,1,Net::PTPServerUDPort));
  
  ObjMaster udp_master(udp,"udp");
  
  
  Net::PTP::ClientDevice ptp("udp");
  
  ObjMaster ptp_master(ptp,"ptp");
 
  
  Net::HFS::ClientDevice hfs("ptp");
  
  ObjMaster hfs_master(hfs,"hfs");
  
  
  Net::HFS::FileSystemDevice host("hfs");
  
  ObjMaster host_master(host,"host");
  
  
  Net::AsyncUDPEndpointDevice::StartStop start_stop(udp);

  ptp.support_guarded();
  
  
  test1();
  
  return true;
 }
 
} // namespace App
 
