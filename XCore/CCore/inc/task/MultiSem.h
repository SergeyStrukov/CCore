/* MultiSem.h */ 
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

#ifndef CCore_inc_task_MultiSem_h
#define CCore_inc_task_MultiSem_h
 
#include <CCore/inc/task/TaskList.h>

namespace CCore {

/* classes */

struct MultiSemNumber;

struct MultiSemEvent;

struct MultiSemEvent_task;

class MultiSemBase;

template <ulen Len> class MultiSem;

/* struct MultiSemNumber */

struct MultiSemNumber
 {
  typedef uint16 ValueType;
  
  static const ValueType Base = 0 ;
  static const ValueType Lim = Base+DefaultEventElementCount ;
  static const EventMarker Marker = EventMarker_None ;
  
  static EventIdType Register(EventMetaInfo &info);  
 };

/* struct MultiSemEvent */

struct MultiSemEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint16 msem;
  uint8 type;
  uint8 index;
  
  enum Type : uint8
   {
    Give
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 msem_,Type type_,ulen index_)
   {
    time=time_;
    id=id_;
    
    msem=msem_;
    type=type_;
    index=(uint8)index_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<MultiSemEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<MultiSemEvent *>(ptr)->id); }
  
  static void * Offset_msem(void *ptr) { return &(static_cast<MultiSemEvent *>(ptr)->msem); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<MultiSemEvent *>(ptr)->type); }
  
  static void * Offset_index(void *ptr) { return &(static_cast<MultiSemEvent *>(ptr)->index); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* struct MultiSemEvent_task */

struct MultiSemEvent_task
 {
  EventTimeType time;
  EventIdType id;
  
  uint16 task;
  uint16 msem;
  uint8 type;
  uint8 index;
  
  enum Type : uint8
   {
    ToTask,
    Take,
    Block
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 task_,uint16 msem_,Type type_,ulen index_)
   {
    time=time_;
    id=id_;
  
    task=task_;
    msem=msem_;
    type=type_;
    index=(uint8)index_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<MultiSemEvent_task *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<MultiSemEvent_task *>(ptr)->id); }
  
  static void * Offset_task(void *ptr) { return &(static_cast<MultiSemEvent_task *>(ptr)->task); }
  
  static void * Offset_msem(void *ptr) { return &(static_cast<MultiSemEvent_task *>(ptr)->msem); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<MultiSemEvent_task *>(ptr)->type); }
  
  static void * Offset_index(void *ptr) { return &(static_cast<MultiSemEvent_task *>(ptr)->index); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class MultiSemBase */ 

class MultiSemBase : public Funchor_nocopy
 {
   TextLabel name;
   EventEnumValue<MultiSemNumber> msem_number;
   PtrLen<ulen> counts;
   ulen base;
   TaskList list;
   
  private:
  
   static AutoTextNameType ObjName;
   
   void event(TaskBase *task,MultiSemEvent_task::Type type,ulen index=0);
   
   void event(MultiSemEvent::Type type,ulen index);
    
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
   
   void init(PtrLen<ulen> counts); 
   
   void putIndex(ulen index);
   
   ulen nextIndex(ulen index) { return (index+1<counts.len)?index+1:0; }
   
   template <class T,class F>
   void give_locked(T cur,F Release,ulen index);
   
   ulen try_take_locked();

   ulen take_locked(MSec timeout);
   
  protected:
   
   explicit MultiSemBase(PtrLen<ulen> counts);
   
   MultiSemBase(TextLabel name,PtrLen<ulen> counts);
   
   ~MultiSemBase();
   
  public: 
   
   TextLabel getName() const { return name; }
   
   // give
  
   void give(ulen index); // [1,Len]
   
   void give_int(ulen index); // [1,Len]
   
   void give_any(ulen index); // [1,Len]
   
   // take
   
   ulen try_take(); // [0,Len]
   
   ulen take(); // [1,Len]
   
   ulen take(MSec timeout); // [0,Len]
   
   ulen take(TimeScope time_scope); // [0,Len]
   
   // give<Index>
   
   template <ulen Index> // [1,Len]
   void give_index() { give(Index); }
   
   template <ulen Index> // [1,Len]
   void give_index_int() { give_int(Index); }
   
   template <ulen Index> // [1,Len]
   void give_index_any() { give_any(Index); }
   
   // functions
   
   template <ulen Index>
   Function<void (void)> function_give() { return FunctionOf(this,&MultiSemBase::give_index<Index>); }
   
   template <ulen Index>
   Function<void (void)> function_give_int() { return FunctionOf(this,&MultiSemBase::give_index_int<Index>); }
   
   template <ulen Index>
   Function<void (void)> function_give_any() { return FunctionOf(this,&MultiSemBase::give_index_any<Index>); }
 };
 
/* class MultiSem<ulen Len> */ 

template <ulen Len> 
class MultiSem : public MultiSemBase
 {
   ulen counts[Len];
   
  public:
  
   MultiSem() : MultiSemBase(Range(counts)) {}
   
   explicit MultiSem(TextLabel name) : MultiSemBase(name,Range(counts)) {}
   
   ~MultiSem() {}
 };
 
} // namespace CCore
 
#endif
 

