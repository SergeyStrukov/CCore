/* TreeMap.h */
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

#ifndef CCore_inc_TreeMap_h
#define CCore_inc_TreeMap_h

#include <CCore/inc/FunctorType.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/NodeAllocator.h>
 
namespace CCore {

/* classes */

template <class K,class T,class KRef=K,template <class Node> class Allocator=NodeAllocator> class RBTreeMap;

/* class RBTreeMap<K,T,KRef,Allocator> */

template <class K,class T,class KRef,template <class Node> class Allocator>
class RBTreeMap : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     RBTreeLink<Node,K> link;
     T obj;
     
     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss) ... ) {}
    };
   
   typedef typename RBTreeLink<Node,K>::template Algo<&Node::link> Algo;
   
   Allocator<Node> allocator;
   
   typename Algo::Root root;
   
  private:
   
   void destroy(Node *node);
   
   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;
     
     return 0;
    }
   
   static const K & GetKey(Node *node)
    {
     return Algo::Link(node).key;
    }

   template <class Func>
   static void ApplyIncr(Node *node,Func &func);
   
   template <class Func>
   static void ApplyDecr(Node *node,Func &func);
   
  public: 
   
   // constructors
   
   template <class ... SS>
   explicit RBTreeMap(SS && ... ss) : allocator( std::forward<SS>(ss) ... ) {}
   
   ~RBTreeMap() { erase(); }
   
   // props
   
   ulen operator + () const { return +allocator; }
   
   bool operator ! () const { return !allocator; }
   
   ulen getCount() const { return allocator.getCount(); }
   
   // find
   
   T * find(KRef key) const;
   
   T * findMin() const;
   
   T * findMin(KRef key) const;
   
   T * findMax() const;
   
   T * findMax(KRef key) const;
   
   struct NodePtr
    {
     Node *node;

     NodePtr() : node(0) {}
     
     NodePtr(Node *node_) : node(node_) {}
     
     // object ptr
     
     Node * operator + () const { return node; }
     
     bool operator ! () const { return !node; }
     
     T * getPtr() const { return &node->obj; }
     
     T & operator * () const { return node->obj; }
     
     T * operator -> () const { return &node->obj; }
     
     const K & getKey() const { return GetKey(node); }
    };
   
   NodePtr find_ptr(KRef key) const;
   
   NodePtr findMin_ptr() const;
   
   NodePtr findMin_ptr(KRef key) const;
   
   NodePtr findMax_ptr() const;
   
   NodePtr findMax_ptr(KRef key) const;
   
   // add/del
   
   struct Result
    {
     T *obj;
     bool new_flag;
     
     Result(T *obj_,bool new_flag_) : obj(obj_),new_flag(new_flag_) {}
     
     operator T * () const { return obj; }
    };
   
   template <class ... SS>
   Result find_or_add(KRef key,SS && ... ss);
   
   bool del(KRef key);
   
   bool delMin();
   
   bool delMax();
   
   bool del(NodePtr node_ptr);
   
   ulen erase();
   
   // apply
   
   template <class FuncInit>
   void applyIncr(FuncInit func_init) const;
   
   template <class FuncInit>
   void applyDecr(FuncInit func_init) const;
 };

template <class K,class T,class KRef,template <class Node> class Allocator>
void RBTreeMap<K,T,KRef,Allocator>::destroy(Node *node)
 {
  if( node )
    {
     destroy(Algo::Link(node).lo);
     destroy(Algo::Link(node).hi);
     
     allocator.free(node);
    }
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
template <class Func>
void RBTreeMap<K,T,KRef,Allocator>::ApplyIncr(Node *node,Func &func)
 {
  if( node )
    {
     ApplyIncr(Algo::Link(node).lo,func);
     
     func(GetKey(node),node->obj);
     
     ApplyIncr(Algo::Link(node).hi,func);
    }
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
template <class Func>
void RBTreeMap<K,T,KRef,Allocator>::ApplyDecr(Node *node,Func &func)
 {
  if( node )
    {
     ApplyDecr(Algo::Link(node).hi,func);
     
     func(GetKey(node),node->obj);
     
     ApplyDecr(Algo::Link(node).lo,func);
    }
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
T * RBTreeMap<K,T,KRef,Allocator>::find(KRef key) const
 {
  return GetObject(root.find(key));
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
T * RBTreeMap<K,T,KRef,Allocator>::findMin() const
 {
  return GetObject(root.findMin());
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
T * RBTreeMap<K,T,KRef,Allocator>::findMin(KRef key) const
 {
  return GetObject(root.findMin(key));
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
T * RBTreeMap<K,T,KRef,Allocator>::findMax() const
 {
  return GetObject(root.findMax());
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
T * RBTreeMap<K,T,KRef,Allocator>::findMax(KRef key) const
 {
  return GetObject(root.findMax(key));
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
auto RBTreeMap<K,T,KRef,Allocator>::find_ptr(KRef key) const -> NodePtr
 {
  return root.find(key); 
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
auto RBTreeMap<K,T,KRef,Allocator>::findMin_ptr() const -> NodePtr
 {
  return root.findMin(); 
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
auto RBTreeMap<K,T,KRef,Allocator>::findMin_ptr(KRef key) const -> NodePtr
 {
  return root.findMin(key); 
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
auto RBTreeMap<K,T,KRef,Allocator>::findMax_ptr() const -> NodePtr
 {
  return root.findMax(); 
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
auto RBTreeMap<K,T,KRef,Allocator>::findMax_ptr(KRef key) const -> NodePtr
 {
  return root.findMax(key); 
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
template <class ... SS>
auto RBTreeMap<K,T,KRef,Allocator>::find_or_add(KRef key,SS && ... ss) -> Result
 {
  typename Algo::PrepareIns prepare(root,key);
  
  if( Node *node=prepare.found ) return Result(&node->obj,false);
  
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  prepare.complete(node);
  
  return Result(&node->obj,true);
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
bool RBTreeMap<K,T,KRef,Allocator>::del(KRef key)
 {
  return allocator.free(root.del(key));
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
bool RBTreeMap<K,T,KRef,Allocator>::delMin()
 {
  return allocator.free(root.delMin());
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
bool RBTreeMap<K,T,KRef,Allocator>::delMax()
 {
  return allocator.free(root.delMax());
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
bool RBTreeMap<K,T,KRef,Allocator>::del(NodePtr node_ptr)
 {
  if( Node *node=node_ptr.node )
    {
     root.del(node);
  
     allocator.free(node);
     
     return true;
    }
  
  return false;
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
ulen RBTreeMap<K,T,KRef,Allocator>::erase()
 {
  Node *ptr=root.root;
  
  root.init();
  
  ulen ret=getCount();
  
  destroy(ptr);
  
  return ret;
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
template <class FuncInit>
void RBTreeMap<K,T,KRef,Allocator>::applyIncr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);
  
  Node *node=root.root;
  
  ApplyIncr(node,func);
 }

template <class K,class T,class KRef,template <class Node> class Allocator>
template <class FuncInit>
void RBTreeMap<K,T,KRef,Allocator>::applyDecr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);
  
  Node *node=root.root;
  
  ApplyDecr(node,func);
 }

} // namespace CCore
 
#endif
 

