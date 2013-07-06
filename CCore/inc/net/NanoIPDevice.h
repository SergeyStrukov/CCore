/* NanoIPDevice.h */ 
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

#ifndef CCore_inc_net_NanoIPDevice_h
#define CCore_inc_net_NanoIPDevice_h

#include <CCore/inc/ObjHost.h>
#include <CCore/inc/PacketPool.h>
#include <CCore/inc/CancelPacketList.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/List.h>
#include <CCore/inc/task/TaskEvent.h>

#include <CCore/inc/net/EthDevice.h>
#include <CCore/inc/net/UDPoint.h>

namespace CCore {
namespace Net {

/* types */ 

typedef uint16 ICMPEchoNumber;

typedef Function<void (ICMPEchoNumber num)> ICMPReplyFunction;

typedef Function<void (void)> IPTickFunction;

typedef Function<void (Packet<uint8> packet,PtrLen<const uint8> data,UDPoint udpoint)> UDPFunction;

/* classes */ 

//enum IPEvent;

struct NetEvent;

class IPStatInfo;

struct IPTxExt;

struct UDPTxExt;

class ARPTable;

class ARPending;

class TxPrepareList;

class TxSendList;

class ICMPEchoEndpoint;

class ICMPEchoList;

class IPTickEndpoint;

class IPTickList;
  
class UDPEndpoint;

class UDPList;

class NanoIPDevice;

class NanoUDPEndpointDevice;

class NanoUDPMultipointDevice;

/* enum IPEvent */ 

enum IPEvent : uint8
 {
  IPTx_ARP,
  IPTx_IP,
  IPTx_UDP,
  
  IPRx_ARP,
  IPRx_IP,
  IPRx_UDP,
  
  IPTx_BadPacketLen,
  IPTx_TimeoutDrop,
  IPTx_ARP_Missing,
  IPTx_ARP_Drop,
  IPTx_Drop,
  
  IPRx_BadPacket,
  IPRx_Drop,
  IPRx_UDP_NoPort,
  
  IPEventLim
 };
 
const char * GetTextDesc(IPEvent ev); 

/* struct NetEvent */

struct NetEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint8 ip_event;
  
  void init(EventTimeType time_,EventIdType id_,IPEvent ip_event_)
   {
    time=time_; 
    id=id_;
    
    ip_event=ip_event_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<NetEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<NetEvent *>(ptr)->id); }
  
  static void * Offset_ip_event(void *ptr) { return &(static_cast<NetEvent *>(ptr)->ip_event); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class IPStatInfo */

class IPStatInfo : public Counters<IPEvent,IPEventLim> 
 {
  public:

   void count(IPEvent ip_event)
    {
     TaskEventHost.addProto<NetEvent>(ip_event);
    
     Counters<IPEvent,IPEventLim>::count(ip_event);
    }
   
   void count(IPEvent ip_event,ulen cnt)
    {
     if( cnt ) TaskEventHost.addProto<NetEvent>(ip_event);
    
     Counters<IPEvent,IPEventLim>::count(ip_event,cnt);
    }
 };

/* struct IPTxExt */ 

struct IPTxExt
 {
  IPAddress dst;
  IProto proto;
  
  // constructors
  
  IPTxExt() : dst(),proto() {}
  
  IPTxExt(IPAddress dst_,IProto proto_) : dst(dst_),proto(proto_) {}
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"-> #; #;",dst,proto);
   }
 };
 
/* struct UDPTxExt */ 

struct UDPTxExt 
 {
  IPAddress dst;
  UDPort dst_port;
  UDPort src_port;
  bool do_checksum;
  
  // constructors
  
  UDPTxExt() : dst(),dst_port(),src_port(),do_checksum()  {}
  
  UDPTxExt(IPAddress dst_,UDPort dst_port_,UDPort src_port_,bool do_checksum_) 
   : dst(dst_),dst_port(dst_port_),src_port(src_port_),do_checksum(do_checksum_) {}
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#; -> #;:#;",src_port,dst,dst_port);
   }
 };
 
