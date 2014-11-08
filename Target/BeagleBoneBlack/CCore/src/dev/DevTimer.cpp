/* DevTimer.cpp */
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

#include <CCore/inc/dev/DevTimer.h>

#include <CCore/inc/dev/AM3359.PRCM.h>
#include <CCore/inc/dev/AM3359.TIMER.h>

namespace CCore {
namespace Dev {

namespace Private_DevTimer {

class TimerDev
 {
   AM3359::TIMER::Bar bar;
   
  public: 
   
   explicit TimerDev(AM3359::TIMER::Instance instance) : bar(instance) {}
   
   // initialization
   
   void reset()
    {
     using namespace AM3359::TIMER;
     
     bar.null_OCPConfig().setbit(OCPConfig_Reset).setTo(bar);
     
     while( bar.get_OCPConfig().maskbit(OCPConfig_Reset)!=0 );
     
     bar.get_OCPConfig().set_IdleMode(OCPConfig_IdleMode_SmartIdle).setTo(bar);
     
     bar.null_RegMode().setbit(RegMode_NoReset|RegMode_PostMode).setTo(bar);
    }
   
   void init(uint32 div)
    {
     using namespace AM3359::TIMER;
     
     while( bar.get_RegPost().maskbit(RegPost_PendingControl)!=0 );
     
     bar.null_Control().setTo(bar);
     
     while( bar.get_RegPost().maskbit(RegPost_PendingCounter)!=0 );
     
     bar.set_Counter_ones();
     
     while( bar.get_RegPost().maskbit(RegPost_PendingReload)!=0 );
     
     bar.set_Reload( UIntFunc<uint32>::Neg(div) );
     
     while( bar.get_RegPost().maskbit(RegPost_PendingControl)!=0 );
     
     bar.null_Control().setbit(Control_Start|Control_AutoReload).setTo(bar);
     
     bar.ones_IntStatus().set(bar.to_IntEnableClear());
     
     bar.ones_IntStatus().setTo(bar);
    }
   
   // operational
   
   uint32 getCounter() 
    { 
     return bar.get_Counter(); 
    } 
   
   void int_enable() 
    {
     using namespace AM3359::TIMER;
     
     bar.null_IntStatus().setbit(IntStatus_Overflow).set(bar.to_IntEnableSet()); 
    }
   
   void int_disable()
    {
     using namespace AM3359::TIMER;
     
     bar.null_IntStatus().setbit(IntStatus_Overflow).set(bar.to_IntEnableClear()); 
    }
   
   bool int_clear()
    {
     using namespace AM3359::TIMER;
     
     auto status=bar.get_IntStatus();
     
     status.setTo(bar);
     
     return status.maskbit(IntStatus_Overflow);
    }
 };

} // namespace Private_DevTimer

using namespace Private_DevTimer;

/* functions */

void TimerInit()
 {
  {
   using namespace AM3359::PRCM;

   {
    BarPER per;
   
    per.null_ClockControl().set_Mode(ClockControl_Mode_Enable).set(per.to_Timer2());
   
    while( per.get_Timer2().get_IdleStatus()!=ClockControl_IdleStatus_Running );
   
    per.null_ClockControl().set_Mode(ClockControl_Mode_Enable).set(per.to_Timer4());
   
    while( per.get_Timer4().get_IdleStatus()!=ClockControl_IdleStatus_Running );
   } 
   
   {
    BarDPLL dpll;
   
    dpll.null_TimerClockSelect().set_Source(TimerClockSelect_Source_CLK_M_OSC).set(dpll.to_Timer2());
   
    dpll.null_TimerClockSelect().set_Source(TimerClockSelect_Source_CLK_M_OSC).set(dpll.to_Timer4());
   } 
  }

  {
   TimerDev dev(AM3359::TIMER::Timer2);
   
   dev.reset();
   
   dev.init(0);
  }
  
  {
   TimerDev dev(AM3359::TIMER::Timer4);
   
   dev.reset();
   
   dev.init(2400);
  }
 }

uint32 TimerClock()
 {
  return TimerDev(AM3359::TIMER::Timer2).getCounter();
 }

void TimerIntEnable()
 {
  TimerDev(AM3359::TIMER::Timer4).int_enable();
 }

void TimerIntDisable()
 {
  TimerDev(AM3359::TIMER::Timer4).int_disable();
 }

bool TimerIntClear()
 {
  return TimerDev(AM3359::TIMER::Timer4).int_clear();
 }

} // namespace Dev
} // namespace CCore

