/* PlanInit_CCore.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/PlanInit.h>

#include <CCore/inc/Task.h>
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/Job.h>
#include <CCore/inc/PerTask.h>
#include <CCore/inc/TaskMemStack.h>

#include <CCore/inc/libc/stdioPlanInit.h>

namespace CCore {

/* GetPlanInitNode_...() */ 

namespace Private_PlanInit {

struct Empty
 {
  static const char * GetTag() { return "CCore"; }
 };
 
PlanInitObject<Empty,PlanInitReq<GetPlanInitNode_TaskCoreExt> 
                    ,PlanInitReq<GetPlanInitNode_stdio>
                    ,PlanInitReq<GetPlanInitNode_ObjHost>
                    ,PlanInitReq<GetPlanInitNode_JobHost>
                    ,PlanInitReq<GetPlanInitNode_PerTask>
                    ,PlanInitReq<GetPlanInitNode_TaskMemStack>
                    > Object CCORE_INITPRI_1 ;

} // namespace Private_PlanInit
 
using namespace Private_PlanInit; 
 
PlanInitNode * GetPlanInitNode_CCore() { return &Object; }
 
} // namespace CCore
 

