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
    "PSec Key Stop"         // ProcessorEvent_KeyStop
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

void PacketProcessor::inbound(KeyResponse &resp,PacketType type,PtrLen<const uint8> data)
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
    }
 }

PacketProcessor::PacketProcessor(const MasterKey &master_key)
 : core(master_key)
 {
  header_len=RoundUp(2*HeaderLen,core.getBLen());
  
  min_out_len=outLen(64);
  min_inp_len=outLen(0);
 }

PacketProcessor::~PacketProcessor()
 {
 }

ulen PacketProcessor::getOutDelta(ulen len)
 {
  ulen delta=0; 
  
  for(ulen cnt=Min<ulen>(DLen*core.getBLen(),len+1); cnt ;cnt--,len--)
    {
     Replace_max(delta,outLen(len)-len);
    }
  
  return delta;
 }

ulen PacketProcessor::getMaxInpLen(ulen len)
 {
  if( len<min_out_len )
    {
     Printf(Exception,"CCore::Net::PSec::PacketProcessor::getMaxInpLen(#;) : too short",len);
    }
  
  return inpLen(len);
 }

auto PacketProcessor::inbound(KeyResponse &resp,PtrLen<uint8> data) -> InboundResult
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
  
  if( header.type!=Packet_Data )
    {
     inbound(resp,header.type,Range_const(base,len));
     
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

bool PacketProcessor::response(const KeyResponse &resp,Packet<uint8> packet,PacketFormat format)
 {
  if( !packet ) 
    {
     stat.count(ProcessorEvent_KeyNoPacket);
    
     return false;
    }
  
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
  
  uint8 *ptr=dev.getRest();
  
  resp.gx.copyTo(ptr);
  
  core.random(Range(ptr+resp.gx.len,len-min_len));
  
  switch( resp.type )
    {
     case Packet_Alert : stat.count(ProcessorEvent_KeyAlert); break; 
     case Packet_Ready : stat.count(ProcessorEvent_KeyReady); break;
     case Packet_Ack   : stat.count(ProcessorEvent_KeyAck); break;
     case Packet_Stop  : stat.count(ProcessorEvent_KeyStop); break;
    }
  
  return true;
 }

/* class EndpointDevice */

void EndpointDevice::response(const KeyResponse &resp)
 {
  switch( resp.type )
    {
     case Packet_Alert :
     case Packet_Ready :
     case Packet_Ack :
     case Packet_Stop :
      {
       Packet<uint8> packet=pset.try_get();
       
       if( ProcLocked(mutex,proc)->response(resp,packet,outbound_format) )
         {
          outbound(packet,resp.type);
         }
      }
     break;
    }
 }

void EndpointDevice::outbound(Packet<uint8> packet,Packets type)
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

void EndpointDevice::inbound(Packet<uint8> packet,PtrLen<const uint8> data)
 {
  KeyResponse resp;
  
  auto result=ProcLocked(mutex,proc)->inbound(resp,Range(const_cast<uint8 *>(data.ptr),data.len));
  
  if( result.consumed )
    {
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
 
void EndpointDevice::tick()
 {
  {
   Hook hook(host);
   
   if( +hook ) hook->tick();
  }
  
  KeyResponse resp;
  
  ProcLocked(mutex,proc)->tick(resp);
  
  response(resp);
 }

EndpointDevice::EndpointDevice(StrLen ep_dev_name,const MasterKey &master_key)
 : hook(ep_dev_name),
   dev(hook),
   host("PSec::EndpointDevice","PSec::EndpointDevice.host"),
   pset("PSec::EndpointDevice.pset"),
   mutex("PSec::EndpointDevice.mutex"),
   proc(master_key)
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

EndpointDevice::~EndpointDevice()
 {
  dev->detach();
 }

void EndpointDevice::getStat(StatInfo &ret)
 {
  Mutex::Lock lock(mutex);
  
  proc.getStat(ret);
 }

PacketFormat EndpointDevice::getOutboundFormat()
 {
  return outbound_format;
 }
 
void EndpointDevice::outbound(Packet<uint8> packet)
 {
  outbound(packet,Packet_Data);
 }
 
ulen EndpointDevice::getMaxInboundLen()
 {
  return max_inbound_len;
 }
 
void EndpointDevice::attach(PacketEndpointDevice::InboundProc *proc)
 {
  host.attach(proc);
 }
 
void EndpointDevice::detach()
 {
  host.detach();
 }

/* class MultipointDevice */

void MultipointDevice::Proc::do_replace(MasterKeyPtr &skey,ClientProfilePtr &client_profile_)
 {
  opened=true;
  
  //proc.replace(*skey);
  
  Swap(client_profile,client_profile_);
 }

void MultipointDevice::Proc::response(XPoint point,const KeyResponse &resp,MultipointDevice *host_dev)
 {
  switch( resp.type )
    {
     case Packet_Alert :
     case Packet_Ready :
     case Packet_Ack :
     case Packet_Stop :
      {
       Packet<uint8> packet=host_dev->pset.try_get();
       
       if( ProcLocked(mutex,proc)->response(resp,packet,host_dev->outbound_format) )
         {
          outbound(point,packet,resp.type,host_dev);
         }
      }
     break;
    }
 }

bool MultipointDevice::Proc::decUse()
 {
  use_count--;
  
  if( !use_count && +replace_skey )
    {
     do_replace(replace_skey,replace_client_profile);
     
     replace_skey.set(0);
     replace_client_profile.set(0);
    }
  
  return !use_count && !opened ;
 }

bool MultipointDevice::Proc::close()
 {
  opened=false;
  
  return !use_count;
 }

void MultipointDevice::Proc::replace(MasterKeyPtr &skey_,ClientProfilePtr &client_profile_)
 {
  replace_skey.set(0);
  replace_client_profile.set(0);
 
  if( use_count )
    {
     Swap(replace_skey,skey_);
     Swap(replace_client_profile,client_profile_);
    }
  else
    {
     do_replace(skey_,client_profile_);
    }
 }

void MultipointDevice::Proc::inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data,MultipointDevice *host_dev)
 {
  KeyResponse resp;
  
  auto result=ProcLocked(mutex,proc)->inbound(resp,Range(const_cast<uint8 *>(data.ptr),data.len));
  
  if( result.consumed )
    {
     response(point,resp,host_dev);
     
     packet.complete();
    }
  else
    {
     Hook hook(host_dev->host);
    
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

void MultipointDevice::Proc::outbound(XPoint point,Packet<uint8> packet,Packets type,MultipointDevice *host_dev)
 {
  if( packet.checkRange(host_dev->outbound_format) )
    {
     auto result=ProcLocked(mutex,proc)->outbound(packet.getRange(host_dev->outbound_format),host_dev->outbound_delta,type);
     
     if( result.ok )
       {
        packet.setDataLen(packet.getDataLen()-result.delta);       
       
        host_dev->dev->outbound(point,packet);
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

void MultipointDevice::Proc::tick(XPoint point,MultipointDevice *host_dev)
 {
  KeyResponse resp;
  
  ProcLocked(mutex,proc)->tick(resp);
  
  response(point,resp,host_dev);
 }

void MultipointDevice::inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data)
 {
  Proc *obj;
  
  {
   Mutex::Lock lock(mutex);
  
   obj=map.find(point);
   
   if( obj ) obj->incUse();
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
 
void MultipointDevice::tick()
 {
  {
   Hook hook(host);
   
   if( +hook ) hook->tick();
  }
  
  Mutex::Lock lock(mutex);

  map.applyIncr( [this] (XPoint point,Proc &obj) { obj.tick(point,this); } );
 }

MultipointDevice::MultipointDevice(StrLen mp_dev_name)
 : hook(mp_dev_name),
   dev(hook),
   host("PSec::MultipointDevice","PSec::MultipointDevice.host"),
   pset("PSec::MultipointDevice.pset"),
   mutex("PSec::MultipointDevice.mutex")
 {
  // TODO
  
  dev->attach(this);
 }

MultipointDevice::~MultipointDevice()
 {
  dev->detach();
 }

StrLen MultipointDevice::toText(XPoint point,PtrLen<char> buf)
 {
  return dev->toText(point,buf);
 }
 
PacketFormat MultipointDevice::getOutboundFormat()
 {
  return outbound_format;
 }
 
void MultipointDevice::outbound(XPoint point,Packet<uint8> packet)
 {
  Proc *obj;
  
  {
   Mutex::Lock lock(mutex);
  
   obj=map.find(point);
   
   if( obj ) obj->incUse();
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
 
ulen MultipointDevice::getMaxInboundLen()
 {
  return max_inbound_len;
 }
 
void MultipointDevice::attach(PacketMultipointDevice::InboundProc *proc)
 {
  host.attach(proc);
 }
 
void MultipointDevice::detach()
 {
  host.detach();
 }

void MultipointDevice::open(XPoint point,MasterKeyPtr &skey,ClientProfilePtr &client_profile)
 {
  SilentReportException report;
  
  try
    {
     Mutex::Lock lock(mutex);
     
     auto result=map.find_or_add(point,*skey,client_profile);
     
     if( !result.new_flag )
       {
        result.obj->replace(skey,client_profile);
       }
    }
  catch(...)
    {
    }
 }

void MultipointDevice::close(XPoint point)
 {
  Mutex::Lock lock(mutex);
 
  Proc *obj=map.find(point);
  
  if( obj && obj->close() ) map.del(point);
 }

void MultipointDevice::closeAll()
 {
  Mutex::Lock lock(mutex);

  // TODO
 }

AbstractClientProfile * MultipointDevice::getClientProfile(XPoint point)
 {
  Mutex::Lock lock(mutex);
 
  Proc *obj=map.find(point);
  
  if( obj ) return obj->client_profile.getPtr();
  
  return 0;
 }

} // namespace PSec 
} // namespace Net
} // namespace CCore
 


