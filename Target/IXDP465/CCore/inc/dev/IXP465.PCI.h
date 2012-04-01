/* IXP465.PCI.h */ 
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

#ifndef CCore_inc_dev_IXP465_PCI_h
#define CCore_inc_dev_IXP465_PCI_h
 
#include <CCore/inc/dev/IXP465.h>
#include <CCore/inc/dev/DevRW.h>

namespace IXP465 {
namespace PCI {

/* IXP465.PCI.desc -> IXP465.PCI.gen.h */ 

#include <CCore/inc/dev/IXP465.PCI.gen.h>

/* struct Bar */ 

struct Bar : PCIBar<CCore::Dev::RegRW>
 {
  Bar() : PCIBar<CCore::Dev::RegRW>(0xC0000000) {}
 };
 
} // namespace PCI
} // namespace IXP465
 
#endif
 

