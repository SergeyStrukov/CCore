/* Shade.h */ 
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

#ifndef CCore_inc_video_Shade_h
#define CCore_inc_video_Shade_h

#include <CCore/inc/video/DrawBuf.h>
 
namespace CCore {
namespace Video {

/* functions */

void Shade(const DrawBuf &buf,VColor vc,Clr alpha);

} // namespace Video 
} // namespace CCore
 
#endif
 

