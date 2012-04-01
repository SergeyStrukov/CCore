/* Cmp.h */ 
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

#ifndef CCore_inc_Cmp_h
#define CCore_inc_Cmp_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {

/* enum CmpResult */ 

enum CmpResult
 {
  CmpLess    = -1,
  CmpEqual   =  0,
  CmpGreater =  1
 };
 
inline CmpResult operator - (CmpResult cmp) { return CmpResult(-int(cmp)); }
 
const char * GetTextDesc(CmpResult cmp);

/* functions */ 

template <class T>
CmpResult LessCmp(const T &a,const T &b)
 {
  return (a<b)?CmpLess:( (b<a)?CmpGreater:CmpEqual );
 }

/* Str...() */ 

CmpResult StrCmp(StrLen a,StrLen b);
 
bool StrLess(StrLen a,StrLen b);

/* classes */ 

template <class T> struct LessComparable;

template <class T> struct CmpComparable;

struct ProbeSet_objCmp;

template <class T> struct Has_objCmp;

template <bool has_objCmp,class T> struct CmpAdapters;

/* struct LessComparable<T> */ 

template <class T> 
struct LessComparable
 {
  friend bool operator > (const T &a,const T &b) { return b<a; }
  
  friend bool operator <= (const T &a,const T &b) { return !(b<a); }
  
  friend bool operator >= (const T &a,const T &b) { return !(a<b); }
  
  friend bool operator == (const T &a,const T &b) { return !( a<b || b<a ); }
  
  friend bool operator != (const T &a,const T &b) { return ( a<b || b<a ); }
 };
  
/* struct CmpComparable<T> */ 

template <class T> 
struct CmpComparable
 {
  friend bool operator < (const T &a,const T &b) { return a.objCmp(b)<0; }
  
  friend bool operator > (const T &a,const T &b) { return a.objCmp(b)>0; }
  
  friend bool operator <= (const T &a,const T &b) { return a.objCmp(b)<=0; }
  
  friend bool operator >= (const T &a,const T &b) { return a.objCmp(b)>=0; }
  
  friend bool operator == (const T &a,const T &b) { return a.objCmp(b)==0; }
  
  friend bool operator != (const T &a,const T &b) { return a.objCmp(b)!=0; }
 };
 
/* struct ProbeSet_objCmp */

struct ProbeSet_objCmp
 {
  template <class T,CmpResult (T::*M)(const T &) const> struct Host;
 
  template <class T>
  static constexpr bool Probe(...) { return false; }
  
  template <class T>
  static constexpr bool Probe(Host<T,&T::objCmp> *) { return true; }
 };

/* struct Has_objCmp<T> */ 

template <class T>
struct Has_objCmp : Meta::Has<T,ProbeSet_objCmp> {};
 
/* struct CmpAdapters<bool has_objCmp,T> */  
 
template <class T> 
struct CmpAdapters<false,T>
 {
  static CmpResult Cmp(const T &a,const T &b) { return LessCmp(a,b); }
 };
 
template <class T> 
struct CmpAdapters<true,T>
 {
  static CmpResult Cmp(const T &a,const T &b) { return a.objCmp(b); }
 };
 
/* Cmp() */  
 
template <class T> 
CmpResult Cmp(const T &a,const T &b) { return CmpAdapters<Has_objCmp<T>::Ret,T>::Cmp(a,b); }

/* AlphaCmp() */
 
template <class T> 
CmpResult AlphaCmp(const T &a,const T &b)
 {
  return Cmp(a,b);
 }
 
template <class T,class S,class ... TT> 
CmpResult AlphaCmp(const T &a,const T &b,const S &a1,const S &b1,const TT & ... tt)
 {
  if( CmpResult ret=Cmp(a,b) ) return ret;
  
  return AlphaCmp(a1,b1,tt...);
 }
 
/* Range...() */ 

template <class T>
CmpResult RangeCmp(const T *a,const T *b,ulen count)
 {
  for(; count ;count--)
    if( CmpResult ret=Cmp(*(a++),*(b++)) ) 
      return ret;
     
  return CmpEqual;   
 }
 
template <class T>
CmpResult RangeCmp(PtrLen<T> a,PtrLen<T> b)
 {
  if( a.len<b.len )
    {
     if( CmpResult ret=RangeCmp(a.ptr,b.ptr,a.len) ) return ret;
     
     return CmpLess;
    }
  else if( a.len>b.len )
    {
     if( CmpResult ret=RangeCmp(a.ptr,b.ptr,b.len) ) return ret;
     
     return CmpGreater;
    }
  else
    {
     return RangeCmp(a.ptr,b.ptr,b.len);
    }
 }
  
template <class T>
bool RangeLess(PtrLen<T> a,PtrLen<T> b) 
 {
  if( a.len<b.len )
    {
     return RangeCmp(a.ptr,b.ptr,a.len) <= 0 ;
    }
  else
    {
     return RangeCmp(a.ptr,b.ptr,b.len) < 0 ;
    }
 }
 
} // namespace CCore
 
#endif
 

