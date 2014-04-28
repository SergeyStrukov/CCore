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

#include <CCore/inc/dev/DevIntHandle.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/video/VideoDevice.h>

#include <CCore/inc/dev/AM3359.LCD.h>

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
 }

/* test2() */

class VideoTest : NoCopy , Video::VideoDevice::PlugControl
 {
   ObjHook hook;
   
   Video::VideoDevice *dev;
   
  private:
   
   virtual void change(bool plug,bool power)
    {
     if( plug && power )
       {
        dev->updateVideoModeList(DefaultTimeout);
        
        dev->setVideoMode(0);
        
        switch( dev->getColorMode() )
          {
           case Video::ColorMode16 : dev->getBuf16().test(); break; 
           case Video::ColorMode24 : dev->getBuf24().test(); break; 
           case Video::ColorMode32 : dev->getBuf32().test(); break; 
          }
       }
    }
   
  public:
 
   VideoTest()
    : hook("video"),
      dev(hook)
    {
     dev->attach(this);
    }
   
   ~VideoTest()
    {
     dev->detach();
    }
 };

void test2()
 {
  VideoTest test;
  
  Task::Sleep(10_min);
 }

/* test3() */

class FBInt : public Funchor_nocopy
 {
  private:
   
   int flag = 0 ;
   ClockDiffTimer timer;
   PtrLen<ClockDiffTimer::ValueType> out;
   
   Sem sem;
   
  private:
   
   void handle_int()
    {
     using namespace AM3359::LCD;
     
     Bar bar;
     
     auto status=bar.get_IRQStatus();
     
     status.setTo(bar);
     
     if( status.maskbit(IRQStatus_RasterFrameDone) )
       {
        switch( flag )
          {
           case 0 :
            {
             flag=1;
            }
           break;
           
           case 1 :
            {
             timer.reset();
             
             flag=2;
            }
           break;
           
           case 2 :
            {
             if( +out )
               {
                *out=timer.get();
                
                ++out;
               }
             else
               {
                sem.give_int();
                   
                flag=3;
               }
            }
           break; 
          }
       }
    }
   
   Function<void (void)> function_handle_int() { return FunctionOf(this,&FBInt::handle_int); }
   
  public:
  
   FBInt() {}
   
   ~FBInt() { Dev::CleanupIntHandler(Dev::Int_LCDCINT); }
   
   void run(PtrLen<ClockDiffTimer::ValueType> out_)
    {
     flag=0;
     out=out_;
     
     using namespace AM3359::LCD;
     
     Bar bar;
     
     bar.ones_IRQStatus()
        .set(bar.to_IRQEnableClear());
     
     bar.null_IRQStatus()
        .setbit(IRQStatus_RasterFrameDone)
        .set(bar.to_IRQEnableSet());
     
     Dev::SetupIntHandler(Dev::Int_LCDCINT,function_handle_int(),15);
     
     sem.take();
     
     Dev::CleanupIntHandler(Dev::Int_LCDCINT);
     
     bar.ones_IRQStatus()
        .set(bar.to_IRQEnableClear());
    }
 };

void test3()
 {
  ClockDiffTimer::ValueType buf[10];
  
  FBInt fbint;
  
  fbint.run(Range(buf));
  
  for(auto t : Range(buf) ) Printf(Con,"#;\n",t);
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
  //test2();
  //test3();
  
  return true;
 }
 
} // namespace App
 
