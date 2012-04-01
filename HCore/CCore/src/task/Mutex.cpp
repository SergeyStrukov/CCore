/* Mutex.cpp */ 
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
 
#include <CCore/inc/task/Mutex.h>

#include <CCore/inc/Abort.h>

#include <CCore/inc/sys/SysTask.h>

namespace CCore {

/* class Mutex */ 

void Mutex::init(unsigned spin_count_)
 {
  spin_count=spin_count_;
  
  reentry=0;
  sem_count=0;
 }
 
Mutex::Mutex(unsigned spin_count)
 {
  init(spin_count);
 }
   
Mutex::Mutex(TextLabel name,unsigned spin_count)
 : sem(name)
 {
  init(spin_count);
 }
   
Mutex::~Mutex()
 {
  if( task_id ) Abort("Fatal error : CCore::Mutex is locked on exit");
 }
   
void Mutex::lock()
 {
  auto id=Sys::GetTaskId();
 
  if( task_id==id )
    {
     reentry++;
    }
  else
    {
     for(unsigned cnt=spin_count; cnt ;cnt--) if( !entry ) break;
       
     if( (entry++)==0 )
       {
        task_id=id;
       }
     else
       {
        sem.take();
        
        sem_count++;
        
        task_id=id;
       }
    }
 }
  
void Mutex::unlock()
 {
  if( reentry )
    {
     reentry--;
    }
  else
    {
     task_id=0;
     
     if( (entry--)!=1 )
       {
        sem.give();
       }
    }  
 }
  
unsigned Mutex::getSemCount()
 {
  unsigned ret;
  
  lock();
  
  ret=sem_count;
  
  unlock();
  
  return ret;
 }
 
} // namespace CCore
 

