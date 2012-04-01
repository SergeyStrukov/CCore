/* SysTime.cpp */ 
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
 
#include <CCore/inc/sys/SysTime.h>
 
#include <CCore/inc/win32/Win32.h>

namespace CCore {
namespace Sys {

/* functions */ 

MSecTimeType GetMSecTime() noexcept
 {
  return Win32::GetTickCount();
 }
 
SecTimeType GetSecTime() noexcept
 {
  Win32::file_time_t sys_time;
 
  Win32::GetSystemTimeAsFileTime(&sys_time);
  
  return SecTimeType( sys_time/10000000-11644473600ull );
 }
 
#if 0
  
struct DoubleUns
 {
  unsigned lo;
  unsigned hi;
 };
 
static DoubleUns CPUClock()
 {
  DoubleUns ret;
 
  asm("rdtsc" : "=a" (ret.lo) , "=d" (ret.hi) );
  
  return ret;
 }
 
ClockTimeType GetClockTime() noexcept
 {
  DoubleUns t=CPUClock();
  
  return (ClockTimeType(t.hi)<<32)|t.lo; 
 }
 
#endif
 
} // namespace Sys
} // namespace CCore
 

