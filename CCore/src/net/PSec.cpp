/* PSec.cpp */
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
 
#include <CCore/inc/net/PSec.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Net {
namespace PSec {

/* enum ProcessorEvent */

const char * GetTextDesc(ProcessorEvent ev)
 {
  static const char *const Table[]=
   {
    "PSec Rx",              // ProcessorEvent_Rx 
    "PSec Rx Bad Len",      // ProcessorEvent_RxBadLen
    "PSec Rx Bad Pad Len",  // ProcessorEvent_RxBadPadLen
    "PSec Rx Replay",       // ProcessorEvent_RxReplay
    "PSec Rx Bad KeyIndex", // ProcessorEvent_RxBadKeyIndex
    "PSec Bad Hash",        // ProcessorEvent_RxBadHash
    "PSec Rx Done",         // ProcessorEvent_RxDone
    
    "PSec Tx",              // ProcessorEvent_Tx
    "PSec Tx Bad Format",   // ProcessorEvent_TxBadFormat
    "PSec Tx No Key",       // ProcessorEvent_TxNoKey
    "PSec Tx Done",         // ProcessorEvent_TxDone
    
    "PSec Key No Packet",   // ProcessorEvent_KeyNoPacket
    "PSec Key Bad Format",  // ProcessorEvent_KeyBadFormat
    
    "PSec Key Alert",       // ProcessorEvent_KeyAlert
    "PSec Key Ready",       // ProcessorEvent_KeyReady
    "PSec Key Ack",         // ProcessorEvent_KeyAck
    "PSec Key Stop",        // ProcessorEvent_KeyStop
    
    "PSec Ping",            // ProcessorEvent_Ping
    "PSec Pong",            // ProcessorEvent_Pong
    "PSec Close"            // ProcessorEvent_Close
   };
  
  return Table[ev];
 }

/* struct EventRegType */

EventIdType EventRegType::Register(EventMetaInfo &info)
 {
  return info.addEnum_uint8("PSecEventType")
    
             .addValueName(ProcessorEvent_Rx,"Rx",EventMarker_Up)
             .addValueName(ProcessorEvent_RxBadLen,"Rx BadLen",EventMarker_DownBlock)
             .addValueName(ProcessorEvent_RxBadPadLen,"Rx BadPadLen",EventMarker_DownBlock)
             .addValueName(ProcessorEvent_RxReplay,"Rx Replay",EventMarker_DownBlock)
             .addValueName(ProcessorEvent_RxBadKeyIndex,"Rx BadKeyIndex",EventMarker_DownBlock)
             .addValueName(ProcessorEvent_RxBadHash,"Rx BadHash",EventMarker_DownBlock)
             .addValueName(ProcessorEvent_RxDone,"Rx Done",EventMarker_Down)
             
             .addValueName(ProcessorEvent_Tx,"Tx",EventMarker_Up)
             .addValueName(ProcessorEvent_TxBadFormat,"Tx BadFormat",EventMarker_DownBlock)
             .addValueName(ProcessorEvent_TxNoKey,"Tx NoKey",EventMarker_DownBlock)
             .addValueName(ProcessorEvent_TxDone,"Tx Done",EventMarker_Down)
             
             .addValueName(ProcessorEvent_KeyNoPacket,"Key NoPacket",EventMarker_Error)
             .addValueName(ProcessorEvent_KeyBadFormat,"Key BadFormat",EventMarker_Error)
             
             .addValueName(ProcessorEvent_KeyAlert,"Key Alert")
             .addValueName(ProcessorEvent_KeyReady,"Key Ready")
             .addValueName(ProcessorEvent_KeyAck,"Key Ack")
             .addValueName(ProcessorEvent_KeyStop,"Key Stop")
             
             .addValueName(ProcessorEvent_Ping,"Ping")
             .addValueName(ProcessorEvent_Pong,"Pong")
             .addValueName(ProcessorEvent_Close,"Close")
             
             .getId();
 }

/* struct ProtoEvent */

void ProtoEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id=info.addStruct("PSecEvent")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint8(EventTypeId<EventRegType>::GetId(),"event",Offset_ev)
              .getId();
  
  desc.setStructId(info,id);
 }
  
/* class PacketProcessor */

