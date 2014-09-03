/* test1030.PKE.cpp */ 
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
#include <CCore/test/testRun.h>

#include <CCore/inc/net/AsyncUDPDevice.h>
#include <CCore/inc/net/PKE.h>
#include <CCore/inc/net/PSec.h>
#include <CCore/inc/crypton/SHA.h>

namespace App {

namespace Private_1030 {

/* class Engine */

class Engine : public Funchor_nocopy
 {
   Net::AsyncUDPEndpointDevice client_pke_ep;
   Net::AsyncUDPEndpointDevice client_psec_ep;
   
   ObjMaster client_pke_master;
   ObjMaster client_psec_master;
  
   Net::PSec::ClientNegotiant client_negotiant;
   
   Net::AsyncUDPMultipointDevice server_pke_mp;
   Net::AsyncUDPMultipointDevice server_psec_mp;
   
   ObjMaster server_pke_master;
   ObjMaster server_psec_master;
  
   class ClientDatabase : NoCopy , public Net::PSec::ClientDatabase
    {
      Engine *engine;
    
      DynArray<uint8> name;
      
     public:
    
      ClientDatabase(Engine *engine_,StrLen name_)
       : engine(engine_),
         name(DoCast(name_.len),name_.ptr)
       {
       }
      
      ~ClientDatabase()
       {
       }
      
      // Net::PSec::ClientDatabase
      
      virtual FindErrorCode findClient(PtrLen<const uint8> client_id,Net::PSec::PrimeKeyPtr &client_key,Net::PSec::ClientProfilePtr &client_profile) const
       {
        if( client_id.equal(Range(name)) )
          {
           SilentReportException report;
          
           try
             {
              client_key.set(engine->createClientKey());
              
              client_profile.set(new Net::PSec::AbstractClientProfile());
             
              return Find_Ok;
             }
           catch(...)
             {
              return FindError_NoMemory;
             }
          }
        
        return FindError_NoClientID;
       }
    };
   
   ClientDatabase client_db;
   
   Net::PSec::MultipointDevice server_psec;
  
   Net::PSec::ServerNegotiant server_negotiant;
  
   Sem sem;
   
  private:
    
   void client_done()
    {
     sem.give();
    }
   
   Function<void (void)> function_done() { return FunctionOf(this,&Engine::client_done); }
 
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
    
   Engine()
    : client_pke_ep(Net::PKEClientUDPort,Net::UDPoint(Net::IPAddress(127,0,0,1),Net::PKEServerUDPort)),
      client_psec_ep(Net::PSecClientUDPort,Net::UDPoint(Net::IPAddress(127,0,0,1),Net::PSecServerUDPort)),
      client_pke_master(client_pke_ep,"ClientPKE"),
      client_psec_master(client_psec_ep,"ClientPSec"),
      client_negotiant("ClientPKE",function_done()),
      
      server_pke_mp(Net::PKEServerUDPort),
      server_psec_mp(Net::PSecServerUDPort),
      server_pke_master(server_pke_mp,"ServerPKE"),
      server_psec_master(server_psec_mp,"ServerPSec"),       
      
      client_db(this,"client"),
      server_psec("ServerPSec",Empty,10),
      server_negotiant("ServerPKE",client_db,server_psec)
    {
    }
    
   ~Engine()
    {
    }

   void prepare()
    {
     using namespace Net::PSec;
     
     {
      ClientIDPtr client_id(new ClientID("client"));
      PrimeKeyPtr client_key(createClientKey());
      PrimeKeyPtr server_key(createServerKey());
     
      client_negotiant.prepare(client_id,client_key,server_key);
     }
     
     {
      PrimeKeyPtr server_key(createServerKey());
      
      server_negotiant.prepare(server_key);
     }
    }
   
   void start()
    {
     using namespace Net::PSec;
     
     server_negotiant.start(CryptAlgoSelect(CryptID_AES128,HashID_SHA256,DHGroupID_I));
     
     client_negotiant.start(CryptAlgoSelect(CryptID_AES128,HashID_SHA256,DHGroupID_I));
    }
   
   bool wait(MSec timeout)
    {
     return sem.take(timeout);
    }
   
   class StartStop : NoCopy
    {
      Net::AsyncUDPEndpointDevice::StartStop client_pke_ep;
      Net::AsyncUDPEndpointDevice::StartStop client_psec_ep;
    
      Net::AsyncUDPMultipointDevice::StartStop server_pke_mp;
      Net::AsyncUDPMultipointDevice::StartStop server_psec_mp;
      
     public:
     
      explicit StartStop(Engine &engine)
       : client_pke_ep(engine.client_pke_ep),
         client_psec_ep(engine.client_psec_ep),
         server_pke_mp(engine.server_pke_mp),
         server_psec_mp(engine.server_psec_mp)
       {
       }
       
      ~StartStop()
       {
       } 
    }; 
 };

} // namespace Private_1030
 
using namespace Private_1030; 
 
/* Testit<1030> */ 

template<>
const char *const Testit<1030>::Name="Test1030 PKE";

template<>
bool Testit<1030>::Main() 
 {
  Engine engine;
  
  {
   Engine::StartStop start_stop(engine);
   
   engine.prepare();
   
   engine.start();
   
   if( engine.wait(10_sec) )
     {
      Printf(Con,"client done\n");
      
      // TODO
     }
  }
  
  return true;
 }
 
} // namespace App
 
