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

void DrawArt::erase(ColorName cname,Clr alpha)
 {
  buf.block_safe(buf.getPane(),cname,alpha);
 }

void DrawArt::block(Pane pane,DesktopColor color)
 {
  buf.block_safe(buf.map(pane),color);
 }

void DrawArt::block(Pane pane,ColorName cname,Clr alpha)
 {
  buf.block_safe(buf.map(pane),cname,alpha);
 }

 // special

void DrawArt::knob(MPoint p,MCoord len,ColorName cname)
 {
  knobField(p,len,ConstantField(cname));
 }

void DrawArt::ball(MPoint center,MCoord radius,ColorName cname)
 {
  ballField(center,radius,ConstantField(cname));
 }

void DrawArt::ball(MPoint center,MCoord radius,TwoField field)
 {
  ballField(center,radius,field);
 }

void DrawArt::ball(MPoint center,MCoord radius,RadioField field)
 {
  ballField(center,radius,field);
 }

void DrawArt::circle(MPoint center,MCoord radius,MCoord width,ColorName cname)
 {
  circleField(center,radius,width,ConstantField(cname));
 }

void DrawArt::pathOf(PtrLen<const MPoint> dots,MCoord width,ColorName cname)
 {
  path(dots,width,cname);
 }

void DrawArt::loopOf(PtrLen<const MPoint> dots,MCoord width,ColorName cname)
 {
  loop(dots,width,cname);
 }

void DrawArt::pathOf(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,ColorName cname)
 {
  path(dots,half_flag,width,cname);
 }

void DrawArt::loopOf(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,ColorName cname)
 {
  loop(dots,half_flag,width,cname);
 }

} // namespace Smooth
} // namespace Video
} // namespace CCore
 

