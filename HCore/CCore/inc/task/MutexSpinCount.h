/* MutexSpinCount.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_task_MutexSpinCount_h
#define CCore_inc_task_MutexSpinCount_h
 
#include <CCore/inc/sys/SysProp.h>
 
namespace CCore {

/* MutexSpinCount() */ 

inline unsigned MutexSpinCount() { return Sys::GetSpinCount(); }
 
} // namespace CCore
 
#endif
 

