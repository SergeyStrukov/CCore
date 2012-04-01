/* test3005.NanoIPDevice-PTP.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/testip/testip.h>

namespace App {

namespace Private_3005 {

/* class Engine */  

class Engine : NoCopy
 {
   Net::NanoUDPEndpointDevice udp1;
   Net::NanoUDPEndpointDevice udp2;
   Net::NanoUDPEndpointDevice udp3;
   
   ObjMaster udp1_master;
   ObjMaster udp2_master;
   ObjMaster udp3_master;
 
   Net::PTP::ClientDevice client1;
   Net::PTP::ClientDevice client2;
   Net::PTP::ClientDevice client3;
   
   ObjMaster client1_master;
   ObjMaster client2_master;
   ObjMaster client3_master;
   
   PTPEchoTest task1;
   PTPEchoTest task2;
   PTPEchoTest task3;
   
  public:
  
   explicit Engine(Net::UDPoint dst)
    : udp1("IP",Net::PTPClientUDPort,false,dst),
      udp2("IP",Net::PTPClientUDPort+1,false,dst),
      udp3("IP",Net::PTPClientUDPort+2,false,dst),
      
      udp1_master(udp1,"udp[1]"),
      udp2_master(udp2,"udp[2]"),
      udp3_master(udp3,"udp[3]"),
      
      client1("udp[1]"),
      client2("udp[2]"),
      client3("udp[3]"),
      
      client1_master(client1,"PTPClient[1]"),
      client2_master(client2,"PTPClient[2]"),
      client3_master(client3,"PTPClient[3]"),
      
      task1("PTPClient[1]"),
      task2("PTPClient[2]"),
      task3("PTPClient[3]")
    {
    }
    
   ~Engine()
    {
    } 
    
   void showStat()
    {
     ShowStat(client1,"PTP client1");
     
     ShowStat(client2,"PTP client2");
     
     ShowStat(client3,"PTP client3");
     
     ShowStat(task1,"task1");
     
     ShowStat(task2,"task2");
     
     ShowStat(task3,"task3");
    } 
    
   class StartStop : NoCopy
    {
      PTPEchoTest::StartStop task1;
      PTPEchoTest::StartStop task2;
      PTPEchoTest::StartStop task3;
    
     public:
     
      explicit StartStop(Engine &engine) 
       : task1(engine.task1),
         task2(engine.task2),
         task3(engine.task3)
       {
       }
      
      ~StartStop() {}
    }; 
 };
    
} // namespace Private_3005
 
using namespace Private_3005; 
 
/* Testit<3005> */ 

template<>
const char *const Testit<3005>::Name="Test3005 NanoIPDevice-PTP";

template<>
bool Testit<3005>::Main() 
 { 
  IPEngine ip_engine;
  
  ip_engine.ping(10_sec);
  
  Engine engine(Net::UDPoint(192,168,1,1,Net::PTPServerUDPort));
  
  {
   Engine::StartStop start_stop(engine);
   
   Task::Sleep(10_sec);
  } 
  
  engine.showStat();
  
  ip_engine.showStat();
  
  return true;
 }
 
} // namespace App
 
