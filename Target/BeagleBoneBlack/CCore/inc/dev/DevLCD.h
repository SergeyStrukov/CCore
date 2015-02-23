/* DevLCD.h */
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

#ifndef CCore_inc_dev_DevLCD_h
#define CCore_inc_dev_DevLCD_h

#include <CCore/inc/video/EDID.h>
#include <CCore/inc/video/Color.h>

#include <CCore/inc/Task.h>
#include <CCore/inc/InstanceLock.h>
 
namespace CCore {
namespace Dev {

/* classes */

class LCD;

/* class LCD */

class LCD : InstanceLock<LCD> , public Funchor 
 {
  public:
  
   struct Mode
    {
     uint32 hlen;   // 16-2048 multiple of 16
     uint32 hfront; // 1-1024
     uint32 hsync;  // 1-1024
     uint32 hback;  // 1-1024
    
     uint32 vlen;   // 1-2048 
     uint32 vfront; // 0-255
     uint32 vsync;  // 1-64
     uint32 vback;  // 0-255
    
     Mode() {}
     
     Mode(const Video::EDIDTimingDesc &desc);
    };
  
  private:

   struct FrameBuf16
    {
     Video::ColorPlane plane;
     void *base;
     void *lim;
     
     FrameBuf16(uint32 hlen,uint32 vlen,Space video_space);
    };
   
   struct FrameBuf24
    {
     Video::ColorPlane plane;
     void *base;
     void *lim;
     
     FrameBuf24(uint32 hlen,uint32 vlen,Space video_space);
    };
   
   struct FrameBuf32
    {
     Video::ColorPlane plane;
     void *base;
     void *lim;
     
     FrameBuf32(uint32 hlen,uint32 vlen,Space video_space);
    };
   
   enum ColorFormat
    {
     ColorFormat16,
     ColorFormat24,
     ColorFormat32
    };
  
   void init_first();
  
   void init(const Mode &mode,void *base,void *lim,ColorFormat fmt);
   
  private:
   
   int stop_flag = 0 ;
   
   Sem sem;
   
  private:
   
   void handle_int();
   
   Function<void (void)> function_handle_int() { return FunctionOf(this,&LCD::handle_int); }
   
  public:
  
   LCD();
   
   ~LCD();
   
   // init
   
   void enable(uint32 clock); // MHz , clock <= 200 , pixel_clock == clock/2
   
   void reset_first();
   
   void setClock(uint32 clock); // MHz
   
   Video::ColorPlane init_first16(const Mode &mode,Space video_space); // Video::RawColor16
   
   Video::ColorPlane init_first24(const Mode &mode,Space video_space); // Video::RawColor24
   
   Video::ColorPlane init_first32(const Mode &mode,Space video_space); // Video::RawColor32Inv
   
   void stop();
   
   Video::ColorPlane init16(const Mode &mode,Space video_space); // Video::RawColor16
   
   Video::ColorPlane init24(const Mode &mode,Space video_space); // Video::RawColor24
   
   Video::ColorPlane init32(const Mode &mode,Space video_space); // Video::RawColor32Inv
 };

} // namespace Dev
} // namespace CCore
 
#endif
 

