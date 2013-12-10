/* DDL2Eval.h */
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

#ifndef CCore_inc_ddl2_DDL2Eval_h
#define CCore_inc_ddl2_DDL2Eval_h

#include <CCore/inc/StepEval.h>

#include <CCore/inc/ddl2/DDL2Semantic.h>
#include <CCore/inc/ddl2/DDL2Value.h>

namespace CCore {
namespace DDL2 {

/* functions */

template <class T,class ... SS> 
void ExtIntType(T &obj,TypeNode::Base::Type type,SS && ... ss)
 {
  switch( type )
    {
     case TypeNode::Base::Type_sint   : obj.template op<imp_sint>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_uint   : obj.template op<imp_uint>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_ulen   : obj.template op<imp_ulen>( std::forward<SS>(ss)... ); break;
   
     case TypeNode::Base::Type_sint8  : obj.template op<imp_sint8>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_uint8  : obj.template op<imp_uint8>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_sint16 : obj.template op<imp_sint16>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_uint16 : obj.template op<imp_uint16>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_sint32 : obj.template op<imp_sint32>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_uint32 : obj.template op<imp_uint32>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_sint64 : obj.template op<imp_sint64>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_uint64 : obj.template op<imp_uint64>( std::forward<SS>(ss)... ); break;
    }
 }

template <class T,class ... SS> 
void ExtBaseType(T &obj,TypeNode::Base::Type type,SS && ... ss)
 {
  switch( type )
    {
     case TypeNode::Base::Type_sint   : obj.template op<imp_sint>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_uint   : obj.template op<imp_uint>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_ulen   : obj.template op<imp_ulen>( std::forward<SS>(ss)... ); break;
   
     case TypeNode::Base::Type_sint8  : obj.template op<imp_sint8>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_uint8  : obj.template op<imp_uint8>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_sint16 : obj.template op<imp_sint16>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_uint16 : obj.template op<imp_uint16>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_sint32 : obj.template op<imp_sint32>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_uint32 : obj.template op<imp_uint32>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_sint64 : obj.template op<imp_sint64>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_uint64 : obj.template op<imp_uint64>( std::forward<SS>(ss)... ); break;
     
     case TypeNode::Base::Type_text   : obj.template op<Text>( std::forward<SS>(ss)... ); break;
     case TypeNode::Base::Type_ip     : obj.template op<IP>( std::forward<SS>(ss)... ); break;
    }
 }

template <class T,class ... SS> 
void UseIntType(T &obj,SS && ... ss)
 {
  ExtIntType(obj,obj.type, std::forward<SS>(ss)... );
 }

template <class T,class ... SS> 
void UseBaseType(T &obj,SS && ... ss)
 {
  ExtBaseType(obj,obj.type, std::forward<SS>(ss)... );
 }

/* classes */

struct TypeAdapter;

struct ConstResult;

struct LenResult;

struct EvalResult;

struct PrintName;

struct PrintType;

struct PrintValue;

class EvalContext;

/* struct TypeAdapter */

struct TypeAdapter
 {
  using AnyPtrType = AnyPtr<TypeNode::Base,TypeNode::Ptr,TypeNode::PolyPtr,TypeNode::Array,TypeNode::ArrayLen,StructNode> ;
  
  AnyPtrType ptr;
  
  template <class P>
  void operator () (P *type_ptr)
   { 
    ptr=type_ptr; 
   }
  
  void operator () (AliasNode *alias_node)
   { 
    alias_node->result_type->ptr.apply( FunctorRef(*this) );
   }
  
  void operator () (StructNode *struct_node)
   { 
    ptr=struct_node; 
   }
  
  void operator () (TypeNode::Ref *type_ptr)
   {
    type_ptr->ptr.apply( FunctorRef(*this) );
   }
  
  void operator () (TypeNode::Struct *type_ptr)
   {
    ptr=type_ptr->struct_node;
   }
  
  explicit TypeAdapter(TypeNode *type)
   {
    type->ptr.apply( FunctorRef(*this) );
   }
 
