/* Abort.cpp */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/Abort.h>

#include <CCore/inc/sys/SysAbort.h>

namespace CCore {

/* functions */ 

void Abort(StrLen str)
 {
  if( AbortMsgFunc )
    {    
     AbortMsgFunc(str);
    }
  
  Sys::Abort(str);
 }
 
void Abort(const char *zstr)
 {
  if( AbortMsgFunc )
    {    
     AbortMsgFunc(zstr);
    }
  
  Sys::Abort(zstr);
 }
 
} // namespace CCore
 

