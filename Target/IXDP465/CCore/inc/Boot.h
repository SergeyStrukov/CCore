/* Boot.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Boot_h
#define CCore_inc_Boot_h
 
#include <CCore/inc/net/PTPBoot.h>

#include <CCore/inc/sys/SysCon.h>

#include <CCore/inc/Flash.h>

namespace CCore {

/* classes */ 

class Boot;

/* class Boot */ 

class Boot : public Net::PTPBoot::BootInfo
 {
   ulen delta;
   
   class Wait : public Funchor_nocopy
    {
      enum SignalCode
       {
        SignalTimeout,
        SignalDone,
        SignalKey,
       
        SignalLim
       };
     
      MultiSem<SignalLim-1> msem;
   
     public:
      
      Wait();
      
      ~Wait();
      
      void complete();
      
      Sys::ConInputResult key_any(char ch);
      
      void wait();
      
      Sys::ConInputFunction function_key() { return FunctionOf(this,&Wait::key_any); }
    };
   
   Wait wait;
   Sys::OwnConInput own;
   
  private:
  
   void boot_run() const;
   
   void boot_flash(ulen off) const;
 
  private:
   
   virtual void signal_complete();
   
   virtual void wait_complete();
  
  public:
  
   enum BootFlags
    {
     BootRun,
     BootFlash,
     BootFlashBoot
    };
    
   static const ulen DeltaFlash   = (Flash::Size/2)   ; 
   static const ulen AppFlashOff  = (Flash::Size/4)*3 ;
   static const ulen BootFlashOff = (Flash::Size/4)*2 ;
   static const ulen MaxFlashLen  = (Flash::Size/4)-Flash::BlockSize ;
   static const ulen ParamOff     = (Flash::Size/4)*3-Flash::BlockSize ;
   static const ulen ParamLen     = Flash::BlockSize ;
   static const ulen BootDataOff  = 64_KByte ;
 
   explicit Boot(bool half_flash); // if upper half is mapped
   
   ~Boot();
   
   void buildBoot(DynArray<unsigned> &ret,PtrLen<const unsigned> tail=Nothing) const;
   
   void show() const;
   
   void boot() const;
   
   PtrLen<const uint8> getParams() const
    {
     const uint8 *base=static_cast<const uint8 *>(Flash::GetBaseAddress());
     
     return PtrLen<const uint8>(base+ParamOff-delta,ParamLen);
    }
 };
 
} // namespace CCore
 
#endif
 

