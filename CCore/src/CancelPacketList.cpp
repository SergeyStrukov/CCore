/* CancelPacketList.cpp */ 
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
 
#include <CCore/inc/CancelPacketList.h>

#include <CCore/inc/Abort.h>
 
namespace CCore {

/* class CancelPacketList */ 

const char * GetTextDesc(CancelPacketList::Event ev)
 {
  static const char *const Table[]=
   {
    "Cancelled",
    "Cancelled on put",
    
    ""
   };
 
  return Table[ev];
 }
 
void CancelPacketList::cancel(PacketHeader *packet)
 {
  {
   Mutex::Lock lock(mutex);
  
   if( PacketList *list=*packet->getExt<PacketList *>() ) list->del(packet);
   
   stat.count(Event_cancel);
  } 
  
  packet->popExt<PacketList *>();
  
  packet->complete();
 }
 
CancelPacketList::CancelPacketList()
 : mutex("CancelPacketList")
 {
 }
   
CancelPacketList::CancelPacketList(TextLabel name)
 : mutex(name)
 {
 }
   
CancelPacketList::~CancelPacketList()
 {
 }
   
void CancelPacketList::getStat(StatInfo &ret)
 {
  Mutex::Lock lock(mutex);
  
  ret=stat;
 }
 
bool CancelPacketList::try_put(PacketList &list,PacketHeader *packet)
 {
  Mutex::Lock lock(mutex);

  if( packet->setCancelFunction(function_cancel())==Packet_NoCancelFunction )
    {
     packet->pushExt<PacketList *>(&list);
      
     list.put(packet);
       
     return true;
    }
    
  stat.count(Event_cancel_on_put);
  
  return false;
 }

void CancelPacketList::put(PacketList &list,PacketHeader *packet)
 {
  if( !try_put(list,packet) ) packet->complete();
 }
   
PacketHeader * CancelPacketList::get(PacketList &list)
 {
  for(;;)
    {
     Mutex::Lock lock(mutex);
 
     PacketHeader *packet=list.get();
  
     if( !packet ) return 0;
  
     if( packet->clearCancelFunction()!=Packet_Cancelled ) 
       {
        packet->popExt<PacketList *>();
       
        return packet;
       }
     else
       {
        *packet->getExt<PacketList *>()=0;
       }
    } 
 }
 
void CancelPacketList::get(PacketList &list,PacketList &dst)
 {
  for(;;)
    {
     Mutex::Lock lock(mutex);
 
     PacketHeader *packet=list.get();
  
     if( !packet ) return;
  
     if( packet->clearCancelFunction()!=Packet_Cancelled ) 
       {
        packet->popExt<PacketList *>();
       
        dst.put(packet);
       }
     else
       {
        *packet->getExt<PacketList *>()=0;
       }
    } 
 }
 
void CancelPacketList::complete(PacketList &list)
 {
  PacketList temp;
  
  get(list,temp);
  
  temp.complete();
 }
 
} // namespace CCore
 

