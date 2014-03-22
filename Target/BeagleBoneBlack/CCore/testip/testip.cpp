/* testip.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/testip/testip.h>
 
#include <CCore/inc/Exception.h>
 
namespace App {

/* class IPEngine */ 

IPEngine::IPEngine()
 : ip_device("Eth",Net::IPAddress(192,168,1,10),Net::IPAddress(255,255,255,0)),
   ip_master(ip_device,"IP")
 {
 }
   
IPEngine::~IPEngine()
 {
  Task::Sleep(1_sec);
 }
 
class IPEngine::Ping : public Funchor_nocopy
 {
   Sem sem;
   
  private: 
 
   void reply(Net::ICMPEchoNumber)
    {
     sem.give();
    }
 
  public:
  
   Ping() {}
   
   ~Ping() {}
   
   Net::ICMPReplyFunction function_reply() { return FunctionOf(this,&Ping::reply); }
   
   bool wait(TimeScope time_scope)
    {
     auto timeout=time_scope.get();
     
     if( !timeout )
       {
        Printf(Exception,"Ping: host is unreachable");
       }
     
     return sem.take(timeout.cap(200_msec));
    }
 };
 
void IPEngine::ping(MSec timeout)
 {
  Ping ping;
 
  Net::ICMPEchoEndpoint echo("IP",Net::IPAddress(192,168,1,1),ping.function_reply());
  
  TimeScope time_scope(timeout);

  for(;;)
    {
     echo.send();
  
     if( ping.wait(time_scope) ) 
       {
        Printf(Con,"Ping: host is found\n");
       
        return;
       }
    }
 }
 
void IPEngine::showStat()
 {
  //ShowStat(eth_device,"Eth"); 
  ShowStat(ip_device,"IP"); 
  
  CancelPacketList::StatInfo info;
  
  ip_device.getStat_arp(info);
  
  Printf(Con,"#;\n\n#15;\n\n",Title("IP arp cancelled"),info);
  
  ip_device.getStat_prepare(info);
  
  Printf(Con,"#;\n\n#15;\n\n",Title("IP prepare cancelled"),info);
  
  ip_device.getStat_arp(info);
  
  Printf(Con,"#;\n\n#15;\n\n",Title("IP send cancelled"),info);
 }
 
/* class HostEngine */ 

HostEngine::HostEngine(Net::UDPoint dst)
 : udp("IP",Net::PTPClientUDPort,false,dst),
   udp_master(udp,"udp"),
   ptp("udp"),
   support(ptp),
   ptp_master(ptp,"ptp"),
   hfs("ptp"),
   hfs_master(hfs,"hfs"),
   fs("hfs"),
   fs_master(fs,"host")
 {
 }
    
HostEngine::~HostEngine()
 {
 } 
 
} // namespace App
 

