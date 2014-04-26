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
#include <CCore/inc/video/FrameBuf.h>

#include <CCore/inc/Task.h>
 
namespace CCore {
namespace Dev {

/* classes */

class LCD;

/* class LCD */

class LCD : public Funchor_nocopy
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
     
     Mode(const Video::EDIDMode &mode);
    };
  
  private:

   struct FrameBuf16
    {
     Video::FrameBuf<Video::Color16> buf;
     void *base;
     void *lim;
     
     FrameBuf16(uint32 hlen,uint32 vlen,Space video_space);
    };
   
   struct FrameBuf24
    {
     Video::FrameBuf<Video::Color24> buf;
     void *base;
     void *lim;
     
     FrameBuf24(uint32 hlen,uint32 vlen,Space video_space);
    };
   
   struct FrameBuf32
    {
     Video::FrameBuf<Video::Color32> buf;
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
   
   void enable(uint32 clock); // MHz
   
   void reset_first();
   
   void setClock(uint32 clock); // MHz
   
   Video::FrameBuf<Video::Color16> init_first16(const Mode &mode,Space video_space);
   
   Video::FrameBuf<Video::Color24> init_first24(const Mode &mode,Space video_space);
   
   Video::FrameBuf<Video::Color32> init_first32(const Mode &mode,Space video_space);
   
   void stop();
   
   Video::FrameBuf<Video::Color16> init16(const Mode &mode,Space video_space);
   
   Video::FrameBuf<Video::Color24> init24(const Mode &mode,Space video_space);
   
   Video::FrameBuf<Video::Color32> init32(const Mode &mode,Space video_space);
 };

} // namespace Dev
} // namespace CCore
 
#endif
 

