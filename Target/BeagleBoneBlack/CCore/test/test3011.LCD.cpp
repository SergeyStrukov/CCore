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
#include <CCore/inc/dev/AM3359.GPIO.h>
#include <CCore/inc/dev/AM3359.CONTROL.h>
#include <CCore/inc/dev/NXP.HDMI.h>
#include <CCore/inc/dev/DevI2C.h>

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

class VideoTest : NoCopy , Video::VideoDevice::Control
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
   
   virtual void tick() {}
   
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

/* test4() */

class Test : NoCopy
 {
   class RegRW : NoCopy
    {
      Dev::I2C dev;
      
      uint8 slave;
      
     private:
      
      void setSlave(uint8 address)
       {
        if( address!=slave )
          {
           dev.setSlave7(address);
          
           slave=address;
          }
       }
      
     public:
      
      RegRW()
       : dev(Dev::I2C_0),
         slave(0)
       {
        dev.init_fast();
       }
      
      ~RegRW()
       {
       }
      
      void setCEC() { setSlave(0x34); }
      
      void setHDMI() { setSlave(0x70); }
      
      uint8 get(uint8 address) 
       {
        uint8 ret;
        
        dev.exchange(Range_const(&address,1),Range(&ret,1));
        
        return ret;
       }
      
      void set(uint8 address,uint8 value) 
       {
        uint8 temp[]={address,value};
        
        dev.write(Range_const(temp));
       }
      
      void set(uint8 address,uint8 value1,uint8 value2) 
       {
        uint8 temp[]={address,value1,value2};
        
        dev.write(Range_const(temp));
       }
    };
   
   class CECRegRW : NoCopy
    {
      RegRW &dev;
      
     public:
      
      explicit CECRegRW(RegRW &dev_) : dev(dev_) {}
  
      typedef uint8 AddressType; 
  
      template <class UInt>
      UInt get(AddressType address);
      
      template <class UInt>
      void set(AddressType address,UInt value);
    };
   
   RegRW regRW;
   
   NXP::HDMI::CECBar<CECRegRW> barCEC;
   
  public:
   
   Test();
   
   ~Test();
   
   void enableInt();
   
   struct Info
    {
     NXP::HDMI::Type_CECStatus status;
     NXP::HDMI::Type_CECIntStatus int_status;
     NXP::HDMI::Type_CECIntSource int_source;
     
     bool operator != (const Info &obj) const
      {
       return status!=obj.status || 
              int_status!=obj.int_status ||
              int_source!=obj.int_source ;
      }
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"#; #; #;",status,int_status,int_source);
      }
    };
   
   bool testInt();
   
   Info test();
 };

template <>
uint8 Test::CECRegRW::get<uint8>(AddressType address)
 {
  dev.setCEC();
  
  return dev.get(address);
 }

template <>
void Test::CECRegRW::set<uint8>(AddressType address,uint8 value)
 {
  dev.setCEC();
  
  dev.set(address,value);
 }

Test::Test()
 : barCEC(regRW)
 {
 }

Test::~Test()
 {
 }

void Test::enableInt()
 {
  using namespace NXP::HDMI;
  
  barCEC.null_CECIntEnable()
        .setbit(CECIntEnable_RxSense|CECIntEnable_Plug)
        .setTo(barCEC);
 }

bool Test::testInt()
 {
  AM3359::GPIO::Bar1 bar;

  return bar.get_DataIn()&(1u<<25);
 }

auto Test::test() -> Info
 {
  Info ret;
  
  ret.int_status=barCEC.get_CECIntStatus();
  ret.status=barCEC.get_CECStatus();
  ret.int_source=barCEC.get_CECIntSource();
  
  return ret;
 }

class Engine : public Funchor_nocopy
 {
   static const uint32 GPIOBit = uint32(1)<<25 ;
  
   enum Events
    {
     StopEvent = 1,
     IntEvent
    };
   
   MultiEvent<2> mevent;
   
   AntiSem asem;
   
   MSecDiffTimer timer;
   
  private:
  
   void process(Test::Info info)
    {
     Printf(Con,"[#;] #;\n",timer.get(),info);
    }
   
   void work()
    {
     for(;;)
       {
        switch( mevent.wait() )
          {
           case StopEvent : return;
           
           case IntEvent :
            {
             Test test;
             
             process(test.test());
     
             AM3359::GPIO::Bar1 bar;

             bar.set_IRQ0Status(GPIOBit);
            
             Dev::EnableInt(Dev::Int_GPIO1_0);
            }
           break;
          }
       }
    }
  
   void handle_int()
    {
     Dev::DisableInt(Dev::Int_GPIO1_0);
     
     mevent.trigger_int(IntEvent);
    }
   
   Function<void (void)> function_handle_int() { return FunctionOf(this,&Engine::handle_int); }
  
  public:
  
   Engine()
    {
     {
      Test test;
      
      test.enableInt();
     }
     
     asem.inc();
     
     RunFuncTask( [=] () { work(); } ,asem.function_dec()); 
     
     AM3359::GPIO::Bar1 bar;
 
     bar.set_Level0Detect(bar.get_Level0Detect()|GPIOBit);
     
     bar.set_IRQ0EnableSet(GPIOBit);
     
     Dev::SetupIntHandler(Dev::Int_GPIO1_0,function_handle_int(),15);
    }
   
   ~Engine()
    {
     Dev::CleanupIntHandler(Dev::Int_GPIO1_0);
     
     AM3359::GPIO::Bar1 bar;
 
     bar.set_Level0Detect(bar.get_Level0Detect()&~GPIOBit);
     
     bar.set_IRQ0EnableClear(GPIOBit);

     mevent.trigger(StopEvent);
     
     asem.wait();
    }
 };

void test4()
 {
  Test test;
  
  Test::Info info;
  bool first=true;
  
  for(;;)
    {
     if( !test.testInt() )
       {
        Printf(Con,"Lo) #;\n",test.test());
        
        first=true;
       }
     else
       {
        if( first )
          {
           info=test.test();
           
           Printf(Con,"Hi) #;\n",info);
           
           first=false;
          }
        else
          {
           auto next=test.test();
           
           if( next!=info )
             {
              info=next;
              
              Printf(Con,"Hi) #;\n",info);
             }
          }
       }
    }
 }

void test5()
 {
  Engine engine;

  Task::Sleep(2_min);
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
  //test4();
  //test5();
  
  return true;
 }
 
} // namespace App
 
