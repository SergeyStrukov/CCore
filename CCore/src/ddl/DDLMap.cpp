/* DDLMap.cpp */
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

#include <CCore/inc/ddl/DDLMap.h>

#include <CCore/inc/Crc.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/algon/CommonIntAlgo.h>

namespace CCore {
namespace DDL {

/* functions */

void GuardMapTooDeep()
 {
  Printf(Exception,"CCore::DDL::(Typed)Map : too deep");
 }

void GuardMapNameDuplication()
 {
  Printf(Exception,"CCore::DDL::(Typed)Map : const name duplication");
 }

void GuardMapStructNameDuplication()
 {
  Printf(Exception,"CCore::DDL::Map : struct name duplication");
 }

void GuardMapLenOverflow()
 {
  Printf(Exception,"CCore::DDL::(Typed)Map : len overflow");
 }

/* struct NameKey */

struct NameKey::Cur
 {
  StrLen::Fin fin;
  ScopeNode *parent;
  char ch;
  
  Cur(const StrLen::Fin &fin_,ScopeNode *parent_) : fin(fin_),parent(parent_),ch(0) {}
  
  bool next()
   {
    if( fin.next() ) 
      {
       ch=*fin;
       
       return true;
      }
    else
      {
       if( parent )
         {
          ch='#';
          
          fin=parent->name.name.token.str.getFin();
          parent=parent->parent;
          
          return true;
         }
       else
         {
          return false;
         }
      }
   }
  
  char operator * () const { return ch; }
 };

auto NameKey::getCur() const -> Cur { return Cur(name.getFin(),parent); }

void NameKey::setHash()
 {
  Crc32 crc;
  
  for(auto cur=getCur(); cur.next() ;) crc.add(*cur);
  
  hash=crc;
 }

CmpResult NameKey::objCmp(const NameKey &obj) const
 {
  if( CmpResult ret=Cmp(hash,obj.hash) ) return ret;
  
  Cur a=getCur();
  Cur b=obj.getCur();

  while( a.next() )
    {
     if( b.next() )
       {
        if( CmpResult ret=Cmp(*a,*b) ) return ret;
       }
     else
       {
        return CmpGreater;
       }
    }
  
  if( b.next() )
    {
     return CmpLess; 
    }
  else
    {
     return CmpEqual;
    }
 }

/* class Map */

template <ulen N>
class Map::AlignMulTable : NoCopy
 {
   ulen table[N];
   
  public:
   
   AlignMulTable()
    {
     for(ulen a=0; a<N ;a++) table[a]=N/Algon::GCD(a,N);
    }
   
   ulen operator () (ulen a) const { return table[a%N]; } // N/GCD(a,N)
   
   static AlignMulTable<N> Object;
 };

template <ulen N>
Map::AlignMulTable<N> Map::AlignMulTable<N>::Object;

template <>
class Map::AlignMulTable<1>
 {
  public:
   
   static ulen Object(ulen)
    {
     return 1;
    }
 };

template <>
class Map::AlignMulTable<2>
 {
  public:
   
   static ulen Object(ulen a)
    {
     return (a&1)?2:1;
    }
 };

template <>
class Map::AlignMulTable<4>
 {
  public:
   
   static ulen Object(ulen a)
    {
     static const ulen Table[4]={1,4,2,4};
    
     return Table[a&3];
    }
 };

template <>
class Map::AlignMulTable<8>
 {
  public:
   
