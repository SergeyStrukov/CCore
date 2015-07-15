/* ShapeLab.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ShapeLab 1.00
//
//  Tag: private
//
//  License: proprietary software, don't distribute!
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/ShapeLab.h>

#include <CCore/inc/video/SmoothDrawArt.h>
#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/Exception.h>

namespace App {

/* class ShapeLab */

void ShapeLab1::change_sw(bool on)
 {
  light.turn(on);
 }

void ShapeLab1::change_color(int id,int)
 {
  switch( id )
    {
     case 1 :
      {
       light.setFace(Green);
      }
     break;
     
     case 2 :
      {
       light.setFace(Red);
      }
     break;
     
     case 3 :
      {
       light.setFace(Blue);
      }
     break; 
    }
 }

void ShapeLab1::change_check(bool on)
 {
  xscroll.enable(on);
 }

void ShapeLab1::btn_pressed()
 {
  auto face=kbtn.getFace();
  
  if( face<KnobShape::FaceLeftLeft )
    face=KnobShape::FaceType(face+1);
  else
    face=KnobShape::FacePlus;
  
  kbtn.setFace(face);
 }

void ShapeLab1::scroll_changed(ulen pos)
 {
  text.printf("#;",pos);
 }

template <class T>
void ShapeLab1::setSize(T &obj,Point point)
 {
  Point p=point-size_base;
  
  if( p>=obj.getMinSize() )
    {
     obj.setPlace(Extent(obj.getPlace().getBase(),p));
     
     redraw();
    }
 }

void ShapeLab1::setSize(Point point)
 {
  Used(point);
  
  //setSize(kbtn,point);
 }

ShapeLab1::ShapeLab1(SubWindowHost &host)
 : SubWindow(host),
   
   wlist(*this),
   dlist(*this),
   
   sw(wlist,cfg.switch_cfg),
   
   radio1(wlist,1,cfg.radio_cfg),
   radio2(wlist,2,cfg.radio_cfg),
   radio3(wlist,3,cfg.radio_cfg),
   
   label1(dlist,cfg.label_cfg,String("Green"),AlignX_Left),
   label2(dlist,cfg.label_cfg,String("Red"),AlignX_Left),
   label3(dlist,cfg.label_cfg,String("Blue"),AlignX_Left),
   
   light(dlist,cfg.light_cfg),
   
   contour(dlist,cfg.contour_cfg),
   text_contour(dlist,cfg.text_contour_cfg,String("Title"),AlignX_Center),
   
   btn(wlist,cfg.btn_cfg,String("Next face")),
   text(dlist,cfg.text_cfg,String("Text"),AlignX_Left),
   kbtn(wlist,cfg.knob_cfg,KnobShape::FaceExclamation),
   check(wlist,cfg.check_cfg,true),
   xscroll(wlist,cfg.scroll_cfg),
   yscroll(wlist,cfg.scroll_cfg),
   
   connector_change_sw(this,&ShapeLab1::change_sw,sw.changed),
   connector_change_color(this,&ShapeLab1::change_color,group.changed),
   connector_change_check(this,&ShapeLab1::change_check,check.changed),
   connector_btn_pressed(this,&ShapeLab1::btn_pressed,btn.pressed),
   connector_scroll_changed(this,&ShapeLab1::scroll_changed,yscroll.changed)
 {
  wlist.insTop(sw,radio1,radio2,radio3,btn,kbtn,check,xscroll,yscroll);
  
  group.add(radio1,radio2,radio3);
  
  wlist.enableTabFocus();
  wlist.enableClickFocus();
  
  dlist.insTop(label1,label2,label3,light,contour,text_contour,text);

  xscroll.setRange(1000,100,20);
  yscroll.setRange(100,10,2);
 }

ShapeLab1::~ShapeLab1()
 {
 }

 // drawing

void ShapeLab1::layout()
 {
  sw.setPlace(Pane(20,20,30));
  
  radio1.setPlace(Pane(60,20,16));
  radio2.setPlace(Pane(60,40,16));
  radio3.setPlace(Pane(60,60,16));
  
  label1.setPlace(Pane(90,20-2,100,20));
  label2.setPlace(Pane(90,40-2,100,20));
  label3.setPlace(Pane(90,60-2,100,20));
  
  light.setPlace(Pane(200,20,30));
  
  contour.setPlace(Pane(300,20,200,200));
  text_contour.setPlace(Pane(520,20,200,200));
  
  btn.setPlace(Pane(20,220,150,30));
  text.setPlace(Pane(20,260,300,30));
  kbtn.setPlace(Pane(20,300,100));
  
  check.setPlace(Pane(20,450,16));
  xscroll.setPlace(Pane(20,480,500,20));
  yscroll.setPlace(Pane(750,20,20,500));

  size_base=Point(20,100);
 }

