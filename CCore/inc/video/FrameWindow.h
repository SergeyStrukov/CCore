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

#include <CCore/inc/video/UserAction.h>
#include <CCore/inc/video/FrameBuf.h>
 
#include <CCore/inc/MemBase.h>
#include <CCore/inc/TimeScope.h>

namespace CCore {
namespace Video {

/* classes */

//enum CmdDisplay;

struct Desktop;

class WindowHost;

class FrameWindow;

/* enum CmdDisplay */

enum CmdDisplay : unsigned
 {
  CmdDisplay_Normal,
  CmdDisplay_Minimized,
  CmdDisplay_Maximized,
  CmdDisplay_Restore
 };

const char * GetTextDesc(CmdDisplay cmd_display);

/* struct Desktop */

struct Desktop
 {
  virtual WindowHost * createHost()=0;
  
  virtual Point getScreenSize()=0;
  
  static const unsigned DefaultLim = 100 ;
  
  virtual bool pump(unsigned lim=DefaultLim)=0;
  
  virtual void wait(TimeScope time_scope)=0;
 };

/* class WindowHost */

class WindowHost : public MemBase_nocopy
 {
  protected:
  
   FrameWindow *frame = 0 ;
   Point max_size = Null ;
   bool is_alive = false ;
   unsigned token = 0 ;
   
   friend class FrameWindow;
   
  public: 
   
   WindowHost() {}
   
   virtual ~WindowHost() {}
   
   // props
   
   bool isAlive() const { return is_alive; }
   
   bool isDead() const { return !is_alive; }
   
   Point getMaxSize() const { return max_size; }
   
   unsigned getToken() const { return token; }
   
   // create/destroy
   
   virtual void createMain(Point max_size)=0;
   
   virtual void createMain(Pane pane,Point max_size)=0; // screen
   
   virtual void create(Pane pane,Point max_size)=0; // screen
   
   virtual void create(WindowHost *parent,Pane pane,Point max_size)=0; // screen
   
   virtual void destroy()=0;
   
   // operations
   
   virtual void setMaxSize(Point max_size)=0;
   
   virtual bool enableUserInput(bool en)=0; // return previous
   
   virtual void display(CmdDisplay cmd_display)=0;
   
   virtual void show()=0;
   
   virtual void hide()=0;
   
   // drawing
   
   virtual void update()=0;
   
   virtual void invalidate(Pane pane,unsigned token=0)=0;
   
   virtual void invalidate(unsigned token=0)=0;
   
   virtual ColorPlane getDrawPlane()=0;
   
   // keyboard
   
   virtual void setFocus()=0;
   
   // mouse
   
   virtual void captureMouse()=0;
   
   virtual void releaseMouse()=0;
   
   virtual void trackMouseHover()=0;
   
   virtual void trackMouseHover(MSec time)=0;
   
   virtual void untrackMouseHover()=0;
   
   virtual void trackMouseLeave()=0;
   
   virtual void untrackMouseLeave()=0;
   
   virtual void setMouseShape(MouseShape mshape)=0;
   
   // place
   
   virtual Pane getPlace()=0; // screen
   
   virtual void move(Pane pane)=0; // screen
   
   // clipboard
   
   virtual void textToClipboard(StrLen text)=0;
   
   virtual ulen textFromClipboard(PtrLen<char> buf)=0;
 };

/* class FrameWindow */

class FrameWindow : public MemBase_nocopy , public UserInput
 {
  protected:
   
   Desktop *const desktop;
   
   WindowHost *const host;
   
  public:
   
   explicit FrameWindow(Desktop *desktop_) : desktop(desktop_),host(desktop_->createHost()) { host->frame=this; }
  
   virtual ~FrameWindow() { delete host; }
   
   // props

   Desktop * getDesktop() const { return desktop; }
   
   WindowHost * getHost() const { return host; }
   
   bool isAlive() const { return host->isAlive(); }
   
   bool isDead() const { return host->isDead(); }
   
   // base
   
   virtual void alive()
    {
     // do nothing
    }
   
   virtual void dead()
    {
     // do nothing
    }
   
   virtual void setSize(Point size,bool buf_dirty)
    {
     Used(size);
     Used(buf_dirty);
     
     // do nothing
    }
   
   virtual void paintDone(unsigned token)
    {
     Used(token);
     
     // do nothing
    }
   
   // keyboard
   
   virtual void gainFocus()
    {
     // do nothing
    }
   
   virtual void looseFocus()
    {
     // do nothing
    }
   
   // mouse
 
   virtual void looseCapture()
    {
     // do nothing
    }
   
   virtual void setMouseShape(Point point)
    {
     Used(point);
     
     host->setMouseShape(Mouse_Arrow);
    }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

