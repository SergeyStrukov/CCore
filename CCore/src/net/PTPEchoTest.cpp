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

#include <CCore/inc/net/PTPSupportBase.h>
 
namespace CCore {
namespace Net {
namespace PTP {

/* class EchoTest */ 

void EchoTest::cancel(TransIndex idx,Packet<uint8> packet)
 {
  packet.complete();
        
  ptp->send_cancel(idx);
 }

template <class T>
void EchoTest::result(TransIndex idx,Packet<uint8> packet,ServiceFunction serv_func,const T &output)
 {
  Result result(serv_func,NoError);
  
  auto data_len=SaveLen(result,output);
  
  if( packet.checkDataLen(data_len) )
    {
     auto info=packet.setDataLen(data_len);
     
     BufPutDev dev(info.ptr);
     
     dev(result,output);
     
     ptp->send_info(idx,packet,Range_const(info));
    }
  else
    {
     cancel(idx,packet);
    }
 }

void EchoTest::inbound(XPoint,TransIndex idx,Packet<uint8> packet,PtrLen<const uint8> client_info)
 {
  RangeGetDev dev(client_info);
     
  ServiceFunction serv_func;
    
  dev(serv_func);
     
  if( !dev ) return cancel(idx,packet);
  
  switch( serv_func.service_id )
    {
     case ServiceId :
      {
       switch( serv_func.function_id )
         {
          case FunctionId :
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
          break;
          
          default: cancel(idx,packet);
         }
      }
     break;
     
     case PTPSupport::ServiceId :
      {
       switch( serv_func.function_id )
         {
          case PTPSupport::FunctionId_Len :
           {
            PTPSupport::LenInput input;
            
            dev(input);
            
            if( !dev.finish() ) return cancel(idx,packet);
            
            PTPSupport::LenOutput output;
            
            output.to_server_info_len=Min(input.to_server_info_len,ptp->getMaxInboundInfoLen());
            output.to_client_info_len=Min(input.to_client_info_len,ptp->getMaxOutboundInfoLen());
            
            result(idx,packet,serv_func,output);
           }
          break;
          
          case PTPSupport::FunctionId_Seed :
           {
            PTPSupport::SeedInput input;
            
            dev(input);
            
            if( !dev.finish() ) return cancel(idx,packet);
            
            PTPSupport::SeedOutput output;
            
            output.seed1=random.next64();
            output.seed2=random.next64();
            
            result(idx,packet,serv_func,output);
           }
          break;
          
          case PTPSupport::FunctionId_Session :
           {
            PTPSupport::SessionInput input;
            
            dev(input);
            
            if( !dev.finish() ) return cancel(idx,packet);
            
            PTPSupport::SessionOutput output;
            
            result(idx,packet,serv_func,output);
           }
          break;
          
          default: cancel(idx,packet);
         }
      }
     break; 
     
     default: cancel(idx,packet);
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
 

