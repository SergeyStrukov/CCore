/* SysProp.h */ 
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

#ifndef CCore_inc_sys_SysProp_h
#define CCore_inc_sys_SysProp_h
 
#include <CCore/inc/PlanInit.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_SysProp();

/* functions */ 

unsigned GetCpuCount() noexcept;
 
unsigned GetSpinCount() noexcept;
 
} // namespace Sys
} // namespace CCore
 
#endif
 

