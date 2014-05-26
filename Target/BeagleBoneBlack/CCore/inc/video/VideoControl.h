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

#include <CCore/inc/dev/DevHDMI.h>
#include <CCore/inc/dev/DevLCD.h>

namespace CCore {
namespace Video {

/* classes */

class VideoControl;

/* class VideoControl */

class VideoControl : public ObjBase , public VideoDevice , public Funchor_nocopy
 {
   static const uint32 GPIOBit = uint32(1)<<25 ;
   
   Dev::HDMI hdmi;
   Dev::LCD lcd;
  
   AttachmentHost<Control> host;
   
   Space video_space;
   bool first = true ;
   
   FrameBuf<Color16> buf16;
   FrameBuf<Color24> buf24;
   FrameBuf<Color32> buf32;
   
   VideoMode mode;
   
   DynArray<VideoMode> mode_list;
   DynArray<EDIDTimingDesc> desc_list;
   
   VideoDim video_dim;
   
   enum Events
    {
     Event_Int = 1,
     Event_Plug,
     Event_Tick,
     Event_Stop,
     
     EventLim
    };
   
   MultiEvent<EventLim-1> mevent;
   Ticker ticker;
   
   AntiSem asem;
   
  private:
   
   using Hook = AttachmentHost<Control>::Hook ;
   
   void init_first(const EDIDTimingDesc &desc,ColorMode color_mode);
   
   void init(const EDIDTimingDesc &desc,ColorMode color_mode);
   
   void process(Dev::HDMI::IntInfo info);
   
   void work();
   
   void handle_int();
   
   Function<void (void)> function_handle_int() { return FunctionOf(this,&VideoControl::handle_int); }
   
   void setupInt();
   
   void cleanupInt();
   
   void disableInt();
   
   void enableInt();
   
   bool readEDID(uint8 block[Video::EDIDLen],TimeScope time_scope,unsigned number=0);
   
   bool append(EDIDTimingDesc desc);
   
   bool append(const EDIDBlockDesc &desc);
  
  public:
  
   VideoControl(StrLen i2c_dev_name,TaskPriority priority=DefaultTaskPriority,ulen stack_len=DefaultStackLen);
   
   virtual ~VideoControl();
   
   // VideoDevice
   
   virtual VideoDim getVideoDim();
   
   virtual ColorMode getColorMode();
   
   virtual VideoMode getVideoMode();
   
   virtual FrameBuf<Color16> getBuf16();
   
   virtual FrameBuf<Color24> getBuf24();
   
   virtual FrameBuf<Color32> getBuf32();
   
   virtual bool updateVideoModeList(MSec timeout);
   
   virtual PtrLen<const VideoMode> getVideoModeList();
   
   virtual bool setVideoMode(ulen index);
   
   virtual void setTick(MSec period);
   
   virtual void attach(Control *ctrl);
   
   virtual void detach();
 };

} // namespace Video
} // namespace CCore
 
#endif
 

