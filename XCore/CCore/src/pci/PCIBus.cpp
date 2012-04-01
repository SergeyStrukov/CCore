/* PCIBus.cpp */ 
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
 
#include <CCore/inc/pci/PCIBus.h>
 
#include <CCore/inc/Exception.h>
#include <CCore/inc/Sort.h>

namespace CCore {
namespace Dev {
namespace PCIBus {

/* enum BarType */ 

const char * GetTextDesc(BarType type)
 {
  switch( type )
    {
     case BarTypeNone          : return "none";
     
     case BarTypeIO            : return "io";

     case BarTypeMem           : return "mem";
     case BarTypeMem64         : return "mem64";
     case BarTypePrefetchMem   : return "prefetch mem";
     case BarTypePrefetchMem64 : return "prefetch mem64";
     
     case BarTypeUnknown       : return "unknown";
    }
  
  return "";
 }
 
/* struct DeviceBar */ 

BarType DeviceBar::GetType(uint32 bar)
 {
  if( (bar&0x80000000)==0 ) return BarTypeNone;
 
  switch( bar&CfgBar_TypeMask )
    {
     case CfgBar_IO                               : return BarTypeIO;
     
     case 0                                       : return BarTypeMem;
     case CfgBar_Mem64                            : return BarTypeMem64;
     case CfgBar_MemPrefetch                      : return BarTypePrefetchMem;
     case CfgBar_Mem64|PCIBus::CfgBar_MemPrefetch : return BarTypePrefetchMem64;
     
     default: return BarTypeUnknown;
    }
 }
  
BusAddressType DeviceBar::GetLen(uint32 bar)
 {
  BitClear(bar,CfgBar_TypeMask);
  
  return (bar<<1)^bar;
 }
 
/* class BusSpace */

void BusSpace::GuardNoMem()
 {
  Printf(Exception,"PCI bus : no PCI memory");
 }

void BusSpace::GuardNotPow2()
 {
  Printf(Exception,"PCI bus : bar length is not a power of 2");
 }

BusAddressType BusSpace::alloc(BusAddressType len)
 {
  if( !len || (len&(len-1)) ) GuardNotPow2();
  
  if( len>pci_len ) GuardNoMem();
 
  BusAddressType aligned_base = (pci_base+len-1)&~(len-1) ;
  BusAddressType delta = aligned_base-pci_base ;
  
  pci_base = aligned_base ;
  pci_len -= delta ;
  
  if( len>pci_len ) GuardNoMem();
 
  BusAddressType ret=pci_base;
 
  pci_base+=len;
  pci_len-=len;
  
  return ret;
 }

void BusSpace::assign(DeviceBarPtr buf[],ulen buf_len)
 {
  Sort(buf,buf_len);
  
  for(auto r=Range(buf,buf_len); +r ;++r)
    {
     r->bar->pci_base=alloc(r->len);
    }
 }

} // namespace PCIBus
} // namespace Dev
} // namespace CCore
 

