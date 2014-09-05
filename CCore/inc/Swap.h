/* Swap.h */ 
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

#ifndef CCore_inc_Swap_h
#define CCore_inc_Swap_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {

/* functions */ 

template <class T>
void CopySwap(T &a,T &b) noexcept(EnableNoExcept)
 {
  T temp(a);
  
  a=b;
  
  b=temp;
 }
 
/* classes */

struct ProbeSet_objSwap;

template <class T> struct Has_objSwap;

template <bool has_objSwap,class T> struct SwapAdapters;

/* struct ProbeSet_objSwap */

struct ProbeSet_objSwap
 {
  template <class T,void (T::*M)(T &)> struct Host;
 
  template <class T>
  static constexpr bool Probe(...) { return false; } 
 
  template <class T>
  static constexpr bool Probe(Host<T,&T::objSwap> *) { return true; }
 };

/* struct Has_objSwap<T> */ 

template <class T> 
struct Has_objSwap : Meta::Has<T,ProbeSet_objSwap> {};

/* struct SwapAdapters<bool has_objSwap,T> */ 

template <class T> 
struct SwapAdapters<true,T>
 {
  static void Swap(T &a,T &b) { a.objSwap(b); }
 };
 
template <class T> 
struct SwapAdapters<false,T>
 {
  static void Swap(T &a,T &b) { CopySwap(a,b); }
 };
 
/* Swap() */ 

template <class T>
void Swap(T &a,T &b) noexcept(EnableNoExcept) { SwapAdapters<Has_objSwap<T>::Ret,T>::Swap(a,b); }

/* NullBySwap() */

template <class T>
void NullBySwap(T &obj)
 {
  T temp{};

  Swap(temp,obj);
 }

/* MoveBySwap() */

template <class T>
void MoveBySwap(T &dst,T &src)
 {
  Swap(dst,src);
  
  NullBySwap(src);
 }

} // namespace CCore
 
#endif
 

