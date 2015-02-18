/* Desktop.cpp */ 
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
 
#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/PrintError.h>

#include <CCore/inc/sys/SysError.h>

#include <CCore/inc/win32/Win32gui.h>
 
namespace CCore {
namespace Video {

namespace Private {

/* class WindowsControl */

class WindowsControl : public WinControl
 {
   Win32::HWindow hWnd = 0 ;
   bool is_main = false ;
   bool correct_max_size = false ;
   
  private: 
   
   void guardAlive(const char *format)
    {
     if( hWnd==0 )
       {
        Printf(Exception,format,"window is dead");
       }
    }
   
   void guardDead(const char *format)
    {
     if( hWnd!=0 )
       {
        Printf(Exception,format,"window is alive");
       }
    }
   
   static void GuardMaxSize(const char *format,Point max_size)
    {
     if( max_size<=Point(0,0) )
       {
        Printf(Exception,format,"bad max_size");
       }
    }
   
   static void GuardPane(const char *format,Pane pane,Point max_size)
    {
     if( !(pane.getSize()<=max_size) )
       {
        Printf(Exception,format,"bad pane size");
       }
    }
   
   void guardCreate(const char *format,Point max_size)
    {
     guardDead(format);
     
     GuardMaxSize(format,max_size);
    }
   
   void guardCreate(const char *format,Pane pane,Point max_size)
    {
     guardDead(format);
     
     GuardMaxSize(format,max_size);
     
     GuardPane(format,pane,max_size);
    }
   
   static void SysGuardFailed(const char *format,Sys::ErrorType error=Sys::NonNullError())
    {
     Printf(Exception,format,PrintError(error));
    }

   static void SysGuard(const char *format,bool ok)
    { 
     if( !ok ) SysGuardFailed(format); 
    }
   
   static Win32::HCursor CursorTable[];
   
   static Win32::HCursor GetCursor(MouseShape mshape)
    {
     return CursorTable[mshape];
    }
   
   class WindowClass : NoCopy
    {
      Win32::Atom atom;
      Sys::ErrorType error;
      
     public:
     
      WindowClass()
       {
        Win32::HModule hModule=(Win32::HModule)Win32::GetModuleHandleA(0);
        
        if( hModule==0 )
          {
           error=Sys::NonNullError();
          
           return;
          }
        
        Win32::WindowClass wndcls;
        
        wndcls.cb=sizeof wndcls;
        wndcls.class_extra=0;
        wndcls.window_extra=sizeof (Win32::UPtrType);
           
        wndcls.hModule=hModule;
        
        wndcls.style=Win32::ClassStyle_VRedraw|Win32::ClassStyle_HRedraw|Win32::ClassStyle_DClick;
        
        wndcls.hCursor=GetCursor(Mouse_Arrow);
        
        wndcls.hBrush=0;
        wndcls.hIcon=Win32::LoadIconA(hModule,Win32::MakeIntResource(AppDesktopConfig.idIcon));
        wndcls.hIconSm=Win32::LoadIconA(hModule,Win32::MakeIntResource(AppDesktopConfig.idIconSmall));
        wndcls.menu_res=0;
        
        wndcls.class_name="9613CA28BE7A78F0-2DD3FC07C7330F49-WindowsControl";
        wndcls.wnd_proc=WndProc;
           
        atom=Win32::RegisterClassExA(&wndcls);
        
        if( atom==0 )
          {
           error=Sys::NonNullError();
          }
        else
          {
           error=Sys::NoError;
          }
       }
      
      Win32::Atom getAtom(const char *format)
       {
        if( error ) SysGuardFailed(format,error);
        
        return atom;
       }
    };
   
   static WindowClass WindowClassObject;
   
   static Win32::HWindow HMainWindow;

  private: 
   
