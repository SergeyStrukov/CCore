/* ShapeLib4.cpp */ 
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

/* class RadioShape */

Point RadioShape::getMinSize() const
 {
  return Point::Diag(10);
 }

void RadioShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  p.square();
  
  Smooth::DrawArt art(buf);
  
  MPoint a=p.getBase();
  
  MCoord len=p.dx;
  MCoord width=len/10;
  MCoord radius=len/2;
  MPoint center=a.addXY(radius);
  MCoord d=Ratio(424,10)*radius;
  
  VColor top=+cfg.top;
  
  // body
  
  {
   VColor bottom;
   
   if( mover && enable )
     bottom=+cfg.bottomUp;
   else
     bottom=+cfg.bottom;
   
   art.ball(center,radius,TwoField(a.addXY(d),top,a.addXY(len-d),bottom));
  }
  
  // mark
  
  if( check )
    {
     VColor mark;
     
     if( enable )
       mark=+cfg.mark;
     else
       mark=top;
     
     art.ball(center,radius/3,mark);
    }
  
  // border
  
  {
   VColor border;
   
   if( focus )
     {
      border=+cfg.focus;
     }
   else
     {
      if( enable )
        border=+cfg.border;
      else
        border=top;
     }
   
   art.circle(center,radius-width/2,width,border);
  }
 }

} // namespace Video
} // namespace CCore
 

