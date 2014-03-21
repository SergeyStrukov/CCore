/* CBase.cpp */ 
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
 
#include <CCore/inc/libc/CBase.h>
 
#include <__std_init.h>

namespace LibC_Internal {

/* functions */ 

void Abort(const char *msg) { __std_abort(msg); }
 
} // namespace LibC_Internal
 