void PacketProcessor::consume(ControlResponse &resp,PacketType type,PtrLen<const uint8> data)
 {
  KeyIndex key_index=0;
  const uint8 *gy=0;
  
  switch( type )
    {
     case Packet_Alert : 
     case Packet_Ready :
      {
       if( data.len<KeyIndexLen+core.getGLen() ) return;
       
       BufGetDev dev(data.ptr);
       
       dev.use<BeOrder>(key_index);
       
       gy=dev.getRest();
      }
     break; 
      
     case Packet_Ack :
     case Packet_Stop :
      {
       if( data.len<KeyIndexLen ) return;
       
       BufGetDev dev(data.ptr);
       
       dev.use<BeOrder>(key_index);
      }
     break; 
    }
  
  switch( type )
    {
     case Packet_Alert : return core.alert(resp,key_index,gy);
     
     case Packet_Ready : return core.ready(resp,key_index,gy);
      
     case Packet_Ack : return core.ack(resp,key_index);
      
     case Packet_Stop : return core.stop(key_index);
     
     case Packet_Ping : return resp.set(Packet_Pong);
    }
 }

PacketProcessor::PacketProcessor(const MasterKey &master_key,MSec keep_alive_timeout)
 : core(master_key),
   keep_alive(keep_alive_timeout)
 {
  header_len=RoundUp(2*HeaderLen,core.getBLen());
  
  min_out_len=outLen(64);
  min_inp_len=outLen(0);
 }

PacketProcessor::~PacketProcessor()
 {
 }

ulen PacketProcessor::getOutDelta(ulen len) const
 {
  ulen delta=0; 
  
  for(ulen cnt=Min<ulen>(DLen*core.getBLen(),len+1); cnt ;cnt--,len--)
    {
     Replace_max(delta,outLen(len)-len);
    }
  
  return delta;
 }

ulen PacketProcessor::getMaxInpLen(ulen len) const
 {
  if( len<min_out_len )
    {
     Printf(Exception,"CCore::Net::PSec::PacketProcessor::getMaxInpLen(#;) : too short",len);
    }
  
  return inpLen(len);
 }

auto PacketProcessor::inbound(ControlResponse &resp,PtrLen<uint8> data) -> InboundResult
 {
  stat.count(ProcessorEvent_Rx);
  
  // 1
  
  ulen blen=core.getBLen();

  if( data.len%blen || data.len<min_inp_len ) 
    {
     stat.count(ProcessorEvent_RxBadLen);
    
     return Nothing;
    }
  
  // 2
  
  uint8 *cur=data.ptr;
  
  Header header;
  
  {
   core.startDecrypt();
   core.setDecryptKey0();
   
   for(ulen cnt=header_len; cnt ;cnt-=blen,cur+=blen) core.applyDecrypt(cur);
   
   BufGetDev dev(cur-HeaderLen);
   
   dev(header);
  }
  
  // 3
  
  uint8 *base=data.ptr+header_len;
  ulen len;
  
  {
   len=data.len-header_len;
   
   if( header.pad_len>=len ) 
     {
      stat.count(ProcessorEvent_RxBadPadLen);
     
      return Nothing;
     }
   
   len-=header.pad_len;
   
   if( anti_replay.testReplay(header.sequence_number) ) 
     {
      stat.count(ProcessorEvent_RxReplay);
     
      return Nothing;
     }
   
   if( !core.selectDecryptKey(header.key_index) ) 
     {
      stat.count(ProcessorEvent_RxBadKeyIndex);
     
      return Nothing;
     }
   
   core.setDecryptKey();
   
   for(ulen cnt=data.len-header_len; cnt ;cnt-=blen,cur+=blen) core.applyDecrypt(cur);
  }
  
  // 4
  
  {
   uint8 *dst=base;
   const uint8 *src=dst+1;
   
   ulen del=DLen;
   
   for(ulen cnt=len-1; cnt ;cnt--)
     {
      if( del )
        {
         *(dst++)=*(src++);
        
         del--;
        }
      else
        {
         src++;
         
         del=DLen;
        }
     }
   
   len=Dist(base,dst);
  }
  
  // 5
  
  {
   ulen hlen=core.getHLen();
   
   if( len<hlen ) 
     {
      stat.count(ProcessorEvent_RxBadLen);
      
      return Nothing;
     }

   len-=hlen;
   
   core.add(Range_const(base-HeaderLen,len+HeaderLen));
   
   const uint8 *hash=core.finish();
   
   if( !Range_const(hash,hlen).equal(base+len) ) 
     {
      stat.count(ProcessorEvent_RxBadHash);
      
      return Nothing;
     }
   
   anti_replay.add(header.sequence_number);
  }
  
  stat.count(ProcessorEvent_RxDone);
  
  keep_alive.reset();
  
  if( header.type!=Packet_Data )
    {
     if( header.type==Packet_Close ) return InboundResult::Close;
    
     consume(resp,header.type,Range_const(base,len));
     
     return Nothing;
    }
  
  return Range_const(base,len);
 }

