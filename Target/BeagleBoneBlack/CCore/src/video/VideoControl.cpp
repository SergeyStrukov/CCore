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

#include <CCore/inc/dev/AM3359.GPIO.h>

#include <CCore/inc/dev/DevIntHandle.h>

#include <CCore/inc/Print.h>

namespace CCore {
namespace Video {

/* class VideoControl */

void VideoControl::init_first(const EDIDTimingDesc &desc,ColorMode color_mode)
 {
  hdmi.setMode(desc);
   
  lcd.enable(180); // 180 MHz clock, 90 MHz pixel_clock
   
  lcd.reset_first();
   
  switch( color_mode )
    {
     case ColorMode16 :
      {
       buf16=lcd.init_first16(desc,video_space);
       buf24=DefaultValue();
       buf32=DefaultValue();
      }
     break;
     
     case ColorMode24 :
      {
       buf16=DefaultValue();
       buf24=lcd.init_first24(desc,video_space);
       buf32=DefaultValue();
      }
     break;
     
     case ColorMode32 :
      {
       buf16=DefaultValue();
       buf24=DefaultValue();
       buf32=lcd.init_first32(desc,video_space);
      }
     break; 
    }
  
  hdmi.enableVIP();
 }

void VideoControl::init(const EDIDTimingDesc &desc,ColorMode color_mode)
 {
  hdmi.disableVIP();
  
  hdmi.setMode(desc);
   
  lcd.stop();
  
  switch( color_mode )
    {
     case ColorMode16 :
      {
       buf16=lcd.init16(desc,video_space);
       buf24=DefaultValue();
       buf32=DefaultValue();
      }
     break;
     
     case ColorMode24 :
      {
       buf16=DefaultValue();
       buf24=lcd.init24(desc,video_space);
       buf32=DefaultValue();
      }
     break;
     
     case ColorMode32 :
      {
       buf16=DefaultValue();
       buf24=DefaultValue();
       buf32=lcd.init32(desc,video_space);
      }
     break; 
    }
  
  hdmi.enableVIP();
 }

void VideoControl::process(Dev::HDMI::IntInfo info)
 {
  if( info.plug || info.power )
    {
     mevent.trigger(Event_Plug);
    }
 }

void VideoControl::work()
 {
  for(;;)
    {
     switch( mevent.wait() )
       {
        case Event_Int :
         {
          process(hdmi.getIntInfo());
          
          enableInt();
         }
        break; 
      
        case Event_Stop : return;
        
        case Event_Tick :
         {
          Hook hook(host);
          
          if( +hook )
            {
             hook->tick();
            }
         }
        break;
        
        case Event_Plug :
         {
          Hook hook(host);
          
          if( +hook )
            {
             auto detect=hdmi.detect();
             
             hook->change(detect.plug,detect.power);
            }
         }
        break; 
       }
    }
 }

void VideoControl::handle_int()
 {
  disableInt();
  
  mevent.trigger_int(Event_Int);
 }

void VideoControl::setupInt()
 {
  AM3359::GPIO::Bar bar(AM3359::GPIO::GPIO1);

  bar.set_Level0Detect(bar.get_Level0Detect()|GPIOBit);
  
  bar.set_IRQ0EnableSet(GPIOBit);
  
  Dev::SetupIntHandler(Dev::Int_GPIO1_0,function_handle_int(),15);
 }

void VideoControl::cleanupInt()
 {
  Dev::CleanupIntHandler(Dev::Int_GPIO1_0);
  
  AM3359::GPIO::Bar bar(AM3359::GPIO::GPIO1);

  bar.set_Level0Detect(bar.get_Level0Detect()&~GPIOBit);
  
  bar.set_IRQ0EnableClear(GPIOBit);
 }

void VideoControl::disableInt()
 {
  Dev::DisableInt(Dev::Int_GPIO1_0);
 }

void VideoControl::enableInt()
 {
  AM3359::GPIO::Bar bar(AM3359::GPIO::GPIO1);

  bar.set_IRQ0Status(GPIOBit);
 
  Dev::EnableInt(Dev::Int_GPIO1_0);
 }

bool VideoControl::readEDID(uint8 block[Video::EDIDLen],TimeScope time_scope,unsigned number)
 {
  Dev::HDMI::ReadEDID read(hdmi,number);
  
  for(;;)
    {
     switch( mevent.wait(time_scope) )
       {
        case 0 : return false;
      
        case Event_Int :
         {
          auto info=hdmi.getIntInfo();
          
          enableInt();
          
          if( info.edid )
            {
             read(block);
             
             return true;
            }
         }
        break;
       }
    }
 }

bool VideoControl::append(EDIDTimingDesc desc)
 {
  try
    {
     Dev::LCD::Mode lcd_mode(desc);
     Dev::HDMI::Mode hdmi_mode(desc);
    
     desc.pixel_clock=90000;
     
     desc_list.append_copy(desc);
     desc_list.append_copy(desc);
     desc_list.append_copy(desc);
     
     VideoMode mode;
     
     mode.dx=desc.hlen;
     mode.dy=desc.vlen;
     mode.freq=desc.freq();
     
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

bool VideoControl::append(const EDIDBlockDesc &desc)
 {
  if( desc.index!=EDIDBlockDesc::Desc_timing ) return false;
  
  return append(desc.desc.timing);
 }

VideoControl::VideoControl(StrLen i2c_dev_name,TaskPriority priority,ulen stack_len)
 : hdmi(i2c_dev_name),
   host("VideoControl"),
   video_space(Sys::AllocVideoSpace()),
   mevent("VideoControl"),
   ticker(mevent.function_trigger_int<Event_Tick>())
 {
  hdmi.init();
  
  asem.inc();
  
  RunFuncTask( [=] () { work(); } ,asem.function_dec(),"VideoTask",priority,stack_len);

  setupInt();
 }
   
VideoControl::~VideoControl()
 {
  cleanupInt();
  
  mevent.trigger(Event_Stop);
  
  asem.wait();
 }
   
VideoDim VideoControl::getVideoDim() 
 { 
  return video_dim; 
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
   
bool VideoControl::updateVideoModeList(MSec timeout)
 {
  mode_list.erase();
  desc_list.erase();
  
  video_dim=DefaultValue();
 
  try
    {
     uint8 buf[EDIDLen];
     
     if( !readEDID(buf,TimeScope(timeout)) ) return false;
     
     EDIDBlock edid(buf);
     
     video_dim.hlen=edid.hlen_cm*10u;
     video_dim.vlen=edid.vlen_cm*10u;
     
     return append(edid.desc[0]);
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
        init_first(desc_list[index],mode.mode);
        
        first=false;
       }
     else
       {
        init(desc_list[index],mode.mode);
       }
     
     return true;
    }
  catch(CatchType)
    {
     return false;
    }
 }
   
void VideoControl::setTick(MSec period)
 {
  ticker.start(1_msec,period);
 }

void VideoControl::attach(Control *ctrl)
 {
  host.attach(ctrl);
  
  mevent.trigger(Event_Plug);
 }
   
void VideoControl::detach()
 {
  host.detach();
  
  ticker.stop();
 }

} // namespace Video
} // namespace CCore
 

