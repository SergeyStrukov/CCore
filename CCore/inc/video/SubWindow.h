/* SubWindow.h */
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

#ifndef CCore_inc_video_SubWindow_h
#define CCore_inc_video_SubWindow_h

#include <CCore/inc/video/FrameWindow.h>
#include <CCore/inc/video/DrawBuf.h>

#include <CCore/inc/List.h>

namespace CCore {
namespace Video {

/* classes */

struct SubWinControl;

class SubWindow;

class WinList;

/* struct SubWinControl */

struct SubWinControl
 {
  virtual FrameWindow * getFrame()=0;
 
  virtual Point getScreenOrigin()=0;
 
  virtual void redraw(Pane pane)=0;
 
  virtual void setFocus(SubWindow *sub_win)=0;
 
  virtual void captureMouse(SubWindow *sub_win)=0;
 
  virtual void releaseMouse(SubWindow *sub_win)=0;
 };

/* class SubWindow */

class SubWindow : public MemBase_nocopy , public UserInput
 {
   DLink<SubWindow> link;
 
   Pane place; // relative parent window coords
  
   SubWinControl &win;
   
   friend class SubWinControl;
   friend class WinList;
  
  public:
  
   explicit SubWindow(SubWinControl &win_) : win(win_) {}
   
   virtual ~SubWindow() {}
   
   // methods
   
   Pane getPlace() const { return place; }
   
   Point getSize() const { return place.getSize(); }
   
   FrameWindow * getFrame() const { return win.getFrame(); }
   
   Point getScreenOrigin() const { return win.getScreenOrigin()+place.getBase(); }
   
   Point toScreen(Point point) const { return point+getScreenOrigin(); }
   
   Point fromScreen(Point point) const { return point-getScreenOrigin(); }
   
   Pane toScreen(Pane pane) const { return pane+getScreenOrigin(); }
   
   Pane fromScreen(Pane pane) const { return pane-getScreenOrigin(); }
   
   void setPlace(Pane place_)
    { 
     place=place_;
     
     layout();
    }
  
   void redraw() { win.redraw(place); }
   
   void redraw(Pane pane) { win.redraw(Inner(place,pane)); }
   
   void setFocus() { win.setFocus(this); }
   
   void captureMouse() { win.captureMouse(this); }
   
   void releaseMouse() { win.releaseMouse(this); }
   
   // drawing
   
   virtual void layout()
    {
    }
   
   virtual void draw(DrawBuf buf,bool drag_active) const
    {
     buf.erase(drag_active?Gray:Black);
    }
   
   virtual void draw(DrawBuf buf,Pane pane,bool drag_active) const
    {
     Used(pane);
     
     draw(buf,drag_active);
    }
   
   // base
   
   virtual void open()
    {
     // do nothing
    }
   
   virtual void close()
    {
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
 
   virtual MouseShape getMouseShape(Point point)
    {
     Used(point);
     
     return Mouse_Arrow;
    }

   // forward
   
   void forward_draw(const DrawBuf &buf,bool drag_active) const
    {
     draw(buf.cutRebase(place),drag_active);
    }

   void forward_draw(const DrawBuf &buf,Pane pane,bool drag_active) const
    {
     pane=Inf(place,pane);
     
     if( +pane ) draw(buf.cutRebase(place),pane-place.getBase(),drag_active);
    }
 
   void forward_clickLeft(Point point,MouseKey mkey) { clickLeft(point-place.getBase(),mkey); }
   
   void forward_upLeft(Point point,MouseKey mkey) { upLeft(point-place.getBase(),mkey); }
   
   void forward_dclickLeft(Point point,MouseKey mkey) { dclickLeft(point-place.getBase(),mkey); }
   
   void forward_clickRight(Point point,MouseKey mkey) { clickRight(point-place.getBase(),mkey); }
   
   void forward_upRight(Point point,MouseKey mkey) { upRight(point-place.getBase(),mkey); }
   
   void forward_dclickRight(Point point,MouseKey mkey) { dclickRight(point-place.getBase(),mkey); }
   
   void forward_move(Point point,MouseKey mkey) { move(point-place.getBase(),mkey); }
   
   void forward_hover(Point point,MouseKey mkey) { hover(point-place.getBase(),mkey); }
   
   void forward_wheel(Point point,MouseKey mkey,Coord delta) { wheel(point-place.getBase(),mkey,delta); }
   
   MouseShape forward_getMouseShape(Point point) { return getMouseShape(point-place.getBase()); }
 };

/* class WinList */

class WinList : NoCopy , public SubWinControl
 {
   SubWindow &parent;
  