   Win32::MsgResult msgProc(Win32::HWindow hWnd_,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam)
    {
     switch( message )
       {
        case Win32::WM_NcCreate :
         {
          hWnd=hWnd_;
          is_alive=true;
          
          if( is_main ) HMainWindow=hWnd_;
          
          auto ret=Win32::DefWindowProcA(hWnd_,message,wParam,lParam);
          
          try { frame->alive(); } catch(...) {}
          
          return ret;
         }
        
        case Win32::WM_NcDestroy :
         {
          try { frame->dead(); } catch(...) {}
          
          hWnd=0;
          is_alive=false;
          
          if( is_main )
            {
             HMainWindow=0;
             
             Win32::PostQuitMessage(0);
            }
          
          return Win32::DefWindowProcA(hWnd_,message,wParam,lParam);
         }
        
#if 0
         
        case Win32::WM_Paint :
         {
          // TODO
         }
        break;
        
        case Win32::WM_Move :
         {
          // TODO
         }
        break;
        
        case Win32::WM_Size :
         {
          // TODO
         }
        break;
        
        case Win32::WM_Destroy :
         {
          // TODO
         }
        break;
        
        case Win32::WM_KeyDown :
         {
          // TODO
         }
        break;
        
        case Win32::WM_SysKeyDown :
         {
          // TODO
         }
        break;
        
        case Win32::WM_KeyUp :
         {
          // TODO
         }
        break;
        
        case Win32::WM_SysKeyUp :
         {
          // TODO
         }
        break;
        
        case Win32::WM_Char :
         {
          // TODO
         }
        break;
        
        case Win32::WM_SysChar :
         {
          // TODO
         }
        break;
        
        case Win32::WM_LButtonDown :
         {
          // TODO
         }
        break;
        
        case Win32::WM_LButtonUp :
         {
          // TODO
         }
        break;
        
        case Win32::WM_LButtonDClick :
         {
          // TODO
         }
        break;
        
        case Win32::WM_RButtonDown :
         {
          // TODO
         }
        break;
        
        case Win32::WM_RButtonUp :
         {
          // TODO
         }
        break;
        
        case Win32::WM_RButtonDClick :
         {
          // TODO
         }
        break;
        
        case Win32::WM_MouseMove :
         {
          // TODO
         }
        break;
        
        case Win32::WM_MouseWheel :
         {
          // TODO
         }
        break;
        
        case Win32::WM_SetCursor :
         {
          // TODO
         }
        break;
        
#endif        
        
        default: return Win32::DefWindowProcA(hWnd_,message,wParam,lParam);
       }
    }
   
   static Win32::MsgResult ObjWndProc(WindowsControl *obj,Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam)
    {
     try
       {
        return obj->msgProc(hWnd,message,wParam,lParam);
       }
     catch(...)
       {
        return 0;
       }
    }
   
   static Win32::MsgResult WIN32_CALLTYPE WndProc(Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam)
    {
     if( message==Win32::WM_NcCreate )
       {
        Win32::CreateData *ctx=(Win32::CreateData *)lParam;
        
        Win32::SetWindowLongA(hWnd,0,(Win32::UPtrType)(ctx->arg));
       }
       
     void *arg=(void *)Win32::GetWindowLongA(hWnd,0);  
     
     if( !arg ) 
       {
        // WM_GetMinMaxInfo comes before WM_NcCreate
       
        return Win32::DefWindowProcA(hWnd,message,wParam,lParam);
       }
     
     return ObjWndProc(static_cast<WindowsControl *>(arg),hWnd,message,wParam,lParam);
    }
   
  public:
  
   WindowsControl() {}
   
   virtual ~WindowsControl() {}
   
   // WinControl
   // create/destroy
   
   virtual void createMain(Point max_size_)
    {
     const char *format="CCore::Video::Private::WindowsControl::createMain(...) : #;";
     
     guardCreate(format,max_size_);
     
     if( HMainWindow!=0 )
       {
        Printf(Exception,format,"main window is already created");
       }
     
     is_main=true;
     correct_max_size=true;
     max_size=max_size_;
     
     Win32::HWindow hWnd=Win32::CreateWindowExA(Win32::WindowStyleEx_OverlappedWindow,
                                                Win32::MakeIntAtom(WindowClassObject.getAtom(format)),
                                                "",
                                                Win32::WindowStyle_OverlappedWindow,
                                                Win32::UserDefault,0,Win32::UserDefault,0,
                                                0,0,0,
                                                (void *)this);  
                       
     SysGuard(format,hWnd!=0);                  
    }
   
