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
    face=KnobShape::FaceOk;
  
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
   kbtn(wlist,cfg.knob_cfg,KnobShape::FaceOk),
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

void TestDialog::align_x_changed(int new_id,int)
 {
  align_x=AlignX(new_id);
  
  redraw();
 }

void TestDialog::align_y_changed(int new_id,int)
 {
  align_y=AlignY(new_id);
  
  redraw();
 }

void TestDialog::setTextLim(Point point)
 {
  tlim=point;
  
  redraw();
 }

void TestDialog::setTextGiven(Point point)
 {
  tgiven=point-tbase;
  
  redraw();
 }

TestDialog::TestDialog(SubWindowHost &host)
 : SubWindow(host),
   wlist(*this),
   dlist(*this),
   
   contour_x(dlist,cfg.contour_cfg,String("Align X")),
   contour_y(dlist,cfg.contour_cfg,String("Align Y")),

   radio_x_Left(wlist,AlignX_Left,cfg.radio_cfg),
   radio_x_Center(wlist,AlignX_Center,cfg.radio_cfg),
   radio_x_Right(wlist,AlignX_Right,cfg.radio_cfg),
   radio_x_Given(wlist,AlignX_Given,cfg.radio_cfg),
   
   label_x_Left(dlist,cfg.label_cfg,String("Left"),AlignX_Left),
   label_x_Center(dlist,cfg.label_cfg,String("Center"),AlignX_Left),
   label_x_Right(dlist,cfg.label_cfg,String("Right"),AlignX_Left),
   label_x_Given(dlist,cfg.label_cfg,String("Given"),AlignX_Left),
   
   radio_y_Top(wlist,AlignY_Top,cfg.radio_cfg),
   radio_y_Center(wlist,AlignY_Center,cfg.radio_cfg),
   radio_y_Bottom(wlist,AlignY_Bottom,cfg.radio_cfg),
   radio_y_Given(wlist,AlignY_Given,cfg.radio_cfg),
   
   label_y_Top(dlist,cfg.label_cfg,String("Top"),AlignX_Left),
   label_y_Center(dlist,cfg.label_cfg,String("Center"),AlignX_Left),
   label_y_Bottom(dlist,cfg.label_cfg,String("Bottom"),AlignX_Left),
   label_y_Given(dlist,cfg.label_cfg,String("Given"),AlignX_Left),
   
   connector_align_x(this,&TestDialog::align_x_changed,group_x.changed),
   connector_align_y(this,&TestDialog::align_y_changed,group_y.changed)
 {
  wlist.insTop(radio_x_Left,radio_x_Center,radio_x_Right,radio_x_Given,radio_y_Top,radio_y_Center,radio_y_Bottom,radio_y_Given);
  
  group_x.add(radio_x_Left,radio_x_Center,radio_x_Right,radio_x_Given);
  group_y.add(radio_y_Top,radio_y_Center,radio_y_Bottom,radio_y_Given);
  
  wlist.enableTabFocus();
  wlist.enableClickFocus();
  
  dlist.insTop(contour_x,contour_y,label_x_Left,label_x_Center,label_x_Right,label_x_Given,label_y_Top,label_y_Center,label_y_Bottom,label_y_Given);
  
  tbase={50,180};
  tlim={300,210};
  tgiven={30,20};
 }
   
TestDialog::~TestDialog()
 {
 }
   
void TestDialog::layout()
 {
  contour_x.setPlace(Pane(10,10,130,135));
  
  radio_x_Left.setPlace(Pane(20,35,20));
  radio_x_Center.setPlace(Pane(20,60,20));
  radio_x_Right.setPlace(Pane(20,85,20));
  radio_x_Given.setPlace(Pane(20,110,20));
  
  label_x_Left.setPlace(Pane(45,35,100,20));
  label_x_Center.setPlace(Pane(45,60,100,20));
  label_x_Right.setPlace(Pane(45,85,100,20));
  label_x_Given.setPlace(Pane(45,110,100,20));
  
  Coord d=140;
  
  contour_y.setPlace(Pane(10+d,10,130,135));
  
  radio_y_Top.setPlace(Pane(20+d,35,20));
  radio_y_Center.setPlace(Pane(20+d,60,20));
  radio_y_Bottom.setPlace(Pane(20+d,85,20));
  radio_y_Given.setPlace(Pane(20+d,110,20));
  
  label_y_Top.setPlace(Pane(45+d,35,100,20));
  label_y_Center.setPlace(Pane(45+d,60,100,20));
  label_y_Bottom.setPlace(Pane(45+d,85,100,20));
  label_y_Given.setPlace(Pane(45+d,110,100,20));
 }

