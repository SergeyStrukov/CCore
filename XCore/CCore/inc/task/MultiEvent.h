/* MultiEvent.h */ 
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

#ifndef CCore_inc_task_MultiEvent_h
#define CCore_inc_task_MultiEvent_h
 
#include <CCore/inc/task/TaskList.h>

namespace CCore {

/* classes */ 

struct MultiEventNumber;

struct MultiEventEvent;

struct MultiEventEvent_task;

class MultiEventBase;

template <ulen Len> class MultiEvent;

/* struct MultiEventNumber */

struct MultiEventNumber
 {
  typedef uint16 ValueType;
  
  static const ValueType Base = 0 ;
  static const ValueType Lim = Base+DefaultEventElementCount ;
  static const EventMarker Marker = EventMarker_None ;
  
  static EventIdType Register(EventMetaInfo &info);  
 };

/* struct MultiEventEvent */

struct MultiEventEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint16 mevent;
  uint8 type;
  uint8 index;
  
  enum Type : uint8
   {
    Trigger
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 mevent_,Type type_,ulen index_)
   {
    time=time_;
    id=id_;
    
    mevent=mevent_;
    type=type_;
    index=(uint8)index_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<MultiEventEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<MultiEventEvent *>(ptr)->id); }
  
  static void * Offset_mevent(void *ptr) { return &(static_cast<MultiEventEvent *>(ptr)->mevent); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<MultiEventEvent *>(ptr)->type); }
  
  static void * Offset_index(void *ptr) { return &(static_cast<MultiEventEvent *>(ptr)->index); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* struct MultiEventEvent_task */

struct MultiEventEvent_task
 {
  EventTimeType time;
  EventIdType id;

  uint16 task;
  uint16 mevent;
  uint8 type;
  uint8 index;
  
  enum Type : uint8
   {
    ToTask,
    Block,
    Consume
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 task_,uint16 mevent_,Type type_,ulen index_)
   {
    time=time_;
    id=id_;
    
    task=task_;
    mevent=mevent_;
    type=type_;
    index=(uint8)index_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<MultiEventEvent_task *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<MultiEventEvent_task *>(ptr)->id); }
  
  static void * Offset_task(void *ptr) { return &(static_cast<MultiEventEvent_task *>(ptr)->task); }
  
  static void * Offset_mevent(void *ptr) { return &(static_cast<MultiEventEvent_task *>(ptr)->mevent); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<MultiEventEvent_task *>(ptr)->type); }
  
  static void * Offset_index(void *ptr) { return &(static_cast<MultiEventEvent_task *>(ptr)->index); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class MultiEventBase */ 

class MultiEventBase : public Funchor_nocopy
 {
   TextLabel name;
   EventEnumValue<MultiEventNumber> mevent_number;
   PtrLen<bool> flags;
   ulen base;
   TaskList list;
   
  private:
  
   static AutoTextNameType ObjName;
    
   void event(TaskBase *task,MultiEventEvent_task::Type type,ulen index=0);
   
   void event(MultiEventEvent::Type type,ulen index);
   
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
   
   void init(PtrLen<bool> flags); 
   
   ulen nextIndex(ulen index) { return (index+1<flags.len)?index+1:0; }
   
   template <class T,class F>
   bool trigger_locked(T cur,F Release,ulen index);
   
   ulen try_wait_locked();
   
   ulen wait_locked(MSec timeout);
   
  protected:
   
   explicit MultiEventBase(PtrLen<bool> flags);
   
   MultiEventBase(TextLabel name,PtrLen<bool> flags);
   
   ~MultiEventBase();
   
  public: 
   
   TextLabel getName() const { return name; }
   
   // trigger
  
   bool trigger(ulen index); // [1,Len]
   
   bool trigger_int(ulen index); // [1,Len]
   
   bool trigger_any(ulen index); // [1,Len]
   
   // wait
   
   ulen try_wait(); // [0,Len]
   
   ulen wait(); // [1,Len]
   
   ulen wait(MSec timeout); // [0,Len]
   
   ulen wait(TimeScope time_scope); // [0,Len]
   
   // trigger<Index>
   
   template <ulen Index> // [1,Len]
   void trigger_index() { trigger(Index); }
   
   template <ulen Index> // [1,Len]
   void trigger_index_int() { trigger_int(Index); }
   
   template <ulen Index> // [1,Len]
   void trigger_index_any() { trigger_any(Index); }
   
   // functions
   
   template <ulen Index>
   Function<void (void)> function_trigger() { return FunctionOf(this,&MultiEventBase::trigger_index<Index>); }
   
   template <ulen Index>
   Function<void (void)> function_trigger_int() { return FunctionOf(this,&MultiEventBase::trigger_index_int<Index>); }
   
   template <ulen Index>
   Function<void (void)> function_trigger_any() { return FunctionOf(this,&MultiEventBase::trigger_index_any<Index>); }
 };
 
/* class MultiEvent<ulen Len> */ 

template <ulen Len> 
class MultiEvent : public MultiEventBase
 {
   bool flags[Len];
   
  public:
  
   MultiEvent() : MultiEventBase(Range(flags)) {}
   
   explicit MultiEvent(TextLabel name) : MultiEventBase(name,Range(flags)) {}
   
   ~MultiEvent() {}
 };
 
} // namespace CCore
 
#endif
 

