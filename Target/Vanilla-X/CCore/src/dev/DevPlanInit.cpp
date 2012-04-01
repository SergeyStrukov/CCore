/* DevPlanInit.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/dev/DevPlanInit.h>

namespace CCore {
namespace Dev {

/* init/exit functions */ 

void Init_CPU()
 {
  // TODO
 }
 
void Exit_CPU() 
 {
  // TODO
 }

/* GetPlanInitNode_...() */ 

namespace Private_DevPlanInit {

struct Empty
 {
  static const char * GetTag() { return "Dev"; }
 };
 
PlanInitObject<Empty> Object CCORE_INITPRI_1 ; // TODO

} // namespace Private_DevPlanInit
 
using namespace Private_DevPlanInit; 
 
PlanInitNode * GetPlanInitNode_Dev() { return &Object; }
 
} // namespace Dev
} // namespace CCore
 

