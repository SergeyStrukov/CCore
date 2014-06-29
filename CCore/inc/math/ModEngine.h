/* ModEngine.h */ 
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

#ifndef CCore_inc_math_ModEngine_h
#define CCore_inc_math_ModEngine_h

#include <CCore/inc/math/Integer.h>
 
namespace CCore {
namespace Math {

/* classes */

template <class Integer> class UnitsPowInteger;

template <class Integer> class ModEngine;

/* class UnitsPowInteger<Integer> */

template <class Integer> 
class UnitsPowInteger : public Integer
 {
   class Builder
    {
      ulen n;
      
     public:
     
      explicit Builder(ulen n_) : n(n_) {}
      
      ulen getLen() const { return LenAdd(n,1); }
      
      using Unit = typename Integer::Unit ;
      
      PtrLen<Unit> operator () (Place<void> place) const
       {
        Unit *base=place;
        
        Integer::AlgoType::Null(base,n);
        
        base[n]=1;
        
        return Range(base,n+1);
       }
    };
   
  public:
  
   explicit UnitsPowInteger(ulen n) // creates B^n , B = 2^UnitBits
    : Integer(DoBuild,Builder(n))
    {
    }
 };

/* class ModEngine<Integer> */

template <class Integer> 
class ModEngine : NoCopy
 {
   Integer P;
   Integer Q;
   ulen n;

  public: 
   
   explicit ModEngine(const Integer &P_) // P_ > 0
    : P(P_)
    {
     n=P.getBody().len;
     
     n=LenAdd(n,n);
     
     Q=UnitsPowInteger<Integer>(n)/P;
    }
   
   const Integer & getModule() const { return P; }
   
   Integer mod(Integer a) // a >= 0 , a < P^2
    {
     Integer b=a*Q;
     Integer c;
     
     auto body=b.getBody();
     
     if( body.len>n )
       {
        body+=n;
        
        c=Integer::Mul(P.getBody(),body);
       }
     
     a-=c;
     
     if( a>=P ) a-=P;
     
     return a;
    }
 };

} // namespace Math
} // namespace CCore
 
#endif
 

