/* DDLTools.h */
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ddl_DDLTools_h
#define CCore_inc_ddl_DDLTools_h

#include <CCore/inc/ddl/DDLToken.h>

#include <CCore/inc/Swap.h>

namespace CCore {
namespace DDL {

/* forward */

struct Step;

/* consts */

const ulen ErrorMsgCap = 100 ;

/* classes */

class AndFlag;

struct PosName;

struct StepId;

template <class T> struct ListPrevPtr;

template <class T> struct ListNextPtr;

template <class T> struct BaseList;

template <class T> struct CountList;

template <class T> struct BegList;

template <class T> struct ForwardList;

template <class T> struct RingNode;

/* class AndFlag */

class AndFlag
 {
   bool flag;
   
  public: 
  
   AndFlag() : flag(true) {}
  
   operator bool() const { return flag; }
  
   void operator += (bool f) { flag = flag && f ; }
 };

/* struct PosName */

struct PosName
 {
  FileId *file_id;
  Token token;
  
  void init(FileId *file_id_,const Token &token_)
   {
    file_id=file_id_;
    token=token_;
   }
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#; #.;",PrintPos(file_id,token.pos),token.str);
   }
 };

/* struct StepId */

struct StepId
 {
  Step *step;
  ulen arg;
  
  // constructors
  
  StepId(Step *step_=0,ulen arg_=0) : step(step_),arg(arg_) {}
  
  // methods
  
  StepId arg1() const { return StepId(step,1); }
  StepId arg2() const { return StepId(step,2); }
  
  StepId argInd(ulen ind) const { return StepId(step,ind+1); }
 };

/* struct ListPrevPtr<T> */

template <class T> 
struct ListPrevPtr
 {
  T *ptr;
  
  ListPrevPtr(T *ptr_) : ptr(ptr_) {}
  
  T & operator * () const { return *ptr; }
  
  void operator ++ () { ptr=ptr->prev; }
  
  bool operator != (ListPrevPtr<T> end) const { return ptr!=end.ptr; }
 };

/* struct ListNextPtr<T> */

template <class T> 
struct ListNextPtr
 {
  T *ptr;
  
  ListNextPtr(T *ptr_) : ptr(ptr_) {}
  
  T & operator * () const { return *ptr; }
  
  void operator ++ () { ptr=ptr->next; }
  
  bool operator != (ListNextPtr<T> end) const { return ptr!=end.ptr; }
 };

/* struct BaseList<T> */

template <class T> 
struct BaseList
 {
  T *list;
  
  void init()
   {
    list=0;
   }
  
  void add(T *node)
   {
    node->prev=list;
    
    list=node;
   }
 };

template <class T> 
ListPrevPtr<T> begin(const BaseList<T> &list) { return list.list; }

template <class T> 
ListPrevPtr<T> end(const BaseList<T> &) { return 0; }

/* struct CountList<T> */

template <class T> 
struct CountList
 {
  T *list;
  ulen count;
  
  void init()
   {
    list=0;
    count=0;
   }
  
  void add(T *node)
   {
    node->prev=list;
    
    list=node;
    
    count++;
   }
 };

template <class T> 
ListPrevPtr<T> begin(const CountList<T> &list) { return list.list; }

template <class T> 
ListPrevPtr<T> end(const CountList<T> &) { return 0; }

/* struct BegList<T> */

template <class T> 
struct BegList
 {
  T *beg;
  T *list;
  ulen count;
  
  void init()
   {
    beg=0;
    list=0;
    count=0;
   }
  
  void add(T *node)
   {
    if( !beg ) beg=node;
    
    node->prev=list;
    
    list=node;
    
    count++;
   }
  
  void join(BegList<T> tail)
   {
    if( auto ptr=tail.beg )
      {
       if( !beg ) beg=ptr;
       
       ptr->prev=list;
       
       list=tail.list;
       
       count+=tail.count;
      }
   }
 };

template <class T> 
ListPrevPtr<T> begin(const BegList<T> &list) { return list.list; }

template <class T> 
ListPrevPtr<T> end(const BegList<T> &) { return 0; }

/* struct ForwardList<T> */

template <class T> 
struct ForwardList
 {
  T *beg;
  T *last;
  ulen count;
  
  void init()
   {
    beg=0;
    last=0;
    count=0;
   }
  
  void add(T *node)
   {
    if( last )
      {
       last->next=node;
      }
    else
      {
       beg=node;
      }
    
    last=node;
    node->next=0;
    
    count++;
   }
 };

template <class T> 
ListNextPtr<T> begin(const ForwardList<T> &list) { return list.beg; }

template <class T> 
ListNextPtr<T> end(const ForwardList<T> &) { return 0; }

/* struct RingNode<T> */

template <class T> 
struct RingNode
 { 
  RingNode<T> *next;
  T obj; 
  
  template <class ... SS>
  RingNode(SS && ... ss) 
   : obj( std::forward<SS>(ss)... )
   {
    next=this;
   }
 };

template <class T> 
RingNode<T> * RingJoin(RingNode<T> *a,RingNode<T> *b)
 {
  if( !a ) return b;
  
  if( b ) Swap(a->next,b->next);
  
  return a;
 }

} // namespace DDL
} // namespace CCore

#endif

