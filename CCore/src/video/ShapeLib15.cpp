/* ShapeLib15.cpp */ 
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

/* class ProgressShape */

Point ProgressShape::getMinSize() const
 {
  return Point(10,40);
 }

void ProgressShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  Smooth::DrawArt art(buf);
  
  MCoord x0=p.x;
  MCoord x2=p.ex;
  
  MCoord y0=p.y;
  MCoord y2=p.ey;
  
  MCoord x1=Position(pos,total,x0,x2);
  
  MCoord dt=p.dy;
  MCoord t0=Position(active_pos,MaxActivePos,x0,x2-dt);
  MCoord t1=t0+dt;
  
  MCoord ds=p.dy/5;
  MCoord s0=y0;
  MCoord s1=s0+ds;
  MCoord s3=y2;
  MCoord s2=s3-ds;
  
  {
   FigureBox fig(x0,x1,y0,y2);
   
   fig.solid(art,TwoField({x0,y0},+cfg.activeTop,{x0,y2},+cfg.activeBottom));
  }
  {
   FigureBox fig(x1,x2,y0,y2);
   
   fig.solid(art,TwoField({x0,y0},+cfg.top,{x0,y2},+cfg.bottom));
  }
  {
   FigureBox fig(x0,x2,y0,y2);
   
   fig.loop(art,HalfPos,+cfg.width,+cfg.border);
  }
  
  if( has_active )
    {
     VColor cname=+cfg.active;
    
     FigureBox fig1(t0,t1,s0,s1);
   
     fig1.solid(art,cname);
   
     FigureBox fig2(t0,t1,s2,s3);
   
     fig2.solid(art,cname);
    }
 }

} // namespace Video
} // namespace CCore
 

