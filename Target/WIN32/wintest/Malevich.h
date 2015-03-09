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

/* functions */

template <class E>
void DragPane(Pane &place,Point delta,E type)
 {
  switch( type )
    {
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

struct MalevichShape;

class MalevichWindow;

/* struct MalevichShape */

struct MalevichShape
 {
  static const int DragWidth   = 20 ;
  static const int BtnWidth    = 16 ;
  static const int MarkerOff   = 10 ;
  static const int MarkerLen   = 20 ;
  static const int MarkerDelta =  5 ;
 
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
  Pane marker;
  Pane hover_marker;
  
  bool has_focus = false ;
  bool max_button = true ;
  
  enum class DragType
   {
    None = 0,
    
    UpLeft,
    Left,
    DownLeft,
    Down,
    DownRight,
    Right,
    UpRight,
    Bar
   };
  
  enum class HitType
   {
    None = 0,
    
    Min,
    Max,
    Close
   };
  
  DragType drag_type = DragType::None ;
  
  bool marker_on = false ;
  
  Point hover_point;
  bool hover_on = false ;
  
  MalevichShape() {}
  
  void layout(Point size);
  
  void draw(FrameBuf<DesktopColor> buf) const;
  
  DragType dragTest(Point point) const;
  
  HitType hitTest(Point point) const;
 };

/* class MalevichWindow */

class MalevichWindow : public FrameWindow
 {
   MalevichShape shape;
   
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
   
   virtual void clickLeft(Point point,MouseKey mkey);
   
   virtual void upLeft(Point point,MouseKey mkey);
 
   virtual void move(Point point,MouseKey mkey);
   
   virtual void hover(Point point,MouseKey mkey);
   
   virtual void leave();
   
   virtual void setMouseShape(Point point);
 };

} // namespace App
 
#endif
 

