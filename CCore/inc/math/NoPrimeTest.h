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

/* functions */

void GuardNoPrimeTestBadInput();

/* classes */

template <class Integer> struct NoPrimeTest;

/* struct NoPrimeTest<Integer> */

template <class Integer> 
struct NoPrimeTest
 {
  using Unit = typename Integer::Unit ;
  
  // simple
  
  class BitScanner : NoCopy
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
    
     explicit BitScanner(const Integer &a_) // a >= 0
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
     
     ~BitScanner() {}
     
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
  
  static Integer ModExp(Integer a,Integer P) // a >= 0 , P > 1 , return a ^ (P>>1) ( mod P )
   {
    Integer b=1;
    
    BitScanner scanner(P);
    
    ++scanner;
    
    for(; +scanner ;++scanner)
      {
       if( *scanner ) b=ModMul(b,a,P);
        
       a=ModMul(a,a,P); 
      }
    
    return b;
   }
  
  // advanced
  
  static const unsigned Delta = 4 ; 
  
  static_assert( (Integer::UnitBits%Delta)==0 ,"CCore::Math::NoPrimeTest<Integer> : bad Integer::UnitBits");
  
  static const Unit Mask = (Unit(1)<<Delta)-1 ;
  
  class ExpEngine : NoCopy
   {
     ModEngine<Integer> engine;
     
     static const ulen Len = (ulen(1)<<Delta)-1 ;
    
     Integer pow[Len];
     Integer result;
     
     Integer P1; // P-1
     
    private: 
    
     Integer sq(Integer a)
      {
       return engine.mod(a.sq());
      }
     
     Integer mul(Integer a,Integer b)
      {
       return engine.mod(a*b);
      }
     
     void init(Integer a) // a >= 0 , a < P
      {
       result=1;
       
       pow[0]=a;
       pow[1]=sq(a);
       
       for(ulen i=2; i<Len ;i++) pow[i]=mul(pow[i-1],a);
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
     
    public: 
    
     explicit ExpEngine(const Integer &P) : engine(P) { P1=P-1; } // P > 1
     
     const Integer & getModule() const { return engine.getModule(); }
     
     Integer exp(Integer a) // a >= 0 , a < P , return a ^ (P>>1) ( mod P )
      {
       init(a);
       
       auto r=RangeReverse(getModule().getBody());
       
       for(; r.len>1 ;++r) next_unit(*r);
       
       last_unit(*r);
       
       return result;
      }
  
     bool test(Integer a) // a > 0 , a < P , P > 1 , P is odd
      {
       Integer b=exp(a);
       
       if( b.cmp(1)==0 ) return QSym(a,getModule())==1;

       if( b==P1 ) return QSym(a,getModule())==-1;
       
       return false;
      }
   };
  
  class RandomTest : NoCopy
   {
     PlatformRandom random;
     
     ExpEngine engine;
     
    public:
   
     explicit RandomTest(const Integer &P) // P > 1 , P is odd
      : engine(P) 
      {
       if( P.cmp(1)<=0 || P.isEven() ) GuardNoPrimeTestBadInput();
      } 
     
     ~RandomTest()
      {
      }
     
     bool operator () (ulen count)
      {
       for(; count ;count--)
         {
          ulen index=random.select_uint<ulen>(DimOf(SmallPrimes));
          
          unsigned a=SmallPrimes[index];
          
          if( engine.getModule().cmp(a)>0 )
            {
             if( !engine.test(a) ) return false;
            }
         }
       
       return true;
      }
   };
 };

} // namespace Math
} // namespace CCore
 
#endif
 

