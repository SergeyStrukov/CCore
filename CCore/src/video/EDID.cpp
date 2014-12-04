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

/* static */

static unsigned Build(uint8 lsb,uint16 msb) { return lsb|(msb<<8); }

static unsigned Build(uint8 lsb,uint32 b1,uint32 b2,uint32 msb) { return lsb|(b1<<8)|(b2<<16)|(msb<<24); }

static char CharInd(unsigned index) { return "ABCDEFGHIJKLMNOPQRSTUVWXYZ     "[index-1]; } 

static ulen Cut(PtrLen<const char> text)
 {
  while( +text && text.back(1)==' ' ) text.len--;
  
  if( +text && text.back(1)=='\n' ) text.len--;
  
  return text.len;
 }

/* functions */

void GuardEDIDBroken()
 {
  Printf(Exception,"CCore::Video::GuardEDIDBroken() : EDID block is broken");
 }

/* struct EDIDTimingDesc */

EDIDTimingDesc::EDIDTimingDesc(const uint8 buf[18])
 {
  pixel_clock=Build(buf[0],buf[1])*10;
  
  hlen=Build(buf[2],buf[4]>>4);
  hblank=Build(buf[3],buf[4]&0x0F);
  
  vlen=Build(buf[5],buf[7]>>4);
  vblank=Build(buf[6],buf[7]&0x0F);
  
  hsync_off=Build(buf[8],buf[11]>>6);
  hsync_pulse=Build(buf[9],(buf[11]>>4)&0x02);
  
  vsync_off=Build(buf[10]>>4,(buf[11]>>2)&0x02);
  vsync_pulse=Build(buf[10]&0x0F,buf[11]&0x02);
  
  flags=buf[17];
 }

/* struct EDIDRangeLimitsDesc */

EDIDRangeLimitsDesc::EDIDRangeLimitsDesc(const uint8 buf[18])
 {
  min_vrate=buf[5];
  max_vrate=buf[6];
  
  min_hrate=buf[7];
  max_hrate=buf[8];
  
  max_pixel_clock=buf[9]*uint32(10000);
 }

/* struct EDIDExtDesc */

EDIDExtDesc::EDIDExtDesc(const uint8 buf[18])
 : text(),
   len(0)
 {
  type=buf[3];
  
  if( type==0xFC || type==0xFE || type==0xFF )
    {
     Range(text).copy(MutatePtr<const char>(buf+5));
     
     len=Cut(Range_const(text));
    }
 }

/* struct EDIDBlockDesc */

EDIDBlockDesc::EDIDBlockDesc(const uint8 buf[18])
 : index(Desc_none)
 {
  if( buf[0] || buf[1] )
    {
     index=Desc_timing;
     
     CreateAt(desc.timing);
     
     desc.timing=EDIDTimingDesc(buf);
    }
  else if( buf[3]==0xFD )
    {
     index=Desc_limits;
     
     CreateAt(desc.limits);
     
     desc.limits=EDIDRangeLimitsDesc(buf);
    }
  else
    {
     index=Desc_ext;
     
     CreateAt(desc.ext);
     
     desc.ext=EDIDExtDesc(buf);
    }
 }

/* struct EDIDBlock */

EDIDBlock::EDIDBlock(const uint8 buf[EDIDLen])
 {
  // 1
  {
   static const uint8 Header[8]=
    {
     0x00, 0xFF, 0xFF, 0xFF,
     0xFF, 0xFF, 0xFF, 0x00
    };
   
   if( !Range(Header).equal(buf) ) GuardEDIDBroken();
  }
  
  // 2
  {
   uint8 sum=0;
   
   for(uint8 b : Range(buf,EDIDLen) ) sum+=b;
   
   if( sum ) GuardEDIDBroken();
  }
  
  // 3
  {
   uint16 vendor=Build(buf[9],buf[8]);
   
   vendor_name[0]=CharInd( (vendor>>10)&31u );
   vendor_name[1]=CharInd( (vendor>> 5)&31u );
   vendor_name[2]=CharInd( (vendor    )&31u );
   
   product_id=Build(buf[10],buf[11]);
   serial_number=Build(buf[12],buf[13],buf[14],buf[15]);
   block_version=buf[18];
   block_revision=buf[19];
   hlen_cm=buf[21];
   vlen_cm=buf[22];
   ext_count=buf[126];
  }
  
  //4
  {
   desc[0]=EDIDBlockDesc(buf+54);
   desc[1]=EDIDBlockDesc(buf+72);
   desc[2]=EDIDBlockDesc(buf+90);
   desc[3]=EDIDBlockDesc(buf+108);
  }
 }

} // namespace Video
} // namespace CCore
 

