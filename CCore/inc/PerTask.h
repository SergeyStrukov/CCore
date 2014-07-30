/* PerTask.h */ 
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

#ifndef CCore_inc_PerTask_h
#define CCore_inc_PerTask_h

#include <CCore/inc/PlanInit.h>
#include <CCore/inc/Task.h>
#include <CCore/inc/MemBase.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Array.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_PerTask();

/* enum TaskObjectFlag */

enum TaskObjectFlag
 {
  TaskObjectSoft,
  TaskObjectHard
 };

/* functions */

void GuardTaskObjectNoBuilder();

/* classes */

class PerTask;

class DestroyPerTask;

template <class TOC> class TaskObjectBuild;

/* class PerTask */

#if 0

struct TaskObjectControl
 {
  class ObjectType
   {
    public:
    
     void destroy();
   };

  class BuilderType
   {
    public:
    
     ObjectType * create();
   };
 };

#endif

class PerTask : public MemBase_nocopy
 {
   DLink<PerTask> link;
   
   struct Slot : NoThrowFlagsBase
    {
     void *obj = 0 ;
     Atomic del_flag;
     
     Slot() {}
     
     void * getObj(ulen slot_id)
      {
       if( obj ) 
         {
          if( !del_flag ) return obj;
          
          del_flag=0;
          
          Destroy(slot_id,Replace_null(obj));
         }
       
       return obj=Create(slot_id); 
      }
     
     void * tryGetObj(ulen slot_id) noexcept
      {
       if( obj ) 
         {
          if( !del_flag ) return obj;
          
          del_flag=0;
          
          Destroy(slot_id,Replace_null(obj));
         }
       
       return obj=TryCreate(slot_id); 
      }
    };
   
   DynArray<Slot> slots;
   
  private: 
  
   static ulen SlotCount;
   
   class SlotId : NoCopy
    {
      ulen id;
      
     public: 
      
      SlotId() : id(SlotCount++) {}
      
      operator ulen() const { return id; }
    };
   
   template <class TOC> 
   struct TaskObjectSlotId
    {
     static SlotId Id;
    };
   
  private:
   
   PerTask();
  
   ~PerTask();
   
   friend class DestroyPerTask;
   
   class BuilderSlot : public NoThrowFlagsBase
    {
      void *builder;
      void * (*create_func)(void *builder);
      void (*destroy_func)(void *obj);
      
     private: 
      
      template <class TOC>
      static void * CreateFunc(void *builder_)
       {
        typename TOC::BuilderType *builder=static_cast<typename TOC::BuilderType *>(builder_);
        
        typename TOC::ObjectType *obj=builder->create();
        
        return obj;
       }
      
      template <class TOC>
      static void DestroyFunc(void *obj)
       {
        static_cast<typename TOC::ObjectType *>(obj)->destroy();
       }
      
     public: 
     
      BuilderSlot() : builder(0),create_func(0),destroy_func(0) {}
      
      bool isTaken() const { return builder!=0; }
     
      template <class TOC>
      void init(typename TOC::BuilderType *builder_)
       {
        builder=builder_;
        create_func=CreateFunc<TOC>;
        destroy_func=DestroyFunc<TOC>;
       }
     
      void clear() { builder=0; }
      
      void * create() const
       {  
        if( !builder ) GuardTaskObjectNoBuilder();
        
        return create_func(builder);
       }
      
      void * try_create() const noexcept
       {  
        if( !builder ) return 0;
        
        try
          {
           return create_func(builder);
          }
        catch(...)
          {
           return 0;
          }
       }    
      
      void destroy(void *obj) const noexcept
       {
        destroy_func(obj);
       }
    };
   
   static void SetBuilder(ulen slot_id,TaskObjectFlag flag,BuilderSlot bslot);
   
   static void ClearBuilder(ulen slot_id,TaskObjectFlag flag);
   
   static void * Create(ulen slot_id);
   
   static void * TryCreate(ulen slot_id) noexcept;
   
   static void Destroy(ulen slot_id,void *obj) noexcept;
  
  public:
  
   class List;
  
   static PerTask * Get();
   
   static PerTask * TryGet() noexcept;
   
   template <class TOC>
   typename TOC::ObjectType * getTaskObject()
    {
     ulen slot_id=TaskObjectSlotId<TOC>::Id;
     
     return static_cast<typename TOC::ObjectType *>(slots[slot_id].getObj(slot_id));
    }
   
   template <class TOC>
   typename TOC::ObjectType * tryGetTaskObject() noexcept
    {
     ulen slot_id=TaskObjectSlotId<TOC>::Id;
     
     return static_cast<typename TOC::ObjectType *>(slots[slot_id].tryGetObj(slot_id));
    }
   
   template <class TOC>
   static void SetBuilder(TaskObjectFlag flag,typename TOC::BuilderType *builder)
    {
     BuilderSlot bslot;
     
     bslot.init<TOC>(builder);
     
     SetBuilder(TaskObjectSlotId<TOC>::Id,flag,bslot);
    }
   
   template <class TOC>
   static void ClearBuilder(TaskObjectFlag flag)
    {
     ClearBuilder(TaskObjectSlotId<TOC>::Id,flag);
    }
 };

template <class TOC> 
PerTask::SlotId PerTask::TaskObjectSlotId<TOC>::Id CCORE_INITPRI_0 ;

/* class DestroyPerTask */

class DestroyPerTask : NoCopy
 {
  public:
  
   ~DestroyPerTask();
 };

/* GetTaskObject<TOC>() */

template <class TOC>
typename TOC::ObjectType * GetTaskObject() 
 { 
  return PerTask::Get()->getTaskObject<TOC>(); 
 }

template <class TOC>
typename TOC::ObjectType * TryGetTaskObject() noexcept 
 { 
  if( PerTask *obj=PerTask::TryGet() ) return obj->tryGetTaskObject<TOC>();
  
  return 0;
 }

/* class TaskObjectBuild<TOC> */

template <class TOC> 
class TaskObjectBuild : NoCopy
 {
   using BuilderType = typename TOC::BuilderType ;
   
   TaskObjectFlag flag;
   BuilderType builder;
 
  public:
 
   template <class ... SS>
   explicit TaskObjectBuild(TaskObjectFlag flag_,SS && ... ss)
    : flag(flag_),
      builder( std::forward<SS>(ss)... )
    {
     PerTask::SetBuilder<TOC>(flag_,&builder);
    }
   
   ~TaskObjectBuild()
    {
     PerTask::ClearBuilder<TOC>(flag);
    }
 };

} // namespace CCore
 
#endif
 

