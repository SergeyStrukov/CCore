/* test0070.LinearSList.cpp */ 
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

#include <CCore/inc/ContainerList.h>
#include <CCore/inc/CompactList.h>

namespace App {

namespace Private_0070 {

void test1()
 {
  LinearSList<int,NodePoolAllocator> list;
  
  Printf(Con,"no top is #;\n",!list.getTop_const());
  
  for(int i=1; i<10 ;i++) list.ins(i);
  
  Printf(Con,"top #;\n",*list.getTop());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  list.apply( [] (int &obj) { obj+=100; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.del() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStart_const(); +cur ;++cur)
    if( *cur==104 )
      {
       list.insAfter(cur,1000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"#;\n",list.erase());
  
  Printf(Con,"#;\n",list.getCount());
 }

void test2()
 {
  LinearSList2<int,NodePoolAllocator> list;
  
  Printf(Con,"no first is #;\n",!list.getFirst_const());
  Printf(Con,"no last is #;\n",!list.getLast_const());
  
  for(int i=1; i<5 ;i++) list.insFirst(i);
  for(int i=5; i<10 ;i++) list.insLast(i);
  
  Printf(Con,"first #;\n",*list.getFirst());
  Printf(Con,"last #;\n",*list.getLast());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  list.apply( [] (int &obj) { obj+=100; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.delFirst() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStart_const(); +cur ;++cur)
    if( *cur==105 )
      {
       list.insAfter(cur,1000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"#;\n",list.erase());
  
  Printf(Con,"#;\n",list.getCount());
 }

void test3()
 {
  CircularSList<int,NodePoolAllocator> list;
  
  Printf(Con,"no bottom is #;\n",!list.getBottom_const());
  
  for(int i=1; i<10 ;i++) list.ins(i);
  
  Printf(Con,"bottom #;\n",*list.getBottom());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  list.apply( [] (int &obj) { obj+=100; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.del() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStart_const(); +cur ;++cur)
    if( *cur==104 )
      {
       list.insAfter(cur,1000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"rotate #;\n",*list.rotate());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"#;\n",list.erase());
  
  Printf(Con,"#;\n",list.getCount());
 }

void test4()
 {
  LinearDList<int,NodePoolAllocator> list;
  
  Printf(Con,"no top is #;\n",!list.getTop_const());
  
  for(int i=1; i<10 ;i++) list.ins(i);
  
  Printf(Con,"top #;\n",*list.getTop());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  list.apply( [] (int &obj) { obj+=100; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.del() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStart_const(); +cur ;++cur)
    if( *cur==104 )
      {
       list.insBefore(cur,1000);
       list.insAfter(cur,2000);
       
       list.delAndMove(cur);
       
       --cur;
       
       list.insAfter(cur,3000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"#;\n",list.erase());
  
  Printf(Con,"#;\n",list.getCount());
 }

void test5()
 {
  LinearDList2<int,NodePoolAllocator> list;
  
  Printf(Con,"no first is #;\n",!list.getFirst_const());
  Printf(Con,"no last is #;\n",!list.getLast_const());
  
  for(int i=1; i<5 ;i++) list.insFirst(i);
  for(int i=5; i<10 ;i++) list.insLast(i);
  
  Printf(Con,"first #;\n",*list.getFirst());
  Printf(Con,"last #;\n",*list.getLast());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  list.apply( [] (int &obj) { obj+=100; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.delFirst() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.delLast() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStart_const(); +cur ;++cur)
    if( *cur==105 )
      {
       list.insBefore(cur,1000);
       list.insAfter(cur,2000);
       
       list.delAndMove(cur);
       
       --cur;
       
       list.insAfter(cur,3000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStartReverse_const(); +cur ;++cur)
    if( *cur==101 )
      {
       list.insBefore(cur,1000);
       list.insAfter(cur,2000);
       
       list.delAndMove(cur);
       
       --cur;
       
       list.insAfter(cur,3000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(int obj : list.reverse_const() ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  int k=1;
  
  list.applyReverse( [&k] (int &obj) { obj-=k++; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"#;\n",list.erase());
  
  Printf(Con,"#;\n",list.getCount());
 }

void test6()
 {
  CircularDList<int,NodePoolAllocator> list;
  
  Printf(Con,"no top is #;\n",!list.getTop_const());
  
  for(int i=1; i<5 ;i++) list.insFirst(i);
  for(int i=5; i<10 ;i++) list.insLast(i);
  
  Printf(Con,"top #;\n",*list.getTop());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"forward #;\n",*list.rotateForward());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"backward #;\n",*list.rotateBackward());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  list.apply( [] (int &obj) { obj+=100; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.delFirst() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.delLast() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStart_const(); +cur ;++cur)
    if( *cur==105 )
      {
       list.insBefore(cur,1000);
       list.insAfter(cur,2000);
       
       list.delAndMove(cur);
       
       --cur;
       
       list.insAfter(cur,3000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStartReverse_const(); +cur ;++cur)
    if( *cur==101 )
      {
       list.insBefore(cur,1000);
       list.insAfter(cur,2000);
       
       list.delAndMove(cur);
       
       --cur;
       
       list.insAfter(cur,3000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(int obj : list.reverse_const() ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  int k=1;
  
  list.applyReverse( [&k] (int &obj) { obj-=k++; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"#;\n",list.erase());
  
  Printf(Con,"#;\n",list.getCount());
 }

template <class T,template <class Node> class Allocator>
void Ins(LinearSList<T,Allocator> &list,const T &obj)
 {
  list.ins(obj);
 }

template <class T,template <class Node> class Allocator>
void Ins(LinearSList2<T,Allocator> &list,const T &obj)
 {
  list.insFirst(obj);
 }

template <class T,template <class Node> class Allocator>
void Ins(CircularSList<T,Allocator> &list,const T &obj)
 {
  list.ins(obj);
 }

template <class T,template <class Node> class Allocator>
void Ins(LinearDList<T,Allocator> &list,const T &obj)
 {
  list.ins(obj);
 }

template <class T,template <class Node> class Allocator>
void Ins(LinearDList2<T,Allocator> &list,const T &obj)
 {
  list.insFirst(obj);
 }

template <class T,template <class Node> class Allocator>
void Ins(CircularDList<T,Allocator> &list,const T &obj)
 {
  list.insFirst(obj);
 }

template <class T>
void Ins(CompactList<T> &list,const T &obj)
 {
  list.ins(obj);
 }

template <class T>
void Ins(CompactList2<T> &list,const T &obj)
 {
  list.insFirst(obj);
 }

template <class T>
void Ins(CompactCircularList<T> &list,const T &obj)
 {
  list.insFirst(obj);
 }

template <class T>
void testSwap()
 {
  T list;
  
  for(int i=1; i<1000 ;i++) Ins(list,i);
  
  T list1;
  
  Swap(list,list1);
  
  int s=0;
  
  list1.apply( [&s] (int i) { s+=i; } );
  
  Printf(Con,"#;\n",s);
 }

void test7()
 {
  testSwap<LinearSList<int,NodePoolAllocator> >();
  testSwap<LinearSList2<int,NodePoolAllocator> >();
  testSwap<CircularSList<int,NodePoolAllocator> >();
  testSwap<LinearDList<int,NodePoolAllocator> >();
  testSwap<LinearDList2<int,NodePoolAllocator> >();
  testSwap<CircularDList<int,NodePoolAllocator> >();
  testSwap<CompactList<int> >();
  testSwap<CompactList2<int> >();
  testSwap<CompactCircularList<int> >();
 }

template <class T>
void testMove()
 {
  InitExitObject<T> init_obj;
  InitStorage<sizeof (T)> mem;
  
  init_obj.clean();
  init_obj.init();
  
  for(int i=1; i<1000 ;i++) Ins(*init_obj,i);

  T *map=Move(init_obj.getPtr(),mem.getPlace());
    
  int s=0;
    
  map->apply( [&s] (int i) { s+=i; } );
    
  Printf(Con,"#;\n",s);
  
  map->~T();
 }

void test8()
 {
  testMove<LinearSList<int,NodePoolAllocator> >();
  testMove<LinearSList2<int,NodePoolAllocator> >();
  testMove<CircularSList<int,NodePoolAllocator> >();
  testMove<LinearDList<int,NodePoolAllocator> >();
  testMove<LinearDList2<int,NodePoolAllocator> >();
  testMove<CircularDList<int,NodePoolAllocator> >();
  testMove<CompactList<int> >();
  testMove<CompactList2<int> >();
  testMove<CompactCircularList<int> >();
 }

void test9()
 {
  CompactList<int> list;
  
  Printf(Con,"no top is #;\n",!list.getTop_const());
  
  for(int i=1; i<10 ;i++) list.ins(i);
  
  Printf(Con,"top #;\n",*list.getTop());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  list.apply( [] (int &obj) { obj+=100; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.del() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStart_const(); +cur ;++cur)
    if( *cur==104 )
      {
       list.insBefore(cur,1000);
       list.insAfter(cur,2000);
       
       list.delAndMove(cur);
       
       --cur;
       
       list.insAfter(cur,3000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"#;\n",list.erase());
  
  Printf(Con,"#;\n",list.getCount());
 }

void test10()
 {
  CompactList2<int> list;
  
  Printf(Con,"no first is #;\n",!list.getFirst_const());
  Printf(Con,"no last is #;\n",!list.getLast_const());
  
  for(int i=1; i<5 ;i++) list.insFirst(i);
  for(int i=5; i<10 ;i++) list.insLast(i);
  
  Printf(Con,"first #;\n",*list.getFirst());
  Printf(Con,"last #;\n",*list.getLast());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  list.apply( [] (int &obj) { obj+=100; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.delFirst() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.delLast() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStart_const(); +cur ;++cur)
    if( *cur==105 )
      {
       list.insBefore(cur,1000);
       list.insAfter(cur,2000);
       
       list.delAndMove(cur);
       
       --cur;
       
       list.insAfter(cur,3000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStartReverse_const(); +cur ;++cur)
    if( *cur==101 )
      {
       list.insBefore(cur,1000);
       list.insAfter(cur,2000);
       
       list.delAndMove(cur);
       
       --cur;
       
       list.insAfter(cur,3000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(int obj : list.reverse_const() ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  int k=1;
  
  list.applyReverse( [&k] (int &obj) { obj-=k++; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"#;\n",list.erase());
  
  Printf(Con,"#;\n",list.getCount());
 }

void test11()
 {
  CompactCircularList<int> list;
  
  Printf(Con,"no top is #;\n",!list.getTop_const());
  
  for(int i=1; i<5 ;i++) list.insFirst(i);
  for(int i=5; i<10 ;i++) list.insLast(i);
  
  Printf(Con,"top #;\n",*list.getTop_const());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"forward #;\n",*list.rotateForward());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"backward #;\n",*list.rotateBackward());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  list.apply( [] (int &obj) { obj+=100; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.delFirst() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.delLast() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStart_const(); +cur ;++cur)
    if( *cur==105 )
      {
       list.insBefore(cur,1000);
       list.insAfter(cur,2000);
       
       list.delAndMove(cur);
       
       --cur;
       
       list.insAfter(cur,3000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStartReverse_const(); +cur ;++cur)
    if( *cur==101 )
      {
       list.insBefore(cur,1000);
       list.insAfter(cur,2000);
       
       list.delAndMove(cur);
       
       --cur;
       
       list.insAfter(cur,3000);
       
       break;
      }
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(int obj : list.reverse_const() ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  int k=1;
  
  list.applyReverse( [&k] (int &obj) { obj-=k++; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  Printf(Con,"#;\n",list.erase());
  
  Printf(Con,"#;\n",list.getCount());
 }

} // namespace Private_0070
 
using namespace Private_0070; 
 
/* Testit<70> */ 

template<>
const char *const Testit<70>::Name="Test70 LinearSList";

template<>
bool Testit<70>::Main() 
 {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  test11();
  
  return true;
 }
 
} // namespace App
 
