/* DevPerfCount.h */ 
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

#ifndef CCore_inc_dev_DevPerfCount_h
#define CCore_inc_dev_DevPerfCount_h
 
#include <CCore/inc/task/Ticker.h>

namespace CCore {
namespace Dev {

/* enum PerfEvent */

enum PerfEvent
 {
  PerfEvent_DataRead       = 0x06,
  PerfEvent_DataWrite      = 0x07,
  PerfEvent_CmdExec        = 0x08,
  PerfEvent_ExceptionTaken = 0x09,
  PerfEvent_L2Cache        = 0x43,
  PerfEvent_L2CacheMiss    = 0x44,
  PerfEvent_AXIRead        = 0x45,
  PerfEvent_AXIWrite       = 0x46
 };

/* classes */

class PerfCount;

/* class PerfCount */

class PerfCount : public Funchor_nocopy
 {
   unsigned number;
   
   struct Rec
    {
     uint32 hi;
     uint32 lo;
     
     Rec() : hi(0),lo(0) {}
     
     void reset()
      {
       hi=0;
       lo=0;
      }
     
     uint64 update(uint32 value)
      {
       if( value<lo ) hi++;
       
       lo=value;
       
       return (uint64(hi)<<32)|value;
      }
    };
   
   Rec buf[32];
   
   Ticker ticker;
   
  private:
   
   static uint32 ToMask() { return 0; }
   
   template <class T,class ... TT>
   static uint32 ToMask(T index,TT ... indexes)
    {
     return (uint32(1)<<index)|ToMask(indexes...);
    }
   
   uint64 do_get(unsigned index);
   
   uint64 do_get_clock();
   
   void tick_int();
   
   Function<void (void)> function_tick_int() { return FunctionOf(this,&PerfCount::tick_int); }
   
  public: 
  
   PerfCount();
   
   ~PerfCount();
   
   // methods
   
   unsigned getNumberOfCounters() const { return number; }
   
   void prepare(unsigned index,PerfEvent event);
   
   void start_mask(bool clock,uint32 mask);
   
   void stop_mask(bool clock,uint32 mask);
   
   template <class ... TT>
   void start(bool clock,TT ... indexes) { start_mask(clock,ToMask(indexes...)); }
   
   template <class ... TT>
   void stop(bool clock,TT ... indexes) { stop_mask(clock,ToMask(indexes...)); }
   
   uint64 get(unsigned index);
   
   uint64 get_clock();
 };

} // namespace Dev
} // namespace CCore
 
#endif
 

