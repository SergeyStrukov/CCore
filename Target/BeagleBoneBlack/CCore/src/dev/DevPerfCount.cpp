/* DevPerfCount.cpp */ 
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
 
#include <CCore/inc/dev/DevPerfCount.h>

#include <CCore/inc/dev/DevInt.h>

#include <CCore/inc/dev/AM3359.CP15CNT.h>
 
namespace CCore {
namespace Dev {

using namespace AM3359::CP15CNT;

/* class PerfCount */

uint64 PerfCount::do_get(unsigned index)
 {
  Type_CounterSelect sel;
  
  sel.set_SEL(index);
  
  SetCounterSelect(sel);
  
  return buf[index].update(GetCount());
 }

uint64 PerfCount::do_get_clock()
 {
  return buf[31].update(GetClockCount());
 }

void PerfCount::tick_int()
 {
  for(unsigned index=0,num=number; index<num ;index++) do_get(index);
  
  do_get_clock();
 }

PerfCount::PerfCount()
 : InstanceLock<PerfCount>("PerfCount"),
   ticker(function_tick_int())
 {
  Type_Control ctrl=GetControl();
  
  number=ctrl.get_N();
  
  ctrl.clearbit(Control_DP|Control_D|Control_E).setbit(Control_X|Control_C|Control_P);
  
  SetControl(ctrl);
  
  
  Type_UserCountEnable uen;
  
  SetUserCountEnable(uen);
  
  
  Type_CounterBits mask;
  
  mask.set_P(ToMask(number)-1).setbit(CounterBits_C);
  
  SetCountEnableClear(mask);
  SetIntEnableClear(mask);
  
  
  ctrl.setbit(Control_E);
  
  SetControl(ctrl);
  
  ticker.start(0_msec,100_msec);
 }

PerfCount::~PerfCount()
 {
  ticker.stop();
  
  Type_Control ctrl=GetControl();
  
  ctrl.clearbit(Control_E).setbit(Control_C|Control_P);
  
  SetControl(ctrl);
 }

 // methods

void PerfCount::prepare(unsigned index,PerfEvent event)
 {
  IntLock lock;
  
  stop(false,index);
  
  Type_CounterSelect sel;
  
  sel.set_SEL(index);
  
  SetCounterSelect(sel);
  
  Type_EventSelect ev;
  
  ev.set_SEL(event);
  
  SetEventSelect(ev);
  
  buf[index].reset();
  
  SetCount(0);
 }

void PerfCount::start_mask(bool clock,uint32 mask)
 {
  Type_CounterBits bits;
  
  bits.set_P(mask).setbitIf(clock,CounterBits_C);
  
  SetCountEnableSet(bits);
 }

void PerfCount::stop_mask(bool clock,uint32 mask)
 {
  Type_CounterBits bits;
  
  bits.set_P(mask).setbitIf(clock,CounterBits_C);
  
  SetCountEnableClear(bits);
 }

uint64 PerfCount::get(unsigned index)
 {
  IntLock lock;
  
  return do_get(index);
 }

uint64 PerfCount::get_clock()
 {
  IntLock lock;

  return do_get_clock();
 }

} // namespace Dev
} // namespace CCore
 

