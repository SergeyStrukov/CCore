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

#include <CCore/inc/net/PacketEndpointDevice.h>
#include <CCore/inc/PacketSet.h>

#include <CCore/inc/net/PSecCore.h>

#include <CCore/inc/ObjHost.h>
#include <CCore/inc/AttachmentHost.h>
#include <CCore/inc/SaveLoad.h>
#include <CCore/inc/Counters.h>
#include <CCore/inc/task/TaskEvent.h>
 
namespace CCore {
namespace Net {
namespace PSec {

/* classes */

//enum ProcessorEvent;

struct EventRegType;

struct ProtoEvent;

class ProcessorStatInfo;

class PacketProcessor;

class EndpointDevice;

/* enum ProcessorEvent */

enum ProcessorEvent
 {
  ProcessorEvent_Rx,
  ProcessorEvent_RxBadLen,
  ProcessorEvent_RxBadPadLen,
  ProcessorEvent_RxReplay,
  ProcessorEvent_RxBadKeyIndex,
  ProcessorEvent_RxBadHash,
  ProcessorEvent_RxDone,
  
  ProcessorEvent_Tx,
  ProcessorEvent_TxBadFormat,
  ProcessorEvent_TxNoKey,
  ProcessorEvent_TxDone,
  
  ProcessorEvent_KeyNoPacket,
  ProcessorEvent_KeyBadFormat,
  
  ProcessorEvent_KeyAlert,
  ProcessorEvent_KeyReady,
  ProcessorEvent_KeyAck,
  ProcessorEvent_KeyStop,
  
  ProcessorEventLim
 };

const char * GetTextDesc(ProcessorEvent ev);

/* struct EventRegType */

struct EventRegType
 {
  static EventIdType Register(EventMetaInfo &info);  
 };

/* struct ProtoEvent */

struct ProtoEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint8 ev;
  
  void init(EventTimeType time_,EventIdType id_,ProcessorEvent ev_)
   {
    time=time_; 
    id=id_;
    
    ev=ev_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<ProtoEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<ProtoEvent *>(ptr)->id); }
  
  static void * Offset_ev(void *ptr) { return &(static_cast<ProtoEvent *>(ptr)->ev); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class ProcessorStatInfo */

class ProcessorStatInfo : public Counters<ProcessorEvent,ProcessorEventLim>
 {
  public:
  
   void count(ProcessorEvent ev)
    {
     TaskEventHost.addProto<ProtoEvent>(ev);
 
     Counters<ProcessorEvent,ProcessorEventLim>::count(ev);
    }
 };

/* class PacketProcessor */

class PacketProcessor : NoCopy
 {
   ProcessorCore core;
   
   ulen header_len;
   ulen min_out_len;
   ulen min_inp_len;
   
   SequenceNumber out_sequence_number = 0 ;
   
   AntiReplay anti_replay;
   
   ProcessorStatInfo stat;
   
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
   
   static const ulen KeyIndexLen = SaveLenCounter<KeyIndex>::SaveLoadLen ;
   
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
   
   KeyResponse inbound(PacketType type,PtrLen<const uint8> data);
   
  public:
  
   explicit PacketProcessor(const MasterKey &master_key);
   
   ~PacketProcessor();
   
   ulen getOutDelta(ulen len);
   
   ulen getMaxInpLen(ulen len);
   
   struct InboundResult
    {
     PtrLen<const uint8> data;
     bool consumed;
     KeyResponse resp;

     InboundResult(NothingType) : consumed(true),resp(Nothing) {}
     
     InboundResult(PtrLen<const uint8> data_) : data(data_),consumed(false),resp(Nothing) {}
     
     InboundResult(KeyResponse resp_) : consumed(true),resp(resp_) {}
    };
   
   InboundResult inbound(PtrLen<uint8> data);
   
   struct OutboundResult
    {
     ulen delta;
     bool ok;
     
     OutboundResult(NothingType) : delta(0),ok(false) {}
     
     OutboundResult(ulen delta_) : delta(delta_),ok(true) {}
    };
   
   OutboundResult outbound(PtrLen<uint8> data,ulen delta,PacketType type);
   
   KeyResponse tick() { return core.tick(); }
   
   void count(ProcessorEvent ev) { stat.count(ev); }
   
   void getStat(ProcessorStatInfo &ret) { ret=stat; }
   
   bool response(KeyResponse resp,Packet<uint8> packet,PacketFormat format);
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
   
   PacketSet<uint8> pset;
   
   Mutex mutex;
   
   PacketProcessor proc;
   
  private: 
   
   void response(KeyResponse resp);
   
   void outbound(Packet<uint8> packet,Packets type);
   
   // InboundProc
   
   virtual void inbound(Packet<uint8> packet,PtrLen<const uint8> data);
    
   virtual void tick();
   
  public:
  
   EndpointDevice(StrLen ep_dev_name,const MasterKey &master_key);
   
   virtual ~EndpointDevice();
   
   // stat
   
   using StatInfo = ProcessorStatInfo ;
   
   void getStat(StatInfo &ret);
   
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
 


