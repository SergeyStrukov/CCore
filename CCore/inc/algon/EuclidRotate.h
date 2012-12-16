/* EuclidRotate.h */ 
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

#ifndef CCore_inc_algon_EuclidRotate_h
#define CCore_inc_algon_EuclidRotate_h
 
#include <CCore/inc/algon/BaseRangeAlgo.h>

namespace CCore {
namespace Algon {

/* classes */

template <class R,class Algo=BaseRangeAlgo<R> > struct EuclidRotateAlgo; 

/* struct EuclidRotateAlgo<R,Algo> */

template <class R,class Algo> 
struct EuclidRotateAlgo : Algo
 {
  typedef typename Algo::LenType LenType;
  
  using Algo::GetLen;
  using Algo::GetPrefix;
  using Algo::GetSuffix;
  using Algo::RangeSwap;
  
  static void Rotate(R r,LenType prefix,LenType suffix)
   {
    for(;;)
      if( prefix>=suffix )
        {
         if( !suffix ) return;
      
         R a=GetSuffix(r,suffix);
         R b=GetPrefix(r,suffix);
         R c=GetSuffix(r,prefix);
       
         RangeSwap(a,b);
       
         r=c;
         prefix-=suffix;
        }
      else
        {
         if( !prefix ) return;
       
         R a=GetPrefix(r,prefix);
         R b=GetSuffix(r,prefix);
         R c=GetPrefix(r,suffix);
       
         RangeSwap(a,b);
       
         r=c;
         suffix-=prefix;
        }
   }
  
  static void Rotate_prefix(R r,LenType prefix)
   {
    Rotate(r,prefix,GetLen(r)-prefix); 
   }
  
  static void Rotate_suffix(R r,LenType suffix)
   {
    Rotate(r,GetLen(r)-suffix,suffix); 
   }
 };
 
/* EuclidRotate...() */

template <class R,class Len>
void EuclidRotate_prefix(R r,Len prefix) { EuclidRotateAlgo<R>::Rotate_prefix(r,prefix); }

template <class R,class Len>
void EuclidRotate_suffix(R r,Len suffix) { EuclidRotateAlgo<R>::Rotate_suffix(r,suffix); }

} // namespace Algon
} // namespace CCore
 
#endif
 

