/* DDLSemantic.h */
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

#ifndef CCore_inc_ddl_DDLSemantic_h
#define CCore_inc_ddl_DDLSemantic_h

#include <CCore/inc/ddl/DDLTools.h>
#include <CCore/inc/ddl/DDLTypes.h>

#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Cmp.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/Array.h>

namespace CCore {
namespace DDL {

/* types */

typedef ulen NameId;

/* classes */

struct NameLink;

class NameIdEngine;

struct From;

class NameLinkEngine;

struct RefBase;

class RefList;

struct DomainBase;

class DomainList;

class ExprList;

struct Context;

struct ExtContext;

struct NameNode;

struct NameRef;

struct ScopeNode;

struct FieldNode;

template <class T> struct NodeBase;

struct AliasNode;

struct ConstNode;

class FieldMap;

struct StructNode;

struct LenNode;

struct BodyNode;

struct SBodyNode;

struct TypeNode; // + variants

struct TypeSwitch;

class FindFieldType;

class TypeCompare;

struct DomainTypeNode;

struct NonameExprNode;

struct NamedExprNode;

struct ExprNode; // + variants

struct ExprSwitch;

/* struct NameLink */

struct NameLink : NoCopy
 {
  NameLink *prev;
  
  PosName name;
  NameId name_id;
  
  void init(ExtContext ctx,const Token &token);
  
  template <class P>
  void print(P &out) const
   {
    Putobj(out,name);
   }
 };

/* class NameIdEngine */

class NameIdEngine : NoCopy
 {
   CountList<NameLink> list;
   
  private: 
  
   struct Rec;
   
  public:
   
   NameIdEngine() { reset(); }
   
   void reset() { list.init(); }
   
   void add(NameLink *name) { list.add(name); }
   
   NameId generate(); // return max id
 };

/* struct From */

struct From
 {
  ScopeNode *scope;
  ulen depth;
  bool ok;
  
  From();
  
  From(ScopeNode *scope,ulen depth);
  
  bool operator ! () const { return !ok; }
  
  bool back();
 };

void SetScope(RingNode<From> *from_ring,From from);

/* class NameLinkEngine */

class NameLinkEngine : NoCopy
 {
   PrintBase &msg;
   NameId max_id;

   struct Rec;
   class Map;
   
   ElementPool pool;
   Map *root;
   
   DynArray<NameLink *> buf;
   
  private:
   
   static void FillBuf(NameLink **buf,ulen len,ScopeNode *ptr);
   
   NameLink ** getBuf(ulen len);
   PtrLen<NameLink *> makePath(ulen depth,ScopeNode *ptr);
   PtrLen<NameLink *> makePath(From from);
   
   Rec * addPath(ulen depth,ScopeNode *parent,NameLink &name,bool allow_map=false);
   
   Rec * find(Map *map,ForwardList<NameNode> name_list);
   Rec * find(PtrLen<NameLink *> path,ForwardList<NameNode> name_list);
   Rec * find(ForwardList<NameNode> name_list);
   
   Rec * find_abs(From from,ForwardList<NameNode> name_list);
   Rec * find_this(From from,ForwardList<NameNode> name_list);
   Rec * find_dots(From from,ForwardList<NameNode> name_list,ulen dots_count);
   Rec * find_rel(From from,ForwardList<NameNode> name_list);
   
   Rec * find(From from,NameRef *name_ref);
   
  public:
   
   NameLinkEngine(PrintBase &msg,NameId max_id);
   
   ~NameLinkEngine();
   
   bool add(AliasNode *node);
   
   bool add(ConstNode *node);
   
   bool add(StructNode *node);
   
   bool link(From from,NameRef *name_ref,ConstNode * &node);
   
   bool link(From from,NameRef *name_ref,AliasNode * &alias_node,StructNode * &struct_node);
   
   bool link(From from,NameRef *name_ref,AliasNode * &node);
 };

/* struct RefBase */

struct RefBase : NoCopy
 {
  RefBase *prev;
  
  typedef bool (RefBase::*LinkFunc)(NameLinkEngine &engine);
  
  LinkFunc link_func;
  
  void addTo(RefList &list);
  
  template <class T>
  void init_ref(T *,RefList &list)
   {
    link_func=static_cast<LinkFunc>(&T::do_link);
    
    addTo(list);
   }
  
  bool link(NameLinkEngine &engine)
   {
    return (this->*link_func)(engine);
   }
 };

/* class RefList */ 

class RefList : NoCopy
 {
   BaseList<RefBase> list;
  
  public:
   
   RefList() { reset(); }
   
   void reset() { list.init(); }
   
   void add(RefBase *ptr) { list.add(ptr); }
   
   bool link(NameLinkEngine &engine);
 };

/* struct DomainBase */

struct DomainBase : NoCopy
 {
  DomainBase *prev;
 };

/* class DomainList */

class DomainList : NoCopy
 {
   BaseList<DomainBase> list;
   
  private: 
 
   struct SetTypeSwitch;
  
  public: 
   
   DomainList() { reset(); }
   
   void reset() { list.init(); }
   
   void add(DomainBase *base) { list.add(base); }
   
   bool setTypes(PrintBase &msg); 
 };

/* class ExprList */

class ExprList : NoCopy
 {
   ForwardList<ExprNode> list;
   BaseList<ExprNode> rev_list;
   
  private: 
   
   struct SetTypesSwitch;
   
  public:
  
   ExprList();
   
   void reset();
   
   void add(ExprNode *node);
   
   bool setTypes();
   
   const ForwardList<ExprNode> & getList() const { return list; }
   
   const BaseList<ExprNode> & getRevList() const { return rev_list; }
 };

/* struct Context */

struct Context : NoCopy
 {
  ulen mem_cap;
  ElementPool pool;
  PrintBase &msg;
  
  NameIdEngine id_engine;
  
  RefList ref_list;
  DomainList domain_list;  
  ExprList expr_list;
  
  // methods
  
  struct SetTypeSwitch;
  
  bool setAliasTypes(BodyNode *body);
  
  struct Loop1Switch;
  
  bool checkLoop1(BodyNode *body);
  
  struct Loop2Switch;
  
  bool checkLoop2(BodyNode *body);
  
  // constructors
  
  explicit Context(PrintBase &msg_,ulen mem_cap_=MaxULen);
  
  ~Context() {}
  
  // methods
  
  void reset();
  
