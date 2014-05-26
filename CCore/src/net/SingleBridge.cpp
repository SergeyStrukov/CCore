/* SingleBridge.cpp */ 
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
 
#include <CCore/inc/net/SingleBridge.h>
 
#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Net {

/* class SingleBridge::Server */

SingleBridge::Server::Server(SingleBridge &bridge_)
 : bridge(bridge_),
   proc(0)
 {
 }

SingleBridge::Server::~Server()
 {
  Mutex::Lock lock(bridge.mutex);
  
  if( bridge.running ) Abort("Fatal error : CCore::Net::SingleBridge is running on exit");
  
  if( proc ) Abort("Fatal error : CCore::Net::SingleBridge is attached on exit");
 }

PacketFormat SingleBridge::Server::getOutboundFormat()
 {
  return bridge.to_client_format;
 }

void SingleBridge::Server::outbound(Packet<uint8> packet)
 {
  bridge.put_to_client(packet);
 }

ulen SingleBridge::Server::getMaxInboundLen()
 {
  return bridge.to_server_format.max_data;
 }

void SingleBridge::Server::attach(InboundProc *proc_)
 {
  bool is_running;
  bool has_proc;
  
  {
   Mutex::Lock lock(bridge.mutex);
   
   is_running=bridge.running;
   has_proc=(proc!=0);
   
   if( !is_running && !has_proc ) proc=proc_;
  }
  
  if( is_running )
    {
     Printf(Exception,"CCore::Net::SingleBridge::Server::attach(...) : bridge is running");
    }
  
  if( has_proc )
    {
     Printf(Exception,"CCore::Net::SingleBridge::Server::attach(...) : already attached");
    }
 }

void SingleBridge::Server::detach()
 {
  bool is_running;
  
  {
   Mutex::Lock lock(bridge.mutex);
   
   is_running=bridge.running;
   
   if( !is_running ) proc=0;
  }
  
  if( is_running )
    {
     Printf(NoException,"CCore::Net::SingleBridge::Server::detach(...) : bridge is running");
     
     Abort("Fatal error : CCore::Net::SingleBridge is running on detach");
    }
 }

void SingleBridge::Server::inbound(Packet<uint8> packet)
 {
  if( proc )
    {
     PacketFormat format=bridge.to_server_format;
     
     if( packet.checkRange(format) )
       {
        proc->inbound(packet,Range_const(packet.getRange(format)));
       }
     else
       {
        packet.complete();
       }
    }
  else
    {
     packet.complete();
    }
 }

void SingleBridge::Server::tick()
 {
  if( proc ) proc->tick();
 }

/* class SingleBridge::Client */

SingleBridge::Client::Client(SingleBridge &bridge_)
 : bridge(bridge_),
   proc(0)
 {
 }
      
SingleBridge::Client::~Client()
 {
  Mutex::Lock lock(bridge.mutex);
  
  if( bridge.running ) Abort("Fatal error : CCore::Net::SingleBridge is running on exit");
  
  if( proc ) Abort("Fatal error : CCore::Net::SingleBridge is attached on exit");
 }
      
PacketFormat SingleBridge::Client::getOutboundFormat()
 {
  return bridge.to_server_format;
 }
   
void SingleBridge::Client::outbound(Packet<uint8> packet)
 {
  bridge.put_to_server(packet);
 }
   
ulen SingleBridge::Client::getMaxInboundLen()
 {
  return bridge.to_client_format.max_data;
 }
      
void SingleBridge::Client::attach(InboundProc *proc_)
 {
  bool is_running;
  bool has_proc;
  
  {
   Mutex::Lock lock(bridge.mutex);
   
   is_running=bridge.running;
   has_proc=(proc!=0);
   
   if( !is_running && !has_proc ) proc=proc_;
  }
  
  if( is_running )
    {
     Printf(Exception,"CCore::Net::SingleBridge::Client::attach(...) : bridge is running");
    }
  
  if( has_proc )
    {
     Printf(Exception,"CCore::Net::SingleBridge::Client::attach(...) : already attached");
    }
 }
   
