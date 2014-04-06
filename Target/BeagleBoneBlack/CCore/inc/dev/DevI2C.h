/* DevI2C.h */ 
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

#ifndef CCore_inc_dev_DevI2C_h
#define CCore_inc_dev_DevI2C_h

#include <CCore/inc/Gadget.h>
#include <CCore/inc/sys/SysAtomic.h>
 
namespace CCore {
namespace Dev {

/* enum I2CInstance */

enum I2CInstance
 {
  I2C_0,
  I2C_1,
  I2C_2
 };

/* classes */

class I2C;

/* class I2C */

class I2C : NoCopy
 {
   I2CInstance instance;
   uint32 base_address;
   
  private:
   
   static const uint32 AddressTable[];
   
   static Sys::Atomic LockTable[];
  
  public:
  
   explicit I2C(I2CInstance instance);
   
   ~I2C();
 };

} // namespace Dev
} // namespace CCore
 
#endif
 

