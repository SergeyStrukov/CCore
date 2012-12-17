/* test0071.GCD.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.03
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/algon/CommonIntAlgo.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_0071 {

/* class RandomGen */

class RandomGen : NoCopy
 {
   Random random;
   
  public:
   
   RandomGen() {}
   
   operator unsigned()
    {
     const unsigned Bits = Meta::UIntBits<unsigned>::Ret/2-1 ;
     const unsigned Mask = (1u<<Bits)-1 ;
     
     return random.next_uint<unsigned>()&Mask;
    }
 };

/* functions */

unsigned GCD(unsigned a,unsigned b) { return Algon::CommonIntAlgo<unsigned>::GCD(a,b); }

void test1(unsigned a,unsigned b)
 {
  Printf(Con,"a = #; b = #; GCD = #;\n",a,b,GCD(a,b));
 }

void test2(unsigned a,unsigned b,unsigned d)
 {
  if( GCD(a,b)!=GCD(b,a) ) Printf(Exception,"1");
  
  if( GCD(a*d,b*d)!=GCD(a,b)*d ) Printf(Exception,"2");
  
  if( GCD(a,b)!=GCD(a+b*d,b) ) Printf(Exception,"3");
 }

} // namespace Private_0071
 
using namespace Private_0071; 
 
/* Testit<71> */ 

template<>
const char *const Testit<71>::Name="Test71 GCD";

template<>
bool Testit<71>::Main() 
 {
  {
   test1(2,4); 
   test1(16,32);
   test1(3,5);
  }
  
  {
   RandomGen gen;
   
   for(ulen cnt=1000000; cnt ;cnt--)
     {
      unsigned a=gen;
      unsigned b=gen;
      unsigned d=gen;
      
      test2(a,b,d);
     }
  }
  
  return true;
 }
 
} // namespace App
 
