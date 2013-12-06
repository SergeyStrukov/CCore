/* DDL2TypedMap.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.07
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ddl2_DDL2TypedMap_h
#define CCore_inc_ddl2_DDL2TypedMap_h
 
#include <CCore/inc/ddl2/DDL2Engine.h>
#include <CCore/inc/ddl2/DDL2MapTools.h>

namespace CCore {
namespace DDL2 {

/* functions */

void GuardBadStructure();

void GuardMapNoConst(StrLen name);

void GuardMapBadConstType(StrLen name);

/* classes */

struct MapSizeInfo;

template <class T,class TypeSet> struct MapTypeFunc;

template <class T> struct MapTypeCheck;

template <class TypeSet> class TypedMap;

/* struct MapSizeInfo */

struct MapSizeInfo
 {
  ulen size_of;
  ulen align_of;
  
  MapSizeInfo() : size_of(0),align_of(0) {}

  template <class T>
  void set()
   {
    size_of=sizeof (T);
    align_of=alignof (T);
   }
 };

/* struct MapTypeCheck<T> */

template <class T> 
struct MapTypeCheck
 {
  template <class TypeSet>
  static bool Match(const TypeSet &type_set,TypeNode *type)
   {
    bool ret=false;
    
    TypeAdapter(type).ptr.apply(MapTypeFunc<T,TypeSet>(ret,type_set));
    
    return ret;
   }
 };

template <class TypeSet>
struct MapTypeFunc<sint8,TypeSet>
 {
  bool &ret;
  
  MapTypeFunc(bool &ret_,const TypeSet &) : ret(ret_) {}
  
  template <class S>
  void operator () (S *) {}
  
  void operator () (TypeNode::Base *type_ptr)
   {
    ret = ( type_ptr->type==TypeNode::Base::Type_sint8 ) ;
   }
 };

template <class T,class TypeSet>
struct MapTypeFunc<T *,TypeSet>
 {
  bool &ret;
  const TypeSet &type_set;
  
  MapTypeFunc(bool &ret_,const TypeSet &type_set_) : ret(ret_),type_set(type_set_) {}
  
  template <class S>
  void operator () (S *) {}
  
  void operator () (TypeNode::Ptr *type_ptr)
   {
    ret=MapTypeCheck<T>::Match(type_set,type_ptr->type_node);
   }
 };

template <class T,class TypeSet>
struct MapTypeFunc<PtrLen<T>,TypeSet>
 {
  bool &ret;
  const TypeSet &type_set;
  
  MapTypeFunc(bool &ret_,const TypeSet &type_set_) : ret(ret_),type_set(type_set_) {}
  
  template <class S>
  void operator () (S *) {}
  
  void operator () (TypeNode::Array *type_ptr)
   {
    ret=MapTypeCheck<T>::Match(type_set,type_ptr->type_node);
   }
  
  void operator () (TypeNode::ArrayLen *type_ptr)
   {
    ret=MapTypeCheck<T>::Match(type_set,type_ptr->type_node);
   }
 };

/* class TypedMap<TypeSet> */

//
// class TypeSet : NoCopy
//  {
//   public:
//
//    explicit TypeSet(ulen struct_count);
//
//    MapSizeInfo structSizeInfo(StructNode *struct_node);
//
//    void guardFieldTypes(StructNode *struct_node);
//
//    static MapSizeInfo PointerSizeInfo(TypeNode *type);
//
//    static MapSizeInfo PointerSizeInfo(TypeList *type_list);
//
//    static MapSizeInfo ArraySizeInfo(TypeNode *type);
//
//    static void CreateArray(Place<void> place,TypeNode *type);
//
//    static void CreateArray(Place<void> place,TypeNode *type,Place<void> ptr,ulen len);
//
//    static void CreatePtr(Place<void> place,TypeNode *type);
//
//    static void CreatePtr(Place<void> place,TypeNode *type,Place<void> ptr);
//
//    static void CreatePtr(Place<void> place,TypeList *type_list);
//
//    static void CreatePtr(Place<void> place,TypeList *type_list,TypeNode *type);
//
//    static void CreatePtr(Place<void> place,TypeList *type_list,TypeNode *type,Place<void> ptr);
//  };
//

