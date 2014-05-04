/* I2CDevice.cpp */ 
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
 
#include <CCore/inc/I2CDevice.h>
 
namespace CCore {

/* class I2CDevice */

void I2CDevice::setSlave(uint8 slave_address_)
 {
  if( slave_address!=slave_address_ )
    {
     dev.setSlave7(slave_address_);
    
     slave_address=slave_address_;
    }
 }

I2CDevice::I2CDevice(Dev::I2CInstance instance)
 : mutex("I2CDevice"),
   dev(instance)
 {
  dev.enable();
  
  dev.reset();
  
  dev.init_fast();
 }
   
I2CDevice::~I2CDevice()
 {
 }
   
void I2CDevice::read(uint8 slave_address,PtrLen<uint8> buf)
 {
  Mutex::Lock lock(mutex);
  
  setSlave(slave_address);
  
  dev.read(buf);
 }
   
void I2CDevice::write(uint8 slave_address,PtrLen<const uint8> buf)
 {
  Mutex::Lock lock(mutex);
  
  setSlave(slave_address);
  
  dev.write(buf);
 }
   
void I2CDevice::exchange(uint8 slave_address,PtrLen<const uint8> out_buf,PtrLen<uint8> in_buf)
 {
  Mutex::Lock lock(mutex);
  
  setSlave(slave_address);
  
  dev.exchange(out_buf,in_buf);
 }

} // namespace CCore
 

