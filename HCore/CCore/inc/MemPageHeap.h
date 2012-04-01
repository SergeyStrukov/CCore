/* MemPageHeap.h */ 
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

#ifndef CCore_inc_MemPageHeap_h
#define CCore_inc_MemPageHeap_h

#include <CCore/inc/RadixHeap.h>
 
namespace CCore {

/* classes */ 

class MemPage;

class PageHeap;

/* class MemPage */ 

class MemPage : NoCopy
 {
   ulen min_alloc_len; // Sys::MemPageLen aligned
   ulen max_cache_len; // Sys::MemPageLen aligned , min_alloc_len <= max_cache_len
   ulen max_store_len; // Sys::MemPageLen aligned , max_cache_len <= max_store_len
 
   RadixHeapBlock *cache;
   ulen count;
  
  private:
  
   static RadixHeapBlock * Alloc(ulen blen);

   static void Free(RadixHeapBlock *block);
   
   void init(ulen min_alloc_len);
  
  public:
  
   MemPage();
   
   explicit MemPage(ulen min_alloc_len);
   
   void cleanup(bool clean);
   
   ulen getMaxStoreLen() const { return max_store_len; }
   
   RadixHeapBlock * alloc(ulen blen);
   
   void free(RadixHeapBlock *block);
   
   bool extend(RadixHeapBlock *block,ulen blen);
   
   ulen shrink(RadixHeapBlock *block,ulen blen);
 };
 
/* class PageHeap */ 

class PageHeap : NoCopy
 {
   RadixHeap<MemPage> heap;
   
  public: 
  
   PageHeap();
   
   explicit PageHeap(ulen min_page_alloc_len);
   
   ~PageHeap();
   
   bool isEmpty() const { return heap.isEmpty(); }
   
   void * alloc(ulen len);
  
   ulen getLen(const void *mem);    // mem!=0
  
   void free(void *mem);            // mem!=0
  
   bool extend(void *mem,ulen len); // mem!=0
  
   bool shrink(void *mem,ulen len); // mem!=0
 };
 
} // namespace CCore
 
#endif
 

