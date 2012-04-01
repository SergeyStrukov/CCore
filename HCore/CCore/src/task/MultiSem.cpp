/* MultiSem.cpp */ 
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
 
#include <CCore/inc/task/MultiSem.h>
 
#include <CCore/inc/Abort.h>

namespace CCore {

/* class MultiSemBase */ 

void MultiSemBase::init(PtrLen<ulen> counts_)
 {
  counts=counts_;
  base=0;
  
  counts_.set_null();
 }
 
void MultiSemBase::putIndex(ulen index)
 {
  FastMutex::Lock lock(mutex);
  
  if( UIntInc(counts[index-1]) ) Abort("Fatal error : CCore::MultiSem counter overflow");
 }
   
ulen MultiSemBase::getIndex()
 {
  FastMutex::Lock lock(mutex);
  
  ulen index=base;
     
  for(; counts[index]==0 ;index=nextIndex(index));
     
  counts[index]--;
     
  base=nextIndex(base);
     
  return index+1;
 }
 
MultiSemBase::MultiSemBase(PtrLen<ulen> counts)
 {
  init(counts);
 }
   
MultiSemBase::MultiSemBase(TextLabel name,PtrLen<ulen> counts) 
 : sem(name)
 {
  init(counts);
 }
   
MultiSemBase::~MultiSemBase()
 {
 }
   
void MultiSemBase::give(ulen index)
 {
  if( index==0 || index>counts.len ) Abort("Fatal error : CCore::MultiSem bad index");
 
  putIndex(index);
  
  sem.give();
 }
   
ulen MultiSemBase::try_take()
 {
  if( sem.try_take() ) return getIndex();
  
  return 0;
 }

ulen MultiSemBase::take()
 {
  sem.take();
  
  return getIndex();
 }
   
ulen MultiSemBase::take(MSec timeout)
 {
  if( sem.take(timeout) ) return getIndex();
  
  return 0;
 }
 
} // namespace CCore
 