auto PacketProcessor::outbound(PtrLen<uint8> data,ulen delta,PacketType type) -> OutboundResult
 {
  stat.count(ProcessorEvent_Tx);
  
  // 1
  
  ulen blen=core.getBLen();
  
  ulen pad_len;
  ulen use_count;
  ulen ret;
  
  {
   ulen len=data.len+core.getHLen();
   ulen s=RoundUpCount(len,DLen)+len;
   ulen sup=RoundUp(s,blen);
   
   pad_len=sup-s;
   use_count=sup/blen;
   
   ret=data.len+delta-header_len-sup;
  }
  
  // 2
  
  uint8 header[HeaderLen];
  
  {
   auto select=core.selectEncryptKey(use_count);
   
   if( !select.ok ) 
     {
      stat.count(ProcessorEvent_TxNoKey);
     
      return Nothing;
     }
   
   Header obj;
   
   obj.sequence_number=out_sequence_number++;
   obj.key_index=select.key_index;
   obj.pad_len=PadLen(pad_len);
   obj.type=type;
   
   BufPutDev dev(header);
   
   dev(obj);
  }
  
  // 3
  
  PtrLen<const uint8> hash;
  
  {
   core.add(Range_const(header));
   core.add(Range_const(data));
   
   hash.ptr=core.finish();
   hash.len=core.getHLen();
  }
  
  // 4
  
  uint8 *out=data.ptr-delta;

  {
   core.startEncrypt();
   core.setEncryptKey0();
   
   const uint8 *ptr=header;
   
   for(ulen rest=header_len; rest ;rest-=blen,out+=blen)
     {
      if( rest<=HeaderLen )
        {
         for(ulen i=0; i<blen ;i++) out[i]=*(ptr++);
        }
      else if( rest>=HeaderLen+blen )
        {
         for(ulen i=0; i<blen ;i++) out[i]=core.random();
        }
      else
        {
         ulen split=rest-HeaderLen;
         ulen i=0;
         
         for(; i<split ;i++) out[i]=core.random();
         
         for(; i<blen ;i++) out[i]=*(ptr++);
        }
     
      core.applyEncrypt(out);
     }
  }
  
  // 5
  
  {
   core.setEncryptKey();
   
   ulen ins=0;
   
   for(; +data || +hash ;out+=blen)
     {
      for(ulen i=0; i<blen ;i++) 
        {
         if( ins )
           {
            if( +data )
              {
               out[i]=*data;
              
               ++data;
              }
            else if( +hash )
              {
               out[i]=*hash;
               
               ++hash;
              }
            else
              {
               out[i]=core.random();
              }
            
            ins--;
           }
         else
           {
            out[i]=core.random();
            
            ins=DLen;
           }
        }
     
      core.applyEncrypt(out);
     }
  }
  
  // 6
  
  {
   Range(out,ret).set_null();
  }
  
  stat.count(ProcessorEvent_TxDone);
  
  return ret;
 }

void PacketProcessor::tick(ControlResponse &resp) 
 { 
  core.tick(resp);
  
  if( resp.type==Packet_None ) keep_alive.tick(resp); 
 }

bool PacketProcessor::response(const ControlResponse &resp,Packet<uint8> packet,PacketFormat format)
 {
  if( !packet ) 
    {
     stat.count(ProcessorEvent_KeyNoPacket);
    
     return false;
    }

  if( IsLifetimePacket(resp.type) )
    {
     ulen max_len=packet.getMaxDataLen(format).len;
    
     ulen len=core.selectLen(0,max_len);
    
     auto data=packet.setDataLen(format,len);
     
     core.random(data);
    }
  else
    {
     ulen min_len=KeyIndexLen+resp.gx.len;
     
     ulen max_len=packet.getMaxDataLen(format).len;
     
     if( min_len>max_len )
       {
        stat.count(ProcessorEvent_KeyBadFormat);
       
        packet.complete();
        
        return false;
       }
     
     ulen len=core.selectLen(min_len,max_len);
     
     auto data=packet.setDataLen(format,len);
        
     BufPutDev dev(data.ptr);
     
     dev.use<BeOrder>(resp.key_index);
     
     dev.put(resp.gx);
     
     core.random(dev.putRange(len-min_len));
    }
  
  switch( resp.type )
    {
     case Packet_Alert : stat.count(ProcessorEvent_KeyAlert); break; 
     case Packet_Ready : stat.count(ProcessorEvent_KeyReady); break;
     case Packet_Ack   : stat.count(ProcessorEvent_KeyAck); break;
     case Packet_Stop  : stat.count(ProcessorEvent_KeyStop); break;
     case Packet_Ping  : stat.count(ProcessorEvent_Ping); break;
     case Packet_Pong  : stat.count(ProcessorEvent_Pong); break;
     case Packet_Close : stat.count(ProcessorEvent_Close); break;
    }
  
  return true;
 }

