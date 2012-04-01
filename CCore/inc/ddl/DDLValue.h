/* DDLValue.h */
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ddl_DDLValue_h
#define CCore_inc_ddl_DDLValue_h

#include <CCore/inc/ddl/DDLToken.h>
#include <CCore/inc/ddl/DDLSemantic.h>

namespace CCore {
namespace DDL {

/* ...ToInt() */

template <class Type>
Type DecToInt(StrLen str)
 {
  Type ret{};
  
  for(; +str ;++str) ret=Type(10)*ret+Type(CharDecValue(*str)); 
  
  return ret;
 }

template <class Type>
Type BinToInt(StrLen str)
 {
  str.len--;
  
  Type ret{};
  
  for(; +str ;++str) ret=Type(2)*ret+Type(CharBinValue(*str)); 
  
  return ret;
 }

template <class Type>
Type HexToInt(StrLen str)
 {
  str.len--;
  
  Type ret{};
  
  for(; +str ;++str) ret=Type(16)*ret+Type(CharHexValue(*str)); 
  
  return ret;
 }

template <class Type>
Type StrToInt(const Token &token)
 {
  switch( token.tc )
    {
     case Token_Dec : return DecToInt<Type>(token.str);
     case Token_Bin : return BinToInt<Type>(token.str);
     case Token_Hex : return HexToInt<Type>(token.str);
      
     default: return Type(0);
    }
 }

/* classes */

struct SLen;

struct Text;

struct IP;

struct PtrNode;

struct Ptr;

struct Block;

union Value;

/* struct SLen */

struct SLen
 {
  enum Flag
   {
    Pos,
    Neg,
    Error
   };
  
  imp_ulen len;
  Flag flag;
  
  // constructors
  
  SLen() 
   {
    len=0;
    flag=Pos;
   }
  
  SLen(Flag flag_,imp_ulen len_=0) 
   {
    len=len_;
    flag=flag_;
   }
  
  SLen(ulen index_a,ulen index_b)
   {
    if( index_a<index_b )
      {
       len=imp_ulen(index_b-index_a);
       flag=Neg;
      }
    else
      {
       len=imp_ulen(index_a-index_b);
       flag=Pos;
      }
   }
  
  // cast
  
  static imp_uint8 UCast(imp_uint8 val) { return val; }
  static imp_uint16 UCast(imp_uint16 val) { return val; }
  static imp_uint32 UCast(imp_uint32 val) { return val; }
  static imp_uint64 UCast(imp_uint64 val) { return val; }
  
  static imp_uint8 UCast(imp_sint8 val) { return val; }
  static imp_uint16 UCast(imp_sint16 val) { return val; }
  static imp_uint32 UCast(imp_sint32 val) { return val; }
  static imp_uint64 UCast(imp_sint64 val) { return val; }
  
  template <class Type>
  explicit SLen(Type val)
   {
    if( val<0 )
      {
       Type v=-val-1;
       
       if( UCast(v)>=imp_ulen(-1) )
         {
          flag=Error;
          len=0;
         }
       else
         {
          flag=Neg;
          len=imp_ulen(v)+1;
         }
      }
    else
      {
       if( UCast(val)>imp_ulen(-1) )
         {
          flag=Error;
          len=0;
         }
       else
         {
          flag=Pos;
          len=imp_ulen(val);
         }
      }
   }
  
  template <class Type>
  explicit operator Type() const
   {
    return (flag==Pos)?Type(len):Type(-Type(len));
   }
  
  // operators
  
  bool noError() const { return flag!=Error; }
  
  bool operator ! () const { return !len; }
  
  SLen operator - () const 
   { 
    switch( flag )
      {
       case Pos : return SLen(Neg,len);
       case Neg : return SLen(Pos,len);
       
       default : return Error;
      }
   }
  
  friend SLen operator + (SLen a,SLen b)
   {
    if( a.flag==Error || b.flag==Error ) return Error;
    
    if( a.flag==Neg )
      {
       if( b.flag==Neg )
         {
          if( a.len>imp_ulen(-1)-b.len ) return Error;
          
          return SLen(Neg,a.len+b.len);
         }
       else
         {
          if( a.len>b.len )
            return SLen(Neg,a.len-b.len);
          else
            return SLen(Pos,b.len-a.len);
         }
      }
    else
      {
       if( b.flag==Neg )
         {
          if( a.len>=b.len )
            return SLen(Pos,a.len-b.len);
          else
            return SLen(Neg,b.len-a.len);
         }
       else
         {
          if( a.len>imp_ulen(-1)-b.len ) return Error;
          
          return SLen(Pos,a.len+b.len);
         }
      }
   }
  
