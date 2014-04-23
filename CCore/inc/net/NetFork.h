/* NetFork.h */ 
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

#ifndef CCore_inc_net_NetFork_h
#define CCore_inc_net_NetFork_h

#include <CCore/inc/net/PacketEndpointDevice.h>
 
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/Task.h>

namespace CCore {
namespace Net {

/* classes */

class EndpointNetFork;

class MultipointNetFork;

/* class EndpointNetFork */

class EndpointNetFork : public ObjBase , public PacketEndpointDevice
 {
   ObjHook hook;

   struct Item
    {
     Packet<uint8> packet;
     PtrLen<const uint8> data;
     
     Item(Packet<uint8> packet_,PtrLen<const uint8> data_) : packet(packet_),data(data_) {}
    };
   
   class Queue : NoCopy
    {
     public:
     
      explicit Queue(ulen queue_len);
      
      ~Queue();
      
      bool operator + () const;
      
      bool operator ! () const;
      
      bool put(Packet<uint8> packet,PtrLen<const uint8> data);
      
      Item get();
    };
   
   class Engine : NoCopy , public InboundProc
    {
      PacketEndpointDevice *ep;
      
      InboundProc *proc;
      
      Sem sem;
      Mutex mutex;
      
      Queue queue;
      
     private: 
     
      void work();
      
     public:
     
      Engine(PacketEndpointDevice *ep,ulen queue_len);
      
      ~Engine();
      
      PacketEndpointDevice * getEPDevice() { return ep; }
      
      void attach(InboundProc *proc);
      
      void detach();
      
      template <class ... TT>
      void run(ulen task_count,TT ... tt);
      
      void stop();
      
      // InboundProc
      
      virtual void inbound(Packet<uint8> packet,PtrLen<const uint8> data);
       
      virtual void tick();
    };
   
   Engine engine;
   
  private: 
   
   EndpointNetFork(StrLen ep_dev_name,ulen queue_len);
   
  public:
  
   template <class ... TT>
   EndpointNetFork(StrLen ep_dev_name,ulen task_count,ulen queue_len,TT ... tt)
    : EndpointNetFork(ep_dev_name,queue_len)
    {
     engine.run(task_count,tt...);
    }
   
   virtual ~EndpointNetFork();
   
   // PacketEndpointDevice
   
   virtual PacketFormat getOutboundFormat();
    
   virtual void outbound(Packet<uint8> packet);
    
   virtual ulen getMaxInboundLen();
    
   virtual void attach(InboundProc *proc);
    
   virtual void detach();
 };

} // namespace Net
} // namespace CCore
 
#endif
 

