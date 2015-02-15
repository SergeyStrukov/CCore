/* RawinMsgBody.cpp */ 
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
 
#include <CCore/inc/rawin/RawinMsgBody.h>
 
namespace CCore {
namespace Rawin {

#define CCORE_NAME(N,T) case Win32::N : return T;

#define CCORE_SELFNAME(N) case Win32::N : return #N;

/* struct MessageCode */ 

const char * MessageCode::GetName(Win32::MsgCode message)
 {
  switch( message )
    {
     CCORE_SELFNAME(WM_Create)             // +
     CCORE_SELFNAME(WM_Destroy)            // +
     CCORE_SELFNAME(WM_Move)               // +
     CCORE_SELFNAME(WM_Size)               // +
     CCORE_SELFNAME(WM_Activate)           // +
     CCORE_SELFNAME(WM_SetFocus)           // +
     CCORE_SELFNAME(WM_KillFocus)          // +
     CCORE_SELFNAME(WM_Enable)             // +
     CCORE_SELFNAME(WM_Paint)              // +
     CCORE_SELFNAME(WM_Close)              // +
     CCORE_SELFNAME(WM_Quit)               // +
     CCORE_SELFNAME(WM_QueryOpen)          // +
     CCORE_SELFNAME(WM_EraseBackground)    // +
     CCORE_SELFNAME(WM_EndSession)         // +
     CCORE_SELFNAME(WM_ShowWindow)         // +
     CCORE_SELFNAME(WM_ActivateApp)        // +
     CCORE_SELFNAME(WM_CancelMode)         // +
     CCORE_SELFNAME(WM_SetCursor)          // + 
     CCORE_SELFNAME(WM_MouseActivate)      // +
     CCORE_SELFNAME(WM_GetMinMaxInfo)      // +
     CCORE_SELFNAME(WM_WindowPosChanging)  // +
     CCORE_SELFNAME(WM_WindowPosChanged)   // +
     CCORE_SELFNAME(WM_ContextMenu)        // +
     CCORE_SELFNAME(WM_NcCreate)           // +
     CCORE_SELFNAME(WM_NcDestroy)          // + 
     CCORE_SELFNAME(WM_NcHitTest)          // +
     CCORE_SELFNAME(WM_NcPaint)            // +
     CCORE_SELFNAME(WM_NcActivate)         // +
     CCORE_SELFNAME(WM_SyncPaint)          // +
     CCORE_SELFNAME(WM_NcMouseMove)        // +
     CCORE_SELFNAME(WM_NcLButtonDown)      // + 
     CCORE_SELFNAME(WM_NcLButtonUp)        // +
     CCORE_SELFNAME(WM_NcLButtonDClick)    // +
     CCORE_SELFNAME(WM_NcRButtonDown)      // +
     CCORE_SELFNAME(WM_NcRButtonUp)        // +
     CCORE_SELFNAME(WM_NcRButtonDClick)    // + 
     CCORE_SELFNAME(WM_NcMButtonDown)      // +
     CCORE_SELFNAME(WM_NcMButtonUp)        // +
     CCORE_SELFNAME(WM_NcMButtonDClick)    // +
     CCORE_SELFNAME(WM_KeyDown)            // +
     CCORE_SELFNAME(WM_KeyUp)              // +
     CCORE_SELFNAME(WM_Char)               // +
     CCORE_SELFNAME(WM_DeadChar)           // +
     CCORE_SELFNAME(WM_SysKeyDown)         // + 
     CCORE_SELFNAME(WM_SysKeyUp)           // +
     CCORE_SELFNAME(WM_SysChar)            // +
     CCORE_SELFNAME(WM_SysDeadChar)        // +   
     CCORE_SELFNAME(WM_Command)            // +
     CCORE_SELFNAME(WM_SysCommand)         // +
     CCORE_SELFNAME(WM_InitMenu)           // +
     CCORE_SELFNAME(WM_InitMenuPopup)      // + 
     CCORE_SELFNAME(WM_MenuSelect)         // +
     CCORE_SELFNAME(WM_EnterIdle)          // +
     CCORE_SELFNAME(WM_UninitMenuPopup)    // +
     CCORE_SELFNAME(WM_MouseMove)          // +
     CCORE_SELFNAME(WM_LButtonDown)        // +
     CCORE_SELFNAME(WM_LButtonUp)          // + 
     CCORE_SELFNAME(WM_LButtonDClick)      // +
     CCORE_SELFNAME(WM_RButtonDown)        // +
     CCORE_SELFNAME(WM_RButtonUp)          // +
     CCORE_SELFNAME(WM_RButtonDClick)      // +
     CCORE_SELFNAME(WM_MButtonDown)        // +
     CCORE_SELFNAME(WM_MButtonUp)          // +
     CCORE_SELFNAME(WM_MButtonDClick)      // + 
     CCORE_SELFNAME(WM_MouseWheel)         // +
     CCORE_SELFNAME(WM_EnterMenuLoop)      // +
     CCORE_SELFNAME(WM_ExitMenuLoop)       // +
     CCORE_SELFNAME(WM_Sizing)             // + 
     CCORE_SELFNAME(WM_CaptureChanged)     // +
     CCORE_SELFNAME(WM_Moving)             // +
     CCORE_SELFNAME(WM_EnterSizeMove)      // +
     CCORE_SELFNAME(WM_ExitSizeMove)       // +
     CCORE_SELFNAME(WM_NcMouseHover)       // +
     CCORE_SELFNAME(WM_MouseHover)         // +
     CCORE_SELFNAME(WM_NcMouseLeave)       // +
     CCORE_SELFNAME(WM_MouseLeave)         // +
   
     default: return 0;
    }
 }
 
/* struct HitCode */ 

const char * HitCode::GetName(Win32::MsgResult hit)
 {
  switch( hit )
    {
     CCORE_NAME(HitCode_Error,"Error")
     CCORE_NAME(HitCode_Transparent,"Transparent")
     CCORE_NAME(HitCode_Nowhere,"Nowhere")
     CCORE_NAME(HitCode_Client,"Client")
     CCORE_NAME(HitCode_Caption,"Caption")
     CCORE_NAME(HitCode_SysMenu,"SysMenu")
     CCORE_NAME(HitCode_Growbox,"Growbox")
     CCORE_NAME(HitCode_Menu,"Menu")
     CCORE_NAME(HitCode_HScroll,"HScroll")
     CCORE_NAME(HitCode_VScroll,"VScroll")
     CCORE_NAME(HitCode_MinButton,"MinButton")
     CCORE_NAME(HitCode_MaxButton,"MaxButton")
     CCORE_NAME(HitCode_Left,"Left")
     CCORE_NAME(HitCode_Right,"Right")
     CCORE_NAME(HitCode_Top,"Top")
     CCORE_NAME(HitCode_TopLeft,"TopLeft")
     CCORE_NAME(HitCode_TopRight,"TopRight")
     CCORE_NAME(HitCode_Bottom,"Bottom")
     CCORE_NAME(HitCode_BottomLeft,"BottomLeft")
     CCORE_NAME(HitCode_BottomRight,"BottomRight")
     CCORE_NAME(HitCode_Border,"Border")
     CCORE_NAME(HitCode_Object,"Object")
     CCORE_NAME(HitCode_Close,"Close")
     CCORE_NAME(HitCode_Help,"Help")

     default: return 0;
    }
 }
 
/* struct VKey */  

const char * VKey::GetName(Win32::MsgWParam vkey)
 {
  switch( vkey )
    {
     CCORE_SELFNAME(VK_Cancel)
     CCORE_SELFNAME(VK_Back)
     CCORE_SELFNAME(VK_Tab)
     CCORE_SELFNAME(VK_Clear)
     CCORE_SELFNAME(VK_Return)
     CCORE_SELFNAME(VK_Shift)
     CCORE_SELFNAME(VK_Control)
     CCORE_SELFNAME(VK_Alt)
     CCORE_SELFNAME(VK_Pause)
     CCORE_SELFNAME(VK_CapsLock)
     CCORE_SELFNAME(VK_Escape)
     CCORE_SELFNAME(VK_Space)
     CCORE_SELFNAME(VK_PgUp)
     CCORE_SELFNAME(VK_PgDown)
     CCORE_SELFNAME(VK_End)
     CCORE_SELFNAME(VK_Home)
     CCORE_SELFNAME(VK_Left)
     CCORE_SELFNAME(VK_Up)
     CCORE_SELFNAME(VK_Right)
     CCORE_SELFNAME(VK_Down)
     CCORE_SELFNAME(VK_Select)
     CCORE_SELFNAME(VK_Print)
     CCORE_SELFNAME(VK_Execute)
     CCORE_SELFNAME(VK_Snapshot)
     CCORE_SELFNAME(VK_Insert)
     CCORE_SELFNAME(VK_Delete)
     CCORE_SELFNAME(VK_Help)
     CCORE_SELFNAME(VK_LeftWin)
     CCORE_SELFNAME(VK_RightWin)
     CCORE_SELFNAME(VK_Apps)
     CCORE_SELFNAME(VK_Sleep)
     CCORE_SELFNAME(VK_Numpad0)
     CCORE_SELFNAME(VK_Numpad1)
     CCORE_SELFNAME(VK_Numpad2)
     CCORE_SELFNAME(VK_Numpad3)
     CCORE_SELFNAME(VK_Numpad4)
     CCORE_SELFNAME(VK_Numpad5)
     CCORE_SELFNAME(VK_Numpad6)
     CCORE_SELFNAME(VK_Numpad7)
     CCORE_SELFNAME(VK_Numpad8)
     CCORE_SELFNAME(VK_Numpad9)
     CCORE_SELFNAME(VK_Mul)
     CCORE_SELFNAME(VK_Add)
     CCORE_SELFNAME(VK_Separator)
     CCORE_SELFNAME(VK_Sub)
     CCORE_SELFNAME(VK_Decimal)
     CCORE_SELFNAME(VK_Div)
     CCORE_SELFNAME(VK_F1)
     CCORE_SELFNAME(VK_F2)
     CCORE_SELFNAME(VK_F3)
     CCORE_SELFNAME(VK_F4)
     CCORE_SELFNAME(VK_F5)
     CCORE_SELFNAME(VK_F6)
     CCORE_SELFNAME(VK_F7)
     CCORE_SELFNAME(VK_F8)
     CCORE_SELFNAME(VK_F9)
     CCORE_SELFNAME(VK_F10)
     CCORE_SELFNAME(VK_F11)
     CCORE_SELFNAME(VK_F12)
     CCORE_SELFNAME(VK_NumLock)
     CCORE_SELFNAME(VK_Scroll)
     CCORE_SELFNAME(VK_Colon)
     CCORE_SELFNAME(VK_Plus)
     CCORE_SELFNAME(VK_Comma)
     CCORE_SELFNAME(VK_Minus)
     CCORE_SELFNAME(VK_Period)
     CCORE_SELFNAME(VK_Slash)
     CCORE_SELFNAME(VK_Tilda)
     CCORE_SELFNAME(VK_OBracket)
     CCORE_SELFNAME(VK_BackSlash)
     CCORE_SELFNAME(VK_CBracket)
     CCORE_SELFNAME(VK_Quote)
 
     default: return 0; 
    }
 }
 
/* struct MsgBody::ShowWindow */ 
 
const char * MsgBody::ShowWindow::GetName(Win32::MsgLParam reason)
 {
  switch( reason )
    {
     CCORE_NAME(ShowReason_ShowWindow,"ShowWindow")
     CCORE_NAME(ShowReason_ParentClosing,"ParentClosing")
     CCORE_NAME(ShowReason_OtherZoom,"OtherZoom")
     CCORE_NAME(ShowReason_ParentOpening,"ParentOpening")
     CCORE_NAME(ShowReason_OtherUnzoom,"OtherUnzoom")

     default: return 0; 
    }
 }
 
/* struct MsgBody::Size */ 
 
const char * MsgBody::Size::GetName(Win32::MsgWParam type)
 {
  switch( type )
    {
     CCORE_NAME(Size_Restored,"Restored")
     CCORE_NAME(Size_Minimized,"Minimized")
     CCORE_NAME(Size_Maximized,"Maximized")
     CCORE_NAME(Size_MaxShow,"MaxShow")
     CCORE_NAME(Size_MaxHide,"MaxHide")
      
     default: return 0;
    }
 }
 
/* struct MsgBody::Sizing */ 
 
const char * MsgBody::Sizing::GetName(Win32::MsgWParam type)
 {
  switch( type )
    {
     CCORE_NAME(Sizing_Left,"Left")
     CCORE_NAME(Sizing_Right,"Right")
     CCORE_NAME(Sizing_Top,"Top")
     CCORE_NAME(Sizing_TopLeft,"TopLeft")
     CCORE_NAME(Sizing_TopRight,"TopRight")
     CCORE_NAME(Sizing_Bottom,"Bottom")
     CCORE_NAME(Sizing_BottomLeft,"BottomLeft")
     CCORE_NAME(Sizing_BottomRight,"BottomRight")
      
     default: return 0;
    }
 }
 
/* struct MsgBody::Activate */ 

const char * MsgBody::Activate::GetName(Win32::MsgWParam activity)
 {
  switch( activity )
    {
     CCORE_NAME(Activity_Inactive,"Inactive")
     CCORE_NAME(Activity_Active,"Active")
     CCORE_NAME(Activity_ClickActive,"ClickActive")
      
     default: return 0;
    };
 }
 
/* struct MsgBody::SysCommand */  
 
const char * MsgBody::SysCommand::GetName(Win32::MsgWParam sys_cmd)
 {
  switch( sys_cmd )
    {
     CCORE_NAME(SysCommand_Size,"Size")
     CCORE_NAME(SysCommand_Move,"Move")
     CCORE_NAME(SysCommand_Minimize,"Minimize")
     CCORE_NAME(SysCommand_Maximize,"Maximize")
     CCORE_NAME(SysCommand_NextWindow,"NextWindow")
     CCORE_NAME(SysCommand_PrevWindow,"PrevWindow")
     CCORE_NAME(SysCommand_Close,"Close")
     CCORE_NAME(SysCommand_VScroll,"VScroll")
     CCORE_NAME(SysCommand_HScroll,"HScroll")
     CCORE_NAME(SysCommand_MouseMenu,"MouseMenu")
     CCORE_NAME(SysCommand_KeyMenu,"KeyMenu")
     CCORE_NAME(SysCommand_Arrange,"Arrange")
     CCORE_NAME(SysCommand_Restore,"Restore")
     CCORE_NAME(SysCommand_TaskList,"TaskList")
     CCORE_NAME(SysCommand_ScreenSave,"ScreenSave")
     CCORE_NAME(SysCommand_HotKey,"HotKey")
     CCORE_NAME(SysCommand_Default,"Default")
     CCORE_NAME(SysCommand_MonitorPower,"MonitorPower")
     CCORE_NAME(SysCommand_ContextHelp,"ContextHelp")
       
     default: return 0;
    }
 }
 
/* struct MsgBody::MouseActivate */ 
 
const char * MsgBody::MouseActivate::GetName(Win32::MsgResult result)
 {
  switch( result )
    {
     CCORE_NAME(Mouse_Activate,"Activate")
     CCORE_NAME(Mouse_ActivateAndEat,"ActivateAndEat")
     CCORE_NAME(Mouse_NoActivate,"NoActivate")
     CCORE_NAME(Mouse_NoActivateAndEat,"NoActivateAndEat")
      
     default: return 0;
    }
 }
 
} // namespace Rawin
} // namespace CCore
 

