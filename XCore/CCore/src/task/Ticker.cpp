/* Ticker.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/task/Ticker.h>

#include <CCore/inc/dev/DevInt.h>

namespace CCore {

/* class Ticker */ 

void Ticker::tick()
 {
  if( period_msec )
    {
     if( ticks.tick(period_msec) )
       {
        action();
       }
    }
  else
    {
     if( ticks.tick() )
       {
        job.stop();
        
        action();
       }
    }  
 }

Ticker::Ticker(Function<void (void)> action_)
 : action(action_),
   job(function_tick())
 {
 }
 
Ticker::Ticker(Function<void (void)> action_,MSec delay,MSec period)
 : action(action_),
   job(function_tick())
 {
  start(delay,period);
 }
   
Ticker::~Ticker()
 {
  stop();
 }
 
void Ticker::start(MSec delay,MSec period)
 {
  Dev::IntLock lock;
  
  ticks.set(+delay);
  
  period_msec=+period;
  
  job.start();
 }

void Ticker::stop()
 {
  Dev::IntLock lock;
  
  job.stop();
 }

/* class TimedTrigger */  
      
void TimedTrigger::tick()
 {
  if( ticks.tick() )
    {
     job.stop();
     
     action();
    }
 }

TimedTrigger::TimedTrigger(Function<void (void)> action_,MSec delay)
 : action(action_),
   delay_msec(+delay),
   job(function_tick())
 {
 }
   
TimedTrigger::~TimedTrigger()
 {
  stop();
 }
 
void TimedTrigger::trigger()
 {
  Dev::IntLock lock;

  if( !job.isActive() )
    {
     ticks.set(delay_msec);
  
     job.start();
    }
 }

void TimedTrigger::stop()
 {
  Dev::IntLock lock;
  
  job.stop();
 }

} // namespace CCore
 

