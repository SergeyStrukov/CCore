/* test3006.IntelAESSpeed.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/WIN32 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/crypton/IntelAES.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_3006 {

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
     
     uint64 s=buf.getLen()*(uint64)rep;
     
     Printf(Con,"#; len = #; byte time = #; sec speed = #; Mbips\n",C::GetName(),s,t,((s*8)/t)/1000000,sum);
    }
 };

} // namespace Private_3006
 
using namespace Private_3006; 
 
/* Testit<3006> */ 

template<>
const char *const Testit<3006>::Name="Test3006 IntelAESSpeed";

template<>
bool Testit<3006>::Main() 
 {
  Test test;
  
  test.test<Crypton::IntelAES128>(100000);
  test.test<Crypton::IntelAES192>(100000);
  test.test<Crypton::IntelAES256>(100000);
  
  test.test<Crypton::IntelAESInverse128>(100000);
  test.test<Crypton::IntelAESInverse192>(100000);
  test.test<Crypton::IntelAESInverse256>(100000);
  
  return true;
 }
 
} // namespace App
 
