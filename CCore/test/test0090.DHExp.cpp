/* test0090.DHExp.cpp */ 
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

#include <CCore/inc/crypton/DHExp.h>
#include <CCore/inc/math/Integer.h>
#include <CCore/inc/math/IntegerFastAlgo.h>
#include <CCore/inc/math/NoPrimeTest.h>

namespace App {

namespace Private_0090 {

/* types */

using Int = Math::Integer<Math::IntegerFastAlgo> ;

/* class ByteBuilder */

class ByteBuilder
 {
   const uint8 *ptr;
   ulen len;
   
   ulen result;
   
  private: 
  
   static const ulen Delta = Int::UnitBits/8 ;
   
   static_assert( (Int::UnitBits%8)==0 ,"Bad bits");
   
   template <class R>
   static Int::Unit Build(R r)
    {
     Int::Unit ret=0;
     
     for(unsigned off=0; +r ;++r,off+=8)
       {
        ret|=(Int::Unit(*r)<<off);
       }
     
     return ret;
    }
   
   void build(Int::Unit *out) const
    {
     auto r=Range(ptr,len);
     
     while( r.len>=Delta ) *(out++)=Build(r+=Delta);
     
     *out=Build(r);
    }
   
  public:
   
   ByteBuilder(const uint8 *ptr_,ulen len_) 
    : ptr(ptr_),
      len(len_) 
    {
     result=len/Delta+1;
    }
   
   ulen getLen() const { return result; }
   
   PtrLen<Int::Unit> operator () (Place<void> place) const
    {
     Int::Unit *base=place;
     
     build(base);
     
     return Range(base,result);
    }
 };

/* test1() */

template <class DHMod>
void test1(StrLen title)
 {
  Printf(Con,"#;\n\n",Title(title));
  
  Math::NoPrimeTest<Int>::RandomTest test; 
  
  Int P(DoBuild,ByteBuilder(DHMod::Mod,DHMod::GLen));
  Int Q=P>>1;

  if( test.test(P,100) ) Printf(Con,"P is probably prime\n"); else Printf(Con,"P is not prime\n");
  
  if( test.test(Q,100) ) Printf(Con,"Q is probably prime\n"); else Printf(Con,"Q is not prime\n");
  
  Printf(Con,"\n");
 }

} // namespace Private_0090
 
using namespace Private_0090; 
 
/* Testit<90> */ 

template<>
const char *const Testit<90>::Name="Test90 DHExp";

template<>
bool Testit<90>::Main() 
 {
  test1<Crypton::DHModI>("DH Group I module");
  test1<Crypton::DHModII>("DH Group II module");
  
  return true;
 }
 
} // namespace App
 
