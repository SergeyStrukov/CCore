/* FrameWindow.cpp */ 
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
 
#include <CCore/inc/video/FrameWindow.h>
 
namespace CCore {
namespace Video {

/* enum CmdDisplay */

const char * GetTextDesc(CmdDisplay cmd_display)
 {
  switch( cmd_display )
    {
     case CmdDisplay_Normal    : return "Normal";
     case CmdDisplay_Minimized : return "Minimized";
     case CmdDisplay_Maximized : return "Maximized";
     case CmdDisplay_Restore   : return "Restore";
     
     default: return "???";
    }
 }

} // namespace Video
} // namespace CCore
 

