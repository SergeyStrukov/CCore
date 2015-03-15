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

#include "DrawArt.h"

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
  
  Min,
  Max,
  Close
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
   
   virtual void layout(Point size);
   
   virtual void draw(FrameBuf<DesktopColor> buf,bool drag_active) const;
 };

/* class DragWindow */

class DragWindow : public FrameWindow
 {
  public:
  
   struct Shape
    {
     struct Config
      {
       int drag_width   = 20 ;
       int btn_width    = 16 ;
       
       ColorName dragOn      =     Olive ;
       ColorName dragCorner  =    Silver ;
       ColorName dragEdge    =      Gray ;
       
       ColorName dragActive  =      Blue ;
       ColorName dragPassive =      Gray ;
       
       ColorName hdragCorner =     White ;
       ColorName hdragEdge   =     White ;
       
       ColorName btnMin      =     Green ;
       ColorName btnClose    =     Black ;
       ColorName btnMax      =       Red ;
       ColorName btnRestore  =    Yellow ;
       
       ColorName hbtnMin     =     White ;
       ColorName hbtnClose   =     White ;
       ColorName hbtnMax     =     White ;
       ColorName hbtnRestore =     White ;
       
       Config() {}
      };
     
     Config cfg;

     Pane dragUp;
     Pane dragUpLeft;
     Pane dragLeft;
     Pane dragDownLeft;
     Pane dragDown;
     Pane dragDownRight;
     Pane dragRight;
     Pane dragUpRight;
     Pane dragBar;
     
     Pane btnMin;
     Pane btnMax;
     Pane btnClose;
     
     Pane client;
     
     bool has_focus = false ;
     bool max_button = true ;
     
     DragType drag_type = DragType::None ;
     DragType hilight = DragType::None ;
     
     Shape() {}
     
     explicit Shape(const Config &cfg_) : cfg(cfg_) {}
     
     void layout(Point size);
     
     void draw(FrameBuf<DesktopColor> buf) const;
     
     DragType dragTest(Point point) const;
    };
  
  private: 
   
   Shape shape;
   
   DragClient &client;
   
   Point drag_from;
   
   Point size;

  private: 
   
   void replace(Pane place,Point delta,DragType drag_type);
   
   void replace(Point delta,DragType drag_type);

   void startDrag(Point point,DragType drag_type);
   
   void dragTo_(Point point);
   
   void dragTo(Point point);
   
   void endDrag(Point point);
   
  public:
  
   DragWindow(Desktop *desktop,DragClient &client);
   
   DragWindow(Desktop *desktop,const Shape::Config &cfg,DragClient &client);
   
   virtual ~DragWindow();
   
   // methods
   
   WinControl * getControl() { return win; }
   
   void createMain(CmdDisplay cmd_display,Point max_size);
   
   void create(Pane pane,Point max_size);
   
   void create(WinControl *parent,Pane pane,Point max_size);
   
   void destroy() { win->destroy(); }
   
   void minimized();
   
   void maximized();
   
   void redraw();
   
   // events
   
   virtual void gainFocus();
   
   virtual void looseFocus();
   
   virtual void alive();
   
   virtual void setSize(Point size,bool buf_dirty);
   
   virtual void key(VKey vkey,KeyMod kmod);
   
   virtual void clickLeft(Point point,MouseKey mkey);
   
   virtual void upLeft(Point point,MouseKey mkey);
 
   virtual void move(Point point,MouseKey mkey);
   
   virtual void leave();
   
   virtual void setMouseShape(Point point);
 };

} // namespace Video
} // namespace CCore
 
#endif
 

