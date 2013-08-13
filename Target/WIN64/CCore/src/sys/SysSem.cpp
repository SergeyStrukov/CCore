/* SysSem.cpp */ 
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
 
#include <CCore/inc/sys/SysSem.h>

#include <CCore/inc/sys/SysAbort.h>
 
#include <CCore/inc/win64/Win64.h>

namespace CCore {
namespace Sys {

/* struct Sem */ 

auto Sem::Create(ulen count) noexcept -> CreateType
 {
  CreateType ret;
  
  if( count>(ulen)Win64::MaxSemaphoreCount )
    {
     ret.handle=0;
     
     ret.error=ErrorType(Win64::ErrorInvalidParameter);
    }
  else
    {
     ret.handle=Win64::CreateSemaphoreA(0,(Win64::sem_count_t)count,Win64::MaxSemaphoreCount,0);
    
     ret.error=ErrorIf( ret.handle==0 );
    }
  
  return ret;  
 }
  
void Sem::Destroy(Type handle) noexcept
 {
  AbortIf( !Win64::CloseHandle(handle) ,"CCore::Sys::Sem::Destroy()");
 }
  
void Sem::Give(Type handle) noexcept
 {
  AbortIf( !Win64::ReleaseSemaphore(handle,1,0) ,"CCore::Sys::Sem::Give()");
 }
  
void Sem::GiveMany(Type handle,ulen count) noexcept
 {
  if( !count ) return; 
  
  AbortIf( count>(ulen)Win64::MaxSemaphoreCount || !Win64::ReleaseSemaphore(handle,(Win64::sem_count_t)count,0) ,"CCore::Sys::Sem::GiveMany()");
 }
 
bool Sem::TryTake(Type handle) noexcept
 {
  Win64::options_t ret=Win64::WaitForSingleObject(handle,Win64::TryTimeout);
 
  AbortIf( ret!=Win64::WaitObject_0 && ret!=Win64::WaitTimeout ,"CCore::Sys::Sem::TryTake()");
  
  return ret==Win64::WaitObject_0;
 }
 
void Sem::Take(Type handle) noexcept
 {
  AbortIf( Win64::WaitForSingleObject(handle,Win64::NoTimeout)!=Win64::WaitObject_0 ,"CCore::Sys::Sem::Take()");
 }
  
bool Sem::Take(Type handle,MSec timeout) noexcept
 {
  Win64::options_t ret=Win64::WaitForSingleObject(handle,+timeout);
 
  AbortIf( ret!=Win64::WaitObject_0 && ret!=Win64::WaitTimeout ,"CCore::Sys::Sem::Take()");
  
  return ret==Win64::WaitObject_0;
 }
  
} // namespace Sys
} // namespace CCore
 

