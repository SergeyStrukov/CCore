/* DDLSemantic.cpp */
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

#include <CCore/inc/ddl/DDLSemantic.h>

#include <CCore/inc/Crc.h>
#include <CCore/inc/Sort.h>

namespace CCore {
namespace DDL {

/* class NameIdEngine */

struct NameIdEngine::Rec : CmpComparable<Rec>
 {
  NameLink *name;
  uint32 hash;
  
  void init(NameLink &name_)
   {
    name=&name_;
    
    Crc32 crc;
    
    crc.addRange(name_.name.token.str);
    
    hash=crc;
   }
  
  void set(NameId id)
   {
    name->name_id=id;
   }
  
  CmpResult objCmp(const Rec &obj) const
   {
    if( CmpResult ret=Cmp(hash,obj.hash) ) return ret;
    
    return StrCmp(name->name.token.str,obj.name->name.token.str);
   }
 };

NameId NameIdEngine::generate()
 {
  ulen len=list.count;
  
  if( !len ) return 1;
  
  DynArray<Rec> buf(len);
  Rec *base=buf.getPtr();
  
  {
   Rec *out=base;
   
   for(NameLink &obj : list ) { out->init(obj); out++; }
  }
  
  Sort(base,len);
  
  NameId id=1;
  
  {
   auto r=Range(base,len);
  
   for(; r.len>1 ;++r)
     {
      r->set(id);
     
      if( r[0]<r[1] ) id++;
     }
  
   r->set(id);
  }
  
  return id;
 }

/* struct From */

void SetScope(RingNode<From> *from_ring,From from)
 {
  if( from_ring )
    {
     RingNode<From> *ptr=from_ring;
     
     do
       {
        ptr->obj=from;
        
        ptr=ptr->next;
       }
     while( ptr!=from_ring );
    }
 }

/* class NameLinkEngine::Rec */

struct NameLinkEngine::Rec
 {
  enum Type
   {
    TypeAlias,
    TypeConst,
    TypeStruct, // + Map
    TypeMap
   };
  
  union Ptr
   {
    AliasNode *alias_node;
    ConstNode *const_node;
    StructNode *struct_node;
   };
  
  Type type;
  Ptr ptr;
  Map *map;
  
  TreeLink<Rec,NameId> link;
  
  // init
  
  void init(AliasNode *node) { type=TypeAlias; ptr.alias_node=node; map=0; }
  
  void init(ConstNode *node) { type=TypeConst; ptr.const_node=node; map=0; }
  
  void init(StructNode *node) { type=TypeStruct; ptr.struct_node=node; }
  
  void init(Map *map_) { type=TypeMap; map=map_; }
  
  // get
  
  bool isStruct() const { return type==TypeStruct; }
  
  bool isMap() const { return type==TypeMap; }
  
  bool get(AliasNode * &node)
   {
    if( type!=TypeAlias ) return false;
    
    node=ptr.alias_node;
    
    return true;
   }
  
  bool get(ConstNode * &node)
   {
    if( type!=TypeConst ) return false;
    
    node=ptr.const_node;
    
    return true;
   }
  
  bool get(AliasNode * &alias_node,StructNode * &struct_node)
   {
    switch( type )
      {
       case TypeAlias :
        {
         alias_node=ptr.alias_node;
         struct_node=0;
        }
       return true;
       
       case TypeStruct :
        {
         alias_node=0;
         struct_node=ptr.struct_node;
        }
       return true;
       
       default: return false;
      }
   }
  
  bool get(Map * &map_)
   {
    if( !map ) return false;
    
    map_=map;
    
    return true;
   }
  
  template <class P>
  void print(P &out) const
   {
    switch( type )
      {
       case TypeAlias : Putobj(out,ptr.alias_node->name); break;
      
       case TypeConst : Putobj(out,ptr.const_node->name); break;
      
       case TypeStruct : Putobj(out,ptr.struct_node->name); break;
      
       case TypeMap : Putobj(out,*map); break;
      }
   }
 };

/* class NameLinkEngine::Map */

class NameLinkEngine::Map : NoCopy
 {
   typedef TreeLink<Rec,NameId>::RadixAlgo<&Rec::link> Algo;
  
