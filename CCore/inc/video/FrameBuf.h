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

#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Point.h>
 
namespace CCore {
namespace Video {

/* classes */

template <class RawColor> class FrameBuf;

/* class FrameBuf<RawColor> */

template <class RawColor>
class FrameBuf : protected ColorPlane
 {
  protected:
  
   using Raw = typename RawColor::Raw ;
   
  protected: 
   
   Raw * place(int y) { return static_cast<Raw *>(PtrAdd(raw,(ulen)y*(ulen)dline)); }
   
   Raw * place(Point p) { return place(p.y)+p.x*RawColor::RawCount; }
   
   static Raw * NextX(Raw *ptr) { return ptr+RawColor::RawCount; }
   
   static Raw * PrevX(Raw *ptr) { return ptr-RawColor::RawCount; }
   
   Raw * nextY(Raw *ptr) { return static_cast<Raw *>(PtrAdd(ptr,dline)); }
   
   Raw * prevY(Raw *ptr) { return static_cast<Raw *>(PtrSub(ptr,dline)); }
   
   Raw * nextXnextY(Raw *ptr) { return NextX(nextY(ptr)); }
   
   Raw * nextXprevY(Raw *ptr) { return NextX(prevY(ptr)); }
   
   Raw * prevXnextY(Raw *ptr) { return PrevX(nextY(ptr)); }
   
   Raw * prevXprevY(Raw *ptr) { return PrevX(prevY(ptr)); }
   
   static void HLine(Raw *ptr,int len,RawColor color);
   
   static void Save(Raw *ptr,int len,RawColor buf[/* len */]);
   
   static void Load(Raw *ptr,int len,const RawColor buf[/* len */]);
   
   template <class Pattern>
   static void HLine(Raw *ptr,Pattern pat,RawColor back,RawColor fore);
   
   template <class Pattern>
   static void HLine(Raw *ptr,Pattern pat,RawColor fore);
   
  public: 
  
   FrameBuf() {}
   
   FrameBuf(ColorPlane plane) : ColorPlane(plane) {}

   FrameBuf(FrameBuf<RawColor> buf,Pane pane)
    {
     if( !pane )
       {
        raw=0;
        dx=0;
        dy=0;
        dline=0;
       }
     else
       { 
        raw=buf.place(pane.getBase());
        dx=pane.dx;
        dy=pane.dy;
        dline=buf.dline;
       }
    }
   
   // properties
   
   bool operator + () const { return dx>0 && dy>0 ; }

   bool operator ! () const { return dx<=0 || dy<=0 ; }
   
   int dX() const { return dx; }
   
   int dY() const { return dy; }
   
   Pane getPane() const { return Pane(0,0,dx,dy); }
   
   Point getSize() const { return Point(dx,dy); }
   
   // methods
  
   FrameBuf<RawColor> cut(Pane pane) const { return FrameBuf<RawColor>(*this,pane); }
   
   RawColor pixel(Point p);
   
   void pixel(Point p,RawColor color);
   
   void erase(RawColor color);
  
   void block(Pane pane,RawColor color);
   
   void save(Pane pane,RawColor buf[/* pane.dx*pane.dy */]);
  
   void load(Pane pane,const RawColor buf[/* pane.dx*pane.dy */]);
   
   template <class Glyph>
   void glyph(Point p,Glyph glyph,RawColor back,RawColor fore);
   
   template <class Glyph>
   void glyph(Point p,Glyph glyph,RawColor fore);
   
