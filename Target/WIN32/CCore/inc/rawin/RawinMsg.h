/* RawinMsg.h */ 
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

#ifndef CCore_inc_rawin_RawinMsg_h
#define CCore_inc_rawin_RawinMsg_h

#include <CCore/inc/rawin/RawinMsgBody.h>
 
namespace CCore {
namespace Rawin {

/* classes */ 

struct GeneralCodeType;

template <Win32::MsgCode Code> struct DefinedCodeType;

template <Win32::MsgCode Code> struct MsgAdapter;

template <Win32::MsgCode Code> struct Msg;

struct MsgOther;
 
/* struct GeneralCodeType */ 

struct GeneralCodeType
 {
  Win32::MsgCode code;
  
  explicit GeneralCodeType(Win32::MsgCode code_) : code(code_) {}
  
  template <class P>
  void print(P &out) const
   {
    Putobj(out,MessageCode(code));
   }
 };
 
/* struct DefinedCodeType<Win32::MsgCode Code> */ 
 
template <Win32::MsgCode Code> 
struct DefinedCodeType
 {
  explicit DefinedCodeType(Win32::MsgCode) {}
  
  static const char * GetName() { return "DefinedCodeType<???" ">"; }
  
  template <class P>
  void print(P &out) const
   {
    Putobj(out,GetName());
   }
 };
 
/* struct MsgAdapter<Win32::MsgCode Code> */ 
 
template <Win32::MsgCode Code> 
struct MsgAdapter
 {
  using CodeType = GeneralCodeType ;
  using BodyType = MsgBody::General ;
 };
 
#define CCORE_TEMP(Code,Body)                                                   \
                                                                                \
template <>                                                                     \
inline const char * DefinedCodeType<Win32::Code>::GetName() { return #Code; }   \
                                                                                \
template <>                                                                     \
struct MsgAdapter<Win32::Code>                                                  \
 {                                                                              \
  using CodeType = DefinedCodeType<Win32::Code> ;                               \
  using BodyType = MsgBody::Body ;                                              \
 };                                                                             \
 
 /* general */ 
 
CCORE_TEMP(WM_NcCreate             ,NcCreate        )
CCORE_TEMP(WM_Create               ,Create          )

CCORE_TEMP(WM_NcDestroy            ,Empty           )
CCORE_TEMP(WM_Destroy              ,Empty           )
CCORE_TEMP(WM_Close                ,Empty           )
CCORE_TEMP(WM_Enable               ,Enable          )
CCORE_TEMP(WM_CancelMode           ,Empty           )
CCORE_TEMP(WM_QueryOpen            ,Empty_Bool      )

CCORE_TEMP(WM_NcPaint              ,NcPaint         )
CCORE_TEMP(WM_Paint                ,Empty           )
CCORE_TEMP(WM_EraseBackground      ,EraseBackground )

CCORE_TEMP(WM_ShowWindow           ,ShowWindow      )
CCORE_TEMP(WM_GetMinMaxInfo        ,GetMinMaxInfo   )
CCORE_TEMP(WM_Move                 ,Move            )
CCORE_TEMP(WM_Size                 ,Size            )
CCORE_TEMP(WM_Moving               ,Moving          )
CCORE_TEMP(WM_Sizing               ,Sizing          )
CCORE_TEMP(WM_EnterSizeMove        ,Empty           )
CCORE_TEMP(WM_ExitSizeMove         ,Empty           )

CCORE_TEMP(WM_NcActivate           ,NcActivate      )
CCORE_TEMP(WM_Activate             ,Activate        )
CCORE_TEMP(WM_ActivateApp          ,ActivateApp     )

CCORE_TEMP(WM_Command              ,Command         )
CCORE_TEMP(WM_SysCommand           ,SysCommand      )

CCORE_TEMP(WM_WindowPosChanging    ,PosChange       )
CCORE_TEMP(WM_WindowPosChanged     ,PosChange       )

CCORE_TEMP(WM_EnterIdle            ,EnterIdle       )

CCORE_TEMP(WM_EndSession           ,EndSession      )

 /* other */ 

CCORE_TEMP(WM_SyncPaint            ,Empty           )

 /* menu */ 

CCORE_TEMP(WM_ContextMenu          ,ContextMenu     )

CCORE_TEMP(WM_EnterMenuLoop        ,MenuLoop        )
CCORE_TEMP(WM_ExitMenuLoop         ,MenuLoop        )

CCORE_TEMP(WM_InitMenu             ,InitMenu        )

CCORE_TEMP(WM_InitMenuPopup        ,InitMenuPopup   )
CCORE_TEMP(WM_UninitMenuPopup      ,UninitMenuPopup )

CCORE_TEMP(WM_MenuSelect           ,MenuSelect      )

 /* keyboard input */ 

CCORE_TEMP(WM_KeyDown              ,KeyDown         )
CCORE_TEMP(WM_KeyUp                ,KeyUp           )
CCORE_TEMP(WM_Char                 ,Char            )
CCORE_TEMP(WM_DeadChar             ,Char            )

CCORE_TEMP(WM_SysKeyDown           ,SysKeyDown      )
CCORE_TEMP(WM_SysKeyUp             ,SysKeyUp        )
CCORE_TEMP(WM_SysChar              ,Char            )
CCORE_TEMP(WM_SysDeadChar          ,Char            )

CCORE_TEMP(WM_SetFocus             ,Focus           )
CCORE_TEMP(WM_KillFocus            ,Focus           )

 /* mouse input */ 

CCORE_TEMP(WM_NcHitTest            ,NcHitTest       )
CCORE_TEMP(WM_SetCursor            ,SetCursor       )

CCORE_TEMP(WM_NcLButtonDown        ,NcMouse         )
CCORE_TEMP(WM_NcLButtonUp          ,NcMouse         )
CCORE_TEMP(WM_NcLButtonDClick      ,NcMouse         )

CCORE_TEMP(WM_NcRButtonDown        ,NcMouse         )
CCORE_TEMP(WM_NcRButtonUp          ,NcMouse         )
CCORE_TEMP(WM_NcRButtonDClick      ,NcMouse         )

CCORE_TEMP(WM_NcMButtonDown        ,NcMouse         )
CCORE_TEMP(WM_NcMButtonUp          ,NcMouse         )
CCORE_TEMP(WM_NcMButtonDClick      ,NcMouse         )

CCORE_TEMP(WM_NcMouseMove          ,NcMouse         )
CCORE_TEMP(WM_NcMouseLeave         ,Empty           )
CCORE_TEMP(WM_NcMouseHover         ,NcMouse         )

CCORE_TEMP(WM_LButtonDown          ,Mouse           )
CCORE_TEMP(WM_LButtonUp            ,Mouse           )
CCORE_TEMP(WM_LButtonDClick        ,Mouse           )

CCORE_TEMP(WM_RButtonDown          ,Mouse           )
CCORE_TEMP(WM_RButtonUp            ,Mouse           )
CCORE_TEMP(WM_RButtonDClick        ,Mouse           )

CCORE_TEMP(WM_MButtonDown          ,Mouse           )
CCORE_TEMP(WM_MButtonUp            ,Mouse           )
CCORE_TEMP(WM_MButtonDClick        ,Mouse           )

CCORE_TEMP(WM_MouseMove            ,Mouse           )
CCORE_TEMP(WM_MouseLeave           ,Empty           )
CCORE_TEMP(WM_MouseHover           ,Mouse           )

CCORE_TEMP(WM_MouseActivate        ,MouseActivate   )
CCORE_TEMP(WM_MouseWheel           ,MouseWheel      )

CCORE_TEMP(WM_CaptureChanged       ,CaptureChange   )
 
#undef CCORE_TEMP
 
/* struct Msg<Win32::MsgCode Code> */  

template <Win32::MsgCode Code> 
struct Msg
 {
  using CodeType = typename MsgAdapter<Code>::CodeType ;
  using BodyType = typename MsgAdapter<Code>::BodyType ;
 
  BodyType body;
  
  Msg() : body() {}
  
  Msg(Win32::MsgWParam wParam,Win32::MsgLParam lParam) { body.init(wParam,lParam); }
  
  Msg(Win32::MsgCode /* message==Code */,Win32::MsgWParam wParam,Win32::MsgLParam lParam) { body.init(wParam,lParam); }
 
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; #;",CodeType(Code),body);
   }
  
  template <class P> 
  void printResult(P &out,Win32::MsgResult result) const
   { 
    body.printResult(out,result);
   }
 };
 
/* struct MsgOther */ 

struct MsgOther
 {
  using CodeType = GeneralCodeType ;
  using BodyType = MsgBody::General ;
 
  Win32::MsgCode message;
  BodyType body;
  
  MsgOther() : message(0),body() {}
  
  MsgOther(Win32::MsgCode message_,Win32::MsgWParam wParam,Win32::MsgLParam lParam) : message(message_) { body.init(wParam,lParam); }
 
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; #;",CodeType(message),body);
   }
 
  template <class P> 
  void printResult(P &out,Win32::MsgResult result) const
   { 
    body.printResult(out,result);
   }
 };
 
} // namespace Rawin
} // namespace CCore
 
#endif
 

