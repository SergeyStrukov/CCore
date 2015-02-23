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
#include <CCore/inc/video/EDID.h>
 
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/AttachmentHost.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Task.h>

#include <CCore/inc/dev/DevHDMI.h>
#include <CCore/inc/dev/DevLCD.h>
#include <CCore/inc/dev/DevBit.h>

namespace CCore {
namespace Video {

/* classes */

class VideoControl;

/* class VideoControl */

class VideoControl : public ObjBase , public VideoDevice , public Funchor_nocopy
 {
   static const auto GPIOBit = Dev::Bit(25) ;
   
   static Space VideoSpace;
   
   Dev::HDMI hdmi;
   Dev::LCD lcd;
  
   AttachmentHost<Control> host;
   
   bool first = true ;
   bool stop_on_exit = false ;
   
   VideoDim video_dim;
   VideoMode mode;
   ColorPlane plane;
   
   DynArray<VideoMode> mode_list;
   DynArray<EDIDTimingDesc> desc_list;
   
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
   
   Sem stop_sem;
   
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
   
   void stopOnExit() { stop_on_exit=true; }
   
   // VideoDevice
   
   virtual bool updateVideoModeList(MSec timeout);
   
   virtual PtrLen<const VideoMode> getVideoModeList() const;
   
   virtual bool setVideoMode(ulen index);
   
   virtual void setTick(MSec period);
   
   virtual VideoDim getVideoDim() const;
   
   virtual ColorMode getColorMode() const;
   
   virtual VideoMode getVideoMode() const;

   virtual ColorPlane getPlane() const;
   
   virtual void attach(Control *ctrl);
   
   virtual void detach();
 };

} // namespace Video
} // namespace CCore
 
#endif
 