/* class ARPTable */ 

class ARPTable : NoCopy
 {
   enum TickResult
    {
     Ok,
     Alert,
     Kill
    }; 
  
   struct TimeGuard
    {
     static const unsigned LifeTime    = 10*60*InboundTicksPerSec ; // 10 min
     static const unsigned AlertTime   = LifeTime/10 ;
     static const unsigned AlertPeriod = 8 ;                        // ticks, 0.8 sec
    
     unsigned ticks;
    
     TimeGuard() { reset(); }
     
     void reset() { ticks=LifeTime; }
      
     TickResult tick(bool noalert);
    };
 
   struct Entry : MemBase_nocopy
    {
     TreeLink<Entry,uint32> tlink;
     DLink<Entry> dlink;
     
     MACAddress mac;
     TimeGuard time_guard;
     
     explicit Entry(MACAddress mac_) : mac(mac_) {}
     
     void refresh(MACAddress mac);
     
     IPAddress getIP() const { return IPAddress(tlink.key); }
    };
    
   typedef TreeLink<Entry,uint32>::RadixAlgo<&Entry::tlink> TreeAlgo;
   typedef DLink<Entry>::CircularAlgo<&Entry::dlink> ListAlgo;
   
   TreeAlgo::Root root;
   ListAlgo::Top list;
 
  public:
  
   ARPTable();
   
   ~ARPTable();
   
   void clear();
   
   void add(IPAddress ip,MACAddress mac);
   
   bool del(IPAddress ip);
   
   bool find(IPAddress ip,MACAddress &mac);
   
   struct TickAction
    {
     IPAddress ip;
     bool resend;
     
     TickAction() : ip(),resend(false) {}
     
     TickAction(IPAddress ip_) : ip(ip_),resend(true) {}
    };
   
   TickAction tick();
 };
 
/* class ARPending */ 

class ARPending : NoCopy
 {
   CancelPacketList canlist;

   struct Entry : MemBase_nocopy
    {
     static const unsigned LifeTime = 10*InboundTicksPerSec ; // 10 sec
     
     TreeLink<Entry,uint32> tlink;
     DLink<Entry> dlink;
     
     PacketList list;
     unsigned ticks;
     
     Entry(CancelPacketList &canlist,Packet<uint8,EthTxExt> packet);
     
     ~Entry() {}
     
     unsigned clear(CancelPacketList &canlist);
     
     bool tick();
     
     void add(CancelPacketList &canlist,Packet<uint8,EthTxExt> packet) { canlist.put(list,packet); }
     
     void del(CancelPacketList &canlist,PacketList &dst) { canlist.get(list,dst); }
     
     IPAddress getIP() const { return IPAddress(tlink.key); }
    };
    
   typedef TreeLink<Entry,uint32>::RadixAlgo<&Entry::tlink> TreeAlgo;
   typedef DLink<Entry>::CircularAlgo<&Entry::dlink> ListAlgo;
   
   TreeAlgo::Root root; 
   ListAlgo::Top list;
 
  public:
  
   ARPending();
   
   ~ARPending();
   
   typedef CancelPacketList::StatInfo StatInfo;
   
   void getStat(StatInfo &ret) { canlist.getStat(ret); }
   
   unsigned clear();
   
   enum AddResult
    {
     Ok,
     Request,
     Drop
    };
   
   AddResult add(IPAddress ip,Packet<uint8,EthTxExt> packet);
   
   bool del(IPAddress ip,PacketList &dst);
   
   struct TickAction
    {
     IPAddress ip;
     bool resend;
     unsigned drop;
     
     TickAction() : ip(),resend(false),drop(0) {}
     
     TickAction(IPAddress ip_) : ip(ip_),resend(true),drop(0) {}
     
     TickAction(unsigned drop_) : resend(false),drop(drop_) {}
    };
   
   TickAction tick();
 };
 
