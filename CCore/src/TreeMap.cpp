/* TreeMap.cpp */
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
 
#include <CCore/inc/TreeMap.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {

/* function */

void GuardKeyOutOfRange()
 {
  Printf(Exception,"CCore::KeyRange<K>::guard(...) : key is out of range");
 }

} // namespace CCore
 

