/* SysTlsSlot.cpp */ 
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
 
#include <CCore/inc/sys/SysTlsSlot.h>
 
#include <CCore/inc/task/TaskCore.h>

namespace CCore {
namespace Sys {

/* struct TlsSlot */ 

auto TlsSlot::Alloc() noexcept -> AllocType
 {
  AllocType ret;
  
  auto result=TlsBuf::Alloc();
  
  if( result.ok )
    {
     ret.index=result.index;
     ret.error=NoError;
    }
  else
    {
     ret.index=0;
     ret.error=Error_TlsFull;
    }
  
  return ret;
 }
  
void TlsSlot::Free(Type index) noexcept
 {
  TlsBuf::Free(index);
 }
  
void * TlsSlot::Get(Type index) noexcept
 {
  return Task::GetCurrent()->tls[index];
 }
  
void TlsSlot::Set(Type index,void *value) noexcept
 {
  Task::GetCurrent()->tls[index]=value;
 }
 
} // namespace Sys
} // namespace CCore
 

