/* SysError.cpp */ 
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
 
#include <CCore/inc/sys/SysError.h>
 
#include <CCore/inc/win32/Win32.h>

namespace CCore {
namespace Sys {

/* private functions */ 

ErrorType NonNullError() noexcept
 {
  if( auto ret=Win32::GetLastError() ) return ErrorType(ret);
  
  return Error_SysErrorFault;
 }
 
/* struct ErrorDesc */ 

bool ErrorDesc::set(StrLen msg)
 {
  str=msg.ptr;
  len=msg.len;
  
  return true;
 }

bool ErrorDesc::init(ErrorType error,PtrLen<char> buf) noexcept
 {
  switch( error )
    {
     case Error_SysErrorFault : return set("System failed to report error");
     case Error_Task          : return set("System cannot create task");
     case Error_Socket        : return set("System socket failure");
    }
  
  Win32::flags_t flags=Win32::FormatMessageFromSystem
                      |Win32::FormatMessageIgnoreInserts
                      |Win32::FormatMessageMaxWidthMask;

  len=Win32::FormatMessageA(flags,0,error,0,buf.ptr,buf.len,0);

  if( len )
    {
     str=buf.ptr;                    

     return true;
    }
  else
    {
     str=0;

     return false;
    }
 }
 
} // namespace Sys
} // namespace CCore
 

