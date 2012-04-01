/* test3003.VIA_Rhine_III.cpp */ 
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

namespace Private_3003 {

/* Show() */

template <class T>
void Show(T &dev,const char *title)
 {
  typename T::StatInfo info;
  
  dev.getStat(info);
  
  Printf(Con,"#;\n\n#15;\n\n",Title(title),info);
 }

/* class Proc */

class Proc : NoCopy , Net::EthProc
 {
   ObjHook hook;
   
   Net::EthDevice *eth;
   
   PacketFormat tx_format;
   
   ulen outbound_enable;
   
  private: 
   
   virtual void start() { outbound_enable=0; }
   
   virtual void linkUp() {}
   
   virtual void linkDown() {}
   
   virtual void tick() 
    {
     outbound_enable++;
     
     eth->signalOutbound(); 
    }
   
   virtual void inbound(Packet<uint8,Net::EthRxExt> packet) { packet.complete(); }
   
   virtual void prepareOutbound() {}
   
   virtual Packet<uint8,Net::EthTxExt> outbound() 
    { 
     if( !outbound_enable ) return Nothing;
     
     outbound_enable--;
     
     Packet<uint8> packet=TryAllocPacket<uint8>();
     
     if( !packet ) return Nothing;
     
     Packet<uint8,Net::EthTxExt> packet2=packet.pushExt<Net::EthTxExt>(Net::MACAddress::Broadcast(),Net::Eth_ARP);
     
     packet2.pushCompleteFunction(DropPacketExt<uint8,Net::EthTxExt>);
     
     static const uint8 data[]=
      {
       0x00, 0x01,
       0x08, 0x00,
       0x06, 0x04,
       0x00, 0x01,
       
       0x00, 0x21, 0x91, 0x52, 0x43, 0x0B,
       0xC0, 0xA8, 0x01, 0x0A,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0xC0, 0xA8, 0x01, 0x01
      };
      
     const ulen len=DimOf(data); 
      
     if( packet2.checkDataLen(tx_format,len) )
       {
        packet2.setDataLen(tx_format,len).copy(data);
       
        return packet2; 
       }
     else
       {
        packet2.complete();
        
        return Nothing;
       }  
    }
   
   virtual void stop() {}
   
  public:
  
   Proc()
    : hook("Eth"),
      eth(hook)
    {
     eth->attach(this);
     
     tx_format=eth->getTxFormat();
    }
   
   ~Proc()
    {
     eth->detach();
    }
    
   Net::EthDevice & getEth() const { return *eth; } 
 };
 
template <class T>
void test(T &dev)
 {
  Proc proc;

  {
   typename T::StartStop start_stop(dev,DefaultTaskPriority);
  
   Task::Sleep(10_sec);
  }
  
  Show(proc.getEth(),"Eth"); 
 }
 
} // namespace Private_3003
 
using namespace Private_3003; 
 
/* Testit<3003> */ 

template<>
const char *const Testit<3003>::Name="Test3003 VIA Rhine III";

template<>
bool Testit<3003>::Main() 
 { 
  Dev::PCIBus::HostInitExit pci_host;
  
  auto *info=pci_host.find(Driver::VIA_Rhine_III::VendorId,Driver::VIA_Rhine_III::DeviceId);
  
  if( !info ) return false;
  
  Driver::VIA_Rhine_III::Device device(*info,pci_host.getAddressMap());
  
  ObjMaster device_master(device,"Eth");

  test(device);
  
  return true;
 }
 
} // namespace App
 
