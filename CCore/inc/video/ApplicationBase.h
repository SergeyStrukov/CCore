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

#include <CCore/inc/video/FrameWindow.h>

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
   
   Desktop *const desktop;
   
  protected: 
  
   virtual void clearException() noexcept(EnableNoExcept) =0;
   
   virtual void guardException()=0;
   
   virtual void showException() noexcept(EnableNoExcept) =0;
   
   virtual void prepare()=0;
   
   virtual void beforeLoop() noexcept(EnableNoExcept) =0;
   
   virtual void afterLoop() noexcept(EnableNoExcept) =0;
   
   virtual void final()=0;
   
   virtual void idle(TimeScope time_scope);
   
  public: 
   
   explicit ApplicationBase(Desktop *desktop,MSec tick_period);
   
   ~ApplicationBase();
   
   int run();
 };

} // namespace Video
} // namespace CCore
 
#endif
 

