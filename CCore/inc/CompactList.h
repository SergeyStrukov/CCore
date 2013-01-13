/* CompactList.h */ 
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

#ifndef CCore_inc_CompactList_h
#define CCore_inc_CompactList_h
 
#include <CCore/inc/List.h>
#include <CCore/inc/algon/ApplyToRange.h>
#include <CCore/inc/CompactNodeAllocator.h>

namespace CCore {

/* classes */

template <class T> class CompactList;

template <class T> class CompactList2;

template <class T> class CompactCircularList;

/* class CompactList<T> */

template <class T> 
class CompactList : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     DLink<Node> link;
     T obj;
 
     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss) ... ) {}
    };

   typedef typename DLink<Node>::template LinearAlgo<&Node::link> Algo;

   CompactNodeAllocator<Node> allocator;

   typename Algo::Top list;

  private:
   
   void delNode(Node *node);
 
   void delNode(Node *node,typename Algo::Cur &cur);
   
   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;
   
     return 0;
    }
 
  public:
 
   // constructors
   
   template <class ... SS>
   explicit CompactList(SS && ... ss) : allocator( std::forward<SS>(ss) ... ) {} 
   
   ~CompactList() { erase(); }
   
   // props
   
   ulen operator + () const { return +allocator; }
   
   bool operator ! () const { return !allocator; }
   
   ulen getCount() const { return allocator.getCount(); }
 
   // content
   
   T * getTop() { return GetObject(list.top); }
   
   const T * getTop() const { return GetObject(list.top); }
   
   const T * getTop_const() const { return GetObject(list.top); }
   
   template <class S>
   struct Cur
    {
     typename Algo::Cur cur;
     
     Cur() : cur(0) {}
     
     Cur(typename Algo::Cur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     S * getPtr() const { return &cur->obj; }
     
     S & operator * () const { return cur->obj; }
 
     S * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
     
     void operator -- () { --cur; }
    };
   
   Cur<T> getStart() { return list.start(); }
   
   Cur<const T> getStart() const { return list.start(); }
   
   Cur<const T> getStart_const() const { return list.start(); }
   
   template <class S>
   struct CountCur
    {
     typename Algo::Cur cur;
     ulen count;
     
     CountCur() : cur(0),count(0) {}
     
     CountCur(typename Algo::Cur cur_,ulen count_) : cur(cur_),count(count_) {}
     
     // object ptr
     
     ulen operator + () const { return count; }
     
     bool operator ! () const { return !count; }
     
     S * getPtr() const { return &cur->obj; }
     
     S & operator * () const { return cur->obj; }
 
     S * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; count--; }
     
     bool operator != (CountCur<S> obj) const { return count!=obj.count; }
    };
   
   CountCur<T> begin() { return CountCur<T>(list.start(),getCount()); }
   
   CountCur<T> end() { return CountCur<T>(); }
   
   CountCur<const T> begin() const { return CountCur<const T>(list.start(),getCount()); }
   
   CountCur<const T> end() const { return CountCur<const T>(); }
   
   // ins/del

   template <class ... SS>
   T * ins(SS && ... ss);
   
   template <class S,class ... SS>
   T * insBefore(Cur<S> pos,SS && ... ss); // +pos   
   
   template <class S,class ... SS>
   T * insAfter(Cur<S> pos,SS && ... ss); // +pos   
   
   bool del();
   
   template <class S>
   void delAndMove(Cur<S> &pos); // +pos
   
   ulen erase();
   
   // apply
   
   template <class FuncInit>
   void apply(FuncInit func_init) { Algon::ApplyToRange(getStart(),func_init); }
   
   template <class FuncInit>
   void apply(FuncInit func_init) const { Algon::ApplyToRange(getStart(),func_init); }
   
   template <class FuncInit>
   void apply_const(FuncInit func_init) const { Algon::ApplyToRange(getStart(),func_init); }
   
   // swap/move objects
   
   void objSwap(CompactList<T> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }
   
   explicit CompactList(ToMoveCtor<CompactList<T> > obj)
    : allocator(ObjToMove(obj->allocator)),
      list(obj->list)
    {
    }
   
   CompactList<T> * objMove(Place<void> place)
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

