/* DevTimer.cpp */ 
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

#include <CCore/inc/dev/DevTimer.h>

#include <CCore/inc/dev/IXP465.OST.h>

namespace CCore {
namespace Dev {

/* using */ 

using namespace IXP465;

 // TS -- time-stamp timer
 
void StartTimerTS() noexcept
 {
  OST::Bar bar;
  
  bar.null_TSPrescale()
     .setTo(bar);
     
  bar.set_TSCmp_null();
  
  bar.null_TSCfg()
     .setTo(bar);   
 }
 
void StopTimerTS() noexcept
 {
  OST::Bar bar;
  
  bar.null_TSCfg()
     .setbit(OST::TSCfg_MHz50|OST::TSCfg_Pause)
     .setTo(bar);
 }
 
unsigned TimerTS() noexcept
 {
  OST::Bar bar;
  
  return bar.get_TS();
 }
 
 // T0 -- timer 0
 
void StartTimerT0(TimerTxMode mode,unsigned div) noexcept
 {
  OST::Bar bar;
  
  uint32 reload=div-1;
  
  bar.null_T0Reload()
     .setTo(bar);

  bar.null_T0Prescale()
     .setTo(bar);

  bar.null_T0Cfg()
     .setbitIf( mode==TimerTx_MHz50 , OST::T0Cfg_MHz50 )
     .set_Reload(reload&3)
     .setTo(bar);
     
  bar.null_T0Reload()
     .setbit(OST::T0Reload_Enable)
     .set_Reload(reload>>2)
     .setTo(bar);
 }
 
void StopTimerT0() noexcept
 {
  OST::Bar bar;
  
  bar.null_T0Reload()
     .setTo(bar);

  bar.null_Status()
     .setbit(OST::Status_T0)
     .setTo(bar);
 }
 
void ClearT0Int() noexcept
 {
  OST::Bar bar;
  
  bar.null_Status()
     .setbit(OST::Status_T0)
     .setTo(bar);
 }
 
 // T1 -- timer 1
 
void StartTimerT1(TimerTxMode mode,unsigned div) noexcept
 {
  OST::Bar bar;
  
  uint32 reload=div-1;
  
  bar.null_T1Reload()
     .setTo(bar);

  bar.null_T1Prescale()
     .setTo(bar);

  bar.null_T1Cfg()
     .setbitIf( mode==TimerTx_MHz50 , OST::T1Cfg_MHz50 )
     .set_Reload(reload&3)
     .setTo(bar);
     
  bar.null_T1Reload()
     .setbit(OST::T1Reload_Enable)
     .set_Reload(reload>>2)
     .setTo(bar);
 }
 
void StopTimerT1() noexcept
 {
  OST::Bar bar;
  
  bar.null_T1Reload()
     .setTo(bar);

  bar.null_Status()
     .setbit(OST::Status_T1)
     .setTo(bar);
 }
 
void ClearT1Int() noexcept
 {
  OST::Bar bar;
  
  bar.null_Status()
     .setbit(OST::Status_T1)
     .setTo(bar);
 }
 
 // WD -- watch-dog timer
 
void EnableWatchDog(unsigned delay) noexcept
 {
  OST::Bar bar;
  
  bar.null_WDKey()
     .set_Key(OST::WDKey_Key_Open)
     .setTo(bar);

  bar.set_WD(delay);   
  
  bar.null_WDControl()
     .setbit(OST::WDControl_Enable|OST::WDControl_Reset)
     .setTo(bar);
  
  bar.null_WDKey()
     .set_Key(OST::WDKey_Key_Close)
     .setTo(bar);
 }
 
void DisableWatchDog() noexcept
 {
  OST::Bar bar;
  
  bar.null_WDKey()
     .set_Key(OST::WDKey_Key_Open)
     .setTo(bar);
     
  bar.null_WDControl()
     .setTo(bar);
  
  bar.null_WDKey()
     .set_Key(OST::WDKey_Key_Close)
     .setTo(bar);
 }
 
void DelayWatchDog(unsigned delay) noexcept
 {
  OST::Bar bar;
  
  bar.null_WDKey()
     .set_Key(OST::WDKey_Key_Open)
     .setTo(bar);
  
  bar.set_WD(delay);   
  
  bar.null_WDKey()
     .set_Key(OST::WDKey_Key_Close)
     .setTo(bar);
 }
 
} // namespace Dev
} // namespace CCore