void TestDialog::draw(DrawBuf buf,bool drag_active) const
 {
  Smooth::DrawArt art(buf);
  
  art.erase(cfg.back);
  
  Pane pane=PaneBaseLim(tbase,tlim);
  
  MPane p(pane);
  
  art.loop(HalfNeg,Fraction(2),Red,p.getTopLeft(),p.getBottomLeft(),p.getBottomRight(),p.getTopRight());
  art.loop(HalfPos,Fraction(2),Black,p.getTopLeft(),p.getBottomLeft(),p.getBottomRight(),p.getTopRight());
  
  Font font;
  
  TextPlace place(align_x,align_y);
  
  place.x=tgiven.x;
  place.y=tgiven.y;
  
  font->text(buf,pane,place,"This"," is a text line",Blue);
  
  // draw lists
  
  dlist.draw(buf,drag_active);
  wlist.draw(buf,drag_active);
 }

 // base

void TestDialog::open()
 {
  wlist.open();
  dlist.open();
  
  wlist.focusTop();
 }

void TestDialog::close()
 {
  wlist.close();
  dlist.close();
 }

 // keyboard

void TestDialog::gainFocus()
 {
  wlist.gainFocus();
  dlist.gainFocus();
 }

void TestDialog::looseFocus()
 {
  wlist.looseFocus();
  dlist.looseFocus();
 }

 // mouse

void TestDialog::looseCapture()
 {
  wlist.looseCapture();
  dlist.looseCapture();
 }

MouseShape TestDialog::getMouseShape(Point point)
 {
  return wlist.getMouseShape(point);
 }

 // user input

void TestDialog::react(UserAction action)
 {
  wlist.react(action, [this] (UserAction action) { action.dispatch(*this); } );
 }

void TestDialog::react_LeftClick(Point point,MouseKey)
 {
  setTextLim(point);
 }

void TestDialog::react_RightClick(Point point,MouseKey)
 {
  setTextGiven(point);
 }

void TestDialog::react_Move(Point point,MouseKey mkey)
 {
  if( mkey&MouseKey_Left )
    {
     setTextLim(point);
    }
  else if( mkey&MouseKey_Right )
    {
     setTextGiven(point);
    }
 }

/* class ShapeLab2 */

void ShapeLab2::btn1_pressed()
 {
  progress.setPos(progress.getPos()+5);
  
  progress.ping();
 }

void ShapeLab2::btn2_pressed()
 {
  const char *str="This is a test information.\nThe second line.\nThe end of information.";
  
  //const char *str="Some error";
  
  msg_window.setInfo(InfoFromString(str));
  
  msg_window.create(String("Test message"));
  
#if 0
  
  if( dialog.isDead() )
    {
     Pane pane(50,50,1000,800);
    
     dialog.create(getFrame()->getHost(),pane,String("Test dialog"));
     
     //btn2.disable();
     
     disableFrameReact();
     
     //getFrame()->getHost()->enableUserInput(false);
    }
  
#endif  
 }

void ShapeLab2::dialog_destroyed()
 {
  //btn2.enable();
  
  enableFrameReact();
  
  //getFrame()->getHost()->enableUserInput(true);
 }

void ShapeLab2::msg_destroyed()
 {
  text.printf("button #;",msg_window.getButtonId());
 }

static const char * TestStr="This is a test string\rthe second line of the test\nthe third line\r\nand the last line.";

ShapeLab2::ShapeLab2(SubWindowHost &host)
 : SubWindow(host),
   
   wlist(*this),
   dlist(*this),
   
   progress(dlist,cfg.progress_cfg),
   btn1(wlist,cfg.knob_cfg,KnobShape::FacePlus),
   btn2(wlist,cfg.btn_cfg,String("Test dialog")),
   
   info(TestStr),
   
   infoframe(dlist,cfg.contour_cfg),
   infow(wlist,cfg.info_cfg,info),
   
   text(dlist,cfg.text_cfg,AlignX_Left),
   
   dialog(host.getFrame()->getDesktop(),cfg.dialog_cfg),
   test(dialog),
   dialog_client(test),
   
   msg_window(host.getFrame()->getDesktop(),cfg.msg_cfg),
   
   connector_btn1_pressed(this,&ShapeLab2::btn1_pressed,btn1.pressed),
   connector_btn2_pressed(this,&ShapeLab2::btn2_pressed,btn2.pressed),
   connector_dialog_destroyed(this,&ShapeLab2::dialog_destroyed,dialog.destroyed),
   connector_msg_destroyed(this,&ShapeLab2::msg_destroyed,msg_window.destroyed)
 {
  wlist.insTop(btn1,btn2,infow);
  dlist.insTop(progress,infoframe,text);
  
  wlist.enableTabFocus();
  
  progress.setTotal(100);
  
  dialog.bindClient(dialog_client);
  
#if 0  
  
  msg_window.add(String("Yes"),Button_Yes)
            .add(String("No"),Button_No)
            .add(String("Cancel"),Button_Cancel);
  
#endif  
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
  
  infoframe.setPlace(Pane(10,200,200,70));
  
  infow.setPlace(infoframe.getInner());
  
  text.setPlace(Pane(10,300,200,30));
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


