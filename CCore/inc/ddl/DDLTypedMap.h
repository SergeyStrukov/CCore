/* DDLTypedMap.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.04
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

#ifndef CCore_inc_ddl_DDLTypedMap_h
#define CCore_inc_ddl_DDLTypedMap_h
 
#include <CCore/inc/ddl/DDLMap.h>

namespace CCore {
namespace DDL {

/* functions */

inline bool HasNames(ScopeNode *) { return true; }

template <class ... TT>
bool HasNames(ScopeNode *scope_node,StrLen name,TT ... scope)
 {
  if( StrCmp(scope_node->name.name.token.str,name) ) return false;
  
  return HasNames(scope_node->parent,scope...);
 }

template <class ... TT>
bool HasName(StructNode *struct_node,StrLen name,TT ... scope)
 {
  if( StrCmp(struct_node->name.name.token.str,name) ) return false;
  
  if( struct_node->depth!=Meta::TypeListLen<TT...>::Ret ) return false;
  
  return HasNames(struct_node->parent,scope...);
 }

void GuardBadStructure();

inline void SetFieldOffsets(FieldNode *field_node)
 {
  if( field_node ) GuardBadStructure();
 }

template <class ... TT>
void SetFieldOffsets(FieldNode *field_node,StrLen name,ulen offset,TT ... args)
 {
  if( !field_node ) GuardBadStructure();
  
  if( StrCmp(field_node->name.name.token.str,name) ) GuardBadStructure();
  
  field_node->index=offset;
  
  SetFieldOffsets(field_node->next,args...);
 }

template <class ... TT>
void SetFieldOffsets(StructNode *struct_node,TT ... args)
 {
  SetFieldOffsets(struct_node->field_list.beg,args...);
 }

void GuardMapNoConst(StrLen name);

void GuardMapBadConstType(StrLen name);

/* classes */

struct MapSizeInfo;

class MapTypeCheck;

template <class ... TT> struct GuardFieldTypes;

template <class TypeSet> class TypedMap;

struct MapHackPtr;

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

/* class MapTypeCheck */

class MapTypeCheck : NoCopy
 {
   enum TypeId
    {
     Type_sint8,
     Type_uint8,
     
     Type_sint16,
     Type_uint16,
     
     Type_sint32,
     Type_uint32,
     
     Type_sint64,
     Type_uint64,
     
     Type_text,
     Type_ptr,
     Type_array,
     Type_struct
    };
  
   struct MatchSwitch : TypeSwitch
    {
     const void *ctx;
     TypeId type_id;
     TypeNode *type_node;
     StructNode *struct_node;
    
     MatchSwitch() : TypeSwitch(this) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { type_id=Type_sint8; }
     void do_uint8(TypeNode_suint<imp_uint8> *) { type_id=Type_uint8; }

     void do_sint16(TypeNode_suint<imp_sint16> *) { type_id=Type_sint16; }
     void do_uint16(TypeNode_suint<imp_uint16> *) { type_id=Type_uint16; }

     void do_sint32(TypeNode_suint<imp_sint32> *) { type_id=Type_sint32; }
     void do_uint32(TypeNode_suint<imp_uint32> *) { type_id=Type_uint32; }

     void do_sint64(TypeNode_suint<imp_sint64> *) { type_id=Type_sint64; }
     void do_uint64(TypeNode_suint<imp_uint64> *) { type_id=Type_uint64; }

     void do_text(TypeNode_text *) { type_id=Type_text; }
     void do_ip(TypeNode_ip *) { type_id=Type_uint32; }

     void do_ptr(TypeNode_ptr *ptr_type) 
      { 
       type_id=Type_ptr;
       type_node=ptr_type->type_node;
      }
     
     void do_array(TypeNode_array *array_type) 
      {
       type_id=Type_array;
       type_node=array_type->type_node;
      }
     
     void do_array_len(TypeNode_array_len *array_type) 
      { 
       type_id=Type_array;
       type_node=array_type->type_node;
      }
     
     void do_struct(StructNode *struct_node_)
      {
       type_id=Type_struct;
       struct_node=struct_node_;
      }
     
     void do_struct(TypeNode_struct *type) { do_struct(type->base_struct); }

     void do_ref(TypeNode_ref *type)
      {
       if( AliasNode *alias=type->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          do_struct(type->struct_node);
         }
      }
    };
  
   MatchSwitch ts_match;
   
  private:
   
   template <class TypeSet,class T> struct Match;
   
  public:
  
   MapTypeCheck() {}
   
   template <class T,class TypeSet>
   bool match(const TypeSet &type_set,TypeNode *type)
    {
     ts_match.ctx=&type_set;
     
     return Match<TypeSet,T>::Do(ts_match,type);
    }
 };

