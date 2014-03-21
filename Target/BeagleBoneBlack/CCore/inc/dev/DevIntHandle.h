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
  
  Int_TableLen
 };
 
/* functions */ 

void SetupIntHandler(IntSource intsrc,Function<void (void)> handle_int); 

void CleanupIntHandler(IntSource intsrc); 

void EnableInt(IntSource intsrc);

void DisableInt(IntSource intsrc);

} // namespace Dev
} // namespace CCore
 
#endif

