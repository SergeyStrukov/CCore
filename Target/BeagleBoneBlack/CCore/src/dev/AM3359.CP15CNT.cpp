/* AM3359.CP15CNT.cpp */
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

#include <CCore/inc/dev/AM3359.CP15CNT.h>

namespace AM3359 {
namespace CP15CNT {

#if 0

 // Fake code

Type_Control GetControl() { return Type_Control(0); }

void SetControl(Type_Control) {}

Type_UserCountEnable GetUserCountEnable() { return Type_UserCountEnable(0); }

void SetUserCountEnable(Type_UserCountEnable) {}

Type_ClockCount GetClockCount() { return Type_ClockCount(0); }

Type_Count GetCount() { return Type_Count(0); }

void SetCounterSelect(Type_CounterSelect) {}

void SetEventSelect(Type_EventSelect) {}

void SetCountEnableSet(Type_CounterBits) {}

void SetCountEnableClear(Type_CounterBits) {}

Type_CounterBits GetCountOverflowStatus() { return Type_CounterBits(0); }

void SetCountOverflowStatus(Type_CounterBits) {}

void SetIntEnableSet(Type_CounterBits) {}

void SetIntEnableClear(Type_CounterBits) {}

void SetCountInc(Type_CounterBits) {}

void SetCount(Type_Count) {}

#endif

} // namespace CP15CNT
} // namespace AM3359