/* class TxPrepareList */ 

class TxPrepareList : public Funchor_nocopy
 {
  public:
  
   typedef CancelPacketList::StatInfo StatInfo;
  
  private:
  
   Mutex mutex;
   
   bool enable_flag;
   PacketList list;
   
   StatInfo stat;
   
  private: 
   
   void cancel(PacketHeader *packet);
   
   PacketFunction function_cancel() { return FunctionOf(this,&TxPrepareList::cancel); }
   
   void get(PacketList &dst);
   
  public:
  
   TxPrepareList();
   
   ~TxPrepareList();
   
   void getStat(StatInfo &ret);
   
   void enable();
   
   void disable();
   
   bool put(PacketHeader *packet,PacketFunction function);
   
   template <class P>
   bool put(P packet,PacketFunction function) { return put(GetPacketHeader(packet),function); }
   
   void prepare();
 };
 
/* class TxSendList */   
  
class TxSendList : NoCopy
 {
   static const ulen LifeTime = 10*InboundTicksPerSec ; // 10 sec
 
   CancelPacketList canlist;
   
   PacketList list[LifeTime];
   
   ulen put_ind;
   ulen get_ind;
   
  private:
  
   static ulen NextInd(ulen ind) { return (ind+1<LifeTime)?ind+1:0; }
   
  public:
  
   TxSendList();
   
   ~TxSendList();
   
   typedef CancelPacketList::StatInfo StatInfo;
   
   void getStat(CancelPacketList::StatInfo &ret) { canlist.getStat(ret); }
   
   unsigned clear();
   
   void put(Packet<uint8,EthTxExt> packet);
   
   Packet<uint8,EthTxExt> get();
   
   unsigned tick();
 };
 
/* class ICMPEchoEndpoint */ 
 
class ICMPEchoEndpoint : NoCopy
 {
   enum { DataLen = 32 };
 
   ObjHook hook;
   
   NanoIPDevice *dev;
   
   IPAddress dst;
   uint16 id;
   uint16 num;
   uint8 data[DataLen];
   
   ICMPReplyFunction reply_function;
   
   AntiSem asem;
   
   TreeLink<ICMPEchoEndpoint,uint16> link;
   
  private: 
   
   void reply(const ICMPEcho &echo,PtrLen<const uint8> echo_data);
   
   friend class ICMPEchoList;
   
  public:
  
   ICMPEchoEndpoint(StrLen ip_dev_name,IPAddress dst,ICMPReplyFunction reply_function);
   
   ~ICMPEchoEndpoint();
   
   ICMPEchoNumber send();
 };
 
/* class ICMPEchoList */  

class ICMPEchoList : NoCopy
 {
   Mutex mutex;
 
   typedef TreeLink<ICMPEchoEndpoint,uint16>::RadixAlgo<&ICMPEchoEndpoint::link> Algo;
   
   Algo::Root root;
   
   uint16 next_id;
   
  private: 
   
   ICMPEchoEndpoint * find(uint16 id);
   
  public:
  
   ICMPEchoList();
   
   ~ICMPEchoList();
   
   void attach(ICMPEchoEndpoint *endpoint);
   
   void detach(ICMPEchoEndpoint *endpoint);
   
   class Hook : NoCopy
    {
      ICMPEchoEndpoint *endpoint;
      
     public:
     
      Hook(ICMPEchoList &list,uint16 id) 
       { 
        endpoint=list.find(id); 
       }
      
      ~Hook() 
       { 
        if( endpoint ) endpoint->asem.dec(); 
       }
      
      void reply(const ICMPEcho &echo,PtrLen<const uint8> echo_data)
       {
        if( endpoint ) endpoint->reply(echo,echo_data);
       }
    };
 };
 
/* class IPTickEndpoint */ 