template <class TypeSet>
class TypedMap : NoCopy
 {
   static const ulen MaxLevel = 100 ;
  
   struct RecValue : NoThrowFlagsBase
    {
     ulen off;
     
     PtrLen<RecValue> elems;
     
     RecValue() : off(0) {}
    };
  
   struct RecConst : RecValue
    {
     TypeNode *type;
     MapSizeInfo size_info;
     
     RBTreeLink<RecConst,NameKey> link;
     
     RecConst() : type(0) {}
     
     void set(TypeNode *type_,MapSizeInfo size_info_)
      {
       type=type_;
       size_info=size_info_;
      }
    };
   
   struct RecStruct : NoThrowFlagsBase
    {
     MapSizeInfo size_info;
     bool done;
     
     RecStruct() : done(false) {}
     
     MapSizeInfo get(TypeSet &type_set,StructNode *struct_node)
      {
       if( !done )
         {
          size_info=type_set.structSizeInfo(struct_node);
          
          done=true;
         }
       
       return size_info;
      }
    };
   
  private: 
   
   EvalResult *eval;
   BodyNode *body;
   
   DynArray<RecConst> const_buf;
   Collector<RecValue> rec_buf;
   DynArray<RecStruct> struct_buf;
   
   typedef typename RBTreeLink<RecConst,NameKey>::template Algo<&RecConst::link> ConstAlgo; 
   
   typename ConstAlgo::Root const_map;
   
   ulen total;
   Place<void> base;
   unsigned level;
   
   TypeSet type_set;
   
  private:
   
   void resetLevel() { level=0; }
   
   void incLevel() { if( level>=MaxLevel ) GuardMapTooDeep(); level++; }
   
   void decLevel() { level--; }
   
  private: 
   
   struct PrepareFunc;
   
   void prepare(TypeNode *type,const Value &value,RecValue &rec);
   
   void prepare();
   
  private:
   
   MapSizeInfo sizeInfo(StructNode *struct_node)
    {
     ulen ind=struct_node->index;
     
     return struct_buf[ind].get(type_set,struct_node);
    }
   
   struct SizeInfoFunc;
   
   MapSizeInfo sizeInfo(TypeNode *type);
   
   void sizeInfo();
   
  private: 
   
   ulen reserve(MapSizeInfo size_info);
   
   ulen reserve(MapSizeInfo size_info,ulen count);
   
   void reserve(RecConst &rec) { rec.off=reserve(rec.size_info); }
   
   struct PlaceFunc;
   
   void place(TypeNode *type,const Value &value,const RecValue &rec);
   
   void place();

  private: 
   
   const RecValue & getRec(PtrNode *node);
   
   struct MapFunc;
   
   void map(TypeNode *type,const Value &value,const RecValue &rec);
   
  public:
   
   explicit TypedMap(EngineResult result);
   
   ~TypedMap();
   
   ulen getLen() const { return total; }
   
   void operator () (void *mem);
   
   template <class T>
   T * findConst(StrLen name);
   
   template <class T>
   T takeConst(StrLen name);
 };

template <class TypeSet>
struct TypedMap<TypeSet>::PrepareFunc
 {
  TypedMap<TypeSet> *map;
  Value value;
  RecValue &rec;
  
  PrepareFunc(TypedMap<TypeSet> *map_,const Value &value_,RecValue &rec_) : map(map_),value(value_),rec(rec_) {}
  
  void operator () (TypeNode::Base *type_ptr)
   {
    if( type_ptr->isText() )
      {
       RecValue *obj=map->rec_buf.append_default();
      
       rec.elems=Range(obj,1);
      }
   }
  
  void operator () (TypeNode::Ptr *) {}
  
  void operator () (TypeNode::PolyPtr *) {}
  
  void array(TypeNode *type)
   {
    PtrLen<Value> data=value.get<Block>().data;
    
    PtrLen<RecValue> elems=map->rec_buf.extend_default(data.len);
    
    rec.elems=elems;
    
    for(; +data ;++data,++elems) map->prepare(type,*data,*elems);
   }
  
  void operator () (TypeNode::Array *type_ptr)
   {
    array(type_ptr->type_node);
   }
  
  void operator () (TypeNode::ArrayLen *type_ptr)
   {
    array(type_ptr->type_node);
   }
  
  void operator () (StructNode *struct_node)
   {
    PtrLen<Value> data=value.get<Block>().data;
    
    PtrLen<RecValue> elems=map->rec_buf.extend_default(data.len);
    
    rec.elems=elems;
    
    auto cur=begin(struct_node->field_list);
    
    for(; +data ;++data,++elems,++cur) map->prepare((*cur).type_node,*data,*elems);
   }
 };

