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

#include <CCore/inc/crypton/DHExp.h>

namespace App {

namespace Private_0108 {

/* type Int */

using Int       = Math::Integer<Math::IntegerFastAlgo> ;
using RandomInt = Math::RandomInteger<Int> ;

/* test1() */

void test1()
 {
  const ulen MaxN = Math::APRTest::TestData::MaxN ;
  
  PrintFile out("APRTestData.gen.cpp");
  
  Math::APRTest::PrepareData<Int>(out,MaxN, [] (ulen n) { Printf(Con,"Data #;\n",n); } );
 }

/* test2() */

class Report
 {
   PrintFile out;
   
  public:
   
   explicit Report(StrLen file_name) : out(file_name) {}
  
   template <class ... TT>
   void operator () (const char *format,TT && ... tt)
    {
     Printf(out,format, std::forward<TT>(tt)... );
    }
 };

void test2()
 {
  Math::APRTest::TestEngine<Int> test(5);
  Report report("report.txt");
  
  Printf(Con,"cap = #;\n",test.getCap());
  
  Int a=Int(999983)*999979;
  
  Printf(Con,"#;\nis #;\n",a,test(a,report));
 }

/* test3() */

class NoReport
 {
  public:
   
   NoReport() {}
  
   template <class ... TT>
   void operator () (const char *,TT && ...)
    {
    }
 };

void test3()
 {
  PlatformRandom random;
  Math::APRTest::TestEngine<Int> test1(7);
  NoReport report;
  
  Int cap=test1.getCap();
  
  Printf(Con,"cap = #;\ncap bits = #;\n",cap,cap.bitsOf().total());
  
  PrintFile out("report.txt");

  for(ulen cnt=1;;cnt++)
    {
     Printf(Con,"cnt = #;\r",cnt);
     
     RandomInt N(32,random);
     
     if( N.sign()<0) N.neg();
     
     if( N.isEven() ) N+=1;
     
     if( Math::NoPrimeTest<Int>::RandomTest(N,30,random) )
       Printf(out,"ProbablePrime");
     else
       Printf(out,"NoPrime");
     
     auto result=test1(N,report);
     
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

class ConReport
 {
  public:
   
   ConReport() {}
  
   template <class ... TT>
   void operator () (const char *format,TT && ... tt)
    {
     Printf(Con,format, std::forward<TT>(tt)... );
    }
 };

void test4()
 {
  PlatformRandom random;
  Math::APRTest::TestEngine<Int> test2(7);
  ConReport report;
  
  Int cap=test2.getCap();
  
  ulen bits=cap.bitsOf().total();
  
  Printf(Con,"cap bits = #;\n",bits);
  
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
   
   Math::APRTest::TestEngine<Int> test(7);
   
   {
    Report report("ModI_P.txt");
     
    Printf(Con,"ModI Prime = #;\n",test(P,report));
   }
   
   {
    Report report("ModI_P2.txt");
     
    Printf(Con,"ModI Prime/2 = #;\n",test(P>>1,report));
   }
  }
  
  // 2
  {
   Math::OctetInteger<Int> P(Range(Crypton::DHModII::Mod));
   
   Math::APRTest::TestEngine<Int> test(8);
   
   {
    Report report("ModII_P.txt");
     
    Printf(Con,"ModII Prime = #;\n",test(P,report));
   }
   
   {
    Report report("ModII_P2.txt");
     
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
  test5();
  
  return true;
 }
 
} // namespace App
 
