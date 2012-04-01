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

/* functions */ 

template <class R>
void ShowRange(const char *title,R r)
 {
  Printf(Con,"#;\n\n",Title(title));
  
  for(; +r ;++r) Printf(Con,"#;\n",*r);
  
  Printf(Con,"\n");
 }
 
/* class PacketSource */  
 
class PacketSource : public Funchor_nocopy
 {
  public:
  
   enum Event
    {
     Event_nofill,
     Event_broken,
    
     EventLim
    };
   
   friend const char * GetTextDesc(Event ev);
   
   typedef Counters<Event,EventLim> StatInfo;
  
  private:
  
   PacketSet<uint8> pset;
   Atomic run_flag;
   
   Mutex mutex;
   
   Net::CheckedData cdata;
   StatInfo stat;
   
  private: 
   
   void count(Event ev)
    {
     Mutex::Lock lock(mutex);
     
     stat.count(ev);
    }
    
  public:
  
   PacketSource()
    : pset(1000)
    {
     run_flag=1;
    }
   
   ~PacketSource()
    {
    }
    
   void getStat(StatInfo &ret) 
    {
     Mutex::Lock lock(mutex);
     
     ret=stat;
    }
   
   bool getRunFlag() { return run_flag; }
   
   void stop() { run_flag=0; }
   
   Function<void (void)> function_stop() { return FunctionOf(this,&PacketSource::stop); }
   
   Packet<uint8> get() 
    { 
     return pset.get(100_msec);
    }
   
   ulen getDataLen() 
    { 
     Mutex::Lock lock(mutex);
    
     return cdata.getLen(1200); 
    }
   
   void fill(PtrLen<uint8> data)
    {
     Mutex::Lock lock(mutex);
     
     if( !cdata.fill(data) )
       {
        stat.count(Event_nofill);
       }
    }
    
   void check(PtrLen<const uint8> data)
    {
     if( !cdata.check(data) ) count(Event_broken);
    }
 };
 
const char * GetTextDesc(PacketSource::Event ev)
 {
  static const char *const Table[]=
   {
    "nofill",
    "broken",
    
    ""
   };
 
  return Table[ev];
 }
 
/* class ClientTask */  
 
class ClientTask : public Funchor_nocopy , Net::PacketEndpointDevice::InboundProc
 {
  public:
  
   enum Event
    {
     Event_nopacket,
     Event_outbound,
     Event_badformat,
     Event_inbound,
     Event_tick,
    
     EventLim
    };
   
   friend const char * GetTextDesc(Event ev);
   
   typedef Counters<Event,EventLim> StatInfo;

  private:
  
   PacketSource &src;
   
   ObjHook hook;
   
   Net::PacketEndpointDevice *ep;
   
   Mutex mutex;      
   
   StatInfo stat;
   
  private: 
  
   void count(Event ev)
    {
     Mutex::Lock lock(mutex);
     
     stat.count(ev);
    }
 
   virtual void inbound(Packet<uint8> packet,PtrLen<const uint8> data)
    {
     count(Event_inbound);
     
     src.check(data);
    
     packet.complete();
    }
     
   virtual void tick()
    {
     count(Event_tick);
    }
    
   void run()
    {
     PacketFormat format=ep->getOutboundFormat();
       
     while( src.getRunFlag() )
       {
        Packet<uint8> packet=src.get();
        
        if( !packet ) 
          {
           count(Event_nopacket);
           
           continue;
          }
           
        ulen len=src.getDataLen();
           
        if( packet.checkDataLen(format,len) )
          {
           src.fill(packet.setDataLen(format,len));

           ep->outbound(packet);
           
           count(Event_outbound);
          }
        else
          {
           packet.complete();
           
           count(Event_badformat);
          }  
       }
    }
    
  public:
  
   ClientTask(PacketSource &src_,ulen number) 
    : src(src_),
      hook(Net::Bridge::ClientName(number).str),
      ep(hook) 
    {
     ep->attach(this);  
    }
    
   ~ClientTask()
    {
     ep->detach();
    }
   
   void getStat(StatInfo &ret) 
    {
     Mutex::Lock lock(mutex);
     
     ret=stat;
    }
    
   Function<void (void)> function_run() { return FunctionOf(this,&ClientTask::run); } 
 };
 
const char * GetTextDesc(ClientTask::Event ev)
 {
  static const char *const Table[]=
   {
    "nopacket",
    "outbound",
    "badformat",
    "inbound",
    "tick",
    
    ""
   };
 
  return Table[ev];
 }
 
/* class Engine */ 

class Engine : NoCopy
 {
   Net::Bridge bridge;
   
   Net::EchoDevice echo;
 
   PacketSource src;
   ClientTask client1;
   ClientTask client2;
   ClientTask client3;
  
  public:
  
   Engine()
    : bridge(10),
      echo(Net::Bridge::ServerName()),
      client1(src,1),
      client2(src,2),
      client3(src,3)
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
 
