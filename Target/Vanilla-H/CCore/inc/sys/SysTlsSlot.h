/* SysTlsSlot.h */ 
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

#ifndef CCore_inc_sys_SysTlsSlot_h
#define CCore_inc_sys_SysTlsSlot_h

#include <CCore/inc/sys/SysError.h>
 
namespace CCore {
namespace Sys {

/* classes */ 

struct TlsSlot;

/* struct TlsSlot */ 

struct TlsSlot
 {
  // public
  
  ErrorType init() noexcept;
  
  void exit() noexcept;
  
  void * get() noexcept;
  
  void set(void *value) noexcept;
 };
 
} // namespace Sys
} // namespace CCore
 
#endif
 

