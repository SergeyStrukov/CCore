/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: PSecEchoTest 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/CharProp.h>
#include <CCore/inc/PrintTitle.h>
#include <CCore/inc/CmdInput.h>
#include <CCore/inc/ReadCon.h>

#include <CCore/inc/net/AsyncUDPDevice.h>
#include <CCore/inc/net/PKE.h>
#include <CCore/inc/net/PSec.h>
#include <CCore/inc/net/PTPEchoTest.h>

namespace App {

/* using */ 

using namespace CCore;

/* functions */

template <class Dev>
void ParseSpace(Dev &dev)
 {
  for(;;++dev)
    {
     typename Dev::Peek peek(dev);

     if( !peek || !CharIsSpace(*peek) ) break; 
    }
 }

template <class Dev>
void ParseUDPoint(Dev &dev,Net::UDPoint &ret)
 {
  Net::UDPoint temp;
  
  Net::ParseIPAddress(dev,temp.address);
  
  ParseChar(dev,':');
  ParseUInt(dev,temp.port);
  
  if( !dev ) return;
  
  ret=temp;
 }

/* classes */

class Proxy;

class Engine;

/* class Proxy */

class Proxy : public ObjBase , public Net::PacketMultipointDevice
 {
   class Engine : NoCopy , public InboundProc , public ConnectionProc 
    {
      Net::PacketMultipointDevice *dev;
      
      AttachmentHost<InboundProc> host;
      
      using Hook = AttachmentHost<InboundProc>::Hook ;
      
     public:
    
      explicit Engine(Net::PacketMultipointDevice *dev_)
       : dev(dev_),
         host("Proxy","Proxy.host")
       {
        dev->attach(this);
       }
      
      ~Engine()
       {
        dev->detach();
       }
      
      StrLen toText(Net::XPoint point,PtrLen<char> buf)
       {
        return dev->toText(point,buf);
       }
       
      PacketFormat getOutboundFormat()
       {
        return dev->getOutboundFormat();
       }
       
      void outbound(Net::XPoint point,Packet<uint8> packet)
       {
        return dev->outbound(point,packet);
       }
       
      ulen getMaxInboundLen()
       {
        return dev->getMaxInboundLen();
       }
      
      void attach(InboundProc *proc) 
       {
        host.attach(proc);
       }
       
      void detach()
       {
        host.detach();
       }
      
      // InboundProc
      
      virtual void inbound(Net::XPoint point,Packet<uint8> packet,PtrLen<const uint8> data)
       {
        Hook hook(host);
        
        if( +hook ) hook->inbound(point,packet,data);
       }
       
      virtual void tick()
       {
        Hook hook(host);
        
        if( +hook ) hook->tick();
       }

      // ConnectionProc
      
      virtual void connection_open(Net::XPoint point)
       {
        Printf(Con,"\n !connect #;\n",Net::PointDesc(dev,point));
       }
        
      virtual void connection_lost(Net::XPoint point)
       {
        Printf(Con,"\n !lost connection #;\n",Net::PointDesc(dev,point));
       }
        
      virtual void connection_close(Net::XPoint point)
       {
        Printf(Con,"\n !close connection #;\n",Net::PointDesc(dev,point));
       }
    };
  
   ObjHook hook;
   
   Engine engine;
  
  public:
 
   explicit Proxy(StrLen mp_dev_name)
    : hook(mp_dev_name),
      engine(hook)
    {
    }
   
   virtual ~Proxy()
    {
    }
   
   // PacketMultipointDevice
   
   virtual StrLen toText(Net::XPoint point,PtrLen<char> buf) { return engine.toText(point,buf); }
    
   virtual PacketFormat getOutboundFormat() { return engine.getOutboundFormat(); }
    
   virtual void outbound(Net::XPoint point,Packet<uint8> packet) { engine.outbound(point,packet); }
    
   virtual ulen getMaxInboundLen() { return engine.getMaxInboundLen(); }
   
   virtual void attach(InboundProc *proc) { engine.attach(proc); }
    
   virtual void detach() { engine.detach(); }
 };

/* class Engine */ 

class Engine : public CmdInput::Target
 {
   // params 
  
   class AlgoSet : public Net::PSec::AlgoSet
    {
     public:
     
      AlgoSet()
       {
        addDefault();
       }
      
      ~AlgoSet() 
       {
       }
    };
   
   AlgoSet algo_set;
  
   class ClientDatabase : NoCopy , public Net::PSec::ClientDatabase
    {
      DynArray<uint8> name;
    
     private: 
      
      Net::PSec::AbstractHashFunc * createClientKey() const
       {
        using namespace Net::PSec;
        
        uint8 buf[]={1,2,3,4,5};
        
        return CreateKeyedHash(HashID_SHA256,Range_const(buf));
       }
      
     public:
    
      explicit ClientDatabase(StrLen name_)
       : name(DoCast(name_.len),name_.ptr)
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
              client_key.set(createClientKey());
              
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
   
   Net::PSec::AbstractHashFunc * createServerKey() const
    {
     using namespace Net::PSec;
     
     uint8 buf[]={6,7,8,9,0};
     
     return CreateKeyedHash(HashID_SHA256,Range_const(buf));
    }

   // devices  
  
   Net::AsyncUDPMultipointDevice psec_udp;
  
   ObjMaster psec_udp_master;

   Net::AsyncUDPMultipointDevice pke_udp;
   
   ObjMaster pke_udp_master;
   
   Net::PSec::MultipointDevice psec;
   
   ObjMaster psec_master;
   
   Net::PSec::ServerNegotiant pke;
   
   Proxy proxy;
   
   ObjMaster proxy_master;
   
