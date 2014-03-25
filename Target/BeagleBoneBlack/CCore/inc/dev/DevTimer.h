/* DevTimer.h */
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

#ifndef CCore_inc_dev_DevTimer_h
#define CCore_inc_dev_DevTimer_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Dev {

/* functions */

void TimerInit(); // 24MHz clock Timer2, 10kHz int Timer4 

uint32 TimerClock();

void TimerIntEnable();

void TimerIntDisable();

bool TimerIntClear();

} // namespace Dev
} // namespace CCore

#endif

