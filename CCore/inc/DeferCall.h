/* DeferCall.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.04
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_DeferCall_h
#define CCore_inc_DeferCall_h

#include <CCore/inc/MemBase.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Task.h>
#include <CCore/inc/Tuple.h>

namespace CCore {

/* classes */

class DeferCall;

class DeferCallQueue;

struct DeferCouple;

class DeferTick;

template <class S> class DeferInput;

/* class DeferCall */

class DeferCall : public MemBase_nocopy
 {
   DLink<DeferCall> link;
   
   friend class DeferCallQueue;
  
  public:
  
   DeferCall() {}
  
   virtual ~DeferCall() {}
   
   virtual void call()=0;
   
   void safeCall();
 };

/* class DeferCallQueue */

class DeferCallQueue : NoCopy
 {
   typedef DLink<DeferCall>::LinearAlgo<&DeferCall::link> Algo;
   
   Algo::FirstLast list;
   Algo::Top tick_list;
   Algo::Cur tick_cur;
   bool stop_flag;
   
  private:
   
   void cleanup() noexcept(EnableNoExcept);
   
   bool pump() noexcept(EnableNoExcept);
   
   bool tick() noexcept(EnableNoExcept);
   
   virtual void forward(TimeScope time_scope)=0;
   
  protected:
   
   void activate(); 
   
   void deactivate();
   
  public:
   
   // constructors
   
   DeferCallQueue();
   
   ~DeferCallQueue();
   
   // call
   
   void post(DeferCall *defer_call) { list.ins_last(defer_call); }
   
   void post_first(DeferCall *defer_call) { list.ins_first(defer_call); }
   
   void start_tick(DeferCall *defer_call) { tick_list.ins(defer_call); }
   
   void stop_tick(DeferCall *defer_call) 
    {
     if( defer_call==tick_cur.ptr )
       {
        tick_list.del_and_move(tick_cur);
       }
     else
       {
        tick_list.del(defer_call);
       }
    }
   
   // loop
   
   static constexpr MSec DefaultTickPeriod = 40_msec ; // 25 Hz 
   
   void loop(MSec tick_period=DefaultTickPeriod);
   
   void stop() { stop_flag=true; }
   
   // per-thread queue
   
   static DeferCallQueue * Get();
   
   static void Loop(MSec tick_period=DefaultTickPeriod) { Get()->loop(tick_period); }
   
   static void Stop() { Get()->stop(); }
 };

/* struct DeferCouple */

struct DeferCouple
 {
  DeferCallQueue *defer_queue;
  DeferCall *defer_call;
  
  DeferCouple() : defer_queue(0),defer_call(0) {}
  
  DeferCouple(DeferCallQueue *defer_queue_,DeferCall *defer_call_) 
   : defer_queue(defer_queue_),
     defer_call(defer_call_) 
   {
    if( !defer_call ) defer_queue=0; 
   }
  
  bool operator ! () const { return !defer_queue; }
  
  void cleanup() noexcept(EnableNoExcept)
   {
    if( defer_queue )
      {
       defer_queue=0;
       
       delete Replace_null(defer_call);
      }
   }
  
  void post() { defer_queue->post(defer_call); }
  
  void post_first() { defer_queue->post_first(defer_call); }
  
  void try_post() { if( defer_queue ) defer_queue->post(defer_call); }
  
  void try_post_first() { if( defer_queue ) defer_queue->post_first(defer_call); }
  
  void start_tick() { defer_queue->start_tick(defer_call); }
  
  void stop_tick() { defer_queue->stop_tick(defer_call); }
 };

/* class DeferTick */

class DeferTick : NoCopy
 {
   DeferCouple couple;
   bool active;
   
  public: 
   
   explicit DeferTick(DeferCouple couple_={}) : couple(couple_),active(false) {}
   
   ~DeferTick() { reset(); }
   
   bool set(DeferCouple couple);
   
   bool reset() { return set({}); }
   
   void operator = (DeferCouple couple) { set(couple); }
   
   bool start();
   
   bool stop();
 };

/* class DeferInput<S> */

