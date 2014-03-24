/* AM3359.INTC.h */
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

#ifndef CCore_inc_dev_AM3359_INTC_h
#define CCore_inc_dev_AM3359_INTC_h

#include <CCore/inc/dev/AM3359.h>
#include <CCore/inc/dev/DevRW.h>

namespace AM3359 {
namespace INTC {

/* AM3359.INTC.desc -> AM3359.INTC.gen.h */

#include <CCore/inc/dev/AM3359.INTC.gen.h>

/* struct Bar */

struct Bar : INTCBar<CCore::Dev::RegRW>
 {
  Bar() : INTCBar<CCore::Dev::RegRW>(0x48200000) {}
 };

} // namespace INTC
} // namespace AM3359

#endif