class IPTickEndpoint : NoCopy
 {
   ObjHook hook;
   
   NanoIPDevice *dev;
   
   IPTickFunction tick_function;
   
   AntiSem asem;
   
   DLink<IPTickEndpoint> link;
   
   friend class IPTickList;
   
  public: 
  
   IPTickEndpoint(StrLen ip_dev_name,IPTickFunction tick_function);
   
   ~IPTickEndpoint();
 };
 
/* class IPTickList */ 

class IPTickList : NoCopy
 {
   Mutex mutex;
   
   typedef DLink<IPTickEndpoint>::CircularAlgo<&IPTickEndpoint::link> Algo;
   
   Algo::Top list;
   
   IPTickEndpoint *guard;
   
  private: 
   
   IPTickEndpoint * take();
   
  public: 
  
   IPTickList();
   
   ~IPTickList();
   
   void attach(IPTickEndpoint *endpoint);
   
   void detach(IPTickEndpoint *endpoint);
   
   void tick();
   
   class Hook : NoCopy
    {
      IPTickEndpoint *endpoint;
      
     public:
     
      explicit Hook(IPTickList &list) { endpoint=list.take(); }
      
      bool operator ! () const { return !endpoint; }
      
      ~Hook() { if( endpoint ) endpoint->asem.dec(); }
      
      void tick() { if( endpoint ) endpoint->tick_function(); }
    };
 };
 
/* class UDPEndpoint */ 

class UDPEndpoint : NoCopy
 {
   ObjHook hook;
   
   NanoIPDevice *dev;
   
   UDPort port;
   bool do_checksum;
   
   UDPFunction rx_function;
   
   AntiSem asem;
   
   TreeLink<UDPEndpoint,UDPort> link;
   
  private:
  
   IPEvent inbound(Packet<uint8> packet,PtrLen<const uint8> data,const IPHeader &iph,const UDPHeader &udph);
   
   friend class UDPList;
   
  public:
  
   UDPEndpoint(StrLen ip_dev_name,UDPort port,bool do_checksum,UDPFunction rx_function);
   
   ~UDPEndpoint();
   
   ulen getMaxInboundLen() const;
   
   PacketFormat getUDPTxFormat() const;
   
   void send(Packet<uint8> packet,UDPoint dst);
 };
 
/* class UDPList */ 

class UDPList : NoCopy
 {
   Mutex mutex;
   
   typedef TreeLink<UDPEndpoint,UDPort>::RadixAlgo<&UDPEndpoint::link> Algo;
   
   Algo::Root root;
 
  private:
  
   UDPEndpoint * find(UDPort port);
  
  public:
  
   UDPList();
   
   ~UDPList();
   
   void attach(UDPEndpoint *endpoint);
   
   void detach(UDPEndpoint *endpoint);
   
   class Hook : NoCopy
    {
      UDPEndpoint *endpoint;
      
     public:
     
      Hook(UDPList &list,UDPort port) 
       { 
        endpoint=list.find(port); 
       }
      
      ~Hook() 
       { 
        if( endpoint ) endpoint->asem.dec(); 
       }
      
      IPEvent inbound(Packet<uint8> packet,PtrLen<const uint8> data,const IPHeader &iph,const UDPHeader &udph)
       {
        if( endpoint ) 
          return endpoint->inbound(packet,data,iph,udph);
        else
          return IPRx_UDP_NoPort;  
       }
    };
 };
 
/* class NanoIPDevice */ 

