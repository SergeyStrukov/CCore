/* test0063.Collector.cpp */ 
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
#include <CCore/test/testArray.h>

namespace App {

namespace Private_0063 {


} // namespace Private_0063
 
using namespace Private_0063; 
 
/* Testit<63> */ 

template<>
const char *const Testit<63>::Name="Test63 Collector";

template<>
bool Testit<63>::Main() 
 {
  // 1
  {
   Collector<int> col(10);
   
   Printf(Con,"#;\n\n",PrintSet(col.flat()));
   
   for(int i=1; i<5 ;i++) col.append_copy(i);
   
   Printf(Con,"#;\n\n",PrintSet(col.flat()));
   
   for(int i=1; i<10 ;i++) col.append_copy(i);
   
   Printf(Con,"#;\n\n",PrintSet(col.flat()));
   
   for(int i=1; i<20 ;i++) col.append_copy(i);
   
   Printf(Con,"#;\n\n",PrintSet(col.flat()));
  }
  
  // 2
  {
   Collector<int> col(10);
   
   for(int i=1; i<5 ;i++) col.append_copy(i);
   
   for(int i=1; i<10 ;i++) col.append_copy(i);
   
   for(int i=1; i<20 ;i++) col.append_copy(i);
   
   DynArray<int> arr;
   
   col.extractTo(arr);
   
   Printf(Con,"#;\n\n",PrintSet(Range_const(arr)));
   
   col.extend_fill(5,5);
   col.extend_fill(10,10);
   col.extend_fill(15,15);
   
   col.extractTo(arr);
   
   Printf(Con,"#;\n\n",PrintSet(Range_const(arr)));
  }
  
  // 3
  {
   Collector<int> col(10);
   
   for(int i=1; i<5 ;i++) col.append_copy(i);
   
   for(int i=1; i<10 ;i++) col.append_copy(i);
   
   col.shrink_one();
   col.shrink_one();
   col.shrink_one();
   col.shrink_one();
   col.shrink_one();
   col.shrink_one();
   col.shrink_one();
   col.shrink_one();
   
   Printf(Con,"#;\n\n",PrintSet(col.flat()));
  }
  
  // 3
  {
   Collector<int> col(10);
   
   for(int i=1; i<5 ;i++) col.append_copy(i);
   
   for(int i=1; i<10 ;i++) col.append_copy(i);
   
   Printf(Con,"#; ",col.shrink(8));
   
   Printf(Con,"#;\n\n",PrintSet(col.flat()));
   
   Printf(Con,"#; ",col.shrink_all());
   
   Printf(Con,"#;\n\n",PrintSet(col.flat()));
  }
  
  // 4
  {
   Collector<int> col(10);
   
   for(int i=1; i<5 ;i++) col.append_copy(i);
   
   for(int i=1; i<10 ;i++) col.append_copy(i);
   
   Printf(Con,"#; ",col.shrink(18));
   
   Printf(Con,"#;\n\n",PrintSet(col.flat()));
  }
  
  // 5
  {
   Collector<int> col(10);
   
   for(int i=1; i<5 ;i++) col.append_copy(i);
   
   for(int i=1; i<10 ;i++) col.append_copy(i);
   
   for(int i=1; i<20 ;i++) col.append_copy(i);
   
   DynArray<int> arr;
   
   col.copyTo(arr);
   
   Printf(Con,"#;\n\n",PrintSet(Range_const(arr)));
   
   col.extend_fill(5,5);
   col.extend_fill(10,10);
   col.extend_fill(15,15);
   
   col.copyTo(arr);
   
   Printf(Con,"#;\n\n",PrintSet(Range_const(arr)));
  }
  
  return true;
 }
 
} // namespace App
 