  template <class Ret,class FuncInit> 
  static Ret Binary(TypeNode *a,TypeNode *b,FuncInit func_init)
   {
    return AnyPtrType::Binary<Ret>(TypeAdapter(a).ptr,TypeAdapter(b).ptr,func_init);
   }
 };

/* IsStructType() */

inline StructNode * IsStructType(TypeNode *type) { return TypeAdapter(type).ptr.castPtr<StructNode>(); }

/* struct ConstResult */

struct ConstResult : NoThrowFlagsBase
 {
  TypeNode *type;
  ConstNode *node;
  Value value;
  
  void set(ConstNode *node_,const Value &value_)
   {
    type=node_->type_node;
    node=node_;
    value=value_;
   }

  struct PrintOptType
   {
    EvalResult &result;
    
    PrintOptType(EvalResult &result_) : result(result_) {}
   };
  
  template <class P>
  void print(P &out,PrintOptType opt) const;
 };

/* struct LenResult */

struct LenResult : NoThrowFlagsBase
 {
  LenNode *node;
  ulen_type value;
  
  void set(LenNode *node_,ulen_type value_)
   {
    node=node_;
    value=value_;
   }
 
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#; = #;",*node,value);
   }
 };

/* struct EvalResult */

struct EvalResult : NoCopy
 {
  DynArray<ConstResult> const_table;
  DynArray<LenResult> len_table;
  
  EvalResult() {}
  
  void erase()
   {
    const_table.erase();
    len_table.erase();
   }
  
  ulen_type getLen(const LenNode &node) const { return len_table[node.index].value; }
 };

/* struct PrintName */

struct PrintName
 {
  ScopeNode *scope;
  ulen depth;
  
  StrLen name;
  
  template <class Node>
  explicit PrintName(Node *node) : scope(node->parent),depth(node->depth),name(node->name.getStr()) {}
  
  template <class P>
  void print(P &out) const
   {
    TempArray<ScopeNode *,25> temp(depth);
    
    ScopeNode *node=scope;
    
    for(ScopeNode * &ptr : temp ) 
      {
       ptr=node;
       node=node->parent;
      }
    
    for(ScopeNode * ptr : RangeReverse(temp) )
      {
       Putch(out,'#');
       Putobj(out,ptr->name.getStr());
      }
    
    Putch(out,'#');
    Putobj(out,name);
   }
 };

/* struct PrintType */

struct PrintType
 {
  EvalResult &result;
  TypeNode *type;
  ulen cap;
  
  PrintType(EvalResult &result_,TypeNode *type_,ulen cap_=100) : result(result_),type(type_),cap(cap_) {}
  
  template <class P>
  void operator () (P &out,DDL2::TypeNode::Base *type_ptr) const
   {
    Putobj(out,type_ptr->type);
   }
  
  template <class P>
  void operator () (P &out,TypeNode::Ptr *type_ptr) const
   {
    if( cap )
      {
       Printf(out,"#; *",PrintType(result,type_ptr->type_node,cap-1));
      } 
    else
      {
       Putobj(out,"... *");
      } 
   }
  
  template <class P>
  void operator () (P &out,TypeNode::PolyPtr *type_ptr) const
   {
    if( cap )
      {
       Putobj(out,"{ ");
      
       bool flag=false;
      
       for(auto &node : *type_ptr->type_list )
         {
          if( flag ) Putobj(out," , "); 
         
          Putobj(out,PrintType(result,node.type_node,cap-1));
         
          flag=true;
         }
      
       Putobj(out," } *");
      }
    else
      {
       Putobj(out,"{ ... } *");
      }
   }
  
  template <class P>
  void operator () (P &out,TypeNode::Array *type_ptr) const
   {
    if( cap )
      {
       Printf(out,"#; []",PrintType(result,type_ptr->type_node,cap-1));
      }
    else
      {
       Printf(out,"... []");
      }
   }
  
  template <class P>
  void operator () (P &out,TypeNode::ArrayLen *type_ptr) const
   {
    auto len=result.getLen(type_ptr->len_node);
    
    if( cap )
      {
       Printf(out,"#; [#;]",PrintType(result,type_ptr->type_node,cap-1),len);
      }
    else
      {
       Printf(out,"... [#;]",len);
      }
   }
  
  template <class P>
  void operator () (P &out,StructNode *struct_node) const
   {
    Printf(out,"struct #;",PrintName(struct_node));
   }
  
