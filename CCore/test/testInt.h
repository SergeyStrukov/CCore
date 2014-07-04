/* testInt.h */
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

#ifndef CCore_test_testInt_h
#define CCore_test_testInt_h

#include <CCore/test/testIntBase.h>

#include <CCore/inc/math/Integer.h>

#include <CCore/inc/String.h>

namespace App {

/* classes */ 

template <class Algo> class TestInteger;

/* class TestInteger<Algo> */

template <class Algo>
class TestInteger : TestIntBase
 {
   typedef Math::Integer<Algo> Int;
   typedef Math::RandomInteger<Int> RandomInt;
  
   static const unsigned SLen = 10 ;
   static const unsigned MLen = 100 ;
   
  private: 
  
   Int getInt() { return RandomInt(select(0,SLen),getBase()); }
   
   Int getMInt() { return RandomInt(select(0,MLen),getBase()); }
   
   static bool CoPrime(Int a,Int b)
    {
     if( a.sign()<0 ) a=-a;
     
     if( b.sign()<0 ) b=-b;
     
     for(;;)
       {
        if( !a ) return b.cmp(1)==0;
        if( !b ) return a.cmp(1)==0;
        
        if( a<b ) b%=a; else a%=b;
       }
    }
   
   static int Eps(const Int &a_,const Int &b_)
    {
     auto a=a_.getBody();
     auto b=b_.getBody();
     
     if( a.len>0 && (a[0]&3u)==3 && b.len>0 && (b[0]&3u)==3 ) return -1;
      
     return 1; 
    }
   
  private: 

   void test1()
    {
     Int a=getInt();
    
     Int b=-a;
    
     if( (a+b).sign() ) Error("test1");
    
     b.neg();
    
     if( b!=a ) Error("test1");
    }
  
   void test2()
    {
     Int a=getInt();
     Int b=getInt();
     Int c=getInt();
    
     if( (a+b)-c != a+(b-c) ) Error("test2"); 
    }
  
   void test3()
    {
     Int a=getInt();
     Int b=getInt();
     Int c=getInt();
    
     if( (a+b)*c != a*c+b*c ) Error("test3"); 
    }
  
   void test4()
    {
     Int a=getInt();
     Int b=getInt();
    
     if( Cmp(a,b) != (a-b).sign() ) Error("test4"); 
    }
  
   void test5()
    {
     Int a=getInt();
     unsigned d=select(0,20);
    
     if( a.pow(d+1) != a.pow(d)*a ) Error("test5"); 
    }
  
   void test6()
    {
     Int a=getInt();
     Int b=getInt();
    
     Int c=a;
    
     a+=b;
     a-=b;
    
     if( a!=c ) Error("test6");
    }
  
   void test7()
    {
     Int a=getInt();
     Int b=getInt();
    
     Int c=a;
    
     a+=b;
    
     if( a!=c+b ) Error("test7");
    }
  
   void test8()
    {
     Int a=getInt();
     Int b=getInt();
    
     Int c=a;
    
     a-=b;
    
     if( a!=c-b ) Error("test8");
    }
  
   void test9()
    {
     Int a=getInt();
     Int b=getInt();

     if( !b ) return;
    
     Int q=a/b;
     Int r=a-q*b;
    
     if( b.sign()>0 )
       {
        if( r.sign()<0 || r>=b ) Error("test9");
       }
     else
       {
        if( r.sign()>0 || r<=b ) Error("test9");
       }
     
     if( r!=a%b ) Error("test9");
    }
  
   void test10()
    {
     Int a=getInt();
     unsigned shift=select(0,100);
    
     if( ((a<<shift)>>shift) != a ) Error("test10");
    }
  
   void test11()
    {
     Int a=getInt();
     unsigned shift1=select(0,50);
     unsigned shift2=select(0,50);
    
     if( ((a<<shift1)<<shift2) != (a<<(shift1+shift2)) ) Error("test11");
    
     if( ((a>>shift1)>>shift2) != (a>>(shift1+shift2)) ) Error("test11");
    } 
  
