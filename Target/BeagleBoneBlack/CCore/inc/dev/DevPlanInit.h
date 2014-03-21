/* DevPlanInit.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_DevPlanInit_h
#define CCore_inc_dev_DevPlanInit_h

#include <CCore/inc/PlanInit.h>
 
namespace CCore {
namespace Dev {

/* init/exit functions */ 

void Init_CPU();

inline void Exit_CPU() {}
 
/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_Dev();

} // namespace Dev
} // namespace CCore
 
#endif
 

