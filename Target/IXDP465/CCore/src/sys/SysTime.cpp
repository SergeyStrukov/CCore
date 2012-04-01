/* SysTime.cpp */ 
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
 
#include <CCore/inc/sys/SysTime.h>

#include <CCore/inc/Task.h>

#include <CCore/inc/dev/DevPlanInit.h>
#include <CCore/inc/dev/DevTimer.h>
#include <CCore/inc/dev/DevSignal.h>
#include <CCore/inc/dev/DevIntHandle.h>
 
namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

namespace Private_SysTime {

/* consts */

const unsigned SecCnt = 10000 ; // timer interrupt frequency 10 kHz

const unsigned TimerDiv = Dev::MHz50/SecCnt ; // divider for timer

const unsigned MSecCnt = SecCnt/1000 ;

const unsigned TickCnt = SecCnt/TicksPerSec ;

static_assert( Dev::MHz50%SecCnt==0  ,"CCore::Sys::SecCnt bad value");
static_assert( SecCnt%1000==0        ,"CCore::Sys::SecCnt bad value");
static_assert( SecCnt%TicksPerSec==0 ,"CCore::TicksPerSec bad value");

/* class StartStop */

class StartStop : NoCopy
 {
   static unsigned Sec_cnt;
   static unsigned MSec_cnt;
   static unsigned Tick_cnt;

   static SecTimeType Time_sec;
   static MSecTimeType Time_msec;
   
   template <class T,class S>
   static bool RoundInc(T &cnt,S Cnt)
    {
     if( (++cnt)>=Cnt )
       {
        cnt=0;
        
        return true;
       }
       
     return false;  
    }

   static void Timer_int()
    {
     using namespace Dev;
  
     ClearT1Int();
  
     SetSignal(Signal_0);
     
     Time_sec+=RoundInc(Sec_cnt,SecCnt);
  
     Time_msec+=RoundInc(MSec_cnt,MSecCnt);
     
     if( RoundInc(Tick_cnt,TickCnt) ) Task::Internal::Tick_int();
    
     ClearSignal(Signal_0);
    }
 
  public:
  
   StartStop()
    {
     using namespace Dev;
  
     EnableSignal(Signal_0);
  
     StartTimerTS();
 
     SetupIntHandler(Int_T1,Timer_int);
  
     StartTimerT1(TimerTx_MHz50,TimerDiv);
    }
    
   ~StartStop() 
    {
     using namespace Dev;
 
     StopTimerT1();
  
     CleanupIntHandler(Int_T1);  
  
     StopTimerTS();
  
     DisableSignal(Signal_0);
    }
    
   static MSecTimeType GetMSecTime() noexcept
    {
     Dev::IntLock lock;
  
     return Time_msec;
    }
    
   static SecTimeType GetSecTime() noexcept
    {
     Dev::IntLock lock;
  
     return Time_sec;
    }
    
   static const char * GetTag() { return "SysTime"; } 
 };
 
unsigned StartStop::Sec_cnt=0;
unsigned StartStop::MSec_cnt=0;
unsigned StartStop::Tick_cnt=0;

SecTimeType StartStop::Time_sec=0;
MSecTimeType StartStop::Time_msec=0;
   
PlanInitObject<StartStop,PlanInitReq<Dev::GetPlanInitNode_Dev> > Object CCORE_INITPRI_1 ;

} // namespace Private_SysTime
 
using namespace Private_SysTime; 
 
PlanInitNode * GetPlanInitNode_SysTime() { return &Object; }
 
/* functions */ 

MSecTimeType GetMSecTime() noexcept
 {
  return StartStop::GetMSecTime();
 }
 
SecTimeType GetSecTime() noexcept
 {
  return StartStop::GetSecTime();
 }
 
ClockTimeType GetClockTime() noexcept
 {
  return Dev::TimerTS();
 }

void ClockDelay(ClockTimeType clocks) noexcept
 {
  for(auto start=GetClockTime(); GetClockTime()-start<=clocks ;);
 }
 
} // namespace Sys
} // namespace CCore
 
 
