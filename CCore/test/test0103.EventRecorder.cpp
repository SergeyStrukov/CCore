/* test0103.EventRecorder.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>

#include <CCore/inc/EventRecorder.h>
#include <CCore/inc/Task.h>

namespace App {

namespace Private_0103 {

/* struct EventRecorderAlgo */

struct EventRecorderAlgo
 {
  static const ulen RecordAlign = 4 ;
  
  static const uint64 TimeFreq = 0 ;
  
  class AllocPos : FastMutexBase
   {
     ulen off;
     
    public:
    
     AllocPos() : off(0) {}
     
     ~AllocPos() {}
     
     operator ulen() const { return off; }
     
     EventRecordPos alloc(ulen len)
      {
       Lock lock(*this);
       
       EventRecordPos ret;
       
       ret.pos=off;
       ret.time=(EventTimeType)Sys::GetClockTime();
       
       off+=len;
       
       return ret;
      }
     
     void back(ulen len)
      {
       Lock lock(*this);
       
       off-=len;
      }
   };
 };

/* struct EventBody */

struct EventBody
 {
  uint8 task;
  uint32 number;
  
  static void * Offset_task(void *ptr) { return &(static_cast<EventBody *>(ptr)->task); }
  
  static void * Offset_number(void *ptr) { return &(static_cast<EventBody *>(ptr)->number); }
  
  static EventIdType Register(EventMetaInfo &info)
   {
    auto id=info.addEnum_uint8("TaskId")
                .addValueName(1,"Task1")
                .addValueName(2,"Task2")
                .addValueName(3,"Task3")
                .addValueName(4,"Task4")
                .addValueName(5,"Task5")
                .addValueName(6,"Task6")
                .addValueName(7,"Task7")
                .addValueName(8,"Task8")
                .getId();
    
    return info.addStruct("EventBody")
               .addField_enum_uint8(id,"task",Offset_task)
               .addField_uint32("number",Offset_number)
               .getId();
   }
 };

/* struct Event */

struct Event
 {
  EventTimeType time;
  EventIdType id;
  EventBody body;

  void init(EventTimeType time_,EventIdType id_,uint8 task_,uint32 number_)
   {
    time=time_;
    id=id_;
    
    body.task=task_;
    body.number=number_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<Event *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<Event *>(ptr)->id); }
  
  static void * Offset_body(void *ptr) { return &(static_cast<Event *>(ptr)->body); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
   {
    auto id_body=EventBody::Register(info);
    
    auto id=info.addStruct("Event")
                .addField_uint32("time",Offset_time)
                .addField_uint16("id",Offset_id)
                .addField_struct(id_body,"body",Offset_body)
                .getId();
    
    desc.setStructId(info,id);
   }
 };

/* EventRecorderHost */

typedef EventRecorderHost<EventRecorder<EventRecorderAlgo> > EventHostType;

EventHostType EventHost;

} // namespace Private_0103
 
using namespace Private_0103; 
 
/* Testit<103> */ 

template<>
const char *const Testit<103>::Name="Test103 EventRecorder";

template<>
bool Testit<103>::Main() 
 {
  EventRecorder<EventRecorderAlgo> recorder(25_MByte);
  
  {
   RunTasks run;
  
   run( [&] () 
            {
             EventHostType::StartStop start_stop(EventHost,&recorder);
    
             for(uint32 number=1; number<=100000 ;number++) EventHost.add<Event>(9,number);
  
            } );
   
   for(uint8 task=1; task<=8 ;task++) 
     run( [=] () 
              {
               for(uint32 number=1; number<=100000 ;number++) EventHost.add<Event>(task,number);
    
              } );
   
  } 
  
  PrintFile out("test103.txt");
  
  Putobj(out,recorder);
  
  StreamFile dev("test103.bin");
  
  dev(recorder);
  
  return true;
 }
 
} // namespace App
 
