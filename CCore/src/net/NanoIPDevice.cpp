/* NanoIPDevice.cpp */ 
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
 
#include <CCore/inc/net/NanoIPDevice.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>
 
namespace CCore {
namespace Net {

/* enum IPEvent */ 

const char * GetTextDesc(IPEvent ev)
 {
  static const char *const Table[]=
   {
    "Tx ARP",         //  IPTx_ARP
    "Tx IP",          //  IPTx_IP
    "Tx UDP",         //  IPTx_UDP
  
    "Rx ARP",         //  IPRx_ARP
    "Rx IP",          //  IPRx_IP
    "Rx UDP",         //  IPRx_UDP
  
    "Tx bad length",  //  IPTx_BadPacketLen
    "Tx timeout",     //  IPTx_TimeoutDrop
    "Tx ARP missing", //  IPTx_ARP_Mising
    "Tx ARP drop",    //  IPTx_ARP_Drop
    "Tx drop",        //  IPTx_Drop
    
    "Rx bad packet",  //  IPRx_BadPacket
    "Rx drop",        //  IPRx_Drop
    "Rx no UDP port", //  IPRx_UDP_NoPort
    
    ""
   };
 
  return Table[ev];
 }
 
/* struct NetEvent */

void NetEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_IPEvent=info.addEnum_uint8("IPEvent")
    
                      .addValueName(IPTx_ARP,"IP Tx ARP")
                      .addValueName(IPTx_IP,"IP Tx IP")
                      .addValueName(IPTx_UDP,"IP Tx UDP")
                      
                      .addValueName(IPRx_ARP,"IP Rx ARP")
                      .addValueName(IPRx_IP,"IP Rx IP")
                      .addValueName(IPRx_UDP,"IP Rx UDP")
                      
                      .addValueName(IPTx_BadPacketLen,"IP Tx bad packet len")
                      .addValueName(IPTx_TimeoutDrop,"IP Tx timeout drop")
                      .addValueName(IPTx_ARP_Missing,"IP Tx ARP missing")
                      .addValueName(IPTx_ARP_Drop,"IP Tx ARP drop")
                      .addValueName(IPTx_Drop,"IP Tx drop")
                      
                      .addValueName(IPRx_BadPacket,"IP Rx bad packet")
                      .addValueName(IPRx_Drop,"IP Rx drop")
                      .addValueName(IPRx_UDP_NoPort,"IP Rx UDP no port")
                      
                      .getId();
  
  auto id=info.addStruct("NetEvent")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint8(id_IPEvent,"ip_event",Offset_ip_event)
              .getId();
  
