/* DevLight.h */ 
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

#ifndef CCore_inc_dev_DevLight_h
#define CCore_inc_dev_DevLight_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Dev {

/* functions */

void LightSet(unsigned mask);    // 4 lsb

void LightOn(unsigned mask);     // 4 lsb

void LightOff(unsigned mask);    // 4 lsb

void LightToggle(unsigned mask); // 4 lsb

} // namespace Dev
} // namespace CCore
 
#endif
 

