/* test1019.UDP.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/WIN32
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

#include <CCore/inc/net/UDPDevice.h>
#include <CCore/inc/net/EchoDevice.h>

namespace App {

namespace Private_1019 {

/* class Engine */ 

class Engine : NoCopy
 {
   Net::UDPMultipointDevice server;
   Net::UDPEndpointDevice client;
   
   ObjMaster server_master;
   ObjMaster client_master;
   
   Net::EchoDevice echo;
   PacketEchoTest test;
   
  public: 
   
   Engine()
    : server(55000),
      client(55001,Net::UDPoint(127,0,0,1,55000)),
      
      server_master(server,"server"),
      client_master(client,"client"),
      
      echo("server"),
      test("client")
    {
    }  
   
   ~Engine()
    {
    }
    
   void send(ulen forward,ulen cnt) { test.run(forward,cnt); }
   
   void showStat()
    {
     ShowStat(echo,"Echo");
     
     Printf(Con,"traffic = #;\n\n",echo.getTraffic());
     
     ShowStat(server,"UDP server");
     ShowStat(client,"UDP client");
    }
    
   class StartStop : NoCopy
    {
      Net::UDPMultipointDevice::StartStop server;
      Net::UDPEndpointDevice::StartStop client;
    
     public:
     
      explicit StartStop(Engine &engine) 
       : server(engine.server),
         client(engine.client)
       {
        Task::Sleep(1_sec);
       }
      
      ~StartStop() 
       {
        Task::Sleep(1_sec);
       }
    };
 };
 
} // namespace Private_1019
 
using namespace Private_1019; 
 
/* Testit<1019> */ 

template<>
const char *const Testit<1019>::Name="Test1019 UDP";

template<>
bool Testit<1019>::Main() 
 { 
  Engine engine;
  
  {
   Engine::StartStop start_stop(engine);
  
   engine.send(5,100000);
  } 
  
  engine.showStat();
 
  return true;
 }
 
} // namespace App
 
