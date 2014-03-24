/* DevIntHandle.h */ 
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

#ifndef CCore_inc_dev_DevIntHandle_h
#define CCore_inc_dev_DevIntHandle_h

#include <CCore/inc/PlanInit.h>

namespace CCore {
namespace Dev {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_DevIntHandle();

/* enum IntSource */ 

enum IntSource
 {
  Int_TINT4 = 92, 
 
  Int_TableLen = 128
 };
 
/* functions */ 

void SetupIntHandler(IntSource int_source,Function<void (void)> handle_int,unsigned priority=0); // priority 0-0x3F 

void CleanupIntHandler(IntSource int_source); 

void EnableInt(IntSource int_source,unsigned priority=0); 

void DisableInt(IntSource int_source);

} // namespace Dev
} // namespace CCore
 
#endif

