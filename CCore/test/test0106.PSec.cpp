/* test0106.PSec.cpp */ 
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
#include <CCore/test/testRun.h>
#include <CCore/test/testNet.h>

#include <CCore/inc/net/SingleBridge.h>
#include <CCore/inc/net/SingleEchoDevice.h>
#include <CCore/inc/net/PSec.h>

namespace App {

namespace Private_0106 {

/* class Engine */ 

class Engine : NoCopy
 {
   Net::SingleBridge bridge;
   Net::PSec::EndpointDevice server_psec;
   Net::PSec::EndpointDevice client_psec;
   
   ObjMaster server_psec_master;
   ObjMaster client_psec_master;
   
   Net::SingleEchoDevice echo;
 
   PacketSource src;
   PacketTask client;
  
  public:
  
   Engine(PacketFormat format,const Net::PSec::MasterKey &master_key)
    : bridge(format,format),
      server_psec(Net::SingleBridge::ServerName(),master_key),
      client_psec(Net::SingleBridge::ClientName(),master_key),
      server_psec_master(server_psec,"server_psec"),
      client_psec_master(client_psec,"client_psec"),
      echo("server_psec"),
      src(1000,1200),
      client(src,"client_psec")
    {
    }
    
   ~Engine()
    {
    } 
    
   void showStat()
    {
     ShowStat(src,"Src");
     ShowStat(echo,"Echo");
     ShowStat(client,"Client");
    } 
    
   class StartStop : NoCopy
    {
      Net::SingleBridge::StartStop bridge;
      
      RunTasks run;
    
     public:
     
      explicit StartStop(Engine &engine)
       : bridge(engine.bridge),
         run(engine.src.function_stop())         
       {
        run(engine.client.function_run());
       }
       
      ~StartStop() {} 
    }; 
 };

} // namespace Private_0106
 
using namespace Private_0106; 
 
/* Testit<106> */ 

template<>
const char *const Testit<106>::Name="Test106 PSec";

template<>
bool Testit<106>::Main() 
 {
  PacketFormat format;
  
  format.prefix=0;
  format.suffix=0;
  format.max_data=1472;
  
  Net::PSec::TestMasterKey master_key;
  
  Engine engine(format,master_key);
  
  {
   Engine::StartStop start_stop(engine);
   
   Task::Sleep(10_sec);
  }
  
  engine.showStat();
  
  return true;
 }
 
} // namespace App
 
