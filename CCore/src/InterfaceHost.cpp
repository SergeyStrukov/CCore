/* InterfaceHost.cpp */ 
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
 
#include <CCore/inc/InterfaceHost.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {

/* functions */

void GuardNoInterface(StrLen from,StrLen name)
 {
  Printf(Exception,"Interface #; is not avaliable from #;",name,from);
 }

} // namespace CCore
 

