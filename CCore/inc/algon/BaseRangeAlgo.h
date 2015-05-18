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
  
  static auto GetPtr(R r) -> decltype(r.ptr) { return r.ptr; }
  
  static LenType GetLen(R r) { return r.len; }
  
  static R GetPrefix(R r,LenType len) { return r.prefix(len); }
   
  static R GetSuffix(R r,LenType len) { return r.suffix(len); }
  
  static R Split(R &r,LenType prefix) { return r+=prefix; }
  
  static R GetPrefix(R r,R suffix) { return r.prefix(suffix); }
  
  static void RangeSwap(R a,R b)
   {
    for(; +a ;++a,++b) Swap(*a,*b); 
   }
 };

template <class T>
struct BaseRangeAlgo<PtrLen<T> >
 {
  typedef ulen LenType;
  
  static T * GetPtr(PtrLen<T> r) { return r.ptr; }
  
  static LenType GetLen(PtrLen<T> r) { return r.len; }
  
  static PtrLen<T> GetPrefix(PtrLen<T> r,LenType len) { return r.prefix(len); }
   
  static PtrLen<T> GetSuffix(PtrLen<T> r,LenType len) { return r.suffix(len); }
  
  static PtrLen<T> Split(PtrLen<T> &r,LenType prefix) { return r+=prefix; }
  
  static PtrLen<T> GetPrefix(PtrLen<T> r,PtrLen<T> suffix) { return r.prefix(suffix); }
  
  static void RangeSwap(PtrLen<T> a,PtrLen<T> b)
   {
    for(T *p=b.ptr; +a ;++a,++p) Swap(*a,*p); 
   }

  static PtrLenReverse<T> Reverse(PtrLen<T> r) { return RangeReverse(r); }
 };

template <class T>
struct BaseRangeAlgo<PtrLenReverse<T> >
 {
  typedef ulen LenType;
  
  static T * GetPtr(PtrLenReverse<T> r) { return r.ptr-1; }
  
  static LenType GetLen(PtrLenReverse<T> r) { return r.len; }
  
  static PtrLenReverse<T> GetPrefix(PtrLenReverse<T> r,LenType len) { return r.prefix(len); }
   
  static PtrLenReverse<T> GetSuffix(PtrLenReverse<T> r,LenType len) { return r.suffix(len); }
  
  static PtrLenReverse<T> Split(PtrLenReverse<T> &r,LenType prefix) { return r+=prefix; }
  
  static PtrLenReverse<T> GetPrefix(PtrLenReverse<T> r,PtrLenReverse<T> suffix) { return r.prefix(suffix); }
  
  static void RangeSwap(PtrLenReverse<T> a,PtrLenReverse<T> b)
   {
    for(T *p=b.ptr; +a ;++a,--p) Swap(*a,p[-1]); 
   }

  static PtrLen<T> Reverse(PtrLenReverse<T> r) { return PtrLen<T>(r.ptr-r.len,r.len); }
 };

} // namespace Algon
} // namespace CCore
 
#endif
 

