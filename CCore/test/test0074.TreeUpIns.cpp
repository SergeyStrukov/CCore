/* test0074.TreeUpIns.cpp */ 
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

#include <CCore/inc/Tree.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/MemBase.h>
#include <CCore/inc/OwnPtr.h>

namespace App {

namespace Private_0074 {

/* class Engine */

struct Node : MemBase_nocopy
 {
  TreeUpLink<Node,unsigned> link;
 };
 
typedef TreeUpLink<Node,unsigned>::RadixAlgo<&Node::link> Algo;

const unsigned MaxKey = 1023 ;
  
class Engine : public MemBase_nocopy
 {
   Random random;
   Algo::Root root;
   ulen count;
   
   bool flags[MaxKey+1];
   
  private:
  
   static void Destroy(Node *root)
    {
     if( root )
       {
        Destroy(Algo::Link(root).lo);
        Destroy(Algo::Link(root).hi);
        
        delete root;
       }
    }
    
   void fail(unsigned num)
    {
     Printf(Exception,"fail #;",num);
    }
    
   unsigned getKey() { return random.select(0,MaxKey); } 
   
   void check() { Algo::Check(root.root,0,MaxKey); }
    
   void add()
    {
     unsigned key=getKey();
     
     Algo::PrepareIns ins(root,key,0,MaxKey);
     
     if( ins.found ) 
       {
        if( Algo::Link(ins.found).key!=key ) fail(1);
       }
     else
       {
        ins.complete(new Node);
        
        count++;
        
        if( flags[key] ) fail(50);
        
        flags[key]=true;
     
        check();
       }
    }
    
   void del()
    {
     unsigned minkey=getKey();
    
     check();
     
     if( Node *node=root.delMin(minkey) )
       {
        count--;
        
        if( !flags[Algo::Link(node).key] ) fail(60);
        
        flags[Algo::Link(node).key]=false;
        
        delete node;
       }
    }
    
   void test_find()
    {
     unsigned key=getKey();
     
     {
      Node *node=root.find(key);
      
      if( flags[key] )
        {
         if( !node ) fail(10);
         
         if( Algo::Link(node).key!=key ) fail(11);
        }
      else
        {
         if( node ) fail(12);
        }
     }
     
     {
      Node *node=root.findMin(key);
      
      if( node )
        {
         unsigned k=Algo::Link(node).key;
         
         if( k<key ) fail(13);
         
         for(; (k--)>key ;) if( flags[k] ) fail(14);
        }
      else
        {
         unsigned k=MaxKey+1;
         
         for(; (k--)>key ;) if( flags[k] ) fail(15);
        }  
     }
     
     {
      Node *node=root.findMax(key);
      
      if( node )
        {
         unsigned k=Algo::Link(node).key;
         
         if( k>key ) fail(16);
         
         for(k++; k<=key ;k++) if( flags[k] ) fail(17);
        }
      else
        {
         unsigned k=0;
        
         for(; k<=key ;k++) if( flags[k] ) fail(18);
        }
     }

     {
      if( root.findMin()!=root.findMin(0) ) fail(19);
      
      if( root.findMax()!=root.findMax(MaxKey) ) fail(20);
     }
    }
    
   void test()
    {
     unsigned s=0;
     
     for(auto r=Range(flags); +r ;++r) s+=(*r);
     
     if( s!=count ) fail(2);
    
     for(ulen cnt=1000; cnt ;cnt--)
       {
        test_find();
       }
    }
    
  public:
  
   Engine()
    {
     count=0;
     
     Range(flags).set_null();
    }
   
   ~Engine()
    {
     Destroy(root.root);
    }
    
   void run()
    {
     bool do_test=true;
     
     for(ulen cnt=10000; cnt ;cnt--) 
       {
        add();
        
        if( do_test && count>=MaxKey/5 ) 
          {
           Printf(Con,"test(#;)\n",count);
           
           test();
           
           do_test=false;
          }
       }
     
     while( count>100 ) del();
    }
 };

} // namespace Private_0074
 
using namespace Private_0074; 
 
/* Testit<74> */ 

template<>
const char *const Testit<74>::Name="Test74 TreeUpIns";

template<>
bool Testit<74>::Main() 
 {
  OwnPtr<Engine> engine(new Engine);
  
  for(ulen cnt=1000; cnt ;cnt--) engine->run();
  
  return true;
 }
 
} // namespace App
 
