/* test0003.List.cpp */ 
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

#include <CCore/inc/List.h>

namespace App {

namespace Private_0003 {

/* Show() */

template <class Cur>
void Show(Cur cur) 
 {
  Printf(Con,"{ ");
  
  for(; +cur ;++cur) Printf(Con,"#; ",cur->value);
  
  Printf(Con,"}\n");
 }

void Show(int value)
 {
  Printf(Con,"#;\n",value);
 }

template <class Cur>
void Show(int value,Cur cur)
 {
  Printf(Con,"#; ",value);
  
  Show(cur);
 }

void ShowTitle(const char *text)
 {
  Printf(Con,"#;\n\n",Title(text));
 }

void ShowDiv()
 {
  Printf(Con,"\n-----\n\n");
 }

/* struct SNode */
 
struct SNode
 {
  SLink<SNode> link;
  
  int value;
  
  SNode(int value_=-1) : value(value_) {}
 };

/* testSNode1() */
 
void testSNode1()
 {
  ShowTitle("testSNode1");
  
  typedef SLink<SNode>::LinearAlgo<&SNode::link> Algo;
  
  const int Len=10;
  SNode buf[Len];
  
  for(int i=0; i<Len ;i++) buf[i].value=i;
 
  // 1
  {
   Algo::Init(buf);

   Show(Algo::Cur(buf));
   
   Algo::InsNext(buf,buf+1);
   
   Show(Algo::Cur(buf));
   
   Algo::InsNext(buf+1,buf+2);
   
   Show(Algo::Cur(buf));
   
   Algo::DelNext(buf);
   
   Show(Algo::Cur(buf));
   
   Algo::DelNext(buf);
   
   Show(Algo::Cur(buf));
   
   ShowDiv();
  }
  
  // 2
  {
   Algo::Top list;
   
   for(int i=0; i<Len ;i++) list.ins(buf+i);
   
   Show(list.start());
   
   while( +list ) Show(list.del()->value);
     
   Show(list.start());
   
   ShowDiv();
  }
  
  // 3
  {
   Algo::FirstLast list;
   
   for(int i=0; i<Len ;i++)
     {
      if( (i&1) ) 
        list.ins_first(buf+i);
      else  
        list.ins_last(buf+i);
     }
   
   Show(list.start());
   
   while( +list ) Show(list.del_first()->value);
     
   Show(list.start());
   
   for(int i=0; i<Len ;i++)
     {
      if( !(i&1) ) 
        list.ins_first(buf+i);
      else  
        list.ins_last(buf+i);
     }
   
   Show(list.start());
   
   while( +list ) Show(list.del_first()->value);
     
   Show(list.start());
   
   ShowDiv();
  }
  
  // 4
  {
   Algo::Top list;
   
   list.ins(buf);

   auto cur=list.start();
   
   for(int i=1; i<Len ;i++)
     {
      list.ins_after(cur,buf+i);
      
      Show(cur);
     }
     
   Show(list.start());
   
   ShowDiv();
  }
  
  // 5
  {
   Algo::FirstLast list;
   
   list.ins_first(buf);
   
   auto cur=list.start();
   
   for(int i=1; i<Len ;i++)
     {
      list.ins_after(cur,buf+i);
      
      Show(cur);
     }
     
   Show(list.start());
   
   ShowDiv();
  }
 } 
  
/* testSNode2() */

void testSNode2()
 {
  ShowTitle("testSNode2");
  
  typedef SLink<SNode>::CircularAlgo<&SNode::link> Algo;
  
  const int Len=10;
  SNode buf[Len];
  
  for(int i=0; i<Len ;i++) buf[i].value=i;
  
  // 1
  {
   Algo::Init(buf);

   Show(Algo::Cur(buf));
   
   Algo::InsNext(buf,buf+1);
   
   Show(Algo::Cur(buf));
   
   Algo::InsNext(buf+1,buf+2);
   
   Show(Algo::Cur(buf));
   
   Algo::DelNext(buf);
   
   Show(Algo::Cur(buf));
   
   Algo::DelNext(buf);
   
   Show(Algo::Cur(buf));
   
   ShowDiv();
  }
  
  // 2
  {
   Algo::Top list;
   
   for(int i=0; i<Len ;i++) list.ins(buf+i);
   
   Show(list.start());
   
   while( +list ) Show(list.del()->value);
     
   Show(list.start());
   
   ShowDiv();
  }
  
  // 3
  {
   Algo::Top list;
   
   list.ins(buf);
   
   auto cur=list.start();
   
   for(int i=1; i<Len ;i++)
     {
      list.ins_after(cur,buf+i);
      
      Show(cur);
     }
     
   Show(list.start());
   
   auto node=list.rotate();
   
   Show(node->value,list.start());
   
   ShowDiv();
  }
 }
  
/* struct DNode */

struct DNode
 {
  DLink<DNode> link;
  