   Algo::Root root;
   NameLink *name;
   
  public: 
  
   explicit Map(NameLink *name_=0) : name(name_) {}
  
   Map * findOrAddMap(PrintBase &msg,ElementPool &pool,NameLink *name,NameId max_id);
  
   Rec * addRec(PrintBase &msg,ElementPool &pool,NameLink *name,NameId max_id,bool allow_map=false);
  
   Map * findMap(NameLink *name);
  
   Rec * findRec(NameLink *name);
  
   template <class P>
   void print(P &out) const
    {
     if( name ) 
       Putobj(out,*name);
     else
       Putobj(out,"<global namespace>");
    }
 };

NameLinkEngine::Map * NameLinkEngine::Map::findOrAddMap(PrintBase &msg,ElementPool &pool,NameLink *name,NameId max_id)
 {
  Algo::PrepareIns prepare(root,name->name_id,1,max_id);
  
  if( prepare.found )
    {
     Map *ret;
     
     if( prepare.found->get(ret) ) return ret;
     
     if( prepare.found->isStruct() )
       {
        Map *ret=pool.create<Map>(name);
        
        prepare.found->map=ret;

        return ret;
       }
     
     Printf(msg,"Used name : #; , \n  Founded object is : #;\n",*name,*prepare.found);
     
     return 0;
    }
  
  Map *ret=pool.create<Map>(name);
  Rec *rec=pool.create<Rec>();
  
  rec->init(ret);
  
  prepare.complete(rec);
  
  return ret;
 }

NameLinkEngine::Rec * NameLinkEngine::Map::addRec(PrintBase &msg,ElementPool &pool,NameLink *name,NameId max_id,bool allow_map)
 {
  Algo::PrepareIns prepare(root,name->name_id,1,max_id);
  
  if( prepare.found )
    {
     if( allow_map )
       {
        if( prepare.found->isMap() ) return prepare.found;
       }
     
     Printf(msg,"Used name : #; , \n  Founded object is : #;\n",*name,*prepare.found);
     
     return 0;
    }
  
  Rec *ret=pool.create<Rec>();
  
  if( allow_map ) ret->map=0;
  
  prepare.complete(ret);
  
  return ret;
 }

auto NameLinkEngine::Map::findMap(NameLink *name) -> Map *
 {
  Rec *rec=root.find(name->name_id);
  
  if( !rec ) return 0;
  
  return rec->map;
 }

auto NameLinkEngine::Map::findRec(NameLink *name) -> Rec *
 {
  return root.find(name->name_id);
 }

/* class NameLinkEngine */

void NameLinkEngine::FillBuf(NameLink **buf,ulen len,ScopeNode *ptr)
 {
  for(; len-- ;ptr=ptr->parent) 
    {
     buf[len]=&ptr->name;
    }
 }

NameLink ** NameLinkEngine::getBuf(ulen len)
 {
  ulen buf_len=buf.getLen();
  
  if( len>buf_len ) buf.extend_raw(len-buf_len);
  
  return buf.getPtr();
 }

PtrLen<NameLink *> NameLinkEngine::makePath(ulen depth,ScopeNode *ptr)
 {
  NameLink **ret=getBuf(depth);
  
  FillBuf(ret,depth,ptr);
  
  return Range(ret,depth);
 }

PtrLen<NameLink *> NameLinkEngine::makePath(From from) 
 { 
  return makePath(from.depth,from.scope); 
 }

auto NameLinkEngine::addPath(ulen depth,ScopeNode *parent,NameLink &name,bool allow_map) -> Rec *
 {
  PtrLen<NameLink *> path=makePath(depth,parent);
  
  Map *map=root;

  for(; +path ;++path)
    {
     Map *next=map->findOrAddMap(msg,pool,*path,max_id);
     
     if( !next ) return 0;
     
     map=next;
    }
  
  return map->addRec(msg,pool,&name,max_id,allow_map);
 }

auto NameLinkEngine::find(Map *map,ForwardList<NameNode> name_list) -> Rec *
 {
  NameNode *ptr=name_list.beg;
  
  if( !ptr ) // internal error
    {
     Printf(msg,"Incorrect name list\n");
     
     return 0;
    }
  
  for(; NameNode *next_ptr=ptr->next ;ptr=next_ptr)
    {
     Map *next=map->findMap(&ptr->name);
     
     if( !next ) return 0;
     
     map=next;
    }
  
  return map->findRec(&ptr->name);
 }

auto NameLinkEngine::find(PtrLen<NameLink *> path,ForwardList<NameNode> name_list) -> Rec *
 {
  Map *map=root;
  
  for(; +path ;++path)
    {
     Map *next=map->findMap(*path);
     
     if( !next ) return 0;
     
     map=next;
    }
  
  return find(map,name_list);
 }

auto NameLinkEngine::find(ForwardList<NameNode> name_list) -> Rec *
 {
  return find(root,name_list);
 }

auto NameLinkEngine::find_abs(From,ForwardList<NameNode> name_list) -> Rec *
 {
  return find(name_list);
 }

auto NameLinkEngine::find_this(From from,ForwardList<NameNode> name_list) -> Rec *
 {
  return find(makePath(from),name_list);
 }

auto NameLinkEngine::find_dots(From from,ForwardList<NameNode> name_list,ulen dots_count) -> Rec *
 {
  for(dots_count--; dots_count ;dots_count--) if( !from.back() ) return 0;
   
  return find(makePath(from),name_list);
 }

auto NameLinkEngine::find_rel(From from,ForwardList<NameNode> name_list) -> Rec *
 {
  do
    {
     if( Rec *ret=find(makePath(from),name_list) ) return ret;
    }
  while( from.back() );
  
  return 0;
 }

auto NameLinkEngine::find(From from,NameRef *name_ref) -> Rec *
 {
  if( !from ) // internal error
    {
     Printf(msg,"Scope is missed at #;\n",*name_ref);
     
     return 0;
    }

  switch( name_ref->type )
    {
     case NameRef::Type_abs    : return find_abs(from,name_ref->name_list);
     case NameRef::Type_this   : return find_this(from,name_ref->name_list);
     case NameRef::Type_dots   : return find_dots(from,name_ref->name_list,name_ref->dots_count);
     case NameRef::Type_rel    : return find_rel(from,name_ref->name_list);
    }
  
  return 0;
 }

NameLinkEngine::NameLinkEngine(PrintBase &msg_,NameId max_id_)
 : msg(msg_),
   max_id(max_id_),
   buf(100)
 {
  root=pool.create<Map>();
 }
   
NameLinkEngine::~NameLinkEngine()
 {
 }

bool NameLinkEngine::add(AliasNode *node)
 {
  Rec *rec=addPath(node->depth,node->parent,node->name);
  
  if( !rec ) return false;
  
  rec->init(node);
  
  return true;
 }

bool NameLinkEngine::add(ConstNode *node)
 {
  Rec *rec=addPath(node->depth,node->parent,node->name);
  
  if( !rec ) return false;
  
  rec->init(node);
  
  return true;
 }

bool NameLinkEngine::add(StructNode *node)
 {
  Rec *rec=addPath(node->depth,node->parent,node->name,true);
  
  if( !rec ) return false;
  
  rec->init(node);
  
  return true;
 }

bool NameLinkEngine::link(From from,NameRef *name_ref,ConstNode * &node)
 {
  Rec *rec=find(from,name_ref);
  
  if( !rec ) 
    {
     Printf(msg,"Undefined name : #;\n",*name_ref);
     
     return false;
    }
  
  if( rec->get(node) ) return true;
  
  Printf(msg,"Miskind name : #; , name of constant is expected\n  Founded object is : #;\n",*name_ref,*rec);
  
  return false;
 }

bool NameLinkEngine::link(From from,NameRef *name_ref,AliasNode * &alias_node,StructNode * &struct_node)
 {
  Rec *rec=find(from,name_ref);
  
  if( !rec )
    {
     Printf(msg,"Undefined name : #;\n",*name_ref);
    
     return false;
    }
  
  if( rec->get(alias_node,struct_node) ) return true;
  
  Printf(msg,"Miskind name : #; , name of type alias or structure is expected\n  Founded object is : #;\n",*name_ref,*rec);
  
  return false;
 }

bool NameLinkEngine::link(From from,NameRef *name_ref,AliasNode * &node)
 {
  Rec *rec=find(from,name_ref);
  
  if( !rec )
    {
     Printf(msg,"Undefined name : #;\n",*name_ref);
  
     return false;
    }
  
  if( rec->get(node) ) return true;
  
  Printf(msg,"Miskind name : #; , name of type alias is expected\n  Founded object is : #;\n",*name_ref,*rec);
  
  return false;
 }

/* class RefList */ 

bool RefList::link(NameLinkEngine &engine)
 {
  AndFlag result;
  
  for(RefBase &obj : list ) result+=obj.link(engine);
  
  return result;
 }

/* class DomainList */

struct DomainList::SetTypeSwitch : TypeSwitch
 {
  PrintBase &msg;
  
