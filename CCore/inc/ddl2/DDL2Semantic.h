/* DDL2Semantic.h */
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

#ifndef CCore_inc_ddl2_DDL2Semantic_h
#define CCore_inc_ddl2_DDL2Semantic_h

#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/AnyPtr.h>
#include <CCore/inc/Cmp.h>

#include <CCore/inc/ddl2/DDL2Tools.h>

namespace CCore {
namespace DDL2 {

/* types */

typedef ulen NameId;

/* classes */

class Context;

class ExtContext;

struct NameIdNode;

struct NameNode;

struct NameNodeList;

struct NameRefNode;

struct ScopeNode;

struct From;

struct LenNode;

struct TypeListNode;

struct TypeNode;

struct LitNull;

struct LitString;

struct LitIP;

struct ExprListNode;

struct NamedExprListNode;

struct ExprNode;

struct DomainRefNode;

struct RefListNode;

template <class T> struct NodeBase;

struct AliasNode;

struct ConstNode;

struct FieldNode;

class FieldMap;

struct StructNode;

class NameLinkMap;

class LinkContext;

struct BodyNode;

struct SBodyNode;

/* class Context */

class Context : NoCopy
 {
   const ulen mem_cap;
  
   CountList<NameIdNode> name_id_list;
   BaseList<DomainRefNode> domain_ref_list;
  
  private:
  
   NameId generateIds();
   
   struct MapScopeRec;
   struct MapScopeExpand;
   
   void mapScopes(BodyNode *body_node,NameId max_id,BaseList<NameLinkMap> &map_list);
   
   template <class Node>
   bool fillMap(NameLinkMap *map,NameId max_id,Node &node);
   
   bool buildMaps(BodyNode *body_node,NameId max_id);
   
   bool setAliasTypes(AliasNode &node,ulen mark);
   
   struct PickNextAlias;

   static AliasNode * NextAlias(AliasNode *node);
   
   bool setAliasTypes(BodyNode *body_node);
   
   struct AliasRec;
   struct AliasExpand;
  
   bool checkLoop1(AliasNode &node,ulen mark);
   
   bool checkLoop1(BodyNode *body_node);
   
   struct StructRec;
   struct StructExpand;
   
   bool checkLoop2(StructNode &node,ulen mark);
   
   bool checkLoop2(BodyNode *body_node);
   
   bool setDomainTypes();
   
  public:
  
   ErrorMsg error;
   ElementPool pool;
   
   explicit Context(PrintBase &msg,ulen mem_cap=MaxULen);
  
   ~Context();
  
   // methods
  
   void reset();
  
   // complete 
   
   void add(NameIdNode *name_id_node);
   
   void add(DomainRefNode *domain_ref_node);
   
   BodyNode * complete(BodyNode *body_node);
 };

/* class ExtContext */

class ExtContext
 {
   Context *ctx;
   FileId *file_id;
   
  public: 
  
   ExtContext(Context *ctx_,FileId *file_id_) : ctx(ctx_),file_id(file_id_) {}
   
   // methods
   
   FileId * getFileId() { return file_id; }
   
   template <class T,class ... SS>
   T * create(SS && ... ss)
    {
     return ctx->pool.create<T>( std::forward<SS>(ss)... );
    }
   
   void add(NameIdNode *name_id_node);
   
   void add(DomainRefNode *domain_ref_node);
 };

/* struct NameIdNode */

struct NameIdNode : NoCopy
 {
  NameIdNode *prev;
  
  PosName name;
  NameId name_id;
  
  void init(ExtContext ctx,const Token &token)
   {
    name.init(ctx.getFileId(),token);
   
    name_id=0;
   
    ctx.add(this); 
   }
  
  void init_qname(ExtContext ctx,const Token &token)
   {
    name.init_qname(ctx.getFileId(),token);
   
    name_id=0;
   
    ctx.add(this); 
   }
  
  StrLen getStr() const { return name.str; }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Putobj(out,name);
   }
 };

inline void Context::add(NameIdNode *name_id_node) 
 { 
  name_id_list.add(name_id_node); 
 }

inline void ExtContext::add(NameIdNode *name_id_node) 
 { 
  ctx->add(name_id_node); 
 }

/* struct NameNode */

struct NameNode : NoCopy
 {
  NameNode *next;
  
  NameIdNode name;
  bool qname_flag;
  
  void init(ExtContext ctx,const Token &token)
   {
    name.init(ctx,token);
    
    qname_flag=false;
   }
  
  void init_qname(ExtContext ctx,const Token &token)
   {
    name.init_qname(ctx,token);
    
    qname_flag=true;
   }
 };

/* struct NameNodeList */

struct NameNodeList : NoCopy
 {
  ForwardList<NameNode> list;
  bool qname_flag;
  
  void init(NameNode *name_node)
   {
    list.init(name_node);
    
    qname_flag=false;
   }
  
  void init_qname(NameNode *name_node)
   {
    list.init(name_node);
    
    qname_flag=true;
   }
  
  void add(NameNode *name_node)
   {
    list.add(name_node);
   }
  
  void add_qname(NameNode *name_node)
   {
    list.add(name_node);
    
    qname_flag=true;
   }

  const PosName & posName() const { return list.last->name.name; }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Putobj(out,posName());
   }
 };

/* struct NameRefNode */

