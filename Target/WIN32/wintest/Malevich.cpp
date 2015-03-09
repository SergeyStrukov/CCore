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

/* struct MalevichShape */

void MalevichShape::layout(Point size)
 {
  if( size>Point(2*DragWidth,2*DragWidth) )
    {
     int x1=DragWidth;
     int x2=size.x-DragWidth;
     int x3=size.x;
     
     int y1=DragWidth;
     int y2=size.y-DragWidth;
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
  
  marker=Extent(client.getBase()+Point(MarkerOff,MarkerOff),Point(MarkerLen,MarkerLen));
  
  if( !client.contains(marker) ) marker=Empty;
  
  hover_marker=Extent(client.getBase()+Point(MarkerOff,MarkerOff+MarkerLen+MarkerDelta),Point(MarkerLen,MarkerLen));
  
  if( !client.contains(hover_marker) ) hover_marker=Empty;
 }

void MalevichShape::draw(FrameBuf<DesktopColor> buf) const
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

auto MalevichShape::dragTest(Point point) const -> DragType
 {
  if( dragUpLeft.contains(point) ) return Drag_UpLeft;

  if( dragLeft.contains(point) ) return Drag_Left;
  
  if( dragDownLeft.contains(point) ) return Drag_DownLeft;
  
  if( dragDown.contains(point) ) return Drag_Down;
  
  if( dragDownRight.contains(point) ) return Drag_DownRight;
  
  if( dragRight.contains(point) ) return Drag_Right;
  
  if( dragUpRight.contains(point) ) return Drag_UpRight;
  
  if( dragBar.contains(point) ) return Drag_Bar;
  
  return Drag_None;
 }

auto MalevichShape::hitTest(Point point) const -> HitType
 {
  if( btnMin.contains(point) ) return Hit_Min;
  
  if( btnMax.contains(point) ) return Hit_Max;
  
  if( btnClose.contains(point) ) return Hit_Close;
  
  return Hit_None;
 }

/* class MalevichWindow */

void MalevichWindow::redraw()
 {
  shape.draw(win->getDrawPlane());
  
  win->invalidate(1);
 }

void MalevichWindow::startDrag(Point point,MalevichShape::DragType drag_type)
 {
  win->captureMouse();
 
  Pane place=win->getPlacement();
  
  shape.drag_type=drag_type;
  
  drag_from=point+place.getBase();
  
  redraw();
 }

void MalevichWindow::dragTo_(Point point)
 {
  Pane place=win->getPlacement();
  Point delta=Diff(drag_from,point+place.getBase());
  
  switch( shape.drag_type )
    {
     case MalevichShape::Drag_UpLeft :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
       
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;
     
     case MalevichShape::Drag_Left :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
      }
     break;
     
     case MalevichShape::Drag_DownLeft :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
       
       place.dy+=delta.y;
      }
     break;
     
     case MalevichShape::Drag_Down :
      {
       place.dy+=delta.y;
      }
     break;
     
     case MalevichShape::Drag_DownRight :
      {
       place.dx+=delta.x;
       
       place.dy+=delta.y;
      }
     break;
     
     case MalevichShape::Drag_Right :
      {
       place.dx+=delta.x;
      }
     break;
     
     case MalevichShape::Drag_UpRight :
      {
       place.dx+=delta.x;
       
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;
     
     case MalevichShape::Drag_Bar :
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
  
  shape.drag_type=MalevichShape::Drag_None;
  
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
  shape.max_button=( cmd_display!=CmdDisplay_Maximized );
  
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
     shape.marker_on=!shape.marker_on;
    
     redraw();
    }
 }

void MalevichWindow::gainFocus()
 {
  shape.has_focus=true;
  
  redraw();
 }

void MalevichWindow::looseFocus()
 {
  shape.has_focus=false;
  
  redraw();
 }

void MalevichWindow::alive()
 {
  win->trackMouseHover();
  win->trackMouseLeave();
 }

void MalevichWindow::setSize(Point size,bool)
 {
  shape.layout(size);
  
  redraw();
 }

void MalevichWindow::clickLeft(Point point,MouseKey)
 {
  if( auto drag_type=shape.dragTest(point) )
    {
     if( drag_type==MalevichShape::Drag_Bar )
       {
        switch( shape.hitTest(point) )
          {
           case MalevichShape::Hit_Min :
            {
             win->display(CmdDisplay_Minimized);
            }
           break;
           
           case MalevichShape::Hit_Max :
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
           break;
           
           case MalevichShape::Hit_Close :
            {
             win->destroy();
            }
           break;
           
           default:
            {
             startDrag(point,drag_type);
            }
          }
       }
     else
       {
        startDrag(point,drag_type);
       }
    }
 }

void MalevichWindow::upLeft(Point point,MouseKey)
 {
  if( shape.drag_type )
    {
     endDrag(point);
    }
 }

void MalevichWindow::move(Point point,MouseKey mkey)
 {
  if( shape.drag_type )
    {
     if( mkey&MouseKey_Left )
       dragTo(point);
     else
       endDrag(point);
    }
 }

void MalevichWindow::hover(Point point,MouseKey)
 {
  shape.hover_point=point;
 
  shape.hover_on=true;
  
  redraw();
 }

void MalevichWindow::leave()
 {
  shape.hover_on=false;
  
  redraw();
 }

void MalevichWindow::setMouseShape(Point point)
 {
  switch( shape.dragTest(point) )
    {
     case MalevichShape::Drag_UpLeft    : win->setMouseShape(Mouse_SizeUpLeft); break;

     case MalevichShape::Drag_Left      : win->setMouseShape(Mouse_SizeLeftRight); break;
     
     case MalevichShape::Drag_DownLeft  : win->setMouseShape(Mouse_SizeUpRight); break;
     
     case MalevichShape::Drag_Down      : win->setMouseShape(Mouse_SizeUpDown); break;
     
     case MalevichShape::Drag_DownRight : win->setMouseShape(Mouse_SizeUpLeft); break;
     
     case MalevichShape::Drag_Right     : win->setMouseShape(Mouse_SizeLeftRight); break;
     
     case MalevichShape::Drag_UpRight   : win->setMouseShape(Mouse_SizeUpRight); break;
     
     case MalevichShape::Drag_Bar :
      {
       switch( shape.hitTest(point) )
         {
          case MalevichShape::Hit_Min :
           {
            win->setMouseShape(Mouse_Hand);
           }
          break;
          
          case MalevichShape::Hit_Max :
           {
            win->setMouseShape(Mouse_Hand);
           }
          break;
          
          case MalevichShape::Hit_Close :
           {
            win->setMouseShape(Mouse_Stop);
           }
          break;
          
          default:
           {
            win->setMouseShape(Mouse_SizeAll);
           }
         }
      }
     break;
     
     default: win->setMouseShape(Mouse_Arrow); break;
    }
 }

} // namespace App
 

