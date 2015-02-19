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

/* SysGuard() */

void SysGuardFailed(const char *format,Sys::ErrorType error=Sys::NonNullError())
 {
  Printf(Exception,format,PrintError(error));
 }

void SysGuard(const char *format,bool ok)
 { 
  if( !ok ) SysGuardFailed(format); 
 }

/* class WindowBuf */

class WindowBuf : NoCopy
 {
   Win32::HGDevice hGD;
   Win32::HGDObject old_bmp;
   
   Win32::HGDObject bmp;
   void *mem = 0 ;
   Point size;
   
  private: 
  
   void setSize(Point new_size,bool first_time)
    {
     const char *format="CCore::Video::Private::WindowBuf::setSize(...) : #;";
    
     if( new_size<=Null )
       {
        Printf(Exception,format,"bad size");
       }
 
     void *new_mem;
     
     Win32::BitmapInfo info;
     
     info.header.cb=sizeof (Win32::BitmapInfoHeader);
     info.header.dx=new_size.x;
     info.header.dy=-new_size.y;
     info.header.planes=1;
     info.header.bpp=32;
     info.header.compression=Win32::Bitmap_RGB;
     
     info.header.image_size=0;
     info.header.x_ppm=0;
     info.header.y_ppm=0;
     info.header.colors_used=1;
     info.header.colors_important=0;
     
     info.colors[0].blue=0;
     info.colors[0].green=0;
     info.colors[0].red=0;
     info.colors[0].alpha=0;
     
     Win32::HGDObject new_bmp=Win32::ToGDObject(Win32::CreateDIBSection(0,&info,Win32::DIB_RGBColors,&new_mem,0,0));
    
     SysGuard(format,new_bmp!=0);
 
     if( first_time )
       {
        old_bmp=Win32::SelectObject(hGD,new_bmp);  
       }  
     else
       {
        Win32::SelectObject(hGD,new_bmp);  
        
        Win32::DeleteObject(bmp);
       }
     
     bmp=new_bmp;
     mem=new_mem; 
     size=new_size;  
    }
   
  public:
  
   WindowBuf()
    {
     const char *format="CCore::Video::Private::WindowBuf::WindowBuf(...) : #;";
    
     hGD=Win32::CreateCompatibleDC(0);
    
     SysGuard(format,hGD!=0);
    }
   
   ~WindowBuf()
    {
     if( mem )
       {
        Win32::SelectObject(hGD,old_bmp);
      
        Win32::DeleteObject(bmp);
       }
     
     Win32::DeleteDC(hGD);
    }
   
   Point getSize() const { return size; }
   
   void * getMem() const { return mem; }
   
   ColorPlane getPlane() const { return ColorPlane(mem,size.x,size.y,size.x*4); }
   
   void setSize(Point new_size)
    {
     if( mem )
       {
        if( new_size!=size ) setSize(new_size,false);
       }
     else
       {
        setSize(new_size,true);
       }
    }
   
   void draw(Win32::HGDevice dstGD,Pane pane)
    {
     const char *format="CCore::Video::Private::WindowBuf::draw(...) : #;";
     
     if( !mem )
       {
        Printf(Exception,format,"no buf");
       }
     
     SysGuard(format, Win32::BitBlt(dstGD,pane.x,pane.y,pane.dx,pane.dy,hGD,pane.x,pane.y,Win32::RasterOp_Copy) );
    }
 };

/* class WindowsControl */

