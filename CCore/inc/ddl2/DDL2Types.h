/* DDL2Types.h */
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

#ifndef CCore_inc_ddl2_DDL2Types_h
#define CCore_inc_ddl2_DDL2Types_h

#include <CCore/inc/Printf.h>
#include <CCore/inc/Array.h>

#include <CCore/inc/ddl2/DDL2PlatformTypes.h>

namespace CCore {
namespace DDL2 {

/* functions */

template <class UInt>
bool AddOverflow(UInt a,UInt b)
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::DDL2::AddOverflow(UInt,UInt) : UInt must be an unsigned integral type");
  
  return a>UInt(-1)-b;
 }

template <class UInt>
bool MulOverflow(UInt a,UInt b)
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::DDL2::MulOverflow(UInt,UInt) : UInt must be an unsigned integral type");
  
  return a && b>UInt(-1)/a ;
 }

template <class UInt,class S>
bool CastOverflow(UInt &a,S b)
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::DDL2::CastOverflow(UInt &,S) : UInt must be an unsigned integral type");
  static_assert( Meta::IsUInt<S>::Ret ,"CCore::DDL2::CastOverflow(UInt &,S) : S must be an unsigned integral type");

  if( b<=UInt(-1) )
    {
     a=(UInt)b;
    
     return false;
    }
  else
    {
     a=0;
     
     return true;
    }
 }

/* classes */

template <class T,class SUInt> struct IntType;

struct Text;

struct IP;

struct SLen;

/* struct IntType<T,SUInt> */

template <class T,class SUInt>
struct IntType : NoThrowFlagsBase
 {
  using ValueType = SUInt ;
 
  SUInt value;
  
  // methods
  
  bool operator ! () const { return !value; }
  
  template <class S>
  void cast(S value_) 
   {
    static_assert( Meta::IsSUInt<S>::Ret ,"CCore::DDL2::IntType::cast(S) : S must be an integral type");
    
    value=(SUInt)value_; 
   }
  
  template <class ExtIntType>
  ExtIntType castTo() const { return ExtIntType(value); }
  
  // operators
  
  friend T operator - (T a) { return T(-a.value); }
  
  friend T operator + (T a,T b) { return T(a.value+b.value); } 
  
  friend T operator - (T a,T b) { return T(a.value-b.value); }
  
  friend T operator * (T a,T b) { return T(a.value*b.value); }
  
  struct RetType
   {
    T value;
    bool ok;
    
    bool operator ! () const { return !ok; }
   };
  
  friend RetType operator / (T a,T b) 
   { 
    if( b.value )
      return {T(a.value/b.value),true};
    else
      return {T(0),false}; 
   }
  
  friend RetType operator % (T a,T b) 
   { 
    if( b.value )
      return {T(a.value%b.value),true};
    else
      return {T(0),false}; 
   }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Putobj(out,value);
   }
 };

/* int types */

struct imp_sint8 : IntType<imp_sint8,sint8>
 {
  imp_sint8() { cast(0); }
  
  template <class S>
  explicit imp_sint8(S value) { cast(value); }
 };

struct imp_uint8 : IntType<imp_uint8,uint8>
 {
  imp_uint8() { cast(0); }
  
  template <class S>
  explicit imp_uint8(S value) { cast(value); }
 };

struct imp_sint16 : IntType<imp_sint16,sint16>
 {
  imp_sint16() { cast(0); }
  
  template <class S>
  explicit imp_sint16(S value) { cast(value); }
 };

struct imp_uint16 : IntType<imp_uint16,uint16>
 {
  imp_uint16() { cast(0); }
  
  template <class S>
  explicit imp_uint16(S value) { cast(value); }
 };

struct imp_sint32 : IntType<imp_sint32,sint32>
 {
  imp_sint32() { cast(0); }
  
  template <class S>
  explicit imp_sint32(S value) { cast(value); }
 };

struct imp_uint32 : IntType<imp_uint32,uint32>
 {
  imp_uint32() { cast(0); }
  
  template <class S>
  explicit imp_uint32(S value) { cast(value); }
 };

struct imp_sint64 : IntType<imp_sint64,sint64>
 {
  imp_sint64() { cast(0); }
  
  template <class S>
  explicit imp_sint64(S value) { cast(value); }
 };

struct imp_uint64 : IntType<imp_uint64,uint64>
 {
  imp_uint64() { cast(0); }
  
  template <class S>
  explicit imp_uint64(S value) { cast(value); }
 };

struct imp_sint : IntType<imp_sint,sint_type>
 {
  imp_sint() { cast(0); }
  
  template <class S>
  explicit imp_sint(S value) { cast(value); }
 };

