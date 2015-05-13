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
#include <CCore/inc/CapString.h>

#include <CCore/inc/sys/SysError.h>

#include <CCore/inc/task/TaskEvent.h>

#include <CCore/inc/win32/Win32gui.h>

namespace CCore {
namespace Video {

/* functions */

CmdDisplay MapCmdShow(unsigned cmd_show)
 {
  switch( cmd_show )
    {
     case Win32::CmdShow_Hide          : return CmdDisplay_Normal;
     default:
     case Win32::CmdShow_Normal        : return CmdDisplay_Normal;
     case Win32::CmdShow_Minimized     : return CmdDisplay_Minimized;
     case Win32::CmdShow_Maximized     : return CmdDisplay_Maximized;
     case Win32::CmdShow_NoActivate    : return CmdDisplay_Normal;
     case Win32::CmdShow_Show          : return CmdDisplay_Normal;
     case Win32::CmdShow_Minimize      : return CmdDisplay_Minimized;
     case Win32::CmdShow_MinNoActive   : return CmdDisplay_Minimized;
     case Win32::CmdShow_NA            : return CmdDisplay_Normal;
     case Win32::CmdShow_Restore       : return CmdDisplay_Restore;
     case Win32::CmdShow_Default       : return CmdDisplay_Normal;
     case Win32::CmdShow_ForceMinimize : return CmdDisplay_Minimized;
    }
 }

/* namespace Private_Desktop */

namespace Private_Desktop {

/* SysGuard() */

void SysGuardFailed(const char *format,Sys::ErrorType error=Sys::NonNullError())
 {
  Printf(Exception,format,PrintError(error));
 }

void SysGuard(const char *format,bool ok)
 { 
  if( !ok ) SysGuardFailed(format); 
 }

/* struct MsgEvent */

struct MsgEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint32 code;
  uint8 flag;
  
  enum FlagType
   {
    Entry,
    Leave,
    Stop
   };
  
  static const uint32 TickCode = 1000 ;
  
  void init(EventTimeType time_,EventIdType id_,Win32::MsgCode code_,FlagType flag_)
   {
    time=time_;
    id=id_;
    
    code=code_;
    flag=flag_;
   }

  void init(EventTimeType time_,EventIdType id_,FlagType flag_)
   {
    time=time_;
    id=id_;
    
    code=TickCode;
    flag=flag_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<MsgEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<MsgEvent *>(ptr)->id); }
  
  static void * Offset_code(void *ptr) { return &(static_cast<MsgEvent *>(ptr)->code); }
  
