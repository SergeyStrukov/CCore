/* DragWindow.h */ 
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

#ifndef CCore_inc_video_DragWindow_h
#define CCore_inc_video_DragWindow_h

#include <CCore/inc/video/ClientWindow.h>
#include <CCore/inc/video/Font.h>

#include <CCore/inc/String.h>
#include <CCore/inc/DeferCall.h>
#include <CCore/inc/Signal.h>

namespace CCore {
namespace Video {

/* consts */

enum DragType
 {
  DragType_None = 0,
  
  DragType_Top,
  DragType_TopLeft,
  DragType_Left,
  DragType_BottomLeft,
  DragType_Bottom,
  DragType_BottomRight,
  DragType_Right,
  DragType_TopRight,
  
  DragType_Bar,
  
  DragType_Alert,
  DragType_Min,
  DragType_Max,
  DragType_Close
 };

enum AlertType
 {
  AlertType_No = 0,
  AlertType_Closed,
  AlertType_Opened
 };

/* DragPane() */

void DragPane(Pane &place,Point delta,DragType drag_type);

/* classes */

class DragWindow;

/* class DragWindow */

class DragWindow : public FrameWindow , public SubWinControl
 {
  public:
  
   class Shape
    {
     public:
    
      struct Config
       {
        Coord frame_dxy = 11 ;
        Coord title_dy  = 32 ;
        
        Coord btn_dx    = 32 ;
        Coord btn_dy    = 30 ;
        
        Coord min_dy    =  3 ;
        Coord alert_dx  =  2 ;
 
        ColorName edge            =     Black ;
        ColorName frame           =    Silver ;
        ColorName accent          =      Gray ;
        ColorName accentHilight   =     Green ;
        ColorName accentDrag      =       Red ;
        
        ColorName active          = RGBColor(128,128,255) ;
        ColorName inactive        =    Silver ;
        
        ColorName btnFace         = SteelBlue ;
        ColorName btnFaceHilight  =     Green ;
        ColorName btnFaceDown     =      Blue ;
        ColorName btnFaceClose    =   DarkRed ;
        ColorName btnEdge         =     Black ;
        ColorName btnPict         =     White ;
        ColorName btnStop         =       Red ;
        
        ColorName titleUp         =      Gray ;
        ColorName titleDown       =      Snow ;
        
        ColorName titleActiveUp   = RGBColor(0,0,128) ;
        ColorName titleActiveDown = RGBColor(200,200,128) ;
        
        ColorName alert           =       Red ;
        ColorName noAlert         =    Silver ;
        ColorName closeAlert      =    Orange ;
        
        ColorName title           =     Black ;
        
        Font title_font;
        
        unsigned blink_time       = 24 ;
        unsigned blink_period     = 3 ;
        
        Config() {}
        
        Signal<> update;
       };
      
      Config &cfg;

     private: 
     
      // layout
     
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
      
      ColorName accentColor(DragType zone) const { return (drag_type==zone)?cfg.accentDrag:( (hilight==zone)?cfg.accentHilight:cfg.accent ); }
      
      ColorName btnColor(DragType zone) const { return (btn_type==zone)?cfg.btnFaceDown:( (hilight==zone)?cfg.btnFaceHilight:cfg.btnFace ); }
      
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
      
      explicit Shape(Config &cfg_) : cfg(cfg_) {}
      
      Pane getClient() const { return client; }
      
      void reset(String title_,bool max_button_)
       {
        has_focus=false;
        max_button=max_button_;
        
        drag_type=DragType_None;
        hilight=DragType_None;
        btn_type=DragType_None;
        alert_type=AlertType_No;
        alert_blink=false;
        
        title=title_;
       }
      
      void layout(Point size);
      
      void draw(DrawBuf buf) const;
      
      void draw(DrawBuf buf,DragType drag_type) const;
      
      Pane getPane(DragType drag_type) const;
      
      DragType dragTest(Point point) const;
    };
  
  private: 
   
   Shape shape;
   
   ClientWindow *client = 0 ;
   ClientWindow *alert_client = 0 ;
   
   Point size;
   
   Point drag_from;
   bool client_enter = false ;
   bool client_capture = false ;
   bool delay_draw = false ;
   
   unsigned tick_count = 0 ;
   
  private:
   
   void guardClient();
   
   void guardDead();
   
   void reset()
    {
     size=Null;
     client_enter=false;
     client_capture=false;
     delay_draw=false;
     tick_count=0;
    }
   
