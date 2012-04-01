/* test0024.PlanInitBuild.cpp */ 
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

#include <CCore/inc/MemBase.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Abort.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/OwnPtr.h>

namespace App {

namespace Private_0024 {

/* struct Node */

struct Node
 {
  ulen order;
  
  PtrLen<Node *> req_list;
 
  SLink<Node> init_link;
  
  int flag;
  Node *back;
  PtrLen<Node *> cur;
  
  bool prepare(Node *back_=0)
   {
    if( flag==2 ) return false;
    
    if( flag==1 )
      {
       throw CatchType();
      }
    
    flag=1;
    back=back_;
    cur=req_list;
    
    return true;
   }
  
  Node * next()
   {
    if( !cur ) return 0;
    
    return cur.take();
   }
  
  Node * complete()
   {
    flag=2;
    
    return back;
   }
 };

/* struct Build */
 
struct Build
 {
  SLink<Node>::LinearAlgo<&Node::init_link>::FirstLast list;
     
  Build() {}
      
  void add(Node *node) { list.ins_last(node); }
  
  void append(Node *node)
   {
    if( !node->prepare() ) return;
    
    while( node )
      {
       if( Node *ptr=node->next() )
         {
          if( ptr->prepare(node) ) node=ptr;
         }
       else
         {
          add(node);
          
          node=node->complete();
         }
      }
   }
   
  template <class R> 
  void build(R r)
   {
    for(R cur=r; +cur ;++cur) cur->flag=0;
    
    for(R cur=r; +cur ;++cur) append(cur.ptr);
   }
 };

/* class Engine */

class Engine : public MemBase_nocopy
 {
   static const ulen Len    = 1000  ;
   static const ulen ReqLen = 10000 ;
   static const ulen MaxReq = 20    ;
 
   Node nodes[Len];
   Node * reqs[ReqLen];
   Build build;
   Random random;
   
  private:
  
   void prepare()
    {
     for(ulen cnt=Len; cnt ;cnt--)
       {
        ulen i=random.select(Len);
        ulen j=random.select(Len);
        
        Swap(nodes[i].order,nodes[j].order);
       }
    
     ulen off=0;
    
     for(ulen i=0; i<Len ;i++)
       {
        ulen len=random.select(0,MaxReq);
        
        Replace_min(len,ReqLen-off);
        
        PtrLen<Node *> req=Range(reqs+off,len);
       
        for(ulen cnt=10*len; +req && cnt ;cnt--) 
          {
           ulen j=random.select(Len);
           
           if( nodes[i].order>nodes[j].order )
             {
              *req=nodes+j;
              
              ++req;
             }
          }
          
        len-=req.len;  
          
        nodes[i].req_list=PtrLen<Node *>(reqs+off,len);
        
        off+=len;
       }
    }
    
   void make_cycle()
    {
     Node *start;
     
     do
       {
        start=nodes+random.select(Len);
       }
     while( start->req_list.len==0 );
     
     Node *node=start;
     
     while( random.select(4) )
       {
        ulen j=random.select(node->req_list.len);
        
        Node *next=node->req_list[j];
        
        if( next->req_list.len )
          {
           node=next;
          }
        else
          {
           node->req_list[j]=start;
           
           return;
          }
       }
       
     {
      ulen j=random.select(node->req_list.len);
      
      node->req_list[j]=start;
     }  
    }
  
   bool step()
    {
     prepare();
     
     try
       {
        build.build(Range(nodes));
        
        return true;
       }
     catch(CatchType)  
       {
        return false;
       }
    }
  
   bool step_cycle()
    {
     prepare();
     
     make_cycle();
     
     try
       {
        build.build(Range(nodes));
        
        return false;
       }
     catch(CatchType)  
       {
        return true;
       }
    }
    
  public:
  
   Engine()
    {
     for(ulen i=0; i<Len ;i++)
       {
        nodes[i].order=i;
       }
    }
   
   ~Engine()
    {
    }
   
   void run()
    {
     ReportException report;
     
     const ulen Count = 1000 ;
    
     ulen count_ok=0;
     
     for(ulen cnt=Count; cnt ;cnt--) count_ok+=step();
     
     Printf(Con,"#; from #;\n",count_ok,Count);
     
     count_ok=0;
     
     for(ulen cnt=Count; cnt ;cnt--) count_ok+=step_cycle();
     
     Printf(Con,"#; from #;\n",count_ok,Count);
    }
 };
 
} // namespace Private_0024
 
using namespace Private_0024; 
 
/* Testit<24> */ 

template<>
const char *const Testit<24>::Name="Test24 PlanInitBuild";

template<>
bool Testit<24>::Main() 
 { 
  OwnPtr<Engine> engine(new Engine);
  
  engine->run();
 
  return true;
 }
 
} // namespace App
 