  static void * Offset_flag(void *ptr) { return &(static_cast<MsgEvent *>(ptr)->flag); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
   {
    auto id_Code=info.addEnum_uint32("WinMsgCode")
                     .addValueName(Win32::WM_Create,"WM_Create")
                     .addValueName(Win32::WM_Destroy,"WM_Destroy")
                     .addValueName(Win32::WM_Move,"WM_Move")
                     .addValueName(Win32::WM_Size,"WM_Size")
                     .addValueName(Win32::WM_Activate,"WM_Activate")
                     .addValueName(Win32::WM_SetFocus,"WM_SetFocus")
                     .addValueName(Win32::WM_KillFocus,"WM_KillFocus")
                     .addValueName(Win32::WM_Enable,"WM_Enable")
                     .addValueName(Win32::WM_Paint,"WM_Paint")
                     .addValueName(Win32::WM_Close,"WM_Close")
                     .addValueName(Win32::WM_Quit,"WM_Quit")
                     .addValueName(Win32::WM_QueryOpen,"WM_QueryOpen")
                     .addValueName(Win32::WM_EraseBackground,"WM_EraseBackground")
                     .addValueName(Win32::WM_EndSession,"WM_EndSession")
                     .addValueName(Win32::WM_ShowWindow,"WM_ShowWindow")
                     .addValueName(Win32::WM_ActivateApp,"WM_ActivateApp")
                     .addValueName(Win32::WM_CancelMode,"WM_CancelMode")
                     .addValueName(Win32::WM_SetCursor,"WM_SetCursor")
                     .addValueName(Win32::WM_MouseActivate,"WM_MouseActivate")
                     .addValueName(Win32::WM_GetMinMaxInfo,"WM_GetMinMaxInfo")
                     .addValueName(Win32::WM_WindowPosChanging,"WM_WindowPosChanging")
                     .addValueName(Win32::WM_WindowPosChanged,"WM_WindowPosChanged")
                     .addValueName(Win32::WM_ContextMenu,"WM_ContextMenu")
                     .addValueName(Win32::WM_NcCreate,"WM_NcCreate")
                     .addValueName(Win32::WM_NcDestroy,"WM_NcDestroy")
                     .addValueName(Win32::WM_NcHitTest,"WM_NcHitTest")
                     .addValueName(Win32::WM_NcPaint,"WM_NcPaint")
                     .addValueName(Win32::WM_NcActivate,"WM_NcActivate")
                     .addValueName(Win32::WM_SyncPaint,"WM_SyncPaint")
                     .addValueName(Win32::WM_NcMouseMove,"WM_NcMouseMove")
                     .addValueName(Win32::WM_NcLButtonDown,"WM_NcLButtonDown")
                     .addValueName(Win32::WM_NcLButtonUp,"WM_NcLButtonUp")
                     .addValueName(Win32::WM_NcLButtonDClick,"WM_NcLButtonDClick")
                     .addValueName(Win32::WM_NcRButtonDown,"WM_NcRButtonDown")
                     .addValueName(Win32::WM_NcRButtonUp,"WM_NcRButtonUp")
                     .addValueName(Win32::WM_NcRButtonDClick,"WM_NcRButtonDClick")
                     .addValueName(Win32::WM_NcMButtonDown,"WM_NcMButtonDown")
                     .addValueName(Win32::WM_NcMButtonUp,"WM_NcMButtonUp")
                     .addValueName(Win32::WM_NcMButtonDClick,"WM_NcMButtonDClick")
                     .addValueName(Win32::WM_KeyDown,"WM_KeyDown")
                     .addValueName(Win32::WM_KeyUp,"WM_KeyUp")
                     .addValueName(Win32::WM_Char,"WM_Char")
                     .addValueName(Win32::WM_DeadChar,"WM_DeadChar")
                     .addValueName(Win32::WM_SysKeyDown,"WM_SysKeyDown")
                     .addValueName(Win32::WM_SysKeyUp,"WM_SysKeyUp")
                     .addValueName(Win32::WM_SysChar,"WM_SysChar")
                     .addValueName(Win32::WM_SysDeadChar,"WM_SysDeadChar")
                     .addValueName(Win32::WM_InitDialog,"WM_InitDialog")
                     .addValueName(Win32::WM_Command,"WM_Command")
                     .addValueName(Win32::WM_SysCommand,"WM_SysCommand")
                     .addValueName(Win32::WM_InitMenu,"WM_InitMenu")
                     .addValueName(Win32::WM_InitMenuPopup,"WM_InitMenuPopup")
                     .addValueName(Win32::WM_MenuSelect,"WM_MenuSelect")
                     .addValueName(Win32::WM_EnterIdle,"WM_EnterIdle")
                     .addValueName(Win32::WM_UninitMenuPopup,"WM_UninitMenuPopup")
                     .addValueName(Win32::WM_MouseMove,"WM_MouseMove")
                     .addValueName(Win32::WM_LButtonDown,"WM_LButtonDown")
                     .addValueName(Win32::WM_LButtonUp,"WM_LButtonUp")
                     .addValueName(Win32::WM_LButtonDClick,"WM_LButtonDClick")
                     .addValueName(Win32::WM_RButtonDown,"WM_RButtonDown")
                     .addValueName(Win32::WM_RButtonUp,"WM_RButtonUp")
                     .addValueName(Win32::WM_RButtonDClick,"WM_RButtonDClick")
                     .addValueName(Win32::WM_MButtonDown,"WM_MButtonDown")
                     .addValueName(Win32::WM_MButtonUp,"WM_MButtonUp")
                     .addValueName(Win32::WM_MButtonDClick,"WM_MButtonDClick")
                     .addValueName(Win32::WM_MouseWheel,"WM_MouseWheel")
                     .addValueName(Win32::WM_EnterMenuLoop,"WM_EnterMenuLoop")
                     .addValueName(Win32::WM_ExitMenuLoop,"WM_ExitMenuLoop")
                     .addValueName(Win32::WM_Sizing,"WM_Sizing")
                     .addValueName(Win32::WM_CaptureChanged,"WM_CaptureChanged")
                     .addValueName(Win32::WM_Moving,"WM_Moving")
                     .addValueName(Win32::WM_EnterSizeMove,"WM_EnterSizeMove")
                     .addValueName(Win32::WM_ExitSizeMove,"WM_ExitSizeMove")
                     .addValueName(Win32::WM_NcMouseHover,"WM_NcMouseHover")
                     .addValueName(Win32::WM_MouseHover,"WM_MouseHover")
                     .addValueName(Win32::WM_NcMouseLeave,"WM_NcMouseLeave")
                     .addValueName(Win32::WM_MouseLeave,"WM_MouseLeave")
                     .addValueName(TickCode,"Tick")
                     .getId();
    
    auto id_Flag=info.addEnum_uint8("WinMsgFlag")
                     .addValueName(Entry,"Entry",EventMarker_Up)
                     .addValueName(Leave,"Leave",EventMarker_Down)
                     .addValueName(Stop,"Stop",EventMarker_Stop)
                     .getId();
    
    auto id=info.addStruct("WinMsgEvent")
                .addField_uint32("time",Offset_time)
                .addField_uint16("id",Offset_id)
                .addField_enum_uint32(id_Code,"code",Offset_code)
                .addField_enum_uint8(id_Flag,"flag",Offset_flag)
                .getId();
    
    desc.setStructId(info,id);
   }
 };

/* struct TickEvent */

struct TickEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint8 flag;
  
