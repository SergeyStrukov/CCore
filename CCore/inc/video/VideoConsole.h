/* VideoConsole.h */ 
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

   MultiMode<SimpleConsole> con;
   
   Sem sem;
   
  private:
   
   struct InitFunc
    {
     VideoDevice *dev;
     
     explicit InitFunc(VideoDevice *dev_) : dev(dev_) {}
     
     template <class T>
     void operator () (T &con) { con.init(dev); }      
    };
   
   struct PrintFunc
    {
     StrLen str;
     
     explicit PrintFunc(StrLen str_) : str(str_) {}
     
     template <class T>
     void operator () (T &con) { con.print(str); }
    };
   
   struct ToggleMarkerFunc
    {
     template <class T>
     void operator () (T &con) { con.toggleMarker(); }
    };
   
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
 };

} // namespace Video
} // namespace CCore
 
#endif
 