class NanoIPDevice : public ObjBase , public Funchor , EthProc
 {
   ObjHook hook;
 
   EthDevice *eth;
   
   PacketFormat tx_format;
   PacketFormat rx_format;
   
   PacketFormat ip_tx_format;
   PacketFormat udp_tx_format;
   PacketFormat ip_rx_format;
   PacketFormat udp_rx_format;
   
   MACAddress mac_address;
   IPAddress address;
   IPAddress net_mask;
   
   IPStatInfo stat;
   
   ARPTable arp_table;
   ARPending arp_pending;
   
   TxPrepareList prepare_list;
   TxSendList send_list;
   
   ICMPEchoList echo_list;
   IPTickList tick_list;
   UDPList udp_list;
   
   Mutex mutex;
   
   IPStatInfo stat_toget;
   
  private:
  
   virtual void start();
   
   virtual void linkUp();
   
   virtual void linkDown();
   
   virtual void tick();
   
   virtual void inbound(Packet<uint8,EthRxExt> packet);
   
   virtual void prepareOutbound();
   
   virtual Packet<uint8,EthTxExt> outbound();
   
   virtual void stop();
   
  private: 
  
   template <class T,class ... SS>
   static Packet<uint8,T> TryGetPacket(SS && ... ss)
    {
     Packet<uint8> packet=TryAllocPacket<uint8>();
  
     if( !packet ) return Nothing;
     
     Packet<uint8,T> packet2=packet.pushExt<T>( std::forward<SS>(ss)... );
  
     packet2.pushCompleteFunction(DropPacketExt<uint8,T>);
     
     return packet2;
    }
  
   // arp
  
   void send_arp(MACAddress dst,const ARPacket &arp);
  
   void send_arp(IPAddress dst);
   
   void send_arp();
  
   void send_arp_reply(IPAddress dst_ip,MACAddress dst_mac);
   
   void arp_done(IPAddress ip,MACAddress mac);
   
   IPEvent inbound_arp(Packet<uint8,EthRxExt> packet);
   
   // inbound ip
   
   IPEvent inbound_icmp(const IPHeader &iph,PtrLen<uint8> body);
   
   IPEvent inbound_udp(Packet<uint8,EthRxExt> packet,const IPHeader &iph,PtrLen<uint8> body);
   
   IPEvent inbound_ip(Packet<uint8,EthRxExt> packet);
   
   // outbound ip
   
   void prepare_ip(PacketHeader *packet);
   
   PacketFunction function_prepare_ip() { return FunctionOf(this,&NanoIPDevice::prepare_ip); }
   
   void prepare_udp(PacketHeader *packet);
   
   PacketFunction function_prepare_udp() { return FunctionOf(this,&NanoIPDevice::prepare_udp); }
   
  public:
   
   // constructors
 
   NanoIPDevice(StrLen eth_dev_name,IPAddress address,IPAddress net_mask);
   
   virtual ~NanoIPDevice();
   
   // properties
   
   EthDevice * getEthDevice() const { return eth; }
   
   IPAddress getAddress() const { return address; }
   
   IPAddress getNetMask() const { return net_mask; }
   
   bool sameNet(IPAddress ip) const { return ip.sameNet(address,net_mask); }
   
   PacketFormat getTxFormat() const { return ip_tx_format; }
   
   PacketFormat getUDPTxFormat() const { return udp_tx_format; }
   
   PacketFormat getRxFormat() const { return ip_rx_format; }
   
   PacketFormat getUDPRxFormat() const { return udp_rx_format; }
   
   // stat
   
   typedef IPStatInfo StatInfo;
   
   void getStat(IPStatInfo &ret);
   
   void getStat_arp(ARPending::StatInfo &ret) { arp_pending.getStat(ret); }
   
   void getStat_prepare(TxPrepareList::StatInfo &ret) { prepare_list.getStat(ret); }
   
   void getStat_send(TxSendList::StatInfo &ret) { send_list.getStat(ret); }
   
   // send
   
   template <class P>
   bool send_prepare(P packet,PacketFunction function) 
    { 
     if( prepare_list.put(packet,function) )
       {
        eth->signalOutbound();
        
        return true;
       }
     else
       {
        return false;
       }
    }
    
   template <class P>
   void send_prepare_or_complete(P packet,PacketFunction function) 
    { 
     if( prepare_list.put(packet,function) )
       {
        eth->signalOutbound();
       }
     else
       {
        packet.complete();
       }
    }
    
   void send(Packet<uint8,IPTxExt> packet);
   
   void send_udp(Packet<uint8,UDPTxExt> packet);
   
   void send_icmp_echo(IPAddress dst,const ICMPEcho &echo,PtrLen<const uint8> data);
   
   // attach/detach
   
   void attach(ICMPEchoEndpoint *endpoint) { echo_list.attach(endpoint); }
   
   void detach(ICMPEchoEndpoint *endpoint) { echo_list.detach(endpoint); }
   
   void attach(IPTickEndpoint *endpoint) { tick_list.attach(endpoint); }
   
   void detach(IPTickEndpoint *endpoint) { tick_list.detach(endpoint); }
   
   void attach(UDPEndpoint *endpoint) { udp_list.attach(endpoint); }
   
   void detach(UDPEndpoint *endpoint) { udp_list.detach(endpoint); }
 };
 
