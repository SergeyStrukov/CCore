/* ContainerList.h */
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

#ifndef CCore_inc_ContainerList_h
#define CCore_inc_ContainerList_h

#include <CCore/inc/List.h>
#include <CCore/inc/algon/ApplyToRange.h>
#include <CCore/inc/NodeAllocator.h>
 
namespace CCore {

/* classes */

template <class T,template <class Node> class Allocator=NodeAllocator> class LinearSList;

template <class T,template <class Node> class Allocator=NodeAllocator> class LinearSList2;

template <class T,template <class Node> class Allocator=NodeAllocator> class CircularSList;

template <class T,template <class Node> class Allocator=NodeAllocator> class LinearDList;

template <class T,template <class Node> class Allocator=NodeAllocator> class LinearDList2;

template <class T,template <class Node> class Allocator=NodeAllocator> class CircularDList;

/* class LinearSList<T,Allocator> */

template <class T,template <class Node> class Allocator> 
class LinearSList : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     SLink<Node> link;
     T obj;
     
     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss) ... ) {}
    };
   
   typedef typename SLink<Node>::template LinearAlgo<&Node::link> Algo;
   
   Allocator<Node> allocator;
   
   typename Algo::Top list;
   
  private: 
   
   void destroy(Node *node);
   
   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;
     
     return 0;
    }
   
  public:

   // constructors
   
   template <class ... SS>
   explicit LinearSList(SS && ... ss) : allocator( std::forward<SS>(ss) ... ) {}
   
   ~LinearSList() { erase(); }
   
   // props
   
   ulen operator + () const { return +allocator; }
   
   bool operator ! () const { return !allocator; }
   
   ulen getCount() const { return allocator.getCount(); }
   
   // content
   
   T * getTop() const { return GetObject(list.top); }
   
   struct Cur
    {
     typename Algo::Cur cur;
     
     Cur() : cur(0) {}
     
     Cur(typename Algo::Cur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
    };
   
   Cur getStart() const { return list.start(); }
   
   struct CountCur
    {
     typename Algo::Cur cur;
     ulen count;
     
     CountCur() : cur(0),count(0) {}
     
     CountCur(typename Algo::Cur cur_,ulen count_) : cur(cur_),count(count_) {}
     
     // object ptr
     
     ulen operator + () const { return count; }
     
     bool operator ! () const { return !count; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; count--; }
     
     bool operator != (CountCur obj) const { return count!=obj.count; }
    };
   
   CountCur begin() const { return CountCur(list.start(),getCount()); }
   
   CountCur end() const { return CountCur(); }
   
   // ins/del

   template <class ... SS>
   T * ins(SS && ... ss);
   
   template <class ... SS>
   T * insAfter(Cur pos,SS && ... ss); // +pos   
   
   bool del();
   
   ulen erase();
   
   // apply
   
   template <class FuncInit>
   void apply(FuncInit func_init) { Algon::ApplyToRange(getStart(),func_init); }
   
   // swap/move objects
   
   void objSwap(LinearSList<T,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }
   
   explicit LinearSList(ToMoveCtor<LinearSList<T,Allocator> > obj)
    : allocator(ObjToMove(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
   
   LinearSList<T,Allocator> * objMove(Place<void> place)
    {
     return CtorMove(this,place); 
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = Allocator<Node>::Default_no_throw,
     Copy_no_throw = true
    };
 };

template <class T,template <class Node> class Allocator> 
void LinearSList<T,Allocator>::destroy(Node *node)
 {
  while( node )
    {
     Node *next=Algo::Link(node).next;
     
     allocator.free(node);
     
     node=next;
    }
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearSList<T,Allocator>::ins(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins(node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearSList<T,Allocator>::insAfter(Cur pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
bool LinearSList<T,Allocator>::del()
 {
  return allocator.free(list.del());
 }

template <class T,template <class Node> class Allocator> 
ulen LinearSList<T,Allocator>::erase()
 {
  Node *node=list.top;
  
  list.init();
  
  ulen ret=getCount();
  
  destroy(node);
  
  return ret;
 }

/* class LinearSList2<T,Allocator> */

template <class T,template <class Node> class Allocator> 
class LinearSList2 : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     SLink<Node> link;
     T obj;
     
     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss) ... ) {}
    };
   
   typedef typename SLink<Node>::template LinearAlgo<&Node::link> Algo;
   
   Allocator<Node> allocator;
   
   typename Algo::FirstLast list;
   
  private: 
   
   void destroy(Node *node);
   
   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;
     
     return 0;
    }
   
  public:
   
   // constructors
   
   template <class ... SS>
   explicit LinearSList2(SS && ... ss) : allocator( std::forward<SS>(ss) ... ) {}
   
   ~LinearSList2() { erase(); }
   
   // props
   
   ulen operator + () const { return +allocator; }
   
   bool operator ! () const { return !allocator; }
   
   ulen getCount() const { return allocator.getCount(); }
   
   // content
   
   T * getFirst() const { return GetObject(list.first); }
   
   T * getLast() const { return GetObject(list.last); }
   
   struct Cur
    {
     typename Algo::Cur cur;
     
     Cur() : cur(0) {}
     
     Cur(typename Algo::Cur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
    };
   
   Cur getStart() const { return list.start(); }
   
   struct CountCur
    {
     typename Algo::Cur cur;
     ulen count;
     
     CountCur() : cur(0),count(0) {}
     
     CountCur(typename Algo::Cur cur_,ulen count_) : cur(cur_),count(count_) {}
     
     // object ptr
     
     ulen operator + () const { return count; }
     
     bool operator ! () const { return !count; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; count--; }
     
     bool operator != (CountCur obj) const { return count!=obj.count; }
    };
   
   CountCur begin() const { return CountCur(list.start(),getCount()); }
   
   CountCur end() const { return CountCur(); }
   
   // ins/del

   template <class ... SS>
   T * insFirst(SS && ... ss);
   
   template <class ... SS>
   T * insLast(SS && ... ss);
   
   template <class ... SS>
   T * insAfter(Cur pos,SS && ... ss); // +pos   
   
   bool delFirst();
   
   ulen erase();
   
   // apply
   
   template <class FuncInit>
   void apply(FuncInit func_init) { Algon::ApplyToRange(getStart(),func_init); }
   
   // swap/move objects
   
   void objSwap(LinearSList2<T,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }
   
   explicit LinearSList2(ToMoveCtor<LinearSList2<T,Allocator> > obj)
    : allocator(ObjToMove(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
   
   LinearSList2<T,Allocator> * objMove(Place<void> place)
    {
     return CtorMove(this,place); 
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = Allocator<Node>::Default_no_throw,
     Copy_no_throw = true
    };
 };  
   
template <class T,template <class Node> class Allocator> 
void LinearSList2<T,Allocator>::destroy(Node *node)
 {
  while( node )
    {
     Node *next=Algo::Link(node).next;
     
     allocator.free(node);
     
     node=next;
    }
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearSList2<T,Allocator>::insFirst(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_first(node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearSList2<T,Allocator>::insLast(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_last(node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearSList2<T,Allocator>::insAfter(Cur pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
bool LinearSList2<T,Allocator>::delFirst()
 {
  return allocator.free(list.del_first());
 }

template <class T,template <class Node> class Allocator> 
ulen LinearSList2<T,Allocator>::erase()
 {
  Node *node=list.first;
  
  list.init();
  
  ulen ret=getCount();
  
  destroy(node);
  
  return ret;
 }

/* class CircularSList<T,Allocator> */

template <class T,template <class Node> class Allocator> 
class CircularSList : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     SLink<Node> link;
     T obj;
   
     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss) ... ) {}
    };
 
   typedef typename SLink<Node>::template CircularAlgo<&Node::link> Algo;
 
   Allocator<Node> allocator;
 
   typename Algo::Top list;
 
  private: 
 
   void destroy(Node *node);
 
   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;
   
     return 0;
    }
 
  public:

   // constructors
   
   template <class ... SS>
   explicit CircularSList(SS && ... ss) : allocator( std::forward<SS>(ss) ... ) {}
   
   ~CircularSList() { erase(); }
   
   // props
   
   ulen operator + () const { return +allocator; }
   
   bool operator ! () const { return !allocator; }
   
   ulen getCount() const { return allocator.getCount(); }
   
   // content
   
   T * getBottom() const { return GetObject(list.bottom); }
   
   struct Cur
    {
     typename Algo::Cur cur;
     
     Cur() : cur(0) {}
     
     Cur(typename Algo::Cur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
    };
   
   Cur getStart() const { return list.start(); }
   
   struct CountCur
    {
     Node *node;
     ulen count;
     
     CountCur() : node(0),count(0) {}
     
     CountCur(Node *bottom,ulen count_) 
      : count(count_) 
      {
       if( bottom )
         node=Algo::Link(bottom).next;
       else
         node=0;
      }
     
     // object ptr
     
     ulen operator + () const { return count; }
     
     bool operator ! () const { return !count; }
     
     T * getPtr() const { return &node->obj; }
     
     T & operator * () const { return node->obj; }
 
     T * operator -> () const { return &node->obj; }
     
     // cursor
     
     void operator ++ () { node=Algo::Link(node).next; count--; }
     
     bool operator != (CountCur obj) const { return count!=obj.count; }
    };
   
   CountCur begin() const { return CountCur(list.bottom,getCount()); }
   
   CountCur end() const { return CountCur(); }
   
   // ins/del

   template <class ... SS>
   T * ins(SS && ... ss);
   
   template <class ... SS>
   T * insAfter(Cur pos,SS && ... ss); // +pos   
   
   bool del();
   
   ulen erase();
   
   T * rotate() { return GetObject(list.rotate()); } // return top element moved to bottom
   
   // apply
   
   template <class FuncInit>
   void apply(FuncInit func_init) { Algon::ApplyToRange(getStart(),func_init); }
   
   // swap/move objects
   
   void objSwap(CircularSList<T,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }
   
   explicit CircularSList(ToMoveCtor<CircularSList<T,Allocator> > obj)
    : allocator(ObjToMove(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
   
   CircularSList<T,Allocator> * objMove(Place<void> place)
    {
     return CtorMove(this,place); 
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = Allocator<Node>::Default_no_throw,
     Copy_no_throw = true
    };
 };

template <class T,template <class Node> class Allocator> 
void CircularSList<T,Allocator>::destroy(Node *node)
 {
  if( !node ) return;
  
  node=Replace_null(Algo::Link(node).next);
  
  while( node )
    {
     Node *next=Algo::Link(node).next;
     
     allocator.free(node);
     
     node=next;
    }
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * CircularSList<T,Allocator>::ins(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins(node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * CircularSList<T,Allocator>::insAfter(Cur pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
bool CircularSList<T,Allocator>::del()
 {
  return allocator.free(list.del());
 }

template <class T,template <class Node> class Allocator> 
ulen CircularSList<T,Allocator>::erase()
 {
  Node *node=list.bottom;
  
  list.init();
  
  ulen ret=getCount();
  
  destroy(node);
  
  return ret;
 }

/* class LinearDList<T,Allocator> */

template <class T,template <class Node> class Allocator> 
class LinearDList : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     DLink<Node> link;
     T obj;
   
     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss) ... ) {}
    };
 
   typedef typename DLink<Node>::template LinearAlgo<&Node::link> Algo;
 
   Allocator<Node> allocator;
 
   typename Algo::Top list;
 
  private: 
   
   void destroy(Node *node);
   
   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;
     
     return 0;
    }
   
  public:

   // constructors
   
   template <class ... SS>
   explicit LinearDList(SS && ... ss) : allocator( std::forward<SS>(ss) ... ) {}
   
   ~LinearDList() { erase(); }
   
   // props
   
   ulen operator + () const { return +allocator; }
   
   bool operator ! () const { return !allocator; }
   
   ulen getCount() const { return allocator.getCount(); }
 
   // content
   
   T * getTop() const { return GetObject(list.top); }
   
   struct Cur
    {
     typename Algo::Cur cur;
     
     Cur() : cur(0) {}
     
     Cur(typename Algo::Cur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
     
     void operator -- () { --cur; }
    };
   
   Cur getStart() const { return list.start(); }
   
   struct CountCur
    {
     typename Algo::Cur cur;
     ulen count;
     
     CountCur() : cur(0),count(0) {}
     
     CountCur(typename Algo::Cur cur_,ulen count_) : cur(cur_),count(count_) {}
     
     // object ptr
     
     ulen operator + () const { return count; }
     
     bool operator ! () const { return !count; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; count--; }
     
     bool operator != (CountCur obj) const { return count!=obj.count; }
    };
   
   CountCur begin() const { return CountCur(list.start(),getCount()); }
   
   CountCur end() const { return CountCur(); }
   
   // ins/del

   template <class ... SS>
   T * ins(SS && ... ss);
   
   template <class ... SS>
   T * insBefore(Cur pos,SS && ... ss); // +pos   
   
   template <class ... SS>
   T * insAfter(Cur pos,SS && ... ss); // +pos   
   
   bool del();
   
   void delAndMove(Cur &pos); // +pos
   
   ulen erase();
   
   // apply
   
   template <class FuncInit>
   void apply(FuncInit func_init) { Algon::ApplyToRange(getStart(),func_init); }
   
   // swap/move objects
   
   void objSwap(LinearDList<T,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }
   
   explicit LinearDList(ToMoveCtor<LinearDList<T,Allocator> > obj)
    : allocator(ObjToMove(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
   
   LinearDList<T,Allocator> * objMove(Place<void> place)
    {
     return CtorMove(this,place); 
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = Allocator<Node>::Default_no_throw,
     Copy_no_throw = true
    };
 };

template <class T,template <class Node> class Allocator> 
void LinearDList<T,Allocator>::destroy(Node *node)
 {
  while( node )
    {
     Node *next=Algo::Link(node).next;
     
     allocator.free(node);
     
     node=next;
    }
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearDList<T,Allocator>::ins(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins(node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearDList<T,Allocator>::insBefore(Cur pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_before(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearDList<T,Allocator>::insAfter(Cur pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
bool LinearDList<T,Allocator>::del()
 {
  return allocator.free(list.del());
 }

template <class T,template <class Node> class Allocator> 
void LinearDList<T,Allocator>::delAndMove(Cur &pos)
 {
  allocator.free(list.del_and_move(pos.cur));
 }

template <class T,template <class Node> class Allocator> 
ulen LinearDList<T,Allocator>::erase()
 {
  Node *node=list.top;
  
  list.init();
  
  ulen ret=getCount();
  
  destroy(node);
  
  return ret;
 }

/* class LinearDList2<T,Allocator> */

template <class T,template <class Node> class Allocator> 
class LinearDList2 : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     DLink<Node> link;
     T obj;
   
     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss) ... ) {}
    };
 
   typedef typename DLink<Node>::template LinearAlgo<&Node::link> Algo;
 
   Allocator<Node> allocator;
 
   typename Algo::FirstLast list;
 
  private: 
   
   void destroy(Node *node);
   
   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;
     
     return 0;
    }
   
  public:

   // constructors
   
   template <class ... SS>
   explicit LinearDList2(SS && ... ss) : allocator( std::forward<SS>(ss) ... ) {}
   
   ~LinearDList2() { erase(); }
   
   // props
   
   ulen operator + () const { return +allocator; }
   
   bool operator ! () const { return !allocator; }
   
   ulen getCount() const { return allocator.getCount(); }
 
   // content
   
   T * getFirst() const { return GetObject(list.first); }
   
   T * getLast() const { return GetObject(list.last); }
   
   struct Cur
    {
     typename Algo::Cur cur;
     
     Cur() : cur(0) {}
     
     Cur(typename Algo::Cur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
     
     void operator -- () { --cur; }
    };
   
   Cur getStart() const { return list.start(); }
   
   struct RevCur
    {
     typename Algo::RevCur cur;
     
     RevCur() : cur(0) {}
     
     RevCur(typename Algo::RevCur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
     
     void operator -- () { --cur; }
    };
   
   RevCur getStartReverse() { return list.start_rev(); }
   
   struct CountCur
    {
     typename Algo::Cur cur;
     ulen count;
     
     CountCur() : cur(0),count(0) {}
     
     CountCur(typename Algo::Cur cur_,ulen count_) : cur(cur_),count(count_) {}
     
     // object ptr
     
     ulen operator + () const { return count; }
     
     bool operator ! () const { return !count; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; count--; }
     
     bool operator != (CountCur obj) const { return count!=obj.count; }
    };
   
   CountCur begin() const { return CountCur(list.start(),getCount()); }
   
   CountCur end() const { return CountCur(); }
   
   struct RevCountCur
    {
     typename Algo::RevCur cur;
     ulen count;
     
     RevCountCur() : cur(0),count(0) {}
     
     RevCountCur(typename Algo::RevCur cur_,ulen count_) : cur(cur_),count(count_) {}
     
     // object ptr
     
     ulen operator + () const { return count; }
     
     bool operator ! () const { return !count; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; count--; }
     
     bool operator != (RevCountCur obj) const { return count!=obj.count; }
    };
   
   RevCountCur rbegin() const { return RevCountCur(list.start_rev(),getCount()); }
   
   RevCountCur rend() const { return RevCountCur(); }
   
   struct ReverseAdapter
    {
     RevCountCur cur;
     
     ReverseAdapter(RevCountCur cur_) : cur(cur_) {}
     
     RevCountCur begin() const { return cur; }
     
     RevCountCur end() const { return RevCountCur(); }
    };
   
   ReverseAdapter reverse() const { return rbegin(); }
   
   // ins/del

   template <class ... SS>
   T * insFirst(SS && ... ss);
   
   template <class ... SS>
   T * insLast(SS && ... ss);
   
   template <class ... SS>
   T * insBefore(Cur pos,SS && ... ss); // +pos   
   
   template <class ... SS>
   T * insBefore(RevCur pos,SS && ... ss); // +pos   
   
   template <class ... SS>
   T * insAfter(Cur pos,SS && ... ss); // +pos   
   
   template <class ... SS>
   T * insAfter(RevCur pos,SS && ... ss); // +pos   
   
   bool delFirst();
   
   bool delLast();
   
   void delAndMove(Cur &pos); // +pos
   
   void delAndMove(RevCur &pos); // +pos
   
   ulen erase();
   
   // apply
   
   template <class FuncInit>
   void apply(FuncInit func_init) { Algon::ApplyToRange(getStart(),func_init); }
   
   template <class FuncInit>
   void applyReverse(FuncInit func_init) { Algon::ApplyToRange(getStartReverse(),func_init); }
   
   // swap/move objects
   
   void objSwap(LinearDList2<T,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }
   
   explicit LinearDList2(ToMoveCtor<LinearDList2<T,Allocator> > obj)
    : allocator(ObjToMove(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
   
   LinearDList2<T,Allocator> * objMove(Place<void> place)
    {
     return CtorMove(this,place); 
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = Allocator<Node>::Default_no_throw,
     Copy_no_throw = true
    };
 };

template <class T,template <class Node> class Allocator> 
void LinearDList2<T,Allocator>::destroy(Node *node)
 {
  while( node )
    {
     Node *next=Algo::Link(node).next;
     
     allocator.free(node);
     
     node=next;
    }
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearDList2<T,Allocator>::insFirst(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_first(node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearDList2<T,Allocator>::insLast(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_last(node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearDList2<T,Allocator>::insBefore(Cur pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_before(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearDList2<T,Allocator>::insBefore(RevCur pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_before(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearDList2<T,Allocator>::insAfter(Cur pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * LinearDList2<T,Allocator>::insAfter(RevCur pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
bool LinearDList2<T,Allocator>::delFirst()
 {
  return allocator.free(list.del_first());
 }

template <class T,template <class Node> class Allocator> 
bool LinearDList2<T,Allocator>::delLast()
 {
  return allocator.free(list.del_last());
 }

template <class T,template <class Node> class Allocator> 
void LinearDList2<T,Allocator>::delAndMove(Cur &pos)
 {
  allocator.free(list.del_and_move(pos.cur));
 }

template <class T,template <class Node> class Allocator> 
void LinearDList2<T,Allocator>::delAndMove(RevCur &pos)
 {
  allocator.free(list.del_and_move(pos.cur));
 }

template <class T,template <class Node> class Allocator> 
ulen LinearDList2<T,Allocator>::erase()
 {
  Node *node=list.first;
  
  list.init();
  
  ulen ret=getCount();
  
  destroy(node);
  
  return ret;
 }

/* class CircularDList<T,Allocator> */

template <class T,template <class Node> class Allocator> 
class CircularDList : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     DLink<Node> link;
     T obj;
 
     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss) ... ) {}
    };

   typedef typename DLink<Node>::template CircularAlgo<&Node::link> Algo;

   Allocator<Node> allocator;

   typename Algo::Top list;

  private: 
 
   void destroy(Node *node);
 
   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;
   
     return 0;
    }
 
  public:

   // constructors
   
   template <class ... SS>
   explicit CircularDList(SS && ... ss) : allocator( std::forward<SS>(ss) ... ) {}
   
   ~CircularDList() { erase(); }
   
   // props
   
   ulen operator + () const { return +allocator; }
   
   bool operator ! () const { return !allocator; }
   
   ulen getCount() const { return allocator.getCount(); }
 
   // content
   
   T * getTop() const { return GetObject(list.top); }
   
   struct Cur
    {
     typename Algo::Cur cur;
     
     Cur() : cur(0) {}
     
     Cur(typename Algo::Cur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
     
     void operator -- () { --cur; }
    };
   
   Cur getStart() const { return list.start(); }
   
   struct RevCur
    {
     typename Algo::RevCur cur;
     
     RevCur() : cur(0) {}
     
     RevCur(typename Algo::RevCur cur_) : cur(cur_) {}
     
     // object ptr
     
     void * operator + () const { return +cur; }
     
     bool operator ! () const { return !cur; }
     
     T * getPtr() const { return &cur->obj; }
     
     T & operator * () const { return cur->obj; }
 
     T * operator -> () const { return &cur->obj; }
     
     // cursor
     
     void operator ++ () { ++cur; }
     
     void operator -- () { --cur; }
    };
   
   RevCur getStartReverse() { return list.start_rev(); }
   
   struct CountCur
    {
     Node *node;
     ulen count;
     
     CountCur() : node(0),count(0) {}
     
     CountCur(Node *node_,ulen count_) : node(node_),count(count_) {}
     
     // object ptr
     
     ulen operator + () const { return count; }
     
     bool operator ! () const { return !count; }
     
     T * getPtr() const { return &node->obj; }
     
     T & operator * () const { return node->obj; }
 
     T * operator -> () const { return &node->obj; }
     
     // cursor
     
     void operator ++ () { node=Algo::Link(node).next; count--; }
     
     bool operator != (CountCur obj) const { return count!=obj.count; }
    };
   
   CountCur begin() const { return CountCur(list.top,getCount()); }
   
   CountCur end() const { return CountCur(); }
   
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
     
     T * getPtr() const { return &node->obj; }
     
     T & operator * () const { return node->obj; }
 
     T * operator -> () const { return &node->obj; }
     
     // cursor
     
     void operator ++ () { node=Algo::Link(node).prev; count--; }
     
     bool operator != (RevCountCur obj) const { return count!=obj.count; }
    };
   
   RevCountCur rbegin() const { return RevCountCur(list.top,getCount()); }
   
   RevCountCur rend() const { return RevCountCur(); }
   
   struct ReverseAdapter
    {
     RevCountCur cur;
     
     ReverseAdapter(RevCountCur cur_) : cur(cur_) {}
     
     RevCountCur begin() const { return cur; }
     
     RevCountCur end() const { return RevCountCur(); }
    };
   
   ReverseAdapter reverse() const { return rbegin(); }
   
   // ins/del

   template <class ... SS>
   T * insFirst(SS && ... ss);
   
   template <class ... SS>
   T * insLast(SS && ... ss);
   
   template <class ... SS>
   T * insBefore(Cur pos,SS && ... ss); // +pos   
   
   template <class ... SS>
   T * insBefore(RevCur &pos,SS && ... ss); // +pos   
   
   template <class ... SS>
   T * insAfter(Cur &pos,SS && ... ss); // +pos   
   
   template <class ... SS>
   T * insAfter(RevCur pos,SS && ... ss); // +pos   
   
   bool delFirst();
   
   bool delLast();
   
   void delAndMove(Cur &pos); // +pos
   
   void delAndMove(RevCur &pos); // +pos
   
   ulen erase();
   
   T * rotateForward() { return GetObject(list.rotate_forward()); } // return top element moved to bottom
   
   T * rotateBackward() { return GetObject(list.rotate_backward()); } // return bottom element moved to top
   
   // apply
   
   template <class FuncInit>
   void apply(FuncInit func_init) { Algon::ApplyToRange(getStart(),func_init); }
   
   template <class FuncInit>
   void applyReverse(FuncInit func_init) { Algon::ApplyToRange(getStartReverse(),func_init); }
   
   // swap/move objects
   
   void objSwap(CircularDList<T,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }
   
   explicit CircularDList(ToMoveCtor<CircularDList<T,Allocator> > obj)
    : allocator(ObjToMove(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
   
   CircularDList<T,Allocator> * objMove(Place<void> place)
    {
     return CtorMove(this,place); 
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = Allocator<Node>::Default_no_throw,
     Copy_no_throw = true
    };
 };

template <class T,template <class Node> class Allocator> 
void CircularDList<T,Allocator>::destroy(Node *node)
 {
  if( !node ) return;
  
  node=Replace_null(Algo::Link(node).next);
  
  while( node )
    {
     Node *next=Algo::Link(node).next;
     
     allocator.free(node);
     
     node=next;
    }
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * CircularDList<T,Allocator>::insFirst(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_first(node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * CircularDList<T,Allocator>::insLast(SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_last(node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * CircularDList<T,Allocator>::insBefore(Cur pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_before(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * CircularDList<T,Allocator>::insBefore(RevCur &pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_before(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * CircularDList<T,Allocator>::insAfter(Cur &pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
template <class ... SS>
T * CircularDList<T,Allocator>::insAfter(RevCur pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_after(pos.cur,node);
  
  return &node->obj;
 }

template <class T,template <class Node> class Allocator> 
bool CircularDList<T,Allocator>::delFirst()
 {
  return allocator.free(list.del_first());
 }

template <class T,template <class Node> class Allocator> 
bool CircularDList<T,Allocator>::delLast()
 {
  return allocator.free(list.del_last());
 }

template <class T,template <class Node> class Allocator> 
void CircularDList<T,Allocator>::delAndMove(Cur &pos)
 {
  allocator.free(list.del_and_move(pos.cur));
 }

template <class T,template <class Node> class Allocator> 
void CircularDList<T,Allocator>::delAndMove(RevCur &pos)
 {
  allocator.free(list.del_and_move(pos.cur));
 }

template <class T,template <class Node> class Allocator> 
ulen CircularDList<T,Allocator>::erase()
 {
  Node *node=list.top;
  
  list.init();
  
  ulen ret=getCount();
  
  destroy(node);
  
  return ret;
 }

} // namespace CCore
 
#endif
 


