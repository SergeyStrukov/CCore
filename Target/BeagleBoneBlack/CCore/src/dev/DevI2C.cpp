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

Sys::Atomic I2C::LockTable[]={};

I2C::I2C(I2CInstance instance_)
 : instance(instance_),
   base_address(AddressTable[instance_]) 
 {
  auto locked=LockTable[instance_]++;
  
  if( locked )
    {
     LockTable[instance]--;
     
     Printf(Exception,"CCore::Dev::I2C::I2C(#;) : instance is locked",instance_);
    }
  
  
 }

I2C::~I2C()
 {
  LockTable[instance]--;
 }

} // namespace Dev
} // namespace CCore
 

