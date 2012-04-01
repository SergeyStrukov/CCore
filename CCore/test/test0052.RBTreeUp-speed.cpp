/* test0052.RBTreeUp-speed.cpp */ 
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

namespace Private_0052 {

/* struct Node */

struct Node
 {
  RBTreeUpLink<Node,uint32> link;
 };

/* test<Algo>() */

template <class Algo>
void test()
 {
  OwnPtr<SpeedEngine<Node,Algo> > engine(new SpeedEngine<Node,Algo>());
  
  engine->test_ins();
  
  engine->test_del();
  
  engine->test_delNode();
  
  engine->test_finddelNode();
 }

} // namespace Private_0052
 
using namespace Private_0052; 
 
/* Testit<52> */ 

template<>
const char *const Testit<52>::Name="Test52 RBTreeUp-speed";

template<>
bool Testit<52>::Main() 
 {
  Printf(Con,"#;\n\n",Title("Algo"));
  
  test<RBTreeUpLink<Node,uint32>::Algo<&Node::link> >();
  
  return true;
 }
 
} // namespace App
 
