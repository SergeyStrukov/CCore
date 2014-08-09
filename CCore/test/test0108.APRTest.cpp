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
#include <CCore/inc/Job.h>
#include <CCore/inc/Counters.h>
#include <CCore/inc/TaskHeap.h>

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
  
  Printf(Con,"testSet = #;\n",(gen.testSet()?"Ok":"Failed"));
  
  Int cap;
  
  gen.getCap(cap);
  
  Printf(out,"cap = #;\n\nbits= #;\n\ntime = #;\n\n",cap,cap.bitsOf().total(),PrintTime(t));
  
  PrintFile cpp("APRTestData.gen.cpp");
  
  gen.printCpp(cpp);
 }

/* class ConReport */

class ConReport
 {
   bool full;
   SecTimer timer;
   
  private:
   
   void time() const { Printf(Con,"time = #;\n",PrintTime(timer.get())); }
   
  public:
   
   explicit ConReport(bool full_=false) : full(full_) {}
   
   ~ConReport() { time(); }
  
   template <class Integer>
   void start(const Integer &N) const { Printf(Con,"N = #;\n",N); }
   
   void sanity(const char *msg) const { Printf(Con,"#;\n",msg); }
   
   void isSmallPrime() const { Printf(Con,"Prime from P or Q\n"); }
   
   void testP(unsigned p) const { Printf(Con,"p = #;\n",p); }
   
   void testQ(Math::APRTest::QType q) const{ if( full ) Printf(Con,"  q = #;\n",q); }
   
   template <class Integer>
   static Integer Fix(const Integer &a,const Integer &Nminus1)
    {
     if( a==Nminus1 ) return -1;
     
     return a;
    }
   
   template <class Integer>
   void cappa(PtrLen<const Integer> cappa,const Integer &Nminus1) const
    { 
     if( !full ) return;
     
     Integer minval;
     
     {
      auto r=cappa;
      
      minval=*r;
      
      for(++r; +r ;++r) Replace_min(minval,*r);
     }
     
     Printf(Con,"    cappa = {");
     
     {
      auto r=cappa;
      
      Printf(Con," #;",Fix(*r-minval,Nminus1));
      
      for(++r; +r ;++r) Printf(Con," , #;",Fix(*r-minval,Nminus1));
     }
     
     Printf(Con," }\n");
    }
   
   template <class Integer>
   void cappa2(const Integer &cappa,const Integer &Nminus1) const
    {
     if( !full ) return;
     
     Printf(Con,"    cappa = #;\n",Fix(cappa,Nminus1)); 
    }
   
   void startProbe() const { time(); Printf(Con,"Probe\n"); }
   
   template <class Integer>
   void probe(const Integer &cnt) const 
    { 
     Used(cnt); 
    }
   
   template <class Integer>
   void div(const Integer &D) const { Printf(Con,"\nHas divisor #;\n",D); }
   
   void hard() const { Printf(Con,"HardCase\n"); }
   
   void isPrime() const { Printf(Con,"\nPrime\n"); }
   
   void noPrime() const { Printf(Con,"No Prime\n"); }
 };

/* class FileReport */

enum PrimeCase
 {
  PrimeCase_Prime,
  PrimeCase_Hard,
  PrimeCase_2_3,
  PrimeCase_0_0,
  PrimeCase_Other,
  
  PrimeCaseLim
 };

const char * GetTextDesc(PrimeCase pcase)
 {
  switch( pcase )
    {
     case PrimeCase_Prime : return "Prime";
     case PrimeCase_Hard  : return "Hard";
     case PrimeCase_2_3   : return "2_3";
     case PrimeCase_0_0   : return "0-0";
     case PrimeCase_Other : return "Other";
   
     default: return "???";
    }
 }

using CaseCounters = Counters<PrimeCase,PrimeCaseLim> ;

