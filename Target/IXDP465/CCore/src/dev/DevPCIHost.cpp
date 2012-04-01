/* DevPCIHost.cpp */ 
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
 
#include <CCore/inc/dev/DevPCIHost.h>

#include <CCore/inc/dev/DevInt.h>
#include <CCore/inc/dev/DevIntHandle.h>

#include <CCore/inc/dev/IXP465.PCI.h>
#include <CCore/inc/dev/IXP465.GPIO.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/Task.h>

namespace CCore {
namespace Dev {
namespace PCIBus {

/* using */ 

using namespace IXP465;

/* namespace Private_DevPCIHost */ 

namespace Private_DevPCIHost {

/* functions */ 

void PCIIntInit()
 {
  GPIO::Bar bar;
  
  bar.get_Out()
     .setbit(GPIO::Out_Pin8|GPIO::Out_Pin9|GPIO::Out_Pin10|GPIO::Out_Pin11)
     .set(bar.to_OutDisable());
     
  bar.get_IntType2()
     .set_Pin8(GPIO::IntType2_Pin8_Lo)
     .set_Pin9(GPIO::IntType2_Pin9_Lo)
     .set_Pin10(GPIO::IntType2_Pin10_Lo)
     .set_Pin11(GPIO::IntType2_Pin11_Lo)
     .setTo(bar);
  
  bar.null_Int()
     .setbit(GPIO::Int_Pin8|GPIO::Int_Pin9|GPIO::Int_Pin10|GPIO::Int_Pin11)
     .setTo(bar);
 }
 
void PCIIntExit()
 {
  GPIO::Bar bar;
  
  bar.null_Int()
     .setbit(GPIO::Int_Pin8|GPIO::Int_Pin9|GPIO::Int_Pin10|GPIO::Int_Pin11)
     .setTo(bar);
 }
 
/* functions */ 

void PCIIntClearAll()
 {
  PCI::Bar bar;
  
  bar.get_IntStatus()
     .setTo(bar);
 }
 
void PCITrap_int()
 {
  Abort("Fatal error : PCI trap");
 }
 
void PCIIntTrapInit()
 {
  SetupIntHandler(Int_PCI,PCITrap_int);
 }
 
void PCIIntTrapExit()
 {
  CleanupIntHandler(Int_PCI);
 }
 
uint32 PCIErrorStatus()
 {
  PCI::Bar bar;
  
  auto status=bar.get_IntStatus();
  
  status.setTo(bar);
  
  return status.maskbit(PCI::IntStatus_SystemError
                       |PCI::IntStatus_FatalError
                       |PCI::IntStatus_ParityError
                       |PCI::IntStatus_AHBError);
 }
 
struct PrintStatus
 {
  uint32 status;
  
  explicit PrintStatus(uint32 status_) : status(status_) {}
  
  template <class P>
  void print(P &out) const
   {
    if( status&PCI::IntStatus_SystemError ) Putobj(out,"SystemError ");
    
    if( status&PCI::IntStatus_FatalError  ) Putobj(out,"FatalError "); 
    
    if( status&PCI::IntStatus_ParityError ) Putobj(out,"ParityError "); 
    
    if( status&PCI::IntStatus_AHBError    ) Putobj(out,"AHBError "); 
   }
 };
 
void GuardBus(DeviceId id) 
 {
  if( uint32 status=PCIErrorStatus() )
    {
     Printf(Exception,"PCISlot #;:#; enumeration error : #;",id.slot,id.function,PrintStatus(status));
    }
 }
 
/* struct PCIHostCfg */ 
 
struct PCIHostCfg
 {
  // input data
  
   // map host address to pci address , 16 MByte each map region
   
   static const uint32 host_base_address = 0x48000000 ;
  
   static const uint8 host_map0 = 0x48 ;
   static const uint8 host_map1 = 0x49 ;
   static const uint8 host_map2 = 0x4A ;
   static const uint8 host_map3 = 0x4B ;
  
   static const unsigned region_bits = 24 ;
  
