/* FigureLib.cpp */ 
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
 
#include <CCore/inc/video/FigureLib.h>
 
namespace CCore {
namespace Video {

/* struct DrawPoints */

void DrawPoints::Path(Smooth::DrawArt &art,PtrLen<const MPoint> dots,MCoord width,VColor cname)
 {
  art.path(dots,width,cname);
 }

void DrawPoints::Loop(Smooth::DrawArt &art,PtrLen<const MPoint> dots,MCoord width,VColor cname)
 {
  art.loop(dots,width,cname);
 }

void DrawPoints::Path(Smooth::DrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor cname)
 {
  art.path(dots,half_flag,width,cname);
 }

void DrawPoints::Loop(Smooth::DrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor cname)
 {
  art.loop(dots,half_flag,width,cname);
 }

void DrawPoints::Solid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,VColor cname)
 {
  art.solid(dots,solid_flag,cname);
 }

void DrawPoints::Solid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,TwoField field)
 {
  art.solid(dots,solid_flag,field);
 }

void DrawPoints::Solid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,RadioField field)
 {
  art.solid(dots,solid_flag,field);
 }

void DrawPoints::CurvePath(Smooth::DrawArt &art,PtrLen<const MPoint> dots,MCoord width,VColor cname)
 {
  art.curve(dots,width,cname);
 }

void DrawPoints::CurveLoop(Smooth::DrawArt &art,PtrLen<const MPoint> dots,MCoord width,VColor cname)
 {
  art.curveLoop(dots,width,cname);
 }

void DrawPoints::CurvePath(Smooth::DrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor cname)
 {
  art.curve(dots,half_flag,width,cname);
 }

void DrawPoints::CurveLoop(Smooth::DrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor cname)
 {
  art.curveLoop(dots,half_flag,width,cname);
 }

void DrawPoints::CurveSolid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,VColor cname)
 {
  art.curveSolid(dots,solid_flag,cname);
 }

void DrawPoints::CurveSolid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,TwoField field)
 {
  art.curveSolid(dots,solid_flag,field);
 }

void DrawPoints::CurveSolid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,RadioField field)
 {
  art.curveSolid(dots,solid_flag,field);
 }

/* struct DrawDots */

void DrawDots::CurvePath(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,MCoord width,VColor cname)
 {
  art.curveBreak(dots,width,cname);
 }

void DrawDots::CurveLoop(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,MCoord width,VColor cname)
 {
  art.curveBreakLoop(dots,width,cname);
 }

void DrawDots::CurvePath(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,HalfFlag half_flag,MCoord width,VColor cname)
 {
  art.curveBreak(dots,half_flag,width,cname);
 }

void DrawDots::CurveLoop(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,HalfFlag half_flag,MCoord width,VColor cname)
 {
  art.curveBreakLoop(dots,half_flag,width,cname);
 }

void DrawDots::CurveSolid(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,SolidFlag solid_flag,VColor cname)
 {
  art.curveBreakSolid(dots,solid_flag,cname);
 }

void DrawDots::CurveSolid(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,SolidFlag solid_flag,TwoField field)
 {
  art.curveBreakSolid(dots,solid_flag,field);
 }

void DrawDots::CurveSolid(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,SolidFlag solid_flag,RadioField field)
 {
  art.curveBreakSolid(dots,solid_flag,field);
 }

/* struct FigureBox */

FigureBox::FigureBox(MCoord x0,MCoord x1,MCoord y0,MCoord y1)
 {
  buf[0]={x0,y0};
  buf[1]={x0,y1};
  buf[2]={x1,y1};
  buf[3]={x1,y0};
 }

/* struct FigureTopBorder */

FigureTopBorder::FigureTopBorder(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord w)
 {
  buf[0]={x0,y0};
  buf[1]={x0,y1};
  buf[2]={x0+w,y1-w};
  buf[3]={x0+w,y0+w};
  buf[4]={x1-w,y0+w};
  buf[5]={x1,y0};
 }

FigurePoints<6> FigureTopBorder::getLeftCut(MCoord t) const
 {
  FigurePoints<6> ret;
  
  ret.buf[0]=buf[0];
  ret.buf[1]=buf[1];
  ret.buf[2]=buf[2];
  ret.buf[3]=buf[3];
  ret.buf[4]=buf[4];
  ret.buf[5]=buf[5];
  
  ret.buf[4].x=t;
  ret.buf[5].x=t;
  
  return ret;
 }

FigurePoints<4> FigureTopBorder::getRightCut(MCoord t) const
 {
  FigurePoints<4> ret;
  
  ret.buf[0]=buf[4];
  ret.buf[1]=buf[5];
  ret.buf[2]=buf[5];
  ret.buf[3]=buf[4];
  
  ret.buf[2].x=t;
  ret.buf[3].x=t;
  
  return ret;
 }

/* struct FigureBottomBorder */

