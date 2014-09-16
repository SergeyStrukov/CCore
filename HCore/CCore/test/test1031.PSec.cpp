/* test1031.PSec.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: HCore 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/CmdInput.h>
#include <CCore/inc/ReadCon.h>
#include <CCore/inc/Scanf.h>

#include <CCore/inc/net/PKE.h>
#include <CCore/inc/net/PSec.h>

#include <CCore/inc/OwnPtr.h>

#include <CCore/inc/net/AsyncUDPDevice.h>

namespace App {

namespace Private_1031 {

/* class DataEngine */

class DataEngine : public Funchor_nocopy , public MemBase
 {
   Net::AsyncUDPEndpointDevice pke_udp;
  
   ObjMaster pke_udp_master;
 
   Net::AsyncUDPEndpointDevice psec_udp;
  
   ObjMaster psec_udp_master;
   
   Net::PSec::ClientNegotiant pke;
   
   Net::AsyncUDPEndpointDevice::StartStop pke_start_stop;

  private: 
   
   void pke_done()
    {
     Printf(Con,"\nconnected\n");
    
     //sem.give();
    }
   
   Function<void (void)> function_pke_done() { return FunctionOf(this,&DataEngine::pke_done); }
   
   Net::PSec::AbstractHashFunc * createClientKey() const
    {
     using namespace Net::PSec;
     
     uint8 buf[]={1,2,3,4,5};
     
     return CreateKeyedHash(HashID_SHA256,Range_const(buf));
    }
   
   Net::PSec::AbstractHashFunc * createServerKey() const
    {
     using namespace Net::PSec;
     
     uint8 buf[]={6,7,8,9,0};
     
     return CreateKeyedHash(HashID_SHA256,Range_const(buf));
    }
   
  public:
  
   DataEngine(Net::UDPort pke_port,Net::UDPort psec_port);
   
   DataEngine() : DataEngine(Net::PKEClientUDPort,Net::PSecClientUDPort) {}
   
   ~DataEngine();
   
   void close();
 };

DataEngine::DataEngine(Net::UDPort pke_port,Net::UDPort psec_port)
 : pke_udp(pke_port,Net::UDPoint(127,0,0,1,Net::PKEServerUDPort)),
   pke_udp_master(pke_udp,"pke_udp"),
   psec_udp(psec_port,Net::UDPoint(127,0,0,1,Net::PSecServerUDPort)),
   psec_udp_master(psec_udp,"psec_udp"),
   pke("pke_udp",function_pke_done()),
   pke_start_stop(pke_udp)
 {
  using namespace Net::PSec;
  
  ClientIDPtr client_id(new ClientID("test_client"));
  PrimeKeyPtr client_key(createClientKey());
  PrimeKeyPtr server_key(createServerKey());
  
  pke.prepare(psec_udp.getDevicePort(),client_id,client_key,server_key);
  
  pke.start(CryptAlgoSelect(CryptID_AES256,HashID_SHA256,DHGroupID_II));
 }

DataEngine::~DataEngine()
 {
 }

void DataEngine::close()
 {
 }

/* class Engine */ 

class Engine : NoCopy , public CmdInput::Target
 {
   OwnPtr<DataEngine> engine;
 
   CmdInputCon<ReadCon> cmd_input;
   bool run_flag;
   
  private:

   void cmd_nothing(StrLen arg);
   void cmd_open(StrLen arg);
   void cmd_close(StrLen arg);
   void cmd_exit(StrLen arg);
   void cmd_help(StrLen arg);
   
   virtual void buildCmdList(CmdInput &input);
   
  public:

   Engine();

   ~Engine();

   void run();
 };
   
void Engine::cmd_nothing(StrLen)
 {
 }

void Engine::cmd_open(StrLen arg)
 {
  if( +arg )
    {
     ScanString inp(arg);
    
     Net::UDPort pke_port;
     Net::UDPort psec_port;

     Scanf(inp," #; #; ",pke_port,psec_port);
     
     if( inp.isOk() )
       {
        engine.set(new DataEngine(pke_port,psec_port));
       }
     else
       {
        Printf(Con,"invalid argument\n");
       }
    }
  else
    {
     engine.set(new DataEngine());
    }
 }

void Engine::cmd_close(StrLen)
 {
  if( +engine ) 
    {
     engine->close();
  
     engine.set(0);
    } 
 }

void Engine::cmd_exit(StrLen)
 {
  cmd_close({});
  
  run_flag=false;
 }

void Engine::cmd_help(StrLen)
 {
  Putobj(Con,"commands: open close help exit\n");
 }

void Engine::buildCmdList(CmdInput &input)
 {
  addCommand(input,"",&Engine::cmd_nothing);
  addCommand(input,"open",&Engine::cmd_open);
  addCommand(input,"close",&Engine::cmd_close);
  addCommand(input,"exit",&Engine::cmd_exit);
  addCommand(input,"help",&Engine::cmd_help);
 }

Engine::Engine()
 : cmd_input(*this,"PSecTest> ")
 {
 }

Engine::~Engine()
 {
 }
 
void Engine::run()
 {
  for(run_flag=true; run_flag ;) cmd_input.command();
 }

} // namespace Private_1031
 
using namespace Private_1031; 
 
/* Testit<1031> */ 

template<>
const char *const Testit<1031>::Name="Test1031 PSec";

template<>
bool Testit<1031>::Main() 
 {
  Engine engine;

  engine.run();
  
  return true;
 }
 
} // namespace App
 
