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
#include <CCore/inc/crypton/SHA.h>

namespace App {

namespace Private_0107 {

/* class Engine */

class Engine : public Funchor_nocopy
 {
   Net::Bridge bridge;
   
   class ClientDataBase : NoCopy , public Net::PSec::AbstractClientDataBase
    {
      Engine *engine;
    
      DynArray<uint8> name;
      
     public:
    
      ClientDataBase(Engine *engine_,StrLen name_)
       : engine(engine_),name(DoCast(name_.len),name_.ptr)
       {
       }
      
      virtual ~ClientDataBase()
       {
       }
      
      // Net::PSec::AbstractClientDataBase
      
      virtual bool findClient(PtrLen<const uint8> client_id,Net::PSec::PrimeKeyPtr &client_key,Net::PSec::ClientProfilePtr &client_profile)
       {
        if( client_id.equal(Range(name)) )
          {
           SilentReportException report;
          
           try
             {
              client_key.set(engine->createClientKey());
              
              client_profile.set(new Net::PSec::AbstractClientProfile());
             
              return true;
             }
           catch(...)
             {
              return false;
             }
          }
        
        return false;
       }
    };
   
   class EndpointManager : NoCopy , public Net::PSec::AbstractEndpointManager
    {
     public:
    
      EndpointManager()
       {
       }
      
      virtual ~EndpointManager()
       {
       }
      
      // Net::PSec::AbstractEndpointManager
      
      virtual void open(Net::XPoint point,Net::PSec::MasterKeyPtr &skey,Net::PSec::ClientProfilePtr &client_profile)
       {
        Used(skey);
        Used(client_profile);
        
        Printf(Con,"open(#;)\n",point);
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

   Net::PSec::AbstractHashFunc * createClientKey() const
    {
     using namespace Net::PSec;
     
     uint8 buf[]={1,2,3,4,5};
     
     return new HashPrimeKey(HashID_SHA256,Range_const(buf));
    }
   
   Net::PSec::AbstractHashFunc * createServerKey() const
    {
     using namespace Net::PSec;
     
     uint8 buf[]={6,7,8,9,0};
     
     return new HashPrimeKey(HashID_SHA256,Range_const(buf));
    }
   
  public:
   
   Engine()
    : bridge(10),
      client(Net::Bridge::ClientName(1).str,function_done()),
      client_db(this,"client"),
      server(Net::Bridge::ServerName(),client_db,epman)
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
     
      client.prepare(client_id,client_key,server_key);
     }
     
     {
      PrimeKeyPtr server_key(createServerKey());
      
      server.prepare(server_key);
     }
    }
   
   void start()
    {
     using namespace Net::PSec;
     
     server.start();
     
     client.start(CryptAlgoSelect(CryptID_AES128,HashID_SHA256,DHGroupID_I));
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
   
   engine.wait(10_sec);
  }
  
  return true;
 }
 
} // namespace App
 
