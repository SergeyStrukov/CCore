/* EventRecorder.h */ 
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

#ifndef CCore_inc_EventRecorder_h
#define CCore_inc_EventRecorder_h

#include <CCore/inc/Task.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/String.h>
#include <CCore/inc/FunctorType.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/SaveLoad.h>
#include <CCore/inc/TextLabel.h>

namespace CCore {

/* consts */

const ulen MaxEventLen = 256 ;

/* types */

typedef uint32 EventTimeType;

typedef uint16 EventIdType;

/* classes */

struct EventPrefix;

template <class T> class EventEnumValue;

class EventMetaInfo;

class EventIdNode;

template <class T> class EventId;

struct EventControl;

template <class Algo> class EventRecorder;

template <class Recorder,unsigned GuardCount=1000000> class EventRecorderHost;

/* struct EventPrefix */

struct EventPrefix // each event type must be layout-compatible with EventPrefix 
 {
  EventTimeType time;
  EventIdType id;
 };

/* class EventEnumValue<T> */

#if 0

struct Value
 {
  typedef uint16 ValueType;
  
  static const ValueType Base = 10 ;
  static const ValueType Lim = 100 ;
 };

#endif

template <class T>
class EventEnumValue
 {
   typedef typename T::ValueType ValueType;
  
   ValueType value;
   
  private:
   
   static Sys::Atomic Next;
   static Sys::Atomic Total;
   
   static InitStorage<(T::Lim-T::Base)*sizeof (TextLabel)> Storage;
   
   static ValueType Reserve(TextLabel name);
   
  public: 
   
   explicit EventEnumValue(TextLabel name) : value(Reserve(name)) {}
   
   operator ValueType() const { return value; }
   
   template <class Desc>
   static void Append(Desc &desc);
 };

template <class T>
Sys::Atomic EventEnumValue<T>::Next{T::Base};

template <class T>
Sys::Atomic EventEnumValue<T>::Total{0};

template <class T>
InitStorage<(T::Lim-T::Base)*sizeof (TextLabel)> EventEnumValue<T>::Storage;

template <class T>
auto EventEnumValue<T>::Reserve(TextLabel name) -> ValueType 
 {
  ValueType ret=Next++;
  
  if( ret<T::Lim ) 
    {
     new(Storage.getPlace()+(ret-T::Base)*sizeof (TextLabel)) TextLabel(name);
     
     Total++;
    
     return ret;
    }
  
  Next--;
  
  return T::Lim;
 }

template <class T>
template <class Desc>
void EventEnumValue<T>::Append(Desc &desc)
 {
  ValueType count=Total;
  
  for(ValueType val=0; val<count ;val++)
    {
     TextLabel *name=Storage.getPlace()+val*sizeof (TextLabel);
     
     desc.addValueName(val+T::Base,StringCat(*name));
    }
 }

/* class EventMetaInfo */

class EventMetaInfo : NoCopy
 {
  public:
  
   enum Kind
    {
     Kind_uint8,
     Kind_uint16,
     Kind_uint32,
     
     Kind_enum_uint8,
     Kind_enum_uint16,
     Kind_enum_uint32,
     
     Kind_struct
    };
   
   friend const char * GetTextDesc(Kind kind);
   
   static uint32 MaxValue(Kind kind)
    {
     switch( kind )
       {
        case Kind_enum_uint8 : return (uint8)UIntMax();
        
        case Kind_enum_uint16 : return (uint16)UIntMax();
        
        default: return (uint32)UIntMax();
       }
    }
   
   template <class Dev>
   static void Save(const String &name,Dev &dev)
    {
     dev.template use<BeOrder>((uint32)name.getLen());
     
     SaveRange_use<BeOrder>(Mutate<const uint8>(Range(name)),dev);
    }
   
   template <class Dev,class Array>
   static void SaveArray(const Array &array,Dev &dev)
    {
     dev.template use<BeOrder>((uint32)array.getLen());
     
     SaveRange_use<BeOrder>(Range(array),dev);
    }
   
   struct ValueDesc : MemBase_nocopy
    {
     TreeLink<ValueDesc,uint32> link;
     String name;
     
