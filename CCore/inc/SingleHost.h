/* SingleHost.h */ 
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

#ifndef CCore_inc_SingleHost_h
#define CCore_inc_SingleHost_h
 
#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Task.h>

namespace CCore {

/* functions */

void SingleHostExitAbort();

void GuardSingleHostTaken();

/* classes */

template <class T> class SingleHost;

template <class T> class SingleHook;

template <class T> class SingleMaster;

template <class T> class SingleMaster_delete;

/* class SingleHost<T> */

template <class T> 
class SingleHost : NoCopy
 {
   Mutex mutex;
   
   T *obj;
   AntiSem *asem;
   
  private: 
   
   struct LockResult
    {
     T *obj;
     AntiSem *asem;
     
     LockResult(NothingType) : obj(0),asem(0) {}
     
     LockResult(T *obj_,AntiSem *asem_) : obj(obj_),asem(asem_) {}
    };

   LockResult try_lock();
   
   friend class SingleHook<T>;
   
   bool add(T &obj,AntiSem &asem);
   
   void del();
   
   friend class SingleMaster<T>;
   friend class SingleMaster_delete<T>;
   
  public: 
   
   explicit SingleHost(TextLabel name);
   
   ~SingleHost();
 };

template <class T> 
auto SingleHost<T>::try_lock() -> LockResult
 {
  Mutex::Lock lock(mutex);

  if( !obj ) return Nothing;
  
  asem->inc();
  
  return LockResult(obj,asem);
 }

template <class T> 
bool SingleHost<T>::add(T &obj_,AntiSem &asem_)
 {
  Mutex::Lock lock(mutex);
  
  if( obj ) return false;
  
  obj=&obj_;
  asem=&asem_;
  
  return true;
 }

template <class T> 
void SingleHost<T>::del()
 {
  Mutex::Lock lock(mutex);
  
  obj=0;
  asem=0;
 }

template <class T> 
SingleHost<T>::SingleHost(TextLabel name)
 : mutex(name),
   obj(0),
   asem(0)
 {
 }

template <class T> 
SingleHost<T>::~SingleHost()
 {
  Mutex::Lock lock(mutex);
  
  if( obj ) SingleHostExitAbort();
 }

/* class SingleHook<T> */

template <class T> 
class SingleHook : NoCopy
 {
   T *obj;
   AntiSem *asem;
   
  public:

   //
   // assign/move/swap are not provided to prevent cyclic dependencies
   //
   
   // constructors
   
   explicit SingleHook(SingleHost<T> &host)
    {
     auto result=host.try_lock();
     
     obj=result.obj;
     asem=result.asem;
    }
   
   ~SingleHook()
    {
     if( asem ) asem->dec();
    }
   
   // object ptr
   
   T * operator + () const { return obj; }
   
   bool operator ! () const { return !obj; }
  
   T * getPtr() const { return obj; }
   
   T & operator * () const { return *obj; }
   
   T * operator -> () const { return obj; }
   
   // copy objects
   
   SingleHook(const SingleHook &hook)
    : NoCopy() // warning supression
    {
     obj=hook.obj;
     asem=hook.asem;
     
     if( asem ) asem->inc();
    }
 };

/* class SingleMaster<T> */

template <class T> 
class SingleMaster : NoCopy
 {
   AntiSem asem;
   
   SingleHost<T> *host;
  
  public:
   
   SingleMaster(SingleHost<T> &host_,TextLabel name,T &obj)
    : asem(name)
    {
     if( host_.add(obj,asem) )
       {
        host=&host_;
       }
     else
       {
        host=0;
       }
    }
   
   ~SingleMaster() 
    {
     if( host )
       {
        host->del();
        
        asem.wait();
       }
    }
   
   void guard()
    {
     if( !host ) GuardSingleHostTaken();
    }
 };

/* class SingleMaster_delete<T> */

template <class T> 
class SingleMaster_delete : NoCopy 
 {
   OwnPtr<T> obj;
   
   SingleMaster<T> master;
  
  public:
   
   SingleMaster_delete(SingleHost<T> &host,TextLabel name,T *obj_) : obj(obj_),master(host,name,*obj) {}
   
   ~SingleMaster_delete() {} 
   
   void guard() { master.guard(); }
 };

} // namespace CCore
 
#endif
 

