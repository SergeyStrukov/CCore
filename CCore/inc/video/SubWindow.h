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

struct SubWindowHost;

class SubWindow;

class WinList;

/* struct SubWindowHost */

struct SubWindowHost
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
   WinList *list = 0 ;
 
   Pane place; // relative parent window coords
  
   SubWindowHost &host;
   
   friend class SubWindowHost;
   friend class WinList;
  
  public:
  
   explicit SubWindow(SubWindowHost &host_) : host(host_) {}
   
   virtual ~SubWindow();
   
   // methods
   
   Pane getPlace() const { return place; }
   
   Point getSize() const { return place.getSize(); }
   
   FrameWindow * getFrame() const { return host.getFrame(); }
   
   Point getScreenOrigin() const { return host.getScreenOrigin()+place.getBase(); }
   
   Point toScreen(Point point) const { return point+getScreenOrigin(); }
   
   Point fromScreen(Point point) const { return point-getScreenOrigin(); }
   
   Pane toScreen(Pane pane) const { return pane+getScreenOrigin(); }
   
   Pane fromScreen(Pane pane) const { return pane-getScreenOrigin(); }
   
   void setPlace(Pane place_)
    { 
     place=place_;
     
     layout();
    }
  
   void redraw() { host.redraw(place); }
   
   void redraw(Pane pane) { host.redraw(Inner(place,pane)); }
   
   void setFocus() { host.setFocus(this); }
   
   void captureMouse() { host.captureMouse(this); }
   
   void releaseMouse() { host.releaseMouse(this); }
   
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
 
   void forward_react(UserAction action)
    {
     action.rebase(place.getBase());
     
     react(action);
    }
   
   struct Forwarder : UserInput
    {
     SubWindow *obj;
     
     explicit Forwarder(SubWindow *obj_) : obj(obj_) {}
     
     virtual void react(UserAction action)
      {
       obj->forward_react(action);
      }
    };
   
   Forwarder forward()
    {
     return Forwarder(this);     
    }
   
   MouseShape forward_getMouseShape(Point point) { return getMouseShape(point-place.getBase()); }
 };

/* class WinList */

class WinList : NoCopy , public SubWindowHost , public UserInput
 {
   SubWindow &parent;
  
   SubWindow *focus = 0 ;
   SubWindow *capture = 0 ;
   SubWindow *enter = 0 ;
   
   bool has_focus = false ;
   bool is_opened = false ;
   
   bool enable_tab = false ;
   
   using Algo = DLink<SubWindow>::LinearAlgo<&SubWindow::link> ;
   
   Algo::FirstLast list;
   
  private:
   
   SubWindow * find(Point point) const;
   
   SubWindow * pick(Point point) const;
   
  public: 
   
   explicit WinList(SubWindow &parent_) : parent(parent_) {}
   
   ~WinList();
   
   // methods
   
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
   
   // multiple insert
   
   template <class ... TT>
   void insTop(SubWindow *sub_win,TT * ... tt)
    {
     insTop(tt...);
     
     insTop(sub_win);
    }
   
   template <class ... TT>
   void insTop(SubWindow &sub_win,TT & ... tt)
    {
     insTop(tt...);
     
     insTop(sub_win);
    }
   
   template <class ... TT>
   void insBottom(SubWindow *sub_win,TT * ... tt)
    {
     insBottom(sub_win);
     
     insBottom(tt...);
    }
   
   template <class ... TT>
   void insBottom(SubWindow &sub_win,TT & ... tt)
    {
     insBottom(sub_win);
     
     insBottom(tt...);
    }
   
   // focus
   
   SubWindow * getFocus() const { return has_focus?focus:0; }
   
   void focusTop();
   
   void focusBottom();
   
   void focusNext();
   
   void focusPrev();
   
   void enableTabFocus(bool enable_tab_=true) { enable_tab=enable_tab_; }
   
   // draw
   
   void draw(const DrawBuf &buf,bool drag_active) const;
   
   void draw(const DrawBuf &buf,Pane pane,bool drag_active) const;
   
   // SubWindowHost
   
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
   
   // mouse
   
   void looseCapture();
   
   MouseShape getMouseShape(Point point,MouseShape def_shape=Mouse_Arrow);
   
   // user input
   
   template <class Func>
   void react(UserAction action,Func func);
   
   template <class Func>
   void react_Keyboard(UserAction action,Func func);
   
   template <class Func>
   void react_Mouse(UserAction action,Func func);
   
   template <class Func>
   void react_Move(Point point,MouseKey mkey,Func func);
   
   template <class Func>
   void react_Leave(Func func);
   
   virtual void react(UserAction action);
 };

