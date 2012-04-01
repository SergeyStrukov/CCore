/* PCIBus.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_pci_PCIBus_h
#define CCore_inc_pci_PCIBus_h

#include <CCore/inc/dev/DevRW.h>

#include <CCore/inc/base/Quick.h>
 
namespace CCore {
namespace Dev {
namespace PCIBus {

/* PCIBus.desc -> PCIBus.gen.h */ 

#include <CCore/inc/pci/PCIBus.gen.h>

/* consts */ 

const ulen MaxDeviceBars = 6 ;

/* enum Cmd */  

enum Cmd : uint32
 {
  Cmd_IntAck   = 0,
  Cmd_Spec     = 1,
  
  Cmd_IORead   = 2,
  Cmd_IOWrite  = 3,
  
  Cmd_MemRead  = 6,
  Cmd_MemWrite = 7,
  
  Cmd_CfgRead  = 10,
  Cmd_CfgWrite = 11,
  
  Cmd_MemReadMultiple       = 12,
  Cmd_DualAddressCycle      = 13,
  Cmd_MemReadLine           = 14,
  Cmd_MemWriteAndInvalidate = 15
 };
 
/* enum CfgRegAddress */  

enum CfgRegAddress : uint32
 {
  // predefined header
 
  CfgRegID            = 0x0000,
  CfgRegStatusCommand = 0x0004, 
  CfgRegClassRevision = 0x0008,
  CfgRegProp          = 0x000C,
  
  // type 0 header
  
  CfgRegBar0          = 0x0010,
  CfgRegBar1          = 0x0014,
  CfgRegBar2          = 0x0018,
  CfgRegBar3          = 0x001C,
  CfgRegBar4          = 0x0020,
  CfgRegBar5          = 0x0024,
  
  CfgRegSubID         = 0x002C,
  
  CfgRegCaps          = 0x0034,
  CfgRegProp2         = 0x003C 
 };
 
/* enum CfgBarBits */  

enum CfgBarBits : uint32
 {
  CfgBar_IO          = 0x0001,
  CfgBar_Mem64       = 0x0004,
  CfgBar_MemPrefetch = 0x0008,
  
  CfgBar_TypeMask    = 0x000F,
  
  CfgBar_Test        = 0xFFFFFFFF
 };
 
/* enum BarType */ 

enum BarType
 {
  BarTypeNone = 0,
 
  BarTypeIO,
       
  BarTypeMem,
  BarTypeMem64,
  BarTypePrefetchMem,
  BarTypePrefetchMem64,
  
  BarTypeUnknown
 };
     
const char * GetTextDesc(BarType type);

/* types */  

typedef uint32 BusAddressType;

/* classes */  

template <bool IsLEHost=IsLEPlatform> struct Endian;

class AddressMap;

struct DeviceBar;

class MemRW;

struct DeviceBarPtr;

class BusSpace;

/* struct Endian<bool IsLEHost> */ 

template <>
struct Endian<true>
 {
  static uint8  host_to_pci(uint8  value) { return value; }
 
  static uint16 host_to_pci(uint16 value) { return value; }
 
  static uint32 host_to_pci(uint32 value) { return value; }
 
  static uint8  pci_to_host(uint8  value) { return value; }
 
  static uint16 pci_to_host(uint16 value) { return value; }
 
  static uint32 pci_to_host(uint32 value) { return value; }
 };
 
template <>
struct Endian<false>
 {
  static uint8  host_to_pci(uint8  value) { return value; }
 
  static uint16 host_to_pci(uint16 value) { return Quick::ByteSwap16(value); }
 
  static uint32 host_to_pci(uint32 value) { return Quick::ByteSwap32(value); }
 
  static uint8  pci_to_host(uint8  value) { return value; }
 
  static uint16 pci_to_host(uint16 value) { return Quick::ByteSwap16(value); }
 
  static uint32 pci_to_host(uint32 value) { return Quick::ByteSwap32(value); }
 };
 
/* class AddressMap */  

class AddressMap // assume AddressType >= BusAddressType
 {
   AddressType delta; 
   
  private:
  
   AddressType add(AddressType a) const { return a+delta; }
   
   AddressType sub(AddressType a) const { return a-delta; }
   
  public: 
    
   AddressMap(BusAddressType pci_base,AddressType host_base) : delta(pci_base-host_base) {}
    
   BusAddressType host_to_pci(AddressType host) const { return (BusAddressType)add(host); }
   
   AddressType pci_to_host(BusAddressType pci) const { return sub(pci); }
 };
    
/* struct DeviceBar */ 

struct DeviceBar
 {
  static BarType GetType(uint32 bar);
  
  static BusAddressType GetLen(uint32 bar);
  
  // data
  
  uint32 bar;
  
  BarType type;
  BusAddressType len;
  
  BusAddressType pci_base;
  AddressType host_base;
  
  // methods
  
  DeviceBar() : bar(0),type(BarTypeNone),len(0),pci_base(0),host_base(0) {}
       
  template <class CfgBar>
  BarType init(CfgBar &cfg,uint32 ind)
   {
    cfg.set_Bar(ind,CfgBar_Test);
          
    bar=cfg.get_Bar(ind);
    
    len=GetLen(bar);
    type=GetType(bar);
    
    return type;
   }
  
  void setHostBase(AddressMap address_map) 
   { 
    if( type ) host_base=address_map.pci_to_host(pci_base); 
   }
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"type=#; len=#8.16i; pci_base=#8.16i; host_base=#8.16i;",type,len,pci_base,host_base);
   }
 };
      
/* class MemRW */ 

class MemRW : NoCopy
 {
   AddressType host_base;
   
  public:
  
   explicit MemRW(AddressType host_base_) : host_base(host_base_) {}
   
   template <class UInt>
   UInt get(uint32 address) { return Endian<>::pci_to_host(VarGet<UInt>(host_base+address)); }
   
   template <class UInt>
   void set(uint32 address,UInt value) { VarSet<UInt>(host_base+address,Endian<>::host_to_pci(value)); }
 };
 
/* struct DeviceBarPtr */  

struct DeviceBarPtr
 {
  DeviceBar *bar;
  ulen len;
  
  void set(DeviceBar *bar_)
   {
    bar=bar_;
    len=bar_->len;
   }
   
  friend bool operator < (const DeviceBarPtr &a,const DeviceBarPtr &b) { return a.len>b.len; }
 };
 
/* class BusSpace */  

class BusSpace : NoCopy
 {
   BusAddressType pci_base;
   BusAddressType pci_len;
 
  private:
  
   static void GuardNoMem();
   
   static void GuardNotPow2();
   
   BusAddressType alloc(BusAddressType len);
   
  public:
  
   BusSpace(BusAddressType pci_base_,BusAddressType pci_len_) : pci_base(pci_base_),pci_len(pci_len_) {}
   
   void assign(DeviceBarPtr buf[],ulen buf_len);
 };
 
} // namespace PCIBus
} // namespace Dev
} // namespace CCore
 
#endif
 

