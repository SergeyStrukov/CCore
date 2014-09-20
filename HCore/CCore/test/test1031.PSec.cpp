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
#include <CCore/inc/Task.h>

#include <CCore/inc/net/PKE.h>
#include <CCore/inc/net/PSec.h>
#include <CCore/inc/net/PTPClientDevice.h>

#include <CCore/inc/OwnPtr.h>

#include <CCore/inc/net/AsyncUDPDevice.h>

namespace App {

namespace Private_1031 {

/* class DataEngine */

class DataEngine : public MemBase_nocopy
 {
   Net::PSec::EndpointDevice psec;
   
   ObjMaster psec_master;
   
   Net::PTP::ClientDevice ptp;
   
   PacketSet<uint8> pset;
  
   Net::AsyncUDPEndpointDevice::StartStop psec_start_stop;
   
  public:
  
   DataEngine(Net::AsyncUDPEndpointDevice &psec_udp,const Net::PSec::MasterKey &key);
   
   ~DataEngine();
   
   void close();
   
   void test();
   
   void stat();
 };

DataEngine::DataEngine(Net::AsyncUDPEndpointDevice &psec_udp,const Net::PSec::MasterKey &key)
 : psec("psec_udp",key,60_sec),
   psec_master(psec,"psec"),
   ptp("psec"),
   psec_start_stop(psec_udp)
 {
  if( ptp.support(pset) )
    Printf(Con,"PTP support exchange is OK\n");
  else
    Printf(Con,"PTP support exchange has failed\n");
 }

DataEngine::~DataEngine()
 {
 }

void DataEngine::close()
 {
  psec.close();
 }

void DataEngine::test()
 {
 }

void DataEngine::stat()
 {
  {
   Net::PSec::EndpointDevice::StatInfo info;
   
   psec.getStat(info);
   
   Printf(Con,"#;\n\n#;\n",Title("PSec"),info);
  }
  
  {
   Net::PTP::ClientDevice::StatInfo info;
   
   ptp.getStat(info);
   
   Printf(Con,"#;\n\n#;\n",Title("PTP"),info);
  } 
 }

/* struct ConnectParam */

struct ConnectParam
 {
  Net::UDPort pke_port = Net::PKEClientUDPort ;
  Net::UDPort psec_port = Net::PSecClientUDPort ;
  Net::PSec::CryptID crypt_id = Net::PSec::CryptID_AES256 ;
  Net::PSec::HashID hash_id = Net::PSec::HashID_SHA256 ;
  Net::PSec::DHGroupID dhg_id = Net::PSec::DHGroupID_II ;
  
  ConnectParam() {}
  
  template <class S>
  void scan(S &inp)
   {
    Scanf(inp,"#; #; #; #; #;",pke_port,psec_port,crypt_id,hash_id,dhg_id);
   }
 };

/* class ConnectEngine */

class ConnectEngine : public Funchor_nocopy , public MemBase
 {
   Net::AsyncUDPEndpointDevice pke_udp;
  
   ObjMaster pke_udp_master;
 
   Net::AsyncUDPEndpointDevice psec_udp;
  
   ObjMaster psec_udp_master;
   
   Net::PSec::ClientNegotiant pke;
   
   Net::AsyncUDPEndpointDevice::StartStop pke_start_stop;
   
   Sem stop_sem;
   
   enum EventId
    {
     EventStop = 1,
     EventDone = 2,
    
     EventLim
    };
   
   MultiEvent<EventLim-1> mevent;
   
   Mutex mutex;
   
   OwnPtr<DataEngine> engine;
   
  private: 
   
   void handle_done();
   
   void run();
   
   void stop() { mevent.trigger(EventStop); }
   
   void pke_done() { mevent.trigger(EventDone); }
   
   Function<void (void)> function_pke_done() { return FunctionOf(this,&ConnectEngine::pke_done); }
   
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
  
   explicit ConnectEngine(const ConnectParam &param);
   
   ~ConnectEngine();
   
   void close();
   
