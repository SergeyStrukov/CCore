/* DevEth.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_DevEth_h
#define CCore_inc_dev_DevEth_h

#include <CCore/inc/dev/DevIntHandle.h>
#include <CCore/inc/dev/DevBit.h>

#include <CCore/inc/Task.h>
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/net/EthDevice.h>
#include <CCore/inc/PacketSet.h>
#include <CCore/inc/InstanceLock.h>
 
namespace CCore {
namespace Dev {

/* classes */

//enum EthPortMode;

class EthControl;

struct EthDescData;

class EthBuf;

class EthDevice;

/* enum EthPortMode */

enum EthPortMode : unsigned
 {
  EthHalfDuplex = 0,
  EthFullDuplex = 1,
  EthGig        = 2
 };

inline EthPortMode operator | (EthPortMode a,EthPortMode b) { return EthPortMode(unsigned(a)|b); }

/* class EthControl */

class EthControl : InstanceLock<EthControl>
 {
   Net::MACAddress address1;
   Net::MACAddress address2;
 
  private:
   
   static Net::MACAddress MakeAddress(uint32 hi,uint32 lo);
  
   void connect();
   
   void enable();
   
   void reset();
   
   void prepare();
   
   void disable();
   
   void show();
   
  public:
  
   EthControl();
   
   ~EthControl();
   
   // addresses
   
   const Net::MACAddress & getAddress1() const { return address1; }
   
   const Net::MACAddress & getAddress2() const { return address2; }
   
   // port control
   
   void enablePort(EthPortMode mode);
   
   void setPort(EthPortMode mode);
   
   // MDIO
   
   bool MDIOReady();
   
   void startMDIOWrite(uint16 phy,uint16 reg,uint16 data);
   
   void startMDIORead(uint16 phy,uint16 reg);
   
   struct MDIODataAck
    {
     uint16 data;
     bool ack;
     
     MDIODataAck(uint16 data_,bool ack_) : data(data_),ack(ack_) {}
    };
   
   MDIODataAck MDIOReadData();
   
   // DMA
   
   void startTx();
   
   void startRx();
   
   void setTx(void *desc);
   
   void setRx(void *desc);
   
   void ackTx(void *desc);
   
   void ackRx(void *desc);
   
   void teardownTx();
   
   void teardownRx();
   
   bool testTxTeardown();
   
   void ackTxTeardown();
   
   bool testRxTeardown();
   
   void ackRxTeardown();
   
   void stopTx();
   
   void stopRx();
 };

/* struct EthDescData */

struct EthDescData
 {
  uint32 desc[4];
  uint8 data[Net::MaxEthFrameLen+4];
  
  // methods
  
  void setData() { desc[1]=(uint32)(void *)data; }
  
  enum RxBits : uint32
   {
    RxTeardown = Bit(27),
    RxEOQ      = Bit(28),
    RxOwn      = Bit(29),
    RxEOP      = Bit(30),
    RxSOP      = Bit(31)  
   };
  
  void prepareRx()
   {
    setData();
   }
  
  void clearRx()
   {
    desc[2]=Net::MaxEthFrameLen;
    desc[3]=RxSOP|RxEOP|RxOwn;
   }
  
  uint32 getRxStatus() const { return desc[3]; }
  
  ulen getRxLen() const { return desc[3]&Mask(11); }
  
  PtrLen<const uint8> getRxRange() const { return Range(data,getRxLen()); }
  
  enum TxBits : uint32
   {
    TxToPortEnable = Bit(20),
    TxTeardown     = Bit(27),
    TxEOQ          = Bit(28),
    TxOwn          = Bit(29),
    TxEOP          = Bit(30),
    TxSOP          = Bit(31)  
   };
  
  void prepareTx()
   {
    setData();
   }
  
  void clearTx(uint32 len) // len<2^11
   {
    desc[2]=len;
    desc[3]=TxSOP|TxEOP|TxOwn|TxToPortEnable|(1u<<16)|len;
   }

  uint32 getTxStatus() const { return desc[3]; }
  
  void setNext(EthDescData *ptr) { desc[0]=(uint32)ptr; }
  
  EthDescData * getNext() { return (EthDescData *)(desc[0]); }
 };

/* class EthBuf */

