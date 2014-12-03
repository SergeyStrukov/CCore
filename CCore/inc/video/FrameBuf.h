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

class Color16;

class Color24;

class Color32;

template <class Color> class FrameBuf;

/* enum ColorName */

enum ColorName : uint32
 {
  Black     = 0x000000,
  Gray      = 0x808080,
  Silver    = 0xC0C0C0,
  White     = 0xFFFFFF,
  
  Red       = 0xFF0000,
  Green     = 0x00FF00,
  Blue      = 0x0000FF,

  Cyan      = 0x00FFFF,
  Fuchsia   = 0xFF00FF,
  Yellow    = 0xFFFF00,
  
  Teal      = 0x008080,
  Purple    = 0x800080, 
  Olive     = 0x808000
 };

inline uint8 RedOf(ColorName cname) { return uint8(cname>>16); }

inline uint8 GreenOf(ColorName cname) { return uint8(cname>>8); }

inline uint8 BlueOf(ColorName cname) { return uint8(cname); }

/* class Color16 */

class Color16
 {
  public:
  
   using Raw = uint16 ;
  
   static const ulen RawCount = 1 ;
  
  private:
  
   Raw color[RawCount];
  
  private:
  
   static uint16 Pack565(uint16 red,uint16 green,uint16 blue) { return (red<<11)|(green<<5)|blue; }
  
  public:
  
   Color16(ColorName cname=Black) { set(cname); }
   
   // methods
   
   void set(ColorName cname) { set(RedOf(cname),GreenOf(cname),BlueOf(cname)); }
   
   void set(uint8 red,uint8 green,uint8 blue) { color[0]=Pack565(red>>3,green>>2,blue>>3); }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; }
   
   void copyFrom(const Raw dst[RawCount]) { color[0]=dst[0]; }
 };

/* class Color24 */

class Color24
 {
  public:
  
   using Raw = uint8 ;
  
   static const ulen RawCount = 3 ;
  
  private:
  
   Raw color[RawCount];
  
  public:
  
   Color24(ColorName cname=Black) { set(cname); }
   
   // methods
   
   void set(ColorName cname) { set(RedOf(cname),GreenOf(cname),BlueOf(cname)); }
   
   void set(uint8 red,uint8 green,uint8 blue) { color[0]=red; color[1]=green; color[2]=blue; }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; dst[1]=color[1]; dst[2]=color[2]; }
   
   void copyFrom(const Raw dst[RawCount]) { color[0]=dst[0]; color[1]=dst[1]; color[2]=dst[2]; }
 };

/* class Color32 */

class Color32
 {
  public:
  
   using Raw = uint32 ;
  
   static const ulen RawCount = 1 ;
  
  private:
  
   Raw color[RawCount];
   
   static uint32 Pack888(uint32 red,uint32 green,uint32 blue) { return red|(green<<8)|(blue<<16); }
  
  public:
  
   Color32(ColorName cname=Black) { set(cname); }
   
   // methods
   
   void set(ColorName cname) { set(RedOf(cname),GreenOf(cname),BlueOf(cname)); }
   
   void set(uint8 red,uint8 green,uint8 blue) { color[0]=Pack888(red,green,blue); }
  
   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; }
   
   void copyFrom(const Raw dst[RawCount]) { color[0]=dst[0]; }
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
   
   static Raw * NextX(Raw *ptr) { return ptr+Color::RawCount; }
   
   Raw * nextY(Raw *ptr) { return ptr+dline; }
   
   static void HLine(Raw *ptr,unsigned bdx,Color color);
   
   template <class Pattern>
   static void HLine(Raw *ptr,Pattern pat,Color back,Color fore);
   
   template <class Pattern>
   static void HLine(Raw *ptr,Pattern pat,Color fore);
   
   static void Save(Raw *ptr,unsigned bdx,Color buf[/* bdx */]);
   
   static void Load(Raw *ptr,unsigned bdx,const Color buf[/* bdx */]);
   
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
   
   void save(unsigned x,unsigned y,unsigned bdx,unsigned bdy,Color buf[/* bdx*bdy */]);
  
   void load(unsigned x,unsigned y,unsigned bdx,unsigned bdy,const Color buf[/* bdx*bdy */]);
   
   template <class Glyph>
   void glyph(unsigned x,unsigned y,Glyph glyph,Color back,Color fore);
   
   template <class Glyph>
   void glyph(unsigned x,unsigned y,Glyph glyph,Color fore);
   
   void test();
 };

template <class Color> 
void FrameBuf<Color>::HLine(Raw *ptr,unsigned bdx,Color color)
 {
  for(; bdx ;bdx--,ptr=NextX(ptr)) color.copyTo(ptr);
 }