  enum FlagType
   {
    Entry,
    Leave
   };
  
  void init(EventTimeType time_,EventIdType id_,FlagType flag_)
   {
    time=time_;
    id=id_;
    
    flag=flag_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<TickEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<TickEvent *>(ptr)->id); }
  
  static void * Offset_flag(void *ptr) { return &(static_cast<TickEvent *>(ptr)->flag); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
   {
    auto id_Flag=info.addEnum_uint8("WinTickFlag")
                     .addValueName(Entry,"Entry",EventMarker_Up)
                     .addValueName(Leave,"Leave",EventMarker_Down)
                     .getId();
    
    auto id=info.addStruct("WinTickEvent")
                .addField_uint32("time",Offset_time)
                .addField_uint16("id",Offset_id)
                .addField_enum_uint8(id_Flag,"flag",Offset_flag)
                .getId();
    
    desc.setStructId(info,id);
   }
 };

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
     const char *format="CCore::Video::Private_Desktop::WindowBuf::setSize(...) : #;";
    
     if( new_size<=Null )
       {
        Printf(Exception,format,"bad size");
       }
 
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
     
     void *new_mem;
     
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
     const char *format="CCore::Video::Private_Desktop::WindowBuf::WindowBuf(...) : #;";
    
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
   
   ColorPlane getPlane() const { return ColorPlane(mem,size.x,size.y,size.x*4u); }
   
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
     const char *format="CCore::Video::Private_Desktop::WindowBuf::draw(...) : #;";
     
     if( !mem )
       {
        Printf(Exception,format,"no buf");
       }
     
     SysGuard(format, Win32::BitBlt(dstGD,pane.x,pane.y,pane.dx,pane.dy,hGD,pane.x,pane.y,Win32::RasterOp_Copy) );
    }
 };

/* class WindowsHost */