  bool complete(BodyNode *body);
 };

/* struct ExtContext */

struct ExtContext
 {
  FileId *file_id;
  Context *ctx;
  
  ExtContext(FileId *file_id_,Context *ctx_) : file_id(file_id_),ctx(ctx_) {}
  
  operator FileId * () const { return file_id; }
  
  Context * operator -> () const { return ctx; }
 };

/* struct NameNode */

struct NameNode : NoCopy
 {
  NameNode *next;
  
  NameLink name;
  
  void init(ExtContext ctx,const Token &token)
   {
    name.init(ctx,token);
   }
 };

/* struct NameRef */

struct NameRef : NoCopy
 {
  enum Type
   {
    Type_rel,
    Type_abs,
    Type_this,
    Type_dots
   };
  
  Type type;
  ForwardList<NameNode> name_list;
  ulen dots_count;
  
  void init(Type type_,const ForwardList<NameNode> &name_list_)
   {
    type=type_;
    name_list=name_list_;
    dots_count=0;
   }
  
  void init_dots(const ForwardList<NameNode> &name_list_,const Token &dots)
   {
    type=Type_dots;
    name_list=name_list_;
    dots_count=dots.str.len;
   }
  
  const PosName & posName() const { return name_list.last->name.name; }
  
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
  
  NameLink name;
  BodyNode *body;
  
  void init(ExtContext ctx,const Token &token,BodyNode *body);
  
  void setParent(ScopeNode *parent_)
   {
    parent=parent_;
   }
 };

/* struct FieldNode */

struct FieldNode : NoCopy
 {
  FieldNode *next;
  
  NameLink name;
  TypeNode *type_node;
  ExprNode *expr_node;
  
  TreeLink<FieldNode,NameId> link;
  
  void init(ExtContext ctx,const Token &token,TypeNode *type_node);
  
  void init(ExtContext ctx,const Token &token,TypeNode *type_node,ExprNode *expr_node);
  
  void setScope(From from);
  
  ulen index;       // for user purpose
  ulen field_index; // for user purpose
  bool flag;        // for user purpose
 };

/* struct NodeBase<T> */

template <class T> 
struct NodeBase : NoCopy
 {
  T *prev;
  
  ScopeNode *parent;
  ulen depth;
  
  NameLink name;
  
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
 };

/* struct AliasNode */

struct AliasNode : NodeBase<AliasNode>
 {
  TypeNode *type_node;
  
  TypeNode *result_type; // don't point to TypeNode_ref with another alias
  
  void init(ExtContext ctx,const Token &token,TypeNode *type_node);
  
  void setScope();
  
  ulen index; // for user purpose
 };

/* struct ConstNode */

struct ConstNode : NodeBase<ConstNode>
 {
  TypeNode *type_node;
  ExprNode *expr_node;
  
  void init(ExtContext ctx,const Token &token,TypeNode *type_node,ExprNode *expr_node);
  
  void setScope();
  
  ulen index; // for user purpose
 };

/* class FieldMap */

class FieldMap : NoCopy
 {
   typedef TreeLink<FieldNode,NameId>::RadixAlgo<&FieldNode::link> Algo;
  
   Algo::Root root;
   bool ok;
   
  private: 
  
   void add(PrintBase &msg,NameId max_id,FieldNode *node);
   
  public: 
  
   FieldMap(PrintBase &msg,NameId max_id,StructNode *node);

   bool operator ! () const { return !ok; }
  
   FieldNode * find(NameLink &name) { return root.find(name.name_id); }
 };

/* struct StructNode */

struct StructNode : NodeBase<StructNode>
 {
  ScopeNode scope_node;
  ForwardList<FieldNode> field_list;
  FieldMap *field_map;
  
  void init(ExtContext ctx,const Token &token,SBodyNode *sbody);
  
  bool setMap(Context *ctx,NameId max_id);
  
  void setScope();
  
  FieldNode * find(NameLink &name) { return field_map->find(name); }
  
  StructNode *back;
  FieldNode *cur;
  
  ulen index; // for user purpose
 };

/* struct LenNode */

struct LenNode : NoCopy
 {
  LenNode *prev;
  
  FileId *file_id;
  TextPos pos;
  ExprNode *expr_node;
  
  void init(ExtContext ctx,ExprNode *expr_node,const Token &token); // token is [
  
  template <class P>
  void print(P &out) const
   {
    Putobj(out,PrintPos(file_id,pos));
   }
  
  ulen index; // for user purpose
 };

/* struct BodyNode */

struct BodyNode
 {
  BegList<AliasNode> alias_list;
  BegList<ConstNode> const_list;
  BegList<StructNode> struct_list;
  
  BegList<ScopeNode> scope_list; // level 1
  
  BegList<LenNode> len_list;
  
  void start()
   {
    alias_list.init();
    const_list.init();
    struct_list.init();
    
    scope_list.init();
    len_list.init();
   }
  
  void add(AliasNode *node);
  
  void add(ConstNode *node);
  
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
  
  void add(TypeNode *node);
  
  void foldin(ScopeNode *scope);
  
  bool addTo(NameLinkEngine &engine);
  
  bool setMap(Context *ctx,NameId max_id);
  
  void setScope();
 };

/* struct SBodyNode */

struct SBodyNode
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
  
  void add(FieldNode *node); 
 };

/* struct TypeNode */

struct TypeNode : NoCopy
 {
  typedef void (TypeNode::*DispatchFunc)(TypeSwitch &ts);
  
  DispatchFunc dispatch_func;
  
  StructNode *base_struct;
  BegList<LenNode> len_list;
  RingNode<From> *from_ring;
  
  template <class T>
  void init_base(T *)
   {
    dispatch_func=static_cast<DispatchFunc>(&T::do_dispatch);
    
    base_struct=0;
    len_list.init();
    from_ring=0;
   }
  
  template <class T>
  void init_base(T *,TypeNode *type_node)
   {
    dispatch_func=static_cast<DispatchFunc>(&T::do_dispatch);
    
    base_struct=type_node->base_struct;
    len_list=type_node->len_list;
    from_ring=type_node->from_ring;
   }
  
  template <class T>
  void init_base(T *,TypeNode *type_node,RingNode<From> *ring,LenNode *len_node)
   {
    dispatch_func=static_cast<DispatchFunc>(&T::do_dispatch);
    
    base_struct=type_node->base_struct;
    len_list=type_node->len_list;
    from_ring=RingJoin(type_node->from_ring,ring);
    
    len_list.add(len_node);
   }
  
