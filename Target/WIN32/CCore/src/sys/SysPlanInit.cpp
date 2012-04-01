/* SysPlanInit.cpp */ 
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
 
#include <CCore/inc/sys/SysPlanInit.h>
#include <CCore/inc/sys/SysProp.h>
#include <CCore/inc/sys/SysFile.h>
#include <CCore/inc/sys/SysNet.h>
 
namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

namespace Private_SysPlanInit {

struct Empty
 {
  static const char * GetTag() { return "Sys"; }
 };
 
PlanInitObject<Empty,PlanInitReq<GetPlanInitNode_SysProp>
                    ,PlanInitReq<GetPlanInitNode_SysFile>
                    ,PlanInitReq<GetPlanInitNode_SysNet>
                    > Object CCORE_INITPRI_1 ;

} // namespace Private_SysPlanInit
 
using namespace Private_SysPlanInit; 
 
PlanInitNode * GetPlanInitNode_Sys() { return &Object; }
 
} // namespace Sys
} // namespace CCore
 

