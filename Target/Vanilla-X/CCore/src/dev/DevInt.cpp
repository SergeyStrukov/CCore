/* DevInt.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/dev/DevInt.h>

namespace CCore {
namespace Dev {

#if 1

 // Fake code

/* functions */ 

bool IsIntContext() noexcept
 {
  return false;
 }
 
/* class IntLock */ 

bool IntLock::Internal::Disable() noexcept
 {
  return true;
 }
     
void IntLock::Internal::Enable() noexcept
 {
 }
 
#endif 
 
} // namespace Dev
} // namespace CCore
 

