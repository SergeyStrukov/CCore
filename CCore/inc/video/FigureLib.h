/* FigureLib.h */ 
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

#ifndef CCore_inc_video_FigureLib_h
#define CCore_inc_video_FigureLib_h

#include <CCore/inc/video/SmoothDrawArt.h>
 
namespace CCore {
namespace Video {

/* classes */

struct MPane;

template <class T,ulen Len> struct FigureBase;

struct DrawPoints;

template <ulen Len> struct FigurePoints;

struct DrawDots;

template <ulen Len> struct FigureDots;

struct FigureBox;

struct FigureTopBorder;

struct FigureBottomBorder;

struct FigureButton;

struct FigureAsterisk;

struct FigureLeftArrow;

struct FigureRightArrow;

struct FigureUpArrow;

struct FigureDownArrow;

/* struct MPane */

struct MPane
 {
  MCoord x;
  MCoord y;
  MCoord dx;
  MCoord dy;
  
  MPane(Pane pane)
   {
    x=MPoint::LShift(pane.x)-MPoint::Half;
    y=MPoint::LShift(pane.y)-MPoint::Half;
    dx=MPoint::LShift(pane.dx);
    dy=MPoint::LShift(pane.dy);
   }
  
  bool operator + () const { return dx>0 && dy>0 ; }
  
  bool operator ! () const { return dx<=0 && dy<=0 ; }
  
  void square()
   {
    if( dx>dy )
      {
       dx=dy;
      }
    else
      {
       dy=dx;
      }
   }
 
  MPoint getBase() const { return MPoint(x,y); }
  
  MPoint getSize() const { return MPoint(dx,dy); }
  
  MPoint getLim() const { return MPoint(x+dx,y+dy); }
 };

/* struct FigureBase<T,Len> */

template <class T,ulen Len> 
struct FigureBase
 {
  T buf[Len];
  
  PtrLen<const T> get() const { return Range(buf); }
  
  T & operator [] (ulen ind) { return buf[ind]; }
  
  const T & operator [] (ulen ind) const { return buf[ind]; }
 };

/* struct DrawPoints */

struct DrawPoints
 {
  static void Path(Smooth::DrawArt &art,PtrLen<const MPoint> dots,MCoord width,ColorName cname);
  
  static void Loop(Smooth::DrawArt &art,PtrLen<const MPoint> dots,MCoord width,ColorName cname);
  

  static void Path(Smooth::DrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,ColorName cname);
  
  static void Loop(Smooth::DrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,ColorName cname);
  

  static void Solid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,ColorName cname);
  
  static void Solid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,TwoField field);
  
  static void Solid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,RadioField field);
  
  
  static void Solid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,ColorName cname)
   {
    Solid(art,dots,SolidAll,cname);
   }
  
  static void Solid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,TwoField field)
   {
    Solid(art,dots,SolidAll,field);
   }
  
  static void Solid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,RadioField field)
   {
    Solid(art,dots,SolidAll,field);
   }
  
  
  static void CurvePath(Smooth::DrawArt &art,PtrLen<const MPoint> dots,MCoord width,ColorName cname);
  
  static void CurveLoop(Smooth::DrawArt &art,PtrLen<const MPoint> dots,MCoord width,ColorName cname);
  
  
  static void CurvePath(Smooth::DrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,ColorName cname);
  
  static void CurveLoop(Smooth::DrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,ColorName cname);
  
  
  static void CurveSolid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,ColorName cname);
  
  static void CurveSolid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,TwoField field);
  
  static void CurveSolid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,RadioField field);
  
  
  static void CurveSolid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,ColorName cname)
   {
    CurveSolid(art,dots,SolidAll,cname);
   }
  
  static void CurveSolid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,TwoField field)
   {
    CurveSolid(art,dots,SolidAll,field);
   }
  
  static void CurveSolid(Smooth::DrawArt &art,PtrLen<const MPoint> dots,RadioField field)
   {
    CurveSolid(art,dots,SolidAll,field);
   }
 };

/* struct FigurePoints<Len> */

