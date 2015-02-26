/* Malevich.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_Malevich_h
#define App_Malevich_h
 
#include <CCore/inc/video/Desktop.h>
#include <CCore/inc/video/FrameBuf.h>

namespace App {

/* using */ 

using namespace CCore;
using namespace CCore::Video;

/* classes */

class MalevichWindow;

/* class MalevichWindow */

class MalevichWindow : public FrameWindow
 {
   static const int DragWidth = 20 ;
   static const int BtnWidth  = 16 ;
  
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
   
   enum DragType
    {
     Drag_None,
     
     Drag_UpLeft,
     Drag_Left,
     Drag_DownLeft,
     Drag_Down,
     Drag_DownRight,
     Drag_Right,
     Drag_UpRight,
     Drag_Bar
    };
   
   DragType drag_type = Drag_None ;
   Point drag_from;

  private: 
   
   void layout(Point size);
  
   void draw(FrameBuf<DesktopColor> buf);
   
   void redraw();

   void startDrag(Point point,DragType drag_type);
   
   void dragTo_(Point point);
   
   void dragTo(Point point);
   
   void endDrag(Point point);
   
  public:
  
   MalevichWindow();
   
   virtual ~MalevichWindow();
   
   WinControl * getControl() { return win.getPtr(); }
   
   void createMain(CmdDisplay cmd_display);
   
   void create(Pane pane);
   
   void create(WinControl *parent,Pane pane);
   
   virtual void gainFocus();
   
   virtual void looseFocus();
   
   virtual void setSize(Point size,bool buf_dirty);
   
   virtual void clickLeft(Point point,MouseKey mkey);
   
   virtual void upLeft(Point point,MouseKey mkey);
 
   virtual void move(Point point,MouseKey mkey);
   
   virtual void setMouseShape(Point point);
 };

} // namespace App
 
#endif
 

