/* ShapeLib10.cpp */ 
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
 
#include <CCore/inc/video/ShapeLib.h>

#include <CCore/inc/video/SmoothDrawArt.h>
#include <CCore/inc/video/FigureLib.h>
 
namespace CCore {
namespace Video {

/* class TextContourShape */

Point TextContourShape::getMinSize() const
 {
  TextSize ts=cfg.font->text(Range(title));
  
  IntGuard( !ts.overflow );
  
  Coord dy=RoundUpLen(cfg.width);
  
  return 2*Point(ts.dy,dy)+Point(ts.full_dx,ts.dy);
 }

Pane TextContourShape::getInner() const
 {
  TextSize ts=cfg.font->text(Range(title));
  
  Coord dxy=RoundUpLen(cfg.width);
  
  if( 2*dxy>=pane.dx || ts.dy+dxy>=pane.dy ) return Empty;
  
  return Pane(pane.x+dxy,pane.y+ts.dy,pane.dx-2*dxy,pane.dy-ts.dy-dxy);
 }

void TextContourShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  Smooth::DrawArt art(buf);
  
  TextSize ts=cfg.font->text(Range(title));
  
  Coord ty=Min(ts.dy,pane.dy);
  Coord tx=Min<Coord>(ty,pane.dx/2);
  
  Coord len=pane.dx-2*tx;
  Coord free;
  
  if( ts.overflow )
    free=0;
  else
    free=(len>ts.full_dx)?len-ts.full_dx:0;
  
  MCoord width=cfg.width;
  
  MCoord x0=p.x;
  MCoord x1=x0+p.dx;
  
  MCoord y0=p.y+Fraction(ty)/2;
  MCoord y1=p.y+p.dy;
  
  MCoord t0;
  MCoord t1;
  
  switch( align_x )
    {
     case AlignX_Left :
      {
       MCoord d=Fraction(tx)/2;
       
       t0=d;
       t1=p.dx-d-Fraction(free);
      }
     break;
     
     case AlignX_Right :
      {
       MCoord d=Fraction(tx)/2;
       
       t0=d+Fraction(free);
       t1=p.dx-d;
      }
     break;
     
     default:
      {
       MCoord d=Fraction(tx)/2+Fraction(free)/2;
       
       t0=d;
       t1=p.dx-d;
      }
    }
  
  t0+=p.x;
  t1+=p.x;
  
  // border
  
  FigureTopBorder fig_top(x0,x1,y0,y1,width);
  
  fig_top.getLeftCut(t0).solid(art,cfg.top);
  
  fig_top.getRightCut(t1).solid(art,cfg.top);
  
  FigureBottomBorder fig_bottom(x0,x1,y0,y1,width);
  
  fig_bottom.solid(art,cfg.bottom);
  
  // title
  
  cfg.font->text(buf,Extent(pane.x+tx,pane.y,len,ty),TextPlace(align_x,AlignY_Center),Range(title),cfg.text);
 }

} // namespace Video
} // namespace CCore
 

