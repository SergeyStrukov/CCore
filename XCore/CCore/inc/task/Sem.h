/* Sem.h */ 
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

#ifndef CCore_inc_task_Sem_h
#define CCore_inc_task_Sem_h

#include <CCore/inc/task/TaskList.h>
 
namespace CCore {

/* classes */

struct SemNumber;

struct SemEvent;

struct SemEvent_task;

class Sem;

/* struct SemNumber */

struct SemNumber
 {
  typedef uint16 ValueType;
  
  static const ValueType Base = 0 ;
  static const ValueType Lim = Base+DefaultEventElementCount ;
  static const EventMarker Marker = EventMarker_None ;
  
  static EventIdType Register(EventMetaInfo &info);  
 };

/* struct SemEvent */

struct SemEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint16 sem;
  uint8 type;
  
  enum Type : uint8
   {
    ToTaskList,
    Give,
    GiveMany
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 sem_,Type type_)
   {
    time=time_;
    id=id_;
    
    sem=sem_;
    type=type_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<SemEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<SemEvent *>(ptr)->id); }
  
  static void * Offset_sem(void *ptr) { return &(static_cast<SemEvent *>(ptr)->sem); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<SemEvent *>(ptr)->type); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* struct SemEvent_task */

struct SemEvent_task
 {
  EventTimeType time;
  EventIdType id;
  
  uint16 task;
  uint16 sem;
  uint8 type;
  
  enum Type : uint8
   {
    ToTask, 
    Take,    
    Block  
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 task_,uint16 sem_,Type type_)
   {
    time=time_;
    id=id_;
    
    task=task_;
    sem=sem_;
    type=type_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<SemEvent_task *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<SemEvent_task *>(ptr)->id); }
  
  static void * Offset_task(void *ptr) { return &(static_cast<SemEvent_task *>(ptr)->task); }
  
  static void * Offset_sem(void *ptr) { return &(static_cast<SemEvent_task *>(ptr)->sem); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<SemEvent_task *>(ptr)->type); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class Sem */ 

class Sem : public Funchor_nocopy
 {
   TextLabel name;
   EventEnumValue<SemNumber> sem_number;
   ulen count;
   TaskList list;
  
  private:
  
   static AutoTextNameType ObjName;
    
   void event(TaskBase *task,SemEvent_task::Type type);
   
   void event(SemEvent::Type type);
   
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
   
   void init(ulen count);
   
   void inc();
   
   void add(ulen dcount);
   
   template <class T,class F>
   void give_locked(T cur,F Release);
   
   template <class T,class F>
   void give_many_locked(T cur,F Release,ulen dcount);
   
   bool take_locked(MSec timeout);
   
  public:
   
   // constructors
  
   explicit Sem(ulen count=0);
   
   explicit Sem(TextLabel name,ulen count=0);
   
   ~Sem();
   
   TextLabel getName() const { return name; }
   
   // give
   
   void give();
   
   void give_int();
   
   void give_any();
   
   void give_many(ulen dcount);
   
   void give_many_int(ulen dcount);
   
   void give_many_any(ulen dcount);
   
   // take
   
   bool try_take();
   
   void take();
   
   bool take(MSec timeout);
   
   bool take(TimeScope time_scope);
   
   // functions
   
   Function<void (void)> function_give() { return FunctionOf(this,&Sem::give); }
   
   Function<void (void)> function_give_int() { return FunctionOf(this,&Sem::give_int); }
   
   Function<void (void)> function_give_any() { return FunctionOf(this,&Sem::give_any); }
 };
 
} // namespace CCore
 
#endif
 

