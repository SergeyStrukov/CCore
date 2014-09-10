/* SingleEchoDevice.h */ 
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

#ifndef CCore_inc_net_SingleEchoDevice_h
#define CCore_inc_net_SingleEchoDevice_h
 
#include <CCore/inc/net/PacketEndpointDevice.h>
 
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/PacketSet.h>
#include <CCore/inc/Counters.h>

namespace CCore {
namespace Net {

/* classes */

class SingleEchoDevice;

/* class SingleEchoDevice */

class SingleEchoDevice : NoCopy , public PacketEndpointDevice::InboundProc , public PacketEndpointDevice::ConnectionProc
 {
  public:
  
   enum Event
    {
     Event_inbound,
     
     Event_nopacket,
     Event_badformat,
     
     Event_lost,
     Event_close,
    
     EventLim
    };
    
   friend const char * GetTextDesc(Event ev); 
   
   typedef Counters<Event,EventLim> StatInfo;
    
  private:
  
   ObjHook hook;
   
   Net::PacketEndpointDevice *ep;
   PacketFormat format;
   
   PacketSet<uint8> pset;
   
   Mutex mutex;
   
   StatInfo stat;
   uint64 traffic;
   
  private: 
  
   void count(Event ev);
  
   void echo(Packet<uint8> packet,PtrLen<const uint8> data);
   
   virtual void inbound(Packet<uint8> packet,PtrLen<const uint8> data);
     
   virtual void tick();
    
   virtual void connection_lost();
   
   virtual void connection_close();
   
  public: 
  
   static const ulen DefaultMaxPackets = 200 ;
  
   explicit SingleEchoDevice(StrLen ep_dev_name,ulen max_packets=DefaultMaxPackets);
   
   ~SingleEchoDevice();
   
   void getStat(StatInfo &ret);
   
   uint64 getTraffic();
 };

} // namespace Net
} // namespace CCore
 
#endif
 

