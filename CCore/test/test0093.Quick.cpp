/* test0093.Quick.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/math/IntegerSlowAlgo.h>

#include <CCore/inc/Random.h>

namespace App {

namespace Private_0093 {

/* consts */

const ulen Count = 100000000 ;

/* test1() */

template <class UInt>
void test1()
 {
  Random random;
  
  for(ulen cnt=Count; cnt ;cnt--)
    {
     UInt a=random.next_uint<UInt>();
     UInt b=random.next_uint<UInt>();
     
     typename UIntFunc<UInt>::Mul mul1(a,b);
     
     typename Math::IntegerSlowMulAlgo<UInt>::DoubleMul mul2(a,b);
     
     if( mul1.hi!=mul2.hi || mul1.lo!=mul2.lo )
       {
        Printf(Exception,"Fail 1");
       }
    }
 }

/* test2() */

template <class UInt>
void test2()
 {
  Random random;
  
  for(ulen cnt=Count; cnt ;cnt--)
    {
     UInt hi=random.next_uint<UInt>();
     UInt lo=random.next_uint<UInt>();
     UInt den=random.next_uint<UInt>();
     
     if( den==0 ) den=1;
     
     hi%=den;
     
     typename UIntFunc<UInt>::DivMod res(hi,lo,den);
     
     if( res.div!=UIntDiv(hi,lo,den) )
       {
        Printf(Exception,"Fail 2");
       }
     
     if( res.mod!=UIntMod(hi,lo,den) )
       {
        Printf(Exception,"Fail 3");
       }
     
     typename UIntFunc<UInt>::Mul mul(den,res.div);
     
     mul.hi+=UIntAdd(mul.lo,res.mod);
     
     if( mul.hi!=hi || mul.lo!=lo )
       {
        Printf(Exception,"Fail 4");
       }
    }
 }

/* test3() */

template <class UInt>
void test3()
 {
  Random random;
  
  for(ulen cnt=Count; cnt ;cnt--)
    {
     UInt a=random.next_uint<UInt>();
     UInt b=random.next_uint<UInt>();
     UInt s=random.next_uint<UInt>();
     UInt mod=random.next_uint<UInt>();
     
     if( mod==0 ) mod=1;
     
     a%=mod;
     b%=mod;
     s%=mod;
     
     typename UIntFunc<UInt>::Mul mul(a,b);
     
     if( UIntMod(mul.hi,mul.lo,mod)!=UIntModMul(a,b,mod) )
       {
        Printf(Exception,"Fail 5");
       }
     
     mul.hi+=UIntAdd(mul.lo,s);
     
     if( UIntMod(mul.hi,mul.lo,mod)!=UIntModMac(s,a,b,mod) )
       {
        Printf(Exception,"Fail 6");
       }
    }
 }

/* test() */

template <class UInt>
void test()
 {
  test1<UInt>();
  test2<UInt>();
  test3<UInt>();
 }

} // namespace Private_0093
 
using namespace Private_0093; 
 
/* Testit<93> */ 

template<>
const char *const Testit<93>::Name="Test93 Quick";

template<>
bool Testit<93>::Main() 
 {
  test<uint8>();
  test<uint16>();
  test<uint32>();
  test<uint64>();
  
  return true;
 }
 
} // namespace App
 
