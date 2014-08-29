/* UtilFunc.h */ 
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

#ifndef CCore_inc_gadget_UtilFunc_h
#define CCore_inc_gadget_UtilFunc_h
 
#include <CCore/inc/gadget/Meta.h>

namespace CCore {

/* functions */

template <class T>
const T & ToConst(T &obj) { return obj; }

template <class T>
constexpr T Min(T a,T b) { return (a<b)?a:b; }
 
template <class T>
constexpr T Max(T a,T b) { return (a<b)?b:a; }

template <class T>
constexpr T Cap(T a,T x,T b) { return (x<a)?a:( (b<x)?b:x ); }

template <class T>
constexpr bool Fit(T a,T x,T b) { return a<=x && x<=b; }

template <class T>
T Diff(T &t,T a) { T ret(a-t); t=a; return ret; }
 
/* functions */

template <class UInt,class S>
void BitSet(UInt &t,S bits) 
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::BitSet<UInt,S> : UInt must be an unsigned integral type");
 
  t|=UInt(bits); 
 }
 
template <class UInt,class S>
void BitClear(UInt &t,S bits) 
 { 
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::BitClear<UInt,S> : UInt must be an unsigned integral type");
 
  t&=~UInt(bits); 
 }

template <class UInt,class S>
UInt BitTest(UInt t,S bits)
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::BitTest<UInt,S> : UInt must be an unsigned integral type");
  
  return UInt( t&UInt(bits) );
 }
 
template <class UInt,class S>
bool BitTestAll(UInt t,S bits_)
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::BitTestAll<UInt,S> : UInt must be an unsigned integral type");
  
  UInt bits=UInt(bits_); 
  
  return UInt( t&bits )==bits;
 }
 
} // namespace CCore
 
#endif
 

