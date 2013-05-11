/* SysProp.cpp */ 
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
 
#include <CCore/inc/sys/SysProp.h>

#include <CCore/inc/Exception.h>
 
#include <unistd.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */

namespace Private_SysProp {

struct SysConfig
 {
  unsigned cpu_count;
  unsigned spin_count;
  
  SysConfig()
   {
    auto result=sysconf(_SC_NPROCESSORS_ONLN);
    
    if( result<=0 )
      {
       Printf(Exception,"CCore::Sys::SysConfig::SysConfig() : cannot determine the number of CPUs");
      }
      
    cpu_count=(unsigned)result;
    
    spin_count=(cpu_count>1)?1000:0;
   }
  
  static const char * GetTag() { return "SysConfig"; }
 };
 
PlanInitObject<SysConfig> Object CCORE_INITPRI_1 ;

} // namespace Private_SysProp

using namespace Private_SysProp;

PlanInitNode * GetPlanInitNode_SysProp() { return &Object; }

/* functions */ 

unsigned GetCpuCount() noexcept
 {
  return Object->cpu_count;
 }
 
unsigned GetSpinCount() noexcept 
 {
  return Object->spin_count;
 }
 
} // namespace Sys
} // namespace CCore
 

