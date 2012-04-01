/* OwnPtr.h */ 
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

#ifndef CCore_inc_OwnPtr_h
#define CCore_inc_OwnPtr_h

#include <CCore/inc/Move.h>
 
namespace CCore {

/* classes */ 

template <class T> struct OwnAlgo;

template <class T,class Algo=OwnAlgo<T> > class OwnPtr;

/* struct OwnAlgo<T> */ 

template <class T> 
struct OwnAlgo
 {
  static void Destroy(T *ptr) { delete ptr; }
 };
 
/* class OwnPtr<T,Algo> */ 

template <class T,class Algo>
class OwnPtr : NoCopy
 {
   T *ptr;
   
  private: 
  
   static void SoftDestroy(OwnPtr<T,Algo> *obj)
    {
     obj->ptr=0;
     obj->~OwnPtr();
    }
   
  public:
  
   // constructors
   
   OwnPtr() : ptr(0) {}
   
   explicit OwnPtr(T *ptr_) : ptr(ptr_) {}
   
   ~OwnPtr() { if( ptr ) Algo::Destroy(ptr); }
   
   // object ptr
   
   T * operator + () const { return ptr; }
   
   bool operator ! () const { return !ptr; }
  
   T * getPtr() const { return ptr; }
   
   T & operator * () const { return *ptr; }
   
   T * operator -> () const { return ptr; }
   
   // reset
   
   void set(T *new_ptr) { if( T *old_ptr=Replace(ptr,new_ptr) ) Algo::Destroy(old_ptr); }
    
   T * detach(T *new_ptr=0) { return Replace(ptr,new_ptr); }
 
   // swap/move objects
   
   void objSwap(OwnPtr<T,Algo> &obj) { Swap(ptr,obj.ptr); }
    
   explicit OwnPtr(ToMoveCtor<OwnPtr<T,Algo> > obj) : ptr(Replace_null(obj->ptr)) {}
   
   OwnPtr<T,Algo> * objMove(Place<void> place) 
    {
     OwnPtr<T,Algo> *ret=new(place) OwnPtr<T,Algo>(ptr);
     
     SoftDestroy(this);
     
     return ret;
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
 

