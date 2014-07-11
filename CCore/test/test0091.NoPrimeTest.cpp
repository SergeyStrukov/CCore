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

using RandomInt = Math::RandomInteger<Int> ;

/* test1() */

void test1()
 {
  PlatformRandom random;
  
  for(ulen cnt=1000; cnt ;cnt--)
    {
     Int P=RandomInt(16,random);
     
     if( P<0 ) P=-P;
     
     Math::ModEngine<Int> engine(P);
     
     Int P2=P.sq();

     for(ulen cnt=1000; cnt ;cnt--)
       {
        Int a=RandomInt(32,random);
        
        if( a<0 ) a=-a;
        
        a%=P2;
        
        if( engine.mod(a)!=(a%P) )
          {
           Printf(Exception,"failed");
          }
       }
    }
 }

/* test2() */

void test2()
 {
  PlatformRandom random;
  
  for(ulen cnt=1000; cnt ;cnt--)
    {
     Int P=RandomInt(16,random);
     Int a=RandomInt(16,random);
     
     if( P<0 ) P=-P;
     
     if( a<0 ) a=-a;
     
     a%=P;
     
     Math::NoPrimeTest<Int>::ExpEngine engine(P);
     
     Math::ModEngine<Int> mod_engine(P);
     
     if( engine.pow(a)!=mod_engine.pow(a,P>>1) ) 
       {
        Printf(Exception,"failed");
       }
    }
 }

/* test3() */

void test3()
 {
  PlatformRandom random;
  
  for(ulen cnt=10000; cnt ;cnt--)
    {
     Printf(Con,"cnt = #;   \r",cnt);
     
     RandomInt a(32,random);
     RandomInt b(32,random);
     
     Int P=a*b;

     if( P<0 ) P=-P;
     
     if( Math::NoPrimeTest<Int>::RandomTest(P,10,random) ) 
       {
        Printf(Con,"\nPassed 10\n");
        
        if( Math::NoPrimeTest<Int>::RandomTest(P,20,random) ) Printf(Con,"  Passed 30\n");
       }
    }
  
  Putch(Con,'\n');
 }

/* test4() */

void test4()
 {
  PlatformRandom random;
  SecTimer timer;
  
  for(ulen cnt=1;;cnt++)
    {
     Printf(Con,"cnt = #;\r",cnt);
    
     Int P=RandomInt(32,random);
     
     if( P<0 ) P=-P;
     
     if( P.isEven() ) P=P+1;
     
     if( Math::NoPrimeTest<Int>::RandomTest(P,30,random) ) 
       {
        Printf(Con,"\ntime = #;\nP = #;\nbits = #;\n",PrintTime(timer.get()),P,P.bitsOf().total());
        
        return;
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
 
