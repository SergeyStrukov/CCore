/* DDL2Tools.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.07
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ddl2_DDL2Tools_h
#define CCore_inc_ddl2_DDL2Tools_h

#include <CCore/inc/Array.h>

#include <CCore/inc/ddl2/DDL2Token.h>

namespace CCore {
namespace DDL2 {

/* classes */

class AndFlag;

struct PosName;

template <class T> struct ListPrevPtr;

template <class T> struct ListNextPtr;

template <class T> struct BaseList;

template <class T> struct CountList;

template <class T> struct BegList;

template <class T> struct ForwardList;

template <class T> struct NoLast;

template <class T> class Enlist;

/* class AndFlag */

class AndFlag
 {
   bool flag;
   
  public: 
  
   AndFlag() : flag(true) {}
  
   operator bool() const { return flag; }
  
   void operator += (bool ok) 
    {
     if( !ok ) flag=false;
    }
 };

/* struct PosName */

struct PosName
 {
  FileId *file_id;
  TextPos pos;
  StrLen str;
  
  void init(FileId *file_id_,const Token &token)
   {
    file_id=file_id_;
    pos=token.pos;
    str=token.str;
   }
  
  void init_qname(FileId *file_id_,const Token &token)
   {
    file_id=file_id_;
    pos=token.pos;
    str=token.str.part(1);
   }
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#; #.q;",PrintPos(file_id,pos),str);
   }
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
struct BaseList : NoCopy
 {
  T *list;
  
  void init()
   {
    list=0;
   }
  
  void init(T *node)
   {
    node->prev=0;
    
    list=node;
   }
  
  void add(T *node)
   {
    node->prev=list;
    
    list=node;
   }
  
  void copy(BaseList<T> &obj)
   {
    list=obj.list;
   }
 };

template <class T> 
ListPrevPtr<T> begin(const BaseList<T> &list) { return list.list; }

template <class T> 
ListPrevPtr<T> end(const BaseList<T> &) { return 0; }

/* struct CountList<T> */

template <class T> 
struct CountList : NoCopy
 {
  T *list;
  ulen count;
  
  void init()
   {
    list=0;
    count=0;
   }
  
  void init(T *node)
   {
    node->prev=0;
    
    list=node;
    
    count=1;
   }
  
  void add(T *node)
   {
    node->prev=list;
    
    list=node;
    
    count++;
   }
  
  void copy(CountList<T> &obj)
   {
    list=obj.list;
    count=obj.count;
   }
 };

template <class T> 
ListPrevPtr<T> begin(const CountList<T> &list) { return list.list; }

template <class T> 
ListPrevPtr<T> end(const CountList<T> &) { return 0; }

/* struct BegList<T> */

template <class T> 
struct BegList : NoCopy
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
  
  void init(T *node)
   {
    node->prev=0;
    
    beg=node;
    list=node;
    count=1;
   }
  
  void add(T *node)
   {
    if( !beg ) beg=node;
    
    node->prev=list;
    
    list=node;
    
    count++;
   }
  
  void join(BegList<T> &tail)
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
struct ForwardList : NoCopy
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
  
  void init(T *node)
   {
    node->next=0;
    
    beg=node;
    last=node;
    count=1;
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
 
  void copy(ForwardList<T> &obj)
   {
    beg=obj.beg;
    last=obj.last;
    count=obj.count;
   }
 };

template <class T> 
ListNextPtr<T> begin(const ForwardList<T> &list) { return list.beg; }

template <class T> 
ListNextPtr<T> end(const ForwardList<T> &) { return 0; }

/* struct NoLast<T> */

template <class T> 
struct NoLast : NoCopy
 {
  T *beg;
  T *last;
  
  explicit NoLast(const ForwardList<T> &list) : beg(list.beg),last(list.last) {}
 };

template <class T> 
ListNextPtr<T> begin(const NoLast<T> &list) { return list.beg; }

template <class T> 
ListNextPtr<T> end(const NoLast<T> &list) { return list.last; }

/* class Enlist<T> */

template <class T> 
class Enlist : NoCopy
 {
   T *root;
   T *last;
   
   Collector<T> col;
   
  private:
   
   void add(T *obj)
    {
     obj->next=0;
     
     last->next=obj;
     
     last=obj;
    }
   
   struct Add
    {
     Enlist<T> *obj;
     
     explicit Add(Enlist<T> *obj_) : obj(obj_) {}
     
     template <class ... SS>
     T * operator () (SS && ... ss)
      {
       T *ret=obj->col.append_fill( std::forward<SS>(ss)... );
       
       obj->add(ret);
       
       return ret;
      }
    };
   
  public:
 
   template <class Func,class ... SS>
   explicit Enlist(Func expand,SS && ... ss)
    {
     root=col.append_fill( std::forward<SS>(ss)... );
     
     root->next=0;
     
     last=root;
     
     for(T *ptr=root; ptr ;ptr=ptr->next)
       {
        expand(ptr,Add(this));
       }
    }
   
   ~Enlist() {}

   T * getRoot() const { return root; }
   
   ulen getCount() const { return col.getLen(); }
 };

template <class T> 
ListNextPtr<T> begin(const Enlist<T> &obj) { return obj.getRoot(); }

template <class T> 
ListNextPtr<T> end(const Enlist<T> &) { return 0; }

} // namespace DDL2
} // namespace CCore

#endif

