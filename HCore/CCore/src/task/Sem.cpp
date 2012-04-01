/* Sem.cpp */ 
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
 
#include <CCore/inc/task/Sem.h>

#include <CCore/inc/Abort.h>
 
namespace CCore {

/* class Sem */  

void Sem::init(ulen count_)
 {
  count=count_;
  take_count=0;
 }
   
bool Sem::begin_take()
 {
  FastMutex::Lock lock(mutex);
   
  if( count )
    {
     count--;
      
     return true;
    }
     
  if( UIntInc(take_count) ) Abort("Fatal error : CCore::Sem take_count overflow");
  
  return false;
 }
 
bool Sem::end_take()
 {
  FastMutex::Lock lock(mutex);
   
  if( take_count )
    {
     take_count--;
      
     return true;
    }
    
  return false;  
 }
 
bool Sem::begin_give()
 {
  FastMutex::Lock lock(mutex);
   
  if( take_count )
    {
     take_count--;
      
     return true;
    }
  else
    {
     if( UIntInc(count) ) Abort("Fatal error : CCore::Sem counter inc overflow");
     
     return false;
    }  
 }
 
ulen Sem::begin_give_many(ulen dcount)
 {
  FastMutex::Lock lock(mutex);
   
  if( take_count<dcount )
    {
     dcount-=take_count;
      
     if( UIntAdd(count,dcount) ) Abort("Fatal error : CCore::Sem counter add overflow");
     
     return Replace_null(take_count);
    }
  else
    {
     take_count-=dcount;
     
     return dcount;
    }  
 }
 
Sem::Sem(ulen count)
 {
  init(count);
 }
   
Sem::Sem(TextLabel name,ulen count)
 : sem(name)
 {
  init(count);
 }
   
Sem::~Sem()
 {
 }
 
void Sem::give()
 {
  if( begin_give() ) sem.give();
 }
   
void Sem::give_many(ulen dcount)
 {
  if( ulen cnt=begin_give_many(dcount) ) sem.give_many(cnt);
 }
   
bool Sem::try_take()
 {
  FastMutex::Lock lock(mutex);
   
  if( count )
    {
     count--;
      
     return true;
    }
     
  return false;  
 }
   
void Sem::take()
 {
  if( begin_take() ) return;
  
  sem.take();
 }
   
bool Sem::take(MSec timeout)
 {
  if( begin_take() ) return true;

  if( sem.take(timeout) ) return true;
  
  for(;;) 
    {
     if( end_take() ) return false;
  
     if( sem.take(1_msec) ) return true;
     
     // unprobable case : repeat
    }
 }
 
} // namespace CCore
 

