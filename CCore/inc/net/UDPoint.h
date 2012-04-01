/* UDPoint.h */ 
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

#ifndef CCore_inc_net_UDPoint_h
#define CCore_inc_net_UDPoint_h

#include <CCore/inc/net/NetBase.h>
 
namespace CCore {
namespace Net {

/* ports */ 

const UDPort EchoUDPort      =     7 ;

const UDPort PTPServerUDPort = 52000 ;

const UDPort PTPClientUDPort = 52001 ;

/* classes */ 

struct UDPoint;

/* struct UDPoint */ 

struct UDPoint
 {
  IPAddress address;
  UDPort port;
  
  // constructors
  
  UDPoint() : address(),port() {}
  
  UDPoint(IPAddress address_,UDPort port_) : address(address_),port(port_) {}
  
  UDPoint(uint8 a1,uint8 a2,uint8 a3,uint8 a4,UDPort port_) : address(a1,a2,a3,a4),port(port_) {}
  
  explicit UDPoint(XPoint a) : address(uint32(a>>16)),port(uint16(a)) {}
  
  // methods
  
  friend bool operator == (UDPoint a,UDPoint b) { return a.address==b.address && a.port==b.port ; }
  
  friend bool operator != (UDPoint a,UDPoint b) { return !(a==b); }
  
  XPoint get() const { return (uint64(address.get())<<16)|port; }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#;:#;",address,port);
   }
 };
 
} // namespace Net
} // namespace CCore
 
#endif
 

