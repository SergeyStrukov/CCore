/* CompactMap.h */ 
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

#ifndef CCore_inc_CompactMap_h
#define CCore_inc_CompactMap_h

#include <CCore/inc/TreeMap.h>
#include <CCore/inc/CompactNodeAllocator.h>
 
namespace CCore {

/* classes */

template <class K,class T,class KRef=K> class CompactRBTreeMap;

template <class K,class T> class CompactRadixTreeMap;

/* class CompactRBTreeMap<K,T,KRef> */

template <class K,class T,class KRef> 
class CompactRBTreeMap : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     RBTreeUpLink<Node,K> link;
     T obj;
   
     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss) ... ) {}
    };
 
   typedef typename RBTreeUpLink<Node,K>::template Algo<&Node::link> Algo;
 
   CompactNodeAllocator<Node> allocator;
 
   typename Algo::Root root;
 
  private:
   
   bool delNode(Node *node);
   
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
   explicit CompactRBTreeMap(SS && ... ss) : allocator( std::forward<SS>(ss) ... ) {}
   
   ~CompactRBTreeMap() { erase(); }
   
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
   
   // swap/move objects
   
   void objSwap(CompactRBTreeMap<K,T,KRef> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(root,obj.root);
    }
   
   explicit CompactRBTreeMap(ToMoveCtor<CompactRBTreeMap<K,T,KRef> > obj)
    : allocator(ObjToMove(obj->allocator)),
      root(obj->root)
    {
    }
   
   CompactRBTreeMap<K,T,KRef> * objMove(Place<void> place)
    {
     return CtorMove(this,place); 
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

template <class K,class T,class KRef> 
bool CompactRBTreeMap<K,T,KRef>::delNode(Node *node)
 {
  if( node )
    {
     Node *todel=allocator.todel();
     
     if( node!=todel )
       {
        root.replace(todel,node);
        
        Swap(todel->obj,node->obj);
       }
     
     allocator.del();
    
     return true;
    }
  
  return false;
 }

template <class K,class T,class KRef> 
template <class Func>
void CompactRBTreeMap<K,T,KRef>::ApplyIncr(Node *node,Func &func)
 {
  if( node )
    {
     ApplyIncr(Algo::Link(node).lo,func);
     
     func(GetKey(node),node->obj);
     
     ApplyIncr(Algo::Link(node).hi,func);
    }
 }

template <class K,class T,class KRef> 
template <class Func>
void CompactRBTreeMap<K,T,KRef>::ApplyDecr(Node *node,Func &func)
 {
  if( node )
    {
     ApplyDecr(Algo::Link(node).hi,func);
     
     func(GetKey(node),node->obj);
     
     ApplyDecr(Algo::Link(node).lo,func);
    }
 }

template <class K,class T,class KRef> 
T * CompactRBTreeMap<K,T,KRef>::find(KRef key) const
 {
  return GetObject(root.find(key));
 }

template <class K,class T,class KRef> 
T * CompactRBTreeMap<K,T,KRef>::findMin() const
 {
  return GetObject(root.findMin());
 }

template <class K,class T,class KRef> 
T * CompactRBTreeMap<K,T,KRef>::findMin(KRef key) const
 {
  return GetObject(root.findMin(key));
 }

template <class K,class T,class KRef> 
T * CompactRBTreeMap<K,T,KRef>::findMax() const
 {
  return GetObject(root.findMax());
 }

template <class K,class T,class KRef> 
T * CompactRBTreeMap<K,T,KRef>::findMax(KRef key) const
 {
  return GetObject(root.findMax(key));
 }

template <class K,class T,class KRef> 
auto CompactRBTreeMap<K,T,KRef>::find_ptr(KRef key) const -> NodePtr
 {
  return root.find(key); 
 }

template <class K,class T,class KRef> 
auto CompactRBTreeMap<K,T,KRef>::findMin_ptr() const -> NodePtr
 {
  return root.findMin(); 
 }

template <class K,class T,class KRef> 
auto CompactRBTreeMap<K,T,KRef>::findMin_ptr(KRef key) const -> NodePtr
 {
  return root.findMin(key); 
 }

template <class K,class T,class KRef> 
auto CompactRBTreeMap<K,T,KRef>::findMax_ptr() const -> NodePtr
 {
  return root.findMax(); 
 }

template <class K,class T,class KRef> 
auto CompactRBTreeMap<K,T,KRef>::findMax_ptr(KRef key) const -> NodePtr
 {
  return root.findMax(key); 
 }

template <class K,class T,class KRef> 
template <class ... SS>
auto CompactRBTreeMap<K,T,KRef>::find_or_add(KRef key,SS && ... ss) -> Result
 {
  typename Algo::PrepareIns prepare(root,key);
  
  if( Node *node=prepare.found ) return Result(&node->obj,false);
  
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  prepare.complete(node);
  
  return Result(&node->obj,true);
 }

template <class K,class T,class KRef> 
bool CompactRBTreeMap<K,T,KRef>::del(KRef key)
 {
  return delNode(root.del(key));
 }

template <class K,class T,class KRef> 
bool CompactRBTreeMap<K,T,KRef>::delMin()
 {
  return delNode(root.delMin());
 }

template <class K,class T,class KRef> 
bool CompactRBTreeMap<K,T,KRef>::delMax()
 {
  return delNode(root.delMax());
 }

template <class K,class T,class KRef> 
bool CompactRBTreeMap<K,T,KRef>::del(NodePtr node_ptr)
 {
  if( Node *node=node_ptr.node )
    {
     root.del(node);
     
     delNode(node);
    
     return true;
    }
  
  return false;
 }

template <class K,class T,class KRef> 
ulen CompactRBTreeMap<K,T,KRef>::erase()
 {
  root.init();
  
  return allocator.erase();
 }

template <class K,class T,class KRef> 
template <class FuncInit>
void CompactRBTreeMap<K,T,KRef>::applyIncr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);
  
  Node *node=root.root;
  
  ApplyIncr(node,func);
 }

