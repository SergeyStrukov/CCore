/* UDPDevice.cpp */ 
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
 
#include <CCore/inc/net/UDPDevice.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/PrintError.h>

namespace CCore {
namespace Net {
 
/* functions */

void UDPDeviceExitRunningAbort()
 {
  Abort("Fatal error : CCore::Net::UDPDevice<T> is running on exit");
 }

void UDPDeviceAttachedAbort()
 {
  Abort("Fatal error : CCore::Net::UDPDevice<T> is attached on exit");
 }

void UDPDeviceDetachRunningAbort()
 {
  Abort("Fatal error : CCore::Net::UDPDevice<T> is running on detach");
 }

void UDPDeviceWaitAbort()
 {
  Abort("Fatal error : CCore::Net::UDPDevice<T>::objRun() wait failed");
 }

void GuardUDPDeviceIsRunning(ExceptionType ex,const char *name)
 {
  Printf(ex,"CCore::Net::UDPDevice<T>::#;(...) : device is running",name);
 }

void GuardUDPDeviceIsAttached()
 {
  Printf(Exception,"CCore::Net::UDPDevice<T>::attach(...) : already attached");
 }

/* class UDPInboundPackets */ 

UDPInboundPackets::UDPInboundPackets(ulen max_packets)
 : pset("UDPInboundPackets",max_packets)
 {
 }
   
UDPInboundPackets::~UDPInboundPackets()
 {
 }
   
Packet<uint8> UDPInboundPackets::getPacket()
 {
  Packet<uint8> packet=pset.get(time_scope);
            
  if( !packet ) packet=pset.try_get();
         
  return packet;
 }
   
void UDPInboundPackets::start()
 {
  time_scope.start( (1000/InboundTicksPerSec)*1_msec );
 }

/* class UDPSocket */

UDPSocket::UDPSocket(UDPort udport)
 {
  if( auto error=sys_sock.open(udport) )
    {
     Printf(Exception,"CCore::Net::UDPSocket::UDPSocket(#;) : #;",udport,PrintError(error));
    }
 }
   
UDPSocket::~UDPSocket()
 {
  if( auto error=sys_sock.close() )
    {
     Printf(NoException,"CCore::Net::UDPSocket::~UDPSocket() : #;",PrintError(error));
    }
 }
   
/* struct UDPEndpointDeviceBase */

const char * GetTextDesc(UDPEndpointDeviceBase::Event ev)
 {
  static const char *const Table[]=
   {
    "Rx",              // Event_read
    "Tx",              // Event_sent
    "Tick",            // Event_tick
    
    "Extra timeout",   // Event_extra_timeout
    
    "Tx failed",       // Event_nosent
    "No packet",       // Event_nopacket
    "Rx failed",       // Event_noread
    "Source mismatch", // Event_nodst
   
    ""
   };
   
  return Table[ev]; 
 }
 
/* class UDPEndpointDevice */ 

UDPEndpointDevice::UDPEndpointDevice(UDPort udport,UDPoint dst,ulen max_packets)
 : dev(udport,max_packets,dst)
 {
 }
   
UDPEndpointDevice::~UDPEndpointDevice()
 {
 }
   
PacketFormat UDPEndpointDevice::getOutboundFormat()
 {
  return dev.getOutboundFormat();
 }
   
void UDPEndpointDevice::outbound(Packet<uint8> packet)
 {
  dev.outbound(dev.extra.dst,packet);
 }
   
ulen UDPEndpointDevice::getMaxInboundLen()
 {
  return dev.getMaxInboundLen();
 }
   
void UDPEndpointDevice::attach(InboundProc *proc)
 {
  dev.attach(proc);
 }
   
void UDPEndpointDevice::detach()
 {
  dev.detach();
 }
 
/* struct UDPMultipointDeviceBase */

const char * GetTextDesc(UDPMultipointDeviceBase::Event ev)
 {
  static const char *const Table[]=
   {
    "Rx",            // Event_read
    "Tx",            // Event_sent
    "Tick",          // Event_tick
    
    "Extra timeout", // Event_extra_timeout
    
    "Tx failed",     // Event_nosent
    "No packet",     // Event_nopacket
    "Rx failed",     // Event_noread
   
    ""
   };
   
  return Table[ev]; 
 }

/* class UDPMultipointDevice */ 
 
UDPMultipointDevice::UDPMultipointDevice(UDPort udport,ulen max_packets)
 : dev(udport,max_packets)
 {
 }
   
UDPMultipointDevice::~UDPMultipointDevice()
 {
 }
   
StrLen UDPMultipointDevice::toText(XPoint point,PtrLen<char> buf)
 {
  PrintBuf out(buf);
  
  UDPoint udpoint(point);
  
  Putobj(out,udpoint);
  
  return out.close();
 }
 
PacketFormat UDPMultipointDevice::getOutboundFormat()
 {
  return dev.getOutboundFormat();
 }
   
void UDPMultipointDevice::outbound(XPoint point,Packet<uint8> packet)
 {
  UDPoint dst(point);
  
  dev.outbound(dst,packet);
 }
   
ulen UDPMultipointDevice::getMaxInboundLen()
 {
  return MaxUDPDataLen;
 }
   
void UDPMultipointDevice::attach(InboundProc *proc)
 {
  dev.attach(proc);
 }
   
void UDPMultipointDevice::detach()
 {
  dev.detach();
 }
 
} // namespace Net
} // namespace CCore
 

