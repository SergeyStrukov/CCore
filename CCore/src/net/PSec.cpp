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

#include <CCore/inc/UIntSplit.h>
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
    "PSec Tx Done"          // ProcessorEvent_TxDone
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

KeySet::Response PacketProcessor::inbound(PacketType type,PtrLen<const uint8> data)
 {
  KeyIndex key_index=0;
  const uint8 *gy=0;
  
  switch( type )
    {
     case Packet_Alert : 
     case Packet_Ready :
      {
       if( data.len<SaveLenCounter<KeyIndex>::SaveLoadLen+core.getGLen() ) return Nothing;
       
       KeyIndex key_index;
       
       BufGetDev dev(data.ptr);
       
       dev.use<BeOrder>(key_index);
       
       gy=dev.getRest();
      }
     break; 
      
     case Packet_Ack :
      {
       if( data.len<SaveLenCounter<KeyIndex>::SaveLoadLen ) return Nothing;
       
       KeyIndex key_index;
       
       BufGetDev dev(data.ptr);
       
       dev.use<BeOrder>(key_index);
      }
     break; 
    }
  
  switch( type )
    {
     case Packet_Alert : return core.alert(key_index,gy);
     
     case Packet_Ready : return core.ready(key_index,gy);
      
     case Packet_Ack : return core.ack(key_index);
      
     default: return Nothing; 
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

auto PacketProcessor::inbound(PtrLen<uint8> data) -> InboundResult
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
   
   if( !core.setDecryptKey(header.key_index) ) 
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
     return inbound(header.type,Range_const(base,len));
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
   
   Header h;
   
   h.sequence_number=out_sequence_number++;
   h.key_index=select.key_index;
   h.pad_len=PadLen(pad_len);
   h.type=type;
   
   BufPutDev dev(header);
   
   dev(h);
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

void PacketProcessor::random(uint8 *ptr,ulen len)
 {
  for(uint8 &x : Range(ptr,len) ) x=core.random();
 }

/* class EndpointDevice */

void EndpointDevice::response(KeyIndex key_index,Packets type,PtrLen<const uint8> gx)
 {
  switch( type )
    {
     case Packet_Alert :
     case Packet_Ready :
      {
       Packet<uint8> packet=pset.try_get();
       
       if( !packet ) 
         {
          return;
         }
       
       ulen min_len=SaveLenCounter<KeyIndex>::SaveLoadLen+gx.len;
       
       ulen max_len=packet.getMaxDataLen(outbound_format).len;
       
       if( min_len>max_len )
         {
          packet.complete();
          
          return;
         }
       
       ulen len=ProcLocked(mutex,proc)->selectLen(min_len,max_len);
       
       auto data=packet.setDataLen(outbound_format,len);
          
       BufPutDev dev(data.ptr);
       
       dev.use<BeOrder>(key_index);
       
       uint8 *ptr=dev.getRest();
       
       gx.copyTo(ptr);
       
       ProcLocked(mutex,proc)->random(ptr+gx.len,max_len-min_len);
         
       outbound(packet,type);
      }
     break; 
      
     case Packet_Ack :
      {
       Packet<uint8> packet=pset.try_get();
       
       if( !packet ) 
         {
          return;
         }
       
       ulen min_len=SaveLenCounter<KeyIndex>::SaveLoadLen;
       
       ulen max_len=packet.getMaxDataLen(outbound_format).len;
       
       if( min_len>max_len )
         {
          packet.complete();
          
          return;
         }
       
       ulen len=ProcLocked(mutex,proc)->selectLen(min_len,max_len);
       
       auto data=packet.setDataLen(outbound_format,len);
          
       BufPutDev dev(data.ptr);
       
       dev.use<BeOrder>(key_index);
       
       uint8 *ptr=dev.getRest();
       
       ProcLocked(mutex,proc)->random(ptr,max_len-min_len);
         
       outbound(packet,type);
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
  auto result=ProcLocked(mutex,proc)->inbound(Range(const_cast<uint8 *>(data.ptr),data.len));
  
  if( result.consumed )
    {
     response(result.resp);
     
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
  
  response(ProcLocked(mutex,proc)->tick());
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

} // namespace PSec 
} // namespace Net
} // namespace CCore
 