   void replace(Pane place,Point delta,DragType drag_type);
   
   void replace(Point delta,DragType drag_type);

   void startDrag(Point point,DragType drag_type);
   
   void dragTo(Point point);
   
   void endDrag();
   
   void endDrag(Point point);
   
   bool forwardKey(VKey vkey,KeyMod kmod,unsigned repeat=1);
   
   bool forwardKeyUp(VKey vkey,KeyMod kmod,unsigned repeat=1);
   
   ClientWindow & getClient();
   
   SubWindow & getClientSub() { return getClient().getSubWindow(); }
   
   void redrawFrame();
   
   void redrawFrame(DragType drag_type);
   
   void pushAlertBlink();
   
   void tick();
   
   void switchClients();
   
  public:
  
   DragWindow(Desktop *desktop,Shape::Config &cfg);
   
   virtual ~DragWindow();
   
   // methods
   
   void bindClient(ClientWindow &client_)
    { 
     guardDead(); 
     
     client=&client_;
    }
   
   void bindAlertClient(ClientWindow &alert_client_)
    { 
     guardDead(); 
     
     alert_client=&alert_client_;
    }
   
   void createMain(CmdDisplay cmd_display,Point max_size,String title);
   
   void create(Pane pane,Point max_size,String title);
   
   void create(WindowHost *parent,Pane pane,Point max_size,String title);
   
   void destroy();
   
   void minimize();
   
   void maximize();
   
   void redrawAll(bool do_layout=false);
   
   void redrawClient();
   
   void redrawClient(Pane pane);
   
   unsigned getToken() { return host->getToken(); }
   
   void setTitle(String title)
    {
     shape.title=title;
     
     redrawFrame();
    }
   
   void alert();
   
   // SubWinControl
   
   virtual FrameWindow * getFrame();
  
   virtual Point getScreenOrigin();
  
   virtual void redraw(Pane pane);
  
   virtual void setFocus(SubWindow *sub_win);
  
   virtual void captureMouse(SubWindow *sub_win);
  
   virtual void releaseMouse(SubWindow *sub_win);
   
   // base
   
   virtual void alive();
   
   virtual void dead();
   
   virtual void setSize(Point size,bool buf_dirty);
   
   virtual void paintDone(unsigned token);
   
   // keyboard
   
   virtual void gainFocus();
   
   virtual void looseFocus();
   
   virtual void key(VKey vkey,KeyMod kmod);
   
   virtual void key(VKey vkey,KeyMod kmod,unsigned repeat);
   
   virtual void keyUp(VKey vkey,KeyMod kmod);
   
   virtual void keyUp(VKey vkey,KeyMod kmod,unsigned repeat);
   
   // character
   
   virtual void putch(char ch);
   
   virtual void putch(char ch,unsigned repeat);
   
   virtual void putchAlt(char ch);
   
   virtual void putchAlt(char ch,unsigned repeat);
   
   // mouse
   
   virtual void looseCapture();
   
   virtual void clickLeft(Point point,MouseKey mkey);
   
   virtual void upLeft(Point point,MouseKey mkey);
 
   virtual void dclickLeft(Point point,MouseKey mkey);
   
   virtual void clickRight(Point point,MouseKey mkey);
   
   virtual void upRight(Point point,MouseKey mkey);
   
   virtual void dclickRight(Point point,MouseKey mkey);
   
   virtual void move(Point point,MouseKey mkey);
   
   virtual void hover(Point point,MouseKey mkey);
   
   virtual void leave();
   
   virtual void wheel(Point point,MouseKey mkey,Coord delta);
 
   virtual void setMouseShape(Point point);

   // DeferInput
   
   class Input : DeferInput<DragWindow>
    {
      friend class DragWindow;
      
      explicit Input(DragWindow *window) : DeferInput<DragWindow>(window) {}
      
      ~Input() {}
      
     public:

      void redrawAll(bool do_layout=false) { try_post(&DragWindow::redrawAll,do_layout); }
      
      void redrawClient() { try_post(&DragWindow::redrawClient); }
      
      void redrawClient(Pane pane) { try_post(&DragWindow::redrawClient,pane); }
    };
   
   Input input;
   
  private:
   
   DeferTick defer_tick;
   
   void updateConfig();
   
   SignalConnector<DragWindow> connector_updateConfig;
 };

} // namespace Video
} // namespace CCore
 
#endif
 

