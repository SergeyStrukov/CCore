/* Move.h */ 
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

#ifndef CCore_inc_Move_h
#define CCore_inc_Move_h

#include <CCore/inc/Swap.h>
 
namespace CCore {

/* classes */ 

template <class T> struct ToMoveCtor;

struct ProbeSet_objMove;

template <class T> struct Has_objMove;

template <bool has_objMove,bool has_objSwap,class T> struct MoveAdapters;

/* struct ToMoveCtor<T> */ 

template <class T>
struct ToMoveCtor
 {
  T *obj;
 
  explicit ToMoveCtor(T &obj_) { obj=&obj_; }
  
  T * operator -> () const { return obj; }
  
  template <class S>
  ToMoveCtor<S> cast() const { return ToMoveCtor<S>(*obj); }
 };
 
/* functions */  

template <class T>
ToMoveCtor<T> ObjToMove(T &obj) { return ToMoveCtor<T>(obj); }
 
template <class T>
T * CopyMove(T *obj,Place<void> place) noexcept(EnableNoExcept)
 {
  T *ret=new(place) T(*obj);
  
  obj->~T();
  
  return ret;
 }
 
template <class T>
T * SwapMove(T *obj,Place<void> place) noexcept(EnableNoExcept)
 {
  T *ret=new(place) T();
  
  Swap(*obj,*ret);
  
  obj->~T();
  
  return ret;
 }
 
template <class T>
T * CtorMove(T *obj,Place<void> place) noexcept(EnableNoExcept)
 {
  T *ret=new(place) T(ObjToMove(*obj));
  
  obj->~T();
  
  return ret;
 }
 
/* struct ProbeSet_objMove*/

struct ProbeSet_objMove
 {
  template <class T,T * (T::*M)(Place<void>)> struct Host;
 
  template <class T>
  static constexpr bool Probe(...) { return false; }
 
  template <class T>
  static constexpr bool Probe(Host<T,&T::objMove> *) { return true; }
 };

/* struct Has_objMove<T> */ 

template <class T> 
struct Has_objMove : Meta::Has<T,ProbeSet_objMove> {};
 
/* struct MoveAdapters<bool has_objMove,bool has_objSwap,T> */ 
 
template <bool has_objSwap,class T> 
struct MoveAdapters<true,has_objSwap,T>
 {
  static T * Move(T *obj,Place<void> place) { return obj->objMove(place); }
 };
 
template <class T> 
struct MoveAdapters<false,true,T>
 {
  static T * Move(T *obj,Place<void> place) { return SwapMove(obj,place); }
 };
 
template <class T> 
struct MoveAdapters<false,false,T>
 {
  static T * Move(T *obj,Place<void> place) { return CopyMove(obj,place); }
 };
 
/* Move() */  

template <class T>
T * Move(T *obj,Place<void> place) noexcept(EnableNoExcept) { return MoveAdapters<Has_objMove<T>::Ret,Has_objSwap<T>::Ret,T>::Move(obj,place); }
 
} // namespace CCore
 
#endif
 

