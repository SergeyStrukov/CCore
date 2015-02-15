/* RawinPanel.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Rawin_RawinPanel_h
#define CCore_inc_Rawin_RawinPanel_h

#include <CCore/inc/rawin/RawinDraw.h>

namespace CCore {
namespace Rawin {

/* classes */ 

class PanelBase;

template <class Panel,class Prop> class PanelWin;

template <class MainWin> class Main;

/* class PanelBase */

class PanelBase : NoCopy
 {
   WinClassBase *win;
   
  protected:
   
   WinClassBase * getWinClass() const { return win; }
   
  public:
   
   explicit PanelBase(WinClassBase *win_) : win(win_) {}
   
   ~PanelBase() {}
   
   // codes
   
   enum RedrawAction
    {
     NoRedraw,
     DoRedraw
    };
   
   enum CloseAction
    {
     NoClose,
     DoClose
    };
   
   enum CommandReply
    {
     CommandIgnored,
     CommandTaken
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
    }
   
   virtual void draw(MemPaint &mem_paint)
    {
     Used(mem_paint);
    }
   
   virtual RedrawAction tick()
    {
     return NoRedraw;
    }
 
   virtual CloseAction close()
    { 
     return DoClose; 
    }
   
   virtual CommandReply command(unsigned cmd,unsigned notify)
    {
     Used(cmd);
     Used(notify);
     
     return CommandIgnored;
    }
   
   // events
   
   virtual RedrawAction key(unsigned vkey,bool ext)
    {
     Used(vkey);
     Used(ext);
     
     return NoRedraw;
    }
   
   virtual RedrawAction key(unsigned vkey,unsigned repeat,bool ext)
    {
     RedrawAction ret=NoRedraw;
     
     for(; repeat ;repeat--) if( key(vkey,ext) ) ret=DoRedraw;
     
     return ret;
    }
   
   virtual RedrawAction key_alt(unsigned vkey,bool ext)
    {
     Used(vkey);
     Used(ext);
     
     return NoRedraw;
    }
   
   virtual RedrawAction key_alt(unsigned vkey,unsigned repeat,bool ext)
    {
     RedrawAction ret=NoRedraw;
     
     for(; repeat ;repeat--) if( key_alt(vkey,ext) ) ret=DoRedraw;
     
     return ret;
    }
   
   virtual RedrawAction putch(char ch)
    {
     Used(ch);
     
     return NoRedraw;
    }
   
   virtual RedrawAction putch(char ch,unsigned repeat)
    {
     RedrawAction ret=NoRedraw;
     
     for(; repeat ;repeat--) if( putch(ch) ) ret=DoRedraw;
     
     return ret;
    }
   
   virtual RedrawAction putch_alt(char ch)
    {
     Used(ch);
     
     return NoRedraw;
    }
   
   virtual RedrawAction putch_alt(char ch,unsigned repeat)
    {
     RedrawAction ret=NoRedraw;
     
     for(; repeat ;repeat--) if( putch_alt(ch) ) ret=DoRedraw;
     
     return ret;
    }
   
   virtual RedrawAction clickL(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     return NoRedraw;
    }
   
   virtual RedrawAction upL(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     return NoRedraw;
    }

   virtual RedrawAction dclickL(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     return NoRedraw;
    }
   
   virtual RedrawAction clickR(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     return NoRedraw;
    }
   
   virtual RedrawAction upR(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     return NoRedraw;
    }
   
   virtual RedrawAction dclickR(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     return NoRedraw;
    }
   
   virtual RedrawAction move(Point point,bool shift,bool ctrl)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     
     return NoRedraw;
    }
   
   virtual RedrawAction wheel(Point point,bool shift,bool ctrl,int delta)
    {
     Used(point);
     Used(shift);
     Used(ctrl);
     Used(delta);
     
     return NoRedraw;
    }
   
   virtual RedrawAction cancel()
    {
     return DoRedraw;
    }
 };

/* class PanelWin<Panel,Prop> */ 

