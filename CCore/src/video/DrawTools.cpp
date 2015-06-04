/* DrawTools.cpp */
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

#include <CCore/inc/video/DrawTools.h>
#include <CCore/inc/video/DrawAlgo.h>

namespace CCore {
namespace Video {

/* struct CircleSpline */

CircleSpline::CircleSpline(Point center,Coord radius)
 {
  IntGuard( radius>0 );
  
  Coord x=Coord( radius/2 );
  Coord y=Coord( DrawAlgo::SqRoot<uMCoord>(Sq<uMCoord>(radius)-Sq<uMCoord>(x),radius) );
 
  buf[0]=center+Point(0,radius);
  buf[1]=center+Point(-x,y);
  buf[2]=center+Point(-y,x);
  buf[3]=center+Point(-radius,0);
  buf[4]=center+Point(-y,-x);
  buf[5]=center+Point(-x,-y);
  buf[6]=center+Point(0,-radius);
  buf[7]=center+Point(x,-y);
  buf[8]=center+Point(y,-x);
  buf[9]=center+Point(radius,0);
  buf[10]=center+Point(y,x);
  buf[11]=center+Point(x,y);
 }

/* struct PaneBorder */

PaneBorder::PaneBorder(Pane pane)
 {
  Coord x=pane.x+pane.dx-1;
  Coord y=pane.y+pane.dy-1;
  
  buf[0]=Point(pane.x,pane.y);
  buf[1]=Point(pane.x,y);
  buf[2]=Point(x,y);
  buf[3]=Point(x,pane.y);
 }

/* struct PaneSub */

PaneSub::PaneSub(Pane outer,Pane inner)
 {
  if( !outer ) return;
  
  if( !inner )
    {
     top=outer;
     
     return;
    }
  
  inner=Inf_nonempty(outer,inner);
  
  if( !inner )
    {
     top=outer;
    
     return;
    }
  
  top.x=outer.x;
  top.y=outer.y;
  top.dx=outer.dx;
  top.dy=inner.y-outer.y;
  
  left.x=outer.x;
  left.y=inner.y;
  left.dx=inner.x-outer.x;
  left.dy=inner.dy;

  right.x=inner.x+inner.dx;
  right.y=inner.y;
  right.dx=outer.x+outer.dx-right.x;
  right.dy=inner.dy;
  
  bottom.x=outer.x;
  bottom.y=inner.y+inner.dy;
  bottom.dx=outer.dx;
  bottom.dy=outer.y+outer.dy-bottom.y;
 }

} // namespace Video
} // namespace CCore

