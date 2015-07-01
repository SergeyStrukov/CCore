/* ShapeLib9.cpp */ 
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

/* class ContourShape */

Point ContourShape::getMinSize() const
 {
  Coord dxy=RoundUpLen(cfg.width);
  
  return Point::Diag(2*dxy);
 }

Pane ContourShape::getInner() const
 {
  Coord dxy=RoundUpLen(cfg.width);
  
  return Shrink(pane,dxy);
 }

void ContourShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  Smooth::DrawArt art(buf);
  
  MCoord width=cfg.width;
  
  MCoord x0=p.x;
  MCoord x1=x0+p.dx;
  
  MCoord y0=p.y;
  MCoord y1=y0+p.dy;
  
  FigureTopBorder fig_top(x0,x1,y0,y1,width);
  
  fig_top.solid(art,cfg.top);
  
  FigureBottomBorder fig_bottom(x0,x1,y0,y1,width);
  
  fig_bottom.solid(art,cfg.bottom);
 }

} // namespace Video
} // namespace CCore
 

