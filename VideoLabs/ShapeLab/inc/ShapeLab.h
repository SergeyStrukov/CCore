/* ShapeLab.h */
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

#ifndef ShapeLab_h
#define ShapeLab_h

#include <inc/Application.h>

#include <CCore/inc/video/WindowLib.h>
#include <CCore/inc/video/WindowLib2.h>
#include <CCore/inc/video/FixedWindow.h>

#include <CCore/inc/video/MessageWindow.h>

namespace App {

/* classes */

class ShapeLab1;

class ShapeLab2;

/* type ShapeLab */

using ShapeLab = ShapeLab2 ;

/* class ShapeLab1 */

class ShapeLab1 : public SubWindow
 {
   struct Config
    {
     MCoord width = Fraction(5,2) ;
     MCoord len = Fraction(100) ;
     
     VColor back = Wheat ;
     
     SwitchShape::Config switch_cfg;
     RadioShape::Config radio_cfg;
     LabelShape::Config label_cfg;
     LightShape::Config light_cfg;
     ButtonShape::Config btn_cfg;
     TextShape::Config text_cfg;
     KnobShape::Config knob_cfg;
     CheckShape::Config check_cfg;
     ScrollShape::Config scroll_cfg;
     ContourShape::Config contour_cfg;
     TextContourShape::Config text_contour_cfg;
     
     Config()
      {
      }
    };
  
   Config cfg;
   
   WindowList wlist;
   WindowList dlist;

   SwitchWindow sw;
   
   RadioWindow radio1;
   RadioWindow radio2;
   RadioWindow radio3;
   
   RadioGroup group;
   
   LabelWindow label1;
   LabelWindow label2;
   LabelWindow label3;
   
   LightWindow light;
   
   ContourWindow contour;
   TextContourWindow text_contour;
   
   ButtonWindow btn;
   TextWindow text;
   KnobWindow kbtn;
   CheckWindow check;
   XScrollWindow xscroll;
   YScrollWindow yscroll;
   
   Point size_base;
   
   SignalConnector<ShapeLab1,bool> connector_change_sw;
   SignalConnector<ShapeLab1,int,int> connector_change_color;
   SignalConnector<ShapeLab1,bool> connector_change_check;
   SignalConnector<ShapeLab1> connector_btn_pressed;
   SignalConnector<ShapeLab1,ulen> connector_scroll_changed;
   
  private: 

   void change_sw(bool on);
   
   void change_color(int id,int prev_id);
   
   void change_check(bool on);
   
   void btn_pressed();
   
   void scroll_changed(ulen pos);
   
   template <class T>
   void setSize(T &obj,Point point);
   
   void setSize(Point point);
   
  public:
 
   explicit ShapeLab1(SubWindowHost &host);
  
   virtual ~ShapeLab1();
   
   // drawing
   
   virtual void layout();
   
   virtual void draw(DrawBuf buf,bool drag_active) const;
   
   // base
   
   virtual void open();
   
   virtual void close();
   
   // keyboard
   
   void gainFocus();
   
   void looseFocus();
   
   // mouse
 
   virtual void looseCapture();
 
   virtual MouseShape getMouseShape(Point point);
   
   // user input
   
   virtual void react(UserAction action);
   
   void react_LeftClick(Point point,MouseKey mkey);
   
   void react_Move(Point point,MouseKey mkey);
 };

/* class TestDialog */

class TestDialog : public SubWindow
 {
   struct Config
    {
     VColor back = Silver ;
     
     TextContourShape::Config contour_cfg;
     RadioShape::Config radio_cfg;
     LabelShape::Config label_cfg;
     
     Config()
      {
      }
    };

   Config cfg;
   
   WindowList wlist;
   WindowList dlist;
   
   TextContourWindow contour_x;
   TextContourWindow contour_y;
   
   RadioGroup group_x;
   RadioGroup group_y;
   
   RadioWindow radio_x_Left;
   RadioWindow radio_x_Center;
   RadioWindow radio_x_Right;
   RadioWindow radio_x_Given;
   
   LabelWindow label_x_Left;
   LabelWindow label_x_Center;
   LabelWindow label_x_Right;
   LabelWindow label_x_Given;
   
