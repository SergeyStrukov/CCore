/* test0073.CompactMap.cpp */ 
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

#include <CCore/inc/CompactMap.h>

namespace App {

namespace Private_0073 {

void test1()
 {
  CompactRBTreeMap<int,int> map;
  
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
  testMap<CompactRBTreeMap<ulen,ulen> >();
  testMap<CompactRadixTreeMap<ulen,ulen> >();
 }

template <class T>
void testSwap()
 {
  T map;
  
  for(int i=1; i<1000 ;i++) map.find_or_add(i,i);
  
  T map1;
  
  Swap(map,map1);
  
  int s=0;
  
  map1.applyIncr( [&s] (int,int i) { s+=i; } );
  
  Printf(Con,"#;\n",s);
 }

template <class T>
void testMove()
 {
  InitExitObject<T> init_obj;
  InitStorage<sizeof (T)> mem;
  
  init_obj.clean();
  init_obj.init();
  
  for(int i=1; i<1000 ;i++) init_obj->find_or_add(i,i);

  T *map=Move(init_obj.getPtr(),mem.getPlace());
    
  int s=0;
    
  map->applyIncr( [&s] (int,int i) { s+=i; } );
    
  Printf(Con,"#;\n",s);
  
  map->~T();
 }

void test3()
 {
  testSwap<CompactRBTreeMap<ulen,ulen> >();
  testMove<CompactRBTreeMap<ulen,ulen> >();
  testSwap<CompactRadixTreeMap<ulen,ulen> >();
  testMove<CompactRadixTreeMap<ulen,ulen> >();
 }

template <class T>
void testSpeed(StrLen name,ulen count)
 {
  T map;

  {
   SecTimer timer;
  
   for(ulen i=0; i<count ;i++) map.find_or_add(i,i);
  
   Printf(Con,"#; : count = #; time = #; sec\n",name,count,timer.get());
  }
  {
   SecTimer timer;
  
   for(ulen i=0; i<count ;i++) map.del(i);
  
   Printf(Con,"time = #; sec\n\n",timer.get());
  }
 }

void test4(ulen count)
 {
  testSpeed<RBTreeMap<ulen,ulen> >("RBTree",count);
  testSpeed<RBTreeMap<ulen,ulen,ulen,NodePoolAllocator> >("RBTree-pool",count);
  testSpeed<CompactRBTreeMap<ulen,ulen> >("CompactRBTree",count);
  testSpeed<CompactRadixTreeMap<ulen,ulen> >("CompactRadixTree",count);
 }

} // namespace Private_0073
 
using namespace Private_0073; 
 
/* Testit<73> */ 

template<>
const char *const Testit<73>::Name="Test73 CompactMap";

template<>
bool Testit<73>::Main() 
 {
  test1();
  test2();
  test3();
  test4(20000000);
  
  return true;
 }
 
} // namespace App
 
