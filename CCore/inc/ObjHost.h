/* ObjHost.h */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ObjHost_h
#define CCore_inc_ObjHost_h

#include <CCore/inc/PlanInit.h>
#include <CCore/inc/Printf.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Task.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_ObjHost();

/* classes */

struct ObjKey;

class ObjBase;

class ObjHost;

struct ObjInfo;

template <class T> struct ObjInfo_if;

struct ObjInfo_obj;

template <class T> struct ObjInfo_obj_if;

class ObjHook;

class ObjMaster;

class ObjMaster_delete;

/* struct ObjKey */

struct ObjKey
 {
  uint32 hash;
  StrLen name;
  
  ObjKey() : hash(),name() {}
  
  explicit ObjKey(StrLen name);
  
  CmpResult objCmp(const ObjKey &obj) const
   {
    if( CmpResult ret=Cmp(hash,obj.hash) ) return ret;
    
    return StrCmp(name,obj.name);
   }
 };

/* class ObjBase */ 

class ObjBase : public MemBase_nocopy
 {
   AntiSem asem;
   RBTreeUpLink<ObjBase,ObjKey> link;
   Atomic hosted;
   
  private:
  
   friend class ObjHost;
   friend class ObjHook;
   
  public:
  
   ObjBase() : asem("ObjBase") {}
   
   virtual ~ObjBase() {}
   
   void wait_released() { asem.wait(); }
   
   bool wait_released(MSec timeout) { return asem.wait(timeout); }
   
   bool wait_released(TimeScope time_scope) { return asem.wait(time_scope); }
 };
 
/* class ObjHost */  

class ObjHost : NoCopy
 {
   Mutex mutex;
   
   typedef RBTreeUpLink<ObjBase,ObjKey>::Algo<&ObjBase::link> Algo;
   
   Algo::Root root;
   
  private:
  
   ObjBase * lock(StrLen name,bool do_throw=true);
   
   ObjBase * try_lock(StrLen name) { return lock(name,false); }
   
   friend class ObjHook;
   
   template <class Func>
   void apply(Func &func,ObjBase *obj)
    {
     if( obj )
       {
        func(obj);
        
        apply(func,Algo::Link(obj).lo);
        apply(func,Algo::Link(obj).hi);
       }
    }
   
   template <class FuncInit>
   void apply(FuncInit func_init) // locked operation
    {
     Mutex::Lock lock(mutex);
     
     FunctorTypeOf<FuncInit> func(func_init);
     
     apply(func,root.root);
    }
   
   template <bool Lock> struct ListLock;
   
   static StrLen Dup(StrLen name);
   
   static void Free(StrLen name);
   
   class SetHosted;
  
  public:
  
   explicit ObjHost(TextLabel name);
   
   ~ObjHost();
   
   void add(ObjBase &obj,StrLen name);
   
   void del(ObjBase &obj);
   
   static ObjHost & Default();
   
   template <class Info> class List;
 };

template <> 
struct ObjHost::ListLock<true>
 {
  static void Lock(ObjBase *obj) { obj->asem.inc(); }
 
  template <class Info>
  static void Unlock(PtrLen<Info> r) 
   {
    for(; +r ;++r) r->getObj()->asem.dec();
   }
 };
 
template <> 
struct ObjHost::ListLock<false>
 {
  static void Lock(ObjBase *) {}
 
  template <class Info>
  static void Unlock(PtrLen<Info>) {}
 };
 
/* class ObjHost::List<Info> */ 

template <class Info>
class ObjHost::List : NoCopy
 {
   ElementPool pool;
   DynArray<Info> infos;
   
  private: 
  
   void add(ObjBase *obj)
    {
     typename Info::Extra extra(obj);
     
     if( !extra ) return;
     
     StrLen name=Algo::Link(obj).key.name;
     
     infos.append_fill(obj,pool.dup(name),extra);
     
     ListLock<Info::Lock>::Lock(obj);
    }
    
  public:
  
   List() : pool(4_KByte),infos(DoReserve,100) {}
   
   ~List() 
    {
     ListLock<Info::Lock>::Unlock(Range(infos));
    }
   
   void build(ObjHost &host=Default())
    {
     List<Info> &list=*this;
  
     host.apply( [&] (ObjBase *obj) { list.add(obj); } );
    }
   
   const Info * getPtr() const { return infos.getPtr(); }
   
   ulen getLen() const { return infos.getLen(); }
 };
 
/* struct ObjInfo */  

struct ObjInfo
 {
  enum LockFlagType { Lock=false };
  
  typedef ObjBase * Extra;
  
  // data
  
  StrLen name;
  
  // constructors
  
  ObjInfo(ObjBase *,StrLen name_,Extra) : name(name_) {}
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#;",name);
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };
 
