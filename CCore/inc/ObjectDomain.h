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
#include <CCore/inc/NewDelete.h>
 
namespace CCore {

/* classes */

class ObjectDomain;

template <class T> class DeleteObjNode;

template <class T> class ExtDelObjPtr;

template <class T> class IntDelObjPtr;

struct ProbeSet_keepAlive;

template <class T> struct Has_keepAlive;

template <class T,bool has_keepAlive=Has_keepAlive<T>::Ret> struct KeepAliveAdapters;

struct ProbeSet_breakWeak;

template <class T> struct Has_breakWeak;

template <class T,bool has_breakWeak=Has_breakWeak<T>::Ret> struct BreakWeakAdapters;

/* class ObjectDomain */

class ObjectDomain : NoCopy
 {
  public:
  
   template <class T> class ExtPtr;
  
   template <class T> class IntPtr;
   
   template <class T> class WeakPtr;
   
   template <class T> class OwnPtr;
   
   class Keeper
    {
      ObjectDomain *domain;
      
     private: 
     
      friend class ObjectDomain; 
      
      Keeper(ObjectDomain *domain_) : domain(domain_) {}
      
     public:

      template <class T>
      void operator () (IntPtr<T> int_ptr);
      
      template <class T>
      void operator () (IntDelObjPtr<T> del_ptr);
    };
   
   class Breaker
    {
      ulen preserved;
      
     private:
      
      friend class ObjectDomain;
      
      Breaker(ulen preserved_) : preserved(preserved_) {}
      
     public:
      
      template <class T>
      void operator () (WeakPtr<T> weak_ptr);
    };
   
  private:
   
   struct AllocInit
    {
     ObjectDomain *domain;
     
     AllocInit(ObjectDomain *domain_) : domain(domain_) {}
     
     typedef AllocInit AllocType;
     
     void * alloc(ulen len) { return domain->alloc(len); }
     
     void free(void *mem,ulen len) { domain->free(mem,len); }
    };
  
   struct ObjBase : NoCopy
    {
     ulen index;
     ulen ref_count;
      
     explicit ObjBase(ulen ref_count_) : ref_count(ref_count_) {}
      
     ~ObjBase() {}
     
     virtual void destroy(ObjectDomain *domain)=0;
      
     virtual void keepAlive(Keeper keeper)=0;
     
     virtual void breakWeak(Breaker breaker)=0;
     
     void incRef() { ++ref_count; }
     
     void decRef() { --ref_count; }
    };
   
   template <class T>
   struct ObjNode : ObjBase
    {
     T obj;
     
     template <class ... SS>
     ObjNode(ObjectDomain *domain,ulen ref_count,SS && ... ss) 
      : ObjBase(ref_count),
        obj( std::forward<SS>(ss)... ) 
      {
       domain->add(this);
      }
     
     ~ObjNode() {}
     
     virtual void destroy(ObjectDomain *domain) 
      {
       Delete<ObjNode<T>,AllocInit>(domain,this);
      }
     
     virtual void keepAlive(Keeper keeper) { KeepAliveAdapters<T>::KeepAlive(obj,keeper); }
     
     virtual void breakWeak(Breaker breaker) { BreakWeakAdapters<T>::BreakWeak(obj,breaker); }
     
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
   bool cleanup_flag;
   bool addlock_flag;
   
   // collect state
   
   ulen preserved;
   
  private:
   
   void * alloc(ulen len);
   
   void free(void *mem,ulen len);
   
   virtual void * try_alloc(ulen len);
  
   virtual void free(void *mem);
   
  private: 
  
   void add(ObjBase *obj);
   
   void markAlive(ObjBase *obj);
   
   void swap(ulen index1,ulen index2);
   
  protected:
   
   void cleanup(); // must be called in the destructor of a derived class
  
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
   friend class WeakPtr<T>;
   
  public:
   
   // constructors
  
   ExtPtr() : node(0) {}
   
   explicit ExtPtr(NothingType) : node(0) {}
   
   ExtPtr(const IntPtr<T> &obj) 
    : node(obj.node) 
    {
     if( node ) node->incRef();
    }
   
   ExtPtr(const WeakPtr<T> &obj) 
    : node(obj.node) 
    {
     if( node ) node->incRef();
    }
   
