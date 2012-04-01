/* testip.h */ 
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

#ifndef CCore_test_testip_h
#define CCore_test_testip_h

#include <CCore/test/testNet.h>

#include <CCore/inc/dev/DevPCIHost.h>

#include <CCore/inc/driver/VIA_Rhine_III.h>

#include <CCore/inc/net/NanoIPDevice.h>

#include <CCore/inc/net/PTPClientDevice.h>

#include <CCore/inc/net/HFSClientDevice.h>

#include <CCore/inc/net/HFSFileSystemDevice.h>

namespace App {

/* classes */ 

class IPEngine;

class HostEngine;

/* class IPEngine */ 

class IPEngine : NoCopy
 {
   Dev::PCIBus::HostInitExit pci_host;
   
   struct FindInfo
    {
     const Dev::PCIBus::DeviceInfo *info;
     
     explicit FindInfo(Dev::PCIBus::HostInitExit &pci_host);
      
     operator const Dev::PCIBus::DeviceInfo & () const { return *info; }
     
    } info;
   
   Driver::VIA_Rhine_III::Device eth_device;
   
   ObjMaster eth_master;
   
   Net::NanoIPDevice ip_device;
   
   ObjMaster ip_master;
   
   Driver::VIA_Rhine_III::Device::StartStop start_stop;
   
   class Ping;
   
  public:
  
   IPEngine();
   
   ~IPEngine();
   
   void ping(MSec timeout);
   
   void showStat();
 };
 
/* class HostEngine */ 

class HostEngine : NoCopy
 {
   Net::NanoUDPEndpointDevice udp;
   
   ObjMaster udp_master;
 
   Net::PTP::ClientDevice ptp;
   
   struct Support
    {
     explicit Support(Net::PTP::ClientDevice &ptp)
      {
       ptp.support_guarded(10_sec);
      }
      
    } support;
   
   ObjMaster ptp_master;
   
   Net::HFS::ClientDevice hfs;
   
   ObjMaster hfs_master;
   
   Net::HFS::FileSystemDevice fs;
   
   ObjMaster fs_master;
   
  public:
  
   explicit HostEngine(Net::UDPoint dst);
   
   ~HostEngine();
 };
 
} // namespace App
 
#endif
 

