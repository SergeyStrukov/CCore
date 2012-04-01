/* RedirectPTPCon.h */ 
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

#ifndef CCore_inc_RedirectPTPCon_h
#define CCore_inc_RedirectPTPCon_h

#include <CCore/inc/Print.h>

#include <CCore/inc/sys/SysCon.h>
 
namespace CCore {

/* classes */ 

class RedirectPTPCon;

/* class RedirectPTPCon */ 

class RedirectPTPCon : NoCopy
 {
   class Engine : PTPConOpenClose::InputProc , public Funchor_nocopy
    {
      PTPConOpenClose open_close;
      
      PacketSet<uint8> pset;
      
      MSec timeout;
      
      Atomic reading;
      
     private:
      
      ulen proc(PtrLen<const uint8> str,char *out);
      
      void write(PtrLen<const char> str);
      
      void write_try(PtrLen<const char> str);
      
      void output(NanoPacket<char> packet);
     
      // PTPConOpenClose::InputProc
    
      virtual void input(PacketBuf &pbuf,PtrLen<const uint8> str);
     
      virtual void stop();
     
     public:
     
      Engine(StrLen con_device_name,StrLen name,const Net::PTPCon::Cfg &cfg);
      
      ~Engine();
      
      Sys::ConOutputFunction function_output() { return FunctionOf(this,&Engine::output); }
    };
    
   Engine engine;
   
   Sys::RedirectCon redirect;
    
  public:  
  
   RedirectPTPCon(StrLen con_device_name,StrLen name,const Net::PTPCon::Cfg &cfg=DefaultValue());
   
   ~RedirectPTPCon();
 };
 
} // namespace CCore
 
#endif
 