   template <class ... SS>
   explicit ExtPtr(ObjectDomain *domain,SS && ... ss)
    {
     node=New<ObjNode<T>,AllocInit>(domain, domain,1, std::forward<SS>(ss)... );
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
   
   ulen getExtRefs() const { return node->ref_count; }
   
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
   friend class WeakPtr<T>;
  
  public:
  
   // constructors
 
   IntPtr() : node(0) {}
  
   explicit IntPtr(NothingType) : node(0) {}
   
   IntPtr(const ExtPtr<T> &obj) : node(obj.node) {}
  
   IntPtr(const WeakPtr<T> &obj) : node(obj.node) {}
   
   template <class ... SS>
   explicit IntPtr(ObjectDomain *domain,SS && ... ss)
    {
     node=New<ObjNode<T>,AllocInit>(domain, domain,1, std::forward<SS>(ss)... );
    }
  
   void nullify() { node=0; }
   
   // object ptr
   
   void * operator + () const { return node; }
   
   bool operator ! () const { return !node; }
  
   T * getPtr() const { return node->getPtr(); }
   
   T & operator * () const { return *node->getPtr(); }
   
   T * operator -> () const { return node->getPtr(); }
   
   ulen getExtRefs() const { return node->ref_count; }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

/* class ObjectDomain<T>::WeakPtr */

template <class T> 
class ObjectDomain::WeakPtr // default copying
 {
   ObjNode<T> *node;
   
   friend class Breaker;
   friend class ExtPtr<T>;
   friend class IntPtr<T>;
   
  private: 
  
   void breakWeak(ulen preserved)
    {
     if( node )
       {
        if( node->index>=preserved )
          {
           node=0;
          }
       }
    }
   
  public:
  
   // constructors
 
   WeakPtr() : node(0) {}
  
   explicit WeakPtr(NothingType) : node(0) {}
   
   WeakPtr(const ExtPtr<T> &obj) : node(obj.node) {}
  
   WeakPtr(const IntPtr<T> &obj) : node(obj.node) {}
   
   template <class ... SS>
   explicit WeakPtr(ObjectDomain *domain,SS && ... ss)
    {
     node=New<ObjNode<T>,AllocInit>(domain, domain,1, std::forward<SS>(ss)... );
    }
  
   void nullify() { node=0; }
   
   // object ptr
   
   void * operator + () const { return node; }
   
   bool operator ! () const { return !node; }
  
   T * getPtr() const { return node->getPtr(); }
   
   T & operator * () const { return *node->getPtr(); }
   
   T * operator -> () const { return node->getPtr(); }
   
   ulen getExtRefs() const { return node->ref_count; }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

/* class ObjectDomain::OwnPtr<T> */

template <class T> 
class ObjectDomain::OwnPtr : NoCopy
 {
   struct Node : NoCopy
    {
     ObjectDomain *domain;
     T obj;
     
     template <class ... SS>
     explicit Node(ObjectDomain *domain_,SS && ... ss) : domain(domain_),obj( std::forward<SS>(ss)... ) {}
     
     ~Node() {}
     
     T * getPtr() { return &obj; }
    };
   
   Node *node;
   
  private:
   
   static void Destroy(Node *node)
    {
     if( node )
       { 
        ObjectDomain *domain=node->domain;

        Delete<Node,AllocInit>(domain,node);
       }
    }
 
  public:
 
   template <class ... SS>
   explicit OwnPtr(ObjectDomain *domain,SS && ... ss)
    {
     node=New<Node,AllocInit>(domain, domain, std::forward<SS>(ss)... ); 
    }
   
   ~OwnPtr()
    {
     Destroy(node);
    }
   
   // object ptr
   
   void * operator + () const { return node; }
   
   bool operator ! () const { return !node; }

   T * getPtr() const { return node->getPtr(); }
   
   T & operator * () const { return *node->getPtr(); }
   
   T * operator -> () const { return node->getPtr(); }
   
   // destroy
   
   void destroy()
    {
     Destroy(Replace_null(node));
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

/* types */

template <class T>
using ExtObjPtr = ObjectDomain::ExtPtr<T> ;

template <class T>
using IntObjPtr = ObjectDomain::IntPtr<T> ;

template <class T>
using WeakObjPtr = ObjectDomain::WeakPtr<T> ;

/* class DeleteObjNode<T> */

template <class T>
class DeleteObjNode : NoCopy
 {
   ObjectDomain::OwnPtr<T> ptr;
   
  public:

   template <class ... SS>
   explicit DeleteObjNode(ObjectDomain *domain,SS && ... ss) 
    : ptr(domain, std::forward<SS>(ss)... )
    {
    }
   
   ~DeleteObjNode()
    {
    }
   
   void destroy()
    {
     ptr.destroy();
    }
   
   void * hasPtr() const { return +ptr; }
   
   T * getPtr() const { return ptr.getPtr(); }
   
   template <class Keeper>
   void keepAlive(Keeper keeper)
    {
     if( +ptr ) KeepAliveAdapters<T>::KeepAlive(*ptr,keeper);
    }
   
   template <class Breaker>
   void breakWeak(Breaker breaker)
    {
     if( +ptr ) BreakWeakAdapters<T>::BreakWeak(*ptr,breaker);
    }
 };

/* class ExtDelObjPtr<T> */

template <class T>
class ExtDelObjPtr
 {
   ExtObjPtr<DeleteObjNode<T> > ptr;
   
   friend class IntDelObjPtr<T>;
   
  public: 
   
   // constructors
   
   ExtDelObjPtr() {}
   
   ExtDelObjPtr(NothingType) {}
   
   ExtDelObjPtr(const IntDelObjPtr<T> &obj) : ptr(obj.ptr) {}
   
   template <class ... SS>
   ExtDelObjPtr(ObjectDomain *domain,SS && ... ss) : ptr(domain, domain, std::forward<SS>(ss)... ) {}
   
   ~ExtDelObjPtr() {}
   
   void nullify() { ptr.nullify(); }
   
   // object ptr
   
   void * operator + () const { return +ptr; }
   
   bool operator ! () const { return !ptr; }
  
   T * getPtr() const { return ptr->getPtr(); }
   
   T & operator * () const { return *getPtr(); }
   
   T * operator -> () const { return getPtr(); }
   
   // destroy
   
   bool destroy()
    {
     if( +ptr ) 
       {
        if( ptr.getExtRefs()>1 ) return false;
        
        ptr->destroy();
        
        ptr.nullify();
       }
     
     return true;
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

/* class IntDelObjPtr<T> */

template <class T>
class IntDelObjPtr
 {
   IntObjPtr<DeleteObjNode<T> > ptr;
   
   friend class ExtDelObjPtr<T>;
   friend class ObjectDomain::Keeper;
   
  private: 
   
   IntObjPtr<DeleteObjNode<T> > getInnerPtr() 
    { 
     if( +ptr && !ptr->hasPtr() ) ptr.nullify();
     
     return ptr; 
    }
   
  public: 
   
   // constructors
   
   IntDelObjPtr() {}
   
   IntDelObjPtr(NothingType) {}
   
   IntDelObjPtr(const ExtDelObjPtr<T> &obj) : ptr(obj.ptr) {}
   
   template <class ... SS>
   IntDelObjPtr(ObjectDomain *domain,SS && ... ss) : ptr(domain, domain, std::forward<SS>(ss)... ) {}
   
   void nullify() { ptr.nullify(); }
   
   // object ptr
   
   void * operator + () const { return +ptr && ptr->hasPtr() ; }
   
   bool operator ! () const { return !ptr || !ptr->hasPtr() ; }
  
   T * getPtr() const { return ptr->getPtr(); }
   
   T & operator * () const { return *getPtr(); }
   
   T * operator -> () const { return getPtr(); }
   
   // destroy
   
   bool destroy()
    {
     if( +ptr ) 
       {
        if( ptr.getExtRefs() ) return false;
       
        ptr->destroy();
        
        ptr.nullify();
       }
     
     return true;
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

/* class ObjectDomain::Keeper */

template <class T>
void ObjectDomain::Keeper::operator () (IntPtr<T> int_ptr)
 {
  domain->markAlive(int_ptr.node);
 }

template <class T>
void ObjectDomain::Keeper::operator () (IntDelObjPtr<T> del_ptr)
 {
  (*this)(del_ptr.getInnerPtr());
 }

/* class ObjectDomain::Breaker */

template <class T>
void ObjectDomain::Breaker::operator () (WeakPtr<T> weak_ptr)
 {
  weak_ptr.breakWeak(preserved);
 }

/* struct ProbeSet_keepAlive */

struct ProbeSet_keepAlive
 {
  template <class T,void (T::*M)(ObjectDomain::Keeper)> struct Host;
 
  template <class T>
  static constexpr bool Probe(...) { return false; } 
 
  template <class T>
  static constexpr bool Probe(Host<T,&T::keepAlive> *) { return true; }
 };

/* struct Has_keepAlive<T> */ 

template <class T> 
struct Has_keepAlive : Meta::Has<T,ProbeSet_keepAlive> {};

/* struct KeepAliveAdapters<T,bool has_keepAlive> */

template <class T>
struct KeepAliveAdapters<T,true>
 {
  static void KeepAlive(T &obj,ObjectDomain::Keeper keeper) { obj.keepAlive(keeper); }
 };

template <class T>
struct KeepAliveAdapters<T,false>
 {
  static void KeepAlive(T &,ObjectDomain::Keeper) {}
 };

/* struct ProbeSet_breakWeak */

struct ProbeSet_breakWeak
 {
  template <class T,void (T::*M)(ObjectDomain::Breaker)> struct Host;
 
  template <class T>
  static constexpr bool Probe(...) { return false; } 
 
  template <class T>
  static constexpr bool Probe(Host<T,&T::breakWeak> *) { return true; }
 };

/* struct Has_breakWeak<T> */ 

template <class T> 
struct Has_breakWeak : Meta::Has<T,ProbeSet_breakWeak> {};

/* struct BreakWeakAdapters<T,bool has_breakWeak> */

template <class T> 
struct BreakWeakAdapters<T,true>
 {
  static void BreakWeak(T &obj,ObjectDomain::Breaker breaker) { obj.breakWeak(breaker); }
 };

template <class T> 
struct BreakWeakAdapters<T,false>
 {
  static void BreakWeak(T &,ObjectDomain::Breaker) {}
 };

} // namespace CCore
 
#endif
 

