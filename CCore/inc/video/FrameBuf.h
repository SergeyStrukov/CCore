/* FrameBuf.h */ 
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

#ifndef CCore_inc_video_FrameBuf_h
#define CCore_inc_video_FrameBuf_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Video {

/* classes */

//enum ColorName;

class Color565;

template <class Color> class FrameBuf;

/* enum ColorName */

enum ColorName
 {
  Black     = 0x000000 ,
  Red       = 0xFF0000 ,
  Green     = 0x00FF00 ,
  Blue      = 0x0000FF ,
  Gray      = 0x808080 ,
  LightGray = 0xC0C0C0 ,
  White     = 0xFFFFFF
 };

inline uint8 RedOf(ColorName cname) { return uint8(cname>>16); }

inline uint8 GreenOf(ColorName cname) { return uint8(cname>>8); }

inline uint8 BlueOf(ColorName cname) { return uint8(cname); }

/* class Color565 */

class Color565
 {
  public:
  
   using Raw = uint16 ;
  
   static const ulen RawCount = 1 ;
  
  private:
  
   Raw color[RawCount];
  
  private:
  
   static uint16 Pack565(uint16 red,uint16 green,uint16 blue) { return (red<<11)|(green<<5)|blue; }
  
  public:
  
   Color565(ColorName cname=Black) { set(cname); }
   
   // methods
   
   void set(ColorName cname) { set(RedOf(cname),GreenOf(cname),BlueOf(cname)); }
   
   void set(uint8 red,uint8 green,uint8 blue) { color[0]=Pack565(red>>3,green>>2,blue>>3); }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; }
 };

/* class FrameBuf<Color> */

template <class Color> 
class FrameBuf
 {
   using Raw = typename Color::Raw ;
  
   Raw *base = 0 ;
   
   unsigned dx = 0 ;
   ulen dline = 0 ;
   unsigned dy = 0 ;
   
  private: 
   
   Raw * place(unsigned x,unsigned y) { return base+(x*Color::RawCount+y*dline); }
   
   static void HLine(Raw *ptr,unsigned dx,Color color);
   
   template <class Glyph>
   static void HLine(Raw *ptr,unsigned dx,Glyph glyph,unsigned by,Color back,Color fore);
   
  public: 
  
   FrameBuf() {}
  
   FrameBuf(Raw *base_,unsigned dx_,unsigned dy_) : base(base_),dx(dx_),dline(dx_*Color::RawCount),dy(dy_) {}
  
   FrameBuf(Raw *base_,unsigned dx_,ulen dline_,unsigned dy_) : base(base_),dx(dx_),dline(dline_),dy(dy_) {}
   
   // properties
   
   bool operator + () const { return dy; }
   
   bool operator ! () const { return !dy; }
   
   unsigned dX() const { return dx; }
   
   unsigned dY() const { return dy; }
   
   // methods
  
   void erase(Color color);
  
   void block(unsigned x,unsigned y,unsigned bdx,unsigned bdy,Color color);
  
   template <class Glyph>
   void glyph(unsigned x,unsigned y,Glyph glyph,Color back,Color fore);
 };

template <class Color> 
void FrameBuf<Color>::HLine(Raw *ptr,unsigned dx,Color color)
 {
  for(; dx ;dx--,ptr+=Color::RawCount) color.copyTo(ptr);
 }

template <class Color> 
template <class Glyph>
void FrameBuf<Color>::HLine(Raw *ptr,unsigned dx,Glyph glyph,unsigned by,Color back,Color fore)
 {
  for(unsigned bx=0; bx<dx ;bx++,ptr+=Color::RawCount) 
    if( glyph(bx,by) ) 
      fore.copyTo(ptr); 
    else 
      back.copyTo(ptr);
 }

template <class Color> 
void FrameBuf<Color>::erase(Color color)
 {
  block(0,0,dx,dy,color);
 }

template <class Color> 
void FrameBuf<Color>::block(unsigned x,unsigned y,unsigned bdx,unsigned bdy,Color color)
 {
  Raw *ptr=place(x,y);
  
  for(; bdy ;bdy--,ptr+=dline)
    {
     HLine(ptr,bdx,color);
    }
 }

template <class Color> 
template <class Glyph>
void FrameBuf<Color>::glyph(unsigned x,unsigned y,Glyph glyph,Color back,Color fore)
 {
  unsigned bdx=glyph.dX();
  unsigned bdy=glyph.dY();
  
  Raw *ptr=place(x,y);
  
  for(unsigned by=0; by<bdy ;by++,ptr+=dline)
    {
     HLine(ptr,bdx,glyph,by,back,fore);
    }
 }

} // namespace Video
} // namespace CCore
 
#endif
 