void SingleBridge::Client::detach()
 {
  bool is_running;
  
  {
   Mutex::Lock lock(bridge.mutex);
   
   is_running=bridge.running;
   
   if( !is_running ) proc=0;
  }
  
  if( is_running )
    {
     Printf(NoException,"CCore::Net::SingleBridge::Client::detach(...) : bridge is running");
     
     Abort("Fatal error : CCore::Net::SingleBridge is running on detach");
    }
 }
      
void SingleBridge::Client::inbound(Packet<uint8> packet)
 {
  if( proc )
    {
     PacketFormat format=bridge.to_client_format;
     
     if( packet.checkRange(format) )
       {
        proc->inbound(packet,Range_const(packet.getRange(format)));
       }
     else
       {
        packet.complete();
       }
    }
  else
    {
     packet.complete();
    }
 }
      
void SingleBridge::Client::tick()
 {
  if( proc ) proc->tick();
 }

/* class SingleBridge */

bool SingleBridge::drop()
 {
  return random.select(drop_den)<drop_rate;
 }
 
void SingleBridge::set(bool running_)
 {
  Mutex::Lock lock(mutex);
  
  running=running_;
 }
 
void SingleBridge::put_to_server(Packet<uint8> packet)
 {
  bool flag;
  
  {
   Mutex::Lock lock(mutex);
   
   flag=running;
     
   if( flag ) to_server.put(packet);
  }
  
  if( flag )
    msem.give(Event_ToServer); 
  else
    packet.complete();
 }
  
void SingleBridge::put_to_client(Packet<uint8> packet)
 {
  bool flag;
  
  {
   Mutex::Lock lock(mutex);
     
   flag=running;
     
   if( flag ) to_client.put(packet);
  }
  
  if( flag )
    msem.give(Event_ToClient); 
  else  
    packet.complete();
 }
   
void SingleBridge::send_to_client(Packet<uint8> packet)
 {
  if( drop() )
    packet.complete();
  else
    client.inbound(packet);
 }
   
void SingleBridge::send_to_server(Packet<uint8> packet)
 {
  if( drop() )
    packet.complete();
  else
    server.inbound(packet);
 }
 
void SingleBridge::handle_to_server()
 {
  Packet<uint8> packet;
 
  {
   Mutex::Lock lock(mutex);
   
   packet=to_server.get();
  }
  
  send_to_server(packet);
 }
   
void SingleBridge::handle_to_client()
 {
  Packet<uint8> packet;
 
  {
   Mutex::Lock lock(mutex);
   
   packet=to_client.get();
  }
  
  send_to_client(packet);
 }
   
void SingleBridge::handle_tick()
 {
  server.tick();
  client.tick();
 }
 
void SingleBridge::objRun()
 {
  set(true);
  
  TimeScope time_scope(100_msec);
  
  for(;;)
    switch( msem.take(time_scope) )
      {
       case Event_Timeout  : if( time_scope.nextScope() ) handle_tick(); break; 
       
       case Event_Stop     : return;
        
       case Event_ToServer : handle_to_server(); break;
       case Event_ToClient : handle_to_client(); break;
      }
 }
 
void SingleBridge::signalStop()
 {
  msem.give(Event_Stop);
 }
 
void SingleBridge::completeStop()
 {
  set(false);
  
  complete(to_server);
  complete(to_client);
 }
 
void SingleBridge::complete(PacketList &list)
 {
  while( PacketHeader *packet_=list.get() )
    {
     Packet<uint8> packet=packet_;
     
     packet.complete();
    }
 }
 
SingleBridge::SingleBridge()
 : server(*this),
   client(*this),
   msem("SingleBridge"),
   mutex("SingleBridge"),
   running(false),
   server_master(server,ServerName()),
   client_master(client,ClientName())
 {
  drop_rate=0;
  drop_den=1;  
  
  to_server_format.prefix=11;
  to_server_format.max_data=1100;
  to_server_format.suffix=10;
  
  to_client_format.prefix=13;
  to_client_format.max_data=1000;
  to_client_format.suffix=15;
 }
   
SingleBridge::SingleBridge(PacketFormat to_server_format_,PacketFormat to_client_format_)
 : SingleBridge()
 {
  to_server_format=to_server_format_;
  to_client_format=to_client_format_;
 }
   
SingleBridge::~SingleBridge()
 {
 }

} // namespace Net
} // namespace CCore
 