  const char *error_msg;
  
  explicit SetTypeSwitch(PrintBase &msg_) : TypeSwitch(this),msg(msg_) {}
  
  bool setType(DomainTypeNode &node);
 
  void do_sint8(TypeNode_suint<imp_sint8> *) { error_msg=0; }
  void do_uint8(TypeNode_suint<imp_uint8> *) { error_msg=0; }
  
  void do_sint16(TypeNode_suint<imp_sint16> *) { error_msg=0; }
  void do_uint16(TypeNode_suint<imp_uint16> *) { error_msg=0; }
  
  void do_sint32(TypeNode_suint<imp_sint32> *) { error_msg=0; }
  void do_uint32(TypeNode_suint<imp_uint32> *) { error_msg=0; }
  
  void do_sint64(TypeNode_suint<imp_sint64> *) { error_msg=0; }
  void do_uint64(TypeNode_suint<imp_uint64> *) { error_msg=0; }
  
  void do_text(TypeNode_text *) { error_msg="text"; }
  void do_ip(TypeNode_ip *) { error_msg="ip"; }
  
  void do_ptr(TypeNode_ptr *) { error_msg="T *"; }
  void do_array(TypeNode_array *) { error_msg="T[]"; }
  void do_array_len(TypeNode_array_len *) { error_msg="T[]"; }
  void do_struct(TypeNode_struct *) { error_msg="struct {}"; }
  
