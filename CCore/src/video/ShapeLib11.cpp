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

  // body
  
  if( check )
    {
     art.ball(center,radius,TwoField(a,+cfg.top,a.addX(len),+cfg.bottom));
    
     art.ball(center,radius/2,enable?+cfg.on:+cfg.bottom);
    }
  else
    {
     art.ball(center,radius,TwoField(a,+cfg.top,a.addY(len),+cfg.bottom));
     
     art.ball(center,radius/2,enable?+cfg.off:+cfg.bottom);
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
        cname=+cfg.bottom;
     }
   
   art.circle(center,radius-width/2,width,cname);
  }
  
  // face
  
  {
   ColorName cname;
   
   if( enable )
     {
      if( mover )
        cname=+cfg.faceUp;
      else
        cname=+cfg.face;
     } 
   else
     {
      cname=+cfg.bottom;
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
   
   fig.solid(art,cname);
  }
 }

} // namespace Video
} // namespace CCore
 

