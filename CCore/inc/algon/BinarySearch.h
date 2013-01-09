/* BinarySearch.h */
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

#ifndef CCore_inc_algon_BinarySearch_h
#define CCore_inc_algon_BinarySearch_h

#include <CCore/inc/algon/BaseRangeAlgo.h>
 
namespace CCore {
namespace Algon {

/* classes */

template <class R,class Algo=BaseRangeAlgo<R> > struct BinarySearchAlgo;

/* struct BinarySearchAlgo<R,Algo> */

template <class R,class Algo>
struct BinarySearchAlgo : Algo
 {
  typedef typename Algo::LenType LenType;
 
  using Algo::GetLen;
  using Algo::Split;
 
  template <class Pred>
  static R Find(R &r,Pred pred) // pred(R) is 0,0,0,...,0,1,1,...
   {
    R temp=r;
    
    LenType off=0;
    LenType len=GetLen(temp);
    
    if( !len ) return temp;
    
    // 0,0,... [off,len) 1,1,...
    
    while( len>1 )
      {
       LenType pref=len/2;
      
       if( pred(temp[off+pref]) )
         {
          len=pref;
         }
       else
         {
          pref++;
          
          off+=pref;
          len-=pref;
          
          if( !len ) return Split(r,off);
         } 
      }
    
    if( pred(temp[off]) )
      {
       return Split(r,off);
      }
    else
      {
       return Split(r,off+1);
      }
   }
  
  template <class S>
  static R Find_less(R &r,const S &med) // R is decreasing
   {
    typedef Meta::RangeObjType<R> T;
    
    return Find(r, [&] (const T &obj) -> bool { return obj<med; } );
   }
  
  template <class S>
  static R Find_less_or_equal(R &r,const S &med) // R is decreasing
   {
    typedef Meta::RangeObjType<R> T;
    
    return Find(r, [&] (const T &obj) -> bool { return obj<=med; } );
   }
  
  template <class S>
  static R Find_greater(R &r,const S &med) // R is increasing
   {
    typedef Meta::RangeObjType<R> T;
    
    return Find(r, [&] (const T &obj) -> bool { return obj>med; } );
   }
  
  template <class S>
  static R Find_greater_or_equal(R &r,const S &med) // R is increasing
   {
    typedef Meta::RangeObjType<R> T;
    
    return Find(r, [&] (const T &obj) -> bool { return obj>=med; } );
   }
 };

/* BinarySearch() */

template <class R,class Pred>
R BinarySearch_if(R &r,Pred pred) { return BinarySearchAlgo<R>::Find(r,pred); }

template <class R,class S>
R BinarySearch_less(R &r,const S &med) { return BinarySearchAlgo<R>::Find_less(r,med); }

template <class R,class S>
R BinarySearch_less_or_equal(R &r,const S &med) { return BinarySearchAlgo<R>::Find_less_or_equal(r,med); }

template <class R,class S>
R BinarySearch_greater(R &r,const S &med) { return BinarySearchAlgo<R>::Find_greater(r,med); }

template <class R,class S>
R BinarySearch_greater_or_equal(R &r,const S &med) { return BinarySearchAlgo<R>::Find_greater_or_equal(r,med); }

} // namespace Algon
} // namespace CCore
 
#endif
 

