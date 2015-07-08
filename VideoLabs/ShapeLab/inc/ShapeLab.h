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
#include <CCore/inc/video/FixedWindow.h>

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
     
     ColorName back = Wheat ;
     
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
   
   WinList wlist;
   WinList dlist;

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
  public:
  
   explicit TestDialog(SubWindowHost &host);
   
   virtual ~TestDialog();
   
   // drawing
   
   virtual void layout();
   
   virtual void draw(DrawBuf buf,bool drag_active) const;
 };

/* class ShapeLab2 */

class ShapeLab2 : public SubWindow
 {
   struct Config
    {
     ColorName back = Wheat ;
     
     ProgressShape::Config progress_cfg;
     KnobShape::Config knob_cfg;
     ButtonShape::Config btn_cfg;
     
     FixedShape::Config dialog_cfg;
     
     Config()
      {
      }
    };
  
   Config cfg;
   
   WinList wlist;
   WinList dlist;
   
   ProgressWindow progress;
   KnobWindow btn1;
   ButtonWindow btn2;
   
   // test dialog
   
   FixedWindow dialog;
   TestDialog test;
   ClientFromSubWindow dialog_client;
   
   SignalConnector<ShapeLab2> connector_btn1_pressed;
   SignalConnector<ShapeLab2> connector_btn2_pressed;
   
   SignalConnector<ShapeLab2> connector_dialog_destroyed;
   
  private:
   
   void btn1_pressed();
   
   void btn2_pressed();
   
   void dialog_destroyed();
   
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
