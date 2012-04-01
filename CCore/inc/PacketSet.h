/* PacketSet.h */ 
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

#ifndef CCore_inc_PacketSet_h
#define CCore_inc_PacketSet_h

#include <CCore/inc/PacketPool.h>
 
namespace CCore {

/* consts */ 

const unsigned DefaultMaxPackets = 50 ;

/* classes */ 

struct PacketSetExt;

template <class POD> class PacketSet;

/* struct PacketSetExt */

struct PacketSetExt : PacketCanceller
 {
  // data
  
  DLink<PacketSetExt> link;
  DLink<PacketSetExt> ext_link;
  
  typedef DLink<PacketSetExt>::LinearAlgo<&PacketSetExt::link>::Top Top;
  typedef DLink<PacketSetExt>::LinearAlgo<&PacketSetExt::ext_link>::Top ExtTop;
  
  ExtTop *ext_list;
  
  // constructors
  
  explicit PacketSetExt(PacketHeader *packet) : PacketCanceller(packet) {}
  
  // methods
  
  void noExt() { ext_list=0; }
  
  void insExt(ExtTop &ext_list_)
   {
    ext_list_.ins(this);
   
    ext_list=&ext_list_;
   }
  
  void delExt()
   {
    if( ext_list ) ext_list->del(this); 
   }
 };

/* class PacketSet<POD> */ 

template <class POD>
class PacketSet : public Funchor_nocopy
 {
  public:
  
   typedef PacketSetExt::ExtTop ExtTop;

  private:
   
   ResSem rsem;
   AntiSem asem;
   Mutex mutex;
   
   PacketSetExt::Top list;
   
  private:
  
   void add(Packet<POD,PacketSetExt> packet);
  
   void add(ExtTop &ext_list,Packet<POD,PacketSetExt> packet);
   
   void del(Packet<POD,PacketSetExt> packet);
   
   void buildCancel(ExtTop &cancel_list);
   
   void buildCancel(ExtTop &ext_list,ExtTop &cancel_list);
   
   static void DoCancel(ExtTop &cancel_list);
   
   void cancel();
   
   void complete(PacketHeader *packet);
   
   PacketFunction function_complete() { return FunctionOf(this,&PacketSet::complete); }
   
   void complete_external(PacketHeader *packet);
   
   PacketFunction function_complete_external() { return FunctionOf(this,&PacketSet::complete_external); }
   
   static Packet<POD,PacketSetExt> Push(Packet<POD> packet,PacketFunction complete_function)
    {
     auto packet_=packet.getPtr();
     
     Packet<POD,PacketSetExt> packet2=packet.template pushExt<PacketSetExt>(packet_);
     
     packet2.pushCompleteFunction(complete_function);
     
     return packet2;
    }
   
   Packet<POD> prepare(Packet<POD> packet);
  
   Packet<POD> prepare(ExtTop &ext_list,Packet<POD> packet);
   
  public:
   
   // constructors
  
   explicit PacketSet(ulen max_packets=DefaultMaxPackets);
   
   explicit PacketSet(TextLabel name,ulen max_packets=DefaultMaxPackets);
   
   ~PacketSet();
   
   // own list
   
   Packet<POD> try_get(); 
   
   Packet<POD> get(); // may return 0
   
   Packet<POD> get(TimeScope time_scope); 
   
   Packet<POD> get(MSec timeout); 
   
   Packet<POD> try_get_short(); 
   
   Packet<POD> get_short(); // never return 0 
   
   Packet<POD> get_short(TimeScope time_scope); 
   
   Packet<POD> get_short(MSec timeout); 
   
   void cancel_and_wait();
   
   bool wait(TimeScope time_scope);
   
   bool wait(MSec timeout);
   
   // external list
   
   Packet<POD> try_get(ExtTop &ext_list); 
   
   Packet<POD> get(ExtTop &ext_list); // may return 0
   
   Packet<POD> get(ExtTop &ext_list,TimeScope time_scope); 
   
   Packet<POD> get(ExtTop &ext_list,MSec timeout); 
   
   Packet<POD> try_get_short(ExtTop &ext_list); 
   
   Packet<POD> get_short(ExtTop &ext_list); // never return 0 
   
   Packet<POD> get_short(ExtTop &ext_list,TimeScope time_scope); 
   
   Packet<POD> get_short(ExtTop &ext_list,MSec timeout); 
   
   void cancel(ExtTop &ext_list);
   
   class Cancel : NoCopy
    {
      PacketSet<POD> &pset;
      ExtTop cancel_list;
      
     public:
     
      explicit Cancel(PacketSet<POD> &pset_) : pset(pset_) {}
      
      void build(ExtTop &ext_list) { pset.buildCancel(ext_list,cancel_list); }
      
