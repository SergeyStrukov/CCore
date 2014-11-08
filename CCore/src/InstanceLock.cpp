/* InstanceLock.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/InstanceLock.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {

/* functions */

void GuardInstanceLockTaken(StrLen name)
 {
  Printf(Exception,"CCore::InstanceLock::InstanceLock() : #; instance is locked",name);
 }

} // namespace CCore
 

