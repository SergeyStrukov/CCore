/* test4005.MulSpeed.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testIntExt.h>

#include <CCore/inc/math/IntegerFastAlgo.h>

namespace App {

namespace Private_4005 {

/* class TestSpeed */

class TestSpeed : NoCopy
 {
   typedef Math::ConvolutionMul<Math::IntegerExtAlgo> Fast;
   
   typedef Math::IntegerExtAlgo::Unit Unit;
   
   static const ulen Len = 50000 ;
   static const unsigned Rep = 10 ;
   
   typedef TimeStat<ClockTimer::ValueType> Stat;
   
  private:
   
   Random gen;
   
   DynArray<Unit> array;
   Unit *a; // Len
   Unit *b; // Len
   Unit *c; // 2*Len
   
  private: 
   
   void fill(PtrLen<Unit> r) { gen.fill(r); }
   
  public: 
   
   TestSpeed()
    : array(4*Len)
    {
     a=array.getPtr();
     b=a+Len;
     c=b+Len;
    }
   
   ~TestSpeed() {}
   
   Stat test1(unsigned d,ulen n) // n<=2^d
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        fill(Range(b,n));
        
        ClockTimer timer;
        
        { 
         Fast::Engine engine(d+1);
         
         engine.downA(a,n);
         engine.downB(b,n);
         engine.mul_lo(c,2*n);
        }
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat test2(unsigned /* d */,ulen n) // n==2^d
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        fill(Range(b,n));
        
        ClockTimer timer;
        
        Math::IntegerFastAlgo::UMul(c,a,n,b,n);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat test3(unsigned /* d */,ulen n) // n==2^d
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        
        ClockTimer timer;
        
        Math::IntegerFastAlgo::USq(c,a,n);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   template <class P>
   void run(P &&out)
    {
     ulen n;
     
     Printf(out,"#;\n\n",Title("Conv"));
     
     for(unsigned d=1; (n=(ulen(1)<<d))<=Len ;d++) 
       {
        Stat stat=test1(d,n);
        
        auto s=stat.getMin()/n;
        
        Printf(out,"n = #; time = #;*n\n",n,s);
       }
     
     Printf(out,"\n#;\n\n",Title("FastAlgo"));
     
     for(unsigned d=1; (n=(ulen(1)<<d))<=Len ;d++) 
       {
        Stat stat=test2(d,n);
       
        auto s=stat.getMin()/n;
       
        Printf(out,"n = #; time = #;*n\n",n,s);
       }
     
     Printf(out,"\n#;\n\n",Title("FastAlgo USq"));
     
     for(unsigned d=1; (n=(ulen(1)<<d))<=Len ;d++) 
       {
        Stat stat=test3(d,n);
       
        auto s=stat.getMin()/n;
       
        Printf(out,"n = #; time = #;*n\n",n,s);
       }
     
     Printf(out,"\n");
    }
 };

} // namespace Private_4005
 
using namespace Private_4005; 
 
/* Testit<4005> */ 

template<>
const char *const Testit<4005>::Name="Test4005 MulSpeed";

template<>
bool Testit<4005>::Main() 
 {
  TestExtAlgo<Math::IntegerFastAlgo,Math::IntegerExtAlgo>().run(100000);
  
  TestSpeed().run(Con);
  
  return true;
 }
 
} // namespace App
 
