/* test0061.SHA-speed.cpp */ 
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

#include <CCore/inc/crypton/SHA.h> 
#include <CCore/inc/Random.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_0061 {

/* class Test */

class Test : NoCopy
 {
   Random random;
   
  public:
   
   Test() {}
   
   ~Test() {}
   
   static uint8 Sum(PtrLen<const uint8> r)
    {
     uint8 ret=0;
     
     for(; +r ;++r) ret+=*r;
     
     return ret;
    }
   
   template <class H>
   void test(ulen len,ulen rep)
    {
     H hash;
     uint8 buf[100];
     uint8 digest[H::DigestLen];
     
     SecTimer timer;
     
     for(ulen cnt=rep; cnt ;cnt--)
       {
        for(ulen cnt=len; cnt ;)
          {
           ulen delta=random.select(1,Min(cnt,DimOf(buf)));
           
           auto r=Range(buf,delta);
           
           random.fill(r);
           hash.add(Range_const(r));
           
           cnt-=delta;
          }
        
        hash.finish(digest);
       }
     
     auto t=timer.get();
     
     if( !t ) t=1;
     
     uint64 s=uint64(len)*rep;
     uint8 sum=Sum(Range_const(digest));
     
     Printf(Con,"#; len = #; byte time = #; sec speed = #; Mbips\n",H::GetName(),s,t,((s*8)/t)/1000000,sum);
    }
 };

} // namespace Private_0061
 
using namespace Private_0061; 
 
/* Testit<61> */ 

template<>
const char *const Testit<61>::Name="Test61 SHA speed";

template<>
bool Testit<61>::Main() 
 {
  Test test;
  
  test.test<Crypton::SHA1>(1000000,100);
  test.test<Crypton::SHA256>(1000000,100);
  test.test<Crypton::SHA512>(1000000,100);
  
  return true;
 }
 
} // namespace App
 
