/* DevVideo.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_DevVideo_h
#define CCore_inc_dev_DevVideo_h

#include <CCore/inc/dev/DevHDMI.h>
#include <CCore/inc/dev/DevLCD.h>
 
namespace CCore {
namespace Dev {

/* classes */

class VideoControl;

/* class VideoControl */

class VideoControl : NoCopy
 {
   Space video_space;
   Video::FrameBuf<Video::Color565> frame_buf;
   
  public:
  
   VideoControl();
   
   ~VideoControl();
   
   bool init();
   
   Video::FrameBuf<Video::Color565> getFrameBuf() const { return frame_buf; }
 };

} // namespace Dev 
} // namespace CCore
 
#endif
 

