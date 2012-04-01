/* HashFunction.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/crypton/HashFunction.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {
namespace Crypton {

/* functions */

void GuardNoHashKey()
 {
  Printf(Exception,"CCore::Crypton::GuardNoHashKey() : no hash key");
 }

} // namespace Crypton
} // namespace CCore
 

