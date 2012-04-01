/* PacketPool.h */ 
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

#ifndef CCore_inc_PacketPool_h
#define CCore_inc_PacketPool_h

#include <CCore/inc/PlanInit.h>
#include <CCore/inc/Packet.h>
#include <CCore/inc/Task.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_PacketPool();

/* global const PacketPool_PacketCount */

extern const ulen PacketPool_PacketCount ;

/* global const PacketPool_PacketMaxDataLen */

extern const ulen PacketPool_PacketMaxDataLen ;

/* functions */ 

PacketHeader * TryAllocPacket_raw();

PacketHeader * AllocPacket_raw(); // may return 0

PacketHeader * AllocPacket_raw(MSec timeout);

PacketHeader * AllocPacket_raw(TimeScope time_scope);

PacketHeader * TryAllocPacket_raw_short();

PacketHeader * AllocPacket_raw_short(); // never return 0

PacketHeader * AllocPacket_raw_short(MSec timeout);

PacketHeader * AllocPacket_raw_short(TimeScope time_scope);

void DetachPacketBufs();

template <class POD>
Packet<POD> TryAllocPacket() { return TryAllocPacket_raw(); }
 
template <class POD>
Packet<POD> AllocPacket() { return AllocPacket_raw(); } // may return 0
 
template <class POD>
Packet<POD> AllocPacket(MSec timeout) { return AllocPacket_raw(timeout); }
 
template <class POD>
Packet<POD> AllocPacket(TimeScope time_scope) { return AllocPacket_raw(time_scope); }
                                                                       
template <class POD>
Packet<POD> TryAllocPacket_short() { return TryAllocPacket_raw_short(); }
 
template <class POD>
Packet<POD> AllocPacket_short() { return AllocPacket_raw_short(); } // never return 0
 
template <class POD>
Packet<POD> AllocPacket_short(MSec timeout) { return AllocPacket_raw_short(timeout); }
 
template <class POD>
Packet<POD> AllocPacket_short(TimeScope time_scope) { return AllocPacket_raw_short(time_scope); }
                                                                       
/* classes */ 

class PacketPool;

/* class PacketPool */ 

class PacketPool : public Funchor_nocopy
 {
   void *mem;
   
   ulen max_data_len;
   
   Mutex mutex;
   
   PacketList list;
   ulen use_count;
   
   Sem sem;
   
  private:
  
   PacketHeader * do_get_first();
   
   PacketHeader * do_get();
 
   PacketHeader * do_get_short();
   
   void do_free_first(PacketHeader *packet);
   
   void do_free_last(PacketHeader *packet);
   
   void do_free(PacketHeader *packet);
   
   void free(PacketHeader *packet);
   
   PacketFunction function_free() { return FunctionOf(this,&PacketPool::free); }
   
   void init(ulen count);
   
  public:
   
   // constructors
  
   explicit PacketPool(ulen count,ulen max_data_len=DefaultPacketMaxDataLen);
   
   PacketPool(TextLabel name,ulen count,ulen max_data_len=DefaultPacketMaxDataLen);
   
   ~PacketPool();
   
   // get
   
   PacketHeader * try_get();
   
   PacketHeader * get(); // may return 0
   
   PacketHeader * get(MSec timeout);
   
   PacketHeader * get(TimeScope time_scope);
   
   // get_short
   
   PacketHeader * try_get_short();
   
   PacketHeader * get_short(); // never return 0
   
   PacketHeader * get_short(MSec timeout);
   
   PacketHeader * get_short(TimeScope time_scope);
   
   // detachBufs
   
   void detachBufs();
 };
 
} // namespace CCore
 
#endif
 

