/* AntiSem.cpp */ 
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
 
#include <CCore/inc/task/AntiSem.h>

#include <CCore/inc/Abort.h>
 
namespace CCore {

/* class AntiSem */ 

void AntiSem::init(ulen level_)
 {
  level=level_;
  count=0;
  wait_count=0;
 }
   
bool AntiSem::begin_wait()
 {
  FastMutex::Lock lock(mutex);
  
  if( count<=level ) return true;
   
  if( UIntInc(wait_count) ) Abort("Fatal error : CCore::AntiSem wait_count overflow");
  
  return false;
 }
 
bool AntiSem::end_wait() 
 {
  FastMutex::Lock lock(mutex);

  if( wait_count ) 
    {
     wait_count--;
     
     return true;
    }
   
  return false;
 }
 
ulen AntiSem::begin_sub(ulen dcount)
 {
  FastMutex::Lock lock(mutex);
   
  if( UIntSub(count,dcount) ) Abort("Fatal error: CCore::AntiSem counter underflow");

  if( count<=level ) return Replace_null(wait_count);
  
  return 0;
 }
 
AntiSem::AntiSem(ulen level)
 {
  init(level);
 }
   
AntiSem::AntiSem(TextLabel name,ulen level)
 : sem(name)
 {
  init(level);
 }
   
AntiSem::~AntiSem()
 {
 }
   
void AntiSem::add(ulen dcount)
 {
  FastMutex::Lock lock(mutex);
  
  if( UIntAdd(count,dcount) ) Abort("Fatal error: CCore::AntiSem counter overflow");
 }
   
void AntiSem::sub(ulen dcount)
 {
  if( ulen cnt=begin_sub(dcount) ) sem.give_many(cnt);
 }
   
bool AntiSem::try_wait()
 {
  FastMutex::Lock lock(mutex);
  
  if( count<=level ) return true;
   
  return false;
 }

void AntiSem::wait()
 {
  if( begin_wait() ) return;
  
  sem.take();
 }
   
bool AntiSem::wait(MSec timeout)
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
 