  template <class T>
  void init_base(T *,StructNode *struct_node)
   {
    dispatch_func=static_cast<DispatchFunc>(&T::do_dispatch);
    
    base_struct=struct_node;
    len_list.init();
    from_ring=0;
   }
  
  template <class T>
  void init_base(T *,RingNode<From> *ring)
   {
    dispatch_func=static_cast<DispatchFunc>(&T::do_dispatch);
    
    base_struct=0;
    len_list.init();
    from_ring=ring;
   }
  
  void setScope(From from)
   {
    SetScope(from_ring,from);
   }
  
  void dispatch(TypeSwitch &ts);
  
  ulen index; // for user purpose
 };

/* struct TypeNode_suint<SUInt> */

template <class SUInt>
struct TypeNode_suint : TypeNode
 {
  void do_dispatch(TypeSwitch &ts);
  
  void init()
   {
    init_base(this);
   }
 };

/* struct TypeNode_text */

struct TypeNode_text : TypeNode
 {
  void do_dispatch(TypeSwitch &ts);
  
  void init()
   {
    init_base(this);
   }
 };

/* struct TypeNode_ip */

struct TypeNode_ip : TypeNode
 {
  void do_dispatch(TypeSwitch &ts);
  
  void init()
   {
    init_base(this);
   }
 };

/* struct TypeNode_ptr */

struct TypeNode_ptr : TypeNode
 {
  TypeNode *type_node;
  
  void do_dispatch(TypeSwitch &ts);
  
  void init(TypeNode *type_node_)
   {
    init_base(this,type_node_);
    
    type_node=type_node_;
   }
 };

/* struct TypeNode_array */

struct TypeNode_array : TypeNode
 {
  TypeNode *type_node;
  
  void do_dispatch(TypeSwitch &ts);
  
  void init(TypeNode *type_node_)
   {
    init_base(this,type_node_);
    
    type_node=type_node_;
   }
 };

/* struct TypeNode_array_len */

struct TypeNode_array_len : TypeNode
 {
  TypeNode *type_node;
  
  LenNode len_node;
  
  void do_dispatch(TypeSwitch &ts);
  
  void init(ExtContext ctx,TypeNode *type_node,ExprNode *expr_node,const Token &token); // token is [
 };

/* struct TypeNode_struct */

struct TypeNode_struct : TypeNode
 {
  void do_dispatch(TypeSwitch &ts);
  
  void init(StructNode *struct_node)
   {
    init_base(this,struct_node);
   }
 };

/* struct TypeNode_ref */

struct TypeNode_ref : TypeNode , RefBase
 {
  NameRef *name;
  AliasNode *alias_node;
  StructNode *struct_node;
  
  RingNode<From> from_node;
  
  bool do_link(NameLinkEngine &engine)
   {
    return engine.link(from_node.obj,name,alias_node,struct_node);
   }
  
  void do_dispatch(TypeSwitch &ts);
  
  void init(ExtContext ctx,NameRef *name_)
   {
    init_base(this,&from_node);
    init_ref(this,ctx->ref_list);
    
    name=name_;
    alias_node=0;
    struct_node=0;
   }
 };

/* struct TypeSwitch */

struct TypeSwitch : NoCopy
 {
  void (TypeSwitch::*case_sint8)(TypeNode_suint<imp_sint8> *node);
  void (TypeSwitch::*case_uint8)(TypeNode_suint<imp_uint8> *node);
   
  void (TypeSwitch::*case_sint16)(TypeNode_suint<imp_sint16> *node);
  void (TypeSwitch::*case_uint16)(TypeNode_suint<imp_uint16> *node);
  
  void (TypeSwitch::*case_sint32)(TypeNode_suint<imp_sint32> *node);
  void (TypeSwitch::*case_uint32)(TypeNode_suint<imp_uint32> *node);
  
  void (TypeSwitch::*case_sint64)(TypeNode_suint<imp_sint64> *node);
  void (TypeSwitch::*case_uint64)(TypeNode_suint<imp_uint64> *node);
  
  void (TypeSwitch::*case_text)(TypeNode_text *node);
  void (TypeSwitch::*case_ip)(TypeNode_ip *node);
  
  void (TypeSwitch::*case_ptr)(TypeNode_ptr *node);
  void (TypeSwitch::*case_array)(TypeNode_array *node);
  void (TypeSwitch::*case_array_len)(TypeNode_array_len *node);
  void (TypeSwitch::*case_struct)(TypeNode_struct *node);
  
  void (TypeSwitch::*case_ref)(TypeNode_ref *node);
  
  template <class T>
  explicit TypeSwitch(T *)
   {
    case_sint8=static_cast<void (TypeSwitch::*)(TypeNode_suint<imp_sint8> *)>(&T::do_sint8);
    case_uint8=static_cast<void (TypeSwitch::*)(TypeNode_suint<imp_uint8> *)>(&T::do_uint8);
    
    case_sint16=static_cast<void (TypeSwitch::*)(TypeNode_suint<imp_sint16> *)>(&T::do_sint16);
    case_uint16=static_cast<void (TypeSwitch::*)(TypeNode_suint<imp_uint16> *)>(&T::do_uint16);
    
    case_sint32=static_cast<void (TypeSwitch::*)(TypeNode_suint<imp_sint32> *)>(&T::do_sint32);
    case_uint32=static_cast<void (TypeSwitch::*)(TypeNode_suint<imp_uint32> *)>(&T::do_uint32);
    
    case_sint64=static_cast<void (TypeSwitch::*)(TypeNode_suint<imp_sint64> *)>(&T::do_sint64);
    case_uint64=static_cast<void (TypeSwitch::*)(TypeNode_suint<imp_uint64> *)>(&T::do_uint64);
    
    case_text=static_cast<void (TypeSwitch::*)(TypeNode_text *)>(&T::do_text);
    case_ip=static_cast<void (TypeSwitch::*)(TypeNode_ip *)>(&T::do_ip);
    
    case_ptr=static_cast<void (TypeSwitch::*)(TypeNode_ptr *)>(&T::do_ptr);
    case_array=static_cast<void (TypeSwitch::*)(TypeNode_array *)>(&T::do_array);
    case_array_len=static_cast<void (TypeSwitch::*)(TypeNode_array_len *)>(&T::do_array_len);
    case_struct=static_cast<void (TypeSwitch::*)(TypeNode_struct *)>(&T::do_struct);
    
    case_ref=static_cast<void (TypeSwitch::*)(TypeNode_ref *)>(&T::do_ref);
   }
  
