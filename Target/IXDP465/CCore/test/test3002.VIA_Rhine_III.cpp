/* test3002.VIA_Rhine_III.cpp */ 
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

namespace App {

namespace Private_3002 {

/* class Engine */ 

class Engine : public Driver::VIA_Rhine_III::DeviceEngine
 {
   ulen outbound_enable;
   ulen outbound_count;
   ulen inbound_count;
   
  private: 
  
   virtual void inbound_packet(uint8 *,InboundStatus)
    {
     inbound_count++;
    }
 
   virtual ulen get_outbound_packet(uint8 *buf,ulen)
    {
     if( !outbound_enable ) return 0;
     
     outbound_enable--;
    
     static const uint8 packet[]=
      {
       0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
       0x00, 0x21, 0x91, 0x52, 0x43, 0x0B,
       0x08, 0x06,
       
       0x00, 0x01,
       0x08, 0x00,
       0x06, 0x04,
       0x00, 0x01,
       
       0x00, 0x21, 0x91, 0x52, 0x43, 0x0B,
       0xC0, 0xA8, 0x01, 0x0A,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0xC0, 0xA8, 0x01, 0x01
      };
      
     Range(buf,DimOf(packet)).copy(packet); 
     
     return DimOf(packet);
    }
   
   virtual void outbound_done(OutboundStatus,ulen)
    {
     outbound_count++;
    }
   
   virtual void linkUp()
    {
     Printf(Con,"link up\n");
    }
   
   virtual void linkDown()
    {
     Printf(Con,"link down\n");
    }
   
   virtual void tick() 
    {
     outbound_enable++;
     
     signalOutbound(); 
    }
   
   virtual void start()
    {
     Printf(Con,"start\n");
     
     outbound_enable=0;
     outbound_count=0;
     inbound_count=0;
    }
   
   virtual void stop()
    {
     Printf(Con,"stop\n");
     
     Printf(Con,"outbound_count = #;\n",outbound_count);
     Printf(Con,"inbound_count = #;\n",inbound_count);
    }
   
  public:
  
   Engine(const Dev::PCIBus::DeviceInfo &info,Dev::PCIBus::AddressMap address_map) 
    : Driver::VIA_Rhine_III::DeviceEngine(info,address_map) 
    {
    }
   
   ~Engine() {}
 };
 
} // namespace Private_3002
 
using namespace Private_3002; 
 
/* Testit<3002> */ 

template<>
const char *const Testit<3002>::Name="Test3002 VIA Rhine III";

template<>
bool Testit<3002>::Main() 
 { 
  Dev::PCIBus::HostInitExit pci_host;
  
  auto *info=pci_host.find(Driver::VIA_Rhine_III::VendorId,Driver::VIA_Rhine_III::DeviceId);
  
  if( !info ) return false;
  
  Engine engine(*info,pci_host.getAddressMap());
  
  engine.do_startTask(DefaultTaskPriority,DefaultStackLen);
  
  Task::Sleep(10_sec);
  
  engine.do_stopTask();
  
  return true;
 }
 
} // namespace App
 
