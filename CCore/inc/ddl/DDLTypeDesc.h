/* DDLTypeDesc.h */
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

#ifndef CCore_inc_ddl_DDLTypeDesc_h
#define CCore_inc_ddl_DDLTypeDesc_h

#include <CCore/inc/ddl/DDLTypes.h>

namespace CCore {
namespace DDL {

/* consts */

enum TypeTag
 {
  TypeTag_sint8,
  TypeTag_uint8,
  
  TypeTag_sint16,
  TypeTag_uint16,
  
  TypeTag_sint32,
  TypeTag_uint32,
  
  TypeTag_sint64,
  TypeTag_uint64,
  
  TypeTag_text,
  TypeTag_ip,
  
  TypeTag_ptr,
  TypeTag_array,
  TypeTag_array_len,
  TypeTag_array_getlen,
  
  TypeTag_struct,
  
  // size-less types 
  
  TypeTag_sint = (std::is_same<imp_sint,imp_sint32>::value)?TypeTag_sint32:TypeTag_sint64 ,
  TypeTag_uint = (std::is_same<imp_uint,imp_uint32>::value)?TypeTag_uint32:TypeTag_uint64 ,
  TypeTag_ulen = (std::is_same<imp_ulen,imp_uint32>::value)?TypeTag_uint32:TypeTag_uint64 ,
   
  TypeTag_int = TypeTag_sint 
 };

/* classes */

struct TypeDesc;

struct TypeDesc_basic;

struct TypeDesc_ptr;

struct TypeDesc_array;

struct TypeDesc_array_len;

struct TypeDesc_array_getlen;

struct TypeDesc_struct_base;

template <ulen FieldCount> struct TypeDesc_struct;

struct ArrayPtr;

template <class T> struct ExtractData;

struct DataPtr;

/* struct TypeDesc */

struct TypeDesc
 {
  TypeTag tag;
 };

/* struct TypeDesc_basic */

struct TypeDesc_basic : TypeDesc
 {
  explicit TypeDesc_basic(TypeTag tag_) { tag=tag_; }
 };

/* struct TypeDesc_ptr */

struct TypeDesc_ptr : TypeDesc
 {
  const TypeDesc &type;
  
  explicit TypeDesc_ptr(const TypeDesc &type_) : type(type_) { tag=TypeTag_ptr; }
 };

/* struct TypeDesc_array */

struct TypeDesc_array : TypeDesc
 {
  const TypeDesc &type;
  
  explicit TypeDesc_array(const TypeDesc &type_) : type(type_) { tag=TypeTag_array; }
 };

/* struct TypeDesc_array_len */

struct TypeDesc_array_len : TypeDesc
 {
  const TypeDesc &type;
  ulen len;
  
  TypeDesc_array_len(const TypeDesc &type_,ulen len_) : type(type_),len(len_) { tag=TypeTag_array_len; }
 };

/* struct TypeDesc_array_getlen */

struct TypeDesc_array_getlen : TypeDesc
 {
  const TypeDesc &type;
  mutable ulen len;
  
  explicit TypeDesc_array_getlen(const TypeDesc &type_) : type(type_),len(0) { tag=TypeTag_array_getlen; }
 };

/* struct TypeDesc_struct_base */

struct TypeDesc_struct_base : TypeDesc
 {
  struct Field
   {
    const TypeDesc &type;
    mutable ulen off;
    
    Field(const TypeDesc &type_) : type(type_),off(0) {}
   };
  
  ulen field_count;
  mutable ulen size_of;
  mutable ulen lock;
  const Field *const fields;
  
  explicit TypeDesc_struct_base(const Field *fields_) : size_of(0),lock(0),fields(fields_) {}
 };

/* struct TypeDesc_struct<ulen FieldCount> */

template <ulen FieldCount> 
struct TypeDesc_struct : TypeDesc_struct_base
 {
  Field buf[FieldCount];
  
  template <class ... TT>
  TypeDesc_struct(const TT & ... tt) : TypeDesc_struct_base(buf),buf{tt...} { tag=TypeTag_struct; field_count=FieldCount; }
 };

/* struct ArrayPtr */ 

struct ArrayPtr
 {
  void *ptr;
  ulen len;

  ArrayPtr() : ptr(0),len(0) {}
  
  ArrayPtr(void *ptr_,ulen len_) : ptr(ptr_),len(len_) {}
 };

/* struct ExtractData<T> */

template <class T> 
struct ExtractData
 {
  static T Do(void *ptr) { return *static_cast<T *>(ptr); }
 };

template <class T> 
struct ExtractData<PtrLen<T> >
 {
  static PtrLen<T> Do(void *ptr) 
   { 
    ArrayPtr a=*static_cast<ArrayPtr *>(ptr);
    
    return Range(static_cast<T *>(a.ptr),a.len);
   }
 };

/* struct DataPtr */

struct DataPtr
 {
  void *ptr;
  
  // constructors
  
  DataPtr() : ptr(0) {}
  
  DataPtr(void *ptr_) : ptr(ptr_) {}
  
  // methods
  
  bool operator ! () const { return !ptr; }
  
  struct Proxy
   {
    void *ptr;
    
    Proxy(void *ptr_) : ptr(ptr_) {}
    
    template <class T> 
    operator T() const { return ExtractData<T>::Do(ptr); }
   };
  
  Proxy operator * () const { return ptr; }
  
  DataPtr elem(const TypeDesc_struct_base &desc,ulen ind) const { return PtrAdd(ptr,ind*desc.size_of); }
  
  DataPtr select(const TypeDesc_struct_base &desc,ulen ind) const { return PtrAdd(ptr,desc.fields[ind].off); }
  
  struct ProxyRange
   {
    void *ptr;
    ulen len;
    
    ProxyRange(void *ptr_,ulen len_) : ptr(ptr_),len(len_) {}
    
    template <class T> 
    operator PtrLen<T>() const { return PtrLen<T>(static_cast<T *>(ptr),len); }
   };
  
  ProxyRange range(ulen len) const { return ProxyRange(ptr,len); }
 };

} // namespace DDL
} // namespace CCore

#endif


