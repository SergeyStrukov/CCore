/* PTPEchoTest.cpp */ 
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
 
#include <CCore/inc/net/PTPEchoTest.h>
 
namespace CCore {
namespace Net {
namespace PTP {

/* class EchoTest */ 

void EchoTest::cancel(TransIndex idx,Packet<uint8> packet)
 {
  packet.complete();
        
  ptp->send_cancel(idx);
 }
  
void EchoTest::inbound(XPoint,TransIndex idx,Packet<uint8> packet,PtrLen<const uint8> client_info)
 {
  RangeGetDev dev(client_info);
     
  ServiceIdType service_id;
  FunctionIdType function_id;
    
  dev.use<BeOrder>(service_id,function_id);
     
  if( !dev ) return cancel(idx,packet);
     
  if( service_id==ServiceId && function_id==FunctionId )
    {
     uint32 len;
        
     dev.use<BeOrder>(len);
        
     if( !dev || len!=dev.getRest().len ) return cancel(idx,packet);
        
     uint8 *buf=const_cast<uint8 *>(client_info.ptr)+8;
        
     BufPutDev outdev(buf);
     uint32 no_error=0;
        
     outdev.use<BeOrder>(no_error);
       
     ptp->send_info(idx,packet,client_info);
    } 
  else
    {
     cancel(idx,packet);
    }
 }
    
void EchoTest::tick()
 {
  // do nothing
 }
   
EchoTest::EchoTest(StrLen ptp_server_name)
 : hook(ptp_server_name),
   ptp(hook)
 {
  ptp->attach(this);
 }
   
EchoTest::~EchoTest()
 {
  ptp->detach();
 }
 
} // namespace PTP
} // namespace Net
} // namespace CCore
 

