/* NoPrimeTest.h */ 
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

#ifndef CCore_inc_math_NoPrimeTest_h
#define CCore_inc_math_NoPrimeTest_h

#include <CCore/inc/math/ModEngine.h>
#include <CCore/inc/math/SmallPrimes.h>

#include <CCore/inc/PlatformRandom.h>
 
namespace CCore {
namespace Math {

/* classes */

template <class Integer> struct NoPrimeTest;

/* struct NoPrimeTest<Integer> */

template <class Integer> 
struct NoPrimeTest
 {
  using Unit = typename Integer::Unit ;
  
  static const unsigned Delta = 4 ; 
  
  static_assert( (Integer::UnitBits%Delta)==0 ,"CCore::Math::NoPrimeTest<Integer> : bad Integer::UnitBits");
  
  static const Unit Mask = (Unit(1)<<Delta)-1 ;
  
  class ExpEngine : NoCopy
   {
     ModEngine<Integer> engine;
     
     static const ulen Len = (ulen(1)<<Delta)-1 ;
    
     Integer Pminus1;
     
    private: 
    
     struct Ctx
      {
       Integer pow[Len];
       Integer result;
       bool one = true ;
       
       Ctx() {}
      };
     
     void init(Ctx &ctx,Integer a) const // a >= 0 , a < P
      {
       ctx.pow[0]=a;
       ctx.pow[1]=engine.sq(a);
       
       for(ulen i=2; i<Len ;i++) ctx.pow[i]=engine.mul(ctx.pow[i-1],a);
      }
     
     void next(Ctx &ctx,Unit bits) const
      {
       if( ctx.one )
         {
          if( bits )
            {
             ctx.result=ctx.pow[bits-1];
             ctx.one=false;
            }
         }
       else
         {
          for(unsigned cnt=Delta; cnt ;cnt--) ctx.result=engine.sq(ctx.result);
         
          if( bits ) ctx.result=engine.mul(ctx.result,ctx.pow[bits-1]);
         }
      }
     
     void last(Ctx &ctx,Unit bits) const
      {
       bits>>=1;
      
       if( ctx.one )
         {
          if( bits ) 
            {
             ctx.result=ctx.pow[bits-1];
            }
          else
            {
             ctx.result=1;
            }
         }
       else
         {
          for(unsigned cnt=Delta-1; cnt ;cnt--) ctx.result=engine.sq(ctx.result);
         
          if( bits ) ctx.result=engine.mul(ctx.result,ctx.pow[bits-1]);
         }
      }
    
     void next_unit(Ctx &ctx,Unit unit) const
      {
       for(unsigned off=Integer::UnitBits-Delta; off ;off-=Delta) next(ctx, (unit>>off)&Mask );
       
       next(ctx, unit&Mask );
      }
     
     void last_unit(Ctx &ctx,Unit unit) const
      {
       for(unsigned off=Integer::UnitBits-Delta; off ;off-=Delta) next(ctx, (unit>>off)&Mask );
       
       last(ctx, unit&Mask );
      }
     
    public: 
    
     explicit ExpEngine(const Integer &P) : engine(P),Pminus1(P-1) {} // P > 1
     
     const Integer & getModule() const { return engine.getModule(); }
     
     Integer pow(Integer a) const // a >= 0 , a < P , return a ^ (P>>1) ( mod P )
      {
       Ctx ctx;
       
       init(ctx,a);
       
       auto r=getModule().getBodyReverse();
       
       for(; r.len>1 ;++r) next_unit(ctx,*r);
       
       last_unit(ctx,*r);
       
       return ctx.result;
      }
  
     bool test(Integer a) const // a > 0 , a < P , P > 1 , P is odd
      {
       Integer b=pow(a);
       
       if( b==1 ) return QSym(a,getModule())==1;

       if( b==Pminus1 ) return QSym(a,getModule())==-1;
       
       return false;
      }
   };
  
  template <class Random>
  static bool RandomTest(Integer P,ulen count,Random &random)
   {
    if( P==2 ) return true;
    
    if( P<2 || P.isEven() ) return false;
    
    ExpEngine engine(P);
    
    for(; count ;count--)
      {
       ulen index=random.template select_uint<ulen>(DimOf(SmallPrimes));
       
       unsigned a=SmallPrimes[index];
       
       if( a<P )
         {
          if( !engine.test(a) ) return false;
         }
       else 
         {
          if( a==P ) return true;
          
          if( !engine.test(a%P) ) return false;
         }
      }
    
    return true;
   }
 };

} // namespace Math
} // namespace CCore
 
#endif
 