struct imp_uint : IntType<imp_uint,uint_type>
 {
  imp_uint() { cast(0); }
  
  template <class S>
  explicit imp_uint(S value) { cast(value); }
 };

struct imp_ulen : IntType<imp_ulen,ulen_type>
 {
  imp_ulen() { cast(0); }
  
  template <class S>
  explicit imp_ulen(S value) { cast(value); }
 };

using imp_int = imp_sint ;

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
  uint8 address[4];
  
  // constructors
  
  IP() : address{} {}
  
  IP(uint8 a1,uint8 a2,uint8 a3,uint8 a4) : address{a1,a2,a3,a4} {}
  
  // methods
  
  uint32 toInt() const
   {
    uint32 a1=address[0];
    uint32 a2=address[1];
    uint32 a3=address[2];
    uint32 a4=address[3];
    
    return uint32( (a1<<24)|(a2<<16)|(a3<<8)|a4 );
   }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#;.#;.#;.#;",address[0],address[1],address[2],address[3]);
   }
 };

/* struct SLen */

struct SLen
 {
  enum Flag
   {
    Pos,
    Neg,
    Error
   };
  
  ulen_type len;
  Flag flag;
  
  // constructors
  
  SLen()
   {
    flag=Pos;
    len=0;
   }
  
  SLen(Flag flag_)
   {
    flag=flag_;
    len=0;
   }
  
  SLen(Flag flag_,ulen_type len_)
   {
    flag=flag_;
    len=len_;
   }
  
  SLen(ulen_type index_a,ulen_type index_b)
   {
    if( index_a<index_b )
      {
       flag=Neg;
       len=index_b-index_a;
      }
    else
      {
       flag=Pos;
       len=index_a-index_b;
      }
   }
  
  // cast
  
  template <class UInt>
  void cast_uint(UInt value,Flag flag_)
   {
    if( CastOverflow(len,value) )
      flag=Error;
    else
      flag=flag_;
   }
  
  template <class UInt,class SInt>
  void cast_sint(SInt value)
   {
    if( value<0 )
      {
       cast_uint<UInt>(UIntFunc<UInt>::Neg(value),Neg);
      }
    else
      {
       cast_uint<UInt>(value,Pos);
      }
   }
  
  void cast(uint8 value) { cast_uint(value,Pos); }
  void cast(uint16 value) { cast_uint(value,Pos); }
  void cast(uint32 value) { cast_uint(value,Pos); }
  void cast(uint64 value) { cast_uint(value,Pos); }
  
  void cast(sint8 value) { cast_sint<uint8>(value); }
  void cast(sint16 value) { cast_sint<uint16>(value); }
  void cast(sint32 value) { cast_sint<uint32>(value); }
  void cast(sint64 value) { cast_sint<uint64>(value); }
  
  explicit SLen(int value) 
   {
    cast_sint<unsigned>(value); 
   }
  
  template <class S>
  explicit SLen(S value) 
   {
    static_assert( Meta::IsSUInt<S>::Ret ,"CCore::DDL2::SLen::SLen(S) : S must be an integral type");
    
    cast(value); 
   }
  
  template <class IntType>
  IntType castTo() const
   {
    return (flag==Neg)?-IntType(len):IntType(len);
   }
  
  // methods
  
  bool operator ! () const { return !len; }
  
  bool noError() const { return flag!=Error; }
  
  // operators
  
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
          if( AddOverflow(a.len,b.len) ) return Error;
          
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
          if( AddOverflow(a.len,b.len) ) return Error;
          
          return SLen(Pos,a.len+b.len);
         }
      }
   }
  
  friend SLen operator - (SLen a,SLen b) { return a+(-b); }
  
  friend SLen operator * (SLen a,SLen b)
   {
    if( a.flag==Error || b.flag==Error ) return Error;
    
    if( MulOverflow(a.len,b.len) ) return Error; 
    
    return SLen( ((a.flag!=b.flag)?Neg:Pos) , a.len*b.len );
   }
  
  friend SLen operator / (SLen a,SLen b)
   {
    if( a.flag==Error || b.flag==Error ) return Error;
    
    if( !b.len ) return Error;
    
    return SLen( ((a.flag!=b.flag)?Neg:Pos) , a.len/b.len );
   }
  
  friend SLen operator % (SLen a,SLen b)
   {
    if( a.flag==Error || b.flag==Error ) return Error;
    
    if( !b.len ) return Error;
    
    return SLen( a.flag , a.len%b.len );
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

} // namespace DDL2
} // namespace CCore

#endif