  template <class P>
  void print(P &out) const
   {
    ElaborateAnyPtr(*this,out,TypeAdapter(type).ptr);
   }
 };

/* struct PrintValue */

struct PrintValue
 {
  EvalResult &result;
  TypeNode *type;
  Value value;
  ulen off;
  
  PrintValue(EvalResult &result_,TypeNode *type_,const Value &value_,ulen off_=0) 
   : result(result_),type(type_),value(value_),off(off_) {}
  
  template <class T,class P>
  void op(P &out,TypeNode::Base::Type type) const
   {
    Printf(out,"#;(#;) #;",RepeatChar(off,' '),type,value.get<T>());
   }
  
  template <class P>
  void operator () (P &out,TypeNode::Base *type_ptr) const
   {
    ExtBaseType(*this,type_ptr->type,out,type_ptr->type);
   }
  
  template <class P>
  static void PrintPtr(P &out,EvalResult &result,PtrNode *ptr_node,ulen cap=100)
   {
    if( PtrNode *parent=ptr_node->parent )
      {
       if( cap )
         PrintPtr(out,result,parent,cap-1);
       else
         Putobj(out,"...");
       
       if( StructNode *struct_node=IsStructType(parent->type) )
         {
          auto cur=begin(struct_node->field_list);
          
          for(auto cnt=ptr_node->index; cnt-- ;) ++cur;
         
          Printf(out,".#;",(*cur).name.name.str);
         }
       else
         {
          Printf(out,"[#;]",ptr_node->index);
         }
      }
    else
      {
       Printf(out,"#;",PrintName(result.const_table[ptr_node->index].node));
      }
   }
  
  template <class P>
  void printPtr(P &out) const
   {
    Ptr ptr=value.get<Ptr>();
    
    Putobj(out,RepeatChar(off,' '));
    
    if( !ptr )
      {
       Printf(out,"(??? *) null");
      }
    else if( ptr.null )
      {
       Printf(out,"(#; *) null",PrintType(result,ptr.getType()));
      }
    else
      {
       Putobj(out,"-> ");
       
       PrintPtr(out,result,ptr.ptr_node);
      }
   }
  
  template <class P>
  void operator () (P &out,TypeNode::Ptr *) const
   {
    printPtr(out);
   }
  
  template <class P>
  void operator () (P &out,TypeNode::PolyPtr *) const
   {
    printPtr(out);
   }
  
  template <class P>
  void printArray(P &out,TypeNode *type) const
   {
    PtrLen<Value> data=value.get<Block>().data;
    
    if( +data )
      {
       if( off )
         {
          if( off>200 )
            {
             Putobj(out,RepeatChar(off,' '),"{ ... }");
             
             return;
            }
         
          Putobj(out,RepeatChar(off,' ')," {\n");
       
          Putobj(out,PrintValue(result,type,*data,off+2));
         
          for(++data; +data ;++data)
            {
             Putobj(out,",\n",PrintValue(result,type,*data,off+2));
            }
        
          Putch(out,'\n');
          Putobj(out,RepeatChar(off,' ')," }");
         }
       else
         {
          Putobj(out,"\n {\n");
        
          Putobj(out,PrintValue(result,type,*data,off+2));
          
          for(++data; +data ;++data)
            {
             Putobj(out,",\n",PrintValue(result,type,*data,off+2));
            }
         
          Putobj(out,"\n }");
         }
      }
    else
      {
       Putobj(out,RepeatChar(off,' '),"{ }");
      }
   }
  
  template <class P>
  void operator () (P &out,TypeNode::Array *type_ptr) const
   {
    printArray(out,type_ptr->type_node);
   }
  
  template <class P>
  void operator () (P &out,TypeNode::ArrayLen *type_ptr) const
   {
    printArray(out,type_ptr->type_node);
   }
  