  void dispatch_suint(TypeNode_suint<imp_sint8> *node) { (this->*case_sint8)(node); }
  void dispatch_suint(TypeNode_suint<imp_uint8> *node) { (this->*case_uint8)(node); }
  
  void dispatch_suint(TypeNode_suint<imp_sint16> *node) { (this->*case_sint16)(node); }
  void dispatch_suint(TypeNode_suint<imp_uint16> *node) { (this->*case_uint16)(node); }
  
  void dispatch_suint(TypeNode_suint<imp_sint32> *node) { (this->*case_sint32)(node); }
  void dispatch_suint(TypeNode_suint<imp_uint32> *node) { (this->*case_uint32)(node); }
  
  void dispatch_suint(TypeNode_suint<imp_sint64> *node) { (this->*case_sint64)(node); }
  void dispatch_suint(TypeNode_suint<imp_uint64> *node) { (this->*case_uint64)(node); }
  
  void dispatch_text(TypeNode_text *node) { (this->*case_text)(node); }
  void dispatch_ip(TypeNode_ip *node) { (this->*case_ip)(node); }
  
  void dispatch_ptr(TypeNode_ptr *node) { (this->*case_ptr)(node); }
  void dispatch_array(TypeNode_array *node) { (this->*case_array)(node); }
  void dispatch_array_len(TypeNode_array_len *node) { (this->*case_array_len)(node); }
  void dispatch_struct(TypeNode_struct *node) { (this->*case_struct)(node); }
  
  void dispatch_ref(TypeNode_ref *node) { (this->*case_ref)(node); }
 };

#if 0

void do_sint8(TypeNode_suint<imp_sint8> *) {}
void do_uint8(TypeNode_suint<imp_uint8> *) {}

void do_sint16(TypeNode_suint<imp_sint16> *) {}
void do_uint16(TypeNode_suint<imp_uint16> *) {}

void do_sint32(TypeNode_suint<imp_sint32> *) {}
void do_uint32(TypeNode_suint<imp_uint32> *) {}

void do_sint64(TypeNode_suint<imp_sint64> *) {}
void do_uint64(TypeNode_suint<imp_uint64> *) {}

void do_text(TypeNode_text *) {}
void do_ip(TypeNode_ip *) {}

void do_ptr(TypeNode_ptr *) {}
void do_array(TypeNode_array *) {}
void do_array_len(TypeNode_array_len *) {}
void do_struct(TypeNode_struct *) {}

void do_ref(TypeNode_ref *) {}

#endif

/* class FindFieldType */

class FindFieldType : NoCopy
 {
  private:
  
   struct StructNodeSwitch : TypeSwitch
    {
     StructNode *struct_node;
     
     StructNodeSwitch() : TypeSwitch(this) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { struct_node=0; }
     void do_uint8(TypeNode_suint<imp_uint8> *) { struct_node=0; }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { struct_node=0; }
     void do_uint16(TypeNode_suint<imp_uint16> *) { struct_node=0; }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { struct_node=0; }
     void do_uint32(TypeNode_suint<imp_uint32> *) { struct_node=0; }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { struct_node=0; }
     void do_uint64(TypeNode_suint<imp_uint64> *) { struct_node=0; }
     
     void do_text(TypeNode_text *) { struct_node=0; }
     void do_ip(TypeNode_ip *) { struct_node=0; }
     
     void do_ptr(TypeNode_ptr *) { struct_node=0; }
     void do_array(TypeNode_array *) { struct_node=0; }
     void do_array_len(TypeNode_array_len *) { struct_node=0; }
     
     void do_struct(TypeNode_struct *node) { struct_node=node->base_struct; }
     
     void do_ref(TypeNode_ref *node)
      {
       if( AliasNode *alias=node->alias_node )
         {
          alias->result_type->dispatch(*this);
         }
       else
         {
          struct_node=node->struct_node;
         }
      }
    };

  private:
   
   StructNodeSwitch ts;

  public:
   
   FindFieldType() {}
   
   StructNode * structType(TypeNode *type)
    {
     type->dispatch(ts);
     
     return ts.struct_node;
    }
   
   FieldNode * field(TypeNode *type,NameLink &name)
    {
     if( StructNode *node=structType(type) )
       {
        if( FieldNode *field=node->find(name) ) return field;
       }
     
     return 0;
    }
   
   TypeNode * fieldType(TypeNode *type,NameLink &name)
    {
     if( StructNode *node=structType(type) )
       {
        if( FieldNode *field=node->find(name) )
          {
           return field->type_node;
          }
       }
     
     return 0;
    }
 };

/* class TypeCompare */

class TypeCompare : NoCopy
 {
   enum TypeClass
    {
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
     
     Type_struct,
     Type_ptr,
     Type_array,
     Type_array_len
    };
  
   struct TypeInfoSwitch : TypeSwitch
    {
     TypeClass tc;
     StructNode *struct_node;
     TypeNode *type_node;
     LenNode *len_node;
     
     TypeInfoSwitch() : TypeSwitch(this) {}
     
     void do_sint8(TypeNode_suint<imp_sint8> *) { tc=Type_sint8; }
     void do_uint8(TypeNode_suint<imp_uint8> *) { tc=Type_uint8; }
     
     void do_sint16(TypeNode_suint<imp_sint16> *) { tc=Type_sint16; }
     void do_uint16(TypeNode_suint<imp_uint16> *) { tc=Type_uint16; }
     
     void do_sint32(TypeNode_suint<imp_sint32> *) { tc=Type_sint32; }
     void do_uint32(TypeNode_suint<imp_uint32> *) { tc=Type_uint32; }
     
     void do_sint64(TypeNode_suint<imp_sint64> *) { tc=Type_sint64; }
     void do_uint64(TypeNode_suint<imp_uint64> *) { tc=Type_uint64; }
     
     void do_text(TypeNode_text *) { tc=Type_text; }
     void do_ip(TypeNode_ip *) { tc=Type_ip; }
     
     void do_struct(StructNode *node) { tc=Type_struct; struct_node=node; }
     
     void do_struct(TypeNode_struct *node) { do_struct(node->base_struct); }
     
