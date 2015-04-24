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

#include <CCore/inc/video/Desktop.h>
#include <CCore/inc/video/FrameBuf.h>
#include <CCore/inc/video/Font.h>

#include <CCore/inc/String.h>
#include <CCore/inc/DeferCall.h>
#include <CCore/inc/Signal.h>

namespace CCore {
namespace Video {

/* consts */

enum class DragType
 {
  None = 0,
  
  Up,
  UpLeft,
  Left,
  DownLeft,
  Down,
  DownRight,
  Right,
  UpRight,
  
  Bar,
  
  Alert,
  Min,
  Max,
  Close
 };

enum class AlertType
 {
  No = 0,
  Closed,
  Opened
 };

/* functions */

template <class E>
void DragPane(Pane &place,Point delta,E type)
 {
  switch( type )
    {
     case E::Up :
      {
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break; 
     
     case E::UpLeft :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
       
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;
     
     case E::Left :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
      }
     break;
     
     case E::DownLeft :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
       
       place.dy+=delta.y;
      }
     break;
     
     case E::Down :
      {
       place.dy+=delta.y;
      }
     break;
     
     case E::DownRight :
      {
       place.dx+=delta.x;
       
       place.dy+=delta.y;
      }
     break;
     
     case E::Right :
      {
       place.dx+=delta.x;
      }
     break;
     
     case E::UpRight :
      {
       place.dx+=delta.x;
       
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;
     
     case E::Bar :
      {
       place.x+=delta.x;
       
       place.y+=delta.y;
      }
     break;
    }
 }

/* classes */

class DragClient;

class DragWindow;

/* class DragClient */

class DragClient : NoCopy
 {
  protected:
  
   DragWindow *win = 0 ;
   
   friend class DragWindow;
  
  public:
  
   DragClient();
   
   virtual ~DragClient();
   
   // drawing
   
   virtual void layout(Point size);
   
   virtual void draw(FrameBuf<DesktopColor> buf,bool drag_active) const;
   
   // base
   
   virtual void alive()
    {
     // do nothing
    }
   
   virtual void dead()
    {
     // do nothing
    }
   
   // keyboard
   
   virtual void key(VKey vkey,KeyMod kmod)
    {
     Used(vkey);
     Used(kmod);
     
     // do nothing
    }
   
   virtual void key(VKey vkey,KeyMod kmod,unsigned repeat)
    {
     for(; repeat ;repeat--) key(vkey,kmod);
    }
   
   virtual void keyUp(VKey vkey,KeyMod kmod)
    {
     Used(vkey);
     Used(kmod);
     
     // do nothing
    }
   
   virtual void keyUp(VKey vkey,KeyMod kmod,unsigned repeat)
    {
     for(; repeat ;repeat--) keyUp(vkey,kmod);
    }
   
   // character
   
   virtual void putch(char ch)
    {
     Used(ch);
     
     // do nothing
    }
   
   virtual void putch(char ch,unsigned repeat)
    {
     for(; repeat ;repeat--) putch(ch);
    }
   
   virtual void putchAlt(char ch)
    {
     Used(ch);
     
     // do nothing
    }
   
   virtual void putchAlt(char ch,unsigned repeat)
    {
     for(; repeat ;repeat--) putchAlt(ch);
    }
   
   // mouse
   
   virtual void clickLeft(Point point,MouseKey mkey)
    {
     Used(point);
     Used(mkey);
     
     // do nothing
    }
   
   virtual void upLeft(Point point,MouseKey mkey)
    {
     Used(point);
     Used(mkey);
     
     // do nothing
    }
 
   virtual void dclickLeft(Point point,MouseKey mkey)
    {
     Used(point);
     Used(mkey);
     
     // do nothing
    }
   
   virtual void clickRight(Point point,MouseKey mkey)
    {
     Used(point);
     Used(mkey);
     
     // do nothing
    }
   
   virtual void upRight(Point point,MouseKey mkey)
    {
     Used(point);
     Used(mkey);
     
     // do nothing
    }
   
   virtual void dclickRight(Point point,MouseKey mkey)
    {
     Used(point);
     Used(mkey);
     
     // do nothing
    }
   
   virtual void move(Point point,MouseKey mkey)
    {
     Used(point);
     Used(mkey);
     
     // do nothing
    }
   
   virtual void hover(Point point,MouseKey mkey)
    {
     Used(point);
     Used(mkey);
     
     // do nothing
    }
   
   virtual void leave()
    {
     // do nothing
    }
   
   virtual void wheel(Point point,MouseKey mkey,Coord delta)
    {
     Used(point);
     Used(mkey);
     Used(delta);
     
     // do nothing
    }
 
