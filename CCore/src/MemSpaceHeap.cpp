/* MemSpaceHeap.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/MemSpaceHeap.h>
 
#include <CCore/inc/Abort.h>
#include <CCore/inc/MemBase.h>

namespace CCore {

/* class MemSpace */ 

MemSpace::MemSpace(Space space)
 {
  max_store_len=space.len;
 
  if( space.len>=RadixHeapStore::MinLen )
    {
     RadixHeapBlock *block=static_cast<RadixHeapBlock *>(space.mem);
  
     block->init(space.len);
  
     cache=block;
    }
  else
    {
     cache=0;
    }
 }
 
void MemSpace::cleanup(bool clean)
 {
  if( clean ) cache=0;
  
  if( cache ) Abort("Fatal error : memory leak");
 }
   
RadixHeapBlock * MemSpace::alloc(ulen blen)
 {
  if( cache && blen<=cache->len ) return Replace_null(cache);
  
  return 0;  
 }
   
void MemSpace::free(RadixHeapBlock *block)
 {
  cache=block;
 }
   
bool MemSpace::extend(RadixHeapBlock *,ulen)
 {
  return false;
 }
   
ulen MemSpace::shrink(RadixHeapBlock *,ulen)
 {
  return 0;
 }
 
/* class SpaceHeap */ 

SpaceHeap::AllocSpace::AllocSpace(ulen mem_len)
 {
  mem_len=AlignDown(mem_len);
 
  mem=MemAlloc(mem_len);
  len=mem_len;
 }
      
SpaceHeap::AllocSpace::~AllocSpace()
 {
  MemFree(mem);
 }
      
SpaceHeap::SpaceHeap(ulen mem_len)
 : space(mem_len),
   heap(space)
 {
 }
   
SpaceHeap::~SpaceHeap()
 {
 }
   
void * SpaceHeap::alloc(ulen len)
 {
  return heap.alloc(len).mem;
 }
  
ulen SpaceHeap::getLen(const void *mem)
 {
  return heap.getLen(mem);
 }
  
void SpaceHeap::free(void *mem)
 {
  heap.free(mem);
 }
  
bool SpaceHeap::extend(void *mem,ulen len)
 {
  return heap.extend(mem,len).ok;
 }
   
bool SpaceHeap::shrink(void *mem,ulen len)
 {
  return heap.shrink(mem,len).ok;
 }
 
} // namespace CCore
 