template <class TypeSet>
void TypedMap<TypeSet>::prepare(TypeNode *type,const Value &value,RecValue &rec)
 {
  incLevel();
  
  TypeAdapter(type).ptr.apply(PrepareFunc(this,value,rec));

  decLevel();
 }

template <class TypeSet>
void TypedMap<TypeSet>::prepare()
 {
  for(ulen i=0,n=const_buf.getLen(); i<n ;i++)
    {
     auto &result=eval->const_table[i];
     
     resetLevel();
     
     prepare(result.type,result.value,const_buf[i]);
    }
 }

template <class TypeSet>
struct TypedMap<TypeSet>::SizeInfoFunc
 {
  TypedMap<TypeSet> *map;
  MapSizeInfo &ret;
  
  SizeInfoFunc(TypedMap<TypeSet> *map_,MapSizeInfo &ret_) : map(map_),ret(ret_) {}
  
  void operator () (TypeNode::Base *type_ptr)
   {
    switch( type_ptr->type )
      {
       case TypeNode::Base::Type_sint   : ret.set<sint_type>(); break; 
       case TypeNode::Base::Type_uint   : ret.set<uint_type>(); break; 
       case TypeNode::Base::Type_ulen   : ret.set<ulen_type>(); break;
       
       case TypeNode::Base::Type_sint8  : ret.set<sint8>(); break; 
       case TypeNode::Base::Type_uint8  : ret.set<uint8>(); break; 
       case TypeNode::Base::Type_sint16 : ret.set<sint16>(); break; 
       case TypeNode::Base::Type_uint16 : ret.set<uint16>(); break;
       case TypeNode::Base::Type_sint32 : ret.set<sint32>(); break; 
       case TypeNode::Base::Type_uint32 : ret.set<uint32>(); break;
       case TypeNode::Base::Type_sint64 : ret.set<sint64>(); break; 
       case TypeNode::Base::Type_uint64 : ret.set<uint64>(); break;
       
       case TypeNode::Base::Type_text   : ret.set<StrLen>(); break; 
       case TypeNode::Base::Type_ip     : ret.set<uint32>(); break; 
      }
   }
  
  void operator () (TypeNode::Ptr *type_ptr) 
   {
    ret=TypeSet::PointerSizeInfo(type_ptr->type_node);
   }
  
  void operator () (TypeNode::PolyPtr *type_ptr) 
   {
    ret=TypeSet::PointerSizeInfo(type_ptr->type_list);
   }
  
  void operator () (TypeNode::Array *type_ptr)
   {
    ret=TypeSet::ArraySizeInfo(type_ptr->type_node);
   }
  
  void operator () (TypeNode::ArrayLen *type_ptr)
   {
    ret=TypeSet::ArraySizeInfo(type_ptr->type_node);
   }
  
  void operator () (StructNode *struct_node)
   {
    ret=map->sizeInfo(struct_node);
   }
 };

template <class TypeSet>
MapSizeInfo TypedMap<TypeSet>::sizeInfo(TypeNode *type)
 {
  MapSizeInfo ret;
  
  TypeAdapter(type).ptr.apply(SizeInfoFunc(this,ret));
  
  return ret;
 }

template <class TypeSet>
void TypedMap<TypeSet>::sizeInfo()
 {
  for(StructNode &node : body->struct_list )
    {
     sizeInfo(&node);
    }
  
  for(ulen i=0,n=const_buf.getLen(); i<n ;i++)
    {
     auto &result=eval->const_table[i];
     
     const_buf[i].set(result.type,sizeInfo(result.type));
    }
  
  for(StructNode &node : body->struct_list )
    {
     type_set.guardFieldTypes(&node);
    }
 }

template <class TypeSet>
ulen TypedMap<TypeSet>::reserve(MapSizeInfo size_info)
 {
  if( !TryAlign(total,size_info.align_of) ) GuardMapLenOverflow();
  
  ulen ret=total;
  
  total=MapAddLen(total,size_info.size_of);
  
  return ret;
 }
   
