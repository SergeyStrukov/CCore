/* Event.h */ 
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

#ifndef CCore_inc_task_Event_h
#define CCore_inc_task_Event_h
 
#include <CCore/inc/task/TaskList.h>

namespace CCore {

/* classes */

struct EventNumber;

struct EventEvent;

struct EventEvent_task;

class Event;

/* struct EventNumber */

struct EventNumber
 {
  typedef uint16 ValueType;
  
  static const ValueType Base = 0 ;
  static const ValueType Lim = Base+DefaultEventElementCount ;
  static const EventMarker Marker = EventMarker_None ;
  
  static EventIdType Register(EventMetaInfo &info);  
 };

/* struct EventEvent */

struct EventEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint16 event;
  uint8 type;
  
  enum Type : uint8
   {
    Trigger
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 event_,Type type_)
   {
    time=time_;
    id=id_;
    
    event=event_;
    type=type_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<EventEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<EventEvent *>(ptr)->id); }
  
  static void * Offset_event(void *ptr) { return &(static_cast<EventEvent *>(ptr)->event); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<EventEvent *>(ptr)->type); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* struct EventEvent_task */

struct EventEvent_task
 {
  EventTimeType time;
  EventIdType id;
  
  uint16 task;
  uint16 event;
  uint8 type;
  
  enum Type : uint8
   {
    ToTask,
    Consume,
    Block
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 task_,uint16 event_,Type type_)
   {
    time=time_;
    id=id_;
    
    task=task_;
    event=event_;
    type=type_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<EventEvent_task *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<EventEvent_task *>(ptr)->id); }
  
  static void * Offset_event(void *ptr) { return &(static_cast<EventEvent_task *>(ptr)->event); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<EventEvent_task *>(ptr)->type); }
  
  static void * Offset_task(void *ptr) { return &(static_cast<EventEvent_task *>(ptr)->task); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class Event */ 

class Event : public Funchor_nocopy
 {
   TextLabel name;
   EventEnumValue<EventNumber> event_number;
   bool flag;
   TaskList list;
   
  private:
  
   static AutoTextNameType ObjName;
   
   void event(TaskBase *task,EventEvent_task::Type type);
   
   void event(EventEvent::Type type);
    
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
   
   void init(bool flag); 
   
   template <class T,class F>
   bool trigger_locked(T cur,F Release);
   
   bool wait_locked(MSec timeout);
   
  public: 
   
   // constructors
  
   explicit Event(int flag=false); // bool is assumed
   
   explicit Event(TextLabel name,bool flag=false);
   
   ~Event();
   
   TextLabel getName() const { return name; }
   
   // trigger
   
   bool trigger();
   
   bool trigger_int();
   
   bool trigger_any();
   
   // wait
   
   bool try_wait();
   
   void wait();
   
   bool wait(MSec timeout);
   
   bool wait(TimeScope time_scope);
   
   // functions
   
   void trigger_void() { trigger(); }
   
   void trigger_int_void() { trigger_int(); }
   
   void trigger_any_void() { trigger_any(); }
   
   Function<void (void)> function_trigger() { return FunctionOf(this,&Event::trigger_void); }
   
   Function<void (void)> function_trigger_int() { return FunctionOf(this,&Event::trigger_int_void); }
   
   Function<void (void)> function_trigger_any() { return FunctionOf(this,&Event::trigger_any_void); }
 };
 
} // namespace CCore
 
#endif
 

