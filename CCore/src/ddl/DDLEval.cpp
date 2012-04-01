/* DDLEval.cpp */
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

#include <CCore/inc/ddl/DDLEval.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace DDL {

/* functions */

void GuardCast()
 {
  Printf(Exception,"CCore::DDL internal : cannot cast");
 }

void GuardArg()
 {
  Printf(Exception,"CCore::DDL internal : no arg");
 }

/* class Eval */

bool Eval::loop()
 {
  while( Step *step=ready_list.del() ) step->step(this);
  
  return !pending_list;
 }

Eval::Eval(ElementPool &pool_,PrintBase &msg_)
 : pool(pool_),
   msg(msg_),
   error_flag(false),
   error_cap(ErrorMsgCap),
   add_cast_ms(this),
   ts_cast_text(this),
   to_int_cast_ms(this),
   ts_to_text(this),
   ts_to_ip(this),
   ts_to_array(this),
   ts_to_array_len(this),
   ts_to_anyptr(this),
   ts_to_ptr(this),
   ts_cast(this),
   ts_nullval(this),
   ts_defval(this)
 {
 }

Eval::~Eval()
 {
 }

void Eval::complete()
 {
  if( error_flag ) return;
  
  if( !loop() )
    {
     error_flag=true;
     
     Printf(msg,"Evaluation error : cannot evaluate because of errors or cyclic dependencies\n");
     
     ulen cap=ErrorMsgCap;
     
     while( Step *step=pending_list.del() )
       {
        if( ExprNode *node=step->node ) 
          {
           if( cap )
             {
              cap--;
              
              Printf(msg,"  at #;\n",node->ops);
             }
          }
       }
     
     Printf(msg,"\n");
    }
 };

StrLen Eval::makeDStr(StrLen str)
 {
  char *buf=pool.createArray_raw<char>(str.len).ptr;
  char *out=buf;
  
  while( +str )
    {
     char ch=*str;
     
     if( ch=='\\' )
       {
        ++str;
        
        ch=*str;
        
        ++str;
        
        *(out++)=MapDChar(ch);
       }
     else
       {
        ++str;
        
        *(out++)=ch;
       }
    }
  
  return Range_const(buf,out);
 }

StrLen Eval::makeStr(const Token &token)
 {
  switch( token.tc )
    {
     case Token_Dec :
     case Token_Bin :
     case Token_Hex : return token.str;
      
     case Token_SString : return token.str.inner(1,1);
     case Token_DString : return makeDStr(token.str.inner(1,1));
      
     default: return StrLen(); 
    }
 }

StrLen Eval::addText(StrLen a,StrLen b)
 {
  ulen len=LenAdd(a.len,b.len);
  
  PtrLen<char> ret=pool.createArray_raw<char>(len);
  
  a.copyTo(ret.ptr);
  
  ret.part(a.len).copy(b.ptr);
  
  return ret;
 }

Ptr Eval::addPtr(Ptr ptr,SLen delta,ExprNode *node)
 {
  if( !delta ) return ptr;
  
  if( !ptr || ptr.node->no_array ) return Ptr(0);
  
  ulen index=ptr.node->index;
  
  if( delta.flag==SLen::Pos )
    {
     if( delta.len>ulen(-1)-index ) return Ptr(0);
     
     index+=delta.len;
    }
  else
    {
     if( index<delta.len ) return Ptr(0);
      
     index-=delta.len;
    }

  PtrNode *ptr_node=pool.create<PtrNode>(ptr.node,index,node);
  
  return Ptr(ptr.type,ptr_node);
 }

Ptr Eval::subPtr(Ptr ptr,SLen delta,ExprNode *node)
 {
  return addPtr(ptr,-delta,node);
 }