   RadioWindow radio_y_Top;
   RadioWindow radio_y_Center;
   RadioWindow radio_y_Bottom;
   RadioWindow radio_y_Given;
   
   LabelWindow label_y_Top;
   LabelWindow label_y_Center;
   LabelWindow label_y_Bottom;
   LabelWindow label_y_Given;
   
   Point tbase;
   Point tlim;
   Point tgiven;
   
   AlignX align_x = AlignX_Left ;
   AlignY align_y = AlignY_Top ;
   
   SignalConnector<TestDialog,int,int> connector_align_x;
   SignalConnector<TestDialog,int,int> connector_align_y;
   
  private:
   
   void align_x_changed(int new_id,int prev_id);
   
   void align_y_changed(int new_id,int prev_id);
   
   void setTextLim(Point point);
   
   void setTextGiven(Point point);
   
  public:
  
   explicit TestDialog(SubWindowHost &host);
   
   virtual ~TestDialog();
   
   // drawing
   
   virtual void layout();
   
   virtual void draw(DrawBuf buf,bool drag_active) const;

   // base
   
   virtual void open();
   
   virtual void close();
   
   // keyboard
   
   void gainFocus();
   
   void looseFocus();
   
   // mouse
 
   virtual void looseCapture();
 
   virtual MouseShape getMouseShape(Point point);
   
   // user input
   
   virtual void react(UserAction action);
 
   void react_LeftClick(Point point,MouseKey mkey);
   
   void react_RightClick(Point point,MouseKey mkey);
   
   void react_Move(Point point,MouseKey mkey);
 };

/* class ShapeLab2 */

class ShapeLab2 : public SubWindow
 {
   struct Config
    {
     VColor back = Wheat ;
     
     ProgressShape::Config progress_cfg;
     KnobShape::Config knob_cfg;
     ButtonShape::Config btn_cfg;
   
     ContourShape::Config contour_cfg;
     
     InfoShape::Config info_cfg;
     
     FixedShape::Config dialog_cfg;
     
     MessageWindow::Config msg_cfg;
     
     TextShape::Config text_cfg;
     
     LineEditShape::Config edit_cfg;
     
     CheckShape::Config check_cfg;
     
     Config()
      {
      }
    };
  
   Config cfg;
   
   WindowList wlist;
   WindowList dlist;
   
   ProgressWindow progress;
   KnobWindow btn1;
   ButtonWindow btn2;
   
   InfoFromString info;
   
   ContourWindow infoframe;
   
   InfoWindow infow;
   
   TextWindow text;
   
   LineEditWindow edit;
   
   CheckWindow check;
   
   // test dialog
   
   FixedWindow dialog;
   TestDialog test;
   ClientFromSubWindow dialog_client;
   
   // message
   
   MessageWindow msg_window;
   
   // connectors
   
   SignalConnector<ShapeLab2> connector_btn1_pressed;
   SignalConnector<ShapeLab2> connector_btn2_pressed;
   
   SignalConnector<ShapeLab2> connector_dialog_destroyed;
   SignalConnector<ShapeLab2> connector_msg_destroyed;
   
   SignalConnector<ShapeLab2> connector_edit_entered;
   SignalConnector<ShapeLab2,bool> connector_check_changed;
   
  private:
   
   void btn1_pressed();
   
   void btn2_pressed();
   
   void dialog_destroyed();
   
   void msg_destroyed();
   
   void edit_entered();
   
   void check_changed(bool check);
   
  public:
 
   explicit ShapeLab2(SubWindowHost &host);
  
   virtual ~ShapeLab2();
   
   // drawing
   
   virtual void layout();
   
   virtual void draw(DrawBuf buf,bool drag_active) const;
   
   // base
   
   virtual void open();
   
   virtual void close();
   
   // keyboard
   
   void gainFocus();
   
   void looseFocus();
   
   // mouse
 
   virtual void looseCapture();
 
   virtual MouseShape getMouseShape(Point point);
   
   // user input
   
   virtual void react(UserAction action);
   
   void react_Key(VKey vkey,KeyMod kmod);
 };

} // namespace App

#endif