void ShapeLab1::draw(DrawBuf buf,bool drag_active) const
 {
  Smooth::DrawArt art(buf);
  
  art.erase(cfg.back);

  {
   MCoord len=cfg.len;
    
   art.path(cfg.width,Black,size_base+MPoint(len,0),size_base,size_base+MPoint(0,len));
  }
  
  dlist.draw(buf,drag_active);
  wlist.draw(buf,drag_active);
 }

 // base

void ShapeLab1::open()
 {
  wlist.open();
  
  wlist.focusTop();
 }

void ShapeLab1::close()
 {
  wlist.close();
 }

 // keyboard

void ShapeLab1::gainFocus()
 {
  wlist.gainFocus();
 }

void ShapeLab1::looseFocus()
 {
  wlist.looseFocus();
 }

 // mouse

void ShapeLab1::looseCapture()
 {
  wlist.looseCapture();
 }

MouseShape ShapeLab1::getMouseShape(Point point)
 {
  return wlist.getMouseShape(point);
 }

 // user input

void ShapeLab1::react(UserAction action)
 {
  wlist.react(action, [this] (UserAction action) { action.dispatch(*this); } );
 }

void ShapeLab1::react_LeftClick(Point point,MouseKey)
 {
  setSize(point);
 }

void ShapeLab1::react_Move(Point point,MouseKey mkey)
 {
  if( mkey&MouseKey_Left )
    {
     setSize(point);
    }
 }

/* class TestDialog */

TestDialog::TestDialog(SubWindowHost &host)
 : SubWindow(host)
 {
 }
   
TestDialog::~TestDialog()
 {
 }
   
void TestDialog::layout()
 {
  // do nothing
 }

void TestDialog::draw(DrawBuf buf,bool) const
 {
  buf.erase(Black);
 }

/* class ShapeLab2 */

void ShapeLab2::btn1_pressed()
 {
  progress.setPos(progress.getPos()+5);
  
  progress.ping();
 }

void ShapeLab2::btn2_pressed()
 {
  if( dialog.isDead() )
    {
     Pane pane(50,50,1000,800);
    
     dialog.create(getFrame()->getHost(),pane,String("Test dialog"));
     
     //btn2.disable();
     
     disableFrameReact();
     
     //getFrame()->getHost()->enableUserInput(false);
    }
 }

void ShapeLab2::dialog_destroyed()
 {
  //btn2.enable();
  
  enableFrameReact();
  
  //getFrame()->getHost()->enableUserInput(true);
 }

ShapeLab2::ShapeLab2(SubWindowHost &host)
 : SubWindow(host),
   
   wlist(*this),
   dlist(*this),
   
   progress(dlist,cfg.progress_cfg),
   btn1(wlist,cfg.knob_cfg,KnobShape::FacePlus),
   btn2(wlist,cfg.btn_cfg,String("Test dialog")),
   
   dialog(host.getFrame()->getDesktop(),cfg.dialog_cfg),
   test(dialog),
   dialog_client(test),
   
   connector_btn1_pressed(this,&ShapeLab2::btn1_pressed,btn1.pressed),
   connector_btn2_pressed(this,&ShapeLab2::btn2_pressed,btn2.pressed),
   connector_dialog_destroyed(this,&ShapeLab2::dialog_destroyed,dialog.destroyed)
 {
  wlist.insTop(btn1,btn2);
  dlist.insTop(progress);
  
  wlist.enableTabFocus();
  
  progress.setTotal(100);
  
  dialog.bindClient(dialog_client);
 }

ShapeLab2::~ShapeLab2()
 {
 }

 // drawing

void ShapeLab2::layout()
 {
  progress.setPlace(Pane(20,20,500,20));
  
  btn1.setPlace(Pane(20,50,40));
  btn2.setPlace(Pane(20,100,140,32));
 }

void ShapeLab2::draw(DrawBuf buf,bool drag_active) const
 {
  Smooth::DrawArt art(buf);
  
  art.erase(cfg.back);

  dlist.draw(buf,drag_active);
  wlist.draw(buf,drag_active);
 }

 // base

void ShapeLab2::open()
 {
  wlist.open();
  
  wlist.focusTop();
 }

void ShapeLab2::close()
 {
  wlist.close();
 }

 // keyboard

void ShapeLab2::gainFocus()
 {
  wlist.gainFocus();
 }

void ShapeLab2::looseFocus()
 {
  wlist.looseFocus();
 }

 // mouse

void ShapeLab2::looseCapture()
 {
  wlist.looseCapture();
 }

MouseShape ShapeLab2::getMouseShape(Point point)
 {
  return wlist.getMouseShape(point);
 }

 // user input

void ShapeLab2::react(UserAction action)
 {
  action.dispatch(*this); 
  
  wlist.react(action);
 }

void ShapeLab2::react_Key(VKey vkey,KeyMod kmod)
 {
  Used(kmod);
  
  switch( vkey )
    {
     case VKey_F12 :
      {
       Printf(Exception,"F12 is pressed -------------------------------");
      }
     break; 
    }
 }

} // namespace App


