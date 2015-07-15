/* ShapeLib7.cpp */ 
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

/* class XSingleLineShape */

Point XSingleLineShape::getMinSize() const
 {
  Coord dxy=RoundUpLen(+cfg.width);
  
  return Point::Diag(dxy);
 }

void XSingleLineShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  Smooth::DrawArt art(buf);
  
  MCoord width=+cfg.width;
  
  MCoord x0=p.x+width/2;
  MCoord x1=p.ex-width/2;
  
  MCoord y=p.y+p.dy/2;
  
  art.path(width,+cfg.line,MPoint(x0,y),MPoint(x1,y));
 }

/* class YSingleLineShape */

Point YSingleLineShape::getMinSize() const
 {
  Coord dxy=RoundUpLen(+cfg.width);
  
  return Point::Diag(dxy);
 }

void YSingleLineShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  Smooth::DrawArt art(buf);
  
  MCoord width=+cfg.width;
  
  MCoord x=p.x+p.dx/2;
  
  MCoord y0=p.y+width/2;
  MCoord y1=p.ey-width/2;
  
  art.path(width,+cfg.line,MPoint(x,y0),MPoint(x,y1));
 }

} // namespace Video
} // namespace CCore
 