      void cancel() { DoCancel(cancel_list); }
    };
    
   // external packets 
   
   Packet<POD> enlist(Packet<POD> packet);
  
   Packet<POD> enlist(ExtTop &ext_list,Packet<POD> packet);
 };
 
template <class POD>
void PacketSet<POD>::add(Packet<POD,PacketSetExt> packet)
 {
  Mutex::Lock lock(mutex);
  
  PacketSetExt *ext=packet.getExt();
  
  ext->noExt();
  
  list.ins(ext);
 }
  
template <class POD>
void PacketSet<POD>::add(ExtTop &ext_list,Packet<POD,PacketSetExt> packet)
 {
  Mutex::Lock lock(mutex);
  
  PacketSetExt *ext=packet.getExt();
  
  ext->insExt(ext_list);
  
  list.ins(ext);
 }
 
template <class POD>
void PacketSet<POD>::del(Packet<POD,PacketSetExt> packet)
 {
  Mutex::Lock lock(mutex);
  
  PacketSetExt *ext=packet.getExt();
  
  ext->delExt();
  
  list.del(ext);
 }
   
template <class POD>
void PacketSet<POD>::buildCancel(ExtTop &cancel_list)
 {
  Mutex::Lock lock(mutex);
  
  for(auto cur=list.start(); +cur ;++cur)
    {
     if( cur->getCancelFunction() ) 
       {
        cur->delExt();
        cur->insExt(cancel_list);
       }
    }
 }
 
template <class POD>
void PacketSet<POD>::buildCancel(ExtTop &ext_list,ExtTop &cancel_list)
 {
  Mutex::Lock lock(mutex);
  
  for(auto cur=ext_list.start(); +cur ;)
    {
     if( cur->getCancelFunction() )
       {
        ext_list.del_and_move(cur)->insExt(cancel_list);
       }
     else
       {
        ++cur;
       }  
    }
 }
 
template <class POD>
void PacketSet<POD>::DoCancel(ExtTop &cancel_list)
 {
  while( PacketSetExt *ext=cancel_list.top ) ext->cancel();
 }
  
template <class POD>
void PacketSet<POD>::cancel()
 {
  ExtTop cancel_list;
  
  buildCancel(cancel_list);
  
  DoCancel(cancel_list);
 }
 
template <class POD>
void PacketSet<POD>::complete(PacketHeader *packet_)
 {
  Packet<POD,PacketSetExt> packet=packet_;
  
  del(packet);
  
  packet.popExt().complete();
  
  rsem.give();
 }
 
template <class POD>
void PacketSet<POD>::complete_external(PacketHeader *packet_)
 {
  Packet<POD,PacketSetExt> packet=packet_;
  
  del(packet);
  
  packet.popExt().complete();
  
  asem.dec();
 }
 
template <class POD>
Packet<POD> PacketSet<POD>::prepare(Packet<POD> packet)
 {
  Packet<POD,PacketSetExt> packet2=Push(packet,function_complete());
  
  add(packet2);
  
  return packet2.template forgetExt<1>();
 }
 
template <class POD>
Packet<POD> PacketSet<POD>::prepare(ExtTop &ext_list,Packet<POD> packet)
 {
  Packet<POD,PacketSetExt> packet2=Push(packet,function_complete());
  
  add(ext_list,packet2);
  
  return packet2.template forgetExt<1>();
 }
 
template <class POD>
PacketSet<POD>::PacketSet(ulen max_packets)
 : rsem("PacketSet",max_packets),
   asem("PacketSet"),
   mutex("PacketSet")
 {
 }
   
template <class POD>
PacketSet<POD>::PacketSet(TextLabel name,ulen max_packets)
 : rsem(name,max_packets),
   asem(name),
   mutex(name)
 {
 }
   
template <class POD>
PacketSet<POD>::~PacketSet()
 {
  cancel_and_wait();
  
  asem.wait();
 }
 
template <class POD>
Packet<POD> PacketSet<POD>::try_get()
 {
  if( !rsem.try_take() ) return Nothing;
  
  Packet<POD> packet=TryAllocPacket<POD>();
  
  if( !packet ) 
    {
     rsem.give();
    
     return Nothing;
    }
    
  return prepare(packet); 
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::get()
 {
  rsem.take();
  
  Packet<POD> packet=AllocPacket<POD>();
  
  if( !packet ) 
    {
     rsem.give();
    
     return Nothing;
    }
    
  return prepare(packet); 
 }
 
template <class POD>
Packet<POD> PacketSet<POD>::get(TimeScope time_scope)
 {
  if( !rsem.take(time_scope) ) return Nothing;
  
  Packet<POD> packet=AllocPacket<POD>(time_scope);
  
  if( !packet ) 
    {
     rsem.give();
    
     return Nothing;
    }
    
  return prepare(packet); 
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::get(MSec timeout)
 {
  TimeScope time_scope(timeout);
  
  return get(time_scope);
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::try_get_short()
 {
  if( !rsem.try_take() ) return Nothing;
  
  Packet<POD> packet=TryAllocPacket_short<POD>();
  
  if( !packet ) 
    {
     rsem.give();
    
     return Nothing;
    }
    
  return prepare(packet); 
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::get_short()
 {
  rsem.take();
  
  return prepare(AllocPacket_short<POD>()); 
 }
 
template <class POD>
Packet<POD> PacketSet<POD>::get_short(TimeScope time_scope)
 {
  if( !rsem.take(time_scope) ) return Nothing;
  
  Packet<POD> packet=AllocPacket_short<POD>(time_scope);
  
  if( !packet ) 
    {
     rsem.give();
    
     return Nothing;
    }
    
  return prepare(packet); 
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::get_short(MSec timeout)
 {
  TimeScope time_scope(timeout);
  
  return get_short(time_scope);
 }
   
template <class POD>
void PacketSet<POD>::cancel_and_wait()
 {
  cancel();
  
  rsem.wait();
 }
 
template <class POD>
bool PacketSet<POD>::wait(TimeScope time_scope)
 {
  if( rsem.wait(time_scope) ) return true;
  
  cancel_and_wait();
  
  return false;
 }
 
template <class POD>
bool PacketSet<POD>::wait(MSec timeout)
 {
  if( rsem.wait(timeout) ) return true;
  
  cancel_and_wait();
  
  return false;
 }
 
template <class POD>
Packet<POD> PacketSet<POD>::try_get(ExtTop &ext_list)
 {
  if( !rsem.try_take() ) return Nothing;
  
  Packet<POD> packet=TryAllocPacket<POD>();
  
  if( !packet ) 
    {
     rsem.give();
    
     return Nothing;
    }
    
  return prepare(ext_list,packet); 
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::get(ExtTop &ext_list)
 {
  rsem.take();
  
  Packet<POD> packet=AllocPacket<POD>();
  
  if( !packet ) 
    {
     rsem.give();
    
     return Nothing;
    }
    
  return prepare(ext_list,packet); 
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::get(ExtTop &ext_list,TimeScope time_scope)
 {
  if( !rsem.take(time_scope) ) return Nothing;
  
  Packet<POD> packet=AllocPacket<POD>(time_scope);
  
  if( !packet ) 
    {
     rsem.give();
    
     return Nothing;
    }
    
  return prepare(ext_list,packet); 
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::get(ExtTop &ext_list,MSec timeout)
 {
  TimeScope time_scope(timeout);
  
  return get(ext_list,time_scope);
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::try_get_short(ExtTop &ext_list)
 {
  if( !rsem.try_take() ) return Nothing;
  
  Packet<POD> packet=TryAllocPacket_short<POD>();
  
  if( !packet ) 
    {
     rsem.give();
    
     return Nothing;
    }
    
  return prepare(ext_list,packet); 
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::get_short(ExtTop &ext_list)
 {
  rsem.take();
  
  return prepare(ext_list,AllocPacket_short<POD>()); 
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::get_short(ExtTop &ext_list,TimeScope time_scope)
 {
  if( !rsem.take(time_scope) ) return Nothing;
  
  Packet<POD> packet=AllocPacket_short<POD>(time_scope);
  
  if( !packet ) 
    {
     rsem.give();
    
     return Nothing;
    }
    
  return prepare(ext_list,packet); 
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::get_short(ExtTop &ext_list,MSec timeout)
 {
  TimeScope time_scope(timeout);

  return get_short(ext_list,time_scope);
 }
 
template <class POD>
void PacketSet<POD>::cancel(ExtTop &ext_list)
 {
  ExtTop cancel_list;
  
  buildCancel(ext_list,cancel_list);
  
  DoCancel(cancel_list);
 }
   
template <class POD>
Packet<POD> PacketSet<POD>::enlist(Packet<POD> packet)
 {
  asem.inc();
 
  Packet<POD,PacketSetExt> packet2=Push(packet,function_complete_external());
  
  add(packet2);
  
  return packet2.template forgetExt<1>();
 }
  
template <class POD>
Packet<POD> PacketSet<POD>::enlist(ExtTop &ext_list,Packet<POD> packet)
 {
  asem.inc();
 
  Packet<POD,PacketSetExt> packet2=Push(packet,function_complete_external());
  
  add(ext_list,packet2);
  
  return packet2.template forgetExt<1>();
 }
 
} // namespace CCore
 
#endif
 

