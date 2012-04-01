/* Bridge.cpp */ 
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
 
#include <CCore/inc/net/Bridge.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Net {

/* class Bridge::Server */ 

Bridge::Server::Server(Bridge &bridge_)
 : bridge(bridge_),
   proc(0)
 {
 }
      
Bridge::Server::~Server()
 {
  Mutex::Lock lock(bridge.mutex);
  
  if( bridge.running ) Abort("Fatal error : CCore::Net::Bridge is running on exit");
  
  if( proc ) Abort("Fatal error : CCore::Net::Bridge is attached on exit");
 }
 
StrLen Bridge::Server::toText(XPoint point,PtrLen<char> buf) 
 {
  PrintBuf out(buf);
  
  Putobj(out,point);
  
  return out.close();
 }
      
PacketFormat Bridge::Server::getOutboundFormat()
 {
  return bridge.to_client_format;
 }
   
void Bridge::Server::outbound(XPoint point,Packet<uint8> packet)
 {
  bridge.put_to_client(point,packet);
 }
   
ulen Bridge::Server::getMaxInboundLen()
 {
  return bridge.to_server_format.max_data;
 }
  
void Bridge::Server::attach(InboundProc *proc_)
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
     Printf(Exception,"CCore::Net::Bridge::Server::attach(...) : bridge is running");
    }
  
  if( has_proc )
    {
     Printf(Exception,"CCore::Net::Bridge::Server::attach(...) : already attached");
    }
 }
   
void Bridge::Server::detach()
 {
  bool is_running;
  
  {
   Mutex::Lock lock(bridge.mutex);
   
   is_running=bridge.running;
   
   if( !is_running ) proc=0;
  }
  
  if( is_running )
    {
     Printf(NoException,"CCore::Net::Bridge::Server::detach(...) : bridge is running");
     
     Abort("Fatal error : CCore::Net::Bridge is running on detach");
    }
 }
      
