/* DevHDMI.h */
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

#ifndef CCore_inc_dev_DevHDMI_h
#define CCore_inc_dev_DevHDMI_h

#include <CCore/inc/video/EDID.h>
#include <CCore/inc/I2CDevice.h>
#include <CCore/inc/dev/NXP.HDMI.h>

namespace CCore {
namespace Dev {

/* classes */

class HDMI;

/* class HDMI */

class HDMI : NoCopy
 {
   class RegRW : NoCopy
    {
      ObjHook hook;
      
      I2CDevice *dev;
      
     public:
      
      explicit RegRW(StrLen i2c_dev_name);
      
      ~RegRW();
      
      uint8 get(uint8 slave_address,uint8 address); 
      
      void set(uint8 slave_address,uint8 address,uint8 value); 
      
      void set(uint8 slave_address,uint8 address,uint8 value1,uint8 value2); 
    };
   
   class CECRegRW : NoCopy
    {
      static const uint8 SlaveAddress = 0x34 ; 
     
      RegRW &dev;
      
     public:
      
      explicit CECRegRW(RegRW &dev_) : dev(dev_) {}

      typedef uint8 AddressType; 

      template <class UInt>
      UInt get(AddressType address);
      
      template <class UInt>
      void set(AddressType address,UInt value);
    };
   
   class HDMIRegRW : NoCopy
    {
      static const uint8 SlaveAddress = 0x70 ;
      
      RegRW &dev;
      
      uint16 page = 0xFFFF ;
      
     private:
      
      void setPage(uint8 page_);
      
     public:
      
      explicit HDMIRegRW(RegRW &dev_) : dev(dev_) {}

      typedef uint16 AddressType; 

      template <class UInt>
      UInt get(AddressType address);
      
      template <class UInt>
      void set(AddressType address,UInt value);
    };
   
   RegRW regRW;
   
   NXP::HDMI::CECBar<CECRegRW> barCEC;
   NXP::HDMI::HDMIBar<HDMIRegRW> barHDMI;
  
  public:
 
   explicit HDMI(StrLen i2c_dev_name);
   
   ~HDMI();
   
   void init();
   
   struct Detect
    {
     bool plug;
     bool power;
     
     Detect() {}
     
     Detect(bool plug_,bool power_) : plug(plug_),power(power_) {}
    };
   
   Detect detect();
   
   struct IntInfo
    {
     bool plug;
     bool power;
     bool edid;
     
     IntInfo() {}
     
     IntInfo(bool plug_,bool power_,bool edid_) : plug(plug_),power(power_),edid(edid_) {}
    };
   
   IntInfo getIntInfo();
   
   void enableVIP();
   
   void disableVIP();
   
   void startReadEDID(unsigned number);
   
   void readEDID(uint8 block[Video::EDIDLen]);
   
   void finishReadEDID();
   
   class ReadEDID : NoCopy
    {
      HDMI &hdmi;
      
     public:
      
      ReadEDID(HDMI &hdmi_,unsigned number) : hdmi(hdmi_) { hdmi_.startReadEDID(number); }
      
      ~ReadEDID() { hdmi.finishReadEDID(); }
      
      void operator () (uint8 block[Video::EDIDLen]) { hdmi.readEDID(block); }
    };

   struct Mode
    {
     uint32 htotal;
     uint32 hdisplay;
     uint32 hsync_start;
     uint32 hsync_end;
     
     uint32 vtotal;
     uint32 vdisplay;
     uint32 vsync_start;
     uint32 vsync_end;
     
     uint32 pixel_clock; // kHz
     
     bool hsync_neg;
     bool vsync_neg;
     
     Mode() {}
     
     Mode(const Video::EDIDMode &mode);
    };
   
   void setMode(const Mode &mode);
 };

} // namespace Dev
} // namespace CCore
 
#endif
 

