/* PlanInit_CCore.cpp */ 
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
 
#include <CCore/inc/PlanInit.h>

#include <CCore/inc/PacketPool.h>
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/Job.h>

namespace CCore {

/* GetPlanInitNode_...() */ 

namespace Private_PlanInit {

struct Empty
 {
  static const char * GetTag() { return "CCore"; }
 };
 
PlanInitObject<Empty,PlanInitReq<GetPlanInitNode_PacketPool>
                    ,PlanInitReq<GetPlanInitNode_ObjHost>
                    ,PlanInitReq<GetPlanInitNode_JobHost>
                    > Object CCORE_INITPRI_1 ;

} // namespace Private_PlanInit
 
using namespace Private_PlanInit; 
 
PlanInitNode * GetPlanInitNode_CCore() { return &Object; }
 
} // namespace CCore
 

