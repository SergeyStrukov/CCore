/* Rawin.h */
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

#ifndef CCore_inc_rawin_Rawin_h
#define CCore_inc_rawin_Rawin_h

#include <CCore/inc/rawin/RawinMsgProc.h>
#include <CCore/inc/rawin/StaticInit.h>

#include <CCore/inc/Timer.h>

namespace CCore {
namespace Rawin {

/* type MemColor */ 

using MemColor = uint32 ;

/* guard functions */ 

void SysCheckFail(const char *format,Sys::ErrorType error=Sys::NonNullError());

inline void SysCheck(const char *format,bool ok) { if( !ok ) SysCheckFail(format); }

inline void SysErrorCheck(const char *format,Sys::ErrorType error) { if( error ) SysCheckFail(format,error); }

inline Sys::ErrorType GetSysError(bool ok=false) { return ok?Sys::NoError:Sys::NonNullError(); }
 
/* functions */

Point GetMousePos();
 
Point GetScreenSize();
 
/* classes */ 

class ResId;

class HModule;

class MessagePump;

class WinPaint;

class WinClientPaint;

class MemPaint;

class RegisterWinClass;

class WinClassAtom;

class WinClassBase;

class MainWindowProp;

/* class ResId */ 

class ResId
 {
   const char *res_id;
   
  public: 
  
   ResId(const char *res_id_) : res_id(res_id_) {}
   
   ResId(Win32::IntRes res_id_) : res_id(Win32::MakeIntResource(res_id_)) {}
   
   operator const char * () const { return res_id; }
 };
 
/* class HModule */ 

class HModule
 {
   Win32::HModule hModule;
   
   struct App
    {
     Win32::HModule hModule;
     Sys::ErrorType error;
     
     void init()
      {
       hModule=(Win32::HModule)Win32::GetModuleHandleA(0);
       
       error=GetSysError(hModule!=0);
      }
    };
    
  public:
  
   HModule();
   
   HModule(Win32::HModule hModule_) : hModule(hModule_) {}
   
   operator Win32::HModule() const { return hModule; }
   
   Win32::HCursor loadCursor(ResId res_id) const;
   
   Win32::HIcon loadIcon(ResId res_id) const;
   
   Win32::HAccelerator loadAccelerator(ResId res_id) const;
 };
 
/* class MessagePump */ 

class MessagePump : NoCopy
 {
   Win32::HAccelerator hAccel;
 
  public:
  
   static const unsigned DefaultLim = 100 ;
   
   MessagePump() : hAccel(0) {}
   
   explicit MessagePump(Win32::HAccelerator hAccel_) : hAccel(hAccel_) {}
   
   explicit MessagePump(ResId res_id) : hAccel(HModule().loadAccelerator(res_id)) {}
   
   bool pump(unsigned lim=DefaultLim);
   
   void wait();
   
   void wait(Win32::timeout_t timeout_ms);
 };
 
/* class WinPaint */ 

class WinPaint : NoCopy
 {
   Win32::HWindow hWnd;
   Win32::PaintData pd;
   Win32::HGDevice hGD;
   
  public:
  
   explicit WinPaint(Win32::HWindow hWnd); 
    
   ~WinPaint(); 
    
   Win32::HGDevice getGD() const { return hGD; } 
   
   Pane getPane() const { return MsgBody::ToPane(pd.rect); }
   
   bool getEraseFlag() const { return pd.erase_flag; }
 };
 
/* class WinClientPaint */ 
 
class WinClientPaint : NoCopy
 {
   Win32::HWindow hWnd;
   Win32::HGDevice hGD;
   
  public: 
  
   explicit WinClientPaint(Win32::HWindow hWnd);
   
   ~WinClientPaint();
   
   Win32::HGDevice getGD() const { return hGD; } 
 };
 
/* class MemPaint */ 

class MemPaint : NoCopy
 {
   Win32::HGDevice hGD;
   Win32::HGDObject old_bmp;
   
   void *mem;
   Win32::HGDObject bmp;
   Point size;
   
  private: 
  
   static const int MaxLen = 10000 ;
   
   bool trySetSize(Point s,bool first_time);
   
  public:
  
   explicit MemPaint(Point size=GetScreenSize());
   
   ~MemPaint();
   
   Win32::HGDevice getGD() const { return hGD; } 
   
   Point getSize() const { return size; }
   
   MemColor * getMem() const { return static_cast<MemColor *>(mem); }
   
   bool fit(Point size_) const { return size_<=size; }
   
   void setSize(Point size=GetScreenSize());
   
