/* DDL2Eval.cpp */
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

#include <CCore/inc/ddl2/DDL2Eval.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace DDL2 {

/* class EvalContext */

using Gate = StepGate<EvalContext> ;

struct EvalContext::ConstRec : NoThrowFlagsBase , NoCopy
 {
  Value value;
  Gate *gate;
  ConstNode *node;
  
  ConstRec() : gate(0),node(0) {}
  
  void prepare(Eval &eval,ConstNode &node);
 };

struct EvalContext::LenRec : NoThrowFlagsBase , NoCopy
 {
  Value value;
  Gate *gate;
  LenNode *node;
  
  LenRec() : gate(0),node(0) {}
  
  void prepare(Eval &eval,TypeNode *type_ulen,LenNode &node);
  
  ulen_type getLen() { return value.get<imp_ulen>().value; }
 };

struct EvalContext::FieldRec : NoThrowFlagsBase , NoCopy
 {
  struct Rec : NoCopy 
   {
    RBTreeLink<Rec,From> link;
   
    Value value;
    Gate *gate;
    
    Rec() : gate(0) {}
    
    void prepare(Eval &eval,From from,FieldNode &field);
   };
  
  using Algo = RBTreeLink<Rec,From>::Algo<&Rec::link> ;
  
  Rec base;
  FieldNode *field;
  Algo::Root root;
 
  FieldRec() : field(0) {}
  
  void prepare(Eval &eval,From from,FieldNode &field);
  
  Rec & take(Eval &eval,From from);
 };

struct EvalContext::CmpLenStep
 {
  CmpResult &ret;
  ulen a;
  ulen b;
  
  CmpLenStep(CmpResult &ret_,ulen a_,ulen b_) : ret(ret_),a(a_),b(b_) {}
  
  void operator () (Eval &eval)
   {
    ret=Cmp(eval.len_list[a].getLen(),eval.len_list[b].getLen());
   }
 };

struct EvalContext::CmpArrayLenStep
 {
  CmpResult &ret;
  ulen a;
  ulen b;
  
  CmpArrayLenStep(CmpResult &ret_,LenNode &a_,LenNode &b_) : ret(ret_),a(a_.index),b(b_.index) {}
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !ret && a!=b )
      {
       auto step=eval.createStep(CmpLenStep(ret,a,b),dep);
      
       eval.len_list[a].gate->delay(step.id);
       eval.len_list[b].gate->delay(step.id);
      }
   }
 };

struct EvalContext::CmpListStep
 {
  CmpResult &ret;
  ulen count;
  
  CmpListStep(CmpResult &ret_,ulen count_) : ret(ret_),count(count_) {}
  
  struct Rec : NoThrowFlagsBase
   {
    TypeNode *type;
    unsigned flags;
    
    void init(TypeNode *type_,unsigned flags_) 
     {
      type=type_;
      flags=flags_;
     }
   };
  
  struct FunctorType : NoCopy
   {
    CmpResult &ret;
    ulen count;
    DynArray<Rec> buf;
    PtrLen<Rec> sorted;
   
    explicit FunctorType(CmpListStep init) 
     : ret(init.ret),count(init.count),buf(DoRaw(LenAdd(init.count,init.count))) {}
    
    ~FunctorType() {}
    
    Rec * fill(Rec *ptr,TypeList *list,unsigned flag)
     {
      for(auto &node : *list )
        {
         ptr->init(node.type_node,flag);
         
         ++ptr;
        }
      
      return ptr;
     }
    
    void init(TypeList *a,TypeList *b)
     {
      Rec *ptr=buf.getPtr();
      
      ptr=fill(ptr,a,1);
      ptr=fill(ptr,b,2);
     }
    
    Rec * getData() { return buf.getPtr(); }
    
    Rec * getSpare() { return buf.getPtr()+count; }
    
    void operator () ()
     {
      for(Rec &rec : sorted )
        {
         switch( rec.flags )
           {
            case 1 : ret=CmpGreater; return; 
            case 2 : ret=CmpLess; return; 
           }
        }
      
      ret=CmpEqual;
     }
   };
 };

struct EvalContext::JoinLoopStep
 {
  using Rec = CmpListStep::Rec ;
  
  PtrLen<Rec> &ret;
  PtrLen<Rec> a;
  PtrLen<Rec> b;
  CmpResult cmp;
  Rec *out;
  
  JoinLoopStep(PtrLen<Rec> &ret_,PtrLen<Rec> a_,PtrLen<Rec> b_,Rec *out_) : ret(ret_),a(a_),b(b_),out(out_) {}
  
  void operator () (Eval &eval,StepId dep);
 };

struct EvalContext::JoinStep
 {
  using Rec = CmpListStep::Rec ;
  
  PtrLen<Rec> &ret;
  PtrLen<Rec> a;
  PtrLen<Rec> b;
  Rec *data;
  Rec *spare;
  
  JoinStep(PtrLen<Rec> &ret_,Rec *data_,Rec *spare_) : ret(ret_),data(data_),spare(spare_) {}
  
  void operator () (Eval &eval,StepId dep);
 };

struct EvalContext::SortStep
 {
  using Rec = CmpListStep::Rec ; 
  
  PtrLen<Rec> &ret;
  Rec *data;
  Rec *spare;
  ulen count;
  
  SortStep(PtrLen<Rec> &ret_,Rec *data_,Rec *spare_,ulen count_) : ret(ret_),data(data_),spare(spare_),count(count_) {}
  
  void operator () (Eval &eval,StepId dep)
   {
    if( count>1 )
      {
       auto step=eval.createStep(JoinStep(ret,data,spare),dep);
      
       ulen count_a=count/2;
       ulen count_b=count-count_a;
      
       eval.createStep(SortStep(step.obj.a,data,spare,count_a),step.id);
       eval.createStep(SortStep(step.obj.b,data+count_a,spare+count_a,count_b),step.id);
      }
    else
      {
       ret=Range(data,count);
      }
   }
 };

struct EvalContext::CmpTypeStep
 {
  CmpResult &ret;
  TypeNode *a;
  TypeNode *b;
  
  CmpTypeStep(CmpResult &ret_,TypeNode *a_,TypeNode *b_) : ret(ret_),a(a_),b(b_) {}
  
  struct CmpRet
   {
    CmpResult result;
    bool done;
    
    CmpRet() : result(CmpEqual),done(true) {}
    
    CmpRet(unsigned a,unsigned b) : result(Cmp(a,b)),done(true) {}
    
    CmpRet(CmpResult result_) : result(result_),done(true) {}
    
    CmpRet(NothingType) : result(CmpEqual),done(false) {}
   };
  
  struct CmpFunc
   {
    Eval &eval;
    CmpResult &ret;
    StepId dep;
    
    CmpFunc(Eval &eval_,CmpResult &ret_,StepId dep_) : eval(eval_),ret(ret_),dep(dep_) {}

    CmpRet cmp(TypeNode *a,TypeNode *b)
     {
      eval.createStep(CmpTypeStep(ret,a,b),dep);
      
      return Nothing;
     }
    
    CmpRet operator () (TypeNode::Base *a,TypeNode::Base *b) 
     { 
      return Cmp(a->type,b->type); 
     } 
    
    CmpRet operator () (TypeNode::Ptr *a,TypeNode::Ptr *b) 
     { 
      return cmp(a->type_node,b->type_node); 
     }
    
    CmpRet operator () (TypeNode::PolyPtr *a,TypeNode::PolyPtr *b) 
     {
      ulen count=LenAdd(a->type_list->count,b->type_list->count);
      
      auto step=eval.createStep(CmpListStep(ret,count),dep);
      
      step.obj.init(a->type_list,b->type_list);
      
      eval.createStep(SortStep(step.obj.sorted,step.obj.getData(),step.obj.getSpare(),count),step.id);
      
      return Nothing;
     }
    
    CmpRet operator () (TypeNode::Array *a,TypeNode::Array *b) 
     { 
      return cmp(a->type_node,b->type_node); 
     } 
    
    CmpRet operator () (TypeNode::ArrayLen *a,TypeNode::ArrayLen *b) 
     { 
      auto step=eval.createStep(CmpArrayLenStep(ret,a->len_node,b->len_node),dep);
      
      eval.createStep(CmpTypeStep(ret,a->type_node,b->type_node),step.id);
      
      return Nothing;
     } 
    
    CmpRet operator () (StructNode *a,StructNode *b)
     {
      return Cmp(a->index,b->index);
     }
   };
  
  void operator () (Eval &eval,StepId dep)
   {
    CmpRet cmp=TypeAdapter::Binary<CmpRet>(a,b,CmpFunc(eval,ret,dep));
    
    if( cmp.done ) ret=cmp.result; 
   }
 };

void EvalContext::JoinStep::operator () (Eval &eval,StepId dep)
 {
  Rec *out = (a.ptr==data)?spare:data ;
  
  ret.ptr=out;
  
  auto step=eval.createStep(JoinLoopStep(ret,a,b,out),dep);
    
  eval.createStep(CmpTypeStep(step.obj.cmp,a->type,b->type),step.id);
 }

void EvalContext::JoinLoopStep::operator () (Eval &eval,StepId dep)
 {
  switch( cmp )
    {
     case CmpLess :
      {
       *out=*a;
       
       ++a;
       ++out;
      }
     break;
     
     case CmpGreater :
      {
       *out=*b;
       
       ++b;
       ++out;
      }
     break;
     
     default: // CmpEqual
      {
       *out=*a;
       
       out->flags|=b->flags;
       
       ++a;
       ++b;
       ++out;
      }
    }
  
  if( a.len )
    {
     if( b.len )
       {
        auto step=eval.createStep(JoinLoopStep(ret,a,b,out),dep);
         
        eval.createStep(CmpTypeStep(step.obj.cmp,a->type,b->type),step.id);
       
        return;
       }
     else
       {
        a.copyTo(out);
        
        out+=a.len;
       }
    }
  else
    {
     if( b.ptr!=out ) b.copyTo(out);
     
     out+=b.len;
    }
  
  ret.len=Dist(ret.ptr,out);
 }

struct EvalContext::CmpToOkStep
 {
  bool &ret;
  CmpResult cmp;
  
  explicit CmpToOkStep(bool &ret_) : ret(ret_) {}
  
  void operator () ()
   {
    ret=!cmp;
   }
 };

struct EvalContext::CheckTypeListStep
 {
  bool &ret;
  TypeListPtr ptr;
  TypeListPtr lim;
  TypeNode *type;
  CmpResult cmp;
  
  CheckTypeListStep(bool &ret_,TypeListPtr ptr_,TypeListPtr lim_,TypeNode *type_) : ret(ret_),ptr(ptr_),lim(lim_),type(type_) {}

  CheckTypeListStep(bool &ret_,TypeListPtr ptr_,TypeListPtr lim_,TypeNode *type_,CmpResult cmp_) : ret(ret_),ptr(ptr_),lim(lim_),type(type_),cmp(cmp_) {}
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !cmp )
      {
       ret=true;
       
       return;
      }
    
    TypeListPtr cur=ptr;
    
    if( cur!=lim )
      {
       TypeNode *next_type=(*cur).type_node;
      
       ++cur;
       
       auto step=eval.createStep(CheckTypeListStep(ret,cur,lim,type),dep);
         
       eval.createStep(CmpTypeStep(step.obj.cmp,type,next_type),step.id);
      }
   }
 };

struct EvalContext::CheckTypeStep
 {
  bool &ret;
  AnyPtr<TypeNode,TypeList> type_set;
  TypeNode *type;
  
  CheckTypeStep(bool &ret_,AnyPtr<TypeNode,TypeList> type_set_,TypeNode *type_) : ret(ret_),type_set(type_set_),type(type_) {}
  
  void operator () (Eval &eval,StepId dep,TypeNode *req_type)
   {
    auto step=eval.createStep(CmpToOkStep(ret),dep);
    
    eval.createStep(CmpTypeStep(step.obj.cmp,type,req_type),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,TypeList *type_list)
   {
    ret=false;
    
    TypeListPtr ptr=begin(*type_list);
    TypeListPtr lim=end(*type_list);
    
    eval.createStep(CheckTypeListStep(ret,ptr,lim,type,CmpLess),dep);
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,type_set);
   }
 };

struct EvalContext::MinusStep
 {
  Value *ret;
  TypeNode::Base::Type type;
  Value arg;
  
  MinusStep(Value *ret_,TypeNode::Base::Type type_) : ret(ret_),type(type_) {}
  
  Value * getArg() 
   { 
    if( ret ) return &arg; 
    
    return 0; 
   }
  
  template <class IntType>
  void op()
   {
    ret->set<IntType>( -arg.get<IntType>() );
   }
  
  void operator () ()
   {
    if( ret ) UseIntType(*this);
   }
 };

struct EvalContext::AddStep
 {
  Value *ret;
  TypeNode::Base::Type type;
  Value arg1;
  Value arg2;
  
  AddStep(Value *ret_,TypeNode::Base::Type type_) : ret(ret_),type(type_) {}
  
  Value * getArg1() 
   { 
    if( ret ) return &arg1; 
    
    return 0; 
   }
  
  Value * getArg2() 
   { 
    if( ret ) return &arg2; 
    
    return 0; 
   }
  
  template <class IntType>
  void op()
   {
    ret->set<IntType>( arg1.get<IntType>()+arg2.get<IntType>() );
   }
  
  void operator () ()
   {
    if( ret ) UseIntType(*this);
   }
 };

struct EvalContext::AddTextStep
 {
  Value *ret;
  Value arg1;
  Value arg2;
  
  explicit AddTextStep(Value *ret_) : ret(ret_) {}
  
  Value * getArg1() 
   { 
    if( ret ) return &arg1; 
    
    return 0; 
   }
  
  Value * getArg2() 
   { 
    if( ret ) return &arg2; 
    
    return 0; 
   }
  
  void operator () (Eval &eval)
   {
    if( ret ) ret->set<Text>( eval.add(arg1.get<Text>(),arg2.get<Text>()) ); 
   }
 };

struct EvalContext::MulStep
 {
  Value *ret;
  TypeNode::Base::Type type;
  Value arg1;
  Value arg2;
  
  MulStep(Value *ret_,TypeNode::Base::Type type_) : ret(ret_),type(type_) {}
  
  Value * getArg1() 
   { 
    if( ret ) return &arg1; 
    
    return 0; 
   }
  
  Value * getArg2() 
   { 
    if( ret ) return &arg2; 
    
    return 0; 
   }
  
  template <class IntType>
  void op()
   {
    ret->set<IntType>( arg1.get<IntType>()*arg2.get<IntType>() );
   }
  
  void operator () ()
   {
    if( ret ) UseIntType(*this);
   }
 };

struct EvalContext::DivStep
 {
  Value *ret;
  TypeNode::Base::Type type;
  Value arg1;
  Value arg2;
  const PosName &ops;
  
  DivStep(Value *ret_,TypeNode::Base::Type type_,const PosName &ops_) : ret(ret_),type(type_),ops(ops_) {}
  
  Value * getArg1()
   { 
    if( ret ) return &arg1; 
    
    return 0; 
   }
  
  Value * getArg2()
   { 
    return &arg2; 
   }
  
  void error(Eval &eval)
   {
    eval.error("Evaluation error #; : division by zero",ops);
   }
  
  template <class IntType>
  void op(Eval &eval)
   {
    if( ret )
      {
       auto result=arg1.get<IntType>()/arg2.get<IntType>();
      
       if( !result ) error(eval);
       
       ret->set<IntType>( result.value );
      }
    else
      {
       IntType mod=arg2.get<IntType>();
     
       if( !mod ) error(eval);
      }
   }
  
  void operator () (Eval &eval)
   {
    UseIntType(*this,eval);
   }
 };

struct EvalContext::RemStep
 {
  Value *ret;
  TypeNode::Base::Type type;
  Value arg1;
  Value arg2;
  const PosName &ops;
  
  RemStep(Value *ret_,TypeNode::Base::Type type_,const PosName &ops_) : ret(ret_),type(type_),ops(ops_) {}
  
  Value * getArg1()
   { 
    if( ret ) return &arg1; 
    
    return 0; 
   }
  
  Value * getArg2()
   { 
    return &arg2; 
   }
  
  void error(Eval &eval)
   {
    eval.error("Evaluation error #; : division by zero",ops);
   }
  
  template <class IntType>
  void op(Eval &eval)
   {
    if( ret )
      {
       auto result=arg1.get<IntType>()%arg2.get<IntType>();
     
       if( !result ) error(eval);
      
       ret->set<IntType>( result.value );
      }
    else
      {
       IntType mod=arg2.get<IntType>();
     
       if( !mod ) error(eval);
      }
   }
  
  void operator () (Eval &eval)
   {
    UseIntType(*this,eval);
   }
 };

struct EvalContext::ExpandArray
 {
  PtrLen<Value> data;
  
  explicit ExpandArray(PtrLen<Value> data_) : data(data_) {}
  
  void operator () ()
   {
    data.part(1).set(*data);
   }
 };

struct EvalContext::NullArrayStep
 {
  Value *ret;
  TypeNode *type;
  LenRec &rec;
  
  NullArrayStep(Value *ret_,TypeNode *type_,LenRec &rec_) : ret(ret_),type(type_),rec(rec_) {}

  void operator () (Eval &eval,StepId dep);
 };

struct EvalContext::NullStep
 {
  Value *ret;
  TypeNode *type;
  
  NullStep(Value *ret_,TypeNode *type_) : ret(ret_),type(type_) {}

  void operator () (Eval &,StepId,TypeNode::Base *type_ptr)
   {
    if( ret ) *ret=NullBaseType(type_ptr->type);
   }

  void operator () (Eval &eval,StepId,TypeNode::Ptr *type_ptr)
   {
    if( ret ) ret->set<Ptr>( eval.nullPtr(type_ptr->type_node) );
   }

  void operator () (Eval &,StepId,TypeNode::PolyPtr *)
   {
    if( ret ) ret->set<Ptr>( Ptr() );
   }

  void operator () (Eval &,StepId,TypeNode::Array *)
   {
    if( ret ) ret->set<Block>( Block() );
   }

  void operator () (Eval &eval,StepId dep,TypeNode::ArrayLen *type_ptr)
   {
    if( ret )
      {
       ulen index=type_ptr->len_node.index;
      
       LenRec &rec=eval.len_list[index];
      
       rec.gate->createStep(NullArrayStep(ret,type_ptr->type_node,rec),dep);
      }
   }

  void operator () (Eval &eval,StepId dep,StructNode *struct_node)
   {
    if( ret )
      {
       PtrLen<Value> result=eval.block(struct_node->field_list.count);
       
       ret->set<Block>( result );
       
       Value *ptr=result.ptr;
       
       for(FieldNode &field : struct_node->field_list )
         {
          eval.createStep(NullStep(ptr,field.type_node),dep);
          
          ++ptr;
         }
      }
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,TypeAdapter(type).ptr);
   }
 };

void EvalContext::NullArrayStep::operator () (Eval &eval,StepId dep)
 {
  if( ret )
    {
     PtrLen<Value> result=eval.block(rec);
     
     ret->set<Block>( result );
     
     if( +result )
       {
        auto step=eval.createStep(ExpandArray(result),dep);
        
        eval.createStep(NullStep(result.ptr,type),step.id);
       }
    }
 }

struct EvalContext::CopyStep
 {
  Value *ret;
  const Value &src;
  
  CopyStep(Value *ret_,const Value &src_) : ret(ret_),src(src_) {}
  
  void operator () ()
   {
    if( ret ) *ret=src;
   }
 };

