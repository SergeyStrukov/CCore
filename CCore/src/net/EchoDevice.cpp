/* EchoDevice.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/net/EchoDevice.h>

#include <CCore/inc/Print.h>
 
namespace CCore {
namespace Net {

/* class EchoDevice */ 

const char * GetTextDesc(EchoDevice::Event ev)
 {
  static const char *const Table[]=
   {
    "Rx",
    
    "No packet",
    "Bad packet format",
    
    "Connection open",
    "Connection lost",
    "Connection close",
   
    ""
   };
   
  return Table[ev]; 
 }
 
void EchoDevice::count(Event ev)
 {
  Mutex::Lock lock(mutex);
 
  stat.count(ev);
 }
 
void EchoDevice::echo(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data)
 {
  if( packet.checkDataLen(format,data.len) )
    {
     packet.setDataLen(format,data.len).copy(data.ptr);
    
     mp->outbound(point,packet);
    }
  else
    {
     count(Event_badformat);
    
     packet.complete();
    }   
 }
   
void EchoDevice::inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data)
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
     echo(point,echo_packet,data);
    }  
  
  packet.complete();
 }
     
void EchoDevice::tick()
 {
  // do nothing
 }

void EchoDevice::connection_open(XPoint point)
 {
  if( show_flag ) Printf(Con,"Connection open #;\n",PointDesc(mp,point));
   
  count(Event_open);
 }

void EchoDevice::connection_lost(XPoint point)
 {
  if( show_flag ) Printf(Con,"Connection lost #;\n",PointDesc(mp,point));
   
  count(Event_lost);
 }

void EchoDevice::connection_close(XPoint point)
 {
  if( show_flag ) Printf(Con,"Connection close #;\n",PointDesc(mp,point));
   
  count(Event_close);
 }
    
EchoDevice::EchoDevice(StrLen mp_dev_name,ulen max_packets,bool show_flag_)
 : hook(mp_dev_name),
   mp(hook),
   show_flag(show_flag_),
   pset("EchoDevice.pset",max_packets),
   mutex("EchoDevice"),
   traffic(0)
 {
  format=mp->getOutboundFormat();
  
  mp->attach(this);  
 }
   
EchoDevice::~EchoDevice()
 {
  mp->detach();
 }
   
void EchoDevice::getStat(StatInfo &ret)
 {
  Mutex::Lock lock(mutex);
  
  ret=stat;
 }
   
uint64 EchoDevice::getTraffic()
 {
  Mutex::Lock lock(mutex);

  return traffic;
 }
 
} // namespace Net
} // namespace CCore
 

