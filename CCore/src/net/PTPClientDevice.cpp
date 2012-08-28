/* PTPClientDevice.cpp */ 
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
 
#include <CCore/inc/net/PTPClientDevice.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/Timer.h>

namespace CCore {
namespace Net {
namespace PTP {

/* functions */

void GuardOutboundTooShort(const char *name)
 {
  Printf(Exception,"#; : too short outbound",name);
 }

/* enum TransResult */ 

const char * GetTextDesc(TransResult result)
 {
  static const char *const Table[]=
   {
    "Ok",                   // Trans_Ok
    
    "Not started",          // Trans_Initial
    "Bad data length",      // Trans_BadDataLen
    "No packet",            // Trans_NoPacket
    "Cancelled",            // Trans_Cancelled
    "Aborted",              // Trans_Aborted
    "Timeout",              // Trans_Timeout
    
    "Bad inbound length 1", // Trans_BadInboundLen1
    "Bad inbound length 2", // Trans_BadInboundLen2
    "Bad inbound length 3", // Trans_BadInboundLen3
    
    ""
   };
 
  return Table[result];
 }
 
/* enum ClientEvent */ 

const char * GetTextDesc(ClientEvent ev)
 {
  static const char *const Table[]=
   {
    "Trans",                 // ClientEvent_Trans
    "Trans done",            // ClientEvent_TransDone
  
    "Trans bad info length", // ClientEvent_BadInfoLen
    "Trans timeout",         // ClientEvent_Timeout
    "Trans cancelled",       // ClientEvent_Cancel
    "Trans aborted",         // ClientEvent_Abort
    
    "-> CALL",               // ClientEvent_CALL
    "-> RECALL",             // ClientEvent_RECALL
    "-> ACK",                // ClientEvent_ACK
    "-> SENDRET",            // ClientEvent_SENDRET
  
    "<- RET",                // ClientEvent_RET
    "<- NOINFO",             // ClientEvent_NOINFO
    "<- RERET",              // ClientEvent_RERET
    "<- CANCEL",             // ClientEvent_CANCEL
  
    "No slot",               // ClientEvent_NoSlot
    "No packet",             // ClientEvent_NoPacket
    
    "Bad inbound",           // ClientEvent_BadInbound
    "Bad outbound",          // ClientEvent_BadOutbound
    
    ""
   };
 
  return Table[ev];
 }
 
/* struct ClientProtoEvent */

void ClientProtoEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Ev=info.addEnum_uint8("PTPClient")
    
                 .addValueName(ClientEvent_Trans,"Trans")
                 .addValueName(ClientEvent_TransDone,"Trans done")
                 
                 .addValueName(ClientEvent_BadInfoLen,"Bad info len")
                 .addValueName(ClientEvent_Timeout,"Timeout")
                 .addValueName(ClientEvent_Cancel,"Cancel")
                 .addValueName(ClientEvent_Abort,"Abort")
                 
                 .addValueName(ClientEvent_CALL,"-> CALL")
                 .addValueName(ClientEvent_RECALL,"-> RECALL")
                 .addValueName(ClientEvent_ACK,"-> ACK")
                 .addValueName(ClientEvent_SENDRET,"-> SENDRET")
                 
                 .addValueName(ClientEvent_RET,"<- RET")
                 .addValueName(ClientEvent_NOINFO,"<- NOINFO")
                 .addValueName(ClientEvent_RERET,"<- RERET")
                 .addValueName(ClientEvent_CANCEL,"<- CANCEL")
                 
                 .addValueName(ClientEvent_NoSlot,"No slot")
                 .addValueName(ClientEvent_NoPacket,"No packet")
                 
                 .addValueName(ClientEvent_BadInbound,"Bad inbound")
                 .addValueName(ClientEvent_BadOutbound,"Bad outbound")
                      
                 .getId();
  
  auto id=info.addStruct("PTPClientEvent")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint8(id_Ev,"event",Offset_ev)
              .getId();
  
