/* SortUnique.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.04
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

#ifndef CCore_inc_algon_SortUnique_h
#define CCore_inc_algon_SortUnique_h

#include <CCore/inc/Sort.h>
#include <CCore/inc/FunctorType.h>
#include <CCore/inc/algon/BaseRangeAlgo.h>
 
namespace CCore {
namespace Algon {

/* classes */

template <class R,class Algo=BaseRangeAlgo<R> > struct ApplyUniqueAlgo;

/* struct ApplyUniqueAlgo<R,Algo> */

template <class R,class Algo> 
struct ApplyUniqueAlgo : Algo
 {
  using Algo::GetPtr;
  using Algo::GetPrefix;
 
  template <class FuncInit>
  static void ApplyUnique(R r,FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    if( +r )
      {
       auto last=GetPtr(r);
       
       func(*last);
       
       for(++r; +r ;++r)
         {
          if( *last!=*r )
            {
             last=GetPtr(r);
             
             func(*last);
            }
         }
      }
   }
  
  template <class Func,class FuncInit>
  static void ApplyUniqueBy(R r,Func by,FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    if( +r )
      {
       auto last=GetPtr(r);
       
       func(*last);
       
       for(++r; +r ;++r)
         {
          if( by(*last)!=by(*r) )
            {
             last=GetPtr(r);
             
             func(*last);
            }
         }
      }
   }
  
  template <class FuncInit>
  static void ApplyUniqueRange(R r,FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    if( +r )
      {
       R last=r;
       
       for(++r; +r ;++r)
         {
          if( *last!=*r )
            {
             R delta=GetPrefix(last,r);
            
             last=r;
             
             func(delta);
            }
         }
       
       func(last);
      }
   }
  
  template <class Func,class FuncInit>
  static void ApplyUniqueRangeBy(R r,Func by,FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    if( +r )
      {
       R last=r;
       
       for(++r; +r ;++r)
         {
          if( by(*last)!=by(*r) )
            {
             R delta=GetPrefix(last,r);
            
             last=r;
             
             func(delta);
            }
         }
       
       func(last);
      }
   }
 };

/* ...SortBy() */

template <class Ran,class Len,class Func>
void IncrSortBy(Ran ptr,Len len,Func by)
 {
  using T = decltype(*ptr) ; 
  
  IncrSort(ptr,len, [=] (const T &a,const T &b) -> bool { return by(a) < by(b) ; } );
 }

template <class Ran,class Len,class Func>
void DecrSortBy(Ran ptr,Len len,Func by)
 {
  using T = decltype(*ptr) ; 
  
  DecrSort(ptr,len, [=] (const T &a,const T &b) -> bool { return by(a) < by(b) ; } );
 }

template <class T,class Func>
void IncrSortBy(PtrLen<T> range,Func by) { IncrSortBy(range.ptr,range.len,by); }

template <class T,class Func>
void DecrSortBy(PtrLen<T> range,Func by) { DecrSortBy(range.ptr,range.len,by); }

template <class T,class Func>
void IncrSortBy(PtrLenReverse<T> range,Func by) { DecrSortBy(range.ptr-range.len,range.len,by); }

template <class T,class Func>
void DecrSortBy(PtrLenReverse<T> range,Func by) { IncrSortBy(range.ptr-range.len,range.len,by); }

/* ApplyUnique() */

template <class R,class FuncInit>
void ApplyUnique(R r,FuncInit func_init)
 {
  ApplyUniqueAlgo<R>::ApplyUnique(r,func_init);
 }

/* SortThenApplyUnique() */

template <class R,class FuncInit>
void SortThenApplyUnique(R r,FuncInit func_init)
 {
  Sort(r);
  ApplyUnique(r,func_init);
 }

/* ApplyUniqueBy() */

template <class R,class Func,class FuncInit>
void ApplyUniqueBy(R r,Func by,FuncInit func_init)
 {
  ApplyUniqueAlgo<R>::ApplyUniqueBy(r,by,func_init);
 }

/* ...SortThenApplyUniqueBy() */

template <class R,class Func,class FuncInit>
void IncrSortThenApplyUniqueBy(R r,Func by,FuncInit func_init)
 {
  IncrSortBy(r,by);
  ApplyUniqueBy(r,by,func_init);
 }

template <class R,class Func,class FuncInit>
void DecrSortThenApplyUniqueBy(R r,Func by,FuncInit func_init)
 {
  DecrSortBy(r,by);
  ApplyUniqueBy(r,by,func_init);
 }

/* ApplyUniqueRange() */

template <class R,class FuncInit>
void ApplyUniqueRange(R r,FuncInit func_init)
 {
  ApplyUniqueAlgo<R>::ApplyUniqueRange(r,func_init);
 }
  
/* SortThenApplyUniqueRange() */

template <class R,class FuncInit>
void SortThenApplyUniqueRange(R r,FuncInit func_init)
 {
  Sort(r);
  ApplyUniqueRange(r,func_init);
 }

/* ApplyUniqueRangeBy() */

template <class R,class Func,class FuncInit>
void ApplyUniqueRangeBy(R r,Func by,FuncInit func_init)
 {
  ApplyUniqueAlgo<R>::ApplyUniqueRangeBy(r,by,func_init);
 }

/* ...SortThenApplyUniqueRangeBy() */
  
template <class R,class Func,class FuncInit>
void IncrSortThenApplyUniqueRangeBy(R r,Func by,FuncInit func_init)
 {
  IncrSortBy(r,by);
  ApplyUniqueRangeBy(r,by,func_init);
 }

template <class R,class Func,class FuncInit>
void DecrSortThenApplyUniqueRangeBy(R r,Func by,FuncInit func_init)
 {
  DecrSortBy(r,by);
  ApplyUniqueRangeBy(r,by,func_init);
 }

} // namespace Algon
} // namespace CCore
 
#endif
 

