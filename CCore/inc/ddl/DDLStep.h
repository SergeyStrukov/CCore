/* DDLStep.h */
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

#ifndef CCore_inc_ddl_DDLStep_h
#define CCore_inc_ddl_DDLStep_h

#include <CCore/inc/ddl/DDLValue.h>

namespace CCore {
namespace DDL {

/* CheckResult() */

template <class Type>
bool CheckResult(Type) { return true; }

inline bool CheckResult(SLen result) { return result.noError(); }

/* forward */

class Eval;

/* classes */

struct Step;

struct RecBase;

struct ConstRec;

struct FieldRec;

struct LenRec;

struct Step_const;

struct Step_field;

struct Step_len;

struct Step_ptr;

template <class Type> struct Step_plus;

template <class Type> struct Step_minus;

template <class Type> struct Step_add;

template <class Type> struct Step_sub;

template <class Type> struct Step_mul;

template <class Type> struct Step_div;

template <class Type> struct Step_rem;

template <class Type,class SrcType> struct Step_cast;

struct Step_add_text;

template <class SrcType> struct Step_cast_text;

struct Step_add_ptr;

struct Step_sub_ptr;

struct Step_sub_ptr2;

struct Step_select;

template <class Type> struct Step_cast_to_int;

struct Step_cast_to_text;

struct Step_cast_to_ip;

struct Step_cast_to_array;

struct Step_cast_to_array_len;

struct Step_cast_to_struct;

struct Step_copy_deref;

struct Step_copyif_deref;

struct Step_deref;

struct Step_deref_struct;

struct Step_ptr_type;

struct Step_set_ptr;

struct Step_bind_elem;

struct Step_bind_const;

struct Step_block;

struct Step_null_len;

struct Step_block_len;

struct Step_copy;

struct Step_block_init;

struct Step_def_len;

struct Step_null_struct;

struct Step_castval;

struct Step_copyif;

/* struct Step */

struct Step
 {
  ExprNode *node;
  Value *args;
  ulen count;
  
  typedef void (Step::* StepFunc)(Eval *eval);
  
  StepFunc step_func;
  
  SLink<Step> link;
  DLink<Step> link2;

  template <ulen Len>
  void set(Value (&argbuf)[Len])
   {
    args=argbuf;
    count=Len;
   }
  
  void set(Value &value)
   {
    args=&value;
    count=1;
   }
  
  enum argbuf_nobuf { argbuf };
  
  void set(argbuf_nobuf)
   {
    args=0;
    count=0;
   }
  
  template <class T>
  void set_func(); // { step_func=static_cast<StepFunc>(&T::do_step); }
  
  template <class T>
  Step(T *,Value &value)
   : node(0)
   {
    set(value);

    set_func<T>();
   }
  
  template <class T>
  Step(T *obj,ExprNode *node_)
   : node(node_)
   {
    set(obj->argbuf);
    
    set_func<T>();
   }
  
  template <class T>
  Step(T *,ExprNode *node_,PtrLen<Value> data)
   : node(node_)
   {
    args=data.ptr;
    count=data.len;
    
    set_func<T>();
   }
  
  void step(Eval *eval)
   {
    (this->*step_func)(eval);
   }
 };

typedef SLink<Step>::LinearAlgo<&Step::link>::Top StepTop;

typedef DLink<Step>::LinearAlgo<&Step::link2>::Top StepTop2;

/* struct RecBase */

struct RecBase : NoCopy
 {
  Value value;
  StepTop list;
  bool done;
  
  RecBase() : done(false) {}
  
  template <class Eval>
  void add(Eval *eval,StepId step_id)
   {
    if( Step *step=eval->getStep(step_id) )
      {
       if( done )
         {
          complete(eval,step);
         }
       else
         {
          list.ins(step);
         }
      }
   }
  
  template <class Eval>
  void complete(Eval *eval,Step *step)
   {
    eval->setArg(step,1)->copy(value);
   }
  
  template <class Eval>
  void loop(Eval *eval)
   {
    done=true;
    
    while( Step *step=list.del() ) complete(eval,step);
   }
 };

/* struct ConstRec */

struct ConstRec : RecBase
 {
  TypeNode *type;
  ConstNode *node;
  
  ConstRec() : type(0),node(0) {}
  
