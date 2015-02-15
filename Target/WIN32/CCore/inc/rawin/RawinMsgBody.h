/* RawinMsgBody.h */ 
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

#ifndef CCore_inc_rawin_RawinMsgBody_h
#define CCore_inc_rawin_RawinMsgBody_h
 
#include <CCore/inc/win32/Win32gui.h>

#include <CCore/inc/rawin/RawinBase.h>

#include <CCore/inc/PrintBits.h>

/* namespace CCore */ 
 
namespace CCore {
namespace Rawin {

/* functions */ 

template <class P,class T> 
void PrintNamedVal(P &out,T val,const char *name)
 {
  if( name )
    Printf(out,"#;",name);
  else
    Printf(out,"unexpected = #;",val);
 }
 
/* classes */  

struct MessageCode;

struct HitCode;

struct MouseKey;

struct VKey;

struct CChar;

struct Utf16;

/* struct MessageCode */ 
 
struct MessageCode
 {
  Win32::MsgCode message; // Win32::WMCode
  
  explicit MessageCode(Win32::MsgCode message_) : message(message_) {}
  
  static const char * GetName(Win32::MsgCode message);
  
  template <class P>
  void print(P &out) const
   {
    if( const char *name=GetName(message) )
      Printf(out,"#;",name);
    else
      Printf(out,"MsgCode(#4.hi;)",message);
   }
 };
 
/* struct HitCode */ 

struct HitCode
 {
  Win32::MsgResult hit; // Win32::HitCode
  
  explicit HitCode(Win32::MsgResult hit_=0) : hit(hit_) {}
  
  static const char * GetName(Win32::MsgResult hit);
  
  template <class P>
  void print(P &out) const
   {
    PrintNamedVal(out,hit,GetName(hit));
   }
 };
 
/* struct MouseKey */ 

struct MouseKey
 {
  Win32::MsgWParam state; // Win32::MouseKey|
  
  explicit MouseKey(Win32::MsgWParam state_) : state(state_) {}
  
  template <class P>
  void print(P &out) const
   {
    PrintBits(out,state)(Win32::MouseKey_Left   ,"L"    )
                        (Win32::MouseKey_Right  ,"R"    )
                        (Win32::MouseKey_Middle ,"M"    )
                        (Win32::MouseKey_Shift  ,"Shift")
                        (Win32::MouseKey_Control,"Ctrl" )
                        .complete();
   }
 };
 
/* struct VKey */  
 
struct VKey
 {
  Win32::MsgWParam vkey; // Win32::VirtualKey
  
  explicit VKey(Win32::MsgWParam vkey_) : vkey(vkey_) {}
  
  static const char * GetName(Win32::MsgWParam vkey);
  
  template <class P>
  void print(P &out) const
   {
    if( const char *name=GetName(vkey) )
      {
       Printf(out,"#;",name);
      } 
    else
      {
       if( ( vkey>='0' && vkey<='9' ) || ( vkey>='A' && vkey<='Z' ) )
         {
          Putch(out,'\'',char(vkey),'\'');
         }
       else
         {
          Printf(out,"VKey(#.h;)",vkey);
         } 
      } 
   }
 };
 
/* struct CChar */  

struct CChar
 {
  char ch; // ascii code
  
  explicit CChar(char ch_) : ch(ch_) {}
  
  template <class P>
  void print(P &out) const
   {
    if( ch>=0 && ch<128 )
      {
       if( ch>=32 )
         {
          Putch(out,'\'',ch,'\'');
         }
       else
         {
          switch( ch )
            {
             case '\t' : Printf(out,"'\\t'"); break;
             case '\n' : Printf(out,"'\\n'"); break;
             case '\v' : Printf(out,"'\\v'"); break;
             case '\f' : Printf(out,"'\\f'"); break;
             case '\r' : Printf(out,"'\\r'"); break;
             
             case 8  : Printf(out,"'\\bs'"); break;
             case 27 : Printf(out,"'\\esc'"); break;
             
             default: Printf(out,"Ascii(#.h;)",ch);
            }
         }  
      }
    else
      {
       Putch(out,'`',ch,'`');
      }
   }
 };
 
/* struct Utf16 */  
 
struct Utf16
 {
  Win32::MsgWParam code;
  
