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

namespace CCore {
namespace Video {

/* class WinList */

SubWindow * WinList::find(Point point) const
 {
  for(auto cur=list.start(); +cur ;++cur) if( cur->place.contains(point) ) return cur.ptr;
  
  return 0;
 }

SubWindow * WinList::pick(Point point) const
 {
  if( capture ) return capture; 

  return find(point);
 }

 // methods

void WinList::insTop(SubWindow *sub_win)
 {
  list.ins_first(sub_win);
  
  if( is_opened ) sub_win->open();
 }

void WinList::insBottom(SubWindow *sub_win)
 {
  list.ins_last(sub_win);
  
  if( is_opened ) sub_win->open();
 }

void WinList::del(SubWindow *sub_win)
 {
  list.del(sub_win);
  
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

void WinList::moveTop(SubWindow *sub_win)
 {
  list.del(sub_win);
  list.ins_first(sub_win);
 }

void WinList::moveBottom(SubWindow *sub_win)
 {
  list.del(sub_win);
  list.ins_last(sub_win);
 }

 // draw

void WinList::draw(const DrawBuf &buf,bool drag_active) const
 {
  for(auto cur=list.start_rev(); +cur ;++cur) cur->forward_draw(buf,drag_active);
 }

void WinList::draw(const DrawBuf &buf,Pane pane,bool drag_active) const
 {
  for(auto cur=list.start_rev(); +cur ;++cur) cur->forward_draw(buf,pane,drag_active);
 }

 // SubWindowHost

FrameWindow * WinList::getFrame()
 {
  return parent.getFrame();
 }

Point WinList::getScreenOrigin()
 {
  return parent.getScreenOrigin();
 }

void WinList::redraw(Pane pane)
 {
  parent.redraw(pane);
 }

void WinList::setFocus(SubWindow *sub_win)
 {
  if( focus!=sub_win )
    {
     if( focus && has_focus ) focus->looseFocus();
    
     focus=sub_win;
    }
  
  parent.setFocus();
 }

void WinList::captureMouse(SubWindow *sub_win)
 {
  capture=sub_win;
  
  parent.captureMouse();
 }

void WinList::releaseMouse(SubWindow *sub_win)
 {
  if( sub_win==capture )
    {
     capture=0;
    
     parent.releaseMouse();
    }
 }

 // base

void WinList::open()
 {
  capture=0;
  enter=0;
  has_focus=false;
  is_opened=true;
  
  for(auto cur=list.start(); +cur ;++cur) cur->open();
 }

void WinList::close()
 {
  is_opened=false;
  
  for(auto cur=list.start(); +cur ;++cur) cur->close();
 }

 // keyboard

void WinList::gainFocus()
 {
  has_focus=true;
  
  if( focus ) focus->gainFocus();
 }

void WinList::looseFocus()
 {
  has_focus=false;
  
  if( focus ) focus->looseFocus();
 }

 // mouse

void WinList::looseCapture()
 {
  if( capture ) Replace_null(capture)->looseCapture();
 }

MouseShape WinList::getMouseShape(Point point,MouseShape def_shape)
 {
  if( SubWindow *sub_win=find(point) ) return sub_win->forward_getMouseShape(point);
  
  return def_shape;
 }

 // user input

void WinList::react(UserAction action)
 {
  react(action, [] (UserAction) {} );
 }

} // namespace Video
} // namespace CCore

