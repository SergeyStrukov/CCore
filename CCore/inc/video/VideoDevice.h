/* VideoDevice.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_VideoDevice_h
#define CCore_inc_video_VideoDevice_h

#include <CCore/inc/video/FrameBuf.h>
 
namespace CCore {
namespace Video {

/* enum ColorMode */

enum ColorMode
 {
  ColorMode_none = 0,
  
  ColorMode16,
  ColorMode24,
  ColorMode32
 };

/* classes */

struct VideoMode;

struct VideoDevice;

/* struct VideoMode */

struct VideoMode
 {
  ColorMode mode;
  unsigned dx;
  unsigned dy;
  unsigned freq; // Hz
  
  VideoMode() : mode(ColorMode_none),dx(0),dy(0),freq(0) {}
  
  ColorMode operator + () const { return mode; }
  
  bool operator ! () const { return !mode; }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* struct VideoDevice */

struct VideoDevice
 {
  virtual ColorMode getColorMode()=0;
  
  virtual VideoMode getVideoMode()=0;
  
  virtual FrameBuf<Color16> getBuf16()=0;
  
  virtual FrameBuf<Color24> getBuf24()=0;
  
  virtual FrameBuf<Color32> getBuf32()=0;
  
  virtual bool updateVideoModeList(MSec timeout)=0;
  
  virtual PtrLen<const VideoMode> getVideoModeList()=0;
  
  virtual bool setVideoMode(ulen index)=0;
  
  struct PlugControl
   {
    // serialized
    
    virtual void change(bool plug,bool power)=0;
   };
  
  virtual void attach(PlugControl *ctrl)=0;
  
  virtual void detach()=0;
 };

} // namespace Video
} // namespace CCore
 
#endif
 

