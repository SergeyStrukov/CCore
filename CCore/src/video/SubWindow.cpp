/* SubWindow.cpp */
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

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* class SubWindow */

SubWindow::~SubWindow()
 {
  if( list ) list->del(this);
 }

/* class WindowList */

SubWindow * WindowList::find(Point point) const
 {
  for(auto cur=list.start(); +cur ;++cur) if( cur->place.contains(point) ) return cur.ptr;
  
  return 0;
 }

SubWindow * WindowList::pick(Point point) const
 {
  if( capture ) return capture; 

  return find(point);
 }

WindowList::~WindowList()
 {
  for(auto cur=list.start(); +cur ;++cur) cur->list=0;
 }

 // methods

void WindowList::insTop(SubWindow *sub_win)
 {
  if( sub_win->list )
    {
     Printf(Exception,"CCore::Video::WindowList::insTop(...) : sub-window is already included in a list");
    }
  
  list.ins_first(sub_win);
  
  sub_win->list=this;
  
  if( is_opened ) sub_win->open();
 }

void WindowList::insBottom(SubWindow *sub_win)
 {
  if( sub_win->list )
    {
     Printf(Exception,"CCore::Video::WindowList::insBottom(...) : sub-window is already included in a list");
    }
  
  list.ins_last(sub_win);
  
  sub_win->list=this;
  
  if( is_opened ) sub_win->open();
 }

void WindowList::del(SubWindow *sub_win)
 {
  if( sub_win->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::del(...) : sub-window from another list");
    }
  
  list.del(sub_win);
  
  sub_win->list=0;
  
  if( sub_win==focus ) 
    {
     focus=0;
    }
  
  if( sub_win==capture )
    {
     capture=0;
   
     parent.releaseMouse();
    }
  
  if( sub_win==enter )
    {
     enter=0;
    }
  
  if( is_opened ) sub_win->close();
 }

void WindowList::moveTop(SubWindow *sub_win)
 {
  if( sub_win->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::moveTop(...) : sub-window from another list");
    }
  
  list.del(sub_win);
  list.ins_first(sub_win);
 }

void WindowList::moveBottom(SubWindow *sub_win)
 {
  if( sub_win->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::moveBottom(...) : sub-window from another list");
    }
  
  list.del(sub_win);
  list.ins_last(sub_win);
 }

 // focus

void WindowList::focusTop()
 {
  if( SubWindow *sub_win=list.first ) sub_win->setFocus();
 }

void WindowList::focusBottom()
 {
  if( SubWindow *sub_win=list.last ) sub_win->setFocus();
 }

void WindowList::focusNext()
 {
  if( focus )
    {
     if( SubWindow *sub_win=Algo::Link(focus).next )
       sub_win->setFocus();
     else
       focusTop();
    }
 }

void WindowList::focusPrev()
 {
  if( focus )
    {
     if( SubWindow *sub_win=Algo::Link(focus).prev )
       sub_win->setFocus();
     else
       focusBottom();
    }
 }

void WindowList::focusOn(Point point)
 {
  if( SubWindow *sub_win=find(point) ) sub_win->setFocus();
 }

 // draw

void WindowList::draw(const DrawBuf &buf,bool drag_active) const
 {
  for(auto cur=list.start_rev(); +cur ;++cur) cur->forward_draw(buf,drag_active);
 }

void WindowList::draw(const DrawBuf &buf,Pane pane,bool drag_active) const
 {
  for(auto cur=list.start_rev(); +cur ;++cur) cur->forward_draw(buf,pane,drag_active);
 }

 // SubWindowHost

FrameWindow * WindowList::getFrame()
 {
  return parent.getFrame();
 }

Point WindowList::getScreenOrigin()
 {
  return parent.getScreenOrigin();
 }

void WindowList::redraw(Pane pane)
 {
  parent.redraw(pane);
 }

void WindowList::setFocus(SubWindow *sub_win)
 {
  if( sub_win->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::setFocus(...) : sub-window from another list");
    }
  
  if( focus!=sub_win )
    {
     if( focus && has_focus ) focus->looseFocus();
    
     focus=sub_win;
    }
  
  parent.setFocus();
 }

void WindowList::captureMouse(SubWindow *sub_win)
 {
  if( sub_win->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::captureMouse(...) : sub-window from another list");
    }
  
  capture=sub_win;
  
  parent.captureMouse();
 }

void WindowList::releaseMouse(SubWindow *sub_win)
 {
  if( sub_win->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::releaseMouse(...) : sub-window from another list");
    }
  
  if( sub_win==capture )
    {
     capture=0;
    
     parent.releaseMouse();
    }
 }

 // base

void WindowList::open()
 {
  capture=0;
  enter=0;
  has_focus=false;
  is_opened=true;
  
  for(auto cur=list.start(); +cur ;++cur) cur->open();
 }

void WindowList::close()
 {
  is_opened=false;
  
  for(auto cur=list.start(); +cur ;++cur) cur->close();
 }

 // keyboard

void WindowList::gainFocus()
 {
  has_focus=true;
  
  if( focus ) focus->gainFocus();
 }

void WindowList::looseFocus()
 {
  has_focus=false;
  
  if( focus ) focus->looseFocus();
 }

 // mouse

void WindowList::looseCapture()
 {
  if( capture ) Replace_null(capture)->looseCapture();
 }

MouseShape WindowList::getMouseShape(Point point,MouseShape def_shape)
 {
  if( SubWindow *sub_win=find(point) ) return sub_win->forward_getMouseShape(point);
  
  return def_shape;
 }

 // user input

void WindowList::react(UserAction action)
 {
  react(action, [] (UserAction) {} );
 }

} // namespace Video
} // namespace CCore

