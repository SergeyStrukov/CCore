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

#ifdef CCORE_TASK_EVENT_ENABLE

TaskEventHostType TaskEventHost;

#else

NoTaskEventHostType TaskEventHost;

#endif

/* struct TaskSwitchEvent */

void TaskSwitchEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Type=info.addEnum_uint16("TaskSwitchType")
                   .addValueName(EnterInt,"EnterInt")
                   .addValueName(LeaveInt,"LeaveInt")
                   .setAppendFunc(EventEnumValue<TaskNumber>::Append)
                   .getId();
  
  auto id=info.addStruct("TaskSwitch")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint16(id_Type,"type",Offset_type)
              .getId();
  
  desc.setStructId(info,id);
 }

} // namespace CCore
 

