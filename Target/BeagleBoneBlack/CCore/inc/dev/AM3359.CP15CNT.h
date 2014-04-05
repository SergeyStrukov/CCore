/* AM3359.CP15CNT.h */
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

#ifndef CCore_inc_dev_AM3359_CP15CNT_h
#define CCore_inc_dev_AM3359_CP15CNT_h

#include <CCore/inc/dev/AM3359.h>

namespace AM3359 {
namespace CP15CNT {

/* AM3359.CP15CNT.desc -> AM3359.CP15CNT.gen.h */

#include <CCore/inc/dev/AM3359.CP15CNT.gen.h>

/* functions */

Type_Control GetControl();

void SetControl(Type_Control);

Type_UserCountEnable GetUserCountEnable();

void SetUserCountEnable(Type_UserCountEnable);

Type_ClockCount GetClockCount();

Type_Count GetCount();

void SetCount(Type_Count);

void SetCounterSelect(Type_CounterSelect);

void SetEventSelect(Type_EventSelect);

void SetCountEnableSet(Type_CounterBits);

void SetCountEnableClear(Type_CounterBits);

Type_CounterBits GetCountOverflowStatus();

void SetCountOverflowStatus(Type_CounterBits);

void SetIntEnableSet(Type_CounterBits);

void SetIntEnableClear(Type_CounterBits);

void SetCountInc(Type_CounterBits);

} // namespace CP15CNT
} // namespace AM3359

#endif

