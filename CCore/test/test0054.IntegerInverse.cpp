/* test0054.IntegerInverse.cpp */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/math/Integer.h>
#include <CCore/inc/math/IntegerSlowAlgo.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_0054 {

/* types */

typedef Math::IntegerSlowAlgo<uint8> Algo8;

/* class TestIntegerInverse<Algo> */

template <class Algo> 
class TestIntegerInverse : NoCopy
 {
   typedef typename Algo::Unit Unit;
   
   DynArray<Unit> buf; 
   
  private:
  
   static Unit Start(Unit a)
    {
     if( a==Algo::MaxUnit ) return 0;
     
     return Algo::DoubleUDiv(Algo::MaxUnit-a,0,a+1);
    }
   
   void check(const Unit *d,const Unit *a,ulen na,const Unit *x,ulen k,Unit *P);
   
  public:
  
   TestIntegerInverse(const Unit *a,ulen na,ulen K);
   
   static void Run(ulen na,ulen K,Random &gen,ulen count);
 };
 
template <class Algo> 
void TestIntegerInverse<Algo>::check(const Unit *d,const Unit *a,ulen na,const Unit *x,ulen k,Unit *P)
 {
  if( Algo::UCmp(d,a,na)>=0 ) 
    {
     Printf(Exception,"error 1\n");
    }

  Algo::UMul(P,a,na,x,k+1);

  Unit c=Algo::UAdd(P,d,na);
  
  c=Algo::UAddUnit(P+na,k+1,c);
  
  if( c || Algo::USign(P,na+k) || P[na+k]!=1 )
    {
     Printf(Exception,"error 2\n");
    }
 }

template <class Algo> 
TestIntegerInverse<Algo>::TestIntegerInverse(const Unit *a,ulen na,ulen K)
 {
  if( na==0 ) Math::GuardIntegerInverseNotNormalized();
  
  Unit msa=a[na-1];
  
  if( (msa&Algo::MSBit)==0 ) Math::GuardIntegerInverseNotNormalized();
  
  if( msa==Algo::MSBit && Algo::USign(a,na-1)==0 )
    {
     buf.extend_default(K);
     buf.append_copy(2);
     
     return;
    }
       
  if( K==0 )
    {
     buf.append_copy(1);
     
     return;
    }
    
  if( na>=MaxULen/2 || K>=MaxULen/2-na ) Math::GuardIntegerInverseOverflow(); 
  
  ulen buf_len = 2*(K+na+1) ; // (K+1)+na+(na+K+1);

  Unit *X=buf.extend_default(buf_len).ptr;    
  ulen k=1;

  Unit *x=X+(K-k);
  Unit *d=X+K+1;
  Unit *P=d+na;

  // 1 x<- d<-
  
  {
   x[1]=1;
   
   x[0]=Start(msa);
   
   Algo::UMul(d,x,2,a,na);
   
   Algo::UNeg(d,na+1);
   
   while( Algo::UCmp(d,na+1,a,na)>=0 )
     {
      x[0]++;
      
      d[na]-=Algo::USub(d,a,na);
     }
  }
  
  check(d,a,na,x,k,P);
  
  // 2
  
  while( 2*k<=K )
    {
     Unit *y=x-k;
     
     Algo::UMul(P,x,k+1,d,na);
     
     Range(y,k).copy(P+na);
     
     Algo::UMulLo(P,na+1,a,na,y,k);
     
     Algo::UNeg(P,na+1);
     
     if( k<=na )
       {
        Algo::UAdd(P+k,d,na+1-k);
       }
       
     if( P[na] || Algo::UCmp(P,a,na)>=0 )  
       {
        Algo::UAddUnit(y,2*k+1,1);
        Algo::USub(P,a,na);
       }

     Range(d,na).copy(P);
    
     k*=2;
     x=y;
     
     check(d,a,na,x,k,P);
    }
  
  // 3
  
  if( k<K )
    {
     ulen l=K-k; // l<k
     
     Algo::UMul(P,x,k+1,d,na);
   
     Range(X,l).copy(P+na+(k-l));
   
     Algo::UMulLo(P,na+1,a,na,X,l);
   
     Algo::UNeg(P,na+1);
   
     if( l<=na )
       {
        Algo::UAdd(P+l,d,na+1-l);
       }
        
     if( P[na] || Algo::UCmp(P,a,na)>=0 )  
       {
        Algo::UAddUnit(X,K+1,1);
        
        Algo::USub(P,a,na);
       }
     
     Range(d,na).copy(P);
     
     check(d,a,na,X,K,P);
    }
 }

template <class Algo> 
void TestIntegerInverse<Algo>::Run(ulen na,ulen K,Random &gen,ulen count)
 {
  SimpleArray<Unit> buf(na);
  Unit *a=buf.getPtr();
  
  for(; count ;count--)
    {
     for(auto r=Range(a,na); +r ;++r) *r=gen.next_uint<Unit>();
     
     a[na-1]|=Algo::MSBit;
     
     TestIntegerInverse(a,na,K);
    }
 }

} // namespace Private_0054
 
using namespace Private_0054; 
 
/* Testit<54> */ 

template<>
const char *const Testit<54>::Name="Test54 IntegerInverse";

template<>
bool Testit<54>::Main() 
 {
  Random gen;

  for(ulen na=5; na<=20 ;na++)
    for(ulen K=1; K<=50 ;K++)
      TestIntegerInverse<Algo8>::Run(na,K,gen,1000);
  
  return true;
 }
 
} // namespace App
 
