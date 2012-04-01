/* PacketPool.cpp */ 
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
 
#include <CCore/inc/PacketPool.h>
 
#include <CCore/inc/Abort.h>
#include <CCore/inc/MemBase.h>

namespace CCore {

/* GetPlanInitNode_...() */ 

namespace Private_PacketPool {

class DefaultPool : public PacketPool
 {
  public:
  
   DefaultPool() : PacketPool("!PacketPool",PacketPool_PacketCount,PacketPool_PacketMaxDataLen) {}
   
   ~DefaultPool() {}
   
   static const char * GetTag() { return "PacketPool"; }
 };
 
PlanInitObject<DefaultPool,PlanInitReq<GetPlanInitNode_MemBase> > Object CCORE_INITPRI_1 ;

} // namespace Private_PacketPool
 
using namespace Private_PacketPool;
 
PlanInitNode * GetPlanInitNode_PacketPool() { return &Object; }
 
/* functions */ 

PacketHeader * TryAllocPacket_raw()
 {
  return Object->try_get();
 }
 
PacketHeader * AllocPacket_raw()
 {
  return Object->get();
 }
 
PacketHeader * AllocPacket_raw(MSec timeout)
 {
  return Object->get(timeout);
 }
 
PacketHeader * AllocPacket_raw(TimeScope time_scope)
 {
  return Object->get(time_scope);
 }
 
PacketHeader * TryAllocPacket_raw_short()
 {
  return Object->try_get_short();
 }
 
PacketHeader * AllocPacket_raw_short()
 {
  return Object->get_short();
 }
 
PacketHeader * AllocPacket_raw_short(MSec timeout)
 {
  return Object->get_short(timeout);
 }
 
PacketHeader * AllocPacket_raw_short(TimeScope time_scope)
 {
  return Object->get_short(time_scope);
 }
 
void DetachPacketBufs()
 {
  Object->detachBufs();
 }

/* class PacketPool */ 

PacketHeader * PacketPool::do_get_first()
 {
  Mutex::Lock lock(mutex);

  use_count++;
  
  return list.get();
 }

PacketHeader * PacketPool::do_get()
 {
  PacketHeader *ret=do_get_first();
  
  if( ret->provide(max_data_len) ) return ret;
  
  do_free_last(ret);
  
  sem.give();
  
  return 0;
 }
 
PacketHeader * PacketPool::do_get_short()
 {
  Mutex::Lock lock(mutex);
 
  use_count++;
   
  return list.get_last();
 }
 
void PacketPool::do_free_first(PacketHeader *packet)
 {
  Mutex::Lock lock(mutex);
  
  list.put_first(packet);
  
  use_count--;
 }
 
void PacketPool::do_free_last(PacketHeader *packet)
 {
  Mutex::Lock lock(mutex);
  
  list.put(packet);
  
  use_count--;
 }
 
void PacketPool::do_free(PacketHeader *packet)
 {
  if( packet->getMaxRawLen()==max_data_len )
    {
     do_free_first(packet);
    }
  else
    {
     packet->detach();
     
     do_free_last(packet);
    }  
 }
 
void PacketPool::free(PacketHeader *packet)
 {
  packet->recycle(function_free());
  
  do_free(packet);
  
  sem.give();
 }

void PacketPool::init(ulen count)
 {
  ulen alloc_len=PacketHeader::AllocLen();
  
  mem=MemAlloc(LenOf(count,alloc_len));  
  
  auto place=PlaceAt(mem);
  
  for(ulen cnt=count; cnt ;cnt--,place+=alloc_len)
    {
     PacketHeader *packet=new(place) PacketHeader(function_free());
     
     list.put(packet);
    }
 }
 
PacketPool::PacketPool(ulen count,ulen max_data_len_)
 : max_data_len(max_data_len_),
   use_count(0),
   sem(count)
 {
  init(count);
 }
   
PacketPool::PacketPool(TextLabel name,ulen count,ulen max_data_len_)
 : max_data_len(max_data_len_),
   mutex(name),
   use_count(0),
   sem(name,count)
 {
  init(count);
 }
   
PacketPool::~PacketPool()
 {
  {
   Mutex::Lock lock(mutex);
   
   if( use_count ) Abort("Fatal error : CCore::PacketPool is used on exit");
  }
  
  while( PacketHeader *packet=list.get() ) packet->~PacketHeader(); // non-trivial
  
  MemFree(mem);
 }

PacketHeader * PacketPool::try_get()
 {
  if( sem.try_take() ) return do_get();
  
  return 0;
 }
   
PacketHeader * PacketPool::get()
 {
  sem.take(); 
  
  return do_get();
 }
   
PacketHeader * PacketPool::get(MSec timeout)
 {
  if( sem.take(timeout) ) return do_get();
  
  return 0;
 }
 
PacketHeader * PacketPool::get(TimeScope time_scope)
 {
  if( sem.take(time_scope) ) return do_get();
  
  return 0;
 }
 
PacketHeader * PacketPool::try_get_short()
 {
  if( sem.try_take() ) return do_get_short();
  
  return 0;
 }
   
PacketHeader * PacketPool::get_short()
 {
  sem.take(); 
  
  return do_get_short();
 }
   
PacketHeader * PacketPool::get_short(MSec timeout)
 {
  if( sem.take(timeout) ) return do_get_short();
  
  return 0;
 }
 
PacketHeader * PacketPool::get_short(TimeScope time_scope)
 {
  if( sem.take(time_scope) ) return do_get_short();
  
  return 0;
 }
 
void PacketPool::detachBufs()
 {
  Mutex::Lock lock(mutex);
  
  PacketList temp;
  
  while( PacketHeader *packet=list.get() ) 
    {
     packet->detach();
     
     temp.put(packet);
    }
  
  Swap(temp,list);
 }
   
} // namespace CCore
 
