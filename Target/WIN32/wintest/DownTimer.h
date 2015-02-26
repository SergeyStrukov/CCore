/* DownTimer.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_DownTimer_h
#define App_DownTimer_h
 
#include <CCore/inc/Timer.h>

namespace App {

/* using */ 

using namespace CCore;

/* classes */

class DownTimer;

/* class DownTimer */

class DownTimer 
 {
   MSecTimer timer;
   MSec period;
   
  public:
   
   explicit DownTimer(MSec period_) : period(period_) {}
   
   bool poll()
    {
     auto t=timer.get();
     
     if( t>=+period ) 
       {
        timer.reset();
        
        return true;
       }
     
     return false;
    }
   
   MSec remains() const 
    {
     auto t=timer.get();
     
     if( t>=+period ) return Null;
     
     return MSec( +period-t ); 
    }
 };

} // namespace App
 
#endif
 

