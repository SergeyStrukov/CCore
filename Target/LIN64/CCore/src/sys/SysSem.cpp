/* SysSem.cpp */ 
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
 
#include <CCore/inc/sys/SysSem.h>
#include <CCore/inc/sys/SysAbort.h>

#include <CCore/inc/sys/SysInternal.h>

#include <semaphore.h>
#include <errno.h>
#include <limits.h>

namespace CCore {
namespace Sys {

/* struct Sem */ 

ErrorType Sem::init(ulen count) noexcept
 {
  if( count>SEM_VALUE_MAX ) return ErrorType(EINVAL);
   
  if( sem_init(sem.getObj<sem_t>(),0,(unsigned)count)!=0 ) return NonNullError();

  return NoError;
 }
  
void Sem::exit() noexcept
 {
  AbortIf( sem_destroy(sem.getObj<sem_t>())!=0 ,"CCore::Sys::Sem::exit()");
 }
  
void Sem::give() noexcept
 {
  AbortIf( sem_post(sem.getObj<sem_t>())!=0 ,"CCore::Sys::Sem::give()");
 }
  
void Sem::give_many(ulen count) noexcept
 {
  for(; count ;count--) give();
 }
  
bool Sem::try_take() noexcept
 {
  if( sem_trywait(sem.getObj<sem_t>())==0 ) return true;
   
  AbortIf( errno!=EAGAIN ,"CCore::Sys::Sem::try_take()");

  return false;
 }
  
void Sem::take() noexcept
 {
  AbortIf( sem_wait(sem.getObj<sem_t>())!=0 ,"CCore::Sys::Sem::take()");
 }
  
bool Sem::take(MSec timeout) noexcept
 {
  TimeSpec abs_to(CLOCK_REALTIME,timeout);

  if( sem_timedwait(sem.getObj<sem_t>(),&abs_to)==0 ) return true;
  
  AbortIf( errno!=ETIMEDOUT ,"CCore::Sys::Sem::take()");

  return false;
 }
  
} // namespace Sys
} // namespace CCore
 

