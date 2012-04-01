/* Sort.h */ 
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

#ifndef CCore_inc_Sort_h
#define CCore_inc_Sort_h

#include <CCore/inc/sort/ShortSort.h>
#include <CCore/inc/sort/HeapSort.h>
#include <CCore/inc/sort/QuickSort.h>
#include <CCore/inc/sort/ParaQuickSort.h>
 
namespace CCore {

/* classes */

template <class Ran,class Func> struct IncrSortCtx;

template <class Ran,class Func> struct DecrSortCtx;

/* struct IncrSortCtx<Ran,Func> */

template <class Ran,class Func>
struct IncrSortCtx : SortCtx<Ran>
 {
  Func func;
  
  IncrSortCtx(const Func &func_) : func(func_) {}
  
  bool less(Ran a,Ran b) { return func(*a,*b); }
 };

/* struct DecrSortCtx<Ran,Func> */

template <class Ran,class Func>
struct DecrSortCtx : SortCtx<Ran>
 {
  Func func;
  
  DecrSortCtx(const Func &func_) : func(func_) {}
  
  bool less(Ran a,Ran b) { return func(*b,*a); }
 };

/* functions */

template <class Ran,class Len>
void Sort(Ran ptr,Len len) { QuickSort<Ran>::Sort(ptr,len); }

template <class T>
void Sort(PtrLen<T> range) { Sort(range.ptr,range.len); }

template <class Ran,class Len,class Func>
void IncrSort(Ran ptr,Len len,Func less) { QuickSort<Ran,IncrSortCtx<Ran,Func> >::Sort(ptr,len,less); }

template <class Ran,class Len,class Func>
void DecrSort(Ran ptr,Len len,Func less) { QuickSort<Ran,DecrSortCtx<Ran,Func> >::Sort(ptr,len,less); }

template <class T,class Func>
void IncrSort(PtrLen<T> range,Func less) { IncrSort(range.ptr,range.len,less); }

template <class T,class Func>
void DecrSort(PtrLen<T> range,Func less) { DecrSort(range.ptr,range.len,less); }

} // namespace CCore
 
#endif
 