template <class T> 
void CompactList<T>::delNode(Node *node)
 {
  Node *todel=allocator.todel();
  
  if( node!=todel )
    {
     list.replace(todel,node);
     
     Swap(node->obj,todel->obj);
    }
  
  allocator.del();
 }

template <class T> 
void CompactList<T>::delNode(Node *node,typename Algo::Cur &cur)
 {
  Node *todel=allocator.todel();
  
  if( node!=todel )
    {
     list.replace(todel,node);
     
     if( cur.ptr==todel ) cur.ptr=node;
     
     Swap(node->obj,todel->obj);
    }
  
  allocator.del();
 }

template <class T> 
template <class ... SS>
T * CompactList<T>::ins(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins(node);
  
  return &node->obj;
 }

template <class T> 
template <class S,class ... SS>
T * CompactList<T>::insBefore(Cur<S> pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_before(pos.cur,node);
  
  return &node->obj;
 }

template <class T> 
template <class S,class ... SS>
T * CompactList<T>::insAfter(Cur<S> pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T> 
bool CompactList<T>::del()
 {
  if( Node *node=list.del() )
    {
     delNode(node);
    
     return true;
    }
  
  return false;
 }

template <class T> 
template <class S>
void CompactList<T>::delAndMove(Cur<S> &pos)
 {
  Node *node=list.del_and_move(pos.cur);
  
  delNode(node,pos.cur);
 }

template <class T> 
ulen CompactList<T>::erase()
 {
  list.init();
  
  return allocator.erase();
 }

/* class CompactList2<T> */

template <class T> 
class CompactList2 : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     DLink<Node> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss) ... ) {}
    };

   typedef typename DLink<Node>::template LinearAlgo<&Node::link> Algo;

   CompactNodeAllocator<Node> allocator;

   typename Algo::FirstLast list;

  private:
 
   void delNode(Node *node);

   void delNode(Node *node,typename Algo::Cur &cur);
 
   void delNode(Node *node,typename Algo::RevCur &cur);
   
   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;
 
     return 0;
    }

  public:
   
   // constructors
   
   template <class ... SS>
   explicit CompactList2(SS && ... ss) : allocator( std::forward<SS>(ss) ... ) {} 
   
   ~CompactList2() { erase(); }
   
   // props
   
   ulen operator + () const { return +allocator; }
   
   bool operator ! () const { return !allocator; }
   
   ulen getCount() const { return allocator.getCount(); }
 
   // content
   
   T * getFirst() { return GetObject(list.first); }
   
   const T * getFirst() const { return GetObject(list.first); }
   
   const T * getFirst_const() const { return GetObject(list.first); }
   
   T * getLast() { return GetObject(list.last); }
   
   const T * getLast() const { return GetObject(list.last); }
   
   const T * getLast_const() const { return GetObject(list.last); }
   
   template <class S>
   struct Cur
    {
     typename Algo::Cur cur;
     
     Cur() : cur(0) {}
     
     Cur(typename Algo::Cur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     S * getPtr() const { return &cur->obj; }
     
     S & operator * () const { return cur->obj; }
 
     S * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
     
     void operator -- () { --cur; }
    };
   
   Cur<T> getStart() { return list.start(); }
   
   Cur<const T> getStart() const { return list.start(); }
   
   Cur<const T> getStart_const() const { return list.start(); }
   
   template <class S>
   struct RevCur
    {
     typename Algo::RevCur cur;
     
     RevCur() : cur(0) {}
     
     RevCur(typename Algo::RevCur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     S * getPtr() const { return &cur->obj; }
     
     S & operator * () const { return cur->obj; }
 
     S * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
     
     void operator -- () { --cur; }
    };
   
   RevCur<T> getStartReverse() { return list.start_rev(); }
   
   RevCur<const T> getStartReverse() const { return list.start_rev(); }
   
   RevCur<const T> getStartReverse_const() const { return list.start_rev(); }

   template <class S>
   struct CountCur
    {
     typename Algo::Cur cur;
     ulen count;
     
     CountCur() : cur(0),count(0) {}
     
     CountCur(typename Algo::Cur cur_,ulen count_) : cur(cur_),count(count_) {}
     
     // object ptr
     
     ulen operator + () const { return count; }
     
     bool operator ! () const { return !count; }
     
     S * getPtr() const { return &cur->obj; }
     
     S & operator * () const { return cur->obj; }
 
     S * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; count--; }
     
     bool operator != (CountCur<S> obj) const { return count!=obj.count; }
    };
   
   CountCur<T> begin() { return CountCur<T>(list.start(),getCount()); }
   
   CountCur<T> end() { return CountCur<T>(); }
   
   CountCur<const T> begin() const { return CountCur<const T>(list.start(),getCount()); }
   
   CountCur<const T> end() const { return CountCur<const T>(); }
   
   template <class S>
   struct RevCountCur
    {
     typename Algo::RevCur cur;
     ulen count;
     
     RevCountCur() : cur(0),count(0) {}
     
     RevCountCur(typename Algo::RevCur cur_,ulen count_) : cur(cur_),count(count_) {}
     
     // object ptr
     
     ulen operator + () const { return count; }
     
     bool operator ! () const { return !count; }
     
     S * getPtr() const { return &cur->obj; }
     
     S & operator * () const { return cur->obj; }
 
     S * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; count--; }
     
     bool operator != (RevCountCur<S> obj) const { return count!=obj.count; }
    };
   
   RevCountCur<T> rbegin() { return RevCountCur<T>(list.start_rev(),getCount()); }
   
   RevCountCur<T> rend() { return RevCountCur<T>(); }
   
   RevCountCur<const T> rbegin() const { return RevCountCur<const T>(list.start_rev(),getCount()); }
   
   RevCountCur<const T> rend() const { return RevCountCur<const T>(); }
   
   template <class S>
   struct ReverseAdapter
    {
     RevCountCur<S> cur;
     
     ReverseAdapter(RevCountCur<S> cur_) : cur(cur_) {}
     
     RevCountCur<S> begin() const { return cur; }
     
     RevCountCur<S> end() const { return RevCountCur<S>(); }
    };
   
   ReverseAdapter<T> reverse() { return rbegin(); }
   
   ReverseAdapter<const T> reverse() const { return rbegin(); }
   
   ReverseAdapter<const T> reverse_const() const { return rbegin(); }
   
   // ins/del

   template <class ... SS>
   T * insFirst(SS && ... ss);
   
   template <class ... SS>
   T * insLast(SS && ... ss);
   
   template <class S,class ... SS>
   T * insBefore(Cur<S> pos,SS && ... ss); // +pos   
   
   template <class S,class ... SS>
   T * insBefore(RevCur<S> pos,SS && ... ss); // +pos   
   
   template <class S,class ... SS>
   T * insAfter(Cur<S> pos,SS && ... ss); // +pos   
   
   template <class S,class ... SS>
   T * insAfter(RevCur<S> pos,SS && ... ss); // +pos   
   
   bool delFirst();
   
   bool delLast();
   
   template <class S>
   void delAndMove(Cur<S> &pos); // +pos
   
   template <class S>
   void delAndMove(RevCur<S> &pos); // +pos
   
   ulen erase();
   
   // apply
   
   template <class FuncInit>
   void apply(FuncInit func_init) { Algon::ApplyToRange(getStart(),func_init); }
   
   template <class FuncInit>
   void apply(FuncInit func_init) const { Algon::ApplyToRange(getStart(),func_init); }
   
   template <class FuncInit>
   void apply_const(FuncInit func_init) const { Algon::ApplyToRange(getStart(),func_init); }
   
   template <class FuncInit>
   void applyReverse(FuncInit func_init) { Algon::ApplyToRange(getStartReverse(),func_init); }
   
   template <class FuncInit>
   void applyReverse(FuncInit func_init) const { Algon::ApplyToRange(getStartReverse(),func_init); }
   
   template <class FuncInit>
   void applyReverse_const(FuncInit func_init) const { Algon::ApplyToRange(getStartReverse(),func_init); }
   
   // swap/move objects
   
   void objSwap(CompactList2<T> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }
   
   explicit CompactList2(ToMoveCtor<CompactList2<T> > obj)
    : allocator(ObjToMove(obj->allocator)),
      list(obj->list)
    {
    }
   
   CompactList2<T> * objMove(Place<void> place)
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