  void do_ref(TypeNode_ref *) { error_msg="struct {}"; }
 };

bool DomainList::SetTypeSwitch::setType(DomainTypeNode &node)
 {
  AliasNode *alias=node.alias_node;
  
  alias->result_type->dispatch(*this);
  
  if( error_msg )
    {
     Printf(msg,"Invalid domain type : #; (#;)\n",error_msg,*node.name);
     
     return false;
    }
  else
    {
     node.type_node=alias->result_type;
     
     return true;
    }
 }

bool DomainList::setTypes(PrintBase &msg)
 {
  SetTypeSwitch ts(msg);
  
  AndFlag result;
  
  for(DomainBase &obj : list ) result+=ts.setType(static_cast<DomainTypeNode &>(obj));
  
  return result;
 }

/* class ExprList */

struct ExprList::SetTypesSwitch : ExprSwitch 
 {
  static TypeNode * AddType(TypeNode *type1,TypeNode *type2)
   {
    if( type1 ) return type1;
    
    return type2;
   }
  
  struct PtrToSwitch : TypeSwitch
   {
    TypeNode *type;
    
    PtrToSwitch() : TypeSwitch(this) {}
    
    void do_sint8(TypeNode_suint<imp_sint8> *) { type=0; }
    void do_uint8(TypeNode_suint<imp_uint8> *) { type=0; }
    
    void do_sint16(TypeNode_suint<imp_sint16> *) { type=0; }
    void do_uint16(TypeNode_suint<imp_uint16> *) { type=0; }
    
    void do_sint32(TypeNode_suint<imp_sint32> *) { type=0; }
    void do_uint32(TypeNode_suint<imp_uint32> *) { type=0; }
    
