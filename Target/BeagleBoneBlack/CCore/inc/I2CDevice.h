/* I2CDevice.h */ 
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

#ifndef CCore_inc_I2CDevice_h
#define CCore_inc_I2CDevice_h

#include <CCore/inc/ObjHost.h>
#include <CCore/inc/Task.h>

#include <CCore/inc/dev/DevI2C.h>
 
namespace CCore {

/* classes */

class I2CDevice;

/* class I2CDevice */

class I2CDevice : public ObjBase
 {
   Mutex mutex;
   
   Dev::I2C dev;
   
   uint32 slave_address = 0xFFFFFFFF ;
   
  private:
   
   void setSlave(uint8 slave_address);
  
  public:
  
   explicit I2CDevice(Dev::I2CInstance instance);
   
   virtual ~I2CDevice();
   
   // methods , may throw exception
   
   void read(uint8 slave_address,PtrLen<uint8> buf);
   
   void write(uint8 slave_address,PtrLen<const uint8> buf);
   
   void exchange(uint8 slave_address,PtrLen<const uint8> out_buf,PtrLen<uint8> in_buf);
 };

} // namespace CCore
 
#endif
 

