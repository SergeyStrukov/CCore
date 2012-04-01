/* SysError.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vanilla-H
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysError.h>
 
namespace CCore {
namespace Sys {

/* struct ErrorDesc */ 

bool ErrorDesc::init(ErrorType /*error*/,PtrLen<char> /*buf*/) noexcept
 {
  // TODO

  str=0;
  len=0;

  return false;
 }
 
} // namespace Sys
} // namespace CCore
 

