/* PlanInit.cpp */ 
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
 
#include <CCore/inc/PlanInit.h>

#include <CCore/inc/PrintAbort.h>

#if 0

#include <CCore/inc/Print.h>

#define Trace Con

#else

#define Trace NoPrint

#endif

namespace CCore {

/* class PlanInitNode::Engine */ 

class PlanInitNode::Engine : NoCopy
 {
   DLink<PlanInitNode>::LinearAlgo<&PlanInitNode::init_link>::FirstLast list;
  
  private:
   
   void add(PlanInitNode *node) { list.ins_last(node); }
   
   void append(PlanInitNode *node);
   
   void build();
   
   void init();
   
   void exit();
   
   static Engine Object;
   
  public:
  
   Engine();
   
   ~Engine();
   
   static SLink<PlanInitNode>::LinearAlgo<&PlanInitNode::link>::Top List;
 };
 
PlanInitNode::Engine PlanInitNode::Engine::Object CCORE_INITPRI_2 ;

SLink<PlanInitNode>::LinearAlgo<&PlanInitNode::link>::Top PlanInitNode::Engine::List CCORE_INITPRI_0 ;

bool PlanInitNode::prepare(PlanInitNode *back_)
 {
  if( flag==2 ) return false;
  
  if( flag==1 ) PrintAbort("Fatal error: plan init cyclic dependency, tag #;",tag);
  
  flag=1;
  back=back_;
  cur=req_list;
  
  return true;
 }

PlanInitNode * PlanInitNode::next()
 {
  if( !cur ) return 0;
  
  return cur.take();
 }

PlanInitNode * PlanInitNode::complete()
 {
  flag=2;
  
  return back;
 }

void PlanInitNode::Engine::append(PlanInitNode *node)
 {
  if( !node->prepare() ) return;
  
  while( node )
    {
     if( PlanInitNode *ptr=node->next() )
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
 
void PlanInitNode::Engine::build()
 {
  for(auto cur=List.start(); +cur ;++cur) cur->flag=0;
  
  for(auto cur=List.start(); +cur ;++cur) append(cur.ptr);
 }

void PlanInitNode::Engine::init()
 {
  for(auto cur=list.start(); +cur ;++cur)
    try
      {
       Printf(Trace,"Plan init : #;\n",cur->getTag());
       
       cur->init();
      }
    catch(...)  
      {
       PrintAbort("Fatal error: plan init exception, tag #;",cur->getTag());
      }
 }
   
void PlanInitNode::Engine::exit()
 {
  for(auto cur=list.start_rev(); +cur ;++cur)
    try
      {
       Printf(Trace,"Plan exit : #;\n",cur->getTag());
       
       cur->exit();
      }
    catch(...)  
      {
       PrintAbort("Fatal error: plan exit exception, tag #;",cur->getTag());
      }
 }
 
PlanInitNode::Engine::Engine()
 {
  build();
  
  init();
 }
 
PlanInitNode::Engine::~Engine()
 {
  exit();
 }
 
/* class PlanInitNode */ 

PlanInitNode::PlanInitNode(const char *tag_,PtrLen<PlanInitNode *> req_list_)
 : tag(tag_),
   req_list(req_list_)
 {
  Engine::List.ins(this);
 }
 
} // namespace CCore
 


