/* EDID.h */ 
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

#ifndef CCore_inc_video_EDID_h
#define CCore_inc_video_EDID_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Video {

/* consts */

const ulen EDIDLen = 128 ;

/* functions */

void GuardEDIDBroken();

/* classes */

struct EDIDMode;

/* struct EDIDMode */

struct EDIDMode
 {
  unsigned hlen;        // 12 bit
  unsigned hblank;      // 12 bit
  unsigned hsync_off;   // 10 bit
  unsigned hsync_pulse; // 10 bit
  
  unsigned vlen;        // 12 bit
  unsigned vblank;      // 12 bit
  unsigned vsync_off;   // 6 bit
  unsigned vsync_pulse; // 6 bit
  
  unsigned pixel_clock; // kHz
  
  unsigned flags;
  
  EDIDMode() {}
  
  explicit EDIDMode(const uint8 buf[EDIDLen]);
  
  bool isInterlaced() const { return flags&0x80; }
  
  enum SyncType
   {
    AnalogCompisite        = 0,
    BipolarAnalogCompisite = 1,
    DigitalComposite       = 2, 
    DigitalSeparate        = 3 
   };
  
  unsigned syncType() const { return (flags>>3)&0x02; }
  
  bool hsyncPos() const { return flags&0x02; } // Digital...
  
  bool vsyncPos() const { return flags&0x04; } // DigitalSeparate
  
  unsigned freq() const { return (pixel_clock*1000)/((hlen+hblank)*(vlen+vblank)); }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

} // namespace Video
} // namespace CCore
 
#endif
 

