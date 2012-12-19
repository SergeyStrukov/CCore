/* test0069.RBTreeMap.cpp */ 
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

#include <CCore/inc/TreeMap.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_0069 {

void test1()
 {
  RBTreeMap<int,int> map;
  
  for(int i=1; i<10 ;i++) map.find_or_add(i,i);
  
  map.applyIncr( [] (int key,int obj) { Printf(Con,"#; #;\n",key,obj); } );
  
  Putch(Con,'\n');
  
  map.applyDecr( [] (int key,int obj) { Printf(Con,"#; #;\n",key,obj); } );
  
  Putch(Con,'\n');
 }

template <class T>
void testMap()
 {
  T map;
  
  for(int i=1; i<10 ;i++) map.find_or_add(i,i);
  
  map.applyIncr( [] (int key,int obj) { Printf(Con,"#; #;\n",key,obj); } );
  
  Putch(Con,'\n');
  
  map.applyDecr( [] (int key,int obj) { Printf(Con,"#; #;\n",key,obj); } );
  
  Putch(Con,'\n');
  
  for(int i=1; i<10 ;i++)
    {
     Printf(Con,"#;\n",*map.find(i));
    }
  
  for(int i=1; i<10 ;i++) 
    {
     auto result=map.find_or_add(i,-1);
     
     Printf(Con,"#; #;\n",*result.obj,result.new_flag);
    }
  
  Putch(Con,'\n');
  
  map.del(5);
  map.delMin();
  map.delMax();
  
  map.applyIncr( [] (int key,int obj) { Printf(Con,"#; #;\n",key,obj); } );
  
  Putch(Con,'\n');
  
  map.del(map.findMin_ptr(5));
  map.del(map.findMax_ptr(5));
  
  map.applyIncr( [] (int key,int obj) { Printf(Con,"#; #;\n",key,obj); } );
  
  Putch(Con,'\n');
 }

void test2()
 {
  testMap<RBTreeMap<int,int,int,NodePoolAllocator> >();
 }

void test3()
 {
  testMap<RadixTreeMap<unsigned,int> >();
 }

template <class T>
void testSpeed(StrLen name,ulen count)
 {
  T map;
  
  SecTimer timer;
  
  for(ulen i=0; i<count ;i++) map.find_or_add(i,i);
  
  Printf(Con,"#; : count = #; time = #; sec\n",name,count,timer.get());
 }

void test4(ulen count)
 {
  testSpeed<RBTreeMap<ulen,ulen,ulen,NodePoolAllocator> >("RBTree-pool",count);
 }

void test5(ulen count)
 {
  testSpeed<RadixTreeMap<ulen,ulen,NodePoolAllocator> >("RadixTree-pool",count);
 }

void test6(ulen count)
 {
  testSpeed<RBTreeMap<ulen,ulen> >("RBTree",count);
 }

void test7(ulen count)
 {
  testSpeed<RadixTreeMap<ulen,ulen> >("RadixTree",count);
 }

} // namespace Private_0069
 
using namespace Private_0069; 
 
/* Testit<69> */ 

template<>
const char *const Testit<69>::Name="Test69 RBTreeMap";

template<>
bool Testit<69>::Main() 
 {
  //test1();
  //test2();
  //test3();
  //test4(20000000);
  //test5(20000000);
  //test6(20000000);
  //test7(20000000);
  
  return true;
 }
 
} // namespace App
 
