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

#include <CCore/inc/TreeMap.h>
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

class MultipointDevice;

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
     SequenceNumber sequence_number = 0 ;
     KeyIndex key_index = 0 ;
     PadLen pad_len = 0 ;
     PacketType type = 0 ;
     
     // constructors

     Header() {}
     
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
   
   void consume(KeyResponse &resp,PacketType type,PtrLen<const uint8> data);
   
  public:
  
   explicit PacketProcessor(const MasterKey &master_key);
   
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
   
   InboundResult inbound(KeyResponse &resp,PtrLen<uint8> data);
   
   struct OutboundResult
    {
     ulen delta;
     bool ok;
     
     OutboundResult(NothingType) : delta(0),ok(false) {}
     
     OutboundResult(ulen delta_) : delta(delta_),ok(true) {}
    };
   
   OutboundResult outbound(PtrLen<uint8> data,ulen delta,PacketType type);
   
   void tick(KeyResponse &resp) { return core.tick(resp); }
   
   void count(ProcessorEvent ev) { stat.count(ev); }
   
   void getStat(ProcessorStatInfo &ret) const { ret=stat; }
   
   bool response(const KeyResponse &resp,Packet<uint8> packet,PacketFormat format);
 };

/* class EndpointDevice */

class EndpointDevice : public ObjBase , public PacketEndpointDevice 
 {
   class Engine : NoCopy , InboundProc
    {
      PacketEndpointDevice *dev;
      
      AttachmentHost<InboundProc> host;
      
      using Hook = AttachmentHost<InboundProc>::Hook ;
      
      using ProcLocked = Locked<Mutex,PacketProcessor> ;
      
      ulen outbound_delta;
      PacketFormat outbound_format;
      ulen max_inbound_len;
      
      PacketSet<uint8> pset;
      
      mutable Mutex mutex;
      
      PacketProcessor proc;
      
     private: 
      
      void response(const KeyResponse &resp);
      
      // InboundProc
      
      virtual void inbound(Packet<uint8> packet,PtrLen<const uint8> data);
       
      virtual void tick();
      
     public: 
      
      Engine(PacketEndpointDevice *dev,const MasterKey &master_key);
      
      ~Engine();
      
      void getStat(ProcessorStatInfo &ret) const;
      
      PacketFormat getOutboundFormat() const;
       
      void outbound(Packet<uint8> packet,Packets type=Packet_Data);
       
      ulen getMaxInboundLen() const;
       
      void attach(InboundProc *proc);
       
      void detach();
    };
   
   ObjHook hook;
   
   Engine engine;
   
  public:
  
   EndpointDevice(StrLen ep_dev_name,const MasterKey &master_key);
   
   virtual ~EndpointDevice();
   
   // stat
   
   using StatInfo = ProcessorStatInfo ;
   
   void getStat(StatInfo &ret) const { engine.getStat(ret); }
   
   // PacketEndpointDevice
   
   virtual PacketFormat getOutboundFormat();
    
   virtual void outbound(Packet<uint8> packet);
    
   virtual ulen getMaxInboundLen();
    
   virtual void attach(InboundProc *proc);
    
   virtual void detach();
 };

/* class MultipointDevice */

class MultipointDevice : public ObjBase , public PacketMultipointDevice , public EndpointManager
 {
   class Engine;
  
   class Proc : NoCopy
    {
      ulen use_count = 0 ;
      bool opened = true ;
     
      MasterKeyPtr replace_skey;
      ClientProfilePtr replace_client_profile;
     
      using ProcLocked = Locked<Mutex,PacketProcessor> ;
     
      Mutex mutex;
     
      PacketProcessor proc;
     
      ClientProfilePtr client_profile;
     
      void do_replace(MasterKeyPtr &skey,ClientProfilePtr &client_profile);
     
      void response(XPoint point,const KeyResponse &resp,Engine *engine);
      
     public: 
     
      Proc(const MasterKey &master_key,ClientProfilePtr &client_profile_)
       : mutex("PSec::MultipointDevice::Proc"),
         proc(master_key)
       {
        client_profile.set(client_profile_.detach());
       }
      
      AbstractClientProfile * getClientProfile() const { return client_profile.getPtr(); }
      
      void incUse() { use_count++; }
      
      bool decUse(); // true to del
      
      bool close(); // true to del
      
      void replace(MasterKeyPtr &skey,ClientProfilePtr &client_profile);
      
      void inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data,Engine *engine);
      
      void outbound(XPoint point,Packet<uint8> packet,Packets type,Engine *engine);
      
      bool tick(XPoint point,Engine *engine); // true to del
    };
  
   class Engine : NoCopy , InboundProc
    {
      PacketMultipointDevice *dev;
      
      AttachmentHost<InboundProc> host;
      
      using Hook = AttachmentHost<InboundProc>::Hook ;
      
      ulen outbound_delta;
      PacketFormat outbound_format;
      ulen max_inbound_len;
      
      PacketSet<uint8> pset;
      
      mutable Mutex mutex;
      
      RadixTreeMap<XPoint,Proc> map;
      
     private: 
 
      // InboundProc
      
      virtual void inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data);
       
      virtual void tick();

     public:
      
      explicit Engine(PacketMultipointDevice *dev);
      
      ~Engine();
      
      StrLen toText(XPoint point,PtrLen<char> buf) const;
       
      PacketFormat getOutboundFormat() const;
       
      void outbound(XPoint point,Packet<uint8> packet);
       
      ulen getMaxInboundLen() const;
       
      void attach(InboundProc *proc);
       
      void detach();
      
      OpenErrorCode open(XPoint point,MasterKeyPtr &skey,ClientProfilePtr &client_profile);
      
      void close(XPoint point);
      
      void closeAll();
      
      AbstractClientProfile * getClientProfile(XPoint point) const;
    };
   
   ObjHook hook;
   
   Engine engine;
   
  public:
  
   MultipointDevice(StrLen mp_dev_name);
   
   virtual ~MultipointDevice();
   
   // stat TODO
   
   // PacketMultipointDevice
   
   virtual StrLen toText(XPoint point,PtrLen<char> buf);
    
   virtual PacketFormat getOutboundFormat();
    
   virtual void outbound(XPoint point,Packet<uint8> packet);
    
   virtual ulen getMaxInboundLen();
    
   virtual void attach(InboundProc *proc);
    
   virtual void detach();
   
   // EndpointManager
   
   virtual OpenErrorCode open(XPoint point,MasterKeyPtr &skey,ClientProfilePtr &client_profile);
   
   virtual void close(XPoint point);
   
   virtual void closeAll();
   
   virtual AbstractClientProfile * getClientProfile(XPoint point); // only inside inbound processing
 };

} // namespace PSec 
} // namespace Net
} // namespace CCore
 
#endif
 


