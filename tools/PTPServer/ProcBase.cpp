/* ProcBase.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: PTPServer 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "ProcBase.h"

#include <CCore/inc/Abort.h>

namespace App {

/* class Log */ 

Log::Log()
 : out("PTPServerLog.txt",Open_ToAppend)
 {
  out.disableExceptions();
 
  Printf(out,"#;\n",Title("PTP Server log"));
 }
   
Log::~Log()
 {
  Printf(out,"\n#;\n\nRun time = #;\n\n#;\n\n\n",TextDivider(),PrintTime(timer.get()),TextDivider());
 }
 
/* struct Inbound */ 

Inbound::Inbound(XPoint point_,TransIndex idx_,Packet<uint8> packet_,PtrLen<const uint8> client_info)
 : point(point_),
   idx(idx_),
   dev(client_info),
   packet(packet_)
 {
  dev(serv_func);
  
  if( !dev ) 
    error_id=Error_BadInput;
  else
    error_id=NoError;
 }
  
void Inbound::send_cancel(Net::PTP::ServerDevice *ptp)
 {
  packet.complete();
 
  ptp->send_cancel(idx);
 } 
  
void Inbound::send_error(Net::PTP::ServerDevice *ptp)
 {
  Net::PTP::Result result(serv_func,error_id);
  
  auto len=SaveLen(result);
     
  if( packet.checkDataLen(len) )
    {
     PtrLen<uint8> info=packet.setDataLen(len);
        
     BufPutDev dev(info.ptr);
        
     dev(result);
        
     ptp->send_info(idx,Replace_null(packet),Range_const(info));
    }
  else
    {
     send_cancel(ptp);
    }
 }
 
/* struct Outbound */ 

bool Outbound::init(Inbound &inbound,PacketFunction cancel_function)
 {
  idx=inbound.idx;
  serv_func=inbound.serv_func;
  
  if( inbound.packet.setCancelFunction(cancel_function)==Packet_Cancelled ) return false;
  
  packet=inbound.packet.pushExt<bool>(true);
  
  return true;
 }
    
void Outbound::send_cancel(Net::PTP::ServerDevice *ptp)
 {
  packet.popExt().complete();
 
  ptp->send_cancel(idx);
 }
 
void Outbound::CancelExt::Complete(PacketHeader *packet_) 
 {
  Packet<uint8,CancelExt> packet=packet_;
  
  CancelExt ext(*packet.getExt());
  
  ext();
  
  packet.popExt().complete();
 }
 
void Outbound::send_cancel(PacketList &complete_list,Net::PTP::ServerDevice *ptp)
 {
  Packet<uint8,CancelExt> packet2=packet.popExt().pushExt<CancelExt>(ptp,idx);
  
  packet2.pushCompleteFunction(CancelExt::Complete);
  
  complete_list.put(packet2);
 }
 
void Outbound::InfoExt::Complete(PacketHeader *packet_)
 {
  Packet<uint8,InfoExt> packet=packet_;
  
  InfoExt ext(*packet.getExt());
  
  ext(packet.popExt());
 }
 
void Outbound::send_info(PacketList &complete_list,Net::PTP::ServerDevice *ptp,PtrLen<const uint8> server_info)
 {
  Packet<uint8,InfoExt> packet2=packet.popExt().pushExt<InfoExt>(ptp,idx,server_info);
  
  packet2.pushCompleteFunction(InfoExt::Complete);
  
  complete_list.put(packet2);
 }
 
void Outbound::send_error(PacketList &complete_list,Net::PTP::ServerDevice *ptp,ErrorIdType error_id)
 {
  Net::PTP::Result result(serv_func,error_id);
  
  auto len=SaveLen(result);
     
  if( packet.checkDataLen(len) )
    {
     PtrLen<uint8> info=packet.setDataLen(len);
        
     BufPutDev dev(info.ptr);
        
     dev(result);
       
     send_info(complete_list,ptp,Range_const(info));
    }
  else
    {
     send_cancel(complete_list,ptp);
    }
 }
 
/* class ServerProcBase */ 

ServerProcBase::ServerProcBase(StrLen ptp_server_name)
 : hook(ptp_server_name),
   ptp(hook)
 {
 }
   
ServerProcBase::~ServerProcBase()
 {
 }
   
} // namespace App
 

