/* test0064.ElementPool.cpp */ 
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

#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_0064 {

/* functions */

void test1(ulen count,ulen maxlen)
 {
  Random random;
  ElementPool pool(2_KByte);
  
  SecTimer timer;
  
  for(ulen cnt=count; cnt ;cnt--)
    {
     ulen len=random.select(1,maxlen);
     
     pool.createArray<int>(len);
    }
  
  Printf(Con,"#; sec\n",timer.get());
 }

void test2(ulen count)
 {
  Random random;
  ElementPool pool(2_KByte);
  
  SecTimer timer;
  
  for(ulen cnt=count; cnt ;cnt--)
    {
     pool.create<int>(0);
    }
  
  Printf(Con,"#; sec\n",timer.get());
 }

void test3()
 {
  ElementPool pool;
  
  auto str1=pool.cat("prefix","12345","suffix");
  pool.shrink_extra();
  auto str2=pool.cat("prefix","12345","suffix");
  pool.shrink_extra();
  
  Printf(Con,"#;\n#;\n",str1,str2);
 }

} // namespace Private_0064
 
using namespace Private_0064; 
 
/* Testit<64> */ 

template<>
const char *const Testit<64>::Name="Test64 ElementPool";

template<>
bool Testit<64>::Main() 
 {
  test1(100000,1000);
  test1(1000000,100);
  
  test2(1000000);
  test2(10000000);
  test2(100000000);
  
  test3();
  
  return true;
 }
 
} // namespace App
 
