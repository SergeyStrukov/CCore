/* test0011.PrintSet.cpp */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/PrintSet.h>
#include <CCore/inc/List.h>

namespace App {

namespace Private_0011 {

/* struct Test */

struct Test
 {
  SLink<Test> link;
  unsigned value;
  
  typedef unsigned PrintProxyType;
  
  operator unsigned() const { return value; }
 };
 
} // namespace Private_0011
 
using namespace Private_0011; 
 
/* Testit<11> */ 

template<>
const char *const Testit<11>::Name="Test11 PrintSet";

template<>
bool Testit<11>::Main() 
 { 
  {
   int data[]={-1,2,-3,4,-5,6,-7,8,-9,10};
   
   Printf(Con,"#;\n",PrintSet(Range(data)));
   Printf(Con,"#+3;\n",PrintSet(Range(data)));
  }
  
  {
   typedef SLink<Test>::LinearAlgo<&Test::link> Algo;
   
   Test test[10];
   Algo::Top top;
   
   for(unsigned i=0; i<DimOf(test) ;i++)
     {
      test[i].value=i;
      
      top.ins(test+i);
     }
     
   Printf(Con,"#;\n",PrintSet(top.start()));  
  }
  
  return true;
 }
 
} // namespace App
 
