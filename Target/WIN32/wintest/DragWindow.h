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

/* classes */

class DragWindow;

/* class DragWindow */

class DragWindow : public FrameWindow
 {
   class Shape
    {
    };
  
   Shape shape;
   
   Point drag_from;

  private: 
   
   void redraw();

   void startDrag(Point point,MalevichShape::DragType drag_type);
   
   void dragTo_(Point point);
   
   void dragTo(Point point);
   
   void endDrag(Point point);
   
  public:
  
   explicit MalevichWindow(Desktop *desktop);
   
   virtual ~MalevichWindow();
   
   WinControl * getControl() { return win; }
   
   void createMain(CmdDisplay cmd_display,Point max_size);
   
   void create(Pane pane,Point max_size);
   
   void create(WinControl *parent,Pane pane,Point max_size);
   
   void destroy() { win->destroy(); }
   
   void tick();
   
   virtual void gainFocus();
   
   virtual void looseFocus();
   
   virtual void alive();
   
   virtual void setSize(Point size,bool buf_dirty);
   
   virtual void key(VKey vkey,KeyMod kmod);
   
   virtual void clickLeft(Point point,MouseKey mkey);
   
   virtual void upLeft(Point point,MouseKey mkey);
 
   virtual void move(Point point,MouseKey mkey);
   
   virtual void hover(Point point,MouseKey mkey);
   
   virtual void leave();
   
   virtual void setMouseShape(Point point);
 };

} // namespace Video
} // namespace CCore
 
#endif
 

