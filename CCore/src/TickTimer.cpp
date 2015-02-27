/* TickTimer.cpp */ 
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
 
#include <CCore/inc/TickTimer.h>
 
namespace CCore {

/* class TickTimer */

bool TickTimer::poll()
 {
  auto t=timer.get();
  
  if( t>=period ) 
    {
     if( t>=2*period )
       timer.reset();
     else
       timer.shift(period);
     
     return true;
    }
  
  return false;
 }

MSec TickTimer::remains() const
 {
  auto t=timer.get();
  
  if( t>=period ) return Null;
  
  return MSec( period-t ); 
 }

} // namespace CCore
 

