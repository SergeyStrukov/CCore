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

namespace App {

namespace Private_0069 {


} // namespace Private_0069
 
using namespace Private_0069; 
 
/* Testit<69> */ 

template<>
const char *const Testit<69>::Name="Test69 RBTreeMap";

template<>
bool Testit<69>::Main() 
 {
  {
   RBTreeMap<int,int> map;
   
   for(int i=1; i<10 ;i++) map.find_or_add(i,i);
   
   map.applyIncr( [] (int key,int obj) { Printf(Con,"#; #;\n",key,obj); } );
   
   map.applyDecr( [] (int key,int obj) { Printf(Con,"#; #;\n",key,obj); } );
  }
  
  {
   RBTreeMap<int,int,int,NodePoolAllocator> map;
   
   for(int i=1; i<10 ;i++) map.find_or_add(i,i);
   
   map.applyIncr( [] (int key,int obj) { Printf(Con,"#; #;\n",key,obj); } );
   
   map.applyDecr( [] (int key,int obj) { Printf(Con,"#; #;\n",key,obj); } );
  }
  
  return true;
 }
 
} // namespace App
 
