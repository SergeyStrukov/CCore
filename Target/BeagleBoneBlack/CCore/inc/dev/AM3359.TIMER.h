/* AM3359.TIMER.h */
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

#ifndef CCore_inc_dev_AM3359_TIMER_h
#define CCore_inc_dev_AM3359_TIMER_h

#include <CCore/inc/dev/AM3359.h>
#include <CCore/inc/dev/DevRW.h>

namespace AM3359 {
namespace TIMER {

/* AM3359.TIMER.desc -> AM3359.TIMER.gen.h */

#include <CCore/inc/dev/AM3359.TIMER.gen.h>

/* Instances */

enum Instance : uint32
 {
  Timer2 = 0x48040000,
  Timer4 = 0x48044000
 };

/* struct DMBar */

struct Bar : DMBar<CCore::Dev::RegRW>
 {
  explicit Bar(Instance instance) : DMBar<CCore::Dev::RegRW>(instance) {}
 };

} // namespace TIMER
} // namespace AM3359

#endif

