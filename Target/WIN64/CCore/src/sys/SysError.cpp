/* SysError.cpp */ 
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
 
#include <CCore/inc/sys/SysError.h>
 
#include <CCore/inc/win64/Win64.h>

namespace CCore {
namespace Sys {

/* private functions */ 

ErrorType NonNullError() noexcept
 {
  if( auto ret=Win64::GetLastError() ) return ErrorType(ret);
  
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
  
  Win64::flags_t flags=Win64::FormatMessageFromSystem
                      |Win64::FormatMessageIgnoreInserts
                      |Win64::FormatMessageMaxWidthMask;
  
  len=Win64::FormatMessageA(flags,0,error,0,buf.ptr,Win64::CapLen(buf.len),0);

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
 

