/* DevI2C.cpp */ 
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
 
#include <CCore/inc/dev/DevI2C.h>

#include <CCore/inc/Exception.h>

#include <CCore/inc/dev/AM3359.I2C.h>
#include <CCore/inc/dev/AM3359.PRCM.h>
#include <CCore/inc/dev/AM3359.CONTROL.h>
 
namespace CCore {
namespace Dev {

/* class I2C */

using namespace AM3359::I2C; 

const uint32 I2C::AddressTable[]=
 {
  I2C0BaseAddress,
  I2C1BaseAddress,
  I2C2BaseAddress
 };

const IntSource I2C::IntTable[]=
 {
  Int_I2C0INT,
  Int_I2C1INT,
  Int_I2C2INT
 };

Sys::Atomic I2C::LockTable[]={};

void I2C::handle_int()
 {
  // TODO
 }

I2C::I2C(I2CInstance instance_)
 : instance(instance_),
   base_address(AddressTable[instance_]),
   int_source(IntTable[instance_])
 {
  auto locked=LockTable[instance_]++;
  
  if( locked )
    {
     LockTable[instance_]--;
     
     Printf(Exception,"CCore::Dev::I2C::I2C(#;) : instance is locked",instance_);
    }
 }

I2C::~I2C()
 {
  CleanupIntHandler(int_source);
  
  LockTable[instance]--;
 }

 // init

void I2C::enable()
 {
  {
   using namespace AM3359::PRCM;
   
   switch( instance )
     {
      case I2C_0 :
       {
        WKUPBar bar;
        
        bar.null_ClockControl().set_Mode(ClockControl_Mode_Enable).set(bar.to_I2C0());
       
        while( bar.get_I2C0().get_IdleStatus()!=ClockControl_IdleStatus_Running );
       }
      break;
      
      case I2C_1 :
       {
        PERBar bar;
        
        bar.null_ClockControl().set_Mode(ClockControl_Mode_Enable).set(bar.to_I2C1());
       
        while( bar.get_I2C1().get_IdleStatus()!=ClockControl_IdleStatus_Running );
       }
      break;
      
      case I2C_2 :
       {
        PERBar bar;
        
        bar.null_ClockControl().set_Mode(ClockControl_Mode_Enable).set(bar.to_I2C2());
       
        while( bar.get_I2C2().get_IdleStatus()!=ClockControl_IdleStatus_Running );
       }
      break;
     }
  } 
  
  {
   using namespace AM3359::CONTROL;
   
   switch( instance )
     {
      case I2C_0 :
       {
        AM3359::CONTROL::Bar bar;
        
        bar.null_PadMux().setbit(PadMux_RXEn|PadMux_SlowSlew).set_MuxMode(0).set(bar.to_Conf_I2C0_SDA());
        bar.null_PadMux().setbit(PadMux_RXEn|PadMux_SlowSlew).set_MuxMode(0).set(bar.to_Conf_I2C0_SCL());
       }
      break;
      
      case I2C_1 :
       {
        // TODO
       }
      break;
      
      case I2C_2 :
       {
        // TODO
       }
      break;
     }
  }
 }

void I2C::reset()
 {
  Bar bar(base_address);
  
  bar.get_SysConfig().setbit(SysConfig_SoftReset).setTo(bar);
  
  while( bar.get_SysConfig().maskbit(SysConfig_SoftReset) );
 }

void I2C::init(bool fast)
 {
  Bar bar(base_address);
  
  bar.null_Config().setTo(bar);
  
  bar.null_Prescale().set_Div(4-1).setTo(bar); // 48 MHz -> 12 MHz
  
  uint32 div;
  
  if( fast ) // 12 MHz clock
    {
     div=30; // -> 400 kHz 
    }
  else
    {
     div=120; // -> 100 kHz
    }
  
  bar.null_SCLLoTime().set_Time(div/2-7).setTo(bar);
  bar.null_SCLHiTime().set_Time(div/2-5).setTo(bar);
  
  uint32 fifo=bar.get_BufStatus().get_FIFODepth();
  uint32 threshold=(4<<fifo)-1;
       
  bar.null_BufControl().set_TXFIFOThreshold(threshold).set_RXFIFOThreshold(threshold).setTo(bar);
  
  bar.null_Config().setbit(Config_Enable).setTo(bar);
  
  bar.ones_IRQStatus().set(bar.to_IRQEnableClear());
  
  SetupIntHandler(int_source,function_handle_int(),15);
 }

 // methods

void I2C::setSlave(uint8 address)
 {
  Bar bar(base_address);

  bar.null_SlaveAddress().set_Address(address).setTo(bar);
 }

bool I2C::read(uint8 *ptr,ulen len)
 {
  // TODO
 }

bool I2C::write(const uint8 *ptr,ulen len)
 {
  // TODO
 }

} // namespace Dev
} // namespace CCore
 

