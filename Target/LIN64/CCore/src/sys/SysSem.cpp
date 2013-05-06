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

#include <time.h>
#include <errno.h>
#include <limits.h>

namespace CCore {
namespace Sys {

/* struct Sem */ 

ErrorType Sem::init(ulen count) noexcept
 {
  if( count>SEM_VALUE_MAX ) return ErrorType(EINVAL);
   
  if( sem_init(&sem,0,(unsigned)count)!=0 ) return NonNullError();

  return NoError;
 }
  
void Sem::exit() noexcept
 {
  AbortIf( sem_destroy(&sem)!=0 ,"CCore::Sys::Sem::exit()");
 }
  
void Sem::give() noexcept
 {
  AbortIf( sem_post(&sem)!=0 ,"CCore::Sys::Sem::give()");
 }
  
void Sem::give_many(ulen count) noexcept
 {
  for(; count ;count--) give();
 }
  
bool Sem::try_take() noexcept
 {
  if( sem_trywait(&sem)==0 ) return true;
   
  AbortIf( errno!=EAGAIN ,"CCore::Sys::Sem::try_take()");

  return false;
 }
  
void Sem::take() noexcept
 {
  AbortIf( sem_wait(&sem)!=0 ,"CCore::Sys::Sem::take()");
 }
  
bool Sem::take(MSec timeout) noexcept
 {
  struct timespec abs_to;

  AbortIf( clock_gettime(CLOCK_REALTIME,&abs_to)!=0 ,"CCore::Sys::Sem::take()");
  
  unsigned delta_sec=(+timeout/1000);
  unsigned delta_nsec=(+timeout%1000)*1000000;
  
  if( (abs_to.tv_nsec+=delta_nsec)>=1000000000 ) 
    {
     abs_to.tv_nsec-=1000000000;
     delta_sec++;
    }
  
  abs_to.tv_sec+=delta_sec;
  
  if( sem_timedwait(&sem,&abs_to)==0 ) return true;
  
  AbortIf( errno!=ETIMEDOUT ,"CCore::Sys::Sem::take()");

  return false;
 }
  
} // namespace Sys
} // namespace CCore
 

