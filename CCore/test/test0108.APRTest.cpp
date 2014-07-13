/* test0108.APRTest.cpp */ 
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

#include <CCore/inc/PrintTitle.h>
#include <CCore/inc/PlatformRandom.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/PrintTime.h>

#include <CCore/inc/math/NoPrimeTest.h>
#include <CCore/inc/math/APRTest.h>
#include <CCore/inc/math/IntegerFastAlgo.h>
#include <CCore/inc/math/IntegerOctetBuilder.h>

#include <CCore/inc/crypton/DHExp.h>

namespace App {

namespace Private_0108 {

/* type Int */

using Int       = Math::Integer<Math::IntegerFastAlgo> ;
using RandomInt = Math::RandomInteger<Int> ;

/* test1() */

void test1()
 {
  PrintFile out("APRTest.txt");
  
  SecTimer timer;
  
  Math::APRTest::DataGen gen(Math::APRTest::TestData::MaxN);
  
  auto t=timer.get();
  
  Putobj(out,gen);
  
  Int cap;
  
  gen.getCap(cap);
  
  Printf(out,"cap = #;\n\nbits= #;\n\ntime = #;\n\n",cap,cap.bitsOf().total(),PrintTime(t));
  
  PrintFile cpp("APRTestData.gen.cpp");
  
  gen.printCpp(cpp);
 }

/* class ConReport */

class ConReport
 {
  public:
   
   ConReport() {}
  
   template <class Integer>
   void start(Integer N) { Printf(Con,"N = #;\n",N); }
   
   void sanity(const char *msg) { Printf(Con,"#;\n",msg); }
   
   void test(unsigned p) { Printf(Con,"p = #;\n",p); }
   
   void startProbe() { Printf(Con,"Probe\n"); }
   
   template <class Integer>
   void probe(Integer cnt) { Printf(Con,"#;          \r",cnt); }
   
   template <class Integer>
   void div(Integer D) { Printf(Con,"\nHas divisor #;\n",D); }
   
   void hard() { Printf(Con,"\nHardCase\n"); }
   
   void isPrime() { Printf(Con,"\nPrime\n"); }
   
   void noPrime() { Printf(Con,"\nNo Prime\n"); }
 };

/* test2() */

void test2()
 {
  Math::APRTest::TestEngine<Int> test;
  ConReport report;
  
  Int a=Int(999983)*999979;
  
  Printf(Con,"#;\nis #;\n",a,test(a,report));
 }

/* test3() */

void test3()
 {
  PlatformRandom random;
  Math::APRTest::TestEngine<Int> test;
  ConReport report;
  
  PrintFile out("report.txt");

  for(ulen cnt=1;;cnt++)
    {
     Printf(Con,"cnt = #;\n",cnt);
     
     RandomInt N(32,random);
     
     if( N.sign()<0) N.neg();
     
     if( N.isEven() ) N+=1;
     
     if( Math::NoPrimeTest<Int>::RandomTest(N,30,random) )
       Printf(out,"ProbablePrime");
     else
       Printf(out,"NoPrime");
     
     auto result=test(N,report);
     
     Printf(out," #;\n",result);
     
     if( !result )
       {
        Printf(out,"\n#;\n",N);
        
        Printf(Con,"\n\n#;\n\n",N);
       
        break;
       }
    }
 }

/* test4() */

void test4()
 {
  PlatformRandom random;
  Math::APRTest::TestEngine<Int> test2;
  ConReport report;
  
  ulen bits=1024;
  
  for(ulen cnt=1;;cnt++)
    {
     Printf(Con,"cnt = #;\r",cnt);
     
     RandomInt N(bits/Int::UnitBits,random);
     
     if( N.sign()<0) N.neg();
     
     if( N.isEven() ) N+=1;
     
     if( Math::NoPrimeTest<Int>::RandomTest(N,30,random) )
       {
        Printf(Con,"\nProbablePrime\n");
        
        SecTimer timer;
        
        auto result=test2(N,report);
        
        if( !result )
          {
           Printf(Con,"\n#;\n\nbits = #;\ntime = #;\n\n",N,N.bitsOf().total(),PrintTime(timer.get()));
          
           break;
          }
       } 
    }
 }

/* test5() */

void test5()
 {
  // 1
  {
   Math::OctetInteger<Int> P(Range(Crypton::DHModI::Mod));
   
   Math::APRTest::TestEngine<Int> test;
   
   {
    ConReport report;
     
    Printf(Con,"ModI Prime = #;\n",test(P,report));
   }
   
   {
    ConReport report;
     
    Printf(Con,"ModI Prime/2 = #;\n",test(P>>1,report));
   }
  }
  
  // 2
  {
   Math::OctetInteger<Int> P(Range(Crypton::DHModII::Mod));
   
   Math::APRTest::TestEngine<Int> test;
   
   {
    ConReport report;
     
    Printf(Con,"ModII Prime = #;\n",test(P,report));
   }
   
   {
    ConReport report;
     
    Printf(Con,"ModII Prime/2 = #;\n",test(P>>1,report));
   }
  }
 }

} // namespace Private_0108
 
using namespace Private_0108; 
 
/* Testit<108> */ 

template<>
const char *const Testit<108>::Name="Test108 APRTest";

template<>
bool Testit<108>::Main() 
 {
  //test1();
  //test2();
  //test3();
  //test4();
  //test5();
  
  return true;
 }
 
} // namespace App
 
