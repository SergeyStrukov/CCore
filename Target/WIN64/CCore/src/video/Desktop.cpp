/* Desktop.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN64
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

#include <CCore/inc/win64/Win64gui.h>

namespace CCore {
namespace Video {

/* functions */

CmdDisplay MapCmdShow(unsigned cmd_show)
 {
  switch( cmd_show )
    {
     case Win64::CmdShow_Hide          : return CmdDisplay_Normal;
     default:
     case Win64::CmdShow_Normal        : return CmdDisplay_Normal;
     case Win64::CmdShow_Minimized     : return CmdDisplay_Minimized;
     case Win64::CmdShow_Maximized     : return CmdDisplay_Maximized;
     case Win64::CmdShow_NoActivate    : return CmdDisplay_Normal;
     case Win64::CmdShow_Show          : return CmdDisplay_Normal;
     case Win64::CmdShow_Minimize      : return CmdDisplay_Minimized;
     case Win64::CmdShow_MinNoActive   : return CmdDisplay_Minimized;
     case Win64::CmdShow_NA            : return CmdDisplay_Normal;
     case Win64::CmdShow_Restore       : return CmdDisplay_Restore;
     case Win64::CmdShow_Default       : return CmdDisplay_Normal;
     case Win64::CmdShow_ForceMinimize : return CmdDisplay_Minimized;
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
  
  void init(EventTimeType time_,EventIdType id_,Win64::MsgCode code_,FlagType flag_)
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
                     .addValueName(Win64::WM_Create,"WM_Create")
                     .addValueName(Win64::WM_Destroy,"WM_Destroy")
                     .addValueName(Win64::WM_Move,"WM_Move")
                     .addValueName(Win64::WM_Size,"WM_Size")
                     .addValueName(Win64::WM_Activate,"WM_Activate")
                     .addValueName(Win64::WM_SetFocus,"WM_SetFocus")
                     .addValueName(Win64::WM_KillFocus,"WM_KillFocus")
                     .addValueName(Win64::WM_Enable,"WM_Enable")
                     .addValueName(Win64::WM_Paint,"WM_Paint")
                     .addValueName(Win64::WM_Close,"WM_Close")
                     .addValueName(Win64::WM_Quit,"WM_Quit")
                     .addValueName(Win64::WM_QueryOpen,"WM_QueryOpen")
                     .addValueName(Win64::WM_EraseBackground,"WM_EraseBackground")
                     .addValueName(Win64::WM_EndSession,"WM_EndSession")
                     .addValueName(Win64::WM_ShowWindow,"WM_ShowWindow")
                     .addValueName(Win64::WM_ActivateApp,"WM_ActivateApp")
                     .addValueName(Win64::WM_CancelMode,"WM_CancelMode")
                     .addValueName(Win64::WM_SetCursor,"WM_SetCursor")
                     .addValueName(Win64::WM_MouseActivate,"WM_MouseActivate")
                     .addValueName(Win64::WM_GetMinMaxInfo,"WM_GetMinMaxInfo")
                     .addValueName(Win64::WM_WindowPosChanging,"WM_WindowPosChanging")
                     .addValueName(Win64::WM_WindowPosChanged,"WM_WindowPosChanged")
                     .addValueName(Win64::WM_ContextMenu,"WM_ContextMenu")
                     .addValueName(Win64::WM_NcCreate,"WM_NcCreate")
                     .addValueName(Win64::WM_NcDestroy,"WM_NcDestroy")
                     .addValueName(Win64::WM_NcHitTest,"WM_NcHitTest")
                     .addValueName(Win64::WM_NcPaint,"WM_NcPaint")
                     .addValueName(Win64::WM_NcActivate,"WM_NcActivate")
                     .addValueName(Win64::WM_SyncPaint,"WM_SyncPaint")
                     .addValueName(Win64::WM_NcMouseMove,"WM_NcMouseMove")
                     .addValueName(Win64::WM_NcLButtonDown,"WM_NcLButtonDown")
                     .addValueName(Win64::WM_NcLButtonUp,"WM_NcLButtonUp")
                     .addValueName(Win64::WM_NcLButtonDClick,"WM_NcLButtonDClick")
                     .addValueName(Win64::WM_NcRButtonDown,"WM_NcRButtonDown")
                     .addValueName(Win64::WM_NcRButtonUp,"WM_NcRButtonUp")
                     .addValueName(Win64::WM_NcRButtonDClick,"WM_NcRButtonDClick")
                     .addValueName(Win64::WM_NcMButtonDown,"WM_NcMButtonDown")
                     .addValueName(Win64::WM_NcMButtonUp,"WM_NcMButtonUp")
                     .addValueName(Win64::WM_NcMButtonDClick,"WM_NcMButtonDClick")
                     .addValueName(Win64::WM_KeyDown,"WM_KeyDown")
                     .addValueName(Win64::WM_KeyUp,"WM_KeyUp")
                     .addValueName(Win64::WM_Char,"WM_Char")
                     .addValueName(Win64::WM_DeadChar,"WM_DeadChar")
                     .addValueName(Win64::WM_SysKeyDown,"WM_SysKeyDown")
                     .addValueName(Win64::WM_SysKeyUp,"WM_SysKeyUp")
                     .addValueName(Win64::WM_SysChar,"WM_SysChar")
                     .addValueName(Win64::WM_SysDeadChar,"WM_SysDeadChar")
                     .addValueName(Win64::WM_InitDialog,"WM_InitDialog")
                     .addValueName(Win64::WM_Command,"WM_Command")
                     .addValueName(Win64::WM_SysCommand,"WM_SysCommand")
                     .addValueName(Win64::WM_InitMenu,"WM_InitMenu")
                     .addValueName(Win64::WM_InitMenuPopup,"WM_InitMenuPopup")
                     .addValueName(Win64::WM_MenuSelect,"WM_MenuSelect")
                     .addValueName(Win64::WM_EnterIdle,"WM_EnterIdle")
                     .addValueName(Win64::WM_UninitMenuPopup,"WM_UninitMenuPopup")
                     .addValueName(Win64::WM_MouseMove,"WM_MouseMove")
                     .addValueName(Win64::WM_LButtonDown,"WM_LButtonDown")
                     .addValueName(Win64::WM_LButtonUp,"WM_LButtonUp")
                     .addValueName(Win64::WM_LButtonDClick,"WM_LButtonDClick")
                     .addValueName(Win64::WM_RButtonDown,"WM_RButtonDown")
                     .addValueName(Win64::WM_RButtonUp,"WM_RButtonUp")
                     .addValueName(Win64::WM_RButtonDClick,"WM_RButtonDClick")
                     .addValueName(Win64::WM_MButtonDown,"WM_MButtonDown")
                     .addValueName(Win64::WM_MButtonUp,"WM_MButtonUp")
                     .addValueName(Win64::WM_MButtonDClick,"WM_MButtonDClick")
                     .addValueName(Win64::WM_MouseWheel,"WM_MouseWheel")
                     .addValueName(Win64::WM_EnterMenuLoop,"WM_EnterMenuLoop")
                     .addValueName(Win64::WM_ExitMenuLoop,"WM_ExitMenuLoop")
                     .addValueName(Win64::WM_Sizing,"WM_Sizing")
                     .addValueName(Win64::WM_CaptureChanged,"WM_CaptureChanged")
                     .addValueName(Win64::WM_Moving,"WM_Moving")
                     .addValueName(Win64::WM_EnterSizeMove,"WM_EnterSizeMove")
                     .addValueName(Win64::WM_ExitSizeMove,"WM_ExitSizeMove")
                     .addValueName(Win64::WM_NcMouseHover,"WM_NcMouseHover")
                     .addValueName(Win64::WM_MouseHover,"WM_MouseHover")
                     .addValueName(Win64::WM_NcMouseLeave,"WM_NcMouseLeave")
                     .addValueName(Win64::WM_MouseLeave,"WM_MouseLeave")
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
   Win64::HGDevice hGD;
   Win64::HGDObject old_bmp;
   
   Win64::HGDObject bmp;
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
 
     Win64::BitmapInfo info;
     
     info.header.cb=sizeof (Win64::BitmapInfoHeader);
     info.header.dx=new_size.x;
     info.header.dy=-new_size.y;
     info.header.planes=1;
     info.header.bpp=32;
     info.header.compression=Win64::Bitmap_RGB;
     
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
     
     Win64::HGDObject new_bmp=Win64::ToGDObject(Win64::CreateDIBSection(0,&info,Win64::DIB_RGBColors,&new_mem,0,0));
    
     SysGuard(format,new_bmp!=0);
 
     if( first_time )
       {
        old_bmp=Win64::SelectObject(hGD,new_bmp);  
       }  
     else
       {
        Win64::SelectObject(hGD,new_bmp);  
        
        Win64::DeleteObject(bmp);
       }
     
     bmp=new_bmp;
     mem=new_mem; 
     size=new_size;  
    }
   
  public:
  
   WindowBuf()
    {
     const char *format="CCore::Video::Private_Desktop::WindowBuf::WindowBuf(...) : #;";
    
     hGD=Win64::CreateCompatibleDC(0);
    
     SysGuard(format,hGD!=0);
    }
   
   ~WindowBuf()
    {
     if( mem )
       {
        Win64::SelectObject(hGD,old_bmp);
      
        Win64::DeleteObject(bmp);
       }
     
     Win64::DeleteDC(hGD);
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
   
   void draw(Win64::HGDevice dstGD,Pane pane)
    {
     const char *format="CCore::Video::Private_Desktop::WindowBuf::draw(...) : #;";
     
     if( !mem )
       {
        Printf(Exception,format,"no buf");
       }
     
     SysGuard(format, Win64::BitBlt(dstGD,pane.x,pane.y,pane.dx,pane.dy,hGD,pane.x,pane.y,Win64::RasterOp_Copy) );
    }
 };

/* class WindowsHost */

class WindowsHost : public WindowHost
 {
   Win64::HWindow hWnd = 0 ;
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
   
   static Win64::HCursor CursorTable[];
   
   static Win64::HCursor GetCursor(MouseShape mshape)
    {
     return CursorTable[mshape];
    }
   
   class WindowClass : NoCopy
    {
      Win64::Atom atom;
      Sys::ErrorType error;
      
     public:
     
      WindowClass()
       {
        Win64::HModule hModule=(Win64::HModule)Win64::GetModuleHandleA(0);
        
        if( hModule==0 )
          {
           error=Sys::NonNullError();
          
           return;
          }
        
        Win64::WindowClass wndcls;
        
        wndcls.cb=sizeof wndcls;
        wndcls.class_extra=0;
        wndcls.window_extra=sizeof (Win64::UPtrType);
           
        wndcls.hModule=hModule;
        
        wndcls.style=Win64::ClassStyle_VRedraw|Win64::ClassStyle_HRedraw|Win64::ClassStyle_DClick;
        
        wndcls.hCursor=GetCursor(Mouse_Arrow);
        
        wndcls.hBrush=0;
        wndcls.hIcon=Win64::LoadIconA(hModule,Win64::MakeIntResource(AppDesktopConfig.idIcon));
        wndcls.hIconSm=Win64::LoadIconA(hModule,Win64::MakeIntResource(AppDesktopConfig.idIconSmall));
        wndcls.menu_res=0;
        
        wndcls.class_name="9613CA28BE7A78F0-2DD3FC07C7330F49-WindowsHost";
        wndcls.wnd_proc=WndProc;
           
        atom=Win64::RegisterClassExA(&wndcls);
        
        if( atom==0 )
          {
           error=Sys::NonNullError();
          }
        else
          {
           error=Sys::NoError;
          }
       }
      
      Win64::Atom getAtom(const char *format)
       {
        if( error ) SysGuardFailed(format,error);
        
        return atom;
       }
    };
   
   static WindowClass WindowClassObject;
   
   static Win64::HWindow HMainWindow;

  private: 
   
   static VKey ToVKey(Win64::MsgWParam wParam)
    {
     switch( wParam )
       {
        case Win64::VK_Escape    : return VKey_Esc;
        case Win64::VK_F1        : return VKey_F1;
        case Win64::VK_F2        : return VKey_F2;
        case Win64::VK_F3        : return VKey_F3;
        case Win64::VK_F4        : return VKey_F4;
        case Win64::VK_F5        : return VKey_F5;
        case Win64::VK_F6        : return VKey_F6;
        case Win64::VK_F7        : return VKey_F7;
        case Win64::VK_F8        : return VKey_F8;
        case Win64::VK_F9        : return VKey_F9;
        case Win64::VK_F10       : return VKey_F10;
        case Win64::VK_F11       : return VKey_F11;
        case Win64::VK_F12       : return VKey_F12;
        
        case Win64::VK_Tilda     : return VKey_Tilda;
        
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
        
        case Win64::VK_Minus     : return VKey_Minus;
        case Win64::VK_Plus      : return VKey_Equal;
        case Win64::VK_BackSlash : return VKey_BackSlash;
        case Win64::VK_Back      : return VKey_BackSpace;
        case Win64::VK_Tab       : return VKey_Tab;
        
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
        
        case Win64::VK_OBracket  : return VKey_OpenBracket;
        case Win64::VK_CBracket  : return VKey_CloseBracket;
        case Win64::VK_Return    : return VKey_Enter;
        
        case Win64::VK_CapsLock  : return VKey_CapsLock;
      
        case 'A'                 : return VKey_a;
        case 'S'                 : return VKey_s;
        case 'D'                 : return VKey_d;
        case 'F'                 : return VKey_f;
        case 'G'                 : return VKey_g;
        case 'H'                 : return VKey_h;
        case 'J'                 : return VKey_j;
        case 'K'                 : return VKey_k;
        case 'L'                 : return VKey_l;
        
        case Win64::VK_Colon     : return VKey_Semicolon;
        case Win64::VK_Quote     : return VKey_Quote;
        
        case Win64::VK_Shift     : return VKey_Shift;
        
        case 'Z'                 : return VKey_z;
        case 'X'                 : return VKey_x;
        case 'C'                 : return VKey_c;
        case 'V'                 : return VKey_v;
        case 'B'                 : return VKey_b;
        case 'N'                 : return VKey_n;
        case 'M'                 : return VKey_m;
        
        case Win64::VK_Comma     : return VKey_Comma;
        case Win64::VK_Period    : return VKey_Period;
        case Win64::VK_Slash     : return VKey_Slash;
        
        case Win64::VK_Control   : return VKey_Ctrl;
        case Win64::VK_Alt       : return VKey_Alt;
        
        case Win64::VK_Space     : return VKey_Space;
        
        case Win64::VK_Scroll    : return VKey_ScrollLock;
        case Win64::VK_Pause     : return VKey_Pause;
        
        case Win64::VK_Insert    : return VKey_Insert;
        case Win64::VK_Home      : return VKey_Home;
        case Win64::VK_PgUp      : return VKey_PageUp;
        case Win64::VK_Delete    : return VKey_Delete;
        case Win64::VK_End       : return VKey_End;
        case Win64::VK_PgDown    : return VKey_PageDown;
        
        case Win64::VK_Up        : return VKey_Up;   
        case Win64::VK_Left      : return VKey_Left;   
        case Win64::VK_Down      : return VKey_Down;   
        case Win64::VK_Right     : return VKey_Right;
        
        case Win64::VK_NumLock   : return VKey_NumLock;
        case Win64::VK_Div       : return VKey_NumSlash;
        case Win64::VK_Mul       : return VKey_NumAsterisk;
        case Win64::VK_Sub       : return VKey_NumMinus;
        case Win64::VK_Add       : return VKey_NumPlus;
        
        case Win64::VK_Numpad7   : return VKey_Num7;
        case Win64::VK_Numpad8   : return VKey_Num8;
        case Win64::VK_Numpad9   : return VKey_Num9;
        case Win64::VK_Numpad4   : return VKey_Num4;
        case Win64::VK_Numpad5   : return VKey_Num5;
        case Win64::VK_Numpad6   : return VKey_Num6;
        case Win64::VK_Numpad1   : return VKey_Num1;
        case Win64::VK_Numpad2   : return VKey_Num2;
        case Win64::VK_Numpad3   : return VKey_Num3;
        
        case Win64::VK_Numpad0   : return VKey_NumIns; 
        case Win64::VK_Decimal   : return VKey_NumDel; 
        
        default: return VKey_Null;
       }
    }
   
   static KeyMod GetKeyMod(bool ext)
    {
     KeyMod kmod=KeyMod_Null;
     
     if( ext ) kmod|=KeyMod_Ext;
     
     if( Win64::GetKeyState(Win64::VK_Shift)&Win64::KeyStateDown ) kmod|=KeyMod_Shift;

     if( Win64::GetKeyState(Win64::VK_Control)&Win64::KeyStateDown ) kmod|=KeyMod_Ctrl;
     
     if( Win64::GetKeyState(Win64::VK_CapsLock)&Win64::KeyStateToggle ) kmod|=KeyMod_CapsLock;
     
     if( Win64::GetKeyState(Win64::VK_NumLock)&Win64::KeyStateToggle ) kmod|=KeyMod_NumLock;
     
     if( Win64::GetKeyState(Win64::VK_Scroll)&Win64::KeyStateToggle ) kmod|=KeyMod_ScrollLock;
     
     return kmod;
    }
   
   static MouseKey ToMouseKey(Win64::MsgWParam wParam)
    {
     MouseKey mkey=MouseKey_Null;
     
     if( wParam&Win64::MouseKey_Left ) mkey|=MouseKey_Left;
     
     if( wParam&Win64::MouseKey_Right ) mkey|=MouseKey_Right;
     
     if( wParam&Win64::MouseKey_Shift ) mkey|=MouseKey_Shift;
     
     if( wParam&Win64::MouseKey_Control ) mkey|=MouseKey_Ctrl;
     
     if( Win64::GetKeyState(Win64::VK_Alt)&Win64::KeyStateDown ) mkey|=MouseKey_Alt;
     
     return mkey;
    }
   
   static Point ToPoint(Win64::MsgLParam lParam)
    {
     return Point((Coord)Win64::SLoWord(lParam),(Coord)Win64::SHiWord(lParam));
    }
   
   static Point ToSize(Win64::MsgLParam lParam)
    {
     return Point((Coord)Win64::LoWord(lParam),(Coord)Win64::HiWord(lParam));
    }
   
   static Pane ToPane(Win64::Rectangle r)
    {
     return Pane((Coord)r.left,(Coord)r.top,(Coord)(r.right-r.left),(Coord)(r.bottom-r.top));
    }

   static Coord RandomLen(Coord len)
    {
     int percent=Win64::GetTickCount()%100u;
     
     return Coord( (len/2)+((len/4)*percent)/100 );
    }
   
   static Coord RandomPos(Coord len)
    {
     int percent=Win64::GetTickCount()%100u;

     return Coord( (len*percent)/100 );
    }
   
   static Pane GetWorkPane()
    {
     Win64::Rectangle rect;
     
     SysGuard("CCore::Video::Private_Desktop::WindowsHost::GetWorkPane() : #;", Win64::SystemParametersInfoA(Win64::SPA_getWorkArea,0,&rect,0) );
     
     return ToPane(rect);
    }
   
   class WindowPaint : NoCopy
    {
      Win64::HWindow hWnd;
      Win64::PaintData pd;
      Win64::HGDevice hGD;
      
     public:
     
      explicit WindowPaint(Win64::HWindow hWnd_)
       {
        const char *format="CCore::Video::Private_Desktop::WindowsHost::WindowPaint::WindowPaint(...) : #;";
       
        if( hWnd_==0 )
          {
           Printf(Exception,format,"null hWnd");
          }
        
        hWnd=hWnd_;
        
        hGD=Win64::BeginPaint(hWnd_,&pd); 
        
        SysGuard(format,hGD!=0);
       }
       
      ~WindowPaint()
       {
        Win64::EndPaint(hWnd,&pd); 
       }
       
      Win64::HGDevice getGD() const { return hGD; } 
      
      Pane getPane() const { return ToPane(pd.rect); }
      
      bool getEraseFlag() const { return pd.erase_flag; }
    };
   
   void setTrack()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::setTrack() : #;";
     
     Win64::TrackMouseDesc desc;
     
     desc.cb=sizeof desc;
     desc.flags=track_flags;
     desc.hWnd=hWnd;
     desc.hover_time=hover_time;
    
     SysGuard(format, Win64::TrackMouseEvent(&desc) );
    }
   
   Win64::MsgResult msgProc(Win64::HWindow hWnd_,Win64::MsgCode message,Win64::MsgWParam wParam,Win64::MsgLParam lParam)
    {
     switch( message )
       {
        case Win64::WM_GetMinMaxInfo :
         {
          Win64::MinMaxInfo *info=(Win64::MinMaxInfo *)lParam;
          
          Replace_min<int>(info->max_size.x,max_size.x);
          Replace_min<int>(info->max_size.y,max_size.y);
         }
        return 0;
        
        case Win64::WM_NcCreate :
         {
          hWnd=hWnd_;
          is_alive=true;
          
          if( is_main ) HMainWindow=hWnd_;
          
          auto ret=Win64::DefWindowProcA(hWnd_,message,wParam,lParam);
          
          try { frame->alive(); } catch(...) {}
          
          return ret;
         }
        
        case Win64::WM_NcDestroy :
         {
          try { frame->dead(); } catch(...) {}
          
          hWnd=0;
          is_alive=false;
          
          if( is_main )
            {
             HMainWindow=0;
             
             Win64::PostQuitMessage(0);
            }
          
          return Win64::DefWindowProcA(hWnd_,message,wParam,lParam);
         }
        
        case Win64::WM_Paint :
         {
          WindowPaint wp(hWnd);

          if( !buf_dirty ) buf.draw(wp.getGD(),wp.getPane());
          
          frame->paintDone(Replace_null(token));
         }
        return 0;
        
        case Win64::WM_Move :
         {
          origin=ToPoint(lParam);
         }
        return 0;
        
        case Win64::WM_Size :
         {
          frame->setSize(ToSize(lParam),buf_dirty);
         }
        return 0;
        
        case Win64::WM_SetFocus :
         {
          frame->gainFocus();
         }
        return 0;
        
        case Win64::WM_KillFocus :
         {
          frame->looseFocus();
         }
        return 0;
        
        case Win64::WM_CaptureChanged :
         {
          frame->looseCapture();
         }
        return 0; 
        
        case Win64::WM_KeyDown :
         {
          unsigned repeat=lParam&0xFFFF;
          bool ext=(lParam>>24)&1;
          
          VKey vkey=ToVKey(wParam);
          KeyMod kmod=GetKeyMod(ext);
          
          if( repeat>1 )
            frame->react(UserAction::Create_RepeatKey(vkey,kmod,repeat));
          else
            frame->react(UserAction::Create_Key(vkey,kmod));
         }
        return 0;
        
        case Win64::WM_SysKeyDown :
         {
          unsigned repeat=lParam&0xFFFF;
          bool ext=(lParam>>24)&1;
          bool alt=(lParam>>29)&1;
          
          VKey vkey=ToVKey(wParam);
          KeyMod kmod=GetKeyMod(ext);
          
          if( alt ) kmod|=KeyMod_Alt;
          
          if( repeat>1 )
            frame->react(UserAction::Create_RepeatKey(vkey,kmod,repeat));
          else
            frame->react(UserAction::Create_Key(vkey,kmod));
         }
        return 0;
        
        case Win64::WM_KeyUp :
         {
          unsigned repeat=lParam&0xFFFF;
          bool ext=(lParam>>24)&1;
          
          VKey vkey=ToVKey(wParam);
          KeyMod kmod=GetKeyMod(ext);
          
          if( repeat>1 )
            frame->react(UserAction::Create_RepeatKeyUp(vkey,kmod,repeat));
          else
            frame->react(UserAction::Create_KeyUp(vkey,kmod));
         }
        return 0;
        
        case Win64::WM_SysKeyUp :
         {
          unsigned repeat=lParam&0xFFFF;
          bool ext=(lParam>>24)&1;
          bool alt=(lParam>>29)&1;
          
          VKey vkey=ToVKey(wParam);
          KeyMod kmod=GetKeyMod(ext);
          
          if( alt ) kmod|=KeyMod_Alt;
          
          if( repeat>1 )
            frame->react(UserAction::Create_RepeatKeyUp(vkey,kmod,repeat));
          else
            frame->react(UserAction::Create_KeyUp(vkey,kmod));
         }
        return 0;
        
        case Win64::WM_Char :
         {
          if( wParam<256 )
            {
             char ch=(char)wParam;
             unsigned repeat=lParam&0xFFFF;
             
             if( repeat>1 )
               frame->react(UserAction::Create_RepeatChar(ch,repeat));
             else
               frame->react(UserAction::Create_Char(ch));
            }
         }
        return 0;
        
        case Win64::WM_SysChar :
         {
          if( wParam<256 )
            {
             char ch=(char)wParam;
             unsigned repeat=lParam&0xFFFF;
             
             if( repeat>1 )
               frame->react(UserAction::Create_RepeatAltChar(ch,repeat));
             else
               frame->react(UserAction::Create_AltChar(ch));
            }
         }
        return 0;
        
        case Win64::WM_LButtonDown :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->react(UserAction::Create_LeftClick(point,mkey));
         }
        return 0;
        
        case Win64::WM_LButtonUp :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->react(UserAction::Create_LeftUp(point,mkey));
         }
        return 0;
        
        case Win64::WM_LButtonDClick :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->react(UserAction::Create_LeftDClick(point,mkey));
         }
        return 0;
        
        case Win64::WM_RButtonDown :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->react(UserAction::Create_RightClick(point,mkey));
         }
        return 0;
        
        case Win64::WM_RButtonUp :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->react(UserAction::Create_RightUp(point,mkey));
         }
        return 0;
        
        case Win64::WM_RButtonDClick :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          frame->react(UserAction::Create_RightDClick(point,mkey));
         }
        return 0;
        
        case Win64::WM_MouseMove :
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
          
          frame->react(UserAction::Create_Move(point,mkey));
         }
        return 0;
        
        case Win64::WM_MouseWheel :
         {
          MouseKey mkey=ToMouseKey(Win64::LoWord(wParam));
          Coord delta=Win64::SHiWord(wParam)/Win64::WheelDelta;
          Point point=ToPoint(lParam)-origin;
          
          frame->react(UserAction::Create_Wheel(point,mkey,delta));
         }
        return 0;
        
        case Win64::WM_MouseHover :
         {
          MouseKey mkey=ToMouseKey(wParam);
          Point point=ToPoint(lParam);
          
          track_on=false;
          
          frame->react(UserAction::Create_Hover(point,mkey));
         }
        return 0; 

        case Win64::WM_MouseLeave :
         {
          track_on=false;
          
          frame->react(UserAction::Create_Leave());
         }
        return 0;
        
        case Win64::WM_NcHitTest :
         {
          Point point=ToPoint(lParam);
          
          frame->setMouseShape(point-origin);
         }
        return Win64::HitCode_Client; 
        
        case Win64::WM_SetCursor :
         {
          // do nothing
         }
        return true;
        
        default: return Win64::DefWindowProcA(hWnd_,message,wParam,lParam);
       }
    }
   
   static Win64::MsgResult ObjWndProc(WindowsHost *obj,Win64::HWindow hWnd,Win64::MsgCode message,Win64::MsgWParam wParam,Win64::MsgLParam lParam)
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
   
   static Win64::MsgResult WndProc(Win64::HWindow hWnd,Win64::MsgCode message,Win64::MsgWParam wParam,Win64::MsgLParam lParam)
    {
     TaskEventHost.add<MsgEvent>(message,MsgEvent::Entry);
     
     if( message==Win64::WM_NcCreate )
       {
        Win64::CreateData *ctx=(Win64::CreateData *)lParam;
        
        Win64::SetWindowLongA(hWnd,0,(Win64::UPtrType)(ctx->arg));
       }
       
     void *arg=(void *)Win64::GetWindowLongA(hWnd,0);
     
     Win64::MsgResult ret;
     
     if( !arg ) 
       {
        // WM_GetMinMaxInfo comes before WM_NcCreate
       
        ret=Win64::DefWindowProcA(hWnd,message,wParam,lParam);
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
     
     Win64::MessageBoxA(HMainWindow,cap,"Abort",Win64::MessageBox_Ok|Win64::MessageBox_IconError);
    }
   
   static void ErrorMsgBox(StrLen text,StrLen title)
    {
     CapString<> cap(text);
     CapString<> cap_title(title);
     
     Win64::MessageBoxA(HMainWindow,cap,cap_title,Win64::MessageBox_Ok|Win64::MessageBox_IconError);
    }
   
   // WinControl
   // create/destroy
   
   virtual void createMain(Point max_size)
    {
     Point screen;
     
     screen.x=(Coord)Win64::GetSystemMetrics(Win64::SysMetric_DXScreen);
     screen.y=(Coord)Win64::GetSystemMetrics(Win64::SysMetric_DYScreen);
     
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
     
     Win64::HWindow hWnd=Win64::CreateWindowExA(0,
                                                Win64::MakeIntAtom(WindowClassObject.getAtom(format)),
                                                "",
                                                Win64::WindowStyle_Popup,
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
     
     Win64::HWindow hWnd=Win64::CreateWindowExA(0,
                                                Win64::MakeIntAtom(WindowClassObject.getAtom(format)),
                                                "",
                                                Win64::WindowStyle_Popup,
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
     
     Win64::HWindow hParent;
     
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
     
     Win64::HWindow hWnd=Win64::CreateWindowExA(0,
                                                Win64::MakeIntAtom(WindowClassObject.getAtom(format)),
                                                "",
                                                Win64::WindowStyle_Popup,
                                                pane.x,pane.y,pane.dx,pane.dy,
                                                hParent,0,0,
                                                (void *)this);  
     
     SysGuard(format,hWnd!=0);                  
    }
   
   virtual void destroy()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::destroy() : #;";
     
     guardAlive(format);
     
     SysGuard(format, Win64::DestroyWindow(hWnd) );
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
     
     return !Win64::EnableWindow(hWnd,en);
    }
   
   virtual void display(CmdDisplay cmd_display)
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::display(...) : #;";
     
     guardAlive(format);
     
     switch( cmd_display )
       {
        default:
        case CmdDisplay_Normal : 
          Win64::ShowWindow(hWnd,Win64::CmdShow_Normal); // error unavailable 
        break;
        
        case CmdDisplay_Minimized : 
          Win64::ShowWindow(hWnd,Win64::CmdShow_Minimized); // error unavailable
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
             
             Win64::InvalidateRect(hWnd,0,true); // ignore error
            }
         }
        break;
        
        case CmdDisplay_Restore :
         {
          if( max_flag )
            {
             max_flag=false;
            
             do_move(restore);
             
             Win64::InvalidateRect(hWnd,0,true); // ignore error
            }
         }
        break;
       }
    }
   
   virtual void show()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::show() : #;";
     
     guardAlive(format);
     
     Win64::ShowWindow(hWnd,Win64::CmdShow_Show); // error unavailable
    }
   
   virtual void hide()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::hide() : #;";
     
     guardAlive(format);
     
     Win64::ShowWindow(hWnd,Win64::CmdShow_Hide); // error unavailable
    }
   
   // drawing
   
   virtual void update()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::update() : #;";
     
     guardAlive(format);
     
     SysGuard(format, Win64::UpdateWindow(hWnd) );
    }
   
   virtual void invalidate(Pane pane,unsigned token_)
    {
     if( !pane ) return;
     
     token|=token_;
     
     Win64::Rectangle rect;
     
     rect.left=pane.x;
     rect.right=pane.x+pane.dx;
     
     rect.top=pane.y;
     rect.bottom=pane.y+pane.dy;
    
     Win64::InvalidateRect(hWnd,&rect,true); // ignore error
     
     buf_dirty=false;
    }
   
   virtual void invalidate(unsigned token_)
    {
     token|=token_;
     
     Win64::InvalidateRect(hWnd,0,true); // ignore error
     
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
     
     Win64::SetFocus(hWnd); // error unavailable
    }
   
   // mouse
   
   virtual void captureMouse()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::captureMouse() : #;";
     
     guardAlive(format);
     
     Win64::SetCapture(hWnd); // error unavailable
    }
   
   virtual void releaseMouse()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::releaseMouse() : #;";
     
     guardAlive(format);
     
     SysGuard(format, Win64::ReleaseCapture() );
    }
   
   virtual void trackMouseHover()
    {
     BitSet(track_flags,Win64::MouseTrack_Hover);
     
     hover_time=Win64::HoverTimeDefault;
     
     setTrack();
    }
   
   virtual void trackMouseHover(MSec time)
    {
     BitSet(track_flags,Win64::MouseTrack_Hover);
     
     hover_time=+time;
     
     setTrack();
    }
   
   virtual void untrackMouseHover()
    {
     BitClear(track_flags,Win64::MouseTrack_Hover);
    }
   
   virtual void trackMouseLeave()
    {
     BitSet(track_flags,Win64::MouseTrack_Leave);
     
     setTrack();
    }
   
   virtual void untrackMouseLeave()
    {
     BitClear(track_flags,Win64::MouseTrack_Leave);
    }
   
   virtual void setMouseShape(MouseShape mshape)
    {
     Win64::SetCursor(GetCursor(mshape)); // error unavailable
    }
   
   // place
   
   virtual Pane getPlace()
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::getPlace() : #;";
     
     guardAlive(format);
     
     Win64::Rectangle rect;
     
     SysGuard(format, Win64::GetWindowRect(hWnd,&rect) );
     
     return ToPane(rect);
    }
   
   void do_move(Pane pane)
    {
     const char *format="CCore::Video::Private_Desktop::WindowsHost::do_move(...) : #;";
     
     guardAlive(format);
     
     GuardPane(format,pane,max_size);
     
     unsigned pos_flags=Win64::WindowPos_NoZOrder|Win64::WindowPos_NoCopyBits|Win64::WindowPos_NoRedraw|Win64::WindowPos_DeferErase;
     
     SysGuard(format, Win64::SetWindowPos(hWnd,(Win64::HWindow)0,pane.x,pane.y,pane.dx,pane.dy,pos_flags) );
    }
   
   virtual void move(Pane pane)
    {
     max_flag=false;
     
     do_move(pane);
    }
 };

