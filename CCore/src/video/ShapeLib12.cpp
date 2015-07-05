/* ShapeLib12.cpp */ 
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

/* class LightShape */

Point LightShape::getMinSize() const
 {
  return Point::Diag(10);
 }

void LightShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  p.square();
  
  Smooth::DrawArt art(buf);
  
  MPoint a=p.getBase();
  
  MCoord len=p.dx;
  MCoord radius=len/2;
  MCoord d=Ratio(424,10)*radius;
  MCoord radius2=(4*radius)/5;
  MPoint center=a.addXY(radius);

  art.ball(center,radius,TwoField(a.addXY(d),+cfg.top,a.addXY(len-d),+cfg.bottom));
  
  if( on )
    {
     art.ball(center,radius2,RadioField(center.subXY(radius/3),radius,White,face));
    }
  else
    {
     art.ball(center,radius2,+cfg.inactive);
    }
 }

} // namespace Video
} // namespace CCore
 

