/* test0051.RBTreeUp.cpp */ 
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

namespace Private_0051 {

/* struct Node */

struct Node
 {
  RBTreeUpLink<Node,uint32> link;
  
  typedef RBTreeUpLink<Node,uint32>::BaseAlgo<&Node::link> BaseAlgo;
  
  template <class P>
  ulen print(P &out) const
   {
    PrintCount<P> count_out(out);
    
    Printf(count_out,"#; #;",link.key,link.flag);
    
    if( link.up ) Printf(count_out," (#;)",BaseAlgo::Link(link.up).key);
    
    return count_out.getCount();
   }
 };

/* test<Algo>() */

template <class Algo>
void test(ulen rep)
 {
  OwnPtr<Engine<Node,Algo> > engine(new Engine<Node,Algo>("test0051.txt"));
  
  for(ulen cnt=rep; cnt ;cnt--) engine->test_ins();
  
  for(ulen cnt=rep; cnt ;cnt--) engine->test_delMin();
  
  for(ulen cnt=rep; cnt ;cnt--) engine->test_delMax();
  
  for(ulen cnt=rep; cnt ;cnt--) engine->test_del();
  
  for(ulen cnt=rep; cnt ;cnt--) engine->test_delNode();
 }

} // namespace Private_0051
 
using namespace Private_0051; 
 
/* Testit<51> */ 

template<>
const char *const Testit<51>::Name="Test51 RBTreeUp";

template<>
bool Testit<51>::Main() 
 {
  Printf(Con,"#;\n\n",Title("Algo"));
  
  test<RBTreeUpLink<Node,uint32>::Algo<&Node::link> >(1000);
  
  return true;
 }
 
} // namespace App
 