Win64::HCursor WindowsHost::CursorTable[]=
 {
  0,
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_Arrow)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_IBeam)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_Wait)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_Cross)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_Hand)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_No)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_Help)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_SizeLeftRight)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_SizeUpDown)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_SizeUpLeft)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_SizeUpRight)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_SizeAll)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_UpArrow)),
  Win64::LoadCursorA(0,Win64::MakeIntResource(Win64::SysCursor_AppStarting))
 };

WindowsHost::WindowClass WindowsHost::WindowClassObject;

Win64::HWindow WindowsHost::HMainWindow=0;

/* class WindowsDesktop */

class WindowsDesktop : public Desktop
 {
  private:
  
   static bool TestMsg()
    {
     Win64::Msg msg;
     
     return Win64::PeekMessageA(&msg,0,0,0,Win64::PeekMessage_NoRemove);
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
     return Point((Coord)Win64::GetSystemMetrics(Win64::SysMetric_DXScreen),(Coord)Win64::GetSystemMetrics(Win64::SysMetric_DYScreen));
    }
   
   virtual bool pump(unsigned lim)
    {
     for(Win64::Msg msg; lim && Win64::PeekMessageA(&msg,0,0,0,Win64::PeekMessage_Remove) ;lim--) 
       {
        if( msg.message==Win64::WM_Quit ) 
          {
           TaskEventHost.add<MsgEvent>(msg.message,MsgEvent::Stop);
          
           return false;
          }
       
        Win64::TranslateMessage(&msg);
        Win64::DispatchMessageA(&msg);
       }
       
     return true;  
    }
   
   virtual void wait(TimeScope time_scope)
    {
     if( auto t=+time_scope.get() ) 
       {
        if( TestMsg() ) return;
        
        Win64::MsgWaitForMultipleObjects(0,0,false,t,Win64::Wake_AllInput);
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
 

