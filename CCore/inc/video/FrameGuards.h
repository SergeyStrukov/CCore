/* FrameGuards.h */ 
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

#ifndef CCore_inc_video_FrameGuards_h
#define CCore_inc_video_FrameGuards_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Video {

/* functions */

void GuardNoClient();

void GuardNotDead();

} // namespace Video
} // namespace CCore
 
#endif
 

