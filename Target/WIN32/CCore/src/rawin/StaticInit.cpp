/* StaticInit.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/rawin/StaticInit.h>

#include <CCore/inc/Abort.h>
 
namespace CCore {
namespace Rawin {

/* functions */ 

void TouchPtr(void *ptr)
 {
  OptimizeBarrier(ptr,1);
 }
 
void StaticInitAbort()
 { 
  Abort("Fatal error : static initialization recursion"); 
 }
 
} // namespace Rawin
} // namespace CCore
 

