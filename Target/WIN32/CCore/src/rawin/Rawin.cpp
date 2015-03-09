/* Rawin.cpp */ 
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
 
#include <CCore/inc/rawin/Rawin.h>

#include <CCore/inc/PrintError.h>
#include <CCore/inc/CapString.h>

namespace CCore {
namespace Rawin {

/* guard functions */ 

void SysCheckFail(const char *format,Sys::ErrorType error)
 {
  Printf(Exception,format,PrintError(error));
 }
 
/* functions */

Point GetMousePos()
 {
  Win32::Point pos;
  
  if( Win32::GetCursorPos(&pos) ) return MsgBody::ToPoint(pos);
  
  return Point(0,0);
 }
 
Point GetScreenSize()
 {
  return Point(Win32::GetSystemMetrics(Win32::SysMetric_DXScreen),Win32::GetSystemMetrics(Win32::SysMetric_DYScreen));
 }
 
/* class HModule */ 

HModule::HModule()
 { 
  const App &obj=StaticInitObj<App>();
  
  hModule=obj.hModule; 
  
  SysErrorCheck("CCore::Rawin::HModule::HModule() : #;",obj.error);
 }
 
Win32::HCursor HModule::loadCursor(ResId res_id) const
 {
  Win32::HCursor ret=Win32::LoadCursorA(hModule,res_id);
  
  SysCheck("CCore::Rawin::HModule::loadCursor(...) : #;",ret!=0);
  
  return ret;
 }
   
Win32::HIcon HModule::loadIcon(ResId res_id) const
 {
  Win32::HIcon ret=Win32::LoadIconA(hModule,res_id);
  
  SysCheck("CCore::Rawin::HModule::loadIcon(...) : #;",ret!=0);
  
  return ret;
 }
 
Win32::HAccelerator HModule::loadAccelerator(ResId res_id) const
 {
  Win32::HAccelerator ret=Win32::LoadAcceleratorsA(hModule,res_id);
  
  SysCheck("CCore::Rawin::HModule::loadAccelerator(...) : #;",ret!=0);
  
  return ret;
 }
 
/* class MessagePump */ 

bool MessagePump::pump(unsigned lim)
 {
  for(Win32::Msg msg; lim && Win32::PeekMessageA(&msg,0,0,0,Win32::PeekMessage_Remove) ;lim--) 
    {
     if( msg.message==Win32::WM_Quit ) return false;
    
     if( hAccel==0 || !Win32::TranslateAcceleratorA(msg.hWnd,hAccel,&msg) )
       {
        Win32::TranslateMessage(&msg);
        Win32::DispatchMessageA(&msg);
       }
    }
    
  return true;  
 }
   
void MessagePump::wait()
 {
  Win32::Msg msg;
  
  if( Win32::PeekMessageA(&msg,0,0,0,Win32::PeekMessage_NoRemove) ) return;
  
  Win32::WaitMessage();
 }
  
void MessagePump::wait(Win32::timeout_t timeout_ms)
 {
  Win32::Msg msg;
  
  if( Win32::PeekMessageA(&msg,0,0,0,Win32::PeekMessage_NoRemove) ) return;
  
  Win32::MsgWaitForMultipleObjects(0,0,false,timeout_ms,Win32::Wake_AllInput);
 }
 
/* class WinPaint */ 

WinPaint::WinPaint(Win32::HWindow hWnd_)
 { 
  if( hWnd_==0 )
    {
     Printf(Exception,"CCore::Rawin::WinPaint::WinPaint(...) : null hWnd");
    }
  
  hWnd=hWnd_;
  
  hGD=Win32::BeginPaint(hWnd_,&pd); 
  
  SysCheck("CCore::Rawin::WinPaint::WinPaint(...) : #;",hGD!=0);
 }
    
WinPaint::~WinPaint()
 { 
  Win32::EndPaint(hWnd,&pd); // ignore errors 
 }
    
/* class WinClientPaint */ 
 
WinClientPaint::WinClientPaint(Win32::HWindow hWnd_)
 {
  if( hWnd_==0 )
    {
     Printf(Exception,"CCore::Rawin::WinClientPaint::WinClientPaint(...) : null hWnd");
    } 
    
  hWnd=hWnd_;
  
  hGD=Win32::GetDC(hWnd_);
  
  SysCheck("CCore::Rawin::WinClientPaint::WinClientPaint(...) : #;",hGD!=0);
 }
   
WinClientPaint::~WinClientPaint()
 {
  Win32::ReleaseDC(hWnd,hGD); // ignore errors
 }
 
/* class MemPaint */ 

bool MemPaint::trySetSize(Point s,bool first_time)
 {
  if( s.x<=0 || s.y<=0 || s.x>MaxLen || s.y>MaxLen ) return false;

  void *new_mem;
  
  Win32::BitmapInfo info;
  
  info.header.cb=sizeof (Win32::BitmapInfoHeader);
  info.header.dx=s.x;
  info.header.dy=-s.y;
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
 
  if( new_bmp==0 ) return false;

  if( first_time )
    {
     old_bmp=Win32::SelectObject(hGD,new_bmp);  
    }  
  else
    {
     Win32::SelectObject(hGD,new_bmp);  
     
     Win32::DeleteObject(bmp);
    }
  
  mem=new_mem; 
  bmp=new_bmp;
  size=s;  
    
  return true;  
 }
 
MemPaint::MemPaint(Point size_)
 {
  hGD=Win32::CreateCompatibleDC(0);
  
  SysCheck("CCore::Rawin::MemPaint::MemPaint(...) : #;",hGD!=0);
  
  if( !trySetSize(size_,true) )
    {
     Win32::DeleteDC(hGD);
     
     Printf(Exception,"CCore::Rawin::MemPaint::MemPaint(...) : no memory");
    } 
 }
   
MemPaint::~MemPaint()
 {
  Win32::SelectObject(hGD,old_bmp);
 
  Win32::DeleteObject(bmp);
 
  Win32::DeleteDC(hGD);
 }
   
void MemPaint::setSize(Point size_)
 {
  if( !trySetSize(size_,false) )
    {
     Printf(Exception,"CCore::Rawin::MemPaint::setSize(...) : no memory");
    } 
 }
   
void MemPaint::supSize(Point size_)
 {
  setSize(Sup(size,size_));
 }
 
void MemPaint::adjust(Point size_)
 {
  if( !fit(size_) )
    {
     Point s=GetScreenSize();
     
     if( !fit(s) ) setSize(s);
    }
 }
   
void MemPaint::draw(Win32::HGDevice dstGD,Pane pane)
 {
  SysCheck("CCore::Rawin::MemPaint::draw(...) : #;", Win32::BitBlt(dstGD,pane.x,pane.y,pane.dx,pane.dy,hGD,pane.x,pane.y,Win32::RasterOp_Copy) );
 }
 
/* class RegisterWinClass */ 
 
RegisterWinClass::RegisterWinClass()
 {
  // predefined
 
  wndcls.cb=sizeof wndcls;
  wndcls.class_extra=0;
  wndcls.window_extra=sizeof (Win32::UPtrType);
     
  wndcls.hModule=hModule;
  
  wndcls.style=Win32::ClassStyle_VRedraw|Win32::ClassStyle_HRedraw|Win32::ClassStyle_DClick;
  
  // custom

  wndcls.hCursor=Win32::LoadCursorA(0,Win32::MakeIntResource(Win32::SysCursor_Arrow));
  
  wndcls.hBrush=Win32::GetSysColorBrush(Win32::SysColor_Window);
     
  wndcls.hIcon=0;
  wndcls.hIconSm=0;
  wndcls.menu_res=0;
 }
 
Win32::Atom RegisterWinClass::regClass(const char *class_name,Win32::WindowProc wnd_proc)
 {
  wndcls.class_name=class_name;
  wndcls.wnd_proc=wnd_proc;
     
  Win32::Atom ret=Win32::RegisterClassExA(&wndcls);
     
  SysCheck("CCore::Rawin::RegisterWinClass::regClass(...) : #;",ret!=0);
  
  return ret;
 }
 
/* class WinClassAtom */

unsigned WinClassAtom::NextNumber=0;

WinClassAtom::WinClassAtom()
 : unique_number(NextNumber++),
   initialized(false)
 {
 }

WinClassAtom::~WinClassAtom()
 {
 }

Win32::Atom WinClassAtom::getAtom()
 {
  if( !initialized )
    {
     RegisterWinClass reg;

     if( auto err=prepare(reg) )
       {
        error=err;
       }
     else
       {
        PrintBuf out(Range(buf));
      
        Printf(out,"9613CA28BE7A78F0-2DD3FC07C7330F49-#;",unique_number);
      
        const char *class_name=out.closeZStr();
        
        atom=reg.regClass(class_name,WinClassBase::WndProc);
      
        error=GetSysError(atom!=0);
       }
     
     initialized=true;
    }
  
  SysErrorCheck("CCore::Rawin::WinClassAtom::getAtom() : #;",error);
  
  return atom;
 }

/* class WinClassBase */ 

void WinClassBase::alive()
 {
  // do nothing
 }
   
void WinClassBase::dead()
 {
  // do nothing
 }
 
WinClassBase::WinClassBase()
 : hWnd(0) 
 {
 }

WinClassBase::~WinClassBase()
 {
 }

void WinClassBase::paint(Win32::HGDevice,Pane,bool)
 {
  // do nothing
 }
 
void WinClassBase::handle(ProcMsgBase *proc,Msg<Win32::WM_NcCreate>)
 { 
  init(proc->hWnd); 
     
  alive();
     
  proc->defProc(); 
 }
   
void WinClassBase::handle(ProcMsgBase *proc,Msg<Win32::WM_NcDestroy>)
 { 
  proc->defProc(); 
     
  dead();
     
  init(0); 
 }
   
void WinClassBase::handle(ProcMsgBase *,Msg<Win32::WM_Paint>)
 {
  WinPaint wp(hWnd);
     
  paint(wp.getGD(),wp.getPane(),wp.getEraseFlag());
 }
 
Win32::MsgResult WinClassBase::ObjWinProc(WinClassBase *obj,Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam)
 {
  try
    {
     return obj->winProc(hWnd,message,wParam,lParam);
    }
  catch(...)
    {
     return 0;
    }
 }
 
Win32::MsgResult WIN32_CALLTYPE WinClassBase::WndProc(Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam)
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
  