   virtual MouseShape getMouseShape(Point point)
    {
     Used(point);
     
     return Mouse_Arrow;
    }
 };

/* class DragWindow */

class DragWindow : public FrameWindow
 {
  public:
  
   struct Shape
    {
     struct Config
      {
       Coord frame_dxy =  9 ;
       Coord title_dy  = 30 ;
       
       Coord btn_dx    = 28 ;
       Coord btn_dy    = 26 ;
       
       Coord min_dy    =  3 ;
       Coord alert_dx  =  2 ;

       ColorName edge            =     Black ;
       ColorName frame           =    Silver ;
       ColorName accent          =      Gray ;
       ColorName accentHilight   =     Green ;
       ColorName accentDrag      =       Red ;
       
       ColorName active          = RGBColor(MedClr,MedClr,MaxClr) ;
       ColorName inactive        =    Silver ;
       
       ColorName btnFace         = SteelBlue ;
       ColorName btnFaceHilight  =     Green ;
       ColorName btnFaceClose    =   DarkRed ;
       ColorName btnEdge         =     Black ;
       ColorName btnPict         =     White ;
       ColorName btnStop         =       Red ;
       
       ColorName titleUp         =      Gray ;
       ColorName titleDown       =      Snow ;
       
       ColorName titleActiveUp   = RGBColor(0,0,MedClr) ;
       ColorName titleActiveDown = RGBColor(200,200,MaxClr) ;
       
       ColorName alert           =       Red ;
       ColorName noAlert         =    Silver ;
       ColorName closeAlert      =      Blue ;
       
       ColorName title           =     Black ;
       
       Font title_font;
       
       Config() {}
       
       Signal<> update;
      };
     
     Config &cfg;

     Pane dragUpLeft;
     Pane dragLeft;
     Pane dragDownLeft;
     Pane dragDown;
     Pane dragDownRight;
     Pane dragRight;
     Pane dragUpRight;
     Pane dragBar;
     
     Pane title;
     Pane btnAlert;
     Pane btnMin;
     Pane btnMax;
     Pane btnClose;
     
     Pane client;
     
     bool has_focus = false ;
     bool max_button = true ;
     
     DragType drag_type = DragType::None ;
     DragType hilight = DragType::None ;
     AlertType alert_type = AlertType::No ;
     
     String title_string;
     
     explicit Shape(Config &cfg_) : cfg(cfg_) {}
     
     void layout(Point size);
     
     class DrawArt;
     
     void draw(FrameBuf<DesktopColor> buf) const;
     
     DragType dragTest(Point point) const;
    };
  
  private: 
   
   Shape shape;
   
   DragClient &client;
   
   Point drag_from;
   
   Point size;
   
   bool client_enter = false ;
   bool client_capture = false ;
   
  private: 
   
   void replace(Pane place,Point delta,DragType drag_type);
   
   void replace(Point delta,DragType drag_type);

   void startDrag(Point point,DragType drag_type);
   
   void dragTo_(Point point);
   
   void dragTo(Point point);
   
   void endDrag(Point point);
   
   bool forwardKey(VKey vkey,KeyMod kmod,unsigned repeat=1);
   
   bool forwardKeyUp(VKey vkey,KeyMod kmod,unsigned repeat=1);
   
  public:
  
   DragWindow(Desktop *desktop,Shape::Config &cfg,DragClient &client);
   
   virtual ~DragWindow();
   
   // DeferInput
   
   class Input : DeferInput<DragWindow>
    {
      friend class DragWindow;
      
      explicit Input(DragWindow *window) : DeferInput<DragWindow>(window) {}
      
      ~Input() {}
      
     public:

      void redraw(bool do_layout=false) { try_post(&DragWindow::redraw,do_layout); }
    };
   
   Input input;
   
  private:
   
   // Signal connectors
   
   void updateConfig() { input.redraw(true); }
   
   SignalConnector<DragWindow> connector_updateConfig;

  public:
   
   // methods
   
   void createMain(CmdDisplay cmd_display,Point max_size,String title);
   
   void create(Pane pane,Point max_size,String title);
   
   void create(WinControl *parent,Pane pane,Point max_size,String title);
   
   void destroy() { win->destroy(); }
   
   void minimize();
   
   void maximize();
   
   void redraw(bool do_layout=false);
   
   unsigned getToken() { return win->getToken(); }
   
   void captureMouse();
   
   void releaseMouse();
   
   void setTitle(String title)
    {
     shape.title_string=title;
     
     redraw();
    }
   
   // base
   
   virtual void alive();
   
   virtual void dead();
   
   virtual void setSize(Point size,bool buf_dirty);
   
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
 };

} // namespace Video
} // namespace CCore
 
#endif
 

