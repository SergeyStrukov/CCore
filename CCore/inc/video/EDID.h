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

struct EDIDTimingDesc;

struct EDIDRangeLimitsDesc;

struct EDIDExtDesc;

struct EDIDBlockDesc;

struct EDIDBlock;

/* struct EDIDTimingDesc */

struct EDIDTimingDesc
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
  
  EDIDTimingDesc() {}
  
  explicit EDIDTimingDesc(const uint8 buf[18]);
  
  // properties
  
  bool isInterlaced() const { return flags&0x80; }
  
  enum SyncType
   {
    AnalogComposite        = 0,
    BipolarAnalogComposite = 1,
    DigitalComposite       = 2, 
    DigitalSeparate        = 3 
   };
  
  friend const char * GetTextDesc(SyncType sync_type)
   {
    switch( sync_type )
      {
       case AnalogComposite        : return "analog-composite";
       case BipolarAnalogComposite : return "bipolar-analog-composite";
       case DigitalComposite       : return "digital-composite";
       case DigitalSeparate        : return "digital-separate";
       
       default: return "???";
      }
   }
  
  SyncType syncType() const { return SyncType( (flags>>3)&0x02 ); }
  
  bool hsyncPositive() const { return flags&0x02; } // Digital...
  
  bool vsyncPositive() const { return flags&0x04; } // DigitalSeparate
  
  unsigned freq() const { return (pixel_clock*1000)/((hlen+hblank)*(vlen+vblank)); }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"H: len = #; blank = #; sync-off = #; sync-pulse = #;\n",hlen,hblank,hsync_off,hsync_pulse);
    Printf(out,"V: len = #; blank = #; sync-off = #; sync-pulse = #;\n",vlen,vblank,vsync_off,vsync_pulse);
    Printf(out,"Pixel Clock = #; kHz\n",pixel_clock);
    
    Putobj(out,"Flags =");
    
    if( isInterlaced() ) Putobj(out," interlaced");
    
    SyncType sync_type=syncType();
    
    Printf(out," #;",sync_type);
    
    switch( sync_type )
      {
       case DigitalSeparate :
        {
         Printf(out," #; #;",(hsyncPositive()?"HSync+":"HSync-"),(vsyncPositive()?"VSync+":"VSync-"));
        }
       break;
       
       case DigitalComposite :
        {
         Printf(out," #;",(hsyncPositive()?"HSync+":"HSync-"));
         
         if( vsyncPositive() ) Putobj(out," VSync-serrated");
        }
       break; 
      }
    
    Putobj(out,"\n");
    
    Printf(out,"Freq = #; Hz\n",freq());
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* struct EDIDRangeLimitsDesc */

struct EDIDRangeLimitsDesc
 {
  uint8 min_vrate; // Hz
  uint8 max_vrate; // Hz
  
  uint8 min_hrate; // kHz
  uint8 max_hrate; // kHz
  
  uint32 max_pixel_clock; // kHz
  
  EDIDRangeLimitsDesc() {}
  
  explicit EDIDRangeLimitsDesc(const uint8 buf[18]);
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"min V-Rate = #; Hz\n",min_vrate);
    Printf(out,"max V-Rate = #; Hz\n",max_vrate);
    Printf(out,"min H-Rate = #; kHz\n",min_hrate);
    Printf(out,"max H-Rate = #; kHz\n",max_hrate);
    Printf(out,"max Pixel Clock = #; kHz\n",max_pixel_clock);
   }
 };

/* struct EDIDExtDesc */

struct EDIDExtDesc
 {
  uint8 type;
  
  char text[13];
  ulen len;
  
  EDIDExtDesc() {}
  
  explicit EDIDExtDesc(const uint8 buf[18]);
  
  StrLen getText() const { return Range(text,len); }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    switch( type )
      {
       case 0xFA : Putobj(out,"additional standard timing identifiers\n"); break;
       case 0xFB : Putobj(out,"additional white point data\n"); break;
       case 0xFD : Putobj(out,"monitor range limits\n"); break;
       
       case 0xFC : Printf(out,"monitor name #.q;\n",getText()); break;
       case 0xFE : Printf(out,"unspecified text #.q;\n",getText()); break;
       case 0xFF : Printf(out,"monitor serial number #.q;\n",getText()); break;
     
       default: Putobj(out,"unknown\n");
      }
   }
 };

/* struct EDIDBlockDesc */

struct EDIDBlockDesc
 {
  union Desc
   {
    EDIDTimingDesc timing;
    EDIDRangeLimitsDesc limits;
    EDIDExtDesc ext;
    
    Desc() {}
   };
  
  enum DescIndex
   {
    Desc_none,
    Desc_timing,
    Desc_limits,
    Desc_ext
   };
  
  Desc desc;
  DescIndex index;
  
  EDIDBlockDesc() : index(Desc_none) {}
  
  explicit EDIDBlockDesc(const uint8 buf[18]);
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    switch( index )
      {
       case Desc_none   : Putobj(out,"none\n");    break;
       case Desc_timing : Putobj(out,desc.timing); break;
       case Desc_limits : Putobj(out,desc.limits); break;
       case Desc_ext    : Putobj(out,desc.ext);    break;
      }
   }
 };

/* struct EDIDBlock */

struct EDIDBlock
 {
  char vendor_name[3];
  
  uint16 product_id;
  uint32 serial_number;
  
  uint8 block_version;
  uint8 block_revision;
  
  uint8 hlen_cm;
  uint8 vlen_cm;
  
  uint8 ext_count;
  
  EDIDBlockDesc desc[4];
  
  EDIDBlock() {}
  
  explicit EDIDBlock(const uint8 buf[EDIDLen]);
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"vendor = #;\n",StrLen(Range_const(vendor_name)));
    Printf(out,"product id = #;\n",product_id);
    Printf(out,"serial number = #;\n",serial_number);
    Printf(out,"version = #;.#;\n",block_version,block_revision);
    Printf(out,"width = #; cm\n",hlen_cm);
    Printf(out,"heights = #; cm\n",vlen_cm);
    Printf(out,"extension blocks = #;\n",ext_count);
    
    Printf(out,"\n#;",desc[0]);
    Printf(out,"\n#;",desc[1]);
    Printf(out,"\n#;",desc[2]);
    Printf(out,"\n#;",desc[3]);
   }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

