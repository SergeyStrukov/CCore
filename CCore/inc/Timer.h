/* Timer.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Timer_h
#define CCore_inc_Timer_h

#include <CCore/inc/Gadget.h>

#include <CCore/inc/sys/SysTime.h>
 
namespace CCore {

/* classes */ 

template <class T,T Time()> class Timer;

template <class T,T Time()> class DiffTimer;

/* class Timer<T,T Time()> */ 

template <class T,T Time()>
class Timer
 {
   T start;
   
  public:
  
   Timer() { reset(); }
   
   void reset() { start=Time(); }
   
   typedef T ValueType;
   
   T get() const { return Time()-start; }
   
   bool less(T lim) const { return get()<lim; }
   
   bool exceed(T lim) const { return get()>=lim; }
   
   void shift(T delta) { start+=delta; }
   
   static T Get() { return Time(); }
 };
 
/* class DiffTimer<T,T Time()> */ 

template <class T,T Time()>
class DiffTimer
 {
   T prev;
   
  public:
  
   DiffTimer() { reset(); }
   
   void reset() { prev=Time(); }
   
   typedef T ValueType;
   
   T get() { return Diff(prev,Time()); }
 };
 
/* types */  
 
typedef Timer<Sys::MSecTimeType,Sys::GetMSecTime> MSecTimer; 

typedef Timer<Sys::SecTimeType,Sys::GetSecTime> SecTimer; 

typedef Timer<Sys::ClockTimeType,Sys::GetClockTime> ClockTimer; 
 
typedef DiffTimer<Sys::MSecTimeType,Sys::GetMSecTime> MSecDiffTimer; 

typedef DiffTimer<Sys::SecTimeType,Sys::GetSecTime> SecDiffTimer; 

typedef DiffTimer<Sys::ClockTimeType,Sys::GetClockTime> ClockDiffTimer; 

} // namespace CCore
 
#endif
 

