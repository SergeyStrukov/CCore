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

#include <CCore/inc/Exception.h>
 
namespace CCore {
namespace Net {

/* class EndpointNetFork */

void EndpointNetFork::Engine::work(Item item)
 {
  Hook hook(host);
  
  if( !hook ) 
    {
     item.packet.complete();
    
     return;
    }
  
  hook->inbound(item.packet,item.data);
 }

void EndpointNetFork::Engine::work()
 {
  for(;;)
    {
     sem.take();
     
     if( stop_flag ) 
       {
        sem.give();
        
        return;
       }
     
     Item item;
     
     {
      Mutex::Lock lock(mutex);
      
      item=queue.get();
     }
     
     work(item);
    }
 }

EndpointNetFork::Engine::Engine(PacketEndpointDevice *ep_,ulen queue_len)
 : ep(ep_),
   host("Net::EndpointNetFork","EndpointNetFork.host"),
   sem("EndpointNetFork.sem"),
   mutex("EndpointNetFork.mutex"),
   queue(queue_len),
   asem("EndpointNetFork.asem")
 {
  ep->attach(this);
 }

EndpointNetFork::Engine::~Engine()
 {
  ep->detach();
  
  stop_flag=1;
  
  sem.give();
  
  asem.wait();
  
  while( +queue ) work(queue.get());
 }

void EndpointNetFork::Engine::attach(InboundProc *proc)
 {
  host.attach(proc);
 }

void EndpointNetFork::Engine::detach()
 {
  host.detach();
 }

void EndpointNetFork::Engine::inbound(Packet<uint8> packet,PtrLen<const uint8> data)
 {
  Item item(packet,data);
  
  bool ok;
  
  {
   Mutex::Lock lock(mutex);
   
   ok=queue.put(item);
  }
  
  if( ok )
    sem.give();
  else 
    work(item);
 }
 
void EndpointNetFork::Engine::tick()
 {
  Hook hook(host);
  
  if( !hook ) return;
  
  hook->tick();
 }

EndpointNetFork::EndpointNetFork(StrLen ep_dev_name,ulen queue_len)
 : hook(ep_dev_name),
   engine(hook,queue_len)
 {
 }
  
EndpointNetFork::~EndpointNetFork()
 {
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

/* class MultipointNetFork */

void MultipointNetFork::Engine::work(Item item)
 {
  Hook hook(host);
  
  if( !hook ) 
    {
     item.packet.complete();
    
     return;
    }
  
  hook->inbound(item.point,item.packet,item.data);
 }

void MultipointNetFork::Engine::work()
 {
  for(;;)
    {
     sem.take();
     
     if( stop_flag ) 
       {
        sem.give();
        
        return;
       }
     
     Item item;
     
     {
      Mutex::Lock lock(mutex);
      
      item=queue.get();
     }
     
     work(item);
    }
 }

MultipointNetFork::Engine::Engine(PacketMultipointDevice *mp_,ulen queue_len)
 : mp(mp_),
   host("Net::MultipointNetFork","MultipointNetFork.host"),
   sem("MultipointNetFork.sem"),
   mutex("MultipointNetFork.mutex"),
   queue(queue_len),
   asem("MultipointNetFork.asem")
 {
  mp->attach(this);
 }

MultipointNetFork::Engine::~Engine()
 {
  mp->detach();
  
  stop_flag=1;
  
  sem.give();
  
  asem.wait();
  
  while( +queue ) work(queue.get());
 }

void MultipointNetFork::Engine::attach(InboundProc *proc)
 {
  host.attach(proc);
 }

void MultipointNetFork::Engine::detach()
 {
  host.detach();
 }

void MultipointNetFork::Engine::inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data)
 {
  Item item(point,packet,data);
  
  bool ok;
  
  {
   Mutex::Lock lock(mutex);
   
   ok=queue.put(item);
  }
  
  if( ok )
    sem.give();
  else 
    work(item);
 }
 
void MultipointNetFork::Engine::tick()
 {
  Hook hook(host);
  
  if( !hook ) return;
  
  hook->tick();
 }

MultipointNetFork::MultipointNetFork(StrLen mp_dev_name,ulen queue_len)
 : hook(mp_dev_name),
   engine(hook,queue_len)
 {
 }
  
MultipointNetFork::~MultipointNetFork()
 {
 }

StrLen MultipointNetFork::toText(XPoint point,PtrLen<char> buf)
 {
  return engine.getMPDevice()->toText(point,buf);
 }

PacketFormat MultipointNetFork::getOutboundFormat()
 {
  return engine.getMPDevice()->getOutboundFormat();
 }
 
void MultipointNetFork::outbound(XPoint point,Packet<uint8> packet)
 {
  engine.getMPDevice()->outbound(point,packet); 
 }
 
ulen MultipointNetFork::getMaxInboundLen()
 {
  return engine.getMPDevice()->getMaxInboundLen();
 }
 
void MultipointNetFork::attach(InboundProc *proc)
 {
  engine.attach(proc);
 }
 
void MultipointNetFork::detach()
 {
  engine.detach();
 }

} // namespace Net
} // namespace CCore
 

