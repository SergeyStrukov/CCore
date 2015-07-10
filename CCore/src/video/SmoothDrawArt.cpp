/* SmoothDrawArt.cpp */ 
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
 
#include <CCore/inc/video/SmoothDrawArt.h>

namespace CCore {
namespace Video {
namespace Smooth {

/* enum DotType */

const char * GetTextDesc(DotType type)
 {
  switch( type )
    {
     case DotSimple : return "Simple";
     case DotBreak  : return "Break";
   
     default: return "???";
    }
 }

/* class DrawArt */

 // simple

void DrawArt::pixel(Point p,DesktopColor color)
 {
  buf.pixel_safe(buf.map(p),color);
 }

void DrawArt::erase(DesktopColor color)
 {
  buf.erase(color);
 }

void DrawArt::erase(VColor vc,Clr alpha)
 {
  buf.block_safe(buf.getPane(),vc,alpha);
 }

void DrawArt::block(Pane pane,DesktopColor color)
 {
  buf.block_safe(buf.map(pane),color);
 }

void DrawArt::block(Pane pane,VColor vc,Clr alpha)
 {
  buf.block_safe(buf.map(pane),vc,alpha);
 }

 // special

void DrawArt::knob(MPoint p,MCoord len,VColor vc)
 {
  knobField(p,len,ConstantField(vc));
 }

void DrawArt::ball(MPoint center,MCoord radius,VColor vc)
 {
  ballField(center,radius,ConstantField(vc));
 }

void DrawArt::ball(MPoint center,MCoord radius,TwoField field)
 {
  ballField(center,radius,field);
 }

void DrawArt::ball(MPoint center,MCoord radius,RadioField field)
 {
  ballField(center,radius,field);
 }

void DrawArt::circle(MPoint center,MCoord radius,MCoord width,VColor vc)
 {
  circleField(center,radius,width,ConstantField(vc));
 }

void DrawArt::pathOf(PtrLen<const MPoint> dots,MCoord width,VColor vc)
 {
  path(dots,width,vc);
 }

void DrawArt::loopOf(PtrLen<const MPoint> dots,MCoord width,VColor vc)
 {
  loop(dots,width,vc);
 }

void DrawArt::pathOf(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  path(dots,half_flag,width,vc);
 }

void DrawArt::loopOf(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  loop(dots,half_flag,width,vc);
 }

} // namespace Smooth
} // namespace Video
} // namespace CCore
 

