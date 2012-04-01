/* DevSignal.cpp */ 
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

#include <CCore/inc/dev/DevSignal.h>

#include <CCore/inc/dev/DevInt.h>

#include <CCore/inc/dev/IXP465.GPIO.h>

namespace CCore {
namespace Dev {

/* using */ 

using namespace IXP465;

/* functions */ 

void EnableSignal(Signal s)
 {
  IntLock lock;
 
  GPIO::Bar bar;
  
  bar.get_OutDisable()
     .clearbit(GPIO::PinBit(s))
     .set(bar.to_OutDisable());
 }
 
void DisableSignal(Signal s)
 {
  IntLock lock;
 
  GPIO::Bar bar;
  
  bar.get_OutDisable()
     .setbit(GPIO::PinBit(s))
     .set(bar.to_OutDisable());
 }
 
void SetSignal(Signal s,bool value)
 {
  if( value )
    SetSignal(s);
  else  
    ClearSignal(s);
 }
 
void SetSignal(Signal s)
 {
  IntLock lock;
 
  GPIO::Bar bar;
  
  bar.get_Out()
     .setbit(GPIO::PinBit(s))
     .set(bar.to_Out());
 }
 
void ClearSignal(Signal s)
 {
  IntLock lock;
 
  GPIO::Bar bar;
  
  bar.get_Out()
     .clearbit(GPIO::PinBit(s))
     .set(bar.to_Out());
 }
 
} // namespace Dev
} // namespace CCore

