/* SingleBridge.h */ 
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

#ifndef CCore_inc_net_SingleBridge_h
#define CCore_inc_net_SingleBridge_h
 
#include <CCore/inc/net/PacketEndpointDevice.h>

#include <CCore/inc/ObjHost.h>
#include <CCore/inc/StartStop.h>
#include <CCore/inc/Random.h>

namespace CCore {
namespace Net {

/* classes */

class SingleBridge;

/* class SingleBridge */

class SingleBridge : NoCopy 
 {
   class Server : public ObjBase , public PacketEndpointDevice
    {
      SingleBridge &bridge;
      InboundProc *proc;
      
     public:
     
      explicit Server(SingleBridge &bridge);
      
      virtual ~Server();
      
      // PacketEndpointDevice
      
      virtual PacketFormat getOutboundFormat();
   
      virtual void outbound(Packet<uint8> packet);
   
      virtual ulen getMaxInboundLen();
      
      virtual void attach(InboundProc *proc);
   
      virtual void detach();
      
      // methods
      
      void inbound(Packet<uint8> packet);
      
      void tick();
    };
  
   class Client : public ObjBase , public PacketEndpointDevice
    {
      SingleBridge &bridge;
      InboundProc *proc;
      
     public:
     
      explicit Client(SingleBridge &bridge);
      
      virtual ~Client();
      
      // PacketEndpointDevice
      
      virtual PacketFormat getOutboundFormat();
   
      virtual void outbound(Packet<uint8> packet);
   
      virtual ulen getMaxInboundLen();
      
      virtual void attach(InboundProc *proc);
   
      virtual void detach();
      
      // methods
      
      void inbound(Packet<uint8> packet);
      
      void tick();
    };
  
   PacketFormat to_server_format;
   PacketFormat to_client_format;
   
   Server server;
   Client client;
   
   enum Events
    {
     Event_Timeout,
     
     Event_Stop,
     Event_ToServer,
     Event_ToClient,
     
     EventLim
    };
   
   MultiSem<EventLim-1> msem;
   
   Random random; 
   uint32 drop_rate;
   uint32 drop_den;
   
   Mutex mutex;

   PacketList to_server;
   PacketList to_client; 
   bool running;
   
   ObjMaster server_master;
   ObjMaster client_master;
   
  private:
   
   bool drop();
  
   void set(bool running);
  
   void put_to_server(Packet<uint8> packet);
  
   void put_to_client(Packet<uint8> packet);
   
   void send_to_client(Packet<uint8> packet);
   
   void send_to_server(Packet<uint8> packet);
   
   void handle_to_server();
   
   void handle_to_client();
   
   void handle_tick();
   
   // object run
   
   void prepareRun() {}
   
   void objRun();
   
   void completeRun() { set(true); }
   
   void signalStop();
   
   void completeStop();
   
   void complete(PacketList &list);
   
  public:
   
   SingleBridge();
   
   SingleBridge(PacketFormat to_server_format,PacketFormat to_client_format);
   
   ~SingleBridge();
   
   // methods
   
   void setDropRate(uint32 drop_rate_,uint32 drop_den_)
    {
     drop_rate=drop_rate_;
     drop_den=drop_den_;  
    }
   
   static StrLen ServerName() { return "BridgeServer"; }
   
   static StrLen ClientName() { return "BridgeClient"; }
   
   // start/stop
   
   friend class StartStopObject<SingleBridge>;
   
   typedef class StartStopObject<SingleBridge> StartStop;
 };

} // namespace Net
} // namespace CCore
 
#endif
 

