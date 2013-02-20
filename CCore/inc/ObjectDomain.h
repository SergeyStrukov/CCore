/* ObjectDomain.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.04
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

#ifndef CCore_inc_ObjectDomain_h
#define CCore_inc_ObjectDomain_h

#include <CCore/inc/Array.h>
 
namespace CCore {

/* classes */

class ObjectDomain;

/* class ObjectDomain */

class ObjectDomain : NoCopy
 {
  public:
  
   template <class T> class ExtPtr;
  
   template <class T> class IntPtr;
   
   class Keeper
    {
      ObjectDomain *domain;
      
     private: 
     
      friend class ObjectDomain; 
      
      Keeper(ObjectDomain *domain_) : domain(domain_) {}
      
     public:

      template <class T>
      void operator () (IntPtr<T> int_ptr);
    };
   
  private:
  
   struct ObjBase : NoCopy
    {
     ulen len;
     ulen index;
     ulen ref_count;
      
     ObjBase(ulen len_,ulen ref_count_) : len(len_),ref_count(ref_count_) {}
      
     ~ObjBase() {}
     
     virtual void destroy(ObjectDomain *domain)=0;
      
     virtual void keepAlive(Keeper)=0;
     
     void incRef() { ++ref_count; }
     
     void decRef() { --ref_count; }
     
     void * operator new(std::size_t len,ObjectDomain *domain) { return domain->alloc(len); }
     
     void operator delete(void *mem,ObjectDomain *domain) { domain->free(mem); }
    };
   
   template <class T>
   struct ObjNode : ObjBase
    {
     T obj;
     
     template <class ... SS>
     explicit ObjNode(ObjectDomain *domain,ulen len,ulen ref_count,SS && ... ss) 
      : ObjBase(len,ref_count),
        obj( std::forward<SS>(ss)... ) 
      {
       domain->add(this);
      }
     
     ~ObjNode() {}
     
     virtual void destroy(ObjectDomain *domain) 
      {  
       ObjNode<T> *obj=this;
       
       obj->~ObjNode();
       
       domain->free(obj);
      }
     
     virtual void keepAlive(Keeper keeper) { obj.keepAlive(keeper); }
     
     T * getPtr() { return &obj; }
    };
   
   struct ObjRec
    {
     ObjBase *obj;
     
     explicit ObjRec(ObjBase *obj_) : obj(obj_) {}
    };
   
  private: 
   
   DynArray<ObjRec> list;
   ulen total_len;
   ulen max_total_len;
   
   // collect state
   
   ulen preserved;
   
  private:
   
   virtual void * alloc(ulen len);
  
   virtual void free(void *mem);
   
   virtual bool enableAlloc(ulen len);
  
   void add(ObjBase *obj);
   
   void markAlive(ObjBase *obj);
   
   void swap(ulen index1,ulen index2);
  
  public:
  
   // constructors
  
   explicit ObjectDomain(ulen max_total_len);
   
   ~ObjectDomain();
   
   void collect();
   
   // props
   
   ulen getObjectCount() const { return list.getLen(); }
   
   ulen getTotalLen() const { return total_len; }
   
   ulen getMaxTotalLen() const { return max_total_len; }
   
   ulen getAvail() const { return max_total_len-total_len; }
 };

/* class ObjectDomain<T>::ExtPtr */

template <class T> 
class ObjectDomain::ExtPtr
 {
   ObjNode<T> *node;
   
   friend class IntPtr<T>;
   
  public:
   
   // constructors
  
   ExtPtr() : node(0) {}
   
   explicit ExtPtr(NothingType) : node(0) {}
   
   ExtPtr(const IntPtr<T> &obj) 
    : node(obj.node) 
    {
     if( node ) node->incRef();
    }
   
   template <class ... SS>
   explicit ExtPtr(ObjectDomain *domain,SS && ... ss)
    {
     ulen len=sizeof (ObjNode<T>);
     
     if( !domain->enableAlloc(len) ) GuardNoMem(len);
     
     node=new(domain) ObjNode<T>(domain,len,1, std::forward<SS>(ss)... );
    }
   
   ~ExtPtr() { if( node ) node->decRef(); }
   
   void nullify() 
    {  
     if( ObjNode<T> *temp=Replace_null(node) ) temp->decRef(); 
    }
   
   // copying
   
   ExtPtr(const ExtPtr<T> &obj) 
    : node(obj.node)
    {
     if( node ) node->incRef();
    }
   
   ExtPtr<T> & operator = (const ExtPtr<T> &obj)
    {
     ObjNode<T> *new_node=obj.node;
     ObjNode<T> *old_node=Replace(node,new_node);
     
     if( new_node ) new_node->incRef();
     if( old_node ) old_node->decRef();
     
     return *this;
    }
   
   // object ptr
   
   void * operator + () const { return node; }
   
   bool operator ! () const { return !node; }
  
   T * getPtr() const { return node->getPtr(); }
   
   T & operator * () const { return *node->getPtr(); }
   
   T * operator -> () const { return node->getPtr(); }
   
   // swap/move objects
   
   void objSwap(ExtPtr<T> &obj)
    {
     Swap(node,obj.node);
    }
   
   explicit ExtPtr(ToMoveCtor<ExtPtr<T> > obj)
    : node(Replace_null(obj.node))
    {
    } 
    
   ExtPtr<T> * objMove(Place<void> place)
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

/* class ObjectDomain<T>::IntPtr */

template <class T> 
class ObjectDomain::IntPtr // default copying
 {
   ObjNode<T> *node;
   
   friend class Keeper;
   friend class ExtPtr<T>;
  
  public:
  
   // constructors
 
   IntPtr() : node(0) {}
  
   explicit IntPtr(NothingType) : node(0) {}
   
   IntPtr(const ExtPtr<T> &obj) : node(obj.node) {}
  
   template <class ... SS>
   explicit IntPtr(ObjectDomain *domain,SS && ... ss)
    {
     ulen len=sizeof (ObjNode<T>);
    
     if( !domain->enableAlloc(len) ) GuardNoMem(len);
     
     node=new(domain) ObjNode<T>(domain,len,0, std::forward<SS>(ss)... );
    }
  
   void nullify() { node=0; }
   
   // object ptr
   
   void * operator + () const { return node; }
   
   bool operator ! () const { return !node; }
  
   T * getPtr() const { return node->getPtr(); }
   
   T & operator * () const { return *node->getPtr(); }
   
   T * operator -> () const { return node->getPtr(); }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

/* class ObjectDomain<T>::Keeper */

template <class T>
void ObjectDomain::Keeper::operator () (IntPtr<T> int_ptr)
 {
  domain->markAlive(int_ptr.node);
 }

/* types */

template <class T>
using ExtObjPtr = ObjectDomain::ExtPtr<T> ;

template <class T>
using IntObjPtr = ObjectDomain::IntPtr<T> ;

} // namespace CCore
 
#endif
 