template <class Panel,class Prop> 
class PanelWin : public WinClassBase
 {
  protected:
  
   using Trace   = typename Prop::TraceType ;
   using TraceOp = typename Trace::Op ;
     
   Trace trace;
   
  private: 
   
   MSecTimer timer;
   
   MemPaint mem_paint;
   
   Point origin;
   bool captured = false ;
   
   Panel panel;
   
  private: 
   
   virtual void alive()
    {
     Prop::Alive(getHandle());
  
     trace.printLine("alive()");
     
     panel.alive();
    }
    
   virtual void paint(Win32::HGDevice hGD,Pane pane,bool)
    {
     mem_paint.draw(hGD,pane);
    }
   
   virtual void dead()
    {
     panel.dead();

     trace.printLine("dead()");
     
     Prop::Dead();
    }
   
   void redraw()
    {
     panel.draw(mem_paint);
     
     invalidate();
    }

   void capture()
    {
     if( !captured )
       {
        captureMouse();
        
        captured=true;
       }
    }
   
   void release(const MsgBody::Mouse &body)
    {
     if( !body.pressed() && captured ) 
       {
        releaseMouse();
        
        captured=false;
       }
    }
   
  public:
  
   PanelWin() : trace(Prop::TraceFileName()),panel(this) {}
   
   ~PanelWin() {}
   
   // class properties
  
   virtual WinClassAtom & getClassAtom() { return Prop::ClassAtomObj; }
   
   // message handlers
   
   using WinClassBase::handle;
   
   void handle(ProcMsgBase *,Msg<Win32::WM_Move> msg)
    {
     origin=msg.body.point;
    }
    
   void handle(ProcMsgBase *,Msg<Win32::WM_Size> msg)
    {
     Point size=msg.body.size;
 
     mem_paint.adjust(size);
  
     panel.setSize(size);
  
     redraw();
    }
   
   void handle(ProcMsgBase *,Msg<Win32::WM_Destroy>)
    {
     Win32::PostQuitMessage(0);
    }
    
   void handle(ProcMsgBase *,Msg<Win32::WM_KeyDown> msg)
    {
     if( msg.body.repeat==1 )
       {
        if( panel.key(msg.body.vkey,msg.body.ext) ) redraw();
       }
     else
       {
        if( panel.key(msg.body.vkey,msg.body.repeat,msg.body.ext) ) redraw();
       }
    }
    
   void handle(ProcMsgBase *,Msg<Win32::WM_SysKeyDown> msg)
    {
     if( msg.body.repeat==1 )
       {
        if( panel.key_alt(msg.body.vkey,msg.body.ext) ) redraw();
       }
     else
       {
        if( panel.key_alt(msg.body.vkey,msg.body.repeat,msg.body.ext) ) redraw();
       }
    }
   
   void handle(ProcMsgBase *,Msg<Win32::WM_Char> msg)
    {
     if( msg.body.code>=256 ) return;
     
     char ch=(char)msg.body.code;
 
     if( msg.body.repeat==1 )
       {
        if( panel.putch(ch) ) redraw();
       }
     else
       {  
        if( panel.putch(ch,msg.body.repeat) ) redraw();
       }
    }
    
   void handle(ProcMsgBase *,Msg<Win32::WM_SysChar> msg)
    {
     if( msg.body.code>=256 ) return;
 
     char ch=(char)msg.body.code;
 
     if( msg.body.repeat==1 )
       {
        if( panel.putch_alt(ch) ) redraw();
       }
     else
       {
        if( panel.putch_alt(ch,msg.body.repeat) ) redraw();
       }
    }
   
   void handle(ProcMsgBase *,Msg<Win32::WM_LButtonDown> msg)
    {
     capture();
 
     if( panel.clickL(msg.body.point,msg.body.state&Win32::MouseKey_Shift,msg.body.state&Win32::MouseKey_Control) ) redraw();
    }
    
   void handle(ProcMsgBase *,Msg<Win32::WM_LButtonUp> msg)
    {
     release(msg.body);
  
     if( panel.upL(msg.body.point,msg.body.state&Win32::MouseKey_Shift,msg.body.state&Win32::MouseKey_Control) ) redraw();
    }
   
   void handle(ProcMsgBase *,Msg<Win32::WM_LButtonDClick> msg)
    {
     if( panel.dclickL(msg.body.point,msg.body.state&Win32::MouseKey_Shift,msg.body.state&Win32::MouseKey_Control) ) redraw();
    }
   
   void handle(ProcMsgBase *,Msg<Win32::WM_RButtonDown> msg)
    {
     capture();
 
     if( panel.clickR(msg.body.point,msg.body.state&Win32::MouseKey_Shift,msg.body.state&Win32::MouseKey_Control) ) redraw();
    }
    
   void handle(ProcMsgBase *,Msg<Win32::WM_RButtonUp> msg)
    {
     release(msg.body);
  
     if( panel.upR(msg.body.point,msg.body.state&Win32::MouseKey_Shift,msg.body.state&Win32::MouseKey_Control) ) redraw();
    }

   void handle(ProcMsgBase *,Msg<Win32::WM_RButtonDClick> msg)
    {
     if( panel.dclickR(msg.body.point,msg.body.state&Win32::MouseKey_Shift,msg.body.state&Win32::MouseKey_Control) ) redraw();
    }
   
   void handle(ProcMsgBase *,Msg<Win32::WM_MouseMove> msg)
    {
     release(msg.body);
     
     if( panel.move(msg.body.point,msg.body.state&Win32::MouseKey_Shift,msg.body.state&Win32::MouseKey_Control) ) redraw();
    }
   
   void handle(ProcMsgBase *,Msg<Win32::WM_MouseWheel> msg)
    {
     if( panel.wheel(msg.body.point-origin,msg.body.state&Win32::MouseKey_Shift,msg.body.state&Win32::MouseKey_Control,msg.body.wheel/Win32::WheelDelta) ) redraw();
    }
   
   void handle(ProcMsgBase *proc,Msg<Win32::WM_CancelMode>)
    {
     proc->defProc();
  
     if( panel.cancel() ) redraw();
    }
   
   void handle(ProcMsgBase *proc,Msg<Win32::WM_Close>)
    {
     if( panel.close() ) proc->defProc();
    }
   
   void handle(ProcMsgBase *proc,Msg<Win32::WM_Command> msg)
    {
     if( !panel.command(msg.body.cmd_id,msg.body.notify_code) ) proc->defProc();
    }
   
   virtual Win32::MsgResult winProc(Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam)
    {
     ProcMsg<PanelWin<Panel,Prop> > proc(hWnd,message,wParam,lParam,this);
     
     TraceOp op(trace,proc,Prop::EnableTrace(message));
     
     return proc.handle();
    }
    
   // tick
   
   void tick()
    {
     if( timer.exceed(100) )
       {
        timer.reset();
 
        if( panel.tick() ) redraw();
       }
    }
 };
 