  int value;
  
  DNode(int value_=-1) : value(value_) {}
 };

/* testDNode1() */

void testDNode1()
 {
  ShowTitle("testDNode1");
  
  typedef DLink<DNode>::LinearAlgo<&DNode::link> Algo;
  
  const int Len=10;
  DNode buf[Len];
  
  for(int i=0; i<Len ;i++) buf[i].value=i;
  
  // 1
  {
   Algo::Init(buf);
   
   Show(Algo::Cur(buf));
   
   Algo::InsNext(buf,buf+1);
   
   Show(Algo::Cur(buf));
   
   Algo::InsPrev(buf+1,buf+2);
   
   Show(Algo::Cur(buf));
   
   Algo::Del(buf+2);
   
   Show(Algo::Cur(buf));
   
   Algo::Del(buf+1);
   
   Show(Algo::Cur(buf));
   
   ShowDiv();
  }

  // 2
  {
   Algo::Init(buf);
   
   for(int i=1; i<Len ;i++) Algo::InsNext(buf,buf+i);
   
   Show(Algo::Cur(buf));
   
   while( auto node=Algo::DelNext(buf) ) Show(node->value);
     
   Show(Algo::Cur(buf));
   
   ShowDiv();
  }

  // 3
  {
   Algo::Init(buf);
   
   for(int i=1; i<Len ;i++) Algo::InsPrev(buf,buf+i);
   
   Show(Algo::RevCur(buf));
   
   while( auto node=Algo::DelPrev(buf) ) Show(node->value);
     
   Show(Algo::RevCur(buf));
   
   ShowDiv();
  }

  // 4
  {
   Algo::Top list;
   
   for(int i=0; i<Len ;i++) list.ins(buf+i);
   
   Show(list.start());
   
   for(int i=0; i<Len ;i+=2) 
     {
      list.del(buf+i);
      
      Show(list.start());
     }
     
   for(int i=1; i<Len ;i+=2) 
     {
      list.del(buf+i);
      
      Show(list.start());
     }
   
   ShowDiv();
  }

  // 5
  {
   Algo::Top list;
   
   for(int i=0; i<Len ;i++) list.ins(buf+i);
   
   Show(list.start());
   
   while( auto node=list.del() ) Show(node->value);
   
   ShowDiv();
  } 

  // 6
  {
   Algo::FirstLast list;
   
   for(int i=0; i<Len ;i++)
     if( i&1 )
       list.ins_first(buf+i);
     else
       list.ins_last(buf+i);
       
   Show(list.start());    
   Show(list.start_rev());
   
   ShowDiv();
  }

  // 7
  {
   Algo::FirstLast list;
   
   for(int i=0; i<Len ;i++)
     if( i&1 )
       list.ins_last(buf+i);
     else
       list.ins_first(buf+i);
       
   Show(list.start());    
   Show(list.start_rev());
   
   ShowDiv();
  }

  // 8
  {
   Algo::FirstLast list;
   
   for(int i=0; i<Len ;i++) list.ins_first(buf+i);
   
   Show(list.start());    
   
   while( auto node=list.del_first() )
     {
      Show(node->value);
      
      if( auto node=list.del_last() ) Show(node->value);
     }
     
   Show(list.start());
   Show(list.start_rev());  
   
   ShowDiv();
  }

  // 9
  {
   Algo::FirstLast list;
   
   for(int i=0; i<Len ;i++) list.ins_first(buf+i);
   
   Show(list.start());    
   
   while( auto node=list.del_last() )
     {
      Show(node->value);
      
      if( auto node=list.del_first() ) Show(node->value);
     }
     
   Show(list.start());
   Show(list.start_rev());  
   
   ShowDiv();
  }

  // 10
  {
   Algo::FirstLast list;
   
   for(int i=0; i<Len ;i++) list.ins_first(buf+i);
   
   Show(list.start());
   
   for(int i=0; i<Len ;i+=2) 
     {
      list.del(buf+i);
      
      Show(list.start());
     }
     
   for(int i=1; i<Len ;i+=2) 
     {
      list.del(buf+i);
      
      Show(list.start());
     }
   
   ShowDiv();
  } 

  // 11
  {
   Algo::Top list;
   
   for(int i=0; i<Len ;i++) list.ins(buf+i);
   
   auto cur=list.start();

   Show(cur);
   
   ++cur;
   
   while( +cur )
     {
      auto node=list.del_and_move(cur);
      
      Show(node->value,cur);
     }
     
   Show(list.start());  
   
   ShowDiv();
  }

  // 12
  {
   Algo::FirstLast list;
   
   for(int i=0; i<Len ;i++) list.ins_first(buf+i);
   
   auto cur=list.start();

   Show(cur);
   
   ++cur;
   
   while( +cur )
     {
      auto node=list.del_and_move(cur);
      
      Show(node->value,cur);
     }
     
   Show(list.start());  
   
   ShowDiv();
  } 

  // 13
  {
   Algo::FirstLast list;
   
   for(int i=0; i<Len ;i++) list.ins_first(buf+i);
   
   auto cur=list.start_rev();

   Show(cur);
   
   ++cur;
   
   while( +cur )
     {
      auto node=list.del_and_move(cur);
      
      Show(node->value,cur);
     }
     
   Show(list.start());  
   
   ShowDiv();
  } 

  // 14
  {
   Algo::FirstLast list;

   list.ins_first(buf);
   
   auto cur=list.start();
   
   for(int i=1; i<Len ;i++)
     {
      if( i&1 )
        list.ins_before(cur,buf+i);
      else
        list.ins_after(cur,buf+i);
      
      Show(cur);
     }
     
   Show(list.start());  
   Show(list.start_rev());
   
   ShowDiv();
  }

  // 15
  {
   Algo::FirstLast list;

   list.ins_first(buf);
   
   auto cur=list.start_rev();
   
   for(int i=1; i<Len ;i++)
     {
      if( !(i&1) )
        list.ins_before(cur,buf+i);
      else
        list.ins_after(cur,buf+i);
      
      Show(cur);
     }
     
   Show(list.start());  
   Show(list.start_rev());
   
   ShowDiv();
  }

  // 16
  {
   Algo::Top list;

   list.ins(buf);
   
   auto cur=list.start();
   
   for(int i=1; i<Len ;i++)
     {
      if( !(i&1) )
        list.ins_before(cur,buf+i);
      else
        list.ins_after(cur,buf+i);
      
      Show(cur);
     }
     
   Show(list.start());  
   
   ShowDiv();
  }
 }
 
/* testDNode2() */

void testDNode2()
 {
  ShowTitle("testDNode2");
  
  typedef DLink<DNode>::CircularAlgo<&DNode::link> Algo;
  
  const int Len=10;
  DNode buf[Len];
  
  for(int i=0; i<Len ;i++) buf[i].value=i;
  
  // 1
  {
   Algo::Init(buf);
   
   Show(Algo::Cur(buf));
   
   Algo::InsNext(buf,buf+1);
   
   Show(Algo::Cur(buf));
   
   Algo::InsPrev(buf+1,buf+2);
   
   Show(Algo::Cur(buf));
   
   Algo::Del(buf+2);
   
   Show(Algo::Cur(buf));
   
   Algo::Del(buf+1);
   
   Show(Algo::Cur(buf));
   
   ShowDiv();
  }

  // 2
  {
   Algo::Init(buf);
   
   for(int i=1; i<Len ;i++) Algo::InsNext(buf,buf+i);
   
   Show(Algo::Cur(buf));
   
   while( auto node=Algo::DelNext(buf) ) Show(node->value);
     
   Show(Algo::Cur(buf));
   
   ShowDiv();
  }

  // 3
  {
   Algo::Init(buf);
   
   for(int i=1; i<Len ;i++) Algo::InsPrev(buf,buf+i);
   
   Show(Algo::RevCur(buf));
   
   while( auto node=Algo::DelPrev(buf) ) Show(node->value);
     
   Show(Algo::RevCur(buf));
   
   ShowDiv();
  }

  // 4
  {
   Algo::Top list;
   
   for(int i=0; i<Len ;i++) list.ins_first(buf+i);
   
   Show(list.start());
   
   for(int i=0; i<Len ;i+=2) 
     {
      list.del(buf+i);
      
      Show(list.start());
     }
     
   for(int i=1; i<Len ;i+=2) 
     {
      list.del(buf+i);
      
      Show(list.start());
     }
   
   ShowDiv();
  }

  // 5
  {
   Algo::Top list;
   
   for(int i=0; i<Len ;i++) list.ins_last(buf+i);
   
   Show(list.start());
   
   for(int i=0; i<Len ;i+=2) 
     {
      list.del(buf+i);
      
      Show(list.start());
     }
     
   for(int i=1; i<Len ;i+=2) 
     {
      list.del(buf+i);
      
      Show(list.start());
     }
   
   ShowDiv();
  }

  // 6
  {
   Algo::Top list;
   
   for(int i=0; i<Len ;i++) list.ins_first(buf+i);
   
   Show(list.start());
   
   while( auto node=list.del_first() ) Show(node->value);
   
   ShowDiv();
  } 

  // 7
  {
   Algo::Top list;
   
   for(int i=0; i<Len ;i++) list.ins_first(buf+i);
   
   Show(list.start());
   
   while( auto node=list.del_last() ) Show(node->value);
   
   ShowDiv();
  } 

  // 8
  {
   Algo::Top list;
   
   for(int i=0; i<Len ;i++) list.ins_first(buf+i);
   
   auto cur=list.start();

   Show(cur);
   
   ++cur;
   
   while( +cur )
     {
      auto node=list.del_and_move(cur);
      
      Show(node->value,cur);
     }
     
   Show(list.start());  
   
   ShowDiv();
  } 

  // 9
  {
   Algo::Top list;
   
   for(int i=0; i<Len ;i++) list.ins_first(buf+i);
   
   auto cur=list.start_rev();

   Show(cur);
   
   ++cur;
   
   while( +cur )
     {
      auto node=list.del_and_move(cur);
      
      Show(node->value,cur);
     }
     
   Show(list.start());  
   
   ShowDiv();
  } 

  // 10
  {
   Algo::Top list;
   
   for(int i=0; i<Len/2 ;i++) list.ins_first(buf+i);
   
   auto cur=list.start();

   for(int i=Len/2; i<Len ;i++)
     {
      list.ins_before(cur,buf+i);
     }
     
   Show(cur);  
   Show(list.start());
   
   ShowDiv();
  }

  // 11
  {
   Algo::Top list;
   
   list.ins_first(buf);
   
   auto cur=list.start();

   for(int i=1; i<Len ;i++)
     {
      list.ins_after(cur,buf+i);
      
      Show(cur);  
     }
     
   Show(list.start());
   
   ShowDiv();
  }

  // 12
  {
   Algo::Top list;
   
   list.ins_first(buf);
   
   auto cur=list.start_rev();

   for(int i=1; i<Len ;i++)
     {
      list.ins_after(cur,buf+i);
      
      Show(cur);  
     }
     
   Show(list.start());
   
   ShowDiv();
  }

  // 13
  {
   Algo::Top list;
   
   list.ins_first(buf);
   
   auto cur=list.start_rev();

   for(int i=1; i<Len ;i++)
     {
      list.ins_before(cur,buf+i);
      
      Show(cur);  
     }
     
   Show(list.start());

   {
    auto node=list.rotate_forward();
   
    Show(node->value,list.start());
   }
   
   {
    auto node=list.rotate_backward();
   
    Show(node->value,list.start());
   }
   
   ShowDiv();
  }
 }
  
} // namespace Private_0003
 
using namespace Private_0003; 
 
/* Testit<3> */ 

template<>
const char *const Testit<3>::Name="Test3 List";

template<>
bool Testit<3>::Main() 
 { 
  testSNode1();
  testSNode2();
  testDNode1();
  testDNode2();
 
  return true;
 }
 
} // namespace App
 