  template <class P>
  void operator () (P &out,StructNode *struct_node) const
   {
    PtrLen<Value> data=value.get<Block>().data;
    
    if( +data )
      {
       if( off )
         {
          if( off>200 )
            {
             Putobj(out,RepeatChar(off,' '),"{ ... }");
             
             return;
            }
         
          Putobj(out,RepeatChar(off,' ')," {\n");
          
          auto cur=begin(struct_node->field_list);
       
          Putobj(out,PrintValue(result,(*cur).type_node,*data,off+2));
          
          ++cur;
         
          for(++data; +data ;++data)
            {
             Putobj(out,",\n",PrintValue(result,(*cur).type_node,*data,off+2));
             
             ++cur;
            }
        
          Putch(out,'\n');
          Putobj(out,RepeatChar(off,' ')," }");
         }
       else
         {
          Putobj(out,"\n {\n");
          
          auto cur=begin(struct_node->field_list);
        
          Putobj(out,PrintValue(result,(*cur).type_node,*data,off+2));
          
          ++cur;
          
          for(++data; +data ;++data)
            {
             Putobj(out,",\n",PrintValue(result,(*cur).type_node,*data,off+2));
             
             ++cur;
            }
         
          Putobj(out,"\n }");
         }
      }
    else
      {
       Putobj(out,RepeatChar(off,' '),"{ }");
      }
   }
  
  template <class P>
  void print(P &out) const
   {
    ElaborateAnyPtr(*this,out,TypeAdapter(type).ptr);
   }
 };

template <class P>
void ConstResult::print(P &out,PrintOptType opt) const
 {
  Printf(out,"#; #; = #;",PrintType(opt.result,type),PrintName(node),PrintValue(opt.result,type,value));
 }

/* class EvalContext */

class EvalContext : NoCopy
 {
   ErrorMsg &error;
   ElementPool &pool;
   NameLinkMap *map;
   
   TypeNode * int_type[TypeNode::Base::Type::TypeIntMax+1];
   
  private: 
   
   using Eval = StepEval<EvalContext> ;
   
   struct ConstRec;
   struct LenRec;
   struct FieldRec;
   
   struct CmpLenStep;
   struct CmpArrayLenStep;
   struct CmpListStep;
   struct JoinLoopStep;
   struct JoinStep;
   struct SortStep;
   struct CmpTypeStep;
   
   struct CmpToOkStep;
   struct CheckTypeListStep;
   struct CheckTypeStep;
   
   struct MinusStep;
   struct AddStep;
   struct AddTextStep;
   struct MulStep;
   struct DivStep;
   struct RemStep;
   
   struct ExpandArray;
   struct NullArrayStep;
   struct NullStep;
   
   struct CopyStep;
   
   struct DefArrayStep;
   struct DefStep;
   
   struct CastIntToIntStep;
   struct CastIntToTextStep;
   
   struct ArrayLenStep;
   
   struct PtrOrSLen;
   struct PtrOrInt;
   
   struct Ops;
   struct OpsSLen;
   struct Trio;
   
   struct CompleteAddPtrStep;
   struct AddPtrStep;
   struct AddAnyPtrStep;
   struct CompleteSubStep;
   struct SubStep;
   struct SubPtrStep;
   struct SubAnyPtrStep;
   
   struct OpNumber;
   
   struct LValue;
   
   struct CompleteReadStep;
   struct ReadPtrStep;
   struct CastSameTypeStep;
   struct CastValueStep;
   struct DecayStep;
   struct CastStep;
   
   struct CompleteCheckPtrStep;
   struct CheckPtrStep;
   
   struct SelectFieldStep;
   
   struct CastValueToPtrStep;
   struct CastToPtrStep;
   
   struct CastToSLenOp;
   struct CastValueToSLenStep;
   struct CastToSLenStep;
   
   struct CastValueToPtrOrSLenStep;
   struct CastToPtrOrSLenStep;
   
   struct SLenMinusStep;
   struct SLenAddStep;
   struct SLenMulStep;
   struct SLenDivStep;
   struct SLenRemStep;
   struct SLenSubStep;
   struct CastIntToSLenStep;
   
   template <class T> struct SetPtrStep;
   struct SetSLenStep;
   
   struct PtrOrSLenAddStep;
   struct PtrOrSLenSubStep;
   
   struct CastValueToPtrOrIntStep;
   struct CastToPtrOrIntStep;
   
   struct PtrOrIntAddStep;
   struct PtrOrIntSubStep;
   
   struct TrioAddStep;
   struct TrioSubStep;
   
   struct CastValueToTrioStep;
   struct CastToTrioStep;
   
   struct DuoMinusStep;
   struct DuoAddStep;
   struct DuoMulStep;
   struct DuoDivStep;
   struct DuoRemStep;
   struct CastIntToDuoStep;
   
   struct DuoSubStep;
   
