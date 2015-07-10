/* Shade.cpp */ 
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
 
#include <CCore/inc/video/Shade.h>

#include <CCore/inc/video/SmoothDrawArt.h>
 
namespace CCore {
namespace Video {

/* functions */

void Shade(const DrawBuf &buf,ColorName color,Clr alpha)
 {
  Smooth::DrawArt art(buf);
  
  art.erase(color,alpha);
 }

} // namespace Video 
} // namespace CCore
 