template <class TypeSet>
ulen TypedMap<TypeSet>::reserve(MapSizeInfo size_info,ulen count)
 {
  if( !TryAlign(total,size_info.align_of) ) GuardMapLenOverflow();
  
  ulen ret=total;
  
  total=MapAddLen(total,MapMulLen(size_info.size_of,count));
  
  return ret;
 }

template <class TypeSet>
struct TypedMap<TypeSet>::PlaceFunc
 {
  TypedMap<TypeSet> *map;
  Value value;
  RecValue rec;
  
  PlaceFunc(TypedMap<TypeSet> *map_,const Value &value_,const RecValue &rec_) : map(map_),value(value_),rec(rec_) {}
  
  void operator () (TypeNode::Base *type_ptr)
   {
    if( type_ptr->isText() )
      {
       Text text=value.get<Text>();
      
       MapSizeInfo info;
       
       info.set<char>();
       
       rec.elems->off=map->reserve(info,text.str.len);
      }
   }
  
  void operator () (TypeNode::Ptr *) {}
  
  void operator () (TypeNode::PolyPtr *) {}

  void array(ulen off,ulen delta,TypeNode *type)
   {
    PtrLen<Value> data=value.get<Block>().data;
    PtrLen<RecValue> elems=rec.elems;
    
    for(; +data ;++data,++elems,off+=delta) 
      {
       elems->off=off;
       
       map->place(type,*data,*elems);
      }
   }
  
  void array(TypeNode *type)
   {
    MapSizeInfo size_info=map->sizeInfo(type);
    
    ulen off=map->reserve(size_info,rec.elems.len);
    
    array(off,size_info.size_of,type);
   }
  
  void operator () (TypeNode::Array *type_ptr)
   {
    array(type_ptr->type_node);
   }
  
  void operator () (TypeNode::ArrayLen *type_ptr)
   {
    array(type_ptr->type_node);
   }
  
  void operator () (StructNode *struct_node)
   {
    PtrLen<Value> data=value.get<Block>().data;

    ulen off=rec.off;
    PtrLen<RecValue> elems=rec.elems;
    
    auto cur=begin(struct_node->field_list);
    
    for(; +data ;++data,++elems,++cur) 
      {
       elems->off=off+(*cur).index;
       
       map->place((*cur).type_node,*data,*elems);
      }
   }
 };

template <class TypeSet>
void TypedMap<TypeSet>::place(TypeNode *type,const Value &value,const RecValue &rec)
 {
  incLevel();
  
  TypeAdapter(type).ptr.apply(PlaceFunc(this,value,rec));
  
  decLevel();
 }

template <class TypeSet>
void TypedMap<TypeSet>::place()
 {
  total=0;
  
  for(ulen i=0,n=const_buf.getLen(); i<n ;i++) 
    {
     reserve(const_buf[i]);
    }
   
  for(ulen i=0,n=const_buf.getLen(); i<n ;i++)
    {
     auto &result=eval->const_table[i];
     
     resetLevel();
     
     place(result.type,result.value,const_buf[i]);
     
     NameKey key(result.node);
     typename ConstAlgo::PrepareIns prepare(const_map,key);
     
     if( prepare.found )
       {
        GuardMapNameDuplication();
       }
     else
       {
        prepare.complete(&const_buf[i]);
       }
    }
 }

template <class TypeSet>
auto TypedMap<TypeSet>::getRec(PtrNode *node) -> const RecValue &
 {
  if( PtrNode *parent=node->parent )
    {
     return getRec(parent).elems[node->index];
    }
  else
    {
     return const_buf[node->index];
    }
 }

