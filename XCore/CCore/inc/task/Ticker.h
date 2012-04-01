/* Ticker.h */ 
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

#ifndef CCore_inc_task_Ticker_h
#define CCore_inc_task_Ticker_h

#include <CCore/inc/task/Tick.h>
 
namespace CCore {

/* classes */ 

class Ticker;

class TimedTrigger;

/* class Ticker */ 

class Ticker : public Funchor_nocopy
 {
   Function<void (void)> action;
   TickCount ticks;
   unsigned period_msec;
   
   TickJob job;
   
  private:
   
   void tick();
   
   Function<void (void)> function_tick() { return FunctionOf(this,&Ticker::tick); }
   
  public:
  
   explicit Ticker(Function<void (void)> action_int);
  
   Ticker(Function<void (void)> action_int,MSec delay,MSec period=Nothing);
   
   ~Ticker();
   
   void start(MSec delay,MSec period=Nothing);
   
   void stop();
 };
 
/* class TimedTrigger */ 
 
class TimedTrigger : public Funchor_nocopy
 {
   Function<void (void)> action;
   TickCount ticks;
   unsigned delay_msec;
   
   TickJob job;
   
  private:
  
   void tick();
  
   Function<void (void)> function_tick() { return FunctionOf(this,&TimedTrigger::tick); }
  
  public:
  
   TimedTrigger(Function<void (void)> action_int,MSec delay);
   
   ~TimedTrigger();
   
   void trigger();
   
   void stop();
 };
 
} // namespace CCore
 
#endif
 

