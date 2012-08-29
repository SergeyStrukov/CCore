/* PTPServerDevice.h */ 
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

#ifndef CCore_inc_net_PTPServerDevice_h
#define CCore_inc_net_PTPServerDevice_h
 
#include <CCore/inc/net/PacketEndpointDevice.h>

#include <CCore/inc/net/PTPBase.h>
#include <CCore/inc/net/PTPSupportBase.h>

#include <CCore/inc/Counters.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/PacketSet.h>
#include <CCore/inc/task/TaskEvent.h>

namespace CCore {
namespace Net {
namespace PTP {

/* classes */ 

//enum ServerEvent;

struct ServerEventRegType;

struct ServerProtoEvent;

struct ServerProtoEvent_slot;

class ServerStatInfo;

struct TransIndex;

struct ServerProc;

class ServerEngine;

class ServerDevice;

/* enum ServerEvent */ 

enum ServerEvent : uint8
 {
  ServerEvent_Trans,
  ServerEvent_TransDone,
  
  ServerEvent_Timeout,
  ServerEvent_Cancel,
  ServerEvent_ClientCancel,
  ServerEvent_Abort,
  
  ServerEvent_CALL,
  ServerEvent_RECALL,
  ServerEvent_SENDRET,
  ServerEvent_ACK,
  
  ServerEvent_RET,
  ServerEvent_CANCEL,
  ServerEvent_NOINFO,
  ServerEvent_RERET,
  
  ServerEvent_BadTransId,

  ServerEvent_NoSlot,
  ServerEvent_NoSlotCancel,
  ServerEvent_NoFreeSlot,
  ServerEvent_NoPacket,
  
  ServerEvent_BadInbound,
  ServerEvent_BadOutbound,
  
  ServerEventLim
 };
 
const char * GetTextDesc(ServerEvent ev);

/* struct ServerEventRegType */

struct ServerEventRegType
 {
  static EventIdType Register(EventMetaInfo &info);  
 };

/* struct ServerProtoEvent */

struct ServerProtoEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint8 ev;
  
  void init(EventTimeType time_,EventIdType id_,ServerEvent ev_)
   {
    time=time_; 
    id=id_;
    
    ev=ev_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<ServerProtoEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<ServerProtoEvent *>(ptr)->id); }
  
