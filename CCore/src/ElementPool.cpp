/* ElementPool.cpp */ 
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
 
#include <CCore/inc/ElementPool.h>

#include <CCore/inc/MemBase.h>
#include <CCore/inc/Exception.h>
 
namespace CCore {

/* class MemPool */ 

Place<void> MemPool::allocBlock(ulen alloc_len)
 {
  Place<void> ptr=PlaceAt(MemAlloc(alloc_len));
  
  list.ins(new(ptr) Node);
  
  return ptr;
 }

void MemPool::newBlock()
 {
  Place<void> new_block=allocBlock(block_len);
  
  if( avail ) MemShrink(block,block_len-avail);
  
  block=new_block;
  cur=new_block+Delta;
  avail=block_len-Delta;
 }

MemPool::MemPool(ulen block_len_,ulen mem_cap_)
 : block(0),
   cur(0),
   avail(0),
   mem_cap(mem_cap_)
 {
  block_len=AlignDown(block_len_);
  
  if( block_len<=Delta )
    {
     Printf(Exception,"CCore::MemPool::MemPool(block_len=#;) : too short",block_len_);
    }
 }
 
MemPool::~MemPool()
 {
  while( Node *node=list.del() ) MemFree(node);
 }
 
Place<void> MemPool::alloc(ulen len)
 {
  if( len>MaxLen ) GuardNoMem(len);
  
  len=Align(len);
  
  if( !len ) len=MaxAlign;
  
  if( len>mem_cap ) GuardNoMem(len);

  if( avail<len ) 
    {
     if( avail>block_len/2 || len+Delta>block_len ) 
       { 
        auto ret=allocBlock(len+Delta)+Delta;
        
        mem_cap-=len;
        
        return ret; 
       }
     
     newBlock();
    }

  avail-=len;
  
  mem_cap-=len;

  return cur+=len;
 }

/* class ElementPool */

StrLen ElementPool::dup(StrLen str) 
 { 
  char *ptr=pool.alloc(str.len);
  
  str.copyTo(ptr);
  
  return StrLen(ptr,str.len);
 }

} // namespace CCore
 

