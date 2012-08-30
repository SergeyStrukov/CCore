/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: IXDP465BootServer 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/dev/DevPCIHost.h>

#include <CCore/inc/driver/VIA_Rhine_III.h>

#include <CCore/inc/net/NanoIPDevice.h>

#include <CCore/inc/net/PTPBoot.h>
#include <CCore/inc/net/PTPServerDevice.h>

#include <CCore/inc/FPGA.h>
#include <CCore/inc/Boot.h>

namespace App {

using namespace CCore;

/* class Eth */ 

class Eth : public Funchor_nocopy
 {
   Driver::VIA_Rhine_III::Device dev;
   
   ObjMaster master;
   
   unsigned tick_count;
   
  private:
  
   void tick()
    {
#if 0
    
     if( ++tick_count<100 ) return;
     
     tick_count=0;
     
     Net::EthStatInfo stat;
     
     dev.getStat(stat);
     
     Printf(Con,"#;\n\n#15;\n\n",Title("Eth"),stat);
     
     Counters<Driver::VIA_Rhine_III::IntEvent,Driver::VIA_Rhine_III::IntEventLim> int_stat;

     dev.getIntCount(int_stat);
     
     Printf(Con,"#;\n\n#15;\n\n",Title("Int"),int_stat);
     
     dev.test();
     
#endif     
    }
   
  public: 
  
   Eth(const Dev::PCIBus::DeviceInfo *info,Dev::PCIBus::AddressMap address_map)
    : dev(*info,address_map),
      master(dev,"eth"),
      tick_count(0)
    {
    }
   
   ~Eth() {}
   
   Net::IPTickFunction function_tick() { return FunctionOf(this,&Eth::tick); }
   
   class StartStop : NoCopy
    {
      Driver::VIA_Rhine_III::Device::StartStop start_stop;
      
     public:
     
      explicit StartStop(Eth &eth) : start_stop(eth.dev,TaskPriority(5000)) {}
      
      ~StartStop() {}
    };
 };
 
/* GetBootInfo() */  

void GetBootInfo(Boot &boot,Net::IPAddress ip_address,Net::IPAddress net_mask)
 {
  Dev::PCIBus::HostInitExit pci_host;
  
  const Dev::PCIBus::DeviceInfo *info=pci_host.find(Driver::VIA_Rhine_III::VendorId,Driver::VIA_Rhine_III::DeviceId);
  
  if( !info )
    {
     Printf(Exception,"Cannot find VIA Rhine III Ethernet device on PCI bus");
    }
    
  Eth eth(info,pci_host.getAddressMap());  
   
  Net::NanoIPDevice ip("eth",ip_address,net_mask);
   
  ObjMaster ip_master(ip,"ip");
   
  Eth::StartStop start_stop(eth);
  
  Net::NanoUDPMultipointDevice udp("ip",Net::PTPServerUDPort,false);
   
  ObjMaster udp_master(udp,"udp");
 
  Net::PTP::ServerDevice ptp("udp");
  
  ObjMaster ptp_master(ptp,"ptp");
  
  Net::IPTickEndpoint tick("ip",eth.function_tick());
  
  boot.get("ptp");
 }
 
/* Main() */ 

int Main()
 {
  bool notus=InitFPGA();
  
  if( notus ) Printf(Con,"Started from RedBoot\n");

  Printf(Con,"#; #;\n",__DATE__,__TIME__);
 
  Boot boot(!notus);
  
  GetBootInfo(boot,Net::IPAddress(192,168,1,10),Net::IPAddress(255,255,255,0));
  
  //boot.show();
  
  boot.boot();
  
  return 0;
 }
 
} // namespace App
 
/* main() */ 

int main()
 {
  using namespace CCore;
  
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
 