  ConstRec * set(TypeNode *type_,ConstNode *node_)
   {
    type=type_;
    node=node_;
    
    return this;
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* struct FieldRec */

struct FieldRec : RecBase
 {
  TypeNode *type;
  
  FieldRec() : type(0) {}
  
  FieldRec * set(TypeNode *type_)
   {
    type=type_;
    
    return this;
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* struct LenRec */

struct LenRec : RecBase
 {
  LenNode *node;
  
  LenRec() {}
  
  LenRec * set(LenNode *node_)
   {
    node=node_;
    
    return this;
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* struct Step_const */

struct Step_const : Step
 {
  ConstRec *rec;
  
  explicit Step_const(ConstRec *rec_) : Step(this,rec_->value),rec(rec_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    rec->loop(eval);
   }
 };

/* struct Step_field */

struct Step_field : Step
 {
  FieldRec *rec;
  
  explicit Step_field(FieldRec *rec_) : Step(this,rec_->value),rec(rec_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    rec->loop(eval);
   }
 };

/* struct Step_len */

struct Step_len : Step
 {
  LenRec *rec;
  
  explicit Step_len(LenRec *rec_) : Step(this,rec_->value),rec(rec_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    rec->loop(eval);
   }
 };

/* struct Step_ptr */

struct Step_ptr : Step
 {
  RecBase temp;
  
  Step_ptr() : Step(this,temp.value) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    temp.loop(eval);
   }
 };

/* struct Step_plus<Type> */

template <class Type> 
struct Step_plus : Step
 {
  Value argbuf[1];
  StepId step_id;
  
  Step_plus(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Type result=Type(   argbuf[0].get<Type>() );
      
    eval->setArg(step_id)->template set<Type>(result);
   }
 };

/* struct Step_minus<Type> */

template <class Type> 
struct Step_minus : Step
 {
  Value argbuf[1];
  StepId step_id;
  
  Step_minus(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Type result=Type( - argbuf[0].get<Type>() );
      
    eval->setArg(step_id)->template set<Type>(result);
   }
 };

/* struct Step_add<Type> */

template <class Type> 
struct Step_add : Step
 {
  Value argbuf[2];
  StepId step_id;
  
  Step_add(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Type result=Type( argbuf[0].get<Type>() + argbuf[1].get<Type>() );
      
    if( CheckResult(result) )
      {
       eval->setArg(step_id)->template set<Type>(result);
      }
    else
      {
       eval->error_void("slen overflow",node);
      }
   }
 };

/* struct Step_sub<Type> */

template <class Type> 
struct Step_sub : Step
 {
  Value argbuf[2];
  StepId step_id;
  
  Step_sub(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Type result=Type( argbuf[0].get<Type>() - argbuf[1].get<Type>() );
      
    if( CheckResult(result) )
      {
       eval->setArg(step_id)->template set<Type>(result);
      }
    else
      {
       eval->error_void("slen overflow",node);
      }
   }
 };

/* struct Step_mul<Type> */

template <class Type> 
struct Step_mul : Step
 {
  Value argbuf[2];
  StepId step_id;
  
  Step_mul(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Type result=Type( argbuf[0].get<Type>() * argbuf[1].get<Type>() );
      
    if( CheckResult(result) )
      {
       eval->setArg(step_id)->template set<Type>(result);
      }
    else
      {
       eval->error_void("slen overflow",node);
      }
   }
 };

/* struct Step_div<Type> */

template <class Type> 
struct Step_div : Step
 {
  Value argbuf[2];
  StepId step_id;
  
  Step_div(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Type a=argbuf[0].get<Type>();
    Type b=argbuf[1].get<Type>();
    
    if( !b )
      {
       eval->error_void("zero division",node);
      }
    else
      {
       Type result=Type( a / b );
      
       eval->setArg(step_id)->template set<Type>(result);
      }
   }
 };

/* struct Step_rem<Type> */

template <class Type> 
struct Step_rem : Step
 {
  Value argbuf[2];
  StepId step_id;
  
  Step_rem(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Type a=argbuf[0].get<Type>();
    Type b=argbuf[1].get<Type>();
    
    if( !b )
      {
       eval->error_void("zero division",node);
      }
    else
      {
       Type result=Type( a % b );
     
       eval->setArg(step_id)->template set<Type>(result);
      }
   }
 };

/* struct Step_cast<Type,SrcType> */

template <class Type,class SrcType> 
struct Step_cast : Step
 {
  Value argbuf[1];
  StepId step_id;
  
  Step_cast(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Type result( argbuf[0].get<SrcType>() );
    
    if( CheckResult(result) )
      {
       eval->setArg(step_id)->template set<Type>(result);
      }
    else
      {
       eval->error_void("slen overflow",node);
      }
   }
 };

/* struct Step_add_text */

struct Step_add_text : Step
 {
  Value argbuf[2];
  StepId step_id;
  
  Step_add_text(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Text result=eval->addText( argbuf[0].get<Text>() , argbuf[1].get<Text>() );
    
    eval->setArg(step_id)->template set<Text>(result);
   }
 };

/* struct Step_cast_text<SrcType> */

template <class SrcType> 
struct Step_cast_text : Step
 {
  Value argbuf[1];
  StepId step_id;
  
  Step_cast_text(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Text result=eval->makeText( argbuf[0].get<SrcType>() );
    
    eval->setArg(step_id)->template set<Text>(result);
   }
 };

/* struct Step_add_ptr */

struct Step_add_ptr : Step
 {
  Value argbuf[2];
  StepId step_id;
  
  Step_add_ptr(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr result=eval->addPtr( argbuf[0].get<Ptr>() , argbuf[1].get<SLen>() ,node);
    
    if( result.isError() )
      {
       eval->error_void("pointer is out of bound",node);
      }
    else
      {
       eval->setArg(step_id)->template set<Ptr>(result);
      }
   }
 };

/* struct Step_sub_ptr */

struct Step_sub_ptr : Step
 {
  Value argbuf[2];
  StepId step_id;
  
  Step_sub_ptr(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr result=eval->subPtr( argbuf[0].get<Ptr>() , argbuf[1].get<SLen>() ,node);
    
    if( result.isError() )
      {
       eval->error_void("pointer is out of bound",node);
      }
    else
      {
       eval->setArg(step_id)->template set<Ptr>(result);
      }
   }
 };

/* struct Step_sub_ptr2 */

struct Step_sub_ptr2 : Step
 {
  Value argbuf[2];
  StepId step_id;
  
  Step_sub_ptr2(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr a=argbuf[0].get<Ptr>();
    Ptr b=argbuf[1].get<Ptr>();
    
    if( !a )
      {
       if( !b )
         {
          SLen result;
          
          Value val;
          
          val.set<SLen>(result);
          
          eval->copyIf(step_id,val,a.type,b.type,node);
         }
       else
         {
          eval->error_void("different pointer domains",node);
         }
      }
    else
      {
       SLen result=eval->subPtr2(a,b,node);
       
       if( result.noError() )
         {
          eval->setArg(step_id)->template set<SLen>(result);
         }
       else
         {
          eval->error_void("different pointer domains",node);
         }
      }
   }
 };

/* struct Step_select */

struct Step_select : Step
 {
  Value argbuf[1];
  NameLink &name;
  StepId step_id;
  
  Step_select(StepId step_id_,NameLink &name_,ExprNode *node) : Step(this,node),name(name_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr a=argbuf[0].get<Ptr>();
    
    if( !a )
      {
       eval->error_void("null pointer",node);
      }
    else
      {
       Ptr result=eval->select(a,name,node);
       
       if( result.isError() )
         {
          eval->error_void("no field",node);
         }
       else
         {
          eval->setArg(step_id)->template set<Ptr>(result);
         }
      }
   }
 };

/* struct Step_cast_to_int<Type> */

template <class Type> 
struct Step_cast_to_int : Step
 {
  Value argbuf[1];
  StepId step_id;
  
  Step_cast_to_int(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr a=argbuf[0].get<Ptr>();
    
    eval->template cast_to_int<Type>(step_id,a.type,*a,node);
   }
 };

/* struct Step_cast_to_text */

struct Step_cast_to_text : Step
 {
  Value argbuf[1];
  StepId step_id;
  
  Step_cast_to_text(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr a=argbuf[0].get<Ptr>();
    
    eval->cast_to_text(step_id,a.type,*a,node);
   }
 };

/* struct Step_cast_to_ip */

struct Step_cast_to_ip : Step
 {
  Value argbuf[1];
  StepId step_id;
  
  Step_cast_to_ip(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr a=argbuf[0].get<Ptr>();
    
    eval->cast_to_ip(step_id,a.type,*a,node);
   }
 };

/* struct Step_cast_to_array */

struct Step_cast_to_array : Step
 {
  Value argbuf[1];
  TypeNode_array *type;
  StepId step_id;
  
  Step_cast_to_array(StepId step_id_,TypeNode_array *type_,ExprNode *node) : Step(this,node),type(type_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr a=argbuf[0].get<Ptr>();
    
    eval->cast_to_array(type,step_id,a.type,*a,node);
   }
 };

/* struct Step_cast_to_array_len */

struct Step_cast_to_array_len : Step
 {
  Value argbuf[1];
  TypeNode_array_len *type;
  StepId step_id;
  
  Step_cast_to_array_len(StepId step_id_,TypeNode_array_len *type_,ExprNode *node) : Step(this,node),type(type_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr a=argbuf[0].get<Ptr>();
    
    eval->cast_to_array_len(type,step_id,a.type,*a,node);
   }
 };

/* struct Step_cast_to_struct */

struct Step_cast_to_struct : Step
 {
  Value argbuf[1];
  StructNode *struct_node;
  StepId step_id;
  
  Step_cast_to_struct(StepId step_id_,StructNode *struct_node_,ExprNode *node) : Step(this,node),struct_node(struct_node_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr a=argbuf[0].get<Ptr>();
    
    eval->cast_to_struct(struct_node,step_id,a,node);
   }
 };

/* struct Step_copy_deref */

struct Step_copy_deref : Step
 {
  Value argbuf[1];
  StepId step_id;
  
  Step_copy_deref(StepId step_id_,ExprNode *node) : Step(this,node),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr a=argbuf[0].get<Ptr>();
    
    eval->setArg(step_id)->copy(*a);
   }
 };

/* struct Step_copyif_deref */

struct Step_copyif_deref : Step
 {
  Value argbuf[1];
  TypeNode *type1;
  TypeNode *type2;
  StepId step_id;
  
  Step_copyif_deref(StepId step_id_,TypeNode *type1_,TypeNode *type2_,ExprNode *node) : Step(this,node),type1(type1_),type2(type2_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr a=argbuf[0].get<Ptr>();
    
    eval->copyIf(step_id,*a,type1,type2,node);
   }
 };

/* struct Step_deref */

struct Step_deref : Step
 {
  Value argbuf[1];
  TypeNode *type;
  StepId step_id;
  
  Step_deref(StepId step_id_,TypeNode *type_,ExprNode *node) : Step(this,node),type(type_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr a=argbuf[0].get<Ptr>();
    
    eval->cast_deref(step_id,a,type,node);
   }
 };

/* struct Step_deref_struct */

struct Step_deref_struct : Step
 {
  Value argbuf[1];
  StructNode *struct_node;
  StepId step_id;
  
  Step_deref_struct(StepId step_id_,StructNode *struct_node_,ExprNode *node) : Step(this,node),struct_node(struct_node_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Ptr a=argbuf[0].get<Ptr>();
    
    eval->cast_deref(step_id,a,struct_node,node);
   }
 };

/* struct Step_ptr_type */

struct Step_ptr_type : Step
 {
  Value argbuf[1];
  TypeNode *type;
  StepId step_id;
  
  Step_ptr_type(StepId step_id_,TypeNode *type_,ExprNode *node) : Step(this,node),type(type_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    Value a=argbuf[0];
    
    Ptr ptr=a.get<Ptr>();
           
    eval->copyIf(step_id,a,ptr.type,type,node);
   }
 };

/* struct Step_set_ptr */

struct Step_set_ptr : Step
 {
  Value argbuf[1];
  Ptr ptr;
  StepId step_id;
  
  Step_set_ptr(StepId step_id_,Ptr ptr_,ExprNode *node) : Step(this,node),ptr(ptr_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    eval->setArg(step_id)->template set<Ptr>(ptr);
   }
 };

/* struct Step_bind_elem */

struct Step_bind_elem : Step
 {
  Value argbuf[1];
  PtrNode *ptr_node;
  StepId step_id;
  
  Step_bind_elem(StepId step_id_,PtrNode *ptr_node_) : Step(this,ptr_node_->node),ptr_node(ptr_node_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    if( eval->bindElem(ptr_node) ) eval->setArg(step_id);
   }
 };

/* struct Step_bind_const */

struct Step_bind_const : Step
 {
  Value argbuf[1];
  PtrNode *ptr_node;
  StepId step_id;
  
  Step_bind_const(StepId step_id_,PtrNode *ptr_node_) : Step(this,ptr_node_->node),ptr_node(ptr_node_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    eval->bindConst(ptr_node);
    
    eval->setArg(step_id);
   }
 };

/* struct Step_block */

struct Step_block : Step
 {
  Block block;
  StepId step_id;
  
  Step_block(StepId step_id_,PtrLen<Value> data,ExprNode *node) : Step(this,node,data),block(data),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    eval->setArg(step_id)->template set<Block>(block);
   }
 };

/* struct Step_null_len */

struct Step_null_len : Step
 {
  Value argbuf[1];
  TypeNode *type;
  StepId step_id;
  
  Step_null_len(StepId step_id_,TypeNode *type_,ExprNode *node) : Step(this,node),type(type_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    imp_ulen count=argbuf[0].get<imp_ulen>();
    
    eval->null_val_len(step_id,type,count,node);
   }
 };

/* struct Step_block_len */

struct Step_block_len : Step
 {
  Value argbuf[2];
  TypeNode *type;
  StepId step_id;
  
  Step_block_len(StepId step_id_,TypeNode *type_,ExprNode *node) : Step(this,node),type(type_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    imp_ulen count=argbuf[0].get<imp_ulen>();
    
    eval->block_len(step_id,argbuf[1].get<Block>(),type,count,node);
   }
 };

/* struct Step_copy */

struct Step_copy : Step
 {
  Value value;
  StepId step_id;
  
  explicit Step_copy(StepId step_id_) : Step(this,value),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    eval->setArg(step_id)->copy(value);
   }
 };

/* struct Step_block_init */

struct Step_block_init : Step
 {
  Value value;
  PtrLen<Value> prefix;
  Block block;
  StepId step_id;
  
  Step_block_init(StepId step_id_,PtrLen<Value> data) : Step(this,value),block(data),step_id(step_id_) {}
  
  Step_block_init(StepId step_id_,PtrLen<Value> data,PtrLen<Value> prefix_) : Step(this,value),prefix(prefix_),block(data),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    block.init(prefix,value);
    
    eval->setArg(step_id)->template set<Block>(block);
   }
 };

/* struct Step_def_len */

struct Step_def_len : Step
 {
  Value argbuf[1];
  TypeNode *type;
  StepId step_id;
  