struct NameRefNode : NoCopy
 {
  enum Type
   {
    Type_rel,
    Type_abs,
    Type_this,
    Type_dots
   };
  
  Type type;
  NameNodeList *name_list;
  ulen dots_count;
  
  void init(Type type_,NameNodeList *name_list_)
   {
    type=type_;
    name_list=name_list_;
    dots_count=0;
   }
  
  void init_dots(const Token &dots,NameNodeList *name_list_)
   {
    type=Type_dots;
    name_list=name_list_;
    dots_count=dots.str.len;
   }
  
  const PosName & posName() const { return name_list->posName(); }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Putobj(out,posName());
   }
 };

/* struct ScopeNode */

struct ScopeNode : NoCopy
 {
  ScopeNode *prev;
  
  ScopeNode *parent;
  
  NameIdNode name;
  BodyNode *body;
  
  void init(ExtContext ctx,const Token &token,BodyNode *body);
  
  void setParent(ScopeNode *parent_)
   {
    parent=parent_;
   }
 };

/* struct From */

struct From : CmpComparable<From>
 {
  ScopeNode *scope;
  ulen depth;
  
  From() : scope(0),depth(0) {}
  
  From(ScopeNode *scope_,ulen depth_) : scope(scope_),depth(depth_) {}
  
  bool back()
   {
    if( depth )
      {
       depth--;
       scope=scope->parent;
      
       return true;
      }
   
    return false;
   }
  
  CmpResult objCmp(From obj) const
   {
    if( CmpResult ret=Cmp(depth,obj.depth) ) return ret;
    
    for(ScopeNode *a=scope,*b=obj.scope; a ;a=a->prev,b=b->prev)
      {
       if( CmpResult ret=Cmp(a->name.name_id,b->name.name_id) ) return ret;
      }
    
    return CmpEqual;
   }
 };

/* class ScopeList */

class ScopeList : public TempArray<ScopeNode *,100>  
 {
  public:
  
   explicit ScopeList(From from);
  
   ~ScopeList();
 };

/* struct LenNode */

struct LenNode : NoCopy
 {
  LenNode *prev;
  
  FileId *file_id;
  TextPos pos;
  ExprNode *expr_node;
  
  void init(ExtContext ctx,const Token &ops,ExprNode *expr_node); // ops is [

  struct FromNode : NoCopy
   {
    FromNode *prev;
    
    From from;
   };
  
  FromNode from_node;
  
  From getFrom() const { return from_node.from; }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"length #;",PrintPos(file_id,pos));
   }
  
  // work area
  
  ulen index;
 };

/* struct TypeListNode */

struct TypeListNode : NoCopy
 {
  TypeListNode *prev;
  
  TypeNode *type_node;
  
  void init(TypeNode *type_node);
 };

/* type TypeList */

using TypeList = CountList<TypeListNode> ;

using TypeListPtr = ListPrevPtr<TypeListNode> ;

/* struct TypeNode */

struct TypeNode : NoCopy
 {
  struct Base
   {
    enum Type
     {
      Type_none = 0,
      
      Type_sint,
      Type_uint,
      Type_ulen,
      
      Type_sint8,
      Type_uint8,
      Type_sint16,
      Type_uint16,
      Type_sint32,
      Type_uint32,
      Type_sint64,
      Type_uint64,
      
      Type_text,
      Type_ip,
      
      TypeIntMin=Type_sint,
      TypeIntMax=Type_uint64
     };
    
    Type type;
    
    explicit Base(Type type_) : type(type_) {}
    
    bool isIntegral() const { return type && type<Type_text ; }
    
    bool isText() const { return type==Type_text; }
    
    bool isIP() const { return type==Type_ip; }
   };
  
  struct Ref
   {
    NameRefNode *name_ref;
    
    AnyPtr<AliasNode,StructNode> ptr; // name link
    
    explicit Ref(NameRefNode *name_ref_) : name_ref(name_ref_) {}
   };
  
  struct Ptr
   {
    TypeNode *type_node;
    
    explicit Ptr(TypeNode *type_node_) : type_node(type_node_) {}
   };
  
  struct PolyPtr
   {
    TypeList *type_list;
    
    explicit PolyPtr(TypeList *type_list_) : type_list(type_list_) {}
   };
  
  struct Array
   {
    TypeNode *type_node;
    
    explicit Array(TypeNode *type_node_) : type_node(type_node_) {}
   };
  
  struct ArrayLen
   {
    TypeNode *type_node;
    
    LenNode len_node;
    
    ArrayLen(TypeNode *type_node_,ExtContext ctx,const Token &ops,ExprNode *expr_node) // ops is [ 
     : type_node(type_node_) 
     { 
      len_node.init(ctx,ops,expr_node); 
     }
   };
  
  struct Struct
   {
    StructNode *struct_node;
    
    explicit Struct(StructNode *struct_node_) : struct_node(struct_node_) {}
   };
  
  AnyPtr<Base,Ref,Ptr,PolyPtr,Array,ArrayLen,Struct> ptr;
  
  struct Lists;
  
  Lists *lists;
  
  void addLists(TypeNode *node);
  
  void init_base(ElementPool &pool,Base::Type base_type);
  
  void init_base(ExtContext ctx,Base::Type base_type);
  
  void init_ref(ExtContext ctx,NameRefNode *name_ref);
  
  void init_ptr(ExtContext ctx,TypeNode *type_node);
  
  void init_polyptr(ExtContext ctx,TypeList *type_list);
  
  void init_array(ExtContext ctx,TypeNode *type_node);
  
  void init_array_len(ExtContext ctx,TypeNode *type_node,const Token &ops,ExprNode *expr_node); // ops is [
  
  void init_struct(ExtContext ctx,StructNode *struct_node);
  
  bool doLink(From from,LinkContext ctx);
 };

inline void TypeListNode::init(TypeNode *type_node_)
 {
  type_node=type_node_;
 }