   template <class Func>
   void cmd(Func func)
    {
     Mutex::Lock lock(mutex);
     
     if( +engine )
       func(*engine);
     else
       Printf(Con,"no connection\n");
    }
 };

void ConnectEngine::handle_done()
 {
  switch( pke.getState() )
    {
     case Net::PSec::ClientNegotiant::State_Done :
      {
       Printf(Con,"\n !connected\n");
       
       try
         {
          Mutex::Lock lock(mutex);
 
          Net::PSec::MasterKeyPtr key;
          
          pke.getSessionKey(key);
          
          engine.set(new DataEngine(psec_udp,*key));
         }
       catch(CatchType)
         {
         }
      }
     break; 
      
     case Net::PSec::ClientNegotiant::State_ClientError :
      {
       Printf(Con,"\n !client error #;\n",pke.getError());
      }
     break; 
      
     case Net::PSec::ClientNegotiant::State_ServerError :
      {
       Printf(Con,"\n !server error #;\n",pke.getError());
      }
     break; 
      
     case Net::PSec::ClientNegotiant::State_Timeout :
      {
       Printf(Con,"\n !timeout\n");
      }
     break; 
    }
 }

void ConnectEngine::run()
 {
  for(;;)
    {
     switch( mevent.wait() )
       {
        case EventStop :
         {
          stop_sem.give();
          
          return;
         }
        break;
        
        case EventDone :
         {
          handle_done();
         }
        break; 
       }
    }
 }

ConnectEngine::ConnectEngine(const ConnectParam &param)
 : pke_udp(param.pke_port,Net::UDPoint(127,0,0,1,Net::PKEServerUDPort)),
   pke_udp_master(pke_udp,"pke_udp"),
   psec_udp(param.psec_port,Net::UDPoint(127,0,0,1,Net::PSecServerUDPort)),
   psec_udp_master(psec_udp,"psec_udp"),
   pke("pke_udp",function_pke_done()),
   pke_start_stop(pke_udp)
 {
  using namespace Net::PSec;
  
  ClientIDPtr client_id(new ClientID("test_client"));
  PrimeKeyPtr client_key(createClientKey());
  PrimeKeyPtr server_key(createServerKey());
  
  pke.prepare(psec_udp.getDevicePort(),client_id,client_key,server_key);
  
  pke.start(CryptAlgoSelect(param.crypt_id,param.hash_id,param.dhg_id));
  
  RunFuncTask( [this] () { run(); } , stop_sem.function_give() );
 }

ConnectEngine::~ConnectEngine()
 {
  stop();
  
  stop_sem.take();
 }

void ConnectEngine::close()
 {
  Mutex::Lock lock(mutex);
  
  if( +engine ) 
    engine->close();
  else
    Printf(Con,"no connection\n");
 }

/* class CommandEngine */ 

class CommandEngine : NoCopy , public CmdInput::Target
 {
   OwnPtr<ConnectEngine> engine;
 
   CmdInputCon<ReadCon> cmd_input;
   bool run_flag;
   
  private:

   template <class Func>
   void cmd(Func func)
    {
     if( +engine )
       {
        engine->cmd(func);
       }
     else
       {
        Printf(Con,"closed\n");
       }
    }
   
   void cmd_nothing(StrLen arg);
   void cmd_open(StrLen arg);
   void cmd_close(StrLen arg);
   void cmd_test(StrLen arg);
   void cmd_stat(StrLen arg);
   void cmd_exit(StrLen arg);
   void cmd_help(StrLen arg);
   
   virtual void buildCmdList(CmdInput &input);
   
  public:

   CommandEngine();

   ~CommandEngine();

   void run();
 };
   
void CommandEngine::cmd_nothing(StrLen)
 {
 }

void CommandEngine::cmd_open(StrLen arg)
 {
  engine.set(0);
  
  ConnectParam param;
  
  if( +arg )
    {
     ScanString inp(arg);
    
     Scanf(inp," #; #;",param,EndOfScan);
     
     if( inp.isFailed() )
       {
        Printf(Con,"invalid arguments\n");
        
        return;
       }
    }

  try
    {
     engine.set(new ConnectEngine(param));
    }
  catch(CatchType)
    {
     return;
    }
 }

void CommandEngine::cmd_close(StrLen)
 {
  if( +engine ) 
    {
     engine->close();
  
     engine.set(0);
    } 
  else
    {
     Printf(Con,"closed\n");
    }
 }

void CommandEngine::cmd_test(StrLen)
 {
  cmd( [] (DataEngine &data) { data.test(); } );
 }

void CommandEngine::cmd_stat(StrLen)
 {
  cmd( [] (DataEngine &data) { data.stat(); } );
 }

void CommandEngine::cmd_exit(StrLen)
 {
  cmd_close({});
  
  run_flag=false;
 }

void CommandEngine::cmd_help(StrLen)
 {
  Putobj(Con,"commands: open close test stat help exit\n");
 }

void CommandEngine::buildCmdList(CmdInput &input)
 {
  addCommand(input,"",&CommandEngine::cmd_nothing);
  addCommand(input,"open",&CommandEngine::cmd_open);
  addCommand(input,"close",&CommandEngine::cmd_close);
  addCommand(input,"test",&CommandEngine::cmd_test);
  addCommand(input,"stat",&CommandEngine::cmd_stat);
  addCommand(input,"exit",&CommandEngine::cmd_exit);
  addCommand(input,"help",&CommandEngine::cmd_help);
 }

CommandEngine::CommandEngine()
 : cmd_input(*this,"PSecTest> ")
 {
 }

CommandEngine::~CommandEngine()
 {
 }
 
void CommandEngine::run()
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
  CommandEngine engine;

  engine.run();
  
  return true;
 }
 
} // namespace App
 