/* class NanoUDPEndpointDevice */  
 
class NanoUDPEndpointDevice : public ObjBase , public PacketEndpointDevice
 {
   class Engine : public Funchor_nocopy
    {
      UDPoint dst;

      AntiSem asem;
      Mutex mutex;
   
      InboundProc *proc;
      
     private: 
     
      InboundProc * getProc();
     
      void inbound(Packet<uint8> packet,PtrLen<const uint8> data,UDPoint udpoint);
     
      void tick();
      
     public:
     
      explicit Engine(UDPoint dst);
      
      ~Engine();
      
      UDPoint getDst() const { return dst; }
     
      UDPFunction function_inbound() { return FunctionOf(this,&Engine::inbound); }
      
      IPTickFunction function_tick() { return FunctionOf(this,&Engine::tick); }
      
      void attach(InboundProc *proc);
      
      void detach();
    };
 
   Engine engine;
   
   UDPEndpoint udp_endpoint;
   IPTickEndpoint tick_endpoint;
 
  public:
  
   NanoUDPEndpointDevice(StrLen ip_dev_name,UDPort udport,bool do_checksum,UDPoint dst);
   
   virtual ~NanoUDPEndpointDevice();
   
   // PacketEndpointDevice 
   
   virtual PacketFormat getOutboundFormat();
   
   virtual void outbound(Packet<uint8> packet);
   
   virtual ulen getMaxInboundLen();
  
   virtual void attach(InboundProc *proc);
   
   virtual void detach();
 };
 
/* class NanoUDPMultipointDevice */ 

class NanoUDPMultipointDevice : public ObjBase , public PacketMultipointDevice
 {
   class Engine : public Funchor_nocopy
    {
      AntiSem asem;
      Mutex mutex;
   
      InboundProc *proc;
      
     private: 
     
      InboundProc * getProc();
     
      void inbound(Packet<uint8> packet,PtrLen<const uint8> data,UDPoint udpoint);
     
      void tick();
      
     public:
     
      Engine();
      
      ~Engine();
      
      UDPFunction function_inbound() { return FunctionOf(this,&Engine::inbound); }
      
      IPTickFunction function_tick() { return FunctionOf(this,&Engine::tick); }
      
      void attach(InboundProc *proc);
      
      void detach();
    };
    
   Engine engine;
   
   UDPEndpoint udp_endpoint;
   IPTickEndpoint tick_endpoint;
   
  public:
  
   NanoUDPMultipointDevice(StrLen ip_dev_name,UDPort udport,bool do_checksum);
   
   virtual ~NanoUDPMultipointDevice();
   
   // PacketMultipointDevice
   
   virtual StrLen toText(XPoint point,PtrLen<char> buf);
   
   virtual PacketFormat getOutboundFormat();
   
   virtual void outbound(XPoint point,Packet<uint8> packet);
   
   virtual ulen getMaxInboundLen();
   
   virtual void attach(InboundProc *proc);
   
   virtual void detach();
 };
 
} // namespace Net
} // namespace CCore
 
#endif
 

