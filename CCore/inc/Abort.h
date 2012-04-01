/* Abort.h */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Abort_h
#define CCore_inc_Abort_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {

/* types */ 

typedef void (*AbortMsgFuncType)(StrLen str);

/* global const AbortMsgFunc */ 

extern const AbortMsgFuncType AbortMsgFunc;

/* functions */ 

void Abort(StrLen str);
 
void Abort(const char *zstr);

} // namespace CCore
 
#endif
 

