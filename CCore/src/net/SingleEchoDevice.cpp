/* SingleEchoDevice.cpp */ 
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
 
#include <CCore/inc/net/SingleEchoDevice.h>
 
namespace CCore {
namespace Net {

/* class SingleEchoDevice */

const char * GetTextDesc(SingleEchoDevice::Event ev)
 {
  static const char *const Table[]=
   {
    "Rx",
    
    "No packet",
    "Bad packet format",
    
    "Connection lost",
    "Connection close",
   
    ""
   };
   
  return Table[ev]; 
 }
 
void SingleEchoDevice::count(Event ev)
 {
  Mutex::Lock lock(mutex);
 
  stat.count(ev);
 }
 
void SingleEchoDevice::echo(Packet<uint8> packet,PtrLen<const uint8> data)
 {
  if( packet.checkDataLen(format,data.len) )
    {
     packet.setDataLen(format,data.len).copy(data.ptr);
    
     ep->outbound(packet);
    }
  else
    {
     count(Event_badformat);
    
     packet.complete();
    }   
 }
   
void SingleEchoDevice::inbound(Packet<uint8> packet,PtrLen<const uint8> data)
 {
  count(Event_inbound);
  
  traffic+=data.len;
 
  Packet<uint8> echo_packet=pset.try_get();
  
  if( !echo_packet ) 
    {
     count(Event_nopacket);
    }
  else
    {
     echo(echo_packet,data);
    }  
  
  packet.complete();
 }
     
void SingleEchoDevice::tick()
 {
  // do nothing
 }

void SingleEchoDevice::connection_lost()
 {
  count(Event_lost);
 }

void SingleEchoDevice::connection_close()
 {
  count(Event_close);
 }

SingleEchoDevice::SingleEchoDevice(StrLen ep_dev_name,ulen max_packets)
 : hook(ep_dev_name),
   ep(hook),
   pset("SingleEchoDevice.pset",max_packets),
   mutex("SingleEchoDevice"),
   traffic(0)
 {
  format=ep->getOutboundFormat();
  
  ep->attach(this);  
 }
   
SingleEchoDevice::~SingleEchoDevice()
 {
  ep->detach();
 }
   
void SingleEchoDevice::getStat(StatInfo &ret)
 {
  Mutex::Lock lock(mutex);
  
  ret=stat;
 }
   
uint64 SingleEchoDevice::getTraffic()
 {
  Mutex::Lock lock(mutex);

  return traffic;
 }

} // namespace Net
} // namespace CCore
 

