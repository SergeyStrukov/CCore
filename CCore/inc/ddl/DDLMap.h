/* DDLMap.h */
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

#ifndef CCore_inc_ddl_DDLMap_h
#define CCore_inc_ddl_DDLMap_h

#include <CCore/inc/ddl/DDLEval.h>
#include <CCore/inc/ddl/DDLTypeDesc.h>

namespace CCore {
namespace DDL {

/* functions */

inline imp_uint32 MapIP(IP val)
 {  
  imp_uint32 b1=val.b[0];
  imp_uint32 b2=val.b[1];
  imp_uint32 b3=val.b[2];
  imp_uint32 b4=val.b[3];
  
  return imp_uint32( (b1<<24)|(b2<<16)|(b3<<8)|b4 );
 }

/* classes */

struct NameKey;

class Map;

class MapBase;

/* struct NameKey */

struct NameKey
 {
  StrLen name;
  ScopeNode *parent;
  uint32 hash;
  
  // private
  
  struct Cur;
  
  Cur getCur() const;
  
  void setHash();
  
  // constructors
  
  NameKey() : parent(0),hash(0) {}
  
  template <class T>
  explicit NameKey(T *node) : name(node->name.name.token.str),parent(node->parent) { setHash(); }
  
  explicit NameKey(const StrLen &name_) : name(name_),parent(0) { setHash(); }
  
  // cmp objects 
  
  CmpResult objCmp(const NameKey &obj) const;
 };

/* class Map */

class Map : NoCopy
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
     ulen size_of;
     
     RBTreeLink<RecConst,NameKey> link;
     
     RecConst() : size_of(0) {}
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
   
   enum TypeFlags
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
     Type_array_ptr
    };
   
   struct SizeInfo
    {
     ulen size_of;
     unsigned flags;
     
     SizeInfo() : size_of(0),flags(0) {}

     SizeInfo(ulen size_of_,TypeFlags flag) { set(size_of_,flag); }
     
     void set(ulen size_of_,TypeFlags flag)
      {
       size_of=size_of_;
       flags=1u<<flag;
      }
     
     void setInfo(const SizeInfo &obj) { *this=obj; }
    };
   
   struct RecStruct : SizeInfo
    {
     StructNode *struct_node;
     bool done;
     
     RBTreeLink<RecStruct,NameKey> link;
     
     RecStruct() : done(false) {}
     
     void set(const SizeInfo &obj,StructNode *struct_node_)
      {
       setInfo(obj);
       
       struct_node=struct_node_;
       done=true;
      }
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
   
   static ulen AddLen(ulen a,ulen b);
   
   static ulen MulLen(ulen a,ulen b);
   
   template <ulen N> class AlignMulTable;
   
   template <class T>
   static ulen AlignAdd(ulen a);
   
   static ulen AlignOf(unsigned flags);
   
   static ulen AlignFor(ulen off,unsigned flags);
   
  private: 
   
   Eval *eval;
   BodyNode *body;
   
   DynArray<RecConst> const_buf;
   Collector<RecValue> rec_buf;
   DynArray<RecStruct> struct_buf;
   
   typedef RBTreeLink<RecConst,NameKey>::Algo<&RecConst::link> ConstAlgo; 
   typedef RBTreeLink<RecStruct,NameKey>::Algo<&RecStruct::link> StructAlgo; 
   
   ConstAlgo::Root const_map;
   StructAlgo::Root struct_map;
   
   ulen total;
   Place<void> base;
   
  private:
   
   struct MapSwitch : TypeSwitch
    {
     Map *map;
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
     
     explicit MapSwitch(Map *map_) : TypeSwitch(this),map(map_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *);
     void do_uint8(TypeNode_suint<imp_uint8> *);

     void do_sint16(TypeNode_suint<imp_sint16> *);
     void do_uint16(TypeNode_suint<imp_uint16> *);

     void do_sint32(TypeNode_suint<imp_sint32> *);
     void do_uint32(TypeNode_suint<imp_uint32> *);

     void do_sint64(TypeNode_suint<imp_sint64> *);
     void do_uint64(TypeNode_suint<imp_uint64> *);

     void do_text(TypeNode_text *);
     void do_ip(TypeNode_ip *);

     void do_ptr(TypeNode_ptr *);
     void do_array(TypeNode_array *);
     void do_array_len(TypeNode_array_len *);
     void do_struct(StructNode *);
     void do_struct(TypeNode_struct *);

     void do_ref(TypeNode_ref *);
    };
   
   MapSwitch ts_map;
   
   void map(TypeNode *type,const Value &value,const RecValue &rec);
   
   const RecValue & getRec(PtrNode *node);
   
   DataPtr mapPtr(Ptr ptr);
   
  private:

   struct PrepareSwitch : TypeSwitch
    {
     Map *map;
     Value value;
     RecValue *rec;
     
     explicit PrepareSwitch(Map *map_) : TypeSwitch(this),map(map_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *);
     void do_uint8(TypeNode_suint<imp_uint8> *);

     void do_sint16(TypeNode_suint<imp_sint16> *);
     void do_uint16(TypeNode_suint<imp_uint16> *);

     void do_sint32(TypeNode_suint<imp_sint32> *);
     void do_uint32(TypeNode_suint<imp_uint32> *);

