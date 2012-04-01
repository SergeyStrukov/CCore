/* test0055.IntegerSlowMul.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/math/IntegerSlowAlgo.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_0055 {

typedef uint8 Unit;

typedef Math::IntegerSlowMulAlgo<Unit>      Algo1;
typedef Math::IntegerSlowMulAlgo<Unit,void> Algo2;

/* test1() */

void test1(Random &gen,ulen count)
 {
  for(; count ;count--)
    {
     Unit a=gen.next_uint<Unit>();
     Unit b=gen.next_uint<Unit>();
     
     Algo1::DoubleMul p1(a,b);
     Algo2::DoubleMul p2(a,b);
     
     if( p1.lo!=p2.lo || p1.hi!=p2.hi )
       {
        Printf(Exception,"error 1");
       }
    }
 }

/* test2() */

void test2(Random &gen,ulen count)
 {
  for(; count ;count--)
    {
     Unit a=gen.next_uint<Unit>();
     Unit b=gen.next_uint<Unit>();
     Unit d=gen.next_uint<Unit>();
     
     if( b>=d ) continue;
     
     Unit c1=Algo1::DoubleUDiv(b,a,d);
     Unit c2=Algo2::DoubleUDiv(b,a,d);
     
     if( c1!=c2 )
       {
        Printf(Exception,"error 2");
       }
     
     Algo1::DoubleMul p(d,c1);
     
     if( p.lo<=a )
       {
        if( p.hi!=b )
          {
           Printf(Exception,"error 3");
          }
        
        if( a-p.lo>=d )
          {
           Printf(Exception,"error 4");
          }
       }
     else
       {
        if( p.hi+1!=b || b==0 )
          {
           Printf(Exception,"error 5");
          }
        
        if( Unit(a-p.lo)>=d )
          {
           Printf(Exception,"error 6");
          }
       }
    }
 }

/* test3() */

void test3(Random &gen,ulen count)
 {
  for(; count ;count--)
    {
     Unit a=gen.next_uint<Unit>();
     Unit b=-a;
     
     if( b>a ) Swap(a,b);
     
     Unit c=Algo2::Inv(a);
     
     if( a==b )
       {
        if( c )
          {
           Printf(Exception,"error 7");
          }
       }
     else
       {
        Algo1::DoubleMul p(a,c);
        
        if( b<p.hi )
          {
           Printf(Exception,"error 8");
          }
        
        if( b==p.hi )
          {
           if( p.lo )
             {
              Printf(Exception,"error 9");
             }
          }
        else
          {
           if( b!=p.hi+1 )
             {
              Printf(Exception,"error 10");
             }
           
           if( Unit(-p.lo)>=a )
             {
              Printf(Exception,"error 11");
             }
          }
       }
    }
 }

} // namespace Private_0055
 
using namespace Private_0055; 
 
/* Testit<55> */ 

template<>
const char *const Testit<55>::Name="Test55 IntegerSlowMul";

template<>
bool Testit<55>::Main() 
 {
  Random gen;
  
  test1(gen,1000000);
  test2(gen,1000000);
  test3(gen,1000000);
  
  return true;
 }
 
} // namespace App
 
