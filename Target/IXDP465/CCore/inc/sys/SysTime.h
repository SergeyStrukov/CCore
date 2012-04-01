/* SysTime.h */ 
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

#ifndef CCore_inc_sys_SysTime_h
#define CCore_inc_sys_SysTime_h
 
#include <CCore/inc/PlanInit.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_SysTime();

/* types */ 

typedef uint64 MSecTimeType;  // unsigned integral type

typedef uint32 SecTimeType;   // unsigned integral type
 
typedef uint32 ClockTimeType; // unsigned integral type

/* consts */ 

const ClockTimeType ClocksPerSec = 66660000 ;
 
/* functions */ 

MSecTimeType GetMSecTime() noexcept;

SecTimeType GetSecTime() noexcept;
 
ClockTimeType GetClockTime() noexcept;

/* delay functions */

void ClockDelay(ClockTimeType clocks) noexcept;

inline ClockTimeType USecToClock(unsigned usecs) { return usecs*(ClocksPerSec/1000000+1); } 
 
inline void USecDelay(unsigned usecs) { ClockDelay(USecToClock(usecs)); }

} // namespace Sys
} // namespace CCore
 
#endif
 

