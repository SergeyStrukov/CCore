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
  using Algo::GetLen;
  using Algo::Half;
  using Algo::SplitBefore;
  using Algo::SplitAfter;
 
  template <class Pred>
  static R Find(R &r,Pred pred) // pred(R) is 0,0,0,...,0,1,1,...
   {
    R temp=r;
    
    if( !temp ) return r;
    
    // 0,0,... temp 1,1,...
    
    while( GetLen(temp)>1 )
      {
       R prefix=Half(temp);
      
       if( pred(*temp) )
         { 
          temp=prefix;
         }
       else
         {
          if( GetLen(temp)==1 ) return SplitAfter(r,temp);
           
          ++temp;
         } 
      }
    
    if( pred(*temp) )
      {
       return SplitBefore(r,temp);
      }
    else
      {
       return SplitAfter(r,temp);
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
 