   uint8 pci_map0; // host address 0x48xxxxxx -> pci address 0xMMxxxxxx
   uint8 pci_map1; // host address 0x49xxxxxx -> pci address 0xMMxxxxxx
   uint8 pci_map2; // host address 0x4Axxxxxx -> pci address 0xMMxxxxxx
   uint8 pci_map3; // host address 0x4Bxxxxxx -> pci address 0xMMxxxxxx
  
   // map pci address to host address , 16 MByte each map region
  
   bool enable_mem;
  
   uint8 pci_bar0; 
   uint8 host_bar0; // pci address 0xPPxxxxxx -> host address 0xHHxxxxxx
   uint8 pci_bar1;
   uint8 host_bar1;
   uint8 pci_bar2;
   uint8 host_bar2;
   uint8 pci_bar3;
   uint8 host_bar3;
  
   // map pci address to internal PCI controller registers , 16 MByte
  
   static const uint32 doorbell_address = 0x38 ;
  
   uint8 pci_bar4; // pci address 0xPPxxxxxx -> PCI register address 0x00xxxxxx
  
   // map pci address to host IO space , 256 byte
  
   bool enable_io;
  
   uint32 pci_bar5; 
   uint32 host_bar5; // pci address 0xPPPPPPxx -> host address 0xHHHHHHxx
  
  // public
  
