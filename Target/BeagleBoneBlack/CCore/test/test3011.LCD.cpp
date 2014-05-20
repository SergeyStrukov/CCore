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
   
  private: 
 
   void run()
    {
     dev->updateVideoModeList();
     
     dev->setVideoMode(0);
     
     switch( dev->getColorMode() )
       {
        case Video::ColorMode16 : dev->getBuf16().test(); break;
        
        case Video::ColorMode24 : dev->getBuf24().test(); break;
        
        case Video::ColorMode32 : dev->getBuf32().test(); break;
       }
    }
   
   // Video::VideoDevice::Control
   
   virtual void change(bool plug,bool power)
    {
     if( plug && power ) run();
    }
   
   virtual void tick()
    {
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
  
  Task::Sleep(10_sec);
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
  test1();
  //test2();
  //test3();
  
  return true;
 }
 
} // namespace App
 
