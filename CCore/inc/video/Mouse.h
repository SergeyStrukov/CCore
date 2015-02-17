/* Mouse.h */ 
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

#ifndef CCore_inc_video_Mouse_h
#define CCore_inc_video_Mouse_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Video {

/* consts */

enum MouseKey : unsigned
 {
  Mouse_Left  = 0x0001,
  Mouse_Right = 0x0002,
 
  Mouse_Shift = 0x0010,
  Mouse_Ctrl  = 0x0020
 };

inline MouseKey operator | (MouseKey a,MouseKey b) { return MouseKey(unsigned(a)|b); }

enum MouseShape : unsigned
 {
  Mouse_Null,
  Mouse_Arrow,
  Mouse_IBeem,
  Mouse_Wait,
  Mouse_Cross,
  Mouse_Hand,
  Mouse_Stop,
  Mouse_Help,
  Mouse_SizeLeftRight,
  Mouse_SizeUpDown,
  Mouse_SizeUpLeft,  // to DownRight 
  Mouse_SizeUpRight, // to DownLeft
  Mouse_SizeAll,
  Mouse_UpArrow,
  Mouse_Progress
 };

} // namespace Video
} // namespace CCore
 
#endif
 

