/* AM3359.I2C.h */
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

#ifndef CCore_inc_dev_AM3359_I2C_h
#define CCore_inc_dev_AM3359_I2C_h

#include <CCore/inc/dev/AM3359.h>
#include <CCore/inc/dev/DevRW.h>

namespace AM3359 {
namespace I2C {

/* AM3359.I2C.desc -> AM3359.I2C.gen.h */

#include <CCore/inc/dev/AM3359.I2C.gen.h>

/* Instances */

enum Instance : uint32
 {
  I2C_0 = 0x44E0B000,
  I2C_1 = 0x4802A000,
  I2C_2 = 0x4819C000 
 };

/* struct Bar */

struct Bar : I2CBar<CCore::Dev::RegRW>
 {
  explicit Bar(Instance instance) : I2CBar<CCore::Dev::RegRW>(instance) {}
 };

} // namespace I2C
} // namespace AM3359

#endif