/* struct ObjInfo_if<T> */  

template <class T>
struct ObjInfo_if
 {
  enum LockFlagType { Lock=false };
  
  struct Extra
   {
    T *ptr;
    
    explicit Extra(ObjBase *obj) : ptr(dynamic_cast<T *>(obj)) {}
    
    bool operator ! () const { return !ptr; }
   };
  
  // data
 
  StrLen name;
  
  // constructors
  
  ObjInfo_if(ObjBase *,StrLen name_,Extra) : name(name_) {}
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#;",name);
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };
 
/* struct ObjInfo_obj */  

struct ObjInfo_obj
 {
  enum LockFlagType { Lock=true };
  
  typedef ObjBase * Extra;
  
  // data
  
  StrLen name;
  ObjBase *obj;
  
  // constructors
  
  ObjInfo_obj(ObjBase *obj_,StrLen name_,Extra) : name(name_),obj(obj_) {}
  
  // methods
  
  ObjBase * getObj() const { return obj; }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#;",name);
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };
 
/* struct ObjInfo_obj_if<T> */  

template <class T>
struct ObjInfo_obj_if
 {
  enum LockFlagType { Lock=true };
  
  struct Extra
   {
    ObjBase *obj;
    T *ptr;
    
    explicit Extra(ObjBase *obj_) : obj(obj_),ptr(dynamic_cast<T *>(obj_)) {}
    
    bool operator ! () const { return !ptr; }
   };
  
  // data
 
  StrLen name;
  Extra extra;
  
  // constructors
  
  ObjInfo_obj_if(ObjBase *,StrLen name_,Extra extra_) : name(name_),extra(extra_) {}
  
  // methods
  
  ObjBase * getObj() const { return extra.obj; }
  
  T * getPtr() const { return extra.ptr; }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#;",name);
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };
 
/* class ObjHook */ 
 
class ObjHook : NoCopy
 {
   ObjBase *obj;
   
  private:
  
   void lock(StrLen name,ObjHost &host=ObjHost::Default()) { obj=host.lock(name); }
 
   void try_lock(StrLen name,ObjHost &host=ObjHost::Default()) { obj=host.try_lock(name); }
   
   static void GuardObjCastFailed();

  public:
   
   //
   // assign/move/swap are not provided to prevent cyclyc dependencies
   //
   
   // constructors
  
   ObjHook(ObjHost &host,StrLen name) { lock(name,host); }
   
   explicit ObjHook(StrLen name) { lock(name); }
    
   ObjHook(JustTryType,ObjHost &host,StrLen name) { try_lock(name,host); }
   
   ObjHook(JustTryType,StrLen name) { try_lock(name); }
    
   ~ObjHook() { if( obj ) obj->asem.dec(); }
   
   // cast
   
   bool operator + () const { return obj; }
   
   bool operator ! () const { return !obj; }
    
   template <class T>
   T * cast() const { return dynamic_cast<T *>(obj); }
   
   template <class T>
   T * cast_guarded() const 
    { 
     T *ret=cast<T>();
     
     if( !ret ) GuardObjCastFailed();
     
     return ret;
    }
   
   template <class T>
   operator T * () const { return cast_guarded<T>(); }
   
   // copy objects
   
   ObjHook(const ObjHook &hook)
    : NoCopy() // warning supression
    {
     obj=hook.obj;
     
     if( obj ) obj->asem.inc();
    }
 };
 
/* class ObjMaster */ 

class ObjMaster : NoCopy
 {
   ObjHost &host;
   ObjBase &obj;
   
  public: 
  
   ObjMaster(ObjHost &host_,ObjBase &obj_,StrLen name) 
    : host(host_),
      obj(obj_)
    {
     host.add(obj,name);
    }
   
   ObjMaster(ObjBase &obj_,StrLen name) 
    : host(ObjHost::Default()),
      obj(obj_)
    {
     host.add(obj,name);
    }
   
   ~ObjMaster() 
    { 
     host.del(obj); 
     
     obj.wait_released();
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };
 
/* class ObjMaster_delete */ 

class ObjMaster_delete : NoCopy
 {
   ObjHost &host;
   OwnPtr<ObjBase> obj;
   
  public: 
  
   ObjMaster_delete(ObjHost &host_,ObjBase *obj_,StrLen name) 
    : host(host_),
      obj(obj_)
    {
     host.add(*obj,name);
    }
   
   ObjMaster_delete(ObjBase *obj_,StrLen name) 
    : host(ObjHost::Default()),
      obj(obj_)
    {
     host.add(*obj,name);
    }
   
   ~ObjMaster_delete() 
    { 
     host.del(*obj); 
     
     obj->wait_released();
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

} // namespace CCore
 
#endif
 