  explicit Utf16(Win32::MsgWParam code_) : code(code_) {}
  
  template <class P>
  void print(P &out) const
   {
    if( code<256 )  
      {
       Printf(out,"#;",CChar((char)code));
      }
    else
      {
       Printf(out,"Utf16(#.h;)",code);
      } 
   }
 };
 
/* namespace MsgBody */ 

namespace MsgBody {

/* functions */ 

inline Pane ToPane(Win32::Rectangle r)
 {
  return Pane(r.left,r.top,r.right-r.left,r.bottom-r.top);
 }
 
inline Point ToPoint(Win32::Point p)
 {
  return Point(p.x,p.y);
 }
 
inline Point ToPoint(Win32::MsgLParam lParam)
 {
  return Point(Win32::SLoWord(lParam),Win32::SHiWord(lParam));
 }
 
inline Point ToSize(Win32::MsgLParam lParam)
 {
  return Point(Win32::LoWord(lParam),Win32::HiWord(lParam));
 }
 
/* bodies */ 

struct General
 {
  Win32::MsgWParam wParam;
  Win32::MsgLParam lParam;
  
  void init(Win32::MsgWParam wParam_,Win32::MsgLParam lParam_)
   {
    wParam=wParam_;
    lParam=lParam_;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"raw (#;(#.h;),#;(#.h;))",wParam,wParam,lParam,lParam);
   }
   
  template <class P> 
  static void printResult(P &out,Win32::MsgResult result)
   {
    Printf(out,"#;(#.h;)",result,result);
   }
 };
 
struct ZeroResult
 {
  template <class P> 
  static void printResult(P &out,Win32::MsgResult result)
   {
    if( result )
      Printf(out,"unexpected = #;(#;)",result,result);
    else
      Printf(out,"ok");
   }
 };
 
struct BoolResult
 {
  template <class P> 
  static void printResult(P &out,Win32::MsgResult result)
   {
    switch( result )
      {
       case true : Printf(out,"true"); break;
       
       case false : Printf(out,"false"); break;
       
       default: Printf(out,"unexpected = #;(#;)",result,result);
      }
   }
 };
 
struct EmptyBase
 {
  void init(Win32::MsgWParam,Win32::MsgLParam) {}
   
  template <class P> 
  void print(P &) const
   {
   }
 };
 
struct Empty : EmptyBase , ZeroResult
 {
 }; 
   
struct Empty_Bool : EmptyBase , BoolResult
 {
 }; 
   
 /* general */ 
 
struct NcCreate : BoolResult
 {
  Win32::CreateData *ctx;
  
  void init(Win32::MsgWParam,Win32::MsgLParam lParam)
   {
    ctx=(Win32::CreateData *)lParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"-> (...)");
   }
 };
 
struct Create
 {
  Win32::CreateData *ctx;
  
  void init(Win32::MsgWParam,Win32::MsgLParam lParam)
   {
    ctx=(Win32::CreateData *)lParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"-> (...)");
   }
   
  template <class P> 
  static void printResult(P &out,Win32::MsgResult result)
   {
    switch( result )
      {
       case 0 : Printf(out,"ok"); break;
       
       case -1 : Printf(out,"fail"); break;
       
       default: Printf(out,"unexpected = #;(#.h;)",result,result);
      }
   }
 };
 
struct Enable : ZeroResult
 {
  bool enable;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam)
   { 
    enable=wParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#;",enable?"enable":"disable");
   }
 }; 
 
struct NcPaint : ZeroResult
 {
  Win32::HRegion frame;
  
  void init(Win32::MsgWParam wParam,Win32::MsgLParam)
   { 
    frame=(Win32::HRegion)wParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"(...)");
   }
 }; 
 
