/* Tick.h */ 
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

#ifndef CCore_inc_task_Tick_h
#define CCore_inc_task_Tick_h

#include <CCore/inc/PlanInit.h>
#include <CCore/inc/List.h>

#include <CCore/inc/dev/DevTick.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_Tick();

/* classes */ 

class TickJob;

template <unsigned TPS> class TickCount_gen;

/* class TickJob */  
 
class TickJob : NoCopy
 {
   DLink<TickJob> link;
   Function<void (void)> action;
   bool active;
 
  public:
  
   explicit TickJob(Function<void (void)> action_int);
   
   ~TickJob();
   
   class Host;
   
   struct Internal;
   
   // IntLocked
  
   bool isActive() const { return active; }
   
   void start();
   
   void stop();
 };
 
/* struct TickJob::Internal */ 

struct TickJob::Internal
 {
  // IntLocked
   
  static void RunJobs_int();
 };
 
/* class TickCount_gen<unsigned TPS> */ 

template <unsigned TPS>
class TickCount_gen
 {
   static const unsigned dt=1000/TPS;
   static const unsigned dr=1000%TPS;
   
  private: 
     
   unsigned t;
   unsigned r;
   
   // represents fraction (t*TPS+r)/1000
   
  public:
  
   TickCount_gen() { set(0); }
   
   void set(unsigned timeout_msec)
    {
     t=timeout_msec;
     r=0;
    }
   
   bool tick();
    
   bool tick(unsigned period_msec);
 };
 
template <unsigned TPS>
bool TickCount_gen<TPS>::tick()
 {
  if( (t|r)==0 ) return true;
     
  if( r>=dr )
    {
     if( t>=dt )
       {
        r-=dr;
        t-=dt;
           
        return (t|r)==0;  
       }
     else
       {
        r=0;
        t=0;
           
        return true;
       }  
    }
  else
    {
     if( t>=dt+1 )
       {
        r+=(TPS-dr);
        t-=dt+1;
           
        return false;
       }
     else
       {
        r=0;
        t=0;
           
        return true;
       }  
    }  
 }
    
template <unsigned TPS>
bool TickCount_gen<TPS>::tick(unsigned period_msec)
 {
  if( period_msec<=dt ) return tick();
     
  if( r>=dr )
    {
     r-=dr;
        
     if( t>=dt )
       {
        t-=dt;
           
        if( (t|r)==0 )    
          {
           t=period_msec;
       
           return true;
          }
             
        return false;  
       }
     else
       {
        t+=(period_msec-dt);
          
        return true;
       }  
    }
  else
    {
     r+=(TPS-dr);
        
     if( t>=dt+1 )
       {
        t-=dt+1;
       
        return false;
       }
     else
       {
        t+=(period_msec-dt-1);
          
        return true;
       }  
    }
 }
    
/* types */     

typedef TickCount_gen<TicksPerSec> TickCount;
    
} // namespace CCore
 
#endif
 

