/* test0088.NetFork.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testNet.h>

#include <CCore/inc/net/Bridge.h>
#include <CCore/inc/net/PTPEchoTest.h>
#include <CCore/inc/net/NetFork.h>

namespace App {

namespace Private_0088 {

/* class Engine1 */  

class Engine1 : NoCopy
 {
   Net::Bridge bridge;
   
   Net::EndpointNetFork fork1; 
   Net::EndpointNetFork fork2;
   
   ObjMaster fork1_master;
   ObjMaster fork2_master;
   
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
  
   Engine1()
    : bridge(2),
      
      fork1(Net::Bridge::ClientName(1).str,4,100),
      fork2(Net::Bridge::ClientName(2).str,4,100),
      
      fork1_master(fork1,"fork[1]"),
      fork2_master(fork2,"fork[2]"),
    
      client1("fork[1]"),
      client2("fork[2]"),
      server(Net::Bridge::ServerName()),
      
      server_master(server,"PTPServer"),
      client1_master(client1,"PTPClient[1]"),
      client2_master(client2,"PTPClient[2]"),
      
      echo("PTPServer"),
      
      task1("PTPClient[1]"),
      task2("PTPClient[2]")
    {
    }
    
   ~Engine1()
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
     
      explicit StartStop(Engine1 &engine) 
       : bridge(engine.bridge),
         task1(engine.task1),
         task2(engine.task2)
       {
       }
      
      ~StartStop() {}
    }; 
 };

/* class Engine2 */  

class Engine2 : NoCopy
 {
   Net::Bridge bridge;
   
   Net::MultipointNetFork fork; 
   
   ObjMaster fork_master;
   
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
  
   Engine2()
    : bridge(2),
      
      fork(Net::Bridge::ServerName(),4,100),
      
      fork_master(fork,"fork"),
    
      client1(Net::Bridge::ClientName(1).str),
      client2(Net::Bridge::ClientName(2).str),
      server("fork"),
      
      server_master(server,"PTPServer"),
      client1_master(client1,"PTPClient[1]"),
      client2_master(client2,"PTPClient[2]"),
      
      echo("PTPServer"),
      
      task1("PTPClient[1]"),
      task2("PTPClient[2]")
    {
    }
    
   ~Engine2()
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
     
      explicit StartStop(Engine2 &engine) 
       : bridge(engine.bridge),
         task1(engine.task1),
         task2(engine.task2)
       {
       }
      
      ~StartStop() {}
    }; 
 };

/* Test() */

template <class Engine>
void Test(StrLen file_name)
 {
  Engine engine;
  TaskEventRecorder recorder(100_MByte);
  
  {
   TickTask tick_task; 
   TaskEventHostType::StartStop event_start_stop(TaskEventHost,&recorder);
   typename Engine::StartStop start_stop(engine);
  
   Task::Sleep(10_sec);
  }
  
  engine.showStat(); 
  
  StreamFile dev(file_name);
  
  dev(recorder);
 }

} // namespace Private_0088
 
using namespace Private_0088; 
 
/* Testit<88> */ 

template<>
const char *const Testit<88>::Name="Test0088 NetFork";

template<>
bool Testit<88>::Main() 
 {
  Test<Engine1>("test88.1.bin");
  Test<Engine2>("test88.2.bin");
  
  return true;
 }
 
} // namespace App
 
