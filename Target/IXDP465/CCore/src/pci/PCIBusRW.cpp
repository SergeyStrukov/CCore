/* PCIBusRW.cpp */ 
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
 
#include <CCore/inc/pci/PCIBusRW.h>
 
#include <CCore/inc/dev/DevInt.h>
#include <CCore/inc/dev/DevIntHandle.h>

#include <CCore/inc/dev/IXP465.PCI.h>
#include <CCore/inc/dev/IXP465.GPIO.h>

namespace CCore {
namespace Dev {
namespace PCIBus {

/* using */ 

using namespace IXP465;

/* namespace Private_PCIBusRW */ 

namespace Private_PCIBusRW {

/* functions */ 

IntSource PCIIntSource(unsigned slot) 
 {
  return IntSource( Int_PCI_Slot0+slot );
 }
 
uint32 PCICfgAddress(DeviceId id,uint32 address)
 {
  const uint32 idsel=0x80000000;
  
  return address|(id.function<<8)|(idsel>>id.slot);
 }
 
/* struct PCIRead */ 

struct PCIRead
 {
  uint32 address;
  uint32 value;
  uint32 byte_enable;
  unsigned shift;
  
  void perform(Cmd cmd)
   {
    IntLock lock;
  
    PCI::Bar bar;
  
    bar.set_Address(address);
  
    bar.null_CBE()
       .set_CMD(cmd)
       .set_BE(byte_enable)
       .setTo(bar);
  
    //bar.get_ControlStatus();
  
    value=bar.get_RData();
   }
  
  uint32 get() const { return value; }
  
  uint16 get_half() const { return uint16(value>>shift); }
  
  uint8 get_byte() const { return uint8(value>>shift); }
  
  void full(uint32 address_)
   {
    address=address_;
    byte_enable=0;
    shift=0;
   }
 
  void half(uint32 address_)
   {
    switch( address_&3 )
      {
       case 0 :
        {
         address=address_;
         byte_enable=0x0C;
         shift=0;
        } 
       break;
     
       case 2 :
        {
         address=address_-2;
         byte_enable=0x03;
         shift=16;
        } 
       break;
       
       default:
        {
         address=0;
         byte_enable=0x0F;
         shift=0;
        } 
      }
   }
   
  void byte(uint32 address_) 
   {
    switch( address_&3 )
      {
       case 0 :
        {
         address=address_;
         byte_enable=0x0E;
         shift=0;
        } 
       break;
     
       case 1 :
        {
         address=address_-1;
         byte_enable=0x0D;
         shift=8;
        } 
       break;
     
       case 2 :
        {
         address=address_-2;
         byte_enable=0x0B;
         shift=16;
        } 
       break;
     
       case 3 :
        {
         address=address_-3;
         byte_enable=0x07;
         shift=24;
        } 
       break;
      }
   }
 };
 
/* struct PCIWrite */ 

struct PCIWrite
 {
  uint32 address;
  uint32 value;
  uint32 byte_enable;
  
  void perform(Cmd cmd)
   {
    IntLock lock;
  
    PCI::Bar bar;
  
    bar.set_Address(address);
  
    bar.null_CBE()
       .set_CMD(cmd)
       .set_BE(byte_enable)
       .setTo(bar);

    bar.set_WData(value);   
  
    //bar.get_ControlStatus().set(bar);
   }
  
  void full(uint32 address_,uint32 value_)
   {
    address=address_;
    value=value_;
    byte_enable=0;
   }
 
  void half(uint32 address_,uint16 value_)
   {
    switch( address_&3 )
      {
       case 0 :
        {
         address=address_;
         value=value_;
         byte_enable=0x0C;
        } 
       break;
     
       case 2 :
        {
         address=address_-2;
         value=uint32(value_)<<16;
         byte_enable=0x03;
        } 
       break;
       
       default:
        {
         address=0;
         value=0;
         byte_enable=0x0F;
        } 
      }
   }
   
