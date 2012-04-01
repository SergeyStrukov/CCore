/* SysProp.cpp */ 
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
 
#include <CCore/inc/sys/SysProp.h>
 
#include <CCore/inc/win32/Win32.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

namespace Private_SysProp {

/* struct Info */

struct Info
 {
  Win32::SystemInfo info;
  
  unsigned spin_count;
  
  Info()
   {
    Win32::GetSystemInfo(&info);
    
    spin_count=(info.cpu_count>1)?1000:0;
   }
   
  static const char * GetTag() { return "SysProp"; } 
 };
 
PlanInitObject<Info> Object CCORE_INITPRI_1 ;
 
} // namespace Private_SysProp
 
using namespace Private_SysProp; 
 
PlanInitNode * GetPlanInitNode_SysProp() { return &Object; }
 
/* functions */ 

unsigned GetCpuCount() noexcept
 {
  return Object->info.cpu_count;
 }
 
unsigned GetSpinCount() noexcept 
 {
  return Object->spin_count;
 }
 
} // namespace Sys
} // namespace CCore
 

