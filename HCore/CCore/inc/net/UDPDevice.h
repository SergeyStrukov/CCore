/* UDPDevice.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_net_UDPDevice_h
#define CCore_inc_net_UDPDevice_h

#include <CCore/inc/ObjHost.h>
#include <CCore/inc/StartStop.h>
#include <CCore/inc/Counters.h>
#include <CCore/inc/PacketSet.h>
 
#include <CCore/inc/sys/SysNet.h> 
 
#include <CCore/inc/net/PacketEndpointDevice.h>

namespace CCore {
namespace Net {

/* functions */

void UDPDeviceExitRunningAbort();

void UDPDeviceAttachedAbort();

void UDPDeviceDetachRunningAbort();

void UDPDeviceWaitAbort();

void GuardUDPDeviceIsRunning(ExceptionType ex,const char *name);

void GuardUDPDeviceIsAttached();

/* classes */ 

class UDPInboundPackets;

class UDPSocket;

template <class T> class UDPDevice;

struct UDPEndpointDeviceBase;

class UDPEndpointDevice;

struct UDPMultipointDeviceBase;

class UDPMultipointDevice;

/* class UDPInboundPackets */ 

class UDPInboundPackets : NoCopy
 {
   PacketSet<uint8> pset;
   TimeScope time_scope;
  
  public:
   
   // constructors
  
   explicit UDPInboundPackets(ulen max_packets);
   
   ~UDPInboundPackets();
   
   // methods
   
   Packet<uint8> getPacket();
   
   void start();
   
   TimeScope getScope() const { return time_scope; }
   
   bool nextScope() { return time_scope.nextScope_skip(); } 
 };

/* class UDPSocket */

class UDPSocket : NoCopy
 {
   Sys::UDPSocket sys_sock;
   
  public:
   
   // constructors
   
   explicit UDPSocket(UDPort udport);
   
   ~UDPSocket();
   
   // methods
   
   bool outbound(UDPoint dst,PtrLen<const uint8> data) { return !sys_sock.outbound(dst,data); }
   
   Sys::WaitResult wait_inbound(TimeScope time_scope) { return sys_sock.wait_in(time_scope); }
   
   Sys::UDPSocket::InResult inbound(PtrLen<uint8> buf) { return sys_sock.inbound(buf); }
 };

/* class UDPDevice<T> */

template <class T>
class UDPDevice : NoCopy
 {
   typedef typename T::ProcType InboundProc;
   typedef typename T::Event Event;
   typedef typename T::StatInfo StatInfo;
   typedef typename T::Extra Extra;
  
  private:
   
   UDPort udport;
   
   UDPInboundPackets src;  

   UDPSocket sock;

   Atomic stop_flag;
   
   Mutex mutex;
   
   InboundProc *proc;
   StatInfo stat;
   bool running;
   
  private: 
   
   void count(Event ev)
    {
     Mutex::Lock lock(mutex);
     
     stat.count(ev);
    }
  
   void set(bool running_)
    {
     Mutex::Lock lock(mutex);
    
     running=running_;
    }
   
  public:
   
   Extra extra;
   
   // constructors
   
   template <class ... SS>
   UDPDevice(UDPort udport_,ulen max_packets,SS ... ss)
    : udport(udport_),
      src(max_packets),
      sock(udport_),
      mutex("UDPDevice"),
      proc(0),
      running(false),
      extra(ss...)
    {
    }
   
   ~UDPDevice()
    {
     Mutex::Lock lock(mutex);
     
     if( running ) UDPDeviceExitRunningAbort(); 
       
     if( proc ) UDPDeviceAttachedAbort(); 
    }
   
   // methods
   
   UDPort getPort() const { return udport; }
   
   void getStat(StatInfo &ret)
    {
     Mutex::Lock lock(mutex);
    
     ret=stat;
    }
   
   // object run
  
   void prepareRun() { stop_flag=0; }
   
   void objRun();
   
   void completeRun() { set(true); }
   
   void signalStop() { stop_flag=1; }
   
   void completeStop() { set(false); }
   
   // device 
   
   PacketFormat getOutboundFormat()
    {
     PacketFormat ret;
     
     ret.prefix=0;
     ret.max_data=MaxUDPDataLen;
     ret.suffix=0;
     
     return ret;
    }
   
   void outbound(UDPoint dst,Packet<uint8> packet)
    {
     PtrLen<uint8> data=packet.getRange();
     
     if( data.len<=MaxUDPDataLen && sock.outbound(dst,Range_const(data)) )
       count(T::Event_sent);
     else
       count(T::Event_nosent);
       
     packet.complete();
    }
   
   ulen getMaxInboundLen()
    {
     return MaxUDPDataLen;
    }
   
   void attach(InboundProc *proc_)
    {
     bool is_running;
     bool has_proc;
     
     {
      Mutex::Lock lock(mutex);
      
      is_running=running;
      has_proc=(proc!=0);
      
      if( !is_running && !has_proc ) proc=proc_;  
     }
     
     if( is_running )
       {
        GuardUDPDeviceIsRunning(Exception,"attach");
       }
       
     if( has_proc )  
       {
        GuardUDPDeviceIsAttached();
       }
    }
   
   void detach()
    {
     bool is_running;
     
     {
      Mutex::Lock lock(mutex);
      
      is_running=running;
      
      if( !is_running ) proc=0;
     }
     
     if( is_running )
       {
        GuardUDPDeviceIsRunning(NoException,"detach");
        
        UDPDeviceDetachRunningAbort();
       }
    }
 };