struct EvalContext::DefArrayStep
 {
  Value *ret;
  TypeNode *type;
  From from;
  LenRec &rec;
  
  DefArrayStep(Value *ret_,TypeNode *type_,From from_,LenRec &rec_) 
   : ret(ret_),type(type_),from(from_),rec(rec_) {}
  
  void operator () (Eval &eval,StepId dep);
 };

struct EvalContext::DefStep
 {
  Value *ret;
  TypeNode *type;
  From from;
  
  DefStep(Value *ret_,TypeNode *type_,From from_) : ret(ret_),type(type_),from(from_) {}
  
  void operator () (Eval &,StepId,TypeNode::Base *type_ptr)
   {
    if( ret ) *ret=NullBaseType(type_ptr->type);
   }

  void operator () (Eval &eval,StepId,TypeNode::Ptr *type_ptr)
   {
    if( ret ) ret->set<Ptr>( eval.nullPtr(type_ptr->type_node) );
   }

  void operator () (Eval &,StepId,TypeNode::PolyPtr *)
   {
    if( ret ) ret->set<Ptr>( Ptr() );
   }

  void operator () (Eval &,StepId,TypeNode::Array *)
   {
    if( ret ) ret->set<Block>( Block() );
   }

  void operator () (Eval &eval,StepId dep,TypeNode::ArrayLen *type_ptr)
   {
    ulen index=type_ptr->len_node.index;
      
    LenRec &rec=eval.len_list[index];
      
    rec.gate->createStep(DefArrayStep(ret,type_ptr->type_node,from,rec),dep);
   }

  void operator () (Eval &eval,StepId dep,StructNode *struct_node)
   {
    if( ret )
      {
       PtrLen<Value> result=eval.block(struct_node->field_list.count);
       
       ret->set<Block>( result );
       
       Value *ptr=result.ptr;
       
       for(FieldNode &field : struct_node->field_list )
         {
          auto &rec=eval.field_list[field.index].take(eval,from);
          
          rec.gate->createStep(CopyStep(ptr,rec.value),dep);
          
          ++ptr;
         }
      }
    else
      {
       for(FieldNode &field : struct_node->field_list )
         {
          auto &rec=eval.field_list[field.index].take(eval,from);
          
          rec.gate->delay(dep);
         }
      }
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,TypeAdapter(type).ptr);
   }
 };

void EvalContext::DefArrayStep::operator () (Eval &eval,StepId dep)
 {
  if( ret )
    {
     PtrLen<Value> result=eval.block(rec);
     
     ret->set<Block>( result );
     
     if( +result )
       {
        auto step=eval.createStep(ExpandArray(result),dep);
        
        eval.createStep(DefStep(result.ptr,type,from),step.id);
       }
    }
  else
    {
     if( rec.getLen() )
       eval.createStep(DefStep(0,type,from),dep);
    }
 }

struct EvalContext::CastIntToIntStep
 {
  struct Cast
   {
    TypeNode::Base::Type type;
    
    explicit Cast(TypeNode::Base::Type type_) : type(type_) {}
    
    template <class RetType,class IntType>
    void op(Value *ret,IntType value)
     {
      ret->set<RetType>( value.template castTo<RetType>() );
     }
    
    template <class IntType>
    void operator () (Value *ret,IntType value)
     {
      UseIntType(*this,ret,value);
     }
   };
  
  Value *ret;
  TypeNode::Base::Type type;
  Cast cast;
  Value arg;
  
  CastIntToIntStep(Value *ret_,TypeNode::Base::Type type_,TypeNode::Base::Type ret_type) 
   : ret(ret_),type(type_),cast(ret_type) {}
  
  CastIntToIntStep(Value *ret_,TypeNode::Base::Type type_,TypeNode::Base::Type ret_type,const Value &arg_) 
   : ret(ret_),type(type_),cast(ret_type),arg(arg_) {}
  
  Value * getArg() 
   { 
    if( ret ) return &arg; 
    
    return 0; 
   }

  template <class IntType>
  void op()
   {
    cast(ret,arg.get<IntType>());
   }
  
  void operator () ()
   {
    if( ret ) UseIntType(*this);
   }
 };

struct EvalContext::CastIntToTextStep
 {
  Value *ret;
  TypeNode::Base::Type type;
  Value arg;
  
  CastIntToTextStep(Value *ret_,TypeNode::Base::Type type_) : ret(ret_),type(type_) {}
  
  Value * getArg() 
   { 
    if( ret ) return &arg; 
    
    return 0; 
   }
  
  template <class IntType>
  void op(Eval &eval)
   {
    ret->set<Text>( eval.castToText( arg.get<IntType>() ) );
   }
  
  void operator () (Eval &eval)
   {
    if( ret ) UseIntType(*this,eval);
   }
 };

struct EvalContext::ArrayLenStep
 {
  Value *ret;
  TypeNode *type;
  From from;
  LenRec &rec;
  ExprList &list;
  const PosName &ops;
  
  ArrayLenStep(Value *ret_,TypeNode *type_,From from_,LenRec &rec_,ExprList &list_,PosName ops_) 
   : ret(ret_),type(type_),from(from_),rec(rec_),list(list_),ops(ops_) {}
  
  void operator () (Eval &eval,StepId dep);
 };

struct EvalContext::PtrOrSLen // Ptr is not null, except error
 {
  Value value;
  bool slen_type;
  
  PtrOrSLen() : slen_type(false) {}
  
  void set(Ptr ptr)
   {
    value.set<Ptr>(ptr);
    slen_type=false;
   } 
  
  void set(SLen slen)
   {
    value.set<SLen>(slen);
    slen_type=true;
   }
  
  Ptr getPtr() const { return value.get<Ptr>(); }
  
  SLen getSLen() const { return value.get<SLen>(); }
 };

struct EvalContext::PtrOrInt // Ptr is not null, except error
 {
  Value value;
  TypeNode::Base::Type type;
  
  explicit PtrOrInt(TypeNode::Base::Type type_) : type(type_) {}
  
  void set(Ptr ptr)
   {
    value.set<Ptr>(ptr);
    
    type=TypeNode::Base::Type_none;
   }
  
  template <class IntType>
  void set(IntType val) 
   {
    value.set<IntType>(val);
   }
  
  template <class IntType>
  IntType get() const { return value.get<IntType>(); }
  
  Ptr getPtr() const { return value.get<Ptr>(); }
  
  template <class IntType>
  void op()
   {
    set( IntType(0) );
   }
  
  void set_null()
   {
    UseIntType(*this);
   }
  
  template <class IntType,class IntType_>
  void op(IntType_ val)
   {
    set( val.template castTo<IntType>() );
   }
  
  template <class IntType_>
  void cast(IntType_ val)
   {
    UseIntType(*this,val);
   }
 
  template <class IntType>
  void op(const Token &token)
   {
    set( StrToInt<IntType>(token) );
   }
  
  void set(const Token &token)
   {
    UseIntType(*this,token);
   }

  Value * getArg() { return &value; }
 };

struct EvalContext::Ops
 {
  const PosName *ops;
  
  Ops() : ops(0) {}
  
  Ops(bool ok,const PosName &ops_) 
   { 
    if( ok )
      ops=0;
    else
      ops=&ops_; 
   }
  
  void set(const PosName &ops_) { ops=&ops_; }
  
  bool set(Ops a,Ops b)
   {
    ops=a.ops?a.ops:b.ops;
    
    return !ops;
   }
  
  bool error(Eval &eval,const char *text) const
   {
    if( ops )
      {
       eval.error("Evaluation error #; : #;",*ops,text);
       
       return true;
      }
    
    return false;
   }
 };

struct EvalContext::OpsSLen
 {
  Ops ops;
  SLen slen;
  
  OpsSLen() {}
  
  explicit OpsSLen(SLen slen_) : slen(slen_) {}
  
  OpsSLen(SLen slen_,const PosName &ops_) : ops(slen_.noError(),ops_),slen(slen_) {}
  
  bool error(Eval &eval) const { return ops.error(eval,"slen overflow or division by zero"); }
  
  void set(SLen slen_,const PosName &ops_) { *this=OpsSLen(slen_,ops_); }
  
  void setMinus(const OpsSLen &a)
   {
    ops=a.ops;
    slen=-a.slen;
   }
  
  void setAdd(const OpsSLen &a,const OpsSLen &b,const PosName &ops_)
   {
    if( ops.set(a.ops,b.ops) ) set(a.slen+b.slen,ops_);
   }
 
  void setSub(const OpsSLen &a,const OpsSLen &b,const PosName &ops_)
   {
    if( ops.set(a.ops,b.ops) ) set(a.slen-b.slen,ops_);
   }
  
  void setMul(const OpsSLen &a,const OpsSLen &b,const PosName &ops_)
   {
    if( ops.set(a.ops,b.ops) ) set(a.slen*b.slen,ops_);
   }
  
  void setDiv(const OpsSLen &a,const OpsSLen &b,const PosName &ops_)
   {
    if( ops.set(a.ops,b.ops) ) set(a.slen/b.slen,ops_);
   }
  
  void setRem(const OpsSLen &a,const OpsSLen &b,const PosName &ops_)
   {
    if( ops.set(a.ops,b.ops) ) set(a.slen%b.slen,ops_);
   }
 };

struct EvalContext::Trio // Ptr is not null, except error
 {
  Value value;
  Ops ops;
  OpsSLen slen;
  TypeNode::Base::Type type;
  
  explicit Trio(TypeNode::Base::Type type_) : type(type_) {}
  
  bool error(Eval &eval) const { return ops.error(eval,"division by zero"); }
  
  void set(Ptr ptr)
   {
    value.set<Ptr>(ptr);
    
    type=TypeNode::Base::Type_none;
   }

  template <class IntType>
  void set(IntType val,OpsSLen slen_) 
   {
    value.set<IntType>(val);
    slen=slen_;
   }
  
  template <class IntType>
  void op(SLen val)
   {
    set( val.castTo<IntType>() , OpsSLen(val) );
   }
  
  void set(SLen val)
   {
    UseIntType(*this,val);
   }
  
  template <class IntType>
  IntType get() const { return value.get<IntType>(); }
  
  Ptr getPtr() const { return value.get<Ptr>(); }
  
  template <class IntType>
  void op()
   {
    set( IntType(0) , OpsSLen() );
   }
  
  void set_null()
   {
    UseIntType(*this);
   }

  template <class IntType,class IntType_>
  void op(IntType_ val,const PosName &ops)
   {
    set( val.template castTo<IntType>() , OpsSLen( val.template castTo<SLen>() ,ops) );
   }
  
  template <class IntType_>
  void cast(IntType_ val,const PosName &ops)
   {
    UseIntType(*this,val,ops);
   }
  
  template <class IntType>
  void op(const Token &token,const PosName &ops)
   {
    set( StrToInt<IntType>(token) , OpsSLen( StrToInt<SLen>(token) ,ops) );
   }
  
  void set(const Token &token,const PosName &ops)
   {
    UseIntType(*this,token,ops);
   }
 
  template <class IntType>
  void setInt(IntType val)
   {
    value.set<IntType>(val);
   }
  
  template <class IntType,class Result>
  void setInt(Result result,const PosName &ops_)
   {
    if( !result )
      {
       ops.set(ops_);
       
       setInt<IntType>( IntType(0) );
      }
    else
      {
       setInt<IntType>(result.value);
      }
   }
  
  template <class IntType>
  void setMinus(const Trio &a)
   {
    ops=a.ops;
    
    setInt<IntType>( -a.get<IntType>() );
    
    slen.setMinus(a.slen);
   }
  
  template <class IntType>
  void setAdd(const Trio &a,const Trio &b,const PosName &ops_)
   {
    if( ops.set(a.ops,b.ops) ) 
      setInt<IntType>( a.get<IntType>()+b.get<IntType>() ); 
    else 
      setInt<IntType>( IntType(0) ); 
    
    slen.setAdd(a.slen,b.slen,ops_);
   }
  
  template <class IntType>
  void setSub(const Trio &a,const Trio &b,const PosName &ops_)
   {
    if( ops.set(a.ops,b.ops) ) 
      setInt<IntType>( a.get<IntType>()-b.get<IntType>() ); 
    else 
      setInt<IntType>( IntType(0) ); 
    
    slen.setSub(a.slen,b.slen,ops_);
   }
  
  template <class IntType>
  void setMul(const Trio &a,const Trio &b,const PosName &ops_)
   {
    if( ops.set(a.ops,b.ops) ) 
      setInt<IntType>( a.get<IntType>()*b.get<IntType>() ); 
    else 
      setInt<IntType>( IntType(0) ); 
    
    slen.setMul(a.slen,b.slen,ops_);
   }
  
  template <class IntType>
  void setDiv(const Trio &a,const Trio &b,const PosName &ops_)
   {
    if( ops.set(a.ops,b.ops) ) 
      setInt<IntType>( a.get<IntType>()/b.get<IntType>() ,ops_); 
    else 
      setInt<IntType>( IntType(0) ); 
    
    slen.setDiv(a.slen,b.slen,ops_);
   }
  
  template <class IntType>
  void setRem(const Trio &a,const Trio &b,const PosName &ops_)
   {
    if( ops.set(a.ops,b.ops) ) 
      setInt<IntType>( a.get<IntType>()%b.get<IntType>() ,ops_); 
    else 
      setInt<IntType>( IntType(0) ); 
    
    slen.setRem(a.slen,b.slen,ops_);
   }
 };

struct EvalContext::CompleteAddPtrStep
 {
  Value *ret;
  Ptr ptr;
  SLen delta;
  bool ok;
  const PosName &ops;
  
  CompleteAddPtrStep(Value *ret_,Ptr ptr_,SLen delta_,const PosName &ops_) 
   : ret(ret_),ptr(ptr_),delta(delta_),ops(ops_) {}
  
  void operator () (Eval &eval)
   {
    if( ok )
      {
       if( ret ) ret->set<Ptr>( eval.add(ptr,delta,ops) );
      }
    else
      {
       eval.error("Evaluation error #; : pointer types mismatch",ops);
     
       if( ret ) ret->set<Ptr>( Ptr() );
      }
   }
 };

struct EvalContext::AddPtrStep
 {
  Value *ret;
  AnyPtr<TypeNode,TypeList> type_set;
  PtrOrSLen arg1;
  PtrOrSLen arg2;
  const PosName &ops;
  
  AddPtrStep(Value *ret_,TypeNode *type_node,const PosName &ops_) : ret(ret_),type_set(type_node),ops(ops_) {}
  
  AddPtrStep(Value *ret_,TypeList *type_list,const PosName &ops_) : ret(ret_),type_set(type_list),ops(ops_) {}
  
  void null()
   {
    if( ret ) ret->set<Ptr>( Ptr() );
   }
  
  void add(Eval &eval,StepId dep,Ptr ptr,SLen delta)
   {
    if( !ptr )
      {
       null();
      }
    else
      {
       auto step=eval.createStep(CompleteAddPtrStep(ret,ptr,delta,ops),dep);
       
       eval.createStep(CheckTypeStep(step.obj.ok,type_set,ptr.getType()),step.id);
      }
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( arg2.slen_type )
      {
       if( arg1.slen_type )
         {
          eval.error("Evaluation error #; : cannot evaluate slen+slen as pointer",ops);
          
          null();
         }
       else
         {
          add(eval,dep,arg1.getPtr(),arg2.getSLen());
         }
      }
    else
      {
       if( arg1.slen_type )
         {
          add(eval,dep,arg2.getPtr(),arg1.getSLen());
         }
       else
         {
          eval.error("Evaluation error #; : cannot evaluate pointer+pointer as pointer",ops);
          
          null();
         }
      }
   }
 };

struct EvalContext::AddAnyPtrStep
 {
  Ptr &ret;
  PtrOrSLen arg1;
  PtrOrSLen arg2;
  const PosName &ops;
  
  AddAnyPtrStep(Ptr &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret=Ptr();
   }
  
  void add(Eval &eval,Ptr ptr,SLen delta)
   {
    if( !ptr )
      {
       null();
      }
    else
      {
       ret=eval.add(ptr,delta,ops);
      }
   }
  
  void operator () (Eval &eval)
   {
    if( arg2.slen_type )
      {
       if( arg1.slen_type )
         {
          eval.error("Evaluation error #; : cannot evaluate slen+slen as pointer",ops);
          
          null();
         }
       else
         {
          add(eval,arg1.getPtr(),arg2.getSLen());
         }
      }
    else
      {
       if( arg1.slen_type )
         {
          add(eval,arg2.getPtr(),arg1.getSLen());
         }
       else
         {
          eval.error("Evaluation error #; : cannot evaluate pointer+pointer as pointer",ops);
          
          null();
         }
      }
   }
 };

struct EvalContext::CompleteSubStep
 {
  CmpResult cmp;
  const PosName &ops;
  
  explicit CompleteSubStep(const PosName &ops_) : ops(ops_) {}
  
  void operator () (Eval &eval)
   {
    if( cmp )
      {
       eval.error("Evaluation error #; : different pointer types",ops);
      }
   }
 };

struct EvalContext::SubStep
 {
  Value *ret;
  TypeNode::Base::Type type;
  PtrOrInt arg1;
  PtrOrInt arg2;
  const PosName &ops;
  
  SubStep(Value *ret_,TypeNode::Base::Type type_,const PosName &ops_)
   : ret(ret_),type(type_),arg1(type_),arg2(type_),ops(ops_) {}

  template <class IntType>
  void op(int)
   {
    if( ret ) ret->set<IntType>( IntType(0) ); 
   }
  
  void null()
   {
    UseIntType(*this,0);
   }
  
  template <class IntType>
  void op()
   {
    if( ret ) ret->set<IntType>( arg1.get<IntType>()-arg2.get<IntType>() ); 
   }
  
  template <class IntType>
  void op(SLen result)
   {
    if( ret ) ret->set<IntType>( result.castTo<IntType>() ); 
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( arg1.type==type )
      {
       if( arg2.type==type )
         {
          UseIntType(*this);
         }
       else
         {
          eval.error("Evaluation error #; : cannot evaluate integer-pointer as integer",ops);
         
          null();
         }
      }
    else
      {
       if( arg2.type==type )
         {
          eval.error("Evaluation error #; : cannot evaluate pointer-integer as integer",ops);
        
          null();
         }
       else
         {
          Ptr a=arg1.getPtr();
          Ptr b=arg2.getPtr();
          
          if( !a || !b )
            {
             null();
            }
          else
            {
             if( a.null && b.null )
               {
                null();
               
                auto step=eval.createStep(CompleteSubStep(ops),dep);
               
                eval.createStep(CmpTypeStep(step.obj.cmp,a.getType(),b.getType()),step.id);
               }
             else
               {
                UseIntType(*this,eval.sub(a,b,ops));
               }
            }
         }
      }
   }
 };

struct EvalContext::SubPtrStep
 {
  Value *ret;
  AnyPtr<TypeNode,TypeList> type_set;
  Ptr arg1;
  SLen arg2;
  const PosName &ops;
  
  SubPtrStep(Value *ret_,TypeNode *type_node,const PosName &ops_) : ret(ret_),type_set(type_node),ops(ops_) {}
  
  SubPtrStep(Value *ret_,TypeList *type_list,const PosName &ops_) : ret(ret_),type_set(type_list),ops(ops_) {}

  void null()
   {
    if( ret ) ret->set<Ptr>( Ptr() );
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !arg1 )
      {
       null();
      }
    else
      {
       auto step=eval.createStep(CompleteAddPtrStep(ret,arg1,-arg2,ops),dep);
       
       eval.createStep(CheckTypeStep(step.obj.ok,type_set,arg1.getType()),step.id);
      }
   }
 };

