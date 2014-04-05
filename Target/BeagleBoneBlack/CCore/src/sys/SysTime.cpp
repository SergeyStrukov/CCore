/* SysTime.cpp */ 
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
 
#include <CCore/inc/sys/SysTime.h>

#include <CCore/inc/Task.h>

#include <CCore/inc/dev/DevPlanInit.h>
#include <CCore/inc/dev/DevTimer.h>
#include <CCore/inc/dev/DevIntHandle.h>
#include <CCore/inc/dev/DevLight.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

namespace Private_SysTime {

/* consts */

const unsigned SecCnt = 10000 ; // timer interrupt frequency 10 kHz

const unsigned MSecCnt = SecCnt/1000 ;

const unsigned TickCnt = SecCnt/TicksPerSec ;

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
     if( Dev::TimerIntClear() )
       {
        if( RoundInc(Sec_cnt,SecCnt) )
          {
           Time_sec++;
          }
    
        if( RoundInc(MSec_cnt,MSecCnt) )
          {
           if( (Time_msec&511)<256 )
             Dev::LightOn(1u<<3);
           else
             Dev::LightOff(1u<<3);
          
           Time_msec++;
          }
       
        if( RoundInc(Tick_cnt,TickCnt) ) 
          {
           Task::Internal::Tick_int();
          }
       }
    }
 
  public:
  
   StartStop()
    {
     Dev::TimerInit();
 
     Dev::SetupIntHandler(Dev::Int_TINT4,Timer_int);

     Dev::TimerIntEnable();
    }
    
   ~StartStop() 
    {
     Dev::TimerIntDisable();
  
     CleanupIntHandler(Dev::Int_TINT4);  
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
  return Dev::TimerClock();
 }

void ClockDelay(ClockTimeType clocks) noexcept
 {
  for(auto start=GetClockTime(); GetClockTime()-start<=clocks ;);
 }
 
} // namespace Sys
} // namespace CCore

