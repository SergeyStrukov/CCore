/* ServerProc.cpp */ 
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
 
#include "ServerProc.h"

#include <CCore/inc/Exception.h>

namespace App {

/* class ServerProc */ 

void ServerProc::session(XPoint point)
 {
  support_proc.session(point);
  con_proc.session(point);
  hfs_proc.session(point);
 }
    
bool ServerProc::exist(ServiceIdType service_id,FunctionIdType function_id)
 {
  switch( service_id )
    {
     case Net::PTPSupport::ServiceId : return support_proc.exist(function_id);
     
     case Net::PTPCon::ServiceId :     return con_proc.exist(function_id);
     
     case Net::HFS::ServiceId :        return hfs_proc.exist(function_id);
     
     default: return false;
    }
 }
 
void ServerProc::inbound(XPoint point,TransIndex idx,Packet<uint8> packet,PtrLen<const uint8> client_info)
 {
  SilentReportException report;
  
  Inbound inbound(point,idx,packet,client_info);
  
  if( !inbound ) return inbound.send_cancel(ptp);
  
  switch( inbound.serv_func.service_id )
    {
     case Net::PTPSupport::ServiceId : support_proc.inbound(inbound); break;
     
     case Net::PTPCon::ServiceId :     con_proc.inbound(inbound); break;
     
     case Net::HFS::ServiceId :        hfs_proc.inbound(inbound); break;
     
     default:
      {
       inbound.error_id=Error_NoFunction;
       
       inbound.send_error(ptp);
      }
    }
 }
    
void ServerProc::tick()
 {
  SilentReportException report;
  
  support_proc.tick();
  con_proc.tick();
  hfs_proc.tick();
  
  log.flush();
 }
 
ServerProc::ServerProc(StrLen ptp_server_name,bool exit_on_close)
 : ServerProcBase(ptp_server_name),
   support_proc(this),
   con_proc(this,exit_on_close),
   hfs_proc(this),
   ins_text(0)
 {
  ptp->attach(this);
 }
   
ServerProc::~ServerProc()
 {
  ptp->detach();
 }
 
char ServerProc::get()
 {
  for(;;)
    {
     if( ins_text )
       {
        if( char ch=*ins_text )
          {
           ins_text++;
           
           return ch;
          }
          
        ins_text=0;  
       }
 
     char ch;
        
     if( con.get(100_msec,ch) )
       {
        if( !con_proc.put(ch) ) return ch;
       }
     else
       {
        ins_text=con_proc.ins();
       }  
    }
 }
    
} // namespace App
 

