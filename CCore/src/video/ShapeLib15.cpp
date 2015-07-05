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
  MCoord x2=p.x+p.dx;
  
  MCoord y0=p.y;
  MCoord y2=p.y+p.dy;
  MCoord y1=y0+(y2-y0)/2;
  
  MCoord x1=Position(pos,total,x0,x2);
  MCoord dx=Position(active_pos,MaxActivePos,0,p.dy);
  
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
  {
   FigurePoints<3> fig;
   
   fig[0]={x1-p.dy+dx,y0};
   fig[1]={x1-p.dy+dx,y2};
   fig[2]={x1+dx,y1};
   
   fig.solid(art,+cfg.activeBottom);
  }
 }

} // namespace Video
} // namespace CCore
 