struct EvalContext::SubAnyPtrStep
 {
  Ptr &ret;
  Ptr arg1;
  SLen arg2;
  const PosName &ops;
  
  SubAnyPtrStep(Ptr &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret=Ptr();
   }
  
  void operator () (Eval &eval)
   {
    if( !arg1 )
      {
       null();
      }
    else
      {
       ret=eval.add(arg1,-arg2,ops);
      }
   }
 };

struct EvalContext::OpNumber
 {
  Value *ret;
  TypeNode::Base::Type type;
  
  OpNumber(Value *ret_,TypeNode::Base::Type type_) : ret(ret_),type(type_) {}
  
  template <class IntType>
  void op(const Token &token)
   {
    ret->set<IntType>( StrToInt<IntType>(token) );
   }
  
  void operator () (const Token &token)
   {
    if( ret ) UseIntType(*this,token);
   }
 };

struct EvalContext::LValue // type is null if error
 {
  TypeNode *type;
  Ptr ptr;
  Value value;
  
  explicit LValue(Ptr ptr_) : type(0),ptr(ptr_) {}
  
  LValue(Ptr ptr_,const Value &value_) : type(ptr_.getType()),ptr(ptr_),value(value_) {}
 };

struct EvalContext::CompleteReadStep
 {
  LValue &ret;
  const Value &src;
  const PosName &ops;
  
  CompleteReadStep(LValue &ret_,const Value &src_,const PosName &ops_) : ret(ret_),src(src_),ops(ops_) {}
  
  void operator () (Eval &eval)
   {
    auto result=eval.readPtr(src,ret.ptr);
    
    if( !result )
      {
       eval.error("Evaluation error #; : out-of-bound pointer",ops);
      
       ret.type=0;
      }
    else
      {
       ret.value=result.value;
       ret.type=ret.ptr.getType();
      }
   }
 };

struct EvalContext::ReadPtrStep
 {
  LValue &ret;
  const PosName &ops;
  
  ReadPtrStep(LValue &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void operator () (Eval &eval,StepId dep)
   {
    Ptr ptr=ret.ptr;
    
    if( ptr.null )
      {
       eval.error("Evaluation error #; : null pointer dereferencing",ops);
      
       ret.type=0;
      }
    else
      {
       ConstRec &rec=eval.getConst(ptr);
       
       rec.gate->createStep(CompleteReadStep(ret,rec.value,ops),dep);
      }
   }
 };

struct EvalContext::CastSameTypeStep
 {
  Value *ret;
  TypeNode *type;
  Value src;
  CmpResult cmp;
  const PosName &ops;
  
  CastSameTypeStep(Value *ret_,TypeNode *type_,const Value &src_,const PosName &ops_) : ret(ret_),type(type_),src(src_),ops(ops_) {}
  
  void null(Eval &eval,StepId dep)
   {
    NullStep(ret,type)(eval,dep);
   }
  
  void impossible(Eval &eval,StepId dep)
   {
    eval.error("Evaluation error #; : impossible cast",ops);
   
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( cmp )
      {
       impossible(eval,dep);
      }
    else
      {
       if( ret ) *ret=src;
      }
   }
 };

struct EvalContext::CastValueStep
 {
  Value *ret;
  TypeNode *type;
  From from;
  LValue src;
  const PosName &ops;
  
  CastValueStep(Value *ret_,TypeNode *type_,From from_,Ptr ptr,const PosName &ops_) 
   : ret(ret_),type(type_),from(from_),src(ptr),ops(ops_) {}
  
  CastValueStep(Value *ret_,TypeNode *type_,From from_,Ptr ptr,const Value &value,const PosName &ops_) 
   : ret(ret_),type(type_),from(from_),src(ptr,value),ops(ops_) {}
  
  void null(Eval &eval,StepId dep)
   {
    NullStep(ret,type)(eval,dep);
   }
  
  void impossible(Eval &eval,StepId dep)
   {
    eval.error("Evaluation error #; : impossible cast",ops);
   
    null(eval,dep);
   }

  // same types
  
  template <class T,class S>
  void operator () (Eval &eval,StepId dep,T *,S *)
   {
    auto step=eval.createStep(CastSameTypeStep(ret,type,src.value,ops),dep);
    
    eval.createStep(CmpTypeStep(step.obj.cmp,type,src.type),step.id);
   }

  // base to base
  
  template <class T>
  void op(Eval &eval)
   {
    ret->set<Text>( eval.castToText( src.value.get<T>() ) );
   }
  
  void operator () (Eval &eval,StepId dep,TypeNode::Base *type_ptr,TypeNode::Base *src_type_ptr)
   {
    if( type_ptr->isIntegral() )
      {
       if( src_type_ptr->isIntegral() )
         {
          CastIntToIntStep(ret,src_type_ptr->type,type_ptr->type,src.value)();
         }
       else
         {
          impossible(eval,dep);
         }
      }
    else if( type_ptr->isText() )
      {
       if( ret )
         {
          ExtBaseType(*this,src_type_ptr->type,eval);
         }
      }
    else // IP
      {
       if( src_type_ptr->isIP() )
         {
          if( ret ) *ret=src.value;
         }
       else
         {
          impossible(eval,dep);
         }
      }
   }
  
  // struct to struct
  
  void operator () (Eval &eval,StepId dep,StructNode *struct_node,StructNode *src_struct_node)
   {
    if( struct_node==src_struct_node )
      {
       if( ret ) *ret=src.value;
      }
    else
      {
       if( ret )
         {
          ulen count=struct_node->field_list.count;
         
          PtrLen<Value> result=eval.block(count);
          
          ret->set<Block>( result );
          
          TempArray<bool,100> flags(count);
          
          Range(flags).set(false);
          
          Value *ptr=result.ptr;
          
          Value *data=src.value.get<Block>().data.ptr;
         
          for(FieldNode &src_field : src_struct_node->field_list )
            {
             if( FieldNode *field=struct_node->find(src_field.name) )
               {
                ulen index=field->field_index;
                
                CastField(eval,ptr+index,field->type_node,eval.ptrToField(src.ptr,&src_field),data[src_field.field_index],from,ops,dep);
                
                flags[index]=true;
               }
            }
          
          DefStruct(eval,ptr,flags.getPtr(),struct_node,from,dep);
         }
       else
         {
          ulen count=struct_node->field_list.count;
        
          TempArray<bool,100> flags(count);
         
          Range(flags).set(false);
         
          Value *data=src.value.get<Block>().data.ptr;
        
          for(FieldNode &src_field : src_struct_node->field_list )
            {
             if( FieldNode *field=struct_node->find(src_field.name) )
               {
                ulen index=field->field_index;
               
                CastField(eval,0,field->type_node,eval.ptrToField(src.ptr,&src_field),data[src_field.field_index],from,ops,dep);
               
                flags[index]=true;
               }
            }
         
          DefStruct(eval,0,flags.getPtr(),struct_node,from,dep);
         }
      }
   }
  
  // general
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !src.type )
      {
       null(eval,dep);
      }
    else
      {
       ElaborateAnyPtr(*this,eval,dep,TypeAdapter(type).ptr,TypeAdapter(src.type).ptr);
      }
   }
 };

struct EvalContext::DecayStep
 {
  Value *ret;
  Ptr ptr;
  TypeNode *type;
  bool ok;
  const PosName &ops;
  
  DecayStep(Value *ret_,Ptr ptr_,TypeNode *type_,const PosName &ops_) : ret(ret_),ptr(ptr_),type(type_),ops(ops_) {}
  
  void operator () (Eval &eval)
   {
    if( ok )
      {
       if( ret ) ret->set<Ptr>( eval.decay(ptr,type) );
      }
    else
      {
       eval.error("Evaluation error #; : incompatible decay types",ops);
     
       if( ret ) ret->set<Ptr>( Ptr() );
      }
   }
 };

struct EvalContext::CastStep
 {
  Value *ret;
  TypeNode *type;
  From from;
  Ptr ptr;
  const PosName &ops;
  
  CastStep(Value *ret_,TypeNode *type_,From from_,const PosName &ops_) : ret(ret_),type(type_),from(from_),ops(ops_) {}
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !ptr )
      {
       NullStep(ret,type)(eval,dep);
      }
    else
      {
       DecayCase decay(type,ptr.getType());
       
       if( decay.type )
         {
          auto step=eval.createStep(DecayStep(ret,ptr,decay.type,ops),dep);
          
          eval.createStep(CheckTypeStep(step.obj.ok,decay.type_set,decay.type),step.id);
         }
       else
         {
          auto step=eval.createStep(CastValueStep(ret,type,from,ptr,ops),dep);
          
          eval.createStep(ReadPtrStep(step.obj.src,ops),step.id);
         }
      }
   }
 };

struct EvalContext::CompleteCheckPtrStep
 {
  Value *ret;
  Ptr ptr;
  bool ok;
  const PosName &ops;
  
  CompleteCheckPtrStep(Value *ret_,Ptr ptr_,const PosName &ops_) : ret(ret_),ptr(ptr_),ops(ops_) {}
  
  void operator () (Eval &eval)
   {
    if( ok )
      {
       if( ret ) ret->set<Ptr>( ptr );
      }
    else
      {
       eval.error("Evaluation error #; : pointer types mismatch",ops);
     
       if( ret ) ret->set<Ptr>( Ptr() );
      }
   }
 };

struct EvalContext::CheckPtrStep
 {
  Value *ret;
  AnyPtr<TypeNode,TypeList> type_set;
  Ptr ptr;
  const PosName &ops;
  
  CheckPtrStep(Value *ret_,TypeNode *type_node,const PosName &ops_) : ret(ret_),type_set(type_node),ops(ops_) {}
  
  CheckPtrStep(Value *ret_,TypeList *type_list,const PosName &ops_) : ret(ret_),type_set(type_list),ops(ops_) {}
  
  void null()
   {
    if( ret ) ret->set<Ptr>( Ptr() );
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !ptr )
      {
       null();
      }
    else
      {
       auto step=eval.createStep(CompleteCheckPtrStep(ret,ptr,ops),dep);
       
       eval.createStep(CheckTypeStep(step.obj.ok,type_set,ptr.getType()),step.id);
      }
   }
 };

struct EvalContext::SelectFieldStep
 {
  Ptr &ret;
  Ptr ptr;
  const NameIdNode &name;
  const PosName &ops;
  
  SelectFieldStep(Ptr &ret_,const NameIdNode &name_,const PosName &ops_) : ret(ret_),name(name_),ops(ops_) {}
  
  void null()
   {
    ret=Ptr();
   }
  
  void operator () (Eval &eval)
   {
    if( !ptr )
      {
       null();
      }
    else
      {
       ret=eval.ptrToField(ptr,name,ops);
      }
   }
 };

struct EvalContext::CastValueToPtrStep
 {
  Ptr &ret;
  LValue src;
  const PosName &ops;
  
  CastValueToPtrStep(Ptr &ret_,Ptr ptr,const PosName &ops_) : ret(ret_),src(ptr),ops(ops_) {}

  void null()
   {
    ret=Ptr();
   }
  
  void operator () (Eval &eval)
   {
    if( !src.type )
      {
       null();
      }
    else
      {
       if( NotPtr(src.type) )
         {
          eval.error("Evaluation error #; : impossible cast",ops);
          
          null();
         }
       else
         {
          ret=src.value.get<Ptr>();
          
          if( !ret )
            {
             eval.error("Evaluation error #; : typeless null pointer",ops);
            }
         }
      }
   }
 };

struct EvalContext::CastToPtrStep
 {
  Ptr &ret;
  Ptr ptr;
  const PosName &ops;
  
  CastToPtrStep(Ptr &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}

  void null()
   {
    ret=Ptr();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !ptr )
      {
       null();
      }
    else
      {
       DecayAnyCase decay(ptr.getType());
       
       if( decay.type )
         {
          ret=eval.decay(ptr,decay.type);
         }
       else
         {
          auto step=eval.createStep(CastValueToPtrStep(ret,ptr,ops),dep);
          
          eval.createStep(ReadPtrStep(step.obj.src,ops),step.id);
         }
      }
   }
 };

struct EvalContext::CastToSLenOp
 {
  TypeNode::Base::Type type;
  SLen result;
  
  template <class IntType>
  void op(const Value &value)
   {
    result=value.get<IntType>().template castTo<SLen>();
   }
  
  CastToSLenOp(TypeNode::Base::Type type_,const Value &value) 
   : type(type_) 
   {
    UseIntType(*this,value);
   }
 };

struct EvalContext::CastValueToSLenStep
 {
  SLen &ret;
  LValue src;
  const PosName &ops;
  
  CastValueToSLenStep(SLen &ret_,Ptr ptr,const PosName &ops_) : ret(ret_),src(ptr),ops(ops_) {}

  void null()
   {
    ret=SLen();
   }
  
  void impossible(Eval &eval)
   {
    eval.error("Evaluation error #; : impossible cast",ops);
   
    null();
   }
  
  template <class T>
  void operator () (Eval &eval,T *)
   {
    impossible(eval); 
   }
  
  void operator () (Eval &eval,TypeNode::Base *src_type_ptr)
   {
    if( src_type_ptr->isIntegral() )
      {
       CastToSLenOp op(src_type_ptr->type,src.value);
       
       if( op.result.noError() )
         {
          ret=op.result;
         }
       else
         {
          eval.error("Evaluation error #; : slen overflow",ops);
          
          null();
         }
      }
    else
      {
       impossible(eval);
      }
   }
  
  void operator () (Eval &eval)
   {
    if( !src.type )
      {
       null();
      }
    else
      {
       ElaborateAnyPtr(*this,eval,TypeAdapter(src.type).ptr);
      }
   }
 };

struct EvalContext::CastToSLenStep
 {
  SLen &ret;
  Ptr ptr;
  const PosName &ops;
  
  CastToSLenStep(SLen &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}

  void null()
   {
    ret=SLen();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !ptr )
      {
       null();
      }
    else
      {
       auto step=eval.createStep(CastValueToSLenStep(ret,ptr,ops),dep);
     
       eval.createStep(ReadPtrStep(step.obj.src,ops),step.id);
      }
   }
 };

struct EvalContext::CastValueToPtrOrSLenStep
 {
  PtrOrSLen &ret;
  LValue src;
  const PosName &ops;
  
  CastValueToPtrOrSLenStep(PtrOrSLen &ret_,Ptr ptr,const PosName &ops_) : ret(ret_),src(ptr),ops(ops_) {}
  
  void null()
   {
    ret.set( SLen() );
   }
  
  void impossible(Eval &eval)
   {
    eval.error("Evaluation error #; : impossible cast",ops);
   
    null();
   }
  
  template <class T>
  void operator () (Eval &eval,T *)
   {
    impossible(eval); 
   }

  void castPtr(Eval &eval)
   {
    Ptr result=src.value.get<Ptr>();
    
    if( !result )
      {
       eval.error("Evaluation error #; : typeless null pointer",ops);
       
       null();
      }
    else
      {
       ret.set(result);
      }
   }
  
  void operator () (Eval &eval,TypeNode::Ptr *)
   {
    castPtr(eval);
   }
  
  void operator () (Eval &eval,TypeNode::PolyPtr *)
   {
    castPtr(eval);
   }
  
  void operator () (Eval &eval,TypeNode::Base *src_type_ptr)
   {
    if( src_type_ptr->isIntegral() )
      {
       CastToSLenOp op(src_type_ptr->type,src.value);
      
       if( op.result.noError() )
         {
          ret.set( op.result );
         }
       else
         {
          eval.error("Evaluation error #; : slen overflow",ops);
          
          null();
         }
      }
    else
      {
       impossible(eval);
      }
   }
  
  void operator () (Eval &eval)
   {
    if( !src.type )
      {
       null();
      }
    else
      {
       ElaborateAnyPtr(*this,eval,TypeAdapter(src.type).ptr);
      }
   }
 };

struct EvalContext::CastToPtrOrSLenStep
 {
  PtrOrSLen &ret;
  Ptr ptr;
  const PosName &ops;
  
  CastToPtrOrSLenStep(PtrOrSLen &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret.set( SLen() );
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !ptr )
      {
       null();
      }
    else
      {
       DecayAnyCase decay(ptr.getType());
       
       if( decay.type )
         {
          ret.set( eval.decay(ptr,decay.type) );
         }
       else
         {
          auto step=eval.createStep(CastValueToPtrOrSLenStep(ret,ptr,ops),dep);
          
          eval.createStep(ReadPtrStep(step.obj.src,ops),step.id);
         }
      }
   };
 };

struct EvalContext::SLenMinusStep
 {
  SLen &ret;
  SLen arg;
  
  explicit SLenMinusStep(SLen &ret_) : ret(ret_) {}
  
  void operator () ()
   {
    ret=-arg;
   }
 };

struct EvalContext::SLenAddStep
 {
  SLen &ret;
  SLen arg1;
  SLen arg2;
  const PosName &ops;
  
  SLenAddStep(SLen &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret=SLen();
   }
  
  void operator () (Eval &eval)
   {
    SLen result=arg1+arg2;
    
    if( result.noError() )
      {
       ret=result;
      }
    else
      {
       eval.error("Evaluation error #; : slen overflow",ops);
      
       null();
      }
   }
 };

struct EvalContext::SLenMulStep
 {
  SLen &ret;
  SLen arg1;
  SLen arg2;
  const PosName &ops;
  
  SLenMulStep(SLen &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret=SLen();
   }
  
  void operator () (Eval &eval)
   {
    SLen result=arg1*arg2;
    
    if( result.noError() )
      {
       ret=result;
      }
    else
      {
       eval.error("Evaluation error #; : slen overflow",ops);
      
       null();
      }
   }
 };

struct EvalContext::SLenDivStep
 {
  SLen &ret;
  SLen arg1;
  SLen arg2;
  const PosName &ops;
  
  SLenDivStep(SLen &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret=SLen();
   }
  
  void operator () (Eval &eval)
   {
    SLen result=arg1/arg2;
   
    if( result.noError() )
      {
       ret=result;
      }
    else
      {
       eval.error("Evaluation error #; : division by zero",ops);
     
       null();
      }
   }
 };

struct EvalContext::SLenRemStep
 {
  SLen &ret;
  SLen arg1;
  SLen arg2;
  const PosName &ops;
  
  SLenRemStep(SLen &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret=SLen();
   }
  
  void operator () (Eval &eval)
   {
    SLen result=arg1%arg2;
   
    if( result.noError() )
      {
       ret=result;
      }
    else
      {
       eval.error("Evaluation error #; : division by zero",ops);
     
       null();
      }
   }
 };

struct EvalContext::SLenSubStep
 {
  SLen &ret;
  PtrOrSLen arg1;
  PtrOrSLen arg2;
  const PosName &ops;
  
  SLenSubStep(SLen &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret=SLen();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( arg1.slen_type )
      {
       if( arg2.slen_type )
         {
          SLen a=arg1.getSLen();
          SLen b=arg2.getSLen();
          
          SLen result=a-b;
          
          if( result.noError() )
            {
             ret=result;
            }
          else
            {
             eval.error("Evaluation error #; : slen overflow",ops);
           
             null();
            }
         }
       else
         {
          eval.error("Evaluation error #; : cannot evaluate integer-pointer as integer",ops);
         
          null();
         }
      }
    else
      {
       if( arg2.slen_type )
         {
          eval.error("Evaluation error #; : cannot evaluate pointer-integer as integer",ops);
        
          null();
         }
       else
         {
          Ptr a=arg1.getPtr();
          Ptr b=arg2.getPtr();
          
          if( !a || !b )
            {
             null();
            }
          else
            {
             if( a.null && b.null )
               {
                null();
              
                auto step=eval.createStep(CompleteSubStep(ops),dep);
              
                eval.createStep(CmpTypeStep(step.obj.cmp,a.getType(),b.getType()),step.id);
               }
             else
               {
                ret=eval.sub(a,b,ops);
               }
            }
         }
      }
   }
 };

