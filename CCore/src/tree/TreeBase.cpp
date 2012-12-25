/* TreeBase.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.03
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/tree/TreeBase.h>
 
#include <CCore/inc/Abort.h>

namespace CCore {

/* functions */ 

void RadixTreeBrokenAbort()
 {
  Abort("Fatal error : radix tree is broken");
 }

} // namespace CCore
 

