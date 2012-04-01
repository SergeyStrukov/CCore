/* AutoText.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/task/AutoText.h>
 
#include <CCore/inc/dev/DevInt.h>

namespace CCore {

/* functions */

unsigned AutoTextAtomicGetNumber(unsigned &Next)
 {
  Dev::IntLock lock; 
  
  return GetTextLabelNumber(Next); 
 }

} // namespace CCore
 