class WindowsControl : public WinControl
 {
   Win32::HWindow hWnd = 0 ;
   bool is_main = false ;
   bool correct_max_size = false ;
   
   Point origin;
   
   WindowBuf buf;
   bool buf_dirty = true ;
   
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
   
   static VKey ToVKey(Win32::MsgWParam wParam)
    {
     switch( wParam )
       {
        // TODO
      
        default: return VKey_Null;
       }
    }
   
   static KeyMod GetKeyMod(bool ext)
    {
     KeyMod kmod=KeyMod_Null;
     
     if( ext ) kmod|=KeyMod_Ext;
     
     if( Win32::GetKeyState(Win32::VK_Shift)&Win32::KeyStateDown ) kmod|=KeyMod_Shift;

     if( Win32::GetKeyState(Win32::VK_Control)&Win32::KeyStateDown ) kmod|=KeyMod_Ctrl;
     
     if( Win32::GetKeyState(Win32::VK_CapsLock)&Win32::KeyStateToggle ) kmod|=KeyMod_CapsLock;
     
     if( Win32::GetKeyState(Win32::VK_NumLock)&Win32::KeyStateToggle ) kmod|=KeyMod_NumLock;
     
     if( Win32::GetKeyState(Win32::VK_Scroll)&Win32::KeyStateToggle ) kmod|=KeyMod_ScrollLock;
     
     return kmod;
    }
   
   static MouseKey ToMouseKey(Win32::MsgWParam wParam)
    {
     MouseKey mkey=MouseKey_Null;
     
     if( wParam&Win32::MouseKey_Left ) mkey|=MouseKey_Left;
     
     if( wParam&Win32::MouseKey_Right ) mkey|=MouseKey_Right;
     
     if( wParam&Win32::MouseKey_Shift ) mkey|=MouseKey_Shift;
     
     if( wParam&Win32::MouseKey_Control ) mkey|=MouseKey_Ctrl;
     
     if( Win32::GetKeyState(Win32::VK_Alt)&Win32::KeyStateDown ) mkey|=MouseKey_Alt;
     
     return mkey;
    }
   
   static Point ToPoint(Win32::MsgLParam lParam)
    {
     return Point(Win32::SLoWord(lParam),Win32::SHiWord(lParam));
    }
   
   static Point ToSize(Win32::MsgLParam lParam)
    {
     return Point(Win32::LoWord(lParam),Win32::HiWord(lParam));
    }
   
   static Pane ToPane(Win32::Rectangle r)
    {
     return Pane(r.left,r.top,r.right-r.left,r.bottom-r.top);
    }

   class WindowPaint : NoCopy
    {
      Win32::HWindow hWnd;
      Win32::PaintData pd;
      Win32::HGDevice hGD;
      
     public:
     
      explicit WindowPaint(Win32::HWindow hWnd_)
       {
        const char *format="CCore::Video::Private::WindowsControl::WindowPaint::WindowPaint(...) : #;";
       
        if( hWnd_==0 )
          {
           Printf(Exception,format,"null hWnd");
          }
        
        hWnd=hWnd_;
        
        hGD=Win32::BeginPaint(hWnd_,&pd); 
        
        SysGuard(format,hGD!=0);
       }
       
      ~WindowPaint()
       {
        Win32::EndPaint(hWnd,&pd); // ignore errors 
       }
       
      Win32::HGDevice getGD() const { return hGD; } 
      
      Pane getPane() const { return ToPane(pd.rect); }
      
      bool getEraseFlag() const { return pd.erase_flag; }
    };
   
   Win32::MsgResult msgProc(Win32::HWindow hWnd_,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam)
    {
     switch( message )
       {
        case Win32::WM_NcCreate :
         {
          hWnd=hWnd_;
          is_alive=true;
          origin=Null;
          
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
        
        case Win32::WM_Paint :
         {
          WindowPaint wp(hWnd);

          if( !buf_dirty ) buf.draw(wp.getGD(),wp.getPane());
         }
        return 0;
        
        case Win32::WM_Move :
         {
          Point point=ToPoint(lParam);
          
          origin=point;
         }
        return 0;
        
        case Win32::WM_Size :
         {
          Point size=ToSize(lParam);
          
          if( correct_max_size && size>Null )
            {
             max_size=Sup(max_size,size);
             
             buf.setSize(max_size);
             
             buf_dirty=true;
            
             correct_max_size=false;
            }
          
          frame->setSize(size,buf_dirty);
         }
        return 0;
        
        case Win32::WM_KeyDown :
         {
          unsigned repeat=lParam&0xFFFF;
          bool ext=(lParam>>24)&1;
          
          VKey vkey=ToVKey(wParam);
          KeyMod kmod=GetKeyMod(ext);
          
          if( repeat>1 )
            frame->key(vkey,kmod,repeat);
          else
            frame->key(vkey,kmod);
         }
        return 0;
        
        case Win32::WM_SysKeyDown :
         {
          unsigned repeat=lParam&0xFFFF;
          bool ext=(lParam>>24)&1;
          bool alt=(lParam>>29)&1;
          
          VKey vkey=ToVKey(wParam);
          KeyMod kmod=GetKeyMod(ext);
          
          if( alt ) kmod|=KeyMod_Alt;
          
          if( repeat>1 )
            frame->key(vkey,kmod,repeat);
          else
            frame->key(vkey,kmod);
         }
        return 0;
        
        case Win32::WM_KeyUp :
         {
          unsigned repeat=lParam&0xFFFF;
          bool ext=(lParam>>24)&1;
          
          VKey vkey=ToVKey(wParam);
          KeyMod kmod=GetKeyMod(ext);
          
          if( repeat>1 )
            frame->keyUp(vkey,kmod,repeat);
          else
            frame->keyUp(vkey,kmod);
         }
        return 0;
        
        case Win32::WM_SysKeyUp :
         {
          unsigned repeat=lParam&0xFFFF;
          bool ext=(lParam>>24)&1;
          bool alt=(lParam>>29)&1;
          
          VKey vkey=ToVKey(wParam);
          KeyMod kmod=GetKeyMod(ext);
          
          if( alt ) kmod|=KeyMod_Alt;
          
          if( repeat>1 )
            frame->keyUp(vkey,kmod,repeat);
          else
            frame->keyUp(vkey,kmod);
         }
        return 0;
        
        case Win32::WM_Char :
         {
          if( wParam<256 )
            {
             char ch=(char)wParam;
             unsigned repeat=lParam&0xFFFF;
             
             if( repeat>1 )
               frame->putch(ch,repeat);
             else
               frame->putch(ch);
            }
         }
        return 0;
        
        case Win32::WM_SysChar :
         {
          if( wParam<256 )
            {
             char ch=(char)wParam;
             unsigned repeat=lParam&0xFFFF;
             
             if( repeat>1 )
               frame->putchAlt(ch,repeat);
             else
               frame->putchAlt(ch);
            }
         }
        return 0;
        
        case Win32::WM_LButtonDown :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->clickLeft(point,mkey);
         }
        return 0;
        
        case Win32::WM_LButtonUp :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->upLeft(point,mkey);
         }
        return 0;
        
        case Win32::WM_LButtonDClick :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->dclickLeft(point,mkey);
         }
        return 0;
        
        case Win32::WM_RButtonDown :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->clickRight(point,mkey);
         }
        return 0;
        
        case Win32::WM_RButtonUp :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->upRight(point,mkey);
         }
        return 0;
        
        case Win32::WM_RButtonDClick :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->dclickRight(point,mkey);
         }
        return 0;
        
        case Win32::WM_MouseMove :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->move(point,mkey);
         }
        return 0;
        
        case Win32::WM_MouseWheel :
         {
          MouseKey mkey=ToMouseKey(Win32::LoWord(wParam));
          int delta=Win32::SHiWord(wParam)/Win32::WheelDelta;
          Point point=ToPoint(lParam);
          
          frame->wheel(point-origin,mkey,delta);
         }
        return 0;

#if 0
        
        case Win32::WM_NcHitTest :
         {
          Point point=ToPoint(lParam);
          
          frame->setMouseShape(point-origin);
         }
        return Win32::HitCode_Client; 
        
        case Win32::WM_SetCursor :
         {
          // do nothing
         }
        return true;
        
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
     buf_dirty=true;
     
     buf.setSize(max_size_);
     
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
     buf_dirty=true;
     
     buf.setSize(max_size_);
     
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
     buf_dirty=true;
     
     buf.setSize(max_size_);
     
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
     buf_dirty=true;
     
     buf.setSize(max_size_);
     
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
   
   virtual void display(unsigned cmd_display)
    {
     const char *format="CCore::Video::Private::WindowsControl::display(...) : #;";
     
     guardAlive(format);
     
     Win32::ShowWindow(hWnd,cmd_display);
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
     
     buf_dirty=false;
    }
   
   virtual void invalidate()
    {
     Win32::InvalidateRect(hWnd,0,true); // ignore error
     
     buf_dirty=false;
    }
   
   virtual ColorPlane getDrawPlane()
    {
     Win32::GdiFlush();
     
     return buf.getPlane();
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
 