/* class Main<MainWin> */ 

template <class MainWin> 
class Main : public MainBase
 {
   unsigned cmd_show;
   const char *title;
   
   MainWin main_win;
   MessagePump msg_pump;
     
  private:
  
   bool pump();
   
   void tick();
  
   virtual void do_run();
  
  public:
  
   Main(unsigned cmd_show,const char *title);
   
   Main(unsigned cmd_show,const char *title,ResId acc_res_id);
   
   ~Main();
 };
 
template <class MainWin> 
bool Main<MainWin>::pump()
 {
  try
    {
     report.clear();
        
     bool ret=msg_pump.pump();
        
     report.guard();
        
     return ret;
    }
  catch(CatchType) 
    {
     if( !report.show() )
       {
        main_win.destroy();
       }
        
     return true;
    } 
 }

template <class MainWin> 
void Main<MainWin>::tick()
 {
  try
    {
     report.clear();
        
     main_win.tick();
        
     report.guard();
    }
  catch(CatchType) 
    {
     if( !report.show() )
       {
        main_win.destroy();
       }
    } 
 }
  
template <class MainWin> 
void Main<MainWin>::do_run()
 {
  main_win.createOverlapped(title);
  
  main_win.show(cmd_show);
  main_win.update();
     
  while( pump() )
    {
     msg_pump.wait(10);
     
     tick();
    }
 }
  
template <class MainWin> 
Main<MainWin>::Main(unsigned cmd_show_,const char *title_) 
 : MainBase(MainWindowProp::ShowException),
   cmd_show(cmd_show_),
   title(title_) 
 {
 }
   
template <class MainWin> 
Main<MainWin>::Main(unsigned cmd_show_,const char *title_,ResId acc_res_id) 
 : MainBase(MainWindowProp::ShowException),
   cmd_show(cmd_show_),
   title(title_),
   msg_pump(acc_res_id) 
 {
 }

template <class MainWin> 
Main<MainWin>::~Main() 
 {
 }
   
} // namespace Rawin
} // namespace CCore
 
#endif
 

