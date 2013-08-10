/* SysSem.cpp */ 
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
 
#include <CCore/inc/sys/SysSem.h>

#include <CCore/inc/sys/SysAbort.h>
 
#include <CCore/inc/win32/Win32.h>

namespace CCore {
namespace Sys {

/* struct Sem */ 

auto Sem::Create(ulen count) noexcept -> CreateType
 {
  CreateType ret;
  
  ret.handle=Win32::CreateSemaphoreA(0,count,Win32::MaxSemaphoreCount,0);
  
  ret.error=ErrorIf( ret.handle==0 );
  
  return ret;  
 }
  
void Sem::Destroy(Type handle) noexcept
 {
  AbortIf( !Win32::CloseHandle(handle) ,"CCore::Sys::Sem::Destroy()");
 }
  
void Sem::Give(Type handle) noexcept
 {
  AbortIf( !Win32::ReleaseSemaphore(handle,1,0) ,"CCore::Sys::Sem::Give()");
 }
  
void Sem::GiveMany(Type handle,ulen count) noexcept
 {
  if( !count ) return;

  AbortIf( count>(ulen)Win32::MaxSemaphoreCount || !Win32::ReleaseSemaphore(handle,count,0) ,"CCore::Sys::Sem::GiveMany()");
 }
 
bool Sem::TryTake(Type handle) noexcept
 {
  Win32::options_t ret=Win32::WaitForSingleObject(handle,Win32::TryTimeout);
 
  AbortIf( ret!=Win32::WaitObject_0 && ret!=Win32::WaitTimeout ,"CCore::Sys::Sem::TryTake()");
  
  return ret==Win32::WaitObject_0;
 }
 
void Sem::Take(Type handle) noexcept
 {
  AbortIf( Win32::WaitForSingleObject(handle,Win32::NoTimeout)!=Win32::WaitObject_0 ,"CCore::Sys::Sem::Take()");
 }
  
bool Sem::Take(Type handle,MSec timeout) noexcept
 {
  Win32::options_t ret=Win32::WaitForSingleObject(handle,+timeout);
 
  AbortIf( ret!=Win32::WaitObject_0 && ret!=Win32::WaitTimeout ,"CCore::Sys::Sem::Take()");
  
  return ret==Win32::WaitObject_0;
 }
  
} // namespace Sys
} // namespace CCore
 

