/* SysTlsSlot.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysTlsSlot.h>
#include <CCore/inc/sys/SysAbort.h>

#include <pthread.h>

namespace CCore {
namespace Sys {

/* struct TlsSlot */

static_assert( std::is_same<pthread_key_t,TlsSlot::Type>::value ,"CCore::Sys::TlsSlot::Type != pthread_key_t");

auto TlsSlot::Alloc() noexcept -> AllocType
 {
  AllocType ret;
  
  ret.error=ErrorType( pthread_key_create(&ret.index,NULL) );
  
  return ret;
 }
  
void TlsSlot::Free(Type index) noexcept
 {
  AbortIfError( pthread_key_delete(index) ,"CCore::Sys::TlsSlot::Free()");
 }
  
void * TlsSlot::Get(Type index) noexcept
 {
  return pthread_getspecific(index);
 }
  
void TlsSlot::Set(Type index,void *value) noexcept
 {
  AbortIfError( pthread_setspecific(index,value) ,"CCore::Sys::TlsSlot::Set()");
 }
 
} // namespace Sys
} // namespace CCore
 