template <class Func>
void WinList::react(UserAction action,Func func)
 {
  if( action.fromKeyboard() )
    {
     react_Keyboard(action,func);
    }
  else
    {
     struct React
      {
       WinList *list;
       const Func &func;
       
       void react_Move(Point point,MouseKey mkey)
        {
         list->react_Move(point,mkey,func);
        }
       
       void react_Leave()
        {
         list->react_Leave(func);
        }
       
       React(WinList *list_,const Func &func_) : list(list_),func(func_) {}
      };
     
     React obj(this,func);
    
     action.dispatch(obj, [this,&func] (UserAction action) { react_Mouse(action,func); } );
    }
 }

template <class Func>
void WinList::react_Keyboard(UserAction action,Func func)
 {
  if( focus )
    {
     if( enable_tab )
       {
        struct React
         {
          WinList *list;
          SubWindow *sub_win;
          
          React(WinList *list_,SubWindow *sub_win_) : list(list_),sub_win(sub_win_) {}
          
          void react_Key(VKey vkey,KeyMod kmod)
           {
            if( vkey==VKey_Tab )
              {
               if( kmod&KeyMod_Shift )
                 {
                  list->focusPrev();
                 }
               else
                 {
                  list->focusNext();
                 }
              }
            else
              {
               sub_win->put_Key(vkey,kmod);
              }
           }
         };
        
        React obj(this,focus);
        SubWindow *sub_win=focus;
       
        action.dispatch(obj, [sub_win] (UserAction action) { sub_win->react(action); } );
       }
     else
       {
        focus->react(action);
       }
    }
  else
    {
     func(action);
    }
 }

template <class Func>
void WinList::react_Mouse(UserAction action,Func func)
 {
  if( SubWindow *sub_win=pick(action.getPoint()) )
    {
     sub_win->forward_react(action);
    }
  else
    {
     func(action);
    }
 }

template <class Func>
void WinList::react_Move(Point point,MouseKey mkey,Func func)
 {
  if( SubWindow *sub_win=find(point) )
    {
     if( enter!=sub_win )
       {
        if( enter ) 
          Replace(enter,sub_win)->put_Leave();
        else
          enter=sub_win;
       }
    
     if( capture )
       capture->forward().put_Move(point,mkey);
     else
       sub_win->forward().put_Move(point,mkey);
    }
  else
    {
     if( enter ) Replace_null(enter)->put_Leave();
     
     if( capture )
       {
        capture->forward().put_Move(point,mkey);
       }
     else
       {
        func(UserAction::Create_Move(point,mkey));
       }
    }
 }

template <class Func>
void WinList::react_Leave(Func func)
 {
  if( enter ) 
    {
     Replace_null(enter)->put_Leave();
    }
  else
    {
     func(UserAction::Create_Leave());
    }
 }

/* class SomeWindow */

#if 0

class SomeWindow : public SubWindow
 {
   WinList list;
  
  public:
   
   explicit SomeWindow(SubWindowHost &host);
   
   virtual ~SomeWindow();
   
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
 };

SomeWindow::SomeWindow(SubWindowHost &host)
 : SubWindow(host),
   list(*this) 
 {
  // TODO
 }

SomeWindow::~SomeWindow()
 {
 }

 // drawing

void SomeWindow::layout()
 {
  // TODO
 }

void SomeWindow::draw(DrawBuf buf,bool drag_active) const
 {
  // TODO
  
  list.draw(buf,drag_active);
 }

void SomeWindow::draw(DrawBuf buf,Pane pane,bool drag_active) const
 {
  // TODO
  
  list.draw(buf,pane,drag_active);
 }

 // base

void SomeWindow::open()
 {
  // TODO
  
  list.open();
 }

void SomeWindow::close()
 {
  // TODO
  
  list.close();
 }

 // keyboard

void SomeWindow::gainFocus()
 {
  // TODO
  
  list.gainFocus();
 }

void SomeWindow::looseFocus()
 {
  // TODO
  
  list.looseFocus();
 }

 // mouse

void SomeWindow::looseCapture()
 {
  // TODO
  
  list.looseCapture();
 }

MouseShape SomeWindow::getMouseShape(Point point)
 {
  // TODO
  
  return list.getMouseShape(point,Mouse_Arrow);
 }

 // user input

void SomeWindow::react(UserAction action)
 {
  action.dispatch(*this, [this] (UserAction action) { list.react(action); } );
  
  /* OR */
  
  list.react(action, [this] (UserAction action) { action.dispatch(*this); } );
 }

#endif

} // namespace Video
} // namespace CCore
 
#endif
 