class FileReport
 {
   PrintFile out;
   
   unsigned last_p;
   Math::APRTest::QType last_q;
  
   CaseCounters stat;
   
  private:
   
   void countPrime()
    {
     stat.count(PrimeCase_Prime);
    }
   
   void countHard()
    {
     stat.count(PrimeCase_Hard);
    }
   
   void countNoPrime(unsigned p,Math::APRTest::QType q)
    {
     if( p==0 && q==0 )
       {
        stat.count(PrimeCase_0_0);
       }
     else if( p==2 && q==3 )
       {
        stat.count(PrimeCase_2_3);
       }
     else
       {
        stat.count(PrimeCase_Other);
       }
    }
   
  public:
   
   explicit FileReport(StrLen file_name) : out(file_name) {}
   
   ~FileReport() { Printf(out,"\n#;\n\n#;\n\n",TextDivider(),stat); }
   
   CaseCounters getStat() const { return stat; }
  
   template <class Integer>
   void start(const Integer &N)
    { 
     out.flush(); 
     
     Printf(out,"\n#;\n\nN = #;\n",TextDivider(),N);
     
     last_p=0;
     last_q=0;
    }
   
   void sanity(const char *msg) { Printf(out,"#;\n",msg); }
   
   void isSmallPrime() { Printf(out,"Prime from P or Q\n"); }
   
   void testP(unsigned p) { Printf(out,"p = #;\n",p); last_p=p; }
   
   void testQ(Math::APRTest::QType q) { Printf(out,"  q = #;\n",q); last_q=q; }
   
   template <class Integer>
   static Integer Fix(const Integer &a,const Integer &Nminus1)
    {
     if( a==Nminus1 ) return -1;
     
     return a;
    }
   
   template <class Integer>
   void cappa(PtrLen<const Integer> cappa,const Integer &Nminus1)
    { 
     Integer minval;
     
     {
      auto r=cappa;
      
      minval=*r;
      
      for(++r; +r ;++r) Replace_min(minval,*r);
     }
     
     Printf(out,"    cappa = {");
     
     {
      auto r=cappa;
      
      Printf(out," #;",Fix(*r-minval,Nminus1));
      
      for(++r; +r ;++r) Printf(out," , #;",Fix(*r-minval,Nminus1));
     }
     
     Printf(out," }\n");
    }
   
   template <class Integer>
   void cappa2(const Integer &cappa,const Integer &Nminus1)
    {
     Printf(out,"    cappa = #;\n",Fix(cappa,Nminus1)); 
    }
   
   void startProbe() { Printf(out,"Probe\n"); }
   
   template <class Integer>
   void probe(const Integer &cnt) { Used(cnt); }
   
   template <class Integer>
   void div(const Integer &D) { Printf(out,"Has divisor #;\n",D); }
   
   void hard() { Printf(out,"HardCase\n"); countHard(); }
   
   void isPrime() { Printf(out,"Prime\n"); countPrime(); }
   
   void noPrime() { Printf(out,"No Prime\n"); countNoPrime(last_p,last_q); }
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
     
     RandomInt N(16,random);
     
     if( N<0) N.neg();
     
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

/* test6() */

void test6()
 {
  Math::APRTest::TestEngine<Int> test;
  FileReport report("report.txt");
  
  uint64 N=1000000000001;
  
  for(ulen cnt=10000000; cnt ;cnt--,N+=2)
    {
     test(N,report);
    }
 }

/* test7() */

void test7()
 {
  Math::APRTest::QType q=2311;
  Math::APRTest::QType gen=3;
  unsigned p=11;
  
  Math::APRTest::Jacobi jacobi(q,0,gen);
  Math::APRTest::AltJacobi alt_jacobi(q,0,gen);
  
  DynArray<Math::APRTest::QType> table(p*(p-2));
  DynArray<Math::APRTest::QType> alt_table(p*(p-2));
  
  jacobi(p,table.getPtr());
  alt_jacobi(p,alt_table.getPtr());
  
  if( Range(table).equal(Range(alt_table)) )
    Printf(Con,"Ok\n");
  else
    Printf(Con,"Failed\n");
 }

/* test8() */

using ParaInt = Math::Integer<Math::IntegerFastAlgo,RefArray,TaskHeapArrayAlgo> ;

using ParaTestEngine = Math::APRTest::ParaTestEngine<ParaInt,TaskHeapArrayAlgo> ;

void test8()
 {
  TaskHeap task_heap;
  ParaTestEngine test;
  
  // 1
  {
   Math::OctetInteger<ParaInt> P(Range(Crypton::DHModI::Mod));
   
   {
    ConReport report;
     
    Printf(Con,"ModI Prime = #;\n",test((ParaInt)P,report));
   }
   
   {
    ConReport report;
     
    Printf(Con,"ModI Prime/2 = #;\n",test(P>>1,report));
   }
  }
  
  // 2
  {
   Math::OctetInteger<ParaInt> P(Range(Crypton::DHModII::Mod));
   
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

/* test9() */

void test9(ulen nbits)
 {
  Printf(Con,"nbits = #;\n\n",nbits);
  
  TaskHeap task_heap;
  ParaTestEngine test;
  
  ulen noctets=nbits/8;
  
  DynArray<uint8> buf(noctets);
  auto data=Range(buf);
  PlatformRandom random;
  
  data.prefix(4).set(0xFF);
  data.suffix(4).set(0xFF);
  
  for(ulen cnt=1;;cnt++)
    {
     random.fill(data.inner(4,4));
     
     Int N=Math::OctetInteger<Int>(Range_const(data));
     
     if( Math::NoPrimeTest<Int>::RandomTest(N,30,random) )
       {
        Printf(Con,"#; Probable Prime\n",cnt);
        
        Math::APRTest::TestResult result;
        
        {
         ConReport report;
         
         result=test(Math::OctetInteger<ParaInt>(Range_const(data)),report);
        }
        
        Printf(Con,"\n\n");
        
        if( !result ) return;
       }
     else
       {
        Printf(Con,"#;\r",cnt);
       }
    }
 }

void test9()
 {
  test9(1u<<10);
  test9(1u<<11);
  test9(1u<<12);
  test9(1u<<13);
  test9(1u<<14);
 }

} // namespace Private_0108
 
using namespace Private_0108; 
 
/* Testit<108> */ 

template<>
const char *const Testit<108>::Name="Test108 APRTest";

template<>
bool Testit<108>::Main() 
 {
  DestroyPerTask dpt;
  Job::Init init;
  
  //test1();
  //test2();
  //test3();
  //test4();
  //test5();
  //test6();
  //test7();
  //test8();
  test9();
  
  return true;
 }
 
} // namespace App
 