class WindowsHost : public WindowHost
 {
   Win32::HWindow hWnd = 0 ;
   bool is_main = false ;
   
   Point origin;
   
   WindowBuf buf;
   bool buf_dirty = true ;
   
   unsigned track_flags = 0 ;
   bool track_on = false ;
   unsigned hover_time = 0 ;
   
   Pane restore;
   bool max_flag = false ;
   
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
     if( max_size<=Null )
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
        
        wndcls.class_name="9613CA28BE7A78F0-2DD3FC07C7330F49-WindowsHost";
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
        case Win32::VK_Escape    : return VKey_Esc;
        case Win32::VK_F1        : return VKey_F1;
        case Win32::VK_F2        : return VKey_F2;
        case Win32::VK_F3        : return VKey_F3;
        case Win32::VK_F4        : return VKey_F4;
        case Win32::VK_F5        : return VKey_F5;
        case Win32::VK_F6        : return VKey_F6;
        case Win32::VK_F7        : return VKey_F7;
        case Win32::VK_F8        : return VKey_F8;
        case Win32::VK_F9        : return VKey_F9;
        case Win32::VK_F10       : return VKey_F10;
        case Win32::VK_F11       : return VKey_F11;
        case Win32::VK_F12       : return VKey_F12;
        
        case Win32::VK_Tilda     : return VKey_Tilda;
        
        case '1'                 : return VKey_1;
        case '2'                 : return VKey_2;
        case '3'                 : return VKey_3;
        case '4'                 : return VKey_4;
        case '5'                 : return VKey_5;
        case '6'                 : return VKey_6;
        case '7'                 : return VKey_7;
        case '8'                 : return VKey_8;
        case '9'                 : return VKey_9;
        case '0'                 : return VKey_0;
        
        case Win32::VK_Minus     : return VKey_Minus;
        case Win32::VK_Plus      : return VKey_Equal;
        case Win32::VK_BackSlash : return VKey_BackSlash;
        case Win32::VK_Back      : return VKey_BackSpace;
        case Win32::VK_Tab       : return VKey_Tab;
        
        case 'Q'                 : return VKey_q;
        case 'W'                 : return VKey_w;
        case 'E'                 : return VKey_e;
        case 'R'                 : return VKey_r;
        case 'T'                 : return VKey_t;
        case 'Y'                 : return VKey_y;
        case 'U'                 : return VKey_u;
        case 'I'                 : return VKey_i;
        case 'O'                 : return VKey_o;
        case 'P'                 : return VKey_p;
        
        case Win32::VK_OBracket  : return VKey_OpenBracket;
        case Win32::VK_CBracket  : return VKey_CloseBracket;
        case Win32::VK_Return    : return VKey_Enter;
        
        case Win32::VK_CapsLock  : return VKey_CapsLock;
      
        case 'A'                 : return VKey_a;
        case 'S'                 : return VKey_s;
        case 'D'                 : return VKey_d;
        case 'F'                 : return VKey_f;
        case 'G'                 : return VKey_g;
        case 'H'                 : return VKey_h;
        case 'J'                 : return VKey_j;
        case 'K'                 : return VKey_k;
        case 'L'                 : return VKey_l;
        
        case Win32::VK_Colon     : return VKey_Semicolon;
        case Win32::VK_Quote     : return VKey_Quote;
        
        case Win32::VK_Shift     : return VKey_Shift;
        
        case 'Z'                 : return VKey_z;
        case 'X'                 : return VKey_x;
        case 'C'                 : return VKey_c;
        case 'V'                 : return VKey_v;
        case 'B'                 : return VKey_b;
        case 'N'                 : return VKey_n;
        case 'M'                 : return VKey_m;
        
        case Win32::VK_Comma     : return VKey_Comma;
        case Win32::VK_Period    : return VKey_Period;
        case Win32::VK_Slash     : return VKey_Slash;
        
        case Win32::VK_Control   : return VKey_Ctrl;
        case Win32::VK_Alt       : return VKey_Alt;
        
        case Win32::VK_Space     : return VKey_Space;
        
        case Win32::VK_Scroll    : return VKey_ScrollLock;
        case Win32::VK_Pause     : return VKey_Pause;
        
        case Win32::VK_Insert    : return VKey_Insert;
        case Win32::VK_Home      : return VKey_Home;
        case Win32::VK_PgUp      : return VKey_PageUp;
        case Win32::VK_Delete    : return VKey_Delete;
        case Win32::VK_End       : return VKey_End;
        case Win32::VK_PgDown    : return VKey_PageDown;
        
        case Win32::VK_Up        : return VKey_Up;   
        case Win32::VK_Left      : return VKey_Left;   
        case Win32::VK_Down      : return VKey_Down;   
        case Win32::VK_Right     : return VKey_Right;
        
        case Win32::VK_NumLock   : return VKey_NumLock;
        case Win32::VK_Div       : return VKey_NumSlash;
        case Win32::VK_Mul       : return VKey_NumAsterisk;
        case Win32::VK_Sub       : return VKey_NumMinus;
        case Win32::VK_Add       : return VKey_NumPlus;
        
        case Win32::VK_Numpad7   : return VKey_Num7;
        case Win32::VK_Numpad8   : return VKey_Num8;
        case Win32::VK_Numpad9   : return VKey_Num9;
        case Win32::VK_Numpad4   : return VKey_Num4;
        case Win32::VK_Numpad5   : return VKey_Num5;
        case Win32::VK_Numpad6   : return VKey_Num6;
        case Win32::VK_Numpad1   : return VKey_Num1;
        case Win32::VK_Numpad2   : return VKey_Num2;
        case Win32::VK_Numpad3   : return VKey_Num3;
        
        case Win32::VK_Numpad0   : return VKey_NumIns; 
        case Win32::VK_Decimal   : return VKey_NumDel; 
        
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
     return Point((Coord)Win32::SLoWord(lParam),(Coord)Win32::SHiWord(lParam));
    }
   
   static Point ToSize(Win32::MsgLParam lParam)
    {
     return Point((Coord)Win32::LoWord(lParam),(Coord)Win32::HiWord(lParam));
    }
   
   static Pane ToPane(Win32::Rectangle r)
    {
     return Pane((Coord)r.left,(Coord)r.top,(Coord)(r.right-r.left),(Coord)(r.bottom-r.top));
    }

   static Coord RandomLen(Coord len)
    {
     int percent=Win32::GetTickCount()%100u;
     
     return Coord( (len/2)+((len/4)*percent)/100 );
    }
   
   static Coord RandomPos(Coord len)
    {
     int percent=Win32::GetTickCount()%100u;

     return Coord( (len*percent)/100 );
    }
   
   static Pane GetWorkPane()
    {
     Win32::Rectangle rect;
     
     SysGuard("CCore::Video::Private_Desktop::WindowsHost::GetWorkPane() : #;", Win32::SystemParametersInfoA(Win32::SPA_getWorkArea,0,&rect,0) );
     
     return ToPane(rect);
    }
   
   class WindowPaint : NoCopy
    {
      Win32::HWindow hWnd;
      Win32::PaintData pd;
      Win32::HGDevice hGD;
      
     public:
     
      explicit WindowPaint(Win32::HWindow hWnd_)
       {
        const char *format="CCore::Video::Private_Desktop::WindowsHost::WindowPaint::WindowPaint(...) : #;";
       
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
        Win32::EndPaint(hWnd,&pd); 
       }
       
      Win32::HGDevice getGD() const { return hGD; } 
      
      Pane getPane() const { return ToPane(pd.rect); }
      
      bool getEraseFlag() const { return pd.erase_flag; }
    };
   
   void setTrack()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::setTrack() : #;";
     
     Win32::TrackMouseDesc desc;
     
     desc.cb=sizeof desc;
     desc.flags=track_flags;
     desc.hWnd=hWnd;
     desc.hover_time=hover_time;
    
     SysGuard(format, Win32::TrackMouseEvent(&desc) );
    }
   
   Win32::MsgResult msgProc(Win32::HWindow hWnd_,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam)
    {
     switch( message )
       {
        case Win32::WM_GetMinMaxInfo :
         {
          Win32::MinMaxInfo *info=(Win32::MinMaxInfo *)lParam;
          
          Replace_min<int>(info->max_size.x,max_size.x);
          Replace_min<int>(info->max_size.y,max_size.y);
         }
        return 0;
        
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
        
        case Win32::WM_Paint :
         {
          WindowPaint wp(hWnd);

          if( !buf_dirty ) buf.draw(wp.getGD(),wp.getPane());
          
          frame->paintDone(Replace_null(token));
         }
        return 0;
        
        case Win32::WM_Move :
         {
          origin=ToPoint(lParam);
         }
        return 0;
        
        case Win32::WM_Size :
         {
          frame->setSize(ToSize(lParam),buf_dirty);
         }
        return 0;
        
        case Win32::WM_SetFocus :
         {
          frame->gainFocus();
         }
        return 0;
        
        case Win32::WM_KillFocus :
         {
          frame->looseFocus();
         }
        return 0;
        
        case Win32::WM_CaptureChanged :
         {
          frame->looseCapture();
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
          if( track_flags ) 
            {
             if( !track_on )
               {
                setTrack();
                
                track_on=true;
               } 
            }
          
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->move(point,mkey);
         }
        return 0;
        
        case Win32::WM_MouseWheel :
         {
          MouseKey mkey=ToMouseKey(Win32::LoWord(wParam));
          Coord delta=Win32::SHiWord(wParam)/Win32::WheelDelta;
          Point point=ToPoint(lParam);
          
          frame->wheel(point-origin,mkey,delta);
         }
        return 0;
        
        case Win32::WM_MouseHover :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          track_on=false;
          
          frame->hover(point,mkey);
         }
        return 0; 

        case Win32::WM_MouseLeave :
         {
          track_on=false;
          
          frame->leave();
         }
        return 0;
        
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
        
        default: return Win32::DefWindowProcA(hWnd_,message,wParam,lParam);
       }
    }
   
   static Win32::MsgResult ObjWndProc(WindowsHost *obj,Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam)
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
     TaskEventHost.add<MsgEvent>(message,MsgEvent::Entry);
     
     if( message==Win32::WM_NcCreate )
       {
        Win32::CreateData *ctx=(Win32::CreateData *)lParam;
        
        Win32::SetWindowLongA(hWnd,0,(Win32::UPtrType)(ctx->arg));
       }
       
     void *arg=(void *)Win32::GetWindowLongA(hWnd,0);
     
     Win32::MsgResult ret;
     
     if( !arg ) 
       {
        // WM_GetMinMaxInfo comes before WM_NcCreate
       
        ret=Win32::DefWindowProcA(hWnd,message,wParam,lParam);
       }
     else
       {
        ret=ObjWndProc(static_cast<WindowsHost *>(arg),hWnd,message,wParam,lParam);
       }
     
     TaskEventHost.add<MsgEvent>(message,MsgEvent::Leave);

     return ret;
    }
   
   void reset()
    {
     origin=Null;
     buf_dirty=true;
     track_flags=0;
     track_on=false;
     max_flag=false;
    }
   
  public:
  
   WindowsHost() {}
   
   virtual ~WindowsHost() {}
   
   // msg boxes
   
   static void AbortMsgBox(StrLen text)
    {
     CapString<> cap(text);
     
     Win32::MessageBoxA(HMainWindow,cap,"Abort",Win32::MessageBox_Ok|Win32::MessageBox_IconError);
    }
   
   static void ErrorMsgBox(StrLen text,StrLen title)
    {
     CapString<> cap(text);
     CapString<> cap_title(title);
     
     Win32::MessageBoxA(HMainWindow,cap,cap_title,Win32::MessageBox_Ok|Win32::MessageBox_IconError);
    }
   
   // WinControl
   // create/destroy
   
   virtual void createMain(Point max_size)
    {
     Point screen;
     
     screen.x=(Coord)Win32::GetSystemMetrics(Win32::SysMetric_DXScreen);
     screen.y=(Coord)Win32::GetSystemMetrics(Win32::SysMetric_DYScreen);
     
     Point size;
     
     size.x=RandomLen(screen.x);
     size.y=RandomLen(screen.y);
     
     size=Inf(size,max_size);
     
     Point base;
     
     screen-=size;
     
     base.x=RandomPos(screen.x);
     base.y=RandomPos(screen.y);
     
     Pane pane=Extent(base,size);
     
     createMain(pane,max_size);
    }
   
   virtual void createMain(Pane pane,Point max_size_)
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::createMain(...) : #;";
     
     guardCreate(format,pane,max_size_);
     
     if( HMainWindow!=0 )
       {
        Printf(Exception,format,"main window is already created");
       }
     
     is_main=true;
     max_size=max_size_;
     
     reset();
     
     buf.setSize(max_size_);
     
     Win32::HWindow hWnd=Win32::CreateWindowExA(0,
                                                Win32::MakeIntAtom(WindowClassObject.getAtom(format)),
                                                "",
                                                Win32::WindowStyle_Popup,
                                                pane.x,pane.y,pane.dx,pane.dy,
                                                0,0,0,
                                                (void *)this);  
                       
     SysGuard(format,hWnd!=0);                  
    }
   
   virtual void create(Pane pane,Point max_size_)
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::create(...) : #;";
     
     guardCreate(format,pane,max_size_);
     
     is_main=false;
     max_size=max_size_;
     
     reset();
     
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
   
   virtual void create(WindowHost *parent,Pane pane,Point max_size_)
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::create(...) : #;";
     
     guardCreate(format,pane,max_size_);
     
     is_main=false;
     max_size=max_size_;
     
     reset();
     
     buf.setSize(max_size_);
     
     Win32::HWindow hParent;
     
     if( parent )
       {
        WindowsHost *ptr=dynamic_cast<WindowsHost *>(parent);
        
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
     const char *format="CCore::Video::Private_Desktop::WindowsHost::destroy() : #;";
     
     guardAlive(format);
     
     SysGuard(format, Win32::DestroyWindow(hWnd) );
    }
   
   // operations
   
   virtual void setMaxSize(Point max_size_)
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::setMaxSize(...) : #;";

     GuardMaxSize(format,max_size_);
     
     buf.setSize(max_size_);
     
     max_size=max_size_;
     
     buf_dirty=true;
    }
   
   virtual bool enableUserInput(bool en)
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::enableUserInput(...) : #;";
     
     guardAlive(format);
     
     return !Win32::EnableWindow(hWnd,en);
    }
   
   virtual void display(CmdDisplay cmd_display)
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::display(...) : #;";
     
     guardAlive(format);
     
     switch( cmd_display )
       {
        default:
        case CmdDisplay_Normal : 
          Win32::ShowWindow(hWnd,Win32::CmdShow_Normal); // error unavailable 
        break;
        
        case CmdDisplay_Minimized : 
          Win32::ShowWindow(hWnd,Win32::CmdShow_Minimized); // error unavailable
        break;
        
        case CmdDisplay_Maximized : 
         {
          if( !max_flag )
            {
             max_flag=true;
            
             restore=getPlace();
             
             Pane pane=GetWorkPane();
             
             Replace_min(pane.dx,max_size.x);
             Replace_min(pane.dy,max_size.y);
            
             do_move(pane);
             
             Win32::InvalidateRect(hWnd,0,true); // ignore error
            }
         }
        break;
        
        case CmdDisplay_Restore :
         {
          if( max_flag )
            {
             max_flag=false;
            
             do_move(restore);
             
             Win32::InvalidateRect(hWnd,0,true); // ignore error
            }
         }
        break;
       }
    }
   
   virtual void show()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::show() : #;";
     
     guardAlive(format);
     
     Win32::ShowWindow(hWnd,Win32::CmdShow_Show); // error unavailable
    }
   
   virtual void hide()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::hide() : #;";
     
     guardAlive(format);
     
     Win32::ShowWindow(hWnd,Win32::CmdShow_Hide); // error unavailable
    }
   
   // drawing
   
   virtual void update()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::update() : #;";
     
     guardAlive(format);
     
     SysGuard(format, Win32::UpdateWindow(hWnd) );
    }
   
   virtual void invalidate(Pane pane,unsigned token_)
    {
     if( !pane ) return;
     
     token|=token_;
     
     Win32::Rectangle rect;
     
     rect.left=pane.x;
     rect.right=pane.x+pane.dx;
     
     rect.top=pane.y;
     rect.bottom=pane.y+pane.dy;
    
     Win32::InvalidateRect(hWnd,&rect,true); // ignore error
     
     buf_dirty=false;
    }
   
   virtual void invalidate(unsigned token_)
    {
     token|=token_;
     
     Win32::InvalidateRect(hWnd,0,true); // ignore error
     
     buf_dirty=false;
    }
   
   virtual ColorPlane getDrawPlane()
    {
     return buf.getPlane();
    }
   
   // keyboard
   
   virtual void setFocus()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::setFocus() : #;";
     
     guardAlive(format);
     
     Win32::SetFocus(hWnd); // error unavailable
    }
   
   // mouse
   
   virtual void captureMouse()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::captureMouse() : #;";
     
     guardAlive(format);
     
     Win32::SetCapture(hWnd); // error unavailable
    }
   
   virtual void releaseMouse()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::releaseMouse() : #;";
     
     guardAlive(format);
     
     SysGuard(format, Win32::ReleaseCapture() );
    }
   
   virtual void trackMouseHover()
    {
     BitSet(track_flags,Win32::MouseTrack_Hover);
     
     hover_time=Win32::HoverTimeDefault;
     
     setTrack();
    }
   
   virtual void trackMouseHover(MSec time)
    {
     BitSet(track_flags,Win32::MouseTrack_Hover);
     
     hover_time=+time;
     
     setTrack();
    }
   
   virtual void untrackMouseHover()
    {
     BitClear(track_flags,Win32::MouseTrack_Hover);
    }
   
   virtual void trackMouseLeave()
    {
     BitSet(track_flags,Win32::MouseTrack_Leave);
     
     setTrack();
    }
   
   virtual void untrackMouseLeave()
    {
     BitClear(track_flags,Win32::MouseTrack_Leave);
    }
   
   virtual void setMouseShape(MouseShape mshape)
    {
     Win32::SetCursor(GetCursor(mshape)); // error unavailable
    }
   
   // place
   
   virtual Pane getPlace()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::getPlace() : #;";
     
     guardAlive(format);
     
     Win32::Rectangle rect;
     
     SysGuard(format, Win32::GetWindowRect(hWnd,&rect) );
     
     return ToPane(rect);
    }
   
   void do_move(Pane pane)
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::do_move(...) : #;";
     
     guardAlive(format);
     
     GuardPane(format,pane,max_size);
     
     unsigned pos_flags=Win32::WindowPos_NoZOrder|Win32::WindowPos_NoCopyBits|Win32::WindowPos_NoRedraw|Win32::WindowPos_DeferErase;
     
     SysGuard(format, Win32::SetWindowPos(hWnd,(Win32::HWindow)0,pane.x,pane.y,pane.dx,pane.dy,pos_flags) );
    }
   
   virtual void move(Pane pane)
    {
     max_flag=false;
     
     do_move(pane);
    }
 };

