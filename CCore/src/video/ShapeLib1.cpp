/* ShapeLib1.cpp */ 
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

/* class ButtonShape */

Point ButtonShape::getMinSize() const
 {
  TextSize ts=cfg.font.get()->text(Range(face));
  
  IntGuard( !ts.overflow );
  
  MCoord width=+cfg.width;
  
  MCoord ex=(Fraction(ts.dy)+2*width)/4;
  
  Coord dx=RoundUpLen(ex);
  Coord dy=RoundUpLen(width);
  
  return 2*Point(dx,dy)+Point(ts.full_dx,ts.dy);
 }
   
void ButtonShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  Smooth::DrawArt art(buf);
  
  // figure
  
  MCoord width=+cfg.width;
  
  MCoord x0=p.x;
  MCoord x1=x0+p.dx;
  
  MCoord y0=p.y;
  MCoord y1=y0+p.dy;
  
  FontSize fs=cfg.font.get()->getSize();
  
  MCoord ex=(Fraction(fs.dy)+2*width)/4;
  
  FigureButton fig(x0,x1,y0,y1,ex);
  
  // body
  
  if( down )
    {
     fig.curveSolid(art,+cfg.bottom);
    }
  else
    {
     ColorName cname;
     
     if( mover && enable )
       cname=+cfg.topUp;
     else
       cname=+cfg.top;
     
     fig.curveSolid(art,TwoField({x0,y0},cname,{x0,y1},+cfg.bottom));
    }
  
  // text

  {
   Coord dx=RoundUpLen(ex);
   Coord dy=RoundUpLen(width);
   
   Point shift=Null;
   
   if( down ) shift=Point::Diag( (dy+1)/2 );
   
   ColorName cname;

   if( enable )
     cname=+cfg.text;
   else
     cname=+cfg.bottom;
   
   cfg.font.get()->text(buf,Shrink(pane,dx,dy)+shift,TextPlace(AlignX_Center,AlignY_Center),Range(face),cname);
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
   
   fig.curveLoop(art,HalfPos,width,cname);
  }
 }

} // namespace Video
} // namespace CCore
 

