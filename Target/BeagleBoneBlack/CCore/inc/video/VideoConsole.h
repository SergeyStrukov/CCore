/* VideoConsole.h */ 
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

#ifndef CCore_inc_video_VideoConsole_h
#define CCore_inc_video_VideoConsole_h

#include <CCore/inc/ObjHost.h>
#include <CCore/inc/SingleHost.h>
#include <CCore/inc/Task.h>

#include <CCore/inc/video/SimpleConsole.h>
#include <CCore/inc/video/VideoDevice.h>
 
namespace CCore {
namespace Video {

/* classes */

class VideoConsole;

/* class VideoConsole */

class VideoConsole : NoCopy , VideoDevice::Control
 {
   ObjHook hook;
   
   VideoDevice *dev;
   
   bool first = true ;
   
   Mutex mutex;

   ColorMode color_mode = ColorMode_none ;
   
   SimpleConsole<Color16> con16;
   SimpleConsole<Color24> con24;
   SimpleConsole<Color32> con32;
   
   Sem sem;
   
  private:
   
   template <class Color>
   void open(FrameBuf<Color> buf);
   
   void open();
   
   void close();
   
   void do_print(StrLen str);
   
   void do_tick();
   
  private: 
 
   // VideoDevice::Control
 
   virtual void change(bool plug,bool power);
   
   virtual void tick();
   
  public:
 
   explicit VideoConsole(StrLen video_dev_name);
   
   ~VideoConsole();
   
   bool waitOpen(MSec timeout=DefaultTimeout);
   
   void print(StrLen str);
   
   static SingleHost<VideoConsole> & GetHost();
 };

} // namespace Video
} // namespace CCore
 
#endif
 

