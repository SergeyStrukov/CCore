/* DDLEval.h */
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

#ifndef CCore_inc_ddl_DDLEval_h
#define CCore_inc_ddl_DDLEval_h

#include <CCore/inc/ddl/DDLStep.h>
#include <CCore/inc/ddl/DDLProcess.h>

namespace CCore {
namespace DDL {

/* functions */

void GuardCast();

void GuardArg();

/* classes */

template <template <class T> class A,class ... TT> struct MultiSelect;

class Eval;

struct ConstResult;

struct LenResult;

/* struct MultiSelect<A,TT> */

template <template <class> class A,class T,class ... TT> 
struct MultiSelect<A,T,TT...> : MultiSelect<A,TT...> 
 {
  A<T> obj;
  
  template <class ... SS>
  explicit MultiSelect(SS && ... ss) : MultiSelect<A,TT...>(ss...),obj( std::forward<SS>(ss)... ) {}
  
  struct Take_first
   {
    static A<T> & Do(MultiSelect<A,T,TT...> *ms) { return ms->obj; }
   };
  
  template <class S>
  struct Take_rest
   {
    static A<S> & Do(MultiSelect<A,T,TT...> *ms) { return ((MultiSelect<A,TT...> *)ms)->template take<S>(); }
   };
  
  template <class S>
  using Take = Meta::Select<( std::is_same<S,T>::value ), Take_first , Take_rest<S> > ;
  
  template <class S>
  A<S> & take() { return Take<S>::Do(this); }
 };

template <template <class> class A> 
struct MultiSelect<A>
 {
  template <class ... SS>
  explicit MultiSelect(SS && ...) {}
 };

/* class Eval */

class Eval : NoCopy
 {
   ElementPool &pool;
   PrintBase &msg;
   bool error_flag;
   ulen error_cap;
   
   DynArray<ConstRec,ArrayAlgo_mini<ConstRec> > const_list;
   DynArray<FieldRec,ArrayAlgo_mini<FieldRec> > field_list;
   DynArray<LenRec,ArrayAlgo_mini<LenRec> > len_list;
   
   StepTop ready_list;
   StepTop2 pending_list;
   
   FindFieldType fft;
   TypeCompare type_compare;
   Value blank;
   
  private:
   
   void setReady(Step *step)
    {
     pending_list.del(step);
     
     ready_list.ins(step);
    }
   
   StepId blankStep() { return 0; }
   
   template <class T,class ... SS>
   StepId addStep(SS && ... ss)
    {
     Step *step=pool.create<T>( std::forward<SS>(ss)... );
     
     if( step->count )
       pending_list.ins(step);
     else
       ready_list.ins(step);
     
     return step;
    }
   
   bool loop();
   
  public:
   
   Step * getStep(StepId step_id) 
    {
     return step_id.step; 
    }
   
   Value * setArg(Step *step,ulen arg)
    {
     if( !arg ) GuardArg();
     
     Value *ret=step->args+(arg-1);
        
     if( !--step->count ) setReady(step);
        
     return ret;
    }
   
   Value * setArg(StepId step_id)
    {
     if( Step *step=getStep(step_id) )
       {
        return setArg(step,step_id.arg);
       }
     else
       {
        return &blank;
       }
    }

  private:
   
   template <class Type>
   void set_null(StepId step_id,ExprNode *)
    {
     Type result{};
       
     setArg(step_id)->set<Type>(result);
    }
   
   void set_null_ptr(StepId step_id,TypeNode *type,ExprNode *)
    {
     Ptr result(type);
       
     setArg(step_id)->set<Ptr>(result);
    }
   
   template <class Type>
   void set_number(StepId step_id,ExprNode_number *node)
    {
     Type number=StrToInt<Type>(node->ops.token);
     
     if( CheckResult(number) )
       {
        setArg(step_id)->set<Type>(number);
       }
     else
       {
        error_void("slen overflow",node);
       }
    }
   
   void set_str(StepId step_id,StrLen str,ExprNode *)
    {
     Text text(str);
     
     setArg(step_id)->set<Text>(text);
    }
   
   void set_ip(StepId step_id,ExprNode_ip *node)
    {
     IP ip(StrToInt<uint8>(node->token1),StrToInt<uint8>(node->token2),
           StrToInt<uint8>(node->token3),StrToInt<uint8>(node->token4));
     
     setArg(step_id)->set<IP>(ip);
    }
   
  private:
   
   template <class Type>
   struct AddCast : ExtTypeSwitch
    {
     Eval *eval;
     StepId step_id;
     ExprNode *node;
     
