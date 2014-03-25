/* AM3359.PRCM.h */
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

#ifndef CCore_inc_dev_AM3359_PRCM_h
#define CCore_inc_dev_AM3359_PRCM_h

#include <CCore/inc/dev/AM3359.h>
#include <CCore/inc/dev/DevRW.h>

namespace AM3359 {
namespace PRCM {

/* AM3359.PRCM.desc -> AM3359.PRCM.gen.h */

#include <CCore/inc/dev/AM3359.PRCM.gen.h>

/* struct PERBar */

struct PERBar : CM_PERBar<CCore::Dev::RegRW>
 {
  PERBar() : CM_PERBar<CCore::Dev::RegRW>(0x44E00000) {}
 };

/* struct DPLLBar */

struct DPLLBar : CM_DPLLBar<CCore::Dev::RegRW>
 {
  DPLLBar() : CM_DPLLBar<CCore::Dev::RegRW>(0x44E00500) {}
 };

} // namespace PRCM
} // namespace AM3359

#endif