/* class PacketProcessor::IOLen */

PacketProcessor::IOLen::IOLen(AlgoLen algo_len) 
 : blen(algo_len.blen),
   hlen(algo_len.hlen) 
 {
  header_len=RoundUp(2*HeaderLen,blen);
  
  min_out_len=outLen(64);
 }

ulen PacketProcessor::IOLen::getOutDelta(ulen len) const
 {
  ulen delta=0; 
  
  for(ulen cnt=Min<ulen>(DLen*blen,len+1); cnt ;cnt--,len--)
    {
     Replace_max(delta,outLen(len)-len);
    }
  
  return delta;
 }

ulen PacketProcessor::IOLen::getMaxInpLen(ulen len) const
 {
  if( len<min_out_len )
    {
     Printf(Exception,"CCore::Net::PSec::PacketProcessor::IOLen::getMaxInpLen(#;) : too short",len);
    }
  
  return inpLen(len);
 }

/* class EndpointDevice::Engine */

void EndpointDevice::Engine::connection_lost()
 {
  Hook hook(host);
 
  if( +hook ) 
    {
     ConnectionProc *proc=dynamic_cast<ConnectionProc *>(hook.getPtr());
    
     if( proc ) proc->connection_lost();
    }
 }

void EndpointDevice::Engine::connection_close()
 {
  Hook hook(host);
 
  if( +hook ) 
    {
     ConnectionProc *proc=dynamic_cast<ConnectionProc *>(hook.getPtr());
    
     if( proc ) proc->connection_close();
    }
 }

void EndpointDevice::Engine::response(const ControlResponse &resp)
 {
  switch( resp.type )
    {
     case Packet_Alert :
     case Packet_Ready :
     case Packet_Ack :
     case Packet_Stop :
     case Packet_Ping :
     case Packet_Pong :
     case Packet_Close :
      {
       Packet<uint8> packet=pset.try_get();
       
       if( ProcLocked(mutex,proc)->response(resp,packet,outbound_format) )
         {
          outbound(packet,resp.type);
         }
      }
     break;
    }
  
  if( resp.type==Packet_Close ) connection_lost();
 }

void EndpointDevice::Engine::inbound(Packet<uint8> packet,PtrLen<const uint8> data)
 {
  ControlResponse resp;
  
  auto result=ProcLocked(mutex,proc)->inbound(resp,Range(const_cast<uint8 *>(data.ptr),data.len));
  
  if( result.consumed )
    {
     if( result.close )
       connection_close();
     else
       response(resp);
     
     packet.complete();
    }
  else
    {
     Hook hook(host);
    
     if( +hook ) 
       {
        hook->inbound(packet,result.data);
       }
     else
       {
        packet.complete();
       }
    }
 }
 
void EndpointDevice::Engine::tick()
 {
  {
   Hook hook(host);
   
   if( +hook ) hook->tick();
  }
  
  ControlResponse resp;
  
  ProcLocked(mutex,proc)->tick(resp);
  
  response(resp);
 }

EndpointDevice::Engine::Engine(PacketEndpointDevice *dev_,const MasterKey &master_key,MSec keep_alive_timeout)
 : dev(dev_),
   host("PSec::EndpointDevice","PSec::EndpointDevice.host"),
   pset("PSec::EndpointDevice.pset"),
   mutex("PSec::EndpointDevice.mutex"),
   proc(master_key,keep_alive_timeout)
 {
  PacketFormat fmt=dev->getOutboundFormat();

  ulen len=proc.getMaxInpLen(fmt.max_data);
  
  outbound_delta=proc.getOutDelta(len);
  
  outbound_format.prefix=fmt.prefix+outbound_delta;
  outbound_format.max_data=len;
  outbound_format.suffix=fmt.suffix;
  
  max_inbound_len=proc.getMaxInpLen(dev->getMaxInboundLen());
  
  dev->attach(this);
 }

