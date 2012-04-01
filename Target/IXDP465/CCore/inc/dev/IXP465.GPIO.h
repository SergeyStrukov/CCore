/* IXP465.GPIO.h */ 
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

#ifndef CCore_inc_dev_IXP465_GPIO_h
#define CCore_inc_dev_IXP465_GPIO_h

#include <CCore/inc/dev/IXP465.h>
#include <CCore/inc/dev/DevRW.h>

namespace IXP465 {
namespace GPIO {

/* IXP465.GPIO.desc -> IXP465.GPIO.gen.h */ 

#include <CCore/inc/dev/IXP465.GPIO.gen.h>

/* struct PinBit */ 

struct PinBit
 {
  uint32 bit;
  
  PinBit() : bit(0) {}
 
  explicit PinBit(unsigned nbit) : bit(uint32(1)<<nbit) {}
  
  operator Bits_Out() const { return Bits_Out(bit); }
  
  operator Bits_Int() const { return Bits_Int(bit); }
 };
 
/* struct GPIOBar */ 

struct Bar : GPIOBar<CCore::Dev::RegRW>
 {
  Bar() : GPIOBar<CCore::Dev::RegRW>(0xC8004000) {}
 };
 
} // namespace GPIO
} // namespace IXP465
 
#endif

