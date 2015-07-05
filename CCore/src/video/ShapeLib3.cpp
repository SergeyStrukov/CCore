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
  MCoord x1=x0+p.dx;
  
  MCoord y0=p.y;
  MCoord y1=y0+p.dy;
  
  MCoord len=p.dx;
  MCoord width=len/10;
  
  FigureBox fig(x0,x1,y0,y1);
  
  // body

  {
   ColorName cname; 
    
   if( mover && enable )
     cname=+cfg.bottomUp;
   else
     cname=+cfg.bottom;
    
   fig.solid(art,TwoField({x0+width,y0+width},+cfg.top,{x1-width,y1-width},cname));
  }
  
  // mark
  
  if( check )
    {
     MCoord d=(3*width)/2;
    
     MPoint a(x0+d,y0+len/2);
     MPoint b(x0+(len+d)/3,y1-d);
     MPoint c(x1-d,y0+d);
     
     ColorName cname;
    
     if( enable )
       cname=+cfg.mark;
     else
       cname=+cfg.top;
     
     art.pathOf(width,cname,a,b,c);
    }
  
  // border
  
  {
   ColorName cname;
   
   if( focus )
     {
      cname=+cfg.focus;
     }
   else
     {
      if( enable )
        cname=+cfg.border;
      else
        cname=+cfg.top;
     }
   
   fig.loop(art,HalfPos,width,cname);
  }
 }

} // namespace Video
} // namespace CCore
 

