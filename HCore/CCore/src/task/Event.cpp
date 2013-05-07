/* Event.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/task/Event.h>

#include <CCore/inc/Abort.h>
 
namespace CCore {

/* class Event */ 

void Event::init(bool flag_)
 {
  flag=flag_;
  wait_count=0;
 }
   
bool Event::begin_wait()
 {
  FastMutex::Lock lock(mutex);

  if( flag )
    {
     flag=false;
     
     return true;
    }
    
  if( UIntInc(wait_count) ) Abort("Fatal error : CCore::Event wait_count overflow"); 
  
  return false;
 }
   
bool Event::end_wait()
 {
  FastMutex::Lock lock(mutex);
   
  if( wait_count ) 
    {
     wait_count--;
     
     return true;
    }
   
  return false; 
 }
 
bool Event::begin_trigger(bool &ret)
 {
  FastMutex::Lock lock(mutex);
   
  if( wait_count )
    {
     wait_count--;
     
     ret=true;
      
     return true;
    }
  else
    {
     ret=!Replace(flag,true);
     
     return false;
    }  
 }
 
Event::Event(int flag)
 {
  init(flag);
 }
   
Event::Event(TextLabel name,bool flag)
 : sem(name)
 {
  init(flag);
 }
  
Event::~Event()
 {
 }
 
bool Event::trigger()
 {
  bool ret;
  
  if( begin_trigger(ret) ) sem.give();
  
  return ret;
 }
   
bool Event::try_wait()
 {
  FastMutex::Lock lock(mutex);

  if( flag )
    {
     flag=false;
     
     return true;
    }
    
  return false;
 }

void Event::wait()
 {
  if( begin_wait() ) return;
  
  sem.take();
 }
   
bool Event::wait(MSec timeout)
 {
  if( begin_wait() ) return true;
  
  if( sem.take(timeout) ) return true;
  
  for(;;)
    {
     if( end_wait() ) return false;
  
     if( sem.take(1_msec) ) return true;
     
     // unprobable case : repeat
    }
 }
 
} // namespace CCore
 

