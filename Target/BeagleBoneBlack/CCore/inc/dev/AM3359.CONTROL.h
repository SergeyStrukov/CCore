/* AM3359.CONTROL.h */
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

#ifndef CCore_inc_dev_AM3359_CONTROL_h
#define CCore_inc_dev_AM3359_CONTROL_h

#include <CCore/inc/dev/AM3359.h>
#include <CCore/inc/dev/DevRW.h>
#include <CCore/inc/dev/DevControlMutex.h>

namespace AM3359 {
namespace CONTROL {

//
// Use Dev::ControlMutex to protect against race-condition.
// 

/* AM3359.CONTROL.desc -> AM3359.CONTROL.gen.h */

#include <CCore/inc/dev/AM3359.CONTROL.gen.h>

/* struct Bar */

struct Bar : CONTROLBar<CCore::Dev::RegRW>
 {
  Bar() : CONTROLBar<CCore::Dev::RegRW>(0x44E10000) {}
 };

} // namespace CONTROL
} // namespace AM3359

#endif

