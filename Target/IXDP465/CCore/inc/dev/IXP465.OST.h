/* IXP465.OST.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_IXP465_OST_h
#define CCore_inc_dev_IXP465_OST_h

#include <CCore/inc/dev/IXP465.h>
#include <CCore/inc/dev/DevRW.h>

namespace IXP465 {
namespace OST {

/* IXP465.OST.desc -> IXP465.OST.gen.h */ 

#include <CCore/inc/dev/IXP465.OST.gen.h>

/* struct Bar */ 

struct Bar : OSTBar<CCore::Dev::RegRW>
 {
  Bar() : OSTBar<CCore::Dev::RegRW>(0xC8005000) {}
 };
 
} // namespace OST 
} // namespace IXP465
 
#endif