  desc.setStructId(info,id);
 }

/* class ARPTable */ 

ARPTable::TickResult ARPTable::TimeGuard::tick(bool noalert)
 {
  if( !ticks ) return Kill;
       
  if( ticks<AlertTime && (ticks%AlertPeriod)==0 )
    {
     if( noalert )
       {
        return Ok;
       }
     else
       {  
        ticks--;
       
        return Alert;
       }
    }
  else
    {  
     ticks--;
       
     return Ok;
    } 
 }
      
void ARPTable::Entry::refresh(MACAddress mac_)
 {
  mac=mac_;
  
  time_guard.reset();
 }
     
ARPTable::ARPTable()
 {
 }
   
ARPTable::~ARPTable()
 {
  clear();
 }
   
void ARPTable::clear()
 {
  root.init();
  
  while( Entry *entry=list.del_first() ) delete entry;
 }
   
void ARPTable::add(IPAddress ip,MACAddress mac)
 {
  TreeAlgo::PrepareIns prepare(root,ip.get());
    
  if( prepare.found )
    {
     prepare.found->refresh(mac);
    }
  else
    {
     if( Entry *entry=new(JustTry) Entry(mac) )
       {
        prepare.complete(entry);
        
        list.ins_first(entry);
       }
    }
 }
   
bool ARPTable::del(IPAddress ip)
 {
  if( Entry *entry=root.find(ip.get()) )
    {
     root.del(entry);
     list.del(entry);
     
     delete entry;
    
     return true;
    }
  
  return false;
 }

bool ARPTable::find(IPAddress ip,MACAddress &mac)
 {
  if( Entry *entry=root.find(ip.get()) )
    {
     mac=entry->mac;
    
     return true;
    }
    
  return false;
 }
   
auto ARPTable::tick() -> TickAction 
 {
  TickAction ret;
  
  for(auto cur=list.start(); +cur ;)
    {
     switch( cur->time_guard.tick(ret.resend) )
       {
        case Alert : 
         {
          ret=cur->getIP(); 
         }
        // falldown;
        
        default:
         {
          ++cur;
         }
        break; 
        
        case Kill :
         {
          Entry *entry=list.del_and_move(cur);
          
          root.del(entry);
          
          delete entry;
         } 
       }
    }
  
  return ret;  
 }
   
/* class ARPending */ 

ARPending::Entry::Entry(CancelPacketList &canlist,Packet<uint8,EthTxExt> packet)
 {
  add(canlist,packet);
  
  ticks=LifeTime;
 }
     
unsigned ARPending::Entry::clear(CancelPacketList &canlist)
 {
  unsigned ret=list.getCount();
       
  canlist.complete(list);
       
  return ret;
 }
     
bool ARPending::Entry::tick()
 {
  if( ticks )
    {
     ticks--;
          
     return true;
    }
         
  return false;  
 }
      
ARPending::ARPending()
 : canlist("ARPending")
 {
 }
   
ARPending::~ARPending()
 {
 }
   
unsigned ARPending::clear()
 {
  unsigned ret=0;
 
  root.init();
  
  while( Entry *entry=list.del_first() )
    {
     ret+=entry->clear(canlist);
     
     delete entry;
    }
    
  return ret;  
 }
   
auto ARPending::add(IPAddress ip,Packet<uint8,EthTxExt> packet) -> AddResult
 {
  TreeAlgo::PrepareIns prepare(root,ip.get());
 
  if( prepare.found )
    {
     prepare.found->add(canlist,packet);
    
     return Ok;
    }
    
  if( Entry *entry=new(JustTry) Entry(canlist,packet) ) 
    {
     prepare.complete(entry);
     
     list.ins_first(entry);
    
     return Request;
    }
    
  packet.complete();
    
  return Drop;  
 }
   
bool ARPending::del(IPAddress ip,PacketList &dst)
 {
  if( Entry *entry=root.find(ip.get()) )
    {
     entry->del(canlist,dst);
     
     list.del(entry);
     root.del(entry);
    
     delete entry;
    
     return true;
    }
    
  return false;  
 }
   
auto ARPending::tick() -> TickAction
 {
  TickAction ret;
 
  Entry *entry=list.rotate_forward();
  
  if( !entry ) return ret;
  
  if( entry->tick() )
    {
     ret=entry->getIP();
    }
  else
    {
     ret=entry->clear(canlist);
     
     list.del(entry);
     root.del(entry);
     
     delete entry;
    }
    
  return ret;  
 }
 
/* class TxPrepareList */ 

void TxPrepareList::cancel(PacketHeader *packet)
 {
  {
   Mutex::Lock lock(mutex);
  
   if( PacketList *list=*packet->getExt<PacketList *>() ) list->del(packet);
   
   stat.count(CancelPacketList::Event_cancel);
  } 
  
  packet->popExt<PacketList *>();
  
  packet->popCompleteFunction();
  
  packet->complete();
 }
 
void TxPrepareList::get(PacketList &dst)
 {
  Mutex::Lock lock(mutex);
  
  for(;;)
    {
     PacketHeader *packet=list.get();
  
     if( !packet ) return;
  
     if( packet->clearCancelFunction()!=Packet_Cancelled ) 
       {
        packet->popExt<PacketList *>();
       
        dst.put(packet);
       }
     else
       {
        *packet->getExt<PacketList *>()=0;
       }
    } 
 }
 
TxPrepareList::TxPrepareList()
 : mutex("TxPrepareList"),
   enable_flag(false)
 {
 }
   
TxPrepareList::~TxPrepareList() 
 {
 }
   
void TxPrepareList::getStat(StatInfo &ret)
 {
  Mutex::Lock lock(mutex);
  
  ret=stat;
 }
 
void TxPrepareList::enable()
 {
  Mutex::Lock lock(mutex);
  
  enable_flag=true;
 }
   
void TxPrepareList::disable()
 {
  Mutex::Lock lock(mutex);
  
  enable_flag=false;
 }
   
bool TxPrepareList::put(PacketHeader *packet,PacketFunction function)
 {
  Mutex::Lock lock(mutex);

  if( enable_flag )
    {
     if( packet->setCancelFunction(function_cancel())==Packet_NoCancelFunction )
       {
        packet->pushExt<PacketList *>(&list);
     
        packet->pushCompleteFunction(function);
   
        packet->stamp();
   
        list.put(packet);
          
        return true;
       }
     
     stat.count(CancelPacketList::Event_cancel_on_put);  
    }
    
  return false;
 }
   
void TxPrepareList::prepare()
 {
  PacketList temp;
  
  get(temp);
  
  temp.complete();
 }
 
/* class TxSendList */   

TxSendList::TxSendList()
 {
  put_ind=0;
  get_ind=0;
 }
   
TxSendList::~TxSendList()
 {
 }
   
unsigned TxSendList::clear()
 {
  put_ind=0;
  get_ind=0;
  
  unsigned ret=0;
  
  for(auto r=Range(list); +r ;++r)
    {
     ret+=r->getCount();
     
     canlist.complete(*r);
    }
  
  return ret;
 }
   
void TxSendList::put(Packet<uint8,EthTxExt> packet)
 {
  canlist.put(list[put_ind],packet);
 }
   
Packet<uint8,EthTxExt> TxSendList::get()
 {
  for(;;)
    {
     Packet<uint8,EthTxExt> ret=canlist.get(list[get_ind]);
     
     if( +ret || get_ind==put_ind ) return ret;
     
     get_ind=NextInd(get_ind);
    }
 }
   
unsigned TxSendList::tick()
 {
  ulen ind=NextInd(put_ind);
  
  put_ind=ind;
  
  if( ind==get_ind )
    {
     get_ind=NextInd(ind);
     
     unsigned ret=list[ind].getCount();
     
     canlist.complete(list[ind]);
     
     return ret;
    }
  else
    {
     return 0;
    }
 }
 
/* class ICMPEchoEndpoint */ 
 
void ICMPEchoEndpoint::reply(const ICMPEcho &echo,PtrLen<const uint8> echo_data)
 {
  if( echo.code!=0 ) return;
  
  if( !Range(data).equal(echo_data) ) return;
  
  reply_function(echo.num);    
 }
   
ICMPEchoEndpoint::ICMPEchoEndpoint(StrLen ip_dev_name,IPAddress dst_,ICMPReplyFunction reply_function_)
 : hook(ip_dev_name),
   dev(hook),
   dst(dst_),
   num(1),
   reply_function(reply_function_),
   asem("ICMPEchoEndpoint")
 {
  uint8 d=1;
 
  for(auto r=Range(data); +r ;++r) *r=d++;
  
  dev->attach(this);
 }
   
ICMPEchoEndpoint::~ICMPEchoEndpoint()
 {
  dev->detach(this);
 
  asem.wait();
 }
   
uint16 ICMPEchoEndpoint::send()
 {
  uint16 ret=num++;
  
  ICMPEcho echo(ICMPEcho_Request,id,ret);
  
  echo.setCheckSum(Range_const(data));
  
  dev->send_icmp_echo(dst,echo,Range_const(data));
  
  return ret;
 }
 
/* class ICMPEchoList */  

ICMPEchoEndpoint * ICMPEchoList::find(uint16 id)
 {
  Mutex::Lock lock(mutex);
  
  if( ICMPEchoEndpoint *ret=root.find(id) )
    {
     ret->asem.inc();
    
     return ret;
    }
  else
    {
     return 0;
    }
 }
   
ICMPEchoList::ICMPEchoList()
 : mutex("ICMPEchoList"),
   next_id(0)
 {
 }
   
ICMPEchoList::~ICMPEchoList()
 {
  if( +root ) Abort("Fatal error : CCore::Net::ICMPEchoList is not empty on exit");
 }
   
void ICMPEchoList::attach(ICMPEchoEndpoint *endpoint)
 {
  for(uint32 cnt=uint32(1)<<16; cnt ;cnt--)
    {
     Mutex::Lock lock(mutex);
  
     uint16 id=next_id++;
     
     Algo::PrepareIns prepare(root,id);
     
     if( !prepare.found )
       {
        endpoint->id=id;
       
        prepare.complete(endpoint);
       
        return;
       }
    }
    
  Printf(Exception,"CCore::Net::ICMPEchoList::attach(...) : no free id");  
 }
   
void ICMPEchoList::detach(ICMPEchoEndpoint *endpoint)
 {
  Mutex::Lock lock(mutex);
  
  root.del(endpoint);
 }
 
/* class IPTickEndpoint */ 

IPTickEndpoint::IPTickEndpoint(StrLen ip_dev_name,IPTickFunction tick_function_)
 : hook(ip_dev_name),
   dev(hook),
   tick_function(tick_function_),
   asem("IPTickEndpoint")
 {
  dev->attach(this);
 }
   
IPTickEndpoint::~IPTickEndpoint()
 {
  dev->detach(this);
 
  asem.wait();
 }
 
/* class IPTickList */ 

IPTickList::IPTickList()
 : mutex("IPTickList")
 {
  guard=0;
 }
   
IPTickList::~IPTickList()
 {
  if( +list ) Abort("Fatal error : CCore::Net::IPTickList is not empty on exit");
 }
   
IPTickEndpoint * IPTickList::take()
 {
  Mutex::Lock lock(mutex);
  
  IPTickEndpoint *ret=list.rotate_forward();
  
  if( ret ) 
    {
     if( guard )
       {
        if( ret==guard ) return 0;
       }
     else
       {
        guard=ret;
       }  
    
     ret->asem.inc();
    }
  
  return ret;
 }
 
void IPTickList::attach(IPTickEndpoint *endpoint)
 {
  Mutex::Lock lock(mutex);
  
  list.ins_last(endpoint);
 }
   
void IPTickList::detach(IPTickEndpoint *endpoint)
 {
  Mutex::Lock lock(mutex);
  
  if( endpoint==guard )
    {
     IPTickEndpoint *new_guard=Algo::Link(endpoint).next;
     
     if( new_guard!=list.top )
       guard=new_guard;
     else
       guard=0;  
    }
  
  list.del(endpoint);
 }
 
void IPTickList::tick()
 {
  Mutex::Lock lock(mutex);
  
  guard=0;
 }
 
/* class UDPEndpoint */ 

IPEvent UDPEndpoint::inbound(Packet<uint8> packet,PtrLen<const uint8> data,const IPHeader &iph,const UDPHeader &udph)
 {
  if( do_checksum )
    {
     if( !udph.testCheckSum(iph.src,iph.dst,data.len+UDPHeaderLen,data) ) return IPRx_BadPacket;
    }
    
  rx_function(packet,data,UDPoint(iph.src,udph.src_port));  
    
  return IPRx_UDP;  
 }
   
UDPEndpoint::UDPEndpoint(StrLen ip_dev_name,UDPort port_,bool do_checksum_,UDPFunction rx_function_)
 : hook(ip_dev_name),
   dev(hook),
   port(port_),
   do_checksum(do_checksum_),
   rx_function(rx_function_),
   asem("UDPEndpoint")
 {
  dev->attach(this);
 }              
   
UDPEndpoint::~UDPEndpoint()
 {
  dev->detach(this);
 
  asem.wait();
 }
 
ulen UDPEndpoint::getMaxInboundLen() const
 {
  return dev->getUDPRxFormat().max_data;
 }
 
PacketFormat UDPEndpoint::getUDPTxFormat() const
 {
  return dev->getUDPTxFormat();
 }
   
void UDPEndpoint::send(Packet<uint8> packet_,UDPoint dst)
 {
  Packet<uint8,UDPTxExt> packet=packet_.pushExt<UDPTxExt>(dst.address,dst.port,port,do_checksum);
 
  packet.pushCompleteFunction(DropPacketExt<uint8,UDPTxExt>);
 
  dev->send_udp(packet);
 }
 
/* class UDPList */ 

UDPEndpoint * UDPList::find(UDPort port)
 {
  Mutex::Lock lock(mutex);
  
  if( UDPEndpoint *ret=root.find(port) )
    {
     ret->asem.inc();
    
     return ret;
    }
  else
    {
     return 0;
    }
 }
  
UDPList::UDPList()
 : mutex("UDPList")
 {
 }
   
UDPList::~UDPList()
 {
  if( +root ) Abort("Fatal error : CCore::Net::UDPList is not empty on exit");
 }
   
void UDPList::attach(UDPEndpoint *endpoint)
 {
  bool found;
  
  {
   Mutex::Lock lock(mutex);
   
   Algo::PrepareIns prepare(root,endpoint->port);
   
   found=(prepare.found!=0);
   
   if( !found ) prepare.complete(endpoint);
  }
  
  if( found )
    {
     Printf(Exception,"CCore::Net::UDPList::attach(...) : #; port is already attached",endpoint->port);
    }
 }
   
void UDPList::detach(UDPEndpoint *endpoint)
 {
  Mutex::Lock lock(mutex);
  
  root.del(endpoint);
 }
 
/* class NanoIPDevice */ 

void NanoIPDevice::start()
 {
  stat.reset();
  
  {
   Mutex::Lock lock(mutex);
  
   stat_toget.reset();  
  }
  
  arp_table.clear();
  
  prepare_list.enable();
 }
   
void NanoIPDevice::linkUp()
 {
  for(ulen cnt=5; cnt ;cnt--) send_arp();
 }
   
void NanoIPDevice::linkDown()
 {
  // do nothing
 }
   
void NanoIPDevice::tick()
 {
  stat.count(IPTx_TimeoutDrop,send_list.tick());
 
  {
   auto action=arp_table.tick();
  
   if( action.resend ) send_arp(action.ip);
  }
  
  {
   auto action=arp_pending.tick();
   
   if( action.resend ) send_arp(action.ip);
   
   stat.count(IPTx_ARP_Drop,action.drop);
  } 
  
  {
   Mutex::Lock lock(mutex);
   
   stat_toget=stat;
  }
  
  tick_list.tick();
  
  for(;;)
    {
     IPTickList::Hook hook(tick_list);
     
     if( !hook ) break;
     
     hook.tick();
    }
 }
   
void NanoIPDevice::inbound(Packet<uint8,EthRxExt> packet)
 {
  if( !packet.checkRange(rx_format) ) 
    {
     stat.count(IPRx_BadPacket);
  
     packet.complete();
     
     return;
    }
 
  EthRxExt *ext=packet.getExt();
  
  IPEvent ev;
  
  switch( ext->type.get() )
    {
     case Eth_IP  : ev=inbound_ip(packet);  break;
     
     case Eth_ARP : ev=inbound_arp(packet); break;
     
     default: ev=IPRx_Drop;
    }
    
  stat.count(ev);  

  if( ev!=IPRx_UDP )  
    {
     packet.complete();
    }
 }
   
void NanoIPDevice::prepareOutbound()
 {
  prepare_list.prepare();
 }
 
Packet<uint8,EthTxExt> NanoIPDevice::outbound()
 {
  return send_list.get();
 }
   
void NanoIPDevice::stop()
 {
  prepare_list.disable();
  
  prepare_list.prepare();
  
  stat.count(IPTx_Drop,send_list.clear());
  
  stat.count(IPTx_Drop,arp_pending.clear());
 }
 
void NanoIPDevice::send_arp(MACAddress dst,const ARPacket &arp)
 {
  Packet<uint8,EthTxExt> packet=TryGetPacket<EthTxExt>(dst,Eth_ARP);
 
  if( !packet ) return;

  auto out_len=SaveLen(arp);
  
  if( packet.checkDataLen(tx_format,out_len) )
    {
     PtrLen<uint8> out_data=packet.setDataLen(tx_format,out_len);
     
     BufPutDev dev(out_data.ptr);
     
     dev(arp);
     
     stat.count(IPTx_ARP);
     
     send_list.put(packet);
     
     eth->signalOutbound();
    }
  else
    {
     packet.complete();
    }
 }
 
void NanoIPDevice::send_arp(IPAddress dst)
 {
  ARPacket arp(ARP_Request,mac_address,address,MACAddress(),dst);
  
  send_arp(MACAddress::Broadcast(),arp);
 }
 
void NanoIPDevice::send_arp()
 {
  send_arp(address);
 }
  
void NanoIPDevice::send_arp_reply(IPAddress dst_ip,MACAddress dst_mac)
 {
  ARPacket arp(ARP_Reply,mac_address,address,dst_mac,dst_ip);
  
  send_arp(dst_mac,arp);
 }
 
void NanoIPDevice::arp_done(IPAddress ip,MACAddress mac)
 {
  arp_table.add(ip,mac);
  
  PacketList temp;
  
  arp_pending.del(ip,temp);
  
  while( PacketHeader *packet_=temp.get() )
    {
     Packet<uint8,EthTxExt> packet=packet_;
     
     packet.getExt()->dst=mac;
     
     stat.count(IPTx_IP);
     
     send_list.put(packet);
    }
    
  eth->signalOutbound();
 }
 
IPEvent NanoIPDevice::inbound_arp(Packet<uint8,EthRxExt> packet)
 {
  PtrLen<uint8> data=packet.getRange(rx_format);
  
  RangeGetDev dev(Range_const(data));
 
  ARPacket arp;
  
  dev(arp);
  
  if( !dev ) return IPRx_BadPacket;
  
  if( !arp.testDefault() ) return IPRx_BadPacket;
  
  if( !sameNet(arp.src_ip) ) return IPRx_Drop; // net check
  
  switch( arp.type.get() )
    {
     case ARP_Request :
      {
       arp_done(arp.src_ip,arp.src_mac);
       
       if( arp.dst_ip==address ) send_arp_reply(arp.src_ip,arp.src_mac);
      } 
     return IPRx_ARP;
     
     case ARP_Reply :
      {
       arp_done(arp.src_ip,arp.src_mac);
      } 
     return IPRx_ARP;
     
     default: return IPRx_BadPacket;
    }
 }
 
IPEvent NanoIPDevice::inbound_icmp(const IPHeader &iph,PtrLen<uint8> body)
 {
  if( body.len<ICMPEchoLen ) return IPRx_BadPacket;
  
  ICMPEcho echo;
  
  BufGetDev dev(body.ptr);
  
  dev(echo);
  
  body+=ICMPEchoLen;
  
  PtrLen<const uint8> data=Range_const(body);
  
  if( !echo.testCheckSum(data) ) return IPRx_BadPacket;
  
  switch( echo.type.get() )
    {
     case ICMPEcho_Request :
      {
       echo.type=ICMPEcho_Reply;
       
       echo.setCheckSum(data);
  
       send_icmp_echo(iph.src,echo,data);
      }
     return IPRx_IP;
     
     case ICMPEcho_Reply :
      {
       ICMPEchoList::Hook hook(echo_list,echo.id);
       
       hook.reply(echo,data);
      }
     return IPRx_IP;
     
     default: return IPRx_BadPacket;
    }
 }
 
IPEvent NanoIPDevice::inbound_udp(Packet<uint8,EthRxExt> packet,const IPHeader &iph,PtrLen<uint8> body)
 {
  if( body.len<UDPHeaderLen ) return IPRx_BadPacket;
  
  UDPHeader udph;
  
  BufGetDev dev(body.ptr);
  
  dev(udph);
  
  if( udph.len!=body.len ) return IPRx_BadPacket;
  
  body+=UDPHeaderLen;
  
  UDPList::Hook hook(udp_list,udph.dst_port);
  
  return hook.inbound(packet.forgetExt<1>(),Range_const(body),iph,udph);
 }        
 
IPEvent NanoIPDevice::inbound_ip(Packet<uint8,EthRxExt> packet)
 {
  PtrLen<uint8> data=packet.getRange(rx_format);
  
  if( data.len<IPHeaderLen ) return IPRx_BadPacket;
    
  IPHeader iph;
  
  BufGetDev dev(data.ptr);   
  
  dev(iph);
  
  if( iph.vhl!=IPHeader::DefaultVHL ) return IPRx_BadPacket;
  
  if( iph.isFragment() ) return IPRx_BadPacket;
  
  if( !iph.testCheckSum() ) return IPRx_BadPacket;
  
  if( iph.len>data.len || iph.len<IPHeaderLen ) return IPRx_BadPacket;
  
  if( iph.dst!=address ) return IPRx_Drop; // not to us
  
  if( !sameNet(iph.src) ) return IPRx_Drop; // net check
  
  data.len=iph.len;
  
  data+=IPHeaderLen;
    
  switch( iph.proto.get() )  
    {
     case IP_ICMP : return inbound_icmp(iph,data);
     
     case IP_UDP  : return inbound_udp(packet,iph,data);
     
     default: return IPRx_Drop;
    }
 }
 
void NanoIPDevice::prepare_ip(PacketHeader *packet_)
 {
  Packet<uint8,IPTxExt> packet=packet_;
  
  if( !packet.checkRange(ip_tx_format) )
    {
     stat.count(IPTx_BadPacketLen);
    
     packet.complete();
     
     return;
    }
  
  PtrLen<uint8> data=packet.getRange(tx_format); 
  IPTxExt *ext=packet.getExt();
  IPAddress dst=ext->dst;
  
  if( !sameNet(dst) ) // net check
    {
     stat.count(IPTx_Drop);
    
     packet.complete();
     
     return;
    }
  
  IPHeader header(address,dst,ext->proto,(IPLen)data.len);
  
  BufPutDev dev(data.ptr);
        
  dev(header);
  
  MACAddress mac_dst;
  
  if( arp_table.find(dst,mac_dst) )
    {
     Packet<uint8,EthTxExt> eth_packet=packet.pushExt<EthTxExt>(mac_dst,Eth_IP).forgetExt<1>();
  
     eth_packet.pushCompleteFunction(DropPacketExt<uint8,EthTxExt>);
  
     stat.count(IPTx_IP);
     
     send_list.put(eth_packet);
    }
  else
    {
     Packet<uint8,EthTxExt> eth_packet=packet.pushExt<EthTxExt>(mac_dst,Eth_IP).forgetExt<1>();
  
     eth_packet.pushCompleteFunction(DropPacketExt<uint8,EthTxExt>);
    
     stat.count(IPTx_ARP_Missing);
     
     switch( arp_pending.add(dst,eth_packet) ) 
       {
        case ARPending::Request : send_arp(dst); break;
        
        case ARPending::Drop    : stat.count(IPTx_Drop); break;
       }
    }   
 }
 
void NanoIPDevice::prepare_udp(PacketHeader *packet_)
 {
  Packet<uint8,UDPTxExt> packet=packet_;
  
  if( !packet.checkRange(udp_tx_format) )
    {
     stat.count(IPTx_BadPacketLen);
    
     packet.complete();
     
     return;
    }
    
  PtrLen<uint8> data=packet.getRange(ip_tx_format);
  UDPTxExt *ext=packet.getExt();
  IPAddress dst=ext->dst;
  
  UDPHeader header(ext->src_port,ext->dst_port,(IPLen)data.len);  
  
  if( ext->do_checksum )
    {
     PtrLen<const uint8> body=Range_const(data);
     
     body+=UDPHeaderLen;
    
     header.setCheckSum(address,dst,(IPLen)data.len,body);
    }

  BufPutDev dev(data.ptr);  
  
  dev(header);
  
  Packet<uint8,IPTxExt> ip_packet=packet.pushExt<IPTxExt>(dst,IP_UDP).forgetExt<1>();
  
  ip_packet.pushCompleteFunction(DropPacketExt<uint8,IPTxExt>);
  
  stat.count(IPTx_UDP);
  
  prepare_ip(ip_packet.getPtr());
 }
 
NanoIPDevice::NanoIPDevice(StrLen eth_dev_name,IPAddress address_,IPAddress net_mask_)
 : hook(eth_dev_name),
   eth(hook),
   address(address_),
   net_mask(net_mask_),
   mutex("NanoIPDevice")
 {
  tx_format=eth->getTxFormat();
  rx_format=eth->getRxFormat();
  mac_address=eth->getAddress();
  
  ip_tx_format=tx_format.addPrefix(IPHeaderLen);
  udp_tx_format=tx_format.addPrefix(IPHeaderLen+UDPHeaderLen);
  ip_rx_format=rx_format.addPrefix(IPHeaderLen);
  udp_rx_format=rx_format.addPrefix(IPHeaderLen+UDPHeaderLen);
  
  eth->attach(this);  
 }
   
NanoIPDevice::~NanoIPDevice()
 {
  eth->detach();
 }
 
void NanoIPDevice::getStat(IPStatInfo &ret)
 {
  Mutex::Lock lock(mutex);
  
  ret=stat_toget;
 }
 
void NanoIPDevice::send(Packet<uint8,IPTxExt> packet)
 {
  send_prepare_or_complete(packet,function_prepare_ip());
 }
 
void NanoIPDevice::send_udp(Packet<uint8,UDPTxExt> packet)
 {
  send_prepare_or_complete(packet,function_prepare_udp());
 }
 
void NanoIPDevice::send_icmp_echo(IPAddress dst,const ICMPEcho &echo,PtrLen<const uint8> data)
 {
  Packet<uint8,IPTxExt> packet=TryGetPacket<IPTxExt>(dst,IP_ICMP);
  
  if( !packet ) return;

  auto out_len=SaveLen(echo)+data.len;
  
  if( packet.checkDataLen(ip_tx_format,out_len) )
    {
     PtrLen<uint8> out_data=packet.setDataLen(ip_tx_format,out_len);
    
     BufPutDev dev(out_data.ptr);
     
     dev(echo);
     
     dev.put(data);
     
     send(packet);
    }
  else
    {
     packet.complete();
    }
 }
 
/* class NanoUDPEndpointDevice */  

PacketEndpointDevice::InboundProc * NanoUDPEndpointDevice::Engine::getProc()
 {
  Mutex::Lock lock(mutex);
  
  if( proc ) asem.inc();
  
  return proc;
 }
 
void NanoUDPEndpointDevice::Engine::inbound(Packet<uint8> packet,PtrLen<const uint8> data,UDPoint udpoint)
 {
  if( udpoint!=dst )
    {
     packet.complete();
     
     return;
    }
 
  if( InboundProc *proc=getProc() )
    {
     proc->inbound(packet,data);
    
     asem.dec();
    }
  else
    {
     packet.complete();
    }  
 }
     
void NanoUDPEndpointDevice::Engine::tick()
 {
  if( InboundProc *proc=getProc() )
    {
     proc->tick();
    
     asem.dec();
    }
 }
      
NanoUDPEndpointDevice::Engine::Engine(UDPoint dst_)
 : dst(dst_),
   asem("NanoUDPEndpointDevice"),
   mutex("NanoUDPEndpointDevice"),
   proc(0)
 {
 }
      
NanoUDPEndpointDevice::Engine::~Engine()
 {
  Mutex::Lock lock(mutex);
  
  if( proc ) Abort("Fatal error : CCore::Net::NanoUDPEndpointDevice is attached on exit");
 }
      
void NanoUDPEndpointDevice::Engine::attach(InboundProc *proc_)
 {
  bool has_proc;
  
  {
   Mutex::Lock lock(mutex);
   
   has_proc=(proc!=0);
   
   if( !has_proc ) proc=proc_;
  }
  
  if( has_proc )
    {
     Printf(Exception,"CCore::Net::NanoUDPEndpointDevice::Engine::attach(...) : already attached");
    }
 }
      
void NanoUDPEndpointDevice::Engine::detach()
 {
  {
   Mutex::Lock lock(mutex);
  
   proc=0;
  }
  
  asem.wait(); 
 }
      
NanoUDPEndpointDevice::NanoUDPEndpointDevice(StrLen ip_dev_name,UDPort udport,bool do_checksum,UDPoint dst)
 : engine(dst),
   udp_endpoint(ip_dev_name,udport,do_checksum,engine.function_inbound()),
   tick_endpoint(ip_dev_name,engine.function_tick())
 {
 }
   
NanoUDPEndpointDevice::~NanoUDPEndpointDevice()
 {
 }
   
PacketFormat NanoUDPEndpointDevice::getOutboundFormat()
 {
  return udp_endpoint.getUDPTxFormat();
 }
   
void NanoUDPEndpointDevice::outbound(Packet<uint8> packet)
 {
  udp_endpoint.send(packet,engine.getDst());
 }
   
ulen NanoUDPEndpointDevice::getMaxInboundLen()
 {
  return udp_endpoint.getMaxInboundLen();
 }
  
void NanoUDPEndpointDevice::attach(InboundProc *proc)
 {
  engine.attach(proc);
 }
   
void NanoUDPEndpointDevice::detach()
 {
  engine.detach();
 }
 
/* class NanoUDPMultipointDevice */ 

PacketMultipointDevice::InboundProc * NanoUDPMultipointDevice::Engine::getProc()
 {
  Mutex::Lock lock(mutex);
  
  if( proc ) asem.inc();
  
  return proc;
 }
     
void NanoUDPMultipointDevice::Engine::inbound(Packet<uint8> packet,PtrLen<const uint8> data,UDPoint udpoint)
 {
  if( InboundProc *proc=getProc() )
    {
     proc->inbound(udpoint.get(),packet,data);
    
     asem.dec();
    }
  else
    {
     packet.complete();
    }  
 }
     
void NanoUDPMultipointDevice::Engine::tick()
 {
  if( InboundProc *proc=getProc() )
    {
     proc->tick();
    
     asem.dec();
    }
 }
      
NanoUDPMultipointDevice::Engine::Engine()
 : asem("NanoUDPMultipointDevice"),
   mutex("NanoUDPMultipointDevice"),
   proc(0)
 {
 }
      
NanoUDPMultipointDevice::Engine::~Engine()
 {
  Mutex::Lock lock(mutex);
  
  if( proc ) Abort("Fatal error : CCore::Net::NanoUDPMultipointDevice is attached on exit");
 }
      
void NanoUDPMultipointDevice::Engine::attach(InboundProc *proc_)
 {
  bool has_proc;
  
  {
   Mutex::Lock lock(mutex);
   
   has_proc=(proc!=0);
   
   if( !has_proc ) proc=proc_;
  }
  
  if( has_proc )
    {
     Printf(Exception,"CCore::Net::NanoUDPMultipointDevice::Engine::attach(...) : already attached");
    }
 }
      
void NanoUDPMultipointDevice::Engine::detach()
 {
  {
   Mutex::Lock lock(mutex);
  
   proc=0;
  }
  
  asem.wait(); 
 }
      
NanoUDPMultipointDevice::NanoUDPMultipointDevice(StrLen ip_dev_name,UDPort udport,bool do_checksum)
 : udp_endpoint(ip_dev_name,udport,do_checksum,engine.function_inbound()),
   tick_endpoint(ip_dev_name,engine.function_tick())
 {
 }
   
NanoUDPMultipointDevice::~NanoUDPMultipointDevice()
 {
 }
 
StrLen NanoUDPMultipointDevice::toText(XPoint point,PtrLen<char> buf)
 {
  PrintBuf out(buf);
  
  UDPoint udpoint(point);
  
  Putobj(out,udpoint);
  
  return out.close();
 }
   
PacketFormat NanoUDPMultipointDevice::getOutboundFormat()
 {
  return udp_endpoint.getUDPTxFormat();
 }
   
void NanoUDPMultipointDevice::outbound(XPoint point,Packet<uint8> packet)
 {
  udp_endpoint.send(packet,UDPoint(point));
 }
   
ulen NanoUDPMultipointDevice::getMaxInboundLen()
 {
  return udp_endpoint.getMaxInboundLen();
 }
   
void NanoUDPMultipointDevice::attach(InboundProc *proc)
 {
  engine.attach(proc);
 }
   
void NanoUDPMultipointDevice::detach()
 {
  engine.detach();
 }
 
} // namespace Net
} // namespace CCore
 