template <class T>
void UDPDevice<T>::objRun()
 {
  set(true);
 
  if( !proc ) return;
  
  src.start();
  
  while( !stop_flag )
    switch( sock.wait_inbound(src.getScope()) )
      {
       case Sys::Wait_timeout :
        {
         if( src.nextScope() )
           {
            proc->tick();  
        
            count(T::Event_tick);
           }
         else
           {
            count(T::Event_extra_timeout);
           }
        }
       break;
     
       case Sys::Wait_error :
        {
         UDPDeviceWaitAbort();
        }
       break;
         
       default:
        {
         Packet<uint8> packet=src.getPacket();
         
         if( !packet )
           {
            count(T::Event_nopacket);  
              
            auto result=sock.inbound(Nothing); // packet drop
            
            if( result.error ) count(T::Event_noread);
           }
         else
           {
            PtrLen<uint8> data=packet.getMaxRange();
            
            auto result=sock.inbound(data);
               
            if( !result.error )
              {
               count( extra.inbound(proc,packet,result.len,result.src) );
              }
            else
              {
               packet.complete();
                 
               count(T::Event_noread);
              }
           }
        }
       break;
      }
 }

/* struct UDPEndpointDeviceBase */

struct UDPEndpointDeviceBase
 {
  typedef PacketEndpointDevice::InboundProc ProcType;
  
  enum Event
   {
    Event_read,
    Event_sent,
    Event_tick,
    
    Event_extra_timeout,
    
    Event_nosent,
    Event_nopacket,
    Event_noread,
    Event_nodst,
    
    EventLim
   };
   
  friend const char * GetTextDesc(Event ev); 
  
  typedef Counters<Event,EventLim> StatInfo;
  
  struct Extra
   {
    UDPoint dst;
    
    explicit Extra(UDPoint dst_) : dst(dst_) {}
    
    Event inbound(ProcType *proc,Packet<uint8> packet,ulen len,UDPoint src)
     {
      if( src==dst )
        {
         PtrLen<uint8> data=packet.setDataLen(len);
            
         proc->inbound(packet,Range_const(data));
         
         return Event_read;
        }
      else
        {
         packet.complete();
           
         return Event_nodst;
        }
     }
   };
 };

/* class UDPEndpointDevice */ 