struct EvalContext::CastIntToSLenStep
 {
  SLen &ret;
  TypeNode::Base::Type type;
  Value arg;
  const PosName &ops;
  
  CastIntToSLenStep(SLen &ret_,TypeNode::Base::Type type_,const PosName &ops_) : ret(ret_),type(type_),ops(ops_) {}
  
  Value * getArg()
   {
    return &arg; 
   }
  
  void null()
   {
    ret=SLen();
   }
  
  template <class IntType>
  void op(Eval &eval)
   {
    SLen result=arg.get<IntType>().template castTo<SLen>();
    
    if( result.noError() )
      {
       ret=result;
      }
    else
      {
       eval.error("Evaluation error #; : slen overflow",ops);
     
       null();
      }
   }
  
  void operator () (Eval &eval)
   {
    UseIntType(*this,eval);
   }
 };

template <class T>
struct EvalContext::SetPtrStep
 {
  T &ret;
  Ptr ptr;
  
  explicit SetPtrStep(T &ret_) : ret(ret_) {}
  
  void operator () ()
   {
    ret.set( ptr );
   }
 };

struct EvalContext::SetSLenStep
 {
  PtrOrSLen &ret;
  SLen slen;
  
  explicit SetSLenStep(PtrOrSLen &ret_) : ret(ret_) {}
  
  void operator () ()
   {
    ret.set( slen );
   }
 };

struct EvalContext::PtrOrSLenAddStep
 {
  PtrOrSLen &ret;
  PtrOrSLen arg1;
  PtrOrSLen arg2;
  const PosName &ops;
  
  PtrOrSLenAddStep(PtrOrSLen &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret.set( SLen() );
   }
  
  void add(Eval &eval,Ptr ptr,SLen delta)
   {
    if( !ptr )
      {
       null();
      }
    else
      {
       ret.set( eval.add(ptr,delta,ops) );
      }
   }
  
  void operator () (Eval &eval)
   {
    if( arg2.slen_type )
      {
       if( arg1.slen_type )
         {
          SLen result=arg1.getSLen()+arg2.getSLen();
         
          if( result.noError() )
            {
             ret.set( result );
            }
          else
            {
             eval.error("Evaluation error #; : slen overflow",ops);
           
             null();
            }
         }
       else
         {
          add(eval,arg1.getPtr(),arg2.getSLen());
         }
      }
    else
      {
       if( arg1.slen_type )
         {
          add(eval,arg2.getPtr(),arg1.getSLen());
         }
       else
         {
          eval.error("Evaluation error #; : cannot evaluate pointer+pointer as pointer or slen",ops);
          
          null();
         }
      }
   }
 };

struct EvalContext::PtrOrSLenSubStep
 {
  PtrOrSLen &ret;
  PtrOrSLen arg1;
  PtrOrSLen arg2;
  const PosName &ops;
  
  PtrOrSLenSubStep(PtrOrSLen &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret.set( SLen() );
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( arg1.slen_type )
      {
       if( arg2.slen_type )
         {
          SLen a=arg1.getSLen();
          SLen b=arg2.getSLen();
          
          SLen result=a-b;
          
          if( result.noError() )
            {
             ret.set( result );
            }
          else
            {
             eval.error("Evaluation error #; : slen overflow",ops);
           
             null();
            }
         }
       else
         {
          eval.error("Evaluation error #; : cannot evaluate integer-pointer as pointer or integer",ops);
         
          null();
         }
      }
    else
      {
       if( arg2.slen_type )
         {
          ret.set( eval.add(arg1.getPtr(),-arg2.getSLen(),ops) );
         }
       else
         {
          Ptr a=arg1.getPtr();
          Ptr b=arg2.getPtr();
          
          if( !a || !b )
            {
             null();
            }
          else
            {
             if( a.null && b.null )
               {
                null();
             
                auto step=eval.createStep(CompleteSubStep(ops),dep);
             
                eval.createStep(CmpTypeStep(step.obj.cmp,a.getType(),b.getType()),step.id);
               }
             else
               {
                ret.set( eval.sub(a,b,ops) );
               }
            }
         }
      }
   }
 };

struct EvalContext::CastValueToPtrOrIntStep
 {
  PtrOrInt &ret;
  LValue src;
  const PosName &ops;
  
  CastValueToPtrOrIntStep(PtrOrInt &ret_,Ptr ptr,const PosName &ops_) : ret(ret_),src(ptr),ops(ops_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void impossible(Eval &eval)
   {
    eval.error("Evaluation error #; : impossible cast",ops);
   
    null();
   }
  
  template <class T>
  void operator () (Eval &eval,T *)
   {
    impossible(eval); 
   }

  void castPtr(Eval &eval)
   {
    Ptr result=src.value.get<Ptr>();
    
    if( !result )
      {
       eval.error("Evaluation error #; : typeless null pointer",ops);
       
       null();
      }
    else
      {
       ret.set(result);
      }
   }
  
  void operator () (Eval &eval,TypeNode::Ptr *)
   {
    castPtr(eval);
   }
  
  void operator () (Eval &eval,TypeNode::PolyPtr *)
   {
    castPtr(eval);
   }

  template <class IntType>
  void op()
   {
    ret.cast( src.value.get<IntType>() );
   }
  
  void operator () (Eval &eval,TypeNode::Base *src_type_ptr)
   {
    if( src_type_ptr->isIntegral() )
      {
       ExtIntType(*this,src_type_ptr->type);
      }
    else
      {
       impossible(eval);
      }
   }
  
  void operator () (Eval &eval)
   {
    if( !src.type )
      {
       null();
      }
    else
      {
       ElaborateAnyPtr(*this,eval,TypeAdapter(src.type).ptr);
      }
   }
 };

struct EvalContext::CastToPtrOrIntStep
 {
  PtrOrInt &ret;
  Ptr ptr;
  const PosName &ops;
  
  CastToPtrOrIntStep(PtrOrInt &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !ptr )
      {
       null();
      }
    else
      {
       DecayAnyCase decay(ptr.getType());
       
       if( decay.type )
         {
          ret.set( eval.decay(ptr,decay.type) );
         }
       else
         {
          auto step=eval.createStep(CastValueToPtrOrIntStep(ret,ptr,ops),dep);
          
          eval.createStep(ReadPtrStep(step.obj.src,ops),step.id);
         }
      }
   };
 };

