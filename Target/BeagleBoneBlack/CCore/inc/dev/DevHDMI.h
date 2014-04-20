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
#include <CCore/inc/dev/DevI2C.h>
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
      I2C dev;
      
      uint8 slave;
      
     private:
      
      void setSlave(uint8 address)
       {
        if( address!=slave )
          {
           dev.setSlave7(address);
          
           slave=address;
          }
       }
      
     public:
      
      RegRW()
       : dev(I2C_0),
         slave(0)
       {
        dev.init_fast();
       }
      
      ~RegRW()
       {
       }
      
      void setCEC() { setSlave(0x34); }
      
      void setHDMI() { setSlave(0x70); }
      
      uint8 get(uint8 address) 
       {
        uint8 ret;
        
        dev.exchange(Range_const(&address,1),Range(&ret,1));
        
        return ret;
       }
      
      void set(uint8 address,uint8 value) 
       {
        uint8 temp[]={address,value};
        
        dev.write(Range_const(temp));
       }
      
      void set(uint8 address,uint8 value1,uint8 value2) 
       {
        uint8 temp[]={address,value1,value2};
        
        dev.write(Range_const(temp));
       }
    };
   
   class CECRegRW : NoCopy
    {
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
      RegRW &dev;
      
      uint16 page;
      
     private:
      
      void setPage(uint8 page_)
       {
        if( page!=page_ )
          {
           dev.set(0xFF,page_);
          
           page=page_;
          }
       }
      
     public:
      
      explicit HDMIRegRW(RegRW &dev_) : dev(dev_),page(0xFFFF) {}

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
 
   HDMI();
   
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
   
   void enableVIP();
   
   void disableVIP();
   
   void readEDID(uint8 block[Video::EDIDLen],unsigned number=0);

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
 