template <class TypeSet,class T>
struct MapTypeCheck::Match
 {
  static bool Do(MatchSwitch &ts_match,TypeNode *type)
   {
    type->dispatch(ts_match);
    
    const TypeSet *type_set=static_cast<const TypeSet *>(ts_match.ctx);
    
    return ts_match.type_id==Type_struct && type_set->template isStruct<T>(ts_match.struct_node) ;
   }
 };

template <class TypeSet>
struct MapTypeCheck::Match<TypeSet,imp_sint8>
 {
  static bool Do(MatchSwitch &ts_match,TypeNode *type)
   {
    type->dispatch(ts_match);
    
    return ts_match.type_id==Type_sint8;
   }
 };

template <class TypeSet>
struct MapTypeCheck::Match<TypeSet,imp_uint8>
 {
  static bool Do(MatchSwitch &ts_match,TypeNode *type)
   {
    type->dispatch(ts_match);
    
    return ts_match.type_id==Type_uint8;
   }
 };

template <class TypeSet>
struct MapTypeCheck::Match<TypeSet,imp_sint16>
 {
  static bool Do(MatchSwitch &ts_match,TypeNode *type)
   {
    type->dispatch(ts_match);
    
    return ts_match.type_id==Type_sint16;
   }
 };

template <class TypeSet>
struct MapTypeCheck::Match<TypeSet,imp_uint16>
 {
  static bool Do(MatchSwitch &ts_match,TypeNode *type)
   {
    type->dispatch(ts_match);
    
    return ts_match.type_id==Type_uint16;
   }
 };

template <class TypeSet>
struct MapTypeCheck::Match<TypeSet,imp_sint32>
 {
  static bool Do(MatchSwitch &ts_match,TypeNode *type)
   {
    type->dispatch(ts_match);
    
    return ts_match.type_id==Type_sint32;
   }
 };

template <class TypeSet>
struct MapTypeCheck::Match<TypeSet,imp_uint32>
 {
  static bool Do(MatchSwitch &ts_match,TypeNode *type)
   {
    type->dispatch(ts_match);
    
    return ts_match.type_id==Type_uint32 ;
   }
 };

template <class TypeSet>
struct MapTypeCheck::Match<TypeSet,imp_sint64>
 {
  static bool Do(MatchSwitch &ts_match,TypeNode *type)
   {
    type->dispatch(ts_match);
    
    return ts_match.type_id==Type_sint64;
   }
 };

template <class TypeSet>
struct MapTypeCheck::Match<TypeSet,imp_uint64>
 {
  static bool Do(MatchSwitch &ts_match,TypeNode *type)
   {
    type->dispatch(ts_match);
    
    return ts_match.type_id==Type_uint64;
   }
 };

template <class TypeSet>
struct MapTypeCheck::Match<TypeSet,StrLen>
 {
  static bool Do(MatchSwitch &ts_match,TypeNode *type)
   {
    type->dispatch(ts_match);
    
    return ts_match.type_id==Type_text;
   }
 };

template <class TypeSet,class T>
struct MapTypeCheck::Match<TypeSet,T *>
 {
  static bool Do(MatchSwitch &ts_match,TypeNode *type)
   {
    type->dispatch(ts_match);
    
    return ts_match.type_id==Type_ptr && Match<TypeSet,T>::Do(ts_match,ts_match.type_node) ;
   }
 };

template <class TypeSet,class T>
struct MapTypeCheck::Match<TypeSet,PtrLen<T> >
 {
  static bool Do(MatchSwitch &ts_match,TypeNode *type)
   {
    type->dispatch(ts_match);
    
    return ts_match.type_id==Type_array && Match<TypeSet,T>::Do(ts_match,ts_match.type_node) ;
   }
 };

/* struct GuardFieldTypes<TT> */

template <> 
struct GuardFieldTypes<>
 {
  template <class TypeSet>
  GuardFieldTypes(const TypeSet &,MapTypeCheck &,FieldNode *field_node) 
   {
    if( field_node ) GuardBadStructure();
   }
  
  template <class TypeSet>
  GuardFieldTypes(const TypeSet &,MapTypeCheck &,StructNode *struct_node) 
   {
    if( struct_node->field_list.beg ) GuardBadStructure();
   }
 };