struct EraseBackground
 {
  Win32::HGDevice hGD;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam)
   { 
    hGD=(Win32::HGDevice)wParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"(...)");
   }
   
  template <class P> 
  static void printResult(P &out,Win32::MsgResult result)
   {
    Putobj(out,result?"erased":"dirty");
   }
 }; 
 
struct ShowWindow : ZeroResult
 {
  bool show;
  Win32::MsgLParam reason; // Win32::ShowReason
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam) 
   { 
    show=wParam;
    reason=lParam;
   }
   
  static const char * GetName(Win32::MsgLParam reason); 
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; ",show?"show":"hide");
    
    PrintNamedVal(out,reason,GetName(reason));
   }
 };
 
struct GetMinMaxInfo
 {
  Win32::MinMaxInfo *ctx;
   
  void init(Win32::MsgWParam,Win32::MsgLParam lParam)
   { 
    ctx=(Win32::MinMaxInfo *)lParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"max_size=#; max_pos=#; max_track_size=#; min_track_size=#;",
                ToPoint(ctx->max_size),
                ToPoint(ctx->max_position),
                ToPoint(ctx->max_track_size),
                ToPoint(ctx->min_track_size));
   }
   
  template <class P> 
  void printResult(P &out,Win32::MsgResult result) const
   {
    ZeroResult::printResult(out,result);
    out.put(' ');
    print(out);
   }
 };
 
struct Move : ZeroResult
 {
  Point point; // client 
   
  void init(Win32::MsgWParam,Win32::MsgLParam lParam)
   { 
    point=ToPoint(lParam);
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#;",point);
   }
 };
 
struct Size : ZeroResult
 {
  Win32::MsgWParam type; // SizeType
  Point size;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    type=wParam;
    size=ToSize(lParam);
   }
   
  static const char * GetName(Win32::MsgWParam type); 
   
  template <class P> 
  void print(P &out) const
   {
    PrintNamedVal(out,type,GetName(type));
    
    Printf(out," #;",size);
   }
 }; 
  
struct Moving
 {
  Win32::Rectangle *ctx;
   
  void init(Win32::MsgWParam,Win32::MsgLParam lParam)
   { 
    ctx=(Win32::Rectangle *)lParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#;",ToPane(*ctx));
   }
   
  template <class P> 
  void printResult(P &out,Win32::MsgResult result) const
   {
    BoolResult::printResult(out,result);
    out.put(' ');
    print(out);
   }
 }; 
 
struct Sizing
 {
  Win32::MsgWParam type; // Win32::SizingType
  Win32::Rectangle *ctx;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    type=wParam;
    ctx=(Win32::Rectangle *)lParam;
   }
   
  static const char * GetName(Win32::MsgWParam type); 
   
  template <class P> 
  void print(P &out) const
   {
    PrintNamedVal(out,type,GetName(type));
    
    Printf(out," #;",ToPane(*ctx));
   }
   
  template <class P> 
  void printResult(P &out,Win32::MsgResult result) const
   {
    BoolResult::printResult(out,result);
    out.put(' ');
    print(out);
   }
 }; 
 
struct NcActivate : BoolResult
 {
  bool active;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam) 
   { 
    active=wParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#;",active?"active":"inactive");
   }
 };
 
struct Activate : ZeroResult
 {
  Win32::MsgWParam activity; // Win32::ActivityType
  bool minimized;
  Win32::HWindow other;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    activity=Win32::LoWord(wParam);
    minimized=Win32::HiWord(wParam);
    
    other=(Win32::HWindow)lParam;
   }
   
  static const char * GetName(Win32::MsgWParam activity); 
   
  template <class P> 
  void print(P &out) const
   {
    PrintNamedVal(out,activity,GetName(activity));
    
    Printf(out,"#;",minimized?" minimized":"");
   }
 }; 
 