EndpointDevice::Engine::~Engine()
 {
  dev->detach();
 }

void EndpointDevice::Engine::close()
 {
  ControlResponse resp;
  
  resp.set(Packet_Close);
  
  response(resp);
 }

void EndpointDevice::Engine::getStat(ProcessorStatInfo &ret) const
 {
  Mutex::Lock lock(mutex);
  
  proc.getStat(ret);
 }

PacketFormat EndpointDevice::Engine::getOutboundFormat() const
 {
  return outbound_format;
 }
 
void EndpointDevice::Engine::outbound(Packet<uint8> packet,Packets type)
 {
  if( packet.checkRange(outbound_format) )
    {
     auto result=ProcLocked(mutex,proc)->outbound(packet.getRange(outbound_format),outbound_delta,type);
     
     if( result.ok )
       {
        packet.setDataLen(packet.getDataLen()-result.delta);       
       
        dev->outbound(packet);
       }
     else
       {
        packet.complete();
       }
    }
  else
    {
     ProcLocked(mutex,proc)->count(ProcessorEvent_TxBadFormat);
    
     packet.complete();
    }
 }
 
ulen EndpointDevice::Engine::getMaxInboundLen() const
 {
  return max_inbound_len;
 }
 
void EndpointDevice::Engine::attach(InboundProc *proc)
 {
  host.attach(proc);
 }
 
void EndpointDevice::Engine::detach()
 {
  host.detach();
 }

/* class EndpointDevice */

EndpointDevice::EndpointDevice(StrLen ep_dev_name,const MasterKey &master_key,MSec keep_alive_timeout)
 : hook(ep_dev_name),
   engine(hook,master_key,keep_alive_timeout)
 {
 }

EndpointDevice::~EndpointDevice()
 {
 }

PacketFormat EndpointDevice::getOutboundFormat()
 {
  return engine.getOutboundFormat();
 }
 
void EndpointDevice::outbound(Packet<uint8> packet)
 {
  engine.outbound(packet);
 }
 
ulen EndpointDevice::getMaxInboundLen()
 {
  return engine.getMaxInboundLen();
 }
 
void EndpointDevice::attach(InboundProc *proc)
 {
  engine.attach(proc);
 }
 
void EndpointDevice::detach()
 {
  engine.detach();
 }

/* class MultipointDevice::Proc */

void MultipointDevice::Proc::connection_lost(XPoint point,Engine *engine)
 {
  {
   Mutex::Lock lock(engine->mutex);
   
   opened=false;
  }
  
  engine->connection_lost(point);
 }

void MultipointDevice::Proc::connection_close(XPoint point,Engine *engine)
 {
  {
   Mutex::Lock lock(engine->mutex);
   
   opened=false;
  }
  
  Hook hook(engine->host);
 
  if( +hook ) 
    {
     ConnectionProc *proc=dynamic_cast<ConnectionProc *>(hook.getPtr());
    
     if( proc ) proc->connection_close(point);
    }
 }

void MultipointDevice::Proc::response(XPoint point,const ControlResponse &resp,Engine *engine)
 {
  switch( resp.type )
    {
     case Packet_Alert :
     case Packet_Ready :
     case Packet_Ack :
     case Packet_Stop :
     case Packet_Ping :
     case Packet_Pong :
     case Packet_Close :
      {
       Packet<uint8> packet=engine->pset.try_get();
       
       if( ProcLocked(mutex,*proc)->response(resp,packet,engine->outbound_format) )
         {
          outbound(point,packet,resp.type,engine);
         }
      }
     break;
    }
  
  if( resp.type==Packet_Close ) connection_lost(point,engine);
 }

bool MultipointDevice::Proc::response(XPoint point,const ControlResponse &resp,Engine *engine,PacketList &list)
 {
  switch( resp.type )
    {
     case Packet_Alert :
     case Packet_Ready :
     case Packet_Ack :
     case Packet_Stop :
     case Packet_Ping :
     case Packet_Pong :
     case Packet_Close :
      {
       Packet<uint8> packet=engine->pset.try_get();
       
       if( ProcLocked(mutex,*proc)->response(resp,packet,engine->outbound_format) )
         {
          outbound(point,packet,resp.type,engine,list);
         }
      }
     break;
    }

  return resp.type==Packet_Close ;
 }

