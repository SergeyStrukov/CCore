/* DDL2Value.h */
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

#ifndef CCore_inc_ddl2_DDL2Value_h
#define CCore_inc_ddl2_DDL2Value_h

#include <CCore/inc/ddl2/DDL2Types.h>
#include <CCore/inc/ddl2/DDL2Token.h>

namespace CCore {
namespace DDL2 {

/* forward */

struct TypeNode;

/* ...ToInt() */

template <class IntType>
IntType DecToInt(StrLen str)
 {
  IntType ret(0);
  
  for(; +str ;++str) ret=IntType(10)*ret+IntType(CharDecValue(*str)); 
  
  return ret;
 }

template <class IntType>
IntType BinToInt(StrLen str)
 {
  str.len--;
  
  IntType ret(0);
  
  for(; +str ;++str) ret=IntType(2)*ret+IntType(CharBinValue(*str)); 
  
  return ret;
 }

template <class IntType>
IntType HexToInt(StrLen str)
 {
  str.len--;
  
  IntType ret(0);
  
  for(; +str ;++str) ret=IntType(16)*ret+IntType(CharHexValue(*str)); 
  
  return ret;
 }

template <class IntType>
IntType StrToInt(const Token &token)
 {
  switch( token.tc )
    {
     case Token_Dec : return DecToInt<IntType>(token.str);
     case Token_Bin : return BinToInt<IntType>(token.str);
     case Token_Hex : return HexToInt<IntType>(token.str);
      
     default: return IntType(0);
    }
 }

/* DString functions */

ulen DStringLen(StrLen str);

void DString(StrLen str,char *out);

/* classes */

struct Block;

struct PtrNode;

struct Ptr;

union Value;

/* struct Block */

struct Block
 {
  PtrLen<Value> data;
  
  // constructors
  
  Block() {}
  
  Block(PtrLen<Value> data_) : data(data_) {}
 };

/* struct PtrNode */

struct PtrNode
 {
  PtrNode *parent;
  ulen_type index;
  TypeNode *type;
  
  // constructors
  
  explicit PtrNode(TypeNode *type_) : parent(0),index(0),type(type_) {}
  
  PtrNode(ulen_type index_,TypeNode *type_) : parent(0),index(index_),type(type_) {}
  
  PtrNode(PtrNode *parent_,ulen_type index_,TypeNode *type_) : parent(parent_),index(index_),type(type_) {}
  
  bool add(SLen delta)
   {
    if( delta.flag==SLen::Pos )
      {
       if( AddOverflow(index,delta.len) ) return false; 
      
       index+=delta.len;
      
       return true;
      }
    else
      {
       if( index<delta.len ) return false;
       
       index-=delta.len;
       
       return true;
      }
   }
 };

/* struct Ptr */

struct Ptr
 {
  PtrNode *ptr_node;
  bool null;
  bool locked;
  
  // constructors
  
  Ptr() : ptr_node(0),null(false),locked(false) {}
  
  Ptr(PtrNode *ptr_node_,bool null_) : ptr_node(ptr_node_),null(null_),locked(false) {}
  
  // methods
  
  bool operator ! () const { return !ptr_node; }
  
  bool add(SLen delta) { return ptr_node->add(delta); }
  
  TypeNode * getType() const { return ptr_node->type; }
  
  PtrNode * getParent() const { return ptr_node->parent; }
  
  ulen_type getIndex() const { return ptr_node->index; }
 };

/* union Value */

union Value
 {
  imp_sint8  val_sint8;
  imp_uint8  val_uint8;
  imp_sint16 val_sint16;
  imp_uint16 val_uint16;
  imp_sint32 val_sint32;
  imp_uint32 val_uint32;
  imp_sint64 val_sint64;
  imp_uint64 val_uint64;
  
  imp_sint   val_sint;
  imp_uint   val_uint;
  imp_ulen   val_ulen;
  
  SLen       val_slen;
  Text       val_text;
  IP         val_ip;
  
  Block      val_block;
  Ptr        val_ptr;
  
  // constructors
  
  Value() {}
  
  // methods
  
  template <class Type>
  Type get() const;
  
  template <class Type>
  void set(Type val);
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

template <>
inline imp_sint8 Value::get<imp_sint8>() const { return val_sint8; }

template <>
inline void Value::set<imp_sint8>(imp_sint8 val) { val_sint8=val; }

template <>
inline imp_uint8 Value::get<imp_uint8>() const { return val_uint8; }

template <>
inline void Value::set<imp_uint8>(imp_uint8 val) { val_uint8=val; }

template <>
inline imp_sint16 Value::get<imp_sint16>() const { return val_sint16; }

template <>
inline void Value::set<imp_sint16>(imp_sint16 val) { val_sint16=val; }

template <>
inline imp_uint16 Value::get<imp_uint16>() const { return val_uint16; }

template <>
inline void Value::set<imp_uint16>(imp_uint16 val) { val_uint16=val; }

template <>
inline imp_sint32 Value::get<imp_sint32>() const { return val_sint32; }

template <>
inline void Value::set<imp_sint32>(imp_sint32 val) { val_sint32=val; }

template <>
inline imp_uint32 Value::get<imp_uint32>() const { return val_uint32; }

template <>
inline void Value::set<imp_uint32>(imp_uint32 val) { val_uint32=val; }

template <>
inline imp_sint64 Value::get<imp_sint64>() const { return val_sint64; }

template <>
inline void Value::set<imp_sint64>(imp_sint64 val) { val_sint64=val; }

template <>
inline imp_uint64 Value::get<imp_uint64>() const { return val_uint64; }

template <>
inline void Value::set<imp_uint64>(imp_uint64 val) { val_uint64=val; }

template <>
inline imp_sint Value::get<imp_sint>() const { return val_sint; }

template <>
inline void Value::set<imp_sint>(imp_sint val) { val_sint=val; }

template <>
inline imp_uint Value::get<imp_uint>() const { return val_uint; }

template <>
inline void Value::set<imp_uint>(imp_uint val) { val_uint=val; }

template <>
inline imp_ulen Value::get<imp_ulen>() const { return val_ulen; }

template <>
inline void Value::set<imp_ulen>(imp_ulen val) { val_ulen=val; }

template <>
inline SLen Value::get<SLen>() const { return val_slen; }

template <>
inline void Value::set<SLen>(SLen val) { val_slen=val; }

template <>
inline Text Value::get<Text>() const { return val_text; }

template <>
inline void Value::set<Text>(Text val) { val_text=val; }

template <>
inline IP Value::get<IP>() const { return val_ip; }

template <>
inline void Value::set<IP>(IP val) { val_ip=val; }

template <>
inline Block Value::get<Block>() const { return val_block; }

template <>
inline void Value::set<Block>(Block val) { val_block=val; }

template <>
inline Ptr Value::get<Ptr>() const { return val_ptr; }

template <>
inline void Value::set<Ptr>(Ptr ptr) { val_ptr=ptr; }

} // namespace DDL2
} // namespace CCore

#endif

