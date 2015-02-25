/* Keyboard.cpp */ 
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
 
#include <CCore/inc/video/Keyboard.h>
 
namespace CCore {
namespace Video {

/* enum VKey */

const char * GetTextDesc(VKey vkey)
 {
  static const char *const Table[]=
   {
    "Null",
    
    "Esc",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    
    "~",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",
    "-",
    "=",
    "\\",
    "BackSpace",
    
    "Tab",
    "q",
    "w",
    "e",
    "r",
    "t",
    "y",
    "u",
    "i",
    "o",
    "p",
    "[",
    "]",
    "Enter",
    
    "CapsLock",
    "a",
    "s",
    "d",
    "f",
    "g",
    "h",
    "j",
    "k",
    "l",
    ";",
    "'",
    
    "Shift",
    "z",
    "x",
    "c",
    "v",
    "b",
    "n",
    "m",
    ",",
    ".",
    "/",
    
    "Ctrl",
    "Alt",
    "Space",
    
    "ScrollLock",
    "Pause",
    
    "Insert",
    "Home",
    "PageUp",
    "Delete",
    "End",
    "PageDown",
    
    "Up",
    "Left",
    "Down",
    "Right",
    
    "NumLock",
    "Num/",
    "Num*",
    "Num-",
    "Num7",
    "Num8",
    "Num9",
    "Num+",
    "Num4",
    "Num5",
    "Num6",
    "Num1",
    "Num2",
    "Num3",
    "NumEnter",
    "NumIns",
    "NumDel"
   };
  
  return (vkey<DimOf(Table))?Table[vkey]:"???";
 }

} // namespace Video
} // namespace CCore
 

