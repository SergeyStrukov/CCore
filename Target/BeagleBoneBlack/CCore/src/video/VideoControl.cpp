/* VideoControl.cpp */ 
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
 
#include <CCore/inc/video/VideoControl.h>
 
#include <CCore/inc/sys/SysMemSpace.h>

#include <CCore/inc/dev/DevHDMI.h>
#include <CCore/inc/dev/DevLCD.h>

namespace CCore {
namespace Video {

/* class VideoControl */

void VideoControl::init_first(const EDIDMode &mode,ColorMode color_mode)
 {
  Dev::HDMI hdmi;

  hdmi.setMode(mode);
   
  Dev::LCD lcd;
   
  lcd.enable(180);
   
  lcd.reset_first();
   
  switch( color_mode )
    {
     case ColorMode16 :
      {
       buf16=lcd.init_first16(mode,video_space);
       buf24=DefaultValue();
       buf32=DefaultValue();
      }
     break;
     
     case ColorMode24 :
      {
       buf16=DefaultValue();
       buf24=lcd.init_first24(mode,video_space);
       buf32=DefaultValue();
      }
     break;
     
     case ColorMode32 :
      {
       buf16=DefaultValue();
       buf24=DefaultValue();
       buf32=lcd.init_first32(mode,video_space);
      }
     break; 
    }
  
  hdmi.enableVIP();
 }

void VideoControl::init(const EDIDMode &mode,ColorMode color_mode)
 {
  Dev::HDMI hdmi;

  hdmi.disableVIP();
  
  hdmi.setMode(mode);
   
  Dev::LCD lcd;
   
  lcd.stop();
  
  switch( color_mode )
    {
     case ColorMode16 :
      {
       buf16=lcd.init16(mode,video_space);
       buf24=DefaultValue();
       buf32=DefaultValue();
      }
     break;
     
     case ColorMode24 :
      {
       buf16=DefaultValue();
       buf24=lcd.init24(mode,video_space);
       buf32=DefaultValue();
      }
     break;
     
     case ColorMode32 :
      {
       buf16=DefaultValue();
       buf24=DefaultValue();
       buf32=lcd.init32(mode,video_space);
      }
     break; 
    }
  
  hdmi.enableVIP();
 }

void VideoControl::work()
 {
  for(;;)
    {
     event.wait();
     
     if( stop_flag ) return;
     
     Hook hook(host);
     
     if( +hook )
       {
        Dev::HDMI::Detect detect;
       
        {
         Dev::HDMI hdmi;
 
         detect=hdmi.detect();
        }
        
        hook->change(detect.plug,detect.power);
       }
    }
 }

VideoControl::VideoControl(TaskPriority priority,ulen stack_len)
 : host("Video::VideoControl"),
   video_space(Sys::AllocVideoSpace())
 {
  {
   Dev::I2C i2c(Dev::I2C_0);
  
   i2c.enable();
   i2c.reset();
  }
  
  {
   Dev::HDMI hdmi;

   hdmi.init();
  }
  
  asem.inc();
  
  RunFuncTask( [=] () { work(); } ,asem.function_dec(),"VideoTask",priority,stack_len);
 }
   
VideoControl::~VideoControl()
 {
  stop_flag=1;
  
  event.trigger();
  
  asem.wait();
 }
   
ColorMode VideoControl::getColorMode()
 {
  return mode.mode;
 }
   
VideoMode VideoControl::getVideoMode()
 {
  return mode;
 }
   
FrameBuf<Color16> VideoControl::getBuf16()
 {
  return buf16;
 }
   
FrameBuf<Color24> VideoControl::getBuf24()
 {
  return buf24;
 }
   
FrameBuf<Color32> VideoControl::getBuf32()
 {
  return buf32;
 }
   
bool VideoControl::updateVideoModeList(MSec timeout) // TODO
 {
  mode_list.erase();
  edid_list.erase();
 
  try
    {
     Dev::HDMI hdmi;
    
     uint8 block[EDIDLen];
     
     if( !hdmi.readEDID(block,TimeScope(timeout)) ) return false;
     
     EDIDMode edid(block);
     
     if( !edid.hlen || !edid.vlen || edid.hlen>2048 || edid.vlen>2048 || (edid.hlen&15) ) return false;
     
     edid.pixel_clock=90000;
     
     edid_list.append_copy(edid);
     edid_list.append_copy(edid);
     edid_list.append_copy(edid);
     
     VideoMode mode;
     
     mode.dx=edid.hlen;
     mode.dy=edid.vlen;
     mode.freq=edid.freq();
     
     mode.mode=ColorMode16;
     
     mode_list.append_copy(mode);
     
     mode.mode=ColorMode24;
     
     mode_list.append_copy(mode);
     
     mode.mode=ColorMode32;
     
     mode_list.append_copy(mode);
     
     return true;
    }
  catch(CatchType)
    {
     return false;
    }
 }
   
PtrLen<const VideoMode> VideoControl::getVideoModeList()
 {
  return Range_const(mode_list);
 }
   
bool VideoControl::setVideoMode(ulen index)
 {
  if( index>=mode_list.getLen() ) return false;
  
  mode=mode_list[index];
  
  try
    {
     if( first )
       {
        init_first(edid_list[index],mode.mode);
        
        first=false;
       }
     else
       {
        init(edid_list[index],mode.mode);
       }
     
     return true;
    }
  catch(CatchType)
    {
     return false;
    }
 }
   
void VideoControl::attach(PlugControl *ctrl)
 {
  host.attach(ctrl);
  
  event.trigger();
 }
   
void VideoControl::detach()
 {
  host.detach();
 }

} // namespace Video
} // namespace CCore
 

