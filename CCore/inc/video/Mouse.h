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

#include <CCore/inc/PrintBits.h>
 
namespace CCore {
namespace Video {

/* classes */

//enum MouseKey;

//enum MouseShape;

/* enum MouseKey */

enum MouseKey : unsigned
 {
  MouseKey_Null  =      0,
    
  MouseKey_Left  = 0x0001,
  MouseKey_Right = 0x0002,
 
  MouseKey_Shift = 0x0010,
  MouseKey_Ctrl  = 0x0020,
  MouseKey_Alt   = 0x0040
 };

inline MouseKey operator | (MouseKey a,MouseKey b) { return MouseKey(unsigned(a)|b); }

inline MouseKey operator |= (MouseKey &a,MouseKey b) { return a=(a|b); }

class PrintMouseKey
 {
   MouseKey mkey;
   
  public: 
   
   explicit PrintMouseKey(MouseKey mkey_) : mkey(mkey_) {}
   
   template <class P>
   void print(P &out) const
    {
     PrintBits<unsigned>(out,mkey)
                        (MouseKey_Left , "Left")
                        (MouseKey_Right,"Right")
                        (MouseKey_Shift,"Shift")
                        (MouseKey_Ctrl , "Ctrl")
                        (MouseKey_Alt  ,  "Alt")
                        .complete();
    }
 };

inline PrintMouseKey GetTextDesc(MouseKey mkey) { return PrintMouseKey(mkey); }

/* enum MouseShape */

enum MouseShape : unsigned
 {
  Mouse_Null = 0,
    
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
 

