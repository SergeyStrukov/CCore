/* SimpleRotate.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_algon_SimpleRotate_h
#define CCore_inc_algon_SimpleRotate_h
 
#include <CCore/inc/algon/BaseRangeAlgo.h>

namespace CCore {
namespace Algon {

/* classes */

template <class R,class Algo=BaseRangeAlgo<R> > struct SimpleRotateAlgo;

/* RangeRotateLeft() */

template <class R>
void RangeRotateLeft(R r) { SimpleRotateAlgo<R>::RotateLeft(r); }

/* RangeRotateRight() */

template <class R>
void RangeRotateRight(R r) { SimpleRotateAlgo<R>::RotateRight(r); }

/* struct SimpleRotateAlgo<R,Algo> */

template <class R,class Algo> 
struct SimpleRotateAlgo : Algo
 {
  using Algo::GetLen;
  using Algo::Reverse;
  
  static void RotateLeft(R r)
   {
    for(; GetLen(r)>1 ;++r) Swap(r[0],r[1]);
   }
  
  static void RotateRight(R r)
   {
    RangeRotateLeft(Reverse(r));
   }
 }; 

} // namespace Algon
} // namespace CCore
 
#endif
 

