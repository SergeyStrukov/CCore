/* SysProp.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysProp.h>
 
namespace CCore {
namespace Sys {

/* functions */ 

unsigned GetCpuCount() noexcept
 {
  // TODO

  return 4;
 }
 
unsigned GetSpinCount() noexcept 
 {
  // TODO

  return 1000;
 }
 
} // namespace Sys
} // namespace CCore
 