    void do_sint64(TypeNode_suint<imp_sint64> *) { type=0; }
    void do_uint64(TypeNode_suint<imp_uint64> *) { type=0; }
    
    void do_text(TypeNode_text *) { type=0; }
    void do_ip(TypeNode_ip *) { type=0; }
    
    void do_struct(TypeNode_struct *) { type=0; }
    
    void do_ptr(TypeNode_ptr *node) { type=node->type_node; }
    
    void do_array(TypeNode_array *node) { type=node->type_node; }
    
    void do_array_len(TypeNode_array_len *node) { type=node->type_node; }
    
    void do_ref(TypeNode_ref *node)
     {
      if( AliasNode *alias=node->alias_node )
        {
         alias->result_type->dispatch(*this);
        }
      else
        {
         type=0;
        }
     }
   };
  
  PtrToSwitch pts;
  FindFieldType fft;
  
  SetTypesSwitch() : ExprSwitch(this) {}
  
  void do_add(ExprNode_add *node) 
   {
    node->ptrto_type=AddType(node->arg1->ptrto_type,node->arg2->ptrto_type);
   }
  
  void do_sub(ExprNode_sub *node) 
   { 
    if( TypeNode *type=node->arg1->ptrto_type )
      {
       if( !node->arg2->ptrto_type ) node->ptrto_type=type;
      }
   }
  
  void do_address(ExprNode_address *node) 
   { 
    node->ptrto_type=node->arg->LV_type;
   }
  
  TypeNode * ptrtoType(TypeNode *type) 
   {
    type->dispatch(pts);
    
    return pts.type;
   }
  
  void setLV_notnull(ExprNode *node,TypeNode *type)
   {
    node->LV_type=type;
    node->ptrto_type=ptrtoType(type);
   }
  
  void setLV(ExprNode *node,TypeNode *type)
   {
    if( type ) setLV_notnull(node,type);
   }
  
  void do_deref(ExprNode_deref *node) 
   {
    setLV(node, node->arg->ptrto_type );
   }
  
  void do_ptr_select(ExprNode_ptr_select *node) 
   {
    if( TypeNode *type=node->arg->ptrto_type ) setLV(node, fft.fieldType(type,node->name) );
   }
  
  void do_select(ExprNode_select *node) 
   { 
    if( TypeNode *type=node->arg->LV_type ) setLV(node, fft.fieldType(type,node->name) );
   }
  
  void do_ind(ExprNode_ind *node) 
   { 
    setLV(node, AddType(node->arg1->ptrto_type,node->arg2->ptrto_type) );
   }
  
  void do_var(ExprNode_var *node) 
   {
    setLV_notnull(node, node->node->type_node );
   }
  
  void do_mul(ExprNode_mul *) {}
  void do_div(ExprNode_div *) {}
  void do_rem(ExprNode_rem *) {}
  void do_plus(ExprNode_plus *) {}
  void do_minus(ExprNode_minus *) {}
  void do_number(ExprNode_number *) {}
  void do_domain(ExprNode_domain *) {}
  void do_null(ExprNode_null *) {}
  void do_string(ExprNode_string *) {}
  void do_ip(ExprNode_ip *) {}
  void do_noname_list(ExprNode_noname_list *) {} 
  void do_named_list(ExprNode_named_list *) {}
  void do_apply_named_list(ExprNode_apply_named_list *) {}
 };

bool ExprList::setTypes()
 {
  SetTypesSwitch es;
  
  for(ExprNode &node : list ) node.dispatch(es);
  
  return true;
 }

/* struct Context */

struct Context::SetTypeSwitch : TypeSwitch
 {
  PrintBase &msg;
  
  AliasNode *next;
  
  explicit SetTypeSwitch(PrintBase &msg_) : TypeSwitch(this),msg(msg_) {}
  
  bool setType(AliasNode &node,ulen mark);
  
  void do_sint8(TypeNode_suint<imp_sint8> *) { next=0; }
  void do_uint8(TypeNode_suint<imp_uint8> *) { next=0; }
  