  return ObjWinProc(static_cast<WinClassBase *>(arg),hWnd,message,wParam,lParam);
 }

bool WinClassBase::show(unsigned cmd_show)
 { 
  return Win32::ShowWindow(hWnd,cmd_show);
 }
   
void WinClassBase::update()
 { 
  SysCheck("CCore::Rawin::WinClassBase::update() : #;", Win32::UpdateWindow(hWnd) );
 }
 
void WinClassBase::destroy()
 {
  SysCheck("CCore::Rawin::WinClassBase::destroy() : #;", Win32::DestroyWindow(hWnd) );
 }
 
bool WinClassBase::enable(bool en)
 {
  return !Win32::EnableWindow(hWnd,en);
 }
   
void WinClassBase::setCaption(const char *text)
 {
  SysCheck("CCore::Rawin::WinClassBase::setCaption(...) : #;", Win32::SetWindowTextA(hWnd,text) );
 }
 
void WinClassBase::invalidate(Pane pane,bool erase_flag)
 {
  Win32::Rectangle rect;
  
  rect.left=pane.x;
  rect.right=pane.x+pane.dx;
  
  rect.top=pane.y;
  rect.bottom=pane.y+pane.dy;
 
  Win32::InvalidateRect(hWnd,&rect,erase_flag); // ignore error
 }
   
void WinClassBase::invalidate(bool erase_flag)
 {
  Win32::InvalidateRect(hWnd,0,erase_flag); // ignore error
 }
 
void WinClassBase::captureMouse()
 {
  Win32::SetCapture(hWnd);
 }
   
void WinClassBase::releaseMouse()
 {
  SysCheck("CCore::Rawin::WinClassBase::releaseMouse() : #;", Win32::ReleaseCapture() );
 }
 
void WinClassBase::setFocus()
 {
  Win32::SetFocus(hWnd); // ignore error
 }

void WinClassBase::setCursor(Win32::HCursor hCursor)
 {
  Win32::SetCursor(hCursor);
 }

void WinClassBase::move(Pane pane)
 {
  SysCheck("CCore::Rawin::WinClassBase::move(...) : #;", Win32::MoveWindow(hWnd,pane.x,pane.y,pane.dx,pane.dy,true) ); 
 }

void WinClassBase::createOverlapped(const char *title)
 {
  Win32::HWindow hWnd=Win32::CreateWindowExA(Win32::WindowStyleEx_OverlappedWindow,
                                             Win32::MakeIntAtom(getClassAtom().getAtom()),
                                             title,
                                             Win32::WindowStyle_OverlappedWindow,
                                             Win32::UserDefault,0,Win32::UserDefault,0,
                                             0,0,0,
                                             this);  
                    
  SysCheck("CCore::Rawin::WinClassBase::createOverlapped(...) : #;",hWnd!=0);                  
 }
 
void WinClassBase::createOverlapped(const char *title,Pane pane)
 {
  Win32::HWindow hWnd=Win32::CreateWindowExA(Win32::WindowStyleEx_OverlappedWindow,
                                             Win32::MakeIntAtom(getClassAtom().getAtom()),
                                             title,
                                             Win32::WindowStyle_OverlappedWindow,
                                             pane.x,pane.y,pane.dx,pane.dy,
                                             0,0,0,
                                             this);  
                    
  SysCheck("CCore::Rawin::WinClassBase::createOverlapped(...) : #;",hWnd!=0);                  
 }

void WinClassBase::createSimple(Pane pane)
 {
  Win32::HWindow hWnd=Win32::CreateWindowExA(0,
                                             Win32::MakeIntAtom(getClassAtom().getAtom()),
                                             "",
                                             Win32::WindowStyle_Popup,
                                             pane.x,pane.y,pane.dx,pane.dy,
                                             0,0,0,
                                             this);  
                    
  SysCheck("CCore::Rawin::WinClassBase::createSimple(...) : #;",hWnd!=0);                  
 }

/* class MainWindowProp */ 

Win32::HWindow MainWindowProp::MainWindowHandle=0;
   
void MainWindowProp::AbortMsgBox(StrLen text)
 {
  CapString<> cap(text);
  
  Win32::MessageBoxA(MainWindowHandle,cap,"Abort",Win32::MessageBox_Ok|Win32::MessageBox_IconError);
 }
 
Win32::UPtrType MainWindowProp::RunModalDialog(ResId res_id,Win32::DialogProc dialog_proc,Win32::MsgLParam lParam)
 {
  return Win32::DialogBoxParamA(HModule(),res_id,MainWindowHandle,dialog_proc,lParam);
 }
 
#include <CCore/inc/rawin/Rawin.rh>

static Win32::UPtrType WIN32_CALLTYPE ExceptionDialogProc(Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam)
 {
  switch( message )
   {
    case Win32::WM_InitDialog :
     {
      const char *text=(const char *)lParam;
          
      Win32::SetWindowTextA(Win32::GetDlgItem(hWnd,IDC_EXCEPTION_TEXT),text);
     }
    return true;
       
    case Win32::WM_Command :
     {
      Msg<Win32::WM_Command> msg(wParam,lParam);
          
      if( msg.body.cmd_id!=IDC_EXCEPTION_TEXT ) Win32::EndDialog(hWnd,msg.body.cmd_id); 
     }
    return true; 
   }
       
  return false;  
 }
    
ExceptionAction MainWindowProp::ShowException(const char *text,bool /*more_text*/) 
 {
  switch( RunModalDialog(IDD_EXCEPTION,ExceptionDialogProc,(Win32::MsgLParam)text) )
    {
     case IDC_EXCEPTION_SILENTCONTINUE : return ExceptionAction_ContinueSilent;
     case IDC_EXCEPTION_EXIT :           return ExceptionAction_Exit;
     case IDC_EXCEPTION_ABORT :          return ExceptionAction_Abort;
     
     default:                            return ExceptionAction_Continue;
    }
 }
 
} // namespace Rawin
} // namespace CCore
 