struct ActivateApp : ZeroResult
 {
  bool active;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam)
   { 
    active=wParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#;",active?"active":"inactive");
   }
 };
 
struct Command : ZeroResult
 {
  Win32::MsgWParam cmd_id;
  Win32::MsgWParam notify_code;
  Win32::HControl hCtrl;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    cmd_id=Win32::LoWord(wParam); 
    notify_code=Win32::HiWord(wParam);
     
    hCtrl=(Win32::HControl)lParam; 
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"cmd_id=#; notify_code=#;",cmd_id,notify_code);
   }
 }; 
   
struct SysCommand : ZeroResult
 {
  Win32::MsgWParam sys_cmd; // Win32::SysCommand
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam)
   { 
    sys_cmd=wParam&0xFFF0;
   }
   
  static const char * GetName(Win32::MsgWParam sys_cmd); 
   
  template <class P> 
  void print(P &out) const
   {
    PrintNamedVal(out,sys_cmd,GetName(sys_cmd));
   }
 }; 
 
struct PosChange
 {
  Win32::WindowPos *ctx;
   
  void init(Win32::MsgWParam,Win32::MsgLParam lParam)
   { 
    ctx=(Win32::WindowPos *)lParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    PrintBits(out,ctx->flags)(Win32::WindowPos_NoSize        ,"NoSize"        )
                             (Win32::WindowPos_NoMove        ,"NoMove"        )
                             (Win32::WindowPos_NoZOrder      ,"NoZOrder"      )
                             (Win32::WindowPos_NoRedraw      ,"NoRedraw"      )
                             (Win32::WindowPos_NoActivate    ,"NoActivate"    )
                             (Win32::WindowPos_FrameChanged  ,"FrameChanged"  )
                             (Win32::WindowPos_ShowWindow    ,"ShowWindow"    )
                             (Win32::WindowPos_HideWindow    ,"HideWindow"    )
                             (Win32::WindowPos_NoCopyBits    ,"NoCopyBits"    )
                             (Win32::WindowPos_NoOwnerZOrder ,"NoOwnerZOrder" )
                             (Win32::WindowPos_NoSendChanging,"NoSendChanging")
                             (Win32::WindowPos_DeferErase    ,"DeferErase"    )
                             (Win32::WindowPos_AsyncWindowPos,"AsyncWindowPos")
                             .complete();
    
    Pane pane(ctx->x,ctx->y,ctx->dx,ctx->dy);
    
    Printf(out," #;",pane);
   }
   
  template <class P> 
  void printResult(P &out,Win32::MsgResult result) const
   {
    BoolResult::printResult(out,result);
    out.put(' ');
    print(out);
   }
 }; 
 
struct EnterIdle : ZeroResult
 {
  bool from_menu;
  Win32::HWindow hWnd;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   {
    from_menu=(wParam==Win32::MsgFrom_Menu);
    hWnd=(Win32::HWindow)lParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#;",from_menu?"menu":"dialog");
   }
 }; 
 
struct EndSession : ZeroResult
 {
  bool ending;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam)
   { 
    ending=wParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#;",ending?"ending":"???");
   }
 }; 
 
 /* other */ 
 
 /* menu */ 
 
struct ContextMenu : ZeroResult
 {
  Win32::HWindow hWnd;
  Point point; // screen
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    hWnd=(Win32::HWindow)wParam;
    point=ToPoint(lParam);
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#;",point);
   }
 }; 
 
struct MenuLoop : ZeroResult
 {
  bool popup_menu;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam)
   { 
    popup_menu=wParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#;",popup_menu?"popup menu":"menu");
   }
 }; 
  
struct InitMenu : ZeroResult
 {
  Win32::HMenu hMenu;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam)
   { 
    hMenu=(Win32::HMenu)wParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"(...)");
   }
 };  
  
