/* SysTime.h */ 
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

#ifndef CCore_inc_sys_SysTime_h
#define CCore_inc_sys_SysTime_h
 
#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Sys {

/* types */ 

typedef uint32 MSecTimeType;  // unsigned integral type

typedef uint32 SecTimeType;   // unsigned integral type
 
typedef uint64 ClockTimeType; // unsigned integral type
 
/* functions */ 

MSecTimeType GetMSecTime() noexcept;

SecTimeType GetSecTime() noexcept;
 
ClockTimeType GetClockTime() noexcept;
 
} // namespace Sys
} // namespace CCore
 
#endif
 

