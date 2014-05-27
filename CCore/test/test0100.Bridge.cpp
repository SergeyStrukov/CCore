/* test0100.Bridge.cpp */ 
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
#include <CCore/test/testRun.h>
#include <CCore/test/testNet.h>

#include <CCore/inc/net/Bridge.h>
#include <CCore/inc/net/EchoDevice.h>

namespace App {

namespace Private_0100 {
 
/* class Engine */ 

class Engine : NoCopy
 {
   Net::Bridge bridge;
   
   Net::EchoDevice echo;
 
   PacketSource src;
   PacketTask client1;
   PacketTask client2;
   PacketTask client3;
  
  public:
  
   Engine()
    : bridge(10),
      echo(Net::Bridge::ServerName()),
      src(1000,1200),
      client1(src,Net::Bridge::ClientName(1).str),
      client2(src,Net::Bridge::ClientName(2).str),
      client3(src,Net::Bridge::ClientName(3).str)
    {
    }
    
   ~Engine()
    {
    } 
    
   void showStat()
    {
     ShowStat(src,"Src");
     ShowStat(echo,"Echo");
     
     ShowStat(client1,"Client 1");
     ShowStat(client2,"Client 2");
     ShowStat(client3,"Client 3");
    } 
    
   class StartStop : NoCopy
    {
      Net::Bridge::StartStop bridge;
      
      RunTasks run;
    
     public:
     
      explicit StartStop(Engine &engine)
       : bridge(engine.bridge),
         run(engine.src.function_stop())         
       {
        run(engine.client1.function_run());
        run(engine.client2.function_run());
        run(engine.client3.function_run());
       }
       
      ~StartStop() {} 
    }; 
 };
 
} // namespace Private_0100
 
using namespace Private_0100; 
 
/* Testit<100> */ 

template<>
const char *const Testit<100>::Name="Test100 Bridge";

template<>
bool Testit<100>::Main() 
 { 
  Engine engine;
  
  {
   ObjHost::List<ObjInfo> list;
   
   list.build();
   
   ShowRange("ObjInfo",Range(list));
  } 
  
  {
   Engine::StartStop start_stop(engine);
   
   Task::Sleep(10_sec);
  }
  
  engine.showStat();
  
  return true;
 }
 
} // namespace App
 
