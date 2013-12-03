/* DDL2TypeDesc.h */ 
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

#ifndef CCore_inc_ddl2_DDL2TypeDesc_h
#define CCore_inc_ddl2_DDL2TypeDesc_h

#include <CCore/inc/ddl2/DDL2Types.h>
 
namespace CCore {
namespace DDL2 {

/* consts */

enum TypeTag
 {
  TypeTag_sint,
  TypeTag_uint,
  TypeTag_ulen,
  
  TypeTag_int = TypeTag_sint, 
 
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
  TypeTag_polyptr,
  TypeTag_array,
  TypeTag_array_len,
  TypeTag_array_getlen,
  
  TypeTag_struct,
  TypeTag_none
 };

/* classes */

struct TypeDesc;

struct TypeDesc_basic;

struct TypeDesc_ptr;

struct TypeDesc_polyptr_base;

template <ulen TypeCount> struct TypeDesc_polyptr;

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
  const TypeTag tag;
  
  explicit TypeDesc(const TypeTag tag_) : tag(tag_) {}
 };

/* struct TypeDesc_basic */

struct TypeDesc_basic : TypeDesc
 {
  explicit TypeDesc_basic(TypeTag tag) : TypeDesc(tag) {}
 };

/* struct TypeDesc_ptr */

struct TypeDesc_ptr : TypeDesc
 {
  const TypeDesc &type;
  
  explicit TypeDesc_ptr(const TypeDesc &type_) : TypeDesc(TypeTag_ptr),type(type_) {}
 };

/* struct TypeDesc_polyptr_base */

struct TypeDesc_polyptr_base : TypeDesc
 {
  struct Type
   {
    const TypeDesc &type;
    
    Type(const TypeDesc &type_) : type(type_) {}
   };
  
  const Type *const types;
  const ulen type_count;
  
  TypeDesc_polyptr_base(const Type *const types_,ulen type_count_) 
   : TypeDesc(TypeTag_polyptr),types(types_),type_count(type_count_) {}
 };

/* struct TypeDesc_polyptr<ulen TypeCount> */

template <ulen TypeCount> 
struct TypeDesc_polyptr : TypeDesc_polyptr_base
 {
  const Type buf[TypeCount];
 
  template <class ... TT>
  explicit TypeDesc_polyptr(const TT & ... tt) : TypeDesc_polyptr_base(buf,TypeCount),buf{tt...} {}
 };

/* struct TypeDesc_array */

struct TypeDesc_array : TypeDesc
 {
  const TypeDesc &type;
  
  explicit TypeDesc_array(const TypeDesc &type_) : TypeDesc(TypeTag_array),type(type_) {}
 };

/* struct TypeDesc_array_len */

struct TypeDesc_array_len : TypeDesc
 {
  const TypeDesc &type;
  const ulen_type len;
  
  TypeDesc_array_len(const TypeDesc &type_,ulen_type len_) : TypeDesc(TypeTag_array_len),type(type_),len(len_) {}
 };

/* struct TypeDesc_array_getlen */

struct TypeDesc_array_getlen : TypeDesc
 {
  const TypeDesc &type;
  mutable ulen_type len; // filled by getConst() method
  
  explicit TypeDesc_array_getlen(const TypeDesc &type_) : TypeDesc(TypeTag_array_getlen),type(type_),len(0) {}
 };

/* struct TypeDesc_struct_base */

struct TypeDesc_struct_base : TypeDesc
 {
  struct Field
   {
    const TypeDesc &type;
    mutable ulen off; // internal
    
    Field(const TypeDesc &type_) : type(type_),off(0) {}
   };
  
  const Field *const fields;
  const ulen field_count;
  mutable ulen size_of; // internal
  mutable ulen lock;    // internal
  
  TypeDesc_struct_base(const Field *fields_,ulen field_count_) 
   : TypeDesc(TypeTag_struct),fields(fields_),field_count(field_count_),size_of(0),lock(0) {}
 };

/* struct TypeDesc_struct<ulen FieldCount> */

template <ulen FieldCount> 
struct TypeDesc_struct : TypeDesc_struct_base
 {
  const Field buf[FieldCount];
  
  template <class ... TT>
  explicit TypeDesc_struct(const TT & ... tt) : TypeDesc_struct_base(buf,FieldCount),buf{tt...} {}
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
  
  void * operator + () const { return ptr; }
  
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

} // namespace DDL2
} // namespace CCore
 
#endif
 

