/* AttachmentHost.cpp */ 
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
 
#include <CCore/inc/AttachmentHost.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/PrintAbort.h>
 
namespace CCore {

/* functions */

void GuardAlreadyAttached(StrLen class_name)
 {
  Printf(Exception,"#;::attach(...) : already attached",class_name);
 }

void AbortAttachOnExit(StrLen class_name)
 {
  PrintAbort("Fatal error : #; is attached on exit",class_name);
 }

} // namespace CCore
 