const char * GetTextDesc(TypeNode::Base::Type base_type);

/* struct LitNull */

struct LitNull
 {
  Token token;
  
  explicit LitNull(const Token &token_) : token(token_) {}
 };

/* struct LitString */

struct LitString
 {
  Token token;
  
  explicit LitString(const Token &token_) : token(token_) {}
 };

/* struct LitIP */

struct LitIP
 {
  Token token1;
  Token token2;
  Token token3;
  Token token4;
  
  LitIP(const Token &token1_,const Token &token2_,const Token &token3_,const Token &token4_)
   : token1(token1_),token2(token2_),token3(token3_),token4(token4_) {} 
 };

/* struct ExprListNode */

struct ExprListNode : NoCopy
 {
  ExprListNode *next;
  
  ExprNode *expr_node;
  
  void init(ExprNode *expr_node);
 };

/* type ExprList */

using ExprList = ForwardList<ExprListNode> ;

/* struct NamedExprListNode */

struct NamedExprListNode : NoCopy
 {
  NamedExprListNode *prev;
  
  NameIdNode name;
  ExprNode *expr_node;
  
  void init(ExtContext ctx,const Token &name,ExprNode *expr_node); 
 };

/* type NamedExprList */

using NamedExprList = BaseList<NamedExprListNode> ;

/* struct ExprNode */

struct ExprNode : NoCopy
 {
  struct Deref
   {
    ExprNode *arg;
    
    explicit Deref(ExprNode *arg_) : arg(arg_) {}
   };
  
  struct Address
   {
    ExprNode *arg;
    
    explicit Address(ExprNode *arg_) : arg(arg_) {}
   };
  
  struct Plus
   {
    ExprNode *arg;
    
    explicit Plus(ExprNode *arg_) : arg(arg_) {}
   };
  
  struct Minus
   {
    ExprNode *arg;
    
    explicit Minus(ExprNode *arg_) : arg(arg_) {}
   };
  
  struct Add
   {
    ExprNode *arg1;
    ExprNode *arg2;
    
    Add(ExprNode *arg1_,ExprNode *arg2_) : arg1(arg1_),arg2(arg2_) {}
   };
  
  struct Sub
   {
    ExprNode *arg1;
    ExprNode *arg2;
    
    Sub(ExprNode *arg1_,ExprNode *arg2_) : arg1(arg1_),arg2(arg2_) {}
   };
  
  struct Mul
   {
    ExprNode *arg1;
    ExprNode *arg2;
    
    Mul(ExprNode *arg1_,ExprNode *arg2_) : arg1(arg1_),arg2(arg2_) {}
   };
  
  struct Div
   {
    ExprNode *arg1;
    ExprNode *arg2;
    
    Div(ExprNode *arg1_,ExprNode *arg2_) : arg1(arg1_),arg2(arg2_) {}
   };
  
  struct Rem
   {
    ExprNode *arg1;
    ExprNode *arg2;
    
    Rem(ExprNode *arg1_,ExprNode *arg2_) : arg1(arg1_),arg2(arg2_) {}
   };
  
  struct Ind
   {
    ExprNode *arg1;
    ExprNode *arg2;
    
    Ind(ExprNode *arg1_,ExprNode *arg2_) : arg1(arg1_),arg2(arg2_) {}
   };
  
  struct Select
   {
    ExprNode *arg;
    NameIdNode name;
    
    Select(ExprNode *arg_,ExtContext ctx,const Token &field) : arg(arg_) { name.init(ctx,field); }
   };
  
  struct PtrSelect
   {
    ExprNode *arg;
    NameIdNode name;
    
    PtrSelect(ExprNode *arg_,ExtContext ctx,const Token &field) : arg(arg_) { name.init(ctx,field); }
   };
  
  struct Domain
   {
    ExprNode *arg;
    TypeNode::Base::Type type; // if( name_ref ) name link
    NameRefNode *name_ref;
    AliasNode *ptr; // if( name_ref ) name link
    
    Domain(ExprNode *arg_,TypeNode::Base::Type type_,NameRefNode *name_ref_) // alternative 
     : arg(arg_),type(type_),name_ref(name_ref_),ptr(0) {}
    
    bool setType(ErrorMsg &error);
   };
  
  struct Ref
   {
    NameRefNode *name_ref;
    
    ConstNode *ptr; // name link
    
    explicit Ref(NameRefNode *name_ref_) : name_ref(name_ref_),ptr(0) {}
   };
  
  struct Null
   {
    Null() {}
   };
  
  struct Number
   {
    Token number;
    
    explicit Number(const Token &number_) : number(number_) {}
   };
  
  struct String
   {
    Token string;
    
    explicit String(const Token &string_) : string(string_) {}
   };
  
  struct IP
   {
    LitIP lit;
    
    explicit IP(const LitIP &lit_) : lit(lit_) {}
   };
  
  struct EmptyList
   {
    EmptyList() {}
   };
  
  struct NonameList
   {
    ExprList list;
    
    explicit NonameList(ExprList *list_) { list.copy(*list_); }
   };
  
  struct NamedList
   {
    NamedExprList list;
    
    explicit NamedList(NamedExprList *list_) { list.copy(*list_); }
   };

  struct ApplyEmptyList
   {
    ExprNode *arg;
    
    explicit ApplyEmptyList(ExprNode *arg_) : arg(arg_) {}
   };
  
  struct ApplyNamedList
   {
    ExprNode *arg;
    NamedExprList list;
    
    ApplyNamedList(ExprNode *arg_,NamedExprList *list_)
     : arg(arg_)
     {
      list.copy(*list_);
     }
   };
  
  PosName ops;
  AnyPtr<Deref,Address,Plus,Minus,
         Add,Sub,Mul,Div,Rem,Ind,
         Select,PtrSelect,
         Domain,
         Ref,Null,Number,String,IP,
         EmptyList,NonameList,NamedList,ApplyEmptyList,ApplyNamedList
        > ptr;
  
  struct Lists;
  
  Lists *lists;
  
  void addLists(ExprNode *node);
  
  void init(ExtContext ctx,ExprNode *node);
  
  template <class T>
  void init_op(ExtContext ctx,const Token &ops,ExprNode *arg);
  
  template <class T>
  void init_op(ExtContext ctx,const Token &ops,ExprNode *arg1,ExprNode *arg2);
  
  template <class T,class S>
  void init_op_ext(ExtContext ctx,const Token &ops,ExprNode *arg,const S &ext);
  
  void init_deref(ExtContext ctx,const Token &ops,ExprNode *arg);

  void init_address(ExtContext ctx,const Token &ops,ExprNode *arg);
  
  void init_plus(ExtContext ctx,const Token &ops,ExprNode *arg);
  
  void init_minus(ExtContext ctx,const Token &ops,ExprNode *arg);
  
  void init_add(ExtContext ctx,const Token &ops,ExprNode *arg1,ExprNode *arg2);
  
  void init_sub(ExtContext ctx,const Token &ops,ExprNode *arg1,ExprNode *arg2);
  
  void init_mul(ExtContext ctx,const Token &ops,ExprNode *arg1,ExprNode *arg2);
  
  void init_div(ExtContext ctx,const Token &ops,ExprNode *arg1,ExprNode *arg2);
  
  void init_rem(ExtContext ctx,const Token &ops,ExprNode *arg1,ExprNode *arg2);
  
  void init_ind(ExtContext ctx,const Token &ops,ExprNode *arg1,ExprNode *arg2);
  
  void init_select(ExtContext ctx,const Token &ops,ExprNode *arg,const Token &field);
  
  void init_ptr_select(ExtContext ctx,const Token &ops,ExprNode *arg,const Token &field);
  
  void init_domain(ExtContext ctx,const Token &ops,ExprNode *arg,TypeNode::Base::Type base_type,NameRefNode *name_ref);
  
  void init_ref(ExtContext ctx,NameRefNode *name_ref);
  
  void init_null(ExtContext ctx,const LitNull &lit);
  
  void init_number(ExtContext ctx,const Token &number);
  
  void init_string(ExtContext ctx,const LitString &lit);
  
  void init_ip(ExtContext ctx,const LitIP &lit);
  
  void init_lit(ExtContext ctx,AnyPtr<LitNull,LitString,LitIP> ptr);
  
  void init_noname_list(ExtContext ctx,const Token &ops);
  
  void init_noname_list(ExtContext ctx,const Token &ops,ExprList *list);
  
  void init_named_list(ExtContext ctx,const Token &ops,NamedExprList *list);
  
  void init_apply_named_list(ExtContext ctx,const Token &ops,ExprNode *arg);
  
  void init_apply_named_list(ExtContext ctx,const Token &ops,ExprNode *arg,NamedExprList *list);
  
  bool doLink(From from,LinkContext ctx);
  
  bool doLinkQName(From from,LinkContext ctx);
  
  bool hasQNames() const;
 };