  static void * Offset_ev(void *ptr) { return &(static_cast<ServerProtoEvent *>(ptr)->ev); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* struct ServerProtoEvent_slot */

struct ServerProtoEvent_slot
 {
  EventTimeType time;
  EventIdType id;
  
  uint8 ev;
  uint32 slot;
  
  void init(EventTimeType time_,EventIdType id_,SlotId slot_,ServerEvent ev_)
   {
    time=time_; 
    id=id_;
    
    slot=slot_;
    ev=ev_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<ServerProtoEvent_slot *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<ServerProtoEvent_slot *>(ptr)->id); }
  
  static void * Offset_ev(void *ptr) { return &(static_cast<ServerProtoEvent_slot *>(ptr)->ev); }
  
  static void * Offset_slot(void *ptr) { return &(static_cast<ServerProtoEvent_slot *>(ptr)->slot); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class ServerStatInfo */

class ServerStatInfo : public Counters<ServerEvent,ServerEventLim>
 {
  public:
 
   void count(ServerEvent ev)
    {
     TaskEventHost.addProto<ServerProtoEvent>(ev);
  
     Counters<ServerEvent,ServerEventLim>::count(ev);
    }
  
   void count(SlotId slot,ServerEvent ev)
    {
     TaskEventHost.addProto<ServerProtoEvent_slot>(slot,ev);
  
     Counters<ServerEvent,ServerEventLim>::count(ev);
    }
 };

/* struct TransIndex */

struct TransIndex
 {
  ulen slot;
  ulen index;
  
  TransIndex() : slot(MaxULen),index(MaxULen) {}
  
  TransIndex(ulen slot_,ulen index_) : slot(slot_),index(index_) {}
 };

/* struct ServerProc */ 
 
struct ServerProc
 {
  virtual void inbound(XPoint point,TransIndex idx,Packet<uint8> packet,PtrLen<const uint8> client_info)=0;
  
  virtual void tick()=0;
 };
   
/* class ServerEngine */ 

class ServerEngine : public Funchor_nocopy , PacketMultipointDevice::InboundProc
 {
   static const unsigned MaxRetries = 100 ;
   
   Mutex mutex;
   
   PacketMultipointDevice *mp;
   PacketFormat outbound_format;
   
   ServerProc *proc;
   AntiSem asem;
   
   struct ProcExt
    {
     ServerProc *proc;
     XPoint point;
     TransIndex idx;
     PtrLen<const uint8> client_info;
     AntiSem *asem;
     
     ProcExt(ServerProc *proc_,XPoint point_,TransIndex idx_,PtrLen<const uint8> client_info_,AntiSem *asem_)
      : proc(proc_),point(point_),idx(idx_),client_info(client_info_),asem(asem_) {}
      
     void operator () (Packet<uint8> packet) 
      {
       proc->inbound(point,idx,packet,client_info);
       
       asem->dec();
      }
      
     static void Complete(PacketHeader *packet); 
    };
   
   struct Key
    {
     XPoint point;
     TransId trans_id;
     
     Key() : point(),trans_id() {}
     
     Key(XPoint point_,const TransId &trans_id_) : point(point_),trans_id(trans_id_) {}
     
     CmpResult objCmp(const Key &obj) const
      {
       return AlphaCmp(trans_id.clock,obj.trans_id.clock,
                       trans_id.number,obj.trans_id.number,
                       point,obj.point
                      );
      }
    };
   
   struct Slot : NoCopy
    {
     ServerEngine *engine;
     DLink<Slot> link;
     
     bool active;
     
     XPoint point;
     TransId trans_id;
     SlotId client_slot;
     SlotId server_slot;
     
     RecallNumber recall_number;
     unsigned timeout_msec;
     unsigned tick_count;
     
     unsigned retry_count;
     
     enum State
      {
       State_pending,
       State_ready,
       State_cancelled
      };
     
     State state;
     
     ulen index;
     PacketBuf pbuf;
     PtrLen<const uint8> server_info;
     
     PacketSet<uint8>::ExtTop plist;
     
     RBTreeUpLink<Slot,Key> tlink;

     void init(ServerEngine *engine_,SlotId server_slot_)
      {
       engine=engine_;
       active=false;
       server_slot=server_slot_;
       index=0;
      }
     
     void setTick()
      {
       tick_count=(timeout_msec*InboundTicksPerSec)/1000;
  
       if( timeout_msec<MaxTimeout ) timeout_msec+=DeltaTimeout;
      }
     
     // send_*()
     
     void send_RET(PacketList &complete_list);
     
     void send_CANCEL(PacketList &complete_list);
     
     void send_RERET(PacketList &complete_list);
     
     void send_NOINFO(PacketList &complete_list);
     
     // execute
     
     void start(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,Packet<uint8> packet,PtrLen<const uint8> client_info,RecallNumber recall_number=0);
     
     void send_info(PacketList &complete_list,Packet<uint8> proc_packet,PtrLen<const uint8> server_info);
     
     void send_cancel(PacketList &complete_list);
     
     // inbound_*()
     
     void inbound_CALL(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,Packet<uint8> packet,PtrLen<const uint8> client_info);
     
     void inbound_RECALL(PacketList &complete_list,SlotId client_slot,RecallNumber recall_number);
     
     void inbound_RECALL_first(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,Packet<uint8> packet,PtrLen<const uint8> client_info,RecallNumber recall_number);
     
     void inbound_ACK(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list);
     
     void inbound_SENDRET(PacketList &complete_list);
     
     bool tick(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list);
     
     void finish(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list);
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
    
   SimpleArray<Slot> slots;
   
   typedef RBTreeUpLink<Slot,Key>::Algo<&Slot::tlink,const Key &> TreeAlgo;
   
   typedef DLink<Slot>::CircularAlgo<&Slot::link> Algo;
   
   Algo::Top avail_list;
   Algo::Top active_list;
   TreeAlgo::Root active_tree;
   
   ServerStatInfo stat;
   
   ulen max_outbound_info_len;
   ulen max_inbound_info_len;
   
   PacketSet<uint8> pset;
   
   AntiSem slots_asem;
   
  private: 
  
   // locked
  
   Slot * find(XPoint point,SlotId server_slot,const TransId &trans_id);

   void activate(Slot *slot);
   
   void deactivate(Slot *slot);
   
   void deactivate_nodel(Slot *slot);
   
   void inbound_CALL(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,Packet<uint8> packet,PtrLen<const uint8> client_info);

   void inbound_RECALL(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,RecallNumber recall_number,Packet<uint8> packet,PtrLen<const uint8> client_info);
   
   void inbound_ACK(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,SlotId server_slot,Packet<uint8> packet);
   
   void inbound_SENDRET(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,SlotId server_slot,Packet<uint8> packet);
   
   void send_CANCEL(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,SlotId server_slot);
   
   Packet<uint8> getDataPacket();
   
   Packet<uint8> getDataPacket(PacketSet<uint8>::ExtTop &plist);
   
   void send(PacketList &complete_list,XPoint point,Packet<uint8> data_packet);
   
   template <class T>
   void send(PacketList &complete_list,XPoint point,const T &t,Packet<uint8> data_packet)
    {
     if( !data_packet ) return;
    
     auto len=SaveLen(t);
     
     if( data_packet.checkDataLen(outbound_format,len) )
       {
        BufPutDev dev(data_packet.setDataLen(outbound_format,len).ptr);
       
        dev(t);
        
        send(complete_list,point,data_packet);
       }
     else
       {
        stat.count(ServerEvent_BadOutbound);

        complete_list.put(data_packet);
       }  
    }
   
   template <class T1,class T2>
   void send(PacketList &complete_list,XPoint point,const T1 &t1,const T2 &t2,PtrLen<const uint8> info,Packet<uint8> data_packet)
    {
     if( !data_packet ) return;
    
     auto len=SaveLen(t1,t2)+info.len;
     
     if( data_packet.checkDataLen(outbound_format,len) )
       {
        BufPutDev dev(data_packet.setDataLen(outbound_format,len).ptr);
       
        dev(t1,t2);
        
        dev.put(info);
        
        send(complete_list,point,data_packet);
       }
     else
       {
        stat.count(ServerEvent_BadOutbound);
        
        complete_list.put(data_packet);
       }  
    }
    
   void bad_inbound(PacketList &complete_list,Packet<uint8> packet) 
    { 
     stat.count(ServerEvent_BadInbound); 
     
     complete_list.put(packet);
    }
   
  private: 
  
   void inbound_locked(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list,XPoint point,Packet<uint8> packet,PtrLen<const uint8> data);
   
   void tick_locked(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list);
   
   void cancelAll_locked(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list);
   
   void send_info_locked(PacketList &complete_list,TransIndex idx,Packet<uint8> proc_packet,PtrLen<const uint8> server_info);
   
   void send_cancel_locked(PacketList &complete_list,TransIndex idx);
   
  private: 
  
   virtual void inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data);
   
   virtual void tick();
   
   void do_send(PacketHeader *packet);
   
   PacketFunction function_send() { return FunctionOf(this,&ServerEngine::do_send); }
   
  public:
   
   // constructors
  
   static const ulen DefaultMaxSlots = 100 ;
  
   explicit ServerEngine(ulen max_slots=DefaultMaxSlots);
   
   ~ServerEngine();
   
   // methods
   
   PacketMultipointDevice * getMPDevice() const { return mp; }
   
   ulen getMaxOutboundInfoLen() const { return max_outbound_info_len; } // always > 0 , <= MaxInfoLen
   
   ulen getMaxInboundInfoLen() const { return max_inbound_info_len; } // always > 0 , <= MaxInfoLen
   
   void attach_to(PacketMultipointDevice *mp);
   
   void cancelAll();
   
   void getStat(ServerStatInfo &ret);
   
   void send_info(TransIndex idx,Packet<uint8> proc_packet,PtrLen<const uint8> server_info);
   
   void send_cancel(TransIndex idx);
   
   void attach(ServerProc *proc);
   
   void detach();
   
   void waitActiveComplete() { slots_asem.wait(); }
   
   bool waitActiveComplete(MSec timeout) { return slots_asem.wait(timeout); }
   
   bool waitActiveComplete(TimeScope time_scope) { return slots_asem.wait(time_scope); }
 };
 
/* class ServerDevice */ 

class ServerDevice : public ObjBase
 {
   ObjHook hook;
  
   ServerEngine engine;
   
  public: 
   
   // constructors
  
   explicit ServerDevice(StrLen mp_dev_name,ulen max_slots=ServerEngine::DefaultMaxSlots);
   
   virtual ~ServerDevice();
   
   // methods
   
   PacketMultipointDevice * getMPDevice() const { return engine.getMPDevice(); }
   
   ulen getMaxOutboundInfoLen() const { return engine.getMaxOutboundInfoLen(); }
   
   ulen getMaxInboundInfoLen() const { return engine.getMaxInboundInfoLen(); }
   
   typedef ServerStatInfo StatInfo;
   
   void getStat(ServerStatInfo &ret);
   
   void send_info(TransIndex idx,Packet<uint8> proc_packet,PtrLen<const uint8> server_info);
   
   void send_cancel(TransIndex idx);
   
   void attach(ServerProc *proc);
   
   void detach();
   
   void waitActiveComplete() { engine.waitActiveComplete(); }
   
   bool waitActiveComplete(MSec timeout) { return engine.waitActiveComplete(timeout); }
   
   bool waitActiveComplete(TimeScope time_scope) { return engine.waitActiveComplete(time_scope); }
 };
 
} // namespace PTP
} // namespace Net
} // namespace CCore
 
#endif
 

