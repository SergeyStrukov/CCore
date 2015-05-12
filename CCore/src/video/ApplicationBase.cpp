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

namespace CCore {
namespace Video {

/* class ApplicationBase */

void ApplicationBase::forward(TimeScope time_scope)
 {
  try
    {
     idle(time_scope);
    
     desktop->wait(time_scope);
     
     if( desktop->pump() )
       {
        guardException();
       }
     else
       {
        stop();
       } 
    }
  catch(CatchType) 
    {
     showException();
     
     clearException();
    }
 }

void ApplicationBase::idle(TimeScope)
 {
 }

ApplicationBase::ApplicationBase(Desktop *desktop_,MSec tick_period)
 : DeferCallQueue(tick_period),
   desktop(desktop_)
 {
  activate();
 }

ApplicationBase::~ApplicationBase()
 {
  deactivate();
 }

int ApplicationBase::run()
 {
  try
    {
     prepare();
    
     guardException();
    }
  catch(CatchType)
    {
     showException();
     
     clearException();
    
     return 1;
    }
  
  beforeLoop();
  
  loop();
  
  afterLoop();
  
  try
    {
     final();
    
     guardException();
    }
  catch(CatchType)
    {
     showException();
     
     clearException();
    
     return 1;
    }
  
  return 0;
 }

} // namespace Video
} // namespace CCore
 

