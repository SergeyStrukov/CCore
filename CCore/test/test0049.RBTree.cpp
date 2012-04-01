/* test0049.RBTree.cpp */ 
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

namespace App {

namespace Private_0049 {

/* struct Node */

struct Node
 {
  RBTreeLink<Node,uint32> link;
  
  typedef RBTreeLink<Node,uint32>::BaseAlgo<&Node::link> BaseAlgo;
  
  template <class P>
  ulen print(P &out) const
   {
    PrintCount<P> count_out(out);
    
    Printf(count_out,"#; #;",link.key,link.flag);
    
    return count_out.getCount();
   }
 };

/* test<Algo>() */

template <class Algo>
static void test(ulen rep)
 {
  OwnPtr<Engine<Node,Algo> > engine(new Engine<Node,Algo>("test0049.txt"));
  
  for(ulen cnt=rep; cnt ;cnt--) engine->test_ins();
  
  for(ulen cnt=rep; cnt ;cnt--) engine->test_delMin();
  
  for(ulen cnt=rep; cnt ;cnt--) engine->test_delMax();
  
  for(ulen cnt=rep; cnt ;cnt--) engine->test_del();
 }

} // namespace Private_0049
 
using namespace Private_0049; 
 
/* Testit<49> */ 

template<>
const char *const Testit<49>::Name="Test49 RBTree";

template<>
bool Testit<49>::Main() 
 {
  Printf(Con,"#;\n\n",Title("Algo"));
  
  test<RBTreeLink<Node,uint32>::Algo<&Node::link> >(1000);
  
  Printf(Con,"#;\n\n",Title("AltAlgo"));
  
  test<RBTreeLink<Node,uint32>::AltAlgo<&Node::link> >(1000);
  
  return true;
 }
 
} // namespace App
 
