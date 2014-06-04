/* test0091.NoPrimeTest.cpp */ 
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

#include <CCore/inc/math/Integer.h>
#include <CCore/inc/math/IntegerFastAlgo.h>
#include <CCore/inc/math/NoPrimeTest.h>

#include <CCore/inc/PlatformRandom.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/PrintTime.h>

namespace App {

namespace Private_0091 {

/* types */

using Int = Math::Integer<Math::IntegerFastAlgo> ;

using RandomInt = Math::RandomInteger<Math::IntegerFastAlgo> ;

/* test1() */

void test1()
 {
  Math::NoPrimeTest<Int>::RandomTest test;
  PlatformRandom random;
  
  for(ulen cnt=100; cnt ;cnt--)
    {
     RandomInt a(32,random);
     RandomInt b(32,random);
     
     Int P=a*b;

     if( P<0 ) P=-P;
     
     if( test.test(P,10) ) 
       {
        Printf(Con,"Passed 10\n");
        
        if( test.test(P,20) ) Printf(Con,"  Passed 30\n");
       }
    }
 }

/* test2() */

void test2()
 {
  Math::NoPrimeTest<Int>::RandomTest test;
  PlatformRandom random;
  SecTimer timer;
  
  for(ulen cnt=1;;cnt++)
    {
     Int P=RandomInt(32,random);
     
     if( P<0 ) P=-P;
     
     Printf(Con,"cnt = #;\r",cnt);
     
     if( test.test(P,30) ) 
       {
        Printf(Con,"\ntime = #;\nP = #;\n",PrintTime(timer.get()),P);
        
        return;
       }
    }
 }

/* test3() */

void test3()
 {
  PlatformRandom random;
  
  for(ulen cnt=1000; cnt ;cnt--)
    {
     Int P=RandomInt(16,random);
     Int a=RandomInt(16,random);
     
     if( P<0 ) P=-P;
     
     if( a<0 ) a=-a;
     
     a%=P;
     
     if( Math::NoPrimeTest<Int>::ModExp(a,P)!=Math::NoPrimeTest<Int>::ModExp2(a,P) ) 
       {
        Printf(Exception,"failed");
       }
    }
 }

/* test4() */

void test4()
 {
  PlatformRandom random;
  
  for(ulen cnt=1000; cnt ;cnt--)
    {
     Int P=RandomInt(16,random);
     
     if( P<0 ) P=-P;
     
     Math::NoPrimeTest<Int>::ModEngine engine(P);
     
     Int P2=P.sq();

     for(ulen cnt=1000; cnt ;cnt--)
       {
        Int a=RandomInt(16,random);
        
        if( a<0 ) a=-a;
        
        a%=P2;
        
        if( engine.mod(a)!=(a%P) )
          {
           Printf(Exception,"failed");
          }
       }
    }
 }

} // namespace Private_0091
 
using namespace Private_0091; 
 
/* Testit<91> */ 

template<>
const char *const Testit<91>::Name="Test91 NoPrimeTest";

template<>
bool Testit<91>::Main() 
 {
  //test1();
  //test2();
  //test3();
  //test4();
  
  return true;
 }
 
} // namespace App
 
