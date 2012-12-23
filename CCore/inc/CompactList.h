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
   
   void objSwap(CompactList<T> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }
   
   explicit CompactList(ToMoveCtor<CompactList<T> > obj)
    : allocator(ObjToMove(obj->allocator)),
      list(Replace_null(obj->list))
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
template <class ... SS>
T * CompactList<T>::insBefore(Cur pos,SS && ... ss)
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );
  
  list.ins_before(pos.cur,node);
  
  return &node->obj;
 }

template <class T> 
template <class ... SS>
T * CompactList<T>::insAfter(Cur pos,SS && ... ss)
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
void CompactList<T>::delAndMove(Cur &pos)
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

} // namespace CCore
 
#endif
 

