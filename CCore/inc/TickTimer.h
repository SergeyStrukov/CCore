/* TickTimer.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_TickTimer_h
#define CCore_inc_TickTimer_h

#include <CCore/inc/Timer.h>
 
namespace CCore {

/* classes */

class TickTimer;

/* class TickTimer */

class TickTimer 
 {
   MSecTimer timer;
   unsigned period;
   
  public:
   
   explicit TickTimer(MSec period_) : period(+period_) {}
   
   bool poll();
   
   MSec remains() const; 
 };

} // namespace CCore
 
#endif
 

