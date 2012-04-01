/* FunctorType.h */ 
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

#ifndef CCore_inc_FunctorType_h
#define CCore_inc_FunctorType_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {

/* classes */

struct ProbeSet_FunctorType;

template <class T> struct Has_FunctorType;

template <bool has_FunctorType,class FuncInit> struct FunctorTypes;

template <class T> struct FunctorRefType;

/* struct ProbeSet_FunctorType */

struct ProbeSet_FunctorType
 {
  template <class T> struct Host;
  
  template <class T>
  static constexpr bool Probe(...) { return false; }
  
  template <class T>
  static constexpr bool Probe(Host<typename T::FunctorType> *) { return true; }
 };

/* struct Has_FunctorType<T> */ 

template <class T>
struct Has_FunctorType : Meta::Has<T,ProbeSet_FunctorType> {};

/* struct FunctorTypes<bool has_FunctorType,FuncInit> */ 

template <class FuncInit> 
struct FunctorTypes<true,FuncInit>
 {
  typedef typename FuncInit::FunctorType Ret;
 };

template <class FuncInit> 
struct FunctorTypes<false,FuncInit>
 {
  typedef FuncInit Ret;
 };

/* type FunctorTypeOf<FuncInit> */

template <class FuncInit>
using FunctorTypeOf = typename FunctorTypes<Has_FunctorType<FuncInit>::Ret,FuncInit>::Ret ;

/* struct FunctorRefType<T> */ 

template <class T> 
struct FunctorRefType
 {
  T *obj;
  
  explicit FunctorRefType(T &obj_) : obj(&obj_) {}
  
  typedef T & FunctorType;
  
  operator FunctorType() const { return *obj; }
 };

/* FunctorRef() */

template <class T>
FunctorRefType<T> FunctorRef(T &obj) { return FunctorRefType<T>(obj); }

} // namespace CCore
 
#endif
 

