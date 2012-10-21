/* VIA_Rhine_III.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_driver_VIA_Rhine_III_h
#define CCore_inc_driver_VIA_Rhine_III_h

#include <CCore/inc/ObjHost.h>
#include <CCore/inc/PacketSet.h>

#include <CCore/inc/net/EthDevice.h>

#include <CCore/inc/pci/PCIBusRW.h>

namespace Driver {

/* using */ 

using namespace CCore;
using namespace CCore::Dev;
using namespace CCore::Net;

/* namespace VIA_Rhine_III */ 

namespace VIA_Rhine_III {

/* VIA_Rhine_III.desc -> VIA_Rhine_III.gen.h */ 

#include <CCore/inc/driver/VIA_Rhine_III.gen.h>

/* types */  

typedef unsigned LinkStatus;
   
/* consts */ 

 // LinkStatus Bits
 
enum LinkStatusBits : LinkStatus
 {
  LinkStatus_NoLink  = 0x01,
  LinkStatus_Duplex  = 0x02,
  LinkStatus_Speed10 = 0x04
 };
 
 // PCI
 
const uint32 VendorId   = 0x1106 ; 
const uint32 DeviceId   = 0x3106 ;
const uint32 RevisionId = 0x008B ;

 //
 // Bar[0] IO
 // Bar[1] Mem
 //
 // Both map 256 byte register space.
 //
 // Bus master.
 //
 
 // MII
 
const unsigned MIIWait   = 1000 ; // usec
const unsigned ResetWait = 100  ; // msec

 // Desc
 
const AddressType RxDescLen = 32 ;
const AddressType TxDescLen = 32 ;

/* classes */ 

//enum IntEvent;

class DeviceControl;

class DeviceEngine;

class DeviceImp;

class Device;

/* enum IntEvent */ 

enum IntEvent
 {
  IntSRC,
  IntRX,
  IntTX,
  IntGEN,
  IntOther,
 
  IntEventLim
 };
 
const char * GetTextDesc(IntEvent ev); 
 
/* class DeviceControl : NOT LOCKED */  

class DeviceControl : NoCopy
 {
   PCIBus::IntConnector connector;
   
   PCIBus::AddressMap address_map;
   
   PCIBus::CfgRW cfg;
   
   PCIBus::CfgBar<PCIBus::CfgRW &> cfg_reg;
   PCIRegBar<PCIBus::CfgRW &> pci_reg;
   
   DevRegBar<PCIBus::MemRW> dev_reg;
   
  public:
  
   DeviceControl(const PCIBus::DeviceInfo &info,PCIBus::AddressMap address_map);
  
   ~DeviceControl();
   
   PCIBus::AddressMap getAddressMap() const { return address_map; }
   
   void enable_pci();
   void mode_pci();
   void enable_pci_busmaster();
   void stop_pci();
   
   void init_int();
   void enable_int();
   void enable_rtx_int();
   void disable_int();
   
   struct IntStatus
    {
     Type_ISR isr;
     Type_MISR misr;
     
     IntStatus(Type_ISR isr_,Type_MISR misr_) : isr(isr_),misr(misr_) {}
    };
   
   IntStatus get_int();
   IntStatus clear_int();
   void delay_int(Type_ISR isr);
   
   void setup_int_handler(Function<void (void)> handle_int);
   void cleanup_int_handler();
   
   void enable_txpoll();
   
   void enable_mmio();
   void reload_eeprom();
   
   void set_tx_threshold(Field_TCR_RTFT value);
   void set_rx_threshold(Field_RCR_RRFT value);
   void set_dma_length(Field_BCR_DMAL value);
   
   void soft_reset();
   void wol_reset();
   
   void enable_duplex();
   void disable_duplex();
   
   LinkStatus check_link();
   
   void set_promiscuous();
   void set_all_multicast();
   void enable_promiscuous();
   void disable_promiscuous();
   
   MACAddress get_MAC();
   
   void cfg_device();
   void start_device(LinkStatus link_status);
   void stop_device();
   
   void init_flow_control();
   void flow_control(unsigned rx_done);
   
   void mii_disable_auto_poll();
   void mii_enable_auto_poll();
   uint16 mii_read(uint8 address);
   void mii_write(uint8 address,uint16 value);
   
   class MIIRW;
   class MII;
   
