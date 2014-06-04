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

#include <CCore/inc/math/Integer.h>
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
  
  // simple
  
  class BitScaner : NoCopy
   {
     Integer a;
     
     PtrLen<const Unit> cur;
     Unit cur_unit;
     Unit bit;
     
    private:
     
     void next_unit()
      {
       cur_unit=*cur;
      
       ++cur;
     
       bit=1;
      }
     
    public: 
    
     explicit BitScaner(const Integer &a_) // a >= 0
      : a(a_) 
      {
       cur=a.getBody();

       if( cur.len )
         {
          next_unit();
         }
       else
         {
          cur_unit=0;
          bit=1;
         }
      }
     
     ~BitScaner() {}
     
     bool operator + () const { return cur.len || ( bit<=cur_unit ) ; }
     
     bool operator ! () const { return !+(*this); }
     
     Unit operator * () const { return cur_unit&bit; }
     
     void operator ++ ()
      {
       bit<<=1;
       
       if( !bit ) next_unit();
      }
   };
  
  static Integer ModMul(Integer a,Integer b,Integer P) // a,b >= 0 , P > 0
   {
    return (a*b)%P;
   }
  
  static Integer ModExp2(Integer a,Integer P) // a >= 0 , P > 1 , a ^ (P>>1) ( mod P )
   {
    Integer b=1;
    
    BitScaner scaner(P);
    
    ++scaner;
    
    for(; +scaner ;++scaner)
      {
       if( *scaner ) b=ModMul(b,a,P);
        
       a=ModMul(a,a,P); 
      }
    
    return b;
   }
  
  // advanced
  
  static const unsigned Delta = 4 ; 
  
  static_assert( (Integer::UnitBits%Delta)==0 ,"CCore::Math::NoPrimeTest<Integer> : bad Integer::UnitBits");
  
  static const Unit Mask = (Unit(1)<<Delta)-1 ;
  
  struct ModEngine : NoCopy
   {
    Integer P;
    Integer Q;
    ulen n;
    
    class Builder
     {
       ulen n;
       
      public:
      
       explicit Builder(ulen n_) : n(n_) {}
       
       ulen getLen() const { return LenAdd(n,1); }
       
       PtrLen<Unit> operator () (Place<void> place) const
        {
         Unit *base=place;
         
         Range(base,n).set_null();
         
         base[n]=1;
         
         return Range(base,n+1);
        }
     };
    
    explicit ModEngine(Integer P_) // P > 0
     : P(P_)
     {
      n=P.getBody().len;
      
      n=LenAdd(n,n);
      
      Q=Integer(DoBuild,Builder(n))/P;
     }
    
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
  
  struct ExpEngine : ModEngine
   {
    using ModEngine::mod;
    
    static const ulen Len = (ulen(1)<<Delta)-1 ;
    
    Integer pow[Len];
    Integer result;
    
    Integer sq(Integer a)
     {
      return mod(a.sq());
     }
    
    Integer mul(Integer a,Integer b)
     {
      return mod(a*b);
     }
    
    ExpEngine(Integer a,Integer P) // a >= 0 , P > 1
     : ModEngine(P),
       result(1)
     {
      a%=P;
      
      pow[0]=a;
      
      for(ulen i=1; i<Len ;i++) pow[i]=mul(pow[i-1],a);
     }
    
    void next(Unit bits)
     {
      for(unsigned cnt=Delta; cnt ;cnt--) result=sq(result);
      
      if( bits ) result=mul(result,pow[bits-1]);
     }
    
    void last(Unit bits)
     {
      for(unsigned cnt=Delta-1; cnt ;cnt--) result=sq(result);
      
      bits>>=1;
      
      if( bits ) result=mul(result,pow[bits-1]);
     }
   
    void next_unit(Unit unit)
     {
      for(unsigned off=Integer::UnitBits-Delta; off ;off-=Delta) next( (unit>>off)&Mask );
      
      next( unit&Mask );
     }
    
    void last_unit(Unit unit)
     {
      for(unsigned off=Integer::UnitBits-Delta; off ;off-=Delta) next( (unit>>off)&Mask );
      
      last( unit&Mask );
     }
   };
  
  static Integer ModExp(Integer a,Integer P) // a >= 0 , P > 1 , a ^ (P>>1) ( mod P )
   {
    ExpEngine engine(a,P);
    
    auto r=RangeReverse(P.getBody());
    
    for(; r.len>1 ;++r) engine.next_unit(*r);
    
    engine.last_unit(*r);
    
    return engine.result;
   }

  static bool TestEvidence(Integer a,Integer P) // a > 0 , P > 1 , P is odd
   {
    Integer b=ModExp(a,P);
    
    if( b==1 ) return QSym(a,P)==1;

    if( b+1==P ) return QSym(a,P)==-1;
    
    return false;
   }
  
  class RandomTest : NoCopy
   {
     PlatformRandom random;
     
    public:
   
     RandomTest()
      {
      }
     
     ~RandomTest()
      {
      }
     
     bool test(Integer P,ulen count)
      {
       if( P.cmp(1)<=0 || P.isEven() ) return false;
       
       for(; count ;count--)
         {
          ulen index=random.select_uint<ulen>(DimOf(SmallPrimes));
          
          if( !TestEvidence(SmallPrimes[index],P) ) return false;
         }
       
       return true;
      }
   };
 };

} // namespace Math
} // namespace CCore
 
#endif
 