inline void LenNode::init(ExtContext ctx,const Token &ops,ExprNode *expr_node_)
 {
  file_id=ctx.getFileId();
  pos=ops.pos;
  
  expr_node=expr_node_; 
 }

inline void ExprListNode::init(ExprNode *expr_node_) 
 { 
  expr_node=expr_node_; 
 }

inline void NamedExprListNode::init(ExtContext ctx,const Token &name_,ExprNode *expr_node_) 
 {
  name.init(ctx,name_);
  expr_node=expr_node_; 
 }

/* struct DomainRefNode */

struct DomainRefNode
 {
  DomainRefNode *prev;
  
  ExprNode::Domain *ptr;
  
  explicit DomainRefNode(ExprNode::Domain *ptr_) : ptr(ptr_) {}
 };

inline void Context::add(DomainRefNode *domain_ref_node)
 {
  domain_ref_list.add(domain_ref_node);
 }

inline void ExtContext::add(DomainRefNode *domain_ref_node)
 {
  ctx->add(domain_ref_node);
 }

/* struct RefListNode */

struct RefListNode : NoCopy
 {
  RefListNode *prev;
  
  AnyPtr<TypeNode::Ref,ExprNode::Domain,ExprNode::Ref> ptr;
  
  template <class T>
  explicit RefListNode(T *ptr_) : ptr(ptr_) {}
 };

/* struct NodeBase<T> */

template <class T> 
struct NodeBase : NoCopy
 {
  T *prev;
  
  ScopeNode *parent;
  ulen depth;
  
  NameIdNode name;
  
  void init_base(ExtContext ctx,const Token &token)
   {
    parent=0;
    depth=0;
    
    name.init(ctx,token);
   }
  
  void setParent(ScopeNode *parent_)
   {
    if( !parent ) parent=parent_;
    
    depth++;
   }
  
  From getFrom() const { return From(parent,depth); }
  
  // work area
  
  ulen index;
 };

/* struct AliasNode */

struct AliasNode : NodeBase<AliasNode>
 {
  TypeNode *type_node;
  
  TypeNode *result_type; // don't point to TypeNode Ref with another alias
  
  TreeLink<AliasNode,NameId> link;
  
  void init(ExtContext ctx,const Token &token,TypeNode *type_node_)
   {
    init_base(ctx,token);
    
    type_node=type_node_;
    
    result_type=0;
   }
  
  bool doLink(LinkContext ctx);
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"type #;",name);
   }
 };

