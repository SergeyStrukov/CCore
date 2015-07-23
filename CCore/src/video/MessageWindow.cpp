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

void MessageSubWindow::Btn::pressed_id()
 {
  sub_win->finish.assert(btn_id);
 }

MessageSubWindow::Btn::Btn(SubWindowHost &host,const ButtonShape::Config &cfg,const String &name,int btn_id_,MessageSubWindow *sub_win_)
 : ButtonWindow(host,cfg,name),
   btn_id(btn_id_),
   sub_win(sub_win_),
   connector_pressed(this,&MessageSubWindow::Btn::pressed_id,pressed)
 {
 }

MessageSubWindow::Btn::~Btn()
 {
 }

void MessageSubWindow::knobOk_pressed()
 {
  finish.assert(Button_Ok);
 }

MessageSubWindow::MessageSubWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),
   list(*this),
   dlist(*this),
   
   showInfo(list,cfg.info_ctor.get()),
   dline(dlist,cfg.dline_ctor.get()),
   knobOk(list,cfg.knob_ctor.get(),KnobShape::FaceOk),
   
   btn_cfg(cfg.btn_ctor.get()),
   
   connector_knobOk_pressed(this,&MessageSubWindow::knobOk_pressed,knobOk.pressed)
 {
  dlist.insTop(dline);
  
  list.enableTabFocus();
  list.enableClickFocus();
 }

MessageSubWindow::~MessageSubWindow()
 {
 }

 // methods

Point MessageSubWindow::getMinSize() const
 {
  Coord space_dxy=+cfg.space_dxy;
  
  Point size=showInfo.getMinSize()+2*Point::Diag(space_dxy);
  
  if( ulen count=btn_list.getLen() )
    {
     Point btnSpace=+cfg.btnSpace;
    
     Point s;
   
     for(ulen ind=0; ind<count ;ind++) s=Sup(s,btn_list[ind]->getMinSize());
    
     s+=btnSpace;
     
     Coord delta=s.y+2*space_dxy;
     
     Coord total=Coord(count)*s.x+Coord(count+1)*space_dxy;
     
     return Point(Max(total,size.x),size.y+delta);
    }
  else
    {
     Coord knob_dxy=+cfg.knob_dxy;
     
     Coord delta=knob_dxy+2*space_dxy;
     
     return Point(Max(knob_dxy,size.x),size.y+delta);
    }
 }

MessageSubWindow & MessageSubWindow::setInfo(const Info &info)
 {
  showInfo.setInfo(info);
  
  return *this;
 }

MessageSubWindow & MessageSubWindow::add(const String &name,int btn_id)
 {
  OwnPtr<Btn> obj(new Btn(list,btn_cfg,name,btn_id,this));
  
  btn_list.append_swap(obj);
  
  return *this;
 }

 // drawing

void MessageSubWindow::layout()
 {
  Point size=getSize();
  
  Coord space_dxy=+cfg.space_dxy;
  
  if( ulen count=btn_count )
    {
     Point btnSpace=+cfg.btnSpace;
     
     Point s;
    
     for(ulen ind=0; ind<count ;ind++) s=Sup(s,btn_list[ind]->getMinSize());
     
     s+=btnSpace;
     
     Coord delta=s.y+2*space_dxy;
     
     showInfo.setPlace(Pane(0,0,size.x,size.y-delta).shrink(space_dxy));
     
     dline.setPlace(Pane(0,size.y-delta-space_dxy,size.x,2*space_dxy));
      
     Coord total=Coord(count)*s.x+Coord(count-1)*space_dxy;
     
     Point o((size.x-total)/2,size.y-s.y-space_dxy);
     Coord delta_x=s.x+space_dxy;
    
     for(ulen ind=0; ind<count ;ind++)
       {
        btn_list[ind]->setPlace(Pane(o,s));
        
        o.x+=delta_x;
       }
    }
  else
    {
     Coord knob_dxy=+cfg.knob_dxy;
     Coord delta=knob_dxy+2*space_dxy;
    
     showInfo.setPlace(Pane(0,0,size.x,size.y-delta).shrink(space_dxy));
    
     dline.setPlace(Pane(0,size.y-delta-space_dxy,size.x,2*space_dxy));
     
     knobOk.setPlace(Pane((size.x-knob_dxy)/2,size.y-knob_dxy-space_dxy,knob_dxy));
    }
 }

void MessageSubWindow::draw(DrawBuf buf,bool drag_active) const
 {
  buf.erase(+cfg.back);
  
  dlist.draw(buf,drag_active);
  list.draw(buf,drag_active);
 }

void MessageSubWindow::draw(DrawBuf buf,Pane pane,bool drag_active) const
 {
  buf.block(pane,+cfg.back);
  
  dlist.draw(buf,pane,drag_active);
  list.draw(buf,pane,drag_active);
 }

 // base

void MessageSubWindow::open()
 {
  list.delAll();
  
  btn_count=btn_list.getLen();
  
  if( btn_count )
    {
     btn_list.apply( [this] (OwnPtr<Btn> &obj) { list.insBottom(obj.getPtr()); } );
     
     list.insBottom(showInfo);
    }
  else
    {
     list.insTop(knobOk,showInfo);
    }
  
  list.open();
  
  list.focusTop();
  
  dlist.open();
 }

void MessageSubWindow::close()
 {
  list.close();
  dlist.close();
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

void MessageWindow::finish(int btn_id_)
 {
  btn_id=btn_id_;
  
  destroy();
 }
   
MessageWindow::MessageWindow(Desktop *desktop,const Config &cfg_)
 : FixedWindow(desktop,cfg_.frame_ctor.get()),
   cfg(cfg_),
   sub_win(*this,cfg.msg_ctor.get()),
   client(sub_win),
   
   connector_finish(this,&MessageWindow::finish,sub_win.finish)
 {
  bindClient(client);
 }
   
MessageWindow::~MessageWindow()
 {
 }

void MessageWindow::alive()
 {
  FixedWindow::alive();
  
  btn_id=Button_Cancel;
 }

Pane MessageWindow::getPane(StrLen title) const
 {
  Point size=getMinSize(title,sub_win.getMinSize());
  
  Point s=desktop->getScreenSize();
  
  size=Inf(size,s-s/4);
  
  return Pane((s.x-size.x)/2,+cfg.pos_ratio*(s.y-size.y),size);
 }

} // namespace Video
} // namespace CCore
 

