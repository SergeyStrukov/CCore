/* EDID.cpp */ 
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
 
#include <CCore/inc/video/EDID.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {
namespace Video {

/* functions */

void GuardEDIDBroken()
 {
  Printf(Exception,"CCore::Video::GuardEDIDBroken() : EDID block is broken");
 }

/* struct EDIDMode */

static unsigned Build(uint8 lsb,uint16 msb) { return lsb|(msb<<8); }

EDIDMode::EDIDMode(const uint8 buf[EDIDLen])
 {
  static const uint8 Header[8]=
   {
    0x00, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0x00
   };
  
  if( !Range(buf,8).equal(Header) ) GuardEDIDBroken();
  
  {
   uint8 sum=0;
   
   for(uint8 b : Range(buf,EDIDLen) ) sum+=b;
   
   if( sum ) GuardEDIDBroken();
  }

  {
   const uint8 *desc=buf+54;
   
   pixel_clock=Build(desc[0],desc[1])*10;
   
   hlen=Build(desc[2],desc[4]>>4);
   hblank=Build(desc[3],desc[4]&0x0F);
   
   vlen=Build(desc[5],desc[7]>>4);
   vblank=Build(desc[6],desc[7]&0x0F);
   
   hsync_off=Build(desc[8],desc[11]>>6);
   hsync_pulse=Build(desc[9],(desc[11]>>4)&0x02);
   
   vsync_off=Build(desc[10]>>4,(desc[11]>>2)&0x02);
   vsync_pulse=Build(desc[10]&0x0F,desc[11]&0x02);
   
   flags=desc[17];
  }
 }

} // namespace Video
} // namespace CCore
 