  desc.setStructId(info,id);
 }

/* class ClientEngine::Slot */ 

void ClientEngine::Slot::send_CALL(PacketList &complete_list)
 {
  engine->stat.count(ClientEvent_CALL);
  
  PtrLen<const uint8> info=getInfo();
  
  PacketPrefix3 prefix(PacketType_CALL,trans_id,client_slot);
  Packet_CALL3 call((InfoLenType)info.len);
  
  engine->send(complete_list,prefix,call,info,engine->getDataPacket(plist));
 }
 
void ClientEngine::Slot::send_RECALL(PacketList &complete_list)
 {
  engine->stat.count(ClientEvent_RECALL);
  
  PtrLen<const uint8> info=getInfo();
  
  PacketPrefix3 prefix(PacketType_RECALL,trans_id,client_slot);
  Packet_RECALL3 recall(recallNumber(),(InfoLenType)info.len);
  
  engine->send(complete_list,prefix,recall,info,engine->getDataPacket(plist));
 }
 
void ClientEngine::Slot::send_SENDRET(PacketList &complete_list)
 {
  engine->stat.count(ClientEvent_SENDRET);
  
  PacketPrefix4 sendret(PacketType_SENDRET,trans_id,client_slot,server_slot);
  
  engine->send(complete_list,sendret,engine->getDataPacket(plist));
 }
 
void ClientEngine::Slot::send_ACK(PacketList &complete_list)
 {
  engine->stat.count(ClientEvent_ACK);
  
  PacketPrefix4 ack(PacketType_ACK,trans_id,client_slot,server_slot);
  
  engine->send(complete_list,ack,engine->getDataPacket(plist));
 }
 
bool ClientEngine::Slot::start(PacketList &complete_list,Packet<uint8,TransExt> packet_)
 {
  if( packet_.getDataLen()>engine->max_outbound_info_len ) 
    {
     engine->stat.count(ClientEvent_BadInfoLen);
     
     engine->completeError(complete_list,packet_,Trans_BadDataLen);
     
     return false;
    }
 
  packet=packet_;
  
  packet.getExt()->setSlot(client_slot);
  
  engine->getTransId(trans_id);
  
  no_info=false;
  number=1;
  timeout_msec=MinTimeout;
  
  retry_count=MaxRetries;
  
  setTick();
  
  send_CALL(complete_list);
  
  return true;
 }
 
void ClientEngine::Slot::inbound_RET(PacketList &complete_list,Packet<uint8> server_packet,PtrLen<const uint8> server_info)
 {
  send_ACK(complete_list);
  
  engine->completeInfo(complete_list,Replace_null(packet),server_packet,server_info);
 }
   
void ClientEngine::Slot::inbound_CANCEL(PacketList &complete_list)
 {
  send_ACK(complete_list);
  
  engine->stat.count(ClientEvent_Cancel);
  
  engine->completeError(complete_list,Replace_null(packet),Trans_Cancelled);
 }
   
void ClientEngine::Slot::inbound_NOINFO(PacketList &)
 {
  no_info=true;
 }
   
void ClientEngine::Slot::inbound_RERET(PacketList &complete_list)
 {
  send_SENDRET(complete_list);
 }
     
bool ClientEngine::Slot::tick(PacketList &complete_list)
 {
  if( tick_count )
    {
     tick_count--;
     
     return true;
    } 
  else
    {
     if( retry_count )
       {
        retry_count--;
       }
     else
       {
        engine->stat.count(ClientEvent_Timeout);
        
        engine->completeError(complete_list,Replace_null(packet),Trans_Timeout);
       
        return false;
       }  
    
     if( no_info )
       {
        send_SENDRET(complete_list);
       }
     else
       {
        send_RECALL(complete_list);
       }
    
     setTick();
     
     return true;
    }  
 }
 
void ClientEngine::Slot::abort(PacketList &complete_list)
 {
  engine->stat.count(ClientEvent_Abort);
 
  engine->completeError(complete_list,Replace_null(packet),Trans_Aborted);
 }
 
/* class ClientEngine */ 

void ClientEngine::getTransId(TransId &trans_id)
 {
  trans_id.number=trans_number++;
  
  uint64 clock_hi=(uint64)SecTimer::Get();
  uint32 clock_lo=(uint32)ClockTimer::Get();
  
  trans_id.clock=(clock_hi<<32)|clock_lo;
  
  trans_id.number^=seed1;
  trans_id.clock^=seed2;
 }
 
void ClientEngine::activate(Slot *slot)
 {
  slot->active=true;
  
  avail_list.del(slot);
  
  active_list.ins_last(slot);
 }
   
void ClientEngine::deactivate(Slot *slot)
 {
  slot->active=false;
 
  active_list.del(slot);
  
  avail_list.ins_last(slot);
 }
 
void ClientEngine::deactivate_nodel(Slot *slot)
 {
  slot->active=false;
 
  avail_list.ins_last(slot);
 }
 
void ClientEngine::pump(PacketList &complete_list)
 {
  while( Slot *slot=avail_list.top )
    {
     Packet<uint8,TransExt> packet=pending_list.get();
     
     if( !packet ) break;
     
     if( slot->start(complete_list,packet) ) activate(slot);
    }
 }
 
ClientEngine::Slot * ClientEngine::find(const TransId &trans_id,SlotId client_slot,SlotId server_slot)
 {
  if( client_slot>=slots.getLen() ) return 0;
     
  Slot *slot=slots.getPtr()+client_slot;
     
  if( slot->active && slot->trans_id==trans_id ) 
    {
     slot->server_slot=server_slot;
     
     return slot;
    }
     
  return 0;
 }
    
void ClientEngine::inbound_RET(PacketList &complete_list,const TransId &trans_id,SlotId client_slot,SlotId server_slot,Packet<uint8> server_packet,PtrLen<const uint8> server_info)
 {
  if( Slot *slot=find(trans_id,client_slot,server_slot) )
    {
     slot->inbound_RET(complete_list,server_packet,server_info);
     
     deactivate(slot);
    }
  else
    {
     send_ACK(complete_list,trans_id,client_slot,server_slot);
    }  
 }
   
void ClientEngine::inbound_CANCEL(PacketList &complete_list,const TransId &trans_id,SlotId client_slot,SlotId server_slot)
 {
  if( Slot *slot=find(trans_id,client_slot,server_slot) )
    {
     slot->inbound_CANCEL(complete_list);
     
     deactivate(slot);
    }
  else
    {
     send_ACK(complete_list,trans_id,client_slot,server_slot);
    }  
 }
   
void ClientEngine::inbound_NOINFO(PacketList &complete_list,const TransId &trans_id,SlotId client_slot,SlotId server_slot)
 {
  if( Slot *slot=find(trans_id,client_slot,server_slot) )
    {
     slot->inbound_NOINFO(complete_list);
    }
  else
    {
     send_ACK(complete_list,trans_id,client_slot,server_slot);
    }  
 }
   
void ClientEngine::inbound_RERET(PacketList &complete_list,const TransId &trans_id,SlotId client_slot,SlotId server_slot)
 {
  if( Slot *slot=find(trans_id,client_slot,server_slot) )
    {
     slot->inbound_RERET(complete_list);
    }
  else
    {
     send_ACK(complete_list,trans_id,client_slot,server_slot);
    }  
 }
 
void ClientEngine::send_ACK(PacketList &complete_list,const TransId &trans_id,SlotId client_slot,SlotId server_slot)
 {
  stat.count(ClientEvent_NoSlot);
  stat.count(ClientEvent_ACK);
 
  PacketPrefix4 ack(PacketType_ACK,trans_id,client_slot,server_slot);
  
  send(complete_list,ack,getDataPacket());
 }
 
Packet<uint8> ClientEngine::getDataPacket()
 {
  Packet<uint8> packet=pset.try_get();
  
  if( !packet ) stat.count(ClientEvent_NoPacket); 
  
  return packet;
 }
 
Packet<uint8> ClientEngine::getDataPacket(PacketSet<uint8>::ExtTop &plist)
 {
  Packet<uint8> packet=pset.try_get(plist);
  
  if( !packet ) stat.count(ClientEvent_NoPacket); 
    
  return packet;
 }
 
void ClientEngine::send(PacketList &complete_list,Packet<uint8> data_packet)
 {
  data_packet.pushCompleteFunction(function_send());
 
  complete_list.put(data_packet);
 }
 
void ClientEngine::abort(PacketHeader *packet_)
 {
  Packet<uint8,TransExt> packet=packet_;
  
  PacketSet<uint8>::Cancel cancel(pset);

  {
   Mutex::Lock lock(mutex);

   switch( packet.getExt()->state )
     {
      case TransExt::Pending :
       {
        pending_list.del(packet);
        
        stat.count(ClientEvent_Abort);
        
        packet.getExt()->setError(Trans_Aborted);
       }
      break;
      
      case TransExt::Active :
       {
        Slot *slot=slots.getPtr()+packet.getExt()->slot;
        
        slot->packet=Nothing;
        
        cancel.build(slot->plist);
        
        deactivate(slot);
       
        stat.count(ClientEvent_Abort);
        
        packet.getExt()->setError(Trans_Aborted);
       }
      break;
      
      case TransExt::Completed :
       {
        // do nothing
       }
      break;
     }
  } 
  
  packet.complete();  
  
  cancel.cancel();
 }
 
void ClientEngine::completeError(PacketList &complete_list,Packet<uint8,TransExt> packet,TransResult result)
 {
  packet.getExt()->setError(result);
  
  if( packet.clearCancelFunction()!=Packet_Cancelled ) 
    {
     complete_list.put(packet);
    }
 }
   
void ClientEngine::completeInfo(PacketList &complete_list,Packet<uint8,TransExt> packet,Packet<uint8> server_packet,PtrLen<const uint8> server_info)
 {
  if( packet.clearCancelFunction()!=Packet_Cancelled ) 
    {
     stat.count(ClientEvent_TransDone);
     
     TransExt *ext=packet.getExt();

     ext->setInfo(server_info);
     
     if( ext->move_flag ) server_packet.detach(packet);
  
     complete_list.put(packet);
    }
  else
    {
     stat.count(ClientEvent_Abort);
    
     packet.getExt()->setError(Trans_Aborted);
    }  
 }
 
void ClientEngine::inbound_locked(PacketList &complete_list,Packet<uint8> server_packet,PtrLen<const uint8> server_data)
 {
  Mutex::Lock lock(mutex);
  
  RangeGetDev dev(server_data);
  
  PacketPrefix4 prefix;
  
  dev(prefix);
  
  if( !dev ) return bad_inbound();
  
  switch( prefix.type )
    {
     case PacketType_RET :
      {
       Packet_RET4 suffix;
       
       dev(suffix);
       
       if( suffix.len>max_inbound_info_len ) return bad_inbound();
       
       PtrLen<const uint8> server_info=dev.getFinalRange(suffix.len);
      
       if( !dev.finish() ) return bad_inbound();
       
       stat.count(ClientEvent_RET);
      
       inbound_RET(complete_list,prefix.trans_id,prefix.client_slot,prefix.server_slot,server_packet,server_info);
      }
     break;
     
     case PacketType_CANCEL : 
      {
       if( !dev.finish() ) return bad_inbound();
       
       stat.count(ClientEvent_CANCEL);
      
       inbound_CANCEL(complete_list,prefix.trans_id,prefix.client_slot,prefix.server_slot); 
      }
     break;
     
     case PacketType_NOINFO : 
      {
       if( !dev.finish() ) return bad_inbound();
       
       stat.count(ClientEvent_NOINFO);
       
       inbound_NOINFO(complete_list,prefix.trans_id,prefix.client_slot,prefix.server_slot); 
      }
     break;
     
     case PacketType_RERET  : 
      {
       if( !dev.finish() ) return bad_inbound();
       
       stat.count(ClientEvent_RERET);
       
       inbound_RERET(complete_list,prefix.trans_id,prefix.client_slot,prefix.server_slot); 
      }
     break;
     
     default: return bad_inbound();
    }
  
  pump(complete_list);
 }
   
void ClientEngine::tick_locked(PacketList &complete_list)
 {
  Mutex::Lock lock(mutex);
  
  auto cur=active_list.start();
  
  while( +cur )
    {
     if( cur->tick(complete_list) ) 
       {
        ++cur;
       }
     else
       {
        Slot *slot=active_list.del_and_move(cur);
        
        deactivate_nodel(slot);
       }
    }
  
  pump(complete_list);
 }
   
void ClientEngine::start_locked(PacketList &complete_list,Packet<uint8,TransExt> packet)
 {
  Mutex::Lock lock(mutex);
  
  if( packet.setCancelFunction(function_abort())==Packet_NoCancelFunction ) 
    {
     stat.count(ClientEvent_Trans);

     pending_list.put(packet);

     packet.getExt()->setPending();

     pump(complete_list);
    }
  else
    {
     packet.getExt()->setError(Trans_Aborted);

     complete_list.put(packet);
    }
 }
   
void ClientEngine::abortAll_locked(PacketList &complete_list)
 {
  Mutex::Lock lock(mutex);
  
  while( Slot *slot=active_list.top )
    {
     slot->abort(complete_list);
     
     deactivate(slot);
    }

  for(;;)  
    {
     Packet<uint8,TransExt> packet=pending_list.get();
     
     if( !packet ) break;
     
     stat.count(ClientEvent_Abort);
 
     completeError(complete_list,packet,Trans_Aborted);
    }
 }
 
void ClientEngine::inbound(Packet<uint8> server_packet,PtrLen<const uint8> server_data)
 {
  PacketList complete_list;
  
  inbound_locked(complete_list,server_packet,server_data);
  
  complete_list.complete();
  
  server_packet.complete();
 }
 
void ClientEngine::tick()
 {
  PacketList complete_list;
  
  tick_locked(complete_list);
  
  complete_list.complete();
 }
 
void ClientEngine::do_send(PacketHeader *packet_)
 {
  Packet<uint8> data_packet=packet_;
  
  ep->outbound(data_packet);
 }
 
ClientEngine::ClientEngine(ulen max_slots)
 : mutex("PTP::ClientEngine"),
   slots(max_slots),
   pset("PTP::ClientEngine.pset",2*max_slots)
 {
  ep=0;
  
  trans_number=0;
  seed1=0;
  seed2=0;
  
  max_outbound_info_len=MaxInfoLen;
  max_inbound_info_len=MaxInfoLen;
  
  for(SlotId client_slot=0; client_slot<max_slots ;client_slot++) 
    {
     Slot *slot=slots.getPtr()+client_slot;
    
     slot->init(this,client_slot);
     
     avail_list.ins_last(slot);
    }
 }
   
ClientEngine::~ClientEngine()
 {
  if( ep ) ep->detach();
  
  abortAll();
 }
   
void ClientEngine::attach_to(PacketEndpointDevice *ep_)
 {
  outbound_format=ep_->getOutboundFormat();
  
  const char *name="CCore::Net::ClientEngine::attach_to(...)";
  
  max_outbound_info_len=LenSub(name,Min(outbound_format.max_data,MaxPacketLen),DeltaInfoLen);
  
  max_inbound_info_len=LenSub(name,Min(ep_->getMaxInboundLen(),MaxPacketLen),DeltaInfoLen);
  
  ep_->attach(this);
  
  ep=ep_;
 }
 
void ClientEngine::start(Packet<uint8,TransExt> packet)
 {
  PacketList complete_list;
  
  start_locked(complete_list,packet);

  complete_list.complete();
 }
   
void ClientEngine::abortAll()
 {
  PacketList complete_list;
  
  abortAll_locked(complete_list);
  
  complete_list.complete();
 }
 
void ClientEngine::getStat(ClientStatInfo &ret)
 {
  Mutex::Lock lock(mutex);

  ret=stat;
 }
 
ulen ClientEngine::getMaxOutboundInfoLen()
 {
  Mutex::Lock lock(mutex);
  
  return max_outbound_info_len;
 }
 
ulen ClientEngine::getMaxInboundInfoLen()
 {
  Mutex::Lock lock(mutex);
  
  return max_inbound_info_len;
 }
 
void ClientEngine::setSeed(uint64 seed1_,uint64 seed2_)
 {
  Mutex::Lock lock(mutex);
  
  seed1=seed1_;
  seed2=seed2_;
 }
   
void ClientEngine::setLengths(ulen max_outbound_info_len_,ulen max_inbound_info_len_)
 {
  Mutex::Lock lock(mutex);
  
  Replace_min(max_outbound_info_len,max_outbound_info_len_);
  Replace_min(max_inbound_info_len,max_inbound_info_len_);
 }
 
/* class ClientDevice */ 

void ClientDevice::complete_Session(PacketHeader *packet_)
 {
  Packet<uint8,Atomic *,PTPSupport::SessionExt> packet=packet_;
  
  PTPSupport::SessionExt *ext=packet.getExt();
  
  if( ext->isOk() )
    {
     Atomic *success=*packet.getDeepExt<1>();
     
     (*success)++;
    }
  
  packet.popExt().popExt().complete();
 }
 
void ClientDevice::complete_Seed(PacketHeader *packet_)
 {
  Packet<uint8,Atomic *,PTPSupport::SeedExt> packet=packet_;
  
  PTPSupport::SeedExt *ext=packet.getExt();
  
  if( ext->isOk() )
    {
     engine.setSeed(ext->seed1,ext->seed2);
     
     Atomic *success=*packet.getDeepExt<1>();
     
     (*success)++;
    }
  
  packet.popExt().popExt().complete();
 }
   
void ClientDevice::complete_Len(PacketHeader *packet_)
 {
  Packet<uint8,Atomic *,PTPSupport::LenExt> packet=packet_;
  
  PTPSupport::LenExt *ext=packet.getExt();
  
  if( ext->isOk() )
    {
     engine.setLengths(ext->max_outbound_info_len,ext->max_inbound_info_len);
     
     Atomic *success=*packet.getDeepExt<1>();
     
     (*success)++;
    }
  
  packet.popExt().popExt().complete();
 }
 
void ClientDevice::BadServerInfo1(PtrLen<const uint8> /* server_info */)
 {
  // do nothing
 }

void ClientDevice::BadServerInfo2(PtrLen<const uint8> /* server_info */)
 {
  // do nothing
 }

void ClientDevice::BadServerInfo3(PtrLen<const uint8> /* server_info */)
 {
  // do nothing
 }

ClientDevice::ClientDevice(StrLen ep_dev_name,ulen max_slots)
 : hook(ep_dev_name),
   engine(max_slots)
 {
  PacketEndpointDevice *ep=hook;
  
  engine.attach_to(ep);
 }
   
ClientDevice::~ClientDevice()
 {
 }
   
void ClientDevice::start(Packet<uint8,TransExt> packet)
 {
  engine.start(packet);
 }
 
void ClientDevice::getStat(ClientStatInfo &ret)
 {
  engine.getStat(ret);
 }
 
ulen ClientDevice::getMaxOutboundInfoLen()
 {
  return engine.getMaxOutboundInfoLen();
 }
 
ulen ClientDevice::getMaxInboundInfoLen()
 {
  return engine.getMaxInboundInfoLen();
 }
 
