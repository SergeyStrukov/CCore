/* Mutex.h */ 
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

#ifndef CCore_inc_task_Mutex_h
#define CCore_inc_task_Mutex_h

#include <CCore/inc/task/TaskList.h>
 
namespace CCore {

/* classes */

struct MutexNumber;

struct MutexEvent;

class Mutex;

/* struct MutexNumber */

struct MutexNumber
 {
  typedef uint16 ValueType;
  
  static const ValueType Base = 0 ;
  static const ValueType Lim = Base+DefaultEventElementCount ;
  static const EventMarker Marker = EventMarker_None ;
  
  static EventIdType Register(EventMetaInfo &info);  
 };

/* struct MutexEvent */

struct MutexEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint16 task;
  uint16 mutex;
  uint8 type;
  
  enum Type : uint8
   {
    Lock,
    Unlock,
    IncLock,
    DecLock,
    Block
   };
  
  void init(EventTimeType time_,EventIdType id_,uint16 task_,uint16 mutex_,Type type_)
   {
    time=time_;
    id=id_;
    
    task=task_;
    mutex=mutex_;
    type=type_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<MutexEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<MutexEvent *>(ptr)->id); }
  
  static void * Offset_task(void *ptr) { return &(static_cast<MutexEvent *>(ptr)->task); }
  
  static void * Offset_mutex(void *ptr) { return &(static_cast<MutexEvent *>(ptr)->mutex); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<MutexEvent *>(ptr)->type); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class Mutex */ 

class Mutex : NoCopy
 {
   TextLabel name;
   EventEnumValue<MutexNumber> mutex_number;
   unsigned count;
   TaskList list;
   
  private:
  
   static AutoTextNameType ObjName;
   
   void event(TaskBase *task,MutexEvent::Type type);
    
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
    
   void init(); 
   
  public: 
  
   Mutex();
   
   explicit Mutex(TextLabel name);
   
   ~Mutex();
   
   TextLabel getName() const { return name; }
   
   void lock();
  
   void unlock();
  
   typedef LockObject<Mutex> Lock;
 };
 
} // namespace CCore
 
#endif
 

