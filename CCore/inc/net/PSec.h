/* PSec.h */
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

#ifndef CCore_inc_net_PSec_h
#define CCore_inc_net_PSec_h

#include <CCore/inc/net/PSecCore.h>

#include <CCore/inc/ObjHost.h>
#include <CCore/inc/AttachmentHost.h>
#include <CCore/inc/SaveLoad.h>
 
#include <CCore/inc/net/PacketEndpointDevice.h>

namespace CCore {
namespace Net {
namespace PSec {

/* classes */

class PacketProcessor;

class EndpointDevice;

/* class PacketProcessor */

class PacketProcessor : NoCopy
 {
   ProcessorCore core;
   
   ulen header_len;
   ulen min_out_len;
   
   SequenceNumber out_sequence_number = 0 ;
   
   AntiReplay anti_replay;
   
  private: 
   
   struct Header
    {
     SequenceNumber sequence_number;
     KeyIndex key_index;
     PadLen pad_len;
     PacketType type;
     
     // constructors

     Header() : sequence_number(),key_index(),pad_len(),type() {}
     
     // save/load object

     enum { SaveLoadLen = SaveLenCounter<SequenceNumber,KeyIndex,PadLen,PacketType>::SaveLoadLen  };
     
     template <class Dev>
     void save(Dev &dev) const
      {
       dev.template use<BeOrder>(sequence_number,key_index,pad_len,type);
      }
     
     template <class Dev>
     void load(Dev &dev)
      {
       dev.template use<BeOrder>(sequence_number,key_index,pad_len,type);
      }
    };
   
   static const ulen HeaderLen = Header::SaveLoadLen ;
   
  private: 
  
   static ulen RoundUpCount(ulen len,ulen N) { return (len+N-1)/N; }
   
   static ulen RoundUp(ulen len,ulen N) { return N*RoundUpCount(len,N); }
   
   static ulen RoundDownCount(ulen len,ulen N) { return len/N; }
   
   static ulen RoundDown(ulen len,ulen N) { return N*RoundDownCount(len,N); }
   
   ulen outLen(ulen len) const 
    { 
     ulen l=len+core.getHLen();
     
     ulen s=RoundUpCount(l,DLen)+l;
     
     return header_len+RoundUp(s,core.getBLen()); 
    }

   ulen inpLen(ulen len) const 
    { 
     ulen s=RoundDown(len-header_len,core.getBLen());
     
     ulen l=s-RoundUpCount(s,DLen+1);
     
     return l-core.getHLen(); 
    }
   
   void inbound(PacketType type,PtrLen<const uint8> data);
   
  public:
  
   explicit PacketProcessor(MasterKey &master_key);
   
   ~PacketProcessor();
   
   ulen getOutDelta(ulen len);
   
   ulen getMaxInpLen(ulen len);
   
   struct InboundResult
    {
     PtrLen<const uint8> data;
     bool consumed;

     InboundResult(NothingType) : consumed(true) {}
     
     InboundResult(PtrLen<const uint8> data_) : data(data_),consumed(false) {}
    };
   
   InboundResult inbound(PtrLen<uint8> data);
   
   struct OutboundResult
    {
     ulen delta;
     bool ok;
     
     OutboundResult(NothingType) : delta(0),ok(false) {}
     
     OutboundResult(ulen delta_) : delta(delta_),ok(true) {}
    };
   
   OutboundResult outbound(PtrLen<uint8> data,ulen delta,PacketType type=Packet_Data);
   
   void tick(PacketFormat fmt,PacketList &list);
 };

/* class EndpointDevice */

class EndpointDevice : public ObjBase , public PacketEndpointDevice , PacketEndpointDevice::InboundProc 
 {
   ObjHook hook;
   
   PacketEndpointDevice *dev;
   
   AttachmentHost<PacketEndpointDevice::InboundProc> host;
   
   using Hook = AttachmentHost<PacketEndpointDevice::InboundProc>::Hook ;
   
   using ProcLocked = Locked<Mutex,PacketProcessor> ;
   
   ulen outbound_delta;
   PacketFormat outbound_format;
   ulen max_inbound_len;
   
   Mutex mutex;
   
   PacketProcessor proc;
   
  private: 
   
   // InboundProc
   
   virtual void inbound(Packet<uint8> packet,PtrLen<const uint8> data);
    
   virtual void tick();
   
  public:
  
   EndpointDevice(StrLen ep_dev_name,MasterKey &master_key);
   
   virtual ~EndpointDevice();
   
   // PacketEndpointDevice
   
   virtual PacketFormat getOutboundFormat();
    
   virtual void outbound(Packet<uint8> packet);
    
   virtual ulen getMaxInboundLen();
    
   virtual void attach(PacketEndpointDevice::InboundProc *proc);
    
   virtual void detach();
 };

} // namespace PSec 
} // namespace Net
} // namespace CCore
 
#endif
 


