/* SupportProc.cpp */ 
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

#include "SupportProc.h"

namespace App {

/* class ProcEcho */ 

void ProcEcho::add(XPoint point,uint32 delay,Ext *ext)
 {
  if( !delay ) delay=1;
    
  if( !list )
    {
     cur_tick=0;
     
     min_delay=delay;
    }
  else
    {
     delay+=cur_tick; // no overflow here
     
     Replace_min(min_delay,delay);
    }
    
  root1.ins(ext,point);
  root2.ins(ext,delay);
  list.ins_last(ext);
 }
 
void ProcEcho::del(Ext *ext) 
 {
  root1.del(ext);
  root2.del(ext);
  list.del(ext);
 }
 
void ProcEcho::kill(Ext *ext) 
 {
  Packet<uint8,Ext> packet=ext->packet;
     
  packet.popExt().complete();
 }
 
void ProcEcho::send(Ext *ext,Net::PTP::ServerDevice *ptp)
 {
  TransIndex idx=ext->idx;
  Packet<uint8,Ext> packet=ext->packet;
  PtrLen<const uint8> server_info=ext->server_info;
  
  ptp->send_info(idx,packet.popExt(),server_info);
 }
 
ProcEcho::ProcEcho()
 {
 }
   
ProcEcho::~ProcEcho()
 {
  while( Ext *ext=list.del_first() ) kill(ext);
 }
   
void ProcEcho::put(XPoint point,uint32 delay_msec,TransIndex idx,Packet<uint8> proc_packet,PtrLen<const uint8> server_info)
 {
  Packet<uint8,Ext> packet=proc_packet.pushExt<Ext>();
  Ext *ext=packet.getExt();

  ext->idx=idx;
  ext->packet=packet;
  ext->server_info=server_info;
  
  uint32 delay_tick=ToTicks(delay_msec);
  
  add(point,delay_tick,ext);
 }
   
void ProcEcho::tick(Net::PTP::ServerDevice *ptp)
 {
  if( !list ) return;
  
  cur_tick++;
  
  if( cur_tick<min_delay ) return;
  
  while( Ext *ext=root2.find(min_delay) )
    {
     del(ext);
     send(ext,ptp);
    }
  
  if( Ext *ext=root2.findMin() )
    {
     min_delay=ext->getDelay();
    }
    
  if( cur_tick>1000000 && +list )  
    {
     root2.init();
     
     for(auto cur=list.start(); +cur ;++cur)
       {
        Ext *ext=cur.ptr;
        
        ext->subDelay(cur_tick);
        
        root2.ins(ext);
       }
    
     min_delay-=cur_tick;
     cur_tick=0;
    }
 }
   
void ProcEcho::purge(XPoint point)
 {
  while( Ext *ext=root1.find(point) )
    {
     del(ext);
     kill(ext);
    }
 }
 
/* class SupportProc */ 

void SupportProc::set(ulen max_outbound_info_len,ulen max_inbound_info_len)
 {
  to_server_info_len=max_inbound_info_len;
  to_client_info_len=max_outbound_info_len;
 }
  
void SupportProc::function_Len(Inbound &inbound)
 {
  Net::PTPSupport::LenInput input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PTPSupport::LenOutput output;

  output.to_server_info_len=Min(input.to_server_info_len,to_server_info_len);
  output.to_client_info_len=Min(input.to_client_info_len,to_client_info_len);
  
  log("SupportLen(#;,#;) : (#;,#;)",input.to_server_info_len,input.to_client_info_len,
                                    output.to_server_info_len,output.to_client_info_len);

  inbound.send_info(output,ptp);
 }
  
void SupportProc::function_Seed(Inbound &inbound)
 {
  Net::PTPSupport::SeedInput input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PTPSupport::SeedOutput output(random.next64(),random.next64());

  log("SupportSeed()");
  
  inbound.send_info(output,ptp);
 }
   
void SupportProc::function_Session(Inbound &inbound)
 {
  Net::PTPSupport::SessionInput input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  base->session(inbound.point);
       
  Net::PTPSupport::SessionOutput output;
  
  log("SupportSession(#;)",Net::PointDesc(ptp->getMPDevice(),inbound.point));

  inbound.send_info(output,ptp);     
 }
   
void SupportProc::function_Echo(Inbound &inbound)
 {
  Tailed<Net::PTPSupport::EchoInput> input;
       
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Tailed<Net::PTPSupport::EchoOutput> output(input.tail.ptr,input.base.len);

  log("SupportEcho()");
     
  Packet<uint8> proc_packet=TryAllocPacket<uint8>();
     
  if( !proc_packet )
    {
     inbound.error_id=Error_Exhausted;
     
     inbound.send_error(ptp);
    }
  else
    {
     Net::PTP::Result result(inbound.serv_func,NoError);
    
     auto len=SaveLen(result,output);
     
     if( proc_packet.checkDataLen(len) )
       {
        PtrLen<uint8> info=proc_packet.setDataLen(len);
        
        BufPutDev dev(info.ptr);
        
        dev(result,output);
           
        inbound.complete();
           
        echo.put(inbound.point,Min(input.base.delay_msec,Net::PTPSupport::MaxDelay),inbound.idx,proc_packet,Range_const(info));
       }
     else
       {
        proc_packet.complete();
           
        inbound.error_id=Error_Exhausted;
     
        inbound.send_error(ptp);
       }
    }  
 }
   
void SupportProc::function_ErrorDesc(Inbound &inbound)
 {
  Net::PTPSupport::ErrorDescInput input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  StrLen desc=GetErrorDesc(input.error_id);
  
  uint8 len=(uint8)Min(desc.len,Net::PTPSupport::ErrorDescOutput::MaxLen);
  
  Tailed<Net::PTPSupport::ErrorDescOutput> output(MutatePtr<const uint8>(desc.ptr),len);
  
  log("SupportErrorDesc(#;,#;,#;) : #;",input.service_id,input.function_id,input.error_id,desc);

  inbound.send_info(output,ptp);     
 }
   
void SupportProc::function_Exist(Inbound &inbound)
 {
  Net::PTPSupport::ExistInput input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PTPSupport::ExistOutput output(input,base->exist(input.service_id,input.function_id)?NoError:Error_NoFunction);
  
  log("SupportExist(#;,#;) : #;",input.service_id,input.function_id,output.error_id);

  inbound.send_info(output,ptp);     
 }
   
SupportProc::SupportProc(ServerProcBase *base_)
 : ProcBase(base_),
   base(base_)
 {
  set(ptp->getMaxOutboundInfoLen(),ptp->getMaxInboundInfoLen());
  
  //set(1000,500); // TEST ONLY
 }
   
SupportProc::~SupportProc()
 {
 }
   
void SupportProc::inbound(Inbound &inbound)
 {
  switch( inbound.serv_func.function_id )
    {
     case Net::PTPSupport::FunctionId_Len :       function_Len(inbound); break;
    
     case Net::PTPSupport::FunctionId_Seed :      function_Seed(inbound); break;
     
     case Net::PTPSupport::FunctionId_Session :   function_Session(inbound); break;
     
     case Net::PTPSupport::FunctionId_Echo :      function_Echo(inbound); break;
     
     case Net::PTPSupport::FunctionId_ErrorDesc : function_ErrorDesc(inbound); break;
     
     case Net::PTPSupport::FunctionId_Exist :     function_Exist(inbound); break;
     
     default:
      {
       inbound.error_id=Error_NoFunction;
       
       inbound.send_error(ptp);
      }
    }
 }
   
void SupportProc::tick()
 {
  echo.tick(ptp);
 }
   
void SupportProc::session(XPoint point)
 {
  echo.purge(point);
 }
   
bool SupportProc::exist(FunctionIdType function_id)
 {
  return function_id>=Net::PTPSupport::FunctionId_Len && function_id<=Net::PTPSupport::FunctionId_Exist ;
 }
 
} // namespace App
 
 

