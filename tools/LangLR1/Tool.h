/* Tool.h */
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef LangLR1_Tool_h
#define LangLR1_Tool_h

#include <CCore/inc/TextTools.h>
#include <CCore/inc/Cmp.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/String.h>
#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/ElementPool.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/FileSystem.h>
#include <CCore/inc/FileToMem.h>

namespace App {

/* using */

using namespace CCore;

/* functions */

/* SetCmp() */

template <class T>
bool SetCmp(T &x,const T &a) { bool ret=( x!=a ); x=a; return ret; }

/* RemoveDup() */

template <class T>
ulen RemoveDup(T *ptr,ulen len)
 {
  if( len<=1 ) return len;
  
  ulen ret=1;
  
  for(; len>1 ;ptr++,len--,ret++)
    if( !( ptr[0]<ptr[1] ) )   
      {
       T *end=ptr;
       
       ptr+=2;
       len-=2;
       
       for(; len>0 ;ptr++,len--) if( *end<*ptr ) { *(++end)=*ptr; ret++; }
       
       return ret;
      }
  
  return ret;
 }

/* RecordPtrs() */

template <class T,class S>
void RecordPtrs(PtrLen<T> range,DynArray<S *> &ret)
 {
  ret.erase();
  
  auto out=ret.extend_raw(range.len).ptr;
  
  for(; +range ;++range,++out) *out=range.ptr;
 }

/* classes */

struct OffLen;

template <class I> class IndexRange;

/* struct OffLen */

struct OffLen
 {
  ulen off;
  ulen len;
  
  OffLen() : off(0),len(0) {}
  
  OffLen(NothingType) : off(0),len(0) {}
  
  OffLen(ulen off_,ulen len_) : off(off_),len(len_) {}
  
  void init(ulen off_,ulen len_) 
   {
    off=off_;
    len=len_;
   }
  
  template <class T>
  PtrLen<T> cut(T *base) const { return Range(base+off,len); }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* class IndexRange<I> */

template <class I> 
class IndexRange
 {
   ulen ind;
   ulen lim;
   
  public: 
  
   explicit IndexRange(ulen lim_) : ind(0),lim(lim_) {}
  
   IndexRange(I ind_,ulen lim_) : ind(ind_),lim(lim_) {}
  
   bool operator + () const { return ind<lim; }
  
   bool operator ! () const { return ind>=lim; }
  
   I operator * () const { return I(ind); }
  
   void operator ++ () { ind++; }
 };

} // namespace App

#endif