  void do_sint16(TypeNode_suint<imp_sint16> *) { next=0; }
  void do_uint16(TypeNode_suint<imp_uint16> *) { next=0; }
  
  void do_sint32(TypeNode_suint<imp_sint32> *) { next=0; }
  void do_uint32(TypeNode_suint<imp_uint32> *) { next=0; }
  
  void do_sint64(TypeNode_suint<imp_sint64> *) { next=0; }
  void do_uint64(TypeNode_suint<imp_uint64> *) { next=0; }
  
  void do_text(TypeNode_text *) { next=0; }
  void do_ip(TypeNode_ip *) { next=0; }
  
  void do_ptr(TypeNode_ptr *) { next=0; }
  void do_array(TypeNode_array *) { next=0; }
  void do_array_len(TypeNode_array_len *) { next=0; }
  void do_struct(TypeNode_struct *) { next=0; }
  
  void do_ref(TypeNode_ref *node) 
   {
    next=node->alias_node;
   }
 };

bool Context::SetTypeSwitch::setType(AliasNode &node,ulen mark)
 {
  if( node.result_type ) return true;
  
  AliasNode *alias=&node;
  
  for(;;)
    {
     alias->index=mark;
     
     alias->type_node->dispatch(*this);
     
     if( next )
       {
        if( next->index==mark ) 
          {
           Printf(msg,"Loop type alias : #;\n",node.name);
           
           return false;
          }
         
        alias=next;
       }
     else
       {
        break;
       }
    }
  
  TypeNode *type=alias->type_node;
  
  alias=&node;
  
  for(;;)
    {
     alias->result_type=type;
     
     alias->type_node->dispatch(*this);
     
     if( next )
       {
        alias=next;
       }
     else
       {
        break;
       }
    }
  
  return true;
 }

bool Context::setAliasTypes(BodyNode *body)
 {
  for(AliasNode &node : body->alias_list ) node.index=0;
  
  AndFlag result;
  
  ulen mark=0;
  
  SetTypeSwitch ts(msg);
  
  for(AliasNode &node : body->alias_list ) result+=ts.setType(node,++mark);
  
  return result;
 }

struct Context::Loop1Switch : TypeSwitch
 {
  PrintBase &msg;
  
  AliasNode *next_alias;
  TypeNode *next_type;
  
  explicit Loop1Switch(PrintBase &msg_) : TypeSwitch(this),msg(msg_) {}
  
  bool checkLoop1(AliasNode &node,ulen mark);
  
  void do_sint8(TypeNode_suint<imp_sint8> *) { next_type=0; }
  void do_uint8(TypeNode_suint<imp_uint8> *) { next_type=0; }
  
  void do_sint16(TypeNode_suint<imp_sint16> *) { next_type=0; }
  void do_uint16(TypeNode_suint<imp_uint16> *) { next_type=0; }
  
  void do_sint32(TypeNode_suint<imp_sint32> *) { next_type=0; }
  void do_uint32(TypeNode_suint<imp_uint32> *) { next_type=0; }
  
  void do_sint64(TypeNode_suint<imp_sint64> *) { next_type=0; }
  void do_uint64(TypeNode_suint<imp_uint64> *) { next_type=0; }
  
  void do_text(TypeNode_text *) { next_type=0; }
  void do_ip(TypeNode_ip *) { next_type=0; }
  
  void do_ptr(TypeNode_ptr *node) { next_type=node->type_node; }
  void do_array(TypeNode_array *node) { next_type=node->type_node; }
  void do_array_len(TypeNode_array_len *node) { next_type=node->type_node; }
  
  void do_struct(TypeNode_struct *) { next_type=0; }
  
