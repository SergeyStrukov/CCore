/* MessageWindow.h */ 
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

#ifndef CCore_inc_video_MessageWindow_h
#define CCore_inc_video_MessageWindow_h

#include <CCore/inc/video/FixedWindow.h>
#include <CCore/inc/video/WindowLib.h>

#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Array.h>
 
namespace CCore {
namespace Video {

/* consts */

enum ButtonId : int
 {
  Button_Cancel = -1 ,
  Button_Ok     =  0 ,
  
  Button_Yes    =  1 ,
  Button_No     =  2 
 };

/* classes */

class MessageSubWindow;

class MessageWindow;

/* class MessageSubWindow */

class MessageSubWindow : public SubWindow
 {
  public:
  
   struct Config
    {
     RefVal<Coord> knob_dxy  = 30 ;
     RefVal<Coord> space_dxy = 10 ;
     
     RefVal<Point> btnSpace = Point(20,10) ;
    
     RefVal<VColor> back = Silver ;

     RefVal<InfoShape::Config> info_ctor;
     RefVal<KnobShape::Config> knob_ctor;
     RefVal<ButtonShape::Config> btn_ctor;
     RefVal<DoubleLineShape::Config> dline_ctor;
     
     Config()
      {
      }
    };
   
  private: 
  
   class Btn : public ButtonWindow
    {
      int btn_id;
      
      MessageSubWindow *sub_win;
      
      SignalConnector<Btn> connector_pressed;

     private: 
      
      void pressed_id();     
      
     public:
    
      Btn(SubWindowHost &host,const ButtonShape::Config &cfg,const String &name,int btn_id,MessageSubWindow *sub_win);
      
      virtual ~Btn();
    };
   
  private:
  
   const Config &cfg;
   
   WindowList list;
   WindowList dlist;
   
   InfoWindow showInfo;
   
   XDoubleLineWindow dline;
   
   KnobWindow knobOk;
   
   const ButtonShape::Config &btn_cfg;
   
   DynArray<OwnPtr<Btn> > btn_list;
   
   ulen btn_count = 0 ;
   
   SignalConnector<MessageSubWindow> connector_knobOk_pressed;
   
  private: 
   
   void knobOk_pressed();
   
  public:
  
   MessageSubWindow(SubWindowHost &host,const Config &cfg);
   
   virtual ~MessageSubWindow();
   
   // methods
   
   Point getMinSize() const;
   
   MessageSubWindow & setInfo(const Info &info);
   
   MessageSubWindow & add(const String &name,int btn_id);
   
   // drawing
   
   virtual void layout();
   
   virtual void draw(DrawBuf buf,bool drag_active) const;
   
   virtual void draw(DrawBuf buf,Pane pane,bool drag_active) const;
   
   // base
   
   virtual void open();
   
   virtual void close();
   
   // keyboard
   
   virtual void gainFocus();
   
   virtual void looseFocus();
   
   // mouse
 
   virtual void looseCapture();

   virtual MouseShape getMouseShape(Point point,KeyMod kmod);
   
   // user input
   
   virtual void react(UserAction action);
   
   // signals
   
   Signal<int> finish; // btn_id
 };

/* class MessageWindow */

class MessageWindow : public FixedWindow 
 {
  public:
  
   struct Config
    {
     RefVal<Ratio> pos_ratio = Rational(5,12) ;
     
     RefVal<ConfigType> frame_ctor;
     RefVal<MessageSubWindow::Config> msg_ctor;
    
     Config()
      {
      }
    };
  
  private:
  
   const Config &cfg;
   
   MessageSubWindow sub_win;
   
   ClientFromSubWindow client;
   
   int btn_id = Button_Cancel ; 
   
   SignalConnector<MessageWindow,int> connector_finish;
   
  private: 
   
   void finish(int btn_id);
   
  public:
  
   MessageWindow(Desktop *desktop,const Config &cfg);
   
   virtual ~MessageWindow();
   
   // methods
   
   MessageWindow & setInfo(const Info &info) { sub_win.setInfo(info); return *this; }

   MessageWindow & add(const String &name,int btn_id) { sub_win.add(name,btn_id); return *this; }
   
   int getButtonId() const { return btn_id; } // available after the signal "destroyed" 
   
   // base
   
   virtual void alive();
   
   // create
   
   Pane getPane(StrLen title) const;
   
   using FixedWindow::createMain;
   using FixedWindow::create;
   
   void createMain(const String &title) { createMain(getPane(Range(title)),title); }
   
   void create(const String &title) { create(getPane(Range(title)),title); }
   
   void create(WindowHost *parent,const String &title) { create(parent,getPane(Range(title)),title); }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

