/* ShapeLib2.cpp */ 
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

/* class KnobShape */

Point KnobShape::getMinSize() const
 {
  Coord dxy=RoundUpLen(4*cfg.width.get());
  
  return Point::Diag(dxy);
 }

void KnobShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  p.square();
  
  Smooth::DrawArt art(buf);
  
  // center and radius
  
  MPoint a=p.getBase();
  
  MCoord len=p.dx;
  MCoord radius=len/2;
  MPoint center=a.addXY(radius);
  
  // body
  
  if( down )
    {
     art.ball(center,radius,+cfg.bottom);
    }
  else
    {
     VColor cname;
    
     if( mover && enable )
       cname=+cfg.topUp;
     else
       cname=+cfg.top; 
     
     art.ball(center,radius,TwoField(a,cname,a.addY(len),+cfg.bottom));
    }
  
  // face
  
  VColor cname=enable?+cfg.face:+cfg.bottom;
  
  switch( face )
    {
     case FacePlus :
      {
       MCoord a=radius/2;
       MCoord w=(2*a)/3;
       
       art.pathOf(w,cname,center.subX(a),center.addX(a));
       art.pathOf(w,cname,center.subY(a),center.addY(a));
      }
     break;
     
     case FaceMinus :
      {
       MCoord a=radius/2;
       MCoord w=(2*a)/3;
       
       art.pathOf(w,cname,center.subX(a),center.addX(a));
      }
     break;
     
     case FaceCross :
      {
       MCoord a=radius/2;
       MCoord w=(2*a)/3;
       
       art.pathOf(w,cname,center.subXY(a),center.addXY(a));
       art.pathOf(w,cname,center.addXsubY(a),center.subXaddY(a));
      }
     break;
     
     case FaceAsterisk :
      {
       FigureAsterisk fig(center,Ratio(652,10)*radius);

       fig.curveSolid(art,cname);
      }
     break;
     
     case FaceExclamation :
      {
       MCoord a=(2*radius)/3;
       MCoord c=radius/5;
       MCoord b=a-2*c;
       MCoord r=(3*c)/4;
       
       FigureDots<4> fig;
       
       fig[0]={{-c,c-a}};
       fig[1]={{0,-a}};
       fig[2]={{c,c-a}};
       fig[3]={{0,b},Smooth::DotBreak};
       
       fig.transform(Smooth::DotShift(center));
       
       fig.curveSolid(art,cname);
       
       art.ball(center.addY(b+r),r,cname);
      }
     break;
     
     case FaceQuestion :
      {
       MCoord a=(2*radius)/3;
       MCoord c=radius/5;
       MCoord b=a-2*c;
       MCoord r=(3*c)/4;
       
       art.ball(center.addY(b+r),r,cname);
      }
     break;
     
     case FaceLeft :
      {
       MCoord a=radius/2;
       MCoord d=radius/12;
       
       FigureLeftArrow fig(-d-a,a-d,-a,a);
       
       fig.transform(Smooth::DotShift(center));
       
       fig.curveSolid(art,cname);
      }
     break;
     
     case FaceRight :
      {
       MCoord a=radius/2;
       MCoord d=radius/12;
       
       FigureRightArrow fig(d-a,a+d,-a,a);
       
       fig.transform(Smooth::DotShift(center));
       
       fig.curveSolid(art,cname);
      }
     break;
     
     case FaceUp :
      {
       MCoord a=radius/2;
       MCoord d=radius/12;
       
       FigureUpArrow fig(-a,a,-d-a,a-d);
       
       fig.transform(Smooth::DotShift(center));
       
       fig.curveSolid(art,cname);
      }
     break;
     
     case FaceDown :
      {
       MCoord a=radius/2;
       MCoord d=radius/12;
       
       FigureDownArrow fig(-a,a,d-a,a+d);
       
       fig.transform(Smooth::DotShift(center));
       
       fig.curveSolid(art,cname);
      }
     break;
     
     case FaceStop :
      {
       MCoord a=radius/2;
       
       FigureBox fig(-a,a,-a,a);
       
       fig.transform(Smooth::DotShift(center));
       
       fig.solid(art,cname);
      }
     break;
     
     case FaceRightRight :
      {
       MCoord a=radius/2;
       MCoord d2=radius/3;
       MCoord d1=d2/2;
       
       FigureRightArrow fig1(-a,a,-a,a);
       FigureRightArrow fig2(fig1);
       
       fig1.transform(Smooth::DotShift(center.subX(d1)));
       
       fig1.curveSolid(art,cname);
       
       fig2.transform(Smooth::DotShift(center.addX(d2)));
       
       fig2.curveSolid(art,cname);
      }
     break;
     
     case FaceLeftLeft :
      {
       MCoord a=radius/2;
       MCoord d2=radius/3;
       MCoord d1=d2/2;
       
       FigureLeftArrow fig1(-a,a,-a,a);
       FigureLeftArrow fig2(fig1);
       
       fig1.transform(Smooth::DotShift(center.addX(d1)));
       
       fig1.curveSolid(art,cname);
       
       fig2.transform(Smooth::DotShift(center.subX(d2)));
       
       fig2.curveSolid(art,cname);
      }
     break; 
    }
  
  // border
  
  {
   VColor cname;
   MCoord width=+cfg.width;
   
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
 }

} // namespace Video
} // namespace CCore
 

