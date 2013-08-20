/* StateMap.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "StateMap.h"

#include <CCore/inc/Exception.h>

namespace App {

/* functions */

void GuardNoTrace()
 {
  Printf(Exception,"App::StateMap::StateMap(...) : no trace"); 
 }

void GuardBrokenMap(ulen state,ulen element)
 {
  Printf(Exception,"App::StateMap::StateMap(...) : map is broken at state #; , element #;",state,element); 
 }

} // namespace App
