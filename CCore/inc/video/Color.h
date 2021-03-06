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

const unsigned ClrBits = 8 ;

const unsigned AlphaLim = 256 ;

const Clr MinClr =   0 ;

const Clr MedClr = 128 ;

const Clr MaxClr = 255 ;

/* functions */

inline Clr Blend(Clr dst,Clr alpha,Clr src)
 {
  return Clr( (dst*uint16(256-alpha)+src*uint16(alpha))>>8 );
 }

inline uint16 BlendBeta(Clr alpha) { return uint16(256-alpha); }

inline uint16 BlendSrc(Clr alpha,Clr src) { return src*uint16(alpha); }

inline Clr PreparedBlend(Clr dst,uint16 beta,uint16 src)
 {
  return Clr( (dst*beta+src)>>8 );
 }

/* classes */

//enum VColor;

class Blender;

class RawColor16;

class RawColor24;

class RawColor24Inv;

class RawColor32;

class RawColor32Inv;

/* enum VColor */

enum VColor : uint32
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

inline constexpr Clr RedOf(VColor vc) { return Clr(vc>>16); }

inline constexpr Clr GreenOf(VColor vc) { return Clr(vc>>8); }

inline constexpr Clr BlueOf(VColor vc) { return Clr(vc); }

inline constexpr VColor RGBColor(Clr r,Clr g,Clr b) { return VColor(b|(uint32(g)<<8)|(uint32(r)<<16)); }

inline constexpr VColor GrayColor(Clr rgb) { return RGBColor(rgb,rgb,rgb); }

/* class Blender */

class Blender
 {
   uint16 beta;
   
   uint16 src_r;
   uint16 src_g;
   uint16 src_b;
   
  public: 
  
   Blender(Clr alpha,VColor vc)
    {
     beta=BlendBeta(alpha);
     
     src_r=BlendSrc(alpha,RedOf(vc));
     src_g=BlendSrc(alpha,GreenOf(vc));
     src_b=BlendSrc(alpha,BlueOf(vc));
    }
   
   Clr blendR(Clr r) const { return PreparedBlend(r,beta,src_r); }
   
   Clr blendG(Clr g) const { return PreparedBlend(g,beta,src_g); }
   
   Clr blendB(Clr b) const { return PreparedBlend(b,beta,src_b); }
 };

/* class RawColor16 */

class RawColor16
 {
  public:
  
   using Raw = uint16 ;
  
   static const unsigned RawCount = 1 ;
  
  private:
  
   Raw color[RawCount];
  
  private:
  
   static uint16 Pack565(uint16 r,uint16 g,uint16 b) { return (r<<11)|(g<<5)|b; }
  
  public:
  
   RawColor16(VColor vc=Black) { set(vc); }
   
   // methods
   
   void set(VColor vc) { set(RedOf(vc),GreenOf(vc),BlueOf(vc)); }
   
   void set(Clr r,Clr g,Clr b) { color[0]=Pack565(r>>3,g>>2,b>>3); }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; }
   
   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; }
   
   static void BlendTo(Blender blender,Raw dst[RawCount])
    {
     Raw raw=dst[0];
     
     Clr r=Clr( (raw>>11)<<3 );
     Clr g=Clr( (raw>>5)<<2 );
     Clr b=Clr( raw<<3 );
     
     dst[0]=Pack565(blender.blendR(r),blender.blendG(g),blender.blendB(b));
    }
   
   void blend(Blender blender) { BlendTo(blender,color); }
   
   void blend(Clr alpha,VColor vc) { blend({alpha,vc}); }
 };

/* class RawColor24 */

class RawColor24
 {
  public:
  
   using Raw = uint8 ;
  
   static const unsigned RawCount = 3 ;
  
  private:
  
   Raw color[RawCount];
  
  public:
  
   RawColor24(VColor vc=Black) { set(vc); }
   
   // methods
   
   void set(VColor vc) { set(RedOf(vc),GreenOf(vc),BlueOf(vc)); }
   
   void set(Clr r,Clr g,Clr b) { color[0]=r; color[1]=g; color[2]=b; }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; dst[1]=color[1]; dst[2]=color[2]; }
   
   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; color[1]=src[1]; color[2]=src[2]; }
   
   static void BlendTo(Blender blender,Raw dst[RawCount])
    {
     dst[0]=blender.blendR(dst[0]);
     dst[1]=blender.blendG(dst[1]);
     dst[2]=blender.blendB(dst[2]);
    }
   
   void blend(Blender blender) { BlendTo(blender,color); }
   
   void blend(Clr alpha,VColor vc) { blend({alpha,vc}); }
 };

/* class RawColor24Inv */

class RawColor24Inv
 {
  public:
  
   using Raw = uint8 ;
  
   static const unsigned RawCount = 3 ;
  
  private:
  
   Raw color[RawCount];
  
  public:
  
   RawColor24Inv(VColor vc=Black) { set(vc); }
   
   // methods
   
   void set(VColor vc) { set(RedOf(vc),GreenOf(vc),BlueOf(vc)); }
   
   void set(Clr r,Clr g,Clr b) { color[0]=b; color[1]=g; color[2]=r; }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; dst[1]=color[1]; dst[2]=color[2]; }
   
   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; color[1]=src[1]; color[2]=src[2]; }
   
   static void BlendTo(Blender blender,Raw dst[RawCount])
    {
     dst[0]=blender.blendB(dst[0]);
     dst[1]=blender.blendG(dst[1]);
     dst[2]=blender.blendR(dst[2]);
    }
   
   void blend(Blender blender) { BlendTo(blender,color); }
   
   void blend(Clr alpha,VColor vc) { blend({alpha,vc}); }
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
  
   RawColor32(VColor vc=Black) { set(vc); }
   
   // methods
   
   void set(VColor vc) { color[0]=vc; }
   
   void set(Clr r,Clr g,Clr b) { color[0]=Pack888(r,g,b); }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; }
   
   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; }
   
   static void BlendTo(Blender blender,Raw dst[RawCount])
    {
     Raw raw=dst[0];
     
     Clr r=Clr(raw>>16);
     Clr g=Clr(raw>> 8);
     Clr b=Clr(raw    );
     
     dst[0]=Pack888(blender.blendR(r),blender.blendG(g),blender.blendB(b));
    }
 
   void blend(Blender blender) { BlendTo(blender,color); }
   
   void blend(Clr alpha,VColor vc) { blend({alpha,vc}); }
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
  
   RawColor32Inv(VColor vc=Black) { set(vc); }
   
   // methods
   
   void set(VColor vc) { set(RedOf(vc),GreenOf(vc),BlueOf(vc)); }
   
   void set(Clr r,Clr g,Clr b) { color[0]=Pack888(r,g,b); }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; }
   
   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; }
   
   static void BlendTo(Blender blender,Raw dst[RawCount])
    {
     Raw raw=dst[0];
     
     Clr r=Clr(raw    );
     Clr g=Clr(raw>> 8);
     Clr b=Clr(raw>>16);
     
     dst[0]=Pack888(blender.blendR(r),blender.blendG(g),blender.blendB(b));
    }
   
   void blend(Blender blender) { BlendTo(blender,color); }
   
   void blend(Clr alpha,VColor vc) { blend({alpha,vc}); }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