   void mii_set_auto_on();
   void mii_set_auto_off();
   void mii_set_mode(); 
   
   LinkStatus check_flow_control();
   
   void setRD(AddressType ptr);
   void setTD(AddressType ptr);
 };
 
/* class DeviceEngine */ 

class DeviceEngine : public Funchor_nocopy
 {
   DeviceControl dc;
 
   static const Field_TCR_RTFT TxThreshold = TCR_RTFT_Thresh128 ;
   static const Field_RCR_RRFT RxThreshold = RCR_RRFT_Thresh32  ;
   static const Field_BCR_DMAL DMALength   = BCR_DMAL_DMAL8     ;
   
   static const ulen TxCount       =   64 ;
   static const ulen RxCount       =   64 ;
   static const ulen PacketLen     = 1540 ; // align(4), < 2048
   static const ulen MinPacketLen  =   60 ;
   
   MACAddress address;
   
   void *ring_mem;

   AddressType rx_ring;
   AddressType tx_ring;
   
   uint8 * rx_buf_ring;
   uint8 * tx_buf_ring;
   
   ulen rx_ind;
   ulen tx_ind;
   ulen txdone_ind;
   ulen tx_active;
   
   enum EventId
    {
     Event_Stop = 1,
     Event_Rx,
     Event_Tx,
     Event_Outbound,
     Event_Tick,
     Event_Link,

     Event_Lim
    };
   
   MultiEvent<Event_Lim-1> mevent;
   
   Counters<IntEvent,IntEventLim> int_count;
   
   LinkStatus link_status;
   
   Ticker ticker; 
   TimedTrigger outbound_trigger;
   
   Sem stop_sem;
   
  private:
  
   static void InitRxDesc(AddressType desc,PCIBus::AddressMap address_map,AddressType buf,ulen buf_len,AddressType next);
   static void InitTxDesc(AddressType desc,PCIBus::AddressMap address_map,AddressType buf,AddressType next);
  
   void init_ring();
 
   void handle_int();
   
   Function<void (void)> function_handle_int() { return FunctionOf(this,&DeviceEngine::handle_int); }
   
   static ulen NextRxInd(ulen ind) { return (ind<RxCount-1)?ind+1:0; }
   static ulen NextTxInd(ulen ind) { return (ind<TxCount-1)?ind+1:0; }
   
   AddressType rx_desc(ulen ind) { return rx_ring+ind*RxDescLen; }
   AddressType tx_desc(ulen ind) { return tx_ring+ind*TxDescLen; }
   
   uint8 * rx_buf(ulen ind) { return rx_buf_ring+ind*PacketLen; }
   uint8 * tx_buf(ulen ind) { return tx_buf_ring+ind*PacketLen; }
   
   void handle_rx();
   void handle_tx();
   void pump_tx();
   
   struct LinkStatusUpdate
    {
     LinkStatus status;
     LinkStatus change;
     
     operator LinkStatus() const { return change; }
    };
   
   LinkStatusUpdate getLinkStatus();
   
   void handle_link();
   
  protected:
  
   // inbound
   
   struct InboundStatus
    {
     Type_RxDescStatus status;
     
     InboundStatus(Type_RxDescStatus status_) : status(status_) {}
     
     ulen getPacketLen() const { return status.get_Len(); } // with CRC
     
     bool isBroadcast() const { return status.maskbit(RxDescStatus_BAR); }
     
     bool isMulticast() const { return status.maskbit(RxDescStatus_MAR); }
    };
  
   virtual void inbound_packet(uint8 *buf,InboundStatus status);
   
   virtual void inbound_error(InboundStatus status);
   
   // outbound
   
   struct OutboundStatus
    {
     Type_TxDescStatus status;
     
     OutboundStatus(Type_TxDescStatus status_) : status(status_) {}
     
     bool isError() const { return status.maskbit(TxDescStatus_ERROR); }
    };
    
   virtual void prepareOutbound(); 
  
   virtual ulen get_outbound_packet(uint8 *buf,ulen buf_len);
   
   virtual void outbound_done(OutboundStatus status,ulen len);
   
   // link
   
   virtual void linkUp();
   
   virtual void linkDown();
   
   // tick
   
   virtual void tick();
   
   // task
   
   virtual void start();
   