     void do_sint64(TypeNode_suint<imp_sint64> *);
     void do_uint64(TypeNode_suint<imp_uint64> *);

     void do_text(TypeNode_text *);
     void do_ip(TypeNode_ip *);

     void do_ptr(TypeNode_ptr *);
     void do_array_type(TypeNode *type);
     void do_array(TypeNode_array *);
     void do_array_len(TypeNode_array_len *);
     void do_struct(StructNode *);
     void do_struct(TypeNode_struct *);

     void do_ref(TypeNode_ref *);
    };
   
   PrepareSwitch ts_prepare;
   ulen level;
   
   void prepare(TypeNode *type,const Value &value,RecValue &rec);
   
   void prepare();
   
  private:
   
   struct SizeSwitch : TypeSwitch
    {
     Map *map;
     SizeInfo info;
     
     explicit SizeSwitch(Map *map_) : TypeSwitch(this),map(map_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *);
     void do_uint8(TypeNode_suint<imp_uint8> *);

     void do_sint16(TypeNode_suint<imp_sint16> *);
     void do_uint16(TypeNode_suint<imp_uint16> *);

     void do_sint32(TypeNode_suint<imp_sint32> *);
     void do_uint32(TypeNode_suint<imp_uint32> *);

     void do_sint64(TypeNode_suint<imp_sint64> *);
     void do_uint64(TypeNode_suint<imp_uint64> *);

     void do_text(TypeNode_text *);
     void do_ip(TypeNode_ip *);

     void do_ptr(TypeNode_ptr *);
     void do_array(TypeNode_array *);
     void do_array_len(TypeNode_array_len *);
     void do_struct(StructNode *);
     void do_struct(TypeNode_struct *);

     void do_ref(TypeNode_ref *);
    };
   
   SizeSwitch ts_size;
   
   SizeInfo sizeOf(TypeNode *type);
   
   void setLen();
   
   void setStruct();
   
   void sizeOf();
   
  private:

   struct PlaceSwitch : TypeSwitch
    {
     Map *map;
     Value value;
     RecValue rec;
     
     explicit PlaceSwitch(Map *map_) : TypeSwitch(this),map(map_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *);
     void do_uint8(TypeNode_suint<imp_uint8> *);

     void do_sint16(TypeNode_suint<imp_sint16> *);
     void do_uint16(TypeNode_suint<imp_uint16> *);

     void do_sint32(TypeNode_suint<imp_sint32> *);
     void do_uint32(TypeNode_suint<imp_uint32> *);

     void do_sint64(TypeNode_suint<imp_sint64> *);
     void do_uint64(TypeNode_suint<imp_uint64> *);

     void do_text(TypeNode_text *);
     void do_ip(TypeNode_ip *);

     void do_ptr(TypeNode_ptr *);
     void do_array_type(ulen off,ulen delta,TypeNode *type);
     void do_array(TypeNode_array *);
     void do_array_len(TypeNode_array_len *);
     void do_struct(StructNode *);
     void do_struct(TypeNode_struct *);

     void do_ref(TypeNode_ref *);
    };
   
   PlaceSwitch ts_place;
   
   void place(TypeNode *type,const Value &value,const RecValue &rec);
   
   void place();
   
   ulen reserve(ulen len);
   
   ulen reserve(ulen len,ulen count);
   
   void reserve(RecConst &rec) { rec.off=reserve(rec.size_of); }
   
  private: 
   
   static void SetDesc(TypeDesc_struct_base &desc,RecStruct *rec);
  
   struct MatchSwitch : TypeSwitch
    {
     Map *map;
     const TypeDesc *desc;
     bool result;
     
     explicit MatchSwitch(Map *map_) : TypeSwitch(this),map(map_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *);
     void do_uint8(TypeNode_suint<imp_uint8> *);

     void do_sint16(TypeNode_suint<imp_sint16> *);
     void do_uint16(TypeNode_suint<imp_uint16> *);

     void do_sint32(TypeNode_suint<imp_sint32> *);
     void do_uint32(TypeNode_suint<imp_uint32> *);

     void do_sint64(TypeNode_suint<imp_sint64> *);
     void do_uint64(TypeNode_suint<imp_uint64> *);

     void do_text(TypeNode_text *);
     void do_ip(TypeNode_ip *);

     void do_ptr(TypeNode_ptr *);
     void do_array(TypeNode_array *);
     void do_array_len(TypeNode_array_len *);
     void do_struct(StructNode *);
     void do_struct(TypeNode_struct *);

     void do_ref(TypeNode_ref *);
    };
   
   MatchSwitch ts_match;
   
   bool match(TypeNode *type,const TypeDesc &desc);

   bool match(StructNode *struct_node,const TypeDesc &desc);

  public:
   
   Map(Eval *eval,BodyNode *body);
   
   ~Map();
   
   ulen getLen() const { return total; }
   
   void operator () (void *mem);
   
   bool findStruct(StrLen name,TypeDesc &desc); 
   
   void * findConst(StrLen name,const TypeDesc &desc);
 };

/* class MapBase */

class MapBase : NoCopy
 {
   void *mem;
  
  public:
   
   explicit MapBase(Map &map)
    {
     mem=MemAlloc(map.getLen());
     
     map(mem);
    }
   
   ~MapBase()
    {
     MemFree(mem);
    }
 };

} // namespace DDL
} // namespace CCore

#endif


