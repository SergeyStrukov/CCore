/* time.cpp */ 
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

#include <time.h>

#include <CCore/inc/sys/SysTime.h>

using namespace CCore;

/* clock() */  
 
clock_t clock(void)
 {
  static_assert( CLOCKS_PER_SEC==Sys::ClocksPerSec ,"Broken CLOCKS_PER_SEC definition");
  
  static_assert( clock_t(-1)==Sys::ClockTimeType(-1) ,"Broken clock_t definition");
  
  return Sys::GetClockTime();
 }
 
/* time() */ 

time_t time(time_t *time_ptr)
 {
  static_assert( time_t(-1)==Sys::SecTimeType(-1) ,"Broken time_t definition");
  
  time_t ret=Sys::GetSecTime();
  
  if( time_ptr ) (*time_ptr)=ret;

  return ret;
 }
 
