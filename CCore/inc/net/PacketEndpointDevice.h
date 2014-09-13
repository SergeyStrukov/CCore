/* PacketEndpointDevice.h */ 
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

#ifndef CCore_inc_net_PacketEndpointDevice_h
#define CCore_inc_net_PacketEndpointDevice_h
 
#include <CCore/inc/net/XPoint.h>

#include <CCore/inc/Packet.h>
#include <CCore/inc/Printf.h>

namespace CCore {
namespace Net {

/* consts */ 

const unsigned InboundTicksPerSec = 10 ;

/* functions */

inline constexpr unsigned ToTickCount(MSec timeout)
 {
  return ((+timeout)*InboundTicksPerSec)/1000+1;
 }

/* classes */ 

struct PacketEndpointDevice;

struct PacketMultipointDevice;

struct PortManager;

class PointDesc;

/* struct PacketEndpointDevice */ 

struct PacketEndpointDevice
 {
  virtual PacketFormat getOutboundFormat()=0;
   
  virtual void outbound(Packet<uint8> packet)=0;
   
  virtual ulen getMaxInboundLen()=0;
   
  struct InboundProc
   {
    virtual void inbound(Packet<uint8> packet,PtrLen<const uint8> data)=0;
     
    virtual void tick()=0;
   };
  
  struct ConnectionProc // optional for InboundProc
   {
    virtual void connection_lost()=0;
    
    virtual void connection_close()=0;
   };
   
  virtual void attach(InboundProc *proc)=0;
   
  virtual void detach()=0;
 };

/* struct PacketMultipointDevice */ 

struct PacketMultipointDevice
 {
  virtual StrLen toText(XPoint point,PtrLen<char> buf)=0;
   
  virtual PacketFormat getOutboundFormat()=0;
   
  virtual void outbound(XPoint point,Packet<uint8> packet)=0;
   
  virtual ulen getMaxInboundLen()=0;
   
  struct InboundProc
   {
    virtual void inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data)=0;
     
    virtual void tick()=0;
   };
   
  struct ConnectionProc // optional for InboundProc
   {
    virtual void connection_open(XPoint point)=0;
    
    virtual void connection_lost(XPoint point)=0;
    
    virtual void connection_close(XPoint point)=0;
   };
  
  virtual void attach(InboundProc *proc)=0;
   
  virtual void detach()=0;
 };
 
/* struct PortManager */

struct PortManager
 {
  virtual XPoint getDevicePort() const =0;
  
  virtual XPoint getPort(XPoint point) const =0;
  
  virtual XPoint changePort(XPoint point,XPoint port) const =0;
 };

/* class PointDesc */  

class PointDesc : NoCopy
 {
   char buf[TextBufLen];
   StrLen str;
   
  public:
  
   PointDesc(PacketMultipointDevice *mp,XPoint point)
    {
     str=mp->toText(point,Range(buf));
    }
    
   StrLen getStr() const { return str; } 
   
   // print object
    
   typedef StrPrintOpt PrintOptType; 
    
   template <class P> 
   void print(P &out,PrintOptType opt) const
    {
     Putobj(out,BindOpt(opt,str));
    }
 };
 
} // namespace Net
} // namespace CCore
 
#endif
 

