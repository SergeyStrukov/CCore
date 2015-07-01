/* ShapeLib6.cpp */ 
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

/* class TextShape */

Point TextShape::getMinSize() const
 {
  TextSize ts=cfg.font->text(Range(text));
  
  IntGuard( !ts.overflow );
  
  MCoord width=cfg.width;
  
  MCoord ex=(Fraction(ts.dy)+2*width)/4;
  
  Coord dx=RoundUpLen(ex);
  Coord dy=RoundUpLen(width);
  
  return 2*Point(dx,dy)+Point(ts.full_dx,ts.dy);
 }

void TextShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  Smooth::DrawArt art(buf);
  
  // border
  
  MCoord x0=p.x;
  MCoord x1=x0+p.dx;
  
  MCoord y0=p.y;
  MCoord y1=y0+p.dy;
  
  MCoord width=cfg.width;
  
  FontSize fs=cfg.font->getSize();
  
  MCoord ex=(Fraction(fs.dy)+2*width)/4;
  
  FigureButton fig(x0,x1,y0,y1,ex);
  
  // body
  
  fig.curveSolid(art,cfg.back);
  
  // border
  
  auto fig_top=fig.getTop();
  
  fig_top.curvePath(art,HalfPos,width,cfg.top);
  
  auto fig_bottom=fig.getBottom();
  
  fig_bottom.curvePath(art,HalfPos,width,cfg.bottom);
  
  // text
  
  Coord dx=RoundUpLen(ex);
  Coord dy=RoundUpLen(width);
  
  cfg.font->text(buf,Shrink(pane,dx,dy),TextPlace(align_x,align_y),Range(text),enable?cfg.text:cfg.inactive);
 }

} // namespace Video
} // namespace CCore
 

