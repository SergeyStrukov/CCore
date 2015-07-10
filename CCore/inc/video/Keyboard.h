/* Keyboard.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_Keyboard_h
#define CCore_inc_video_Keyboard_h
 
#include <CCore/inc/PrintBits.h>

namespace CCore {
namespace Video {

/* classes */

//enum VKey;

//enum KeyMod;

/* enum VKey */

enum VKey : unsigned
 {
  VKey_Null = 0,
    
  VKey_Esc,
  VKey_F1,
  VKey_F2,
  VKey_F3,
  VKey_F4,
  VKey_F5,
  VKey_F6,
  VKey_F7,
  VKey_F8,
  VKey_F9,
  VKey_F10,
  VKey_F11,
  VKey_F12,
  
  VKey_Tilda,
  VKey_1,
  VKey_2,
  VKey_3,
  VKey_4,
  VKey_5,
  VKey_6,
  VKey_7,
  VKey_8,
  VKey_9,
  VKey_0,
  VKey_Minus,
  VKey_Equal,
  VKey_BackSlash,
  VKey_BackSpace,
  
  VKey_Tab,
  VKey_q,
  VKey_w,
  VKey_e,
  VKey_r,
  VKey_t,
  VKey_y,
  VKey_u,
  VKey_i,
  VKey_o,
  VKey_p,
  VKey_OpenBracket,
  VKey_CloseBracket,
  VKey_Enter,
  
  VKey_CapsLock,
  VKey_a,
  VKey_s,
  VKey_d,
  VKey_f,
  VKey_g,
  VKey_h,
  VKey_j,
  VKey_k,
  VKey_l,
  VKey_Semicolon,
  VKey_Quote,
  
  VKey_Shift,
  VKey_z,
  VKey_x,
  VKey_c,
  VKey_v,
  VKey_b,
  VKey_n,
  VKey_m,
  VKey_Comma,
  VKey_Period,
  VKey_Slash,
  
  VKey_Ctrl,
  VKey_Alt,
  VKey_Space,
  
  VKey_ScrollLock,
  VKey_Pause,
  
  VKey_Insert,
  VKey_Home,
  VKey_PageUp,
  VKey_Delete,
  VKey_End,
  VKey_PageDown,
  
  VKey_Up,
  VKey_Left,
  VKey_Down,
  VKey_Right,
  
  VKey_NumLock,
  VKey_NumSlash,
  VKey_NumAsterisk,
  VKey_NumMinus,
  VKey_Num7,
  VKey_Num8,
  VKey_Num9,
  VKey_NumPlus,
  VKey_Num4,
  VKey_Num5,
  VKey_Num6,
  VKey_Num1,
  VKey_Num2,
  VKey_Num3,
  VKey_NumEnter,
  VKey_NumIns,
  VKey_NumDel
 };

const char * GetTextDesc(VKey vkey);

/* enum KeyMod */

enum KeyMod : unsigned
 {
  KeyMod_Null       =      0,
    
  KeyMod_Shift      = 0x0001,
  KeyMod_Ctrl       = 0x0002,
  KeyMod_Alt        = 0x0004,
  
  KeyMod_CapsLock   = 0x0100,
  KeyMod_NumLock    = 0x0200,
  KeyMod_ScrollLock = 0x0400,
  
  KeyMod_Ext        = 0x1000
 };

inline KeyMod operator | (KeyMod a,KeyMod b) { return KeyMod(unsigned(a)|b); }

inline KeyMod operator |= (KeyMod &a,KeyMod b) { return a=(a|b); }

class PrintKeyMod
 {
   KeyMod kmod;
   
  public: 
   
   explicit PrintKeyMod(KeyMod kmod_) : kmod(kmod_) {}
   
   template <class P>
   void print(P &out) const
    {
     PrintBits<unsigned>(out,kmod)
                        (KeyMod_Shift     ,"Shift"     )
                        (KeyMod_Ctrl      ,"Ctrl"      )
                        (KeyMod_Alt       ,"Alt"       )
                        (KeyMod_CapsLock  ,"CapsLock"  )
                        (KeyMod_NumLock   ,"NumLock"   )
                        (KeyMod_ScrollLock,"ScrollLock")
                        (KeyMod_Ext       ,"Ext"       )
                        .complete();
    }
 };

inline PrintKeyMod GetTextDesc(KeyMod kmod) { return PrintKeyMod(kmod); }

} // namespace Video
} // namespace CCore
 
#endif
 

