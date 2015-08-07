/* TaskEvent.cpp */ 
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
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/task/TaskEvent.h>
 
namespace CCore {

/* global TaskEventHost */

TaskEventHostType TaskEventHost CCORE_INITPRI_0 ;

/* struct TaskNumber */

EventIdType TaskNumber::Register(EventMetaInfo &info)
 {
  return info.addEnum_uint16("TaskNumber")
             .addValueName(EnterInt,"EnterInt",EventMarker_Up)
             .addValueName(LeaveInt,"LeaveInt",EventMarker_Down)
             .setAppendFunc(EventEnumValue<TaskNumber>::Append)
             .getId();
 }

/* struct TaskSwitchEvent */

void TaskSwitchEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id=info.addStruct("TaskSwitch")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint16(EventTypeId<TaskNumber>::GetId(),"task",Offset_task)
              .getId();
  
  desc.setStructId(info,id);
 }

} // namespace CCore
 

