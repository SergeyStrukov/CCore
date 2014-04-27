/* AttachmentHost.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_AttachmentHost_h
#define CCore_inc_AttachmentHost_h

#include <CCore/inc/Task.h>
 
namespace CCore {

/* functions */

void GuardAlreadyAttached(StrLen class_name);

void AbortAttachOnExit(StrLen class_name);

/* classes */

template <class T> class AttachmentHost;

/* class AttachmentHost<T> */

template <class T>
class AttachmentHost : NoCopy
 {
   StrLen class_name;
   
   Mutex mutex;
 
   T *obj = 0 ;
   bool enable = false ;
 
   AntiSem asem;
   
  public: 
   
   explicit AttachmentHost(StrLen class_name);
   
   AttachmentHost(StrLen class_name,TextLabel name);
   
   ~AttachmentHost();
   
   void attach(T *obj);
   
   void detach();
   
   class Hook : NoCopy
    {
      T *obj;
      AntiSem *asem;
      
     public:
      
      explicit Hook(AttachmentHost<T> &host);
      
      ~Hook();
      
      // object ptr
      
      T * operator + () const { return obj; }
      
      bool operator ! () const { return !obj; }
     
      T * getPtr() const { return obj; }
      
      T & operator * () const { return *obj; }
      
      T * operator -> () const { return obj; }
    };
 };

template <class T>
AttachmentHost<T>::AttachmentHost(StrLen class_name_)
 : class_name(class_name_)
 {
 }

template <class T>
AttachmentHost<T>::AttachmentHost(StrLen class_name_,TextLabel name)
 : class_name(class_name_),
   mutex(name),
   asem(name)
 {
 }

template <class T>
AttachmentHost<T>::~AttachmentHost()
 {
  Mutex::Lock lock(mutex);
  
  if( obj ) AbortAttachOnExit(class_name);
 }

template <class T>
void AttachmentHost<T>::attach(T *obj_)
 {
  bool has_obj;
  
  {
   Mutex::Lock lock(mutex);
   
   if( obj )
     {
      has_obj=true;
     }
   else 
     {
      has_obj=false;
      
      obj=obj_;
      enable=true;
     }
  }

  if( has_obj ) GuardAlreadyAttached(class_name); 
 }

template <class T>
void AttachmentHost<T>::detach()
 {
  {
   Mutex::Lock lock(mutex);
   
   enable=false;
  }
  
  asem.wait();
  
  {
   Mutex::Lock lock(mutex);
   
   obj=0;
  }
 }

template <class T>
AttachmentHost<T>::Hook::Hook(AttachmentHost<T> &host)
 {
  {
   Mutex::Lock lock(host.mutex);
  
   if( host.enable )
     {
      obj=host.obj;
     
      asem=&host.asem;
     }
   else
     {
      obj=0;
     }
  }
  
  if( obj ) asem->inc();
 }

template <class T>
AttachmentHost<T>::Hook::~Hook()
 {
  if( obj ) asem->dec();
 }

} // namespace CCore
 
#endif
 