class EthBuf : NoCopy
 {
   void *mem;
   
   EthDescData *rx_list=0;
   EthDescData *rx_last=0;
   
   EthDescData *tx_list=0;
   
   EthDescData *tx_send_list=0;
   EthDescData *tx_send_last=0;
   
  private: 
   
   void freeRx(EthDescData *ptr);
   
   void freeTx(EthDescData *ptr);
   
  public:
  
   EthBuf(ulen rx_count,ulen tx_count);
   
   ~EthBuf();
   
   void start();
   
   EthDescData * getRxList() const { return rx_list; }
   
   void turnRx();
   
   EthDescData * getTxList() const { return tx_list; }
   
   bool turnTx();
   
   EthDescData * getTxSendList() const { return tx_send_list; }
   
   void completeTx();
   
   void stop();
 };

/* class EthDevice */

class EthDevice : public ObjBase , public Net::EthDevice , public Funchor  
 {
   PacketSet<uint8> pset;
 
   EthBuf buf;
   
   Net::EthStatInfo stat;
   
   Net::EthProc *proc=0;
   
   EthControl control;
   
   Net::XPoint point;
   Net::XPoint point_broadcast;
   
   enum PhyRead
    {
     PhyNone,
     PhyStatus,
     PhyExtraStatus
    };
   
   PhyRead phy_read=PhyNone;
   bool phy_link=false;
   bool phy_full_duplex=true;
   
   Atomic promisc_mode;
   
   enum TeardownFlag
    {
     TeardownRxComplete = 1,
     TeardownTxComplete = 2
    };
   
   unsigned teardown_flag=0;
   
   bool delay_rx=false;
   
   enum EventType
    {
     EventTick = 1,
     EventTx,
     EventRx,
     EventPushTx,
     EventStop,
     
     EventLim
    };
   
   MultiEvent<EventLim-1> mevent;
   
  private:
   
   void tick_int();
   
   void tx_int();
   
   void rx_int();
   
   Function<void (void)> function_tick_int() { return FunctionOf(this,&EthDevice::tick_int); }
   
   Function<void (void)> function_tx_int() { return FunctionOf(this,&EthDevice::tx_int); }
   
   Function<void (void)> function_rx_int() { return FunctionOf(this,&EthDevice::rx_int); }
   
   void processPhy();
   
   void processTick();
   
   void processTx();
   
   bool testRx(PtrLen<const uint8> data,Net::EthHeader &header);
   
   Packet<uint8,Net::EthRxExt> copyRx(PtrLen<const uint8> data,const Net::EthHeader &header);
   
   void processRx();
   
   void processPushTx();
   
   bool mustStop();
   
   void work();
   
  private: 
   
   Ticker ticker;
   
   Sem stop_sem;
   
   Mutex mutex;
   
   Net::EthStatInfo stat_shared;
   
   enum TaskFlag
    {
     TaskRunning,
     TaskStopping,
     TaskStopped
    };
   
   TaskFlag task_flag=TaskStopped;
   
  public:
  
   EthDevice(ulen rx_count=50,ulen tx_count=50);
   
   virtual ~EthDevice();
   
   // Net::EthDevice
   
   // static properties
  
   virtual Net::MACAddress getAddress();
   
   virtual PacketFormat getTxFormat();
   
   virtual PacketFormat getRxFormat();
   
   // attach/detach
   
   virtual void attach(Net::EthProc *proc);
   
   virtual void detach();
   
   // dynamic properties
   
   using StatInfo = Net::EthStatInfo ;
   
   virtual void getStat(StatInfo &ret);
   
   virtual bool getPromiscMode();
   
   virtual void setPromiscMode(bool enable);
   
   // outbound
   
   virtual void signalOutbound();
   
   // start/stop
   
   void startTask(TaskPriority priority,ulen stack_len=DefaultStackLen);
   
   void stopTask();
   
   class StartStop : NoCopy
    {
      EthDevice &obj;
      
     public: 
     
      template <class ... TT>
      StartStop(EthDevice &obj_,TT ... tt) : obj(obj_) { obj_.startTask(tt...); }
      
      ~StartStop() { obj.stopTask(); }
    };
 };

} // namespace Dev
} // namespace CCore
 
#endif


