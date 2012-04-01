/* RedirectPTPCon.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/RedirectPTPCon.h>
 
namespace CCore {

/* class RedirectPTPCon::Engine */ 

ulen RedirectPTPCon::Engine::proc(PtrLen<const uint8> str,char *out)
 {
  ulen ret=0;
  
  Sys::HookConInput hook;
  
  for(; +str ;++str)
    {
     char ch=*str;
     
     switch( hook(ch) )
       {
        case Sys::Con_Echo : out[ret++]=ch; break;
        
        case Sys::Con_EOL : out[ret++]='\n'; break;
        
        default: ; // do nothing
       }
    }
  
  return ret;
 }

void RedirectPTPCon::Engine::write(PtrLen<const char> str) 
 {
  PacketFormat format=open_close.getWriteFormat();
  
  while( +str )
    {
     Packet<uint8> packet=pset.get(timeout);
     
     if( !packet ) return;
     
     PtrLen<const char> frame=str.takeup(packet.getMaxDataLen(format).len);
     
     if( !frame.len )
       {
        packet.complete();
       
        return;
       }
     
     packet.setDataLen(format,frame.len).copyFrom(frame.ptr);
     
     open_close.write(packet);
    }
 }
 
void RedirectPTPCon::Engine::write_try(PtrLen<const char> str) 
 {
  PacketFormat format=open_close.getWriteFormat();
  
  while( +str )
    {
     Packet<uint8> packet=pset.try_get();
     
     if( !packet ) return;
     
     PtrLen<const char> frame=str.takeup(packet.getMaxDataLen(format).len);
     
     if( !frame.len )
       {
        packet.complete();
       
        return;
       }
     
     packet.setDataLen(format,frame.len).copyFrom(frame.ptr);
     
     open_close.write(packet);
    }
 }
 
void RedirectPTPCon::Engine::output(NanoPacket<char> packet)
 {
  write(Range_const(packet.getRange()));
  
  packet.free();  
 }
     
void RedirectPTPCon::Engine::input(PacketBuf &,PtrLen<const uint8> str)
 {
  const ulen Len = 128 ;
  
  char temp[Len];
  
  for(;;)
    {
     PtrLen<const uint8> frame=str.takeup(Len);
     
     if( !frame ) return;
     
     ulen len=proc(frame,temp);
     
     write_try(Range_const(temp,len));
    }
 }
     
void RedirectPTPCon::Engine::stop()
 {
  if( reading ) write_try(StrLen("\nConsole is lost !\n"));
 }
 
RedirectPTPCon::Engine::Engine(StrLen con_device_name,StrLen name,const Net::PTPCon::Cfg &cfg)
 : open_close(con_device_name,name,cfg),
   pset("RedirectPTPCon"),
   timeout(cfg.timeout)
 {
  reading=1;
  
  open_close.start_read(this);
 }
      
RedirectPTPCon::Engine::~Engine()
 {
  reading=0;
 
  open_close.stop_read();
  
  pset.wait(timeout);
 }
 
/* class RedirectPTPCon */ 

RedirectPTPCon::RedirectPTPCon(StrLen con_device_name,StrLen name,const Net::PTPCon::Cfg &cfg)
 : engine(con_device_name,name,cfg),
   redirect("RedirectPTPCon",engine.function_output())
 {
 }
   
RedirectPTPCon::~RedirectPTPCon() 
 {
 }
 
} // namespace CCore
 

