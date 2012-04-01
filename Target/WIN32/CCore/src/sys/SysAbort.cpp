/* SysAbort.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysAbort.h>
#include <CCore/inc/sys/SysCon.h>
 
#include <CCore/inc/PrintError.h>

#include <CCore/inc/win32/Win32.h>

namespace CCore {
namespace Sys {

/* private functions */

void AbortOnError(const char *text,ErrorType error)
 {
  char buf[TextBufLen];
  PrintBuf out(Range(buf));
     
  Printf(out,"\nFatal error : #; failed, #;\n\n",text,PrintError(error));
     
  ConWrite(out.close());
     
  AbortProcess();
 }
 
/* functions */ 

void AbortProcess()
 {
  Win32::TerminateProcess(Win32::GetCurrentProcess(),666);
 }
 
} // namespace Sys
} // namespace CCore
 


