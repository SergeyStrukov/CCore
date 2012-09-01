/* test0059.AES-speed.cpp */ 
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

#include <CCore/inc/crypton/AES.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_0059 {

/* class Test */

class Test : NoCopy
 {
   Random random;
   DynArray<uint8> buf;
   
  public:
   
   Test() : buf(100000) {}
   
   ~Test() {}
   
   template <class C>
   static void Apply(C &cipher,PtrLen<uint8> r)
    {
     for(; r.len>=C::BlockLen ;r+=C::BlockLen) cipher.apply(r.ptr);
    }
   
   static uint8 Sum(PtrLen<const uint8> r)
    {
     uint8 ret=0;
     
     for(; +r ;++r) ret+=*r;
     
     return ret;
    }
   
   template <class C>
   void test(ulen rep)
    {
     uint8 key[C::KeyLen];
     
     random.fill(Range(key));
     
     C cipher(key);
     uint8 sum=0;
     
     SecTimer timer;
     
     for(ulen cnt=rep; cnt ;cnt--)
       {
        auto r=Range(buf);
        
        random.fill(r);
        Apply(cipher,r);
        sum+=Sum(Range_const(r));
       }
     
     auto t=timer.get();
     
     if( !t ) t=1;
     
     uint64 s=buf.getLen()*rep;
     
     Printf(Con,"#; len = #; byte time = #; sec speed = #; Mbips\n",C::GetName(),s,t,((s*8)/t)/1000000,sum);
    }
 };

} // namespace Private_0059
 
using namespace Private_0059; 
 
/* Testit<59> */ 

template<>
const char *const Testit<59>::Name="Test59 AES speed";

template<>
bool Testit<59>::Main() 
 {
  Test test;
  
  test.test<Crypton::AES128>(10000);
  test.test<Crypton::AES192>(10000);
  test.test<Crypton::AES256>(10000);
  
  test.test<Crypton::AESInverse128>(10000);
  test.test<Crypton::AESInverse192>(10000);
  test.test<Crypton::AESInverse256>(10000);
  
  return true;
 }
 
} // namespace App
 