     void do_ptr(TypeNode_ptr *node) { tc=Type_ptr; type_node=node->type_node; }
     void do_array(TypeNode_array *node) { tc=Type_array; type_node=node->type_node; }
     void do_array_len(TypeNode_array_len *node) { tc=Type_array_len; type_node=node->type_node; len_node=&node->len_node; }
     
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
   
  private: 
  
   TypeInfoSwitch ts1;
   TypeInfoSwitch ts2;
   
  public:
   
   TypeCompare() {}
   
   enum Result
    {
     Same,
     NotSame,
     Continue
    };
   
   Result operator () (TypeNode *type1,TypeNode *type2);
   
   TypeNode *type1;
   TypeNode *type2;
   LenNode *len1;
   LenNode *len2;
 };

/* struct DomainTypeNode */

struct DomainTypeNode : RefBase , DomainBase
 {
  TypeNode *type_node;
  NameRef *name;
  AliasNode *alias_node;
  RingNode<From> from_node;
  RingNode<From> *from_ring;
  
  bool do_link(NameLinkEngine &engine)
   {
    return engine.link(from_node.obj,name,alias_node);
   }
  
  void init(TypeNode *type_node_)
   {
    type_node=type_node_;
    name=0;
    alias_node=0;
    from_ring=0;
   }
  
  void init(ExtContext ctx,NameRef *name_)
   {
    init_ref(this,ctx->ref_list);
    
    ctx->domain_list.add(this);
    
    type_node=0;
    name=name_;
    alias_node=0;
    from_ring=&from_node;
   }
 };

/* struct NonameExprNode */

struct NonameExprNode : NoCopy
 {
  NonameExprNode *next;
  
  ExprNode *expr_node;
  
  void init(ExprNode *expr_node_)
   {
    expr_node=expr_node_;
   }
 };

/* struct NamedExprNode */

struct NamedExprNode : NoCopy
 {
  NamedExprNode *prev;

  NameLink name;
  ExprNode *expr_node;
  
  void init(ExtContext ctx,const Token &token,ExprNode *expr_node_)
   {
    name.init(ctx,token);
    
    expr_node=expr_node_;
   }
 };

/* struct ExprNode */

struct ExprNode : NoCopy
 {
  ExprNode *next;
  ExprNode *prev;
  
  typedef void (ExprNode::*DispatchFunc)(ExprSwitch &es);
  
  DispatchFunc dispatch_func;
  
  PosName ops;
  RingNode<From> *from_ring;
  
  TypeNode *ptrto_type;
  TypeNode *LV_type;
  
  template <class T>
  void init_base(T *,ExtContext ctx,const Token &ops_,RingNode<From> *from_ring_=0)
   {
    ops.init(ctx,ops_);
    
    dispatch_func=static_cast<DispatchFunc>(&T::do_dispatch);
    from_ring=from_ring_;
    
    ctx->expr_list.add(this);
    
    ptrto_type=0;
    LV_type=0;
   }
  
  template <class T>
  void init_base(T *,ExtContext ctx,const PosName &ops_,RingNode<From> *from_ring_=0)
   {
    ops=ops_;
    
    dispatch_func=static_cast<DispatchFunc>(&T::do_dispatch);
    from_ring=from_ring_;
    
    ctx->expr_list.add(this);
    
    ptrto_type=0;
    LV_type=0;
   }
  
  void setScope(From from)
   {
    SetScope(from_ring,from);
   }
  
  void dispatch(ExprSwitch &es);
  
  StepId step_id;     // for user purpose
  TypeNode *ret_type; // for user purpose
 };

/* struct ExprNode_add */

struct ExprNode_add : ExprNode
 {
  ExprNode *arg1;
  ExprNode *arg2;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg1_,ExprNode *arg2_)
   {
    init_base(this,ctx,ops,RingJoin(arg1_->from_ring,arg2_->from_ring));
    
    arg1=arg1_;
    arg2=arg2_;
   }
 };

/* struct ExprNode_sub */

struct ExprNode_sub : ExprNode
 {
  ExprNode *arg1;
  ExprNode *arg2;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg1_,ExprNode *arg2_)
   {
    init_base(this,ctx,ops,RingJoin(arg1_->from_ring,arg2_->from_ring));
    
    arg1=arg1_;
    arg2=arg2_;
   }
 };

/* struct ExprNode_mul */

struct ExprNode_mul : ExprNode
 {
  ExprNode *arg1;
  ExprNode *arg2;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg1_,ExprNode *arg2_)
   {
    init_base(this,ctx,ops,RingJoin(arg1_->from_ring,arg2_->from_ring));
    
    arg1=arg1_;
    arg2=arg2_;
   }
 };

/* struct ExprNode_div */

struct ExprNode_div : ExprNode
 {
  ExprNode *arg1;
  ExprNode *arg2;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg1_,ExprNode *arg2_)
   {
    init_base(this,ctx,ops,RingJoin(arg1_->from_ring,arg2_->from_ring));
    
    arg1=arg1_;
    arg2=arg2_;
   }
 };

/* struct ExprNode_rem */

struct ExprNode_rem : ExprNode
 {
  ExprNode *arg1;
  ExprNode *arg2;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg1_,ExprNode *arg2_)
   {
    init_base(this,ctx,ops,RingJoin(arg1_->from_ring,arg2_->from_ring));
    
    arg1=arg1_;
    arg2=arg2_;
   }
 };

/* struct ExprNode_deref */

struct ExprNode_deref : ExprNode
 {
  ExprNode *arg;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg_)
   {
    init_base(this,ctx,ops,arg_->from_ring);
    
    arg=arg_;
   }
 };

/* struct ExprNode_address */

struct ExprNode_address : ExprNode
 {
  ExprNode *arg;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg_)
   {
    init_base(this,ctx,ops,arg_->from_ring);
    
    arg=arg_;
   }
 };

/* struct ExprNode_plus */

struct ExprNode_plus : ExprNode
 {
  ExprNode *arg;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg_)
   {
    init_base(this,ctx,ops,arg_->from_ring);
    
    arg=arg_;
   }
 };

/* struct ExprNode_minus */

struct ExprNode_minus : ExprNode
 {
  ExprNode *arg;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg_)
   {
    init_base(this,ctx,ops,arg_->from_ring);
    
    arg=arg_;
   }
 };

/* struct ExprNode_number */

struct ExprNode_number : ExprNode
 {
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &token) // token is number
   {
    init_base(this,ctx,token);
   }
 };

/* struct ExprNode_ptr_select */

