/* test3016.Eth.cpp */ 
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

#include <CCore/inc/dev/DevPCIHost.h>

#include <CCore/inc/driver/VIA_Rhine_III.h>

#include <CCore/inc/net/NanoIPDevice.h>

namespace App {

namespace Private_3016 {

/* class Ping */

class Ping : public Funchor_nocopy
 {
   Sem sem;
   
  private: 
 
   void reply(Net::ICMPEchoNumber)
    {
     sem.give();
    }
 
  public:
  
   Ping() {}
   
   ~Ping() {}
   
   Net::ICMPReplyFunction function_reply() { return FunctionOf(this,&Ping::reply); }
   
   bool wait(TimeScope time_scope)
    {
     auto timeout=time_scope.get();
     
     if( !timeout )
       {
        Printf(Exception,"Ping: host is unreachable");
       }
     
     return sem.take(timeout.cap(200_msec));
    }
 };

/* ping() */

void ping(MSec timeout)
 {
  Ping ping;
 
  Net::ICMPEchoEndpoint echo("ip",Net::IPAddress(192,168,1,1),ping.function_reply());
  
  TimeScope time_scope(timeout);

  for(;;)
    {
     echo.send();
  
     if( ping.wait(time_scope) ) 
       {
        Printf(Con,"Ping: host is found\n");
       
        return;
       }
    }
 }
 
} // namespace Private_3016
 
using namespace Private_3016; 
 
/* Testit<3016> */ 

template<>
const char *const Testit<3016>::Name="Test3016 Eth";

template<>
bool Testit<3016>::Main() 
 { 
  for(ulen cnt=2; cnt ;cnt--)
    {
     Dev::PCIBus::HostInitExit pci_host;
     
     const Dev::PCIBus::DeviceInfo *info=pci_host.find(Driver::VIA_Rhine_III::VendorId,Driver::VIA_Rhine_III::DeviceId);
       
     if( !info )
       {
        Printf(Exception,"Cannot find VIA Rhine III");
       }
    
     Driver::VIA_Rhine_III::Device eth(*info,pci_host.getAddressMap());  
    
     ObjMaster eth_master(eth,"eth");
   
     Net::NanoIPDevice ip("eth",Net::IPAddress(192,168,1,10),Net::IPAddress(255,255,255,0));
   
     ObjMaster ip_master(ip,"ip");
   
     Driver::VIA_Rhine_III::Device::StartStop start_stop(eth,TaskPriority(5000));
  
     ping(10_sec);
    }
   
  return true;
 }
 
} // namespace App
 
