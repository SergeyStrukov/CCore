/* EventRecorder.cpp */ 
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
 
#include <CCore/inc/EventRecorder.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {

/* class EventMetaInfo */

const char * GetTextDesc(EventMetaInfo::Kind kind)
 {
  static const char *const Table[]=
   {
    "uint8",
    "uint16",
    "uint32",
     
    "enum uint8",
    "enum uint16",
    "enum uint32",
     
    "struct"
   };
  
  return Table[kind];
 }

String * EventMetaInfo::EnumDesc::findValueName(uint32 value) const
 {
  if( auto *ptr=root.find(value) ) return &ptr->name;
   
  return 0; 
 }

auto EventMetaInfo::EnumDesc::addValueName(uint32 value,const String &name) -> EnumDesc &
 {
  uint32 max_value=MaxValue(kind);
  
  if( value>max_value ) 
    {
     Printf(Exception,"CCore::EventMetaInfo::EnumDesc::addValueName(#;,...) : out of bound, enum #;",value,name);
    }
  
  Algo::PrepareIns prepare(root,value,0,max_value);
  
  if( prepare.found )
    {
     Printf(Exception,"CCore::EventMetaInfo::EnumDesc::addValueName(#;,...) : duplication, enum #;",value,name);
    }
  else
    {
     prepare.complete(new ValueDesc(name));
     
     count++;
    }
  
  return *this;
 }

void EventMetaInfo::EnumDesc::Destroy(ValueDesc *ptr) 
 {
  if( ptr )
    {
     Destroy(Algo::Link(ptr).lo);
     Destroy(Algo::Link(ptr).hi);
     
     delete ptr;
    }
 }

EventIdType EventMetaInfo::IndexToId(ulen index)
 {
  if( index>(EventIdType)UIntMax() )
    {
     Printf(Exception,"CCore::EventMetaInfo::IndexToId(...) : too many types");
    }
   
  return EventIdType(index); 
 }

EventMetaInfo::EventMetaInfo(uint64 time_freq_)
 : time_freq(time_freq_)
 {
 }
   
EventMetaInfo::~EventMetaInfo()
 {
 }

auto EventMetaInfo::addEnum(Kind kind,const String &name) -> EnumDesc &
 {
  if( kind<Kind_enum_uint8 || kind>Kind_enum_uint32 )
    {
     Printf(Exception,"CCore::EventMetaInfo::addEnum(#;,...) : bad kind",kind);
    }
  
  EventIdType id=IndexToId(enum_list.getLen());
  
  return *enum_list.append_fill(id,name,kind);
 }

auto EventMetaInfo::addStruct(const String &name) -> StructDesc &
 {
  EventIdType id=IndexToId(struct_list.getLen());
  
  return *struct_list.append_fill(id,name);
 }

auto EventMetaInfo::addEvent(ulen alloc_len) -> EventDesc &
 {
  EventIdType id=IndexToId(event_list.getLen());
  
  return *event_list.append_fill(id,alloc_len);
 }

void EventMetaInfo::appendEnums()
 {
  for(auto &desc : enum_list ) desc.append();
 }

auto EventMetaInfo::getEnum(EventIdType id) const -> const EnumDesc &
 {
  if( id>=enum_list.getLen() )
    {
     Printf(Exception,"CCore::EventMetaInfo::getEnum(...) : bad enum id");
    }
  
  return enum_list[id];
 }

auto EventMetaInfo::getStruct(EventIdType id) const -> const StructDesc &
 {
  if( id>=struct_list.getLen() )
    {
     Printf(Exception,"CCore::EventMetaInfo::getStruct(...) : bad struct id");
    }
  
  return struct_list[id];
 }

auto EventMetaInfo::getEvent(EventIdType id) const -> const EventDesc &
 {
  if( id>=event_list.getLen() )
   {
    Printf(Exception,"CCore::EventMetaInfo::getEvent(...) : bad event id");
   }
  
  return event_list[id];
 }

/* struct EventIdNode */

static EventIdNode * List = 0 ;

EventIdNode::EventIdNode(RegisterFunc func_,ulen size_of_)
 {
  next=List;
  List=this;
  
  id=0;
  size_of=size_of_;
  func=func_; 
 }

void EventIdNode::Register(EventMetaInfo &info,ulen align)
 {
  for(EventIdNode *ptr=List; ptr ;ptr=ptr->next) ptr->reg(info,align); 
 }

/* struct EventControl */

void EventControl::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Type=info.addEnum_uint8("EventControlType")
                   .addValueName(Type_Start,"Start")
                   .addValueName(Type_Tick,"Tick")
                   .addValueName(Type_Stop,"Stop")
                   .addValueName(Type_End,"End")
                   .getId();
  
  auto id=info.addStruct("EventControl")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint8(id_Type,"type",Offset_type)
              .getId();
  
  desc.setStructId(info,id);
 }

} // namespace CCore
 