template <class TypeSet>
struct TypedMap<TypeSet>::MapFunc
 {
  TypedMap<TypeSet> *map;
  Value value;
  RecValue rec;
  
  MapFunc(TypedMap<TypeSet> *map_,const Value &value_,const RecValue &rec_) : map(map_),value(value_),rec(rec_) {}
  
  template <class T,class ... SS>
  void place(SS && ... ss)
   {
    new(map->base+rec.off) T( std::forward<SS>(ss)... );
   }
  
  template <class IntType>
  void placeBase(IntType value)
   {
    place<typename IntType::ValueType>(value.value);
   }
  
  void placeBase(IP ip)
   {
    place<uint32>(ip.toInt());
   }
  
  void placeBase(Text text)
   {
    StrLen str=text.str;
    
    char *dst=map->base+rec.elems->off;
    
    str.copyTo(dst);
    
    place<StrLen>(dst,str.len);
   }
  
  template <class T>
  void op()
   {
    placeBase(value.get<T>());
   }
  
  void operator () (TypeNode::Base *type_ptr)
   {
    ExtBaseType(*this,type_ptr->type);
   }
  
  void operator () (TypeNode::Ptr *type_ptr) 
   {
    Ptr ptr=value.get<Ptr>();

    if( !ptr || ptr.null )
      {
       TypeSet::CreatePtr(map->base+rec.off,type_ptr->type_node);
      }
    else
      {
       TypeSet::CreatePtr(map->base+rec.off,type_ptr->type_node,map->base+map->getRec(ptr.ptr_node).off);
      }
   }
  
  void operator () (TypeNode::PolyPtr *type_ptr) 
   {
    Ptr ptr=value.get<Ptr>();

    if( !ptr ) 
      {
       TypeSet::CreatePtr(map->base+rec.off,type_ptr->type_list);
      }
    else if( ptr.null )
      {
       TypeSet::CreatePtr(map->base+rec.off,type_ptr->type_list,ptr.ptr_node->type);
      }
    else
      {
       TypeSet::CreatePtr(map->base+rec.off,type_ptr->type_list,ptr.ptr_node->type,map->base+map->getRec(ptr.ptr_node).off);
      }
   }
  
  void array(TypeNode *type)
   {
    PtrLen<Value> data=value.get<Block>().data;
    
    if( !data )
      {
       TypeSet::CreateArray(map->base+rec.off,type);
      }
    else
      {
       PtrLen<RecValue> elems=rec.elems;
       
       TypeSet::CreateArray(map->base+rec.off,type,map->base+elems->off,data.len);
       
       for(; +data ;++data,++elems) map->map(type,*data,*elems);
      }
   }
  
  void operator () (TypeNode::Array *type_ptr)
   {
    array(type_ptr->type_node); 
   }
  
  void operator () (TypeNode::ArrayLen *type_ptr)
   {
    array(type_ptr->type_node); 
   }
  
  void operator () (StructNode *struct_node) // no structure constructor call
   {
    PtrLen<Value> data=value.get<Block>().data;
    
    PtrLen<RecValue> elems=rec.elems;
    
    auto cur=begin(struct_node->field_list);
    
    for(; +data ;++data,++elems,++cur) map->map((*cur).type_node,*data,*elems);
   }
 };

template <class TypeSet>
void TypedMap<TypeSet>::map(TypeNode *type,const Value &value,const RecValue &rec)
 {
  incLevel();
  
  TypeAdapter(type).ptr.apply(MapFunc(this,value,rec));
  
  decLevel();
 }

template <class TypeSet>
TypedMap<TypeSet>::TypedMap(EngineResult result)
 : eval(result.eval), 
   body(result.body),
   const_buf(result.eval->const_table.getLen()),
   struct_buf(result.body->struct_list.count),
   total(0),
   base(0),
   level(0),
   type_set(result.body->struct_list.count)
 {
  prepare();
  
  sizeInfo();
  
  place();
 }

template <class TypeSet>
TypedMap<TypeSet>::~TypedMap()
 {
 }

template <class TypeSet>
void TypedMap<TypeSet>::operator () (void *mem)
 {
  base=Place<void>(mem);
  
  for(ulen i=0,n=const_buf.getLen(); i<n ;i++)
    {
     auto &result=eval->const_table[i];
     
     resetLevel();
     
     map(result.type,result.value,const_buf[i]);
    }
 }

template <class TypeSet>
template <class T>
T * TypedMap<TypeSet>::findConst(StrLen name)
 {
  NameKey key(name);
  
  RecConst *rec=const_map.find(key);
  
  if( !rec || !MapTypeCheck<T>::template Match<T>(type_set,rec->type) ) return 0;
  
  return base+rec->off;
 }

template <class TypeSet>
template <class T>
T TypedMap<TypeSet>::takeConst(StrLen name)
 {
  NameKey key(name);
  
  RecConst *rec=const_map.find(key);
  
  if( !rec ) GuardMapNoConst(name);
   
  if( !MapTypeCheck<T>::template Match(type_set,rec->type) ) GuardMapBadConstType(name); 
  
  T *ptr=base+rec->off;
  
  return *ptr;
 }

} // namespace DDL2
} // namespace CCore
 
#endif
 

