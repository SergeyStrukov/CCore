/* DrawLab.h */
//----------------------------------------------------------------------------------------
//
//  Project: DrawLab 1.00
//
//  Tag: private
//
//  License: proprietary software, don't distribute!
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef DrawLab_h
#define DrawLab_h

#include <inc/Application.h>

#include <CCore/inc/video/SmoothDrawArt.h>

#include <CCore/inc/Array.h>

namespace App {

/* classes */

class DrawLab;

/* class DrawLab */

class DrawLab : public SubWindow
 {
   struct Config
    {
     MCoord grid_width = Fraction(1,0) ;
     MCoord width = Fraction(5,2) ;
     
     Coord space_dxy     =  10 ;
     Coord control_dx    = 200 ;
     Coord textspace_dxy =   4 ;
     
     unsigned zoom_deg   =   4 ;
     
     Coord zoom_mul      = 1u<<zoom_deg ;
     
     Coord simple_len    = 3 ;  
     Coord break_len     = 4 ;
     Coord pick_len      = 7 ;
     Coord near_len      = 8 ;
     
     Coord dot_len       = 2 ;
     
     ColorName back      = Wheat ;
     ColorName work      = Silver ;
     
     ColorName part      = RGBColor(200,200,255) ;
     
     ColorName grid      = Blue ;
     ColorName grid2     = Black ;
     
     ColorName path      = Red ;
     ColorName mark      = RGBColor(128,0,0) ;
     ColorName pick      = Orange ;
     ColorName near      = Blue ;
     
     ColorName text      = Blue ;
     
     ColorName menu      = Black ;
     ColorName select    = RGBColor(180,180,255) ;
     
     ColorName width1    = GrayColor(160);
     ColorName width2    = GrayColor(170);
     
     Font font;
     
     Config() {}
    };
   
   Config cfg;
  
   // areas
   
   Pane info;
   Pane control;
   Pane zoom;
   Pane normal;
   
   Pane select_Path;
   Pane select_Loop;
   Pane select_Curve;
   Pane select_CurveLoop;
   
   Pane select_SolidOdd;
   Pane select_SolidAll;
   Pane select_CurveSolidOdd;
   Pane select_CurveSolidAll;
   
   Pane select_LinePath;
   Pane select_LineLoop;
   Pane select_LineCurve;
   Pane select_LineCurveLoop;
   
   Pane select_HalfLinePath;
   Pane select_HalfLineLoop;
   Pane select_HalfLineCurve;
   Pane select_HalfLineCurveLoop;
   
   Pane width;
   Pane width_plus;
   Pane width_minus;
   Pane width_value;
   
   // edit
   
   bool do_ins = true ;
   Smooth::DotType dot_type = Smooth::DotSimple ;
   
   bool move_normal = false ;
   bool move_zoom = false ;
   
   // shape
   
   DynArray<Smooth::Dot> dots;
   ulen pick_ind = 0 ;
   ulen near_ind = 0 ;
   
   Pane part;
   
   MCoord line_width = Fraction(10) ;
   HalfFlag half_flag = HalfPos ;
   
   enum DrawType
    {
     DrawPath,
     DrawLoop,
     DrawCurve,
     DrawCurveLoop,
     
     DrawSolidOdd,
     DrawSolidAll,
     DrawCurveSolidOdd,
     DrawCurveSolidAll,
     
     DrawLinePath,
     DrawLineLoop,
     DrawLineCurve,
     DrawLineCurveLoop,
     
     DrawHalfLinePath,
     DrawHalfLineLoop,
     DrawHalfLineCurve,
     DrawHalfLineCurveLoop
    };

   DrawType draw_type = DrawPath ;
   bool show_marks = false ;
   
  private: 
   
   static Ratio Zoom(Coord delta);
   
   static MPoint Zoom(MPoint point,MPoint base,Ratio zoom)
    {
     return base+zoom*(point-base);
    }

   static uCoord Distance(Point a,Point b) { return Max(IntAbs(a.x,b.x),IntAbs(a.y,b.y)); }
   
   MCoord toMilli(Coord x) const;
   
   Coord fromMilli(MCoord x) const;
   
   MPoint toMilli(Point point) const;
   
   Point fromMilli(MPoint point) const;
   
   MPoint map(Point point) const;
   
   MPoint mapZoom(Point point) const;
   
   // react
   
   void ins(MPoint point);
   
   void move(MPoint point);
   
   void zoom_based(MPoint base,Coord delta);
   
   void setType(Smooth::DotType dot_type);
   
   void insDot(Point point);
   
   void insZoomDot(Point point);
   
   void delDot();
   
   void moveDot(Point point);
   
   void moveZoomDot(Point point);

   void zoomDots(Point point,Coord delta);
   
   void zoomZoomDots(Point point,Coord delta);
   
   void setNear_based(Point point);
   
   void setNear(Point point);
   
   void setZoomNear(Point point);
   
   void setPickInd(ulen ind);
   
   bool noNear();
   
   void setWidth(MCoord width);
   
   void incWidth();
   
   void decWidth();
   
   // layout
   
   void setEmpty();
   
   // draw
   
   void drawMark(Smooth::DrawArt &art,Point point,Smooth::DotType dot_type) const;
   
   void drawPickMark(Smooth::DrawArt &art,Point point) const;
   
   void drawNearMark(Smooth::DrawArt &art,Point point) const;
   
   template <class Map>
   void drawPath(Smooth::DrawArt art,Map map,bool do_loop) const;
   
   void drawMarks(DrawBuf buf) const;
   
   void drawNormal(DrawBuf buf) const;
   
   class ZoomMap;
   class ZoomPath;
   class ZoomLoop;
   class ZoomDot;
   
   template <class R,class Map,class FuncInit>
   static void Apply(R r,Map map,FuncInit func_init);
   
   void drawZoom(DrawBuf buf) const;
   
  public:
  
   explicit DrawLab(SubWindowHost &host);
  
   virtual ~DrawLab();
   
   // drawing
   
   virtual void layout();
   
   virtual void draw(DrawBuf buf,bool drag_active) const;
   
   // base
   
   virtual void open();
   
   // mouse
 
   virtual void looseCapture();
 
   virtual MouseShape getMouseShape(Point point);
   
   // user input
   
   virtual void react(UserAction action);
   
   void react_Key(VKey vkey,KeyMod kmod);
   
   void react_LeftClick(Point point,MouseKey mkey);
   
   void react_LeftUp(Point point,MouseKey mkey);
   
   void react_RightClick(Point point,MouseKey mkey);
   
   void react_Move(Point point,MouseKey mkey);
   
   void react_Leave();
   
   void react_Wheel(Point point,MouseKey mkey,Coord delta);
 };

} // namespace App

#endif