MultipointDevice::Proc::Proc(const MasterKey &master_key,MSec keep_alive_timeout,ClientProfilePtr &client_profile_)
 : mutex("PSec::MultipointDevice::Proc"),
   proc(new PacketProcessor(master_key,keep_alive_timeout))
 {
  MoveBySwap(client_profile,client_profile_);
 }

MultipointDevice::Proc::~Proc()
 {
 }

void MultipointDevice::Proc::getStat(ProcessorStatInfo &ret) const
 { 
  Mutex::Lock lock(mutex);
  
  proc->getStat(ret); 
 }

void MultipointDevice::Proc::replace(const MasterKey &master_key,MSec keep_alive_timeout,ClientProfilePtr &client_profile_)
 {
  OwnPtr<PacketProcessor> proc_(new PacketProcessor(master_key,keep_alive_timeout));
  
  if( use_count )
    {
     MoveBySwap(replace_proc,proc_);
     MoveBySwap(replace_client_profile,client_profile_);
     
     opened=false;
    }
  else
    {
     NullBySwap(replace_proc);
     NullBySwap(replace_client_profile);

     MoveBySwap(proc,proc_);
     MoveBySwap(client_profile,client_profile_);
     
     opened=true;
    }
 }

bool MultipointDevice::Proc::incUse()
 {
  if( opened )
    {
     use_count++;
     
     return true;
    }
  
  return false;
 }

bool MultipointDevice::Proc::decUse()
 {
  use_count--;
  
  if( !use_count )
    {
     if( +replace_proc )
       {
        MoveBySwap(proc,replace_proc);
        MoveBySwap(client_profile,replace_client_profile);
        
        opened=true;
       }
     
     return !opened;
    }
  else
    {
     return false;
    }
 }

bool MultipointDevice::Proc::close(XPoint point,Engine *engine,PacketList &list)
 {
  ControlResponse resp;
  
  resp.set(Packet_Close);
  
  response(point,resp,engine,list);
  
  opened=false;
  
  engine->connection_lost(point); // TODO
   
  return !use_count;
 }

bool MultipointDevice::Proc::tick(XPoint point,Engine *engine,PacketList &list)
 {
  ControlResponse resp;
  
  ProcLocked(mutex,*proc)->tick(resp);
  
  if( response(point,resp,engine,list) )
    {
     opened=false;
     
     engine->connection_lost(point); // TODO
    }
  
  return !opened && !use_count ;
 }

void MultipointDevice::Proc::inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data,Engine *engine)
 {
  ControlResponse resp;
  
  auto result=ProcLocked(mutex,*proc)->inbound(resp,Range(const_cast<uint8 *>(data.ptr),data.len));
  
  if( result.consumed )
    {
     if( result.close )
       connection_close(point,engine);
     else
       response(point,resp,engine);
     
     packet.complete();
    }
  else
    {
     Hook hook(engine->host);
    
     if( +hook ) 
       {
        hook->inbound(point,packet,result.data);
       }
     else
       {
        packet.complete();
       }
    }
 }

void MultipointDevice::Proc::outbound(XPoint point,Packet<uint8> packet,Packets type,Engine *engine)
 {
  if( packet.checkRange(engine->outbound_format) )
    {
     auto result=ProcLocked(mutex,*proc)->outbound(packet.getRange(engine->outbound_format),engine->outbound_delta,type);
     
     if( result.ok )
       {
        packet.setDataLen(packet.getDataLen()-result.delta);       
       
        engine->dev->outbound(point,packet);
       }
     else
       {
        packet.complete();
       }
    }
  else
    {
     ProcLocked(mutex,*proc)->count(ProcessorEvent_TxBadFormat);
    
     packet.complete();
    }
 }

void MultipointDevice::Proc::outbound(XPoint point,Packet<uint8> packet,Packets type,Engine *engine,PacketList &list)
 {
  if( packet.checkRange(engine->outbound_format) )
    {
     auto result=ProcLocked(mutex,*proc)->outbound(packet.getRange(engine->outbound_format),engine->outbound_delta,type);
     
     if( result.ok )
       {
        packet.setDataLen(packet.getDataLen()-result.delta);       
       
        list.put(packet.pushExt<XPoint>(point));  
       }
     else
       {
        packet.complete();
       }
    }
  else
    {
     ProcLocked(mutex,*proc)->count(ProcessorEvent_TxBadFormat);
    
     packet.complete();
    }
 }

