/* FrameGuards.cpp */ 
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
 
#include <CCore/inc/video/FrameGuards.h>
 
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* guards */

void GuardNoClient()
 {
  Printf(Exception,"CCore::Video::GuardNoClient() : no client");
 }

void GuardNotDead()
 {
  Printf(Exception,"CCore::Video::GuardNotDead() : window is alive");
 }

} // namespace Video
} // namespace CCore
 

