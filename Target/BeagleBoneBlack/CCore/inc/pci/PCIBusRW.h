/* PCIBusRW.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_pci_PCIBusRW_h
#define CCore_inc_pci_PCIBusRW_h

#include <CCore/inc/Printf.h>

#include <CCore/inc/pci/PCIBus.h>
 
namespace CCore {
namespace Dev {
namespace PCIBus {

/* classes */ 

struct DeviceId;

struct DeviceInfo;

class IntConnector;

class HostCfgRW;

class CfgRW;

class IORW;

/* struct DeviceId */ 

struct DeviceId
 {
  static const unsigned SlotLim     = 4 ;
  static const unsigned FunctionLim = 8 ;
  
  unsigned slot;    
  unsigned function;
  
  DeviceId() : slot(0),function(0) {}
  
  DeviceId(unsigned slot_,unsigned function_) : slot(slot_),function(function_) {}
 };
 
/* struct DeviceInfo */ 

struct DeviceInfo
 {
  DeviceId id;
  
  DeviceBar bars[MaxDeviceBars];
 };
  
/* class IntConnector */ 

class IntConnector : NoCopy
 {
   unsigned slot;
 
  public:
  
   explicit IntConnector(const DeviceId &id) : slot(id.slot) {}
   
   void setup(Function<void (void)> handle_int);
   
   void cleanup();
   
   void clear();
 };
    
/* class HostCfgRW */ 
 
class HostCfgRW : NoCopy
 {
  public:
  
   // uint32 , align(UInt) [0,255)
   
   template <class UInt>
   UInt get(uint32 address);
   
   template <class UInt>
   void set(uint32 address,UInt value);
 };
 
/* class CfgRW */ 

class CfgRW : NoCopy
 {
   DeviceId id;
 
  public:
  
   explicit CfgRW(const DeviceId &id_) : id(id_) {}
   
   // uint32, uint16, uint8, align(UInt) [0,255)
   
   template <class UInt>
   UInt get(uint32 address);
   
   template <class UInt>
   void set(uint32 address,UInt value);
   
   // probe
   
   static bool Probe(DeviceId id);
 };
 
/* class IORW */ 

class IORW : NoCopy
 {
   BusAddressType pci_base;
   
  public:
  
   explicit IORW(BusAddressType pci_base_) : pci_base(pci_base_) {}
   
   // uint32, uint16, uint8, align(UInt) 
   
   template <class UInt>
   UInt get(uint32 address);
   
   template <class UInt>
   void set(uint32 address,UInt value);
 };
 
} // namespace PCIBus
} // namespace Dev
} // namespace CCore
 
#endif
 

