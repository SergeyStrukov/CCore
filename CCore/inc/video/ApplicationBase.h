/* ApplicationBase.h */ 
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

#ifndef CCore_inc_video_ApplicationBase_h
#define CCore_inc_video_ApplicationBase_h

#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/DeferCall.h>
 
namespace CCore {
namespace Video {

/* classes */

class ApplicationBase;

/* class ApplicationBase */

class ApplicationBase : public DeferCallQueue
 {
   virtual void forward(TimeScope time_scope); 
   
  protected:
   
   const MSec tick_period;
   
   Desktop *const desktop;
  
   virtual void clearException()=0;
   
   virtual void guardException()=0;
   
   virtual void showException()=0;
   
   virtual void prepare()=0;
   
  private:
   
   bool pump();
   
  public: 
   
   explicit ApplicationBase(MSec tick_period,Desktop *desktop=DefaultDesktop);
   
   ~ApplicationBase();
   
   int run();
 };

} // namespace Video
} // namespace CCore
 
#endif
 