template <class S> 
class DeferInput : NoCopy
 {
   S *obj;
   DeferCallQueue *defer_queue;
   
   class DeferBase : public DeferCall
    {
      DLink<DeferBase> link;
      DeferInput<S> *parent;
      
      friend class DeferInput<S>;
      
     protected:
     
      S *obj;
      
     private: 
      
      void cancel()
       {
        parent=0;
        obj=0;
       }
      
     public: 
      
      explicit DeferBase(DeferInput<S> *parent_) 
       : parent(parent_),
         obj(parent_->obj) 
       {
        parent->list.ins(this);
       }
      
      virtual ~DeferBase()
       {
        if( parent )
          {
           parent->list.del(this);
          }
       }
    };
   
   typedef typename DLink<DeferBase>::template LinearAlgo<&DeferBase::link> Algo;
   
   typename Algo::Top list;
   
   template <class ... TT>
   class DeferMethod : public DeferBase
    {
      void (S::* method)(TT... tt);
      Tuple<TT...> args;
        
     public:
     
      DeferMethod(DeferInput<S> *parent,void (S::* method_)(TT... tt),const TT & ... tt)
       : DeferBase(parent),
         method(method_),
         args(tt...)
       {
       }
      
      virtual ~DeferMethod() {}
      
      virtual void call() 
       { 
        if( S *obj_=this->obj )
          {
           void (S::* method_)(TT... tt)=method;
          
           args.call( [=] (const TT & ... tt) { (obj_->*method_)(tt...); } ); 
          }
       }
    };
   
   template <class Func>
   class DeferFunc : public DeferBase
    {
      Func func;
      
     public:
      
      DeferFunc(DeferInput<S> *parent,const Func &func_) : DeferBase(parent),func(func_) {}
      
      virtual ~DeferFunc() {}
      
      virtual void call()
       {
        if( S *obj_=this->obj ) func(*obj_);
       }
    };
   
  public:
 
   explicit DeferInput(S *obj);
   
   ~DeferInput() { cancel(); }
   
   void cancel();
   
   template <class ... TT>
   DeferCouple create(void (S::* method)(TT... tt),const TT & ... tt) 
    {  
     return DeferCouple(defer_queue,new DeferMethod<TT...>(this,method,tt...));
    }
   
   template <class ... TT>
   void post(void (S::* method)(TT... tt),const TT & ... tt) 
    { 
     create(method,tt...).post(); 
    }
   
   template <class ... TT>
   void post_first(void (S::* method)(TT... tt),const TT & ... tt) 
    { 
     create(method,tt...).post_first(); 
    }
   
   template <class ... TT>
   DeferCouple try_create(void (S::* method)(TT... tt),const TT & ... tt) 
    {  
     return DeferCouple(defer_queue,new(JustTry) DeferMethod<TT...>(this,method,tt...));
    }
   
   template <class ... TT>
   void try_post(void (S::* method)(TT... tt),const TT & ... tt) 
    { 
     try_create(method,tt...).try_post(); 
    }
   
   template <class ... TT>
   void try_post_first(void (S::* method)(TT... tt),const TT & ... tt) 
    { 
     try_create(method,tt...).try_post_first(); 
    }
   
   template <class Func>
   DeferCouple create(Func func) // func(S &)
    {
     return DeferCouple(defer_queue,new DeferFunc<Func>(this,func));
    }
   
   template <class Func>
   void post(Func func) 
    { 
     create(func).post(); 
    }
   
   template <class Func>
   void post_first(Func func) 
    { 
     create(func).post_first(); 
    }
   
   template <class Func>
   DeferCouple try_create(Func func) // func(S &)
    {
     return DeferCouple(defer_queue,new(JustTry) DeferFunc<Func>(this,func));
    }
   
   template <class Func>
   void try_post(Func func) 
    { 
     try_create(func).try_post(); 
    }
   
   template <class Func>
   void try_post_first(Func func) 
    { 
     try_create(func).try_post_first(); 
    }
 };

template <class S> 
DeferInput<S>::DeferInput(S *obj_)
 : obj(obj_),
   defer_queue(DeferCallQueue::Get())
 {
 }

template <class S> 
void DeferInput<S>::cancel()
 {
  for(auto cur=list.start(); +cur ;++cur) cur->cancel();
  
  list.init();
 }

} // namespace CCore
 
#endif
 