  void do_ref(TypeNode_ref *node) 
   {
    next_type=0;
    next_alias=node->alias_node;
   }
 };

bool Context::Loop1Switch::checkLoop1(AliasNode &node,ulen mark)
 {
  if( node.index ) return true;
  
  node.index=mark;
  
  TypeNode *type=node.type_node;
  
  next_alias=0;
  
  for(;;)
    {
     type->dispatch(*this);
     
     if( next_type )
       {
        type=next_type;
       }
     else if( next_alias )
       {
        if( next_alias->index )
          {
           if( next_alias->index!=mark ) return true;
            
           Printf(msg,"Loop type definition : #;\n",node.name);
           
           return false;
          }
        else
          {
           next_alias->index=mark;
           
           type=next_alias->type_node;
           
           next_alias=0;
          }
       }
     else
       {
        return true;
       }
    }
 }

bool Context::checkLoop1(BodyNode *body)
 {
  for(AliasNode &node : body->alias_list ) node.index=0;
  
  AndFlag result;
  
  ulen mark=0;
  
  Loop1Switch ts(msg);
  
  for(AliasNode &node : body->alias_list ) result+=ts.checkLoop1(node,++mark);
  
  return result;
 }

struct Context::Loop2Switch : TypeSwitch
 {
  PrintBase &msg;
  
  TypeNode *next_type;
  StructNode *next_struct;
  
  bool result;

  explicit Loop2Switch(PrintBase &msg_) : TypeSwitch(this),msg(msg_),result(true) {}
  
  bool prepare(StructNode *node,StructNode *back=0)
   {
    if( node->index )
      {
       if( node->index==1 )
         {
          Printf(msg,"Self-include structure : #;\n",node->name);
          
          result=false;
         }
       
       return false;
      }
    
    node->index=1;
    node->back=back;
    node->cur=node->field_list.beg;
    
    return true;
   }
  
  StructNode * next(StructNode *node)
   {
    for(; FieldNode *field=node->cur ;node->cur=field->next)
      {
       if( StructNode *ret=forward(field->type_node) ) 
         {
          node->cur=field->next;
          
          return ret;
         }
      }
    
    return 0;
   }
  
  StructNode * complete(StructNode *node)
   {
    node->index=2;
    
    return node->back;
   }
  
  void checkLoop2(StructNode *node);
  
  StructNode * forward(TypeNode *type)
   {
    next_struct=0;
    
    while( type )
      {
       type->dispatch(*this);
       
       type=next_type;
      }
    
    return next_struct;
   }
  
  void do_sint8(TypeNode_suint<imp_sint8> *) { next_type=0; }
  void do_uint8(TypeNode_suint<imp_uint8> *) { next_type=0; }
  
  void do_sint16(TypeNode_suint<imp_sint16> *) { next_type=0; }
  void do_uint16(TypeNode_suint<imp_uint16> *) { next_type=0; }
  
  void do_sint32(TypeNode_suint<imp_sint32> *) { next_type=0; }
  void do_uint32(TypeNode_suint<imp_uint32> *) { next_type=0; }
  
  void do_sint64(TypeNode_suint<imp_sint64> *) { next_type=0; }
  void do_uint64(TypeNode_suint<imp_uint64> *) { next_type=0; }
  
  void do_text(TypeNode_text *) { next_type=0; }
  void do_ip(TypeNode_ip *) { next_type=0; }
  
  void do_ptr(TypeNode_ptr *) { next_type=0; }
  
  void do_array(TypeNode_array *node) { next_type=node->type_node; }
  void do_array_len(TypeNode_array_len *node) { next_type=node->type_node; }
  
  void do_struct(StructNode *node)
   {
    next_type=0;
    next_struct=node;
   }
  
