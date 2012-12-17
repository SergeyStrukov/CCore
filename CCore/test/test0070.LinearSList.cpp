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

namespace App {

namespace Private_0070 {

void test1()
 {
  LinearSList<int,NodePoolAllocator> list;
  
  Printf(Con,"no top is #;\n",!list.getTop());
  
  for(int i=1; i<10 ;i++) list.ins(i);
  
  Printf(Con,"top #;\n",*list.getTop());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  list.apply( [] (int &obj) { obj+=100; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.del() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStart(); +cur ;++cur)
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
  
  Printf(Con,"no first is #;\n",!list.getFirst());
  Printf(Con,"no last is #;\n",!list.getLast());
  
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
  
  for(auto cur=list.getStart(); +cur ;++cur)
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
  
  Printf(Con,"no bottom is #;\n",!list.getBottom());
  
  for(int i=1; i<10 ;i++) list.ins(i);
  
  Printf(Con,"bottom #;\n",*list.getBottom());
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  list.apply( [] (int &obj) { obj+=100; } );
  
  for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  if( list.del() ) for(int obj : list ) Printf(Con,"#;\n",obj);
  
  Putch(Con,'\n');
  
  for(auto cur=list.getStart(); +cur ;++cur)
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

} // namespace Private_0070
 
using namespace Private_0070; 
 
/* Testit<70> */ 

template<>
const char *const Testit<70>::Name="Test70 LinearSList";

template<>
bool Testit<70>::Main() 
 {
  //test1();
  //test2();
  test3();
  
  return true;
 }
 
} // namespace App
 
