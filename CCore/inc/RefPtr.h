/* RefPtr.h */ 
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

#ifndef CCore_inc_RefPtr_h
#define CCore_inc_RefPtr_h

#include <CCore/inc/Move.h>
 
namespace CCore {

/* classes */ 

template <class T> struct RefAlgo;

template <class T,class Algo=RefAlgo<T> > class RefPtr;

/* struct RefAlgo<T> */ 

template <class T> 
struct RefAlgo
 {
  static void IncRef(T *ptr) { ptr->incRef(); }
  
  static bool DecRef(T *ptr) { return ptr->decRef(); }
  
  static void Destroy(T *ptr) { ptr->destroy(); }
 };
 
/* class RefPtr<T,Algo> */ 

template <class T,class Algo> 
class RefPtr
 {
   T *ptr;
   
  private:
  
   static void SoftDestroy(RefPtr<T,Algo> *obj)
    {
     obj->ptr=0;
     obj->~RefPtr();
    }
  
  public: 
  
   // constructors
   
   explicit RefPtr(T *ptr_) : ptr(ptr_) {} // ptr_!=0
   
   ~RefPtr() { if( ptr && Algo::DecRef(ptr) ) Algo::Destroy(ptr); }
    
   // copying 
    
   RefPtr(const RefPtr<T,Algo> &obj) : ptr(obj.ptr) { Algo::IncRef(ptr); }
    
   RefPtr<T,Algo> & operator = (const RefPtr<T,Algo> &obj)
    {
     T *new_ptr=obj.ptr;
     T *old_ptr=Replace(ptr,new_ptr);

     Algo::IncRef(new_ptr);
     
     if( Algo::DecRef(old_ptr) ) Algo::Destroy(old_ptr);
    
     return *this;
    }
    
   // object ptr
    
   T * getPtr() const { return ptr; }
   
   T & operator * () const { return *ptr; }
   
   T * operator -> () const { return ptr; }
   
   // reset
   
   void set(T *new_ptr) // new_ptr!=0
    {
     T *old_ptr=Replace(ptr,new_ptr);

     if( Algo::DecRef(old_ptr) ) Algo::Destroy(old_ptr);
    }
   
   // update
   
   template <class Func>
   void update(Func func) { ptr=func(ptr); }
 
   // swap/move objects
   
   void objSwap(RefPtr<T,Algo> &obj) { Swap(ptr,obj.ptr); }
    
   explicit RefPtr(ToMoveCtor<RefPtr<T,Algo> > obj) : ptr(Replace_null(obj->ptr)) {}
   
   RefPtr<T,Algo> * objMove(Place<void> place)
    {
     RefPtr<T,Algo> *ret=new(place) RefPtr<T,Algo>(ptr);
     
     SoftDestroy(this);
     
     return ret;
    }
 };
 
} // namespace CCore
 
#endif
 

