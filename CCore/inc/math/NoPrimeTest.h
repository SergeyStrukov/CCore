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

template <class Int> struct NoPrimeTest;

/* struct NoPrimeTest<Int> */

template <class Int> 
struct NoPrimeTest
 {
  using Unit = typename Int::Unit ;
  
  class BitScaner : NoCopy
   {
     Int a;
     
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
    
     explicit BitScaner(const Int &a_) // a >= 0
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
  
  static Int ModMul(Int a,Int b,Int P) // a,b >= 0 , P > 0
   {
    return (a*b)%P;
   }
  
  static Int ModExp(Int a,Int P) // a >= 0 , P > 1 , P is odd , a ^ (P-1)/2 ( mod P )
   {
    Int b=1;
    
    BitScaner scaner(P);
    
    ++scaner;
    
    for(; +scaner ;++scaner)
      {
       if( *scaner ) b=ModMul(b,a,P);
        
       a=ModMul(a,a,P); 
      }
    
    return b;
   }

  static bool TestEvidence(Int a,Int P) // a > 0 , P > 1 , P is odd
   {
    Int b=ModExp(a,P);
    
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
     
     bool test(Int P,ulen count) // P > 1 , P is odd
      {
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
 

