/* DDLProcess.h */
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

#ifndef CCore_inc_ddl_DDLProcess_h
#define CCore_inc_ddl_DDLProcess_h

#include <CCore/inc/ddl/DDLSemantic.h>

namespace CCore {
namespace DDL {

/* classes */

struct ExtTypeSwitch;

struct TypeNode_fields;

struct TypeNode_anyptr;

struct TypeNode_slen;

struct TypeNode_LVPtr;

struct TypeNode_void;

template <class Eval> class Process;

/* struct ExtTypeSwitch */

struct ExtTypeSwitch : TypeSwitch
 {
  void (ExtTypeSwitch::*case_fields)(TypeNode_fields *node);
  void (ExtTypeSwitch::*case_anyptr)(TypeNode_anyptr *node);
  void (ExtTypeSwitch::*case_slen)(TypeNode_slen *node);
  void (ExtTypeSwitch::*case_LVPtr)(TypeNode_LVPtr *node);
  void (ExtTypeSwitch::*case_void)(TypeNode_void *node);
  
  template <class T>
  explicit ExtTypeSwitch(T *ptr) 
   : TypeSwitch(ptr) 
   {
    case_fields=static_cast<void (ExtTypeSwitch::*)(TypeNode_fields *)>(&T::do_fields);
    case_anyptr=static_cast<void (ExtTypeSwitch::*)(TypeNode_anyptr *)>(&T::do_anyptr);
    case_slen=static_cast<void (ExtTypeSwitch::*)(TypeNode_slen *)>(&T::do_slen);
    case_LVPtr=static_cast<void (ExtTypeSwitch::*)(TypeNode_LVPtr *)>(&T::do_LVPtr);
    case_void=static_cast<void (ExtTypeSwitch::*)(TypeNode_void *)>(&T::do_void);
   }
  
  void dispatch_fields(TypeNode_fields *node) { (this->*case_fields)(node); }
  
  void dispatch_anyptr(TypeNode_anyptr *node) { (this->*case_anyptr)(node); }
  
  void dispatch_slen(TypeNode_slen *node) { (this->*case_slen)(node); }
  
  void dispatch_LVPtr(TypeNode_LVPtr *node) { (this->*case_LVPtr)(node); }
  
  void dispatch_void(TypeNode_void *node) { (this->*case_void)(node); }
 };

/* struct TypeNode_fields */

struct TypeNode_fields : TypeNode
 {
  StructNode *struct_node;
  bool *flags;
  
  void do_dispatch(TypeSwitch &ts)
   {
    static_cast<ExtTypeSwitch &>(ts).dispatch_fields(this);
   }
  
  void init(StructNode *struct_node_,bool *flags_)
   {
    init_base(this);
    
    struct_node=struct_node_;
    flags=flags_;
   }
 };

/* struct TypeNode_anyptr */

struct TypeNode_anyptr : TypeNode
 {
  void do_dispatch(TypeSwitch &ts)
   {
    static_cast<ExtTypeSwitch &>(ts).dispatch_anyptr(this);
   }
  
  void init()
   {
    init_base(this);
   }
 };

/* struct TypeNode_slen */

struct TypeNode_slen : TypeNode
 {
  void do_dispatch(TypeSwitch &ts)
   {
    static_cast<ExtTypeSwitch &>(ts).dispatch_slen(this);
   }
  
  void init()
   {
    init_base(this);
   }
 };

/* struct TypeNode_LVPtr */

struct TypeNode_LVPtr : TypeNode
 {
  void do_dispatch(TypeSwitch &ts)
   {
    static_cast<ExtTypeSwitch &>(ts).dispatch_LVPtr(this);
   }
  
  void init()
   {
    init_base(this);
   }
 };

/* struct TypeNode_void */

struct TypeNode_void : TypeNode
 {
  bool skip;
  
  void do_dispatch(TypeSwitch &ts)
   {
    static_cast<ExtTypeSwitch &>(ts).dispatch_void(this);
   }
  
  void init(bool skip_)
   {
    init_base(this);
    
    skip=skip_;
   }
 };

/* class Process<Eval> */

template <class Eval>
class Process : ExprSwitch
 {
   ElementPool &pool;
   Eval eval;
   FindFieldType fft;
   
   TypeNode_suint<imp_ulen> *ulen_type;
   TypeNode_anyptr *anyptr_type;
   TypeNode_slen *slen_type;
   TypeNode_LVPtr *LVPtr_type;
   TypeNode_void *void_type;
   TypeNode_void *skip_type;
   
   friend class ExprSwitch;
   
  private:
   
   void initTypes()
    {
     ulen_type=pool.create<TypeNode_suint<imp_ulen> >();
     
     ulen_type->init();
     
     anyptr_type=pool.create<TypeNode_anyptr>();
     
     anyptr_type->init();
     
     slen_type=pool.create<TypeNode_slen>();
     
     slen_type->init();
     
     LVPtr_type=pool.create<TypeNode_LVPtr>();
     
     LVPtr_type->init();
     
     void_type=pool.create<TypeNode_void>();
     
     void_type->init(false);
     
     skip_type=pool.create<TypeNode_void>();
     
     skip_type->init(true);
    }
   
  private:
  
   struct AddSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_add *node;
     
     explicit AddSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct SubSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_sub *node;
     
     explicit SubSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct MulSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_mul *node;
     
     explicit MulSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct DivSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_div *node;
     
     explicit DivSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct RemSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_rem *node;
     
     explicit RemSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct PlusSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_plus *node;
     
     explicit PlusSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct MinusSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_minus *node;
     
     explicit MinusSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct DomainSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_domain *node;
     
     explicit DomainSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct NumberSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_number *node;
     
     explicit NumberSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct StringSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_string *node;
     
     explicit StringSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct IPSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_ip *node;
     
     explicit IPSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct AddressSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_address *node;
     
     explicit AddressSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct NullSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_null *node;
     
