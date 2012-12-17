/* NodeAllocator.h */
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

#ifndef CCore_inc_NodeAllocator_h
#define CCore_inc_NodeAllocator_h

#include <CCore/inc/MemBase.h>
 
namespace CCore {

/* functions */

void NodePoolAbort();

/* classes */

template <class Node> class NodeAllocator;

class MemBlockPool;

template <class Node> class NodePoolAllocator;

/* class NodeAllocator<Node> */

template <class Node> 
class NodeAllocator : NoCopy
 {
   ulen count;
   
  public: 
   
   NodeAllocator() : count(0) {}
   
   ulen operator + () const { return count; }
   
   bool operator ! () const { return !count; }
   
   ulen getCount() const { return count; }
   
   template <class ... SS>
   Node * alloc(SS && ... ss)
    {
     Node *ret=new Node( std::forward<SS>(ss) ... );
     
     count++;
     
     return ret;
    }
  
   bool free(Node *node)
    {
     if( node )
       {
        count--;
        
        delete node;    
       
        return true;
       }
     
     return false;
    }
 };

/* class MemBlockPool */

class MemBlockPool : NoCopy
 {
   struct FreeNode
    {
     FreeNode *next;
     
     explicit FreeNode(FreeNode *next_) : next(next_) {}
    };
   
   static const ulen Delta = Align(sizeof (FreeNode)) ;
   
  private:
   
   ulen len;
   ulen alloc_count;
   ulen alloc_len;
   
   FreeNode *free_list;
   FreeNode *mem_list;
   
   Place<void> cur;
   ulen count;
   
  private:
   
   void * alloc_new();
  
  public: 
  
   static const ulen DefaultCount = 100 ;
  
   MemBlockPool(ulen len,ulen align_of,ulen alloc_count=DefaultCount);
   
   ~MemBlockPool();
   
   void * alloc()
    {
     if( FreeNode *node=free_list )
       {
        free_list=node->next;
        
        return node;
       }
     
     return alloc_new();
    }
   
   void free(void *mem)
    {
     free_list=new(PlaceAt(mem)) FreeNode(free_list); 
    }
   
   // AllocGuard
   
   class AllocGuard : NoCopy
    {
      MemBlockPool &pool;
      void *mem;
      
     public:
     
      explicit AllocGuard(MemBlockPool &pool_)
       : pool(pool_)
       {
        mem=pool.alloc();
       }
      
      ~AllocGuard()
       {
        if( mem ) pool.free(mem);
       }
      
      operator void * () const { return mem; }
      
      void * disarm() { return Replace_null(mem); }
    };
 };

/* class NodePoolAllocator<Node> */

template <class Node> 
class NodePoolAllocator : NoCopy
 {
   MemBlockPool pool;
   
   ulen count;
   
  public: 
   
   explicit NodePoolAllocator(ulen pool_count=MemBlockPool::DefaultCount)
    : pool(sizeof (Node),alignof (Node),pool_count),
      count(0) 
    {
    }
   
   ~NodePoolAllocator() { if( count ) NodePoolAbort(); }
   
   ulen operator + () const { return count; }
   
   bool operator ! () const { return !count; }
   
   ulen getCount() const { return count; }
   
   template <class ... SS>
   Node * alloc(SS && ... ss)
    {
     MemBlockPool::AllocGuard guard(pool);
     
     Node *ret=new(PlaceAt(guard)) Node( std::forward<SS>(ss) ... );
     
     guard.disarm();
     
     count++;
     
     return ret;
    }
  
   bool free(Node *node)
    {
     if( node )
       {
        count--;
       
        node->~Node(); // assume no-throw
        
        pool.free(node);
       
        return true;
       }
     
     return false;
    }
 };

} // namespace CCore
 
#endif
 


