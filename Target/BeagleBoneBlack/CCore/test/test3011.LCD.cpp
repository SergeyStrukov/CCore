/* test3011.LCD.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/video/VideoDevice.h>

#include <CCore/inc/dev/AM3359.CONTROL.h>

namespace App {

namespace Private_3011 {

/* test1() */

void test1()
 {
  for(ulen cnt=100; cnt ;cnt--)
    {
     Printf(Con,"cnt = #;\n",cnt);
     
     Task::Sleep(1_sec);
    }
  
  Printf(Con,"\n");
 }

/* test2() */

class Test : NoCopy , Video::VideoDevice::Control 
 {
   ObjHook hook;
   
   Video::VideoDevice *dev;
   
   ulen index;
   ulen count;
   
  private: 
 
   void update()
    {
     dev->setVideoMode(index);
     
     auto mode=dev->getColorMode();
     
     Printf(Con,"update(#;)\n",mode);
     
     switch( mode )
       {
        case Video::ColorMode16 : Video::FrameBuf<Video::RawColor16>(dev->getPlane()).test(); break;
        
        case Video::ColorMode24 : Video::FrameBuf<Video::RawColor24>(dev->getPlane()).test(); break;
        
        case Video::ColorMode32Inv : Video::FrameBuf<Video::RawColor32Inv>(dev->getPlane()).test(); break;
       }
    }
   
   void run()
    {
     dev->updateVideoModeList();
     
     auto list=dev->getVideoModeList();
     
     Printf(Con,"run(#;)\n",list.len);
     
     for(ulen i=0; i<list.len ;i++) 
       {
        auto mode=list[i];
        
        Printf(Con,"  mode = #; dx = #; dy = #; freq = #;\n",mode.mode,mode.dx,mode.dy,mode.freq);
       }
     
     index=0;
     count=list.len;
     
     dev->setTick(5_sec);
     
     update();
    }
   
   // Video::VideoDevice::Control
   
   virtual void change(bool plug,bool power)
    {
     if( plug && power ) run();
    }
   
   virtual void tick()
    {
     if( ++index>=count ) index=0;
     
     update();
    }
   
  public:
 
   explicit Test(StrLen video_dev_name)
    : hook(video_dev_name),
      dev(hook)
    {
     dev->attach(this);
    }
   
   ~Test()
    {
     dev->detach();
    }
 };

void test2()
 {
  Test test("video");
  
  Task::Sleep(1000_sec);
 }

/* test3() */

void test3()
 {
  using namespace AM3359::CONTROL;
  
  Bar bar;

  Printf(Con,"#;\n",bar.get_Conf_GPMC_A9());
 }

} // namespace Private_3011
 
using namespace Private_3011; 
 
/* Testit<3011> */ 

template<>
const char *const Testit<3011>::Name="Test3011 LCD";

template<>
bool Testit<3011>::Main() 
 {
  //test1();
  test2();
  //test3();
  
  return true;
 }
 
} // namespace App
 