     explicit NullSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct DoNullSwitch : TypeSwitch
    {
     Process<Eval> *obj;
     StepId step_id;
     ExprNode *node;
     
     explicit DoNullSwitch(Process<Eval> *obj_) : TypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     
     void do_ptr(TypeNode_ptr *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     
     void do_ref(TypeNode_ref *type_node);
    };
   
   struct NonameSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_noname_list *node;
     
     explicit NonameSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct NamedSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_named_list *node;
     
     explicit NamedSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct ApplyNamedSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_apply_named_list *node;
     
     explicit ApplyNamedSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct VarSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_var *node;
     
     void do_ptr(StepId step_id);
     
     explicit VarSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct DerefSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_deref *node;
     
     void do_ptr(StepId step_id);
     
     explicit DerefSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct PtrSelectSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_ptr_select *node;
     
     void do_ptr(StepId step_id);
     
     explicit PtrSelectSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct SelectSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_select *node;
     
     void do_ptr(StepId step_id);
     
     explicit SelectSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
   struct IndSwitch : ExtTypeSwitch
    {
     Process<Eval> *obj;
     ExprNode_ind *node;
     
     void do_ptr(StepId step_id);
     
     explicit IndSwitch(Process<Eval> *obj_) : ExtTypeSwitch(this),obj(obj_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *type_node);
     void do_uint8(TypeNode_suint<imp_uint8> *type_node);
     void do_sint16(TypeNode_suint<imp_sint16> *type_node);
     void do_uint16(TypeNode_suint<imp_uint16> *type_node);
     void do_sint32(TypeNode_suint<imp_sint32> *type_node);
     void do_uint32(TypeNode_suint<imp_uint32> *type_node);
     void do_sint64(TypeNode_suint<imp_sint64> *type_node);
     void do_uint64(TypeNode_suint<imp_uint64> *type_node);
     void do_slen(TypeNode_slen *type_node);
     void do_text(TypeNode_text *type_node);
     void do_ip(TypeNode_ip *type_node);
     void do_array(TypeNode_array *type_node);
     void do_array_len(TypeNode_array_len *type_node);
     void do_fields(TypeNode_fields *type_node);
     void do_struct(StructNode *struct_node);
     void do_struct(TypeNode_struct *type_node);
     void do_ref(TypeNode_ref *type_node);
     void do_ptr(TypeNode_ptr *type_node);
     void do_anyptr(TypeNode_anyptr *type_node);
     void do_LVPtr(TypeNode_LVPtr *type_node);
     void do_void(TypeNode_void *type_node);
    };
   
  private: 
   
   AddSwitch ts_add;
   SubSwitch ts_sub;
   MulSwitch ts_mul;
   DivSwitch ts_div;
   RemSwitch ts_rem;
   
   PlusSwitch ts_plus;
   MinusSwitch ts_minus;
   
   DomainSwitch ts_domain;
   
   NumberSwitch ts_number;
   StringSwitch ts_string;
   IPSwitch ts_ip;
   
   AddressSwitch ts_address;
   
   NullSwitch ts_null;
   DoNullSwitch ts_donull;
   
   NonameSwitch ts_noname;
   NamedSwitch ts_named;
   ApplyNamedSwitch ts_apply_named;
   
   VarSwitch ts_var;
   DerefSwitch ts_deref;
   PtrSelectSwitch ts_ptr_select;
   SelectSwitch ts_select;
   IndSwitch ts_ind;
   
  private:
   
   void do_add(ExprNode_add *node) { ts_add.node=node; node->ret_type->dispatch(ts_add); }
   void do_sub(ExprNode_sub *node) { ts_sub.node=node; node->ret_type->dispatch(ts_sub); }
   void do_mul(ExprNode_mul *node) { ts_mul.node=node; node->ret_type->dispatch(ts_mul); }
   void do_div(ExprNode_div *node) { ts_div.node=node; node->ret_type->dispatch(ts_div); }
   void do_rem(ExprNode_rem *node) { ts_rem.node=node; node->ret_type->dispatch(ts_rem); }
   
   void do_plus(ExprNode_plus *node) { ts_plus.node=node; node->ret_type->dispatch(ts_plus); }
   void do_minus(ExprNode_minus *node) { ts_minus.node=node; node->ret_type->dispatch(ts_minus); }
   
   void do_domain(ExprNode_domain *node) { ts_domain.node=node; node->ret_type->dispatch(ts_domain); }
   
   void do_number(ExprNode_number *node) { ts_number.node=node; node->ret_type->dispatch(ts_number); }
   void do_string(ExprNode_string *node) { ts_string.node=node; node->ret_type->dispatch(ts_string); }
   void do_ip(ExprNode_ip *node) { ts_ip.node=node; node->ret_type->dispatch(ts_ip); }
   
   void do_address(ExprNode_address *node) { ts_address.node=node; node->ret_type->dispatch(ts_address); }
   
   void do_null(ExprNode_null *node) { ts_null.node=node; node->ret_type->dispatch(ts_null); }
   
   void do_noname_list(ExprNode_noname_list *node) { ts_noname.node=node; node->ret_type->dispatch(ts_noname); }
   void do_named_list(ExprNode_named_list *node) { ts_named.node=node; node->ret_type->dispatch(ts_named); }
   void do_apply_named_list(ExprNode_apply_named_list *node) { ts_apply_named.node=node; node->ret_type->dispatch(ts_apply_named); }
   
   void do_var(ExprNode_var *node) { ts_var.node=node; node->ret_type->dispatch(ts_var); }
   void do_deref(ExprNode_deref *node) { ts_deref.node=node; node->ret_type->dispatch(ts_deref); }
   void do_ptr_select(ExprNode_ptr_select *node) { ts_ptr_select.node=node; node->ret_type->dispatch(ts_ptr_select); }
   void do_select(ExprNode_select *node) { ts_select.node=node; node->ret_type->dispatch(ts_select); }
   void do_ind(ExprNode_ind *node) { ts_ind.node=node; node->ret_type->dispatch(ts_ind); }
   
  private:
   
   void expr_void(ExprNode &node);
   
   void expr(ConstNode &node);
   
   void expr(LenNode &node);
   
   void expr(FieldNode &field);
   
   void do_expr(ExprNode &node);
   
  private:
   
   void expr_skip(ExprNode *expr_node);
   
   void expr(StepId step_id,TypeNode *type_node,ExprNode *expr_node);
   
   void expr_ulen(StepId step_id,ExprNode *expr_node) { expr(step_id,ulen_type,expr_node); }
   
   void expr_anyptr(StepId step_id,ExprNode *expr_node) { expr(step_id,anyptr_type,expr_node); }
   
   void expr_slen(StepId step_id,ExprNode *expr_node) { expr(step_id,slen_type,expr_node); }
   
   void expr_LVPtr(StepId step_id,ExprNode *expr_node) { expr(step_id,LVPtr_type,expr_node); }
   
  private:
   
   void do_expr_null(StepId step_id,TypeNode *type,ExprNode *node);
   
   void deref_fields(StepId step_id,TypeNode_fields *type_node,StepId ptr_id,ExprNode *node);
   
  public:
   
   template <class ... SS>
   explicit Process(ElementPool &pool_,SS && ... ss) 
    : ExprSwitch(this),
      pool(pool_),
      eval( std::forward<SS>(ss)... ),
      ts_add(this),
      ts_sub(this),
      ts_mul(this),
      ts_div(this),
      ts_rem(this),
      ts_plus(this),
      ts_minus(this),
      ts_domain(this),
      ts_number(this),
      ts_string(this),
      ts_ip(this),
      ts_address(this),
      ts_null(this),
      ts_donull(this),
      ts_noname(this),
      ts_named(this),
      ts_apply_named(this),
      ts_var(this),
      ts_deref(this),
      ts_ptr_select(this),
      ts_select(this),
      ts_ind(this)
    {
    }
   
   ~Process() {}
   
   void reset() { eval.reset(); }
   
   Eval & operator () (BodyNode *body,const BaseList<ExprNode> &expr_list);
 };