void Bridge::Server::inbound(XPoint point,Packet<uint8> packet)
 {
  if( proc )
    {
     PacketFormat format=bridge.to_server_format;
     
     if( packet.checkRange(format) )
       {
        proc->inbound(point,packet,Range_const(packet.getRange(format)));
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
      
void Bridge::Server::tick()
 {
  if( proc ) proc->tick();
 }
 
/* class Bridge::Client */ 

Bridge::Client::Client(Bridge &bridge_,XPoint point_)
 : bridge(bridge_),
   point(point_),
   proc(0)
 {
 }
      
Bridge::Client::~Client()
 {
  Mutex::Lock lock(bridge.mutex);
  
  if( bridge.running ) Abort("Fatal error : CCore::Net::Bridge is running on exit");
  
  if( proc ) Abort("Fatal error : CCore::Net::Bridge is attached on exit");
 }
      
PacketFormat Bridge::Client::getOutboundFormat()
 {
  return bridge.to_server_format;
 }
   
void Bridge::Client::outbound(Packet<uint8> packet)
 {
  bridge.put_to_server(point,packet);
 }
   
ulen Bridge::Client::getMaxInboundLen()
 {
  return bridge.to_client_format.max_data;
 }
      
void Bridge::Client::attach(InboundProc *proc_)
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
     Printf(Exception,"CCore::Net::Bridge::Client::attach(...) : bridge is running");
    }
  
  if( has_proc )
    {
     Printf(Exception,"CCore::Net::Bridge::Client::attach(...) : already attached");
    }
 }
   
void Bridge::Client::detach()
 {
  bool is_running;
  
  {
   Mutex::Lock lock(bridge.mutex);
   
   is_running=bridge.running;
   
   if( !is_running ) proc=0;
  }
  
  if( is_running )
    {
     Printf(NoException,"CCore::Net::Bridge::Client::detach(...) : bridge is running");
     
     Abort("Fatal error : CCore::Net::Bridge is running on detach");
    }
 }
      
void Bridge::Client::inbound(Packet<uint8> packet)
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
      
void Bridge::Client::tick()
 {
  if( proc ) proc->tick();
 }
 
/* class Bridge */ 

bool Bridge::drop()
 {
  return random.select(drop_den)<drop_rate;
 }
 
void Bridge::set(bool running_)
 {
  Mutex::Lock lock(mutex);
  
  running=running_;
 }
 
void Bridge::put_to_server(XPoint point,Packet<uint8> packet)
 {
  bool flag;
  
  {
   Mutex::Lock lock(mutex);
   
   flag=running;
     
   if( flag ) to_server.put(packet.pushExt<XPoint>(point));
  }
  
  if( flag )
    msem.give(Event_ToServer); 
  else
    packet.complete();
 }
  
void Bridge::put_to_client(XPoint point,Packet<uint8> packet)
 {
  bool flag;
  
  {
   Mutex::Lock lock(mutex);
     
   flag=running;
     
   if( flag ) to_client.put(packet.pushExt<XPoint>(point));
  }
  
  if( flag )
    msem.give(Event_ToClient); 
  else  
    packet.complete();
 }
   
void Bridge::send_to_client(XPoint point,Packet<uint8> packet)
 {
  if( point==0 || point>clients.getLen() )
    {
     packet.complete();
    }
  else
    {  
     ulen i=ulen(point-1);

     if( drop() )
       packet.complete();
     else
       clients[i].inbound(packet);
    }
 }
   
void Bridge::send_to_server(XPoint point,Packet<uint8> packet)
 {
  if( drop() )
    packet.complete();
  else
    server.inbound(point,packet);
 }
 
void Bridge::handle_to_server()
 {
  Packet<uint8,XPoint> packet;
 
  {
   Mutex::Lock lock(mutex);
   
   packet=to_server.get();
  }
  
  XPoint point=*packet.getExt();
  
  send_to_server(point,packet.popExt());
 }
   
void Bridge::handle_to_client()
 {
  Packet<uint8,XPoint> packet;
 
  {
   Mutex::Lock lock(mutex);
   
   packet=to_client.get();
  }
  
  XPoint point=*packet.getExt();
  
  send_to_client(point,packet.popExt());
 }
   
void Bridge::handle_tick()
 {
  server.tick();
  
  for(auto cur=Range(clients); +cur ;++cur) cur->tick();
 }
 
void Bridge::objRun()
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
 
void Bridge::signalStop()
 {
  msem.give(Event_Stop);
 }
 
void Bridge::completeStop()
 {
  set(false);
  
  complete(to_server);
  complete(to_client);
 }
 
void Bridge::complete(PacketList &list)
 {
  while( PacketHeader *packet_=list.get() )
    {
     Packet<uint8,XPoint> packet=packet_;
     
     packet.popExt().complete();
    }
 }
 
Bridge::ClientName::ClientName(ulen number)
 {
  PrintBuf out(Range(buf));
     
  Printf(out,"BridgeClient[#;]",number);
  
  str=out.guardOverflow().close();
 }
 
void Bridge::init(ulen num_clients)
 {
  masters.append_fill(server,ServerName());
  
  for(ulen i=0; i<num_clients ;i++) 
    {
     Client *client=clients.append_fill(*this,i+1);
     
     masters.append_fill(*client,ClientName(i+1).str);
    }
    
  drop_rate=0;
  drop_den=1;  
 }
 
Bridge::Bridge(ulen num_clients)
 : server(*this),
   clients(DoReserve,num_clients),
   masters(DoReserve,num_clients+1),
   msem("Bridge"),
   mutex("Bridge"),
   running(false)
 {
  init(num_clients);
  
  to_server_format.prefix=11;
  to_server_format.max_data=1100;
  to_server_format.suffix=10;
  
  to_client_format.prefix=13;
  to_client_format.max_data=1000;
  to_client_format.suffix=15;
 }
   
Bridge::Bridge(ulen num_clients,PacketFormat to_server_format_,PacketFormat to_client_format_)
 : server(*this),
   clients(DoReserve,num_clients),
   masters(DoReserve,num_clients+1),
   msem("Bridge"),
   mutex("Bridge"),
   running(false)
 {
  init(num_clients);
  
  to_server_format=to_server_format_;
  to_client_format=to_client_format_;
 }
   
Bridge::~Bridge()
 {
 }
 
} // namespace Net
} // namespace CCore
 