   struct CastValueToDuoStep;
   struct CastToDuoStep;
   
   struct CastValueToStructStep;
   struct CastToStructStep;
   
   struct ExprAddressStep;
   
   struct ExprSLenStep;
   struct ExprPtrOrSLenStep;
   struct ExprPtrOrIntStep;
   struct ExprDuoStep;
   struct ExprTrioStep;
   struct ExprPtrStep;
   
   struct ExprStructStep;
   
   struct ExprStep;
   struct CheckPtrBoundStep;
   struct LockStep;
   struct ExprLockStep;
   struct GateStep;
   
   static void CastField(Eval &eval,Value *ret,TypeNode *type,Ptr ptr,const Value &src,From from,const PosName &ops,StepId dep);
   
   static void NullStruct(Eval &eval,Value *result,bool *flags,StructNode *struct_node,StepId dep);
   
   static void DefStruct(Eval &eval,Value *result,bool *flags,StructNode *struct_node,From from,StepId dep);
   
  private: 
   
   DynArray<ConstRec> const_list; 
   DynArray<LenRec> len_list; 
   DynArray<FieldRec> field_list;
   
  private: 
   
   // utilities
   
   static bool OR(bool a,bool b) { return a || b ; }
   
   ConstRec & getConst(Ptr ptr);
   
   struct ReadPtrResult
    {
     Value value;
     bool ok;
     
     ReadPtrResult(NothingType) : ok(false) {}
     
     ReadPtrResult(const Value &value_) : value(value_),ok(true) {}
     
     bool operator ! () const { return !ok; }
    };
   
   ReadPtrResult readPtr(Value val,Ptr ptr);

   struct NeedLockFunc;
   
   static bool NeedLock(TypeNode *type,unsigned level=100);
   
   Text add(Text arg1,Text arg2) { return pool.cat(arg1.str,arg2.str); }
   
   struct NullBaseOp;
   
   static Value NullBaseType(TypeNode::Base::Type type);
   
   Ptr nullPtr(TypeNode *type);
   
   void guardLen(ulen len);
   
   PtrLen<Value> block(ulen len) { guardLen(len); return pool.createArray<Value>(len); }
   
   PtrLen<bool> flags(ulen len) { return pool.createArray<bool>(len); }
   
   PtrLen<Value> block(LenRec &rec);

   template <class T>
   Text castToText(const T &obj);
   
   struct NotArrayFunc;
   
   static bool NotArray(TypeNode *type);
   
   Ptr add(Ptr ptr,SLen delta,const PosName &ops); // ptr is not null
   
   static bool SamePtr(PtrNode *a,PtrNode *b);
   
   SLen sub(Ptr a,Ptr b,const PosName &ops); // a,b are not null
   
   Ptr ptrToField(Ptr ptr,FieldNode *field);
   
   Ptr ptrToField(Ptr ptr,const NameIdNode &name,const PosName &ops); // ptr is not null
   
   struct PtrTypeFunc;
   
   struct ArrayTypeFunc;
   
   struct DecayCase
    {
     AnyPtr<TypeNode,TypeList> type_set;
     TypeNode *type;
     
     DecayCase(TypeNode *ptr_type_expected,TypeNode *array_type_expected);
    };
   
   struct DecayAnyCase
    {
     TypeNode *type;
     
     explicit DecayAnyCase(TypeNode *array_type_expected);
    };
   
   Ptr decay(Ptr ptr,TypeNode *type);
   
   ConstNode * doLink(From from,ExprNode::Ref *expr_ptr) { return map->doLink(from,expr_ptr); }
   
   Ptr ptrTo(ConstNode *node);
   
   struct NotPtrFunc;
   
   static bool NotPtr(TypeNode *type);
   
   Text string(const Token &token);
   
   static IP ToIP(const LitIP &lit);
   
   // main
   
   bool process(Eval &eval,BodyNode *body_node,EvalResult &result);

  public:
  
   EvalContext(ErrorMsg &error,ElementPool &pool);
   
   ~EvalContext();
   
   DefaultHeapAlloc getAlloc() { return DefaultHeapAlloc(); }
   
   static bool Process(ErrorMsg &error,ElementPool &pool,BodyNode *body_node,EvalResult &result);
 };

} // namespace DDL2
} // namespace CCore

#endif