/* struct ConstNode */

struct ConstNode : NodeBase<ConstNode>
 {
  TypeNode *type_node;
  ExprNode *expr_node;
  
  TreeLink<ConstNode,NameId> link;
  
  void init(ExtContext ctx,const Token &token,TypeNode *type_node_,ExprNode *expr_node_)
   {
    init_base(ctx,token);
    
    type_node=type_node_;
    expr_node=expr_node_;
   }
  
  bool doLink(LinkContext ctx);
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"const #;",name);
   }
 };

/* struct FieldNode */

struct FieldNode : NoCopy
 {
  FieldNode *next;
  
  NameIdNode name;
  TypeNode *type_node;
  ExprNode *expr_node;
  
  TreeLink<FieldNode,NameId> link;
  
  void init(ExtContext ctx,const Token &token,TypeNode *type_node_)
   {
    name.init(ctx,token);
    
    type_node=type_node_;
    
    ExprNode *node=ctx.create<ExprNode>();
    
    node->init_noname_list(ctx,token);
    
    expr_node=node;
   }
  
  void init(ExtContext ctx,const Token &token,TypeNode *type_node_,ExprNode *expr_node_)
   {
    name.init(ctx,token);
    
    type_node=type_node_;
    expr_node=expr_node_;
   }
  
  bool doLink(From from,LinkContext ctx);
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"default field #;",name);
   }
  
  // work area
  
  ulen index;
  ulen field_index;
 };

/* class FieldMap */

class FieldMap : NoCopy
 {
   typedef TreeLink<FieldNode,NameId>::RadixAlgo<&FieldNode::link> Algo;
  
   Algo::Root root;
   bool ok;
   
  private: 
  
   void add(ErrorMsg &error,NameId max_id,FieldNode *node);
   
  public: 
  
   FieldMap(ErrorMsg &error,NameId max_id,StructNode *node);

   bool operator + () const { return ok; }
   
   bool operator ! () const { return !ok; }
  
   FieldNode * find(const NameIdNode &name) const { return root.find(name.name_id); }
 };

/* struct StructNode */

struct StructNode : NodeBase<StructNode>
 {
  ScopeNode scope_node;
  ForwardList<FieldNode> field_list;
  FieldMap *field_map;
  
  TreeLink<StructNode,NameId> link;
  
  void init(ExtContext ctx,const Token &token,SBodyNode *sbody);
  
  bool setMap(Context *ctx,NameId max_id);
  
  From getFieldFrom() { return From(&scope_node,depth+1); }
  
  bool doLink(LinkContext ctx);
  
  FieldNode * find(const NameIdNode &name) const { return field_map->find(name); }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"struct #;",name);
   }
 };

/* class NameLinkMap */

class NameLinkMap : NoCopy
 {
   TreeLink<NameLinkMap,NameId> link;
  
   template <class T>
   using Algo = typename TreeLink<T,NameId>::template RadixAlgo<&T::link> ;
 
   Algo<AliasNode>::Root alias_root;
   Algo<ConstNode>::Root const_root;
   Algo<StructNode>::Root struct_root;
   
   Algo<NameLinkMap>::Root map_root;
   
   NameIdNode *name;
   
  private:
   
   using RecPtr = AnyPtr<AliasNode,ConstNode,StructNode,NameLinkMap> ;
   
   struct Rec : NoThrowFlagsBase
    {
     RecPtr ptr;
     NameIdNode *name;
     
     template <class T>
     explicit Rec(T *node) : ptr(node),name(&node->name) {}
     
     explicit Rec(NameLinkMap *map) : ptr(map),name(map->name) {}
    };
   
   template <class T>
   void fill(Collector<Rec> &col,T *root);
   
   bool check(ErrorMsg &error,RecPtr a,RecPtr b);
   
   bool check(ErrorMsg &error,PtrLen<Rec> range);
   
  public:
  
   NameLinkMap *prev;
   
   NameLinkMap() : name(0) {}
   
   explicit NameLinkMap(ScopeNode &node) : name(&node.name) {}
   
   // add
   
   NameLinkMap * add(ElementPool &pool,NameId max_id,ScopeNode &node,BaseList<NameLinkMap> &map_list);
   
   bool add(ErrorMsg &error,NameId max_id,AliasNode &node);
   
   bool add(ErrorMsg &error,NameId max_id,ConstNode &node);
   
   bool add(ErrorMsg &error,NameId max_id,StructNode &node);
   
   bool check(ErrorMsg &error);
   
  private: 
   
   // find
   
   NameLinkMap * findMap(const NameIdNode &name) { return map_root.find(name.name_id); }
   
   AliasNode * findAlias(const NameIdNode &name) { return alias_root.find(name.name_id); }
   
   ConstNode * findConst(const NameIdNode &name) { return const_root.find(name.name_id); }
   
   StructNode * findStruct(const NameIdNode &name) { return struct_root.find(name.name_id); }
   
   // link
   
   struct NoError
    {
     template <class ... SS>
     void operator () (SS && ...) {}
    };
   
   template <class Error>
   NameLinkMap * findMap(Error &error,From from,NameNodeList *name_list);
   
   NameLinkMap * tryFindMap(From from,NameNodeList *name_list);
   
   template <class Func>
   bool tryFindNode(From from,NameNodeList *name_list,Func func);
   
   template <class Error,class Func>
   void findNode(Error &error,From from,NameNodeList *name_list,Func func);
   
   template <class Error,class Func>
   void findNode(Error &error,From from,NameRefNode *name_ref,Func func);
   
   template <class Error>
   ConstNode * findConst(Error &error,From from,NameRefNode *name_ref);
   
   AliasNode * findAlias(ErrorMsg &error,From from,NameRefNode *name_ref);
   
   AnyPtr<AliasNode,StructNode> findAliasStruct(ErrorMsg &error,From from,NameRefNode *name_ref);
   
  public: 
   
   bool doLink(ErrorMsg &error,From from,TypeNode::Ref *ptr);
   
   bool doLink(ErrorMsg &error,From from,ExprNode::Domain *ptr);
   
   bool doLink(ErrorMsg &error,From from,ExprNode::Ref *ptr);
   
   bool doLinkQName(ErrorMsg &error,From from,TypeNode::Ref *ptr) { return doLink(error,from,ptr); }
   
   bool doLinkQName(ErrorMsg &error,From from,ExprNode::Domain *ptr) { return doLink(error,from,ptr); }
   
   bool doLinkQName(ErrorMsg &error,From from,ExprNode::Ref *ptr);
   
   ConstNode * doLink(From from,ExprNode::Ref *ptr);
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     if( name )
       Printf(out,"scope #;",*name);
     else
       Putobj(out,"root scope");
    }
 };