  friend SLen operator - (SLen a,SLen b) { return a+(-b); }
  
  friend SLen operator * (SLen a,SLen b)
   {
    if( a.flag==Error || b.flag==Error ) return Error;
    
    if( a.len && b.len>imp_ulen(-1)/a.len ) return Error; 
    
    return SLen( ((a.flag!=b.flag)?Neg:Pos) ,a.len*b.len);
   }
  
  friend SLen operator / (SLen a,SLen b)
   {
    if( a.flag==Error || b.flag==Error ) return Error;
    
    return SLen( ((a.flag!=b.flag)?Neg:Pos) ,a.len/b.len);
   }
  
  friend SLen operator % (SLen a,SLen b)
   {
    if( a.flag==Error || b.flag==Error ) return Error;
    
    return SLen( a.flag ,a.len%b.len);
   }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    switch( flag )
      {
       case Neg : out.put('-'); // falldown;
       
       case Pos : Putobj(out,len); break;
       
       case Error : Putobj(out,"<error>"); 
      }
   }
 };

/* struct Text */

struct Text
 {
  StrLen str;
  
  // constructors
  
  Text() {}
  
  Text(StrLen str_) : str(str_) {}
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Putobj(out,str);
   }
 };

/* struct IP */

struct IP
 {
  uint8 b[4];
  
  // constructors
  
  explicit IP() : b{} {}
  
  IP(uint8 b1,uint8 b2,uint8 b3,uint8 b4) 
   {
    b[0]=b1;
    b[1]=b2;
    b[2]=b3;
    b[3]=b4;
   }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#;.#;.#;.#;",b[0],b[1],b[2],b[3]);
   }
 };

/* struct PtrNode */

struct PtrNode
 {
  TypeNode *type; // type of base , Ptr(type,base) is a poiner to the parent object
  PtrNode *base;
  ulen index;
  bool no_array; // type is not an array type
  
  Value *ptr;
  ExprNode *node;
  
  PtrNode(ulen index_,ExprNode *node_) // &const 
   : type(0),
     base(0),
     index(index_),
     no_array(true),
     ptr(0),
     node(node_) 
   {
   }
  
  PtrNode(TypeNode *type_,PtrNode *base_,ulen index_,ExprNode *node_) // struct field
   : type(type_),
     base(base_),
     index(index_),
     no_array(true),
     ptr(0),
     node(node_) 
   {
   }
  
  PtrNode(TypeNode *type_,PtrNode *base_,ExprNode *node_) // decay 
   : type(type_),
     base(base_),
     index(0),
     no_array(false),
     ptr(0),
     node(node_) 
   {
   }
  
  PtrNode(PtrNode *ptr_node,ulen index_,ExprNode *node_) // another index 
   : type(ptr_node->type),
     base(ptr_node->base),
     index(index_),
     no_array(false),
     ptr(0),
     node(node_) 
   {
   }
 };

/* struct Ptr */

struct Ptr
 {
  TypeNode *type;
  PtrNode *node;
  
  // constructors
  
  explicit Ptr(TypeNode *type_) : type(type_),node(0) {}
  
  Ptr(TypeNode *type_,PtrNode *node_) : type(type_),node(node_) {}
  
  // methods
  
  bool isError() const { return !type; }
  
  bool operator ! () const { return !node; }
  
  Value & operator * () const;
 };

/* struct Block */

struct Block
 {
  PtrLen<Value> data;
  
  Block() {}
  
  explicit Block(PtrLen<Value> data_) : data(data_) {}
  
  void init(PtrLen<Value> prefix,const Value &value) const;
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
  
  SLen       val_slen;
  Text       val_text;
  IP         val_ip;
  
  Block      val_block;
  Ptr        val_ptr;
  
  Value() {}
  
  void copy(const Value &val) { *this=val; }
  
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

/* inlines */

/* struct Ptr */

inline Value & Ptr::operator * () const { return *node->ptr; }

/* struct Block */

inline void Block::init(PtrLen<Value> prefix,const Value &value) const
 {
  prefix.copyTo(data.ptr);
  
  data.part(prefix.len).set(value);
 }

} // namespace DDL
} // namespace CCore

#endif