SLen Eval::subPtr2(Ptr a,Ptr b,ExprNode *)
 {
  PtrNode *node_a=a.node;
  PtrNode *node_b=b.node;

  if( node_b )
    {
     SLen ret;
     
     if( node_a->no_array )
       {
        if( node_a->index!=node_b->index ) return SLen::Error;
       }
     else
       {
        ret=SLen(node_a->index,node_b->index);
       }
     
     node_a=node_a->base;
     node_b=node_b->base;
     
     while( node_a )
       {
        if( !node_b || node_a->index!=node_b->index ) return SLen::Error;
        
        node_a=node_a->base;
        node_b=node_b->base;
       }
     
     if( node_b ) return SLen::Error;
     
     return ret;
    }
  else
    {
     return SLen::Error;
    }
 }

Ptr Eval::select(Ptr ptr,FieldNode *field,ExprNode *node)
 {
  PtrNode *ptr_node=pool.create<PtrNode>(ptr.type,ptr.node,field->field_index,node);
  
  return Ptr(field->type_node,ptr_node);
 }

Ptr Eval::select(Ptr ptr,NameLink &name,ExprNode *node)
 {
  FieldNode *field=fft.field(ptr.type,name);
  
  if( !field ) return Ptr(0);
  
  return select(ptr,field,node);
 }

Ptr Eval::decay(Ptr ptr,TypeNode *array_type,TypeNode *elem_type,ExprNode *node)
 {
  PtrNode *base=ptr.node;
  
  if( !base )
    {
     return Ptr(elem_type);
    }
  else
    {
     PtrNode *ptr_node=pool.create<PtrNode>(array_type,base,node);
     
     return Ptr(elem_type,ptr_node);
    }
 }

void Eval::bindConst(PtrNode *ptr_node)
 {
  ptr_node->ptr=&const_list[ptr_node->index].value;
 }

bool Eval::bindElem(PtrNode *ptr_node)
 {
  PtrNode *base=ptr_node->base;
  
  Block block=base->ptr->get<Block>();
  ulen index=ptr_node->index;
  
  if( index>=block.data.len )
    {
     error_void("pointer is out of bound",ptr_node->node);
     
     return false;
    }
  
  ptr_node->ptr=&block.data[index];
  
  return true;
 }

void Eval::bindPtr(StepId step_id,Ptr ptr,ExprNode *node)
 {
  if( !ptr )
    {
     error_void("null pointer",node);
    }
  else
    {
     PtrNode *ptr_node=ptr.node;
     
     if( ptr_node->ptr )
       {
        setArg(step_id)->set<Ptr>(ptr);
       }
     else
       {
        step_id=addStep<Step_set_ptr>(step_id,ptr,node).arg1();
        
        while( PtrNode *base=ptr_node->base )
          {
           step_id=addStep<Step_bind_elem>(step_id,ptr_node).arg1();
            
           if( base->ptr )
             {
              setArg(step_id);
              
              return;
             }
           else
             {
              ptr_node=base;
             }
          }
        
        step_id=addStep<Step_bind_const>(step_id,ptr_node).arg1();
           
        const_list[ptr_node->index].add(this,step_id);
       }
    }
 }
  
void Eval::address_var(StepId step_id,ExprNode_var *node) 
 {
  PtrNode *ptr_node=pool.create<PtrNode>(node->node->index,node);
  
  Ptr ptr(node->node->type_node,ptr_node);
  
  setArg(step_id)->set<Ptr>(ptr);
 }

void Eval::cast_to_struct(StructNode *struct_node,StepId step_id,Ptr ptr,ExprNode *node)
 {
  StructNode *val_node=fft.structType(ptr.type);
  
  if( !val_node )
    {
     error_void("cannot cast non-struct to struct",node);
    }
  else if( val_node==struct_node )
    {
     setArg(step_id)->copy(*ptr); 
    }
  else
    {
     StepId step1_id=brace_struct(step_id,struct_node,node);

     for(FieldNode &field : struct_node->field_list )
       {
        if( FieldNode *val_field=val_node->find(field.name) )
          {
           addStep<Step_castval>(step1_id.argInd(field.field_index),select(ptr,val_field,node),field.type_node,node);
          }
        else
          {
           def_field(step1_id.argInd(field.field_index),field.index,node);
          }
       }
    }
 }

void Eval::cast_deref(StepId step_id,Ptr ptr,StructNode *struct_node,ExprNode *node)
 {
  StepId step1_id=addStep<Step_cast_to_struct>(step_id,struct_node,node);
  
  bindPtr(step1_id.arg1(),ptr,node);
 }

