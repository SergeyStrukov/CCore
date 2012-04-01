/* Packet.cpp */ 
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
 
#include <CCore/inc/Packet.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/MemBase.h>

namespace CCore {

/* functions */ 

void GuardLenSubTooShort(const char *name,ulen len,ulen delta)
 {
  Printf(Exception,"#; : #; - #; <= 0",name,len,delta);
 }
 
/* struct PacketFormat */ 
 
PacketFormat PacketFormat::addPrefix(ulen prefix_len) const
 {
  if( max_data<prefix_len )
    {
     Printf(Exception,"CCore::PacketFormat::addPrefix(#;) : too short packet format #;",prefix_len,max_data);
    }
    
  PacketFormat ret;
  
  ret.prefix=prefix+prefix_len;
  ret.max_data=max_data-prefix_len;
  ret.suffix=suffix;
  
  return ret;
 }
  
PacketFormat PacketFormat::addSuffix(ulen suffix_len) const
 {
  if( max_data<suffix_len )
    {
     Printf(Exception,"CCore::PacketFormat::addSuffix(#;) : too short packet format #;",suffix_len,max_data);
    }
    
  PacketFormat ret;
  
  ret.prefix=prefix;
  ret.max_data=max_data-suffix_len;
  ret.suffix=suffix+suffix_len;
  
  return ret;
 }
 
PacketFormat PacketFormat::addPrefixSuffix(ulen prefix_len,ulen suffix_len) const
 {
  ulen len=prefix_len+suffix_len;
 
  if( max_data<len )
    {
     Printf(Exception,"CCore::PacketFormat::addPrefixSuffix(#;,#;) : too short packet format #;",prefix_len,suffix_len,max_data);
    }
    
  PacketFormat ret;
  
  ret.prefix=prefix+prefix_len;
  ret.max_data=max_data-len;
  ret.suffix=suffix+suffix_len;
  
  return ret;
 }
 
/* class PacketBuf */  
 
void PacketBuf::GuardLenAbort()
 {
  Abort("Fatal error : too long packet data len");
 }

PacketBuf::PacketBuf()
 {
  data=0;
  max_data_len=0;
  data_len=0;
 }
   
PacketBuf::PacketBuf(ulen max_data_len_)
 {
  if( max_data_len_ )
    {
     data=MemAlloc(max_data_len_);
  
     max_data_len=max_data_len_;
     data_len=0;
    }
  else
    {
     data=0;
     max_data_len=0;
     data_len=0;
    }
 }
   
PacketBuf::~PacketBuf()
 {
  MemFree(data);
 }
 
bool PacketBuf::provide(ulen max_data_len_)
 {
  if( max_data_len==max_data_len_ )
    {
     data_len=0;
     
     return true;
    }
  
  if( max_data_len_<max_data_len )
    {
     if( max_data_len_ )
       {
        MemShrink(data,max_data_len_);
       }
     else
       {
        MemFree(data);
        
        data=0;
       }
     
     max_data_len=max_data_len_;
     data_len=0;
     
     return true;
    }
  
  if( MemExtend(data,max_data_len_) )
    {
     max_data_len=max_data_len_;
     data_len=0;
     
     return true;
    }
  
  if( void *data_=TryMemAlloc(max_data_len_) )  
    {
     MemFree(data);
     
     data=data_;
     max_data_len=max_data_len_;
     data_len=0;
     
     return true;
    }
    
  return false;  
 }
 
void PacketBuf::detach()
 {
  if( data )
    {
     MemFree(data);
    
     data=0;
     max_data_len=0;
     data_len=0;
    }
 }
 
void PacketBuf::moveTo(PacketBuf &pbuf)
 {
  if( &pbuf==this ) return;
  
  MemFree(pbuf.data);
  
  pbuf.data=Replace_null(data);
  pbuf.max_data_len=Replace_null(max_data_len);
  pbuf.data_len=Replace_null(data_len);
 }
 
/* class PacketHeader */ 

void PacketHeader::PushCompleteFunctionAbort()
 {
  Abort("Fatal error : packet complete stack overflow");
 }
 
void PacketHeader::PopCompleteFunctionAbort()
 {
  Abort("Fatal error : packet complete stack underflow");
 }
 
void PacketHeader::PushExtAbort()
 {
  Abort("Fatal error : packet extension stack overflow");
 }
 
void PacketHeader::initList()
 {
  Algo::Init(this);
  
  in_list=false;
 }
 
PacketHeader::PacketHeader(PacketFunction complete_function) noexcept(EnableNoExcept)
 {
  time_stamp=0;
     
  cancel_state=Packet_NoCancelFunction;
  cancel_arg=0;

  stack[0]=complete_function;
  stack_len=1;
  
  ext_len=0;
  
  initList();
 }

void PacketHeader::recycle(PacketFunction complete_function)
 {
  if( ext_len ) Abort("Fatal error : packet has extensions");
  
  if( stack_len ) Abort("Fatal error : packet has complete functions");
  
  if( cancel_state==Packet_HasCancelFunction ) Abort("Fatal error : packet has a cancel function on recycle(...)");
  
  pbuf.setRawLen(0);
 
  time_stamp=0;
     
  cancel_state=Packet_NoCancelFunction;
  cancel_arg=0;

  stack[0]=complete_function;
  stack_len=1;
 }
    
PacketCancelState PacketHeader::setCancelFunction(PacketFunction cancel_function_,void *cancel_arg_)
 {
  Atomic::Type state = cancel_state ;

  if( state==Packet_Cancelled ) return Packet_Cancelled;
  
  if( state==Packet_HasCancelFunction ) Abort("Fatal error : packet has a cancel function on setCancelFunction(...)");
  
  cancel_function=cancel_function_;
  cancel_arg=cancel_arg_;
  
  state = cancel_state.trySet(Packet_NoCancelFunction,Packet_HasCancelFunction) ;
  
  if( state==Packet_Cancelled )
    {
     cancel_function=Nothing;
     cancel_arg=0;
    }
  
  return PacketCancelState(state);
 }

PacketCancelState PacketHeader::clearCancelFunction()
 {
  Atomic::Type state = cancel_state.trySet(Packet_HasCancelFunction,Packet_NoCancelFunction) ;
  
  if( state==Packet_NoCancelFunction ) Abort("Fatal error : packet has no cancel function");
  
  if( state==Packet_HasCancelFunction )
    {
     cancel_function=Nothing;
     cancel_arg=0;
    }
  
  return PacketCancelState(state);
 }

PacketCancelState PacketHeader::getCancelFunction(PacketFunction &ret)
 {
  Atomic::Type state = ( cancel_state=Packet_Cancelled ) ;
  
  if( state==Packet_HasCancelFunction )
    {
     ret=Replace_null(cancel_function);
    }
  
  return PacketCancelState(state);
 }

bool PacketHeader::provide(ulen max_data_len)
 {
  if( in_list ) Abort("Fatal error : packet is in list on provide(...)");

  return pbuf.provide(max_data_len);
 }
 
void PacketHeader::detach()
 {
  if( in_list ) Abort("Fatal error : packet is in list on detach(...)");

  pbuf.detach();
 }
 
void PacketHeader::attach(PacketBuf &pbuf_)
 {
  if( in_list ) Abort("Fatal error : packet is in list on attach(...)");
  
  pbuf_.moveTo(pbuf);
 }
   
void PacketHeader::detach(PacketBuf &pbuf_)
 {
  if( in_list ) Abort("Fatal error : packet is in list on detach(PacketBuf &)");
  
  pbuf.moveTo(pbuf_);
 }

void PacketHeader::detach(PacketHeader *dst)
 {
  if( in_list || dst->in_list ) Abort("Fatal error : packet is in list on detach(PacketHeader *)");
  
  pbuf.moveTo(dst->pbuf);
 }
 
/* struct PacketList */ 

void PacketList::post_ins(PacketHeader *packet)
 {
  packet->in_list=true;
  
  count++;
  total_len+=packet->getMaxRawLen();
 }
  
void PacketList::post_del(PacketHeader *packet)
 {
  packet->initList();  
  
  count--;
  total_len-=packet->getMaxRawLen();
 }
 
PacketList::PacketList()
 {
  count=0;
  total_len=0;
 }
 
PacketList::~PacketList()
 {
  if( count ) Abort("Fatal error : packet list is not empty on exit");
 }
 
void PacketList::put(PacketHeader *packet)
 {
  if( packet->in_list ) Abort("Fatal error : packet is in list on put(...)");
    
  list.ins_last(packet); 
  
  post_ins(packet); 
 }
  
void PacketList::put_first(PacketHeader *packet)
 {
  if( packet->in_list ) Abort("Fatal error : packet is in list put_first(...)");

  list.ins_first(packet);
  
  post_ins(packet);
 }
  
PacketHeader * PacketList::get()
 {
  if( PacketHeader *ret=list.del_first() )
    {
     post_del(ret);
    
     return ret;
    }
    
  return 0;  
 }
  
PacketHeader * PacketList::get_last()
 {
  if( PacketHeader *ret=list.del_last() )
    {
     post_del(ret);
    
     return ret;
    }
    
  return 0;  
 }
  
void PacketList::del(PacketHeader *packet)
 {
  if( !packet->in_list ) Abort("Fatal error : packet is not in list");
  
  list.del(packet); 
  
  post_del(packet);
 }
    
void PacketList::complete()
 {
  while( PacketHeader *packet=get() ) packet->complete();
 }
 
void PacketList::moveOld(TimeStamp how_old,PacketList &dest)
 {
  TimeStamp now=SecTimer::Get();
  
  for(auto cur=list.start(); +cur ;)
    {
     if( cur->isOld(now,how_old) )
       {
        PacketHeader *packet=list.del_and_move(cur);
        
        post_del(packet);
        
        dest.put(packet);
       }
     else
       {
        ++cur;
       }  
    }
 }
 
} // namespace CCore
 

