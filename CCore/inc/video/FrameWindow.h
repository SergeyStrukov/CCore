/* FrameWindow.h */ 
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

#ifndef CCore_inc_video_FrameWindow_h
#define CCore_inc_video_FrameWindow_h

#include <CCore/inc/video/Point.h>
 
namespace CCore {
namespace Video {

/* classes */

struct WinControl;

class FrameWindow;

/* struct WinControl */

struct WinControl
 {
  virtual bool isAlive()=0;
  
  bool isDead() { return !isAlive(); }
  
  virtual void show()=0;
  
  virtual void hide()=0;
  
  virtual void update()=0;
  
  virtual void destroy()=0;
  
  virtual void invalidate(Pane pane)=0;
  
  virtual void invalidate()=0;
  
  virtual void captureMouse()=0;
  
  virtual void releaseMouse()=0;
  
  virtual void setFocus()=0;
  
  virtual void move(Pane pane)=0; // screen
  
  virtual void moveTop()=0;
 };

/* class FrameWindow */

class FrameWindow : NoCopy
 {
   WinControl *win;
   
  protected:
   
   WinControl * getWinControl() const { return win; }
   
  public:
   
   explicit FrameWindow(WinControl *win_) : win(win_) {}
  
   ~FrameWindow() {}
  
   // codes
   
   enum CloseAction
    {
     NoClose,
     DoClose
    };
   
   // base
   
   virtual void alive()
    {
     // do nothing
    }
   
   virtual void dead()
    {
     // do nothing
    }
   
   virtual void setSize(Point size)
    {
     Used(size);
     
     // do nothing
    }
   
   virtual void draw()
    {
     // do nothing
    }
   
   virtual void tick()
    {
     // do nothing
    }
 
   virtual CloseAction close()
    { 
     return DoClose; 
    }
   
   // events
   
   virtual void key(unsigned vkey,bool ext)
    {
     Used(vkey);
     Used(ext);
     
     // do nothing
    }
   
   virtual void key(unsigned vkey,unsigned repeat,bool ext)
    {
     for(; repeat ;repeat--) key(vkey,ext);
     
     // do nothing
    }
   
   virtual void key_alt(unsigned vkey,bool ext)
    {
     Used(vkey);
     Used(ext);
     
     // do nothing
    }
   
   virtual void key_alt(unsigned vkey,unsigned repeat,bool ext)
    {
     for(; repeat ;repeat--) key_alt(vkey,ext);
     
     // do nothing
    }
   
   virtual void putch(char ch)
    {
     Used(ch);
     
     // do nothing
    }
   
   virtual void putch(char ch,unsigned repeat)
    {
     for(; repeat ;repeat--) putch(ch);
     
     // do nothing
    }
   
   virtual void putch_alt(char ch)
    {
     Used(ch);
     
     // do nothing
    }
   
   virtual void putch_alt(char ch,unsigned repeat)
    {
     for(; repeat ;repeat--) putch_alt(ch);
     
     // do nothing
    }
   
   virtual void clickL(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     // do nothing
    }
   
   virtual void upL(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     // do nothing
    }
 
   virtual void dclickL(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     // do nothing
    }
   
   virtual void clickR(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     // do nothing
    }
   
   virtual void upR(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     // do nothing
    }
   
   virtual void dclickR(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     // do nothing
    }
   
   virtual void move(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     // do nothing
    }
   
   virtual void wheel(Point point,bool shift,bool ctrl,int delta)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     Used(delta);
     
     // do nothing
    }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

