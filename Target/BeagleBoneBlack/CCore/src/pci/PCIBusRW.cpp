/* PCIBusRW.cpp */ 
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
 
#include <CCore/inc/pci/PCIBusRW.h>
 
namespace CCore {
namespace Dev {
namespace PCIBus {

/* class IntConnector */ 

void IntConnector::setup(Function<void (void)>)
 {
 }
   
void IntConnector::cleanup()
 {
 }
   
void IntConnector::clear()
 {
 }
    
/* class HostCfgRW */ 

template <>
uint32 HostCfgRW::get<uint32>(uint32) 
 { 
  return 0;
 }
 
template <>
void HostCfgRW::set<uint32>(uint32,uint32) 
 { 
 }
 
/* class CfgRW */ 

template <>
uint32 CfgRW::get<uint32>(uint32) 
 {
  return 0;
 }
 
template <>
uint16 CfgRW::get<uint16>(uint32) 
 { 
  return 0;
 }
 
template <>
uint8 CfgRW::get<uint8>(uint32) 
 { 
  return 0;
 }
 
template <>
void CfgRW::set<uint32>(uint32,uint32) 
 { 
 }
 
template <>
void CfgRW::set<uint16>(uint32,uint16) 
 { 
 }
 
template <>
void CfgRW::set<uint8>(uint32,uint8) 
 {
 }
 
bool CfgRW::Probe(DeviceId)
 {
  return false;
 }
 
/* class IORW */ 

template <>
uint32 IORW::get<uint32>(uint32) 
 { 
  return 0;
 }
 
template <>
uint16 IORW::get<uint16>(uint32) 
 { 
  return 0;
 }
 
template <>
uint8 IORW::get<uint8>(uint32) 
 { 
  return 0;
 }
 
template <>
void IORW::set<uint32>(uint32,uint32) 
 { 
 }
 
template <>
void IORW::set<uint16>(uint32,uint16) 
 { 
 }
 
template <>
void IORW::set<uint8>(uint32,uint8) 
 { 
 }
 
} // namespace PCIBus
} // namespace Dev
} // namespace CCore
 

