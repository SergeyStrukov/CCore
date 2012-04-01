/* IXP465.h */ 
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

#ifndef CCore_inc_dev_IXP465_h
#define CCore_inc_dev_IXP465_h

#include <CCore/inc/Gadget.h>

namespace IXP465 {

/* using */ 

using CCore::uint8;
using CCore::uint16;
using CCore::uint32;

/* IXP465.desc -> IXP465.gen.h */ 

#include <CCore/inc/dev/IXP465.gen.h>

/* CPU Status */ 

Type_CPUStatus GetCPSR() noexcept;
Type_CPUStatus GetSPSR() noexcept;

void SetCPSR(Type_CPUStatus status) noexcept;
void SetCPSR_control(Type_CPUStatus status) noexcept;

} // namespace IXP465
 
#endif