/* class LinkContext */

class LinkContext
 {
   ErrorMsg &error;
   NameLinkMap *map;
   
   struct Func;
   struct FuncQName;
   
  public: 
  
   LinkContext(ErrorMsg &error_,NameLinkMap *map_) : error(error_),map(map_) {}
  
   // link
  
   template <class T>
   bool doLink(From from,T *ptr) { return map->doLink(error,from,ptr); }
  
   template <class T>
   bool doLinkQName(From from,T *ptr) { return map->doLinkQName(error,from,ptr); }
   
   bool doLink(From from,AnyPtr<TypeNode::Ref,ExprNode::Domain,ExprNode::Ref> ptr);
   
   bool doLinkQName(From from,AnyPtr<TypeNode::Ref,ExprNode::Domain,ExprNode::Ref> ptr);
 };

inline bool AliasNode::doLink(LinkContext ctx)
 {
  From from=getFrom();
  
  return type_node->doLink(from,ctx);
 }

inline bool ConstNode::doLink(LinkContext ctx)
 {
  From from=getFrom();
  
  AndFlag ret;
  
  ret+=type_node->doLink(from,ctx);
  ret+=expr_node->doLink(from,ctx);
  
  return ret;
 }

inline bool FieldNode::doLink(From from,LinkContext ctx)
 {
  AndFlag ret;
  
  ret+=type_node->doLink(from,ctx);
  ret+=expr_node->doLinkQName(from,ctx);
  
  return ret;
 }

/* struct BodyNode */

struct BodyNode : NoCopy
 {
  BegList<AliasNode> alias_list;
  BegList<ConstNode> const_list;
  BegList<StructNode> struct_list;
  
  BegList<ScopeNode> scope_list; // level 1
  
  BegList<LenNode> len_list;
  
  NameLinkMap *map; // name link
  
  void start()
   {
    alias_list.init();
    const_list.init();
    struct_list.init();
    
    scope_list.init();
    len_list.init();
    
    map=0;
   }
  
  void add(AliasNode *node)
   {
    alias_list.add(node);
    
    add(node->type_node);
   }
  
  void add(ConstNode *node)
   {
    const_list.add(node);
    
    add(node->type_node);
   }
  
  void add(StructNode *node)
   {
    struct_list.add(node);
    
    add(&node->scope_node);
   }
  
  void add(ScopeNode *scope)
   {
    scope_list.add(scope);
    
    add_inner(scope->body);
   }
  
  void add(BodyNode *body)
   {
    alias_list.join(body->alias_list);
    const_list.join(body->const_list);
    struct_list.join(body->struct_list);
    scope_list.join(body->scope_list);
    len_list.join(body->len_list);
   }
  
  void add_inner(BodyNode *body)
   {
    alias_list.join(body->alias_list);
    const_list.join(body->const_list);
    struct_list.join(body->struct_list);
    len_list.join(body->len_list);
   }
  
  void add(TypeNode *type_node);
  
  void foldin(ScopeNode *scope);
  
  bool setMap(Context *ctx,NameId max_id);
  
  bool doLink(LinkContext ctx);
 };

/* struct SBodyNode */

struct SBodyNode : NoCopy
 {
  BodyNode body_node;
  ForwardList<FieldNode> field_list;
  
  void start()
   {
    body_node.start();
    field_list.init();
   }
  
  void add(AliasNode *node) { body_node.add(node); }
  
  void add(ConstNode *node) { body_node.add(node); }
  
  void add(StructNode *node) { body_node.add(node); }
  
  void add(FieldNode *node) 
   {
    field_list.add(node);
    
    body_node.add(node->type_node);
   }
 };

inline void StructNode::init(ExtContext ctx,const Token &token,SBodyNode *sbody)
 {
  init_base(ctx,token);
  
  scope_node.init(ctx,token,&sbody->body_node);
  
  field_list.copy(sbody->field_list);
  
  field_map=0;
 }

/* struct TypeNode::Lists */