template <class T> 
void CompactList2<T>::delNode(Node *node)
 {
  Node *todel=allocator.todel();
  
  if( node!=todel )
    {
     list.replace(todel,node);
     
     Swap(node->obj,todel->obj);
    }
  
  allocator.del();
 }

template <class T> 
void CompactList2<T>::delNode(Node *node,typename Algo::Cur &cur)
 {
  Node *todel=allocator.todel();
  
  if( node!=todel )
    {
     list.replace(todel,node);
     
     if( cur.ptr==todel ) cur.ptr=node;
     
     Swap(node->obj,todel->obj);
    }
  
  allocator.del();
 }

template <class T> 
void CompactList2<T>::delNode(Node *node,typename Algo::RevCur &cur)
 {
  Node *todel=allocator.todel();
  
  if( node!=todel )
    {
     list.replace(todel,node);
     
     if( cur.ptr==todel ) cur.ptr=node;
     
     Swap(node->obj,todel->obj);
    }
  
  allocator.del();
 }

template <class T> 
template <class ... SS>
T * CompactList2<T>::insFirst(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_first(node);
  
  return &node->obj;
 }

template <class T> 
template <class ... SS>
T * CompactList2<T>::insLast(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_last(node);
  
  return &node->obj;
 }

template <class T> 
template <class S,class ... SS>
T * CompactList2<T>::insBefore(Cur<S> pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_before(pos.cur,node);
  
  return &node->obj;
 }

