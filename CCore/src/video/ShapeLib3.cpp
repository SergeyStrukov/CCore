/* ShapeLib3.cpp */ 
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

/* class CheckShape */

Point CheckShape::getMinSize() const
 {
  return Point::Diag(10);
 }

void CheckShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  p.square();
  
  Smooth::DrawArt art(buf);
  
  // border
  
  MCoord x0=p.x;
  MCoord x1=p.ex;
  
  MCoord y0=p.y;
  MCoord y1=p.ey;
  
  MCoord len=p.dx;
  MCoord width=len/10;
  
  FigureBox fig(p);
  
  VColor top=+cfg.top;
  
  // body

  {
   VColor bottom; 
    
   if( mover && enable )
     bottom=+cfg.bottomUp;
   else
     bottom=+cfg.bottom;
    
   fig.solid(art,TwoField({x0+width,y0+width},top,{x1-width,y1-width},bottom));
  }
  
  // mark
  
  if( check )
    {
     MCoord d=(3*width)/2;
    
     MPoint a(x0+d,y0+len/2);
     MPoint b(x0+(len+d)/3,y1-d);
     MPoint c(x1-d,y0+d);
     
     VColor mark;
    
     if( enable )
       mark=+cfg.mark;
     else
       mark=top;
     
     art.path(width,mark,a,b,c);
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
   
   fig.loop(art,HalfPos,width,border);
  }
 }

} // namespace Video
} // namespace CCore
 