struct TypeNode::Lists : NoCopy
 {
  BegList<StructNode> struct_list;
  BegList<LenNode> len_list;
  BegList<RefListNode> ref_list;
  
  BaseList<LenNode::FromNode> from_list;
    
  explicit Lists(StructNode *struct_node)
   {
    struct_list.init(struct_node);
    len_list.init();
    ref_list.init();
    from_list.init();
   }
    
  explicit Lists(LenNode *len_node)
   {
    struct_list.init();
    len_list.init(len_node);
    ref_list.init();
    from_list.init();
   }
  
  explicit Lists(RefListNode *ref_node)
   {
    struct_list.init();
    len_list.init();
    ref_list.init(ref_node);
    from_list.init();
   }
  
  void fill_from_list()
   {
    for(LenNode &node : len_list ) from_list.add(&node.from_node);
   }
  
  void join(Lists *obj)
   {
    if( obj )
      {
       struct_list.join(obj->struct_list);
       len_list.join(obj->len_list);
       ref_list.join(obj->ref_list);
      } 
   }
 };

/* struct ExprNode::Lists */

struct ExprNode::Lists : NoCopy
 {
  BegList<RefListNode> ref_list;
  bool qname_flag;
  
  explicit Lists(RefListNode *ref_node,bool qname_flag_=false)
   {
    ref_list.init(ref_node);
    
    qname_flag=qname_flag_;
   }
  
  void join(Lists *obj)
   {
    if( obj )
      {
       ref_list.join(obj->ref_list);
       
       if( obj->qname_flag ) qname_flag=true;
      } 
   }
 };
  
/* struct TypeNode */
  
inline void TypeNode::addLists(TypeNode *node)
 {
  if( lists )
    lists->join(node->lists);
  else
    lists=node->lists;
 }
  
inline void TypeNode::init_base(ElementPool &pool,Base::Type base_type)
 {
  ptr=pool.create<Base>(base_type);
  lists=0;
 }

inline void TypeNode::init_base(ExtContext ctx,Base::Type base_type)
 {
  ptr=ctx.create<Base>(base_type);
  lists=0;
 }

inline void TypeNode::init_ref(ExtContext ctx,NameRefNode *name_ref)
 {
  Ref *obj=ctx.create<Ref>(name_ref);
  
  ptr=obj;
  
  lists=ctx.create<Lists>(ctx.create<RefListNode>(obj));
 }

inline void TypeNode::init_ptr(ExtContext ctx,TypeNode *type_node)
 {
  ptr=ctx.create<Ptr>(type_node);
  lists=type_node->lists;
 }

inline void TypeNode::init_polyptr(ExtContext ctx,TypeList *type_list)
 {
  ptr=ctx.create<PolyPtr>(type_list);
  
  lists=0;
  
  for(TypeListNode &obj : *type_list ) addLists(obj.type_node);
 }

inline void TypeNode::init_array(ExtContext ctx,TypeNode *type_node)
 {
  ptr=ctx.create<Array>(type_node);
  lists=type_node->lists;
 }

inline void TypeNode::init_array_len(ExtContext ctx,TypeNode *type_node,const Token &ops,ExprNode *expr_node)
 {
  ArrayLen *obj=ctx.create<ArrayLen>(type_node,ctx,ops,expr_node);
  
  ptr=obj;
  
  lists=type_node->lists;
  
  if( lists )
    lists->len_list.add(&obj->len_node);
  else
    lists=ctx.create<Lists>(&obj->len_node);
   
  if( auto *expr_lists=expr_node->lists ) lists->ref_list.join(expr_lists->ref_list);
 }

inline void TypeNode::init_struct(ExtContext ctx,StructNode *struct_node)
 {
  ptr=ctx.create<Struct>(struct_node);
  lists=ctx.create<Lists>(struct_node);
 }

/* struct ExprNode */

inline void ExprNode::addLists(ExprNode *node)
 {
  if( lists )
    lists->join(node->lists);
  else
    lists=node->lists;
 }

inline void ExprNode::init(ExtContext,ExprNode *node)
 {
  ops=node->ops;
  ptr=node->ptr;
  lists=node->lists;
 }

template <class T>
void ExprNode::init_op(ExtContext ctx,const Token &ops_,ExprNode *arg)
 {
  ops.init(ctx.getFileId(),ops_);
  
  ptr=ctx.create<T>(arg);
  
  lists=arg->lists;
 }
  
template <class T>
void ExprNode::init_op(ExtContext ctx,const Token &ops_,ExprNode *arg1,ExprNode *arg2)
 {
  ops.init(ctx.getFileId(),ops_);
  
  ptr=ctx.create<T>(arg1,arg2);
  
  lists=arg1->lists;
  
  addLists(arg2);
 }
  
template <class T,class S>
void ExprNode::init_op_ext(ExtContext ctx,const Token &ops_,ExprNode *arg,const S &ext)
 {
  ops.init(ctx.getFileId(),ops_);
  
  ptr=ctx.create<T>(arg,ctx,ext);
  
  lists=arg->lists;
 }

inline void ExprNode::init_deref(ExtContext ctx,const Token &ops_,ExprNode *arg)
 {
  init_op<Deref>(ctx,ops_,arg);
 }

inline void ExprNode::init_address(ExtContext ctx,const Token &ops_,ExprNode *arg)
 {
  init_op<Address>(ctx,ops_,arg);
 }

inline void ExprNode::init_plus(ExtContext ctx,const Token &ops_,ExprNode *arg)
 {
  init_op<Plus>(ctx,ops_,arg);
 }

inline void ExprNode::init_minus(ExtContext ctx,const Token &ops_,ExprNode *arg)
 {
  init_op<Minus>(ctx,ops_,arg);
 }

inline void ExprNode::init_add(ExtContext ctx,const Token &ops_,ExprNode *arg1,ExprNode *arg2)
 {
  init_op<Add>(ctx,ops_,arg1,arg2);
 }

