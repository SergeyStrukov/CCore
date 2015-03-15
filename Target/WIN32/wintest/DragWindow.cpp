/* DragWindow.cpp */ 
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
 
#include "DragWindow.h"
 
namespace CCore {
namespace Video {

/* class DragClient */

DragClient::DragClient()
 {
 }
   
DragClient::~DragClient()
 {
 }
   
void DragClient::layout(Point)
 {
 }
   
void DragClient::draw(FrameBuf<DesktopColor> buf,bool drag_active) const
 {
  buf.erase(drag_active?Gray:Black);
 }

/* class DragWindow::Shape */

void DragWindow::Shape::layout(Point size)
 {
  if( size>Point(2*cfg.drag_width,2*cfg.drag_width) )
    {
     int x1=cfg.drag_width;
     int x2=size.x-cfg.drag_width;
     int x3=size.x;
     
     int y1=cfg.drag_width;
     int y2=size.y-cfg.drag_width;
     int y3=size.y;
    
     dragUpLeft=Pane(Point(0,0),Point(x1,y1));
     dragLeft=Pane(Point(0,y1),Point(x1,y2));
     dragDownLeft=Pane(Point(0,y2),Point(x1,y3));
     
     dragDown=Pane(Point(x1,y2),Point(x2,y3));
     
     dragDownRight=Pane(Point(x2,y2),Point(x3,y3));
     dragRight=Pane(Point(x2,y1),Point(x3,y2));
     dragUpRight=Pane(Point(x2,0),Point(x3,y1));
     
     dragBar=Pane(Point(x1,0),Point(x2,y1));
     
     client=Pane(Point(x1,y1),Point(x2,y2));
     
     int yb=(cfg.drag_width-cfg.btn_width)/2;
     
     if( size.x>=(3*cfg.btn_width+2*yb)+4*cfg.drag_width )
       {
        int xb=(size.x-(3*cfg.btn_width+2*yb))/2; // >= 2*cfg.drag_width 
        
        btnMin=Pane(xb,yb,cfg.btn_width,cfg.btn_width);
        btnMax=Pane(xb+cfg.btn_width+yb,yb,cfg.btn_width,cfg.btn_width);
        btnClose=Pane(xb+2*cfg.btn_width+2*yb,yb,cfg.btn_width,cfg.btn_width);
       }
     else
       {
        btnMin=Empty;
        btnMax=Empty;
        btnClose=Empty;
       }
    }
  else
    {
     dragUpLeft=Empty;
     dragLeft=Empty;
     dragDownLeft=Empty;
     
     dragDown=Empty;
     
     dragDownRight=Pane(Point(0,0),size);
     dragRight=Empty;
     dragUpRight=Empty;
     
     dragBar=Empty;
     
     client=Empty;
     
     btnMin=Empty;
     btnMax=Empty;
     btnClose=Empty;
    }
 }

void DragWindow::Shape::draw(FrameBuf<DesktopColor> buf) const
 {
  if( drag_type!=DragType::None )
    {
     buf.block(dragUpLeft,cfg.dragOn);
     buf.block(dragLeft,cfg.dragOn);
     buf.block(dragDownLeft,cfg.dragOn);
     buf.block(dragDown,cfg.dragOn);
     buf.block(dragDownRight,cfg.dragOn);
     buf.block(dragRight,cfg.dragOn);
     buf.block(dragUpRight,cfg.dragOn);
     
     buf.block(dragBar,cfg.dragOn);
    }
  else
    {
     buf.block(dragUpLeft,(hilight==DragType::UpLeft)?cfg.hdragCorner:cfg.dragCorner);
     buf.block(dragLeft,(hilight==DragType::Left)?cfg.hdragEdge:cfg.dragEdge);
     buf.block(dragDownLeft,(hilight==DragType::DownLeft)?cfg.hdragCorner:cfg.dragCorner);
     buf.block(dragDown,(hilight==DragType::Down)?cfg.hdragEdge:cfg.dragEdge);
     buf.block(dragDownRight,(hilight==DragType::DownRight)?cfg.hdragCorner:cfg.dragCorner);
     buf.block(dragRight,(hilight==DragType::Right)?cfg.hdragEdge:cfg.dragEdge);
     buf.block(dragUpRight,(hilight==DragType::UpRight)?cfg.hdragCorner:cfg.dragCorner);
     
     buf.block(dragBar,has_focus?cfg.dragActive:cfg.dragPassive);
    }
  
  buf.block(btnMin,(hilight==DragType::Min)?cfg.hbtnMin:cfg.btnMin);
  buf.block(btnMax,(hilight==DragType::Max)?(max_button?cfg.hbtnMax:cfg.hbtnRestore):(max_button?cfg.btnMax:cfg.btnRestore));
  buf.block(btnClose,(hilight==DragType::Close)?cfg.hbtnClose:cfg.btnClose);
 }

DragType DragWindow::Shape::dragTest(Point point) const
 {
  if( dragUp.contains(point) ) return DragType::Up;
  
  if( dragUpLeft.contains(point) ) return DragType::UpLeft;

  if( dragLeft.contains(point) ) return DragType::Left;
  
  if( dragDownLeft.contains(point) ) return DragType::DownLeft;
  
  if( dragDown.contains(point) ) return DragType::Down;
  
  if( dragDownRight.contains(point) ) return DragType::DownRight;
  
  if( dragRight.contains(point) ) return DragType::Right;
  
  if( dragUpRight.contains(point) ) return DragType::UpRight;
  
  if( dragBar.contains(point) ) 
    {
     if( btnMin.contains(point) ) return DragType::Min;
    
     if( btnMax.contains(point) ) return DragType::Max;
    
     if( btnClose.contains(point) ) return DragType::Close;
     
     return DragType::Bar;
    }
  
  return DragType::None;
 }

/* class DragWindow */

void DragWindow::replace(Pane place,Point delta,DragType drag_type)
 {
  DragPane(place,delta,drag_type);
  
  Point new_size(place.dx,place.dy);
  
  if( new_size>Null && new_size<=win->getMaxSize() ) win->move(place);
 }

void DragWindow::replace(Point delta,DragType drag_type)
 {
  Pane place=win->getPlacement();

  replace(place,delta,drag_type);
 }

void DragWindow::startDrag(Point point,DragType drag_type)
 {
  win->captureMouse();
 
  Pane place=win->getPlacement();
  
  shape.drag_type=drag_type;
  
  drag_from=point+place.getBase();
  
  redraw();
 }

void DragWindow::dragTo_(Point point)
 {
  Pane place=win->getPlacement();
  Point delta=Diff(drag_from,point+place.getBase());
  
  replace(place,delta,shape.drag_type);
 }

void DragWindow::dragTo(Point point)
 {
  if( win->getToken() ) return;
  
  dragTo_(point);
 }

void DragWindow::endDrag(Point point)
 {
  dragTo_(point);
  
  win->releaseMouse();
  
  shape.drag_type=DragType::None;
  
  redraw();
 }

DragWindow::DragWindow(Desktop *desktop,DragClient &client_)
 : FrameWindow(desktop),
   client(client_)
 {
  client_.win=this;
 }

DragWindow::DragWindow(Desktop *desktop,const Shape::Config &cfg,DragClient &client_)
 : FrameWindow(desktop),
   shape(cfg),
   client(client_)
 {
  client_.win=this;
 }

DragWindow::~DragWindow()
 {
 }

void DragWindow::createMain(CmdDisplay cmd_display,Point max_size)
 {
  shape.max_button=( cmd_display!=CmdDisplay_Maximized );
  
  win->createMain(max_size);
  
  win->display(cmd_display);
  win->update();
 }

void DragWindow::create(Pane pane,Point max_size)
 {
  win->create(pane,max_size);
  win->show();
 }

void DragWindow::create(WinControl *parent,Pane pane,Point max_size)
 {
  win->create(parent,pane,max_size);
  win->show();
 }

void DragWindow::minimized()
 {
  win->display(CmdDisplay_Minimized);
 }

void DragWindow::maximized()
 {
  if( shape.max_button )
    {
     shape.max_button=false;
     
     win->display(CmdDisplay_Maximized);
    } 
  else
    {
     shape.max_button=true;
     
     win->display(CmdDisplay_Restore);
    } 
  
  redraw();
 }

void DragWindow::redraw()
 {
  FrameBuf<DesktopColor> buf(win->getDrawPlane());
  
  if( !(size<=buf.getSize()) ) 
    {
     buf.erase(Black);
    
     return;
    }
  
  shape.draw(buf);
  
  client.draw(buf.cut(shape.client),(bool)shape.drag_type);
  
  win->invalidate(1);
 }

void DragWindow::gainFocus()
 {
  shape.has_focus=true;
  
  redraw();
 }

void DragWindow::looseFocus()
 {
  shape.has_focus=false;
  
  redraw();
 }

void DragWindow::alive()
 {
  win->trackMouseHover();
  win->trackMouseLeave();
 }

void DragWindow::setSize(Point size_,bool)
 {
  if( size==size_ ) return;
  
  size=size_;
  
  shape.layout(size_);
  
  client.layout(shape.client.getSize());
  
  redraw();
 }

void DragWindow::key(VKey vkey,KeyMod kmod)
 {
  if( kmod&KeyMod_Alt )
    {
     switch( vkey )
       {
        case VKey_Left  : replace(Point(-1,0),(kmod&KeyMod_Shift)?DragType::Right:DragType::Bar); break;
        
        case VKey_Right : replace(Point(1,0),(kmod&KeyMod_Shift)?DragType::Right:DragType::Bar); break;
        
        case VKey_Up    : replace(Point(0,-1),(kmod&KeyMod_Shift)?DragType::Down:DragType::Bar); break;
        
        case VKey_Down  : replace(Point(0,1),(kmod&KeyMod_Shift)?DragType::Down:DragType::Bar); break;
        
        case VKey_F2    : minimized(); break;
        
        case VKey_F3    : maximized(); break;
        
        case VKey_F4    : destroy(); break; 
       }
    }
 }

void DragWindow::clickLeft(Point point,MouseKey)
 {
  switch( auto drag_type=shape.dragTest(point) )
    {
     case DragType::None : break;
   
     case DragType::Min   : minimized(); break;
     
     case DragType::Max   : maximized(); break;
     
     case DragType::Close : destroy(); break;
     
     default: if( !(bool)shape.drag_type ) startDrag(point,drag_type);
    }
 }

void DragWindow::upLeft(Point point,MouseKey)
 {
  if( (bool)shape.drag_type )
    {
     endDrag(point);
    }
 }

void DragWindow::move(Point point,MouseKey mkey)
 {
  if( (bool)shape.drag_type )
    {
     if( mkey&MouseKey_Left )
       dragTo(point);
     else
       endDrag(point);
    }
  
  auto drag_type=shape.dragTest(point);
  
  if( drag_type==DragType::Bar ) drag_type=DragType::None;
  
  if( drag_type!=shape.hilight )
    {
     shape.hilight=drag_type;
     
     redraw();
    }
 }

void DragWindow::leave()
 {
  if( (bool)shape.hilight )
    {
     shape.hilight=DragType::None;
     
     redraw();
    }
 }

void DragWindow::setMouseShape(Point point)
 {
  switch( shape.dragTest(point) )
    {
     case DragType::Up        : win->setMouseShape(Mouse_SizeUpDown); break;
      
     case DragType::UpLeft    : win->setMouseShape(Mouse_SizeUpLeft); break;

     case DragType::Left      : win->setMouseShape(Mouse_SizeLeftRight); break;
     
     case DragType::DownLeft  : win->setMouseShape(Mouse_SizeUpRight); break;
     
     case DragType::Down      : win->setMouseShape(Mouse_SizeUpDown); break;
     
     case DragType::DownRight : win->setMouseShape(Mouse_SizeUpLeft); break;
     
     case DragType::Right     : win->setMouseShape(Mouse_SizeLeftRight); break;
     
     case DragType::UpRight   : win->setMouseShape(Mouse_SizeUpRight); break;
     
     case DragType::Min       : 
     case DragType::Max       : win->setMouseShape(Mouse_Hand); break;
     
     case DragType::Close     : win->setMouseShape(Mouse_Stop); break;
      
     case DragType::Bar       : win->setMouseShape(Mouse_SizeAll); break;
     
     default: win->setMouseShape(Mouse_Arrow);
    }
 }

} // namespace Video
} // namespace CCore
 

