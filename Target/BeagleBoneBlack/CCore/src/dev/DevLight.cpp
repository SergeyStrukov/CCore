/* DevLight.cpp */ 
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
 
#include <CCore/inc/dev/DevLight.h>

#include <CCore/inc/dev/DevInt.h>

#include <CCore/inc/dev/AM3359.GPIO.h>
 
namespace CCore {
namespace Dev {

using namespace AM3359::GPIO;

/* functions */

static uint32 Mask(uint32 mask)
 {
  return (mask&15)<<21;
 }

void LightSet(unsigned mask)
 {
  IntLock lock;
  
  Bar bar(GPIO1);
  
  bar.set_Out(Mask(mask));
 }

void LightOn(unsigned mask)
 {
  Bar bar(GPIO1);
  
  bar.set_SetOut(Mask(mask));
 }

void LightOff(unsigned mask)
 {
  Bar bar(GPIO1);
  
  bar.set_ClearOut(Mask(mask));
 }

void LightToggle(unsigned mask)
 {
  IntLock lock;
  
  Bar bar(GPIO1);
  
  bar.set_Out( bar.get_Out()^Mask(mask) );
 }

} // namespace Dev
} // namespace CCore
 