struct InitMenuPopup : ZeroResult
 {
  Win32::HMenu hMenu;
  Win32::MsgLParam index;
  bool wnd_menu;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    hMenu=(Win32::HMenu)wParam;
    
    index=Win32::LoWord(lParam);
    wnd_menu=Win32::HiWord(lParam);
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"index=#; #;",index,wnd_menu?"window menu":"");
   }
 };  
  
struct UninitMenuPopup : ZeroResult
 {
  Win32::HMenu hMenu;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam)
   { 
    hMenu=(Win32::HMenu)wParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"(...)");
   }
 };  
  
struct MenuSelect : ZeroResult
 {
  Win32::HMenu hMenu;
  Win32::MsgWParam index;
  Win32::MsgWParam flags;
  bool closed;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    index=Win32::LoWord(wParam);
    flags=Win32::HiWord(wParam);
    
    hMenu=(Win32::HMenu)lParam;
    
    closed=( flags==0xFFFF && lParam==0 );
   }
   
  template <class P> 
  void print(P &out) const
   {
    if( closed )
      {
       Printf(out,"closed");
      } 
    else
      {
       PrintBits(out,flags)(Win32::Menu_Grayed     ,"Grayed"     )
                           (Win32::Menu_Disabled   ,"Disabled"   )
                           (Win32::Menu_Bitmap     ,"Bitmap"     )
                           (Win32::Menu_Checked    ,"Checked"    )
                           (Win32::Menu_Popup      ,"Popup"      )
                           (Win32::Menu_Highlight  ,"Highlight"  )
                           (Win32::Menu_Ownerdraw  ,"Ownerdraw"  )
                           (Win32::Menu_Sysmenu    ,"Sysmenu"    )
                           (Win32::Menu_MouseSelect,"MouseSelect")
                           .complete();
       
       Printf(out," index=#;",index);
      }
   }
 };  
  
 /* keyboard input */ 
 
struct KeyDown : ZeroResult
 {
  Win32::MsgWParam vkey; // Win32::VirtualKey
  unsigned repeat;
  unsigned scan;
  bool ext;
  bool prev;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    vkey=wParam;
    
    repeat=lParam&0xFFFF;
    scan=(lParam>>16)&0xFF;
    ext=(lParam>>24)&1;
    prev=(lParam>>30)&1;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; repeat=#; scan=#; #;prev=#;",VKey(vkey),repeat,scan,ext?"ext ":"",prev?"down":"up");
   }
 }; 
 
struct KeyUp : ZeroResult
 {
  Win32::MsgWParam vkey; // Win32::VirtualKey
  unsigned repeat;
  unsigned scan;
  bool ext;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    vkey=wParam;
    
    repeat=lParam&0xFFFF;
    scan=(lParam>>16)&0xFF;
    ext=(lParam>>24)&1;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; repeat=#; scan=#; #;",VKey(vkey),repeat,scan,ext?"ext ":"");
   }
 }; 
 
struct Char : ZeroResult
 {
  Win32::MsgWParam code; // UTF-16
  unsigned repeat;
  unsigned scan;
  bool ext;
  bool prev;
  bool alt;
  bool trans;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    code=wParam;
    
    repeat=lParam&0xFFFF;
    scan=(lParam>>16)&0xFF;
    ext=(lParam>>24)&1;
    prev=(lParam>>30)&1;
    alt=(lParam>>29)&1;
    trans=(lParam>>31)&1;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; repeat=#; scan=#; #;prev=#;#; #;",Utf16(code),repeat,scan,ext?"ext ":"",prev?"down":"up",alt?" Alt":"",trans?"released":"pressed");
   }
 }; 
 
struct SysKeyDown : ZeroResult
 {
  Win32::MsgWParam vkey; // Win32::VirtualKey
  unsigned repeat;
  unsigned scan;
  bool ext;
  bool prev;
  bool alt;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    vkey=wParam;
    
    repeat=lParam&0xFFFF;
    scan=(lParam>>16)&0xFF;
    ext=(lParam>>24)&1;
    prev=(lParam>>30)&1;
    alt=(lParam>>29)&1;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; repeat=#; scan=#; #;prev=#;#;",VKey(vkey),repeat,scan,ext?"ext ":"",prev?"down":"up",alt?" Alt":"");
   }
 }; 
 