 // support service
   
void ClientDevice::support(Packet<uint8,PTPSupport::LenExt> packet)
 {
  PTPSupport::LenInput input((LenType)getMaxOutboundInfoLen(),(LenType)getMaxInboundInfoLen());

  start(packet,input);
 }
 
void ClientDevice::support(Packet<uint8,PTPSupport::SeedExt> packet)
 {
  PTPSupport::SeedInput input;
  
  start(packet,input);
 }
 
void ClientDevice::support(Packet<uint8,PTPSupport::SessionExt> packet)
 {
  PTPSupport::SessionInput input;
 
  start(packet,input);
 }
 
void ClientDevice::support(Packet<uint8,PTPSupport::EchoExt> packet,uint32 delay_msec)
 {
  auto sub=packet.getDataLen(GetFormat<PTPSupport::EchoExt>()); // ignore max_outbound_info_len limitation
  
  if( sub.notFitFormat() )
    {
     packet.getExt()->fail(Trans_BadDataLen);
        
     packet.complete();
    }  
  else
    {
     PTPSupport::EchoInput input(delay_msec,(uint8)sub.len);
  
     start_format(packet,input);
    }
 }
 
void ClientDevice::support(Packet<uint8,PTPSupport::ErrorDescExt> packet,ServiceIdType service_id,FunctionIdType function_id,ErrorIdType error_id)
 {
  PTPSupport::ErrorDescInput input(service_id,function_id,error_id);
 
  start(packet,input);
 }
 
void ClientDevice::support(Packet<uint8,PTPSupport::ExistExt> packet,ServiceIdType service_id,FunctionIdType function_id)
 {
  PTPSupport::ExistInput input(service_id,function_id);
 
  start(packet,input);
 }
 
