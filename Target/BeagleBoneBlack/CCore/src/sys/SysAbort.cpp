/* SysAbort.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysAbort.h>

#include <__std_init.h>

namespace CCore {
namespace Sys {

/* functions */ 

void Abort(StrLen str)
 {
  __std_abort2(str.ptr,str.len);
 }
 
void Abort(const char *zstr)
 {
  __std_abort(zstr);
 }
 
} // namespace Sys
} // namespace CCore
 


