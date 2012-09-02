/* AntiSem.h */ 
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

#ifndef CCore_inc_task_AntiSem_h
#define CCore_inc_task_AntiSem_h
 
#include <CCore/inc/task/TaskList.h>

namespace CCore {

/* classes */ 

struct AntiSemNumber;

struct AntiSemEvent;

struct AntiSemEvent_task;

class AntiSem;

/* struct AntiSemNumber */

struct AntiSemNumber
 {
  typedef uint16 ValueType;
  
  static const ValueType Base = 0 ;
  static const ValueType Lim = Base+DefaultEventElementCount ;
  
  static EventIdType Register(EventMetaInfo &info);  
 };

/* struct AntiSemEvent */

struct AntiSemEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint16 asem;
  uint8 type;
  
  enum Type : uint8
   {
    Add,
    Sub,
    Release
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 asem_,Type type_)
   {
    time=time_;
    id=id_;
    
    asem=asem_;
    type=type_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<AntiSemEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<AntiSemEvent *>(ptr)->id); }
  
  static void * Offset_asem(void *ptr) { return &(static_cast<AntiSemEvent *>(ptr)->asem); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<AntiSemEvent *>(ptr)->type); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* struct AntiSemEvent_task */

struct AntiSemEvent_task
 {
  EventTimeType time;
  EventIdType id;

  uint16 task;
  uint16 asem;
  uint8 type;
  
  enum Type : uint8
   {
    Wait,
    Pass
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 task_,uint16 asem_,Type type_)
   {
    time=time_;
    id=id_;
    
    task=task_;
    asem=asem_;
    type=type_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<AntiSemEvent_task *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<AntiSemEvent_task *>(ptr)->id); }
  
  static void * Offset_task(void *ptr) { return &(static_cast<AntiSemEvent_task *>(ptr)->task); }
  
  static void * Offset_asem(void *ptr) { return &(static_cast<AntiSemEvent_task *>(ptr)->asem); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<AntiSemEvent_task *>(ptr)->type); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class AntiSem */ 

class AntiSem : public Funchor_nocopy
 {
   TextLabel name;
   EventEnumValue<AntiSemNumber> asem_number;
   ulen count;
   ulen level;
   TaskList list;
   
  private:
  
   static AutoTextNameType ObjName;
   
   void event(TaskBase *task,AntiSemEvent_task::Type type);
   
   void event(AntiSemEvent::Type type);
 
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
   
   void init(ulen level); 
   
   void add_count(ulen dcount);
   
   void sub_count(ulen dcount);
   
   template <class T>
   void add_locked(T cur,ulen dcount);
   
   template <class T,class F>
   void sub_locked(T cur,F Release,ulen dcount);
   
   bool wait_locked(MSec timeout);
   
  public:
   
   // constructors
  
   explicit AntiSem(ulen level=0);
   
   explicit AntiSem(TextLabel name,ulen level=0);
   
   ~AntiSem();
   
   TextLabel getName() const { return name; }
   
   // add/sub
   
   void add(ulen dcount);
   
   void sub(ulen dcount);
   
   void add_int(ulen dcount);
   
   void sub_int(ulen dcount);
   
   void add_any(ulen dcount);
   
   void sub_any(ulen dcount);
   
   // inc/dec
   
   void inc() { add(1); }
   
   void dec() { sub(1); }
   
   void inc_int() { add_int(1); }
   
   void dec_int() { sub_int(1); }
   
   void inc_any() { add_any(1); }
   
   void dec_any() { sub_any(1); }
   
   // wait
   
   bool try_wait();
   
   void wait();
   
   bool wait(MSec timeout);
   
   bool wait(TimeScope time_scope);
   
   // functions
   
   Function<void (void)> function_inc() { return FunctionOf(this,&AntiSem::inc); }
   
   Function<void (void)> function_dec() { return FunctionOf(this,&AntiSem::dec); }
   
   Function<void (void)> function_inc_int() { return FunctionOf(this,&AntiSem::inc_int); }
   
   Function<void (void)> function_dec_int() { return FunctionOf(this,&AntiSem::dec_int); }
   
   Function<void (void)> function_inc_any() { return FunctionOf(this,&AntiSem::inc_any); }
   
   Function<void (void)> function_dec_any() { return FunctionOf(this,&AntiSem::dec_any); }
 };
 
} // namespace CCore
 
#endif
 

