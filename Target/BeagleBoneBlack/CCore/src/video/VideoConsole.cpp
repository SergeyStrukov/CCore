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

void VideoConsole::lock()
 {
  mutex.lock();
  
  flag=1;
 }
   
void VideoConsole::unlock()
 {
  flag=0;
  
  mutex.unlock();
 }
   
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
  Lock lock(*this);
  
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
     
     if( color_mode!=ColorMode_none ) sem.give();
    }
 }

void VideoConsole::close()
 {
  Lock lock(*this);
  
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
  Lock lock(*this);
  
  do_print(str);
 }

void VideoConsole::debug_print(StrLen str)
 {
  Dev::IntLock lock;
  
  if( !flag ) do_print(str);
 }

} // namespace Video
} // namespace CCore
 