template <class T,class ... TT> 
struct GuardFieldTypes<T,TT...>
 {
  template <class TypeSet>
  GuardFieldTypes(const TypeSet &type_set,MapTypeCheck &type_check,FieldNode *field_node)
   {
    if( !field_node ) GuardBadStructure();
    
    if( !type_check.match<T>(type_set,field_node->type_node) ) GuardBadStructure();
    
    GuardFieldTypes<TT...>(type_set,type_check,field_node->next);
   }

  template <class TypeSet>
  GuardFieldTypes(const TypeSet &type_set,MapTypeCheck &type_check,StructNode *struct_node)
   : GuardFieldTypes(type_set,type_check,struct_node->field_list.beg) 
   {
   }
 };

/* class TypedMap<TypeSet> */

template <class TypeSet>
class TypedMap : NoCopy
 {
   static const ulen MaxLevel = 100 ;
  
   struct RecValue
    {
     ulen off;
     
     PtrLen<RecValue> elems;
     
     RecValue() : off(0) {}
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
  
   struct RecConst : RecValue
    {
     TypeNode *type;
     MapSizeInfo size_info;
     
     RBTreeLink<RecConst,NameKey> link;
     
     RecConst() : type(0) {}
    };
   
   struct RecStruct
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
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
   
  private: 
   
   Eval *eval;
   BodyNode *body;
   
   DynArray<RecConst> const_buf;
   Collector<RecValue> rec_buf;
   DynArray<RecStruct> struct_buf;
   
   typedef typename RBTreeLink<RecConst,NameKey>::template Algo<&RecConst::link> ConstAlgo; 
   
   typename ConstAlgo::Root const_map;
   
   ulen total;
   Place<void> base;
   
  private: 
   
   ulen reserve(MapSizeInfo size_info);
   
   ulen reserve(MapSizeInfo size_info,ulen count);
   
   void reserve(RecConst &rec) { rec.off=reserve(rec.size_info); }
   
  private:

   struct PrepareSwitch : TypeSwitch
    {
     TypedMap<TypeSet> *map;
     Value value;
     RecValue *rec;
     
     explicit PrepareSwitch(TypedMap<TypeSet> *map_) : TypeSwitch(this),map(map_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) {}
     void do_uint8(TypeNode_suint<imp_uint8> *) {}

     void do_sint16(TypeNode_suint<imp_sint16> *) {}
     void do_uint16(TypeNode_suint<imp_uint16> *) {}

     void do_sint32(TypeNode_suint<imp_sint32> *) {}
     void do_uint32(TypeNode_suint<imp_uint32> *) {}

     void do_sint64(TypeNode_suint<imp_sint64> *) {}
     void do_uint64(TypeNode_suint<imp_uint64> *) {}

     void do_text(TypeNode_text *)
      {
       RecValue *obj=map->rec_buf.append_default();
       
       rec->elems=Range(obj,1);
      }
     
     void do_ip(TypeNode_ip *) {}

     void do_ptr(TypeNode_ptr *) {}
     
     void do_array_type(TypeNode *type)
      {
       PtrLen<Value> data=value.get<Block>().data;
       
       PtrLen<RecValue> elems=map->rec_buf.extend_default(data.len);
       
       rec->elems=elems;
       
       for(; +data ;++data,++elems) map->prepare(type,*data,*elems);
      }
     
     void do_array(TypeNode_array *array_type)
      {
       do_array_type(array_type->type_node);
      }
     
     void do_array_len(TypeNode_array_len *array_type)
      {
       do_array_type(array_type->type_node);
      }
     
     void do_struct(StructNode *struct_node)
      {
       PtrLen<Value> data=value.get<Block>().data;
       
       PtrLen<RecValue> elems=map->rec_buf.extend_default(data.len);
       
       rec->elems=elems;
       
       auto cur=begin(struct_node->field_list);
       
       for(; +data ;++data,++elems,++cur) map->prepare((*cur).type_node,*data,*elems);
      }
     
     void do_struct(TypeNode_struct *type)
      {
       do_struct(type->base_struct);
      }

     void do_ref(TypeNode_ref *type)
      {
       if( AliasNode *alias=type->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          do_struct(type->struct_node);
         }
      }
    };
   
   PrepareSwitch ts_prepare;
   ulen level;
   
   void prepare(TypeNode *type,const Value &value,RecValue &rec);
   
   void prepare();
   
  private:
   
   struct SizeSwitch : TypeSwitch
    {
     TypedMap<TypeSet> *map;
     MapSizeInfo info;
     
     explicit SizeSwitch(TypedMap<TypeSet> *map_) : TypeSwitch(this),map(map_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { info.template set<imp_sint8>(); }
     void do_uint8(TypeNode_suint<imp_uint8> *) { info.template set<imp_uint8>(); }

     void do_sint16(TypeNode_suint<imp_sint16> *) { info.template set<imp_sint16>(); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { info.template set<imp_uint16>(); }

     void do_sint32(TypeNode_suint<imp_sint32> *) { info.template set<imp_sint32>(); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { info.template set<imp_uint32>(); }

     void do_sint64(TypeNode_suint<imp_sint64> *) { info.template set<imp_sint64>(); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { info.template set<imp_uint64>(); }

     void do_text(TypeNode_text *) { info.template set<StrLen>(); }
     void do_ip(TypeNode_ip *) { info.template set<imp_uint32>(); }

     void do_ptr(TypeNode_ptr *ptr_type)
      {
       info=TypeSet::PointerSizeInfo(ptr_type->type_node);
      }
     
     void do_array(TypeNode_array *array_type)
      {
       info=TypeSet::ArraySizeInfo(array_type->type_node);
      }
     
     void do_array_len(TypeNode_array_len *array_type)
      {
       info=TypeSet::ArraySizeInfo(array_type->type_node);
      }
     
     void do_struct(StructNode *struct_node)
      {
       info=map->sizeInfo(struct_node);
      }
     
     void do_struct(TypeNode_struct *type)
      {
       do_struct(type->base_struct);
      }

     void do_ref(TypeNode_ref *type)
      {
       if( AliasNode *alias=type->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          do_struct(type->struct_node);
         }
      }
    };
   
   SizeSwitch ts_size;
   
   MapSizeInfo sizeInfo(StructNode *struct_node)
    {
     ulen ind=struct_node->index;
     
     return struct_buf[ind].get(type_set,struct_node);
    }
   
   MapSizeInfo sizeInfo(TypeNode *type);
   
   void setStruct();
   
   void sizeInfo();
   
  private:

   struct PlaceSwitch : TypeSwitch
    {
     TypedMap<TypeSet> *map;
     Value value;
     RecValue rec;
     
     explicit PlaceSwitch(TypedMap<TypeSet> *map_) : TypeSwitch(this),map(map_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) {}
     void do_uint8(TypeNode_suint<imp_uint8> *) {}

     void do_sint16(TypeNode_suint<imp_sint16> *) {}
     void do_uint16(TypeNode_suint<imp_uint16> *) {}

     void do_sint32(TypeNode_suint<imp_sint32> *) {}
     void do_uint32(TypeNode_suint<imp_uint32> *) {}

     void do_sint64(TypeNode_suint<imp_sint64> *) {}
     void do_uint64(TypeNode_suint<imp_uint64> *) {}

     void do_text(TypeNode_text *)
      {
       Text text=value.get<Text>();
       
       MapSizeInfo info;
       
       info.template set<char>();
       
       rec.elems->off=map->reserve(info,text.str.len);
      }
     
     void do_ip(TypeNode_ip *) {}

     void do_ptr(TypeNode_ptr *) {}
     
     void do_array_type(ulen off,ulen delta,TypeNode *type)
      {
       PtrLen<Value> data=value.get<Block>().data;
       PtrLen<RecValue> elems=rec.elems;
       
       for(; +data ;++data,++elems,off+=delta) 
         {
          elems->off=off;
          
          map->place(type,*data,*elems);
         }
      }
     
     void do_array_type(TypeNode *type)
      {
       MapSizeInfo size_info=map->sizeInfo(type);
       
       ulen off=map->reserve(size_info,rec.elems.len);
       
       do_array_type(off,size_info.size_of,type);
      }
     
     void do_array(TypeNode_array *array_type) { do_array_type(array_type->type_node); }
     
     void do_array_len(TypeNode_array_len *array_type) { do_array_type(array_type->type_node); }
     
     void do_struct(StructNode *struct_node)
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
     
     void do_struct(TypeNode_struct *type)
      {
       do_struct(type->base_struct);
      }

     void do_ref(TypeNode_ref *type)
      {
       if( AliasNode *alias=type->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          do_struct(type->struct_node);
         }
      }
    };
   
   PlaceSwitch ts_place;
   
   void place(TypeNode *type,const Value &value,const RecValue &rec);
   
   void place();
   
  private:
   
   struct MapSwitch : TypeSwitch
    {
     TypedMap<TypeSet> *map;
     Value value;
     RecValue rec;
     
     template <class T>
     void do_val()
      {
       new(map->base+rec.off) T( value.get<T>() );
      }
     
     template <class T>
     void do_val(T val)
      {
       new(map->base+rec.off) T( val );
      }
     
     explicit MapSwitch(TypedMap<TypeSet> *map_) : TypeSwitch(this),map(map_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { do_val<imp_sint8>(); }
     void do_uint8(TypeNode_suint<imp_uint8> *) { do_val<imp_uint8>(); }

     void do_sint16(TypeNode_suint<imp_sint16> *) { do_val<imp_sint16>(); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { do_val<imp_uint16>(); }

     void do_sint32(TypeNode_suint<imp_sint32> *) { do_val<imp_sint32>(); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { do_val<imp_uint32>(); }

     void do_sint64(TypeNode_suint<imp_sint64> *) { do_val<imp_sint64>(); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { do_val<imp_uint64>(); }

     void do_text(TypeNode_text *)
      {
       Text text=value.get<Text>();
       
       char *dst=map->base+rec.elems->off;
       
       text.str.copyTo(dst);
       
       do_val( StrLen(dst,text.str.len) );
      }
     
     void do_ip(TypeNode_ip *) { do_val( MapIP(value.get<IP>()) ); }

     void do_ptr(TypeNode_ptr *ptr_type) 
      { 
       Ptr ptr=value.get<Ptr>();

       if( !ptr )
         {
          TypeSet::CreatePtr(map->base+rec.off,ptr_type->type_node);
         }
       else
         {
          TypeSet::CreatePtr(map->base+rec.off,ptr_type->type_node,map->base+map->getRec(ptr.node).off);
         }
      }
     
     void do_array_type(TypeNode *type)
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
     
     void do_array(TypeNode_array *array_type) { do_array_type(array_type->type_node); }
     
     void do_array_len(TypeNode_array_len *array_type) { do_array_type(array_type->type_node); }
     
     void do_struct(StructNode *struct_node) // no structure constructor call
      {
       PtrLen<Value> data=value.get<Block>().data;
       
       PtrLen<RecValue> elems=rec.elems;
       
       auto cur=begin(struct_node->field_list);
       
       for(; +data ;++data,++elems,++cur) map->map((*cur).type_node,*data,*elems);
      }
     
     void do_struct(TypeNode_struct *type) { do_struct(type->base_struct); }

     void do_ref(TypeNode_ref *type)
      {
       if( AliasNode *alias=type->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          do_struct(type->struct_node);
         }
      }
    };
   
   MapSwitch ts_map;
   
   void map(TypeNode *type,const Value &value,const RecValue &rec);
   
   const RecValue & getRec(PtrNode *node);
   
  private: 
   
   MapTypeCheck type_check;
   TypeSet type_set;
   
  public:
   
   TypedMap(Eval *eval,BodyNode *body);
   
   ~TypedMap();
   
   ulen getLen() const { return total; }
   
   void operator () (void *mem);
   
   template <class T>
   T * findConst(StrLen name);
   
   template <class T>
   T takeConst(StrLen name);
 };

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
void TypedMap<TypeSet>::prepare(TypeNode *type,const Value &value,RecValue &rec)
 {
  if( level>MaxLevel ) GuardMapTooDeep(); 
  
  level++;
  
  ts_prepare.value=value;
  ts_prepare.rec=&rec;
  
  type->dispatch(ts_prepare);
  
  level--;
 }

template <class TypeSet>
void TypedMap<TypeSet>::prepare()
 {
  level=0;
  
  for(ulen i=0,n=eval->getConstCount(); i<n ;i++)
    {
     auto result=eval->getConstResult(i);
     
     prepare(result.type,result.value,const_buf[i]);
    }
 }

template <class TypeSet>
MapSizeInfo TypedMap<TypeSet>::sizeInfo(TypeNode *type)
 {
  type->dispatch(ts_size);
  
  return ts_size.info;
 }

template <class TypeSet>
void TypedMap<TypeSet>::setStruct()
 {
  ulen ind=0;
  
  for(StructNode &node : body->struct_list )
    {
     node.index=ind++;
    }
 }

template <class TypeSet>
void TypedMap<TypeSet>::sizeInfo()
 {
  for(ulen i=0,n=eval->getConstCount(); i<n ;i++)
    {
     auto result=eval->getConstResult(i);
     
     const_buf[i].size_info=sizeInfo(result.type);
    }
  
  for(StructNode &node : body->struct_list )
    {
     sizeInfo(&node);
    }
  
  for(StructNode &node : body->struct_list )
    {
     type_set.guardFieldTypes(type_check,&node);
    }
 }

template <class TypeSet>
void TypedMap<TypeSet>::place(TypeNode *type,const Value &value,const RecValue &rec)
 {
  ts_place.value=value;
  ts_place.rec=rec;
  
  type->dispatch(ts_place);
 }

template <class TypeSet>
void TypedMap<TypeSet>::place()
 {
  total=0;
  
  for(ulen i=0,n=eval->getConstCount(); i<n ;i++) 
    {
     reserve(const_buf[i]);
    }
   
  for(ulen i=0,n=eval->getConstCount(); i<n ;i++)
    {
     auto result=eval->getConstResult(i);
     
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
        
        const_buf[i].type=result.type;
       }
    }
 }

template <class TypeSet>
void TypedMap<TypeSet>::map(TypeNode *type,const Value &value,const RecValue &rec)
 {
  ts_map.value=value;
  ts_map.rec=rec;
  
  type->dispatch(ts_map);
 }

template <class TypeSet>
auto TypedMap<TypeSet>::getRec(PtrNode *node) -> const RecValue &
 {
  if( PtrNode *next=node->base )
    {
     return getRec(next).elems[node->index];
    }
  else
    {
     return const_buf[node->index];
    }
 }

template <class TypeSet>
TypedMap<TypeSet>::TypedMap(Eval *eval_,BodyNode *body_)
 : eval(eval_), 
   body(body_),
   const_buf(eval_->getConstCount()),
   struct_buf(body_->struct_list.count),
   base(0),
   ts_prepare(this),
   ts_size(this),
   ts_place(this),
   ts_map(this)
 {
  prepare();
  
  setStruct();
  
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
  
  for(ulen i=0,n=eval->getConstCount(); i<n ;i++)
    {
     auto result=eval->getConstResult(i);
     
     map(result.type,result.value,const_buf[i]);
    }
 }

template <class TypeSet>
template <class T>
T * TypedMap<TypeSet>::findConst(StrLen name)
 {
  NameKey key(name);
  
  RecConst *rec=const_map.find(key);
  
  if( !rec || !type_check.match<T>(type_set,rec->type) ) return 0;
  
  return base+rec->off;
 }

template <class TypeSet>
template <class T>
T TypedMap<TypeSet>::takeConst(StrLen name)
 {
  NameKey key(name);
  
  RecConst *rec=const_map.find(key);
  
  if( !rec ) GuardMapNoConst(name);
   
  if( !type_check.match<T>(type_set,rec->type) ) GuardMapBadConstType(name); 
  
  T *ptr=base+rec->off;
  
  return *ptr;
 }

/* struct MapHackPtr */

struct MapHackPtr
 {
  // HACK: all pointers are the same
  
  static MapSizeInfo PointerSizeInfo(TypeNode *)
   {
    MapSizeInfo ret;
    
    ret.set<char *>();
    
    return ret;
   }
  
  static void CreatePtr(Place<void> place,TypeNode *)
   {
    new(place) (char *){};
   }
  
  static void CreatePtr(Place<void> place,TypeNode *,Place<void> ptr)
   {
    new(place) (char *){ptr};
   }
  
  static MapSizeInfo ArraySizeInfo(TypeNode *)
   {
    MapSizeInfo ret;
    
    ret.set<PtrLen<char> >();
    
    return ret;
   }
  
  static void CreateArray(Place<void> place,TypeNode *)
   {
    new(place) PtrLen<char>();
   }
  
  static void CreateArray(Place<void> place,TypeNode *,Place<void> ptr,ulen len)
   {
    new(place) PtrLen<char>(ptr,len);
   }
 };

} // namespace DDL
} // namespace CCore
 
#endif
 

