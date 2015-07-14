/* ShapeLib11.cpp */ 
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

/* class SwitchShape */

Point SwitchShape::getMinSize() const
 {
  return Point::Diag(16);
 }

void SwitchShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  p.square();
  
  Smooth::DrawArt art(buf);
  
  MPoint a=p.getBase();
  
  MCoord len=p.dx;
  MCoord radius=len/2;
  MPoint center=a.addXY(radius);
  MCoord width=len/16;
  
  VColor top=+cfg.top;
  VColor bottom=+cfg.bottom;

  // body
  
  if( check )
    {
     art.ball(center,radius,TwoField(a,top,a.addX(len),bottom));
    
     art.ball(center,radius/2,enable?+cfg.on:bottom);
    }
  else
    {
     art.ball(center,radius,TwoField(a,top,a.addY(len),bottom));
     
     art.ball(center,radius/2,enable?+cfg.off:bottom);
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
        border=bottom;
     }
   
   art.circle(center,radius-width/2,width,border);
  }
  
  // face
  
  {
   VColor face;
   
   if( enable )
     {
      if( mover )
        face=+cfg.faceUp;
      else
        face=+cfg.face;
     } 
   else
     {
      face=bottom;
     } 
   
   MCoord d1=len/20;
   MCoord d2=len/8;
   
   FigurePoints<6> fig;
   
   if( check )
     {
      fig[0]={radius+d1,0};
      fig[1]={radius-d1,0};
      fig[2]={radius-d2,radius};
      fig[3]={radius-d1,len};
      fig[4]={radius+d1,len};
      fig[5]={radius+d2,radius};
     }
   else
     {
      fig[0]={0,radius+d1};
      fig[1]={0,radius-d1};
      fig[2]={radius,radius-d2};
      fig[3]={len,radius-d1};
      fig[4]={len,radius+d1};
      fig[5]={radius,radius+d2};
     }
   
   fig.transform(Smooth::DotShift(a));
   
   fig.solid(art,face);
  }
 }

} // namespace Video
} // namespace CCore
 