     // constructors
     
     explicit ValueDesc(const String &name_) : name(name_) {}
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"  #; = #;\n",name,link.key); 
      }
    };
   
   class EnumDesc : NoCopy
    {
      typedef void (*AppendFunc)(EnumDesc &desc);
     
      EventIdType id;
      String name;
      Kind kind;
      AppendFunc append_func;
      
      typedef TreeLink<ValueDesc,uint32>::RadixAlgo<&ValueDesc::link> Algo;
      
      Algo::Root root;
      ulen count;
      
     private:
      
      static void Destroy(ValueDesc *ptr);
      
      template <class Dev>
      static void SaveValues(ValueDesc *ptr,Dev &dev)
       {
        if( ptr )
          {
           SaveValues(Algo::Link(ptr).lo,dev);
          
           dev.template use<BeOrder>(Algo::Link(ptr).key);
           
           Save(ptr->name,dev);
          
           SaveValues(Algo::Link(ptr).hi,dev);
          }
       }
      
      template <class P>
      static void PrintValues(P &out,ValueDesc *ptr)
       {
        if( ptr )
          {
           PrintValues(out,Algo::Link(ptr).lo);
           
           ptr->print(out);
           
           PrintValues(out,Algo::Link(ptr).hi);
          }
       }
      
     public:
      
      // constructors
      
      EnumDesc(EventIdType id_,const String &name_,Kind kind_) : id(id_),name(name_),kind(kind_),append_func(0),count(0) {}
      
      ~EnumDesc() { Destroy(root.root); }
      
      // props
      
      EventIdType getId() const { return id; }
      
      const String & getName() const { return name; }
      
      Kind getKind() const { return kind; }
      
      String * findValueName(uint32 value) const;
      
      EnumDesc & addValueName(uint32 value,const String &name);
      EnumDesc & addValueName(uint32 value,const char *name) { return addValueName(value,String(name)); }
      
      EnumDesc & setAppendFunc(AppendFunc append_func_) { append_func=append_func_; return *this; }
      
      void append()
       {  
        if( append_func )
          {
           append_func(*this);
           
           append_func=0;
          }
       }
      
      // save/load object

      template <class Dev>
      void save(Dev &dev) const
       {
        dev.template use<BeOrder>((uint8)kind);
        
        Save(name,dev);
        
        dev.template use<BeOrder>((uint32)count);
        
        SaveValues(root.root,dev);
       }
      
      // swap/move objects
      
      void objSwap(EnumDesc &obj)
       {
        Swap(id,obj.id);
        Swap(name,obj.name);
        Swap(kind,obj.kind);
        Swap(append_func,obj.append_func);
        Swap(root,obj.root);
        Swap(count,obj.count);
       }
      
      explicit EnumDesc(ToMoveCtor<EnumDesc> obj)
       : id(obj->id),
         name(ObjToMove(obj->name)),
         kind(obj->kind),
         append_func(obj->append_func),
         root(Replace_null(obj->root)),
         count(obj->count)
       {
       }
      
      EnumDesc * objMove(Place<void> place)
       {
        return CtorMove(this,place);
       }
      
      // print object
      
      template <class P>
      void print(P &out) const
       {
        Printf(out,"#; #;\n {\n",kind,name);
        
        PrintValues(out,root.root);        
        
        Printf(out," }\n\n");
       }
      
      template <class P>
      void print(P &out,uint32 value) const
       {
        if( String *name=findValueName(value) )
          {
           Putobj(out,*name);
          }
        else
          {
           Putobj(out,value);
          }
       }
      
      // no-throw flags
      
      enum NoThrowFlagType
       {
        Default_no_throw = true,
        Copy_no_throw = true
       };
    };
   
   typedef void * (*OffsetFunc)(void *);
   
   class FieldDesc : NoCopy
    {
      Kind kind;
      EventIdType id;
      String name;
      OffsetFunc offset;
      
     public:
     
      // constructors
     
      FieldDesc(Kind kind_,EventIdType id_,const String &name_,OffsetFunc offset_) : kind(kind_),id(id_),name(name_),offset(offset_) {}
      
      ~FieldDesc() {}
      
      // save/load object

      template <class Dev>
      void save(Dev &dev) const
       {
        dev.template use<BeOrder>((uint8)kind,id);
        
        Save(name,dev);
       }
      
      template <class Dev>
      void save(Dev &dev,const EventMetaInfo &info,void *ptr) const
       {
        ptr=offset(ptr);
        
        switch( kind )
          {
           case Kind_uint8 : 
           case Kind_enum_uint8 : 
            {
             dev.template use<BeOrder>(*static_cast<uint8 *>(ptr));
            }
           break;
           
           case Kind_uint16 : 
           case Kind_enum_uint16 : 
            {
             dev.template use<BeOrder>(*static_cast<uint16 *>(ptr));
            }
           break;
           
           case Kind_uint32 : 
           case Kind_enum_uint32 : 
            {
             dev.template use<BeOrder>(*static_cast<uint32 *>(ptr));
            } 
           break;
           
           case Kind_struct : 
            {
             info.getStruct(id).save(dev,info,ptr);
            }
           break;
          }
       }
      
      uint32 saveLen(const EventMetaInfo &info) const
       {
        switch( kind )
          {
           case Kind_uint8 : 
           case Kind_enum_uint8 : 
            {
             uint8 temp;
             
             return (uint32)SaveLen(temp).value;
            }
           break;
           
           case Kind_uint16 : 
           case Kind_enum_uint16 : 
            {
             uint16 temp;
             
             return (uint32)SaveLen(temp).value;
            }
           break;
           
           case Kind_uint32 : 
           case Kind_enum_uint32 : 
            {
             uint32 temp;
             
             return (uint32)SaveLen(temp).value;
            } 
           break;
           
           case Kind_struct : 
            {
             return info.getStruct(id).saveLen(info);
            }
           break;
          }
        
        return 0;
       }
      
      // swap/move objects
      
      void objSwap(FieldDesc &obj)
       {
        Swap(kind,obj.kind);
        Swap(id,obj.id);
        Swap(name,obj.name);
        Swap(offset,obj.offset);
       }
      
      explicit FieldDesc(ToMoveCtor<FieldDesc> obj)
       : kind(obj->kind),
         id(obj->id),
         name(ObjToMove(obj->name)),
         offset(obj->offset)
       {
       }
      
      FieldDesc * objMove(Place<void> place)
       {
        return CtorMove(this,place);
       }
      
      // print object
      
      template <class P>
      void print(P &out,const EventMetaInfo &info) const
       {
        switch( kind )
          {
           case Kind_uint8 : Printf(out,"  uint8"); break;
           case Kind_uint16 : Printf(out,"  uint16"); break;
           case Kind_uint32 : Printf(out,"  uint32"); break;
           
           case Kind_enum_uint8 : Printf(out,"  enum uint8 #;",info.getEnum(id).getName()); break;
           case Kind_enum_uint16 : Printf(out,"  enum uint16 #;",info.getEnum(id).getName()); break;
           case Kind_enum_uint32 : Printf(out,"  enum uint32 #;",info.getEnum(id).getName()); break;
           
           case Kind_struct : Printf(out,"  struct #;",info.getStruct(id).getName()); break;
          }
        
        Printf(out," #;;\n",name);
       }
      
      template <class P>
      void print(P &out,const EventMetaInfo &info,void *ptr,ulen off) const
       {
        ptr=offset(ptr);
        
        out.put(' ',off);
        
        switch( kind )
          {
           case Kind_uint8 : 
            {
             Printf(out,"  uint8 #; = #; ;\n",name,*static_cast<uint8 *>(ptr));
            }
           break;
           
           case Kind_uint16 : 
            {
             Printf(out,"  uint16 #; = #; ;\n",name,*static_cast<uint16 *>(ptr));
            }
           break;
           
           case Kind_uint32 : 
            {
             Printf(out,"  uint32 #; = #; ;\n",name,*static_cast<uint32 *>(ptr));
            } 
           break;
           
           case Kind_enum_uint8 : 
            {
             Printf(out,"  enum uint8 #; = ",name);
             
             info.getEnum(id).print(out,*static_cast<uint8 *>(ptr));
             
             Printf(out," ;\n");
            }
           break;
           
           case Kind_enum_uint16 : 
            {
             Printf(out,"  enum uint16 #; = ",name);
             
             info.getEnum(id).print(out,*static_cast<uint16 *>(ptr));
             
             Printf(out," ;\n");
            }
           break;
           
           case Kind_enum_uint32 : 
            {
             Printf(out,"  enum uint32 #; = ",name);
             
             info.getEnum(id).print(out,*static_cast<uint32 *>(ptr));
             
             Printf(out," ;\n");
            }
           break;
           
           case Kind_struct : 
            {
             auto &desc=info.getStruct(id);
             
             Printf(out,"  struct #; #; =\n",desc.getName(),name);
             
             out.put(' ',off);
             
             Printf(out,"   {\n");
             
             desc.print(out,info,ptr,off+2);
             
             out.put(' ',off);
             
             Printf(out,"   };\n");
            }
           break;
          }
       }
      
      // no-throw flags
      
      enum NoThrowFlagType
       {
        Default_no_throw = true,
        Copy_no_throw = true
       };
    };
   
   class StructDesc : NoCopy
    {
      EventIdType id;
      String name;
      DynArray<FieldDesc> field_list;
      
     public: 
      
      // constructors
      
      StructDesc(EventIdType id_,const String &name_) : id(id_),name(name_) {}
      
      ~StructDesc() {}
      
      // props
      
      EventIdType getId() const { return id; }
      
      const String & getName() const { return name; }
      
      PtrLen<const FieldDesc> getFieldList() const { return Range(field_list); }
      
      StructDesc & addField(Kind kind,EventIdType id,const String &name,OffsetFunc offset) { field_list.append_fill(kind,id,name,offset); return *this; }
      StructDesc & addField(Kind kind,EventIdType id,const char *name,OffsetFunc offset) { field_list.append_fill(kind,id,String(name),offset); return *this; }
      
      StructDesc & addField_uint8(const String &name,OffsetFunc offset) { return addField(Kind_uint8,0,name,offset); }
      StructDesc & addField_uint16(const String &name,OffsetFunc offset) { return addField(Kind_uint16,0,name,offset); }
      StructDesc & addField_uint32(const String &name,OffsetFunc offset) { return addField(Kind_uint32,0,name,offset); }

      StructDesc & addField_enum_uint8(EventIdType id,const String &name,OffsetFunc offset) { return addField(Kind_enum_uint8,id,name,offset); }
      StructDesc & addField_enum_uint16(EventIdType id,const String &name,OffsetFunc offset) { return addField(Kind_enum_uint16,id,name,offset); }
      StructDesc & addField_enum_uint32(EventIdType id,const String &name,OffsetFunc offset) { return addField(Kind_enum_uint32,id,name,offset); }
      
      StructDesc & addField_struct(EventIdType id,const String &name,OffsetFunc offset) { return addField(Kind_struct,id,name,offset); }
      
      StructDesc & addField_uint8(const char *name,OffsetFunc offset) { return addField(Kind_uint8,0,name,offset); }
      StructDesc & addField_uint16(const char *name,OffsetFunc offset) { return addField(Kind_uint16,0,name,offset); }
      StructDesc & addField_uint32(const char *name,OffsetFunc offset) { return addField(Kind_uint32,0,name,offset); }

      StructDesc & addField_enum_uint8(EventIdType id,const char *name,OffsetFunc offset) { return addField(Kind_enum_uint8,id,name,offset); }
      StructDesc & addField_enum_uint16(EventIdType id,const char *name,OffsetFunc offset) { return addField(Kind_enum_uint16,id,name,offset); }
      StructDesc & addField_enum_uint32(EventIdType id,const char *name,OffsetFunc offset) { return addField(Kind_enum_uint32,id,name,offset); }
      
      StructDesc & addField_struct(EventIdType id,const char *name,OffsetFunc offset) { return addField(Kind_struct,id,name,offset); }
      
      // save/load object

      template <class Dev>
      void save(Dev &dev) const
       {
        Save(name,dev);
        SaveArray(field_list,dev);
       }
      
      template <class Dev>
      void save(Dev &dev,const EventMetaInfo &info,void *ptr) const
       {
        for(const auto &desc : field_list ) desc.save(dev,info,ptr);
       }
      
      uint32 saveLen(const EventMetaInfo &info) const
       {
        uint32 ret=0;
        
        for(const auto &desc : field_list ) ret+=desc.saveLen(info);
        
        return ret;
       }
      
      // swap/move objects
      
      void objSwap(StructDesc &obj)
       {
        Swap(id,obj.id);
        Swap(name,obj.name);
        Swap(field_list,obj.field_list);
       }
      
      explicit StructDesc(ToMoveCtor<StructDesc> obj)
       : id(obj->id),
         name(ObjToMove(obj->name)),
         field_list(ObjToMove(obj->field_list))
       {
       }
      
      StructDesc * objMove(Place<void> place)
       {
        return CtorMove(this,place);
       }
      
      // print object
      
      template <class P>
      void print(P &out,const EventMetaInfo &info) const
       {
        Printf(out,"struct #;\n {\n",name);
        
        for(const auto &desc : field_list ) desc.print(out,info); 
        
        Printf(out," }\n\n");
       }
      
      template <class P>
      void print(P &out,const EventMetaInfo &info,void *ptr,ulen off=0) const
       {
        if( !off ) Printf(out,"event #;\n {\n",name);
        
        for(const auto &desc : field_list ) desc.print(out,info,ptr,off); 
        
        if( !off ) Printf(out," }\n\n");
       }
      
      // no-throw flags
      
      enum NoThrowFlagType
       {
        Default_no_throw = true,
        Copy_no_throw = true
       };
    };
  
   class EventDesc : NoCopy
    {
      EventIdType id;
      ulen alloc_len;
      EventIdType struct_id;
      uint32 save_len;
      
     public: 
      
      // constructors
      
      EventDesc(EventIdType id_,ulen alloc_len_) : id(id_),alloc_len(alloc_len_),struct_id(0),save_len(0) {}
      
      ~EventDesc() {}
      
      // props
      
      EventIdType getId() const { return id; }
      
      ulen getAllocLen() const { return alloc_len; }
      
      EventIdType getStructId() const { return struct_id; }
      
      void setStructId(const EventMetaInfo &info,EventIdType struct_id_) 
       {
        save_len=info.getStruct(struct_id_).saveLen(info);
        struct_id=struct_id_; 
       }
      
      // save/load object

      template <class Dev>
      void save(Dev &dev) const
       {
        dev.template use<BeOrder>(struct_id,save_len);
       }
      
      template <class Dev>
      void save(Dev &dev,const EventMetaInfo &info,void *ptr) const
       {
        info.getStruct(struct_id).save(dev,info,ptr);
       }
      
      // swap/move objects
      
      void objSwap(EventDesc &obj)
       {
        Swap(id,obj.id);
        Swap(alloc_len,obj.alloc_len);
        Swap(struct_id,obj.struct_id);
        Swap(save_len,obj.save_len);
       }
      
      explicit EventDesc(ToMoveCtor<EventDesc> obj)
       : id(obj->id),
         alloc_len(obj->alloc_len),
         struct_id(obj->struct_id),
         save_len(obj->save_len)
       {
       }
      
      EventDesc * objMove(Place<void> place)
       {
        return CtorMove(this,place);
       }
      
      // no-throw flags
      
      enum NoThrowFlagType
       {
        Default_no_throw = true,
        Copy_no_throw = true
       };
    };
   
  private:
  
   uint64 time_freq;
   
   DynArray<EnumDesc> enum_list;
   DynArray<StructDesc> struct_list;
   DynArray<EventDesc> event_list;
   
  private:
   
   static EventIdType IndexToId(ulen index);
   
  public: 
  
   explicit EventMetaInfo(uint64 time_freq);
   
   ~EventMetaInfo();
   
   // add type
   
   EnumDesc & addEnum(Kind kind,const String &name);
   EnumDesc & addEnum(Kind kind,const char *name) { return addEnum(kind,String(name)); }
   
   EnumDesc & addEnum_uint8(const String &name) { return addEnum(Kind_enum_uint8,name); }
   EnumDesc & addEnum_uint16(const String &name) { return addEnum(Kind_enum_uint16,name); }
   EnumDesc & addEnum_uint32(const String &name) { return addEnum(Kind_enum_uint32,name); }
   
   EnumDesc & addEnum_uint8(const char *name) { return addEnum(Kind_enum_uint8,String(name)); }
   EnumDesc & addEnum_uint16(const char *name) { return addEnum(Kind_enum_uint16,String(name)); }
   EnumDesc & addEnum_uint32(const char *name) { return addEnum(Kind_enum_uint32,String(name)); }
   
   StructDesc & addStruct(const String &name);
   StructDesc & addStruct(const char *name) { return addStruct(String(name)); }
   
   EventDesc & addEvent(ulen alloc_len);
   
   void appendEnums();
   
   // meta info
   
   const EnumDesc & getEnum(EventIdType id) const;
   
   const StructDesc & getStruct(EventIdType id) const;
   
   const EventDesc & getEvent(EventIdType id) const;
   
   // save/load object

   template <class Dev>
   void save(Dev &dev) const
    {
     dev.template use<BeOrder>(time_freq);
     
     SaveArray(enum_list,dev);
     SaveArray(struct_list,dev);
     SaveArray(event_list,dev);
    }
   
   template <class Dev>
   void saveEvent(Dev &dev,const EventDesc &desc,void *ptr) const
    {
     desc.save(dev,*this,ptr);
    }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"#;\n\nfreq = #;\n\n",Title("Event record"),time_freq);
     
     for(const auto &desc : enum_list ) 
       {
        Putobj(out,desc);
       }
     
     for(const auto &desc : struct_list ) 
       {
        desc.print(out,*this);
       }
     
     for(const auto &desc : event_list )
       {
        Printf(out,"event #;\n\n",getStruct(desc.getStructId()).getName());
       }
     
     Printf(out,"#;\n\n",TextDivider());
    }
   
   template <class P>
   void printEvent(P &out,const EventDesc &desc,void *ptr) const
    {
     getStruct(desc.getStructId()).print(out,*this,ptr);
    }
 };