Win32::HCursor WindowsHost::CursorTable[]=
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

WindowsHost::WindowClass WindowsHost::WindowClassObject;

Win32::HWindow WindowsHost::HMainWindow=0;

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
   
   virtual WindowHost * createHost()
    { 
     return new WindowsHost(); 
    }
   
   virtual Point getScreenSize()
    {
     return Point((Coord)Win32::GetSystemMetrics(Win32::SysMetric_DXScreen),(Coord)Win32::GetSystemMetrics(Win32::SysMetric_DYScreen));
    }
   
   virtual bool pump(unsigned lim)
    {
     for(Win32::Msg msg; lim && Win32::PeekMessageA(&msg,0,0,0,Win32::PeekMessage_Remove) ;lim--) 
       {
        if( msg.message==Win32::WM_Quit ) 
          {
           TaskEventHost.add<MsgEvent>(msg.message,MsgEvent::Stop);
          
           return false;
          }
       
        Win32::TranslateMessage(&msg);
        Win32::DispatchMessageA(&msg);
       }
       
     return true;  
    }
   
   virtual void wait(TimeScope time_scope)
    {
     if( auto t=+time_scope.get() ) 
       {
        if( TestMsg() ) return;
        
        Win32::MsgWaitForMultipleObjects(0,0,false,t,Win32::Wake_AllInput);
       }
    }
 };

} // namespace Private_Desktop

using namespace Private_Desktop;

/* functions */

void TickEntryEvent()
 {
  TaskEventHost.add<TickEvent>(TickEvent::Entry);
 }

void TickLeaveEvent()
 {
  TaskEventHost.add<TickEvent>(TickEvent::Leave);
 }

void AbortMsgBox(StrLen text)
 {
  WindowsHost::AbortMsgBox(text);
 }

void ErrorMsgBox(StrLen text,StrLen title)
 {
  WindowsHost::ErrorMsgBox(text,title);
 }

/* global DefaultDesktop */

static WindowsDesktop DesktopObject;

DefaultDesktopPtr DefaultDesktop(&DesktopObject); 

} // namespace Video
} // namespace CCore
 