 // initial interaction
   
bool ClientDevice::support(PacketSet<uint8> &pset,MSec timeout)
 {
  Atomic success;
 
  TimeScope time_scope(timeout);
  
  // session
  {
   Packet<uint8> packet=pset.get(time_scope);
   
   if( !packet ) return false;
   
   Packet<uint8,Atomic *,PTPSupport::SessionExt> packet2=packet.pushExt<Atomic *>(&success).pushExt<PTPSupport::SessionExt>();
      
   packet2.pushCompleteFunction(FunctionOf(this,&ClientDevice::complete_Session));
   
   support(packet2.forgetExt<1>());
  }
  
  // seed
  {
   Packet<uint8> packet=pset.get(time_scope);
   
   if( !packet ) return false;
   
   Packet<uint8,Atomic *,PTPSupport::SeedExt> packet2=packet.pushExt<Atomic *>(&success).pushExt<PTPSupport::SeedExt>();
   
   packet2.pushCompleteFunction(FunctionOf(this,&ClientDevice::complete_Seed));

   support(packet2.forgetExt<1>());
  }
  
  // lengths
  {
   Packet<uint8> packet=pset.get(time_scope);
   
   if( !packet ) return false;
   
   Packet<uint8,Atomic *,PTPSupport::LenExt> packet2=packet.pushExt<Atomic *>(&success).pushExt<PTPSupport::LenExt>();
   
   packet2.pushCompleteFunction(FunctionOf(this,&ClientDevice::complete_Len));
   
   support(packet2.forgetExt<1>());
  }
  
  pset.wait(time_scope);
  
  return success==3;
 }

void ClientDevice::support_guarded(MSec timeout)
 {
  PacketSet<uint8> pset("PTP::ClientDevice");
  
  if( !support(pset,timeout) )   
    {
     Printf(Exception,"CCore::Net::PTP::ClientDevice::support(...) : failure");
    }
 }
 
} // namespace PTP
} // namespace Net
} // namespace CCore
 

