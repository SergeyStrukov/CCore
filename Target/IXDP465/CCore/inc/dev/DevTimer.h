/* DevTimer.h */ 
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

#ifndef CCore_inc_dev_DevTimer_h
#define CCore_inc_dev_DevTimer_h

namespace CCore {
namespace Dev {

/* consts */ 

const unsigned MHz66 = 66660000 ;

const unsigned MHz50 = 50000000 ;

const unsigned TimerTSFq = MHz66 ;

enum TimerTxMode
 {
  TimerTx_MHz50,
  TimerTx_MHz66
 };
 
/* functions : NOT LOCKED */ 

 // TS -- time-stamp timer 

void StartTimerTS() noexcept; // 66 MHz

void StopTimerTS() noexcept;

unsigned TimerTS() noexcept;

 // T0 -- timer 0
 
void StartTimerT0(TimerTxMode mode,unsigned div) noexcept;

void StopTimerT0() noexcept;

void ClearT0Int() noexcept;

 // T1 -- timer 1
 
void StartTimerT1(TimerTxMode mode,unsigned div) noexcept;

void StopTimerT1() noexcept;

void ClearT1Int() noexcept;

 // WD -- watch-dog timer
 
void EnableWatchDog(unsigned delay) noexcept; // 66 MHz

void DisableWatchDog() noexcept;

void DelayWatchDog(unsigned delay) noexcept;

} // namespace Dev
} // namespace CCore
 
#endif





