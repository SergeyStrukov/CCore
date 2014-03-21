/* SysPlanInit.cpp */ 
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
 
#include <CCore/inc/sys/SysPlanInit.h>

#include <CCore/inc/sys/SysCon.h>
#include <CCore/inc/sys/SysTime.h>

#include <CCore/inc/task/TaskCore.h>

#include <CCore/inc/dev/DevPlanInit.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

namespace Private_SysPlanInit {

struct Empty
 {
  static const char * GetTag() { return "Sys"; }
 };
 
PlanInitObject<Empty,PlanInitReq<Dev::GetPlanInitNode_Dev>
                    ,PlanInitReq<GetPlanInitNode_SysTime>
                    ,PlanInitReq<GetPlanInitNode_SysCon>
                    > Object CCORE_INITPRI_1 ;

} // namespace Private_SysPlanInit
 
using namespace Private_SysPlanInit; 
 
PlanInitNode * GetPlanInitNode_Sys() { return &Object; }
 
} // namespace Sys
} // namespace CCore
 

