/* test0086.RandomSelect.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Random.h>

namespace App {

namespace Private_0086 {


} // namespace Private_0086
 
using namespace Private_0086; 
 
/* Testit<86> */ 

template<>
const char *const Testit<86>::Name="Test86 RandomSelect";

template<>
bool Testit<86>::Main() 
 {
  Random random;
  
  for(ulen cnt=100; cnt ;cnt--)
    Printf(Con,"#;\n",random.select_uint<uint64>(1,1000));
  
  for(ulen cnt=10000000; cnt ;cnt--)
    {
     uint8 a=random.next8();
     uint32 b=random.next32();
     uint8 lim=random.next8();
     
     if( !lim ) continue;
     
     uint8 res1=RandomSelect<uint8>::Do(a,b,lim);
     uint8 res2=uint8( ((uint64(a)<<32)|b)%lim );
     
     if( res1!=res2 )
       {
        Printf(Exception,"Fault a = #; b = #; lim = #;",a,b,lim);
       }
    }
  
  return true;
 }
 
} // namespace App
 