   static ulen Object(ulen a)
    {
     static const ulen Table[8]={1,8,4,8,2,8,4,8};
   
     return Table[a&7];
    }
 };

template <class T>
ulen Map::AlignAdd(ulen a)
 {
  return a*AlignMulTable<alignof (T)>::Object(a);
 }

ulen Map::AlignOf(unsigned flags)
 {
  ulen ret=1;
  
  if( flags&(1u<<Type_sint8) ) ret=AlignAdd<imp_sint8>(ret);
  if( flags&(1u<<Type_uint8) ) ret=AlignAdd<imp_uint8>(ret);
  
  if( flags&(1u<<Type_sint16) ) ret=AlignAdd<imp_sint16>(ret);
  if( flags&(1u<<Type_uint16) ) ret=AlignAdd<imp_uint16>(ret);
  
  if( flags&(1u<<Type_sint32) ) ret=AlignAdd<imp_sint32>(ret);
  if( flags&(1u<<Type_uint32) ) ret=AlignAdd<imp_uint32>(ret);
  
  if( flags&(1u<<Type_sint64) ) ret=AlignAdd<imp_sint64>(ret);
  if( flags&(1u<<Type_uint64) ) ret=AlignAdd<imp_uint64>(ret);
  
  if( flags&(1u<<Type_text) )      ret=AlignAdd<StrLen>(ret);
  if( flags&(1u<<Type_ptr) )       ret=AlignAdd<DataPtr>(ret);
  if( flags&(1u<<Type_array_ptr) ) ret=AlignAdd<ArrayPtr>(ret);
  
  return ret;
 }

ulen Map::AlignFor(ulen off,unsigned flags)
 {
  if( !TryAlign(off,AlignOf(flags)) ) GuardMapLenOverflow();
  
  return off;
 }

void Map::MapSwitch::do_sint8(TypeNode_suint<imp_sint8> *) { do_val<imp_sint8>(); }

void Map::MapSwitch::do_uint8(TypeNode_suint<imp_uint8> *) { do_val<imp_uint8>(); }

void Map::MapSwitch::do_sint16(TypeNode_suint<imp_sint16> *) { do_val<imp_sint16>(); }

void Map::MapSwitch::do_uint16(TypeNode_suint<imp_uint16> *) { do_val<imp_uint16>(); }

void Map::MapSwitch::do_sint32(TypeNode_suint<imp_sint32> *) { do_val<imp_sint32>(); }

void Map::MapSwitch::do_uint32(TypeNode_suint<imp_uint32> *) { do_val<imp_uint32>(); }

void Map::MapSwitch::do_sint64(TypeNode_suint<imp_sint64> *) { do_val<imp_sint64>(); }

void Map::MapSwitch::do_uint64(TypeNode_suint<imp_uint64> *) { do_val<imp_uint64>(); }

void Map::MapSwitch::do_text(TypeNode_text *)
 {
  Text text=value.get<Text>();
  
  char *dst=map->base+rec.elems->off;
  
  text.str.copyTo(dst);
  
  do_val( StrLen(dst,text.str.len) );
 }

void Map::MapSwitch::do_ip(TypeNode_ip *) { do_val( MapIP(value.get<IP>()) ); }

void Map::MapSwitch::do_ptr(TypeNode_ptr *) { do_val( map->mapPtr(value.get<Ptr>()) ); }

void Map::MapSwitch::do_array(TypeNode_array *array_type)
 {
  PtrLen<Value> data=value.get<Block>().data;
  TypeNode *type=array_type->type_node;
  
  if( !data )
    {
     do_val( ArrayPtr() );
    }
  else
    {
     PtrLen<RecValue> elems=rec.elems;
     
     do_val( ArrayPtr(map->base+elems->off,data.len) );
     
     for(; +data ;++data,++elems) map->map(type,*data,*elems);
    }
 }

void Map::MapSwitch::do_array_len(TypeNode_array_len *array_type)
 {
  PtrLen<Value> data=value.get<Block>().data;
  TypeNode *type=array_type->type_node;
  
  PtrLen<RecValue> elems=rec.elems;
  
  for(; +data ;++data,++elems) map->map(type,*data,*elems);
 }

void Map::MapSwitch::do_struct(StructNode *struct_node)
 {
  PtrLen<Value> data=value.get<Block>().data;
  
  PtrLen<RecValue> elems=rec.elems;
  
  auto cur=begin(struct_node->field_list);
  
  for(; +data ;++data,++elems,++cur) map->map((*cur).type_node,*data,*elems);
 }

void Map::MapSwitch::do_struct(TypeNode_struct *type)
 {
  do_struct(type->base_struct);
 }

void Map::MapSwitch::do_ref(TypeNode_ref *type)
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

void Map::map(TypeNode *type,const Value &value,const RecValue &rec)
 {
  ts_map.value=value;
  ts_map.rec=rec;
  
  type->dispatch(ts_map);
 }

auto Map::getRec(PtrNode *node) -> const RecValue &
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

DataPtr Map::mapPtr(Ptr ptr)
 {
  if( !ptr ) return 0;
  
  void *place=base+getRec(ptr.node).off;
  
  return place;
 }

void Map::PrepareSwitch::do_sint8(TypeNode_suint<imp_sint8> *) {}

void Map::PrepareSwitch::do_uint8(TypeNode_suint<imp_uint8> *) {}

void Map::PrepareSwitch::do_sint16(TypeNode_suint<imp_sint16> *) {}

void Map::PrepareSwitch::do_uint16(TypeNode_suint<imp_uint16> *) {}

void Map::PrepareSwitch::do_sint32(TypeNode_suint<imp_sint32> *) {}

void Map::PrepareSwitch::do_uint32(TypeNode_suint<imp_uint32> *) {}

void Map::PrepareSwitch::do_sint64(TypeNode_suint<imp_sint64> *) {}

void Map::PrepareSwitch::do_uint64(TypeNode_suint<imp_uint64> *) {}

void Map::PrepareSwitch::do_text(TypeNode_text *)
 {
  RecValue *obj=map->rec_buf.append_default();
  
  rec->elems=Range(obj,1);
 }

void Map::PrepareSwitch::do_ip(TypeNode_ip *) {}

void Map::PrepareSwitch::do_ptr(TypeNode_ptr *) {}

void Map::PrepareSwitch::do_array_type(TypeNode *type)
 {
  PtrLen<Value> data=value.get<Block>().data;
  
  PtrLen<RecValue> elems=map->rec_buf.extend_default(data.len);
  
  rec->elems=elems;
  
  for(; +data ;++data,++elems) map->prepare(type,*data,*elems);
 }

void Map::PrepareSwitch::do_array(TypeNode_array *array_type)
 {
  do_array_type(array_type->type_node);
 }

void Map::PrepareSwitch::do_array_len(TypeNode_array_len *array_type)
 {
  do_array_type(array_type->type_node);
 }

void Map::PrepareSwitch::do_struct(StructNode *struct_node)
 {
  PtrLen<Value> data=value.get<Block>().data;
  
  PtrLen<RecValue> elems=map->rec_buf.extend_default(data.len);
  
  rec->elems=elems;
  
  auto cur=begin(struct_node->field_list);
  
  for(; +data ;++data,++elems,++cur) map->prepare((*cur).type_node,*data,*elems);
 }

void Map::PrepareSwitch::do_struct(TypeNode_struct *type)
 {
  do_struct(type->base_struct);
 }

void Map::PrepareSwitch::do_ref(TypeNode_ref *type)
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

void Map::prepare(TypeNode *type,const Value &value,RecValue &rec)
 {
  if( level>MaxLevel ) GuardMapTooDeep(); 
  
  level++;
  
  ts_prepare.value=value;
  ts_prepare.rec=&rec;
  
  type->dispatch(ts_prepare);
  
  level--;
 }

void Map::prepare()
 {
  level=0;
  
  for(ulen i=0,n=eval->getConstCount(); i<n ;i++)
    {
     auto result=eval->getConstResult(i);
     
     prepare(result.type,result.value,const_buf[i]);
    }
 }

void Map::SizeSwitch::do_sint8(TypeNode_suint<imp_sint8> *) { info.set(sizeof (imp_sint8),Type_sint8); }
void Map::SizeSwitch::do_uint8(TypeNode_suint<imp_uint8> *) { info.set(sizeof (imp_uint8),Type_uint8); }

void Map::SizeSwitch::do_sint16(TypeNode_suint<imp_sint16> *) { info.set(sizeof (imp_sint16),Type_sint16); }
void Map::SizeSwitch::do_uint16(TypeNode_suint<imp_uint16> *) { info.set(sizeof (imp_uint16),Type_uint16); }

void Map::SizeSwitch::do_sint32(TypeNode_suint<imp_sint32> *) { info.set(sizeof (imp_sint32),Type_sint32); }
void Map::SizeSwitch::do_uint32(TypeNode_suint<imp_uint32> *) { info.set(sizeof (imp_uint32),Type_uint32); }

void Map::SizeSwitch::do_sint64(TypeNode_suint<imp_sint64> *) { info.set(sizeof (imp_sint64),Type_sint64); }
void Map::SizeSwitch::do_uint64(TypeNode_suint<imp_uint64> *) { info.set(sizeof (imp_uint64),Type_uint64); }

void Map::SizeSwitch::do_text(TypeNode_text *) { info.set(sizeof (StrLen),Type_text); }

void Map::SizeSwitch::do_ip(TypeNode_ip *) { info.set(sizeof (imp_uint32),Type_uint32); }

void Map::SizeSwitch::do_ptr(TypeNode_ptr *) { info.set(sizeof (DataPtr),Type_ptr); }

void Map::SizeSwitch::do_array(TypeNode_array *array_type) 
 {
  map->sizeOf(array_type->type_node);
  
  info.set(sizeof (ArrayPtr),Type_array_ptr); 
 }

void Map::SizeSwitch::do_array_len(TypeNode_array_len *array_type)
 {
  map->sizeOf(array_type->type_node);
  
  ulen len=array_type->len_node.index;
  
  info.size_of=MapMulLen(info.size_of,len);
 }

void Map::SizeSwitch::do_struct(StructNode *struct_node)
 {
  auto &rec=map->struct_buf[struct_node->index];
  
  if( rec.done )
    {
     info=rec;
    }
  else
    {
     ulen off=0;
     unsigned flags=0;
     
     for(FieldNode &node : struct_node->field_list )
       {
        SizeInfo s=map->sizeOf(node.type_node);
        
        off=AlignFor(off,s.flags);
        
        node.index=off;
        
        off=MapAddLen(off,s.size_of);
        
        flags|=s.flags;
       }
     
     info.size_of=AlignFor(off,flags);
     info.flags=flags;
     
     rec.set(info,struct_node);
     
     NameKey key(struct_node);
     StructAlgo::PrepareIns prepare(map->struct_map,key);
     
     if( prepare.found )
       {
        GuardMapStructNameDuplication();
       }
     else
       {
        prepare.complete(&rec);
       }
    }
 }

void Map::SizeSwitch::do_struct(TypeNode_struct *type)
 {
  do_struct(type->base_struct);
 }

void Map::SizeSwitch::do_ref(TypeNode_ref *type)
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

auto Map::sizeOf(TypeNode *type) -> SizeInfo
 {
  type->dispatch(ts_size);
  
  type->index=ts_size.info.size_of;
  
  return ts_size.info;
 }

void Map::setLen()
 {
  for(ulen i=0,n=eval->getLenCount(); i<n ;i++)
    {
     auto result=eval->getLenResult(i);
     
     result.node->index=result.value;
    }
 }

void Map::setStruct()
 {
  ulen ind=0;
  
  for(StructNode &node : body->struct_list )
    {
     node.index=ind++;
    }
 }

void Map::sizeOf()
 {
  for(ulen i=0,n=eval->getConstCount(); i<n ;i++)
    {
     auto result=eval->getConstResult(i);
     
     const_buf[i].size_of=sizeOf(result.type).size_of;
    }
 }

void Map::PlaceSwitch::do_sint8(TypeNode_suint<imp_sint8> *) {}

void Map::PlaceSwitch::do_uint8(TypeNode_suint<imp_uint8> *) {}

void Map::PlaceSwitch::do_sint16(TypeNode_suint<imp_sint16> *) {}

void Map::PlaceSwitch::do_uint16(TypeNode_suint<imp_uint16> *) {}

void Map::PlaceSwitch::do_sint32(TypeNode_suint<imp_sint32> *) {}

void Map::PlaceSwitch::do_uint32(TypeNode_suint<imp_uint32> *) {}

void Map::PlaceSwitch::do_sint64(TypeNode_suint<imp_sint64> *) {}

void Map::PlaceSwitch::do_uint64(TypeNode_suint<imp_uint64> *) {}

void Map::PlaceSwitch::do_text(TypeNode_text *)
 {
  Text text=value.get<Text>();
  
  rec.elems->off=map->reserve(text.str.len);
 }

void Map::PlaceSwitch::do_ip(TypeNode_ip *) {}

void Map::PlaceSwitch::do_ptr(TypeNode_ptr *) {}

void Map::PlaceSwitch::do_array_type(ulen off,ulen delta,TypeNode *type)
 {
  PtrLen<Value> data=value.get<Block>().data;
  PtrLen<RecValue> elems=rec.elems;
  
  for(; +data ;++data,++elems,off+=delta) 
    {
     elems->off=off;
     
     map->place(type,*data,*elems);
    }
 }

void Map::PlaceSwitch::do_array(TypeNode_array *array_type)
 {
  TypeNode *type=array_type->type_node;
  
  ulen delta=type->index;
  ulen off=map->reserve(delta,rec.elems.len);
  
  do_array_type(off,delta,type);
 }

void Map::PlaceSwitch::do_array_len(TypeNode_array_len *array_type)
 {
  TypeNode *type=array_type->type_node;
  
  do_array_type(rec.off,type->index,type);
 }

void Map::PlaceSwitch::do_struct(StructNode *struct_node)
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

void Map::PlaceSwitch::do_struct(TypeNode_struct *type)
 {
  do_struct(type->base_struct);
 }

void Map::PlaceSwitch::do_ref(TypeNode_ref *type)
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

void Map::place(TypeNode *type,const Value &value,const RecValue &rec)
 {
  ts_place.value=value;
  ts_place.rec=rec;
  
  type->dispatch(ts_place);
 }

void Map::place()
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
     ConstAlgo::PrepareIns prepare(const_map,key);
     
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

ulen Map::reserve(ulen len)
 {
  if( !TryAlign(len) ) GuardMapLenOverflow();
  
  ulen ret=total;
  
  total=MapAddLen(total,len);
  
  return ret;
 }

ulen Map::reserve(ulen len,ulen count)
 {
  return reserve(MapMulLen(len,count));
 }

void Map::SetDesc(TypeDesc_struct_base &desc,RecStruct *rec)
 {
  desc.size_of=rec->size_of;
  
  auto cur=begin(rec->struct_node->field_list);
  
  for(auto r=Range(desc.fields,desc.field_count); +r ;++r,++cur) r->off=(*cur).index;
 }

void Map::MatchSwitch::do_sint8(TypeNode_suint<imp_sint8> *)
 {
  result = ( desc->tag==TypeTag_sint8 ) ;
 }

void Map::MatchSwitch::do_uint8(TypeNode_suint<imp_uint8> *)
 {
  result = ( desc->tag==TypeTag_uint8 ) ;
 }

void Map::MatchSwitch::do_sint16(TypeNode_suint<imp_sint16> *)
 {
  result = ( desc->tag==TypeTag_sint16 ) ;
 }

void Map::MatchSwitch::do_uint16(TypeNode_suint<imp_uint16> *)
 {
  result = ( desc->tag==TypeTag_uint16 ) ;
 }

void Map::MatchSwitch::do_sint32(TypeNode_suint<imp_sint32> *)
 {
  result = ( desc->tag==TypeTag_sint32 ) ;
 }

void Map::MatchSwitch::do_uint32(TypeNode_suint<imp_uint32> *)
 {
  result = ( desc->tag==TypeTag_uint32 ) ;
 }

void Map::MatchSwitch::do_sint64(TypeNode_suint<imp_sint64> *)
 {
  result = ( desc->tag==TypeTag_sint64 ) ;
 }

void Map::MatchSwitch::do_uint64(TypeNode_suint<imp_uint64> *)
 {
  result = ( desc->tag==TypeTag_uint64 ) ;
 }

void Map::MatchSwitch::do_text(TypeNode_text *)
 {
  result = ( desc->tag==TypeTag_text ) ;
 }

void Map::MatchSwitch::do_ip(TypeNode_ip *)
 {
  result = ( desc->tag==TypeTag_ip ) ;
 }

void Map::MatchSwitch::do_ptr(TypeNode_ptr *type)
 {
  if( desc->tag==TypeTag_ptr )
    {
     desc=&( static_cast<const TypeDesc_ptr *>(desc)->type );

     type->type_node->dispatch(*this);
    }
  else
    {
     result=false;
    }
 }

void Map::MatchSwitch::do_array(TypeNode_array *type)
 {
  if( desc->tag==TypeTag_array )
    {
     desc=&( static_cast<const TypeDesc_array *>(desc)->type );

     type->type_node->dispatch(*this);
    }
  else
    {
     result=false;
    }
 }

void Map::MatchSwitch::do_array_len(TypeNode_array_len *type)
 {
  switch( desc->tag )
    {
     case TypeTag_array_len :
      {
       const TypeDesc_array_len *ptr=static_cast<const TypeDesc_array_len *>(desc);
       
       if( type->len_node.index==ptr->len )
         {
          desc=&( ptr->type );

          type->type_node->dispatch(*this);
         }
       else
         {
          result=false;
         }
      }
     break;
     
     case TypeTag_array_getlen :
      {
       const TypeDesc_array_getlen *ptr=static_cast<const TypeDesc_array_getlen *>(desc);
       
       ptr->len=type->len_node.index;
       
       desc=&( ptr->type );

       type->type_node->dispatch(*this);
      }
     break;
     
     default:
      {
       result=false;
      }
    }
 }
  
void Map::MatchSwitch::do_struct(StructNode *struct_node)
 {
  if( desc->tag==TypeTag_struct )
    {
     const TypeDesc_struct_base *ptr=static_cast<const TypeDesc_struct_base *>(desc);
     
     if( ptr->lock )
       {
        result=( ptr->lock==struct_node->index+1 );
         
        return; 
       }
     else
      {
       ptr->lock=struct_node->index+1;
      }
     
     if( ptr->field_count==struct_node->field_list.count )
       {
        auto f=ptr->fields;
        
        for(FieldNode &field : struct_node->field_list )
          {
           desc=&( f->type );
           
           field.type_node->dispatch(*this);
           
           if( !result ) 
             {
              ptr->lock=0;
              
              return;
             }
           
           f->off=field.index;
           
           ++f;
          }
        
        ptr->size_of=map->struct_buf[struct_node->index].size_of;
        
        result=true;
       }
     else
       {
        ptr->lock=0;
        
        result=false;
       }
    }
  else
    {
     result=false;
    }
 }

void Map::MatchSwitch::do_struct(TypeNode_struct *type)
 {
  do_struct(type->base_struct);
 }

void Map::MatchSwitch::do_ref(TypeNode_ref *type)
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

bool Map::match(TypeNode *type,const TypeDesc &desc)
 {
  ts_match.desc=&desc;
  
  type->dispatch(ts_match);
  
  return ts_match.result;
 }

bool Map::match(StructNode *struct_node,const TypeDesc &desc)
 {
  ts_match.desc=&desc;
  
  ts_match.do_struct(struct_node);
  
  return ts_match.result;
 }

Map::Map(Eval *eval_,BodyNode *body_)
 : eval(eval_), 
   body(body_),
   const_buf(eval_->getConstCount()),
   struct_buf(body_->struct_list.count),
   base(0),
   ts_map(this),
   ts_prepare(this),
   ts_size(this),
   ts_place(this),
   ts_match(this)
 {
  prepare();
  
  setLen();
  
  setStruct();
  
  sizeOf();
  
  place();
 }

Map::~Map()
 {
 }

void Map::operator () (void *mem)
 {
  base=Place<void>(mem);
  
  for(ulen i=0,n=eval->getConstCount(); i<n ;i++)
    {
     auto result=eval->getConstResult(i);
     
     map(result.type,result.value,const_buf[i]);
    }
 }

bool Map::findStruct(StrLen name,TypeDesc &desc)
 {
  NameKey key(name);
  
  RecStruct *rec=struct_map.find(key);
  
  if( !rec ) return false;

  if( !match(rec->struct_node,desc) ) return false;
  
  SetDesc(static_cast<TypeDesc_struct_base &>(desc),rec);
  
  return true;
 }

void * Map::findConst(StrLen name,const TypeDesc &desc)
 {
  NameKey key(name);
  
  RecConst *rec=const_map.find(key);
  
  if( !rec ) return 0;
  
  if( !match(rec->type,desc) ) return 0; 
  
  return base+rec->off;
 }

} // namespace DDL
} // namespace CCore
