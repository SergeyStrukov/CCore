/* MultiEvent.cpp */ 
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
 
#include <CCore/inc/task/MultiEvent.h>
 
#include <CCore/inc/Abort.h>

namespace CCore {

/* class MultiEventBase */ 

void MultiEventBase::init(PtrLen<bool> flags_)
 {
  flags=flags_;
  base=0;
  
  flags_.set_null();
 }
   
bool MultiEventBase::putIndex(ulen index)
 {
  FastMutex::Lock lock(mutex);
  
  return !Replace(flags[index-1],true);
 }
   
ulen MultiEventBase::getIndex()
 {
  FastMutex::Lock lock(mutex);
  
  ulen index=base;
     
  for(; !flags[index] ;index=nextIndex(index));
     
  flags[index]=false;
     
  base=nextIndex(base);
     
  return index+1;
 }
 
MultiEventBase::MultiEventBase(PtrLen<bool> flags)
 {
  init(flags);
 }
   
MultiEventBase::MultiEventBase(TextLabel name,PtrLen<bool> flags) 
 : sem(name)
 {
  init(flags);
 }
   
MultiEventBase::~MultiEventBase()
 {
 }
  
bool MultiEventBase::trigger(ulen index)
 {
  if( index==0 || index>flags.len ) Abort("Fatal error : CCore::MultiEvent bad index");
  
  bool ret=putIndex(index);
 
  if( ret ) sem.give();
  
  return ret;
 }

ulen MultiEventBase::try_wait()
 {
  if( sem.try_take() ) return getIndex();
  
  return 0;
 }

ulen MultiEventBase::wait()
 {
  sem.take();
  
  return getIndex();
 }
   
ulen MultiEventBase::wait(MSec timeout)
 {
  if( sem.take(timeout) ) return getIndex();
  
  return 0;
 }
 
} // namespace CCore
 