   Net::PTP::ServerDevice ptp;
   
   ObjMaster ptp_master;

   Net::PTP::EchoTest echo;
   
   CmdInputCon<ReadCon> cmd_input;
   bool run_flag;

   // stat info base
   
   Net::AsyncUDPMultipointDevice::StatInfo base_udp_info;
   Net::PTP::ServerDevice::StatInfo base_info;
   
  private:

   void clearStat();

   void printStat();

   void cmd_nothing(StrLen arg);
   void cmd_exit(StrLen arg);
   void cmd_stat(StrLen arg);
   void cmd_clear(StrLen arg);
   void cmd_psecstat(StrLen arg);
   void cmd_close(StrLen arg);
   void cmd_help(StrLen arg);
   
   virtual void buildCmdList(CmdInput &input);
   
  public:

   Engine();

   ~Engine();

   int run();
 };
 
void Engine::clearStat()
 {
  psec_udp.getStat(base_udp_info);
  
  ptp.getStat(base_info);
 }
 
void Engine::printStat()
 {
  Net::AsyncUDPMultipointDevice::StatInfo udp_info;
  
  psec_udp.getStat(udp_info);
  
  udp_info-=base_udp_info;
  
  Net::PTP::ServerDevice::StatInfo info;
  
  ptp.getStat(info);
  
  info-=base_info;
 
  Printf(Con,"\n#15;\n#15;\n",info,udp_info);
 }
 
void Engine::cmd_nothing(StrLen)
 {
 }

void Engine::cmd_exit(StrLen)
 {
  printStat();
  
  run_flag=false;
 }

void Engine::cmd_stat(StrLen)
 {
  printStat();
 }

void Engine::cmd_clear(StrLen)
 {
  clearStat();
 }

void Engine::cmd_psecstat(StrLen arg)
 {
  if( !arg )
    {
     Putch(Con,'\n');
     
     psec.processStat( [this] (Net::XPoint point,const Net::PSec::MultipointDevice::StatInfo &info) 
                              {
                               Printf(Con,"#;\n\n#;\n",PrintTitle(Net::PointDesc(&psec,point)),info); 
                              } );
    }
  else
    {
     StrParse dev(arg);
     
     Net::UDPoint udpoint;
     
     ParseSpace(dev);
     ParseUDPoint(dev,udpoint);
     ParseSpace(dev);
     
     if( !dev.finish() )
       {
        Printf(Con,"invalid argument\n");
       }
     else
       {
        Net::PSec::MultipointDevice::StatInfo info;
       
        if( psec.getStat(udpoint.get(),info) )
          Printf(Con,"\n#;\n",info);
        else
          Printf(Con,"no such connection\n");
       }
    }
 }

void Engine::cmd_close(StrLen arg)
 {
  if( !arg )
    {
     ulen count=psec.closeAll();
     
     Printf(Con,"#; connections are closed\n",count);
    }
  else
    {
     StrParse dev(arg);
     
     Net::UDPoint udpoint;
     
     ParseSpace(dev);
     ParseUDPoint(dev,udpoint);
     ParseSpace(dev);
     
     if( !dev.finish() )
       {
        Printf(Con,"invalid argument\n");
       }
     else
       {
        if( psec.close(udpoint.get()) )
          Printf(Con,"connecton is closed\n");
        else
          Printf(Con,"no such connection\n");
       }
    }
 }

void Engine::cmd_help(StrLen)
 {
  Putobj(Con,"commands: stat clear psecstat close help exit\n");
 }

void Engine::buildCmdList(CmdInput &input)
 {
  addCommand(input,"",&Engine::cmd_nothing);
  addCommand(input,"exit",&Engine::cmd_exit);
  addCommand(input,"stat",&Engine::cmd_stat);
  addCommand(input,"clear",&Engine::cmd_clear);
  addCommand(input,"psecstat",&Engine::cmd_psecstat);
  addCommand(input,"close",&Engine::cmd_close);
  addCommand(input,"help",&Engine::cmd_help);
 }
 
Engine::Engine()
 : client_db("test_client"),
   psec_udp(Net::PSecServerUDPort),
   psec_udp_master(psec_udp,"psec_udp"),
   pke_udp(Net::PKEServerUDPort),
   pke_udp_master(pke_udp,"pke_udp"),
   psec("psec_udp",algo_set.getAlgoLens(),1000,60_sec),
   psec_master(psec,"psec"),
   pke("pke_udp",client_db,psec,100,30_sec),
   proxy("psec"),
   proxy_master(proxy,"proxy-psec"),
   ptp("proxy-psec"),
   ptp_master(ptp,"ptp"),
   echo("ptp"),
   cmd_input(*this,"PSecEcho> ")
 {
  Net::PSec::PrimeKeyPtr server_key(createServerKey());

  pke.prepare(server_key);

  pke.start(algo_set.getAlgoList());
 }
 
Engine::~Engine()
 {
 }
 
int Engine::run()
 {
  Net::AsyncUDPMultipointDevice::StartStop psec_start_stop(psec_udp);
  Net::AsyncUDPMultipointDevice::StartStop pke_start_stop(pke_udp);

  for(run_flag=true; run_flag ;) cmd_input.command();
  
  return 0;
 }
 
} // namespace App
 
/* main() */ 

using namespace App;

int main()
 {
  ReportException report;
  
  try
    {
     int ret;
     
     {
      Putobj(Con,"--- PSecEchoTest 1.00 ---\n--- Copyright (c) 2014 Sergey Strukov. All rights reserved. ---\n\n");
      
      Engine engine;

      ret=engine.run();
     }
     
     report.guard();

     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
 
