/* Color.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_Color_h
#define CCore_inc_video_Color_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Video {

/* types */

using Clr = uint8 ;

/* consts */

const Clr MinClr =   0 ;

const Clr MedClr = 128 ;

const Clr MaxClr = 255 ;

/* classes */

//enum ColorName;

class RawColor16;

class RawColor24;

class RawColor24Inv;

class RawColor32;

class RawColor32Inv;

struct ColorPlane;

/* enum ColorName */

enum ColorName : uint32
 {
  Black       = 0x000000,
  Gray        = 0x808080,
  Silver      = 0xC0C0C0,
  White       = 0xFFFFFF,
  
  Red         = 0xFF0000,
  Green       = 0x00FF00,
  Blue        = 0x0000FF,

  Cyan        = 0x00FFFF,
  Fuchsia     = 0xFF00FF,
  Yellow      = 0xFFFF00,
  
  Teal        = 0x008080,
  Purple      = 0x800080, 
  Olive       = 0x808000,
  
  // extra
  
  Aqua        = 0x00FFFF,
  Maroon      = 0x800000,
  Navy        = 0x000080,
  Orange      = 0xFFA500,
  Crimson     = 0xDC143C,
  DarkGray    = 0xA9A9A9,
  DarkGreen   = 0x006400,
  DarkOrange  = 0xFF8C00,
  DarkOrchid  = 0x9932CC,
  DarkRed     = 0x8B0000,
  DarkViolet  = 0x9400D3,
  DimGray     = 0x696969,
  ForestGreen = 0x228B22,
  GhostWhite  = 0xF8F8FF,
  Gold        = 0xFFD700,
  GoldenRod   = 0xDAA520,
  Indigo      = 0x4B0082,
  Ivory       = 0xFFFFF0,
  Lavender    = 0xE6E6FA,
  LightGray   = 0xD3D3D3,
  MediumBlue  = 0x0000CD,
  OrangeRed   = 0xFF4500,
  Orchid      = 0xDA70D6,
  SeaGreen    = 0x2E8B57,
  SkyBlue     = 0x87CEEB,
  Snow        = 0xFFFAFA,
  SteelBlue   = 0x4682B4,
  Violet      = 0xEE82EE,
  Wheat       = 0xF5DEB3
 };

inline constexpr Clr RedOf(ColorName cname) { return Clr(cname>>16); }

inline constexpr Clr GreenOf(ColorName cname) { return Clr(cname>>8); }

inline constexpr Clr BlueOf(ColorName cname) { return Clr(cname); }

inline constexpr ColorName RGBColor(Clr r,Clr g,Clr b) { return ColorName(b|(uint32(g)<<8)|(uint32(r)<<16)); }

/* class RawColor16 */

class RawColor16
 {
  public:
  
   using Raw = uint16 ;
  
   static const ulen RawCount = 1 ;
  
  private:
  
   Raw color[RawCount];
  
  private:
  
   static uint16 Pack565(uint16 r,uint16 g,uint16 b) { return (r<<11)|(g<<5)|b; }
  
  public:
  
   RawColor16(ColorName cname=Black) { set(cname); }
   
   // methods
   
   void set(ColorName cname) { set(RedOf(cname),GreenOf(cname),BlueOf(cname)); }
   
   void set(Clr r,Clr g,Clr b) { color[0]=Pack565(r>>3,g>>2,b>>3); }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; }
   
   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; }
 };

/* class RawColor24 */

class RawColor24
 {
  public:
  
   using Raw = uint8 ;
  
   static const ulen RawCount = 3 ;
  
  private:
  
   Raw color[RawCount];
  
  public:
  
   RawColor24(ColorName cname=Black) { set(cname); }
   
   // methods
   
   void set(ColorName cname) { set(RedOf(cname),GreenOf(cname),BlueOf(cname)); }
   
   void set(Clr r,Clr g,Clr b) { color[0]=r; color[1]=g; color[2]=b; }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; dst[1]=color[1]; dst[2]=color[2]; }
   
   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; color[1]=src[1]; color[2]=src[2]; }
 };

/* class RawColor24Inv */

class RawColor24Inv
 {
  public:
  
   using Raw = uint8 ;
  
   static const ulen RawCount = 3 ;
  
  private:
  
   Raw color[RawCount];
  
  public:
  
   RawColor24Inv(ColorName cname=Black) { set(cname); }
   
   // methods
   
   void set(ColorName cname) { set(RedOf(cname),GreenOf(cname),BlueOf(cname)); }
   
   void set(Clr r,Clr g,Clr b) { color[0]=b; color[1]=g; color[2]=r; }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; dst[1]=color[1]; dst[2]=color[2]; }
   
   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; color[1]=src[1]; color[2]=src[2]; }
 };

/* class RawColor32 */

class RawColor32
 {
  public:
  
   using Raw = uint32 ;
  
   static const unsigned RawCount = 1 ;
  
  private:
  
   Raw color[RawCount];
   
   static uint32 Pack888(uint32 r,uint32 g,uint32 b) { return b|(g<<8)|(r<<16); }
  
  public:
  
   RawColor32(ColorName cname=Black) { set(cname); }
   
   // methods
   
   void set(ColorName cname) { color[0]=cname; }
   
   void set(Clr r,Clr g,Clr b) { color[0]=Pack888(r,g,b); }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; }
   
   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; }
 };

/* class RawColor32Inv */

class RawColor32Inv
 {
  public:
  
   using Raw = uint32 ;
  
   static const unsigned RawCount = 1 ;
  
  private:
  
   Raw color[RawCount];
   
   static uint32 Pack888(uint32 r,uint32 g,uint32 b) { return r|(g<<8)|(b<<16); }
  
  public:
  
   RawColor32Inv(ColorName cname=Black) { set(cname); }
   
   // methods
   
   void set(ColorName cname) { set(RedOf(cname),GreenOf(cname),BlueOf(cname)); }
   
   void set(Clr r,Clr g,Clr b) { color[0]=Pack888(r,g,b); }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; }
   
   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; }
 };

/* struct ColorPlane */

struct ColorPlane
 {
  void *raw;
  int dx;
  int dy;
  int dline; // in chars
  
  ColorPlane() : raw(0),dx(0),dy(0),dline(0) {}
  
  ColorPlane(void *raw_,int dx_,int dy_,int dline_) : raw(raw_),dx(dx_),dy(dy_),dline(dline_) {}
 };

} // namespace Video
} // namespace CCore
 
#endif
 

