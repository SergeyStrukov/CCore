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
  
  VColor bottom=+cfg.bottom;
  
  // body
  
  if( down )
    {
     art.ball(center,radius,bottom);
    }
  else
    {
     VColor top;
    
     if( mover && enable )
       top=+cfg.topUp;
     else
       top=+cfg.top; 
     
     art.ball(center,radius,TwoField(a,top,a.addY(len),bottom));
    }
  
  // face
  
  VColor fc=enable?+cfg.face:bottom;
  
  switch( face )
    {
     case FacePlus :
      {
       MCoord a=radius/2;
       MCoord w=radius/3;
       
       art.pathOf(w,fc,center.subX(a),center.addX(a));
       art.pathOf(w,fc,center.subY(a),center.addY(a));
      }
     break;
     
     case FaceMinus :
      {
       MCoord a=radius/2;
       MCoord w=radius/3;
       
       art.pathOf(w,fc,center.subX(a),center.addX(a));
      }
     break;
     
     case FaceCross :
      {
       MCoord a=radius/2;
       MCoord w=radius/3;
       
       art.pathOf(w,fc,center.subXY(a),center.addXY(a));
       art.pathOf(w,fc,center.addXsubY(a),center.subXaddY(a));
      }
     break;
     
     case FaceAsterisk :
      {
       FigureAsterisk fig(center,Ratio(652,10)*radius);

       fig.curveSolid(art,fc);
      }
     break;
     
     case FaceExclamation :
      {
       MCoord a=Ratio(683,10)*radius;
       MCoord c=radius/5;
       MCoord b=a-2*c;
       MCoord r=Ratio(3,2)*c;
       
       FigureDots<4> fig;
       
       fig[0]={{-c,c-a}};
       fig[1]={{0,-a}};
       fig[2]={{c,c-a}};
       fig[3]={{0,b},Smooth::DotBreak};
       
       fig.transform(Smooth::DotShift(center));
       
       fig.curveSolid(art,fc);
       
       art.ball(center.addY(b+r),r,fc);
      }
     break;
     
     case FaceQuestion :
      {
       MCoord a=Ratio(683,10)*radius;
       MCoord c=radius/5;
       MCoord b=a-2*c;
       MCoord r=Ratio(3,2)*c;
       
       art.ball(center.addY(b+r),r,fc);
      }
     break;
     
     case FaceLeft :
      {
       MCoord a=radius/2;
       MCoord d=radius/12;
       
       FigureLeftArrow fig(-d-a,a-d,-a,a);
       
       fig.transform(Smooth::DotShift(center));
       
       fig.curveSolid(art,fc);
      }
     break;
     
     case FaceRight :
      {
       MCoord a=radius/2;
       MCoord d=radius/12;
       
       FigureRightArrow fig(d-a,a+d,-a,a);
       
       fig.transform(Smooth::DotShift(center));
       
       fig.curveSolid(art,fc);
      }
     break;
     
     case FaceUp :
      {
       MCoord a=radius/2;
       MCoord d=radius/12;
       
       FigureUpArrow fig(-a,a,-d-a,a-d);
       
       fig.transform(Smooth::DotShift(center));
       
       fig.curveSolid(art,fc);
      }
     break;
     
     case FaceDown :
      {
       MCoord a=radius/2;
       MCoord d=radius/12;
       
       FigureDownArrow fig(-a,a,d-a,a+d);
       
       fig.transform(Smooth::DotShift(center));
       
       fig.curveSolid(art,fc);
      }
     break;
     
     case FaceStop :
      {
       MCoord a=radius/2;
       
       FigureBox fig(-a,a,-a,a);
       
       fig.transform(Smooth::DotShift(center));
       
       fig.solid(art,fc);
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
       
       fig1.curveSolid(art,fc);
       
       fig2.transform(Smooth::DotShift(center.addX(d2)));
       
       fig2.curveSolid(art,fc);
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
       
       fig1.curveSolid(art,fc);
       
       fig2.transform(Smooth::DotShift(center.subX(d2)));
       
       fig2.curveSolid(art,fc);
      }
     break; 
    }
  
  // border
  
  {
   VColor border;
   MCoord width=+cfg.width;
   
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
 }

} // namespace Video
} // namespace CCore
 