   virtual void createMain(Pane pane,Point max_size_)
    {
     const char *format="CCore::Video::Private::WindowsControl::createMain(...) : #;";
     
     guardCreate(format,pane,max_size_);
     
     if( HMainWindow!=0 )
       {
        Printf(Exception,format,"main window is already created");
       }
     
     is_main=true;
     correct_max_size=false;
     max_size=max_size_;
     
     Win32::HWindow hWnd=Win32::CreateWindowExA(Win32::WindowStyleEx_OverlappedWindow,
                                                Win32::MakeIntAtom(WindowClassObject.getAtom(format)),
                                                "",
                                                Win32::WindowStyle_OverlappedWindow,
                                                pane.x,pane.y,pane.dx,pane.dy,
                                                0,0,0,
                                                (void *)this);  
                       
     SysGuard(format,hWnd!=0);                  
    }
   
   virtual void create(Pane pane,Point max_size_)
    {
     const char *format="CCore::Video::Private::WindowsControl::create(...) : #;";
     
     guardCreate(format,pane,max_size_);
     
     is_main=false;
     correct_max_size=false;
     max_size=max_size_;
     
     Win32::HWindow hWnd=Win32::CreateWindowExA(0,
                                                Win32::MakeIntAtom(WindowClassObject.getAtom(format)),
                                                "",
                                                Win32::WindowStyle_Popup,
                                                pane.x,pane.y,pane.dx,pane.dy,
                                                HMainWindow,0,0,
                                                (void *)this);  
     
     SysGuard(format,hWnd!=0);                  
    }
   
   virtual void create(WinControl *parent,Pane pane,Point max_size_)
    {
     const char *format="CCore::Video::Private::WindowsControl::create(...) : #;";
     
     guardCreate(format,pane,max_size_);
     
     is_main=false;
     correct_max_size=false;
     max_size=max_size_;
     
     Win32::HWindow hParent;
     
     if( parent )
       {
        WindowsControl *ptr=dynamic_cast<WindowsControl *>(parent);
        
        if( !ptr )
          {
           Printf(Exception,format,"bad parent");
          }
       
        hParent=ptr->hWnd;
        
        if( hParent==0 )
          {
           Printf(Exception,format,"dead parent");
          }
       }
     else
       {
        hParent=HMainWindow;
       }
     
     Win32::HWindow hWnd=Win32::CreateWindowExA(0,
                                                Win32::MakeIntAtom(WindowClassObject.getAtom(format)),
                                                "",
                                                Win32::WindowStyle_Popup,
                                                pane.x,pane.y,pane.dx,pane.dy,
                                                hParent,0,0,
                                                (void *)this);  
     
     SysGuard(format,hWnd!=0);                  
    }
   
   virtual void destroy()
    {
     const char *format="CCore::Video::Private::WindowsControl::destroy() : #;";
     
     guardAlive(format);
     
     SysGuard(format, Win32::DestroyWindow(hWnd) );
    }
   
   // operations
   
   virtual bool enableUserInput(bool en)
    {
     const char *format="CCore::Video::Private::WindowsControl::enableUserInput(...) : #;";
     
     guardAlive(format);
     
     return !Win32::EnableWindow(hWnd,en);
    }
   
   virtual void show()
    {
     const char *format="CCore::Video::Private::WindowsControl::show() : #;";
     
     guardAlive(format);
     
     Win32::ShowWindow(hWnd,Win32::CmdShow_Show);
    }
   
   virtual void hide()
    {
     const char *format="CCore::Video::Private::WindowsControl::hide() : #;";
     
     guardAlive(format);
     
     Win32::ShowWindow(hWnd,Win32::CmdShow_Hide);
    }
   
   virtual void update()
    {
     const char *format="CCore::Video::Private::WindowsControl::update() : #;";
     
     guardAlive(format);
     
     SysGuard(format, Win32::UpdateWindow(hWnd) );
    }
   
