/* testIntAlgo.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_test_testIntAlgo_h
#define CCore_test_testIntAlgo_h

#include <CCore/test/testIntBase.h>

#include <CCore/inc/math/IntegerSlowAlgo.h>

namespace App {

/* classes */

template <class Algo> class TestIntegerAlgo;

template <class Algo,class Alt> class TestIntegerAlgo2;

/* class TestIntegerAlgo<Algo> */

template <class Algo>
class TestIntegerAlgo : TestIntBase
 {
   typedef typename Algo::Unit Unit;
   
   typedef Math::IntegerSlowAlgo<Unit> Slow;
   
   static const unsigned Len = 100 ;
   static const unsigned GLen = 10 ;
   
   static_assert( Meta::IsUInt<Unit>::Ret ,"Unit must be an unsigned integral type");
   
  private: 
   
   Unit a[Len+GLen];
   ulen na;
   Unit b[Len];
   ulen nb;
 
   Unit c[2*Len+GLen];
   ulen nc;
   Unit d[2*Len];
   Unit e[2*Len];
   
   Unit g[GLen];
   
  private: 
   
   struct AddC
    {
     Unit d;
     bool c;
     
     AddC(Unit a,Unit b,bool c_)
      {
       d=a+b+c_;
 
       if( c_ )
         c=( a>=Unit(-1)-b );
       else
         c=( a>Unit(-1)-b );
      }
    };
   
   static Unit LShift(Unit hi,Unit lo,unsigned shift)
    {
     return Unit( (hi<<shift)|(lo>>(Algo::UnitBits-shift)) );
    }
   
   static Unit RShift(Unit hi,Unit lo,unsigned shift)
    {
     return Unit( (hi<<(Algo::UnitBits-shift))|(lo>>shift) );
    }
   
  private: 
   
   void fill_a()
    {
     na=select(0,Len);
     
     fill(Range(a,na));
    }
   
   void fill_b()
    {
     nb=select(0,Len);
     
     fill(Range(b,nb));
    }
   
   void fill_bna()
    {
     nb=na;
     
     fill(Range(b,nb));
    }
   
   void fill_ab()
    {
     fill_a();
     fill_bna();
    }

   void fill_ag()
    {
     na=select(0,Len);
     
     fill(Range(a,na+GLen));
     
     Range(g,GLen).copy(a+na);
    }
   
   void fill_ad()
    {
     fill_ag();
     
     Range(a,na).copyTo(d);
    }
   
   void fill_abd()
    {
     fill_ad();
     fill_bna();
    }
   
   void unit_bna(Unit u)
    {
     nb=na;
     
     b[0]=u;
     
     Algo::Null(b+1,nb-1);
    }
   
   void guard(const char *msg)
    {
     if( !Range(g,GLen).equal(a+na) ) Error(msg);
    }
   
   void same(const char *msg)
    {
     if( !Range(a,na).equal(d) ) Error(msg);
    }
   
   void same(Unit c,Unit c1,const char *msg)
    {
     if( c!=c1 || !Range(a,na).equal(d) ) Error(msg);
    }
   
   void same_b(Unit c,Unit c1,const char *msg)
    {
     if( c!=c1 || !Range(a,na).equal(b) ) Error(msg);
    }
      
   void fill_c(ulen n)
    {
     nc=n;
     
     fill(Range(c,nc+GLen));
     
     Range(c+nc,GLen).copyTo(g);
    }
   
   void fill_abc()
    {
     fill_a();
     fill_b();
     fill_c(na+nb);
    }
   
   void guard_c(const char *msg)
    {
     if( !Range(g,GLen).equal(c+nc) ) Error(msg);
    }
   
   void fill_a2c()
    {
     fill_a();
     fill_c(2*na);
    }
   
  private: 
   
   static void test0()
    {
     Unit a=1;
     unsigned n=0;
     
     for(; a ;a<<=1,n++);
     
     if( n!=Algo::UnitBits ) Error("Algo::UnitBits");
     
     Unit b=Algo::MaxUnit;
     
     if( Unit(b+1) ) Error("Algo::MaxUnit");
     
     Unit c=Algo::MSBit;
     
     if( c==0 || ((c<<1)&b) || (c&(c-1)) ) Error("Algo::MSBit");
    }
   
   void test1()
    {
     Unit a;
     
     fill_unit(a);
     
     Unit b=Algo::SignExt(a);
     
     if( (a&Algo::MSBit) )
       {
        if( b!=Algo::MaxUnit ) Error("Algo::SignExt(<0)");
       }
     else
       {
        if( b!=0 ) Error("Algo::SignExt(>=0)");
       }
    }
   
   void test2()
    {
     Unit a;
     Unit b;
     
     fill_unit(a);
     fill_unit(b);
     
     if( a&Algo::MSBit )
       {
        if( b&Algo::MSBit )
          {
           if( Algo::SignCmp(a,b)!=LessCmp(a,b) ) Error("Algo::SignCmp(<0,<0)");
          }
        else
          {
           if( Algo::SignCmp(a,b)!=CmpLess ) Error("Algo::SignCmp(<0,>=0)");
          }
       }
     else
       {
        if( b&Algo::MSBit )
          {
           if( Algo::SignCmp(a,b)!=CmpGreater ) Error("Algo::SignCmp(>=0,<0)");
          }
        else
          {
           if( Algo::SignCmp(a,b)!=LessCmp(a,b) ) Error("Algo::SignCmp(>=0,>=0)");
          }
       }
    }
   
   void test3()
    {
     Unit a;
     
     fill_unit(a);
     
     unsigned n=Algo::CountZeroMSB(a);
 
     if( a )
       {
        Unit b=Algo::MSBit;
     
        for(; n ;n--,b>>=1) if( a&b ) Error("Algo::CountZeroMSB 1");
     
        if( (a&b)==0 ) Error("Algo::CountZeroMSB 2");
       }
     else
       {
        if( n!=Algo::UnitBits ) Error("Algo::CountZeroMSB 3");
       }
    }
   
   void test4()
    {
     Unit a;
     Unit b;
     Unit d;
     
     fill_unit(a);
     fill_unit(b);
     fill_unit(d);
     
     if( b>=d ) return;
     
     Unit c=Algo::DoubleUDiv(b,a,d);
     
     typename Slow::DoubleMul p(d,c);
     
     if( p.lo<=a )
       {
        if( p.hi!=b ) Error("Algo::DoubleUDiv 1");
        
        if( a-p.lo>=d ) Error("Algo::DoubleUDiv 2");
       }
     else
       {
        if( p.hi+1!=b || b==0 ) Error("Algo::DoubleUDiv 3");
        
        if( Unit(a-p.lo)>=d ) Error("Algo::DoubleUDiv 4");
       }
    }
   
   void test5()
    {
     fill_a();
     
     if( Algo::SignExt(a,na)!=Slow::SignExt(a,na) ) Error("Algo::SignExt(a,na)");
    }
   
   void test6()
    {
     fill_a();
     
     if( Algo::USign(a,na)!=Slow::USign(a,na) ) Error("Algo::USign(a,na)");
    }
   
   void test7()
    {
     fill_a();
     
     if( Algo::Sign(a,na)!=Slow::Sign(a,na) ) Error("Algo::Sign(a,na)");
    }
   
   void test8()
    {
     fill_ab();
     
     if( Algo::UCmp(a,b,na)!=Slow::UCmp(a,b,na) ) Error("Algo::UCmp(a,b,nab)");
    }
   
   void test9()
    {
     fill_a();
     fill_b();
     
     if( Algo::UCmp(a,na,b,nb)!=Slow::UCmp(a,na,b,nb) ) Error("Algo::UCmp(a,na,b,nb)");
    }
   
   void test10()
    {
     fill_ab();
     
     if( Algo::Cmp(a,b,na)!=Slow::Cmp(a,b,na) ) Error("Algo::Cmp(a,b,nab)");
    }
   
   void test11()
    {
     fill_a();
     fill_b();
     
     if( Algo::Cmp(a,na,b,nb)!=Slow::Cmp(a,na,b,nb) ) Error("Algo::Cmp(a,na,b,nb)");
    }
   
   void test12()
    {
     fill_a();
     
     ulen n=Algo::UNormalize(a,na);
     
     if( n>na ) Error("Algo::UNormalize 1");
     
     if( n>0 && a[n-1]==0 ) Error("Algo::UNormalize 2");
     
     for(; n<na ;n++) if( a[n] ) Error("Algo::UNormalize 3");
    }
   
   void test13()
    {
     fill_a();
     
     ulen n=Algo::Normalize(a,na);
     
     if( n>na ) Error("Algo::Normalize 1");
     
     Unit c=Algo::SignExt(a,n);
     
     if( n>0 && a[n-1]==Algo::SignExt(a,n-1) ) Error("Algo::Normalize 2");
     
     for(; n<na ;n++) if( a[n]!=c ) Error("Algo::Normalize 3");
    }
   
   void test14()
    {
     fill_abd();
     
     Unit c=Algo::UAdd(a,b,na);
     
     guard("Algo::UAdd guard");
     
     Unit c1=Slow::UAdd(d,b,na);
     
     same(c,c1,"Algo::UAdd same");
    }
   
   void test15()
    {
     fill_abd();
     
     Unit c=Algo::USub(a,b,na);
     
     guard("Algo::USub guard");
     
     Unit c1=Slow::USub(d,b,na);
     
     same(c,c1,"Algo::USub same");
    }
   
   void test16()
    {
     fill_abd();
     
     Unit c=Algo::URevSub(a,b,na);
     
     guard("Algo::URevSub guard");
     
     Unit c1=Slow::URevSub(d,b,na);
     
     same(c,c1,"Algo::URevSub same");
    }
   
   void test17()
    {
     fill_ad();
     
     Unit c=Algo::UNeg(a,na);
     
     guard("Algo::UNeg guard");
     
     Unit c1=Algo::UAdd(a,d,na);
     
     if( c!=c1 ) Error("Algo::UNeg 1");
     
     for(auto r=Range(a,na); +r ;++r) if( *r ) Error("Algo::UNeg 2");
    }
   
   void test18()
    {
     fill_ad();
     
     Unit msu=Algo::Neg(a,na);
     
     guard("Algo::Neg guard");
     
     msu+=Algo::UAdd(a,d,na)+Algo::SignExt(d,na);
     
     if( msu ) Error("Algo::Neg 1");
     
     for(auto r=Range(a,na); +r ;++r) if( *r ) Error("Algo::Neg 2");
    }
   
   void test19()
    {
     fill_ad();
     
     Unit u;
     
     fill_unit(u);
     
     Unit c=Algo::UAddUnit(a,na,u);
     
     guard("Algo::UAddUnit guard");
     
     if( na )
       {
        unit_bna(u);
        
        Unit c1=Algo::UAdd(d,b,na);
        
        same(c,c1,"Algo::UAddUnit same");
       }
     else
       {
        if( c!=u ) Error("Algo::UAddUnit 0");
       }
    }
   
   void test20()
    {
     fill_ad();
     
     Unit u;
     
     fill_unit(u);
     
     Unit aext=Algo::SignExt(a,na);
     
     Unit msu=Algo::AddUnit(a,na,u);
     
     guard("Algo::AddUnit guard");
     
     Unit c=Algo::UAddUnit(d,na,u);
     
     same("Algo::AddUnit same");
     
     aext+=c;
     
     if( aext!=msu ) Error("Algo::AddUnit");
     
     if( na==0 && msu!=u ) Error("Algo::AddUnit 0");
    }
   
   void test21()
    {
     fill_ad();
     
     Unit u;
     
     fill_unit(u);
     
     Unit c=Algo::USubUnit(a,na,u);
     
     guard("Algo::USubUnit guard");
     
     if( na )
       {
        unit_bna(u);
        
        Unit c1=Algo::USub(d,b,na);
        
        same(c,c1,"Algo::USubUnit");
       }
     else
       {
        if( c!=u ) Error("Algo::USubUnit 0");
       }
    }
   
   void test22()
    {
     fill_ad();
     
     Unit u;
     
     fill_unit(u);
     
     Unit aext=Algo::SignExt(a,na);
     
     Unit msu=Algo::SubUnit(a,na,u);
     
     guard("Algo::SubUnit guard");
     
     Unit c=Algo::USubUnit(d,na,u);
     
     same("Algo::SubUnit");
     
     aext-=c;
     
     if( aext!=msu ) Error("Algo::SubUnit");
     
     if( na==0 && msu!=Unit(-u) ) Error("Algo::SubUnit 0");
    }
   
   void test23()
    {
     fill_ad();
     
     Unit u;
     
     fill_unit(u);
     
     Unit c=Algo::UNegAddUnit(a,na,u);
     
     guard("Algo::UNegAddUnit guard");
     
     if( na )
       {
        unit_bna(u);
        
        Unit c1=Algo::URevSub(d,b,na);
        
        same(c,c1,"Algo::UNegAddUnit");
       }
     else
       {
        if( Unit(c+u) ) Error("Algo::UNegAddUnit 0");
       }
    }
   
   void test24()
    {
     fill_ad();
     
     Unit u;
     
     fill_unit(u);
     
     Unit aext=Algo::SignExt(a,na);
     
     Unit msu=Algo::NegAddUnit(a,na,u);
     
     guard("Algo::NegAddUnit guard");
     
     Unit c=Algo::UNegAddUnit(d,na,u);
     
     same("Algo::NegAddUnit");
     
     aext=-aext-c;
     
     if( aext!=msu ) Error("Algo::NegAddUnit");
     
     if( na==0 && msu!=u ) Error("Algo::NegAddUnit 0");
    }
   
   void test25()
    {
     fill_abd();
     
     if( na==0 ) return;
     
     Unit c=Algo::UAdd(a,b,na);
     
     guard("Algo::UAdd guard");
     
     Unit c1=Algo::UAdd(d,b,na-1);
     
     AddC result(d[na-1],b[na-1],c1);
     
     d[na-1]=result.d;
     
     same(c,result.c,"Algo::UAdd same");
    }
   
   void test26()
    {
     fill_abd();
     
     if( na==0 ) return;
     
     Unit c=Algo::USub(a,b,na);
     
     guard("Algo::USub guard");
     
     Unit c1=Algo::UAdd(a,b,na);
     
     same(c,c1,"Algo::USub same");
    }
   
   void test27()
    {
     fill_abd();
     
     if( na==0 ) return;
     
     Unit c=Algo::URevSub(a,b,na);
     
     guard("Algo::URevSub guard");
 
     Unit c1=Algo::UAdd(a,d,na);
     
     same_b(c,c1,"Algo::URevSub same");
    }
   
   void test28()
    {
     fill_ad();
     fill_b();
     
     if( na<nb ) return;
 
     Unit ext=Algo::SignExt(a,na);
     Unit ext1=Algo::SignExt(b,nb);
     
     Unit msu=Algo::Add(a,na,b,nb);
     
     guard("Algo::Add guard");
     
     Range(b+nb,na-nb).set(ext1);
     
     Unit c=Algo::UAdd(d,b,na);
     
     ext+=ext1+c;
     
     same(msu,ext,"Algo::Add same");
    }
   
   void test29()
    {
     fill_ad();
     fill_b();
     
     if( na<nb ) return;
     
     Unit ext=Algo::SignExt(a,na);
     
     Unit msu=Algo::Sub(a,na,b,nb);
     
     guard("Algo::Sub guard");
     
     Unit ext1=Algo::SignExt(a,na);
     
     Unit msu1=Algo::Add(a,na,b,nb);
     
     msu1-=ext1;
     ext-=msu;
     
     same(msu1,ext,"Algo::Sub same");
    }
   
   void test30()
    {
     fill_ad();
     fill_b();
     
     if( na<nb ) return;
     
     Unit ext=Algo::SignExt(a,na);
     
     Unit msu=Algo::RevSub(a,na,b,nb);
     
     guard("Algo::RevSub guard");
 
     Unit c=Algo::UAdd(a,d,na);
     
     msu+=ext+c;
 
     Unit ext1=Algo::SignExt(b,nb);
 
     Range(b+nb,na-nb).set(ext1);
     
     same_b(msu,ext1,"Algo::RevSub same");
    }
   
   void test31()
    {
     fill_ad();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     
     Unit msu=Algo::ULShift(a,na,shift);
     
     guard("Algo::ULShift guard");
     
     if( na && a[0]!=LShift(d[0],0,shift) ) Error("Algo::ULShift 1");
     
     for(ulen i=1; i<na ;i++) if( a[i]!=LShift(d[i],d[i-1],shift) ) Error("Algo::ULShift 2");
 
     if( na )
       {
        if( msu!=LShift(0,d[na-1],shift) ) Error("Algo::ULShift 3");
       }
     else
       {
        if( msu ) Error("Algo::ULShift 4");
       }
    }
   
   void test32()
    {
     fill_ad();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     
     Unit msu=Algo::LShift(a,d,na,shift);
     
     guard("Algo::LShift guard");
     
     if( na && a[0]!=LShift(d[0],0,shift) ) Error("Algo::LShift 1");
     
     for(ulen i=1; i<na ;i++) if( a[i]!=LShift(d[i],d[i-1],shift) ) Error("Algo::LShift 2");
 
     if( na )
       {
        if( msu!=LShift(Algo::SignExt(d[na-1]),d[na-1],shift) ) Error("Algo::LShift 3");
       }
     else
       {
        if( msu ) Error("Algo::LShift 4");
       }
    }
   
   void test33()
    {
     fill_ad();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     ulen delta=select(0,na);
     ulen n=na-delta;
     
     Unit msu=Algo::ShiftUp(a,n,delta,shift);
     
     guard("Algo::ShiftUp guard");
     
     if( !Range(a,delta).equal(d) ) Error("Algo::ShiftUp 1");
     
     if( n && a[delta]!=LShift(d[0],0,shift) ) Error("Algo::ShiftUp 2");
     
     for(ulen i=1; i<n ;i++) if( a[delta+i]!=LShift(d[i],d[i-1],shift) ) Error("Algo::ShiftUp 3");
 
     if( n )
       {
        if( msu!=LShift(Algo::SignExt(d[n-1]),d[n-1],shift) ) Error("Algo::ShiftUp 4");
       }
     else
       {
        if( msu ) Error("Algo::ShiftUp 5");
       }
    }
   
   void test34()
    {
     fill_ad();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     
     Algo::RShift(a,d,na,shift);
     
     guard("Algo::RShift guard");
     
     if( na ) d[na]=Algo::SignExt(d[na-1]);
     
     for(ulen i=0; i<na ;i++) if( a[i]!=RShift(d[i+1],d[i],shift) ) Error("Algo::RShift");
    }
   
   void test35()
    {
     fill_ad();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     ulen delta=select(0,na);
     ulen n=na-delta;
     
     Algo::ShiftDown(a,n,delta,shift);
     
     guard("Algo::ShiftDown guard");
     
     if( !Range(a+n,delta).equal(d+n) ) Error("Algo::ShiftDown 1");
     
     if( na ) d[na]=Algo::SignExt(d[na-1]);
     
     for(ulen i=0; i<n ;i++) if( a[i]!=RShift(d[delta+i+1],d[delta+i],shift) ) Error("Algo::ShiftDown 2");
    }
   
   void test36()
    {
     fill_ag();
     
     Algo::Null(a,na);
     
     guard("Algo::Null guard");
     
     for(ulen i=0; i<na ;i++) if( a[i] ) Error("Algo::Null");
    }
   
   void test37()
    {
     fill_ad();
     
     ulen delta=select(0,na);
     ulen n=na-delta;
     
     Algo::MoveUp(a,n,delta);
     
     guard("Algo::MoveUp guard");
     
     if( !Range(a,delta).equal(d) ) Error("Algo::MoveUp 1");
     
     if( !Range(a+delta,n).equal(d) ) Error("Algo::MoveUp 2");
    }
   
   void test38()
    {
     fill_ad();
     
     ulen delta=select(0,na);
     ulen n=na-delta;
     
     Algo::MoveDown(a,n,delta);
     
     guard("Algo::MoveDown guard");
     
     if( !Range(a+n,delta).equal(d+n) ) Error("Algo::MoveDown 1");
     
     if( !Range(a,n).equal(d+delta) ) Error("Algo::MoveDown 2");
    }
   
   void test39()
    {
     fill_abc();
     
     Algo::UMul(c,a,na,b,nb);
     
     guard_c("Algo::UMul guard");
     
     Slow::UMul(d,a,na,b,nb);
     
     if( !Range(c,nc).equal(d) ) Error("Algo::UMul");
    }
   
   void test40()
    {
     fill_a();
     fill_b();
     fill_c(select(0,na+nb));
     
     Algo::UMulLo(c,nc,a,na,b,nb);
     
     guard_c("Algo::UMulLo guard");
     
     Algo::UMul(d,a,na,b,nb);
     
     if( !Range(c,nc).equal(d) ) Error("Algo::UMulLo");
    }
   
   void test41()
    {
     fill_abc();
     
     Algo::Mul(c,a,na,b,nb);
     
     guard_c("Algo::Mul guard");
     
     Algo::UMul(d,a,na,b,nb);
     
     if( na && nb )
       {
        if( a[na-1]&Algo::MSBit ) Algo::USub(d+na,b,nb);
        
        if( b[nb-1]&Algo::MSBit ) Algo::USub(d+nb,a,na);
       }
     
     if( !Range(c,nc).equal(d) ) Error("Algo::Mul");
    }
   
   void test42()
    {
     fill_abc();
     
     Algo::UMul(c,a,na,b,nb);
     
     guard_c("Algo::UMul guard");
 
     Algo::UMul(d,b,nb,a,na);
     
     if( !Range(c,nc).equal(d) ) Error("Algo::UMul");
    }
   
   void test43()
    {
     fill_abc();
     
     Algo::UMul(c,a,na,b,nb);
     
     guard_c("Algo::UMul guard");
     
     if( na )
       {
        Algo::UMul(d,a,na-1,b,nb);
        
        d[nc-1]=0;
        
        Algo::UMul(e,a+na-1,1,b,nb);
        
        Algo::UAdd(d+na-1,e,nb+1);
       }
     else
       {
        Algo::Null(d,nc);
       }
     
     if( !Range(c,nc).equal(d) ) Error("Algo::UMul");
    }
   
   void test44()
    {
     fill_abc();
     
     Algo::UMul(c,a,na,b,nb);
     
     guard_c("Algo::UMul guard");
     
     fill(Range(e,na));
     
     Algo::UMul(d,e,na,b,nb);
     
     Algo::UAdd(c,d,nc);
     
     Unit carry=Algo::UAdd(e,a,na);
     
     Algo::UMul(d,e,na,b,nb);
     
     if( carry ) Algo::UAdd(d+na,b,nb);
     
     if( !Range(c,nc).equal(d) ) Error("Algo::UMul");
    }
   
   void test45()
    {
     fill_abc();
     
     Range(c,nc).copyTo(d);
     
     Unit carry1=Algo::UMac(c,a,na,b,nb);
     
     guard_c("Algo::UMac guard");
 
     Algo::UMul(e,a,na,b,nb);
 
     Unit carry2=Algo::UAdd(d,e,nc);
     
     if( carry1!=carry2 || !Range(c,nc).equal(d) ) Error("Algo::UMac");
    }
   
   void test46()
    {
     fill_a2c();
     
     Algo::USq(c,a,na);
     
     guard_c("Algo::USq guard");
     
     Algo::UMul(d,a,na,a,na);
     
     if( !Range(c,nc).equal(d) ) Error("Algo::USq");
    }
   
   void test47()
    {
     fill_a2c();
     
     Algo::Sq(c,a,na);
     
     guard_c("Algo::Sq guard");
     
     Algo::Mul(d,a,na,a,na);
     
     if( !Range(c,nc).equal(d) ) Error("Algo::Sq");
    }
   
   void test48()
    {
     fill_ad();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     ulen delta=select(0,na);
     ulen n=na-delta;
     
     Unit msu=Algo::UShiftUp(a,n,delta,shift);
     
     guard("Algo::UShiftUp guard");
     
     if( !Range(a,delta).equal(d) ) Error("Algo::UShiftUp 1");
     
     if( n && a[delta]!=LShift(d[0],0,shift) ) Error("Algo::UShiftUp 2");
     
     for(ulen i=1; i<n ;i++) if( a[delta+i]!=LShift(d[i],d[i-1],shift) ) Error("Algo::UShiftUp 3");
 
     if( n )
       {
        if( msu!=LShift(0,d[n-1],shift) ) Error("Algo::UShiftUp 4");
       }
     else
       {
        if( msu ) Error("Algo::UShiftUp 5");
       }
    }
   
   void test49()
    {
     fill_ad();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     ulen delta=select(0,na);
     ulen n=na-delta;
     
     Algo::UShiftDown(a,n,delta,shift);
     
     guard("Algo::UShiftDown guard");
     
     if( !Range(a+n,delta).equal(d+n) ) Error("Algo::UShiftDown 1");
     
     if( na ) d[na]=0;
     
     for(ulen i=0; i<n ;i++) if( a[i]!=RShift(d[delta+i+1],d[delta+i],shift) ) Error("Algo::UShiftDown 2");
    }
   
   void test50()
    {
     fill_ad();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     
     Algo::URShift(a,na,shift);
     
     guard("Algo::URShift guard");

     if( na )
       {
        for(ulen i=0; i<na-1 ;i++) if( a[i]!=RShift(d[i+1],d[i],shift) ) Error("Algo::URShift 1");
     
        if( a[na-1]!=RShift(0,d[na-1],shift) ) Error("Algo::URShift 2");
       }
    }
   
   void test51()
    {
     Unit a;
     
     fill_unit(a);
     
     unsigned s=Algo::CountZeroLSB(a);
     
     if( s<Algo::UnitBits )
       {
        Unit bit=Unit(1)<<s;
        
        if( (a&bit)==0 || (a&(bit-1))!=0 ) Error("Algo::CountZeroLSB 1");
       }
     else
       {
        if( a!=0 ) Error("Algo::CountZeroLSB 2");
       }
    }

  public:
   
   TestIntegerAlgo() {}
   
   void run(ulen rep)
    {
     test0();
 
     for(; rep ;rep--)
       {
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        test7();
        test8();
        test9();
        test10();
        test11();
        test12();
        test13();
        test14();
        test15();
        test16();
        test17();
        test18();
        test19();
        test20();
        test21();
        test22();
        test23();
        test24();
        test25();
        test26();
        test27();
        test28();
        test29();
        test30();
        test31();
        test32();
        test33();
        test34();
        test35();
        test36();
        test37();
        test38();
        test39();
        test40();
        test41();
        test42();
        test43();
        test44();
        test45();
        test46();
        test47();
        test48();
        test49();
        test50();
        test51();
       }
    }
 };

