/* WindowReport.h */ 
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

#ifndef CCore_inc_video_WindowReport_h
#define CCore_inc_video_WindowReport_h

#include <CCore/inc/video/DragWindow.h>
#include <CCore/inc/video/WindowLib.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {
namespace Video {

/* classes */

class ExceptionStore;

class ExceptionWindow;

template <class Shape> struct WindowReportParamOf;

class WindowReportBase;

template <class Shape> class WindowReportOf;

class ExceptionClient;

/* class ExceptionStore */

class ExceptionStore : NoCopy 
 {
   static const ulen MaxMsgLen = Align(256) ;
   static const ulen MaxMsgCount = 100 ;
   
   struct Header
    {
     Header *next;
     ulen index;
     ulen len;
     bool done;
     bool divide; // after this message
    };
   
   static const ulen Delta = Align(sizeof (Header)) ;
   
   static StrLen GetStr(Header *ptr) { return StrLen(PlaceAt(ptr)+Delta,ptr->len); }
   
   static PtrLen<char> GetBuf(Header *ptr) { return PtrLen<char>(PlaceAt(ptr)+Delta,ptr->len); }
   
   static void * GetNext(Header *ptr) { return PlaceAt(ptr)+Delta+Align(ptr->len); }
   
  private:
   
   void *mem;
   void *lim;
   
   Header *head;
   Header *tail;
   
   ulen index = 1 ;
   
  private:
  
   Header * try_alloc();
   
   Header * alloc();
   
   void free();
   
  protected: 
   
   PtrLen<char> startMsg();
   
   void endMsg(PtrLen<char> rest);
   
   void divide();
   
  public:
 
   ExceptionStore();
   
   ~ExceptionStore();
   
   bool nonEmpty() const { return head!=0; }
   
   template <class Func>
   void apply(Func func) const // func(ulen index,StrLen text,bool divide)
    {
     for(Header *ptr=head; ptr ;ptr=ptr->next) if( ptr->done ) func(ptr->index,GetStr(ptr),ptr->divide);
    }
 };

/* class ExceptionWindow */

class ExceptionWindow : public SubWindow
 {
  public:
  
   struct Config
    {
     RefVal<Coord> scroll_dxy = 20 ;
    
     RefVal<VColor> back    = Black ;
     RefVal<VColor> text    = Green ;
     RefVal<VColor> divider =   Red ;
     
     RefVal<Font> text_font;
     
     RefVal<ScrollShape::Config> scroll_cfg; 
     
     Config() {}
    };
   
  private:
   
   const Config &cfg;
   
   WindowReportBase &report;
   
   WindowList list;
   
   YScrollWindow yscroll;
   XScrollWindow xscroll;
   
  private: 

   bool opened = false ;
   
   ulen lines = 0 ;
   
   Pane ptext;
   
   Coord text_by = 0 ;
   Coord text_dy = 0 ;
   Coord text_dx = 0 ;
   
   ulen visible_lines = 0 ;
   Coord visible_dx = 0 ;
   
  private:
  
   static ulen Lines(StrLen text);
   
   static Coord VisibleDx(Font font,ulen index,StrLen text);
   
   void setLines();
   
   void setScrollPage();
   
   void drawText(DrawBuf buf,Pane pane) const;
   
  public:
  
   ExceptionWindow(SubWindowHost &host,const Config &cfg,WindowReportBase &report);
   
   virtual ~ExceptionWindow();
   
   // methods
   
   void reposition();
   
   // drawing
   
   virtual void layout();
   
   virtual void draw(DrawBuf buf,bool drag_active) const;
   
   // base
   
   virtual void open();
   
   virtual void close();
   
   // user input
   
   virtual void react(UserAction action);
   
   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat);
   
  private:
   
   void updateReport();
   
   void yposChanged(ulen pos);
   
   void xposChanged(ulen pos);
   
   SignalConnector<ExceptionWindow> connector_updateReport;
   SignalConnector<ExceptionWindow,ulen> connector_yposChanged;
   SignalConnector<ExceptionWindow,ulen> connector_xposChanged;
  };

/* struct WindowReportParamOf<Shape> */

template <class Shape>
struct WindowReportParamOf
 {
  Desktop *desktop = DefaultDesktop ;
  MSec tick_period = DeferCallQueue::DefaultTickPeriod ;
  
  typename Shape::Config drag_cfg;
  ExceptionWindow::Config cfg;
  
  WindowReportParamOf() {}
 };

/* type WindowReportParam */

using WindowReportParam = WindowReportParamOf<DragShape> ;

/* class WindowReportBase */

class WindowReportBase : public ExceptionStore , public ReportException 
 {
   PtrLen<char> buf;
   bool msg = false ;
   
   bool enable = true ;
   bool non_cleared = false ;
   
  protected: 
   
   Desktop *desktop;
   MSec tick_period;
   const ExceptionWindow::Config &cfg;
   
  private: 
  
   virtual void print(StrLen str);
   
   virtual void end();
   
  private:
  
   void boxShow();
   
   virtual void modalLoop()=0;
   
   class TempQueue;
   
  public:
  
   WindowReportBase(Desktop *desktop,MSec tick_period,const ExceptionWindow::Config &cfg);
   
   ~WindowReportBase();
   
   void clear()
    {
     ReportException::clear();
     
     non_cleared=false;
     
     divide();
    }
   
   void show();
   
   Signal<> update;
 };

/* class WindowReportOf<Shape> */

template <class Shape> 
class WindowReportOf : public WindowReportBase
 {
   const typename Shape::Config &drag_cfg;
   
  private: 
   
   virtual void modalLoop();
   
  public:
  
   explicit WindowReportOf(const WindowReportParamOf<Shape> &param)
    : WindowReportBase(param.desktop,param.tick_period,param.cfg),
      drag_cfg(param.drag_cfg)
    {
    }
 };

template <class Shape> 
void WindowReportOf<Shape>::modalLoop()
 {
  DragWindowOf<Shape> main_win(desktop,drag_cfg);
  
  ExceptionWindow sub_win(main_win,cfg,*this);
  
  ClientFromSubWindow client(sub_win); 
  
  main_win.bindClient(client);
  
  Point max_size=main_win.getDesktop()->getScreenSize();
  
  main_win.createMain(CmdDisplay_Normal,max_size,drag_cfg.fatal_error);
  
  DeferCallQueue::Enable();
  
  DeferCallQueue::Loop();
 }

/* type WindowReport */

using WindowReport = WindowReportOf<DragShape> ;

/* class ExceptionClient */

class ExceptionClient : public ClientWindow
 {
   WindowReportBase &report;
   
   ExceptionWindow window;
   
   bool in_loop = false ;
   
   Signal<> alert;
   
  public:
  
   template <class W>
   ExceptionClient(W &parent,const ExceptionWindow::Config &cfg,WindowReportBase &report_)
    : report(report_),
      window(parent,cfg,report_)
    {
     sub_win=&window;
     
     parent.connectAlert(alert);
    }
   
   ~ExceptionClient();
   
   // methods
   
   void clear();
   
   void guard();
   
   void show();
   
   void beforeLoop();
   
   void afterLoop();
   
   // base
   
   virtual void alive();
 };

} // namespace Video
} // namespace CCore
 
#endif
 