   virtual void invalidate(Pane pane)
    {
     Win32::Rectangle rect;
     
     rect.left=pane.x;
     rect.right=pane.x+pane.dx;
     
     rect.top=pane.y;
     rect.bottom=pane.y+pane.dy;
    
     Win32::InvalidateRect(hWnd,&rect,true); // ignore error
    }
   
   virtual void invalidate()
    {
     Win32::InvalidateRect(hWnd,0,true); // ignore error
    }
   
   virtual void captureMouse()
    {
     const char *format="CCore::Video::Private::WindowsControl::captureMouse() : #;";
     
     guardAlive(format);
     
     Win32::SetCapture(hWnd);
    }
   
   virtual void releaseMouse()
    {
     const char *format="CCore::Video::Private::WindowsControl::releaseMouse() : #;";
     
     guardAlive(format);
     
     SysGuard(format, Win32::ReleaseCapture() );
    }
   
   virtual void setFocus()
    {
     const char *format="CCore::Video::Private::WindowsControl::setFocus() : #;";
     
     guardAlive(format);
     
     Win32::SetFocus(hWnd);
    }
   
   virtual void setMouseShape(MouseShape mshape)
    {
     Win32::SetCursor(GetCursor(mshape));
    }
   
   virtual void move(Pane pane)
    {
     const char *format="CCore::Video::Private::WindowsControl::move(...) : #;";
     
     guardAlive(format);
     
     GuardPane(format,pane,max_size);
     
     SysGuard(format, Win32::MoveWindow(hWnd,pane.x,pane.y,pane.dx,pane.dy,true) ); 
    }
   
   virtual void moveTop()
    {
     const char *format="CCore::Video::Private::WindowsControl::moveTop(...) : #;";
     
     guardAlive(format);
     
     SysGuard(format, SetWindowPos(hWnd,(Win32::HWindow)Win32::HWND_TopMost,0,0,0,0,Win32::WindowPos_NoSize|Win32::WindowPos_NoMove) );
    }
 };

Win32::HCursor WindowsControl::CursorTable[]=
 {
  0,
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_Arrow)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_IBeam)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_Wait)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_Cross)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_Hand)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_No)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_Help)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_SizeLeftRight)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_SizeUpDown)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_SizeUpLeft)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_SizeUpRight)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_SizeAll)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_UpArrow)),
  Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_AppStarting))
 };

WindowsControl::WindowClass WindowsControl::WindowClassObject;

Win32::HWindow WindowsControl::HMainWindow=0;

/* class WindowsDesktop */

class WindowsDesktop : public Desktop
 {
  private:
  
   static bool TestMsg()
    {
     Win32::Msg msg;
     
     return Win32::PeekMessageA(&msg,0,0,0,Win32::PeekMessage_NoRemove);
    }
  
  public:
  
   WindowsDesktop() {}
   
   ~WindowsDesktop() {}
   
   // Desktop
   
   virtual WinControl * createControl()
    { 
     return new WindowsControl(); 
    }
   
   virtual Point getScreenSize()
    {
     return Point(Win32::GetSystemMetrics(Win32::SysMetric_DXScreen),Win32::GetSystemMetrics(Win32::SysMetric_DYScreen));
    }
   
   virtual bool pump(unsigned lim)
    {
     for(Win32::Msg msg; lim && Win32::PeekMessageA(&msg,0,0,0,Win32::PeekMessage_Remove) ;lim--) 
       {
        if( msg.message==Win32::WM_Quit ) return false;
       
        Win32::TranslateMessage(&msg);
        Win32::DispatchMessageA(&msg);
       }
       
     return true;  
    }
   
   virtual void wait()
    {
     if( TestMsg() ) return;
     
     Win32::WaitMessage();
    }
   
   virtual void wait(MSec timeout)
    {
     if( TestMsg() ) return;
     
     Win32::MsgWaitForMultipleObjects(0,0,false,+timeout,Win32::Wake_AllInput);
    }
 };

} // namespace Private

using namespace Private;

/* global DefaultDesktop */

static WindowsDesktop DesktopObject;

DefaultDesktopPtr DefaultDesktop(&DesktopObject); 

} // namespace Video
} // namespace CCore
 