  void byte(uint32 address_,uint8 value_) 
   {
    switch( address_&3 )
      {
       case 0 :
        {
         address=address_;
         value=value_;
         byte_enable=0x0E;
        } 
       break;
     
       case 1 :
        {
         address=address_-1;
         value=uint32(value_)<<8;
         byte_enable=0x0D;
        } 
       break;
     
       case 2 :
        {
         address=address_-2;
         value=uint32(value_)<<16;
         byte_enable=0x0B;
        } 
       break;
     
       case 3 :
        {
         address=address_-3;
         value=uint32(value_)<<24;
         byte_enable=0x07;
        } 
       break;
      }
   }
 };
 
} // namespace Private_PCIBusRW
 
using namespace Private_PCIBusRW;
 
/* class IntConnector */ 

void IntConnector::setup(Function<void (void)> handle_int)
 {
  SetupIntHandler(PCIIntSource(slot),handle_int);
 }
   
void IntConnector::cleanup()
 {
  CleanupIntHandler(PCIIntSource(slot));
 }
   
void IntConnector::clear()
 {
  GPIO::Bar bar;
  
  bar.null_Int()
     .setbit(GPIO::PinBit(11-slot))
     .setTo(bar);
 }
    
/* class HostCfgRW */ 

template <>
uint32 HostCfgRW::get<uint32>(uint32 address) 
 { 
  IntLock lock;

  PCI::Bar bar;
  
  bar.null_CfgAddressCBE()
     .set_Address(address)
     .set_CMD(PCI::CfgAddressCBE_CMD_Read)
     .setTo(bar);
  
  return bar.get_CfgRData();
 }
 
template <>
void HostCfgRW::set<uint32>(uint32 address,uint32 value) 
 { 
  IntLock lock;

  PCI::Bar bar;
  
  bar.null_CfgAddressCBE()
     .set_Address(address)
     .set_CMD(PCI::CfgAddressCBE_CMD_Write)
     .setTo(bar);
     
  bar.set_CfgWData(value);   
 }
 
/* class CfgRW */ 

template <>
uint32 CfgRW::get<uint32>(uint32 address) 
 { 
  PCIRead op;
  
  op.full(PCICfgAddress(id,address));
  op.perform(Cmd_CfgRead);
 
  return op.get();
 }
 
template <>
uint16 CfgRW::get<uint16>(uint32 address) 
 { 
  PCIRead op;
  
  op.half(PCICfgAddress(id,address));
  op.perform(Cmd_CfgRead);
 
  return op.get_half();
 }
 
template <>
uint8 CfgRW::get<uint8>(uint32 address) 
 { 
  PCIRead op;
  
  op.byte(PCICfgAddress(id,address));
  op.perform(Cmd_CfgRead);
 
  return op.get_byte();
 }
 
template <>
void CfgRW::set<uint32>(uint32 address,uint32 value) 
 { 
  PCIWrite op;
  
  op.full(PCICfgAddress(id,address),value);
  
  op.perform(Cmd_CfgWrite);
 }
 
template <>
void CfgRW::set<uint16>(uint32 address,uint16 value) 
 { 
  PCIWrite op;
  
  op.half(PCICfgAddress(id,address),value);
  
  op.perform(Cmd_CfgWrite);
 }
 
template <>
void CfgRW::set<uint8>(uint32 address,uint8 value) 
 {
  PCIWrite op;
  
  op.byte(PCICfgAddress(id,address),value);
  
  op.perform(Cmd_CfgWrite);
 }
 
bool CfgRW::Probe(DeviceId id)
 {
  IntLock lock;
  
  PCI::Bar bar;
  
  bar.set_Address(PCICfgAddress(id,CfgRegID));
  
  bar.null_CBE()
     .set_CMD(Cmd_CfgRead)
     .setTo(bar);
  
  //bar.get_ControlStatus();
  
  auto status=bar.get_IntStatus();
  
  if( status.maskbit(PCI::IntStatus_FatalError) )
    {
     bar.null_IntStatus()
        .setbit(PCI::IntStatus_FatalError)
        .setTo(bar);
     
     return false;
    }
  else
    {
     uint32 ID=bar.get_RData();
    
     return ID!=0 && ID!=0xFFFFFFFF ;
    } 
 }
 
/* class IORW */ 

template <>
uint32 IORW::get<uint32>(uint32 address) 
 { 
  PCIRead op;
  
  op.full(pci_base+address);
  op.perform(Cmd_IORead);
 
  return op.get();
 }
 
template <>
uint16 IORW::get<uint16>(uint32 address) 
 { 
  PCIRead op;
  
  op.half(pci_base+address);
  op.perform(Cmd_IORead);
 
  return op.get_half();
 }
 
template <>
uint8 IORW::get<uint8>(uint32 address) 
 { 
  PCIRead op;
  
  op.byte(pci_base+address);
  op.perform(Cmd_IORead);
 
  return op.get_byte();
 }
 
template <>
void IORW::set<uint32>(uint32 address,uint32 value) 
 { 
  PCIWrite op;
  
  op.full(pci_base+address,value);
  
  op.perform(Cmd_IOWrite);
 }
 
template <>
void IORW::set<uint16>(uint32 address,uint16 value) 
 { 
  PCIWrite op;
  
  op.half(pci_base+address,value);
  
  op.perform(Cmd_IOWrite);
 }
 
template <>
void IORW::set<uint8>(uint32 address,uint8 value) 
 { 
  PCIWrite op;
  
  op.byte(pci_base+address,value);
  
  op.perform(Cmd_IOWrite);
 }
 
} // namespace PCIBus
} // namespace Dev
} // namespace CCore
 

