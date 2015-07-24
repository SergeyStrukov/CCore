/* ShapeLib17.cpp */ 
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
 
#include <CCore/inc/video/ShapeLib2.h>
 
#include <CCore/inc/video/SmoothDrawArt.h>
#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class LineEditShape */

Point LineEditShape::getMinSize() const
 {
  Font font=cfg.font.get();
  
  MCoord width=+cfg.width;
  
  FontSize fs=font->getSize();
  
  MCoord ex=(Fraction(fs.dy)+2*width)/4+Fraction(+cfg.ex);
  
  Coord dx=RoundUpLen(ex);
  Coord dy=RoundUpLen(width)+(+cfg.cursor_dx);
  
  TextSize ts=font->text("Sample");
  
  IntGuard( !ts.overflow );
  
  return Point(ts.full_dx,ts.dy)+2*Point(dx,dy);
 }

void LineEditShape::setMax()
 {
  Font font=cfg.font.get();
  
  MCoord width=+cfg.width;
  
  FontSize fs=font->getSize();
  
  MCoord ex=(Fraction(fs.dy)+2*width)/4+Fraction(+cfg.ex);
  
  Coord dx=RoundUpLen(ex);
  Coord dy=RoundUpLen(width);
  
  Pane inner=pane.shrink(dx,dy);
  
  TextSize ts=font->text(text_buf.prefix(len));
  
  IntGuard( !ts.overflow );
  
  Coord tx=IntAdd(ts.full_dx,2*(+cfg.cursor_dx));
  
  tx=IntAdd(tx,fs.max_dx); 
  
  tx=IntAdd(tx,IntAbs(ts.skew));
  
  if( tx>inner.dx )
    xoffMax=tx-inner.dx;
  else
    xoffMax=0;
  
  dxoff=fs.medDx();  
 }

void LineEditShape::showCursor()
 {
  MCoord width=+cfg.width;
  
  Font font=cfg.font.get();
  
  FontSize fs=font->getSize();
  
  MCoord ex=(Fraction(fs.dy)+2*width)/4+Fraction(+cfg.ex);
  
  Coord dx=RoundUpLen(ex);
  Coord inner_dx=pane.dx-2*dx;
  
  if( inner_dx<=0 ) return;
  
  TextSize ts=font->text(text_buf.prefix(pos));
  
  Coord cursor_dx=+cfg.cursor_dx;
  Coord x=IntAbs(ts.skew)+cursor_dx+ts.dx-xoff;
  
  inner_dx-=2*cursor_dx;
  
  if( x<cursor_dx )
    {
     x=cursor_dx-x;
     
     if( xoff>x )
       xoff-=x;
     else
       xoff=0;
    }
  else if( x>=inner_dx )
    {
     x=x-inner_dx;
     
     if( xoff<xoffMax-x )
       xoff+=x;
     else
       xoff=xoffMax;
    }
 }

void LineEditShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  Smooth::DrawArt art(buf);
  
  Font font=cfg.font.get();
  
  // figure
  
  MCoord width=+cfg.width;
  
  FontSize fs=font->getSize();
  
  MCoord ex=(Fraction(fs.dy)+2*width)/4+Fraction(+cfg.ex);
  
  VColor text=enable?+cfg.text:+cfg.inactive;
  
  FigureButton fig(p,ex);
  
  // body
  
  fig.curveSolid(art,+cfg.back);
  
  // border
  
  if( focus )
    {
     fig.curveLoop(art,HalfPos,width,+cfg.focus);
    }
  else
    {
     auto fig_top=fig.getTop();
     
     fig_top.curvePath(art,HalfPos,width,+cfg.top);
     
     auto fig_bottom=fig.getBottom();
     
     fig_bottom.curvePath(art,HalfPos,width,+cfg.bottom);
    }
  
  // arrows
  
  {
   MCoord len=ex-width;

   if( xoff>0 ) // Left
     {
      MCoord x=p.x;
      MCoord y=p.y+p.dy/2;
     
      FigurePoints<3> fig;
      
      fig[0]={x,y};
      fig[1]={x+len,y-len};
      fig[2]={x+len,y+len};
      
      fig.solid(art,text);
     }
   
   if( xoff<xoffMax ) // Right
     {
      MCoord x=p.ex;
      MCoord y=p.y+p.dy/2;
      
      FigurePoints<3> fig;
      
      fig[0]={x,y};
      fig[1]={x-len,y-len};
      fig[2]={x-len,y+len};
      
      fig.solid(art,text);
     }
  }
  
  // text
  
  {
   Coord dx=RoundUpLen(ex);
   Coord dy=RoundUpLen(width);
   
   Pane inner=pane.shrink(dx,dy);
   
   if( !inner ) return;
   
   DrawBuf tbuf=buf.cutRebase(inner);
   
   Pane tpane(-xoff,0,IntAdd(xoff,inner.dx),inner.dy);
   
   TextSize ts=font->text(text_buf.prefix(pos));
   
   Coord cursor_dx=+cfg.cursor_dx;
   
   Coord x1=IntAbs(ts.skew)+cursor_dx;
   Coord x2=x1+ts.dx;
   Coord x3=x2+cursor_dx;
   
   font->text(tbuf,tpane,TextPlace(x1,AlignY_Center),text_buf.prefix(pos),text);
   
   font->text(tbuf,tpane,TextPlace(x3,AlignY_Center),text_buf.part(pos,len-pos),text);
   
   if( enable )
     {
      MCoord w=Fraction(cursor_dx);
      MCoord h=Fraction(ts.dy);
      MCoord skew=Fraction(ts.skew);
      
      MCoord y0=(Fraction(inner.dy)-h)/2;
      MCoord y1=y0+h;
      
      MCoord b0=Fraction(x2-xoff)-Rational(h-Fraction(ts.by),h)*skew;
      MCoord b1=b0+w;
      
      MCoord a0=b0+skew;
      MCoord a1=a0+w;
     
      Smooth::DrawArt art(tbuf);
      
      FigurePoints<12> fig;
      
      fig[0]={a1,y0};
      fig[1]={a1+w,y0};
      fig[2]={a1+w,y0-w};
      fig[3]={a0-w,y0-w};
      fig[4]={a0-w,y0};
      fig[5]={a0,y0};
      
      fig[6]={b0,y1};
      fig[7]={b0-w,y1};
      fig[8]={b0-w,y1+w};
      fig[9]={b1+w,y1+w};
      fig[10]={b1+w,y1};
      fig[11]={b1,y1};
     
      if( focus && cursor )
        {
         fig.solid(art,+cfg.cursor);
        }
      else
        {
         fig.loop(art,HalfPos,w/3,+cfg.cursor);
        }
     }
  }
 }

} // namespace Video
} // namespace CCore
 

