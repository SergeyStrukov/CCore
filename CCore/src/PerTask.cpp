/* PerTask.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/PerTask.h>
 
#include <CCore/inc/sys/SysTlsSlot.h>
#include <CCore/inc/sys/SysPlanInit.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>

namespace CCore {

/* functions */

void GuardTaskObjectNoBuilder()
 {
  Printf(Exception,"CCore::GetTaskObject<...>() : no object builder");
 }

/* class PerTask::List */

class PerTask::List : NoCopy
 {
   Mutex mutex;
   
   DLink<PerTask>::LinearAlgo<&PerTask::link>::Top list;
   
   DynArray<BuilderSlot> bslots;
   
  private: 
   
   void clear(ulen slot_id,TaskObjectFlag flag)
    {
     if( flag==TaskObjectSoft )
       {
        for(auto cur=list.start(); +cur ;++cur) 
          {
           Slot &slot=cur->slots[slot_id];
           
           slot.del_flag=1;
          }
       }
     else
       {
        for(auto cur=list.start(); +cur ;++cur) 
          {
           Slot &slot=cur->slots[slot_id];
           
           void *obj=Replace_null(slot.obj);
           
           if( obj ) bslots[slot_id].destroy(obj);
          }
       }
    }
   
  public:
   
   List() : mutex("!PerTask"),bslots(SlotCount) {}
   
   ~List() {}
   
   void ins(PerTask *obj)
    {
     Mutex::Lock lock(mutex);
     
     list.ins(obj);
    }
   
   void del(PerTask *obj)
    {
     Mutex::Lock lock(mutex);
     
     list.del(obj);
    }
 
   void setBuilder(ulen slot_id,TaskObjectFlag flag,BuilderSlot bslot)
    {
     Mutex::Lock lock(mutex);

     if( bslots[slot_id].isTaken() )
       {
        Printf(Exception,"CCore::TaskObjectBuild<...>::TaskObjectBuild(...) : object builder is already assigned");
       }
     
     bslots[slot_id]=bslot;
     
     clear(slot_id,flag);
    }
   
   void clearBuilder(ulen slot_id,TaskObjectFlag flag)
    {
     Mutex::Lock lock(mutex);
     
     bslots[slot_id].clear();
     
     clear(slot_id,flag);
    }
   
   void * create(ulen slot_id) 
    {
     Mutex::Lock lock(mutex);
     
     return bslots[slot_id].create();
    }
   
   void * try_create(ulen slot_id) noexcept 
    {
     Mutex::Lock lock(mutex);
     
     return bslots[slot_id].try_create();
    }
   
   void destroy(ulen slot_id,void *obj) noexcept
    {
     Mutex::Lock lock(mutex);
     
     bslots[slot_id].destroy(obj);
    }
 };

/* GetPlanInitNode_...() */ 

namespace Private_PerTask {

class PerTaskHost : public PerTask::List
 {
   Sys::TlsSlot slot;
   
  public:
  
   PerTaskHost()
    {
     if( slot.init() ) Abort("Fatal error : TLS is full"); 
    }
  
   ~PerTaskHost()
    {
     slot.exit(); 
    }
   
   void set(void *value) { slot.set(value); }
  
   void * get() { return slot.get(); }
   
   static const char * GetTag() { return "PerTask"; }
 };

PlanInitObject<PerTaskHost,PlanInitReq<Sys::GetPlanInitNode_Sys>
                          ,PlanInitReq<GetPlanInitNode_MemBase> 
                          > Object CCORE_INITPRI_1 ;

} // namespace Private_PerTask
 
using namespace Private_PerTask;
 
PlanInitNode * GetPlanInitNode_PerTask() { return &Object; }

/* class PerTask */

ulen PerTask::SlotCount = 0 ;

PerTask::PerTask()
 : slots(SlotCount)
 {
  Object->ins(this);
 }
  
PerTask::~PerTask()
 {
  Object->del(this);
  
  for(ulen slot_id=0,len=slots.getLen(); slot_id<len ;slot_id++) 
    {
     if( void *obj=slots[slot_id].obj ) Destroy(slot_id,obj);
    }
 }

void PerTask::SetBuilder(ulen slot_id,TaskObjectFlag flag,BuilderSlot bslot)
 {
  Object->setBuilder(slot_id,flag,bslot);
 }

void PerTask::ClearBuilder(ulen slot_id,TaskObjectFlag flag)
 {
  Object->clearBuilder(slot_id,flag);
 }

void * PerTask::Create(ulen slot_id)
 {
  return Object->create(slot_id);
 }

void * PerTask::TryCreate(ulen slot_id) noexcept
 {
  return Object->try_create(slot_id);
 }

void PerTask::Destroy(ulen slot_id,void *obj) noexcept
 {
  Object->destroy(slot_id,obj);
 }

PerTask * PerTask::Get()
 {
  if( void *obj=Object->get() ) return static_cast<PerTask *>(obj);
  
  PerTask *ret=new PerTask();
  
  Object->set(ret);
  
  return ret;
 }

PerTask * PerTask::TryGet() noexcept
 {
  if( void *obj=Object->get() ) return static_cast<PerTask *>(obj);
  
  try
    {
     PerTask *ret=new PerTask();
    
     Object->set(ret);
    
     return ret;
    }
  catch(...)
    {
     return 0;
    }
 }

/* class DestroyPerTask */

static DestroyPerTask ForMainTask;

DestroyPerTask::~DestroyPerTask()
 {
  if( void *obj=Object->get() ) 
    {
     delete static_cast<PerTask *>(obj);
     
     Object->set(0);
    }
 }

} // namespace CCore
 

