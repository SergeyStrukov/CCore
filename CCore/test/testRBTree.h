/* testRBTree.h */
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

#ifndef CCore_test_testRBTree_h
#define CCore_test_testRBTree_h

#include <CCore/test/test.h>

#include <CCore/inc/MemBase.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Tree.h>

namespace App {

/* using */

using namespace CCore;

namespace Private_testRBTree {

/* struct PrintTree<Node> */

template <class Node>
struct PrintTree
 {
  Node *node;
  
  explicit PrintTree(Node *node_) : node(node_) {}
  
  struct Stack
   {
    ulen stack[100];
    ulen ind;
    
    Stack() : ind(0) {}
    
    void push(ulen off)
     {
      stack[ind++]=off-1;
     }
    
    void pop()
     {
      ind--;
     }
    
    template <class P>
    void prefix(P &out) const
     {
      Printf(out,"\n");
      
      for(ulen i=0; i<ind ;i++) Printf(out,"|#;",RepeatChar(stack[i],' '));
     }
    
    template <class P>
    void print(P &out,Node *node)
     {
      ulen off=node->print(out);
      
      auto &link=Node::BaseAlgo::Link(node);
      
      if( Node *hi=link.hi )
        {
         Printf(out," -- ");
         
         push(off+4);
         
         print(out,hi);
         
         pop();
        }
      
      if( Node *lo=link.lo )
        {
         prefix(out);
      
         Printf(out,"|");
      
         prefix(out);
         
         print(out,lo);
        }
     }
   };
  
  template <class P>
  void print(P &out) const
   {
    if( node )
      {
       Stack stack;
       
       stack.print(out,node);
      }
    else
      {
       Printf(out,"<empty>");
      }
   }
 };

/* class Log */

#if 0

class Log : NoCopy
 {
   PrintFile out;
  
  public:
   
   explicit Log(StrLen file_name) : out(file_name) {}
   
   void operator () ()
    {
     Printf(out,"#;\n\n",TextDivider());
    }
   
   template <class Node>
   void operator () (Node *node,const char *op,uint32 key)
    {
     Printf(out,"#;\n\n",PrintTree<Node>(node));
     
     Printf(out,"#; key = #;\n\n",op,key);
     
     out.flush();
    }
   
   template <class Node>
   void operator () (Node *node)
    {
     Printf(out,"#;\n\n",PrintTree<Node>(node));
    }
   
   void operator () (uint32 key)
    {
     Printf(out,"key = #;\n",key);
    }
 };

#else

class Log
 {
  public:
   
   explicit Log(StrLen) {}
   
   template <class ... TT>
   void operator () (TT ...)
    {
    }
 };

#endif

/* class KeyCheck */

class KeyCheck
 {
   uint32 key;
   bool exist;
   
  public: 
   
   KeyCheck() : key(),exist(false) {}
   
   void nextUp(uint32 key_)
    {
     if( exist )
       {
        if( key_<=key )
          {
           Printf(Exception,"nextUp failed");
          }
       }
     
     key=key_;
     exist=true;
    }
   
   void nextDown(uint32 key_)
    {
     if( exist )
       {
        if( key_>=key )
          {
           Printf(Exception,"nextDown failed");
          }
       }
     
     key=key_;
     exist=true;
    }
 };

/* class Engine<Node,Algo> */

template <class Node,class Algo>
class Engine : public MemBase_nocopy
 {
   static const ulen PoolLen = 1000 ;
   static const uint32 MaxKey = 2*PoolLen ;
   
   Node pool[PoolLen];
   Random random;
   
   Log log;
   
  public:
   
   explicit Engine(StrLen file_name) : log(file_name) {}
   
   ~Engine() {}
   
   void test_ins();
   
   void test_delMin();
   
   void test_delMax();
   
   void test_del();
   
