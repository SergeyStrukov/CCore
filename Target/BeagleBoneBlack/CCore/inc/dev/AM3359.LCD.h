/* AM3359.LCD.h */
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

#ifndef CCore_inc_dev_AM3359_LCD_h
#define CCore_inc_dev_AM3359_LCD_h

#include <CCore/inc/dev/AM3359.h>
#include <CCore/inc/dev/DevRW.h>

namespace AM3359 {
namespace LCD {

/* AM3359.LCD.desc -> AM3359.LCD.gen.h */

#include <CCore/inc/dev/AM3359.LCD.gen.h>

/* struct Bar */

struct Bar : LCDBar<CCore::Dev::RegRW>
 {
  Bar() : LCDBar<CCore::Dev::RegRW>(0x4830E000) {}
 };

} // namespace LCD
} // namespace AM3359

#endif

