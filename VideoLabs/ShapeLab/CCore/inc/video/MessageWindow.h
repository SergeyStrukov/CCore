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
 
namespace CCore {
namespace Video {

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
    
     RefVal<VColor> back = Silver ;

     RefVal<InfoShape::Config> info_ctor;
     RefVal<KnobShape::Config> knob_ctor;
     
     Config()
      {
      }
    };
  
  private:
  
   const Config &cfg;
   
   WindowList list;
   
   InfoWindow showInfo;
   
   KnobWindow knobOk;
   
   SignalConnector<MessageSubWindow> connector_knobOk_pressed;
   
  private: 
   
   void knobOk_pressed();
   
  public:
  
   MessageSubWindow(SubWindowHost &host,const Config &cfg);
   
   virtual ~MessageSubWindow();
   
   // methods
   
   Point getMinSize() const;
   
   void setInfo(const Info &info);
   
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

   virtual MouseShape getMouseShape(Point point);
   
   // user input
   
   virtual void react(UserAction action);
   
   // signals
   
   Signal<> finish;
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
   
   SignalConnector<MessageWindow> connector_finish;
   
  private: 
   
   void finish();
   
  public:
  
   MessageWindow(Desktop *desktop,const Config &cfg);
   
   virtual ~MessageWindow();
   
   // methods
   
   void setInfo(const Info &info) { sub_win.setInfo(info); }

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
 