   void test_delNode();
 };

template <class Node,class Algo>
void Engine<Node,Algo>::test_ins()
 {
  typename Algo::Root root;
  ulen count=0;
  ulen found_count=0;
  
  log();
  
  while( count<PoolLen )
    {
     uint32 key=random.select(0,MaxKey);
     
     log(root.root,"add",key);
     
     typename Algo::PrepareIns prepare_ins(root,key);
     
     if( Node *node=prepare_ins.found )
       {
        if( Algo::Link(node).key!=key ) 
          {
           Printf(Exception,"bad found");
          }
        
        found_count++;
       }
     else
       {
        if( random.select(2) )
          prepare_ins.complete(pool+(count++));
       }
     
     typename Algo::Check check(root.root);
    }
  
  log(root.root);
  
  //Printf(Con,"ins = #; found = #;\n",count,found_count);
 }

template <class Node,class Algo>
void Engine<Node,Algo>::test_delMin()
 {
  typename Algo::Root root;
  ulen count=0;
  
  log();
  
  while( count<PoolLen )
    {
     uint32 key=random.next16();
     
     log(key);
     
     typename Algo::PrepareIns prepare_ins(root,key);
     
     if( !prepare_ins.found )
       {
        prepare_ins.complete(pool+(count++));
       }
    }
  
  log();
  
  KeyCheck key_check;
  
  for(; count ;count--)
    {
     Node *node=root.delMin();
     
     if( !node )
       {
        Printf(Exception,"min not found");
       }
     
     uint32 key=Algo::Link(node).key;
     
     log(key);
     
     key_check.nextUp(key);
     
     typename Algo::Check check(root.root);
    }
  
  if( root.delMin() )
    {
     Printf(Exception,"min found");
    }
 }

template <class Node,class Algo>
void Engine<Node,Algo>::test_delMax()
 {
  typename Algo::Root root;
  ulen count=0;
  
  log();
  
  while( count<PoolLen )
    {
     uint32 key=random.next16();
     
     log(key);
     
     typename Algo::PrepareIns prepare_ins(root,key);
     
     if( !prepare_ins.found )
       {
        prepare_ins.complete(pool+(count++));
       }
    }
  
  log();
  
  KeyCheck key_check;
  
  for(; count ;count--)
    {
     Node *node=root.delMax();
     
     if( !node )
       {
        Printf(Exception,"max not found");
       }
     
     uint32 key=Algo::Link(node).key;
     
     log(key);
     
     key_check.nextDown(key);
     
     typename Algo::Check check(root.root);
    }
  
  if( root.delMax() )
    {
     Printf(Exception,"max found");
    }
 }

template <class Node,class Algo>
void Engine<Node,Algo>::test_del()
 {
  typename Algo::Root root;
  ulen count=0;
  
  while( count<PoolLen )
    {
     uint32 key=random.next16();
     
     typename Algo::PrepareIns prepare_ins(root,key);
     
     if( !prepare_ins.found )
       {
        prepare_ins.complete(pool+(count++));
       }
    }
  
  log();
  
  while( count-- )
    {
     Node *todel=pool+count;
     
     uint32 key=Algo::Link(todel).key;
     
     log(root.root,"del",key);
     
     Node *node=root.del(key);
     
     if( node!=todel )
       {
        Printf(Exception,"bad del");
       }

     typename Algo::Check check(root.root);
    }
 }

template <class Node,class Algo>
void Engine<Node,Algo>::test_delNode()
 {
  typename Algo::Root root;
  ulen count=0;
  
  while( count<PoolLen )
    {
     uint32 key=random.next16();
     
     typename Algo::PrepareIns prepare_ins(root,key);
     
     if( !prepare_ins.found )
       {
        prepare_ins.complete(pool+(count++));
       }
    }
  
  while( count-- )
    {
     Node *todel=pool+count;
     
     log(root.root,"del",Algo::Link(todel).key);
     
     root.del(todel);
     
     log(root.root);
     
     typename Algo::Check check(root.root);
    }
 }

/* class SpeedEngine<Node,Algo> */

template <class Node,class Algo>
class SpeedEngine : public MemBase_nocopy
 {
   static const ulen PoolLen = 100000 ;
   
   Node pool[PoolLen];
   Random random;
   
  private:
   
   ClockTimer::ValueType do_ins(ulen size);
   
   ClockTimer::ValueType do_del(ulen size);
   
   ClockTimer::ValueType do_delNode(ulen size);
   
   ClockTimer::ValueType do_finddelNode(ulen size);
   
   void test_ins(ulen size);
   
   void test_del(ulen size);
   
   void test_delNode(ulen size);
   
   void test_finddelNode(ulen size);
   
  public:
   
   SpeedEngine() {}
   
   ~SpeedEngine() {}
   
   void test_ins();
   
   void test_del();
   
   void test_delNode();
   
