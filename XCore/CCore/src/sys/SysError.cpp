/* SysError.cpp */ 
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
 
#include <CCore/inc/sys/SysError.h>
 
namespace CCore {
namespace Sys {

/* struct ErrorDesc */ 

bool ErrorDesc::set(StrLen msg)
 {
  str=msg.ptr;
  len=msg.len;
  
  return true;
 }
 
bool ErrorDesc::init(ErrorType error,PtrLen<char>) noexcept
 {
  switch( error )
    {
     case Error_TlsFull : return set("TLS is full");
     case Error_Unknown : return set("unknown error");
     
     default : str=0; len=0; return false;
    }
 }
 
} // namespace Sys
} // namespace CCore
 