inline void ExprNode::init_sub(ExtContext ctx,const Token &ops_,ExprNode *arg1,ExprNode *arg2)
 {
  init_op<Sub>(ctx,ops_,arg1,arg2);
 }

inline void ExprNode::init_mul(ExtContext ctx,const Token &ops_,ExprNode *arg1,ExprNode *arg2)
 {
  init_op<Mul>(ctx,ops_,arg1,arg2);
 }

inline void ExprNode::init_div(ExtContext ctx,const Token &ops_,ExprNode *arg1,ExprNode *arg2)
 {
  init_op<Div>(ctx,ops_,arg1,arg2);
 }

inline void ExprNode::init_rem(ExtContext ctx,const Token &ops_,ExprNode *arg1,ExprNode *arg2)
 {
  init_op<Rem>(ctx,ops_,arg1,arg2);
 }

inline void ExprNode::init_ind(ExtContext ctx,const Token &ops_,ExprNode *arg1,ExprNode *arg2)
 {
  init_op<Ind>(ctx,ops_,arg1,arg2);
 }

inline void ExprNode::init_select(ExtContext ctx,const Token &ops_,ExprNode *arg,const Token &field)
 {
  init_op_ext<Select>(ctx,ops_,arg,field);
 }

inline void ExprNode::init_ptr_select(ExtContext ctx,const Token &ops_,ExprNode *arg,const Token &field)
 {
  init_op_ext<PtrSelect>(ctx,ops_,arg,field);
 }

inline void ExprNode::init_domain(ExtContext ctx,const Token &ops_,ExprNode *arg,TypeNode::Base::Type type,NameRefNode *name_ref)
 {
  ops.init(ctx.getFileId(),ops_);
  
  auto *obj=ctx.create<Domain>(arg,type,name_ref);
  
  ptr=obj;
  
  lists=arg->lists;
  
  if( name_ref )
    {
     {
      auto *node=ctx.create<RefListNode>(obj);
     
      if( lists )
        lists->ref_list.add(node);
      else
        lists=ctx.create<Lists>(node);
     }
     {
      auto *node=ctx.create<DomainRefNode>(obj);
      
      ctx.add(node);
     }
    }
 }

inline void ExprNode::init_ref(ExtContext ctx,NameRefNode *name_ref)
 {
  ops=name_ref->posName();
  
  auto *obj=ctx.create<Ref>(name_ref);
  
  ptr=obj;
  
  lists=ctx.create<Lists>(ctx.create<RefListNode>(obj),name_ref->name_list->qname_flag);
 }

inline void ExprNode::init_null(ExtContext ctx,const LitNull &lit)
 {
  ops.init(ctx.getFileId(),lit.token);
  
  ptr=(Null *)0;
  
  lists=0;
 }

inline void ExprNode::init_number(ExtContext ctx,const Token &number)
 {
  ops.init(ctx.getFileId(),number);
  
  ptr=ctx.create<Number>(number);
  
  lists=0;
 }

inline void ExprNode::init_string(ExtContext ctx,const LitString &lit)
 {
  ops.init(ctx.getFileId(),lit.token);
  
  ptr=ctx.create<String>(lit.token);
  
  lists=0;
 }

inline void ExprNode::init_ip(ExtContext ctx,const LitIP &lit)
 {
  ops.init(ctx.getFileId(),lit.token1);
  
  ptr=ctx.create<IP>(lit);
  
  lists=0;
 }

inline void ExprNode::init_lit(ExtContext ctx,AnyPtr<LitNull,LitString,LitIP> ptr)
 {
  struct Func
   {
    ExprNode *node;
    ExtContext ctx;
    
    Func(ExprNode *node_,ExtContext ctx_) : node(node_),ctx(ctx_) {}
    
    void operator () (LitNull *lit) { node->init_null(ctx,*lit); }
    
    void operator () (LitString *lit) { node->init_string(ctx,*lit); }
    
    void operator () (LitIP *lit) { node->init_ip(ctx,*lit); }
   };
  
  ptr.apply(Func(this,ctx));
 }

inline void ExprNode::init_noname_list(ExtContext ctx,const Token &ops_)
 {
  ops.init(ctx.getFileId(),ops_);
  
  ptr=(EmptyList *)0;
  
  lists=0;
 }

inline void ExprNode::init_noname_list(ExtContext ctx,const Token &ops_,ExprList *list)
 {
  ops.init(ctx.getFileId(),ops_);
  
  ptr=ctx.create<NonameList>(list);
  
  lists=0;
  
  for(auto &node : *list ) addLists(node.expr_node);
 }

inline void ExprNode::init_named_list(ExtContext ctx,const Token &ops_,NamedExprList *list)
 {
  ops.init(ctx.getFileId(),ops_);
  
  ptr=ctx.create<NamedList>(list);
  
  lists=0;
  
  for(auto &node : *list ) addLists(node.expr_node);
 }

inline void ExprNode::init_apply_named_list(ExtContext ctx,const Token &ops_,ExprNode *arg)
 {
  ops.init(ctx.getFileId(),ops_);
  
  ptr=ctx.create<ApplyEmptyList>(arg);
  
  lists=arg->lists;
 }

inline void ExprNode::init_apply_named_list(ExtContext ctx,const Token &ops_,ExprNode *arg,NamedExprList *list)
 {
  ops.init(ctx.getFileId(),ops_);
  
  ptr=ctx.create<ApplyNamedList>(arg,list);
  
  lists=arg->lists;
  
  for(auto &node : *list ) addLists(node.expr_node);
 }

inline bool ExprNode::hasQNames() const
 {
  if( !lists ) return false;
  
  return lists->qname_flag;
 }

} // namespace DDL2
} // namespace CCore

#endif
