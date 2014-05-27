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

/* class PacketProcessor */

void PacketProcessor::inbound(PacketType type,PtrLen<const uint8> data) // TODO
 {
  Used(type);
  Used(data);
 }

PacketProcessor::PacketProcessor(const MasterKey &master_key)
 : core(master_key)
 {
  header_len=RoundUp(2*HeaderLen,core.getBLen());
  
  min_out_len=outLen(64);
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
  // 1
  
  ulen blen=core.getBLen();

  if( data.len%blen || data.len<=header_len ) return Nothing;
  
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
   
   if( header.pad_len>=len ) return Nothing;
   
   len-=header.pad_len;
   
   if( !anti_replay.test(header.sequence_number) ) return Nothing;
   
   if( !core.setDecryptKey(header.key_index) ) return Nothing;
   
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
   
   if( len<hlen ) return Nothing;

   len-=hlen;
   
   core.add(Range_const(base-HeaderLen,len+HeaderLen));
   
   const uint8 *hash=core.finish();
   
   if( !Range_const(hash,hlen).equal(base+len) ) return Nothing;
  }
  
  if( header.type!=Packet_Data )
    {
     inbound(header.type,Range_const(base,len));
    
     return Nothing;
    }
  
  return Range_const(base,len);
 }

auto PacketProcessor::outbound(PtrLen<uint8> data,ulen delta,PacketType type) -> OutboundResult
 {
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
   
   if( !select.ok ) return Nothing;
   
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
  
  return ret;
 }

void PacketProcessor::tick(PacketFormat format,PacketList &list) // TODO
 {
  Used(format);
  Used(list);
 }

/* class EndpointDevice */

void EndpointDevice::inbound(Packet<uint8> packet,PtrLen<const uint8> data)
 {
  auto result=ProcLocked(mutex,proc)->inbound(Range(const_cast<uint8 *>(data.ptr),data.len));
  
  if( result.consumed )
    {
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
  
  PacketList list;
  
  ProcLocked(mutex,proc)->tick(outbound_format,list);

  while( auto packet=list.get() ) dev->outbound(packet);
 }

EndpointDevice::EndpointDevice(StrLen ep_dev_name,const MasterKey &master_key)
 : hook(ep_dev_name),
   dev(hook),
   host("PSec::EndpointDevice","PSec::EndpointDevice.host"),
   mutex("PSec::EndpointDevice"),
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

PacketFormat EndpointDevice::getOutboundFormat()
 {
  return outbound_format;
 }
 
void EndpointDevice::outbound(Packet<uint8> packet)
 {
  if( packet.checkRange(outbound_format) )
    {
     auto result=ProcLocked(mutex,proc)->outbound(packet.getRange(outbound_format),outbound_delta);
     
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
     packet.complete();
    }
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
 