class UDPEndpointDevice : public ObjBase , public PacketEndpointDevice , public UDPEndpointDeviceBase , public PortManager
 {
  private:
   
   UDPDevice<UDPEndpointDeviceBase> dev;
   
   typedef StartStopObject<UDPDevice<UDPEndpointDeviceBase> > StartStopDev; 
  
  public:
   
   // constructors
  
   static const ulen DefaultMaxPackets = 500 ;
  
   UDPEndpointDevice(UDPort udport,UDPoint dst,ulen max_packets=DefaultMaxPackets);
   
   virtual ~UDPEndpointDevice();
   
   // methods
   
   UDPort getPort() const { return dev.getPort(); }
   
   UDPoint getDst() const { return dev.extra.dst; }
   
   void getStat(StatInfo &ret) { dev.getStat(ret); }
   
   // PacketEndpointDevice
   
   virtual PacketFormat getOutboundFormat();
   
   virtual void outbound(Packet<uint8> packet);
   
   virtual ulen getMaxInboundLen();
   
   virtual void attach(InboundProc *proc);
   
   virtual void detach();
   
   // PortManager
   
   virtual XPoint getDevicePort() const;
   
   virtual XPoint getPort(XPoint point) const;
   
   virtual XPoint changePort(XPoint point,XPoint port) const;
   
   // start/stop
   
   class StartStop : public StartStopDev 
    {
     public:

      template <class ... TT>
      StartStop(UDPEndpointDevice &obj,TT ... tt) : StartStopDev(obj.dev,tt...) {}
      
      ~StartStop() {}
    };
 };
 
/* struct UDPMultipointDeviceBase */

struct UDPMultipointDeviceBase
 {
  typedef PacketMultipointDevice::InboundProc ProcType; 
  
  enum Event
   {
    Event_read,
    Event_sent,
    Event_tick,
    
    Event_extra_timeout,
    
    Event_nosent,
    Event_nopacket,
    Event_noread,
    
    EventLim
   };
   
  friend const char * GetTextDesc(Event ev); 
  
  typedef Counters<Event,EventLim> StatInfo;
  
  struct Extra
   {
    Extra() {}
    
    Event inbound(ProcType *proc,Packet<uint8> packet,ulen len,UDPoint src)
     {
      PtrLen<uint8> data=packet.setDataLen(len);
      
      proc->inbound(src.get(),packet,Range_const(data));
      
      return Event_read;
     }
   };
 };

/* class UDPMultipointDevice */ 

class UDPMultipointDevice : public ObjBase , public PacketMultipointDevice , public UDPMultipointDeviceBase , public PortManager
 {
   UDPDevice<UDPMultipointDeviceBase> dev;
  
   typedef StartStopObject<UDPDevice<UDPMultipointDeviceBase> > StartStopDev; 
   
  public:
   
   // constructors
  
   static const ulen DefaultMaxPackets = 500 ;
  
   explicit UDPMultipointDevice(UDPort udport,ulen max_packets=DefaultMaxPackets);
   
   virtual ~UDPMultipointDevice();
   
   // methods
   
   UDPort getPort() const { return dev.getPort(); }
   
   void getStat(StatInfo &ret) { dev.getStat(ret); }
   
   // PacketMultipointDevice
   
   virtual StrLen toText(XPoint point,PtrLen<char> buf);
   
   virtual PacketFormat getOutboundFormat();
   
   virtual void outbound(XPoint point,Packet<uint8> packet);
   
   virtual ulen getMaxInboundLen();
   
   virtual void attach(InboundProc *proc);
   
   virtual void detach();
   
   // PortManager
   
   virtual XPoint getDevicePort() const;
   
   virtual XPoint getPort(XPoint point) const;
   
   virtual XPoint changePort(XPoint point,XPoint port) const;
   
   // start/stop
   
   class StartStop : public StartStopDev 
    {
     public:

      template <class ... TT>
      StartStop(UDPMultipointDevice &obj,TT ... tt) : StartStopDev(obj.dev,tt...) {}
      
      ~StartStop() {}
    };
 };
 
} // namespace Net
} // namespace CCore
 
#endif
 

