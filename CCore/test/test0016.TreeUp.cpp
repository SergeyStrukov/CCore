/* test0016.TreeUp.cpp */ 
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

#include <CCore/inc/Tree.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/MemBase.h>
#include <CCore/inc/OwnPtr.h>

namespace App {

namespace Private_0016 {

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
   
   unsigned flags[MaxKey+1];
   
  private:
  
   static void Destroy(Node *root)
    {
     if( root )
       {
        Node *lo=Algo::Link(root).lo;
        
        if( root!=lo )
          {
           Destroy(lo);
           Destroy(Algo::Link(root).hi);
           
           delete root;
          }
        else
          {
           while( root )
             {
              delete Replace(root,Algo::Link(root).hi);
             }
          }  
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
     
     for(ulen cnt=random.select(1,10); cnt ;cnt--)
       {
        root.ins(new Node,key,0,MaxKey);
     
        count++;
        
        flags[key]++;
     
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
        
        flags[Algo::Link(node).key]--;
        
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
      Node *node1=root.findMin();
      Node *node2=root.findMin(0);
      
      if( node1!=node2 ) 
        {
         //Printf(Con,"min\n");
        
         if( node1 )
           {
            if( !node2 ) fail(19);
            
            if( Algo::Link(node1).key!=Algo::Link(node2).key ) fail(20);
           }
         else
           {
            if( node2 ) fail(21);
           }
        }
     }
     
     {
      Node *node1=root.findMax();
      Node *node2=root.findMax(MaxKey);
      
      if( node1!=node2 ) 
        {
         //Printf(Con,"max\n");
        
         if( node1 )
           {
            if( !node2 ) fail(22);
            
            if( Algo::Link(node1).key!=Algo::Link(node2).key ) fail(23);
           }
         else
           {
            if( node2 ) fail(24);
           }
        }
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
     
     for(ulen cnt=2000; cnt ;cnt--) 
       {
        add();
        
        if( do_test && count>=MaxKey ) 
          {
           Printf(Con,"test(#;)\n",count);
           
           test();
           
           do_test=false;
          }
       }
     
     while( count>100 ) del();
    }
 };
 
} // namespace Private_0016
 
using namespace Private_0016; 
 
/* Testit<16> */ 

template<>
const char *const Testit<16>::Name="Test16 TreeUp";

template<>
bool Testit<16>::Main() 
 {
  OwnPtr<Engine> engine(new Engine);
  
  for(unsigned cnt=100; cnt ;cnt--) engine->run();
  
  return true;
 }
 
} // namespace App
 
