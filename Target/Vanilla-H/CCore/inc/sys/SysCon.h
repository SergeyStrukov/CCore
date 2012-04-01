/* SysCon.h */ 
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

#ifndef CCore_inc_sys_SysCon_h
#define CCore_inc_sys_SysCon_h
 
#include <CCore/inc/sys/SysError.h>

namespace CCore {
namespace Sys {

/* functions */ 

void ConWrite(StrLen str) noexcept;

/* classes */ 

struct ConRead;

/* struct ConRead */ 

struct ConRead
 {
  // public
  
  struct IOResult
   {
    ulen len;
    ErrorType error;
   };
  
  // public
  
  ErrorType init() noexcept;
  
  ErrorType exit() noexcept;
  
  IOResult read(char *buf,ulen len) noexcept;
  
  IOResult read(char *buf,ulen len,MSec timeout) noexcept;
 };
 
} // namespace Sys
} // namespace CCore
 
#endif
 

