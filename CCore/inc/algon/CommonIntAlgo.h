/* CommonIntAlgo.h */ 
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

#ifndef CCore_inc_algon_CommonIntAlgo_h
#define CCore_inc_algon_CommonIntAlgo_h

#include <CCore/inc/Swap.h>
 
namespace CCore {
namespace Algon {

/* classes */

template <class UInt> struct BitIntAlgo;

template <class UInt,class Algo=BitIntAlgo<UInt> > struct CommonIntAlgo;

/* struct BitIntAlgo<UInt> */

template <class UInt> 
struct BitIntAlgo
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::Algon::BitIntAlgo<UInt> : UInt must be an unsigned integral type");
  
  static bool IsEven(UInt a) { return !(a&UInt(1)); }
  
  static unsigned BitScan(UInt a) // a!=0
   {
    unsigned ret=0;
    
    while( IsEven(a) )
      {
       a>>=1;
       ret++;
      }
    
    return ret;
   }
  
  static UInt OddPart(UInt a) // a!=0
   {
    while( IsEven(a) ) a>>=1;
    
    return a;
   }
 };

/* struct CommonIntAlgo<UInt,Algo> */

template <class UInt,class Algo> 
struct CommonIntAlgo : Algo
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::Algon::CommonIntAlgo<UInt> : UInt must be an unsigned integral type");

  using Algo::BitScan;
  using Algo::OddPart;
  
  static void Order(UInt &a,UInt &b)
   {
    if( a>b ) CopySwap(a,b);
   }
  
  static UInt GCD(UInt a,UInt b)
   {
    if( !a ) return b;
    if( !b ) return a;
    
    unsigned s=BitScan(a|b);
    
    a=OddPart(a>>s);
    b=OddPart(b>>s);
    
    for(;;)
      {
       Order(a,b);
       
       if( !(b-=a) ) return a<<s;
       
       b=OddPart(b>>1);
      }
   }
  
  static UInt LCM(UInt a,UInt b) // no overflow check
   {
    UInt d=GCD(a,b);
    
    if( !d ) return 0;
    
    return (a/d)*b;
   }
 };

/* functions */

template <class UInt>
UInt GCD(UInt a,UInt b) { return CommonIntAlgo<UInt>::GCD(a,b); }

template <class UInt>
UInt LCM(UInt a,UInt b) { return CommonIntAlgo<UInt>::LCM(a,b); }

} // namespace Algon
} // namespace CCore
 
#endif
 

