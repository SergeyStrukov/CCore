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
   
   class EndpointManager : NoCopy , public Net::PSec::EndpointManager
    {
     public:
    
      EndpointManager()
       {
       }
      
      ~EndpointManager()
       {
       }
      
      // Net::PSec::EndpointManager
      
      virtual OpenErrorCode open(Net::XPoint pke_point,Net::PSec::MasterKeyPtr &skey,Net::PSec::ClientProfilePtr &client_profile)
       {
        Used(skey);
        Used(client_profile);
        
        Printf(Con,"open(#;)\n",pke_point);
        
        return Open_Ok;
       }
      
      virtual bool close(Net::XPoint psec_point)
       {
        Used(psec_point);
        
        return false;
       }

      virtual ulen closeAll()
       {
        return 0;
       }
      
      virtual Net::PSec::AbstractClientProfile * getClientProfile(Net::XPoint psec_point)
       {
        Used(psec_point);
        
        return 0;
       }
    };
   
   Net::PSec::ClientNegotiant client;
   
   ClientDatabase client_db;
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
    : bridge(10),
      client(Net::Bridge::ClientName(1).str,function_done()),
      client_db(this,"client"),
      server(Net::Bridge::ServerName(),client_db,epman,10)
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
     
      client.prepare(0,client_id,client_key,server_key);
     }
     
     {
      PrimeKeyPtr server_key(createServerKey());
      
      server.prepare(server_key);
     }
    }
   
   void start()
    {
     using namespace Net::PSec;
     
     server.start(CryptAlgoSelect(CryptID_AES128,HashID_SHA256,DHGroupID_I));
     
     client.start(CryptAlgoSelect(CryptID_AES128,HashID_SHA256,DHGroupID_I));
    }
   
   bool wait(MSec timeout)
    {
     return sem.take(timeout);
    }
   
   void show()
    {
     Printf(Con,"#;\n#;\n",client.getState(),client.getError());
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
   
   if( engine.wait(10_sec) )
     {
      Task::Sleep(10_msec);
     
      engine.show();
     }
   else
     {
      Printf(Con,"timeout\n");
     }
  }
  
  return true;
 }
 
} // namespace App
 