template <class Color> 
template <class Pattern>
void FrameBuf<Color>::HLine(Raw *ptr,Pattern pat,Color back,Color fore)
 {
  unsigned bdx=pat.dX();
  
  for(unsigned bx=0; bx<bdx ;bx++,ptr=NextX(ptr)) 
    if( pat[bx] ) 
      fore.copyTo(ptr); 
    else 
      back.copyTo(ptr);
 }

template <class Color> 
template <class Pattern>
void FrameBuf<Color>::HLine(Raw *ptr,Pattern pat,Color fore)
 {
  unsigned bdx=pat.dX();
  
  for(unsigned bx=0; bx<bdx ;bx++,ptr=NextX(ptr)) 
    if( pat[bx] ) 
      fore.copyTo(ptr); 
 }

template <class Color> 
void FrameBuf<Color>::Save(Raw *ptr,unsigned bdx,Color buf[/* bdx */])
 {
  for(; bdx ;bdx--,ptr=NextX(ptr),buf++) buf->copyFrom(ptr);
 }

template <class Color> 
void FrameBuf<Color>::Load(Raw *ptr,unsigned bdx,const Color buf[/* bdx */])
 {
  for(; bdx ;bdx--,ptr=NextX(ptr),buf++) buf->copyTo(ptr);
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
  
  for(; bdy ;bdy--,ptr=nextY(ptr))
    {
     HLine(ptr,bdx,color);
    }
 }

template <class Color> 
void FrameBuf<Color>::save(unsigned x,unsigned y,unsigned bdx,unsigned bdy,Color buf[/* bdx*bdy */])
 {
  Raw *ptr=place(x,y);
  
  for(; bdy ;bdy--,ptr=nextY(ptr),buf+=bdx)
    {
     Save(ptr,bdx,buf);
    }
 }

template <class Color> 
void FrameBuf<Color>::load(unsigned x,unsigned y,unsigned bdx,unsigned bdy,const Color buf[/* bdx*bdy */])
 {
  Raw *ptr=place(x,y);
  
  for(; bdy ;bdy--,ptr=nextY(ptr),buf+=bdx)
    {
     Load(ptr,bdx,buf);
    }
 }

template <class Color> 
template <class Glyph>
void FrameBuf<Color>::glyph(unsigned x,unsigned y,Glyph glyph,Color back,Color fore)
 {
  unsigned bdy=glyph.dY();
  
  Raw *ptr=place(x,y);
  
  for(unsigned by=0; by<bdy ;by++,ptr=nextY(ptr))
    {
     HLine(ptr,glyph[by],back,fore);
    }
 }

template <class Color> 
template <class Glyph>
void FrameBuf<Color>::glyph(unsigned x,unsigned y,Glyph glyph,Color fore)
 {
  unsigned bdy=glyph.dY();
  
  Raw *ptr=place(x,y);
  
  for(unsigned by=0; by<bdy ;by++,ptr=nextY(ptr))
    {
     HLine(ptr,glyph[by],fore);
    }
 }

template <class Color> 
void FrameBuf<Color>::test()
 {
  {
   unsigned x1=(1*dx)/4;
   unsigned x2=(2*dx)/4;
   unsigned x3=(3*dx)/4;
   
   block(0,0,x1,dy,Black);
   block(x1,0,x2-x1,dy,Gray);
   block(x2,0,x3-x2,dy,Silver);
   block(x3,0,dx-x3,dy,White);
  }
  
  {
   block(0,0,1,dy,Red);
   block(dx-1,0,1,dy,Red);
   block(0,0,dx,1,Red);
   block(0,dy-1,dx,1,Red);
  }
  
  {
   unsigned bdy=(dy*10)/36;
   unsigned bdx=bdy;
   
   unsigned gap=bdy/10;
   
   unsigned x1=(dx-3*bdx-2*gap)/2;
   unsigned x2=x1+bdx+gap;
   unsigned x3=x2+bdx+gap;
   
   unsigned y1=(dy-3*bdy-2*gap)/2;
   unsigned y2=y1+bdy+gap;
   unsigned y3=y2+bdy+gap;
   
   block(x1,y1,bdx,bdy,Red);
   block(x2,y1,bdx,bdy,Green);
   block(x3,y1,bdx,bdy,Blue);
   
   block(x1,y2,bdx,bdy,Cyan);
   block(x2,y2,bdx,bdy,Fuchsia);
   block(x3,y2,bdx,bdy,Yellow);
   
   block(x1,y3,bdx,bdy,Teal);
   block(x2,y3,bdx,bdy,Purple);
   block(x3,y3,bdx,bdy,Olive);
  }
 }

} // namespace Video
} // namespace CCore
 
#endif
 

