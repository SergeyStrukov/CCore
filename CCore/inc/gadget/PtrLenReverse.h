/* PtrLenReverse.h */ 
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
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_PtrLenReverse_h
#define CCore_inc_gadget_PtrLenReverse_h

#include <CCore/inc/gadget/PtrLen.h>
 
namespace CCore {

/* classes */

template <class T> struct PtrLenReverse;

/* struct PtrLenReverse<T> */

template <class T> 
struct PtrLenReverse
 {
  T *ptr;
  ulen len;
  
  // constructors
  
  PtrLenReverse() : ptr(0),len(0) {}
  
  PtrLenReverse(NothingType) : ptr(0),len(0) {}
  
  PtrLenReverse(T *ptr_,ulen len_) : ptr(ptr_+len_),len(len_) {}
  
  // cursor
  
  ulen operator + () const { return len; }
  
  bool operator ! () const { return !len;  }
  
  T & operator * () const { return ptr[-1]; }
  
  T * operator -> () const { return ptr-1; }
  
  void operator ++ () { ptr--; len--; }
  
  void operator -- () { ptr++; len++; }
  
  PtrLenReverse<T> operator += (ulen delta) // assume fit(delta)
   {
    PtrLenReverse<T> ret=MakeFrom(ptr,delta);
    
    ptr-=delta;
    len-=delta;
    
    return ret;
   }
   
  PtrLenReverse<T> takeup(ulen delta)
   {
    Replace_min(delta,len);
   
    PtrLenReverse<T> ret=MakeFrom(ptr,delta);
    
    ptr-=delta;
    len-=delta;
    
    return ret;
   }
  
  T & take()
   {
    T &ret=ptr[-1];
    
    ptr--;
    len--;
    
    return ret;
   }
  
  // fit
   
  bool fit(ulen length) const { return length<=len; }
  
  bool fit(ulen off,ulen length) const { return off<=len && length<=(len-off) ; }
  
  // parts
  
  static PtrLenReverse<T> MakeFrom(T *ptr,ulen len)
   {
    PtrLenReverse<T> ret;
    
    ret.ptr=ptr;
    ret.len=len;
    
    return ret; 
   }
  
  PtrLenReverse<T> prefix(ulen length) const { return MakeFrom(ptr,length); }                     // assume fit(length)
  
  PtrLenReverse<T> prefix(PtrLenReverse<T> suffix) const { return MakeFrom(ptr,len-suffix.len); }
  
  PtrLenReverse<T> suffix(ulen length) const { return MakeFrom(ptr-(len-length),length); }        // assume fit(length)
  
  PtrLenReverse<T> part(ulen off,ulen length) const { return MakeFrom(ptr-off,length); }          // assume fit(off,length)
  
  PtrLenReverse<T> part(ulen off) const { return MakeFrom(ptr-off,len-off); }                     // assume fit(off)
  
  PtrLenReverse<T> inner(ulen off,ulen endoff) const { return MakeFrom(ptr-off,len-off-endoff); } // assume fit(off,endoff)
   
  // index access
  
  T & operator [] (ulen index) const
   {
    return *(ptr-1-index);
   }
   
  T & at(ulen index) const
   {
    GuardIndex(index,len);
    
    return *(ptr-1-index);
   }
  
  T & back(ulen index) const // 1 is the last
   {
    return *(ptr-(len-index+1));
   }
   
  // begin()/end() support
  
  bool operator != (PtrLenReverse<T> end) const { return len!=end.len; }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* RangeReverse...() */  

template <class T> 
PtrLenReverse<T> RangeReverse(PtrLenReverse<T> a) { return a; }
 
template <class T> 
PtrLenReverse<T> RangeReverse(PtrLen<T> a) { return PtrLenReverse<T>(a.ptr,a.len); }
 
template <class T,ulen Len> 
PtrLenReverse<T> RangeReverse(T (&buf)[Len]) { return PtrLenReverse<T>(buf,Len); }
 
template <class T> 
PtrLenReverse<T> RangeReverse(T *ptr,ulen len) { return PtrLenReverse<T>(ptr,len); }
 
template <class T> 
PtrLenReverse<T> RangeReverse(T *ptr,T *lim) { return PtrLenReverse<T>::MakeFrom(lim,Dist(ptr,lim)); }
 
template <class T> 
PtrLenReverse<const T> RangeReverse_const(PtrLenReverse<T> a) { return PtrLenReverse<const T>::MakeFrom(a.ptr,a.len); }
 
template <class T> 
PtrLenReverse<const T> RangeReverse_const(PtrLen<T> a) { return PtrLenReverse<const T>(a.ptr,a.len); }
 
template <class T,ulen Len> 
PtrLenReverse<const T> RangeReverse_const(T (&buf)[Len]) { return PtrLenReverse<const T>(buf,Len); }
 
template <class T> 
PtrLenReverse<const T> RangeReverse_const(T *ptr,ulen len) { return PtrLenReverse<const T>(ptr,len); }
 
template <class T> 
PtrLenReverse<const T> RangeReverse_const(T *ptr,T *lim) { return PtrLenReverse<const T>::MakeFrom(lim,Dist(ptr,lim)); }

/* container RangeReverse...() */  

template <class S>
auto RangeReverse(S &&src) -> decltype( RangeReverse(src.getPtr(),src.getLen()) ) 
 { 
  return RangeReverse(src.getPtr(),src.getLen()); 
 }
 
template <class S>
auto RangeReverse_const(const S &src) -> decltype( RangeReverse_const(src.getPtr_const(),src.getLen()) )
 { 
  return RangeReverse_const(src.getPtr_const(),src.getLen()); 
 }
 
/* begin()/end() */

template <class T> 
PtrLenReverse<T> begin(PtrLenReverse<T> a) { return a; }
 
template <class T> 
PtrLenReverse<T> end(PtrLenReverse<T>) { return Nothing; }
 
} // namespace CCore
 
#endif
 