     explicit AddCast(Eval *eval_) : ExtTypeSwitch(this),eval(eval_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { step_id=eval->addStep<Step_cast<Type,imp_sint8> >(step_id,node); }
     void do_uint8(TypeNode_suint<imp_uint8> *) { step_id=eval->addStep<Step_cast<Type,imp_uint8> >(step_id,node); }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { step_id=eval->addStep<Step_cast<Type,imp_sint16> >(step_id,node); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { step_id=eval->addStep<Step_cast<Type,imp_uint16> >(step_id,node); }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { step_id=eval->addStep<Step_cast<Type,imp_sint32> >(step_id,node); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { step_id=eval->addStep<Step_cast<Type,imp_uint32> >(step_id,node); }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { step_id=eval->addStep<Step_cast<Type,imp_sint64> >(step_id,node); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { step_id=eval->addStep<Step_cast<Type,imp_uint64> >(step_id,node); }
     
     void do_slen(TypeNode_slen *) { step_id=eval->addStep<Step_cast<Type,SLen> >(step_id,node); }
     
     void do_text(TypeNode_text *) { GuardCast(); }
     void do_ip(TypeNode_ip *) { GuardCast(); }
     
     void do_ptr(TypeNode_ptr *) { GuardCast(); }
     void do_array(TypeNode_array *) { GuardCast(); }
     void do_array_len(TypeNode_array_len *) { GuardCast(); }
     void do_struct(TypeNode_struct *) { GuardCast(); }
     
     void do_ref(TypeNode_ref *type_node)
      {
       if( AliasNode *alias=type_node->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          GuardCast(); 
         }
      }
     
     void do_fields(TypeNode_fields *) { GuardCast(); }
     void do_anyptr(TypeNode_anyptr *) { GuardCast(); }
     void do_LVPtr(TypeNode_LVPtr *) { GuardCast(); }
     void do_void(TypeNode_void *) { GuardCast(); }
    };
   
   MultiSelect<AddCast,imp_sint8,imp_uint8,imp_sint16,imp_uint16,
                       imp_sint32,imp_uint32,imp_sint64,imp_uint64,
                       SLen> add_cast_ms;
   
   template <class Type>
   StepId cast_int(StepId step_id,TypeNode *src_type,ExprNode *node) // int type
    {
     auto &obj=add_cast_ms.take<Type>();
     
     obj.step_id=step_id;
     obj.node=node;
     
     src_type->dispatch(obj);
     
     return obj.step_id;
    }
   
   struct AddCastText : ExtTypeSwitch
    {
     Eval *eval;
     StepId step_id;
     ExprNode *node;
     
     explicit AddCastText(Eval *eval_) : ExtTypeSwitch(this),eval(eval_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { step_id=eval->addStep<Step_cast_text<imp_sint8> >(step_id,node); }
     void do_uint8(TypeNode_suint<imp_uint8> *) { step_id=eval->addStep<Step_cast_text<imp_uint8> >(step_id,node); }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { step_id=eval->addStep<Step_cast_text<imp_sint16> >(step_id,node); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { step_id=eval->addStep<Step_cast_text<imp_uint16> >(step_id,node); }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { step_id=eval->addStep<Step_cast_text<imp_sint32> >(step_id,node); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { step_id=eval->addStep<Step_cast_text<imp_uint32> >(step_id,node); }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { step_id=eval->addStep<Step_cast_text<imp_sint64> >(step_id,node); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { step_id=eval->addStep<Step_cast_text<imp_uint64> >(step_id,node); }
     
     void do_slen(TypeNode_slen *) { step_id=eval->addStep<Step_cast_text<SLen> >(step_id,node); }
     
     void do_text(TypeNode_text *) { GuardCast(); }
     void do_ip(TypeNode_ip *) { GuardCast(); }
     
     void do_ptr(TypeNode_ptr *) { GuardCast(); }
     void do_array(TypeNode_array *) { GuardCast(); }
     void do_array_len(TypeNode_array_len *) { GuardCast(); }
     void do_struct(TypeNode_struct *) { GuardCast(); }
     
     void do_ref(TypeNode_ref *type_node)
      {
       if( AliasNode *alias=type_node->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          GuardCast(); 
         }
      }
     
     void do_fields(TypeNode_fields *) { GuardCast(); }
     void do_anyptr(TypeNode_anyptr *) { GuardCast(); }
     void do_LVPtr(TypeNode_LVPtr *) { GuardCast(); }
     void do_void(TypeNode_void *) { GuardCast(); }
    };
   
   AddCastText ts_cast_text;
   
  private:
   
   template <class Type>
   struct ToIntCast : ExtTypeSwitch
    {
     Eval *eval;
     StepId step_id;
     Value val;
     ExprNode *node;
     
     template <class SrcType>
     void complete()
      {
       Type result( val.get<SrcType>() );

       if( CheckResult(result) )
         {
          eval->setArg(step_id)->set<Type>(result);
         }
       else
         {
          eval->error_void("slen overflow",node);
         }
      }
     
     explicit ToIntCast(Eval *eval_) : ExtTypeSwitch(this),eval(eval_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { complete<imp_sint8>(); }
     void do_uint8(TypeNode_suint<imp_uint8> *) { complete<imp_uint8>(); }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { complete<imp_sint16>(); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { complete<imp_uint16>(); }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { complete<imp_sint32>(); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { complete<imp_uint32>(); }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { complete<imp_sint64>(); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { complete<imp_uint64>(); }
     
     void do_slen(TypeNode_slen *) { complete<SLen>(); }
     
     void do_text(TypeNode_text *) { eval->error_void("cannot cast text to int",node); }
     void do_ip(TypeNode_ip *) { eval->error_void("cannot cast ip to int",node); }
     
     void do_ptr(TypeNode_ptr *) { eval->error_void("cannot cast pointer to int",node); }
     void do_anyptr(TypeNode_anyptr *) { eval->error_void("cannot cast pointer to int",node); }
     void do_array(TypeNode_array *) { eval->error_void("cannot cast array to int",node); }
     void do_array_len(TypeNode_array_len *) { eval->error_void("cannot cast array to int",node); }
     void do_struct(TypeNode_struct *) { eval->error_void("cannot cast struct to int",node); }
     
     void do_ref(TypeNode_ref *type_node)
      {
       if( AliasNode *alias=type_node->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          eval->error_void("cannot cast struct to int",node);
         }
      }
     
     void do_fields(TypeNode_fields *) { GuardCast(); }
     void do_LVPtr(TypeNode_LVPtr *) { GuardCast(); }
     void do_void(TypeNode_void *) { GuardCast(); }
    };
   
   MultiSelect<ToIntCast,imp_sint8,imp_uint8,imp_sint16,imp_uint16,
                         imp_sint32,imp_uint32,imp_sint64,imp_uint64,
                         SLen> to_int_cast_ms;
   
   template <class Type>
   void cast_to_int(StepId step_id,Ptr ptr,ExprNode *node)
    {
     StepId step1_id=addStep<Step_cast_to_int<Type> >(step_id,node);
     
     bindPtr(step1_id.arg1(),ptr,node);
    }
   
   struct ToTextCast : ExtTypeSwitch
    {
     Eval *eval;
     StepId step_id;
     Value val;
     ExprNode *node;
     
     template <class Type>
     void complete()
      {
       Text result=eval->makeText( val.get<Type>() );
       
       eval->setArg(step_id)->set<Text>(result);
      }
     
     explicit ToTextCast(Eval *eval_) : ExtTypeSwitch(this),eval(eval_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { complete<imp_sint8>(); }
     void do_uint8(TypeNode_suint<imp_uint8> *) { complete<imp_uint8>(); }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { complete<imp_sint16>(); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { complete<imp_uint16>(); }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { complete<imp_sint32>(); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { complete<imp_uint32>(); }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { complete<imp_sint64>(); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { complete<imp_uint64>(); }
     
     void do_slen(TypeNode_slen *) { complete<SLen>(); }
     
     void do_text(TypeNode_text *) { eval->setArg(step_id)->copy(val); }
     
     void do_ip(TypeNode_ip *) { complete<IP>(); }
     
     void do_ptr(TypeNode_ptr *) { eval->error_void("cannot cast ptr to text",node); }
     void do_anyptr(TypeNode_anyptr *) { eval->error_void("cannot cast ptr to text",node); }
     void do_array(TypeNode_array *) { eval->error_void("cannot cast array to text",node); }
     void do_array_len(TypeNode_array_len *) { eval->error_void("cannot cast array to text",node); }
     void do_struct(TypeNode_struct *) { eval->error_void("cannot cast struct to text",node); }
     
     void do_ref(TypeNode_ref *type_node)
      {
       if( AliasNode *alias=type_node->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          eval->error_void("cannot cast struct to text",node);
         }
      }
     
     void do_fields(TypeNode_fields *) { GuardCast(); }
     void do_LVPtr(TypeNode_LVPtr *) { GuardCast(); }
     void do_void(TypeNode_void *) { GuardCast(); }
    };
   
   ToTextCast ts_to_text;
   
   void cast_to_text(StepId step_id,Ptr ptr,ExprNode *node)
    {
     StepId step1_id=addStep<Step_cast_to_text>(step_id,node);
     
     bindPtr(step1_id.arg1(),ptr,node);
    }
   
   struct ToIPCast : ExtTypeSwitch
    {
     Eval *eval;
     StepId step_id;
     Value val;
     ExprNode *node;
     
     explicit ToIPCast(Eval *eval_) : ExtTypeSwitch(this),eval(eval_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { eval->error_void("cannot cast int to ip",node); }
     void do_uint8(TypeNode_suint<imp_uint8> *) { eval->error_void("cannot cast int to ip",node); }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { eval->error_void("cannot cast int to ip",node); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { eval->error_void("cannot cast int to ip",node); }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { eval->error_void("cannot cast int to ip",node); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { eval->error_void("cannot cast int to ip",node); }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { eval->error_void("cannot cast int to ip",node); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { eval->error_void("cannot cast int to ip",node); }
     
     void do_slen(TypeNode_slen *) { eval->error_void("cannot cast int to ip",node); }
     
     void do_text(TypeNode_text *) { eval->error_void("cannot cast text to ip",node); }
     
     void do_ip(TypeNode_ip *) { eval->setArg(step_id)->copy(val); }
     
     void do_ptr(TypeNode_ptr *) { eval->error_void("cannot cast pointer to ip",node); }
     void do_anyptr(TypeNode_anyptr *) { eval->error_void("cannot cast pointer to ip",node); }
     void do_array(TypeNode_array *) { eval->error_void("cannot cast array to ip",node); }
     void do_array_len(TypeNode_array_len *) { eval->error_void("cannot cast array to ip",node); }
     void do_struct(TypeNode_struct *) { eval->error_void("cannot cast struct to ip",node); }
     
     void do_ref(TypeNode_ref *type_node)
      {
       if( AliasNode *alias=type_node->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          eval->error_void("cannot cast struct to ip",node);
         }
      }
     
     void do_fields(TypeNode_fields *) { GuardCast(); }
     void do_LVPtr(TypeNode_LVPtr *) { GuardCast(); }
     void do_void(TypeNode_void *) { GuardCast(); }
    };
   
   ToIPCast ts_to_ip;
   
   void cast_to_ip(StepId step_id,Ptr ptr,ExprNode *node)
    {
     StepId step1_id=addStep<Step_cast_to_ip>(step_id,node);
     
     bindPtr(step1_id.arg1(),ptr,node);
    }
   
   struct ToArrayCast : ExtTypeSwitch
    {
     Eval *eval;
     StepId step_id;
     Value val;
     TypeNode *type;
     ExprNode *node;
     
     explicit ToArrayCast(Eval *eval_) : ExtTypeSwitch(this),eval(eval_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { eval->error_void("cannot cast int to array",node); }
     void do_uint8(TypeNode_suint<imp_uint8> *) { eval->error_void("cannot cast int to array",node); }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { eval->error_void("cannot cast int to array",node); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { eval->error_void("cannot cast int to array",node); }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { eval->error_void("cannot cast int to array",node); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { eval->error_void("cannot cast int to array",node); }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { eval->error_void("cannot cast int to array",node); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { eval->error_void("cannot cast int to array",node); }
     
     void do_slen(TypeNode_slen *) { eval->error_void("cannot cast int to array",node); }
     
     void do_text(TypeNode_text *) { eval->error_void("cannot cast text to array",node); }
     void do_ip(TypeNode_ip *) { eval->error_void("cannot cast ip to array",node); }
     
     void do_ptr(TypeNode_ptr *) { eval->error_void("cannot cast pointer to array",node); }
     void do_anyptr(TypeNode_anyptr *) { eval->error_void("cannot cast pointer to array",node); }
     
     void do_array(TypeNode_array *type_node) { eval->copyIf(step_id,val,type,type_node->type_node,node); }
     void do_array_len(TypeNode_array_len *type_node) { eval->copyIf(step_id,val,type,type_node->type_node,node); }
     
     void do_struct(TypeNode_struct *) { eval->error_void("cannot cast struct to array",node); }
     
     void do_ref(TypeNode_ref *type_node)
      {
       if( AliasNode *alias=type_node->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          eval->error_void("cannot cast struct to array",node);
         }
      }
     
     void do_fields(TypeNode_fields *) { GuardCast(); }
     void do_LVPtr(TypeNode_LVPtr *) { GuardCast(); }
     void do_void(TypeNode_void *) { GuardCast(); }
    };
   
   ToArrayCast ts_to_array;
   
   void cast_to_array(TypeNode_array *type,StepId step_id,Ptr ptr,ExprNode *node)
    {
     StepId step1_id=addStep<Step_cast_to_array>(step_id,type,node);
     
     bindPtr(step1_id.arg1(),ptr,node);
    }
   
   struct ToArrayLenCast : ExtTypeSwitch
    {
     Eval *eval;
     StepId step_id;
     Value val;
     TypeNode_array_len *type;
     ExprNode *node;
     
     explicit ToArrayLenCast(Eval *eval_) : ExtTypeSwitch(this),eval(eval_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { eval->error_void("cannot cast int to array",node); }
     void do_uint8(TypeNode_suint<imp_uint8> *) { eval->error_void("cannot cast int to array",node); }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { eval->error_void("cannot cast int to array",node); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { eval->error_void("cannot cast int to array",node); }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { eval->error_void("cannot cast int to array",node); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { eval->error_void("cannot cast int to array",node); }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { eval->error_void("cannot cast int to array",node); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { eval->error_void("cannot cast int to array",node); }
     
     void do_slen(TypeNode_slen *) { eval->error_void("cannot cast int to array",node); }
     
     void do_text(TypeNode_text *) { eval->error_void("cannot cast text to array",node); }
     void do_ip(TypeNode_ip *) { eval->error_void("cannot cast ip to array",node); }
     
     void do_ptr(TypeNode_ptr *) { eval->error_void("cannot cast pointer to array",node); }
     void do_anyptr(TypeNode_anyptr *) { eval->error_void("cannot cast pointer to array",node); }
     
     void do_array(TypeNode_array *type_node) { eval->copyIf(step_id,val,type,type_node->type_node,val.get<Block>().data.len,node); }
     void do_array_len(TypeNode_array_len *type_node) { eval->copyIf(step_id,val,type,type_node,node); }
     
     void do_struct(TypeNode_struct *) { eval->error_void("cannot cast struct to array",node); }
     
     void do_ref(TypeNode_ref *type_node)
      {
       if( AliasNode *alias=type_node->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          eval->error_void("cannot cast struct to array",node);
         }
      }
     
     void do_fields(TypeNode_fields *) { GuardCast(); }
     void do_LVPtr(TypeNode_LVPtr *) { GuardCast(); }
     void do_void(TypeNode_void *) { GuardCast(); }
    };
   
   ToArrayLenCast ts_to_array_len;
   
   void cast_to_array_len(TypeNode_array_len *type,StepId step_id,Ptr ptr,ExprNode *node)
    {
     StepId step1_id=addStep<Step_cast_to_array_len>(step_id,type,node);
     
     bindPtr(step1_id.arg1(),ptr,node);
    }
   
   struct ToAnyPtrCast : ExtTypeSwitch
    {
     Eval *eval;
     StepId step_id;
     Ptr ptr;
     ExprNode *node;
     
     void copy_deref()
      {
       StepId step1_id=eval->addStep<Step_copy_deref>(step_id,node);
       
       eval->bindPtr(step1_id.arg1(),ptr,node);
      }
     
     void decay(TypeNode *array_type,TypeNode *elem_type)
      {
       Ptr result=eval->decay(ptr,array_type,elem_type,node);
       
       eval->setArg(step_id)->set<Ptr>(result);
      }
     
     explicit ToAnyPtrCast(Eval *eval_) : ExtTypeSwitch(this),eval(eval_),ptr(0) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { eval->error_void("cannot cast int to pointer",node); }
     void do_uint8(TypeNode_suint<imp_uint8> *) { eval->error_void("cannot cast int to pointer",node); }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { eval->error_void("cannot cast int to pointer",node); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { eval->error_void("cannot cast int to pointer",node); }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { eval->error_void("cannot cast int to pointer",node); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { eval->error_void("cannot cast int to pointer",node); }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { eval->error_void("cannot cast int to pointer",node); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { eval->error_void("cannot cast int to pointer",node); }
     
     void do_slen(TypeNode_slen *) { eval->error_void("cannot cast int to pointer",node); }
     
     void do_text(TypeNode_text *) { eval->error_void("cannot cast text to pointer",node); }
     void do_ip(TypeNode_ip *) { eval->error_void("cannot cast ip to pointer",node); }
     
     void do_ptr(TypeNode_ptr *) { copy_deref(); }
     void do_anyptr(TypeNode_anyptr *) { copy_deref(); }
     
     void do_array(TypeNode_array *type_node) { decay(type_node,type_node->type_node); }
     void do_array_len(TypeNode_array_len *type_node) { decay(type_node,type_node->type_node); }
     
     void do_struct(TypeNode_struct *) { eval->error_void("cannot cast struct to pointer",node); }
     
     void do_ref(TypeNode_ref *type_node)
      {
       if( AliasNode *alias=type_node->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          eval->error_void("cannot cast struct to pointer",node);
         }
      }
     
     void do_fields(TypeNode_fields *) { GuardCast(); }
     void do_LVPtr(TypeNode_LVPtr *) { GuardCast(); }
     void do_void(TypeNode_void *) { GuardCast(); }
    };
   
   ToAnyPtrCast ts_to_anyptr;
   
   void cast_to_anyptr(StepId step_id,Ptr ptr,ExprNode *node)
    {
     ts_to_anyptr.step_id=step_id;
     ts_to_anyptr.ptr=ptr;
     ts_to_anyptr.node=node;
     
     ptr.type->dispatch(ts_to_anyptr);
    }
   
   struct ToPtrCast : ExtTypeSwitch
    {
     Eval *eval;
     StepId step_id;
     Ptr ptr;
     TypeNode_ptr *type;
     ExprNode *node;
     
     void copy_deref()
      {
       StepId step1_id=eval->addStep<Step_copyif_deref>(step_id,type,ptr.type,node);
       
       eval->bindPtr(step1_id.arg1(),ptr,node);
      }
     
     void decay(TypeNode *array_type,TypeNode *elem_type)
      {
       Ptr result=eval->decay(ptr,array_type,elem_type,node);
       
       Value val;
       
       val.set<Ptr>(result);
       
       eval->copyIf(step_id,val,type->type_node,elem_type,node);
      }
     
     explicit ToPtrCast(Eval *eval_) : ExtTypeSwitch(this),eval(eval_),ptr(0) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { eval->error_void("cannot cast int to pointer",node); }
     void do_uint8(TypeNode_suint<imp_uint8> *) { eval->error_void("cannot cast int to pointer",node); }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { eval->error_void("cannot cast int to pointer",node); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { eval->error_void("cannot cast int to pointer",node); }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { eval->error_void("cannot cast int to pointer",node); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { eval->error_void("cannot cast int to pointer",node); }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { eval->error_void("cannot cast int to pointer",node); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { eval->error_void("cannot cast int to pointer",node); }
     
     void do_slen(TypeNode_slen *) { eval->error_void("cannot cast int to pointer",node); }
     
     void do_text(TypeNode_text *) { eval->error_void("cannot cast text to pointer",node); }
     void do_ip(TypeNode_ip *) { eval->error_void("cannot cast ip to pointer",node); }
     
     void do_ptr(TypeNode_ptr *) { copy_deref(); }
     void do_anyptr(TypeNode_anyptr *) { copy_deref(); }
     
     void do_array(TypeNode_array *type_node) { decay(type_node,type_node->type_node); }
     void do_array_len(TypeNode_array_len *type_node) { decay(type_node,type_node->type_node); }
     
     void do_struct(TypeNode_struct *) { eval->error_void("cannot cast struct to pointer",node); }
     
     void do_ref(TypeNode_ref *type_node)
      {
       if( AliasNode *alias=type_node->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          eval->error_void("cannot cast struct to pointer",node);
         }
      }
     
     void do_fields(TypeNode_fields *) { GuardCast(); }
     void do_LVPtr(TypeNode_LVPtr *) { GuardCast(); }
     void do_void(TypeNode_void *) { GuardCast(); }
    };
   
   ToPtrCast ts_to_ptr;
   
   void cast_to_ptr(TypeNode_ptr *type,StepId step_id,Ptr ptr,ExprNode *node)
    {
     ts_to_ptr.step_id=step_id;
     ts_to_ptr.ptr=ptr;
     ts_to_ptr.type=type;
     ts_to_ptr.node=node;
     
     ptr.type->dispatch(ts_to_ptr);
    }
   
   struct ValueCast : ExtTypeSwitch
    {
     Eval *eval;
     StepId step_id;
     Ptr ptr;
     ExprNode *node;
     
     explicit ValueCast(Eval *eval_) : ExtTypeSwitch(this),eval(eval_),ptr(0) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { eval->cast_to_int<imp_sint8>(step_id,ptr,node); }
     void do_uint8(TypeNode_suint<imp_uint8> *) { eval->cast_to_int<imp_uint8>(step_id,ptr,node); }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { eval->cast_to_int<imp_sint16>(step_id,ptr,node); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { eval->cast_to_int<imp_uint16>(step_id,ptr,node); }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { eval->cast_to_int<imp_sint32>(step_id,ptr,node); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { eval->cast_to_int<imp_uint32>(step_id,ptr,node); }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { eval->cast_to_int<imp_sint64>(step_id,ptr,node); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { eval->cast_to_int<imp_uint64>(step_id,ptr,node); }
     
     void do_slen(TypeNode_slen *) { eval->cast_to_int<SLen>(step_id,ptr,node); }
     
     void do_text(TypeNode_text *) { eval->cast_to_text(step_id,ptr,node); }
     void do_ip(TypeNode_ip *) { eval->cast_to_ip(step_id,ptr,node); }
     
     void do_array(TypeNode_array *type_node) { eval->cast_to_array(type_node,step_id,ptr,node); }
     void do_array_len(TypeNode_array_len *type_node) { eval->cast_to_array_len(type_node,step_id,ptr,node); }
     
     void do_anyptr(TypeNode_anyptr *) { eval->cast_to_anyptr(step_id,ptr,node); }
     void do_ptr(TypeNode_ptr *type_node) { eval->cast_to_ptr(type_node,step_id,ptr,node); }
     
     void do_struct(StructNode *struct_node) { eval->cast_deref(step_id,ptr,struct_node,node); }
     
     void do_struct(TypeNode_struct *type_node) { do_struct(type_node->base_struct); }
     
     void do_ref(TypeNode_ref *type_node)
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
     
     void do_fields(TypeNode_fields *) { GuardCast(); }
     void do_LVPtr(TypeNode_LVPtr *) { GuardCast(); }
     void do_void(TypeNode_void *) { GuardCast(); }
    };
   
   ValueCast ts_cast;
   
  private:
   
   struct NullValSwitch : TypeSwitch
    {
     Eval *eval;
     StepId step_id;
     ExprNode *node;
     
     template <class Type>
     void complete()
      {
       Type result{};
         
       eval->setArg(step_id)->set<Type>(result);
      }
     
     explicit NullValSwitch(Eval *eval_) : TypeSwitch(this),eval(eval_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { complete<imp_sint8>(); } 
     void do_uint8(TypeNode_suint<imp_uint8> *) { complete<imp_uint8>(); }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { complete<imp_sint16>(); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { complete<imp_uint16>(); }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { complete<imp_sint32>(); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { complete<imp_uint32>(); }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { complete<imp_sint64>(); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { complete<imp_uint64>(); }
     
     void do_text(TypeNode_text *) { complete<Text>(); }
     void do_ip(TypeNode_ip *) { complete<IP>(); }
     
     void do_ptr(TypeNode_ptr *type_node) 
      {
       Ptr ptr(type_node->type_node);
       
       eval->setArg(step_id)->set<Ptr>(ptr);
      }
     
     void do_array(TypeNode_array *) { complete<Block>(); } 
     
     void do_array_len(TypeNode_array_len *type_node) { eval->null_array_len(step_id,type_node,node); }
     
     void do_struct(StructNode *struct_node) { eval->addStep<Step_null_struct>(step_id,struct_node,node); }
     
     void do_struct(TypeNode_struct *type_node) { do_struct(type_node->base_struct); }
     
     void do_ref(TypeNode_ref *type_node)
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
    };
   
   NullValSwitch ts_nullval;
   
   struct DefValSwitch : TypeSwitch
    {
     Eval *eval;
     StepId step_id;
     ExprNode *node;
     
     template <class Type>
     void complete()
      {
       Type result{};
         
       eval->setArg(step_id)->set<Type>(result);
      }
     
     explicit DefValSwitch(Eval *eval_) : TypeSwitch(this),eval(eval_) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { complete<imp_sint8>(); } 
     void do_uint8(TypeNode_suint<imp_uint8> *) { complete<imp_uint8>(); }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { complete<imp_sint16>(); }
     void do_uint16(TypeNode_suint<imp_uint16> *) { complete<imp_uint16>(); }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { complete<imp_sint32>(); }
     void do_uint32(TypeNode_suint<imp_uint32> *) { complete<imp_uint32>(); }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { complete<imp_sint64>(); }
     void do_uint64(TypeNode_suint<imp_uint64> *) { complete<imp_uint64>(); }
     
     void do_text(TypeNode_text *) { complete<Text>(); }
     void do_ip(TypeNode_ip *) { complete<IP>(); }
     
     void do_ptr(TypeNode_ptr *type_node) 
      {
       Ptr ptr(type_node->type_node);
       
       eval->setArg(step_id)->set<Ptr>(ptr);
      }
     
     void do_array(TypeNode_array *) { complete<Block>(); }
     
     void do_array_len(TypeNode_array_len *type_node) { eval->def_array_len(step_id,type_node,node); }
     
     void do_struct(StructNode *struct_node) { eval->def_struct(step_id,struct_node,node); }
     
     void do_struct(TypeNode_struct *type_node) { do_struct(type_node->base_struct); }
     
     void do_ref(TypeNode_ref *type_node)
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
    };
   
   DefValSwitch ts_defval;
   
  public:
   
   Eval(ElementPool &pool,PrintBase &msg);
   
   ~Eval();
   
   ElementPool & getPool() { return pool; }
   
   PrintBase & getMsg() { return msg; }
   
   // result
   
   bool operator ! () const { return error_flag; }
   
   ulen getConstCount() const { return const_list.getLen(); }
   
   ConstResult getConstResult(ulen ind) const;
   
   ulen getLenCount() const { return len_list.getLen(); }
   
   LenResult getLenResult(ulen ind) const;
   
   // print object
   
   template <class P>
   void print(P &out) const;

   // methods
   
   void reset()
    {
     error_flag=false;
     error_cap=ErrorMsgCap;
     
     const_list.erase();
     field_list.erase();
     len_list.erase();
     
     ready_list.init();
     pending_list.init();
    }
   
   void setConstCount(ulen count)
    {
     const_list.extend_default(count);
    }
   
   void setFieldCount(ulen count)
    {
     field_list.extend_default(count);
    }
   
   void setLenCount(ulen count)
    {
     len_list.extend_default(count);
    }
   
   StepId set_const(ulen index,TypeNode *type,ConstNode *node)
    {
     return addStep<Step_const>(const_list[index].set(type,node));
    }
   
   StepId set_def_field(ulen index,TypeNode *type)
    {
     return addStep<Step_field>(field_list[index].set(type));
    }
   
   StepId set_len(ulen index,LenNode *node)
    {
     return addStep<Step_len>(len_list[index].set(node));
    }
   
   StepId set_temp_ptr()
    {
     return addStep<Step_ptr>();
    }
   
   void temp(StepId step_id,StepId temp_id)
    {
     Step_ptr *step=static_cast<Step_ptr *>(getStep(temp_id));
     
     step->temp.add(this,addStep<Step_copy>(step_id));
    }
   
   void def_field(StepId step_id,ulen index,ExprNode *)
    {
     field_list[index].add(this,addStep<Step_copy>(step_id));
    }
   
   void complete();
   
   // void
   
   void error_void(StrLen msgtext,ExprNode *node)
    {
     error_flag=true;
     
     if( error_cap )
       {
        error_cap--;
        
        Printf(msg,"Evaluation error : #; -- #;\n",node->ops,msgtext);
       }
    }
   
   // any
   
   void error_any(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   // sint8
   
   void error_sint8(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   StepId plus_sint8(StepId step_id,ExprNode *node) { return addStep<Step_plus<imp_sint8> >(step_id,node); }
   
   StepId minus_sint8(StepId step_id,ExprNode *node) { return addStep<Step_minus<imp_sint8> >(step_id,node); }
   
   StepId add_sint8(StepId step_id,ExprNode *node) { return addStep<Step_add<imp_sint8> >(step_id,node); }
   
   StepId sub_sint8(StepId step_id,ExprNode *node) { return addStep<Step_sub<imp_sint8> >(step_id,node); }
   
   StepId mul_sint8(StepId step_id,ExprNode *node) { return addStep<Step_mul<imp_sint8> >(step_id,node); }
   
   StepId div_sint8(StepId step_id,ExprNode *node) { return addStep<Step_div<imp_sint8> >(step_id,node); }
   
   StepId rem_sint8(StepId step_id,ExprNode *node) { return addStep<Step_rem<imp_sint8> >(step_id,node); }
   
   StepId cast_sint8(StepId step_id,TypeNode *src_type,ExprNode *node) { return cast_int<imp_sint8>(step_id,src_type,node); }
   
   void null_sint8(StepId step_id,ExprNode *node) { set_null<imp_sint8>(step_id,node); }
   
   void number_sint8(StepId step_id,ExprNode_number *node) { set_number<imp_sint8>(step_id,node); }
   
   // uint8
   
   void error_uint8(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   StepId plus_uint8(StepId step_id,ExprNode *node) { return addStep<Step_plus<imp_uint8> >(step_id,node); }
   
   StepId minus_uint8(StepId step_id,ExprNode *node) { return addStep<Step_minus<imp_uint8> >(step_id,node); }
   
   StepId add_uint8(StepId step_id,ExprNode *node) { return addStep<Step_add<imp_uint8> >(step_id,node); }
   
   StepId sub_uint8(StepId step_id,ExprNode *node) { return addStep<Step_sub<imp_uint8> >(step_id,node); }
   
   StepId mul_uint8(StepId step_id,ExprNode *node) { return addStep<Step_mul<imp_uint8> >(step_id,node); }
   
   StepId div_uint8(StepId step_id,ExprNode *node) { return addStep<Step_div<imp_uint8> >(step_id,node); }
   
   StepId rem_uint8(StepId step_id,ExprNode *node) { return addStep<Step_rem<imp_uint8> >(step_id,node); }
   
   StepId cast_uint8(StepId step_id,TypeNode *src_type,ExprNode *node) { return cast_int<imp_uint8>(step_id,src_type,node); }
   
   void null_uint8(StepId step_id,ExprNode *node) { set_null<imp_uint8>(step_id,node); }
   
   void number_uint8(StepId step_id,ExprNode_number *node) { set_number<imp_uint8>(step_id,node); }
   
   // sint16
   
   void error_sint16(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   StepId plus_sint16(StepId step_id,ExprNode *node) { return addStep<Step_plus<imp_sint16> >(step_id,node); }
   
   StepId minus_sint16(StepId step_id,ExprNode *node) { return addStep<Step_minus<imp_sint16> >(step_id,node); }
   
   StepId add_sint16(StepId step_id,ExprNode *node) { return addStep<Step_add<imp_sint16> >(step_id,node); }
   
   StepId sub_sint16(StepId step_id,ExprNode *node) { return addStep<Step_sub<imp_sint16> >(step_id,node); }
   
   StepId mul_sint16(StepId step_id,ExprNode *node) { return addStep<Step_mul<imp_sint16> >(step_id,node); }
   
   StepId div_sint16(StepId step_id,ExprNode *node) { return addStep<Step_div<imp_sint16> >(step_id,node); }
   
   StepId rem_sint16(StepId step_id,ExprNode *node) { return addStep<Step_rem<imp_sint16> >(step_id,node); }
   
   StepId cast_sint16(StepId step_id,TypeNode *src_type,ExprNode *node) { return cast_int<imp_sint16>(step_id,src_type,node); }
   
   void null_sint16(StepId step_id,ExprNode *node) { set_null<imp_sint16>(step_id,node); }
   
   void number_sint16(StepId step_id,ExprNode_number *node) { set_number<imp_sint16>(step_id,node); }
   
   // uint16
   
   void error_uint16(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   StepId plus_uint16(StepId step_id,ExprNode *node) { return addStep<Step_plus<imp_uint16> >(step_id,node); }
   
   StepId minus_uint16(StepId step_id,ExprNode *node) { return addStep<Step_minus<imp_uint16> >(step_id,node); }
   
   StepId add_uint16(StepId step_id,ExprNode *node) { return addStep<Step_add<imp_uint16> >(step_id,node); }
   
   StepId sub_uint16(StepId step_id,ExprNode *node) { return addStep<Step_sub<imp_uint16> >(step_id,node); }
   
   StepId mul_uint16(StepId step_id,ExprNode *node) { return addStep<Step_mul<imp_uint16> >(step_id,node); }
   
   StepId div_uint16(StepId step_id,ExprNode *node) { return addStep<Step_div<imp_uint16> >(step_id,node); }
   
   StepId rem_uint16(StepId step_id,ExprNode *node) { return addStep<Step_rem<imp_uint16> >(step_id,node); }
   
   StepId cast_uint16(StepId step_id,TypeNode *src_type,ExprNode *node) { return cast_int<imp_uint16>(step_id,src_type,node); }
   
   void null_uint16(StepId step_id,ExprNode *node) { set_null<imp_uint16>(step_id,node); }
   
   void number_uint16(StepId step_id,ExprNode_number *node) { set_number<imp_uint16>(step_id,node); }
   
   // sint32
   
   void error_sint32(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   StepId plus_sint32(StepId step_id,ExprNode *node) { return addStep<Step_plus<imp_sint32> >(step_id,node); }
   
   StepId minus_sint32(StepId step_id,ExprNode *node) { return addStep<Step_minus<imp_sint32> >(step_id,node); }
   
   StepId add_sint32(StepId step_id,ExprNode *node) { return addStep<Step_add<imp_sint32> >(step_id,node); }
   
   StepId sub_sint32(StepId step_id,ExprNode *node) { return addStep<Step_sub<imp_sint32> >(step_id,node); }
   
   StepId mul_sint32(StepId step_id,ExprNode *node) { return addStep<Step_mul<imp_sint32> >(step_id,node); }
   
   StepId div_sint32(StepId step_id,ExprNode *node) { return addStep<Step_div<imp_sint32> >(step_id,node); }
   
   StepId rem_sint32(StepId step_id,ExprNode *node) { return addStep<Step_rem<imp_sint32> >(step_id,node); }
   
   StepId cast_sint32(StepId step_id,TypeNode *src_type,ExprNode *node) { return cast_int<imp_sint32>(step_id,src_type,node); }
   
   void null_sint32(StepId step_id,ExprNode *node) { set_null<imp_sint32>(step_id,node); }
   
   void number_sint32(StepId step_id,ExprNode_number *node) { set_number<imp_sint32>(step_id,node); }
   
   // uint32
   
   void error_uint32(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   StepId plus_uint32(StepId step_id,ExprNode *node) { return addStep<Step_plus<imp_uint32> >(step_id,node); }
   
   StepId minus_uint32(StepId step_id,ExprNode *node) { return addStep<Step_minus<imp_uint32> >(step_id,node); }
   
   StepId add_uint32(StepId step_id,ExprNode *node) { return addStep<Step_add<imp_uint32> >(step_id,node); }
   
   StepId sub_uint32(StepId step_id,ExprNode *node) { return addStep<Step_sub<imp_uint32> >(step_id,node); }
   
   StepId mul_uint32(StepId step_id,ExprNode *node) { return addStep<Step_mul<imp_uint32> >(step_id,node); }
   
   StepId div_uint32(StepId step_id,ExprNode *node) { return addStep<Step_div<imp_uint32> >(step_id,node); }
   
   StepId rem_uint32(StepId step_id,ExprNode *node) { return addStep<Step_rem<imp_uint32> >(step_id,node); }
   
   StepId cast_uint32(StepId step_id,TypeNode *src_type,ExprNode *node) { return cast_int<imp_uint32>(step_id,src_type,node); }
   
   void null_uint32(StepId step_id,ExprNode *node) { set_null<imp_uint32>(step_id,node); }
   
   void number_uint32(StepId step_id,ExprNode_number *node) { set_number<imp_uint32>(step_id,node); }
   
   // sint64
   
   void error_sint64(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   StepId plus_sint64(StepId step_id,ExprNode *node) { return addStep<Step_plus<imp_sint64> >(step_id,node); }
   
   StepId minus_sint64(StepId step_id,ExprNode *node) { return addStep<Step_minus<imp_sint64> >(step_id,node); }
   
   StepId add_sint64(StepId step_id,ExprNode *node) { return addStep<Step_add<imp_sint64> >(step_id,node); }
   
   StepId sub_sint64(StepId step_id,ExprNode *node) { return addStep<Step_sub<imp_sint64> >(step_id,node); }
   
   StepId mul_sint64(StepId step_id,ExprNode *node) { return addStep<Step_mul<imp_sint64> >(step_id,node); }
   
   StepId div_sint64(StepId step_id,ExprNode *node) { return addStep<Step_div<imp_sint64> >(step_id,node); }
   
   StepId rem_sint64(StepId step_id,ExprNode *node) { return addStep<Step_rem<imp_sint64> >(step_id,node); }
   
   StepId cast_sint64(StepId step_id,TypeNode *src_type,ExprNode *node) { return cast_int<imp_sint64>(step_id,src_type,node); }
   
   void null_sint64(StepId step_id,ExprNode *node) { set_null<imp_sint64>(step_id,node); }
   
   void number_sint64(StepId step_id,ExprNode_number *node) { set_number<imp_sint64>(step_id,node); }
   
   // uint64
   
   void error_uint64(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   StepId plus_uint64(StepId step_id,ExprNode *node) { return addStep<Step_plus<imp_uint64> >(step_id,node); }
   
   StepId minus_uint64(StepId step_id,ExprNode *node) { return addStep<Step_minus<imp_uint64> >(step_id,node); }
   
   StepId add_uint64(StepId step_id,ExprNode *node) { return addStep<Step_add<imp_uint64> >(step_id,node); }
   
   StepId sub_uint64(StepId step_id,ExprNode *node) { return addStep<Step_sub<imp_uint64> >(step_id,node); }
   
   StepId mul_uint64(StepId step_id,ExprNode *node) { return addStep<Step_mul<imp_uint64> >(step_id,node); }
   
   StepId div_uint64(StepId step_id,ExprNode *node) { return addStep<Step_div<imp_uint64> >(step_id,node); }
   
   StepId rem_uint64(StepId step_id,ExprNode *node) { return addStep<Step_rem<imp_uint64> >(step_id,node); }
   
   StepId cast_uint64(StepId step_id,TypeNode *src_type,ExprNode *node) { return cast_int<imp_uint64>(step_id,src_type,node); }
   
   void null_uint64(StepId step_id,ExprNode *node) { set_null<imp_uint64>(step_id,node); }
   
   void number_uint64(StepId step_id,ExprNode_number *node) { set_number<imp_uint64>(step_id,node); }
   
   // slen
   
   void error_slen(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   StepId plus_slen(StepId step_id,ExprNode *node) { return addStep<Step_plus<SLen> >(step_id,node); }
   
   StepId minus_slen(StepId step_id,ExprNode *node) { return addStep<Step_minus<SLen> >(step_id,node); }
   
   StepId add_slen(StepId step_id,ExprNode *node) { return addStep<Step_add<SLen> >(step_id,node); }
   
   StepId sub_slen(StepId step_id,ExprNode *node) { return addStep<Step_sub<SLen> >(step_id,node); }
   
   StepId mul_slen(StepId step_id,ExprNode *node) { return addStep<Step_mul<SLen> >(step_id,node); }
   
   StepId div_slen(StepId step_id,ExprNode *node) { return addStep<Step_div<SLen> >(step_id,node); }
   
   StepId rem_slen(StepId step_id,ExprNode *node) { return addStep<Step_rem<SLen> >(step_id,node); }
   
   StepId cast_slen(StepId step_id,TypeNode *src_type,ExprNode *node) { return cast_int<SLen>(step_id,src_type,node); }
   
   void null_slen(StepId step_id,ExprNode *node) { set_null<SLen>(step_id,node); }
   
   void number_slen(StepId step_id,ExprNode_number *node) { set_number<SLen>(step_id,node); }
   
   // text
   
   StrLen makeDStr(StrLen str);
   
   StrLen makeStr(const Token &token);
   
   StrLen addText(StrLen a,StrLen b);
   
   Text addText(Text a,Text b) { return addText(a.str,b.str); }
   
   template <class SrcType>
   Text makeText(SrcType val)
    {
     PrintCount<void> count_out;
     
     Putobj(count_out,val);
     
     ulen len=count_out.getCount();
     
     PrintBuf out(pool.createArray_raw<char>(len+1));
     
     Putobj(out,val);
     
     return Text(out.close());
    }
   
   
   void error_text(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   StepId add_text(StepId step_id,ExprNode *node) { return addStep<Step_add_text>(step_id,node); }
   
   StepId cast_text(StepId step_id,TypeNode *src_type,ExprNode *node) // int type 
    {
     ts_cast_text.step_id=step_id;
     ts_cast_text.node=node;
     
     src_type->dispatch(ts_cast_text);
     
     return ts_cast_text.step_id;
    }
   
   StepId cast_text_ip(StepId step_id,ExprNode *node) { return addStep<Step_cast_text<IP> >(step_id,node); }
   
   void null_text(StepId step_id,ExprNode *node) { set_null<Text>(step_id,node); }
   
   void number_text(StepId step_id,ExprNode_number *node) { set_str(step_id,makeStr(node->ops.token),node); }
   
   void string_text(StepId step_id,ExprNode_string *node) { set_str(step_id,makeStr(node->ops.token),node); }
   
   // ip
   
   void error_ip(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   void null_ip(StepId step_id,ExprNode *node) { set_null<IP>(step_id,node); }
   
   void ip(StepId step_id,ExprNode_ip *node) { set_ip(step_id,node); }
   
   // anyptr
   
   Ptr addPtr(Ptr ptr,SLen delta,ExprNode *node);
   
   Ptr subPtr(Ptr ptr,SLen delta,ExprNode *node);
   
   SLen subPtr2(Ptr a,Ptr b,ExprNode *node); // a not null
   
   Ptr select(Ptr ptr,FieldNode *field,ExprNode *node); // ptr not null
   
   Ptr select(Ptr ptr,NameLink &name,ExprNode *node); // ptr not null
   
   Ptr decay(Ptr ptr,TypeNode *array_type,TypeNode *elem_type,ExprNode *node);
   
   void bindConst(PtrNode *ptr_node);
   
   bool bindElem(PtrNode *ptr_node);
   
   void bindPtr(StepId step_id,Ptr ptr,ExprNode *node);
   
   
   template <class Type>
   void cast_to_int(StepId step_id,TypeNode *val_type,const Value &val,ExprNode *node)
    {
     auto &obj=to_int_cast_ms.take<Type>();
     
     obj.step_id=step_id;
     obj.val=val;
     obj.node=node;
     
     val_type->dispatch(obj);
    }
   
   void cast_to_text(StepId step_id,TypeNode *val_type,const Value &val,ExprNode *node)
    {
     ts_to_text.step_id=step_id;
     ts_to_text.val=val;
     ts_to_text.node=node;
     
     val_type->dispatch(ts_to_text);
    }
   
   void cast_to_ip(StepId step_id,TypeNode *val_type,const Value &val,ExprNode *node)
    {
     ts_to_ip.step_id=step_id;
     ts_to_ip.val=val;
     ts_to_ip.node=node;
     
     val_type->dispatch(ts_to_ip);
    }
   
   void cast_to_array(TypeNode_array *type,StepId step_id,TypeNode *val_type,const Value &val,ExprNode *node)
    {
     ts_to_array.step_id=step_id;
     ts_to_array.val=val;
     ts_to_array.type=type->type_node;
     ts_to_array.node=node;
     
     val_type->dispatch(ts_to_array);
    }
   
   void cast_to_array_len(TypeNode_array_len *type,StepId step_id,TypeNode *val_type,const Value &val,ExprNode *node)
    {
     ts_to_array_len.step_id=step_id;
     ts_to_array_len.val=val;
     ts_to_array_len.type=type;
     ts_to_array_len.node=node;

     val_type->dispatch(ts_to_array_len);
    }
   
   void cast_to_struct(StructNode *struct_node,StepId step_id,Ptr ptr,ExprNode *node);
   
   
   void cast_deref(StepId step_id,Ptr ptr,TypeNode *type,ExprNode *node)
    {
     ts_cast.step_id=step_id;
     ts_cast.ptr=ptr;
     ts_cast.node=node;
 
     type->dispatch(ts_cast);
    }
   
   void cast_deref(StepId step_id,Ptr ptr,StructNode *struct_node,ExprNode *node);
   
   
   void error_ptr(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   StepId add_ptr_slen(StepId step_id,ExprNode *node) { return addStep<Step_add_ptr>(step_id,node); }
   
   StepId sub_ptr_slen(StepId step_id,ExprNode *node) { return addStep<Step_sub_ptr>(step_id,node); }
   
   StepId sub_ptr(StepId step_id,ExprNode *node) { return addStep<Step_sub_ptr2>(step_id,node); }
   
   StepId select(StepId step_id,NameLink &name,ExprNode *node) { return addStep<Step_select>(step_id,name,node); }
   
   void address_var(StepId step_id,ExprNode_var *node); 
   
   StepId cast_deref(StepId step_id,TypeNode *type,ExprNode *node) { return addStep<Step_deref>(step_id,type,node); }
   
   StepId cast_deref(StepId step_id,StructNode *struct_node,ExprNode *node) { return addStep<Step_deref_struct>(step_id,struct_node,node); }
   
   // ptr
   
   void copyIf(StepId step_id,const Value &val,TypeNode *type1,TypeNode *type2,ExprNode *node);
   
   void copyIf(StepId step_id,const Value &val,TypeNode_array_len *type1,TypeNode *type2,imp_ulen len,ExprNode *node);
   
   
   StepId ptr_type(StepId step_id,TypeNode_ptr *type,ExprNode *node) { return addStep<Step_ptr_type>(step_id,type->type_node,node); }
   
   void null_ptr(StepId step_id,TypeNode_ptr *type,ExprNode *node) { set_null_ptr(step_id,type->type_node,node); }
   
   // array
   
   void error_array(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   void null_array(StepId step_id,TypeNode_array *,ExprNode *node) { set_null<Block>(step_id,node); }
   
   StepId brace_array(StepId step_id,ulen count,TypeNode_array *,ExprNode *node)
    {
     if( count>imp_ulen(-1) )
       {
        error_void("len overflow",node);
        
        return blankStep(); 
       }
     else
       {
        PtrLen<Value> data=pool.createArray<Value>(count);
        
        return addStep<Step_block>(step_id,data,node); 
       }
    }
   
   // array_len
   
   void error_array_len(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   void null_array_len(StepId step_id,TypeNode_array_len *type,ExprNode *node)
    {
     len_list[type->len_node.index].add(this,addStep<Step_null_len>(step_id,type->type_node,node));
    }
   
   StepId brace_array_len(StepId step_id,ulen count,TypeNode_array_len *type,ExprNode *node)
    {
     StepId step1_id=addStep<Step_block_len>(step_id,type->type_node,node);
        
     len_list[type->len_node.index].add(this,step1_id);
        
     PtrLen<Value> data=pool.createArray<Value>(count);
        
     return addStep<Step_block>(step1_id.arg2(),data,node);
    }
   
   // struct
   
   void error_struct(StepId,StrLen msg,ExprNode *node) { error_void(msg,node); }
   
   void null_struct(StepId step_id,StructNode *struct_node,ExprNode *node);
   
   StepId brace_struct(StepId step_id,StructNode *struct_node,ExprNode *node)
    {
     ulen count=struct_node->field_list.count;
     
     PtrLen<Value> data=pool.createArray<Value>(count);
        
     return addStep<Step_block>(step_id,data,node); 
    }
   
   // null-def
   
   void len(StepId step_id,LenNode *node)
    {
     len_list[node->index].add(this,addStep<Step_copy>(step_id));
    }
   
   void null_val_len(StepId step_id,TypeNode *type,imp_ulen count,ExprNode *node);
   
   void block_len(StepId step_id,Block block,TypeNode *type,imp_ulen count,ExprNode *node);
   
   void null_val(StepId step_id,TypeNode *type,ExprNode *node)
    {
     ts_nullval.step_id=step_id;
     ts_nullval.node=node;
     
     type->dispatch(ts_nullval);
    }
   
   void def_val(StepId step_id,TypeNode *type,ExprNode *node)
    {
     ts_defval.step_id=step_id;
     ts_defval.node=node;
     
     type->dispatch(ts_defval);
    }
   
   void def_array_len(StepId step_id,TypeNode_array_len *type,ExprNode *node)
    {
     len_list[type->len_node.index].add(this,addStep<Step_def_len>(step_id,type->type_node,node));
    }
   
   void def_val_len(StepId step_id,TypeNode *type,imp_ulen count,ExprNode *node);
   
   void def_struct(StepId step_id,StructNode *struct_node,ExprNode *node);
 };

/* struct ConstResult */

struct ConstResult
 {
  TypeNode *type;
  ConstNode *node;
  Value value;
  
  explicit ConstResult(const ConstRec &rec)
   : type(rec.type),
     node(rec.node),
     value(rec.value)
   {
   }
  
  // print object
  
  struct PrintName;
  
  struct PrintValue;
  
  template <class P>
  void print(P &out) const;
 };

/* struct LenResult */

struct LenResult
 {
  LenNode *node;
  ulen value;
  
  explicit LenResult(const LenRec &rec)
   : node(rec.node),
     value((ulen)rec.value.get<imp_ulen>())
   {
   }
 };

/* struct ConstResult::PrintName */

struct ConstResult::PrintName
 {
  ConstNode *node;
  
  explicit PrintName(ConstNode *node_) : node(node_) {}
  
  template <class P>
  void print(P &out) const
   {
    DynArray<StrLen> list(node->depth+1);
    
    list[node->depth]=node->name.name.token.str;
    
    auto ptr=node->parent;
    
    for(ulen i=node->depth; i-- ;ptr=ptr->parent) list[i]=ptr->name.name.token.str;
    
    auto r=Range(list);
      
    Putobj(out,*r);
      
    for(++r; +r ;++r) Putobj(out,"#",*r); 
   }
 };

/* struct ConstResult::PrintValue */

struct ConstResult::PrintValue
 {
  TypeNode *type;
  Value value;
  ulen off;
  
  template <class P>
  struct PrintSwitch : TypeSwitch
   {
    P &out;
    Value value;
    ulen off;
    
    template <class Type>
    void complete(const char *name)
     {
      Printf(out,"#;(#;) #;",RepeatChar(off,' '),name,value.get<Type>());
     }
    
    PrintSwitch(P &out_,const Value &value_,ulen off_) : TypeSwitch(this),out(out_),value(value_),off(off_) {}
    
    void do_sint8(TypeNode_suint<imp_sint8> *) { complete<imp_sint8>("sint8"); }
    void do_uint8(TypeNode_suint<imp_uint8> *) { complete<imp_uint8>("uint8"); }
    
    void do_sint16(TypeNode_suint<imp_sint16> *) { complete<imp_sint16>("sint16"); }
    void do_uint16(TypeNode_suint<imp_uint16> *) { complete<imp_uint16>("uint16"); }
    
    void do_sint32(TypeNode_suint<imp_sint32> *) { complete<imp_sint32>("sint32"); }
    void do_uint32(TypeNode_suint<imp_uint32> *) { complete<imp_uint32>("uint32"); }
    
    void do_sint64(TypeNode_suint<imp_sint64> *) { complete<imp_sint64>("sint64"); }
    void do_uint64(TypeNode_suint<imp_uint64> *) { complete<imp_uint64>("uint64"); }
    
    void do_text(TypeNode_text *) { complete<Text>("text"); }
    void do_ip(TypeNode_ip *) { complete<IP>("ip"); }
    
    void do_ptr(TypeNode_ptr *) 
     {
      Printf(out,"#;(pointer)",RepeatChar(off,' '));
     }
    
    void do_array_type(TypeNode *type)
     {
      Block block=value.get<Block>();
      
      Printf(out,"#; {\n",RepeatChar(off,' '));
      
      for(ulen ind=0; ind<block.data.len ;ind++) Printf(out,"#;\n",PrintValue(type,block.data[ind],off+2));
      
      Printf(out,"#; }",RepeatChar(off,' '));
     }
    
    void do_array(TypeNode_array *node) 
     {
      do_array_type(node->type_node);
     }
    
    void do_array_len(TypeNode_array_len *node) 
     {
      do_array_type(node->type_node);
     }
    
    void do_struct(StructNode *struct_node)
     {
      Block block=value.get<Block>();
      
      Printf(out,"#; {\n",RepeatChar(off,' '));
      
      ulen ind=0;
      
      for(FieldNode &field : struct_node->field_list )
        {
         Printf(out,"#;\n",PrintValue(field.type_node,block.data[ind],off+2));
         
         ind++;
        }
      
      Printf(out,"#; }",RepeatChar(off,' '));
     }
    
    void do_struct(TypeNode_struct *node) { do_struct(node->base_struct); }
    
    void do_ref(TypeNode_ref *node)
     {
      if( AliasNode *alias=node->alias_node )
        {
         alias->result_type->dispatch(*this);
        }
      else
        {
         do_struct(node->struct_node);
        }
     }
   };
  
  PrintValue(TypeNode *type_,const Value &value_,ulen off_=0) : type(type_),value(value_),off(off_) {}
  
  template <class P>
  void print(P &out) const
   {
    PrintSwitch<P> ts(out,value,off);
    
    type->dispatch(ts);
   }
 };

/* struct ConstResult */

template <class P>
void ConstResult::print(P &out) const
 {
  Printf(out,"#; = #;",PrintName(node),PrintValue(type,value));
 }

/* class Eval */

inline ConstResult Eval::getConstResult(ulen ind) const { return ConstResult(const_list[ind]); }

inline LenResult Eval::getLenResult(ulen ind) const { return LenResult(len_list[ind]); }

template <class P>
void Eval::print(P &out) const
 {
  for(ulen i=0,n=getConstCount(); i<n ;i++) Printf(out,"#;\n\n",getConstResult(i));
 }

/* struct Step */

template <class T>
void Step::set_func() { step_func=static_cast<StepFunc>(&T::do_step); }

} // namespace DDL
} // namespace CCore

#endif

