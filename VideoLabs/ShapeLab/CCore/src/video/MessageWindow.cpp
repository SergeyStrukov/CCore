/* MessageWindow.cpp */ 
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
 
#include <CCore/inc/video/MessageWindow.h>
 
namespace CCore {
namespace Video {

void MessageSubWindow::knobOk_pressed()
 {
  finish.assert();
 }

MessageSubWindow::MessageSubWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),
   list(*this),
   
   showInfo(list,cfg.info_cfg.get()),
   knobOk(list,cfg.knob_cfg.get(),KnobShape::FaceOk),
   
   connector_knobOk_pressed(this,&MessageSubWindow::knobOk_pressed,knobOk.pressed)
 {
  list.insTop(knobOk,showInfo);
  
  list.enableTabFocus();
  list.enableClickFocus();
 }

MessageSubWindow::~MessageSubWindow()
 {
 }

 // methods

Point MessageSubWindow::getMinSize() const
 {
  Point size=showInfo.getMinSize();
  
  Coord space_dxy=+cfg.space_dxy;
  Coord knob_dxy=+cfg.knob_dxy;
  
  Coord delta=knob_dxy+2*space_dxy;
  
  return Point(Max(knob_dxy,size.x),size.y+delta);
 }

void MessageSubWindow::setInfo(const Info &info)
 {
  showInfo.setInfo(info);
 }

 // drawing

void MessageSubWindow::layout()
 {
  Point size=getSize();
  
  Coord space_dxy=+cfg.space_dxy;
  Coord knob_dxy=+cfg.knob_dxy;
  
  Coord delta=knob_dxy+2*space_dxy;
  
  showInfo.setPlace(Pane(0,0,size.x,size.y-delta));
  
  knobOk.setPlace(Pane((size.x-knob_dxy)/2,size.y-knob_dxy-space_dxy,knob_dxy));
 }

void MessageSubWindow::draw(DrawBuf buf,bool drag_active) const
 {
  buf.erase(+cfg.back);
  
  list.draw(buf,drag_active);
 }

void MessageSubWindow::draw(DrawBuf buf,Pane pane,bool drag_active) const
 {
  buf.block(pane,+cfg.back);
  
  list.draw(buf,pane,drag_active);
 }

 // base

void MessageSubWindow::open()
 {
  list.open();
  
  list.focusTop();
 }

void MessageSubWindow::close()
 {
  list.close();
 }

 // keyboard

void MessageSubWindow::gainFocus()
 {
  list.gainFocus();
 }

void MessageSubWindow::looseFocus()
 {
  list.looseFocus();
 }

 // mouse

void MessageSubWindow::looseCapture()
 {
  list.looseCapture();
 }

MouseShape MessageSubWindow::getMouseShape(Point point)
 {
  return list.getMouseShape(point,Mouse_Arrow);
 }

 // user input

void MessageSubWindow::react(UserAction action)
 {
  list.react(action);
 }

/* class MessageWindow */

void MessageWindow::finish()
 {
  destroy();
 }
   
MessageWindow::MessageWindow(Desktop *desktop,const Config &cfg)
 : FixedWindow(desktop,cfg.frame_cfg.get()),
   pos_ratio(cfg.pos_ratio),
   sub_win(*this,cfg.msg_cfg.get()),
   client(sub_win),
   
   connector_finish(this,&MessageWindow::finish,sub_win.finish)
 {
  bindClient(client);
 }
   
MessageWindow::~MessageWindow()
 {
 }

Pane MessageWindow::getPane(StrLen title) const
 {
  Point size=getMinSize(title,sub_win.getMinSize());
  
  Point s=desktop->getScreenSize();
  
  size=Inf(size,s-s/4);
  
  return Pane((s.x-size.x)/2,+pos_ratio*(s.y-size.y),size);
 }

} // namespace Video
} // namespace CCore
 