  Step_def_len(StepId step_id_,TypeNode *type_,ExprNode *node) : Step(this,node),type(type_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    imp_ulen count=argbuf[0].get<imp_ulen>();
    
    eval->def_val_len(step_id,type,count,node);
   }
 };

/* struct Step_null_struct */

struct Step_null_struct : Step
 {
  StructNode *struct_node;
  StepId step_id;
  
  Step_null_struct(StepId step_id_,StructNode *struct_node_,ExprNode *node) : Step(this,node),struct_node(struct_node_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    eval->null_struct(step_id,struct_node,node);
   }
 };

/* struct Step_castval */

struct Step_castval : Step
 {
  Ptr ptr;
  TypeNode *type;
  StepId step_id;
  
  Step_castval(StepId step_id_,Ptr ptr_,TypeNode *type_,ExprNode *node) : Step(this,node),ptr(ptr_),type(type_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    eval->cast_deref(step_id,ptr,type,node);
   }
 };

/* struct Step_copyif */

struct Step_copyif : Step
 {
  Value argbuf[2];
  Value val;
  TypeNode *type1;
  TypeNode *type2;
  StepId step_id;
  
  Step_copyif(StepId step_id_,const Value &val_,TypeNode *type1_,TypeNode *type2_,ExprNode *node) : Step(this,node),val(val_),type1(type1_),type2(type2_),step_id(step_id_) {}
  
  template <class Eval>
  void do_step(Eval *eval)
   {
    imp_ulen len1=argbuf[0].get<imp_ulen>();
    imp_ulen len2=argbuf[1].get<imp_ulen>();
    
    if( len1!=len2 )
      {
       eval->error_void("type mismatch",node);
      }
    else
      {
       eval->copyIf(step_id,val,type1,type2,node);
      }
   }
 };

} // namespace DDL
} // namespace CCore

#endif

