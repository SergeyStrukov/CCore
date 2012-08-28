/* test0101.PTP.cpp */ 
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

#include <CCore/test/test.h>
#include <CCore/test/testNet.h>

#include <CCore/inc/net/Bridge.h>
#include <CCore/inc/net/PTPEchoTest.h>

namespace App {

namespace Private_0101 {

/* class Engine */  

class Engine : NoCopy
 {
   Net::Bridge bridge;
   
   Net::PTP::ClientDevice client1;
   Net::PTP::ClientDevice client2;
   Net::PTP::ServerDevice server;
   
   ObjMaster server_master;
   ObjMaster client1_master;
   ObjMaster client2_master;
   
   Net::PTP::EchoTest echo;
   
   PTPEchoTest task1;
   PTPEchoTest task2;
   
  public:
  
   Engine()
    : bridge(2),
    
      client1(Net::Bridge::ClientName(1).str),
      client2(Net::Bridge::ClientName(2).str),
      server(Net::Bridge::ServerName()),
      
      server_master(server,"PTPServer"),
      client1_master(client1,"PTPClient[1]"),
      client2_master(client2,"PTPClient[2]"),
      
      echo("PTPServer"),
      
      task1("PTPClient[1]"),
      task2("PTPClient[2]")
    {
     bridge.setDropRate(1,100000);
    }
    
   ~Engine()
    {
    } 
    
   void showStat()
    {
     ShowStat(server,"PTP server");
     
     ShowStat(client1,"PTP client1");
     
     ShowStat(client2,"PTP client2");
     
     ShowStat(task1,"task1");
     
     ShowStat(task2,"task2");
    } 
    
   class StartStop : NoCopy
    {
      Net::Bridge::StartStop bridge;
      PTPEchoTest::StartStop task1;
      PTPEchoTest::StartStop task2;
    
     public:
     
      explicit StartStop(Engine &engine) 
       : bridge(engine.bridge),
         task1(engine.task1),
         task2(engine.task2)
       {
       }
      
      ~StartStop() {}
    }; 
 };
 
} // namespace Private_0101
 
using namespace Private_0101; 
 
/* Testit<101> */ 

template<>
const char *const Testit<101>::Name="Test101 PTP";

template<>
bool Testit<101>::Main() 
 { 
  Engine engine;
  TaskEventRecorder recorder(100_MByte);
  
  {
   TaskEventHostType::StartStop event_start_stop(TaskEventHost,&recorder);
   Engine::StartStop start_stop(engine);
  
   Task::Sleep(10_sec);
  }
  
  engine.showStat(); 
  
  StreamFile dev("test101.bin");
  
  dev(recorder);
  
  return true;
 }
 
} // namespace App
 