   SubWindow *focus = 0 ;
   SubWindow *capture = 0 ;
   SubWindow *enter = 0 ;
   
   bool has_focus = false ;
   bool is_opened = false ;
   
   using Algo = DLink<SubWindow>::LinearAlgo<&SubWindow::link> ;
   
   Algo::FirstLast list;
   
  private:
   
   SubWindow * find(Point point) const;
   
   SubWindow * pick(Point point) const;
   
  public: 
   
   explicit WinList(SubWindow &parent_) : parent(parent_) {}
   
   // methods
   
   void reset()
    {
     capture=0;
     enter=0;
    }
   
   void insTop(SubWindow *sub_win);
   
   void insBottom(SubWindow *sub_win);
   
   void del(SubWindow *sub_win);
   
   void moveTop(SubWindow *sub_win);
   
   void moveBottom(SubWindow *sub_win);
   
   void insTop(SubWindow &sub_win) { insTop(&sub_win); }
   
   void insBottom(SubWindow &sub_win) { insBottom(&sub_win); }
   
   void del(SubWindow &sub_win) { del(&sub_win); }
   
   void moveTop(SubWindow &sub_win) { moveTop(&sub_win); }
   
   void moveBottom(SubWindow &sub_win) { moveBottom(&sub_win); }
   
   // draw
   
   void draw(const DrawBuf &buf,bool drag_active) const;
   
   void draw(const DrawBuf &buf,Pane pane,bool drag_active) const;
   
   // SubWinControl
   
   virtual FrameWindow * getFrame();
  
   virtual Point getScreenOrigin();
  
   virtual void redraw(Pane pane);
  
   virtual void setFocus(SubWindow *sub_win);
  
   virtual void captureMouse(SubWindow *sub_win);
  
   virtual void releaseMouse(SubWindow *sub_win);

   // base
   
   void open();
   
   void close();
   
   // keyboard
   
   void gainFocus();
   
   void looseFocus();
   
   bool key(VKey vkey,KeyMod kmod);
   
   bool key(VKey vkey,KeyMod kmod,unsigned repeat);
   
   bool keyUp(VKey vkey,KeyMod kmod);
   
   bool keyUp(VKey vkey,KeyMod kmod,unsigned repeat);
   
   // character
   
   bool putch(char ch);
   
   bool putch(char ch,unsigned repeat);
   
   bool putchAlt(char ch);
   
   bool putchAlt(char ch,unsigned repeat);
   
   // mouse
   
   void looseCapture();
   
   bool clickLeft(Point point,MouseKey mkey);
   
   bool upLeft(Point point,MouseKey mkey);

   bool dclickLeft(Point point,MouseKey mkey);
   
   bool clickRight(Point point,MouseKey mkey);
   
   bool upRight(Point point,MouseKey mkey);
   
   bool dclickRight(Point point,MouseKey mkey);
   
   bool move(Point point,MouseKey mkey);
   
   bool hover(Point point,MouseKey mkey);
   
   void leave();
   
   bool wheel(Point point,MouseKey mkey,Coord delta);
   
   MouseShape getMouseShape(Point point,MouseShape def_shape=Mouse_Arrow);
 };

} // namespace Video
} // namespace CCore
 
#endif
 