struct EvalContext::PtrOrIntAddStep
 {
  PtrOrInt &ret;
  Trio arg1;
  Trio arg2;
  const PosName &ops;
  
  PtrOrIntAddStep(PtrOrInt &ret_,const PosName &ops_) : ret(ret_),arg1(ret.type),arg2(ret.type),ops(ops_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void add(Eval &eval,Ptr ptr,OpsSLen delta)
   {
    if( OR( !ptr , delta.error(eval) ) )
      {
       null();
      }
    else
      {
       ret.set( eval.add(ptr,delta.slen,ops) );
      }
   }
  
  template <class IntType>
  void op(Eval &eval)
   {
    arg1.error(eval);
    arg2.error(eval);
    
    ret.set( arg1.get<IntType>()+arg2.get<IntType>() );
   }
    
  void operator () (Eval &eval)
   {
    TypeNode::Base::Type type=ret.type;
    
    if( arg1.type==type )
      {
       if( arg2.type==type )
         {
          ExtIntType(*this,type,eval);
         }
       else
         {
          add(eval,arg2.getPtr(),arg1.slen);
         }
      }
    else
      {
       if( arg2.type==ret.type )
         {
          add(eval,arg1.getPtr(),arg2.slen);
         }
       else
         {
          eval.error("Evaluation error #; : cannot evaluate pointer+pointer as pointer or integer",ops);
         
          null();
         }
      }
   }
 };

struct EvalContext::PtrOrIntSubStep
 {
  PtrOrInt &ret;
  PtrOrInt arg1;
  Trio arg2;
  const PosName &ops;
  
  PtrOrIntSubStep(PtrOrInt &ret_,const PosName &ops_) : ret(ret_),arg1(ret.type),arg2(ret.type),ops(ops_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void sub(Eval &eval,Ptr ptr,OpsSLen delta)
   {
    if( OR( !ptr , delta.error(eval) ) )
      {
       null();
      }
    else
      {
       ret.set( eval.add(ptr,-delta.slen,ops) );
      }
   }
  
  void sub(Eval &eval,StepId dep,Ptr a,Ptr b)
   {
    if( !a || !b )
      {
       null();
      }
    else
      {
       if( a.null && b.null )
         {
          null();
       
          auto step=eval.createStep(CompleteSubStep(ops),dep);
       
          eval.createStep(CmpTypeStep(step.obj.cmp,a.getType(),b.getType()),step.id);
         }
       else
         {
          ret.cast( eval.sub(a,b,ops) );
         }
      }
   }
  
  template <class IntType>
  void op(Eval &eval)
   {
    arg2.error(eval);
    
    ret.set( arg1.get<IntType>()-arg2.get<IntType>() );
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    TypeNode::Base::Type type=ret.type;
    
    if( arg1.type==type )
      {
       if( arg2.type==type )
         {
          ExtIntType(*this,type,eval);
         }
       else
         {
          eval.error("Evaluation error #; : cannot evaluate integer-pointer as pointer or integer",ops);
        
          null();
         }
      }
    else
      {
       if( arg2.type==ret.type )
         {
          sub(eval,arg1.getPtr(),arg2.slen);
         }
       else
         {
          sub(eval,dep,arg1.getPtr(),arg2.getPtr());
         }
      }
   }
 };

struct EvalContext::TrioAddStep
 {
  Trio &ret;
  Trio arg1;
  Trio arg2;
  const PosName &ops;
  
  TrioAddStep(Trio &ret_,const PosName &ops_) : ret(ret_),arg1(ret.type),arg2(ret.type),ops(ops_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void add(Eval &eval,Ptr ptr,OpsSLen delta)
   {
    if( OR( !ptr , delta.error(eval) ) )
      {
       null();
      }
    else
      {
       ret.set( eval.add(ptr,delta.slen,ops) );
      }
   }
  
  template <class IntType>
  void op()
   {
    ret.setAdd<IntType>(arg1,arg2,ops);
   }
  
  void operator () (Eval &eval)
   {
    TypeNode::Base::Type type=ret.type;
    
    if( arg1.type==type )
      {
       if( arg2.type==type )
         {
          ExtIntType(*this,type);
         }
       else
         {
          add(eval,arg2.getPtr(),arg1.slen);
         }
      }
    else
      {
       if( arg2.type==ret.type )
         {
          add(eval,arg1.getPtr(),arg2.slen);
         }
       else
         {
          eval.error("Evaluation error #; : cannot evaluate pointer+pointer as pointer or integer",ops);
         
          null();
         }
      }
   }
 };

struct EvalContext::TrioSubStep
 {
  Trio &ret;
  Trio arg1;
  Trio arg2;
  const PosName &ops;
  
  TrioSubStep(Trio &ret_,const PosName &ops_) : ret(ret_),arg1(ret.type),arg2(ret.type),ops(ops_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void sub(Eval &eval,Ptr ptr,OpsSLen delta)
   {
    if( OR( !ptr , delta.error(eval) ) )
      {
       null();
      }
    else
      {
       ret.set( eval.add(ptr,-delta.slen,ops) );
      }
   }
  
  void sub(Eval &eval,StepId dep,Ptr a,Ptr b)
   {
    if( !a || !b )
      {
       null();
      }
    else
      {
       if( a.null && b.null )
         {
          null();
      
          auto step=eval.createStep(CompleteSubStep(ops),dep);
      
          eval.createStep(CmpTypeStep(step.obj.cmp,a.getType(),b.getType()),step.id);
         }
       else
         {
          ret.set( eval.sub(a,b,ops) );
         }
      }
   }
  
  template <class IntType>
  void op()
   {
    ret.setSub<IntType>(arg1,arg2,ops);
   }
    
  void operator () (Eval &eval,StepId dep)
   {
    TypeNode::Base::Type type=ret.type;
    
    if( arg1.type==type )
      {
       if( arg2.type==type )
         {
          ExtIntType(*this,type);
         }
       else
         {
          eval.error("Evaluation error #; : cannot evaluate integer-pointer as pointer or integer",ops);
        
          null();
         }
      }
    else
      {
       if( arg2.type==ret.type )
         {
          sub(eval,arg1.getPtr(),arg2.slen);
         }
       else
         {
          sub(eval,dep,arg1.getPtr(),arg2.getPtr());
         }
      }
   }
 };

struct EvalContext::CastValueToTrioStep
 {
  Trio &ret;
  LValue src;
  const PosName &ops;
  
  CastValueToTrioStep(Trio &ret_,Ptr ptr,const PosName &ops_) : ret(ret_),src(ptr),ops(ops_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void impossible(Eval &eval)
   {
    eval.error("Evaluation error #; : impossible cast",ops);
   
    null();
   }
  
  template <class T>
  void operator () (Eval &eval,T *)
   {
    impossible(eval); 
   }

  void castPtr(Eval &eval)
   {
    Ptr result=src.value.get<Ptr>();
    
    if( !result )
      {
       eval.error("Evaluation error #; : typeless null pointer",ops);
       
       null();
      }
    else
      {
       ret.set(result);
      }
   }
  
  void operator () (Eval &eval,TypeNode::Ptr *)
   {
    castPtr(eval);
   }
  
  void operator () (Eval &eval,TypeNode::PolyPtr *)
   {
    castPtr(eval);
   }

  template <class IntType>
  void op()
   {
    ret.cast( src.value.get<IntType>() ,ops);
   }
  
  void operator () (Eval &eval,TypeNode::Base *src_type_ptr)
   {
    if( src_type_ptr->isIntegral() )
      {
       ExtIntType(*this,src_type_ptr->type);
      }
    else
      {
       impossible(eval);
      }
   }
  
  void operator () (Eval &eval)
   {
    if( !src.type )
      {
       null();
      }
    else
      {
       ElaborateAnyPtr(*this,eval,TypeAdapter(src.type).ptr);
      }
   }
 };

struct EvalContext::CastToTrioStep
 {
  Trio &ret;
  Ptr ptr;
  const PosName &ops;
  
  CastToTrioStep(Trio &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !ptr )
      {
       null();
      }
    else
      {
       DecayAnyCase decay(ptr.getType());
       
       if( decay.type )
         {
          ret.set( eval.decay(ptr,decay.type) );
         }
       else
         {
          auto step=eval.createStep(CastValueToTrioStep(ret,ptr,ops),dep);
          
          eval.createStep(ReadPtrStep(step.obj.src,ops),step.id);
         }
      }
   };
 };

struct EvalContext::DuoMinusStep
 {
  Trio &ret;
  Trio arg;
  
  explicit DuoMinusStep(Trio &ret_) : ret(ret_),arg(ret.type) {}
  
  template <class IntType>
  void op()
   {
    ret.setMinus<IntType>(arg);
   }
  
  void operator () ()
   {
    ExtIntType(*this,ret.type);
   }
 };

struct EvalContext::DuoAddStep
 {
  Trio &ret;
  Trio arg1;
  Trio arg2;
  const PosName &ops;
  
  DuoAddStep(Trio &ret_,const PosName &ops_) : ret(ret_),arg1(ret.type),arg2(ret.type),ops(ops_) {}
  
  template <class IntType>
  void op()
   {
    ret.setAdd<IntType>(arg1,arg2,ops);
   }
  
  void operator () ()
   {
    ExtIntType(*this,ret.type);
   }
 };

struct EvalContext::DuoMulStep
 {
  Trio &ret;
  Trio arg1;
  Trio arg2;
  const PosName &ops;
  
  DuoMulStep(Trio &ret_,const PosName &ops_) : ret(ret_),arg1(ret.type),arg2(ret.type),ops(ops_) {}
  
  template <class IntType>
  void op()
   {
    ret.setMul<IntType>(arg1,arg2,ops);
   }
  
  void operator () ()
   {
    ExtIntType(*this,ret.type);
   }
 };

struct EvalContext::DuoDivStep
 {
  Trio &ret;
  Trio arg1;
  Trio arg2;
  const PosName &ops;
  
  DuoDivStep(Trio &ret_,const PosName &ops_) : ret(ret_),arg1(ret.type),arg2(ret.type),ops(ops_) {}
  
  template <class IntType>
  void op()
   {
    ret.setDiv<IntType>(arg1,arg2,ops);
   }
  
  void operator () ()
   {
    ExtIntType(*this,ret.type);
   }
 };

struct EvalContext::DuoRemStep
 {
  Trio &ret;
  Trio arg1;
  Trio arg2;
  const PosName &ops;
  
  DuoRemStep(Trio &ret_,const PosName &ops_) : ret(ret_),arg1(ret.type),arg2(ret.type),ops(ops_) {}
  
  template <class IntType>
  void op()
   {
    ret.setRem<IntType>(arg1,arg2,ops);
   }
  
  void operator () ()
   {
    ExtIntType(*this,ret.type);
   }
 };

struct EvalContext::CastIntToDuoStep
 {
  Trio &ret;
  TypeNode::Base::Type type;
  Value arg;
  const PosName &ops;
  
  CastIntToDuoStep(Trio &ret_,TypeNode::Base::Type type_,const PosName &ops_) : ret(ret_),type(type_),ops(ops_) {}

  Value * getArg() { return &arg; }

  template <class IntType>
  void op()
   {
    ret.cast( arg.get<IntType>() ,ops);
   }
  
  void operator () ()
   {
    UseIntType(*this);
   }
 };

struct EvalContext::DuoSubStep
 {
  Trio &ret;
  Trio arg1;
  Trio arg2;
  const PosName &ops;
  
  DuoSubStep(Trio &ret_,const PosName &ops_) : ret(ret_),arg1(ret.type),arg2(ret.type),ops(ops_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void sub(Eval &eval,StepId dep,Ptr a,Ptr b)
   {
    if( !a || !b )
      {
       null();
      }
    else
      {
       if( a.null && b.null )
         {
          null();
     
          auto step=eval.createStep(CompleteSubStep(ops),dep);
     
          eval.createStep(CmpTypeStep(step.obj.cmp,a.getType(),b.getType()),step.id);
         }
       else
         {
          ret.set( eval.sub(a,b,ops) );
         }
      }
   }
  
  template <class IntType>
  void op()
   {
    ret.setSub<IntType>(arg1,arg2,ops);
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    TypeNode::Base::Type type=ret.type;
    
    if( arg1.type==type )
      {
       if( arg2.type==type )
         {
          ExtIntType(*this,type);
         }
       else
         {
          eval.error("Evaluation error #; : cannot evaluate integer-pointer as integer",ops);
        
          null();
         }
      }
    else
      {
       if( arg2.type==ret.type )
         {
          eval.error("Evaluation error #; : cannot evaluate pointer-integer as integer",ops);
       
          null();
         }
       else
         {
          sub(eval,dep,arg1.getPtr(),arg2.getPtr());
         }
      }
   }
 };

struct EvalContext::CastValueToDuoStep
 {
  Trio &ret;
  LValue src;
  const PosName &ops;
  
  CastValueToDuoStep(Trio &ret_,Ptr ptr,const PosName &ops_) : ret(ret_),src(ptr),ops(ops_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void impossible(Eval &eval)
   {
    eval.error("Evaluation error #; : impossible cast",ops);
   
    null();
   }
  
  template <class T>
  void operator () (Eval &eval,T *)
   {
    impossible(eval); 
   }

  template <class IntType>
  void op()
   {
    ret.cast( src.value.get<IntType>() ,ops);
   }
  
  void operator () (Eval &eval,TypeNode::Base *src_type_ptr)
   {
    if( src_type_ptr->isIntegral() )
      {
       ExtIntType(*this,src_type_ptr->type);
      }
    else
      {
       impossible(eval);
      }
   }
  
  void operator () (Eval &eval)
   {
    if( !src.type )
      {
       null();
      }
    else
      {
       ElaborateAnyPtr(*this,eval,TypeAdapter(src.type).ptr);
      }
   }
 };

struct EvalContext::CastToDuoStep
 {
  Trio &ret;
  Ptr ptr;
  const PosName &ops;
  
  CastToDuoStep(Trio &ret_,const PosName &ops_) : ret(ret_),ops(ops_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !ptr )
      {
       null();
      }
    else
      {
       auto step=eval.createStep(CastValueToDuoStep(ret,ptr,ops),dep);
          
       eval.createStep(ReadPtrStep(step.obj.src,ops),step.id);
      }
   };
 };

struct EvalContext::CastValueToStructStep
 {
  Value *result; // may == 0 
  bool *flags;
  StructNode *struct_node;
  From from;
  LValue src;
  const PosName &ops;
  
  CastValueToStructStep(Value *result_,bool *flags_,StructNode *struct_node_,From from_,Ptr ptr,const PosName &ops_) 
   : result(result_),flags(flags_),struct_node(struct_node_),from(from_),src(ptr),ops(ops_) {}
 
  void null(Eval &eval,StepId dep)
   {
    NullStruct(eval,result,flags,struct_node,dep);
   }
  
  void impossible(Eval &eval,StepId dep)
   {
    eval.error("Evaluation error #; : impossible cast",ops);
   
    null(eval,dep);
   }

  template <class T>
  void operator () (Eval &eval,StepId dep,T *)
   {
    impossible(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,StructNode *src_struct_node)
   {
    if( struct_node==src_struct_node )
      {
       if( Value *ptr=result )
         {
          bool *f=flags;
          Value *data=src.value.get<Block>().data.ptr;
          
          for(ulen cnt=struct_node->field_list.count; cnt ;cnt--)
            {
             if( !*f ) *ptr=*data;
           
             ++ptr;
             ++data;
             ++f;
            }
         }
      }
    else
      {
       if( Value *ptr=result )
         {
          Value *data=src.value.get<Block>().data.ptr;
         
          for(FieldNode &src_field : src_struct_node->field_list )
            {
             if( FieldNode *field=struct_node->find(src_field.name) )
               {
                ulen index=field->field_index;
                
                if( !flags[index] )
                  {
                   CastField(eval,ptr+index,field->type_node,eval.ptrToField(src.ptr,&src_field),data[src_field.field_index],from,ops,dep);
                  
                   flags[index]=true;
                  }
               }
            }
          
          DefStruct(eval,ptr,flags,struct_node,from,dep);
         }
       else
         {
          Value *data=src.value.get<Block>().data.ptr;
         
          for(FieldNode &src_field : src_struct_node->field_list )
            {
             if( FieldNode *field=struct_node->find(src_field.name) )
               {
                ulen index=field->field_index;
                
                if( !flags[index] )
                  {
                   CastField(eval,0,field->type_node,eval.ptrToField(src.ptr,&src_field),data[src_field.field_index],from,ops,dep);
                  
                   flags[index]=true;
                  }
               }
            }
          
          DefStruct(eval,0,flags,struct_node,from,dep);
         }
      }
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !src.type )
      {
       null(eval,dep);
      }
    else
      {
       ElaborateAnyPtr(*this,eval,dep,TypeAdapter(src.type).ptr);
      }
   }
 };

struct EvalContext::CastToStructStep
 {
  Value *result; // may == 0 
  bool *flags;
  StructNode *struct_node;
  From from;
  Ptr ptr;
  const PosName &ops;
  
  CastToStructStep(Value *result_,bool *flags_,StructNode *struct_node_,From from_,const PosName &ops_) 
   : result(result_),flags(flags_),struct_node(struct_node_),from(from_),ops(ops_) {}
  
  void null(Eval &eval,StepId dep)
   {
    NullStruct(eval,result,flags,struct_node,dep);
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    if( !ptr )
      {
       null(eval,dep);
      }
    else
      {
       auto step=eval.createStep(CastValueToStructStep(result,flags,struct_node,from,ptr,ops),dep);
          
       eval.createStep(ReadPtrStep(step.obj.src,ops),step.id);
      }
   }
 };

struct EvalContext::ExprAddressStep
 {
  Ptr &ret;
  From from;
  ExprNode *expr;
  
  ExprAddressStep(Ptr &ret_,From from_,ExprNode *expr_) : ret(ret_),from(from_),expr(expr_) {}
  
  void null()
   {
    ret=Ptr();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr);
  
  void operator () (Eval &eval,StepId,ExprNode::Address *)
   {
    eval.error("Evaluation error #; : &a is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Plus *)
   {
    eval.error("Evaluation error #; : +a is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Minus *)
   {
    eval.error("Evaluation error #; : -a is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Add *)
   {
    eval.error("Evaluation error #; : a+b is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Sub *)
   {
    eval.error("Evaluation error #; : a-b is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Mul *)
   {
    eval.error("Evaluation error #; : a*b is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Div *)
   {
    eval.error("Evaluation error #; : a/b is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Rem *)
   {
    eval.error("Evaluation error #; : a%b is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ind *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Select *expr_ptr)
   {
    auto step=eval.createStep(SelectFieldStep(ret,expr_ptr->name,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr_ptr->arg),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::PtrSelect *expr_ptr);
  
  void operator () (Eval &eval,StepId,ExprNode::Domain *)
   {
    eval.error("Evaluation error #; : I(a) is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Ref *expr_ptr)
   {
    if( ConstNode *node=eval.doLink(from,expr_ptr) )
      {
       ret=eval.ptrTo(node);
      }
    else
      {
       eval.error("Evaluation error #; : undefined name",expr->ops);
      
       null();
      }
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Null *)
   {
    eval.error("Evaluation error #; : null is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Number *)
   {
    eval.error("Evaluation error #; : Number is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::String *)
   {
    eval.error("Evaluation error #; : String is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::IP *)
   {
    eval.error("Evaluation error #; : IP is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::EmptyList *)
   {
    eval.error("Evaluation error #; : {} is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NonameList *)
   {
    eval.error("Evaluation error #; : {a,...} is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NamedList *)
   {
    eval.error("Evaluation error #; : {.name=a,...} is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyEmptyList *)
   {
    eval.error("Evaluation error #; : b {.name=a,...} is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyNamedList *)
   {
    eval.error("Evaluation error #; : b {.name=a,...} is not lvalue",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,expr->ptr);
   }
 };

struct EvalContext::ExprSLenStep
 {
  SLen &ret;
  From from;
  ExprNode *expr;
  
  ExprSLenStep(SLen &ret_,From from_,ExprNode *expr_) : ret(ret_),from(from_),expr(expr_) {}
  
  void null()
   {
    ret=SLen();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr);
  
  void operator () (Eval &eval,StepId,ExprNode::Address *)
   {
    eval.error("Evaluation error #; : cannot evaluate &a as slen",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Plus *expr_ptr)
   {
    eval.createStep(ExprSLenStep(ret,from,expr_ptr->arg),dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Minus *expr_ptr)
   {
    auto step=eval.createStep(SLenMinusStep(ret),dep);
    
    eval.createStep(ExprSLenStep(step.obj.arg,from,expr_ptr->arg),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Add *expr_ptr)
   {
    auto step=eval.createStep(SLenAddStep(ret,expr->ops),dep);
    
    eval.createStep(ExprSLenStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Sub *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Mul *expr_ptr)
   {
    auto step=eval.createStep(SLenMulStep(ret,expr->ops),dep);
    
    eval.createStep(ExprSLenStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Div *expr_ptr)
   {
    auto step=eval.createStep(SLenDivStep(ret,expr->ops),dep);
    
    eval.createStep(ExprSLenStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Rem *expr_ptr)
   {
    auto step=eval.createStep(SLenRemStep(ret,expr->ops),dep);
    
    eval.createStep(ExprSLenStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ind *)
   {
    auto step=eval.createStep(CastToSLenStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Select *)
   {
    auto step=eval.createStep(CastToSLenStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::PtrSelect *)
   {
    auto step=eval.createStep(CastToSLenStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Domain *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ref *)
   {
    auto step=eval.createStep(CastToSLenStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &,StepId,ExprNode::Null *)
   {
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Number *expr_ptr)
   {
    SLen result=StrToInt<SLen>(expr_ptr->number);
    
    if( result.noError() )
      {
       ret=result;
      }
    else
      {
       eval.error("Evaluation error #; : slen overflow",expr->ops);
      
       null();
      }
   }
  
  void operator () (Eval &eval,StepId,ExprNode::String *)
   {
    eval.error("Evaluation error #; : cannot evaluate String as slen",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::IP *)
   {
    eval.error("Evaluation error #; : cannot evaluate IP as slen",expr->ops);
    
    null();
   }
  
  void operator () (Eval &,StepId,ExprNode::EmptyList *)
   {
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NonameList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {a,...} as slen",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NamedList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {.name=a,...} as slen",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyEmptyList *)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as slen",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyNamedList *)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as slen",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,expr->ptr);
   }
 };

struct EvalContext::ExprPtrOrSLenStep
 {
  PtrOrSLen &ret;
  From from;
  ExprNode *expr;
  
  ExprPtrOrSLenStep(PtrOrSLen &ret_,From from_,ExprNode *expr_) : ret(ret_),from(from_),expr(expr_) {}
  
  void null()
   {
    ret.set( SLen() );
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Address *expr_ptr)
   {
    auto step=eval.createStep(SetPtrStep<PtrOrSLen>(ret),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr_ptr->arg),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Plus *expr_ptr)
   {
    auto step=eval.createStep(SetSLenStep(ret),dep);

    ExprSLenStep(step.obj.slen,from,expr)(eval,step.id,expr_ptr);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Minus *expr_ptr)
   {
    auto step=eval.createStep(SetSLenStep(ret),dep);

    ExprSLenStep(step.obj.slen,from,expr)(eval,step.id,expr_ptr);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Add *expr_ptr)
   {
    auto step=eval.createStep(PtrOrSLenAddStep(ret,expr->ops),dep);
    
    eval.createStep(ExprPtrOrSLenStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprPtrOrSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Sub *expr_ptr)
   {
    auto step=eval.createStep(PtrOrSLenSubStep(ret,expr->ops),dep);
    
    eval.createStep(ExprPtrOrSLenStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprPtrOrSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Mul *expr_ptr)
   {
    auto step=eval.createStep(SetSLenStep(ret),dep);

    ExprSLenStep(step.obj.slen,from,expr)(eval,step.id,expr_ptr);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Div *expr_ptr)
   {
    auto step=eval.createStep(SetSLenStep(ret),dep);

    ExprSLenStep(step.obj.slen,from,expr)(eval,step.id,expr_ptr);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Rem *expr_ptr)
   {
    auto step=eval.createStep(SetSLenStep(ret),dep);

    ExprSLenStep(step.obj.slen,from,expr)(eval,step.id,expr_ptr);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ind *)
   {
    auto step=eval.createStep(CastToPtrOrSLenStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Select *)
   {
    auto step=eval.createStep(CastToPtrOrSLenStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::PtrSelect *)
   {
    auto step=eval.createStep(CastToPtrOrSLenStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Domain *expr_ptr)
   {
    auto step=eval.createStep(SetSLenStep(ret),dep);

    ExprSLenStep(step.obj.slen,from,expr)(eval,step.id,expr_ptr);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ref *)
   {
    auto step=eval.createStep(CastToPtrOrSLenStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &,StepId,ExprNode::Null *)
   {
    null();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Number *expr_ptr)
   {
    auto step=eval.createStep(SetSLenStep(ret),dep);

    ExprSLenStep(step.obj.slen,from,expr)(eval,step.id,expr_ptr);
   }
  
  void operator () (Eval &eval,StepId,ExprNode::String *)
   {
    eval.error("Evaluation error #; : cannot evaluate String as pointer or slen",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::IP *)
   {
    eval.error("Evaluation error #; : cannot evaluate IP as pointer or slen",expr->ops);

    null();
   }
  
  void operator () (Eval &,StepId,ExprNode::EmptyList *)
   {
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NonameList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {a,...} as pointer or slen",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NamedList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {.name=a,...} as pointer or slen",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyEmptyList *)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as pointer or slen",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyNamedList *)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as pointer or slen",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,expr->ptr);
   }
 };

void EvalContext::ExprSLenStep::operator () (Eval &eval,StepId dep,ExprNode::Sub *expr_ptr)
 {
  auto step=eval.createStep(SLenSubStep(ret,expr->ops),dep);
 
  eval.createStep(ExprPtrOrSLenStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
  eval.createStep(ExprPtrOrSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
 }

struct EvalContext::ExprPtrOrIntStep
 {
  PtrOrInt &ret;
  From from;
  ExprNode *expr;
  
  ExprPtrOrIntStep(PtrOrInt &ret_,From from_,ExprNode *expr_) : ret(ret_),from(from_),expr(expr_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Address *expr_ptr)
   {
    auto step=eval.createStep(SetPtrStep<PtrOrInt>(ret),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr_ptr->arg),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Plus *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Minus *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Add *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Sub *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Mul *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Div *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Rem *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ind *)
   {
    auto step=eval.createStep(CastToPtrOrIntStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Select *)
   {
    auto step=eval.createStep(CastToPtrOrIntStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::PtrSelect *)
   {
    auto step=eval.createStep(CastToPtrOrIntStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Domain *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ref *)
   {
    auto step=eval.createStep(CastToPtrOrIntStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &,StepId,ExprNode::Null *)
   {
    null();
   }
  
  void operator () (Eval &,StepId,ExprNode::Number *expr_ptr)
   {
    ret.set(expr_ptr->number);    
   }
  
  void operator () (Eval &eval,StepId,ExprNode::String *)
   {
    eval.error("Evaluation error #; : cannot evaluate String as pointer or integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::IP *)
   {
    eval.error("Evaluation error #; : cannot evaluate IP as pointer or integer",expr->ops);

    null();
   }
  
  void operator () (Eval &,StepId,ExprNode::EmptyList *)
   {
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NonameList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {a,...} as pointer or integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NamedList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {.name=a,...} as pointer or integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyEmptyList *)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as pointer or integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyNamedList *)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as pointer or integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,expr->ptr);
   }
 };

struct EvalContext::ExprDuoStep
 {
  Trio &ret;
  From from;
  ExprNode *expr;
  
  ExprDuoStep(Trio &ret_,From from_,ExprNode *expr_) : ret(ret_),from(from_),expr(expr_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr);
  
  void operator () (Eval &eval,StepId,ExprNode::Address *)
   {
    eval.error("Evaluation error #; : cannot evaluate &a as integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Plus *expr_ptr)
   {
    eval.createStep(ExprDuoStep(ret,from,expr_ptr->arg),dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Minus *expr_ptr)
   {
    auto step=eval.createStep(DuoMinusStep(ret),dep);
    
    eval.createStep(ExprDuoStep(step.obj.arg,from,expr_ptr->arg),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Add *expr_ptr)
   {
    auto step=eval.createStep(DuoAddStep(ret,expr->ops),dep);
    
    eval.createStep(ExprDuoStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprDuoStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Sub *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Mul *expr_ptr)
   {
    auto step=eval.createStep(DuoMulStep(ret,expr->ops),dep);
    
    eval.createStep(ExprDuoStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprDuoStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Div *expr_ptr)
   {
    auto step=eval.createStep(DuoDivStep(ret,expr->ops),dep);
    
    eval.createStep(ExprDuoStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprDuoStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Rem *expr_ptr)
   {
    auto step=eval.createStep(DuoRemStep(ret,expr->ops),dep);
    
    eval.createStep(ExprDuoStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprDuoStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ind *)
   {
    auto step=eval.createStep(CastToDuoStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Select *)
   {
    auto step=eval.createStep(CastToDuoStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::PtrSelect *)
   {
    auto step=eval.createStep(CastToDuoStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Domain *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ref *)
   {
    auto step=eval.createStep(CastToDuoStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &,StepId,ExprNode::Null *)
   {
    null();
   }
  
  void operator () (Eval &,StepId,ExprNode::Number *expr_ptr)
   {
    ret.set(expr_ptr->number,expr->ops);    
   }
  
  void operator () (Eval &eval,StepId,ExprNode::String *)
   {
    eval.error("Evaluation error #; : cannot evaluate String as integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::IP *)
   {
    eval.error("Evaluation error #; : cannot evaluate IP as integer",expr->ops);

    null();
   }
  
  void operator () (Eval &,StepId,ExprNode::EmptyList *)
   {
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NonameList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {a,...} as integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NamedList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {.name=a,...} as integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyEmptyList *)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyNamedList *)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,expr->ptr);
   }
 };

struct EvalContext::ExprTrioStep
 {
  Trio &ret;
  From from;
  ExprNode *expr;
  
  ExprTrioStep(Trio &ret_,From from_,ExprNode *expr_) : ret(ret_),from(from_),expr(expr_) {}
  
  void null()
   {
    ret.set_null();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::Address *expr_ptr)
   {
    auto step=eval.createStep(SetPtrStep<Trio>(ret),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr_ptr->arg),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Plus *expr_ptr)
   {
    ExprDuoStep(ret,from,expr_ptr->arg)(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Minus *expr_ptr)
   {
    ExprDuoStep(ret,from,expr)(eval,dep,expr_ptr);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Add *expr_ptr)
   {
    auto step=eval.createStep(TrioAddStep(ret,expr->ops),dep);
    
    eval.createStep(ExprTrioStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprTrioStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Sub *expr_ptr)
   {
    auto step=eval.createStep(TrioSubStep(ret,expr->ops),dep);
    
    eval.createStep(ExprTrioStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprTrioStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Mul *expr_ptr)
   {
    ExprDuoStep(ret,from,expr)(eval,dep,expr_ptr);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Div *expr_ptr)
   {
    ExprDuoStep(ret,from,expr)(eval,dep,expr_ptr);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Rem *expr_ptr)
   {
    ExprDuoStep(ret,from,expr)(eval,dep,expr_ptr);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ind *)
   {
    auto step=eval.createStep(CastToTrioStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Select *)
   {
    auto step=eval.createStep(CastToTrioStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::PtrSelect *)
   {
    auto step=eval.createStep(CastToTrioStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Domain *expr_ptr)
   {
    ExprDuoStep(ret,from,expr)(eval,dep,expr_ptr);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ref *)
   {
    auto step=eval.createStep(CastToTrioStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &,StepId,ExprNode::Null *)
   {
    null();
   }
  
  void operator () (Eval &,StepId,ExprNode::Number *expr_ptr)
   {
    ret.set(expr_ptr->number,expr->ops);    
   }
  
  void operator () (Eval &eval,StepId,ExprNode::String *)
   {
    eval.error("Evaluation error #; : cannot evaluate String as pointer or integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::IP *)
   {
    eval.error("Evaluation error #; : cannot evaluate IP as pointer or integer",expr->ops);

    null();
   }
  
  void operator () (Eval &,StepId,ExprNode::EmptyList *)
   {
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NonameList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {a,...} as pointer or integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NamedList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {.name=a,...} as pointer or integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyEmptyList *)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as pointer or integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyNamedList *)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as pointer or integer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,expr->ptr);
   }
 };

void EvalContext::ExprPtrOrIntStep::operator () (Eval &eval,StepId dep,ExprNode::Add *expr_ptr)
 {
  auto step=eval.createStep(PtrOrIntAddStep(ret,expr->ops),dep);
  
  eval.createStep(ExprTrioStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
  eval.createStep(ExprTrioStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
 }

void EvalContext::ExprPtrOrIntStep::operator () (Eval &eval,StepId dep,ExprNode::Sub *expr_ptr)
 {
  auto step=eval.createStep(PtrOrIntSubStep(ret,expr->ops),dep);
  
  eval.createStep(ExprPtrOrIntStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
  eval.createStep(ExprTrioStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
 }

void EvalContext::ExprDuoStep::operator () (Eval &eval,StepId dep,ExprNode::Sub *expr_ptr)
 {
  auto step=eval.createStep(DuoSubStep(ret,expr->ops),dep);
  
  eval.createStep(ExprTrioStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
  eval.createStep(ExprTrioStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
 }

struct EvalContext::ExprPtrStep
 {
  Ptr &ret;
  From from;
  ExprNode *expr;
  
  ExprPtrStep(Ptr &ret_,From from_,ExprNode *expr_) : ret(ret_),from(from_),expr(expr_) {}

  void null()
   {
    ret=Ptr();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr)
   {
    auto step=eval.createStep(CastToPtrStep(ret,expr->ops),dep);
    
    eval.createStep(ExprPtrStep(step.obj.ptr,from,expr_ptr->arg),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Address *expr_ptr)
   {
    eval.createStep(ExprAddressStep(ret,from,expr_ptr->arg),dep);
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Plus *)
   {
    eval.error("Evaluation error #; : cannot evaluate +a as pointer",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Minus *)
   {
    eval.error("Evaluation error #; : cannot evaluate -a as pointer",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Add *expr_ptr)
   {
    auto step=eval.createStep(AddAnyPtrStep(ret,expr->ops),dep);
    
    eval.createStep(ExprPtrOrSLenStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprPtrOrSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Sub *expr_ptr)
   {
    auto step=eval.createStep(SubAnyPtrStep(ret,expr->ops),dep);
    
    eval.createStep(ExprPtrStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Mul *)
   {
    eval.error("Evaluation error #; : cannot evaluate a*b as pointer",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Div *)
   {
    eval.error("Evaluation error #; : cannot evaluate a/b as pointer",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Rem *)
   {
    eval.error("Evaluation error #; : cannot evaluate a%b as pointer",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ind *)
   {
    auto step=eval.createStep(CastToPtrStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Select *)
   {
    auto step=eval.createStep(CastToPtrStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::PtrSelect *)
   {
    auto step=eval.createStep(CastToPtrStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Domain *)
   {
    eval.error("Evaluation error #; : cannot evaluate I(a) as pointer",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ref *)
   {
    auto step=eval.createStep(CastToPtrStep(ret,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Null *)
   {
    eval.error("Evaluation error #; : cannot evaluate null as pointer",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::Number *)
   {
    eval.error("Evaluation error #; : cannot evaluate Number as pointer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::String *)
   {
    eval.error("Evaluation error #; : cannot evaluate String as pointer",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::IP *)
   {
    eval.error("Evaluation error #; : cannot evaluate IP as pointer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::EmptyList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {} as pointer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NonameList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {a,...} as pointer",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::NamedList *)
   {
    eval.error("Evaluation error #; : cannot evaluate {.name=a,...} as pointer",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyEmptyList *)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as pointer",expr->ops);
    
    null();
   }
  
  void operator () (Eval &eval,StepId,ExprNode::ApplyNamedList *)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as pointer",expr->ops);

    null();
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,expr->ptr);
   }
 };

void EvalContext::ExprAddressStep::operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr)
 {
  eval.createStep(ExprPtrStep(ret,from,expr_ptr->arg),dep);
 }

void EvalContext::ExprAddressStep::operator () (Eval &eval,StepId dep,ExprNode::Ind *expr_ptr)
 {
  auto step=eval.createStep(AddAnyPtrStep(ret,expr->ops),dep);
  
  eval.createStep(ExprPtrOrSLenStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
  eval.createStep(ExprPtrOrSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
 }

void EvalContext::ExprAddressStep::operator () (Eval &eval,StepId dep,ExprNode::PtrSelect *expr_ptr)
 {
  auto step=eval.createStep(SelectFieldStep(ret,expr_ptr->name,expr->ops),dep);
  
  eval.createStep(ExprPtrStep(step.obj.ptr,from,expr_ptr->arg),step.id);
 }

void EvalContext::ExprSLenStep::operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr)
 {
  auto step=eval.createStep(CastToSLenStep(ret,expr->ops),dep);
  
  eval.createStep(ExprPtrStep(step.obj.ptr,from,expr_ptr->arg),step.id);
 }

void EvalContext::ExprPtrOrSLenStep::operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr)
 {
  auto step=eval.createStep(CastToPtrOrSLenStep(ret,expr->ops),dep);
  
  eval.createStep(ExprPtrStep(step.obj.ptr,from,expr_ptr->arg),step.id);
 }

void EvalContext::ExprPtrOrIntStep::operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr)
 {
  auto step=eval.createStep(CastToPtrOrIntStep(ret,expr->ops),dep);
  
  eval.createStep(ExprPtrStep(step.obj.ptr,from,expr_ptr->arg),step.id);
 }

void EvalContext::ExprDuoStep::operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr)
 {
  auto step=eval.createStep(CastToDuoStep(ret,expr->ops),dep);
  
  eval.createStep(ExprPtrStep(step.obj.ptr,from,expr_ptr->arg),step.id);
 }

void EvalContext::ExprTrioStep::operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr)
 {
  auto step=eval.createStep(CastToTrioStep(ret,expr->ops),dep);
  
  eval.createStep(ExprPtrStep(step.obj.ptr,from,expr_ptr->arg),step.id);
 }

struct EvalContext::ExprStructStep
 {
  Value *result; // may == 0 
  bool *flags;
  StructNode *struct_node;
  From from;
  ExprNode *expr;
  
  ExprStructStep(Value *result_,bool *flags_,StructNode *struct_node_,From from_,ExprNode *expr_)
   : result(result_),flags(flags_),struct_node(struct_node_),from(from_),expr(expr_) {}
  
  void null(Eval &eval,StepId dep)
   {
    NullStruct(eval,result,flags,struct_node,dep);
   }
  
  void apply(Eval &eval,StepId dep,NamedExprList &list);  
  
  void operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr)
   {
    auto step=eval.createStep(CastToStructStep(result,flags,struct_node,from,expr->ops),dep);
    
    eval.createStep(ExprPtrStep(step.obj.ptr,from,expr_ptr->arg),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Address *)
   {
    eval.error("Evaluation error #; : cannot evaluate &a as struct S",expr->ops);
    
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Plus *)
   {
    eval.error("Evaluation error #; : cannot evaluate +a as struct S",expr->ops);
    
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Minus *)
   {
    eval.error("Evaluation error #; : cannot evaluate -a as struct S",expr->ops);
    
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Add *)
   {
    eval.error("Evaluation error #; : cannot evaluate a+b as struct S",expr->ops);
    
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Sub *)
   {
    eval.error("Evaluation error #; : cannot evaluate a-b as struct S",expr->ops);
    
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Mul *)
   {
    eval.error("Evaluation error #; : cannot evaluate a*b as struct S",expr->ops);
    
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Div *)
   {
    eval.error("Evaluation error #; : cannot evaluate a/b as struct S",expr->ops);
    
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Rem *)
   {
    eval.error("Evaluation error #; : cannot evaluate a%b as struct S",expr->ops);
    
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ind *)
   {
    auto step=eval.createStep(CastToStructStep(result,flags,struct_node,from,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Select *)
   {
    auto step=eval.createStep(CastToStructStep(result,flags,struct_node,from,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::PtrSelect *)
   {
    auto step=eval.createStep(CastToStructStep(result,flags,struct_node,from,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Domain *)
   {
    eval.error("Evaluation error #; : cannot evaluate I(a) as struct S",expr->ops);
    
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Ref *)
   {
    auto step=eval.createStep(CastToStructStep(result,flags,struct_node,from,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Null *)
   {
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::Number *)
   {
    eval.error("Evaluation error #; : cannot evaluate Number as struct S",expr->ops);
    
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::String *)
   {
    eval.error("Evaluation error #; : cannot evaluate String as struct S",expr->ops);
    
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::IP *)
   {
    eval.error("Evaluation error #; : cannot evaluate IP as struct S",expr->ops);
    
    null(eval,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::EmptyList *)
   {
    DefStruct(eval,result,flags,struct_node,from,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::NonameList *expr_ptr);
  
  void operator () (Eval &eval,StepId dep,ExprNode::NamedList *expr_ptr)
   {
    apply(eval,dep,expr_ptr->list);
    
    DefStruct(eval,result,flags,struct_node,from,dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::ApplyEmptyList *expr_ptr)
   {
    eval.createStep(ExprStructStep(result,flags,struct_node,from,expr_ptr->arg),dep);
   }
  
  void operator () (Eval &eval,StepId dep,ExprNode::ApplyNamedList *expr_ptr)
   {
    apply(eval,dep,expr_ptr->list);

    eval.createStep(ExprStructStep(result,flags,struct_node,from,expr_ptr->arg),dep);
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,expr->ptr);
   }
 };

struct EvalContext::ExprStep
 {
  Value *ret;
  TypeNode *type;
  From from;
  ExprNode *expr;
  
  ExprStep(Value *ret_,TypeNode *type_,From from_,ExprNode *expr_) 
   : ret(ret_),type(type_),from(from_),expr(expr_) {}

  // Deref

  void operator () (Eval &eval,StepId dep,ExprNode::Deref *expr_ptr)
   {
    auto step=eval.createStep(CastStep(ret,type,from,expr->ops),dep);
    
    eval.createStep(ExprPtrStep(step.obj.ptr,from,expr_ptr->arg),step.id);
   }

  // Address

  void operator () (Eval &eval,StepId dep,ExprNode::Address *,TypeNode::Base *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate &a as base type",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Address *expr_ptr,TypeNode::Ptr *type_ptr)
   {
    auto step=eval.createStep(CheckPtrStep(ret,type_ptr->type_node,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr_ptr->arg),step.id);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Address *expr_ptr,TypeNode::PolyPtr *type_ptr)
   {
    auto step=eval.createStep(CheckPtrStep(ret,type_ptr->type_list,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr_ptr->arg),step.id);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Address *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate &a as T[]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Address *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate &a as T[Len]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Address *,StructNode *struct_node)
   {
    eval.error("Evaluation error #; : cannot evaluate &a as struct S",expr->ops);
    
    null(eval,dep,struct_node);
   }

  // Plus

  void operator () (Eval &eval,StepId dep,ExprNode::Plus *expr_ptr,TypeNode::Base *type_ptr)
   {
    if( type_ptr->isIntegral() )
      {
       eval.createStep(ExprStep(ret,type,from,expr_ptr->arg),dep);
      }
    else
      {
       eval.error("Evaluation error #; : cannot evaluate +a as text or ip",expr->ops);
       
       null(eval,dep,type_ptr);
      }
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Plus *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate +a as T *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Plus *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate +a as {T,...} *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Plus *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate +a as T[]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Plus *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate +a as T[Len]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Plus *,StructNode *struct_node)
   {
    eval.error("Evaluation error #; : cannot evaluate +a as struct S",expr->ops);
    
    null(eval,dep,struct_node);
   }

  // Minus

  void operator () (Eval &eval,StepId dep,ExprNode::Minus *expr_ptr,TypeNode::Base *type_ptr)
   {
    if( type_ptr->isIntegral() )
      {
       auto step=eval.createStep(MinusStep(ret,type_ptr->type),dep);
       
       eval.createStep(ExprStep(step.obj.getArg(),type,from,expr_ptr->arg),step.id);
      }
    else
      {
       eval.error("Evaluation error #; : cannot evaluate -a as text or ip",expr->ops);
       
       null(eval,dep,type_ptr);
      }
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Minus *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate -a as T *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Minus *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate -a as {T,...} *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Minus *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate -a as T[]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Minus *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate -a as T[Len]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Minus *,StructNode *struct_node)
   {
    eval.error("Evaluation error #; : cannot evaluate -a as struct S",expr->ops);
    
    null(eval,dep,struct_node);
   }

  // Add

  void operator () (Eval &eval,StepId dep,ExprNode::Add *expr_ptr,TypeNode::Base *type_ptr)
   {
    if( type_ptr->isIntegral() )
      {
       auto step=eval.createStep(AddStep(ret,type_ptr->type),dep);
       
       eval.createStep(ExprStep(step.obj.getArg1(),type,from,expr_ptr->arg1),step.id);
       eval.createStep(ExprStep(step.obj.getArg2(),type,from,expr_ptr->arg2),step.id);
      }
    else if( type_ptr->isText() )
      {
       auto step=eval.createStep(AddTextStep(ret),dep);
      
       eval.createStep(ExprStep(step.obj.getArg1(),type,from,expr_ptr->arg1),step.id);
       eval.createStep(ExprStep(step.obj.getArg2(),type,from,expr_ptr->arg2),step.id);
      }
    else 
      {
       eval.error("Evaluation error #; : cannot evaluate a+b as ip",expr->ops);
       
       null(eval,dep,type_ptr);
      }
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Add *expr_ptr,TypeNode::Ptr *type_ptr)
   {
    auto step=eval.createStep(AddPtrStep(ret,type_ptr->type_node,expr->ops),dep);
    
    eval.createStep(ExprPtrOrSLenStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprPtrOrSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Add *expr_ptr,TypeNode::PolyPtr *type_ptr)
   {
    auto step=eval.createStep(AddPtrStep(ret,type_ptr->type_list,expr->ops),dep);
    
    eval.createStep(ExprPtrOrSLenStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprPtrOrSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Add *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a+b as T[]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Add *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a+b as T[Len]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Add *,StructNode *struct_node)
   {
    eval.error("Evaluation error #; : cannot evaluate a+b as struct S",expr->ops);
    
    null(eval,dep,struct_node);
   }

  // Sub

  void operator () (Eval &eval,StepId dep,ExprNode::Sub *expr_ptr,TypeNode::Base *type_ptr)
   {
    if( type_ptr->isIntegral() )
      {
       auto step=eval.createStep(SubStep(ret,type_ptr->type,expr->ops),dep);
      
       eval.createStep(ExprPtrOrIntStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
       eval.createStep(ExprPtrOrIntStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
      }
    else 
      {
       eval.error("Evaluation error #; : cannot evaluate a-b as text or ip",expr->ops);
       
       null(eval,dep,type_ptr);
      }
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Sub *expr_ptr,TypeNode::Ptr *type_ptr)
   {
    auto step=eval.createStep(SubPtrStep(ret,type_ptr->type_node,expr->ops),dep);
    
    eval.createStep(ExprPtrStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Sub *expr_ptr,TypeNode::PolyPtr *type_ptr)
   {
    auto step=eval.createStep(SubPtrStep(ret,type_ptr->type_list,expr->ops),dep);
    
    eval.createStep(ExprPtrStep(step.obj.arg1,from,expr_ptr->arg1),step.id);
    eval.createStep(ExprSLenStep(step.obj.arg2,from,expr_ptr->arg2),step.id);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Sub *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a-b as T[]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Sub *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a-b as T[Len]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Sub *,StructNode *struct_node)
   {
    eval.error("Evaluation error #; : cannot evaluate a-b as struct S",expr->ops);
    
    null(eval,dep,struct_node);
   }

  // Mul

  void operator () (Eval &eval,StepId dep,ExprNode::Mul *expr_ptr,TypeNode::Base *type_ptr)
   {
    if( type_ptr->isIntegral() )
      {
       auto step=eval.createStep(MulStep(ret,type_ptr->type),dep);
       
       eval.createStep(ExprStep(step.obj.getArg1(),type,from,expr_ptr->arg1),step.id);
       eval.createStep(ExprStep(step.obj.getArg2(),type,from,expr_ptr->arg2),step.id);
      }
    else
      {
       eval.error("Evaluation error #; : cannot evaluate a*b as text or ip",expr->ops);
       
       null(eval,dep,type_ptr);
      }
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Mul *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a*b as T *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Mul *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a*b as {T,...} *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Mul *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a*b as T[]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Mul *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a*b as T[Len]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Mul *,StructNode *struct_node)
   {
    eval.error("Evaluation error #; : cannot evaluate a*b as struct S",expr->ops);
    
    null(eval,dep,struct_node);
   }

  // Div

  void operator () (Eval &eval,StepId dep,ExprNode::Div *expr_ptr,TypeNode::Base *type_ptr)
   {
    if( type_ptr->isIntegral() )
      {
       auto step=eval.createStep(DivStep(ret,type_ptr->type,expr->ops),dep);
       
       eval.createStep(ExprStep(step.obj.getArg1(),type,from,expr_ptr->arg1),step.id);
       eval.createStep(ExprStep(step.obj.getArg2(),type,from,expr_ptr->arg2),step.id);
      }
    else
      {
       eval.error("Evaluation error #; : cannot evaluate a/b as text or ip",expr->ops);
       
       null(eval,dep,type_ptr);
      }
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Div *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a/b as T *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Div *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a/b as {T,...} *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Div *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a/b as T[]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Div *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a/b as T[Len]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Div *,StructNode *struct_node)
   {
    eval.error("Evaluation error #; : cannot evaluate a/b as struct S",expr->ops);
    
    null(eval,dep,struct_node);
   }

  // Rem

  void operator () (Eval &eval,StepId dep,ExprNode::Rem *expr_ptr,TypeNode::Base *type_ptr)
   {
    if( type_ptr->isIntegral() )
      {
       auto step=eval.createStep(RemStep(ret,type_ptr->type,expr->ops),dep);
       
       eval.createStep(ExprStep(step.obj.getArg1(),type,from,expr_ptr->arg1),step.id);
       eval.createStep(ExprStep(step.obj.getArg2(),type,from,expr_ptr->arg2),step.id);
      }
    else
      {
       eval.error("Evaluation error #; : cannot evaluate a%b as text or ip",expr->ops);
       
       null(eval,dep,type_ptr);
      }
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Rem *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a%b as T *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Rem *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a%b as {T,...} *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Rem *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a%b as T[]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Rem *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate a%b as T[Len]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Rem *,StructNode *struct_node)
   {
    eval.error("Evaluation error #; : cannot evaluate a%b as struct S",expr->ops);
    
    null(eval,dep,struct_node);
   }

  // Ind

  void operator () (Eval &eval,StepId dep,ExprNode::Ind *)
   {
    auto step=eval.createStep(CastStep(ret,type,from,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }

  // Select

  void operator () (Eval &eval,StepId dep,ExprNode::Select *)
   {
    auto step=eval.createStep(CastStep(ret,type,from,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }

  // PtrSelect

  void operator () (Eval &eval,StepId dep,ExprNode::PtrSelect *)
   {
    auto step=eval.createStep(CastStep(ret,type,from,expr->ops),dep);
    
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }

  // Domain

  void operator () (Eval &eval,StepId dep,ExprNode::Domain *expr_ptr,TypeNode::Base *type_ptr)
   {
    if( type_ptr->isIntegral() )
      {
       TypeNode::Base::Type base_type=expr_ptr->type;
       
       auto step=eval.createStep(CastIntToIntStep(ret,base_type,type_ptr->type),dep);
       
       TypeNode *domain_type=eval.int_type[base_type];
      
       eval.createStep(ExprStep(step.obj.getArg(),domain_type,from,expr_ptr->arg),step.id);
      }
    else if( type_ptr->isText() )
      {
       TypeNode::Base::Type base_type=expr_ptr->type;
      
       auto step=eval.createStep(CastIntToTextStep(ret,base_type),dep);
     
       TypeNode *domain_type=eval.int_type[base_type];
      
       eval.createStep(ExprStep(step.obj.getArg(),domain_type,from,expr_ptr->arg),step.id);
      }
    else // IP
      {
       eval.error("Evaluation error #; : cannot evaluate I(a) as ip",expr->ops);
      
       null(eval,dep,type_ptr);
      }
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Domain *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate I(a) as T *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Domain *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate I(a) as {T,...} *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Domain *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate I(a) as T[]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Domain *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate I(a) as T[Len]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Domain *,StructNode *struct_node)
   {
    eval.error("Evaluation error #; : cannot evaluate I(a) as struct S",expr->ops);
    
    null(eval,dep,struct_node);
   }

  // Ref

  void operator () (Eval &eval,StepId dep,ExprNode::Ref *)
   {
    auto step=eval.createStep(CastStep(ret,type,from,expr->ops),dep);
   
    eval.createStep(ExprAddressStep(step.obj.ptr,from,expr),step.id);
   }

  // Null
  
  template <class T>
  void operator () (Eval &eval,StepId dep,ExprNode::Null *,T *type_ptr)
   {
    null(eval,dep,type_ptr);
   }

  template <class T>
  void null(Eval &eval,StepId dep,T *type_ptr)
   {
    NullStep(ret,type)(eval,dep,type_ptr);
   }

  // Number

  void operator () (Eval &eval,StepId dep,ExprNode::Number *expr_ptr,TypeNode::Base *type_ptr)
   {
    if( type_ptr->isIntegral() )
      {
       OpNumber(ret,type_ptr->type)(expr_ptr->number);
      }
    else if( type_ptr->isText() )
      {
       if( ret ) ret->set<Text>( expr_ptr->number.str );
      }
    else
      {
       eval.error("Evaluation error #; : cannot evaluate Number as ip",expr->ops);
      
       null(eval,dep,type_ptr);
      }
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Number *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate Number as T *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Number *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate Number as {T,...} *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Number *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate Number as T[]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Number *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate Number as T[Len]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::Number *,StructNode *struct_node)
   {
    eval.error("Evaluation error #; : cannot evaluate Number as struct S",expr->ops);
    
    null(eval,dep,struct_node);
   }

  // String

  void operator () (Eval &eval,StepId dep,ExprNode::String *expr_ptr,TypeNode::Base *type_ptr)
   {
    if( type_ptr->isText() )
      {
       if( ret ) ret->set<Text>( eval.string(expr_ptr->string) );
      }
    else
      {
       eval.error("Evaluation error #; : cannot evaluate String as integer or ip",expr->ops);
          
       null(eval,dep,type_ptr);
      } 
   }

  void operator () (Eval &eval,StepId dep,ExprNode::String *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate String as T *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::String *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate String as {T,...} *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::String *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate String as T[]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::String *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate String as T[Len]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::String *,StructNode *struct_node)
   {
    eval.error("Evaluation error #; : cannot evaluate String as struct S",expr->ops);
    
    null(eval,dep,struct_node);
   }

  // IP

  void operator () (Eval &eval,StepId dep,ExprNode::IP *expr_ptr,TypeNode::Base *type_ptr)
   {
    if( type_ptr->isText() )
      {
       if( ret ) ret->set<Text>( eval.castToText(ToIP(expr_ptr->lit)) );
      }
    else if( type_ptr->isIP() )
      {
       if( ret ) ret->set<IP>( ToIP(expr_ptr->lit) );
      }
    else
      {
       eval.error("Evaluation error #; : cannot evaluate IP as integer",expr->ops);
        
       null(eval,dep,type_ptr);
      }
   }

  void operator () (Eval &eval,StepId dep,ExprNode::IP *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate IP as T *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::IP *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate IP as {T,...} *",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::IP *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate IP as T[]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::IP *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate IP as T[Len]",expr->ops);
    
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::IP *,StructNode *struct_node)
   {
    eval.error("Evaluation error #; : cannot evaluate IP as struct S",expr->ops);
    
    null(eval,dep,struct_node);
   }

  // EmptyList

  void operator () (Eval &eval,StepId dep,ExprNode::EmptyList *,TypeNode::Base *type_ptr)
   {
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::EmptyList *,TypeNode::Ptr *type_ptr)
   {
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::EmptyList *,TypeNode::PolyPtr *type_ptr)
   {
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::EmptyList *,TypeNode::Array *type_ptr)
   {
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::EmptyList *,TypeNode::ArrayLen *type_ptr)
   {
    DefStep(ret,type,from)(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::EmptyList *,StructNode *struct_node)
   {
    DefStep(ret,type,from)(eval,dep,struct_node);
   }

  // NonameList

  void operator () (Eval &eval,StepId dep,ExprNode::NonameList *,TypeNode::Base *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate {a,...} as base type",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::NonameList *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate {a,...} as T *",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::NonameList *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate {a,...} as {T,...} *",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::NonameList *expr_ptr,TypeNode::Array *type_ptr)
   {
    if( ret )
      {
       PtrLen<Value> result=eval.block(expr_ptr->list.count);
       
       ret->set<Block>( result );
       
       TypeNode *type=type_ptr->type_node;
       
       Value *ptr=result.ptr;
       
       for(auto &node : expr_ptr->list )
         {
          eval.createStep(ExprStep(ptr,type,from,node.expr_node),dep);
          
          ++ptr;
         }
      }
    else
      {
       TypeNode *type=type_ptr->type_node;
       
       for(auto &node : expr_ptr->list )
         {
          eval.createStep(ExprStep(0,type,from,node.expr_node),dep);
         }
      }
   }

  void operator () (Eval &eval,StepId dep,ExprNode::NonameList *expr_ptr,TypeNode::ArrayLen *type_ptr)
   {
    ulen index=type_ptr->len_node.index;
   
    LenRec &rec=eval.len_list[index];
   
    rec.gate->createStep(ArrayLenStep(ret,type_ptr->type_node,from,rec,expr_ptr->list,expr->ops),dep);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::NonameList *expr_ptr,StructNode *struct_node)
   {
    if( expr_ptr->list.count>struct_node->field_list.count )
      {
       eval.error("Evaluation error #; : extra initializers",expr->ops);
      
       null(eval,dep,struct_node);
      
       return;
      }

    if( ret )
      {
       PtrLen<Value> result=eval.block(struct_node->field_list.count);
       
       ret->set<Block>( result );
       
       Value *ptr=result.ptr;
       
       auto cur=begin(expr_ptr->list);
       auto lim=end(expr_ptr->list);
       
       for(FieldNode &field : struct_node->field_list )
         {
          if( cur!=lim )
            {
             eval.createStep(ExprStep(ptr,field.type_node,from,(*cur).expr_node),dep);
            
             ++cur;
            }
          else
            {
             auto &rec=eval.field_list[field.index].take(eval,from);
            
             rec.gate->createStep(CopyStep(ptr,rec.value),dep);
            }
          
          ++ptr;
         }
      }
    else
      {
       auto cur=begin(expr_ptr->list);
       auto lim=end(expr_ptr->list);
      
       for(FieldNode &field : struct_node->field_list )
         {
          if( cur!=lim )
            {
             eval.createStep(ExprStep(0,field.type_node,from,(*cur).expr_node),dep);
           
             ++cur;
            }
          else
            {
             auto &rec=eval.field_list[field.index].take(eval,from);
           
             rec.gate->delay(dep);
            }
         }
      }
   }

  // NamedList

  void operator () (Eval &eval,StepId dep,ExprNode::NamedList *,TypeNode::Base *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate {.name=a,...} as base type",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::NamedList *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate {.name=a,...} as T *",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::NamedList *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate {.name=a,...} as {T,...} *",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::NamedList *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate {.name=a,...} as T[]",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::NamedList *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate {.name=a,...} as T[Len]",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::NamedList *expr_ptr,StructNode *struct_node)
   {
    if( ret )
      {
       ulen count=struct_node->field_list.count;
      
       PtrLen<Value> result=eval.block(count);
       
       ret->set<Block>( result );
       
       TempArray<bool,100> flags(count);
       
       Range(flags).set(false);
       
       ExprStructStep(result.ptr,flags.getPtr(),struct_node,from,expr)(eval,dep,expr_ptr);
      }
    else
      {
       ulen count=struct_node->field_list.count;
     
       TempArray<bool,100> flags(count);
      
       Range(flags).set(false);
      
       ExprStructStep(0,flags.getPtr(),struct_node,from,expr)(eval,dep,expr_ptr);
      }
   }

  // ApplyEmptyList

  void operator () (Eval &eval,StepId dep,ExprNode::ApplyEmptyList *,TypeNode::Base *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as base type",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::ApplyEmptyList *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as T *",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::ApplyEmptyList *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as {T,...} *",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::ApplyEmptyList *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as T[]",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::ApplyEmptyList *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as T[Len]",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::ApplyEmptyList *expr_ptr,StructNode *)
   {
    eval.createStep(ExprStep(ret,type,from,expr_ptr->arg),dep);
   }

  // ApplyNamedList

  void operator () (Eval &eval,StepId dep,ExprNode::ApplyNamedList *,TypeNode::Base *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as base type",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::ApplyNamedList *,TypeNode::Ptr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as T *",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::ApplyNamedList *,TypeNode::PolyPtr *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as {T,...} *",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::ApplyNamedList *,TypeNode::Array *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as T[]",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::ApplyNamedList *,TypeNode::ArrayLen *type_ptr)
   {
    eval.error("Evaluation error #; : cannot evaluate b {.name=a,...} as T[Len]",expr->ops);
     
    null(eval,dep,type_ptr);
   }

  void operator () (Eval &eval,StepId dep,ExprNode::ApplyNamedList *expr_ptr,StructNode *struct_node)
   {
    if( ret )
      {
       ulen count=struct_node->field_list.count;
      
       PtrLen<Value> result=eval.block(count);
       
       ret->set<Block>( result );
       
       PtrLen<bool> flags=eval.flags(count);
       
       Value *ptr=result.ptr;
       
       ExprStructStep(ptr,flags.ptr,struct_node,from,expr)(eval,dep,expr_ptr);
      }
    else
      {
       ulen count=struct_node->field_list.count;
     
       PtrLen<bool> flags=eval.flags(count);
       
       ExprStructStep(0,flags.ptr,struct_node,from,expr)(eval,dep,expr_ptr);
      }
   }
  
  // general
  
  template <class T>
  void operator () (Eval &eval,StepId dep,T *expr_ptr)
   {
    ElaborateAnyPtr(*this,eval,dep,expr_ptr,TypeAdapter(type).ptr);
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,expr->ptr);
   }
 };

void EvalContext::ArrayLenStep::operator () (Eval &eval,StepId dep)
 {
  if( rec.getLen()<list.count )
    {
     eval.error("Evaluation error #; : extra initializers",ops);
     
     NullArrayStep(ret,type,rec)(eval,dep);
    
     return;
    }
 
  if( ret )
    {
     PtrLen<Value> result=eval.block(rec);
     
     ret->set<Block>( result );
     
     if( +result )
       {
        Value *ptr=result.ptr;
       
        for(auto &node : list )
          {
           eval.createStep(ExprStep(ptr,type,from,node.expr_node),dep);
          
           ++ptr;
          }
       
        result+=list.count;
        
        if( +result )
          {
           auto step=eval.createStep(ExpandArray(result),dep);
         
           eval.createStep(DefStep(result.ptr,type,from),step.id);
          }
       }
    }
  else
    {
     for(auto &node : list )
       {
        eval.createStep(ExprStep(0,type,from,node.expr_node),dep);
       }
    
     if( rec.getLen()>list.count )
       {
        eval.createStep(DefStep(0,type,from),dep);
       }
    }
 }

void EvalContext::ExprSLenStep::operator () (Eval &eval,StepId dep,ExprNode::Domain *expr_ptr)
 {
  TypeNode::Base::Type base_type=expr_ptr->type;
  
  auto step=eval.createStep(CastIntToSLenStep(ret,base_type,expr->ops),dep);
  
  TypeNode *domain_type=eval.int_type[base_type];
 
  eval.createStep(ExprStep(step.obj.getArg(),domain_type,from,expr_ptr->arg),step.id);
 }

void EvalContext::ExprPtrOrIntStep::operator () (Eval &eval,StepId dep,ExprNode::Plus *expr_ptr)
 {
  TypeNode *type=eval.int_type[ret.type];
  
  eval.createStep(ExprStep(ret.getArg(),type,from,expr_ptr->arg),dep);
 }

void EvalContext::ExprPtrOrIntStep::operator () (Eval &eval,StepId dep,ExprNode::Minus *expr_ptr)
 {
  TypeNode *type=eval.int_type[ret.type];
  
  auto step=eval.createStep(MinusStep(ret.getArg(),ret.type),dep);
  
  eval.createStep(ExprStep(step.obj.getArg(),type,from,expr_ptr->arg),step.id);
 }

void EvalContext::ExprPtrOrIntStep::operator () (Eval &eval,StepId dep,ExprNode::Mul *expr_ptr)
 {
  TypeNode *type=eval.int_type[ret.type];
  
  auto step=eval.createStep(MulStep(ret.getArg(),ret.type),dep);
  
  eval.createStep(ExprStep(step.obj.getArg1(),type,from,expr_ptr->arg1),step.id);
  eval.createStep(ExprStep(step.obj.getArg2(),type,from,expr_ptr->arg2),step.id);
 }

void EvalContext::ExprPtrOrIntStep::operator () (Eval &eval,StepId dep,ExprNode::Div *expr_ptr)
 {
  TypeNode *type=eval.int_type[ret.type];
  
  auto step=eval.createStep(DivStep(ret.getArg(),ret.type,expr->ops),dep);
  
  eval.createStep(ExprStep(step.obj.getArg1(),type,from,expr_ptr->arg1),step.id);
  eval.createStep(ExprStep(step.obj.getArg2(),type,from,expr_ptr->arg2),step.id);
 }

void EvalContext::ExprPtrOrIntStep::operator () (Eval &eval,StepId dep,ExprNode::Rem *expr_ptr)
 {
  TypeNode *type=eval.int_type[ret.type];
  
  auto step=eval.createStep(RemStep(ret.getArg(),ret.type,expr->ops),dep);
  
  eval.createStep(ExprStep(step.obj.getArg1(),type,from,expr_ptr->arg1),step.id);
  eval.createStep(ExprStep(step.obj.getArg2(),type,from,expr_ptr->arg2),step.id);
 }

void EvalContext::ExprPtrOrIntStep::operator () (Eval &eval,StepId dep,ExprNode::Domain *expr_ptr)
 {
  TypeNode::Base::Type base_type=expr_ptr->type;
  
  auto step=eval.createStep(CastIntToIntStep(ret.getArg(),base_type,ret.type),dep);
  
  TypeNode *domain_type=eval.int_type[base_type];
 
  eval.createStep(ExprStep(step.obj.getArg(),domain_type,from,expr_ptr->arg),step.id);
 }

void EvalContext::ExprDuoStep::operator () (Eval &eval,StepId dep,ExprNode::Domain *expr_ptr)
 {
  TypeNode::Base::Type base_type=expr_ptr->type;
  
  auto step=eval.createStep(CastIntToDuoStep(ret,base_type,expr->ops),dep);
  
  TypeNode *domain_type=eval.int_type[base_type];
 
  eval.createStep(ExprStep(step.obj.getArg(),domain_type,from,expr_ptr->arg),step.id);
 }

void EvalContext::ExprStructStep::operator () (Eval &eval,StepId dep,ExprNode::NonameList *expr_ptr)
 {
  if( expr_ptr->list.count>struct_node->field_list.count )
    {
     eval.error("Evaluation error #; : extra initializers",expr->ops);
    
     null(eval,dep);
    
     return;
    }

  if( Value *ptr=result )
    {
     auto cur=begin(expr_ptr->list);
     auto lim=end(expr_ptr->list);
     
     for(FieldNode &field : struct_node->field_list )
       {
        if( cur!=lim )
          {
           if( !flags[field.field_index] )
             {
              eval.createStep(ExprStep(ptr,field.type_node,from,(*cur).expr_node),dep);
             } 
          
           ++cur;
          }
        else
          {
           if( !flags[field.field_index] )
             {
              auto &rec=eval.field_list[field.index].take(eval,from);
            
              rec.gate->createStep(CopyStep(ptr,rec.value),dep);
             }
          }
        
        ++ptr;
       }
    }
  else
    {
     auto cur=begin(expr_ptr->list);
     auto lim=end(expr_ptr->list);
     
     for(FieldNode &field : struct_node->field_list )
       {
        if( cur!=lim )
          {
           if( !flags[field.field_index] )
             {
              eval.createStep(ExprStep(0,field.type_node,from,(*cur).expr_node),dep);
             } 
          
           ++cur;
          }
        else
          {
           if( !flags[field.field_index] )
             {
              auto &rec=eval.field_list[field.index].take(eval,from);
            
              rec.gate->delay(dep);
             }
          }
       }
    }
 }

void EvalContext::ExprStructStep::apply(Eval &eval,StepId dep,NamedExprList &list)
 {
  if( Value *ptr=result )
    {
     for(NamedExprListNode &node : list )
       {
        if( FieldNode *field=struct_node->find(node.name) )
          {
           ulen index=field->field_index;
           
           if( !flags[index] )
             {
              eval.createStep(ExprStep(ptr+index,field->type_node,from,node.expr_node),dep);
             
              flags[index]=true;
             }
          }
       }
    }
  else
    {
     for(NamedExprListNode &node : list )
       {
        if( FieldNode *field=struct_node->find(node.name) )
          {
           ulen index=field->field_index;
           
           if( !flags[index] )
             {
              eval.createStep(ExprStep(0,field->type_node,from,node.expr_node),dep);
             
              flags[index]=true;
             }
          }
       }
    }
 }

struct EvalContext::CheckPtrBoundStep
 {
  ConstNode *node;
  Value &value;
  Ptr ptr;
  
  CheckPtrBoundStep(ConstNode *node_,Value &value_,Ptr ptr_) : node(node_),value(value_),ptr(ptr_) {}
  
  void operator () (Eval &eval)
   {
    auto result=eval.readPtr(value,ptr);
    
    if( !result )
      {
       eval.error("Evaluation error #; : out-of-bound pointer within",*node);
      }
   }
 };

struct EvalContext::LockStep
 {
  Value &value;
  TypeNode *type;
  ConstNode *node;
  
  LockStep(Value &value_,TypeNode *type_,ConstNode *node_) : value(value_),type(type_),node(node_) {}

  void lockPtr(Eval &eval)
   {
    Ptr ptr=value.get<Ptr>();
    
    ptr.locked=true;
    
    value.set<Ptr>( ptr );
    
    if( node ) 
      {
       if( !ptr || ptr.null ) return;
       
       ConstRec &rec=eval.getConst(ptr);
       
       rec.gate->createStep(CheckPtrBoundStep(node,rec.value,ptr));
      }
   }
  
  void lockBlock(Eval &eval,StepId dep,TypeNode *type)
   {
    if( NeedLock(type) )
      {
       PtrLen<Value> data=value.get<Block>().data;
      
       for(Value &val : data ) eval.createStep(LockStep(val,type,node),dep);
      }
   }
  
  void operator () (Eval &,StepId,TypeNode::Base *) {}
  
  void operator () (Eval &eval,StepId,TypeNode::Ptr *) { lockPtr(eval); }
  
  void operator () (Eval &eval,StepId,TypeNode::PolyPtr *) { lockPtr(eval); }
  
  void operator () (Eval &eval,StepId dep,TypeNode::Array *type_ptr) { lockBlock(eval,dep,type_ptr->type_node); }
  
  void operator () (Eval &eval,StepId dep,TypeNode::ArrayLen *type_ptr) { lockBlock(eval,dep,type_ptr->type_node); }
  
  void operator () (Eval &eval,StepId dep,StructNode *struct_node)
   {
    Value *ptr=value.get<Block>().data.ptr;
    
    for(FieldNode &field : struct_node->field_list )
      {
       eval.createStep(LockStep(*ptr,field.type_node,node),dep);
      
       ++ptr;
      }
   }
  
  void operator () (Eval &eval,StepId dep)
   {
    ElaborateAnyPtr(*this,eval,dep,TypeAdapter(type).ptr);
   }
 };

struct EvalContext::ExprLockStep
 {
  Value &ret;
  TypeNode *type;
  From from;
  ExprNode *expr;
  ConstNode *node;
  
  ExprLockStep(Value &ret_,TypeNode *type_,From from_,ExprNode *expr_,ConstNode *node_=0) 
   : ret(ret_),type(type_),from(from_),expr(expr_),node(node_) {}
  
  void operator () (Eval &eval,StepId dep)
   {
    auto step=eval.createStep(LockStep(ret,type,node),dep);
    
    eval.createStep(ExprStep(&ret,type,from,expr),step.id);
   }
 };

struct EvalContext::GateStep
 {
  AnyPtr<ConstNode,LenNode,FieldNode> ptr;
  
  template <class T>
  explicit GateStep(T *node) : ptr(node) {}
  
  void operator () () {}
  
  void final(Eval &eval)
   {
    eval.error("Cyclic dependencies, #; cannot be evaluated",ptr);
   }
 };

void EvalContext::CastField(Eval &eval,Value *ret,TypeNode *type,Ptr ptr,const Value &src,From from,const PosName &ops,StepId dep)
 {
  DecayCase decay(type,ptr.getType());
  
  if( decay.type )
    {
     auto step=eval.createStep(DecayStep(ret,ptr,decay.type,ops),dep);
    
     eval.createStep(CheckTypeStep(step.obj.ok,decay.type_set,decay.type),step.id);
    }
  else
    {
     eval.createStep(CastValueStep(ret,type,from,ptr,src,ops),dep);
    }
 }

void EvalContext::NullStruct(Eval &eval,Value *result,bool *flags,StructNode *struct_node,StepId dep)
 {
  if( result )
    {
     for(FieldNode &field : struct_node->field_list )
       {
        if( !*flags )
          {
           NullStep(result,field.type_node)(eval,dep);
          }
       
        ++result;
        ++flags;
       }
    }
 }

void EvalContext::DefStruct(Eval &eval,Value *result,bool *flags,StructNode *struct_node,From from,StepId dep)
 {
  if( result )
    {
     for(FieldNode &field : struct_node->field_list )
       {
        if( !*flags )
          {
           auto &rec=eval.field_list[field.index].take(eval,from);
          
           rec.gate->createStep(CopyStep(result,rec.value),dep);
          }
        
        ++result;
        ++flags;
       }
    }
  else
    {
     for(FieldNode &field : struct_node->field_list )
       {
        if( !*flags )
          {
           auto &rec=eval.field_list[field.index].take(eval,from);
        
           rec.gate->delay(dep);
          }
        
        ++flags;
       }
    }
 }

void EvalContext::ConstRec::prepare(Eval &eval,ConstNode &node)
 {
  this->node=&node;
  
  gate=eval.createGate(GateStep(&node),ExprLockStep(value,node.type_node,node.getFrom(),node.expr_node,&node));
 }

void EvalContext::LenRec::prepare(Eval &eval,TypeNode *type_ulen,LenNode &node)
 {
  this->node=&node;
  
  gate=eval.createGate(GateStep(&node),ExprStep(&value,type_ulen,node.getFrom(),node.expr_node));
 }

void EvalContext::FieldRec::Rec::prepare(Eval &eval,From from,FieldNode &field)
 {
  gate=eval.createGate(GateStep(&field),ExprLockStep(value,field.type_node,from,field.expr_node));
 }

void EvalContext::FieldRec::prepare(Eval &eval,From from,FieldNode &field)
 {
  if( field.expr_node->hasQNames() )
    {
     this->field=&field;
    }
  else
    {
     base.prepare(eval,from,field);
    }
 }

auto EvalContext::FieldRec::take(Eval &eval,From from) -> Rec &
 {
  if( field )
    {
     Algo::PrepareIns prepare(root,from);
     
     if( prepare.found )
       {
        return *prepare.found;
       }
     else
       {
        Rec *rec=eval.pool.create<Rec>();
        
        rec->prepare(eval,from,*field);
        
        prepare.complete(rec);
        
        return *rec;
       }
    }
  else
    {
     return base;
    }
 }

 // utilities

auto EvalContext::getConst(Ptr ptr) -> ConstRec & 
 {
  PtrNode *ptr_node=ptr.ptr_node;
  
  while( PtrNode *parent=ptr_node->parent ) ptr_node=parent;
  
  return const_list[ptr_node->index];
 }

auto EvalContext::readPtr(Value val,Ptr ptr) -> ReadPtrResult
 {
  ulen count=0;
  
  for(PtrNode *ptr_node=ptr.ptr_node; ptr_node ;ptr_node=ptr_node->parent) count++;
  
  TempArray<ulen_type,100> temp(count);
  
  {
   ulen *out=temp.getPtr();
  
   for(PtrNode *ptr_node=ptr.ptr_node; ptr_node ;ptr_node=ptr_node->parent) *(out++)=ptr_node->index;
  }
  
  for(count--; count-- ;)
    {
     PtrLen<Value> data=val.get<Block>().data;
     
     ulen_type index=temp[count];
     
     if( index<data.len )
       {
        val=data[index];
       }
     else
       {
        return Nothing;
       }
    }
  
  return val;
 }

struct EvalContext::NeedLockFunc
 {
  bool ret;
  
  NeedLockFunc() : ret(false) {}
  
  void operator () (unsigned,TypeNode::Base *) {}
  
  void operator () (unsigned,TypeNode::Ptr *) { ret=true; }
  
  void operator () (unsigned,TypeNode::PolyPtr *) { ret=true; }
  
  void operator () (unsigned level,TypeNode::Array *ptr) { ret=NeedLock(ptr->type_node,level-1); }
  
  void operator () (unsigned level,TypeNode::ArrayLen *ptr) { ret=NeedLock(ptr->type_node,level-1); }
  
  void operator () (unsigned level,StructNode *struct_node)
   { 
    for(FieldNode &field : struct_node->field_list )
      {
       if( NeedLock(field.type_node,level-1) )
         {
          ret=true;
         
          break;
         }
      }
   }
 };

bool EvalContext::NeedLock(TypeNode *type,unsigned level)
 {
  if( !level ) return true;
  
  NeedLockFunc func;
  
  ElaborateAnyPtr(func,level,TypeAdapter(type).ptr);
  
  return func.ret;
 }

struct EvalContext::NullBaseOp
 {
  Value ret;
  TypeNode::Base::Type type;
  
  explicit NullBaseOp(TypeNode::Base::Type type_) : type(type_) {}
  
  template <class T>
  void op()
   {
    ret.set<T>( T() );
   }
 };

Value EvalContext::NullBaseType(TypeNode::Base::Type type)
 {
  NullBaseOp op(type);
  
  UseBaseType(op);
  
  return op.ret;
 }

Ptr EvalContext::nullPtr(TypeNode *type)
 {
  PtrNode *ptr_node=pool.create<PtrNode>(type);
  
  return Ptr(ptr_node,true);
 }

void EvalContext::guardLen(ulen len)
 {
  ulen_type temp;
  
  if( CastOverflow(temp,len) )
    {
     Printf(Exception,"CCore::DDL2::EvalContext::guardLen(#;) : type overflow",len);
    }
 }

PtrLen<Value> EvalContext::block(LenRec &rec)
 {
  ulen len;
  
  if( CastOverflow(len,rec.getLen()) )
    {
     error("Evaluation error #; : length overflow",*rec.node);
    }
   
  return block(len); 
 }

template <class T>
Text EvalContext::castToText(const T &obj)
 {
  PrintCount<void> count;
  
  Putobj(count,obj);
  
  ulen len=count.getCount()+1;
  
  PrintBuf out(pool.createArray_raw<char>(len));
  
  Putobj(out,obj);
  
  return out.close();
 }

struct EvalContext::NotArrayFunc
 {
  bool ret;
  
  NotArrayFunc() : ret(true) {}
  
  template <class T>
  void operator () (T *) {}
  
  void operator () (TypeNode::Array *) { ret=false; }
  
  void operator () (TypeNode::ArrayLen *) { ret=false; }
 };

bool EvalContext::NotArray(TypeNode *type)
 {
  NotArrayFunc func;
  
  ElaborateAnyPtr(func,TypeAdapter(type).ptr);
  
  return func.ret;
 }

Ptr EvalContext::add(Ptr ptr,SLen delta,const PosName &ops)
 {
  if( !delta )
    {
     return ptr;
    }
  else
    {
     PtrNode *parent=ptr.getParent();
     
     if( !parent || NotArray(parent->type) )
       {
        error("Evaluation error #; : pointer does not point to array object",ops);
        
        return Ptr();
       }
    
     if( ptr.locked )
       {
        ptr.ptr_node=pool.create<PtrNode>(*ptr.ptr_node);
        ptr.locked=false;
       }
    
     if( ptr.add(delta) )
       {
        return ptr;
       }
     else
       {
        error("Evaluation error #; : pointer is out of representation",ops);
        
        return Ptr();
       }
    }
 }

bool EvalContext::SamePtr(PtrNode *a,PtrNode *b)
 {
  while( a )
    {
     if( b )
       {
        if( a->index!=b->index ) return false;
        
        a=a->parent;
        b=b->parent;
       }
     else
       {
        return false;
       }
    }
  
  return !b;
 }

SLen EvalContext::sub(Ptr a,Ptr b,const PosName &ops)
 {
  if( a.null )
    {
     if( b.null )
       {
        return SLen();
       }
     else
       {
        error("Evaluation error #; : null - non-null pointer subtraction",ops);
        
        return SLen();
       }
    }
  else
    {
     if( b.null )
       {
        error("Evaluation error #; : non-null - null pointer subtraction",ops);
       
        return SLen();
       }
     else
       {
        PtrNode *parent_a=a.getParent();
        PtrNode *parent_b=b.getParent();
        
        if( SamePtr(parent_a,parent_b) )
          {
           ulen_type index_a=a.getIndex();
           ulen_type index_b=b.getIndex();
           
           if( index_a==index_b )
             {
              return SLen();
             }
           else
             {
              if( !parent_a || NotArray(parent_a->type) )
                {
                 error("Evaluation error #; : pointers do not point to array objects",ops);
                
                 return SLen();
                }
            
              return SLen(index_a,index_b);
             }
          }
        else
          {
           error("Evaluation error #; : different parent objects",ops);
         
           return SLen();
          }
       }
    }
 }

Ptr EvalContext::ptrToField(Ptr ptr,FieldNode *field)
 {
  ulen_type index;
  
  if( CastOverflow(index,field->field_index) )
    {
     error("Evaluation error #; : field index overflow",*field);
    
     return Ptr();
    }
  
  return Ptr(pool.create<PtrNode>(ptr.ptr_node,index,field->type_node),false);
 }

Ptr EvalContext::ptrToField(Ptr ptr,const NameIdNode &name,const PosName &ops)
 {
  if( StructNode *struct_node=IsStructType(ptr.getType()) )
    {
     if( ptr.null )
       {
        error("Evaluation error #; : null pointer",ops);
      
        return Ptr();
       }
     else
       {
        if( FieldNode *field=struct_node->find(name) )
          {
           return ptrToField(ptr,field);
          }
        else
          {
           error("Evaluation error #; : no such field",ops);
        
           return Ptr();
          }
       }
    }
  else
    {
     error("Evaluation error #; : not a struct type",ops);
    
     return Ptr();
    }
 }

struct EvalContext::PtrTypeFunc
 {
  AnyPtr<TypeNode,TypeList> ret;
  
  PtrTypeFunc() {}
  
  template <class T>
  void operator () (T *) {}
  
  void operator () (TypeNode::Ptr *ptr) { ret=ptr->type_node; }
  
  void operator () (TypeNode::PolyPtr *ptr) { ret=ptr->type_list; }
 };

struct EvalContext::ArrayTypeFunc
 {
  TypeNode *ret;
  
  ArrayTypeFunc() : ret(0) {}
  
  template <class T>
  void operator () (T *) {}
  
  void operator () (TypeNode::Array *ptr) { ret=ptr->type_node; }
  
  void operator () (TypeNode::ArrayLen *ptr) { ret=ptr->type_node; }
 };

EvalContext::DecayCase::DecayCase(TypeNode *ptr_type_expected,TypeNode *array_type_expected)
 {
  ArrayTypeFunc func;
  
  ElaborateAnyPtr(func,TypeAdapter(array_type_expected).ptr);
  
  type=func.ret;
  
  if( type )
    {
     PtrTypeFunc func;
     
     ElaborateAnyPtr(func,TypeAdapter(ptr_type_expected).ptr);

     type_set=func.ret;
     
     if( !type_set ) type=0;
    }
 }

EvalContext::DecayAnyCase::DecayAnyCase(TypeNode *array_type_expected)
 {
  ArrayTypeFunc func;
  
  ElaborateAnyPtr(func,TypeAdapter(array_type_expected).ptr);
  
  type=func.ret;
 }

Ptr EvalContext::decay(Ptr ptr,TypeNode *type)
 {
  return Ptr(pool.create<PtrNode>(ptr.ptr_node,0,type),false);
 }

Ptr EvalContext::ptrTo(ConstNode *node)
 {
  ulen_type index;
  
  if( CastOverflow(index,node->index) )
    {
     error("Evaluation error #; : const index overflow",*node);
     
     return Ptr();
    }
  
  return Ptr(pool.create<PtrNode>(index,node->type_node),false);
 }

struct EvalContext::NotPtrFunc
 {
  bool ret;
  
  NotPtrFunc() : ret(true) {}
  
  template <class T>
  void operator () (T *) {}
  
  void operator () (TypeNode::Ptr *) { ret=false; }
  
  void operator () (TypeNode::PolyPtr *) { ret=false; }
 };

bool EvalContext::NotPtr(TypeNode *type)
 {
  NotPtrFunc func;

  ElaborateAnyPtr(func,TypeAdapter(type).ptr);
  
  return func.ret;
 }

Text EvalContext::string(const Token &token)
 {
  StrLen str=token.str.inner(1,1);
  
  if( token.tc==Token_SString ) return str;
  
  ulen len=DStringLen(str);
  
  auto ret=pool.createArray_raw<char>(len);

  DString(str,ret.ptr);
  
  return StrLen(ret);
 }

IP EvalContext::ToIP(const LitIP &lit)
 {
  uint8 a1=StrToInt<imp_uint8>(lit.token1).value;
  uint8 a2=StrToInt<imp_uint8>(lit.token2).value;
  uint8 a3=StrToInt<imp_uint8>(lit.token3).value;
  uint8 a4=StrToInt<imp_uint8>(lit.token4).value;
  
  return IP(a1,a2,a3,a4);
 }

 // main

bool EvalContext::process(Eval &eval,BodyNode *body_node,EvalResult &result)
 {
  map=body_node->map;
  
  // const
  {
   ulen index=0;
   
   for(ConstNode &node : body_node->const_list ) node.index=index++;
   
   {
    DynArray<ConstRec> temp(index);
    
    Swap(const_list,temp);
   }
   
   for(ConstNode &node : body_node->const_list ) const_list[node.index].prepare(eval,node);
  }
  
  // fields
  {
   ulen index=0;
   ulen struct_index=0;
   
   for(StructNode &node : body_node->struct_list )
     {
      node.index=struct_index++;
     
      ulen field_index=0;
     
      for(FieldNode &field : node.field_list )
        {
         field.index=index++;
         field.field_index=field_index++;
        }
     }
   
   {
    DynArray<FieldRec> temp(index);
    
    Swap(field_list,temp);
   }
   
   for(StructNode &node : body_node->struct_list )
     {
      From from=node.getFieldFrom();
     
      for(FieldNode &field : node.field_list )
        {
         field_list[field.index].prepare(eval,from,field);
        }
     }
  }
  
  // len
  {
   ulen index=0;
   
   for(LenNode &node : body_node->len_list ) node.index=index++;
   
   {
    DynArray<LenRec> temp(index);
    
    Swap(len_list,temp);
   }
   
   TypeNode *type_ulen=int_type[TypeNode::Base::Type_ulen];
   
   for(LenNode &node : body_node->len_list ) len_list[node.index].prepare(eval,type_ulen,node);
  }
  
  eval.run();
  
  if( !error )
    {
     DynArray<ConstResult> const_table(const_list.getLen());
     DynArray<LenResult> len_table(len_list.getLen());
     
     for(ulen i=0,len=const_table.getLen(); i<len ;i++) 
       const_table[i].set(const_list[i].node,const_list[i].value);
     
     for(ulen i=0,len=len_table.getLen(); i<len ;i++) 
       len_table[i].set(len_list[i].node,len_list[i].getLen());
     
     Swap(result.const_table,const_table);
     Swap(result.len_table,len_table);
    
     return true;
    }
  
  return false;
 }

EvalContext::EvalContext(ErrorMsg &error_,ElementPool &pool_)
 : error(error_),
   pool(pool_)
 {
  for(int t=TypeNode::Base::TypeIntMin; t<=TypeNode::Base::TypeIntMax ;t++)
    {
     TypeNode *type=pool.create<TypeNode>();
     
     type->init_base(pool_,TypeNode::Base::Type(t));
     
     int_type[t]=type;
    }
 }

EvalContext::~EvalContext()
 {
 }

bool EvalContext::Process(ErrorMsg &error,ElementPool &pool,BodyNode *body_node,EvalResult &result)
 {
  Eval eval(error,pool);
  
  return eval.process(eval,body_node,result);
 }

} // namespace DDL2
} // namespace CCore