 // struct AddSwitch

template <class Eval>
void Process<Eval>::AddSwitch::do_sint8(TypeNode_suint<imp_sint8> *type_node)
 {
  StepId step_id=obj->eval.add_sint8(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_uint8(TypeNode_suint<imp_uint8> *type_node)
 {
  StepId step_id=obj->eval.add_uint8(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_sint16(TypeNode_suint<imp_sint16> *type_node)
 {
  StepId step_id=obj->eval.add_sint16(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_uint16(TypeNode_suint<imp_uint16> *type_node)
 {
  StepId step_id=obj->eval.add_uint16(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_sint32(TypeNode_suint<imp_sint32> *type_node)
 {
  StepId step_id=obj->eval.add_sint32(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_uint32(TypeNode_suint<imp_uint32> *type_node)
 {
  StepId step_id=obj->eval.add_uint32(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_sint64(TypeNode_suint<imp_sint64> *type_node)
 {
  StepId step_id=obj->eval.add_sint64(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_uint64(TypeNode_suint<imp_uint64> *type_node)
 {
  StepId step_id=obj->eval.add_uint64(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_slen(TypeNode_slen *type_node)
 {
  StepId step_id=obj->eval.add_slen(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_text(TypeNode_text *type_node)
 {
  StepId step_id=obj->eval.add_text(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate a + b as ip",node);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate a + b as T[]",node);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate a + b as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_fields(TypeNode_fields *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate a + b as struct S",node);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_struct(StructNode *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate a + b as struct S",node);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_ptr(TypeNode_ptr *type_node)
 {
  StepId step_id=obj->eval.add_ptr_slen(node->step_id,node);
  
  if( node->arg1->ptrto_type )
    {
     obj->expr(step_id.arg1(),type_node,node->arg1);
     obj->expr_slen(step_id.arg2(),node->arg2);
    }
  else
    {
     obj->expr(step_id.arg1(),type_node,node->arg2);
     obj->expr_slen(step_id.arg2(),node->arg1);
    }
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_anyptr(TypeNode_anyptr *type_node)
 {
  StepId step_id=obj->eval.add_ptr_slen(node->step_id,node);
  
  if( node->arg1->ptrto_type )
    {
     obj->expr(step_id.arg1(),type_node,node->arg1);
     obj->expr_slen(step_id.arg2(),node->arg2);
    }
  else
    {
     obj->expr(step_id.arg1(),type_node,node->arg2);
     obj->expr_slen(step_id.arg2(),node->arg1);
    }
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"a + b is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::AddSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg1);
     obj->expr_skip(node->arg2);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct SubSwitch

template <class Eval>
void Process<Eval>::SubSwitch::do_sint8(TypeNode_suint<imp_sint8> *type_node)
 {
  if( node->arg1->ptrto_type )
    {
     StepId step_id=obj->eval.cast_sint8(node->step_id,obj->slen_type,node);
     
     StepId step1_id=obj->eval.sub_ptr(step_id.arg1(),node);
     
     obj->expr_anyptr(step1_id.arg1(),node->arg1);
     obj->expr_anyptr(step1_id.arg2(),node->arg2);
    }
  else
    {
     StepId step_id=obj->eval.sub_sint8(node->step_id,node);
     
     obj->expr(step_id.arg1(),type_node,node->arg1);
     obj->expr(step_id.arg2(),type_node,node->arg2);
    }
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_uint8(TypeNode_suint<imp_uint8> *type_node)
 {
  if( node->arg1->ptrto_type )
    {
     StepId step_id=obj->eval.cast_uint8(node->step_id,obj->slen_type,node);
     
     StepId step1_id=obj->eval.sub_ptr(step_id.arg1(),node);
     
     obj->expr_anyptr(step1_id.arg1(),node->arg1);
     obj->expr_anyptr(step1_id.arg2(),node->arg2);
    }
  else
    {
     StepId step_id=obj->eval.sub_uint8(node->step_id,node);
     
     obj->expr(step_id.arg1(),type_node,node->arg1);
     obj->expr(step_id.arg2(),type_node,node->arg2);
    }
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_sint16(TypeNode_suint<imp_sint16> *type_node)
 {
  if( node->arg1->ptrto_type )
    {
     StepId step_id=obj->eval.cast_sint16(node->step_id,obj->slen_type,node);
     
     StepId step1_id=obj->eval.sub_ptr(step_id.arg1(),node);
     
     obj->expr_anyptr(step1_id.arg1(),node->arg1);
     obj->expr_anyptr(step1_id.arg2(),node->arg2);
    }
  else
    {
     StepId step_id=obj->eval.sub_sint16(node->step_id,node);
     
     obj->expr(step_id.arg1(),type_node,node->arg1);
     obj->expr(step_id.arg2(),type_node,node->arg2);
    }
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_uint16(TypeNode_suint<imp_uint16> *type_node)
 {
  if( node->arg1->ptrto_type )
    {
     StepId step_id=obj->eval.cast_uint16(node->step_id,obj->slen_type,node);
     
     StepId step1_id=obj->eval.sub_ptr(step_id.arg1(),node);
     
     obj->expr_anyptr(step1_id.arg1(),node->arg1);
     obj->expr_anyptr(step1_id.arg2(),node->arg2);
    }
  else
    {
     StepId step_id=obj->eval.sub_uint16(node->step_id,node);
     
     obj->expr(step_id.arg1(),type_node,node->arg1);
     obj->expr(step_id.arg2(),type_node,node->arg2);
    }
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_sint32(TypeNode_suint<imp_sint32> *type_node)
 {
  if( node->arg1->ptrto_type )
    {
     StepId step_id=obj->eval.cast_sint32(node->step_id,obj->slen_type,node);
     
     StepId step1_id=obj->eval.sub_ptr(step_id.arg1(),node);
     
     obj->expr_anyptr(step1_id.arg1(),node->arg1);
     obj->expr_anyptr(step1_id.arg2(),node->arg2);
    }
  else
    {
     StepId step_id=obj->eval.sub_sint32(node->step_id,node);
     
     obj->expr(step_id.arg1(),type_node,node->arg1);
     obj->expr(step_id.arg2(),type_node,node->arg2);
    }
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_uint32(TypeNode_suint<imp_uint32> *type_node)
 {
  if( node->arg1->ptrto_type )
    {
     StepId step_id=obj->eval.cast_uint32(node->step_id,obj->slen_type,node);
     
     StepId step1_id=obj->eval.sub_ptr(step_id.arg1(),node);
     
     obj->expr_anyptr(step1_id.arg1(),node->arg1);
     obj->expr_anyptr(step1_id.arg2(),node->arg2);
    }
  else
    {
     StepId step_id=obj->eval.sub_uint32(node->step_id,node);
     
     obj->expr(step_id.arg1(),type_node,node->arg1);
     obj->expr(step_id.arg2(),type_node,node->arg2);
    }
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_sint64(TypeNode_suint<imp_sint64> *type_node)
 {
  if( node->arg1->ptrto_type )
    {
     StepId step_id=obj->eval.cast_sint64(node->step_id,obj->slen_type,node);
     
     StepId step1_id=obj->eval.sub_ptr(step_id.arg1(),node);
     
     obj->expr_anyptr(step1_id.arg1(),node->arg1);
     obj->expr_anyptr(step1_id.arg2(),node->arg2);
    }
  else
    {
     StepId step_id=obj->eval.sub_sint64(node->step_id,node);
     
     obj->expr(step_id.arg1(),type_node,node->arg1);
     obj->expr(step_id.arg2(),type_node,node->arg2);
    }
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_uint64(TypeNode_suint<imp_uint64> *type_node)
 {
  if( node->arg1->ptrto_type )
    {
     StepId step_id=obj->eval.cast_uint64(node->step_id,obj->slen_type,node);
     
     StepId step1_id=obj->eval.sub_ptr(step_id.arg1(),node);
     
     obj->expr_anyptr(step1_id.arg1(),node->arg1);
     obj->expr_anyptr(step1_id.arg2(),node->arg2);
    }
  else
    {
     StepId step_id=obj->eval.sub_uint64(node->step_id,node);
     
     obj->expr(step_id.arg1(),type_node,node->arg1);
     obj->expr(step_id.arg2(),type_node,node->arg2);
    }
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_slen(TypeNode_slen *type_node)
 {
  if( node->arg1->ptrto_type )
    {
     StepId step_id=obj->eval.sub_ptr(node->step_id,node);
     
     obj->expr_anyptr(step_id.arg1(),node->arg1);
     obj->expr_anyptr(step_id.arg2(),node->arg2);
    }
  else
    {
     StepId step_id=obj->eval.sub_slen(node->step_id,node);
     
     obj->expr(step_id.arg1(),type_node,node->arg1);
     obj->expr(step_id.arg2(),type_node,node->arg2);
    }
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_text(TypeNode_text *)
 {
  obj->eval.error_text(node->step_id,"cannot evaluate a - b as text",node);
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate a - b as ip",node);
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate a - b as T[]",node);
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate a - b as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_fields(TypeNode_fields *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate a - b as struct S",node);
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_struct(StructNode *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate a - b as struct S",node);
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_ptr(TypeNode_ptr *type_node)
 {
  StepId step_id=obj->eval.sub_ptr_slen(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr_slen(step_id.arg2(),node->arg2);
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_anyptr(TypeNode_anyptr *type_node)
 {
  StepId step_id=obj->eval.sub_ptr_slen(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr_slen(step_id.arg2(),node->arg2);
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"a - b is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::SubSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg1);
     obj->expr_skip(node->arg2);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct MulSwitch

template <class Eval>
void Process<Eval>::MulSwitch::do_sint8(TypeNode_suint<imp_sint8> *type_node)
 {
  StepId step_id=obj->eval.mul_sint8(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_uint8(TypeNode_suint<imp_uint8> *type_node)
 {
  StepId step_id=obj->eval.mul_uint8(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_sint16(TypeNode_suint<imp_sint16> *type_node)
 {
  StepId step_id=obj->eval.mul_sint16(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_uint16(TypeNode_suint<imp_uint16> *type_node)
 {
  StepId step_id=obj->eval.mul_uint16(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_sint32(TypeNode_suint<imp_sint32> *type_node)
 {
  StepId step_id=obj->eval.mul_sint32(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_uint32(TypeNode_suint<imp_uint32> *type_node)
 {
  StepId step_id=obj->eval.mul_uint32(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_sint64(TypeNode_suint<imp_sint64> *type_node)
 {
  StepId step_id=obj->eval.mul_sint64(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_uint64(TypeNode_suint<imp_uint64> *type_node)
 {
  StepId step_id=obj->eval.mul_uint64(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_slen(TypeNode_slen *type_node)
 {
  StepId step_id=obj->eval.mul_slen(node->step_id,node);
  
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_text(TypeNode_text *)
 {
  obj->eval.error_text(node->step_id,"cannot evaluate a * b as text",node);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate a * b as ip",node);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate a * b as T[]",node);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate a * b as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_fields(TypeNode_fields *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate a * b as struct S",node);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_struct(StructNode *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate a * b as struct S",node);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_ptr(TypeNode_ptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate a * b as T *",node);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate a * b as T *",node);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"a * b is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::MulSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg1);
     obj->expr_skip(node->arg2);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct DivSwitch

template <class Eval>
void Process<Eval>::DivSwitch::do_sint8(TypeNode_suint<imp_sint8> *type_node)
 {
  StepId step_id=obj->eval.div_sint8(node->step_id,node);
 
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_uint8(TypeNode_suint<imp_uint8> *type_node)
 {
  StepId step_id=obj->eval.div_uint8(node->step_id,node);
 
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_sint16(TypeNode_suint<imp_sint16> *type_node)
 {
  StepId step_id=obj->eval.div_sint16(node->step_id,node);
 
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_uint16(TypeNode_suint<imp_uint16> *type_node)
 {
  StepId step_id=obj->eval.div_uint16(node->step_id,node);
 
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_sint32(TypeNode_suint<imp_sint32> *type_node)
 {
  StepId step_id=obj->eval.div_sint32(node->step_id,node);
 
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_uint32(TypeNode_suint<imp_uint32> *type_node)
 {
  StepId step_id=obj->eval.div_uint32(node->step_id,node);
 
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_sint64(TypeNode_suint<imp_sint64> *type_node)
 {
  StepId step_id=obj->eval.div_sint64(node->step_id,node);
 
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_uint64(TypeNode_suint<imp_uint64> *type_node)
 {
  StepId step_id=obj->eval.div_uint64(node->step_id,node);
 
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_slen(TypeNode_slen *type_node)
 {
  StepId step_id=obj->eval.div_slen(node->step_id,node);
 
  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_text(TypeNode_text *)
 {
  obj->eval.error_text(node->step_id,"cannot evaluate a / b as text",node);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate a / b as ip",node);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate a / b as T[]",node);
 } 

template <class Eval>
void Process<Eval>::DivSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate a / b as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_fields(TypeNode_fields *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate a / b as struct S",node);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_struct(StructNode *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate a / b as struct S",node);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_ptr(TypeNode_ptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate a / b as T *",node);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate a / b as T *",node);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"a / b is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::DivSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg1);
     obj->expr_skip(node->arg2);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

// struct RemSwitch

template <class Eval>
void Process<Eval>::RemSwitch::do_sint8(TypeNode_suint<imp_sint8> *type_node)
 {
  StepId step_id=obj->eval.rem_sint8(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_uint8(TypeNode_suint<imp_uint8> *type_node)
 {
  StepId step_id=obj->eval.rem_uint8(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_sint16(TypeNode_suint<imp_sint16> *type_node)
 {
  StepId step_id=obj->eval.rem_sint16(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_uint16(TypeNode_suint<imp_uint16> *type_node)
 {
  StepId step_id=obj->eval.rem_uint16(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_sint32(TypeNode_suint<imp_sint32> *type_node)
 {
  StepId step_id=obj->eval.rem_sint32(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_uint32(TypeNode_suint<imp_uint32> *type_node)
 {
  StepId step_id=obj->eval.rem_uint32(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_sint64(TypeNode_suint<imp_sint64> *type_node)
 {
  StepId step_id=obj->eval.rem_sint64(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_uint64(TypeNode_suint<imp_uint64> *type_node)
 {
  StepId step_id=obj->eval.rem_uint64(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_slen(TypeNode_slen *type_node)
 {
  StepId step_id=obj->eval.rem_slen(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg1);
  obj->expr(step_id.arg2(),type_node,node->arg2);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_text(TypeNode_text *)
 {
  obj->eval.error_text(node->step_id,"cannot evaluate a % b as text",node);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate a % b as ip",node);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate a % b as T[]",node);
 } 

template <class Eval>
void Process<Eval>::RemSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate a % b as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_fields(TypeNode_fields *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate a % b as struct S",node);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_struct(StructNode *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate a % b as struct S",node);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_ptr(TypeNode_ptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate a % b as T *",node);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate a % b as T *",node);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"a % b is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::RemSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg1);
     obj->expr_skip(node->arg2);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct PlusSwitch

template <class Eval>
void Process<Eval>::PlusSwitch::do_sint8(TypeNode_suint<imp_sint8> *type_node)
 {
  StepId step_id=obj->eval.plus_sint8(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_uint8(TypeNode_suint<imp_uint8> *type_node)
 {
  StepId step_id=obj->eval.plus_uint8(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_sint16(TypeNode_suint<imp_sint16> *type_node)
 {
  StepId step_id=obj->eval.plus_sint16(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_uint16(TypeNode_suint<imp_uint16> *type_node)
 {
  StepId step_id=obj->eval.plus_uint16(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_sint32(TypeNode_suint<imp_sint32> *type_node)
 {
  StepId step_id=obj->eval.plus_sint32(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_uint32(TypeNode_suint<imp_uint32> *type_node)
 {
  StepId step_id=obj->eval.plus_uint32(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_sint64(TypeNode_suint<imp_sint64> *type_node)
 {
  StepId step_id=obj->eval.plus_sint64(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_uint64(TypeNode_suint<imp_uint64> *type_node)
 {
  StepId step_id=obj->eval.plus_uint64(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_slen(TypeNode_slen *type_node)
 {
  StepId step_id=obj->eval.plus_slen(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_text(TypeNode_text *)
 {
  obj->eval.error_text(node->step_id,"cannot evaluate + a as text",node);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate + a as ip",node);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate + a as T[]",node);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate + a as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_fields(TypeNode_fields *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate + a as struct S",node);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_struct(StructNode *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate + a as struct S",node);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_ptr(TypeNode_ptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate + a as T *",node);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate + a as T *",node);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"+ a is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::PlusSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

// struct MinusSwitch

template <class Eval>
void Process<Eval>::MinusSwitch::do_sint8(TypeNode_suint<imp_sint8> *type_node)
 {
  StepId step_id=obj->eval.minus_sint8(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_uint8(TypeNode_suint<imp_uint8> *type_node)
 {
  StepId step_id=obj->eval.minus_uint8(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_sint16(TypeNode_suint<imp_sint16> *type_node)
 {
  StepId step_id=obj->eval.minus_sint16(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_uint16(TypeNode_suint<imp_uint16> *type_node)
 {
  StepId step_id=obj->eval.minus_uint16(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_sint32(TypeNode_suint<imp_sint32> *type_node)
 {
  StepId step_id=obj->eval.minus_sint32(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_uint32(TypeNode_suint<imp_uint32> *type_node)
 {
  StepId step_id=obj->eval.minus_uint32(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_sint64(TypeNode_suint<imp_sint64> *type_node)
 {
  StepId step_id=obj->eval.minus_sint64(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_uint64(TypeNode_suint<imp_uint64> *type_node)
 {
  StepId step_id=obj->eval.minus_uint64(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_slen(TypeNode_slen *type_node)
 {
  StepId step_id=obj->eval.minus_slen(node->step_id,node);

  obj->expr(step_id.arg1(),type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_text(TypeNode_text *)
 {
  obj->eval.error_text(node->step_id,"cannot evaluate - a as text",node);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate - a as ip",node);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate - a as T[]",node);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate - a as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_fields(TypeNode_fields *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate - a as struct S",node);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_struct(StructNode *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate - a as struct S",node);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_ptr(TypeNode_ptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate - a as T *",node);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate - a as T *",node);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"- a is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::MinusSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct DomainSwitch

template <class Eval>
void Process<Eval>::DomainSwitch::do_sint8(TypeNode_suint<imp_sint8> *)
 {
  TypeNode *type=node->domain_node->type_node;
  
  StepId step_id=obj->eval.cast_sint8(node->step_id,type,node);

  obj->expr(step_id.arg1(),type,node->arg);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_uint8(TypeNode_suint<imp_uint8> *)
 {
  TypeNode *type=node->domain_node->type_node;
  
  StepId step_id=obj->eval.cast_uint8(node->step_id,type,node);

  obj->expr(step_id.arg1(),type,node->arg);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_sint16(TypeNode_suint<imp_sint16> *)
 {
  TypeNode *type=node->domain_node->type_node;
  
  StepId step_id=obj->eval.cast_sint16(node->step_id,type,node);

  obj->expr(step_id.arg1(),type,node->arg);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_uint16(TypeNode_suint<imp_uint16> *)
 {
  TypeNode *type=node->domain_node->type_node;
  
  StepId step_id=obj->eval.cast_uint16(node->step_id,type,node);

  obj->expr(step_id.arg1(),type,node->arg);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_sint32(TypeNode_suint<imp_sint32> *)
 {
  TypeNode *type=node->domain_node->type_node;
  
  StepId step_id=obj->eval.cast_sint32(node->step_id,type,node);

  obj->expr(step_id.arg1(),type,node->arg);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_uint32(TypeNode_suint<imp_uint32> *)
 {
  TypeNode *type=node->domain_node->type_node;
  
  StepId step_id=obj->eval.cast_uint32(node->step_id,type,node);

  obj->expr(step_id.arg1(),type,node->arg);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_sint64(TypeNode_suint<imp_sint64> *)
 {
  TypeNode *type=node->domain_node->type_node;
  
  StepId step_id=obj->eval.cast_sint64(node->step_id,type,node);

  obj->expr(step_id.arg1(),type,node->arg);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_uint64(TypeNode_suint<imp_uint64> *)
 {
  TypeNode *type=node->domain_node->type_node;
  
  StepId step_id=obj->eval.cast_uint64(node->step_id,type,node);

  obj->expr(step_id.arg1(),type,node->arg);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_slen(TypeNode_slen *)
 {
  TypeNode *type=node->domain_node->type_node;
  
  StepId step_id=obj->eval.cast_slen(node->step_id,type,node);

  obj->expr(step_id.arg1(),type,node->arg);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_text(TypeNode_text *)
 {
  TypeNode *type=node->domain_node->type_node;
  
  StepId step_id=obj->eval.cast_text(node->step_id,type,node);

  obj->expr(step_id.arg1(),type,node->arg);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate domain(a) as ip",node);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate domain(a) as T[]",node);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate domain(a) as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_fields(TypeNode_fields *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate domain(a) as struct S",node);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_struct(StructNode *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate domain(a) as struct S",node);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_ptr(TypeNode_ptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate domain(a) as T *",node);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate domain(a) as T *",node);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"domain(a) is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::DomainSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct NumberSwitch

template <class Eval>
void Process<Eval>::NumberSwitch::do_sint8(TypeNode_suint<imp_sint8> *)
 {
  obj->eval.number_sint8(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_uint8(TypeNode_suint<imp_uint8> *)
 {
  obj->eval.number_uint8(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_sint16(TypeNode_suint<imp_sint16> *)
 {
  obj->eval.number_sint16(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_uint16(TypeNode_suint<imp_uint16> *)
 {
  obj->eval.number_uint16(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_sint32(TypeNode_suint<imp_sint32> *)
 {
  obj->eval.number_sint32(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_uint32(TypeNode_suint<imp_uint32> *)
 {
  obj->eval.number_uint32(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_sint64(TypeNode_suint<imp_sint64> *)
 {
  obj->eval.number_sint64(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_uint64(TypeNode_suint<imp_uint64> *)
 {
  obj->eval.number_uint64(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_slen(TypeNode_slen *)
 {
  obj->eval.number_slen(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_text(TypeNode_text *)
 {
  obj->eval.number_text(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate number as ip",node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate number as T[]",node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate number as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_fields(TypeNode_fields *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate number as struct S",node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_struct(StructNode *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate number as struct S",node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_ptr(TypeNode_ptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate number as T *",node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate number as T *",node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"number is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::NumberSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     // do nothing
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct StringSwitch
  
template <class Eval>
void Process<Eval>::StringSwitch::do_sint8(TypeNode_suint<imp_sint8> *)
 {
  obj->eval.error_sint8(node->step_id,"cannot evaluate string as sint8",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_uint8(TypeNode_suint<imp_uint8> *)
 {
  obj->eval.error_uint8(node->step_id,"cannot evaluate string as uint8",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_sint16(TypeNode_suint<imp_sint16> *)
 {
  obj->eval.error_sint16(node->step_id,"cannot evaluate string as sint16",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_uint16(TypeNode_suint<imp_uint16> *)
 {
  obj->eval.error_uint16(node->step_id,"cannot evaluate string as uint16",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_sint32(TypeNode_suint<imp_sint32> *)
 {
  obj->eval.error_sint32(node->step_id,"cannot evaluate string as sint32",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_uint32(TypeNode_suint<imp_uint32> *)
 {
  obj->eval.error_uint32(node->step_id,"cannot evaluate string as uint32",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_sint64(TypeNode_suint<imp_sint64> *)
 {
  obj->eval.error_sint64(node->step_id,"cannot evaluate string as sint64",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_uint64(TypeNode_suint<imp_uint64> *)
 {
  obj->eval.error_uint64(node->step_id,"cannot evaluate string as uint64",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_slen(TypeNode_slen *)
 {
  obj->eval.error_slen(node->step_id,"cannot evaluate string as slen",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_text(TypeNode_text *)
 {
  obj->eval.string_text(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate string as ip",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate string as T[]",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate string as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_fields(TypeNode_fields *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate string as struct S",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_struct(StructNode *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate string as struct S",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_ptr(TypeNode_ptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate string as T *",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate string as T *",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"string is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::StringSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     // do nothing
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }
  
 // struct IPSwitch

template <class Eval>
void Process<Eval>::IPSwitch::do_sint8(TypeNode_suint<imp_sint8> *)
 {
  obj->eval.error_sint8(node->step_id,"cannot evaluate ip as sint8",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_uint8(TypeNode_suint<imp_uint8> *)
 {
  obj->eval.error_uint8(node->step_id,"cannot evaluate ip as uint8",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_sint16(TypeNode_suint<imp_sint16> *)
 {
  obj->eval.error_sint16(node->step_id,"cannot evaluate ip as sint16",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_uint16(TypeNode_suint<imp_uint16> *)
 {
  obj->eval.error_uint16(node->step_id,"cannot evaluate ip as uint16",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_sint32(TypeNode_suint<imp_sint32> *)
 {
  obj->eval.error_sint32(node->step_id,"cannot evaluate ip as sint32",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_uint32(TypeNode_suint<imp_uint32> *)
 {
  obj->eval.error_uint32(node->step_id,"cannot evaluate ip as uint32",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_sint64(TypeNode_suint<imp_sint64> *)
 {
  obj->eval.error_sint64(node->step_id,"cannot evaluate ip as sint64",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_uint64(TypeNode_suint<imp_uint64> *)
 {
  obj->eval.error_uint64(node->step_id,"cannot evaluate ip as uint64",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_slen(TypeNode_slen *)
 {
  obj->eval.error_slen(node->step_id,"cannot evaluate ip as slen",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_text(TypeNode_text *)
 {
  StepId step_id=obj->eval.cast_text_ip(node->step_id,node);
  
  obj->eval.ip(step_id.arg1(),node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.ip(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate ip as T[]",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate ip as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_fields(TypeNode_fields *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate ip as struct S",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_struct(StructNode *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate ip as struct S",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_ptr(TypeNode_ptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate ip as T *",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate ip as T *",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"ip is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::IPSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     // do nothing
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct AddressSwitch

template <class Eval>
void Process<Eval>::AddressSwitch::do_sint8(TypeNode_suint<imp_sint8> *)
 {
  obj->eval.error_sint8(node->step_id,"cannot evaluate & a as sint8",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_uint8(TypeNode_suint<imp_uint8> *)
 {
  obj->eval.error_uint8(node->step_id,"cannot evaluate & a as uint8",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_sint16(TypeNode_suint<imp_sint16> *)
 {
  obj->eval.error_sint16(node->step_id,"cannot evaluate & a as sint16",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_uint16(TypeNode_suint<imp_uint16> *)
 {
  obj->eval.error_uint16(node->step_id,"cannot evaluate & a as uint16",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_sint32(TypeNode_suint<imp_sint32> *)
 {
  obj->eval.error_sint32(node->step_id,"cannot evaluate & a as sint32",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_uint32(TypeNode_suint<imp_uint32> *)
 {
  obj->eval.error_uint32(node->step_id,"cannot evaluate & a as uint32",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_sint64(TypeNode_suint<imp_sint64> *)
 {
  obj->eval.error_sint64(node->step_id,"cannot evaluate & a as sint64",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_uint64(TypeNode_suint<imp_uint64> *)
 {
  obj->eval.error_uint64(node->step_id,"cannot evaluate & a as uint64",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_slen(TypeNode_slen *)
 {
  obj->eval.error_slen(node->step_id,"cannot evaluate & a as slen",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_text(TypeNode_text *)
 {
  obj->eval.error_text(node->step_id,"cannot evaluate & a as text",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate & a as ip",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate & a as T[]",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate & a as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_fields(TypeNode_fields *)
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate & a as struct S",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_struct(StructNode *) 
 {
  obj->eval.error_struct(node->step_id,"cannot evaluate & a as struct S",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_ptr(TypeNode_ptr *type_node)
 {
  StepId step_id=obj->eval.ptr_type(node->step_id,type_node,node);
     
  obj->expr_LVPtr(step_id.arg1(),node->arg);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->expr_LVPtr(node->step_id,node->arg);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"& a is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::AddressSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct NullSwitch

template <class Eval>
void Process<Eval>::NullSwitch::do_sint8(TypeNode_suint<imp_sint8> *)
 {
  obj->eval.null_sint8(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_uint8(TypeNode_suint<imp_uint8> *)
 {
  obj->eval.null_uint8(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_sint16(TypeNode_suint<imp_sint16> *)
 {
  obj->eval.null_sint16(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_uint16(TypeNode_suint<imp_uint16> *)
 {
  obj->eval.null_uint16(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_sint32(TypeNode_suint<imp_sint32> *)
 {
  obj->eval.null_sint32(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_uint32(TypeNode_suint<imp_uint32> *)
 {
  obj->eval.null_uint32(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_sint64(TypeNode_suint<imp_sint64> *)
 {
  obj->eval.null_sint64(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_uint64(TypeNode_suint<imp_uint64> *)
 {
  obj->eval.null_uint64(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_slen(TypeNode_slen *)
 {
  obj->eval.null_slen(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_text(TypeNode_text *)
 {
  obj->eval.null_text(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.null_ip(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_array(TypeNode_array *type_node)
 {
  obj->eval.null_array(node->step_id,type_node,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_array_len(TypeNode_array_len *type_node)
 {
  obj->eval.null_array_len(node->step_id,type_node,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_fields(TypeNode_fields *type_node)
 {
  StructNode *struct_node=type_node->struct_node;
  bool *flags=type_node->flags;
  StepId step_id=node->step_id;
  
  for(FieldNode &field : struct_node->field_list )
    if( flags[field.field_index] )
      {
       obj->do_expr_null(step_id.argInd(field.field_index),field.type_node,node);
      }
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_struct(StructNode *struct_node)
 {
  obj->eval.null_struct(node->step_id,struct_node,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_ptr(TypeNode_ptr *type_node)
 {
  obj->eval.null_ptr(node->step_id,type_node,node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate null as ??? *",node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"null is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::NullSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     // do nothing
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct DoNullSwitch

template <class Eval>
void Process<Eval>::DoNullSwitch::do_sint8(TypeNode_suint<imp_sint8> *)
 {
  obj->eval.null_sint8(step_id,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_uint8(TypeNode_suint<imp_uint8> *)
 {
  obj->eval.null_uint8(step_id,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_sint16(TypeNode_suint<imp_sint16> *)
 {
  obj->eval.null_sint16(step_id,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_uint16(TypeNode_suint<imp_uint16> *)
 {
  obj->eval.null_uint16(step_id,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_sint32(TypeNode_suint<imp_sint32> *)
 {
  obj->eval.null_sint32(step_id,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_uint32(TypeNode_suint<imp_uint32> *)
 {
  obj->eval.null_uint32(step_id,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_sint64(TypeNode_suint<imp_sint64> *)
 {
  obj->eval.null_sint64(step_id,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_uint64(TypeNode_suint<imp_uint64> *)
 {
  obj->eval.null_uint64(step_id,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_text(TypeNode_text *)
 {
  obj->eval.null_text(step_id,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.null_ip(step_id,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_ptr(TypeNode_ptr *type_node)
 {
  obj->eval.null_ptr(step_id,type_node,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_array(TypeNode_array *type_node)
 {
  obj->eval.null_array(step_id,type_node,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_array_len(TypeNode_array_len *type_node)
 {
  obj->eval.null_array_len(step_id,type_node,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_struct(StructNode *struct_node)
 {
  obj->eval.null_struct(step_id,struct_node,node);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::DoNullSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

 // struct NonameSwitch

template <class Eval>
void Process<Eval>::NonameSwitch::do_sint8(TypeNode_suint<imp_sint8> *)
 {
  if( node->list.count )
    obj->eval.error_sint8(node->step_id,"cannot evaluate {a, ...} as sint8",node);
  else
    obj->eval.null_sint8(node->step_id,node);   
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_uint8(TypeNode_suint<imp_uint8> *)
 {
  if( node->list.count )
    obj->eval.error_uint8(node->step_id,"cannot evaluate {a, ...} as uint8",node);
  else
    obj->eval.null_uint8(node->step_id,node);   
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_sint16(TypeNode_suint<imp_sint16> *)
 {
  if( node->list.count )
    obj->eval.error_sint16(node->step_id,"cannot evaluate {a, ...} as sint16",node);
  else
    obj->eval.null_sint16(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_uint16(TypeNode_suint<imp_uint16> *)
 {
  if( node->list.count )
    obj->eval.error_uint16(node->step_id,"cannot evaluate {a, ...} as uint16",node);
  else
    obj->eval.null_uint16(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_sint32(TypeNode_suint<imp_sint32> *)
 {
  if( node->list.count )
    obj->eval.error_sint32(node->step_id,"cannot evaluate {a, ...} as sint32",node);
  else
    obj->eval.null_sint32(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_uint32(TypeNode_suint<imp_uint32> *)
 {
  if( node->list.count )
    obj->eval.error_uint32(node->step_id,"cannot evaluate {a, ...} as uint32",node);
  else
    obj->eval.null_uint32(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_sint64(TypeNode_suint<imp_sint64> *)
 {
  if( node->list.count )
    obj->eval.error_sint64(node->step_id,"cannot evaluate {a, ...} as sint64",node);
  else
    obj->eval.null_sint64(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_uint64(TypeNode_suint<imp_uint64> *)
 {
  if( node->list.count )
    obj->eval.error_uint64(node->step_id,"cannot evaluate {a, ...} as uint64",node);
  else
    obj->eval.null_uint64(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_slen(TypeNode_slen *)
 {
  if( node->list.count )
    obj->eval.error_slen(node->step_id,"cannot evaluate {a, ...} as slen",node);
  else
    obj->eval.null_slen(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_text(TypeNode_text *)
 {
  if( node->list.count )
    obj->eval.error_text(node->step_id,"cannot evaluate {a, ...} as text",node);
  else
    obj->eval.null_text(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_ip(TypeNode_ip *)
 {
  if( node->list.count )
    obj->eval.error_ip(node->step_id,"cannot evaluate {a, ...} as ip",node);
  else
    obj->eval.null_ip(node->step_id,node);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_array(TypeNode_array *type_node)
 {
  StepId step_id=obj->eval.brace_array(node->step_id,node->list.count,type_node,node);
  
  TypeNode *type=type_node->type_node;
  ulen ind=0;
  
  for(NonameExprNode &enode : node->list )
    {
     obj->expr(step_id.argInd(ind),type,enode.expr_node);
     
     ind++;
    }
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_array_len(TypeNode_array_len *type_node)
 {
  StepId step_id=obj->eval.brace_array_len(node->step_id,node->list.count,type_node,node);
  
  TypeNode *type=type_node->type_node;
  ulen ind=0;
  
  for(NonameExprNode &enode : node->list )
    {
     obj->expr(step_id.argInd(ind),type,enode.expr_node);
     
     ind++;
    }
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_fields(TypeNode_fields *type_node)
 {
  StructNode *struct_node=type_node->struct_node;
  bool *flags=type_node->flags;
  StepId step_id=node->step_id;
  
  ulen count=node->list.count;
  
  if( count>struct_node->field_list.count )
    {
     obj->eval.error_void("excessive initializers",node);
    }
  else
    {
     auto ptr=begin(node->list);

     for(FieldNode &field : struct_node->field_list ) 
       {
        if( field.field_index<count )
          {
           if( flags[field.field_index] )
             obj->expr(step_id.argInd(field.field_index),field.type_node,(*ptr).expr_node);
           else
             obj->expr_skip((*ptr).expr_node);
           
           ++ptr;
          }
        else
          {
           if( flags[field.field_index] )
             obj->eval.def_field(step_id.argInd(field.field_index),field.index,node);
          }
       }
    }
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_struct(StructNode *struct_node)
 {
  ulen count=node->list.count;
  
  if( count>struct_node->field_list.count )
    {
     obj->eval.error_struct(node->step_id,"excessive initializers",node);
    }
  else
    {
     StepId step_id=obj->eval.brace_struct(node->step_id,struct_node,node);
     
     auto ptr=begin(node->list);

     for(FieldNode &field : struct_node->field_list ) 
       {
        if( field.field_index<count )
          {
           obj->expr(step_id.argInd(field.field_index),field.type_node,(*ptr).expr_node);
           
           ++ptr;
          }
        else
          {
           obj->eval.def_field(step_id.argInd(field.field_index),field.index,node);
          }
       }
    }
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_ptr(TypeNode_ptr *type_node)
 {
  if( node->list.count )
    obj->eval.error_ptr(node->step_id,"cannot evaluate {a, ...} as T *",node);
  else
    obj->eval.null_ptr(node->step_id,type_node,node);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate {a, ...} as ??? *",node);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"{a, ...} is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::NonameSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     for(NonameExprNode &enode : node->list ) obj->expr_skip(enode.expr_node);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct NamedSwitch

template <class Eval>
void Process<Eval>::NamedSwitch::do_sint8(TypeNode_suint<imp_sint8> *)
 {
  obj->eval.error_sint8(node->step_id,"cannot evaluate {.name=a, ...} as sint8",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_uint8(TypeNode_suint<imp_uint8> *)
 {
  obj->eval.error_uint8(node->step_id,"cannot evaluate {.name=a, ...} as uint8",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_sint16(TypeNode_suint<imp_sint16> *)
 {
  obj->eval.error_sint16(node->step_id,"cannot evaluate {.name=a, ...} as sint16",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_uint16(TypeNode_suint<imp_uint16> *)
 {
  obj->eval.error_uint16(node->step_id,"cannot evaluate {.name=a, ...} as uint16",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_sint32(TypeNode_suint<imp_sint32> *)
 {
  obj->eval.error_sint32(node->step_id,"cannot evaluate {.name=a, ...} as sint32",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_uint32(TypeNode_suint<imp_uint32> *)
 {
  obj->eval.error_uint32(node->step_id,"cannot evaluate {.name=a, ...} as uint32",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_sint64(TypeNode_suint<imp_sint64> *)
 {
  obj->eval.error_sint64(node->step_id,"cannot evaluate {.name=a, ...} as sint64",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_uint64(TypeNode_suint<imp_uint64> *)
 {
  obj->eval.error_uint64(node->step_id,"cannot evaluate {.name=a, ...} as uint64",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_slen(TypeNode_slen *)
 {
  obj->eval.error_slen(node->step_id,"cannot evaluate {.name=a, ...} as slen",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_text(TypeNode_text *)
 {
  obj->eval.error_text(node->step_id,"cannot evaluate {.name=a, ...} as text",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate {.name=a, ...} as ip",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate {.name=a, ...} as T[]",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate {.name=a, ...} as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_fields(TypeNode_fields *type_node)
 {
  StructNode *struct_node=type_node->struct_node;
  bool *flags=type_node->flags;
  StepId step_id=node->step_id;
  
  for(NamedExprNode &enode : node->list )
    {
     if( FieldNode *field=struct_node->find(enode.name) )
       {
        if( flags[field->field_index] )
          {
           obj->expr(step_id.argInd(field->field_index),field->type_node,enode.expr_node);
           
           flags[field->field_index]=false;
          }
        else
          {
           obj->expr_skip(enode.expr_node);
          }
       }
     else
       {
        obj->expr_skip(enode.expr_node);
       }
    }

  for(FieldNode &field : struct_node->field_list )
    if( flags[field.field_index] )
      {
       obj->eval.def_field(step_id.argInd(field.field_index),field.index,node);
      }
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_struct(StructNode *struct_node)
 {
  StepId step_id=obj->eval.brace_struct(node->step_id,struct_node,node);

  for(FieldNode &field : struct_node->field_list ) field.flag=true;
  
  for(NamedExprNode &enode : node->list )
    {
     if( FieldNode *field=struct_node->find(enode.name) )
       {
        if( field->flag )
          {
           obj->expr(step_id.argInd(field->field_index),field->type_node,enode.expr_node);
           
           field->flag=false;
          }
        else
          {
           obj->expr_skip(enode.expr_node);
          }
       }
     else
       {
        obj->expr_skip(enode.expr_node);
       }
    }
  
  for(FieldNode &field : struct_node->field_list )
    if( field.flag )
      {
       obj->eval.def_field(step_id.argInd(field.field_index),field.index,node);
      }
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_ptr(TypeNode_ptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate {.name=a, ...} as T *",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate {.name=a, ...} as T *",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"{.name=a, ...} is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::NamedSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     for(NamedExprNode &enode : node->list ) obj->expr_skip(enode.expr_node);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct ApplyNamedSwitch

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_sint8(TypeNode_suint<imp_sint8> *)
 {
  obj->eval.error_sint8(node->step_id,"cannot evaluate b {.name=a, ...} as sint8",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_uint8(TypeNode_suint<imp_uint8> *)
 {
  obj->eval.error_uint8(node->step_id,"cannot evaluate b {.name=a, ...} as uint8",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_sint16(TypeNode_suint<imp_sint16> *)
 {
  obj->eval.error_sint16(node->step_id,"cannot evaluate b {.name=a, ...} as sint16",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_uint16(TypeNode_suint<imp_uint16> *)
 {
  obj->eval.error_uint16(node->step_id,"cannot evaluate b {.name=a, ...} as uint16",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_sint32(TypeNode_suint<imp_sint32> *)
 {
  obj->eval.error_sint32(node->step_id,"cannot evaluate b {.name=a, ...} as sint32",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_uint32(TypeNode_suint<imp_uint32> *)
 {
  obj->eval.error_uint32(node->step_id,"cannot evaluate b {.name=a, ...} as uint32",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_sint64(TypeNode_suint<imp_sint64> *)
 {
  obj->eval.error_sint64(node->step_id,"cannot evaluate b {.name=a, ...} as sint64",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_uint64(TypeNode_suint<imp_uint64> *)
 {
  obj->eval.error_uint64(node->step_id,"cannot evaluate b {.name=a, ...} as uint64",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_slen(TypeNode_slen *)
 {
  obj->eval.error_slen(node->step_id,"cannot evaluate b {.name=a, ...} as slen",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_text(TypeNode_text *)
 {
  obj->eval.error_text(node->step_id,"cannot evaluate b {.name=a, ...} as text",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_ip(TypeNode_ip *)
 {
  obj->eval.error_ip(node->step_id,"cannot evaluate b {.name=a, ...} as ip",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_array(TypeNode_array *)
 {
  obj->eval.error_array(node->step_id,"cannot evaluate b {.name=a, ...} as T[]",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_array_len(TypeNode_array_len *)
 {
  obj->eval.error_array_len(node->step_id,"cannot evaluate b {.name=a, ...} as T[Len]",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_fields(TypeNode_fields *type_node)
 {
  StructNode *struct_node=type_node->struct_node;
  bool *flags=type_node->flags;
  StepId step_id=node->step_id;
  
  for(NamedExprNode &enode : node->list )
    {
     if( FieldNode *field=struct_node->find(enode.name) )
       {
        if( flags[field->field_index] )
          {
           obj->expr(step_id.argInd(field->field_index),field->type_node,enode.expr_node);
           
           flags[field->field_index]=false;
          }
        else
          {
           obj->expr_skip(enode.expr_node);
          }
       }
     else
       {
        obj->expr_skip(enode.expr_node);
       }
    }
  
  obj->expr(step_id,type_node,node->arg);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_struct(StructNode *struct_node)
 {
  TypeNode_fields *type=obj->pool.template create<TypeNode_fields>();
  
  type->init(struct_node,obj->pool.template createArray_fill<bool>(struct_node->field_list.count,true).ptr);
  
  node->step_id=obj->eval.brace_struct(node->step_id,struct_node,node);
  
  do_fields(type);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_ptr(TypeNode_ptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate b {.name=a, ...} as T *",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_anyptr(TypeNode_anyptr *)
 {
  obj->eval.error_ptr(node->step_id,"cannot evaluate b {.name=a, ...} as T *",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  obj->eval.error_ptr(node->step_id,"b {.name=a, ...} is not an LValue",node);
 }

template <class Eval>
void Process<Eval>::ApplyNamedSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg);
     
     for(NamedExprNode &enode : node->list ) obj->expr_skip(enode.expr_node);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct VarSwitch

template <class Eval>
void Process<Eval>::VarSwitch::do_ptr(StepId step_id)
 {
  obj->eval.address_var(step_id,node);
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_sint8(TypeNode_suint<imp_sint8> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_uint8(TypeNode_suint<imp_uint8> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_sint16(TypeNode_suint<imp_sint16> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_uint16(TypeNode_suint<imp_uint16> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_sint32(TypeNode_suint<imp_sint32> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_uint32(TypeNode_suint<imp_uint32> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_sint64(TypeNode_suint<imp_sint64> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_uint64(TypeNode_suint<imp_uint64> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_slen(TypeNode_slen *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_text(TypeNode_text *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_ip(TypeNode_ip *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_array(TypeNode_array *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_array_len(TypeNode_array_len *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_fields(TypeNode_fields *type_node)
 {
  StepId step_id=obj->eval.set_temp_ptr();
  
  do_ptr(step_id.arg1());
  
  obj->deref_fields(node->step_id,type_node,step_id,node);
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_struct(StructNode *struct_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,struct_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_ptr(TypeNode_ptr *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_anyptr(TypeNode_anyptr *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  do_ptr(node->step_id);
 }

template <class Eval>
void Process<Eval>::VarSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     // do nothing
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct DerefSwitch

template <class Eval>
void Process<Eval>::DerefSwitch::do_ptr(StepId step_id)
 {
  obj->expr_anyptr(step_id,node->arg);
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_sint8(TypeNode_suint<imp_sint8> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_uint8(TypeNode_suint<imp_uint8> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_sint16(TypeNode_suint<imp_sint16> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_uint16(TypeNode_suint<imp_uint16> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_sint32(TypeNode_suint<imp_sint32> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_uint32(TypeNode_suint<imp_uint32> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_sint64(TypeNode_suint<imp_sint64> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_uint64(TypeNode_suint<imp_uint64> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_slen(TypeNode_slen *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_text(TypeNode_text *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_ip(TypeNode_ip *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_array(TypeNode_array *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_array_len(TypeNode_array_len *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_fields(TypeNode_fields *type_node)
 {
  StepId step_id=obj->eval.set_temp_ptr();
  
  do_ptr(step_id.arg1());
  
  obj->deref_fields(node->step_id,type_node,step_id,node);
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_struct(StructNode *struct_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,struct_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_ptr(TypeNode_ptr *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_anyptr(TypeNode_anyptr *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  do_ptr(node->step_id);
 }

template <class Eval>
void Process<Eval>::DerefSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct PtrSelectSwitch

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_ptr(StepId step_id)
 {
  StepId step1_id=obj->eval.select(step_id,node->name,node);
 
  obj->expr_anyptr(step1_id.arg1(),node->arg);
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_sint8(TypeNode_suint<imp_sint8> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_uint8(TypeNode_suint<imp_uint8> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_sint16(TypeNode_suint<imp_sint16> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_uint16(TypeNode_suint<imp_uint16> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_sint32(TypeNode_suint<imp_sint32> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_uint32(TypeNode_suint<imp_uint32> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_sint64(TypeNode_suint<imp_sint64> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_uint64(TypeNode_suint<imp_uint64> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_slen(TypeNode_slen *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_text(TypeNode_text *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_ip(TypeNode_ip *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_array(TypeNode_array *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_array_len(TypeNode_array_len *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_fields(TypeNode_fields *type_node)
 {
  StepId step_id=obj->eval.set_temp_ptr();
  
  do_ptr(step_id.arg1());
  
  obj->deref_fields(node->step_id,type_node,step_id,node);
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_struct(StructNode *struct_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,struct_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_ptr(TypeNode_ptr *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_anyptr(TypeNode_anyptr *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  do_ptr(node->step_id);
 }

template <class Eval>
void Process<Eval>::PtrSelectSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct SelectSwitch

template <class Eval>
void Process<Eval>::SelectSwitch::do_ptr(StepId step_id)
 {
  StepId step1_id=obj->eval.select(step_id,node->name,node);

  obj->expr_LVPtr(step1_id.arg1(),node->arg);
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_sint8(TypeNode_suint<imp_sint8> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_uint8(TypeNode_suint<imp_uint8> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_sint16(TypeNode_suint<imp_sint16> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_uint16(TypeNode_suint<imp_uint16> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_sint32(TypeNode_suint<imp_sint32> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_uint32(TypeNode_suint<imp_uint32> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_sint64(TypeNode_suint<imp_sint64> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_uint64(TypeNode_suint<imp_uint64> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_slen(TypeNode_slen *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_text(TypeNode_text *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_ip(TypeNode_ip *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_array(TypeNode_array *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_array_len(TypeNode_array_len *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_fields(TypeNode_fields *type_node)
 {
  StepId step_id=obj->eval.set_temp_ptr();
  
  do_ptr(step_id.arg1());
  
  obj->deref_fields(node->step_id,type_node,step_id,node);
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_struct(StructNode *struct_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,struct_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_ptr(TypeNode_ptr *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_anyptr(TypeNode_anyptr *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  do_ptr(node->step_id);
 }

template <class Eval>
void Process<Eval>::SelectSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // struct IndSwitch

template <class Eval>
void Process<Eval>::IndSwitch::do_ptr(StepId step_id)
 {
  StepId step1_id=obj->eval.add_ptr_slen(step_id,node);
  
  if( node->arg1->ptrto_type )
    {
     obj->expr_anyptr(step1_id.arg1(),node->arg1);
     obj->expr_slen(step1_id.arg2(),node->arg2);
    }
  else
    {
     obj->expr_anyptr(step1_id.arg1(),node->arg2);
     obj->expr_slen(step1_id.arg2(),node->arg1);
    }
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_sint8(TypeNode_suint<imp_sint8> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_uint8(TypeNode_suint<imp_uint8> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_sint16(TypeNode_suint<imp_sint16> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_uint16(TypeNode_suint<imp_uint16> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_sint32(TypeNode_suint<imp_sint32> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_uint32(TypeNode_suint<imp_uint32> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_sint64(TypeNode_suint<imp_sint64> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_uint64(TypeNode_suint<imp_uint64> *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_slen(TypeNode_slen *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_text(TypeNode_text *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_ip(TypeNode_ip *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_array(TypeNode_array *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_array_len(TypeNode_array_len *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_fields(TypeNode_fields *type_node)
 {
  StepId step_id=obj->eval.set_temp_ptr();
  
  do_ptr(step_id.arg1());
  
  obj->deref_fields(node->step_id,type_node,step_id,node);
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_struct(StructNode *struct_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,struct_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_struct(TypeNode_struct *type_node)
 {
  do_struct(type_node->base_struct);
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_ref(TypeNode_ref *type_node)
 {
  if( AliasNode *alias=type_node->alias_node )
    {
     alias->result_type->dispatch(*this);
    }
  else
    {
     do_struct(type_node->struct_node);
    }
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_ptr(TypeNode_ptr *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_anyptr(TypeNode_anyptr *type_node)
 {
  StepId step_id=obj->eval.cast_deref(node->step_id,type_node,node);
  
  do_ptr(step_id.arg1());
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_LVPtr(TypeNode_LVPtr *)
 {
  do_ptr(node->step_id);
 }

template <class Eval>
void Process<Eval>::IndSwitch::do_void(TypeNode_void *type_node)
 {
  if( type_node->skip )
    {
     obj->expr_skip(node->arg1); 
     obj->expr_skip(node->arg2);
    }
  else
    {
     obj->eval.error_void("isolated expression",node);
    }
 }

 // methods

template <class Eval>
void Process<Eval>::expr_void(ExprNode &node)
 {
  node.step_id=StepId();
  node.ret_type=void_type;
 }

template <class Eval>
void Process<Eval>::expr(ConstNode &node)
 {
  StepId step_id=eval.set_const(node.index,node.type_node,&node);
  
  expr(step_id.arg1(),node.type_node,node.expr_node);
 }

template <class Eval>
void Process<Eval>::expr(LenNode &node)
 {
  StepId step_id=eval.set_len(node.index,&node);
  
  expr_ulen(step_id.arg1(),node.expr_node);
 }

template <class Eval>
void Process<Eval>::expr(FieldNode &field)
 {
  StepId step_id=eval.set_def_field(field.index,field.type_node);

  expr(step_id.arg1(),field.type_node,field.expr_node);
 }

template <class Eval>
void Process<Eval>::do_expr(ExprNode &node)
 {
  node.dispatch(*this);
 }

template <class Eval>
void Process<Eval>::expr_skip(ExprNode *expr_node)
 {
  expr_node->step_id=StepId();
  expr_node->ret_type=skip_type;
 }

template <class Eval>
void Process<Eval>::expr(StepId step_id,TypeNode *type_node,ExprNode *expr_node)
 {
  expr_node->step_id=step_id;
  expr_node->ret_type=type_node;
 }

template <class Eval>
void Process<Eval>::do_expr_null(StepId step_id,TypeNode *type,ExprNode *node)
 {
  ts_donull.step_id=step_id;
  ts_donull.node=node;
  
  type->dispatch(ts_donull);
 }

template <class Eval>
void Process<Eval>::deref_fields(StepId step_id,TypeNode_fields *type_node,StepId ptr_id,ExprNode *node)
 {
  if( TypeNode *LV_type=node->LV_type )
    {
     if( StructNode *src_struct=fft.structType(LV_type) )
       {
        StructNode *struct_node=type_node->struct_node;
        bool *flags=type_node->flags;

        for(FieldNode &field : struct_node->field_list )
          {
           if( flags[field.field_index] )
             {
              if( src_struct->find(field.name) )
                {
                 StepId step1_id=eval.cast_deref(step_id.argInd(field.field_index),field.type_node,node);
                 
                 StepId step2_id=eval.select(step1_id.arg1(),field.name,node);
                 
                 eval.temp(step2_id.arg1(),ptr_id);
                }
              else
                {
                 eval.def_field(step_id.argInd(field.field_index),field.index,node);
                }
             }
          }
       }
     else
       {
        eval.error_void("expression is not a struct",node);
       }
    }
  else
    {
     eval.error_void("expression is not an LValue",node);
    }
 }

template <class Eval>
Eval & Process<Eval>::operator () (BodyNode *body,const BaseList<ExprNode> &expr_list)
 {
  initTypes();
  
  // set indexes
  
  {
   ulen index=0;
  
   for(ConstNode &node : body->const_list ) node.index=index++;
   
   eval.setConstCount(index);
  }
  
  {
   ulen index=0;
   
   for(LenNode &node : body->len_list ) node.index=index++;
  
   eval.setLenCount(index);
  }
  
  {
   ulen index=0;
   
   for(StructNode &node : body->struct_list )
     {
      ulen field_index=0;
      
      for(FieldNode &field : node.field_list )
        {
         field.index=index++;
         field.field_index=field_index++;
        }
     }
   
   eval.setFieldCount(index);
  }
  
  // clean expr_list
  
  for(ExprNode &node : expr_list ) expr_void(node);
  
  // run variables 
  
  for(ConstNode &node : body->const_list ) expr(node); 
  
  for(LenNode &node : body->len_list ) expr(node);
  
  for(StructNode &node : body->struct_list )
    for(FieldNode &field : node.field_list )
      expr(field); 
  
  // run expr_list
  
  for(ExprNode &node : expr_list ) do_expr(node);
  
  // complete
  
  eval.complete();
  
  return eval;
 }

} // namespace DDL
} // namespace CCore

#endif

