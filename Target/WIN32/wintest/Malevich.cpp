/* Malevich.cpp */ 
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
 
#include "Malevich.h"
 
namespace App {

/* class MalevichWindow */

void MalevichWindow::layout(Point size)
 {
  if( size>Point(2*DragWidth,2*DragWidth) )
    {
     int x1=DragWidth;
     int x2=size.x-DragWidth;
     int x3=size.x;
     
     int y1=DragWidth;
     int y2=size.y-DragWidth;
     int y3=size.y;
    
     dragUpLeft=Pane(Null,Point(x1,y1));
     dragLeft=Pane(Point(0,y1),Point(x1,y2));
     dragDownLeft=Pane(Point(0,y2),Point(x1,y3));
     
     dragDown=Pane(Point(x1,y2),Point(x2,y3));
     
     dragDownRight=Pane(Point(x2,y2),Point(x3,y3));
     dragRight=Pane(Point(x2,y1),Point(x3,y2));
     dragUpRight=Pane(Point(x2,0),Point(x3,y1));
     
     dragBar=Pane(Point(x1,0),Point(x2,y1));
     
     client=Pane(Point(x1,y1),Point(x2,y2));
     
     int yb=(DragWidth-BtnWidth)/2;
     
     if( size.x>=(3*BtnWidth+2*yb)+4*DragWidth )
       {
        int xb=(size.x-(3*BtnWidth+2*yb))/2; // >= 2*DragWidth 
        
        btnMin=Pane(xb,yb,BtnWidth,BtnWidth);
        btnMax=Pane(xb+BtnWidth+yb,yb,BtnWidth,BtnWidth);
        btnClose=Pane(xb+2*BtnWidth+2*yb,yb,BtnWidth,BtnWidth);
       }
     else
       {
        btnMin=Null;
        btnMax=Null;
        btnClose=Null;
       }
    }
  else
    {
     dragUpLeft=Null;
     dragLeft=Null;
     dragDownLeft=Null;
     
     dragDown=Null;
     
     dragDownRight=Pane(Null,size);
     dragRight=Null;
     dragUpRight=Null;
     
     dragBar=Null;
     
     client=Null;
     
     btnMin=Null;
     btnMax=Null;
     btnClose=Null;
    }
  
  marker=Extent(client.getBase()+Point(MarkerOff,MarkerOff),Point(MarkerLen,MarkerLen));
  
  if( !client.contains(marker) ) marker=Null;
  
  hover_marker=Extent(client.getBase()+Point(MarkerOff,MarkerOff+MarkerLen+MarkerDelta),Point(MarkerLen,MarkerLen));
  
  if( !client.contains(hover_marker) ) hover_marker=Null;
 }

void MalevichWindow::draw(FrameBuf<DesktopColor> buf)
 {
  if( drag_type )
    {
     buf.block(dragUpLeft,Olive);
     buf.block(dragLeft,Olive);
     buf.block(dragDownLeft,Olive);
     buf.block(dragDown,Olive);
     buf.block(dragDownRight,Olive);
     buf.block(dragRight,Olive);
     buf.block(dragUpRight,Olive);
     buf.block(dragBar,Olive);
    }
  else
    {
     buf.block(dragUpLeft,Silver);
     buf.block(dragLeft,Gray);
     buf.block(dragDownLeft,Silver);
     buf.block(dragDown,Gray);
     buf.block(dragDownRight,Silver);
     buf.block(dragRight,Gray);
     buf.block(dragUpRight,Silver);
     buf.block(dragBar,has_focus?Blue:Gray);
    }
  
  buf.block(btnMin,Green);
  buf.block(btnMax,max_button?Red:Yellow);
  buf.block(btnClose,Black);
  
  buf.cut(client).test();
  
  buf.block(marker,marker_on?Green:DarkGreen);
  
  DesktopColor hover_color;
  
  if( hover_on && buf.getPane().contains(hover_point) )
    {
     hover_color=buf.pixel(hover_point);
    }
  else
    {
     hover_color=Black;
    }
  
  buf.block(hover_marker,hover_color);
 }

void MalevichWindow::redraw()
 {
  draw(win->getDrawPlane());
  
  win->invalidate(1);
 }

void MalevichWindow::startDrag(Point point,DragType drag_type_)
 {
  win->captureMouse();
 
  Pane place=win->getPlacement();
  
  drag_type=drag_type_;
  drag_from=point+place.getBase();
  
  redraw();
 }

void MalevichWindow::dragTo_(Point point)
 {
  Pane place=win->getPlacement();
  Point delta=Diff(drag_from,point+place.getBase());
  
  switch( drag_type )
    {
     case Drag_UpLeft :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
       
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;
     
     case Drag_Left :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
      }
     break;
     
     case Drag_DownLeft :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
       
       place.dy+=delta.y;
      }
     break;
     
     case Drag_Down :
      {
       place.dy+=delta.y;
      }
     break;
     
     case Drag_DownRight :
      {
       place.dx+=delta.x;
       
       place.dy+=delta.y;
      }
     break;
     
     case Drag_Right :
      {
       place.dx+=delta.x;
      }
     break;
     
     case Drag_UpRight :
      {
       place.dx+=delta.x;
       
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;
     
     case Drag_Bar :
      {
       place.x+=delta.x;
       
       place.y+=delta.y;
      }
     break;
    }
  
