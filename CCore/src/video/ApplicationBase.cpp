/* ApplicationBase.cpp */ 
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
 
#include <CCore/inc/video/ApplicationBase.h>

#include <CCore/inc/TickTimer.h>
 
namespace CCore {
namespace Video {

/* class ApplicationBase */

bool ApplicationBase::pump()
 {
  try
    {
     clearException();
        
     if( desktop->pump() )
       {
        guardException();
          
        return true;
       }
     else
       {
        return false;
       } 
    }
  catch(CatchType) 
    {
     showException();
        
     return true;
    } 
 }

void ApplicationBase::tick()
 {
  try
    {
     clearException();
     
     do_tick();
     
     guardException();
    }
  catch(CatchType) 
    {
     showException();
    } 
 }

ApplicationBase::ApplicationBase(MSec tick_period_,Desktop *desktop_)
 : tick_period(tick_period_),
   desktop(desktop_) 
 {
 }

ApplicationBase::~ApplicationBase()
 {
 }

int ApplicationBase::run()
 {
  prepare();
  
  guardException();
  
  TickTimer timer(tick_period);
  
  while( pump() )
    {
     if( timer.poll() ) tick();
     
     desktop->wait(timer.remains());
    }
  
  guardException();
  
  return 0;
 }

} // namespace Video
} // namespace CCore
 

