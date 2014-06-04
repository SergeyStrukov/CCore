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
#include <CCore/inc/math/IntegerOctetBuilder.h>
#include <CCore/inc/math/NoPrimeTest.h>

namespace App {

namespace Private_0090 {

/* types */

using Int = Math::Integer<Math::IntegerFastAlgo> ;

using Builder = Math::IntegerOctetBuilder<Int> ;

/* test1() */

template <class DHMod>
void test1(StrLen title)
 {
  Printf(Con,"#;\n\n",Title(title));
  
  Math::NoPrimeTest<Int>::RandomTest test; 
  
  Int P(DoBuild,Builder(Range(DHMod::Mod)));
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
 