/* class MultipointDevice::Engine */

ulen MultipointDevice::Engine::GetMaxInpLen(PtrLen<const AlgoLen> algo_lens,ulen len)
 {
  ulen ret=len;
  
  for(AlgoLen algo_len : algo_lens )
    {
     PacketProcessor::IOLen iolen(algo_len);
     
     Replace_min(ret,iolen.getMaxInpLen(len));
    }
  
  return ret;
 }

ulen MultipointDevice::Engine::GetOutDelta(PtrLen<const AlgoLen> algo_lens,ulen len)
 {
  ulen ret=0;
  
  for(AlgoLen algo_len : algo_lens )
    {
     PacketProcessor::IOLen iolen(algo_len);
     
     Replace_max(ret,iolen.getOutDelta(len));
    }
  
  return ret;
 }

void MultipointDevice::Engine::connection_lost(XPoint point)
 {
  Hook hook(host);
 
  if( +hook ) 
    {
     ConnectionProc *proc=dynamic_cast<ConnectionProc *>(hook.getPtr());
    
     if( proc ) proc->connection_lost(point);
    }
 }

void MultipointDevice::Engine::send(PacketList &list)
 {
  while( PacketHeader *packet_=list.get() )
    {
     Packet<uint8,XPoint> packet=packet_;
     
     XPoint point=*packet.getExt();
     
     dev->outbound(point,packet.popExt());
    }
 }

void MultipointDevice::Engine::inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data)
 {
  Proc *obj;
  
  {
   Mutex::Lock lock(mutex);
  
   obj=map.find(point);
   
   if( obj && !obj->incUse() ) obj=0;
  }
  
  if( obj )
    {
     obj->inbound(point,packet,data,this);
    
     {
      Mutex::Lock lock(mutex);
    
      if( obj->decUse() ) map.del(point);
     }
    }
  else
    {
     packet.complete();
    }
 }
 
void MultipointDevice::Engine::tick()
 {
  {
   Hook hook(host);
   
   if( +hook ) hook->tick();
  }
  
  PacketList list;
  
  {
   Mutex::Lock lock(mutex);

   map.delIf( [this,&list] (XPoint point,Proc &obj) { return obj.tick(point,this,list); } );
  } 

  send(list);
 }

MultipointDevice::Engine::Engine(PacketMultipointDevice *dev_,PtrLen<const AlgoLen> algo_lens,ulen max_clients_,MSec keep_alive_timeout_)
 : dev(dev_),
   max_clients(max_clients_),
   keep_alive_timeout(keep_alive_timeout_),
   host("PSec::MultipointDevice","PSec::MultipointDevice.host"),
   pset("PSec::MultipointDevice.pset"),
   mutex("PSec::MultipointDevice.mutex")
 {
  PacketFormat fmt=dev->getOutboundFormat();

  ulen len=GetMaxInpLen(algo_lens,fmt.max_data);
  
  outbound_delta=GetOutDelta(algo_lens,len);
  
  outbound_format.prefix=fmt.prefix+outbound_delta;
  outbound_format.max_data=len;
  outbound_format.suffix=fmt.suffix;
  
  max_inbound_len=GetMaxInpLen(algo_lens,dev->getMaxInboundLen());
  
  dev->attach(this);
 }

MultipointDevice::Engine::~Engine()
 {
  dev->detach();
 }

void MultipointDevice::Engine::getStat(ProcessorStatInfo &ret) const
 {
  ret.reset();
  
  Mutex::Lock lock(mutex);
  
  map.applyIncr( [&ret] (XPoint,const Proc &obj) { ProcessorStatInfo temp; obj.getStat(temp); ret+=temp; } );
 }

bool MultipointDevice::Engine::getStat(XPoint point,ProcessorStatInfo &ret) const
 {
  Mutex::Lock lock(mutex);
  
  if( const Proc *obj=map.find(point) )
    {
     obj->getStat(ret);
     
     return true;
    }
  else
    {
     ret.reset();
     
     return false;
    }
 }

StrLen MultipointDevice::Engine::toText(XPoint point,PtrLen<char> buf) const
 {
  return dev->toText(point,buf);
 }
 
PacketFormat MultipointDevice::Engine::getOutboundFormat() const
 {
  return outbound_format;
 }
 
