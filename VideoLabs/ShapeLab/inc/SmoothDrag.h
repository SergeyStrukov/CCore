/* SmoothDrag.h */
//----------------------------------------------------------------------------------------
//
//  Project: ShapeLab 1.00
//
//  Tag: private
//
//  License: proprietary software, don't distribute!
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef SmoothDrag_h
#define SmoothDrag_h

#include <CCore/inc/video/DragWindow.h>

namespace App {

/* using */

using namespace CCore;
using namespace CCore::Video;

/* classes */

class SmoothDragShape;

/* class SmoothDragShape */

class SmoothDragShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
    
     RefVal<Coord> frame_dxy = 12 ;
     RefVal<Coord> title_dy  = 32 ;
     
     RefVal<Coord> btn_dx    = 24 ;
     RefVal<Coord> btn_dy    = 24 ;

     RefVal<ColorName> top          =   Snow ;
     RefVal<ColorName> bottom       =   Gray ;
     RefVal<ColorName> frame        = Silver ;
     
     RefVal<ColorName> drag         = Silver ;
     RefVal<ColorName> dragHilight  =  Green ;
     RefVal<ColorName> dragActive   =    Red ;
     
     RefVal<ColorName> active       = RGBColor(128,128,255) ;
     RefVal<ColorName> inactive     =    Silver ;
     RefVal<ColorName> title        =     Black ;
     
     RefVal<ColorName> btnFace      = SteelBlue ;
     
#if 0
     
     RefVal<ColorName> accent          =      Gray ;
     RefVal<ColorName> accentHilight   =     Green ;
     RefVal<ColorName> accentDrag      =       Red ;
     
     
     RefVal<ColorName> btnFaceHilight  =     Green ;
     RefVal<ColorName> btnFaceDown     =      Blue ;
     RefVal<ColorName> btnFaceClose    =   DarkRed ;
     RefVal<ColorName> btnEdge         =     Black ;
     RefVal<ColorName> btnPict         =     White ;
     RefVal<ColorName> btnClose        =       Red ;
     
     RefVal<ColorName> titleUp         =      Gray ;
     RefVal<ColorName> titleDown       =      Snow ;
     
     RefVal<ColorName> titleActiveUp   = RGBColor(0,0,128) ;
     RefVal<ColorName> titleActiveDown = RGBColor(200,200,128) ;
     
     RefVal<ColorName> alert           =       Red ;
     RefVal<ColorName> noAlert         =    Silver ;
     RefVal<ColorName> closeAlert      =    Orange ;
     
#endif     
     
     
     RefVal<Font> title_font;
     
     RefVal<unsigned> blink_time       = 24 ;
     RefVal<unsigned> blink_period     = 3 ;
     
     Config() {}
     
     mutable Signal<> update;
    };
   
   const Config &cfg;
  
  private:
  
   Point size;
   
   Pane dragTopLeft;
   Pane dragLeft;
   Pane dragBottomLeft;
   Pane dragBottom;
   Pane dragBottomRight;
   Pane dragRight;
   Pane dragTopRight;
   Pane dragBar;
   
   Pane titleBar;
   Pane btnAlert;
   Pane btnMin;
   Pane btnMax;
   Pane btnClose;
   
   Pane client;
   
  private:
   
   class DrawArt;
   
   ColorName dragColor(DragType zone) const;
   
   void draw_TopLeft(DrawArt &art) const;
   
   void draw_Left(DrawArt &art) const;
   
   void draw_BottomLeft(DrawArt &art) const;
   
   void draw_Bottom(DrawArt &art) const;
   
   void draw_BottomRight(DrawArt &art) const;
   
   void draw_Right(DrawArt &art) const;
   
   void draw_TopRight(DrawArt &art) const;
   
   void draw_Alert(DrawArt &art) const;
   
   void draw_Min(DrawArt &art) const;
   
   void draw_Max(DrawArt &art) const;
   
   void draw_Close(DrawArt &art) const;
   
   void draw_Bar(DrawArt &art) const;
   
   void draw_Border(DrawArt &art) const;
   
  public:
   
   // state
   
   bool has_focus = false ;
   bool max_button = true ;
   
   DragType drag_type = DragType_None ;
   DragType hilight = DragType_None ;
   DragType btn_type = DragType_None ;
   AlertType alert_type = AlertType_No ;
   bool alert_blink = false ;
   
   String title;
  
   // methods
   
   explicit SmoothDragShape(const Config &cfg_) : cfg(cfg_) {}
   
   Pane getClient() const { return client; }
   
   void reset(const String &title,bool max_button);
   
   void layout(Point size);
   
   void draw(const DrawBuf &buf) const;
   
   void draw(const DrawBuf &buf,DragType drag_type) const;
   
   Pane getPane(DragType drag_type) const;
   
   DragType dragTest(Point point) const;
 };

} // namespace App

#endif

