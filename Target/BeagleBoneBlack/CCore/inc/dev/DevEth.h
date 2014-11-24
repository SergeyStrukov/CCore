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

#include <CCore/inc/Task.h>
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/net/EthDevice.h>
#include <CCore/inc/InstanceLock.h>
 
namespace CCore {
namespace Dev {

/* classes */

//enum EthPortMode;

class EthControl;

class EthBuf;

class EthDevice;

/* enum EthPortMode */

enum EthPortMode : unsigned
 {
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
   
   void stopTx(); // TODO
   
   void stopRx(); // TODO
 };

/* class EthBuf */

class EthBuf : NoCopy
 {
  public:
  
   EthBuf();
   
   ~EthBuf();
   
   void start();
   
   void stop();
 };

/* class EthDevice */

class EthDevice : public ObjBase , public Net::EthDevice , public Funchor  
 {
   EthBuf buf;
   
   Net::EthStatInfo stat;
   
   Net::EthProc *proc=0;
   
   EthControl control;
   
   Atomic promisc_mode;
   
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
   
  private:
   
   void tick_int();
   
   void eth_int();
   
   Function<void (void)> function_tick_int() { return FunctionOf(this,&EthDevice::tick_int); }
   
   Function<void (void)> function_eth_int() { return FunctionOf(this,&EthDevice::eth_int); }
   
   void processTick();
   
   void processTx();
   
   void processRx();
   
   void processPushTx();
   
   void work();
   
  public:
  
   EthDevice();
   
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


