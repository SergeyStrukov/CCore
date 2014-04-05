/* AM3359.GPIO.h */ 
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

#ifndef CCore_inc_dev_AM3359_GPIO_h
#define CCore_inc_dev_AM3359_GPIO_h
 
#include <CCore/inc/dev/AM3359.h>
#include <CCore/inc/dev/DevRW.h>

namespace AM3359 {
namespace GPIO {

/* AM3359.GPIO.desc -> AM3359.GPIO.gen.h */

#include <CCore/inc/dev/AM3359.GPIO.gen.h>

/* struct Bar1 */

struct Bar1 : GPIOBar<CCore::Dev::RegRW>
 {
  Bar1() : GPIOBar<CCore::Dev::RegRW>(0x4804C000) {}
 };

} // namespace GPIO
} // namespace AM3359

#endif
 