   void supSize(Point size=GetScreenSize());
   
   void adjust(Point size);
   
   void draw(Win32::HGDevice dstGD,Pane pane);
 };
 
/* class RegisterWinClass */ 
 
class RegisterWinClass : NoCopy
 {
   HModule hModule;
   Win32::WindowClass wndcls;
   
  public: 
  
   RegisterWinClass();
   
   Win32::Atom regClass(const char *class_name,Win32::WindowProc wnd_proc); 
   
   // set
   
   void setCursor(Win32::HCursor hCursor) { wndcls.hCursor=hCursor; }
   
   void setIcon(Win32::HIcon hIcon) { wndcls.hIcon=hIcon;  }
   
   void setSmallIcon(Win32::HIcon hIcon) { wndcls.hIconSm=hIcon; }
   
   void setBrush(Win32::HBrush hBrush) { wndcls.hBrush=hBrush; }
   
   // set res_id
   
   void setCursor(ResId res_id) { setCursor(hModule.loadCursor(res_id)); }
   
   void setIcon(ResId res_id) { setIcon(hModule.loadIcon(res_id)); }
   
   void setSmallIcon(ResId res_id) { setSmallIcon(hModule.loadIcon(res_id)); }
   
   void setMenu(ResId res_id) { wndcls.menu_res=res_id; }
   
   // set system brush
   
   void setSysBrush(unsigned sys_color_index) { setBrush(Win32::GetSysColorBrush(sys_color_index)); } // Win32::SysColor
 };

/* class WinClassAtom */

class WinClassAtom : NoCopy
 {
   unsigned unique_number;
   char buf[128];
   Win32::Atom atom;
   Sys::ErrorType error;
   bool initialized;
   
   static unsigned NextNumber;
   
  private: 
  
   virtual Sys::ErrorType prepare(RegisterWinClass &reg)=0;
   
  public:
  
   WinClassAtom();
   
   ~WinClassAtom();
   
   Win32::Atom getAtom();
 };

/* class WinClassBase */ 

class WinClassBase : NoCopy
 {
   Win32::HWindow hWnd;
   
  private: 

   void init(Win32::HWindow hWnd_) { hWnd=hWnd_; }
   
   virtual void alive();
   
   virtual void dead();
   
   virtual void paint(Win32::HGDevice hGD,Pane pane,bool erase_flag);
   
  public: 
  
   WinClassBase();
   
   ~WinClassBase();
   
   Win32::HWindow getHandle() const { return hWnd; }
   
   bool isAlive() const { return hWnd!=0; }
   
   bool isDead() const { return hWnd==0; }
  
   // class properties

   virtual WinClassAtom & getClassAtom()=0;
   
   // message handlers
   
   void handle(ProcMsgBase *proc,Msg<Win32::WM_NcCreate> msg); 
   
   void handle(ProcMsgBase *proc,Msg<Win32::WM_NcDestroy> msg); 
   
   void handle(ProcMsgBase *proc,Msg<Win32::WM_Paint> msg);
   
   virtual Win32::MsgResult winProc(Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam)=0;
   
   static Win32::MsgResult ObjWinProc(WinClassBase *obj,Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam);
   
   static Win32::MsgResult WIN32_CALLTYPE WndProc(Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam);
   
   // operations
   
   bool show(unsigned cmd_show); // Win32::CmdShow , return previous state
   
   void update();
   
   void destroy();
   
   bool enable(bool en); // return previous state
   
   void setCaption(const char *text);
   
   void invalidate(Pane pane,bool erase_flag);
   
   void invalidate(bool erase_flag=true);
   
   void captureMouse();
   
   void releaseMouse();
   
   void setFocus();
   
   void setCursor(Win32::HCursor hCursor);
   
   void move(Pane pane);
   
   void moveTop();
   
   // create
   
   void createOverlapped(const char *title);
    
   void createOverlapped(const char *title,Pane pane);
   
   void createSimple(Pane pane);
 };
 
/* class MainWindowProp */ 

class MainWindowProp
 {
   static Win32::HWindow MainWindowHandle;
   
  public: 
  
   static void Alive(Win32::HWindow hWnd) { MainWindowHandle=hWnd; }
  
   static void Dead() { MainWindowHandle=0; }
   
   static void AbortMsgBox(StrLen text);
   
   static Win32::UPtrType RunModalDialog(ResId res_id,Win32::DialogProc dialog_proc,Win32::MsgLParam lParam);
   
   static ExceptionAction ShowException(const char *text,bool more_text); 
 };
 
} // namespace Rawin
} // namespace CCore
 
#endif
 

