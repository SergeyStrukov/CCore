/* VideConsole.cpp */ 
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
 
#include <CCore/inc/video/VideoConsole.h>
 
namespace CCore {
namespace Video {

/* class VideoConsole */

template <>
void VideoConsole::open<Color16>(FrameBuf<Color16> buf)
 {
  con16.init(buf);
  
  first=false;
 }

template <>
void VideoConsole::open<Color24>(FrameBuf<Color24> buf)
 {
  con24.init(buf);
  
  first=false;
 }

template <>
void VideoConsole::open<Color32>(FrameBuf<Color32> buf)
 {
  con32.init(buf);
  
  first=false;
 }

void VideoConsole::open()
 {
  Mutex::Lock lock(mutex);
  
  color_mode=ColorMode_none;
  
  if( dev->updateVideoModeList(DefaultTimeout) && dev->setVideoMode(0) )
    {
     color_mode=dev->getColorMode();
     
     switch( color_mode )
       {
        case ColorMode16 : open(dev->getBuf16()); break; 
        case ColorMode24 : open(dev->getBuf24()); break; 
        case ColorMode32 : open(dev->getBuf32()); break; 
       }
     
     if( color_mode!=ColorMode_none ) 
       {
        dev->setTick(500_msec);
       
        sem.give();
       }
    }
 }

void VideoConsole::close()
 {
  Mutex::Lock lock(mutex);
  
  color_mode=ColorMode_none;
 }

void VideoConsole::do_print(StrLen str)
 {
  switch( color_mode )
    {
     case ColorMode16 : con16.print(str); break;
     case ColorMode24 : con24.print(str); break;
     case ColorMode32 : con32.print(str); break;
    }
 }

void VideoConsole::do_tick()
 {
  switch( color_mode )
    {
     case ColorMode16 : con16.toggleMarker(); break;
     case ColorMode24 : con24.toggleMarker(); break;
     case ColorMode32 : con32.toggleMarker(); break;
    }
 }

void VideoConsole::change(bool plug,bool power)
 {
  if( plug )
    {
     if( power )
       {
        if( first )
          {
           open();
          }
       }
    }
  else
    {
     first=true;
     
     close();
    }
 }

void VideoConsole::tick()
 {
  Mutex::Lock lock(mutex);
  
  do_tick();
 }

VideoConsole::VideoConsole(StrLen video_dev_name)
 : hook(video_dev_name),
   dev(hook),
   mutex("!VideoConsole.mutex"),
   sem("!VideoConsole.sem")
 {
  dev->attach(this);
 }

VideoConsole::~VideoConsole()
 {
  dev->detach();
 }

bool VideoConsole::waitOpen(MSec timeout)
 {
  return sem.take(timeout);
 }

void VideoConsole::print(StrLen str)
 {
  Mutex::Lock lock(mutex);
  
  do_print(str);
 }

} // namespace Video
} // namespace CCore
 