template <class K,class T,class KRef> 
template <class FuncInit>
void CompactRBTreeMap<K,T,KRef>::applyDecr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);
  
  Node *node=root.root;
  
  ApplyDecr(node,func);
 }

/* class CompactRadixTreeMap<K,T> */

template <class K,class T> 
class CompactRadixTreeMap : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     TreeUpLink<Node,K> link;
     T obj;
 
     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss) ... ) {}
    };

   typedef typename TreeUpLink<Node,K>::template RadixAlgo<&Node::link> Algo;

   KeyRange<K> key_range;
 
   CompactNodeAllocator<Node> allocator;

   typename Algo::Root root;

  private:
   
   bool delNode(Node *node);
   
   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;
     
     return 0;
    }
   
   static K GetKey(Node *node)
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
   explicit CompactRadixTreeMap(SS && ... ss) : allocator( std::forward<SS>(ss) ... ) {}
   
   template <class ... SS>
   explicit CompactRadixTreeMap(KeyRange<K> key_range_,SS && ... ss) : key_range(key_range_),allocator( std::forward<SS>(ss) ... ) {}
   
   ~CompactRadixTreeMap() { erase(); }
   
   // props
   
   ulen operator + () const { return +allocator; }
   
   bool operator ! () const { return !allocator; }
   
   ulen getCount() const { return allocator.getCount(); }
   
   // find
   
   T * find(K key) const;
   
   T * findMin() const;
   
   T * findMin(K key) const;
   
   T * findMax() const;
   
   T * findMax(K key) const;
   
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
     
     K getKey() const { return GetKey(node); }
    };
   
   NodePtr find_ptr(K key) const;
   
   NodePtr findMin_ptr() const;
   
   NodePtr findMin_ptr(K key) const;
   
   NodePtr findMax_ptr() const;
   
   NodePtr findMax_ptr(K key) const;
   
   // add/del
   
   struct Result
    {
     T *obj;
     bool new_flag;
     
     Result(T *obj_,bool new_flag_) : obj(obj_),new_flag(new_flag_) {}
     
     operator T * () const { return obj; }
    };
   
   template <class ... SS>
   Result find_or_add(K key,SS && ... ss);
   
   bool del(K key);
   
   bool delMin();
   
   bool delMax();
   
   bool del(NodePtr node_ptr);
   
   ulen erase();
   
   // apply
   
   template <class FuncInit>
   void applyIncr(FuncInit func_init) const;
   
   template <class FuncInit>
   void applyDecr(FuncInit func_init) const;
   
   // swap/move objects
   
   void objSwap(CompactRadixTreeMap<K,T> &obj)
    {
     Swap(key_range,obj.key_range);
     Swap(allocator,obj.allocator);
     Swap(root,obj.root);
    }
   
   explicit CompactRadixTreeMap(ToMoveCtor<CompactRadixTreeMap<K,T> > obj)
    : key_range(obj->key_range),
      allocator(ObjToMove(obj->allocator)),
      root(obj->root)
    {
    }
   
   CompactRadixTreeMap<K,T> * objMove(Place<void> place)
    {
     return CtorMove(this,place); 
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

template <class K,class T> 
bool CompactRadixTreeMap<K,T>::delNode(Node *node)
 {
  if( node )
    {
     Node *todel=allocator.todel();
     
     if( node!=todel )
       {
        root.replace(todel,node);
        
        Swap(todel->obj,node->obj);
       }
     
     allocator.del();
    
     return true;
    }
  
  return false;
 }

template <class K,class T> 
template <class Func>
void CompactRadixTreeMap<K,T>::ApplyIncr(Node *node,Func &func)
 {
  if( node )
    {
     ApplyIncr(Algo::Link(node).lo,func);
     
     func(GetKey(node),node->obj);
     
     ApplyIncr(Algo::Link(node).hi,func);
    }
 }

template <class K,class T> 
template <class Func>
void CompactRadixTreeMap<K,T>::ApplyDecr(Node *node,Func &func)
 {
  if( node )
    {
     ApplyDecr(Algo::Link(node).hi,func);
     
     func(GetKey(node),node->obj);
     
     ApplyDecr(Algo::Link(node).lo,func);
    }
 }

template <class K,class T> 
T * CompactRadixTreeMap<K,T>::find(K key) const
 {
  return GetObject(root.find(key));
 }

template <class K,class T> 
T * CompactRadixTreeMap<K,T>::findMin() const
 {
  return GetObject(root.findMin());
 }

template <class K,class T> 
T * CompactRadixTreeMap<K,T>::findMin(K key) const
 {
  return GetObject(root.findMin(key));
 }

template <class K,class T> 
T * CompactRadixTreeMap<K,T>::findMax() const
 {
  return GetObject(root.findMax());
 }

template <class K,class T> 
T * CompactRadixTreeMap<K,T>::findMax(K key) const
 {
  return GetObject(root.findMax(key));
 }

template <class K,class T> 
auto CompactRadixTreeMap<K,T>::find_ptr(K key) const -> NodePtr
 {
  return root.find(key); 
 }

template <class K,class T> 
auto CompactRadixTreeMap<K,T>::findMin_ptr() const -> NodePtr
 {
  return root.findMin(); 
 }

template <class K,class T> 
auto CompactRadixTreeMap<K,T>::findMin_ptr(K key) const -> NodePtr
 {
  return root.findMin(key); 
 }

template <class K,class T> 
auto CompactRadixTreeMap<K,T>::findMax_ptr() const -> NodePtr
 {
  return root.findMax(); 
 }

template <class K,class T> 
auto CompactRadixTreeMap<K,T>::findMax_ptr(K key) const -> NodePtr
 {
  return root.findMax(key); 
 }

template <class K,class T> 
template <class ... SS>
auto CompactRadixTreeMap<K,T>::find_or_add(K key,SS && ... ss) -> Result
 {
  key_range.guard(key);
  
  typename Algo::PrepareIns prepare(root,key,key_range.kmin,key_range.kmax);
  
  if( Node *node=prepare.found ) return Result(&node->obj,false);
  
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  prepare.complete(node);
  
  return Result(&node->obj,true);
 }

template <class K,class T> 
bool CompactRadixTreeMap<K,T>::del(K key)
 {
  return delNode(root.del(key));
 }

template <class K,class T> 
bool CompactRadixTreeMap<K,T>::delMin()
 {
  return delNode(root.delMin());
 }

template <class K,class T> 
bool CompactRadixTreeMap<K,T>::delMax()
 {
  return delNode(root.delMax());
 }

template <class K,class T> 
bool CompactRadixTreeMap<K,T>::del(NodePtr node_ptr)
 {
  if( Node *node=node_ptr.node )
    {
     root.del(node);
     
     delNode(node);
    
     return true;
    }
  
  return false;
 }

template <class K,class T> 
ulen CompactRadixTreeMap<K,T>::erase()
 {
  root.init();
  
  return allocator.erase();
 }

template <class K,class T> 
template <class FuncInit>
void CompactRadixTreeMap<K,T>::applyIncr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);
  
  Node *node=root.root;
  
  ApplyIncr(node,func);
 }

template <class K,class T> 
template <class FuncInit>
void CompactRadixTreeMap<K,T>::applyDecr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);
  
  Node *node=root.root;
  
  ApplyDecr(node,func);
 }

} // namespace CCore
 
#endif
 

