/* BaseRangeAlgo.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.03
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_algon_BaseRangeAlgo_h
#define CCore_inc_algon_BaseRangeAlgo_h

#include <CCore/inc/Swap.h>
 
namespace CCore {
namespace Algon {

/* classes */

template <class R> struct BaseRangeAlgo;

/* struct BaseRangeAlgo<R> */

template <class R>
struct BaseRangeAlgo
 {
  typedef ulen LenType;
  
  static LenType GetLen(R r) { return r.len; }
  
  static R GetPrefix(R r,LenType len) { return r.prefix(len); }
   
  static R GetSuffix(R r,LenType len) { return r.suffix(len); }
  
  static R Split(R &r,LenType prefix) { return r+=prefix; }
  
  static void RangeSwap(R a,R b)
   {
    for(; +a ;++a,++b) Swap(*a,*b); 
   }
 };

template <class T>
struct BaseRangeAlgo<PtrLen<T> >
 {
  typedef ulen LenType;
  
  static LenType GetLen(PtrLen<T> r) { return r.len; }
  
  static PtrLen<T> GetPrefix(PtrLen<T> r,LenType len) { return r.prefix(len); }
   
  static PtrLen<T> GetSuffix(PtrLen<T> r,LenType len) { return r.suffix(len); }
  
  static PtrLen<T> Split(PtrLen<T> &r,LenType prefix) { return r+=prefix; }
  
  static void RangeSwap(PtrLen<T> a,PtrLen<T> b)
   {
    for(T *p=b.ptr; +a ;++a,++p) Swap(*a,*p); 
   }
 };

} // namespace Algon
} // namespace CCore
 
#endif
 