  void init();
 };
 
void PCIHostCfg::init()
 {
  PCI::Bar bar;
  
  // check host bits
  {
   if( !bar.get_ControlStatus()
           .testbit(PCI::ControlStatus_Host|PCI::ControlStatus_Arbiter) ) 
     {
      Printf(Exception,"Not a PCI host");
     }
  }

  auto cs=bar.null_ControlStatus();
  
  if( !IsLEPlatform )
    {
     cs.setbit(PCI::ControlStatus_AHBswap|PCI::ControlStatus_PCIswap|PCI::ControlStatus_AHBbigendian);
    }
    
#if 0      
    
  // set reset
  {
   cs.setbit(PCI::ControlStatus_Reset)
     .setTo(bar);
  }
  
  Task::Sleep(1*tuMSec);

  // clear reset
  {
   cs.clearbit(PCI::ControlStatus_Reset)
     .setTo(bar);
  }

  Task::Sleep(1*tuMSec);
  
#endif    
  
  // configure
  {
   bar.null_DMAControl()
      .setbit(PCI::DMAControl_WriteIntEnable|PCI::DMAControl_ReadIntEnable)
      .setTo(bar);
    
   bar.null_IntEnable()
      .setbit(PCI::IntEnable_SystemError|PCI::IntEnable_FatalError
             |PCI::IntEnable_ParityError|PCI::IntEnable_AHBError
             |PCI::IntEnable_DMAWrite|PCI::IntEnable_DMARead)
      .setTo(bar);
    
   bar.null_PCIMemBase()
      .set_Base0(pci_map0)
      .set_Base1(pci_map1)
      .set_Base2(pci_map2)
      .set_Base3(pci_map3)
      .setTo(bar);
    
   bar.null_AHBMemBase()
      .set_Base0(host_bar0)
      .set_Base1(host_bar1)
      .set_Base2(host_bar2)
      .set_Base3(host_bar3)
      .setTo(bar);

   bar.null_AHBIOBase()
      .set_Base(host_bar5)
      .setTo(bar);                         
  }

  // configure PCI Host Cfg
  {
   CfgBar<HostCfgRW> cfgbar;
 
   cfgbar.set_Bar(0,uint32(pci_bar0)<<24);
   cfgbar.set_Bar(1,uint32(pci_bar1)<<24);
   cfgbar.set_Bar(2,uint32(pci_bar2)<<24);
   cfgbar.set_Bar(3,uint32(pci_bar3)<<24);
   cfgbar.set_Bar(4,uint32(pci_bar4)<<24);
   cfgbar.set_Bar(5,uint32(pci_bar5)<< 8);
 
   cfgbar.get_StatusCommand()
         .setbit(StatusCommand_BusMasterEnable)
         .setbitIf( enable_mem ,StatusCommand_MemEnable)
         .setbitIf( enable_io ,StatusCommand_IOEnable)
         .setTo(cfgbar);
  }  

  // complete
  {
   cs.setbit(PCI::ControlStatus_InitComplete)
     .setTo(bar);
  }
 }

} // namespace Private_DevPCIHost
 
using namespace Private_DevPCIHost; 

/* struct DeviceInfoExt */ 

bool DeviceInfoExt::IsSupported(BarType type)
 {
  return type==BarTypeNone || type==BarTypeIO || type==BarTypeMem || type==BarTypePrefetchMem ;
 }
 
void DeviceInfoExt::init(DeviceId id_)
 {
  id=id_;
  
  CfgBar<CfgRW> bar(id_);
  
  bar.null_StatusCommand()
     .setTo(bar);
     
  auto ID=bar.get_ID();   
  auto ClassRevision=bar.get_ClassRevision();
  auto Prop=bar.get_Prop();
  
  vendor_id=ID.get_VendorID();
  device_id=ID.get_DeviceID();
  revision_id=ClassRevision.get_RevisionID();
  
  base_class=ClassRevision.get_BaseClass();
  sub_class=ClassRevision.get_SubClass();
  if_class=ClassRevision.get_IfClass();
  
  is_type0=( Prop.get_Type()==Prop_Type_Type0 );

  if( is_type0 )
    {
     auto SubID=bar.get_SubID();
     
     subsystem_vendor_id=SubID.get_SubVendorID();
     subsystem_id=SubID.get_SubID();
       
     auto Prop2=bar.get_Prop2();  
     
     int_pin=Prop2.get_IntPin();
     
     msi_address=0;
     msi_bits=0;
     
     is_supported=true;  
    
     for(ulen i=0; i<MaxDeviceBars ;i++)
       {
        auto type=bars[i].init(bar,i);
     
        if( !IsSupported(type) ) is_supported=false;
       }
       
     auto Status=bar.get_StatusCommand();
     
     if( Status.maskbit(StatusCommand_CapsList) )
       {
        uint32 cap_off=bar.get_Caps().get_Offset();
        
        while( cap_off )
          {
           if( cap_off&3 ) break;
           
           Type_Cap cap( bar.rw.get<uint32>(cap_off) );
           
           if( cap.get_ID()==Cap_ID_MSI )
             {
              bar.rw.set<uint32>(cap_off,0); // disable MSI
              
              if( cap.maskbit(Cap_MsiA64) )
                {
                 is_supported=false;
                }  
              else
                {
                 msi_bits=cap.get_MsiMultiCap();
                 msi_address=cap_off;
                }
              
              break;
             }
           
           cap_off=cap.get_Next();
          }
       }
    }
  else
    {
     subsystem_vendor_id=0;
     subsystem_id=0;
     
     int_pin=0;
     msi_address=0;
     msi_bits=0;
    
     is_supported=false;
    }

  GuardBus(id_);
 }
     
void DeviceInfoExt::setBars()
 {
  if( is_supported )
    {
     CfgBar<CfgRW> bar(id);
         
     for(ulen i=0; i<MaxDeviceBars ;i++)
       if( bars[i].type )
         {
          bar.set_Bar(i,bars[i].pci_base);
         }
         
     GuardBus(id);    
    }
 }
 
void DeviceInfoExt::setHostBase(AddressMap address_map)
 {
  if( is_supported )
    {
     for(ulen i=0; i<MaxDeviceBars ;i++) bars[i].setHostBase(address_map);
    }
 }
      
void DeviceInfoExt::disable()
 {
  CfgBar<CfgRW> bar(id);
  
  bar.null_StatusCommand()
     .setTo(bar);
 }
 
/* class BusEnum */ 

void BusEnum::scan()
 {
  len=0;
  
  PCIIntClearAll();
  
  for(unsigned s=0; s<DeviceId::SlotLim ;s++)
    {
     DeviceId id0(s,0);
     
     if( CfgRW::Probe(id0) )
       {
        CfgBar<CfgRW> bar(id0);
       
        auto prop=bar.get_Prop();
        
        if( prop.maskbit(Prop_MultiFunc) )
          {
           for(unsigned f=0; f<DeviceId::FunctionLim ;f++)
             {
              DeviceId id(s,f);
             
              if( CfgRW::Probe(id) )
                {
                 table[len].init(id);
                
                 len++;
                }
             }  
          }
        else
          {
           table[len].init(id0);
           
           len++;
          }  
       }
    }
 }
 
void BusEnum::assignMem(BusAddressType pci_base,BusAddressType pci_len)
 {
  DeviceBarPtr buf[DeviceId::SlotLim*DeviceId::FunctionLim*MaxDeviceBars];
  ulen buf_len=0;
 
  for(auto r=Range(table,len); +r ;++r)
    if( r->is_supported )
      for(ulen i=0; i<MaxDeviceBars ;i++)
        {
         DeviceBar *bar=r->bars+i;
         
         if( bar->type ) buf[buf_len++].set(bar);
        }
        
  BusSpace space(pci_base,pci_len);
  
  space.assign(buf,buf_len);
 }
   
void BusEnum::setBars()
 {
  for(auto r=Range(table,len); +r ;++r) r->setBars();
 }
 
void BusEnum::setHostBase(BusAddressType pci_base,AddressType host_base)
 {
  AddressMap address_map(pci_base,host_base);
  
  for(auto r=Range(table,len); +r ;++r) r->setHostBase(address_map);
 }
 
void BusEnum::disable()
 {
  for(auto r=Range(table,len); +r ;++r) r->disable();
 }
   
/* class HostInitExit */ 

HostInitExit::HostInitExit()
 {
  PCIHostCfg cfg;
  
  // PCI: 0x01000000 - 0x04FFFFFF
  
  cfg.pci_map0=0x01;
  cfg.pci_map1=0x02;
  cfg.pci_map2=0x03;
  cfg.pci_map3=0x04;
  
  // PCI: 0x05000000 - 0x08FFFFFF map to 0x00000000 - 0x03FFFFFF
  
  cfg.enable_mem=true;
  
  cfg.pci_bar0=0x05;
  cfg.host_bar0=0x00;
  cfg.pci_bar1=0x06;
  cfg.host_bar1=0x01;
  cfg.pci_bar2=0x07;
  cfg.host_bar2=0x02;
  cfg.pci_bar3=0x08;
  cfg.host_bar3=0x03;
  
  // PCI: 0x09000000 - 0x090000FF map to PCI registers
  
  cfg.pci_bar4=0x09;
  
  // PCI: 0x0A000000 - 0x0A0000FF map to nowhere
  
  cfg.enable_io=false;
  
  cfg.pci_bar5=0x0A0000;
  cfg.host_bar5=0x000000;
  
  // init()
  
  cfg.init();
  
  // enum PCI
    
  bus_enum.scan();
  
  bus_enum.assignMem(0x01000000,0x04000000);
    
  bus_enum.setBars();  
    
  bus_enum.setHostBase(0x01000000,PCIHostCfg::host_base_address);  
    
  PCIIntInit();
  
  PCIIntTrapInit();
 }
   
HostInitExit::~HostInitExit()
 {
  bus_enum.disable();
 
  PCIIntTrapExit();
  
  PCIIntExit();
 }
 
const DeviceInfo * HostInitExit::find(uint32 vendor_id,uint32 device_id) const
 {
  for(auto r=Range(bus_enum); +r ;++r)
    if( r->is_supported && r->vendor_id==vendor_id && r->device_id==device_id )
      return r.ptr;
      
  return 0;    
 }
   
ulen HostInitExit::find(uint32 vendor_id,uint32 device_id,PtrLen<const DeviceInfo *> buf) const
 {
  ulen ret=0;
 
  for(auto r=Range(bus_enum); +r && +buf ;++r)
    if( r->is_supported && r->vendor_id==vendor_id && r->device_id==device_id )
      {
       *buf=r.ptr;
       
       ++buf;
       ++ret;
      }
      
  return ret;    
 }  
   
AddressMap HostInitExit::getAddressMap() const
 {
  return AddressMap(0x05000000,0); 
 }
 
} // namespace PCIBus
} // namespace Dev
} // namespace CCore
 

