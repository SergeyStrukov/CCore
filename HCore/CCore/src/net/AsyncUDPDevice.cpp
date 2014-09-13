/* AsyncUDPDevice.cpp */ 
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/net/AsyncUDPDevice.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/PrintError.h>

namespace CCore {
namespace Net {

/* functions */

void AsyncUDPDeviceExitRunningAbort()
 {
  Abort("Fatal error : CCore::Net::AsyncUDPDevice<T> is running on exit");
 }

void AsyncUDPDeviceAttachedAbort()
 {
  Abort("Fatal error : CCore::Net::AsyncUDPDevice<T> is attached on exit");
 }

void AsyncUDPDeviceDetachRunningAbort()
 {
  Abort("Fatal error : CCore::Net::AsyncUDPDevice<T> is running on detach");
 }

void AsyncUDPDeviceWaitAbort()
 {
  Abort("Fatal error : CCore::Net::AsyncUDPDevice<T> wait error");
 }

void GuardAsyncUDPDeviceMaxPackets()
 {
  Printf(Exception,"CCore::Net::AsyncUDPDevice<T>::AsyncUDPDevice(...) : max_packets==0");
 }

void GuardAsyncUDPDeviceIsRunning(ExceptionType ex,const char *name)
 {
  Printf(ex,"CCore::Net::AsyncUDPDevice<T>::#;(...) : device is running",name);
 }

void GuardAsyncUDPDeviceIsAttached()
 {
  Printf(Exception,"CCore::Net::AsyncUDPDevice<T>::attach(...) : already attached");
 }

/* class AsyncUDPSocket */

AsyncUDPSocket::AsyncUDPSocket(UDPort udport)
 {
  if( auto error=sys_sock.open(udport) )
    {
     Printf(Exception,"CCore::Net::AsyncUDPSocket::AsyncUDPSocket(#;) : #;",udport,PrintError(error));
    }
 }
   
AsyncUDPSocket::~AsyncUDPSocket()
 {
  if( auto error=sys_sock.close() )
    {
     Printf(NoException,"CCore::Net::AsyncUDPSocket::~AsyncUDPSocket() : #;",PrintError(error));
    }
 }

/* class AsyncUDPSocketWait */

AsyncUDPSocketWait::AsyncUDPSocketWait(Function<void (void)> finish_)
 : finish(finish_)
 {
  if( auto error=sys_wait.init(2) )
    {
     Printf(Exception,"CCore::Net::AsyncUDPSocketWait::AsyncUDPSocketWait() : #;",PrintError(error));
    }
 }
   
AsyncUDPSocketWait::~AsyncUDPSocketWait()
 {
  for(;;)
    {
     auto result=sys_wait.waitAll(DefaultTimeout);
     
     if( result==Sys::WaitResult(0) ) break;
     
     if( result==Sys::Wait_error )
       {
        Abort("Fatal error : CCore::Net::AsyncUDPSocketWait wait error");
       }
    }
  
  finish();
  
  sys_wait.exit();
 }

/* struct AsyncUDPEndpointDeviceBase */

const char * GetTextDesc(AsyncUDPEndpointDeviceBase::Event ev)
 {
  static const char *const Table[]=
   {
    "Rx",              // Event_read
    "Tx",              // Event_sent
    "Tick",            // Event_tick
    
    "Extra timeout",   // Event_extra_timeout
    
    "Cancel on put",   // Event_cancel_on_put
    "Cancel on get",   // Event_cancel_on_get
    "Cancel",          // Event_cancel
    "Tx failed",       // Event_nosent
    "No packet",       // Event_nopacket
    "Rx failed",       // Event_noread
    "Source mismatch", // Event_nodst
     
    ""
   };
 
  return Table[ev];
 }

/* class AsyncUDPEndpointDevice */ 

AsyncUDPEndpointDevice::AsyncUDPEndpointDevice(UDPort udport,UDPoint dst,ulen max_packets)
 : dev(udport,max_packets,dst)
 {
 }

AsyncUDPEndpointDevice::~AsyncUDPEndpointDevice()
 {
 }

PacketFormat AsyncUDPEndpointDevice::getOutboundFormat()
 {
  return dev.getOutboundFormat();
 }

void AsyncUDPEndpointDevice::outbound(Packet<uint8> packet)
 {
  dev.outbound(dev.extra.dst,packet);
 }

ulen AsyncUDPEndpointDevice::getMaxInboundLen()
 {
  return dev.getMaxInboundLen();
 }

void AsyncUDPEndpointDevice::attach(InboundProc *proc)
 {
  dev.attach(proc);
 }

void AsyncUDPEndpointDevice::detach()
 {
  dev.detach();
 }

XPoint AsyncUDPEndpointDevice::getDevicePort() const
 {
  return dev.getPort();
 }

XPoint AsyncUDPEndpointDevice::getPort(XPoint point) const
 {
  UDPoint udpoint(point);

  return udpoint.port;
 }

XPoint AsyncUDPEndpointDevice::changePort(XPoint point,XPoint port) const
 {
  UDPoint udpoint(point);
  
  udpoint.port=(UDPort)port;
  
  return udpoint.get();
 }

/* struct AsyncUDPMultipointDeviceBase */

const char * GetTextDesc(AsyncUDPMultipointDeviceBase::Event ev)
 {
  static const char *const Table[]=
   {
    "Rx",              // Event_read
    "Tx",              // Event_sent
    "Tick",            // Event_tick
    
    "Extra timeout",   // Event_extra_timeout
    
    "Cancel on put",   // Event_cancel_on_put
    "Cancel on get",   // Event_cancel_on_get
    "Cancel",          // Event_cancel
    "Tx failed",       // Event_nosent
    "No packet",       // Event_nopacket
    "Rx failed",       // Event_noread
     
    ""
   };
 
  return Table[ev];
 }

/* class AsyncUDPMultipointDevice */

AsyncUDPMultipointDevice::AsyncUDPMultipointDevice(UDPort udport,ulen max_packets)
 : dev(udport,max_packets)
 {
 }

AsyncUDPMultipointDevice::~AsyncUDPMultipointDevice()
 {
 }

StrLen AsyncUDPMultipointDevice::toText(XPoint point,PtrLen<char> buf)
 {
  PrintBuf out(buf);
  
  UDPoint udpoint(point);
  
  Putobj(out,udpoint);
  
  return out.close();
 }

PacketFormat AsyncUDPMultipointDevice::getOutboundFormat()
 {
  return dev.getOutboundFormat();
 }

void AsyncUDPMultipointDevice::outbound(XPoint point,Packet<uint8> packet)
 {
  UDPoint dst(point);
  
  dev.outbound(dst,packet);
 }

ulen AsyncUDPMultipointDevice::getMaxInboundLen()
 {
  return dev.getMaxInboundLen();
 }

void AsyncUDPMultipointDevice::attach(InboundProc *proc)
 {
  dev.attach(proc);
 }

void AsyncUDPMultipointDevice::detach()
 {
  dev.detach();
 }

XPoint AsyncUDPMultipointDevice::getDevicePort() const
 {
  return dev.getPort();
 }

XPoint AsyncUDPMultipointDevice::getPort(XPoint point) const
 {
  UDPoint udpoint(point);

  return udpoint.port;
 }

XPoint AsyncUDPMultipointDevice::changePort(XPoint point,XPoint port) const
 {
  UDPoint udpoint(point);
  
  udpoint.port=(UDPort)port;
  
  return udpoint.get();
 }

} // namespace Net
} // namespace CCore
 

