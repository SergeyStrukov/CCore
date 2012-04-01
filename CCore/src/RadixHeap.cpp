/* RadixHeap.cpp */ 
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
 
#include <CCore/inc/RadixHeap.h>

#include <CCore/inc/Abort.h>
 
namespace CCore {

/* functions */ 

void RadixHeapAbort()
 {
  Abort("Fatal error : heap violation");
 }
 
/* struct RadixHeapBlock */ 

unsigned RadixHeapBlock::Check(void *mem,ulen total)
 {
  RadixHeapBlock *block=static_cast<RadixHeapBlock *>(mem);
     
  if( !(block->flags&RadixHeapBlock::FirstBit) ) return 1;
     
  while( !(block->flags&RadixHeapBlock::LastBit) )
    {
     ulen len=block->len;
       
     if( len>=total ) return 2;
        
     if( len<RadixHeapStore::MinLen ) return 3;
        
     if( (len%MaxAlign)!=0 ) return 4;
        
     RadixHeapBlock *next=block->getNext();
        
     if( next->prev_len!=len ) return 5;
        
     if( (block->flags&RadixHeapBlock::LockBit) )
       {
        if( block->magic!=block->stamp() ) return 6;
       }
        
     block=next;
     total-=len;
    }
       
    {
     ulen len=block->len;
       
     if( len!=total || len<RadixHeapStore::MinLen ) return 7;
        
     if( (len%MaxAlign)!=0 ) return 8;
        
     if( (block->flags&RadixHeapBlock::LockBit) )
       {
        if( block->magic!=block->stamp() ) return 9;
       }
    }
    
  return 0;  
 }
 
/* struct RadixHeapStore_small */ 

RadixHeapStore_small::RadixHeapStore_small()
 {
 }
 
void RadixHeapStore_small::ins(Node *node,ulen ind)
 {
  tops[ind].ins(node);
  
  bits.set(ind);
 }
  
void RadixHeapStore_small::del(Node *node,ulen ind)
 {
  Algo::Top &top=tops[ind];
  
  top.del(node);
  
  if( !top ) bits.clear(ind);
 }
  
auto RadixHeapStore_small::find_and_del(ulen ind) -> Node *
 {
  ind=bits.findMin(ind);
  
  if( ind<IndexLim )
    {
     Algo::Top &top=tops[ind];
     
     Node *ret=top.del();
  
     if( !top ) bits.clear(ind);
     
     return ret;
    }
    
  return 0;  
 }
 
/* struct RadixHeapStore_large */ 

void RadixHeapStore_large::ins(Node *node,ulen ind)
 {
  root.ins(node,ind,0,max_ind);
 }
  
void RadixHeapStore_large::del(Node *node,ulen)
 {
  root.del(node);
 }
  
auto RadixHeapStore_large::find_and_del(ulen ind) -> Node *
 {
  return root.delMin(ind);
 }
 
/* struct RadixHeapStore */ 

void RadixHeapStore::ins(RadixHeapBlock *block)
 {
  static_assert( RadixHeapStore_small::IndexLim*MaxAlign >= sizeof (RadixHeapStore_large::Node) ,"CCore::RadixHeapStore_small::IndexLim is too small");

  ulen ind=Index(block->len);
  
  if( ind<RadixHeapStore_small::IndexLim )
    small.ins(block->getMem(),ind);
  else
    large.ins(block->getMem(),ind);
 }
  
void RadixHeapStore::del(RadixHeapBlock *block)
 {
  ulen ind=Index(block->len);
  
  if( ind<RadixHeapStore_small::IndexLim )
    small.del(block->getMem(),ind);
  else
    large.del(block->getMem(),ind);
 }
  
RadixHeapBlock * RadixHeapStore::find_and_del(ulen len)
 {
  ulen ind=Index(len);
  
  if( ind<RadixHeapStore_small::IndexLim )
    {
     if( RadixHeapStore_small::Node *node=small.find_and_del(ind) )
       {
        return RadixHeapBlock::GetBlock(node);
       }
    }
 
  if( RadixHeapStore_large::Node *node=large.find_and_del(ind) )
    {
     return RadixHeapBlock::GetBlock(node);
    }
       
  return 0;
 }
 
} // namespace CCore
 

