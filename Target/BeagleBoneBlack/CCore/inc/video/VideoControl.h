/* VideoControl.h */ 
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

#ifndef CCore_inc_video_VideoControl_h
#define CCore_inc_video_VideoControl_h

#include <CCore/inc/video/VideoDevice.h>
 
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/AttachmentHost.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Task.h>
#include <CCore/inc/video/EDID.h>

namespace CCore {
namespace Video {

/* classes */

class VideoControl;

/* class VideoControl */

class VideoControl : public ObjBase , public VideoDevice
 {
   AttachmentHost<PlugControl> host;
   
   Space video_space;
   bool first = true ;
   
   FrameBuf<Color16> buf16;
   FrameBuf<Color24> buf24;
   FrameBuf<Color32> buf32;
   
   VideoMode mode;
   
   DynArray<VideoMode> mode_list;
   DynArray<EDIDMode> edid_list;
   
   Event event;
   Atomic stop_flag;
   AntiSem asem;
   
  private:
   
   using Hook = AttachmentHost<PlugControl>::Hook ;
   
   void init_first(const EDIDMode &mode,ColorMode color_mode);
   
   void init(const EDIDMode &mode,ColorMode color_mode);
   
   void work();
  
  public:
  
   VideoControl(TaskPriority priority=DefaultTaskPriority,ulen stack_len=DefaultStackLen);
   
   virtual ~VideoControl();
   
   // VideoDevice
   
   virtual ColorMode getColorMode();
   
   virtual VideoMode getVideoMode();
   
   virtual FrameBuf<Color16> getBuf16();
   
   virtual FrameBuf<Color24> getBuf24();
   
   virtual FrameBuf<Color32> getBuf32();
   
   virtual bool updateVideoModeList(MSec timeout);
   
   virtual PtrLen<const VideoMode> getVideoModeList();
   
   virtual bool setVideoMode(ulen index);
   
   virtual void attach(PlugControl *ctrl);
   
   virtual void detach();
 };

} // namespace Video
} // namespace CCore
 
#endif
 

