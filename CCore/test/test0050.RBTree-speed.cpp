/* test0050.RBTree-speed.cpp */ 
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
#include <CCore/test/testRBTree.h>

#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_0050 {

/* struct Node */

struct Node
 {
  RBTreeLink<Node,uint32> link;
 };

/* test<Algo>() */ 

template <class Algo>
void test()
 {
  OwnPtr<SpeedEngine<Node,Algo> > engine(new SpeedEngine<Node,Algo>());
  
  engine->test_ins();
  
  engine->test_del();
 }

} // namespace Private_0050
 
using namespace Private_0050; 
 
/* Testit<50> */ 

template<>
const char *const Testit<50>::Name="Test0050 RBTree-speed";

template<>
bool Testit<50>::Main() 
 {
  Printf(Con,"#;\n\n",Title("Algo"));
  
  test<RBTreeLink<Node,uint32>::Algo<&Node::link> >();
  
  Printf(Con,"#;\n\n",Title("AltAlgo"));
  
  test<RBTreeLink<Node,uint32>::AltAlgo<&Node::link> >();
  
  return true;
 }
 
} // namespace App
 
