/* PTPConDevice.cpp */ 
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
 
#include <CCore/inc/net/PTPConDevice.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Net {
namespace PTPCon {

/* class ClientDevice */ 

void ClientDevice::OpenResult::complete(PacketHeader *packet_)
 {
  Packet<uint8,OpenExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  if( set(ext) ) con_id=ext->con_id;
  
  packet.popExt().complete();
 }
 
void ClientDevice::CloseResult::complete(PacketHeader *packet_)
 {
  Packet<uint8,CloseExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  set(ext);
  
  packet.popExt().complete();
 }
 
void ClientDevice::do_open(const ConId &con_id_) 
 {
  bool opened;
  
  {
   Mutex::Lock lock(mutex);
   
   opened=is_opened;
   
   if( !opened )
     {
      con_id=con_id_;
      is_opened=true;
      write_number=0;
      
      read_input.con_id=con_id_;
      
      write_error_flag=0;
     }
  }
  
  if( opened )
    {
     Printf(Exception,"CCore::Net::PTPCon::ClientDevice::open(...) : already opened");
    }
 }
 
bool ClientDevice::do_close(ConId &con_id_) 
 {
  bool opened;
  
  {
   Mutex::Lock lock(mutex);
   
   opened=is_opened;
   
   if( opened )
     {
      con_id_=con_id;
      
      is_opened=false;
     }
  }
  
  if( opened ) return true;
  
  Printf(NoException,"CCore::Net::PTPCon::ClientDevice::close(...) : already closed");
  
  return false;
 }
 
void ClientDevice::open(PacketSet<uint8> &pset,StrLen name,const Cfg &cfg)
 {
  TimeScope time_scope(cfg.timeout);
  OpenResult result;
  
  Packet<uint8> packet=pset.get(time_scope);
  
  if( !packet )
    {
     result.setNoPacket();
    }
  else if( !packet.checkDataLen(open_format,name.len) )  
    {
     packet.complete();
     
     result.setTransError(Trans_BadDataLen);
    }
  else
    {
     packet.setDataLen(open_format,name.len).copyFrom(name.ptr);  
       
     Packet<uint8,OpenExt> packet2=packet.pushExt<OpenExt>();  
     
     packet2.pushCompleteFunction(result.function_complete());
     
     OpenInput input(cfg.write_timeout_msec,cfg.read_timeout_msec,cfg.trigger_mask,name.len);
     
     ptp->start_format(packet2,input);
     
     pset.wait(time_scope);
    }
  
  result.guard<OpenExt>(Exception,ptp,pset,"CCore::Net::PTPCon::ClientDevice::open(...)",time_scope);

  do_open(result.con_id);
 }
   
void ClientDevice::close(PacketSet<uint8> &pset,MSec timeout)
 {
  CloseInput input;

  if( !do_close(input.con_id) ) return;
 
  TimeScope time_scope(timeout);
  CloseResult result;
  
  Packet<uint8> packet=pset.get(time_scope);
  
  if( !packet )
    {
     result.setNoPacket();
    }
  else
    {
     Packet<uint8,CloseExt> packet2=packet.pushExt<CloseExt>(); 
     
     packet2.pushCompleteFunction(result.function_complete());
     
     ptp->start(packet2,input); 
     
     pset.wait(time_scope); 
    }
  
  result.guard<CloseExt>(NoException,ptp,pset,"CCore::Net::PTPCon::ClientDevice::close(...)",time_scope);
 }
 
