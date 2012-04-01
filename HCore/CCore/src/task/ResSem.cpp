/* ResSem.cpp */ 
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
 
#include <CCore/inc/task/ResSem.h>

#include <CCore/inc/Abort.h> 

namespace CCore {

/* class ResSem */ 

void ResSem::init(ulen max_count_)
 {
  if( max_count_==0 ) Abort("Fatal error : CCore::ResSem initialization");
    
  max_count=max_count_;
  count=0;
  take_count=0;
  wait_count=0;
 }
   
bool ResSem::begin_take()
 {
  FastMutex::Lock lock(mutex);
  
  if( count<max_count )
    {
     count++;
     
     return true;
    }
     
  if( UIntInc(take_count) ) Abort("Fatal error : CCore::ResSem take_count overflow");
  
  return false;
 }
 
bool ResSem::begin_wait()
 {
  FastMutex::Lock lock(mutex);
   
  if( count==0 ) return true;
   
  if( UIntInc(wait_count) ) Abort("Fatal error : CCore::ResSem wait_count overflow");
  
  return false;
 }
 
bool ResSem::end_take()
 {
  FastMutex::Lock lock(mutex);
   
  if( take_count ) 
    {
     take_count--;
    
     return true;
    }
   
  return false;
 }
 
bool ResSem::end_wait()
 {
  FastMutex::Lock lock(mutex);
   
  if( wait_count ) 
    {
     wait_count--;
    
     return true;
    }
   
  return false;
 }
 
auto ResSem::begin_give() -> Result
 {
  FastMutex::Lock lock(mutex);
  
  if( count==0 ) Abort("Fatal error : CCore::ResSem underflow");
   
  if( take_count )
    {
     take_count--;
    
     return Result(true,0);
    }
  else
    {
     count--;
      
     if( count==0 ) return Result(false,Replace_null(wait_count));
     
     return Result(false,0);
    }
 }
 
ResSem::ResSem(ulen max_count)
 {
  init(max_count);
 }
   
ResSem::ResSem(TextLabel name,ulen max_count)
 : take_sem(name),
   wait_sem(name)
 {
  init(max_count);
 }
   
ResSem::~ResSem()
 {
 }
   
void ResSem::give()
 {
  auto result=begin_give();
  
  if( result.take ) take_sem.give();
  
  if( result.wait ) wait_sem.give_many(result.wait);
 }
  
bool ResSem::try_take()
 {
  FastMutex::Lock lock(mutex);
  
  if( count<max_count )
    {
     count++;
     
     return true;
    }
     
  return false;
 }
  
void ResSem::take()
 {
  if( begin_take() ) return;

  take_sem.take();
 }
  
bool ResSem::take(MSec timeout)
 {
  if( begin_take() ) return true;
  
  if( take_sem.take(timeout) ) return true;
  
  for(;;)
    {
     if( end_take() ) return false;
  
     if( take_sem.take(1_msec) ) return true;
     
     // unprobable case : repeat
    }
 }
  
bool ResSem::try_wait()
 {
  FastMutex::Lock lock(mutex);
   
  if( count==0 ) return true;
   
  return false;
 }

void ResSem::wait()
 {
  if( begin_wait() ) return;
 
  wait_sem.take();
 }
  
bool ResSem::wait(MSec timeout)
 {
  if( begin_wait() ) return true;
  
  if( wait_sem.take(timeout) ) return true;
  
  for(;;)
    {
     if( end_wait() ) return false;
  
     if( wait_sem.take(1_msec) ) return true;
     
     // unprobable case : repeat
    }
 }
 
} // namespace CCore
 