   void test_finddelNode();
 };

template <class Node,class Algo>
ClockTimer::ValueType SpeedEngine<Node,Algo>::do_ins(ulen size)
 {
  ClockTimer timer;
  
  typename Algo::Root root;
  ulen count=0;
  
  while( count<size )
    {
     uint32 key=random.next32();
     
     typename Algo::PrepareIns prepare_ins(root,key);
     
     if( !prepare_ins.found )
       {
        prepare_ins.complete(pool+(count++));
       }
    }
  
  return timer.get();
 }

template <class Node,class Algo>
ClockTimer::ValueType SpeedEngine<Node,Algo>::do_del(ulen size)
 {
  typename Algo::Root root;
  ulen count=0;
  
  while( count<size )
    {
     uint32 key=random.next32();
     
     typename Algo::PrepareIns prepare_ins(root,key);
     
     if( !prepare_ins.found )
       {
        prepare_ins.complete(pool+(count++));
       }
    }
  
  ClockTimer timer;
  
  while( count-- )
    {
     root.del(Algo::Link(pool+count).key);
    }
  
  return timer.get();
 }

template <class Node,class Algo>
ClockTimer::ValueType SpeedEngine<Node,Algo>::do_delNode(ulen size)
 {
  typename Algo::Root root;
  ulen count=0;
  
  while( count<size )
    {
     uint32 key=random.next32();
     
     typename Algo::PrepareIns prepare_ins(root,key);
     
     if( !prepare_ins.found )
       {
        prepare_ins.complete(pool+(count++));
       }
    }
  
  ClockTimer timer;
  
  while( count-- )
    {
     root.del(pool+count);
    }
  
  return timer.get();
 }

template <class Node,class Algo>
ClockTimer::ValueType SpeedEngine<Node,Algo>::do_finddelNode(ulen size)
 {
  typename Algo::Root root;
  ulen count=0;
  
  while( count<size )
    {
     uint32 key=random.next32();
     
     typename Algo::PrepareIns prepare_ins(root,key);
     
     if( !prepare_ins.found )
       {
        prepare_ins.complete(pool+(count++));
       }
    }
  
  ClockTimer timer;
  
  while( count-- )
    {
     root.del(root.find(Algo::Link(pool+count).key));
    }
  
  return timer.get();
 }

template <class Node,class Algo>
void SpeedEngine<Node,Algo>::test_ins(ulen size)
 {
  TimeStat<ClockTimer::ValueType> stat;
  
  for(unsigned rep=100; rep ;rep--)
    {
     stat.add(do_ins(size));
    }
  
  Printf(Con,"size = #7; #10;\n",size,stat);
 }

template <class Node,class Algo>
void SpeedEngine<Node,Algo>::test_del(ulen size)
 {
  TimeStat<ClockTimer::ValueType> stat;
  
  for(unsigned rep=100; rep ;rep--)
    {
     stat.add(do_del(size));
    }
  
  Printf(Con,"size = #7; #10;\n",size,stat);
 }

template <class Node,class Algo>
void SpeedEngine<Node,Algo>::test_delNode(ulen size)
 {
  TimeStat<ClockTimer::ValueType> stat;
  
  for(unsigned rep=100; rep ;rep--)
    {
     stat.add(do_delNode(size));
    }
  
  Printf(Con,"size = #7; #10;\n",size,stat);
 }

template <class Node,class Algo>
void SpeedEngine<Node,Algo>::test_finddelNode(ulen size)
 {
  TimeStat<ClockTimer::ValueType> stat;
  
  for(unsigned rep=100; rep ;rep--)
    {
     stat.add(do_finddelNode(size));
    }
  
  Printf(Con,"size = #7; #10;\n",size,stat);
 }

template <class Node,class Algo>
void SpeedEngine<Node,Algo>::test_ins()
 {
  Printf(Con,"ins\n\n");
  
  for(ulen size=10; size<=PoolLen ;size*=10) test_ins(size);
  
  Printf(Con,"\n");
 }

template <class Node,class Algo>
void SpeedEngine<Node,Algo>::test_del()
 {
  Printf(Con,"del\n\n");
  
  for(ulen size=10; size<=PoolLen ;size*=10) test_del(size);
  
  Printf(Con,"\n");
 }

template <class Node,class Algo>
void SpeedEngine<Node,Algo>::test_delNode()
 {
  Printf(Con,"delNode\n\n");
  
  for(ulen size=10; size<=PoolLen ;size*=10) test_delNode(size);
  
  Printf(Con,"\n");
 }

template <class Node,class Algo>
void SpeedEngine<Node,Algo>::test_finddelNode()
 {
  Printf(Con,"finddelNode\n\n");
  
  for(ulen size=10; size<=PoolLen ;size*=10) test_finddelNode(size);
  
  Printf(Con,"\n");
 }

} // namespace Private_testRBTree

using namespace Private_testRBTree;

} // namespace App

#endif