void Eval::copyIf(StepId step_id,const Value &val,TypeNode *type1,TypeNode *type2,ExprNode *node)
 {
  switch( type_compare(type1,type2) )
    {
     case TypeCompare::Same :
      {
       setArg(step_id)->copy(val);
      }
     break;
      
     case TypeCompare::NotSame :
      {
       error_void("type mismatch",node);
      }
     break;
     
     case TypeCompare::Continue :
      {
       StepId step1_id=addStep<Step_copyif>(step_id,val,type_compare.type1,type_compare.type2,node);
       
       len(step1_id.arg1(),type_compare.len1);
       len(step1_id.arg2(),type_compare.len2);
      }
    }
 }

void Eval::copyIf(StepId step_id,const Value &val,TypeNode_array_len *type1,TypeNode *type2,imp_ulen len2,ExprNode *node)
 {
  StepId step1_id=addStep<Step_copyif>(step_id,val,type1->type_node,type2,node);
  
  len(step1_id.arg1(),&type1->len_node);
  
  setArg(step1_id.arg2())->set<imp_ulen>(len2);
 }

void Eval::null_struct(StepId step_id,StructNode *struct_node,ExprNode *node)
 {
  ulen count=struct_node->field_list.count;
  
  if( count>imp_ulen(-1) )
    {
     error_void("len overflow",node);
    }
  else
    {
     PtrLen<Value> data=pool.createArray<Value>(count);
     
     StepId step1_id=addStep<Step_block>(step_id,data,node);
     
     ulen ind=0;
     
     for(FieldNode &field: struct_node->field_list )
       {
        null_val(step1_id.argInd(ind),field.type_node,node);
        
        ind++;
       }
    }
 }

void Eval::null_val_len(StepId step_id,TypeNode *type,imp_ulen count_,ExprNode *node)
 {
  if( count_>ulen(-1) )
    {
     error_void("len overflow",node);
    }
  else
    {
     ulen count=(ulen)count_;
     PtrLen<Value> data=pool.createArray<Value>(count);
     
     StepId step1_id=addStep<Step_block_init>(step_id,data);
     
     null_val(step1_id.arg1(),type,node);
    }
 }

void Eval::block_len(StepId step_id,Block block,TypeNode *type,imp_ulen count_,ExprNode *node)
 {
  if( count_<block.data.len ) 
    {
     error_void("to many array initializers",node);
    }
  else if( count_>block.data.len )
    {
     if( count_>ulen(-1) ) 
       {
        error_void("len overflow",node);
       }
     else
       {
        ulen count=(ulen)count_;
        PtrLen<Value> data=pool.createArray<Value>(count);
        
        StepId step1_id=addStep<Step_block_init>(step_id,data,block.data);
        
        def_val(step1_id.arg1(),type,node);
       }
    }
  else
    {
     setArg(step_id)->set<Block>(block);
    }
 }

void Eval::def_val_len(StepId step_id,TypeNode *type,imp_ulen count_,ExprNode *node)
 {
  if( count_>ulen(-1) )
    {
     error_void("len overflow",node);
    }
  else
    {
     ulen count=(ulen)count_;
     PtrLen<Value> data=pool.createArray<Value>(count);
     
     StepId step1_id=addStep<Step_block_init>(step_id,data);
     
     def_val(step1_id.arg1(),type,node);
    }
 }

void Eval::def_struct(StepId step_id,StructNode *struct_node,ExprNode *node)
 {
  ulen count=struct_node->field_list.count;
  
  if( count>imp_ulen(-1) )
    {
     error_void("len overflow",node);
    }
  else
    {
     PtrLen<Value> data=pool.createArray<Value>(count);
     
     StepId step1_id=addStep<Step_block>(step_id,data,node);
     
     ulen ind=0;
     
     for(FieldNode &field: struct_node->field_list )
       {
        def_field(step1_id.argInd(ind),field.index,node);
        
        ind++;
       }
    }
 }

} // namespace DDL
} // namespace CCore

