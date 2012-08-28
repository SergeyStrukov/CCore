/* PTPClientDevice.h */ 
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

#ifndef CCore_inc_net_PTPClientDevice_h
#define CCore_inc_net_PTPClientDevice_h

#include <CCore/inc/net/PacketEndpointDevice.h>
 
#include <CCore/inc/net/PTPBase.h>
#include <CCore/inc/net/PTPSupportBase.h>

#include <CCore/inc/Counters.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/PacketSet.h>
#include <CCore/inc/task/TaskEvent.h>

namespace CCore {
namespace Net {
namespace PTP {

/* consts */

/* enum MoveFlagType */

enum MoveFlagType
 {
  MoveNothing,
  MovePacketBuf,
  MovePacketBufByRequest
 };

/* functions */

void GuardOutboundTooShort(const char *name);

/* classes */ 

//enum TransResult;

//enum ClientEvent;

struct ClientProtoEvent;

struct ClientProtoEvent_slot;

class ClientStatInfo;

struct TransExt;

class ClientEngine;

template <MoveFlagType MoveFlag> struct ExtMoveBase;

template <ServiceIdType ServiceId,FunctionIdType FunctionId,MoveFlagType MoveFlag=MoveNothing> struct ExtBase;

template <class T,ulen MaxLen=T::MaxLen> struct Tailed;

class ClientDevice;

/* enum TransResult */ 

enum TransResult
 {
  Trans_Ok = 0,
  
  Trans_Initial,
  Trans_BadDataLen,
  Trans_NoPacket,
  Trans_Cancelled,
  Trans_Aborted,
  Trans_Timeout,
  
  Trans_BadInboundLen1,
  Trans_BadInboundLen2,
  Trans_BadInboundLen3
 };
 
const char * GetTextDesc(TransResult result); 
 
/* enum ClientEvent */ 

enum ClientEvent : uint8
 {
  ClientEvent_Trans,
  ClientEvent_TransDone,
  
  ClientEvent_BadInfoLen,
  ClientEvent_Timeout,
  ClientEvent_Cancel,
  ClientEvent_Abort,
  
  ClientEvent_CALL,
  ClientEvent_RECALL,
  ClientEvent_ACK,
  ClientEvent_SENDRET,
  
  ClientEvent_RET,
  ClientEvent_NOINFO,
  ClientEvent_RERET,
  ClientEvent_CANCEL,
  
  ClientEvent_NoSlot,
  ClientEvent_NoPacket,
  
  ClientEvent_BadInbound,
  ClientEvent_BadOutbound,
 
  ClientEventLim
 };
 
const char * GetTextDesc(ClientEvent ev); 

/* struct ClientProtoEvent */

struct ClientProtoEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint8 ev;
  
  void init(EventTimeType time_,EventIdType id_,ClientEvent ev_)
   {
    time=time_; 
    id=id_;
    
    ev=ev_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<ClientProtoEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<ClientProtoEvent *>(ptr)->id); }
  
