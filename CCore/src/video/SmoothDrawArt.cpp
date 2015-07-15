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

void DrawArt::knob(MPoint center,MCoord len,VColor vc)
 {
  knob_gen(center,len,ConstantField(vc));
 }

void DrawArt::ball(MPoint center,MCoord radius,VColor vc)
 {
  ball_gen(center,radius,ConstantField(vc));
 }

void DrawArt::ball(MPoint center,MCoord radius,const TwoField &field)
 {
  ball_gen(center,radius,field);
 }

void DrawArt::ball(MPoint center,MCoord radius,const RadioField &field)
 {
  ball_gen(center,radius,field);
 }

void DrawArt::circle(MPoint center,MCoord radius,MCoord width,VColor vc)
 {
  circle_gen(center,radius,width,ConstantField(vc));
 }

 // special line

void DrawArt::path(PtrLen<const MPoint> dots,MCoord width,VColor vc)
 {
  path_gen(dots,width,vc);
 }

void DrawArt::loop(PtrLen<const MPoint> dots,MCoord width,VColor vc)
 {
  loop_gen(dots,width,vc);
 }

 // special half line

void DrawArt::path(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  path_gen(dots,half_flag,width,vc);
 }

void DrawArt::loop(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  loop_gen(dots,half_flag,width,vc);
 }

 // special curve

void DrawArt::curvePath(PtrLen<const MPoint> dots,MCoord width,VColor vc)
 {
  curvePath_gen(dots,width,vc);
 }

void DrawArt::curveLoop(PtrLen<const MPoint> dots,MCoord width,VColor vc)
 {
  curveLoop_gen(dots,width,vc);
 }

void DrawArt::curvePath(PtrLen<const Dot> dots,MCoord width,VColor vc)
 {
  curveBreakPath_gen(dots,width,vc);
 }

void DrawArt::curveLoop(PtrLen<const Dot> dots,MCoord width,VColor vc)
 {
  curveBreakLoop_gen(dots,width,vc);
 }

 // special half curve

void DrawArt::curvePath(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  curvePath_gen(dots,half_flag,width,vc);
 }

void DrawArt::curveLoop(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  curveLoop_gen(dots,half_flag,width,vc);
 }

void DrawArt::curvePath(PtrLen<const Dot> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  curveBreakPath_gen(dots,half_flag,width,vc);
 }

void DrawArt::curveLoop(PtrLen<const Dot> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  curveBreakLoop_gen(dots,half_flag,width,vc);
 }

 // special solid

void DrawArt::solid(PtrLen<const MPoint> dots,SolidFlag solid_flag,VColor vc)
 {
  solid_gen(dots,solid_flag,vc);
 }

void DrawArt::solid(PtrLen<const MPoint> dots,SolidFlag solid_flag,const TwoField &field)
 {
  solid_gen(dots,solid_flag,field);
 }

void DrawArt::solid(PtrLen<const MPoint> dots,SolidFlag solid_flag,const RadioField &field)
 {
  solid_gen(dots,solid_flag,field);
 }

 // special curve solid

void DrawArt::curveSolid(PtrLen<const MPoint> dots,SolidFlag solid_flag,VColor vc)
 {
  curveSolid_gen(dots,solid_flag,vc);
 }

void DrawArt::curveSolid(PtrLen<const MPoint> dots,SolidFlag solid_flag,const TwoField &field)
 {
  curveSolid_gen(dots,solid_flag,field);
 }

void DrawArt::curveSolid(PtrLen<const MPoint> dots,SolidFlag solid_flag,const RadioField &field)
 {
  curveSolid_gen(dots,solid_flag,field);
 }

void DrawArt::curveSolid(PtrLen<const Dot> dots,SolidFlag solid_flag,VColor vc)
 {
  curveBreakSolid_gen(dots,solid_flag,vc);
 }

void DrawArt::curveSolid(PtrLen<const Dot> dots,SolidFlag solid_flag,const TwoField &field)
 {
  curveBreakSolid_gen(dots,solid_flag,field);
 }

void DrawArt::curveSolid(PtrLen<const Dot> dots,SolidFlag solid_flag,const RadioField &field)
 {
  curveBreakSolid_gen(dots,solid_flag,field);
 }

} // namespace Smooth
} // namespace Video
} // namespace CCore
 

