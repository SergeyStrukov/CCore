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
#include <CCore/inc/Fifo.h>
#include <CCore/inc/Array.h>

namespace CCore {
namespace Net {

/* classes */

class EndpointNetFork;

class MultipointNetFork;

/* class EndpointNetFork */

class EndpointNetFork : public ObjBase , public PacketEndpointDevice
 {
   ObjHook hook;

   struct Item : NoThrowFlagsBase
    {
     Packet<uint8> packet;
     PtrLen<const uint8> data;
     
     Item() {}
     
     Item(Packet<uint8> packet_,PtrLen<const uint8> data_) : packet(packet_),data(data_) {}
    };
   
   class Queue : NoCopy
    {
      DynArray<Item> buf;
      Fifo<Item> fifo;
      
     public:
     
      explicit Queue(ulen queue_len);
      
      ~Queue();
      
      bool operator + () const { return !fifo.isEmpty(); }
      
      bool operator ! () const { return fifo.isEmpty(); }
      
      bool put(Item item);
      
      Item get(); // non-empty
    };
   
   class Engine : NoCopy , public InboundProc
    {
      PacketEndpointDevice *ep;

      Mutex proc_mutex;
      
      InboundProc *proc;
      bool proc_enable;
      
      AntiSem proc_asem;
      
      Sem sem;
      Mutex mutex;
      Atomic stop_flag;
      
      Queue queue;
      
      AntiSem asem;
      
     private: 
      
      class Hook : NoCopy
       {
         InboundProc *proc;
         AntiSem *asem;
         
        public:
         
         explicit Hook(Engine &engine);
         
         ~Hook();
         
         bool operator ! () const { return !proc; }
         
         InboundProc * operator -> () const { return proc; }
       };
     
      void work(Item item);
      
      void work();
      
     public:
     
      Engine(PacketEndpointDevice *ep,ulen queue_len);
      
      ~Engine();
      
      PacketEndpointDevice * getEPDevice() { return ep; }
      
      void attach(InboundProc *proc);
      
      void detach();
      
      template <class ... TT>
      void run(ulen task_count,TT ... tt)
       {
        while( task_count-- )
          {
           asem.inc();
           
           RunFuncTask( [this] () { work(); } ,asem.function_dec(),tt...);
          }
       }
      
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
 

