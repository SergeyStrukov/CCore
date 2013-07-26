/* AnyPtr.h */ 
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

#ifndef CCore_inc_AnyPtr_h
#define CCore_inc_AnyPtr_h

#include <CCore/inc/FunctorType.h>
 
namespace CCore {

/* ApplyToPtr() */

template <class T,class FuncInit>
void ApplyToPtr(void *ptr,FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  func(static_cast<T *>(ptr));
 }

/* ApplyToPtr_const() */

template <class T,class FuncInit>
void ApplyToPtr_const(const void *ptr,FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  func(static_cast<const T *>(ptr));
 }

/* classes */

template <class ... TT> class AnyPtr;

template <class ... TT> class AnyPtr_const;

/* class AnyPtr<TT> */

template <class ... TT> 
class AnyPtr
 {
   void *ptr;
   unsigned type;
   
  public:
  
   AnyPtr() : ptr(0),type(0) {}
   
   AnyPtr(NothingType) : AnyPtr() {}
   
   AnyPtr(std::nullptr_t) : AnyPtr() {}
   
   template <class T>
   AnyPtr(T *ptr_) : ptr(ptr_),type(Meta::IndexOf<T,TT...>::Ret) {}
   
   void * operator + () const { return ptr; }
   
   bool operator ! () const { return !ptr; }
   
   template <class T>
   bool hasType() const { return type==Meta::IndexOf<T,TT...>::Ret; }
   
   template <class FuncInit>
   void apply(FuncInit func_init) const
    {
     using FuncType = void (*)(void *ptr,FuncInit func_init) ; 
     
     static const FuncType Table[]={ ApplyToPtr<TT,FuncInit>... };
     
     if( type ) Table[type-1](ptr,func_init);
    }
   
   template <class T,class FuncInit>
   void applyFor(FuncInit func_init) const
    {
     if( hasType<T>() ) ApplyToPtr<T>(ptr,func_init);
    }
 };

/* class AnyPtr_const<TT> */

template <class ... TT> 
class AnyPtr_const
 {
   const void *ptr;
   unsigned type;
   
  public:
  
   AnyPtr_const() : ptr(0),type(0) {}
   
   AnyPtr_const(NothingType) : AnyPtr_const() {}
   
   AnyPtr_const(std::nullptr_t) : AnyPtr_const() {}
   
   template <class T>
   AnyPtr_const(const T *ptr_) : ptr(ptr_),type(Meta::IndexOf<T,TT...>::Ret) {}
   
   const void * operator + () const { return ptr; }
   
   bool operator ! () const { return !ptr; }
   
   template <class T>
   bool hasType() const { return type==Meta::IndexOf<T,TT...>::Ret; }
   
   template <class FuncInit>
   void apply(FuncInit func_init) const
    {
     using FuncType = void (*)(const void *ptr,FuncInit func_init) ; 
     
     static const FuncType Table[]={ ApplyToPtr_const<TT,FuncInit>... };
     
     if( type ) Table[type-1](ptr,func_init);
    }
   
   template <class T,class FuncInit>
   void applyFor(FuncInit func_init) const
    {
     if( hasType<T>() ) ApplyToPtr_const<T>(ptr,func_init);
    }
 };

} // namespace CCore
 
#endif