template <class T> 
template <class S,class ... SS>
T * CompactList2<T>::insBefore(RevCur<S> pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_before(pos.cur,node);
  
  return &node->obj;
 }

template <class T> 
template <class S,class ... SS>
T * CompactList2<T>::insAfter(Cur<S> pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T> 
template <class S,class ... SS>
T * CompactList2<T>::insAfter(RevCur<S> pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T> 
bool CompactList2<T>::delFirst()
 {
  if( Node *node=list.del_first() )
    {
     delNode(node);
    
     return true;
    }
  
  return false;
 }

template <class T> 
bool CompactList2<T>::delLast()
 {
  if( Node *node=list.del_last() )
    {
     delNode(node);
    
     return true;
    }
  
  return false;
 }

template <class T> 
template <class S>
void CompactList2<T>::delAndMove(Cur<S> &pos)
 {
  Node *node=list.del_and_move(pos.cur);
  
  delNode(node,pos.cur);
 }

template <class T> 
template <class S>
void CompactList2<T>::delAndMove(RevCur<S> &pos)
 {
  Node *node=list.del_and_move(pos.cur);
  
  delNode(node,pos.cur);
 }

template <class T> 
ulen CompactList2<T>::erase()
 {
  list.init();
  
  return allocator.erase();
 }

/* class CompactCircularList<T> */

template <class T> 
class CompactCircularList : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     DLink<Node> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss) ... ) {}
    };

   typedef typename DLink<Node>::template CircularAlgo<&Node::link> Algo;

   CompactNodeAllocator<Node> allocator;

   typename Algo::Top list;
   
  private:
 
   void delNode(Node *node);

   void delNode(Node *node,typename Algo::Cur &cur);
 
   void delNode(Node *node,typename Algo::RevCur &cur);
   
   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;
 
     return 0;
    }

  public:
   
   // constructors
   
   template <class ... SS>
   explicit CompactCircularList(SS && ... ss) : allocator( std::forward<SS>(ss) ... ) {} 
   
   ~CompactCircularList() { erase(); }
   
   // props
   
   ulen operator + () const { return +allocator; }
   
   bool operator ! () const { return !allocator; }
   
   ulen getCount() const { return allocator.getCount(); }
 
   // content
   
   T * getTop() { return GetObject(list.top); }
   
   const T * getTop() const { return GetObject(list.top); }
   
   const T * getTop_const() const { return GetObject(list.top); }

   template <class S>
   struct Cur
    {
     typename Algo::Cur cur;
     
     Cur() : cur(0) {}
     
     Cur(typename Algo::Cur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     S * getPtr() const { return &cur->obj; }
     
     S & operator * () const { return cur->obj; }
 
     S * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
     
     void operator -- () { --cur; }
    };
   
   Cur<T> getStart() { return list.start(); }
   
   Cur<const T> getStart() const { return list.start(); }
   
   Cur<const T> getStart_const() const { return list.start(); }
   
   template <class S>
   struct RevCur
    {
     typename Algo::RevCur cur;
     
     RevCur() : cur(0) {}
     
     RevCur(typename Algo::RevCur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     S * getPtr() const { return &cur->obj; }
     
     S & operator * () const { return cur->obj; }
 
     S * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
     
     void operator -- () { --cur; }
    };
   
   RevCur<T> getStartReverse() { return list.start_rev(); }
   
   RevCur<const T> getStartReverse() const { return list.start_rev(); }
   
   RevCur<const T> getStartReverse_const() const { return list.start_rev(); }
   
   template <class S>
   struct CountCur
    {
     Node *node;
     ulen count;
     
     CountCur() : node(0),count(0) {}
     
     CountCur(Node *node_,ulen count_) : node(node_),count(count_) {}
     
     // object ptr
     
     ulen operator + () const { return count; }
     
     bool operator ! () const { return !count; }
     
     S * getPtr() const { return &node->obj; }
     
     S & operator * () const { return node->obj; }
 
     S * operator -> () const { return &node->obj; }
     
     // cursor
     
     void operator ++ () { node=Algo::Link(node).next; count--; }
     
     bool operator != (CountCur<S> obj) const { return count!=obj.count; }
    };
   
   CountCur<T> begin() { return CountCur<T>(list.top,getCount()); }
   
   CountCur<T> end() { return CountCur<T>(); }
   
   CountCur<const T> begin() const { return CountCur<const T>(list.top,getCount()); }
   
   CountCur<const T> end() const { return CountCur<const T>(); }
   
   template <class S>
   struct RevCountCur
    {
     Node *node;
     ulen count;
     
     RevCountCur() : node(0),count(0) {}
     
     RevCountCur(Node *top,ulen count_) 
      : count(count_) 
      {
       if( top )
         node=Algo::Link(top).prev;
       else
         node=0;
      }
     
     // object ptr
     
     ulen operator + () const { return count; }
     
     bool operator ! () const { return !count; }
     
     S * getPtr() const { return &node->obj; }
     
     S & operator * () const { return node->obj; }
 
     S * operator -> () const { return &node->obj; }
     
     // cursor
     
     void operator ++ () { node=Algo::Link(node).prev; count--; }
     
     bool operator != (RevCountCur<S> obj) const { return count!=obj.count; }
    };
   
   RevCountCur<T> rbegin() { return RevCountCur<T>(list.top,getCount()); }
   
   RevCountCur<T> rend() { return RevCountCur<T>(); }
   
   RevCountCur<const T> rbegin() const { return RevCountCur<const T>(list.top,getCount()); }
   
   RevCountCur<const T> rend() const { return RevCountCur<const T>(); }
   
   template <class S>
   struct ReverseAdapter
    {
     RevCountCur<S> cur;
     
     ReverseAdapter(RevCountCur<S> cur_) : cur(cur_) {}
     
     RevCountCur<S> begin() const { return cur; }
     
     RevCountCur<S> end() const { return RevCountCur<S>(); }
    };
   
   ReverseAdapter<T> reverse() { return rbegin(); }
   
   ReverseAdapter<const T> reverse() const { return rbegin(); }
   
   ReverseAdapter<const T> reverse_const() const { return rbegin(); }
   
   // ins/del

   template <class ... SS>
   T * insFirst(SS && ... ss);
   
   template <class ... SS>
   T * insLast(SS && ... ss);
   
   template <class S,class ... SS>
   T * insBefore(Cur<S> pos,SS && ... ss); // +pos   
   
   template <class S,class ... SS>
   T * insBefore(RevCur<S> &pos,SS && ... ss); // +pos   
   
   template <class S,class ... SS>
   T * insAfter(Cur<S> &pos,SS && ... ss); // +pos   
   
   template <class S,class ... SS>
   T * insAfter(RevCur<S> pos,SS && ... ss); // +pos   
   
   bool delFirst();
   
   bool delLast();
   
   template <class S>
   void delAndMove(Cur<S> &pos); // +pos
   
   template <class S>
   void delAndMove(RevCur<S> &pos); // +pos
   
   ulen erase();
   
   T * rotateForward() { return GetObject(list.rotate_forward()); } // return top element moved to bottom
   
   T * rotateBackward() { return GetObject(list.rotate_backward()); } // return bottom element moved to top
   
   // apply
   
   template <class FuncInit>
   void apply(FuncInit func_init) { Algon::ApplyToRange(getStart(),func_init); }
   
   template <class FuncInit>
   void apply(FuncInit func_init) const { Algon::ApplyToRange(getStart(),func_init); }
   
   template <class FuncInit>
   void apply_const(FuncInit func_init) const { Algon::ApplyToRange(getStart(),func_init); }
   
   template <class FuncInit>
   void applyReverse(FuncInit func_init) { Algon::ApplyToRange(getStartReverse(),func_init); }
   
   template <class FuncInit>
   void applyReverse(FuncInit func_init) const { Algon::ApplyToRange(getStartReverse(),func_init); }
   
   template <class FuncInit>
   void applyReverse_const(FuncInit func_init) const { Algon::ApplyToRange(getStartReverse(),func_init); }
   
   // swap/move objects
   
   void objSwap(CompactCircularList<T> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }
   
   explicit CompactCircularList(ToMoveCtor<CompactCircularList<T> > obj)
    : allocator(ObjToMove(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
   
   CompactCircularList<T> * objMove(Place<void> place)
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

template <class T> 
void CompactCircularList<T>::delNode(Node *node)
 {
  Node *todel=allocator.todel();
  
  if( node!=todel )
    {
     list.replace(todel,node);
     
     Swap(node->obj,todel->obj);
    }
  
  allocator.del();
 }

template <class T> 
void CompactCircularList<T>::delNode(Node *node,typename Algo::Cur &cur)
 {
  Node *todel=allocator.todel();
  
  if( node!=todel )
    {
     list.replace(todel,node);
     
     if( cur.ptr==todel ) cur.ptr=node;
     if( cur.last==todel ) cur.last=node;
     
     Swap(node->obj,todel->obj);
    }
  
  allocator.del();
 }

template <class T> 
void CompactCircularList<T>::delNode(Node *node,typename Algo::RevCur &cur)
 {
  Node *todel=allocator.todel();
  
  if( node!=todel )
    {
     list.replace(todel,node);
     
     if( cur.ptr==todel ) cur.ptr=node;
     if( cur.first==todel ) cur.first=node;
     
     Swap(node->obj,todel->obj);
    }
  
  allocator.del();
 }

template <class T> 
template <class ... SS>
T * CompactCircularList<T>::insFirst(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_first(node);
  
  return &node->obj;
 }

template <class T> 
template <class ... SS>
T * CompactCircularList<T>::insLast(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_last(node);
  
  return &node->obj;
 }

template <class T> 
template <class S,class ... SS>
T * CompactCircularList<T>::insBefore(Cur<S> pos,SS && ... ss)   
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_before(pos.cur,node);
  
  return &node->obj;
 }

template <class T> 
template <class S,class ... SS>
T * CompactCircularList<T>::insBefore(RevCur<S> &pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_before(pos.cur,node);
  
  return &node->obj;
 }

template <class T> 
template <class S,class ... SS>
T * CompactCircularList<T>::insAfter(Cur<S> &pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T> 
template <class S,class ... SS>
T * CompactCircularList<T>::insAfter(RevCur<S> pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T> 
bool CompactCircularList<T>::delFirst()
 {
  if( Node *node=list.del_first() )
    {
     delNode(node);
    
     return true;
    }
  
  return false;
 }

template <class T> 
bool CompactCircularList<T>::delLast()
 {
  if( Node *node=list.del_last() )
    {
     delNode(node);
    
     return true;
    }
  
  return false;
 }

template <class T> 
template <class S>
void CompactCircularList<T>::delAndMove(Cur<S> &pos)
 {
  Node *node=list.del_and_move(pos.cur);
  
  delNode(node,pos.cur);
 }

template <class T> 
template <class S>
void CompactCircularList<T>::delAndMove(RevCur<S> &pos)
 {
  Node *node=list.del_and_move(pos.cur);
  
  delNode(node,pos.cur);
 }

template <class T> 
ulen CompactCircularList<T>::erase()
 {
  list.init();
  
  return allocator.erase();
 }

} // namespace CCore
 
#endif
 