/* class TestIntegerAlgo2<Algo,Alt> */

template <class Algo,class Alt> 
class TestIntegerAlgo2 : TestIntBase
 {
   typedef typename Algo::Unit Unit;
   
   static const ulen Len = 100 ;
   static const ulen GLen = 10 ;
   
  private: 
   
   Unit a[Len];
   ulen na;
   Unit b[Len];
   ulen nb;
 
   Unit c[2*Len+GLen];
   Unit d[2*Len+GLen];
   ulen nc;
   
  private: 
   
   void fill_c(ulen n)
    {
     nc=n;
     
     fill(Range(c,nc+GLen));
     
     Range(c,nc+GLen).copyTo(d);
    }
   
   void fill_abc()
    {
     na=select(0,Len);
     nb=select(0,Len);
     
     fill(Range(a,na));
     fill(Range(b,nb));
     
     fill_c(na+nb);
    }
   
   void fill_c()
    {
     na=select(0,Len);
     nb=select(0,Len);
     
     fill_c(na+nb);
    }
   
   void fill_ac()
    {
     na=select(0,Len);
     
     fill(Range(a,na));
     
     fill_c(na);
    }
   
   void fill_acext()
    {
     na=select(0,Len);
     nb=select(0,Len);
     
     fill(Range(a,na));
     
     fill_c(na+nb);
    }
   
   void fill_a()
    {
     na=select(0,Len);
     
     fill(Range(a,na));
    }
   
   void fill_abn()
    {
     na=select(0,Len);
     nb=na;
     
     fill(Range(a,na));
     fill(Range(b,nb));
    }
   
   void fill_ab()
    {
     na=select(0,Len);
     nb=select(0,Len);
     
     fill(Range(a,na));
     fill(Range(b,nb));
    }
   
   void fill_a2c()
    {
     na=select(0,Len);
     
     fill(Range(a,na));
     
     fill_c(2*na);
    }
   
   void guard(const char *msg)
    {
     if( !Range(c,nc+GLen).equal(d) ) Error(msg);
    }
   
   void guard(Unit u,Unit u1,const char *msg)
    {
     if( u!=u1 || !Range(c,nc+GLen).equal(d) ) Error(msg);
    }
   
  private: 
   
   void test1()
    {
     fill_abc();
     
     Algo::UMul(c,a,na,b,nb);
     Alt::UMul(d,a,na,b,nb);
     
     guard("Algo::UMul");
    }
   
   void test2()
    {
     fill_abc();
     
     Algo::Mul(c,a,na,b,nb);
     Alt::Mul(d,a,na,b,nb);
     
     guard("Algo::UMul");
    }
   
   void test3()
    {
     fill_abc();
     
     ulen n=select(0,nc);
     
     Algo::UMulLo(c,n,a,na,b,nb);
     Alt::UMulLo(d,n,a,na,b,nb);
     
     guard("Algo::UMulLo");
    }
   
   void test4()
    {
     fill_c();
     
     Algo::Null(c,nc);
     Alt::Null(d,nc);
     
     guard("Algo::Null");
    }
   
   void test5()
    {
     fill_c();
     
     Algo::MoveUp(c,na,nb);
     Alt::MoveUp(d,na,nb);
     
     guard("Algo::MoveUp");
    }
   
   void test6()
    {
     fill_c();
     
     Algo::MoveDown(c,na,nb);
     Alt::MoveDown(d,na,nb);
     
     guard("Algo::MoveDown");
    }
   
   void test7()
    {
     fill_c();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     
     Unit u=Algo::ULShift(c,nc,shift);
     Unit u1=Alt::ULShift(d,nc,shift);
     
     guard(u,u1,"Algo::ULShift");
    }
   
   void test8()
    {
     fill_c();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     
     Unit u=Algo::ShiftUp(c,na,nb,shift);
     Unit u1=Alt::ShiftUp(d,na,nb,shift);
     
     guard(u,u1,"Algo::ShiftUp");
    }
   
   void test9()
    {
     fill_c();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     
     Algo::ShiftDown(c,na,nb,shift);
     Alt::ShiftDown(d,na,nb,shift);
     
     guard("Algo::ShiftDown");
    }
   
   void test10()
    {
     fill_ac();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     
     Unit u=Algo::LShift(c,a,na,shift);
     Unit u1=Alt::LShift(d,a,na,shift);
     
     guard(u,u1,"Algo::LShift");
    }
   
   void test11()
    {
     fill_ac();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     
     Algo::RShift(c,a,na,shift);
     Alt::RShift(d,a,na,shift);
     
     guard("Algo::RShift");
    }
   
   void test12()
    {
     fill_ac();
     
     Unit u=Algo::UAdd(c,a,na);
     Unit u1=Alt::UAdd(d,a,na);
     
     guard(u,u1,"Algo::UAdd");
    }
   
   void test13()
    {
     fill_ac();
     
     Unit u=Algo::USub(c,a,na);
     Unit u1=Alt::USub(d,a,na);
     
     guard(u,u1,"Algo::USub");
    }
   
   void test14()
    {
     fill_ac();
     
     Unit u=Algo::URevSub(c,a,na);
     Unit u1=Alt::URevSub(d,a,na);
     
     guard(u,u1,"Algo::URevSub");
    }
   
   void test15()
    {
     fill_acext();
     
     Unit u=Algo::Add(c,nc,a,na);
     Unit u1=Alt::Add(d,nc,a,na);
     
     guard(u,u1,"Algo::Add");
    }
   
   void test16()
    {
     fill_acext();
     
     Unit u=Algo::Sub(c,nc,a,na);
     Unit u1=Alt::Sub(d,nc,a,na);
     
     guard(u,u1,"Algo::Sub");
    }
   
   void test17()
    {
     fill_acext();
     
     Unit u=Algo::RevSub(c,nc,a,na);
     Unit u1=Alt::RevSub(d,nc,a,na);
     
     guard(u,u1,"Algo::RevSub");
    }
   
   void test18()
    {
     fill_c();
     
     Unit x;
     
     fill_unit(x);
     
     Unit u=Algo::UAddUnit(c,nc,x);
     Unit u1=Alt::UAddUnit(d,nc,x);
     
     guard(u,u1,"Algo::UAddUnit");
    }
   
   void test19()
    {
     fill_c();
     
     Unit x;
     
     fill_unit(x);
     
     Unit u=Algo::AddUnit(c,nc,x);
     Unit u1=Alt::AddUnit(d,nc,x);
     
     guard(u,u1,"Algo::AddUnit");
    }
   
   void test20()
    {
     fill_c();
     
     Unit x;
     
     fill_unit(x);
     
     Unit u=Algo::USubUnit(c,nc,x);
     Unit u1=Alt::USubUnit(d,nc,x);
     
     guard(u,u1,"Algo::USubUnit");
    }
   
   void test21()
    {
     fill_c();
     
     Unit x;
     
     fill_unit(x);
     
     Unit u=Algo::SubUnit(c,nc,x);
     Unit u1=Alt::SubUnit(d,nc,x);
     
     guard(u,u1,"Algo::SubUnit");
    }
   
   void test22()
    {
     fill_c();
     
     Unit x;
     
     fill_unit(x);
     
     Unit u=Algo::UNegAddUnit(c,nc,x);
     Unit u1=Alt::UNegAddUnit(d,nc,x);
     
     guard(u,u1,"Algo::UNegAddUnit");
    }
   
   void test23()
    {
     fill_c();
     
     Unit x;
     
     fill_unit(x);
     
     Unit u=Algo::NegAddUnit(c,nc,x);
     Unit u1=Alt::NegAddUnit(d,nc,x);
     
     guard(u,u1,"Algo::NegAddUnit");
    }
   
   void test24()
    {
     fill_c();
     
     Unit u=Algo::UNeg(c,nc);
     Unit u1=Alt::UNeg(d,nc);
     
     guard(u,u1,"Algo::UNeg");
    }
   
   void test25()
    {
     fill_c();
     
     Unit u=Algo::Neg(c,nc);
     Unit u1=Alt::Neg(d,nc);
     
     guard(u,u1,"Algo::Neg");
    }
   
   void test26()
    {
     fill_a();
     
     CmpResult u=Algo::USign(a,na);
     CmpResult u1=Alt::USign(a,na);
     
     if( u!=u1 ) Error("Algo::USign");
    }
   
   void test27()
    {
     fill_a();
     
     CmpResult u=Algo::Sign(a,na);
     CmpResult u1=Alt::Sign(a,na);
     
     if( u!=u1 ) Error("Algo::Sign");
    }
   
   void test28()
    {
     fill_a();
     
     ulen u=Algo::UNormalize(a,na);
     ulen u1=Alt::UNormalize(a,na);
     
     if( u!=u1 ) Error("Algo::UNormalize");
    }
   
   void test29()
    {
     fill_a();
     
     ulen u=Algo::Normalize(a,na);
     ulen u1=Alt::Normalize(a,na);
     
     if( u!=u1 ) Error("Algo::Normalize");
    }
   
   void test30()
    {
     fill_abn();
     
     CmpResult u=Algo::UCmp(a,b,na);
     CmpResult u1=Alt::UCmp(a,b,na);
     
     if( u!=u1 ) Error("Algo::UCmp");
    }
   
   void test31()
    {
     fill_abn();
     
     CmpResult u=Algo::Cmp(a,b,na);
     CmpResult u1=Alt::Cmp(a,b,na);
     
     if( u!=u1 ) Error("Algo::Cmp");
    }
   
   void test32()
    {
     fill_ab();
     
     CmpResult u=Algo::UCmp(a,na,b,nb);
     CmpResult u1=Alt::UCmp(a,na,b,nb);
     
     if( u!=u1 ) Error("Algo::UCmp");
    }
   
   void test33()
    {
     fill_ab();
     
     CmpResult u=Algo::Cmp(a,na,b,nb);
     CmpResult u1=Alt::Cmp(a,na,b,nb);
     
     if( u!=u1 ) Error("Algo::Cmp");
    }
   
   void test34()
    {
     fill_a();
     
     Unit u=Algo::SignExt(a,na);
     Unit u1=Alt::SignExt(a,na);
     
     if( u!=u1 ) Error("Algo::SignExt");
    }
   
   void test35()
    {
     Unit a;
     
     fill_unit(a);
     
     Unit u=Algo::SignExt(a);
     Unit u1=Alt::SignExt(a);
     
     if( u!=u1 ) Error("Algo::SignExt(Unit)");
    }
   
   void test36()
    {
     Unit a;
     
     fill_unit(a);
     
     Unit b;
     
     fill_unit(b);
     
     CmpResult u=Algo::SignCmp(a,b);
     CmpResult u1=Alt::SignCmp(a,b);
     
     if( u!=u1 ) Error("Algo::SignCmp");
    }
   
   void test37()
    {
     Unit a;
     
     fill_unit(a);
     
     unsigned u=Algo::CountZeroMSB(a);
     unsigned u1=Alt::CountZeroMSB(a);
     
     if( u!=u1 ) Error("Algo::CountZeroMSB");
    }
   
   void test38()
    {
     Unit hi;
     
     fill_unit(hi);
     
     Unit lo;
     
     fill_unit(lo);
     
     Unit den;
     
     fill_unit(den);
     
     if( hi>=den ) return;
     
     Unit u=Algo::DoubleUDiv(hi,lo,den);
     Unit u1=Alt::DoubleUDiv(hi,lo,den);
     
     if( u!=u1 ) Error("Algo::DoubleUDiv");
    }
   
   void test39()
    {
     fill_a2c();
     
     Algo::USq(c,a,na);
     Alt::USq(d,a,na);
     
     guard("Algo::USq");
    }
   
   void test40()
    {
     fill_a2c();
     
     Algo::Sq(c,a,na);
     Alt::Sq(d,a,na);
     
     guard("Algo::Sq");
    }
   
   void test41()
    {
     fill_abc();
 
     Unit u=Algo::UMac(c,a,na,b,nb);
     Unit u1=Alt::UMac(d,a,na,b,nb);
     
     guard(u,u1,"Algo::UMac");
    }
   
   void test42()
    {
     fill_c();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     
     Unit u=Algo::UShiftUp(c,na,nb,shift);
     Unit u1=Alt::UShiftUp(d,na,nb,shift);
     
     guard(u,u1,"Algo::UShiftUp");
    }
   
   void test43()
    {
     fill_c();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     
     Algo::UShiftDown(c,na,nb,shift);
     Alt::UShiftDown(d,na,nb,shift);
     
     guard("Algo::UShiftDown");
    }
   
   void test44()
    {
     fill_c();
     
     unsigned shift=select(1,Algo::UnitBits-1);
     
     Algo::URShift(c,nc,shift);
     Alt::URShift(d,nc,shift);
     
     guard("Algo::URShift");
    }
   
   void test45()
    {
     Unit a;
     
     fill_unit(a);
     
     unsigned u=Algo::CountZeroLSB(a);
     unsigned u1=Alt::CountZeroLSB(a);
     
     if( u!=u1 ) Error("Algo::CountZeroLSB");
    }

  public: 
   
   TestIntegerAlgo2() {}
   
   void run(ulen rep)
    {
     static_assert( std::is_same<typename Algo::Unit,typename Alt::Unit>::value ,"Algo::Unit");
     static_assert( Algo::UnitBits==Alt::UnitBits ,"Algo::UnitBits");
     static_assert( Algo::MaxUnit==Alt::MaxUnit ,"Algo::MaxUnit");
     static_assert( Algo::MSBit==Alt::MSBit ,"Algo::MSBit");
     
     for(; rep ;rep--) 
       {
        test1();
        test2();
        test3();
        
        test4();
        test5();
        test6();
        
        test7();
        test8();
        test9();
        test10();
        test11();
        
        test12();
        test13();
        test14();
        
        test15();
        test16();
        test17();
        
        test18();
        test19();
        test20();
        test21();
        test22();
        test23();
        
        test24();
        test25();
        
        test26();
        test27();
        test28();
        test29();
        
        test30();
        test31();
        test32();
        test33();
        
        test34();
        test35();
        test36();
        test37();
        test38();
        test39();
        test40();
        test41();
        
        test42();
        test43();
        test44();
        
        test45();
       }
    }
 };

} // namespace App

#endif




