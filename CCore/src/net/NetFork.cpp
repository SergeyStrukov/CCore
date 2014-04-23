/* NetFork.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/net/NetFork.h>
 
namespace CCore {
namespace Net {

/* class EndpointNetFork */

EndpointNetFork::EndpointNetFork(StrLen ep_dev_name,ulen queue_len)
 : hook(ep_dev_name),
   engine(hook,queue_len)
 {
 }
  
EndpointNetFork::~EndpointNetFork()
 {
  engine.stop();
 }

PacketFormat EndpointNetFork::getOutboundFormat()
 {
  return engine.getEPDevice()->getOutboundFormat();
 }
 
void EndpointNetFork::outbound(Packet<uint8> packet)
 {
  engine.getEPDevice()->outbound(packet); 
 }
 
ulen EndpointNetFork::getMaxInboundLen()
 {
  return engine.getEPDevice()->getMaxInboundLen();
 }
 
void EndpointNetFork::attach(InboundProc *proc)
 {
  engine.attach(proc);
 }
 
void EndpointNetFork::detach()
 {
  engine.detach();
 }

} // namespace Net
} // namespace CCore
 

