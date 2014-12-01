/* Boot.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Boot_h
#define CCore_inc_Boot_h
 
#include <CCore/inc/net/PTPBoot.h>

namespace CCore {

/* classes */ 

class Boot;

/* class Boot */ 

class Boot : public Net::PTPBoot::BootInfo
 {
   class Wait : NoCopy
    {
      Event event;
   
     public:
      
      Wait();
      
      ~Wait();
      
      void complete();
      
      void wait();
    };
   
   Wait wait;
   
  private:
  
   using UnitType = unsigned ;
   
   static const uint32 MinAddress   = 0x80100000 ;
   static const uint32 LimAddress   = 0x90000000 ;
   static const uint32 TopAddress   = 0xA0000000 ;
   static const uint32 AlignAddress =          4 ;
   
   const unsigned UnitLen = sizeof (UnitType) ;
   
   DynArray<UnitType> buf;

   void buildBoot(PtrLen<const UnitType> tail=Nothing);
   
   enum BootFlags
    {
     BootRun,
     BootFlash,
     BootFlashBoot
    };
   
   void boot_run();
   
   void boot_flash();
 
   void boot_flashboot();
   
  private:
   
   virtual void signal_complete();
   
   virtual void wait_complete();
  
  public:
  
   Boot();
   
   ~Boot();
   
   void show() const;
   
   void prepareBoot();
   
   void commitBoot() const;
 };
 
} // namespace CCore
 
#endif
 

