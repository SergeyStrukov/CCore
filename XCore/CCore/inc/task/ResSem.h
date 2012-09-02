/* ResSem.h */ 
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

#ifndef CCore_inc_task_ResSem_h
#define CCore_inc_task_ResSem_h
 
#include <CCore/inc/task/TaskList.h>

namespace CCore {

/* classes */

struct ResSemNumber;

struct ResSemEvent;

struct ResSemEvent_task;

class ResSem;

/* struct ResSemNumber */

struct ResSemNumber
 {
  typedef uint16 ValueType;
  
  static const ValueType Base = 0 ;
  static const ValueType Lim = Base+DefaultEventElementCount ;
  
  static EventIdType Register(EventMetaInfo &info);  
 };

/* struct ResSemEvent */

struct ResSemEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint16 rsem;
  uint8 type;
  
  enum Type : uint8
   {
    Give
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 rsem_,Type type_)
   {
    time=time_;
    id=id_;
    
    rsem=rsem_;
    type=type_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<ResSemEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<ResSemEvent *>(ptr)->id); }
  
  static void * Offset_rsem(void *ptr) { return &(static_cast<ResSemEvent *>(ptr)->rsem); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<ResSemEvent *>(ptr)->type); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* struct ResSemEvent_task */

struct ResSemEvent_task
 {
  EventTimeType time;
  EventIdType id;
  
  uint16 task;
  uint16 rsem;
  uint8 type;
  
  enum Type : uint8
   {
    ToTask,
    Wait,
    Pass,
    Block,
    Take
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 task_,uint16 rsem_,Type type_)
   {
    time=time_;
    id=id_;
    
    task=task_;
    rsem=rsem_;
    type=type_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<ResSemEvent_task *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<ResSemEvent_task *>(ptr)->id); }
  
  static void * Offset_task(void *ptr) { return &(static_cast<ResSemEvent_task *>(ptr)->task); }
  
  static void * Offset_rsem(void *ptr) { return &(static_cast<ResSemEvent_task *>(ptr)->rsem); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<ResSemEvent_task *>(ptr)->type); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class ResSem */ 

class ResSem : public Funchor_nocopy
 {
   TextLabel name;
   EventEnumValue<ResSemNumber> rsem_number;
   ulen count;
   ulen max_count;
   TaskList take_list;
   TaskList wait_list;
   
  private:
  
   static AutoTextNameType ObjName;
   
   void event(TaskBase *task,ResSemEvent_task::Type type);
    
   void event(ResSemEvent::Type type);
   
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
   
   void init(ulen max_count);
   
   template <class T,class F,class FL>
   void give_locked(T cur,F Release,FL ReleaseList);
   
   bool take_locked(MSec timeout);
   
   bool wait_locked(MSec timeout);
   
  public: 
   
   // constructors
  
   explicit ResSem(ulen max_count);
   
   ResSem(TextLabel name,ulen max_count);
   
   ~ResSem();
   
   TextLabel getName() const { return name; }
   
   // give
   
   void give();
   
   void give_int();
   
   void give_any();
   
   // take
  
   bool try_take();
  
   void take();
  
   bool take(MSec timeout);
  
   bool take(TimeScope time_scope);
   
   // wait
   
   bool try_wait();
   
   void wait();
  
   bool wait(MSec timeout);
   
   bool wait(TimeScope time_scope);
   
   // functions
   
   Function<void (void)> function_give() { return FunctionOf(this,&ResSem::give); }
   
   Function<void (void)> function_give_int() { return FunctionOf(this,&ResSem::give_int); }
   
   Function<void (void)> function_give_any() { return FunctionOf(this,&ResSem::give_any); }
 };
 
} // namespace CCore
 
#endif
 