   void test();
 };

template <class RawColor> 
void FrameBuf<RawColor>::HLine(Raw *ptr,int len,RawColor color)
 {
  for(; len>0 ;len--,ptr=NextX(ptr)) color.copyTo(ptr);
 }

template <class RawColor> 
void FrameBuf<RawColor>::Save(Raw *ptr,int len,RawColor buf[])
 {
  for(; len>0 ;len--,ptr=NextX(ptr),buf++) buf->copyFrom(ptr);
 }

template <class RawColor> 
void FrameBuf<RawColor>::Load(Raw *ptr,int len,const RawColor buf[])
 {
  for(; len>0 ;len--,ptr=NextX(ptr),buf++) buf->copyTo(ptr);
 }

template <class RawColor> 
template <class Pattern>
void FrameBuf<RawColor>::HLine(Raw *ptr,Pattern pat,RawColor back,RawColor fore)
 {
  int bdx=pat.dX();
  
  for(int bx=0; bx<bdx ;bx++,ptr=NextX(ptr)) 
    if( pat[bx] ) 
      fore.copyTo(ptr); 
    else 
      back.copyTo(ptr);
 }

template <class RawColor> 
template <class Pattern>
void FrameBuf<RawColor>::HLine(Raw *ptr,Pattern pat,RawColor fore)
 {
  int bdx=pat.dX();
  
  for(int bx=0; bx<bdx ;bx++,ptr=NextX(ptr)) 
    if( pat[bx] ) 
      fore.copyTo(ptr); 
 }

template <class RawColor> 
RawColor FrameBuf<RawColor>::pixel(Point p)
 {
  RawColor ret;
  
  ret.copyFrom(place(p));
  
  return ret;
 }

template <class RawColor> 
void FrameBuf<RawColor>::pixel(Point p,RawColor color)
 {
  color.copyTo(place(p));
 }

template <class RawColor> 
void FrameBuf<RawColor>::erase(RawColor color)
 {
  block(getPane(),color);
 }

template <class RawColor> 
void FrameBuf<RawColor>::block(Pane pane,RawColor color)
 {
  if( !pane ) return;
  
  Raw *ptr=place(pane.getBase());
  
  for(; pane.dy>0 ;pane.dy--,ptr=nextY(ptr))
    {
     HLine(ptr,pane.dx,color);
    }
 }

template <class RawColor> 
void FrameBuf<RawColor>::save(Pane pane,RawColor buf[])
 {
  if( !pane ) return;
  
  Raw *ptr=place(pane.getBase());
  
  for(; pane.dy>0 ;pane.dy--,ptr=nextY(ptr),buf+=pane.dx)
    {
     Save(ptr,pane.dx,buf);
    }
 }

template <class RawColor> 
void FrameBuf<RawColor>::load(Pane pane,const RawColor buf[])
 {
  if( !pane ) return;
   
  Raw *ptr=place(pane.getBase());
   
  for(; pane.dy>0 ;pane.dy--,ptr=nextY(ptr),buf+=pane.dx)
    {
     Load(ptr,pane.dx,buf);
    }
 }

template <class RawColor> 
template <class Glyph>
void FrameBuf<RawColor>::glyph(Point p,Glyph glyph,RawColor back,RawColor fore)
 {
  int bdy=glyph.dY();
  
  Raw *ptr=place(p);
  
  for(int by=0; by<bdy ;by++,ptr=nextY(ptr))
    {
     HLine(ptr,glyph[by],back,fore);
    }
 }

template <class RawColor> 
template <class Glyph>
void FrameBuf<RawColor>::glyph(Point p,Glyph glyph,RawColor fore)
 {
  int bdy=glyph.dY();
  
  Raw *ptr=place(p);
  
  for(int by=0; by<bdy ;by++,ptr=nextY(ptr))
    {
     HLine(ptr,glyph[by],fore);
    }
 }

template <class RawColor> 
void FrameBuf<RawColor>::test()
 {
  if( dx<=0 || dy<=0 ) return;
  
  {
   int x1=(1*dx)/4;
   int x2=(2*dx)/4;
   int x3=(3*dx)/4;
   
   block(Pane(0,0,x1,dy),Black);
   block(Pane(x1,0,x2-x1,dy),Gray);
   block(Pane(x2,0,x3-x2,dy),Silver);
   block(Pane(x3,0,dx-x3,dy),White);
  }
  
  {
   block(Pane(0,0,1,dy),Red);
   block(Pane(dx-1,0,1,dy),Red);
   block(Pane(0,0,dx,1),Red);
   block(Pane(0,dy-1,dx,1),Red);
  }
  
  {
   int bdy=(Min(dx,dy)*10)/36;
   int bdx=bdy;
   
   int gap=bdy/10;
   
   int x1=(dx-3*bdx-2*gap)/2;
   int x2=x1+bdx+gap;
   int x3=x2+bdx+gap;
   
   int y1=(dy-3*bdy-2*gap)/2;
   int y2=y1+bdy+gap;
   int y3=y2+bdy+gap;
   
   block(Pane(x1,y1,bdx,bdy),Red);
   block(Pane(x2,y1,bdx,bdy),Green);
   block(Pane(x3,y1,bdx,bdy),Blue);
   
   block(Pane(x1,y2,bdx,bdy),Cyan);
   block(Pane(x2,y2,bdx,bdy),Fuchsia);
   block(Pane(x3,y2,bdx,bdy),Yellow);
   
   block(Pane(x1,y3,bdx,bdy),Teal);
   block(Pane(x2,y3,bdx,bdy),Purple);
   block(Pane(x3,y3,bdx,bdy),Olive);
  }
 }

} // namespace Video
} // namespace CCore
 
#endif
 