  void do_struct(TypeNode_struct *node) 
   {
    do_struct(node->base_struct);
   }
  
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

void Context::Loop2Switch::checkLoop2(StructNode *node)
 {
  if( !prepare(node) ) return;
  
  while( node )
    {
     if( StructNode *ptr=next(node) )
       {
        if( prepare(ptr,node) ) node=ptr;
       }
     else
       {
        node=complete(node);
       }
    }
 }

bool Context::checkLoop2(BodyNode *body)
 {
  for(StructNode &node : body->struct_list ) node.index=0;
  
  Loop2Switch ts(msg);
  
  for(StructNode &node : body->struct_list ) ts.checkLoop2(&node);
  
  return ts.result;
 }

Context::Context(PrintBase &msg_,ulen mem_cap_) 
 : mem_cap(mem_cap_),
   pool(MemPool::DefaultBlockLen,mem_cap_),
   msg(msg_) 
 {
 }

void Context::reset()
 {
  ElementPool pool_(MemPool::DefaultBlockLen,mem_cap);
  
  Swap(pool,pool_);
  
  id_engine.reset();
  ref_list.reset();
  domain_list.reset();
  expr_list.reset();
 }

bool Context::complete(BodyNode *body)
 {
  NameId max_id=id_engine.generate();
  
  NameLinkEngine engine(msg,max_id);
  
  // 1
  
  AndFlag result;
  
  body->setScope();
  
  result+=body->setMap(this,max_id);
  
  result+=body->addTo(engine);
  
  result+=ref_list.link(engine);
  
  // 2
  
  return result &&
         setAliasTypes(body) &&
         domain_list.setTypes(msg) &&
         expr_list.setTypes() &&
         checkLoop1(body) &&
         checkLoop2(body) ;
 }

/* struct FieldMap */

void FieldMap::add(PrintBase &msg,NameId max_id,FieldNode *node)
 {
  Algo::PrepareIns prepare(root,node->name.name_id,1,max_id);
    
  if( prepare.found )
    {
     Printf(msg,"Used field name : #;\n  Founded field is : #;\n",node->name,prepare.found->name);
       
     ok=false;
    }
  else
    {
     prepare.complete(node);
    }
 }
  
FieldMap::FieldMap(PrintBase &msg,NameId max_id,StructNode *node)
 : ok(true)
 {
  for(FieldNode &field : node->field_list ) add(msg,max_id,&field);
 }
  
/* struct StructNode */

bool StructNode::setMap(Context *ctx,NameId max_id)
 {
  FieldMap *map=ctx->pool.create<FieldMap>(ctx->msg,max_id,this);
  
  if( !*map ) return false;
  
  field_map=map;
  
  return true;
 }

void StructNode::setScope()
 {
  From from(&scope_node,depth+1);
  
  for(FieldNode &node : field_list ) node.setScope(from);
 }

/* struct BodyNode */

void BodyNode::foldin(ScopeNode *scope) 
 {
  for(AliasNode &node : alias_list ) node.setParent(scope);
  
  for(ConstNode &node : const_list ) node.setParent(scope);
  
  for(StructNode &node : struct_list ) node.setParent(scope);
  
  for(ScopeNode &node : scope_list ) node.setParent(scope);
 }

bool BodyNode::addTo(NameLinkEngine &engine)
 {
  AndFlag result;
  
  for(AliasNode &node : alias_list ) result+=engine.add(&node);
  
  for(ConstNode &node : const_list ) result+=engine.add(&node);
  
  for(StructNode &node : struct_list ) result+=engine.add(&node);
  
  return result;
 }

bool BodyNode::setMap(Context *ctx,NameId max_id)
 {
  AndFlag result;
  
  for(StructNode &node : struct_list ) result+=node.setMap(ctx,max_id);
  
  return result;
 }

void BodyNode::setScope()
 {
  for(AliasNode &node : alias_list ) node.setScope();
  
  for(ConstNode &node : const_list ) node.setScope();
  
  for(StructNode &node : struct_list ) node.setScope();
 }

/* class TypeCompare */

auto TypeCompare::operator () (TypeNode *type1,TypeNode *type2) -> Result
 {
  for(;;)
    {
     if( type1==type2 ) return Same;
     
     type1->dispatch(ts1);
     type2->dispatch(ts2);
     
     if( ts1.tc!=ts2.tc ) return NotSame;
     
     switch( ts1.tc )
       {
        default : return Same;
      
        case Type_struct : return (ts1.struct_node==ts2.struct_node)?Same:NotSame;
         
        case Type_ptr : // falldown;  
         
        case Type_array : type1=ts1.type_node; type2=ts2.type_node; continue;
         
        case Type_array_len :
         {
          this->type1=ts1.type_node; 
          this->type2=ts2.type_node;
          len1=ts1.len_node;
          len2=ts2.len_node;
         }
        return Continue; 
       }
    }
 }

} // namespace DDL
} // namespace CCore