FigureBottomBorder::FigureBottomBorder(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord w)
 {
  buf[0]={x0,y1};
  buf[1]={x1,y1};
  buf[2]={x1,y0};
  buf[3]={x1-w,y0+w};
  buf[4]={x1-w,y1-w};
  buf[5]={x0+w,y1-w};
 }

/* struct FigureButton */

FigureButton::FigureButton(MCoord x0,MCoord x5,MCoord y0,MCoord y4,MCoord ex)
 {
  MCoord dy=y4-y0;
  
  MCoord ey=Ratio(200,10)*dy;
  
  MCoord y1=y0+ey;
  MCoord y2=y0+dy/2;
  MCoord y3=y4-ey;
  
  MCoord fx=ex/3;
  
  MCoord x1=x0+fx;
  MCoord x2=x0+ex;
  MCoord x3=x5-ex;
  MCoord x4=x5-fx;

  buf[0]={{x2,y0},Smooth::DotBreak};
  buf[1]={{x1,y1},Smooth::DotSimple};
  buf[2]={{x0,y2},Smooth::DotSimple};
  buf[3]={{x1,y3},Smooth::DotSimple};
  buf[4]={{x2,y4},Smooth::DotBreak};
  
  buf[5]={{x3,y4},Smooth::DotBreak};
  buf[6]={{x4,y3},Smooth::DotSimple};
  buf[7]={{x5,y2},Smooth::DotSimple};
  buf[8]={{x4,y1},Smooth::DotSimple};
  buf[9]={{x3,y0},Smooth::DotBreak};
 }

FigureDots<6> FigureButton::getTop() const
 {
  FigureDots<6> ret;
  
  ret.buf[0]=buf[9];
  ret.buf[1]=buf[0];
  ret.buf[2]=buf[1];
  ret.buf[3]=buf[2];
  ret.buf[4]=buf[3];
  ret.buf[5]=buf[4];
  
  return ret;
 }

FigureDots<6> FigureButton::getBottom() const
 {
  FigureDots<6> ret;
  
  ret.buf[0]=buf[4];
  ret.buf[1]=buf[5];
  ret.buf[2]=buf[6];
  ret.buf[3]=buf[7];
  ret.buf[4]=buf[8];
  ret.buf[5]=buf[9];
  
  return ret;
 }

/* struct FigureAsterisk */

FigureAsterisk::FigureAsterisk(MPoint center,MCoord radius)
 {
  MCoord a=radius/14;
  MCoord b=3*a;
  MCoord c=11*a;
  MCoord d=radius;
  
  buf[0]={-a,b};
  buf[1]={-b,c};
  buf[2]={0,d};
  buf[3]={b,c};
  buf[4]={a,b};
  
  Smooth::Rotate rotate(MPoint(1024,-1774));
  
  for(unsigned i=0; i<25 ;i++) buf[i+5]=rotate(buf[i]);
  
  for(unsigned i=0; i<30 ;i++) buf[i]+=center;
 }

/* struct FigureLeftArrow */

FigureLeftArrow::FigureLeftArrow(MCoord x0,MCoord x2,MCoord y0,MCoord y2)
 {
  MCoord x1=x2-(x2-x0)/6;
  MCoord y1=y0+(y2-y0)/2;
  
  buf[0]={{x2,y0},Smooth::DotBreak};
  buf[1]={{x0,y1},Smooth::DotBreak};
  buf[2]={{x2,y2},Smooth::DotBreak};
  buf[3]={{x1,y1}};
 }

/* struct FigureRightArrow */

FigureRightArrow::FigureRightArrow(MCoord x0,MCoord x2,MCoord y0,MCoord y2)
 {
  MCoord x1=x0+(x2-x0)/6;
  MCoord y1=y0+(y2-y0)/2;
  
  buf[0]={{x0,y2},Smooth::DotBreak};
  buf[1]={{x2,y1},Smooth::DotBreak};
  buf[2]={{x0,y0},Smooth::DotBreak};
  buf[3]={{x1,y1}};
 }

/* struct FigureUpArrow */

FigureUpArrow::FigureUpArrow(MCoord x0,MCoord x2,MCoord y0,MCoord y2)
 {
  MCoord x1=x0+(x2-x0)/2;
  MCoord y1=y2-(y2-y0)/6;
  
  buf[0]={{x2,y2},Smooth::DotBreak};
  buf[1]={{x1,y0},Smooth::DotBreak};
  buf[2]={{x0,y2},Smooth::DotBreak};
  buf[3]={{x1,y1}};
 }

/* struct FigureDownArrow */

FigureDownArrow::FigureDownArrow(MCoord x0,MCoord x2,MCoord y0,MCoord y2)
 {
  MCoord x1=x0+(x2-x0)/2;
  MCoord y1=y0+(y2-y0)/6;
  
  buf[0]={{x0,y0},Smooth::DotBreak};
  buf[1]={{x1,y2},Smooth::DotBreak};
  buf[2]={{x2,y0},Smooth::DotBreak};
  buf[3]={{x1,y1}};
 }

} // namespace Video
} // namespace CCore
 

