/* DevInt.cpp */ 
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

#include <CCore/inc/dev/DevInt.h>

#include <CCore/inc/dev/IXP465.h>

namespace CCore {
namespace Dev {

#if 0

/* using */ 

using namespace IXP465;

/* functions */ 

bool IsIntContext() noexcept
 {
  return GetCPSR().get_Mode()==CPUStatus_Mode_IRQ;
 }
 
/* class IntLock */ 

bool IntLock::Internal::Disable() noexcept
 {
  auto CPSR=GetCPSR();

  if( CPSR.maskbit(CPUStatus_I) )
    {
     return false;
    }
  else
    {
     CPSR.setbit(CPUStatus_I);
    
     SetCPSR_control(CPSR);
     
     return true;
    }
 }
     
void IntLock::Internal::Enable() noexcept
 {
  auto CPSR=GetCPSR();
  
  CPSR.clearbit(CPUStatus_I);

  SetCPSR_control(CPSR);
 }
 
#endif 
 
} // namespace Dev
} // namespace CCore
 

