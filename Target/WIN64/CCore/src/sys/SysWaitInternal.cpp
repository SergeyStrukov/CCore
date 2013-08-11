/* SysWaitInternal.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysWaitInternal.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/PrintError.h>

namespace CCore {
namespace Sys {

/* functions */

void GuardError(ErrorType error)
 {
  Printf(Exception,"CCore::Sys::Guard() : #;",PrintError(error));
 }

/* class WaitSem */

WaitSem::WaitSem()
 {
  h_sem=Win64::CreateSemaphoreA(0,0,Win64::MaxSemaphoreCount,0);
  
  Guard( !h_sem );
 }

WaitSem::~WaitSem()
 {
  AbortIf( !Win64::CloseHandle(h_sem) ,"CCore::Sys::WaitSem::~WaitSem()");
 }

void WaitSem::give()
 {
  AbortIf( !Win64::ReleaseSemaphore(h_sem,1,0) ,"CCore::Sys::WaitSem::give()");
 }

} // namespace Sys
} // namespace CCore
 