template <ulen Len> 
struct FigurePoints : FigureBase<MPoint,Len> , DrawPoints 
 {
  template <class FuncInit>
  void transform(FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    for(MPoint &p : this->buf ) p=func(p);
   }
 
  template <class ... TT>
  void path(Smooth::DrawArt &art,TT && ... tt) const
   {
    Path(art,this->get(), std::forward<TT>(tt)... );
   }
  
  template <class ... TT>
  void loop(Smooth::DrawArt &art,TT && ... tt) const
   {
    Loop(art,this->get(), std::forward<TT>(tt)... );
   }
  
  template <class ... TT>
  void solid(Smooth::DrawArt &art,TT && ... tt) const
   {
    Solid(art,this->get(), std::forward<TT>(tt)... );
   }
 
  template <class ... TT>
  void curvePath(Smooth::DrawArt &art,TT && ... tt) const
   {
    CurvePath(art,this->get(), std::forward<TT>(tt)... );
   }
  
  template <class ... TT>
  void curveLoop(Smooth::DrawArt &art,TT && ... tt) const
   {
    CurveLoop(art,this->get(), std::forward<TT>(tt)... );
   }
  
  template <class ... TT>
  void curveSolid(Smooth::DrawArt &art,TT && ... tt) const
   {
    CurveSolid(art,this->get(), std::forward<TT>(tt)... );
   }
 };

/* struct DrawDots */

struct DrawDots
 {
  static void CurvePath(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,MCoord width,ColorName cname);
  
  static void CurveLoop(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,MCoord width,ColorName cname);
  
  
  static void CurvePath(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,HalfFlag half_flag,MCoord width,ColorName cname);
  
  static void CurveLoop(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,HalfFlag half_flag,MCoord width,ColorName cname);
  
  
  static void CurveSolid(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,SolidFlag solid_flag,ColorName cname);
  
  static void CurveSolid(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,SolidFlag solid_flag,TwoField field);
  
  static void CurveSolid(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,SolidFlag solid_flag,RadioField field);
  
  
  static void CurveSolid(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,ColorName cname)
   {
    CurveSolid(art,dots,SolidAll,cname);
   }
  
  static void CurveSolid(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,TwoField field)
   {
    CurveSolid(art,dots,SolidAll,field);
   }
  
  static void CurveSolid(Smooth::DrawArt &art,PtrLen<const Smooth::Dot> dots,RadioField field)
   {
    CurveSolid(art,dots,SolidAll,field);
   }
 };

/* struct FigureDots<Len> */

template <ulen Len> 
struct FigureDots : FigureBase<Smooth::Dot,Len> , DrawDots
 {
  template <class FuncInit>
  void transform(FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    for(Smooth::Dot &p : this->buf ) p.point=func(p.point);
   }
  
  template <class ... TT>
  void curvePath(Smooth::DrawArt &art,TT && ... tt) const
   {
    CurvePath(art,this->get(), std::forward<TT>(tt)... );
   }
  
  template <class ... TT>
  void curveLoop(Smooth::DrawArt &art,TT && ... tt) const
   {
    CurveLoop(art,this->get(), std::forward<TT>(tt)... );
   }
  
  template <class ... TT>
  void curveSolid(Smooth::DrawArt &art,TT && ... tt) const
   {
    CurveSolid(art,this->get(), std::forward<TT>(tt)... );
   }
 };

/* struct FigureBox */

struct FigureBox : FigurePoints<4> 
 {
  FigureBox(MCoord x0,MCoord x1,MCoord y0,MCoord y1);
 };

/* struct FigureTopBorder */

struct FigureTopBorder : FigurePoints<6>
 {
  FigureTopBorder(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord w);
  
  FigurePoints<6> getLeftCut(MCoord t) const;
  
  FigurePoints<4> getRightCut(MCoord t) const;
 };

/* struct FigureBottomBorder */

struct FigureBottomBorder : FigurePoints<6>
 {
  FigureBottomBorder(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord w);
 };

/* struct FigureButton */

struct FigureButton : FigureDots<10>
 {
  FigureButton(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord ex);
  
  FigureDots<6> getTop() const;
  
  FigureDots<6> getBottom() const;
 };

/* struct FigureAsterisk */

struct FigureAsterisk : FigurePoints<30>
 {
  FigureAsterisk(MPoint center,MCoord radius);
 };

/* struct FigureLeftArrow */

struct FigureLeftArrow : FigureDots<4>
 {
  FigureLeftArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1);
 };

/* struct FigureRightArrow */

struct FigureRightArrow : FigureDots<4>
 {
  FigureRightArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1);
 };

/* struct FigureUpArrow */

struct FigureUpArrow : FigureDots<4>
 {
  FigureUpArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1);
 };

/* struct FigureDownArrow */

struct FigureDownArrow : FigureDots<4>
 {
  FigureDownArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1);
 };

} // namespace Video
} // namespace CCore
 
#endif
 

