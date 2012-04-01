/* TimeScope.h */ 
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

#ifndef CCore_inc_TimeScope_h
#define CCore_inc_TimeScope_h

#include <CCore/inc/Timer.h>
 
namespace CCore {

/* classes */ 

class TimeScope;

/* class TimeScope */ 

class TimeScope
 {
   MSecTimer timer;
   
   MSec timeout;
 
  public:
  
   explicit TimeScope(MSec timeout_=Null) : timeout(timeout_) {}
   
   void start(MSec timeout_)
    {
     timer.reset();
     
     timeout=timeout_;
    }
    
   bool nextScope() 
    { 
     auto t=timer.get();
    
     if( t >= +timeout )
       {
        timer.shift(+timeout); 
        
        return true;
       } 
       
     return false;  
    }
   
   MSec get() const
    {
     auto t=timer.get();
     
     if( t >= +timeout ) return Null;
     
     return MSec(unsigned( +timeout - t ));
    }
 };
 
} // namespace CCore
 
#endif
 

