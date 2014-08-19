/* test0107.PKE.cpp */ 
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

#include <CCore/inc/net/Bridge.h>
#include <CCore/inc/net/PKE.h>

namespace App {

namespace Private_0107 {

/* class Engine */

class Engine : public Funchor_nocopy
 {
   Net::Bridge bridge;
   
   class ClientDataBase : NoCopy , public Net::PSec::AbstractClientDataBase
    {
     public:
    
      ClientDataBase()
       {
       }
      
      ~ClientDataBase()
       {
       }
      
      // Net::PSec::AbstractClientDataBase
      
      virtual bool findClient(PtrLen<const uint8> client_id,Net::PSec::PrimeKey &client_key,Net::PSec::ClientProfile &client_profile)
       {
        return true;
       }
    };
   
   class EndpointManager : NoCopy , public Net::PSec::AbstractEndpointManager
    {
     public:
    
      EndpointManager()
       {
       }
      
      ~EndpointManager()
       {
       }
      
      // Net::PSec::AbstractEndpointManager
      
      virtual ulen getBufLen() const
       {
       }
      
      virtual StrLen createName(char buf[ /* BufLen */ ])
       {
       }
      
      virtual void open(StrLen ep_dev_name,Net::PSec::SKey &skey,Net::PSec::ClientProfile &client_profile)
       {
       }
    };
   
   Net::PSec::ClientNegotiant client;
   
   ClientDataBase client_db;
   EndpointManager epman;
   
   Net::PSec::ServerNegotiant server;
   
   Sem sem;
   
  private:
   
   void client_done()
    {
     sem.give();
    }
   
   Function<void (void)> function_done() { return FunctionOf(this,&Engine::client_done); }

  public:
   
   Engine()
    : bridge(10),
      client(Net::Bridge::ClientName(1).str,function_done()),
      server(Net::Bridge::ServerName(),client_db,epman)
    {
    }
   
   ~Engine()
    {
    }

   void prepare()
    {
     {
      Net::PSec::ClientID client_id;
      Net::PSec::PrimeKey client_key;
      Net::PSec::PrimeKey server_key;
     
      client.prepare(client_id,client_key,server_key);
     }
     
     {
      Net::PSec::PrimeKey server_key;
      
      server.prepare(server_key);
     }
    }
   
   void start()
    {
     server.start();
     
     client.start(Net::PSec::CryptAlgoSelect(Net::PSec::CryptID_AES128,Net::PSec::HashID_SHA256,Net::PSec::DHGroupID_I));
    }
   
   void wait(MSec timeout)
    {
     sem.take(timeout);
    }
   
   class StartStop : NoCopy
    {
      Net::Bridge::StartStop bridge;
    
     public:
     
      explicit StartStop(Engine &engine)
       : bridge(engine.bridge)
       {
       }
       
      ~StartStop() 
       {
       } 
    }; 
 };

} // namespace Private_0107
 
using namespace Private_0107; 
 
/* Testit<107> */ 

template<>
const char *const Testit<107>::Name="Test107 PKE";

template<>
bool Testit<107>::Main()
 {
  Engine engine;
  
  {
   Engine::StartStop start_stop(engine);
   
   engine.prepare();
   
   engine.start();
   
   engine.wait(200_sec);
  }
  
  return true;
 }
 
} // namespace App
 