struct ExprNode_ptr_select : ExprNode
 {
  ExprNode *arg;
  
  NameLink name;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg_,const Token &token)
   {
    init_base(this,ctx,ops,arg_->from_ring);
    
    arg=arg_;
    
    name.init(ctx,token);
   }
 };

/* struct ExprNode_select */

struct ExprNode_select : ExprNode
 {
  ExprNode *arg;
  
  NameLink name;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg_,const Token &token)
   {
    init_base(this,ctx,ops,arg_->from_ring);
    
    arg=arg_;

    name.init(ctx,token);
   }
 };

/* struct ExprNode_ind */

struct ExprNode_ind : ExprNode
 {
  ExprNode *arg1;
  ExprNode *arg2;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg1_,ExprNode *arg2_)
   {
    init_base(this,ctx,ops,RingJoin(arg1_->from_ring,arg2_->from_ring));
    
    arg1=arg1_;
    arg2=arg2_;
   }
 };

/* struct ExprNode_domain */

struct ExprNode_domain : ExprNode
 {
  ExprNode *arg;
  DomainTypeNode *domain_node;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg_,DomainTypeNode *domain_node_)
   {
    init_base(this,ctx,ops,RingJoin(arg_->from_ring,domain_node_->from_ring));
    
    arg=arg_;
    domain_node=domain_node_;
   }
 };

/* struct ExprNode_var */

struct ExprNode_var : ExprNode , RefBase
 {
  NameRef *name;
  ConstNode *node;
  RingNode<From> from_node;
  
  bool do_link(NameLinkEngine &engine)
   {
    return engine.link(from_node.obj,name,node);
   }
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,NameRef *name_)
   {
    init_base(this,ctx,name_->posName(),&from_node);
    init_ref(this,ctx->ref_list);
    
    name=name_;
    node=0;
   }
 };

/* struct ExprNode_null */

struct ExprNode_null : ExprNode
 {
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &token) // token is null
   {
    init_base(this,ctx,token);
   }
 };

/* struct ExprNode_string */

struct ExprNode_string : ExprNode
 {
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &token) // token is string
   {
    init_base(this,ctx,token);
   }
 };

/* struct ExprNode_ip */

struct ExprNode_ip : ExprNode
 {
  Token token1;
  Token token2;
  Token token3;
  Token token4;
  
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &token1_,const Token &token2_,const Token &token3_,const Token &token4_)
   {
    init_base(this,ctx,token1_);
    
    token1=token1_;
    token2=token2_;
    token3=token3_;
    token4=token4_;
   }
 };

/* struct ExprNode_noname_list */

struct ExprNode_noname_list : ExprNode
 {
  ForwardList<NonameExprNode> list;
 
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops)
   {
    init_base(this,ctx,ops);
    
    list.init();
   }
  
  void init(ExtContext ctx,const Token &ops,const ForwardList<NonameExprNode> &list_)
   {
    RingNode<From> *ring=0;
    
    for(NonameExprNode &node : list_ ) ring=RingJoin(ring,node.expr_node->from_ring);
    
    init_base(this,ctx,ops,ring);
    
    list=list_;
   }
 };

/* struct ExprNode_named_list */

struct ExprNode_named_list : ExprNode
 {
  BegList<NamedExprNode> list;
 
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,const BegList<NamedExprNode> &list_)
   {
    RingNode<From> *ring=0;
    
    for(NamedExprNode &node : list_ ) ring=RingJoin(ring,node.expr_node->from_ring);
    
    init_base(this,ctx,ops,ring);
    
    list=list_;
   }
 };

/* struct ExprNode_apply_named_list */

struct ExprNode_apply_named_list : ExprNode
 {
  ExprNode *arg;
  BegList<NamedExprNode> list;
 
  void do_dispatch(ExprSwitch &es);
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg_)
   {
    init_base(this,ctx,ops,arg_->from_ring);
    
    arg=arg_;
    
    list.init();
   }
  
  void init(ExtContext ctx,const Token &ops,ExprNode *arg_,const BegList<NamedExprNode> &list_)
   {
    RingNode<From> *ring=arg_->from_ring;
    
    for(NamedExprNode &node : list_ ) ring=RingJoin(ring,node.expr_node->from_ring);
    
    init_base(this,ctx,ops,ring);
    
    arg=arg_;
    
    list=list_;
   }
 };

/* struct ExprSwitch */

