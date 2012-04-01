/* test0015.Tree.cpp */ 
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

namespace Private_0015 {

/* class Engine */

struct Node : MemBase_nocopy
 {
  TreeLink<Node,unsigned> link;
 };
 
typedef TreeLink<Node,unsigned>::RadixAlgo<&Node::link> Algo;

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
    
   void test_locate()
    {
     unsigned key=getKey();
     
     {
      auto loc=root.locate(key);
      
      if( flags[key] )
        {
         if( !loc ) fail(30);
         
         if( Algo::Link(loc.node()).key!=key ) fail(31);
        }
      else
        {
         if( +loc ) fail(32);
        }
     }
     
     {
      auto loc=root.locateMin(key);
      
      if( +loc )
        {
         unsigned k=Algo::Link(loc.node()).key;
         
         if( k<key ) fail(33);
         
         for(; (k--)>key ;) if( flags[k] ) fail(34);
        }
      else
        {
         unsigned k=MaxKey+1;
         
         for(; (k--)>key ;) if( flags[k] ) fail(35);
        }  
     }
     
     {
      auto loc=root.locateMax(key);
      
      if( +loc )
        {
         unsigned k=Algo::Link(loc.node()).key;
         
         if( k>key ) fail(36);
         
         for(k++; k<=key ;k++) if( flags[k] ) fail(37);
        }
      else
        {
         unsigned k=0;
        
         for(; k<=key ;k++) if( flags[k] ) fail(38);
        }
     }
     
     {
      if( +root.locateMin()!=+root.locateMin(0) ) fail(39);
      
      if( +root.locateMax()!=+root.locateMax(MaxKey) ) fail(40);
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
        test_locate();
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
 
} // namespace Private_0015
 
using namespace Private_0015;
 
/* Testit<15> */ 

template<>
const char *const Testit<15>::Name="Test15 Tree";

template<>
bool Testit<15>::Main() 
 {
  OwnPtr<Engine> engine(new Engine);
  
  for(ulen cnt=1000; cnt ;cnt--) engine->run();
  
  return true;
 }
 
} // namespace App
 
