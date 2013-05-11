/* SysInternal.h */ 
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

#ifndef CCore_inc_sys_SysInternal_h
#define CCore_inc_sys_SysInternal_h

#include <CCore/inc/sys/SysAbort.h>
 
#include <time.h>

namespace CCore {
namespace Sys {

/* classes */

struct TimeSpec;

struct TimeVal;

/* struct TimeSpec */

struct TimeSpec : timespec
 {
  static unsigned GetSec(MSec time) { return +time/1000u; }
  
  static unsigned GetNanoSec(MSec time) { return (+time%1000u)*1000000u; }
  
  TimeSpec() {}
  
  explicit TimeSpec(MSec time)
   {
    tv_sec=GetSec(time);
    tv_nsec=GetNanoSec(time);
   }
  
  explicit TimeSpec(clockid_t clock_id)
   {
    AbortIf( clock_gettime(clock_id,this)!=0 ,"CCore::Sys::TimeSpec::TimeSpec");
   }
  
  TimeSpec(clockid_t clock_id,MSec time)
   {
    AbortIf( clock_gettime(clock_id,this)!=0 ,"CCore::Sys::TimeSpec::TimeSpec");
    
    unsigned delta_sec=GetSec(time);
    unsigned delta_nsec=GetNanoSec(time);
    
    if( (tv_nsec+=delta_nsec)>=1000000000 ) 
      {
       tv_nsec-=1000000000;
       delta_sec++;
      }
    
    tv_sec+=delta_sec;
   }
  
  unsigned long long getMSec() const { return tv_nsec/1000000u+tv_sec*1000ull; }
  
  unsigned long long getSec() const { return tv_sec; }
  
  unsigned long long getNanoSec() const { return tv_nsec+tv_sec*1000000000ull; }
 };

/* struct TimeVal */

struct TimeVal : timeval
 {
  static unsigned GetSec(MSec time) { return +time/1000u; }
  
  static unsigned GetMilliSec(MSec time) { return (+time%1000u)*1000u; }
  
  TimeVal() {}
  
  explicit TimeVal(MSec time)
   {
    tv_sec=GetSec(time);
    tv_usec=GetMilliSec(time);
   }
 };

} // namespace Sys
} // namespace CCore
 
#endif
 