void MultipointDevice::Engine::outbound(XPoint point,Packet<uint8> packet)
 {
  Proc *obj;
  
  {
   Mutex::Lock lock(mutex);
  
   obj=map.find(point);
   
   if( obj && !obj->incUse() ) obj=0;
  }
  
  if( obj )
    {
     obj->outbound(point,packet,Packet_Data,this);
    
     {
      Mutex::Lock lock(mutex);
    
      if( obj->decUse() ) map.del(point);
     }
    }
  else
    {
     packet.complete();
    }
 }
 
ulen MultipointDevice::Engine::getMaxInboundLen() const
 {
  return max_inbound_len;
 }
 
void MultipointDevice::Engine::attach(InboundProc *proc)
 {
  host.attach(proc);
 }
 
void MultipointDevice::Engine::detach()
 {
  host.detach();
 }

auto MultipointDevice::Engine::open(XPoint point,MasterKeyPtr &skey,ClientProfilePtr &client_profile) -> OpenErrorCode
 {
  SilentReportException report;
  
  try
    {
     {
      Mutex::Lock lock(mutex);
      
      if( map.getCount()>=max_clients ) return OpenError_OpenLimit;
      
      auto result=map.find_or_add(point,*skey,keep_alive_timeout,client_profile);
      
      if( !result.new_flag )
        {
         result.obj->replace(*skey,keep_alive_timeout,client_profile);
        }
     }
     
     Hook hook(host);
    
     if( +hook ) 
       {
        ConnectionProc *proc=dynamic_cast<ConnectionProc *>(hook.getPtr());
       
        if( proc ) proc->connection_open(point);
       }
     
     return Open_Ok;
    }
  catch(...)
    {
     return OpenError_NoMemory;
    }
 }

bool MultipointDevice::Engine::close(XPoint point)
 {
  PacketList list;
  bool ret;
  
  {
   Mutex::Lock lock(mutex);
  
   if( Proc *obj=map.find(point) )
     { 
      if( obj->close(point,this,list) ) map.del(point);
      
      ret=true;
     }
   else
     {
      ret=false;
     }
  }
  
  send(list);
  
  return ret;
 }

ulen MultipointDevice::Engine::closeAll()
 {
  PacketList list;
  ulen ret;
  
  {
   Mutex::Lock lock(mutex);
   
   ret=map.getCount();

   map.delIf( [this,&list] (XPoint point,Proc &obj) { return obj.close(point,this,list); } );
  }
  
  send(list);
  
  return ret;
 }

AbstractClientProfile * MultipointDevice::Engine::getClientProfile(XPoint point) const
 {
  Mutex::Lock lock(mutex);
 
  const Proc *obj=map.find(point);
  
  if( obj ) return obj->getClientProfile();
  
  return 0;
 }

/* class MultipointDevice */

MultipointDevice::MultipointDevice(StrLen mp_dev_name,PtrLen<const AlgoLen> algo_lens,ulen max_clients,MSec keep_alive_timeout)
 : hook(mp_dev_name),
   engine(hook,algo_lens,max_clients,keep_alive_timeout)
 {
 }

MultipointDevice::~MultipointDevice()
 {
 }

StrLen MultipointDevice::toText(XPoint point,PtrLen<char> buf)
 {
  return engine.toText(point,buf);
 }
 
PacketFormat MultipointDevice::getOutboundFormat()
 {
  return engine.getOutboundFormat();
 }
 
void MultipointDevice::outbound(XPoint point,Packet<uint8> packet)
 {
  engine.outbound(point,packet);
 }
 
ulen MultipointDevice::getMaxInboundLen()
 {
  return engine.getMaxInboundLen();
 }
 
void MultipointDevice::attach(InboundProc *proc)
 {
  engine.attach(proc);
 }
 
void MultipointDevice::detach()
 {
  engine.detach();
 }

auto MultipointDevice::open(XPoint point,MasterKeyPtr &skey,ClientProfilePtr &client_profile) -> OpenErrorCode
 {
  return engine.open(point,skey,client_profile);
 }

bool MultipointDevice::close(XPoint point)
 {
  return engine.close(point);
 }

ulen MultipointDevice::closeAll()
 {
  return engine.closeAll();
 }

AbstractClientProfile * MultipointDevice::getClientProfile(XPoint point)
 {
  return engine.getClientProfile(point);
 }

} // namespace PSec 
} // namespace Net
} // namespace CCore
 