   virtual void stop();
   
   void entry();
   
   Function<void (void)> function_entry() { return FunctionOf(this,&DeviceEngine::entry); }
   
  public:
  
   DeviceEngine(const PCIBus::DeviceInfo &info,PCIBus::AddressMap address_map);
   
   ~DeviceEngine();
   
   void test();
   
   MACAddress getAddress() const { return address; }
   
   void do_startTask(TaskPriority priority,ulen stack_len);
   
   void do_stopTask();
   
   void signalOutbound() { outbound_trigger.trigger(); }
  
   void getIntCount(Counters<IntEvent,IntEventLim> &ret);
   
   void enable_promiscuous();
   
   void disable_promiscuous();
 };

/* struct PacketEvent */

struct PacketEvent
 {
  EventTimeType time;
  EventIdType id;
  
  enum Type
   {
    RxBegin,
    RxEnd,
    TxBegin,
    TxEnd
   };
  
  uint8 type;
  
  void init(EventTimeType time_,EventIdType id_,Type type_)
   {
    time=time_;
    id=id_;
    
    type=type_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<PacketEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<PacketEvent *>(ptr)->id); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<PacketEvent *>(ptr)->type); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };
 
/* class DeviceImp */ 

class DeviceImp : public DeviceEngine
 {
   static const ulen MaxRxPackets = 500 ;
 
   EthStatInfo stat;
   bool has_link;
   
   PacketSet<uint8> pset;
   
   Mutex mutex;
   
   enum RunFlag
    {
     Running,
     Stopping,
     Stopped
    };
   
   EthProc *proc;
   RunFlag run_flag;
   bool promisc;
   
   EthStatInfo stat_toget;
   
  private: 
 
   // inbound
   
   virtual void inbound_packet(uint8 *buf,InboundStatus status);
   
   virtual void inbound_error(InboundStatus status);
   
   // outbound
   
   virtual void prepareOutbound(); 
  
   virtual ulen get_outbound_packet(uint8 *buf,ulen buf_len);
   
   virtual void outbound_done(OutboundStatus status,ulen len);
   
   // link
   
   virtual void linkUp();
   
   virtual void linkDown();
   
   // tick
   
   virtual void tick();
   
   // task
   
   virtual void start();
   
   virtual void stop();
   
  public:
  
   DeviceImp(const PCIBus::DeviceInfo &info,PCIBus::AddressMap address_map);
   
   ~DeviceImp();
   
   // static properties
 
   PacketFormat getTxFormat();
  
   PacketFormat getRxFormat();
  
   // attach/detach
  
   void attach(EthProc *proc);
  
   void detach();
  
   // dynamic properties
  
   void getStat(EthStatInfo &ret);
  
   bool getPromiscMode();
  
   void setPromiscMode(bool enable);
  
   // start/stop
  
   void startTask(TaskPriority priority,ulen stack_len);
  
   void stopTask();
 };
 
/* class Device */ 

class Device : public ObjBase , public EthDevice
 {
   DeviceImp dev;
 
  public:
  
   Device(const PCIBus::DeviceInfo &info,PCIBus::AddressMap address_map);
   
   virtual ~Device();
   
   void getIntCount(Counters<IntEvent,IntEventLim> &ret); 
   
   void test() { dev.test(); }
   
   // static properties
 
   virtual MACAddress getAddress();
  
   virtual PacketFormat getTxFormat();
  
   virtual PacketFormat getRxFormat();
  
   // attach/detach
  
   virtual void attach(EthProc *proc);
  
   virtual void detach();
  
   // dynamic properties
  
   virtual void getStat(EthStatInfo &ret);
  
   virtual bool getPromiscMode();
  
   virtual void setPromiscMode(bool enable);
   
   // outbound
  
   virtual void signalOutbound();
  
   // start/stop
  
   void startTask(TaskPriority priority,ulen stack_len=DefaultStackLen);
  
   void stopTask();
   
   class StartStop : NoCopy
    {
      Device &obj;
      
     public: 
     
      template <class ... TT>
      StartStop(Device &obj_,TT ... tt) : obj(obj_) { obj_.startTask(tt...); }
      
      ~StartStop() { obj.stopTask(); }
    };
 };
 
} // namespace VIA_Rhine_III
} // namespace Driver
 
#endif
