/* PCIBusRW.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/pci/PCIBusRW.h>
 
namespace CCore {
namespace Dev {
namespace PCIBus {

/* class IntConnector */ 

void IntConnector::setup(Function<void (void)> /*handle_int*/)
 {
  // TODO
 }
   
void IntConnector::cleanup()
 {
  // TODO
 }
   
void IntConnector::clear()
 {
  // TODO
 }
    
/* class HostCfgRW */ 

template <>
uint32 HostCfgRW::get<uint32>(uint32 /*address*/) 
 { 
  // TODO

  return 0;
 }
 
template <>
void HostCfgRW::set<uint32>(uint32 /*address*/,uint32 /*value*/) 
 { 
  // TODO
 }
 
/* class CfgRW */ 

template <>
uint32 CfgRW::get<uint32>(uint32 /*address*/) 
 { 
  // TODO

  return 0;
 }
 
template <>
uint16 CfgRW::get<uint16>(uint32 /*address*/) 
 { 
  // TODO

  return 0;
 }
 
template <>
uint8 CfgRW::get<uint8>(uint32 /*address*/) 
 { 
  // TODO

  return 0;
 }
 
template <>
void CfgRW::set<uint32>(uint32 /*address*/,uint32 /*value*/) 
 { 
  // TODO
 }
 
template <>
void CfgRW::set<uint16>(uint32 /*address*/,uint16 /*value*/) 
 { 
  // TODO
 }
 
template <>
void CfgRW::set<uint8>(uint32 /*address*/,uint8 /*value*/) 
 {
  // TODO
 }
 
bool CfgRW::Probe(DeviceId /*id*/)
 {
  // TODO

  return false;
 }
 
/* class IORW */ 

template <>
uint32 IORW::get<uint32>(uint32 /*address*/) 
 { 
  // TODO

  return 0;
 }
 
template <>
uint16 IORW::get<uint16>(uint32 /*address*/) 
 { 
  // TODO

  return 0;
 }
 
template <>
uint8 IORW::get<uint8>(uint32 /*address*/) 
 { 
  // TODO

  return 0;
 }
 
template <>
void IORW::set<uint32>(uint32 /*address*/,uint32 /*value*/) 
 { 
  // TODO
 }
 
template <>
void IORW::set<uint16>(uint32 /*address*/,uint16 /*value*/) 
 { 
  // TODO
 }
 
template <>
void IORW::set<uint8>(uint32 /*address*/,uint8 /*value*/) 
 { 
  // TODO
 }
 
} // namespace PCIBus
} // namespace Dev
} // namespace CCore
 

