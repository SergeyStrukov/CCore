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

EndpointNetFork::Queue::Queue(ulen queue_len)
 : buf(queue_len),
   fifo(buf.getPtr(),buf.getLen())
 {
 }

EndpointNetFork::Queue::~Queue()
 {
 }

bool EndpointNetFork::Queue::put(Item item)
 {
  return fifo.put(item);
 }

auto EndpointNetFork::Queue::get() -> Item
 {
  Item ret;
  
  fifo.get_swap(ret);
    
  return ret; 
 }

EndpointNetFork::Engine::Hook::Hook(Engine &engine)
 {
  {
   Mutex::Lock lock(engine.proc_mutex);
  
   if( engine.proc_enable )
     {
      proc=engine.proc;
     
      asem=&engine.proc_asem;
     }
   else
     {
      proc=0;
     }
  }
  
  if( proc ) asem->inc();
 }

EndpointNetFork::Engine::Hook::~Hook()
 {
  if( proc ) asem->dec();
 }

void EndpointNetFork::Engine::work(Item item)
 {
  Hook hook(*this);
  
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
   proc_mutex("EndpointNetFork.proc_mutex"),
   proc(0),
   proc_enable(false),
   proc_asem("EndpointNetFork.proc_asem"),
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

void EndpointNetFork::Engine::attach(InboundProc *proc_)
 {
  bool has_proc;
  
  {
   Mutex::Lock lock(proc_mutex);
   
   if( proc )
     {
      has_proc=true;
     }
   else 
     {
      has_proc=false;
      proc=proc_;
      proc_enable=true;
     }
  }

  if( has_proc )
    {
     Printf(Exception,"CCore::Net::EndpointNetFork(...) : already attached");
    }
 }

void EndpointNetFork::Engine::detach()
 {
  {
   Mutex::Lock lock(proc_mutex);
   
   proc_enable=false;
  }
  
  proc_asem.wait();
  
  {
   Mutex::Lock lock(proc_mutex);
   
   proc=0;
  }
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
  Hook hook(*this);
  
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

} // namespace Net
} // namespace CCore
 