 // write

void ClientDevice::push_write()
 {
  for(;;)
    {
     {
      Mutex::Lock lock(mutex);
   
      if( list_count==0 || packet_count!=0 ) return;
   
      list_count--;
      packet_count++;
     }
     
     start_write();
     
     {
      Mutex::Lock lock(mutex);
   
      packet_count--;
     }
    }
 }
 
void ClientDevice::complete_write(PacketHeader *packet_)
 {
  Packet<uint8,WriteExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  if( !ext->isOk() ) write_error();
  
  packet.popExt().complete();
  
  {
   Mutex::Lock lock(mutex);
   
   packet_count--;
  }
  
  push_write();
 }
   
void ClientDevice::start_write(Packet<uint8> packet)
 {
  {
   Mutex::Lock lock(mutex);
   
   packet_count++;
  }
  
  Packet<uint8,WriteExt> packet2=packet.pushExt<WriteExt>();
  
  packet2.pushCompleteFunction(function_complete_write());
  
  WriteInput input;
  bool ok;
  
  {
   Mutex::Lock lock(mutex);
   
   if( is_opened )
     {
      input.con_id=con_id;
      input.number=write_number++;
      
      ok=true;
     }
   else
     {
      ok=false;
     }  
  }
  
  if( ok )
    {
     input.len=packet2.getDataLen(write_format).len;
  
     ptp->start_format(packet2,input);
    }
  else
    {
     packet2.getExt()->fail(Trans_Aborted);
     
     packet2.complete();
    }  
 }  
   
void ClientDevice::start_write()
 {
  Packet<uint8> packet=canlist.get(list);
  
  if( !packet ) return;
  
  start_write(packet);
 }
 
 // read

bool ClientDevice::getReadInput(ReadInput &input)
 {
  Mutex::Lock lock(mutex);
  
  if( is_opened )
    {
     input=read_input;
     
     return true;
    }
    
  return false;  
 }
 
void ClientDevice::complete_read(PacketHeader *packet_)
 {
  Packet<uint8,InputProc *,ReadExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  InputProc *proc=*packet.getDeepExt<1>();  
  
  if( !ext->isOk() )
    {
     proc->stop();
    
     packet.popExt().popExt().complete();
     
     return;
    }
    
  if( +ext->data ) 
    {
     PacketBuf pbuf;
    
     packet.detach(pbuf);
    
     proc->input(pbuf,ext->data);
    }
    
  ReadInput input;

  if( getReadInput(input) )
    {
     ext->reset();
     ext->data=Nothing;
     
     packet.provide();
    
     packet.pushCompleteFunction(function_complete_read());
    
     ptp->start(packet.forgetExt<1>(),input);
    } 
  else
    {
     proc->stop();
    
     packet.popExt().popExt().complete();
    } 
 }
 
ClientDevice::ClientDevice(StrLen ptp_dev_name)
 : hook(ptp_dev_name),
   ptp(hook),
   pset("PTPCon::ClientDevice.pset"),
   mutex("PTPCon::ClientDevice"),
   is_opened(false)
 {
  list_count=0;
  packet_count=0;
  
  const char *name="CCore::Net::PTPCon::ClientDevice::ClientDevice(...)";
  
  open_format=ptp->getFormat_guarded<OpenExt>(name);
  write_format=ptp->getFormat_guarded<WriteExt>(name);
  
  read_input.len=LenSub(name,ptp->getMaxInboundInfoLen(),DeltaReadLen);  
  read_input.number=0;
 }
   
ClientDevice::~ClientDevice() 
 {
  canlist.complete(list);
 }
 
void ClientDevice::write(Packet<uint8> packet)
 {
  if( packet.checkRange(write_format) )
    {
     canlist.put(list,packet);
     
     {
      Mutex::Lock lock(mutex);
      
      list_count++;
     }
     
     push_write();
    }
  else
    {
     packet.complete();
     
     write_error();
    }
 }
 
void ClientDevice::start_read(InputProc *proc)
 {
  ReadInput input;
  
  if( !getReadInput(input) )
    {
     Printf(Exception,"CCore::Net::PTPCon::ClientDevice::start_read(...) : not opened");
    }
    
  Packet<uint8> packet=pset.try_get();
  
  if( !packet )
    {
     Printf(Exception,"CCore::Net::PTPCon::ClientDevice::start_read(...) : no packet");
    }
    
  Packet<uint8,InputProc *,ReadExt> packet2=packet.pushExt<InputProc *>(proc).pushExt<ReadExt>(); 
  
  packet2.pushCompleteFunction(function_complete_read());
  
  ptp->start(packet2.forgetExt<1>(),input);
 }
 
void ClientDevice::stop_read()
 {
  pset.cancel_and_wait();
 }
 
} // namespace PTPCon
} // namespace Net
} // namespace CCore
 