   void test12()
    {
     Int a=getInt();
    
     if( (a<<1) != a*2 ) Error("test12");
    
     Int b=a-((a>>1)<<1);
    
     if( b.sign()<0 || (b-2).sign()>=0 ) Error("test12");
    }
  
   void test13()
    {
     Int a=getMInt();

     String text=StringCat(a);
    
     Int b(Range(text));
    
     if( a!=b ) Error("test13");
    }
  
   void test14()
    {
     Int a=getInt();
     Int b=getInt();
    
     Int c=a;
    
     a*=b;
    
     if( a!=c*b ) Error("test14");
    }
  
   void test15()
    {
     Int a=getInt();
     Int b=getInt();
    
     if( !b ) return;
    
     Int c=a;
    
     a/=b;
    
     if( a!=c/b ) Error("test15");
    }
  
   void test16()
    {
     Int a=getInt();
     Int b=getInt();
    
     if( !b ) return;
    
     Int c=a;
    
     a%=b;
    
     if( a!=c%b ) Error("test16");
    }
  
   void test17()
    {
     Int a=getInt();
     unsigned shift=select(0,100);
    
     Int c=a;
    
     a<<=shift;
    
     if( a!=(c<<shift) ) Error("test17");
    }
  
   void test18()
    {
     Int a=getInt();
     unsigned shift=select(0,100);
    
     Int c=a;
    
     a>>=shift;
    
     if( a!=(c>>shift) ) Error("test18");
    }
  
   void test19()
    {
     Int a=getInt();
     Int b=getInt();
    
     Int c=a;
    
     a.revsub(b);
    
     if( a!=b-c ) Error("test19");
    }
  
   void test20()
    {
     Int a=getInt();
    
     Int c=a.sq();
    
     if( c!=a*a ) Error("test20");
    }
   
   void test21()
    {
     Int a=getMInt();
     Int b=getMInt();
     
     if( !a && !b ) return;
     
     Int c=Math::GCDiv(a,b);
     
     if( (a%c).sign() || (b%c).sign() || c.sign()<=0 || !CoPrime(a/c,b/c) ) Error("test21");
    }
  
   void test22()
    {
     Int d=getInt();
     Int a=getMInt()*d;
     Int b=getMInt()*d;
     
     if( !a && !b ) return;
     
     Int c=Math::GCDiv(a,b);
     
     if( (a%c).sign() || (b%c).sign() || c.sign()<=0 || !CoPrime(a/c,b/c) ) Error("test22");
    }
   
   void test23()
    {
     Int a=getInt();
     Int b=2*getInt()+1;
     
     if( Math::GCDiv(a,b)>1 ) return;
     
     if( Math::QSym(a,b)!=Math::QSym(a+b,b) ) Error("test23");
     
     if( Math::QSym(a,b)!=Math::QSym(a,-b) ) Error("test23");
     
     if( a.sign()>0 )
       {
        if( Math::QSym(a,b)!=Math::QSym(a,b-4*a) ) Error("test23");
       }
     
     Int c=getMInt();
     
     if( Math::GCDiv(c,b)>1 ) return;
     
     if( Math::QSym(a*c,b)!=Math::QSym(a,b)*Math::QSym(c,b) ) Error("test23");
    }
  
   void test24()
    {
     Int a=2*getInt()+1;
     Int b=2*getInt()+1;
     
     if( Math::GCDiv(a,b)>1 ) return;
     
     if( a.sign()>0 || b.sign()>0  )
       {
        if( Math::QSym(a,b)*Math::QSym(b,a)!=Eps(a,b) ) Error("test24");
       }
     else
       {
        if( Math::QSym(a,b)*Math::QSym(b,a)!=-Eps(a,b) ) Error("test24");
       }
    }
   
  public:
  
   TestInteger() {}
   
   void run(ulen rep)
    {
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
       }
    }
 };
 
} // namespace App
 
#endif
 