/* class EventIdNode */

class EventIdNode
 {
  public:
  
   typedef void (*RegisterFunc)(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
   
  private: 
  
   EventIdNode *next;  
   EventIdType id;
   ulen size_of;
   RegisterFunc func;
   
  private:
   
   void reg(EventMetaInfo &info,ulen align) 
    {
     auto &desc=info.addEvent(Align(size_of,align));
    
     id=desc.getId();
     
     func(info,desc);
    }
   
  public: 
  
   EventIdNode(RegisterFunc func,ulen size_of);
   
   EventIdType getId() const { return id; }
   
   static void Register(EventMetaInfo &info,ulen align);
 };

/* class EventId<T> */

template <class T> 
class EventId
 {
   static EventIdNode Node;
  
  public:
  
   static EventIdType GetId() { return Node.getId(); }
 };

template <class T> 
EventIdNode EventId<T>::Node(T::Register,sizeof (T));

/* struct EventControl */

struct EventControl
 {
  EventTimeType time;
  EventIdType id;
  uint8 type;
  
  enum Type
   {
    Type_Start,
    Type_Tick,
    Type_Stop,
    Type_End
   };
  
  void init(EventTimeType time_,EventIdType id_,Type type_)
   {
    time=time_;
    id=id_;
    
    type=type_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<EventControl *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<EventControl *>(ptr)->id); }
  
  static void * Offset_type(void *ptr) { return &(static_cast<EventControl *>(ptr)->type); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class EventRecorder<Algo> */

#if 0

struct EventRecorderAlgo
 {
  static const ulen RecordAlign = 4 ;
  
  static const uint64 TimeFreq = ??? ;
  
  static EventTimeType GetTime() { ??? }
 };

#endif

template <class Algo>
class EventRecorder : public EventMetaInfo
 {
   void *buf;
   ulen buf_len;
   
   Atomic pos;
   
  public: 
   
   static const ulen RecordAlign = Algo::RecordAlign ;
   
   explicit EventRecorder(ulen buf_len_)
    : EventMetaInfo(Algo::TimeFreq)
    {
     Replace_max(buf_len_,MaxEventLen);
     
     buf=MemAlloc(buf_len_);
     buf_len=buf_len_;
     
     pos=0;
    }
   
   ~EventRecorder()
    {
     MemFree(buf); 
    }
   
   template <class T,class ... SS>
   void add(SS && ... ss)
    {
     static_assert( std::is_pod<T>::value ,"CCore::EventRecorder<Algo>::add(...) : T must be POD");
     
     const ulen len=Align(sizeof (T),RecordAlign);
     
     static_assert( len<=MaxEventLen ,"CCore::EventRecorder<Algo>::add(...) : T is too large");
     
     ulen off=(pos+=len);
     
     if( off>buf_len-len )
       {
        pos-=len;
       }
     else
       {
        static_cast<T *>(PtrAdd(buf,off))->init( Algo::GetTime() , EventId<T>::GetId() , std::forward<SS>(ss)... );
       }
    }
   
   template <class FuncInit>
   void parse(FuncInit func_init) const
    {
     ulen off=0;
     ulen lim=pos;
     
     FunctorTypeOf<FuncInit> func(func_init);
     
     while( off<lim )
       {
        void *ptr=PtrAdd(buf,off);
        EventPrefix *prefix=static_cast<EventPrefix *>(ptr);
       
        auto &desc=getEvent(prefix->id);
        
        func(*this,desc,ptr);
        
        off+=desc.getAllocLen();
       }
    }
   
   // save/load object

   template <class Dev>
   void save(Dev &dev) const
    {
     EventMetaInfo::save(dev);
     
     parse( [&] (const EventMetaInfo &info,const EventDesc &desc,void *ptr) { info.saveEvent(dev,desc,ptr); } );
     
     EventControl end;
     
     end.init(0,EventId<EventControl>::GetId(),EventControl::Type_End);
     
     saveEvent(dev,getEvent(end.id),&end);
    }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     EventMetaInfo::print(out);
     
     parse( [&] (const EventMetaInfo &info,const EventDesc &desc,void *ptr) { info.printEvent(out,desc,ptr); } );
     
     Printf(out,"#;\n\n",TextDivider());
    }
 };

/* class EventRecorderHost<Recorder,unsigned GuardCount> */

template <class Recorder,unsigned GuardCount> 
class EventRecorderHost : NoCopy
 {
   Recorder *obj;
   Atomic count;
   
  private: 
   
   Recorder * lock() 
    {
     if( (count++)<GuardCount )
       {
        count--; 
     
        return 0; 
       }
     else
       {
        return obj;
       }
    }
   
   void unlock() 
    { 
     count--; 
    }
   
   void start(Recorder *obj_)
    {
     obj=obj_;
     
     obj_->template add<EventControl>(EventControl::Type_Start);
     
     count+=GuardCount;
    }
   
   void stop()
    {
     count-=GuardCount;
     
     Recorder *temp=Replace_null(obj);
     
     while( count ) Task::Yield();
     
     temp->template add<EventControl>(EventControl::Type_Stop);
     
     temp->appendEnums();
    }
   
  public:
   
   EventRecorderHost()
    {
     obj=0;
     count=0;
    }
   
   class StartStop : NoCopy
    {
      EventRecorderHost &host;
      
     public: 
      
      StartStop(EventRecorderHost &host_,Recorder *obj) 
       : host(host_) 
       {
        EventIdNode::Register(*obj,Recorder::RecordAlign);
       
        host_.start(obj); 
       } 
      
      ~StartStop() 
       { 
        host.stop(); 
       }
    };
   
   template <class T,class ... SS>
   void add(SS && ... ss)
    {
     if( Recorder *obj=lock() )
       {
        obj->template add<T>( std::forward<SS>(ss)... );
       
        unlock();
       }
    }
   
   void tick()
    {
     add<EventControl>(EventControl::Type_Tick);
    }
 };

} // namespace CCore
 
#endif
 

