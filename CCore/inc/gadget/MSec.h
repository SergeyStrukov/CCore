/* MSec.h */ 
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_MSec_h
#define CCore_inc_gadget_MSec_h

#include <CCore/inc/gadget/Replace.h>
#include <CCore/inc/gadget/Nothing.h>
 
namespace CCore {

/* classes */

struct MSecUnit;

struct MSec;

/* struct MSecUnit */

struct MSecUnit
 {
  unsigned scale;
  
  // constructors
  
  explicit constexpr MSecUnit(unsigned scale_) : scale(scale_) {}
  
  // methods
  
  template <class T>
  constexpr unsigned operator () (T time) const { return time*scale; }
 };

/* consts */

constexpr MSecUnit tuMSec(1);

constexpr MSecUnit tuSec(1000);

constexpr MSecUnit tuMin(60*1000);

constexpr MSecUnit tuHour(60*60*1000);

/* struct MSec */

struct MSec
 {
  unsigned time;
  
  // constructors
  
  constexpr MSec(NothingType) : time(0) {}
  
  explicit constexpr MSec(unsigned time_) : time(time_) {}
  
  template <class T>
  constexpr MSec(T time_,MSecUnit unit) : time(unit(time_)) {}
  
  // methods
  
  constexpr unsigned operator + () const { return time; }
  
  constexpr bool operator ! () const { return !time; }
  
  MSec cap(MSec lim) { Replace_min(time,lim.time); return *this; }
 };

inline constexpr MSec operator + (MSec a,MSec b) { return MSec(a.time+b.time);  }

inline constexpr MSec operator * (unsigned a,MSec b) { return MSec(a*b.time);  }

/* unit functions */

inline constexpr MSec operator "" _msec (unsigned long long time) { return MSec(time,tuMSec); }

inline constexpr MSec operator "" _sec  (unsigned long long time) { return MSec(time,tuSec); }

inline constexpr MSec operator "" _min  (unsigned long long time) { return MSec(time,tuMin); }

inline constexpr MSec operator "" _hour (unsigned long long time) { return MSec(time,tuHour); }

} // namespace CCore
 
#endif
 