struct ExprSwitch : NoCopy
 {
  void (ExprSwitch::*case_add)(ExprNode_add *node);
  void (ExprSwitch::*case_sub)(ExprNode_sub *node);
  void (ExprSwitch::*case_mul)(ExprNode_mul *node);
  void (ExprSwitch::*case_div)(ExprNode_div *node);
  void (ExprSwitch::*case_rem)(ExprNode_rem *node);
  void (ExprSwitch::*case_deref)(ExprNode_deref *node);
  void (ExprSwitch::*case_address)(ExprNode_address *node);
  void (ExprSwitch::*case_plus)(ExprNode_plus *node);
  void (ExprSwitch::*case_minus)(ExprNode_minus *node);
  void (ExprSwitch::*case_number)(ExprNode_number *node);
  void (ExprSwitch::*case_ptr_select)(ExprNode_ptr_select *node);
  void (ExprSwitch::*case_select)(ExprNode_select *node);
  void (ExprSwitch::*case_ind)(ExprNode_ind *node);
  void (ExprSwitch::*case_domain)(ExprNode_domain *node);
  void (ExprSwitch::*case_var)(ExprNode_var *node);
  void (ExprSwitch::*case_null)(ExprNode_null *node);
  void (ExprSwitch::*case_string)(ExprNode_string *node);
  void (ExprSwitch::*case_ip)(ExprNode_ip *node);
  void (ExprSwitch::*case_noname_list)(ExprNode_noname_list *node);
  void (ExprSwitch::*case_named_list)(ExprNode_named_list *node);
  void (ExprSwitch::*case_apply_named_list)(ExprNode_apply_named_list *node);
  
  template <class T>
  explicit ExprSwitch(T *)
   {
    case_add=static_cast<void (ExprSwitch::*)(ExprNode_add *)>(&T::do_add);
    case_sub=static_cast<void (ExprSwitch::*)(ExprNode_sub *)>(&T::do_sub);
    case_mul=static_cast<void (ExprSwitch::*)(ExprNode_mul *)>(&T::do_mul);
    case_div=static_cast<void (ExprSwitch::*)(ExprNode_div *)>(&T::do_div);
    case_rem=static_cast<void (ExprSwitch::*)(ExprNode_rem *)>(&T::do_rem);
    case_deref=static_cast<void (ExprSwitch::*)(ExprNode_deref *)>(&T::do_deref);
    case_address=static_cast<void (ExprSwitch::*)(ExprNode_address *)>(&T::do_address);
    case_plus=static_cast<void (ExprSwitch::*)(ExprNode_plus *)>(&T::do_plus);
    case_minus=static_cast<void (ExprSwitch::*)(ExprNode_minus *)>(&T::do_minus);
    case_number=static_cast<void (ExprSwitch::*)(ExprNode_number *)>(&T::do_number);
    case_ptr_select=static_cast<void (ExprSwitch::*)(ExprNode_ptr_select *)>(&T::do_ptr_select);
    case_select=static_cast<void (ExprSwitch::*)(ExprNode_select *)>(&T::do_select);
    case_ind=static_cast<void (ExprSwitch::*)(ExprNode_ind *)>(&T::do_ind);
    case_domain=static_cast<void (ExprSwitch::*)(ExprNode_domain *)>(&T::do_domain);
    case_var=static_cast<void (ExprSwitch::*)(ExprNode_var *)>(&T::do_var);
    case_null=static_cast<void (ExprSwitch::*)(ExprNode_null *)>(&T::do_null);
    case_string=static_cast<void (ExprSwitch::*)(ExprNode_string *)>(&T::do_string);
    case_ip=static_cast<void (ExprSwitch::*)(ExprNode_ip *)>(&T::do_ip);
    case_noname_list=static_cast<void (ExprSwitch::*)(ExprNode_noname_list *)>(&T::do_noname_list);
    case_named_list=static_cast<void (ExprSwitch::*)(ExprNode_named_list *)>(&T::do_named_list);
    case_apply_named_list=static_cast<void (ExprSwitch::*)(ExprNode_apply_named_list *)>(&T::do_apply_named_list);
   }
  
  void dispatch_add(ExprNode_add *node) { (this->*case_add)(node); }
  void dispatch_sub(ExprNode_sub *node) { (this->*case_sub)(node); }
  void dispatch_mul(ExprNode_mul *node) { (this->*case_mul)(node); }
  void dispatch_div(ExprNode_div *node) { (this->*case_div)(node); }
  void dispatch_rem(ExprNode_rem *node) { (this->*case_rem)(node); }
  void dispatch_deref(ExprNode_deref *node) { (this->*case_deref)(node); }
  void dispatch_address(ExprNode_address *node) { (this->*case_address)(node); }
  void dispatch_plus(ExprNode_plus *node) { (this->*case_plus)(node); }
  void dispatch_minus(ExprNode_minus *node) { (this->*case_minus)(node); }
  void dispatch_number(ExprNode_number *node) { (this->*case_number)(node); }
  void dispatch_ptr_select(ExprNode_ptr_select *node) { (this->*case_ptr_select)(node); }
  void dispatch_select(ExprNode_select *node) { (this->*case_select)(node); }
  void dispatch_ind(ExprNode_ind *node) { (this->*case_ind)(node); }
  void dispatch_domain(ExprNode_domain *node) { (this->*case_domain)(node); }
  void dispatch_var(ExprNode_var *node) { (this->*case_var)(node); }
  void dispatch_null(ExprNode_null *node) { (this->*case_null)(node); }
  void dispatch_string(ExprNode_string *node) { (this->*case_string)(node); }
  void dispatch_ip(ExprNode_ip *node) { (this->*case_ip)(node); }
  void dispatch_noname_list(ExprNode_noname_list *node) { (this->*case_noname_list)(node); }
  void dispatch_named_list(ExprNode_named_list *node) { (this->*case_named_list)(node); }
  void dispatch_apply_named_list(ExprNode_apply_named_list *node) { (this->*case_apply_named_list)(node); }
 };

#if 0

void do_add(ExprNode_add *) {}
void do_sub(ExprNode_sub *) {}
void do_mul(ExprNode_mul *) {}
void do_div(ExprNode_div *) {}
void do_rem(ExprNode_rem *) {}

void do_plus(ExprNode_plus *) {}
void do_minus(ExprNode_minus *) {}

void do_domain(ExprNode_domain *) {}

void do_number(ExprNode_number *) {}
void do_string(ExprNode_string *) {}
void do_ip(ExprNode_ip *) {}

void do_address(ExprNode_address *) {}

void do_null(ExprNode_null *) {}

void do_noname_list(ExprNode_noname_list *) {}
void do_named_list(ExprNode_named_list *) {}
void do_apply_named_list(ExprNode_apply_named_list *) {}

void do_var(ExprNode_var *) {}
void do_deref(ExprNode_deref *) {}
void do_ptr_select(ExprNode_ptr_select *) {}
void do_select(ExprNode_select *) {}
void do_ind(ExprNode_ind *) {}

#endif

/* inlines */

/* struct NameLink */

inline void NameLink::init(ExtContext ctx,const Token &token)
 {
  name.init(ctx,token);
  
  name_id=0;
  
  ctx->id_engine.add(this);
 }

/* struct From */

inline From::From()
 : scope(0),
   depth(0),
   ok(false)
 {
 }

inline From::From(ScopeNode *scope_,ulen depth_)
 : scope(scope_),
   depth(depth_),
   ok(true)
 {
 }

inline bool From::back()
 {
  if( depth )
    {
     depth--;
     scope=scope->parent;
     
     return true;
    }
  
  return false;
 }

/* struct RefBase */

inline void RefBase::addTo(RefList &list)
 {
  list.add(this);
 }

/* class ExprList */

inline ExprList::ExprList() { reset(); }
   
inline void ExprList::reset() 
 { 
  list.init();
  rev_list.init();
 }
   
inline void ExprList::add(ExprNode *node) 
 { 
  list.add(node);
  rev_list.add(node);
 }
   
/* struct ScopeNode */

inline void ScopeNode::init(ExtContext ctx,const Token &token,BodyNode *body_)
 {
  parent=0;
  
  name.init(ctx,token);
  
  body=body_;
  
  body_->foldin(this);
 }

/* struct FieldNode */

inline void FieldNode::init(ExtContext ctx,const Token &token,TypeNode *type_node_)
 {
  name.init(ctx,token);
  
  type_node=type_node_;
  
  ExprNode_noname_list *node=ctx->pool.create<ExprNode_noname_list>();
  
  node->init(ctx,token);
  
  expr_node=node;
 }

