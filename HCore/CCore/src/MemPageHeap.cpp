/* MemPageHeap.cpp */ 
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
 
#include <CCore/inc/MemPageHeap.h>
 
#include <CCore/inc/Abort.h>

#include <CCore/inc/sys/SysMemPage.h>

namespace CCore {

/* class MemPage */ 

RadixHeapBlock * MemPage::Alloc(ulen blen)
 {
  ulen num_pages=(blen+Sys::MemPageLen-1)/Sys::MemPageLen;
  
  if( !num_pages ) return 0;
 
  void *mem=Sys::MemPageAlloc(num_pages);
  
  if( !mem ) return 0;
  
  RadixHeapBlock *ret=static_cast<RadixHeapBlock *>(mem);
  
  ret->init(num_pages*Sys::MemPageLen);
  
  return ret;
 }
 
void MemPage::Free(RadixHeapBlock *block)
 {
  Sys::MemPageFree(block,block->len/Sys::MemPageLen);
 }
 
void MemPage::init(ulen min_alloc_len_)
 {
  min_alloc_len=min_alloc_len_;
  max_cache_len=2*min_alloc_len;
  max_store_len=16*min_alloc_len;
 
  cache=0;
  count=0;
 }

MemPage::MemPage()
 {      
  init(1024*Sys::MemPageLen);
 }
   
MemPage::MemPage(ulen min_alloc_len)
 {
  init(Align(min_alloc_len,Sys::MemPageLen));
 }
   
void MemPage::cleanup(bool clean)
 {
  if( clean )
    {
     if( cache ) 
       {
        Free(Replace_null(cache));
        
        count--;
       }
    }
    
  if( count ) Abort("Fatal error : memory page leak");
 }
 
RadixHeapBlock * MemPage::alloc(ulen blen)
 {
  if( cache && blen<=cache->len ) return Replace_null(cache);
  
  if( RadixHeapBlock *ret=Alloc(Max(blen,min_alloc_len)) )
    {
     count++;
     
     return ret;
    }
    
  return 0;  
 }
   
void MemPage::free(RadixHeapBlock *block)
 {
  if( cache || block->len>max_cache_len || block->len<min_alloc_len )
    {
     Free(block);
     
     count--;
    }
  else
    {
     cache=block;
    }
 }
   
bool MemPage::extend(RadixHeapBlock *block,ulen blen)
 {
  ulen len=block->len;
  
  blen=Align(blen,Sys::MemPageLen);
  
  if( blen<=len ) return false;
  
  if( !Sys::MemPageExtend(block,len/Sys::MemPageLen,(blen-len)/Sys::MemPageLen) ) return false;
  
  block->init(blen);
  
  return true;
 }
   
ulen MemPage::shrink(RadixHeapBlock *block,ulen blen)
 {
  ulen len=block->len;
  
  blen=Align(blen,Sys::MemPageLen);
  
  if( blen>=len ) return 0;
  
  ulen delta=Sys::MemPageShrink(block,len/Sys::MemPageLen,(len-blen)/Sys::MemPageLen);
  
  if( !delta ) return 0;
  
  delta*=Sys::MemPageLen;
  
  block->init(len-delta);
  
  return delta;
 }
   
/* class PageHeap */ 

PageHeap::PageHeap()
 {
 }
   
PageHeap::PageHeap(ulen min_page_alloc_len)
 : heap(min_page_alloc_len)
 {
 }
   
PageHeap::~PageHeap()
 {
 }
   
void * PageHeap::alloc(ulen len)
 {
  return heap.alloc(len).mem;
 }
  
ulen PageHeap::getLen(const void *mem)
 {
  return heap.getLen(mem);
 }
  
void PageHeap::free(void *mem)
 {
  heap.free(mem);
 }
  
bool PageHeap::extend(void *mem,ulen len)
 {
  return heap.extend(mem,len).ok;
 }
  
bool PageHeap::shrink(void *mem,ulen len)
 {
  return heap.shrink(mem,len).ok;
 }
   
} // namespace CCore
 

