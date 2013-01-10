/* test0075.PtrLenReverse.cpp */ 
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
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Array.h>

namespace App {

namespace Private_0075 {

void test1()
 {
  int buf[]={1,2,3,4,5};
  
  for(auto r=RangeReverse(buf); +r ;++r) Printf(Con,"#; ",*r);
  
  Putch(Con,'\n');
 }

void test2()
 {
  int buf[]={1,2,3,4,5};
  
  for(int obj : RangeReverse(buf) ) Printf(Con,"#; ",obj);
  
  Putch(Con,'\n');
 }

void test3()
 {
  DynArray<int> buf{1,2,3,4,5};
  
  for(auto r=RangeReverse(buf); +r ;++r) Printf(Con,"#; ",*r);
  
  Putch(Con,'\n');
 }

template <class R>
void show(R r)
 {
  for(; +r ;++r) Printf(Con,"#; ",*r);
  
  Putch(Con,'\n');
 }

void test4()
 {
  DynArray<int> buf{1,2,3,4,5};
  
  show(Range(buf));
  show(RangeReverse(buf));
 }

void test5()
 {
  int buf[]={1,2,3,4,5};
  
  auto r=RangeReverse(buf);
  
  show(r.prefix(3));
  show(r.suffix(3));
  show(r.prefix(r.suffix(3)));
  show(r.part(1,2));
  show(r.part(1));
  show(r.inner(1,1));
 } 

void test6()
 {
  int buf[]={1,2,3,4,5};
  
  auto r=RangeReverse(buf);

  for(ulen i=0; i<r.len ;i++) Printf(Con,"#; ",r[i]);
  
  Putch(Con,'\n');
  
  for(ulen i=1; i<=r.len ;i++) Printf(Con,"#; ",r.back(i));
  
  Putch(Con,'\n');
 }

void test7()
 {
  int buf[]={1,2,3,4,5};
  
  auto r=RangeReverse(buf);

  show(r+=3);
  show(r);
 }
  
} // namespace Private_0075
 
using namespace Private_0075; 
 
/* Testit<75> */ 

template<>
const char *const Testit<75>::Name="Test75 PtrLenReverse";

template<>
bool Testit<75>::Main() 
 {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  
  return true;
 }
 
} // namespace App
 