  static void * Offset_ev(void *ptr) { return &(static_cast<ClientProtoEvent *>(ptr)->ev); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* struct ClientProtoEvent_slot */

struct ClientProtoEvent_slot
 {
  EventTimeType time;
  EventIdType id;
  
  uint8 ev;
  uint32 slot;
  
  void init(EventTimeType time_,EventIdType id_,SlotId slot_,ClientEvent ev_)
   {
    time=time_; 
    id=id_;
    
    slot=slot_;
    ev=ev_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<ClientProtoEvent_slot *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<ClientProtoEvent_slot *>(ptr)->id); }
  
  static void * Offset_ev(void *ptr) { return &(static_cast<ClientProtoEvent_slot *>(ptr)->ev); }
  
  static void * Offset_slot(void *ptr) { return &(static_cast<ClientProtoEvent_slot *>(ptr)->slot); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class ClientStatInfo */

class ClientStatInfo : public Counters<ClientEvent,ClientEventLim>
 {
  public:
 
   void count(ClientEvent ev)
    {
     TaskEventHost.addProto<ClientProtoEvent>(ev);
  
     Counters<ClientEvent,ClientEventLim>::count(ev);
    }
 
   void count(SlotId slot,ClientEvent ev)
    {
     TaskEventHost.addProto<ClientProtoEvent_slot>(slot,ev);
  
     Counters<ClientEvent,ClientEventLim>::count(ev);
    }
 };

/* struct TransExt */ 

struct TransExt
 {
  enum State
   {
    Completed,
    Pending,
    Active,
   };
  
  TransResult result;              // output
  PtrLen<const uint8> server_info; // output
  
  State state;                     // internal
  ulen slot;                       // internal
  
  MoveFlagType move_flag;
  
  // constructors
  
  explicit TransExt(MoveFlagType move_flag_) : result(Trans_Initial),move_flag(move_flag_) {}
  
  // methods
  
  bool operator ! () const { return result!=Trans_Ok; }
  
  void setPending()
   {
    state=Pending;
   }
  
  void setSlot(ulen slot_)
   {
    state=Active;
    slot=slot_;
   }
  
  void setError(TransResult result_)
   {
    state=Completed;
    result=result_;
    server_info=Nothing;
   }
  
  void setInfo(PtrLen<const uint8> server_info_)
   {
    state=Completed;
    result=Trans_Ok;
    server_info=server_info_;
   }
 };
 
/* class ClientEngine */ 

class ClientEngine : public Funchor_nocopy , PacketEndpointDevice::InboundProc
 {
   static const unsigned MaxRetries = 100 ;
   
   Mutex mutex;
 
   PacketEndpointDevice *ep;
   PacketFormat outbound_format;
   
   PacketList pending_list;
   
   struct Slot : NoCopy
    {
     ClientEngine *engine;
     DLink<Slot> link;
     
     bool active;
    
     Packet<uint8,TransExt> packet;
     
     TransId trans_id;
     SlotId client_slot;
     SlotId server_slot;
     
     bool no_info;
     RecallNumber number;
     unsigned timeout_msec;
     unsigned tick_count;
     
     unsigned retry_count;
     
     PacketSet<uint8>::ExtTop plist;
     
     // methods
     
     void init(ClientEngine *engine_,SlotId client_slot_) 
      { 
       engine=engine_;
       client_slot=client_slot_; 
       active=false; 
      }
     
     void setTick() 
      { 
       tick_count=(timeout_msec*InboundTicksPerSec)/1000; 
       
       if( timeout_msec<MaxTimeout ) timeout_msec+=DeltaTimeout;
      }
      
     RecallNumber recallNumber()
      {
       RecallNumber ret=number;
       
       if( RecallNumber next=ret+1 ) number=next;
       
       return ret;
      }
      
     PtrLen<const uint8> getInfo() { return Range_const(packet.getRange()); }
     
     // send_*()
      
     void send_CALL(PacketList &complete_list);
     
     void send_RECALL(PacketList &complete_list);
     
     void send_SENDRET(PacketList &complete_list);
     
     void send_ACK(PacketList &complete_list);
     
     // inbound_*()
     
     bool start(PacketList &complete_list,Packet<uint8,TransExt> packet);
     
     void inbound_RET(PacketList &complete_list,Packet<uint8> server_packet,PtrLen<const uint8> server_info);
   
     void inbound_CANCEL(PacketList &complete_list);
   
     void inbound_NOINFO(PacketList &complete_list);
   
     void inbound_RERET(PacketList &complete_list);
     
     bool tick(PacketList &complete_list);
     
     void abort(PacketList &complete_list);
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
    
   SimpleArray<Slot> slots;
   
   typedef DLink<Slot>::CircularAlgo<&Slot::link> Algo;
   
   Algo::Top avail_list;
   Algo::Top active_list;
   
   uint64 trans_number;
   uint64 seed1;
   uint64 seed2;
   
   ClientStatInfo stat;
   
   ulen max_outbound_info_len;
   ulen max_inbound_info_len;
   
   PacketSet<uint8> pset;
   
  private: 
  
   // locked
  
   void getTransId(TransId &trans_id);
   
   void activate(Slot *slot);
   
   void deactivate(Slot *slot);
   
   void deactivate_nodel(Slot *slot);
   
   void pump(PacketList &complete_list);
   
   Slot * find(const TransId &trans_id,SlotId client_slot,SlotId server_slot);
   
   void inbound_RET(PacketList &complete_list,const TransId &trans_id,SlotId client_slot,SlotId server_slot,Packet<uint8> server_packet,PtrLen<const uint8> server_info);
   
   void inbound_CANCEL(PacketList &complete_list,const TransId &trans_id,SlotId client_slot,SlotId server_slot);
   
   void inbound_NOINFO(PacketList &complete_list,const TransId &trans_id,SlotId client_slot,SlotId server_slot);
   
   void inbound_RERET(PacketList &complete_list,const TransId &trans_id,SlotId client_slot,SlotId server_slot);
   
   void send_ACK(PacketList &complete_list,const TransId &trans_id,SlotId client_slot,SlotId server_slot);
   
   Packet<uint8> getDataPacket();
   
   Packet<uint8> getDataPacket(PacketSet<uint8>::ExtTop &plist);
   
   void send(PacketList &complete_list,Packet<uint8> data_packet);
   
   template <class T> 
   void send(PacketList &complete_list,const T &t,Packet<uint8> data_packet)
    {
     if( !data_packet ) return;
     
     auto len=SaveLen(t);
     
     if( data_packet.checkDataLen(outbound_format,len) )
       {
        BufPutDev dev(data_packet.setDataLen(outbound_format,len).ptr);
       
        dev(t);
        
        send(complete_list,data_packet);
       }
     else
       {
        stat.count(ClientEvent_BadOutbound);
        
        complete_list.put(data_packet);
       }  
    }
   
   template <class T1,class T2> 
   void send(PacketList &complete_list,const T1 &t1,const T2 &t2,PtrLen<const uint8> info,Packet<uint8> data_packet)
    {
     if( !data_packet ) return;
     
     auto len=SaveLen(t1,t2)+info.len;
     
     if( data_packet.checkDataLen(outbound_format,len) )
       {
        BufPutDev dev(data_packet.setDataLen(outbound_format,len).ptr);
       
        dev(t1,t2);
        
        dev.put(info);
        
        send(complete_list,data_packet);
       }
     else
       {
        stat.count(ClientEvent_BadOutbound);
        
        complete_list.put(data_packet);
       }  
    }
   
   void abort(PacketHeader *packet);
   
   PacketFunction function_abort() { return FunctionOf(this,&ClientEngine::abort); }
   
   void completeError(PacketList &complete_list,Packet<uint8,TransExt> packet,TransResult result);
   
   void completeInfo(PacketList &complete_list,Packet<uint8,TransExt> packet,Packet<uint8> server_packet,PtrLen<const uint8> server_info);
   
   void bad_inbound() { stat.count(ClientEvent_BadInbound); }
   
  private: 
   
   void inbound_locked(PacketList &complete_list,Packet<uint8> server_packet,PtrLen<const uint8> server_data);
   
   void tick_locked(PacketList &complete_list);
   
   void start_locked(PacketList &complete_list,Packet<uint8,TransExt> packet);
   
   void abortAll_locked(PacketList &complete_list);
   
  private: 
   
   virtual void inbound(Packet<uint8> server_packet,PtrLen<const uint8> server_data);
   
   virtual void tick();
   
   void do_send(PacketHeader *packet);
   
   PacketFunction function_send() { return FunctionOf(this,&ClientEngine::do_send); }
   
  public:
   
   // constructors
  
   static const ulen DefaultMaxSlots = 100 ;
   
   explicit ClientEngine(ulen max_slots=DefaultMaxSlots);
   
   ~ClientEngine();
   
   // methods
   
   PacketEndpointDevice * getEPDevice() const { return ep; }
   
   void attach_to(PacketEndpointDevice *ep);
   
   void start(Packet<uint8,TransExt> packet);
   
   void abortAll();
   
   void getStat(ClientStatInfo &ret);
   
   ulen getMaxOutboundInfoLen();
   
   ulen getMaxInboundInfoLen();
   
   void setSeed(uint64 seed1,uint64 seed2);
   
   void setLengths(ulen max_outbound_info_len,ulen max_inbound_info_len);
 };

/* struct ExtMoveBase<MoveFlagType MoveFlag> */

template <MoveFlagType MoveFlag> 
struct ExtMoveBase
 {
  template <class Ext>
  static MoveFlagType GetMoveFlag(Packet<uint8,Ext>) { return MoveFlag; }
 
  ExtMoveBase() {}
 };

template <> 
struct ExtMoveBase<MovePacketBufByRequest>
 {
  template <class Ext>
  static MoveFlagType GetMoveFlag(Packet<uint8,Ext> packet) { return packet.getExt()->move_flag; }
  
  MoveFlagType move_flag;
 
  explicit ExtMoveBase(MoveFlagType move_flag_) : move_flag(move_flag_) {}
 };

/* struct ExtBase<ServiceIdType ServiceId,FunctionIdType FunctionId,MoveFlagType MoveFlag> */ 

template <ServiceIdType ServiceId_,FunctionIdType FunctionId_,MoveFlagType MoveFlag>
struct ExtBase : ExtMoveBase<MoveFlag>
 {
  // consts
  
  static const ServiceIdType  ServiceId  = ServiceId_ ;
  static const FunctionIdType FunctionId = FunctionId_ ;
  
  // data
  
  TransResult result;
  ErrorIdType error_id;
  
  // constructors

  template <class ... TT>
  explicit ExtBase(TT ... tt) : ExtMoveBase<MoveFlag>(tt...) { reset(); }
  
  // methods
  
  bool isOk() const { return !result && !error_id ; }
  
  void reset()
   {
    result=Trans_Initial;
    error_id=Error_Unknown;
   }
  
  void setOk()
   {
    result=Trans_Ok;
    error_id=NoError;
   }
 
  void fail(TransResult result_)
   {
    result=result_;
    error_id=Error_Unknown;
   }
  
  void error(ErrorIdType error_id_)
   {
    result=Trans_Ok;
    error_id=error_id_;
   }
 };
 
/* struct Tailed<T,ulen MaxLen> */ 
 
template <class T,ulen MaxLen> 
struct Tailed
 {
  T output;
  PtrLen<const uint8> tail;
  
  Tailed() : output() {}
  
  // load object
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(output);
    
    if( output.len>MaxLen )
      dev.fail();
    else
      tail=dev.getFinalRange(output.len);
   }
 };
 
} // namespace PTP

namespace PTPSupport {

/* classes */

struct LenExt;

struct SeedExt;

struct SessionExt;

struct EchoExt;

struct ErrorDescExt;

struct ExistExt;

/* struct LenExt */  

struct LenExt : ExtBase<ServiceId,FunctionId_Len>
 {
  typedef LenInput InputType;
  typedef LenOutput OutputType;
  
  ulen max_outbound_info_len;
  ulen max_inbound_info_len;
  
  void done(const OutputType &output)
   {
    max_outbound_info_len=output.to_server_info_len;
    max_inbound_info_len=output.to_client_info_len;
   }
 };
 
/* struct SeedExt */  

struct SeedExt : ExtBase<ServiceId,FunctionId_Seed>
 {
  typedef SeedInput InputType;
  typedef SeedOutput OutputType;
  
  uint64 seed1;
  uint64 seed2;
  
  void done(const OutputType &output)
   {
    seed1=output.seed1;
    seed2=output.seed2;
   }
 };
 
/* struct SessionExt */ 

struct SessionExt : ExtBase<ServiceId,FunctionId_Session>
 {
  typedef SessionInput InputType;
  typedef SessionOutput OutputType;
  
  void done(const OutputType &)
   {
   }
 };
 
/* struct EchoExt */ 

struct EchoExt : ExtBase<ServiceId,FunctionId_Echo,MovePacketBuf>
 {
  typedef EchoInput InputType;
  typedef Tailed<EchoOutput> OutputType;
  
  PtrLen<const uint8> data;
  
  void done(const OutputType &output)
   {
    data=output.tail;
   }
 };
 
/* struct ErrorDescExt */ 

struct ErrorDescExt : ExtBase<ServiceId,FunctionId_ErrorDesc,MovePacketBuf>
 {
  typedef ErrorDescInput InputType;
  typedef Tailed<ErrorDescOutput> OutputType;
  
  PtrLen<const uint8> desc;
  
  void done(const OutputType &output)
   {
    desc=output.tail;
   }
 };
 
/* struct ExistExt */  
 
struct ExistExt : ExtBase<ServiceId,FunctionId_Exist>
 {
  typedef ExistInput InputType;
  typedef ExistOutput OutputType;
  
  bool exist;
  
  void done(const OutputType &output)
   {
    exist=!output.error_id;
   }
 };
 
} // namespace PTPSupport

namespace PTP {

/* class ClientDevice */ 

class ClientDevice : public ObjBase , public Funchor
 {
   ObjHook hook;
  
   ClientEngine engine; 
   
  private: 
  
   template <class Ext>
   static void Complete(PacketHeader *packet);
   
   void complete_Session(PacketHeader *packet);
   
   void complete_Seed(PacketHeader *packet);
   
   void complete_Len(PacketHeader *packet);
   
   static void BadServerInfo1(PtrLen<const uint8> server_info);
   
   static void BadServerInfo2(PtrLen<const uint8> server_info);
   
   static void BadServerInfo3(PtrLen<const uint8> server_info);
   
  public:
   
   // constructors
  
   explicit ClientDevice(StrLen ep_dev_name,ulen max_slots=ClientEngine::DefaultMaxSlots);
   
   virtual ~ClientDevice();
   
   // methods
   
   PacketEndpointDevice * getEPDevice() const { return engine.getEPDevice(); }
   
   void start(Packet<uint8,TransExt> packet);
   
   typedef ClientStatInfo StatInfo;
   
   void getStat(ClientStatInfo &ret);
   
   ulen getMaxOutboundInfoLen(); // always > 0 , <= MaxInfoLen
   
   ulen getMaxInboundInfoLen(); // always > 0 , <= MaxInfoLen
   
   // generic transactions
   
   template <class Ext>
   void start(Packet<uint8,Ext> packet,const typename Ext::InputType &input);
   
   template <class Ext>
   void start_format(Packet<uint8,Ext> packet,const typename Ext::InputType &input);
   
   struct FormatResult
    {
     PacketFormat format;
     bool too_short;
     
     FormatResult(NothingType) : too_short(true) {}
     
     FormatResult(PacketFormat format_) : format(format_),too_short(false) {}
     
     bool operator ! () const { return too_short; }
     
     bool noRoom() const { return format.max_data==0; }
    };
   
   template <class Ext>
   static PacketFormat GetFormat(); 
   
   template <class Ext>
   static FormatResult GetFormat(ulen max_outbound_info_len); 
   
   template <class Ext>
   FormatResult getFormat() { return GetFormat<Ext>(getMaxOutboundInfoLen()); }
   
   template <class Ext>
   PacketFormat getFormat_guarded(const char *name) 
    { 
     auto result=getFormat<Ext>();
     
     if( !result ) GuardOutboundTooShort(name);
     
     return result.format;
    }
   
   // support service
   
   void support(Packet<uint8,PTPSupport::LenExt> packet);
   
   void support(Packet<uint8,PTPSupport::SeedExt> packet);
   
   void support(Packet<uint8,PTPSupport::SessionExt> packet);
   
   FormatResult getEchoFormat() { return getFormat<PTPSupport::EchoExt>(); }
   
   void support(Packet<uint8,PTPSupport::EchoExt> packet,uint32 delay_msec);
   
   void support(Packet<uint8,PTPSupport::ErrorDescExt> packet,ServiceIdType service_id,FunctionIdType function_id,ErrorIdType error_id);
   
   void support(Packet<uint8,PTPSupport::ExistExt> packet,ServiceIdType service_id,FunctionIdType function_id);
   
   // initial interaction
   
   bool support(PacketSet<uint8> &pset,MSec timeout=DefaultTimeout);
   
   void support_guarded(MSec timeout=DefaultTimeout);
 };
 
template <class Ext>
void ClientDevice::Complete(PacketHeader *packet_)
 {
  Packet<uint8,Ext,TransExt> packet2=packet_;
     
  TransExt *trans_ext=packet2.getExt();
     
  if( TransResult result=trans_ext->result )
    {
     Packet<uint8,Ext> packet=packet2.popExt();
        
     packet.getExt()->fail(result);
        
     packet.complete();
    }
  else
    {
     PtrLen<const uint8> server_info=trans_ext->server_info;
    
     RangeGetDev dev(server_info);
        
     Result prefix;
     
     dev(prefix);
     
     if( !dev )
       {
        Packet<uint8,Ext> packet=packet2.popExt();
        
        packet.getExt()->fail(Trans_BadInboundLen1);
        
        BadServerInfo1(server_info);
        
        packet.complete();
       }
     else if( prefix.error_id )
       {
        Packet<uint8,Ext> packet=packet2.popExt();
        
        if( !dev.finish() )
          {
           packet.getExt()->fail(Trans_BadInboundLen2);
           
           BadServerInfo2(server_info);
          }
        else
          {
           packet.getExt()->error(prefix.error_id);
          }
          
        packet.complete();
       }
     else
       {
        typename Ext::OutputType output;
        
        dev(output);
        
        if( !dev.finish() )
          {
           Packet<uint8,Ext> packet=packet2.popExt();
        
           packet.getExt()->fail(Trans_BadInboundLen3);
           
           BadServerInfo3(server_info);
        
           packet.complete();
          }  
        else
          {
           Packet<uint8,Ext> packet=packet2.popExt();
           
           Ext *ext=packet.getExt();
           
           ext->setOk();
           ext->done(output);
        
           packet.complete();
          }
       }  
    }
 }
    
template <class Ext>
void ClientDevice::start(Packet<uint8,Ext> packet,const typename Ext::InputType &input)
 {
  ServiceFunction serv_func(Ext::ServiceId,Ext::FunctionId);
     
  auto len=SaveLen(serv_func,input);
     
  if( packet.checkDataLen(len) )
    {
     BufPutDev dev(packet.setDataLen(len).ptr);
        
     dev(serv_func,input);
     
     auto move_flag=Ext::GetMoveFlag(packet);
        
     Packet<uint8,Ext,TransExt> packet2=packet.template pushExt<TransExt>(move_flag);
        
     packet2.pushCompleteFunction(Complete<Ext>);
        
     start(packet2.template forgetExt<1>());
    }
  else
    {
     packet.getExt()->fail(Trans_BadDataLen);
        
     packet.complete();
    }  
 }
    
template <class Ext>
void ClientDevice::start_format(Packet<uint8,Ext> packet,const typename Ext::InputType &input)
 {
  ServiceFunction serv_func(Ext::ServiceId,Ext::FunctionId);

  BufPutDev dev(packet.getData());
        
  dev(serv_func,input);
        
  auto move_flag=Ext::GetMoveFlag(packet);
  
  Packet<uint8,Ext,TransExt> packet2=packet.template pushExt<TransExt>(move_flag);
        
  packet2.pushCompleteFunction(Complete<Ext>);
        
  start(packet2.template forgetExt<1>());
 }
 
template <class Ext>
PacketFormat ClientDevice::GetFormat()
 {
  PacketFormat ret;
     
  ret.prefix=SaveLenCounter<ServiceFunction,typename Ext::InputType>::SaveLoadLen;
  ret.suffix=0;
  ret.max_data=Ext::InputType::MaxLen;
  
  return ret;
 }
 
template <class Ext>
ClientDevice::FormatResult ClientDevice::GetFormat(ulen max_outbound_info_len)
 {
  PacketFormat ret;
     
  ret.prefix=SaveLenCounter<ServiceFunction,typename Ext::InputType>::SaveLoadLen;
  ret.suffix=0;
  
  if( max_outbound_info_len>=ret.prefix )
    { 
     ret.max_data=Min<ulen>(Ext::InputType::MaxLen,max_outbound_info_len-ret.prefix);
  
     return ret;
    }
  
  return Nothing;
 }
 
} // namespace PTP
} // namespace Net
} // namespace CCore
 
#endif
 

