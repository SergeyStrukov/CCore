/* DevVideo.cpp */ 
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
 
#include <CCore/inc/dev/DevVideo.h>

#include <CCore/inc/sys/SysMemSpace.h>
 
namespace CCore {
namespace Dev {

/* class VideoControl */

VideoControl::VideoControl()
 : video_space(Sys::AllocVideoSpace())
 {
 }
   
VideoControl::~VideoControl()
 {
 }
   
bool VideoControl::init()
 {
  Video::EDIDMode mode;
  
  HDMI hdmi;

  hdmi.init();
  
  auto detect=hdmi.detect();
  
  if( !detect.plug ) return false;
  
  if( !hdmi.waitForPower(5_min) ) return false;
   
  uint8 block[Video::EDIDLen];
   
  hdmi.readEDID(block);
   
  mode=Video::EDIDMode(block);
   
  mode.pixel_clock=100000;
   
  hdmi.setMode(mode);
   
  LCD lcd;
   
  lcd.enable(200);
   
  lcd.reset_first();
   
  frame_buf=lcd.init_first(mode,video_space);
  
  hdmi.enableVIP();
  
  return true;
 }

} // namespace Dev 
} // namespace CCore
 

