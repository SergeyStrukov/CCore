/* Tick.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/task/Tick.h>

#include <CCore/inc/Abort.h>

#include <CCore/inc/dev/DevInt.h>

namespace CCore {

/* class TickJob::Host */ 

class TickJob::Host : NoCopy
 {
   typedef DLink<TickJob>::LinearAlgo<&TickJob::link> Algo;
 
   Algo::Top top;
   Algo::Cur next;
   
  public:
  
   Host() 
    : next(0)
    {
    }
   
   void ins(TickJob *obj)
    {
     top.ins(obj);
    }
   
   void del(TickJob *obj) 
    {
     if( obj==next.ptr ) ++next;
   
     top.del(obj);
    }
   
   void run()
    {
     for(auto cur=top.start(); +cur ;)
       {
        TickJob *ptr=cur.ptr;
        
        ++cur;
       
        next=cur;
     
        ptr->action();
     
        cur=next;
       }
    }
    
   static const char * GetTag() { return "Tick"; } 
 };
 
/* GetPlanInitNode_...() */ 

namespace Private_Tick {

PlanInitObject<TickJob::Host> Object CCORE_INITPRI_1 ;

} // namespace Private_Tick
 
using namespace Private_Tick; 
 
PlanInitNode * GetPlanInitNode_Tick() { return &Object; }
 
/* class TickJob */  

void TickJob::Internal::RunJobs_int()
 {
  Object->run();
 }
  
TickJob::TickJob(Function<void (void)> action_)
 : action(action_),
   active(false)
 {
 }
   
TickJob::~TickJob()
 {
  Dev::IntLock lock;
  
  if( active ) Abort("Fatal error : TickJob is attached on exit");
 }
 
void TickJob::start()
 {
  if( active ) return;
  
  Object->ins(this);
  
  active=true;
 }
   
void TickJob::stop()
 {
  if( !active ) return;
  
  Object->del(this);
  
  active=false;
 }
   
} // namespace CCore
 

