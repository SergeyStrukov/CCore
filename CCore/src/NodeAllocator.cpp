/* NodeAllocator.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.03
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/NodeAllocator.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/MemBase.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/algon/CommonIntAlgo.h>
 
namespace CCore {

/* functions */

void NodePoolAbort()
 {
  Abort("Fatal error : node pool object leak");
 }

/* class MemBlockPool */

void * MemBlockPool::alloc_new()
 {
  if( !count )
    {
     Place<void> place(MemAlloc(alloc_len));
    
     mem_list=new(place+=Delta) FreeNode(mem_list);
     
     cur=place;
     count=alloc_count;
    }

  void *mem=(cur+=len);
  
  count--;
  
  return mem;
 }
  
MemBlockPool::MemBlockPool(ulen len_,ulen align_of,ulen alloc_count_)
 : free_list(0),
   mem_list(0),
   cur(0),
   count(0)
 {
  align_of=Algon::LCM<ulen>(align_of,alignof (FreeNode));
    
  len=Max<ulen>(len_,sizeof (FreeNode));
  
  if( !TryAlign(len,align_of) )
    {
     Printf(Exception,"CCore::MemBlockPool::MemBlockPool(len=#;,...) : too large len",len_);
    }
  
  alloc_count=Min<ulen>(alloc_count_,(MaxULen-Delta)/len);
  
  if( !alloc_count )
    {
     Printf(Exception,"CCore::MemBlockPool::MemBlockPool(len=#;,alloc_count=#;) : bad arguments",len_,alloc_count_);
    }
  
  alloc_len=Delta+len*alloc_count;
 }
   
MemBlockPool::~MemBlockPool()
 {
  for(FreeNode *node=mem_list; node ;)
    {
     FreeNode *next=node->next;
     
     MemFree(node);
     
     node=next;
    }
 }

} // namespace CCore
 