  Point new_size(place.dx,place.dy);
  
  if( new_size>Null && new_size<=win->getMaxSize() )
    {
     win->move(place);
    }
 }

void MalevichWindow::dragTo(Point point)
 {
  if( win->getToken() ) return;
  
  dragTo_(point);
 }

void MalevichWindow::endDrag(Point point)
 {
  dragTo_(point);
  
  win->releaseMouse();
  
  drag_type=Drag_None;
  
  redraw();
 }

MalevichWindow::MalevichWindow(Desktop *desktop) 
 : FrameWindow(desktop) 
 {
 }

MalevichWindow::~MalevichWindow() 
 {
 }

void MalevichWindow::createMain(CmdDisplay cmd_display,Point max_size)
 {
  max_button=( cmd_display!=CmdDisplay_Maximized );
  
  win->createMain(max_size);
  
  win->display(cmd_display);
  win->update();
 }

void MalevichWindow::create(Pane pane,Point max_size)
 {
  win->create(pane,max_size);
  win->show();
 }

void MalevichWindow::create(WinControl *parent,Pane pane,Point max_size)
 {
  win->create(parent,pane,max_size);
  win->show();
 }

void MalevichWindow::tick()
 {
  if( win->isAlive() )
    {
     marker_on=!marker_on;
    
     redraw();
    }
 }

void MalevichWindow::gainFocus()
 {
  has_focus=true;
  
  redraw();
 }

void MalevichWindow::looseFocus()
 {
  has_focus=false;
  
  redraw();
 }

void MalevichWindow::alive()
 {
  win->trackMouseHover();
  win->trackMouseLeave();
 }

void MalevichWindow::setSize(Point size,bool)
 {
  layout(size);
  
  redraw();
 }

void MalevichWindow::clickLeft(Point point,MouseKey)
 {
  if( dragUpLeft.contains(point) )
    {
     startDrag(point,Drag_UpLeft);
    }
  else if( dragLeft.contains(point) )
    {
     startDrag(point,Drag_Left);
    }
  else if( dragDownLeft.contains(point) )
    {
     startDrag(point,Drag_DownLeft);
    }
  else if( dragDown.contains(point) )
    {
     startDrag(point,Drag_Down);
    }
  else if( dragDownRight.contains(point) )
    {
     startDrag(point,Drag_DownRight);
    }
  else if( dragRight.contains(point) )
    {
     startDrag(point,Drag_Right);
    }
  else if( dragUpRight.contains(point) )
    {
     startDrag(point,Drag_UpRight);
    }
  else if( dragBar.contains(point) )
    {
     if( btnMin.contains(point) )
       {
        win->display(CmdDisplay_Minimized);
       }
     else if( btnMax.contains(point) )
       {
        if( max_button )
          {
           max_button=false;
           
           win->display(CmdDisplay_Maximized);
          } 
        else
          {
           max_button=true;
           
           win->display(CmdDisplay_Restore);
          } 
        
        redraw();
       }
     else if( btnClose.contains(point) )
       {
        win->destroy();
       }
     else
       {
        startDrag(point,Drag_Bar);
       }
    }
  else
    {
     // do nothing
    }
 }

void MalevichWindow::upLeft(Point point,MouseKey)
 {
  if( drag_type )
    {
     endDrag(point);
    }
 }

void MalevichWindow::move(Point point,MouseKey mkey)
 {
  if( drag_type )
    {
     if( mkey&MouseKey_Left )
       dragTo(point);
     else
       endDrag(point);
    }
 }

void MalevichWindow::hover(Point point,MouseKey)
 {
  hover_point=point;
 
  hover_on=true;
  
  redraw();
 }

void MalevichWindow::leave()
 {
  hover_on=false;
  
  redraw();
 }

void MalevichWindow::setMouseShape(Point point)
 {
  if( dragUpLeft.contains(point) )
    {
     win->setMouseShape(Mouse_SizeUpLeft);
    }
  else if( dragLeft.contains(point) )
    {
     win->setMouseShape(Mouse_SizeLeftRight);
    }
  else if( dragDownLeft.contains(point) )
    {
     win->setMouseShape(Mouse_SizeUpRight);
    }
  else if( dragDown.contains(point) )
    {
     win->setMouseShape(Mouse_SizeUpDown);
    }
  else if( dragDownRight.contains(point) )
    {
     win->setMouseShape(Mouse_SizeUpLeft);
    }
  else if( dragRight.contains(point) )
    {
     win->setMouseShape(Mouse_SizeLeftRight);
    }
  else if( dragUpRight.contains(point) )
    {
     win->setMouseShape(Mouse_SizeUpRight);
    }
  else if( dragBar.contains(point) )
    {
     if( btnMin.contains(point) )
       {
        win->setMouseShape(Mouse_Arrow);
       }
     else if( btnMax.contains(point) )
       {
        win->setMouseShape(Mouse_Arrow);
       }
     else if( btnClose.contains(point) )
       {
        win->setMouseShape(Mouse_Arrow);
       }
     else
       {
        win->setMouseShape(Mouse_SizeAll);
       }
    }
  else
    {
     win->setMouseShape(Mouse_Arrow);
    }
 }

} // namespace App
 