struct SysKeyUp : ZeroResult
 {
  Win32::MsgWParam vkey; // Win32::VirtualKey
  unsigned repeat;
  unsigned scan;
  bool ext;
  bool alt;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    vkey=wParam;
    
    repeat=lParam&0xFFFF;
    scan=(lParam>>16)&0xFF;
    ext=(lParam>>24)&1;
    alt=(lParam>>29)&1;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; repeat=#; scan=#; #;",VKey(vkey),repeat,scan,ext?"ext ":"");
   }
 }; 
 
struct Focus : ZeroResult
 {
  Win32::HWindow hWnd;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam)
   { 
    hWnd=(Win32::HWindow)wParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"(...)");
   }
 }; 
 
 /* mouse input */ 
 
struct NcHitTest
 {
  Point point; // screen
   
  void init(Win32::MsgWParam,Win32::MsgLParam lParam)
   { 
    point=ToPoint(lParam);
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#;",point);
   }
   
  template <class P> 
  static void printResult(P &out,Win32::MsgResult result)
   {
    Printf(out,"#;",HitCode(result));
   }
 }; 
 
struct SetCursor : BoolResult
 {
  Win32::HWindow hWnd;
  Win32::MsgResult hit; // Win32::HitCode
  Win32::MsgCode message;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    hWnd=(Win32::HWindow)wParam;
    
    hit=Win32::SLoWord(lParam);
    message=Win32::HiWord(lParam);
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; #;",HitCode(hit),MessageCode(message));
   }
 }; 
 
struct NcMouse : ZeroResult
 {
  Win32::MsgResult hit; // Win32::HitCode
  Point point; // client
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   {
    hit=wParam;
    point=ToPoint(lParam);
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; #;",HitCode(hit),point);
   }
 }; 
 
struct Mouse : ZeroResult
 {
  Win32::MsgWParam state; // Win32::MouseKey|
  Point point;            // client
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    state=wParam;
    point=ToPoint(lParam);
   }
   
  bool pressed() const { return state&(Win32::MouseKey_Left|Win32::MouseKey_Right); }
  
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; #;",MouseKey(state),point);
   }
 }; 
 
struct MouseWheel : ZeroResult
 {
  int wheel;
  Win32::MsgWParam state; // Win32::MouseKey|
  Point point;            // screen
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    wheel=Win32::SHiWord(wParam);
    state=Win32::LoWord(wParam);
    
    point=ToPoint(lParam);
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; #; #;",MouseKey(state),point,wheel);
   }
 }; 
 
struct MouseActivate
 {
  Win32::HWindow hWnd;
  Win32::MsgResult hit; // Win32::HitCode
  Win32::MsgCode message;
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
    hWnd=(Win32::HWindow)wParam;
    
    hit=Win32::SLoWord(lParam);
    message=Win32::HiWord(lParam);
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#; #;",HitCode(hit),MessageCode(message));
   }
   
  static const char * GetName(Win32::MsgResult result);
  
  template <class P> 
  static void printResult(P &out,Win32::MsgResult result)
   {
    PrintNamedVal(out,result,GetName(result));
   }
 }; 
 
struct CaptureChange : ZeroResult
 {
  Win32::HWindow hWnd;
   
  void init(Win32::MsgWParam,Win32::MsgLParam lParam)
   { 
    hWnd=(Win32::HWindow)lParam;
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"(...)");
   }
 }; 
 
#if 0
   
struct 
 {
   
  void init(Win32::MsgWParam wParam,Win32::MsgLParam lParam)
   { 
   }
   
  template <class P> 
  void print(P &out) const
   {
   }
 }; 
 
#endif 
   
} // namespace MsgBody
 
} // namespace Rawin
} // namespace CCore
 
#endif
 