inline void FieldNode::init(ExtContext ctx,const Token &token,TypeNode *type_node_,ExprNode *expr_node_)
 {
  name.init(ctx,token);
  
  type_node=type_node_;
  expr_node=expr_node_;
 }

inline void FieldNode::setScope(From from)
 {
  type_node->setScope(from);
  
  if( expr_node ) expr_node->setScope(from);
 }

/* struct AliasNode */

inline void AliasNode::init(ExtContext ctx,const Token &token,TypeNode *type_node_)
 {
  init_base(ctx,token);
  
  type_node=type_node_;
  
  result_type=0;
 }

inline void AliasNode::setScope()
 {
  From from=getFrom();
  
  type_node->setScope(from);
 }

/* struct ConstNode */

inline void ConstNode::init(ExtContext ctx,const Token &token,TypeNode *type_node_,ExprNode *expr_node_)
 {
  init_base(ctx,token);
  
  type_node=type_node_;
  expr_node=expr_node_;
 }

inline void ConstNode::setScope()
 {
  From from=getFrom();
  
  type_node->setScope(from);
  expr_node->setScope(from);
 }

/* struct StructNode */

inline void StructNode::init(ExtContext ctx,const Token &token,SBodyNode *sbody)
 {
  init_base(ctx,token);
  
  scope_node.init(ctx,token,&sbody->body_node);
  
  field_list=sbody->field_list;
  
  field_map=0;
 }

/* struct LenNode */

inline void LenNode::init(ExtContext ctx,ExprNode *expr_node_,const Token &token) 
 {
  file_id=ctx;
  pos=token.pos;
  
  expr_node=expr_node_; 
 }

/* struct BodyNode */

inline void BodyNode::add(AliasNode *node)
 {
  alias_list.add(node);
  
  add(node->type_node);
 }

inline void BodyNode::add(ConstNode *node)
 {
  const_list.add(node);
  
  add(node->type_node);
 }

inline void BodyNode::add(TypeNode *type_node)
 {
  len_list.join(type_node->len_list);
  
  if( StructNode *node=type_node->base_struct ) add(node);
 }

/* struct SBodyNode */

inline void SBodyNode::add(FieldNode *node) 
 {
  field_list.add(node);
  
  body_node.add(node->type_node);
 }
  
/* struct TypeNode */

inline void TypeNode::dispatch(TypeSwitch &ts)
 {
  (this->*dispatch_func)(ts);
 }

/* struct TypeNode_suint<SUInt> */

template <class SUInt>
void TypeNode_suint<SUInt>::do_dispatch(TypeSwitch &ts)
 {
  ts.dispatch_suint(this);
 }
  
/* struct TypeNode_text */

inline void TypeNode_text::do_dispatch(TypeSwitch &ts)
 {
  ts.dispatch_text(this);
 }
  
/* struct TypeNode_ip */

inline void TypeNode_ip::do_dispatch(TypeSwitch &ts)
 {
  ts.dispatch_ip(this);
 }

/* struct TypeNode_ptr */

inline void TypeNode_ptr::do_dispatch(TypeSwitch &ts)
 {
  ts.dispatch_ptr(this);
 }

/* struct TypeNode_array */

inline void TypeNode_array::do_dispatch(TypeSwitch &ts)
 {
  ts.dispatch_array(this);
 }

/* struct TypeNode_array_len */

inline void TypeNode_array_len::do_dispatch(TypeSwitch &ts)
 {
  ts.dispatch_array_len(this);
 }

inline void TypeNode_array_len::init(ExtContext ctx,TypeNode *type_node_,ExprNode *expr_node,const Token &token)
 {
  len_node.init(ctx,expr_node,token);
  
  init_base(this,type_node_,expr_node->from_ring,&len_node);
  
  type_node=type_node_;
 }

/* struct TypeNode_struct */

inline void TypeNode_struct::do_dispatch(TypeSwitch &ts)
 {
  ts.dispatch_struct(this);
 }

/* struct TypeNode_ref */

inline void TypeNode_ref::do_dispatch(TypeSwitch &ts)
 {
  ts.dispatch_ref(this);
 }

/* struct ExprNode */

inline void ExprNode::dispatch(ExprSwitch &es)
 {
  (this->*dispatch_func)(es);
 }

/* struct ExprNode_add */

inline void ExprNode_add::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_add(this);
 }

/* struct ExprNode_sub */

inline void ExprNode_sub::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_sub(this);
 }

/* struct ExprNode_mul */

inline void ExprNode_mul::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_mul(this);
 }

/* struct ExprNode_div */

inline void ExprNode_div::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_div(this);
 }

/* struct ExprNode_rem */

inline void ExprNode_rem::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_rem(this);
 }

/* struct ExprNode_deref */

inline void ExprNode_deref::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_deref(this);
 }

/* struct ExprNode_address */

inline void ExprNode_address::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_address(this);
 }

/* struct ExprNode_plus */

inline void ExprNode_plus::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_plus(this);
 }

/* struct ExprNode_minus */

inline void ExprNode_minus::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_minus(this);
 }

/* struct ExprNode_number */

inline void ExprNode_number::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_number(this);
 }

/* struct ExprNode_ptr_select */

inline void ExprNode_ptr_select::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_ptr_select(this);
 }

/* struct ExprNode_select */

inline void ExprNode_select::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_select(this);
 }

/* struct ExprNode_ind */

inline void ExprNode_ind::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_ind(this);
 }

/* struct ExprNode_domain */

inline void ExprNode_domain::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_domain(this);
 }

/* struct ExprNode_var */

inline void ExprNode_var::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_var(this);
 }

/* struct ExprNode_null */

inline void ExprNode_null::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_null(this);
 }

/* struct ExprNode_string */

inline void ExprNode_string::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_string(this);
 }

/* struct ExprNode_ip */

inline void ExprNode_ip::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_ip(this);
 }

/* struct ExprNode_noname_list */

inline void ExprNode_noname_list::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_noname_list(this);
 }

/* struct ExprNode_named_list */

inline void ExprNode_named_list::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_named_list(this);
 }

/* struct ExprNode_apply_named_list */

inline void ExprNode_apply_named_list::do_dispatch(ExprSwitch &es)
 {
  es.dispatch_apply_named_list(this);
 }

} // namespace DDL
} // namespace CCore
 
#endif
