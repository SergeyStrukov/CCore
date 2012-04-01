/* SysTlsSlot.cpp */ 
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
 
#include <CCore/inc/sys/SysTlsSlot.h>

namespace CCore {
namespace Sys {

/* struct TlsSlot */ 

ErrorType TlsSlot::init() noexcept
 {
  // TODO

  return NoError;
 }
  
void TlsSlot::exit() noexcept
 {
  // TODO
 }
  
void * TlsSlot::get() noexcept
 {
  // TODO

  return 0;
 }
  
void TlsSlot::set(void * /*value*/) noexcept
 {
  // TODO
 }
 
} // namespace Sys
} // namespace CCore
 

