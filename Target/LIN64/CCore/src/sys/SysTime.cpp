/* SysTime.cpp */ 
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
 
#include <CCore/inc/sys/SysTime.h>
#include <CCore/inc/sys/SysAbort.h>

#include <time.h>
 
namespace CCore {
namespace Sys {

/* functions */ 

MSecTimeType GetMSecTime() noexcept
 {
  struct timespec ret;
  
  AbortIf( clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ret)!=0 ,"CCore::Sys::GetMSecTime()");

  return ret.tv_sec*1000+ret.tv_nsec/1000000;
 }
 
SecTimeType GetSecTime() noexcept
 {
  time_t ret=time(0);
  
  AbortIf( ret==time_t(-1) ,"CCore::Sys::GetSecTime()");
  
  return (SecTimeType)ret;
 }
 
ClockTimeType GetClockTime() noexcept
 {
  struct timespec ret;
  
  AbortIf( clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ret)!=0 ,"CCore::Sys::GetClockTime()");

  return ret.tv_sec*1000000000ul+ret.tv_nsec;
 }
 
} // namespace Sys
} // namespace CCore
 

