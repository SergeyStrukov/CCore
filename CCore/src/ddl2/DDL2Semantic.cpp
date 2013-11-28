/* DDL2Semantic.cpp */
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

#include <CCore/inc/ddl2/DDL2Semantic.h>

#include <CCore/inc/Crc.h>

#include <CCore/inc/algon/SortUnique.h>

namespace CCore {
namespace DDL2 {

/* struct Context */

NameId Context::generateIds()
 {
  struct Rec : CmpComparable<Rec>
   {
    NameIdNode *name;
    uint32 hash;
    
    explicit Rec(NameIdNode &name_)
     {
      name=&name_;
      
      Crc32 crc;
      
      crc.addRange(name_.getStr());
      
      hash=crc;
     }
    
    void set(NameId id)
     {
      name->name_id=id;
     }
    
    CmpResult objCmp(const Rec &obj) const
     {
      if( auto ret=Cmp(hash,obj.hash) ) return ret;
      
      return StrCmp(name->getStr(),obj.name->getStr());
     }
   };
  
  DynArray<Rec> buf(DoReserve,name_id_list.count);
  
  for(NameIdNode &obj : name_id_list ) buf.append_fill(obj);
  
  NameId id=0;
  
  Algon::SortThenApplyUniqueRange(Range(buf), [&] (PtrLen<Rec> range) 
                                                  {
                                                   ++id;
                                            
                                                   for(Rec &rec : range ) rec.set(id);
                                                  } 
                                 );
  
  if( !id ) return 1;
  
  return id;
 }

struct Context::MapScopeRec : NoThrowFlagsBase , NoCopy
 {
  MapScopeRec *next;
  
  BodyNode *body_node;
  
  explicit MapScopeRec(BodyNode *body_node_) : body_node(body_node_) {}
  
  void addMaps(ElementPool &pool,NameId max_id,BaseList<NameLinkMap> &map_list)
   {
    auto *map=body_node->map;
    
    for(ScopeNode &node : body_node->scope_list )
      {
       node.body->map=map->add(pool,max_id,node,map_list);
      }
   }
 };

struct Context::MapScopeExpand
 {
  template <class Add>
  void operator () (MapScopeRec *rec,Add add)
   {
    for(ScopeNode &node : rec->body_node->scope_list ) add(node.body);
   }
 };

void Context::mapScopes(BodyNode *body_node,NameId max_id,BaseList<NameLinkMap> &map_list)
 {
  Enlist<MapScopeRec> enlist(MapScopeExpand(),body_node);
  
  for(auto &rec : enlist ) rec.addMaps(pool,max_id,map_list);
 }

template <class Node>
bool Context::fillMap(NameLinkMap *map,NameId max_id,Node &node)
 {
  if( ScopeNode *parent=node.parent ) map=parent->body->map;
  
  return map->add(error,max_id,node);
 }

bool Context::buildMaps(BodyNode *body_node,NameId max_id)
 {
  BaseList<NameLinkMap> map_list;
  
  NameLinkMap *map=pool.create<NameLinkMap>();
  
  map_list.init(map);
  
  body_node->map=map;
  
  mapScopes(body_node,max_id,map_list);
  
  AndFlag ret;
  
  for(AliasNode &node : body_node->alias_list ) ret+=fillMap(map,max_id,node);
  
  for(ConstNode &node : body_node->const_list ) ret+=fillMap(map,max_id,node);
  
  for(StructNode &node : body_node->struct_list ) ret+=fillMap(map,max_id,node);
  
  for(NameLinkMap &map : map_list ) ret+=map.check(error);
  
  return ret;
 }

struct Context::PickNextAlias
 {
  AliasNode * &ret;
  
  explicit PickNextAlias(AliasNode * &ret_) : ret(ret_) {}
  
  template <class T>
  void operator () (T *) { ret=0; }
  
  void operator () (TypeNode::Ref *ptr)
   {
    ret=ptr->ptr.castPtr<AliasNode>();
   }
 };

AliasNode * Context::NextAlias(AliasNode *node)
 {
  AliasNode *ret;
  
  node->type_node->ptr.apply( PickNextAlias(ret) );
  
  return ret;
 }

bool Context::setAliasTypes(AliasNode &node,ulen mark)
 {
  if( node.result_type ) return true;
  
  AliasNode *alias=&node;
  
  for(;;)
    {
     alias->index=mark;
     
     if( AliasNode *next=NextAlias(alias) )
       {
        if( next->index==mark ) 
          {
           error("Cyclic type definition : #;",node.name);
           
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
     
     if( AliasNode *next=NextAlias(alias) )
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

bool Context::setAliasTypes(BodyNode *body_node)
 {
  for(AliasNode &node : body_node->alias_list ) node.index=0;
  
  AndFlag ret;
  
  ulen mark=0;
  
  for(AliasNode &node : body_node->alias_list ) ret+=setAliasTypes(node,++mark);
  
  return ret;
 }

struct Context::AliasRec : NoThrowFlagsBase , NoCopy
 {
  AliasRec *next;
  
  AliasNode *node;
  
  explicit AliasRec(AliasNode *node_) : node(node_) {}
 };

struct Context::AliasExpand
 {
  ErrorMsg &error;
  ulen mark;
  bool &ret;
  
  AliasExpand(ErrorMsg &error_,ulen mark_,bool &ret_) : error(error_),mark(mark_),ret(ret_) {}
  
  struct Rec : NoThrowFlagsBase , NoCopy
   {
    Rec *next;
    
    TypeNode *type;
    
    explicit Rec(TypeNode *type_) : type(type_) {}
   };
  
  template <class AliasAdd>
  struct Expand
   {
    AliasAdd alias_add;
    
    explicit Expand(const AliasAdd &alias_add_) : alias_add(alias_add_) {}
    
    template <class Add>
    struct Func
     {
      AliasAdd alias_add;
      Add add;
      
      Func(const AliasAdd &alias_add_,const Add &add_) : alias_add(alias_add_),add(add_) {}
      
      template <class T> 
      void operator () (T *) {}
      
      void operator () (TypeNode::Ref *ptr)
       {
        if( AliasNode *node=ptr->ptr.castPtr<AliasNode>() ) alias_add(node);
       }
      
      void operator () (TypeNode::Ptr *ptr)
       {
        add(ptr->type_node);
       }
      
      void operator () (TypeNode::Array *ptr)
       {
        add(ptr->type_node);
       }
      
      void operator () (TypeNode::ArrayLen *ptr)
       {
        add(ptr->type_node);
       }
      
      void operator () (TypeNode::PolyPtr *ptr)
       {
        for(auto &node : *(ptr->type_list) ) add(node.type_node);
       }
     };
    
    template <class Add>
    void operator () (Rec *rec,Add add)
     {
      TypeNode *type=rec->type;
      
      type->ptr.apply( Func<Add>(alias_add,add) );
     }
   };
  
  template <class Add>
  void operator () (AliasRec *rec,Add add)
   {
    AliasNode *node=rec->node;
    
    ulen prev_mark=node->index;
    
    if( prev_mark==mark )
      {
       error("Cyclic type definition : #;",node->name);
       
       ret=false;
       
       return;
      }
     
    if( prev_mark ) return;
    
    node->index=mark;
    
    Enlist<Rec> enlist(Expand<Add>(add),node->result_type);
   }
 };

bool Context::checkLoop1(AliasNode &node,ulen mark)
 {
  if( node.index ) return true;
  
  bool ret=true;
  
  Enlist<AliasRec> enlist(AliasExpand(error,mark,ret),&node);
  
  return ret;
 }

bool Context::checkLoop1(BodyNode *body_node)
 {
  for(AliasNode &node : body_node->alias_list ) node.index=0;
  
  AndFlag ret;
  
  ulen mark=0;
  
  for(AliasNode &node : body_node->alias_list ) ret+=checkLoop1(node,++mark);
  
  return ret; 
 }

struct Context::StructRec : NoThrowFlagsBase , NoCopy
 {
  StructRec *next;
  
  StructNode *node;
  
  explicit StructRec(StructNode *node_) : node(node_) {} 
 };

struct Context::StructExpand
 {
  ErrorMsg &error;
  ulen mark;
  bool &ret;
  
  StructExpand(ErrorMsg &error_,ulen mark_,bool &ret_) : error(error_),mark(mark_),ret(ret_) {}
  
  struct Rec : NoThrowFlagsBase , NoCopy
   {
    Rec *next;
    
    AnyPtr<StructNode,TypeNode> ptr;
    
    explicit Rec(StructNode *struct_node) : ptr(struct_node) {}
    
    explicit Rec(TypeNode *type) : ptr(type) {}
   };
  
  template <class StructAdd>
  struct Expand
   {
    StructAdd struct_add;
    
    explicit Expand(const StructAdd &struct_add_) : struct_add(struct_add_) {}
    
    template <class Add>
    struct Func
     {
      StructAdd struct_add;
      Add add;
      
      Func(const StructAdd &struct_add_,const Add &add_) : struct_add(struct_add_),add(add_) {}
      
      template <class T> 
      void operator () (T *) {}
      
      void operator () (AliasNode *node)
       {
        add(node->result_type);
       }
      
      void operator () (StructNode *node)
       {
        struct_add(node);
       }
      
      void operator () (TypeNode::Ref *ptr)
       {
        ptr->ptr.apply(*this);
       }
      
      void operator () (TypeNode::Array *ptr)
       {
        add(ptr->type_node);
       }
      
      void operator () (TypeNode::ArrayLen *ptr)
       {
        add(ptr->type_node);
       }
     };
    
    template <class Add>
    struct RecFunc
     {
      Func<Add> func;
      
      RecFunc(const StructAdd &struct_add,const Add &add) : func(struct_add,add) {}
      
      void operator () (StructNode *struct_node)
       {
        for(FieldNode &node : struct_node->field_list )
          {
           node.type_node->ptr.apply(func);
          }
       }
      
      void operator () (TypeNode *type)
       {
        type->ptr.apply(func);
       }
     };
    
    template <class Add>
    void operator () (Rec *rec,Add add)
     {
      rec->ptr.apply( RecFunc<Add>(struct_add,add) );
     }
   };
  
  template <class Add>
  void operator () (StructRec *rec,Add add)
   {
    StructNode *node=rec->node;
    
    ulen prev_mark=node->index;
    
    if( prev_mark==mark )
      {
       error("Cyclic type definition : #;",node->name);
       
       ret=false;
       
       return;
      }
     
    if( prev_mark ) return;
    
    node->index=mark;
    
    Enlist<Rec> enlist(Expand<Add>(add),node);
   }
 };

bool Context::checkLoop2(StructNode &node,ulen mark)
 {
  if( node.index ) return true;
  
  bool ret=true;
  
  Enlist<StructRec> enlist(StructExpand(error,mark,ret),&node);
  
  return ret;
 }

bool Context::checkLoop2(BodyNode *body_node)
 {
  for(StructNode &node : body_node->struct_list ) node.index=0;
  
  AndFlag ret;
  
  ulen mark=0;
  
  for(StructNode &node : body_node->struct_list ) ret+=checkLoop2(node,++mark);
  
  return ret; 
 }

bool Context::setDomainTypes()
 {
  AndFlag ret;
  
  for(DomainRefNode &node : domain_ref_list ) ret+=node.ptr->setType(error);
  
  return ret;
 }

Context::Context(PrintBase &msg,ulen mem_cap_)
 : mem_cap(mem_cap_),
   error(msg),
   pool(MemPool::DefaultBlockLen,mem_cap_)
 {
  name_id_list.init();
  domain_ref_list.init();
 }

Context::~Context() 
 {
 }
  
void Context::reset()
 {
  error.reset();
  
  ElementPool pool_(MemPool::DefaultBlockLen,mem_cap);
  
  Swap(pool,pool_);
  
  name_id_list.init();
  domain_ref_list.init();
 }

BodyNode * Context::complete(BodyNode *body_node)
 {
  NameId max_id=generateIds();
  
  AndFlag ret; 
  
  ret+=body_node->setMap(this,max_id);
  
  ret+=buildMaps(body_node,max_id);
  
  ret+=body_node->doLink(LinkContext(error,body_node->map));
  
  if( ret && setAliasTypes(body_node) 
          && checkLoop1(body_node) 
          && checkLoop2(body_node) 
          && setDomainTypes() ) 
    return body_node;
  
  error("\nName link error\n");
  
  return 0;
 }

/* struct ScopeNode */

void ScopeNode::init(ExtContext ctx,const Token &token,BodyNode *body_)
 {
  parent=0;
  
  name.init(ctx,token);
  
  body=body_;
  
  body_->foldin(this);
 }

/* class ScopeList */

ScopeList::ScopeList(From from) 
 : TempArray<ScopeNode *,100>(from.depth)
 {
  for(auto r=RangeReverse(*this); +r ;++r)
    {
     *r=from.scope; 
     
     from.back();
    }
 }

ScopeList::~ScopeList()
 {
 }
   
/* struct TypeNode */

bool TypeNode::doLink(From from,LinkContext ctx) 
 {
  if( !lists ) return true;
  
  for(auto &node : lists->from_list ) node.from=from;
  
  AndFlag ret;
  
  for(RefListNode &node : lists->ref_list ) ret+=ctx.doLink(from,node.ptr);
  
  return ret;
 }

const char * GetTextDesc(TypeNode::Base::Type base_type)
 {
  switch( base_type )
    {
     case TypeNode::Base::Type_none   : return "none";
   
     case TypeNode::Base::Type_sint   : return "sint";
     case TypeNode::Base::Type_uint   : return "uint";
     case TypeNode::Base::Type_ulen   : return "ulen";
   
     case TypeNode::Base::Type_sint8  : return "sint8";
     case TypeNode::Base::Type_uint8  : return "uint8";
     case TypeNode::Base::Type_sint16 : return "sint16";
     case TypeNode::Base::Type_uint16 : return "uint16";
     case TypeNode::Base::Type_sint32 : return "sint32";
     case TypeNode::Base::Type_uint32 : return "uint32";
     case TypeNode::Base::Type_sint64 : return "sint64";
     case TypeNode::Base::Type_uint64 : return "uint64";
   
     case TypeNode::Base::Type_text   : return "text";
     case TypeNode::Base::Type_ip     : return "ip";
   
     default: return "???";
    }
 }

/* struct ExprNode::Domain */

bool ExprNode::Domain::setType(ErrorMsg &error)
 {
  if( TypeNode::Base *base_ptr=ptr->result_type->ptr.castPtr<TypeNode::Base>() )
    {
     if( base_ptr->isIntegral() )
       {
        type=base_ptr->type;
       
        return true;
       }
    }
  
  error("Bad domain type : #;",*name_ref);
  
  return false;
 }

/* struct ExprNode */

bool ExprNode::doLink(From from,LinkContext ctx)
 {
  if( !lists ) return true;
  
  AndFlag ret;
  
  for(RefListNode &node : lists->ref_list ) ret+=ctx.doLink(from,node.ptr);
  
  return ret;
 }

bool ExprNode::doLinkQName(From from,LinkContext ctx)
 {
  if( !lists ) return true;
  
  AndFlag ret;
  
  for(RefListNode &node : lists->ref_list ) ret+=ctx.doLinkQName(from,node.ptr);
  
  return ret;
 }

/* class FieldMap */

void FieldMap::add(ErrorMsg &error,NameId max_id,FieldNode *node)
 {
  Algo::PrepareIns prepare(root,node->name.name_id,1,max_id);
    
  if( prepare.found )
    {
     error("Field name duplication : #;\n  Found field is : #;",node->name,prepare.found->name);
       
     ok=false;
    }
  else
    {
     prepare.complete(node);
    }
 }
  
FieldMap::FieldMap(ErrorMsg &error,NameId max_id,StructNode *node)
 : ok(true)
 {
  for(FieldNode &field : node->field_list ) add(error,max_id,&field);
 }
  
/* struct StructNode */

bool StructNode::setMap(Context *ctx,NameId max_id)
 {
  FieldMap *map=ctx->pool.create<FieldMap>(ctx->error,max_id,this);
  
  if( !*map ) return false;
  
  field_map=map;
  
  return true;
 }

bool StructNode::doLink(LinkContext ctx)
 {
  From from=getFieldFrom();
  
  AndFlag ret;
  
  for(FieldNode &node : field_list ) ret+=node.doLink(from,ctx);
  
  return ret;
 }

/* class NameLinkMap */

template <class T>
void NameLinkMap::fill(Collector<Rec> &col,T *root)
 {
  if( root )
    {
     col.append_fill(root);
     
     fill(col,Algo<T>::Link(root).lo);
     fill(col,Algo<T>::Link(root).hi);
    }
 }

bool NameLinkMap::check(ErrorMsg &error,RecPtr a,RecPtr b)
 {
  if( a.hasType<StructNode>() && b.hasType<NameLinkMap>() ) return true;
  
  if( b.hasType<StructNode>() && a.hasType<NameLinkMap>() ) return true;
  
  error("Same name of different kind : #; and #;",a,b);
  
  return false;
 }

bool NameLinkMap::check(ErrorMsg &error,PtrLen<Rec> range)
 {
  AndFlag ret;
  
  for(; +range ;++range)
    {
     auto r=range;
     
     for(++r; +r ;++r)
       {
        ret+=check(error,range->ptr,r->ptr);
       }
    }
  
  return ret;
 }

NameLinkMap * NameLinkMap::add(ElementPool &pool,NameId max_id,ScopeNode &node,BaseList<NameLinkMap> &map_list)
 {
  Algo<NameLinkMap>::PrepareIns prepare(map_root,node.name.name_id,1,max_id);
  
  if( prepare.found )
    {
     return prepare.found;
    }
  else
    {
     NameLinkMap *map=pool.create<NameLinkMap>(node);
    
     prepare.complete(map);
     
     map_list.add(map);
     
     return map;
    }
 }

bool NameLinkMap::add(ErrorMsg &error,NameId max_id,AliasNode &node)
 {
  Algo<AliasNode>::PrepareIns prepare(alias_root,node.name.name_id,1,max_id);
  
  if( prepare.found )
    {
     error("Type name duplication : #; , \n  Found object is : #;",node.name,prepare.found->name);
     
     return false;
    }
  
  prepare.complete(&node);
  
  return true;
 }

bool NameLinkMap::add(ErrorMsg &error,NameId max_id,ConstNode &node)
 {
  Algo<ConstNode>::PrepareIns prepare(const_root,node.name.name_id,1,max_id);
  
  if( prepare.found )
    {
     error("Constant name duplication : #; , \n  Found object is : #;",node.name,prepare.found->name);
    
     return false;
    }
  
  prepare.complete(&node);
  
  return true;
 }

bool NameLinkMap::add(ErrorMsg &error,NameId max_id,StructNode &node)
 {
  Algo<StructNode>::PrepareIns prepare(struct_root,node.name.name_id,1,max_id);
  
  if( prepare.found )
    {
     error("Structure name duplication : #; , \n  Found object is : #;",node.name,prepare.found->name);
   
     return false;
    }
  
  prepare.complete(&node);
  
  return true;
 }

bool NameLinkMap::check(ErrorMsg &error)
 {
  Collector<Rec> col;
  
  fill(col,alias_root.root);
  fill(col,const_root.root);
  fill(col,struct_root.root);
  fill(col,map_root.root);
  
  AndFlag ret;
  
  Algon::IncrSortThenApplyUniqueRangeBy(col.flat(), [] (Rec &rec) { return rec.name->name_id; } ,
                                                    [&] (PtrLen<Rec> range) 
                                                        {
                                                         ret+=check(error,range);
                                                        } 
                                       );

  return ret;
 }

template <class Error>
NameLinkMap * NameLinkMap::findMap(Error &error,From from,NameNodeList *name_list)
 {
  ScopeList list(from);
  
  NameLinkMap *map=this;
  
  for(ScopeNode *node : list )
    {
     map=map->findMap(node->name);
     
     if( !map )
       {
        error("Undefined scope : #;",node->name);
       
        return 0;
       }
    }
  
  for(NameNode &node : NoLast<NameNode>(name_list->list) )
    {
     map=map->findMap(node.name);
    
     if( !map )
       {
        error("Undefined scope : #;",node.name);
      
        return 0;
       }
    }
  
  return map;
 }

NameLinkMap * NameLinkMap::tryFindMap(From from,NameNodeList *name_list)
 {
  NoError error;
  
  return findMap(error,from,name_list);
 }
   
template <class Func>
bool NameLinkMap::tryFindNode(From from,NameNodeList *name_list,Func func)
 {
  if( auto *map=tryFindMap(from,name_list) )
    {
     if( func(map,name_list->list.last->name) ) return true;
    }
  
  return false;
 }

template <class Error,class Func>
void NameLinkMap::findNode(Error &error,From from,NameNodeList *name_list,Func func)
 {
  if( auto *map=findMap(error,from,name_list) )
    {
     if( func(map,name_list->list.last->name) ) return;
    }
  
  error("Undefined name : #;",*name_list);
 }

template <class Error,class Func>
void NameLinkMap::findNode(Error &error,From from,NameRefNode *name_ref,Func func)
 {
  auto *name_list=name_ref->name_list;
  
  switch( name_ref->type )
    {
     case NameRefNode::Type_rel :
      {
       do
         {
          if( tryFindNode(from,name_list,func) ) return;
         }
       while( from.back() );
       
       error("Undefined name : #;",*name_ref);
      }
     break;
     
     case NameRefNode::Type_abs :
      {
       findNode(error,From(),name_list,func);
      }
     break;
     
     case NameRefNode::Type_this :
      {
       findNode(error,from,name_list,func);
      }
     break;
     
     case NameRefNode::Type_dots :
      {
       for(ulen cnt=name_ref->dots_count-1; cnt ;cnt--)
         if( !from.back() )
           {
            error("Undefined name, too many dots : #;",*name_ref);
            
            return;
           }
       
       findNode(error,from,name_list,func);
      }
     break;
    }
 }

template <class Error>
ConstNode * NameLinkMap::findConst(Error &error,From from,NameRefNode *name_ref)
 {
  ConstNode *ret=0;
  
  findNode(error,from,name_ref, [&] (NameLinkMap *map,NameIdNode &name) 
                                    {
                                     ret=map->findConst(name);
                                   
                                     return ret;
                                    } 
          );
  
  return ret;
 }

AliasNode * NameLinkMap::findAlias(ErrorMsg &error,From from,NameRefNode *name_ref)
 {
  AliasNode *ret=0;
  
  findNode(error,from,name_ref, [&] (NameLinkMap *map,NameIdNode &name) 
                                    {
                                     ret=map->findAlias(name);
                                   
                                     return ret;
                                    } 
          );
  
  return ret;
 }

AnyPtr<AliasNode,StructNode> NameLinkMap::findAliasStruct(ErrorMsg &error,From from,NameRefNode *name_ref)
 {
  AnyPtr<AliasNode,StructNode> ret;
  
  findNode(error,from,name_ref, [&] (NameLinkMap *map,NameIdNode &name) 
                                    {
                                     if( auto *ptr=map->findAlias(name) )
                                       {
                                        ret=ptr;
                                      
                                        return true;
                                       }
                                   
                                     if( auto *ptr=map->findStruct(name) )
                                       {
                                        ret=ptr;
                                      
                                        return true;
                                       }
                                   
                                     return false;
                                    } 
          );
  
  return ret;
 }

bool NameLinkMap::doLink(ErrorMsg &error,From from,TypeNode::Ref *ptr)
 {
  auto *name_ref=ptr->name_ref;
  
  auto result=findAliasStruct(error,from,name_ref);
  
  if( +result )
    {
     ptr->ptr=result;
    
     return true;
    }
  
  return false;
 }

bool NameLinkMap::doLink(ErrorMsg &error,From from,ExprNode::Domain *ptr)
 {
  auto *name_ref=ptr->name_ref;
  
  if( name_ref->name_list->qname_flag ) 
    {
     error("QName is not allowed here : #;",*name_ref);
    
     return false;
    }
  
  if( auto *result=findAlias(error,from,name_ref) )
    {
     ptr->ptr=result;
    
     return true;
    }
  
  return false;
 }

bool NameLinkMap::doLink(ErrorMsg &error,From from,ExprNode::Ref *ptr)
 {
  auto *name_ref=ptr->name_ref;
  
  if( name_ref->name_list->qname_flag ) 
    {
     error("QName is not allowed here : #;",*name_ref);
    
     return false;
    }
  
  if( auto *result=findConst(error,from,name_ref) )
    {
     ptr->ptr=result;
    
     return true;
    }
  
  return false;
 }

bool NameLinkMap::doLinkQName(ErrorMsg &error,From from,ExprNode::Ref *ptr)
 {
  auto *name_ref=ptr->name_ref;
  
  if( name_ref->name_list->qname_flag ) return true; 
  
  if( auto *result=findConst(error,from,name_ref) )
    {
     ptr->ptr=result;
    
     return true;
    }
  
  return false;
 }

ConstNode * NameLinkMap::doLink(From from,ExprNode::Ref *ptr)
 {
  if( ConstNode *ret=ptr->ptr ) return ret;
  
  NoError error;
  
  return findConst(error,from,ptr->name_ref);
 }

/* struct LinkContext */
  
struct LinkContext::Func
 {
  LinkContext *ctx;
  bool &ret;
  From from;
  
  Func(LinkContext *ctx_,bool &ret_,From from_)
   : ctx(ctx_),
     ret(ret_),
     from(from_)
   {
   }

  template <class T>
  void operator () (T *ptr)
   {
    ret=ctx->doLink(from,ptr);
   }
 };

struct LinkContext::FuncQName
 {
  LinkContext *ctx;
  bool &ret;
  From from;
  
  FuncQName(LinkContext *ctx_,bool &ret_,From from_)
   : ctx(ctx_),
     ret(ret_),
     from(from_)
   {
   }

  template <class T>
  void operator () (T *ptr)
   {
    ret=ctx->doLinkQName(from,ptr);
   }
 };

bool LinkContext::doLink(From from,AnyPtr<TypeNode::Ref,ExprNode::Domain,ExprNode::Ref> ptr)
 {
  bool ret;
  
  ptr.apply( Func(this,ret,from) );
  
  return ret;
 }

bool LinkContext::doLinkQName(From from,AnyPtr<TypeNode::Ref,ExprNode::Domain,ExprNode::Ref> ptr)
 {
  bool ret;
  
  ptr.apply( FuncQName(this,ret,from) );
  
  return ret;
 }

/* struct BodyNode */

void BodyNode::add(TypeNode *type_node)
 {
  if( auto *lists=type_node->lists )
    {
     lists->fill_from_list();
    
     len_list.join(lists->len_list);
    
     for(StructNode &node : lists->struct_list ) add(&node.scope_node);
      
     struct_list.join(lists->struct_list);
    }
 }
  
void BodyNode::foldin(ScopeNode *scope) 
 {
  for(AliasNode &node : alias_list ) node.setParent(scope);
  
  for(ConstNode &node : const_list ) node.setParent(scope);
  
  for(StructNode &node : struct_list ) node.setParent(scope);
  
  for(ScopeNode &node : scope_list ) node.setParent(scope);
 }

bool BodyNode::setMap(Context *ctx,NameId max_id)
 {
  AndFlag result;
  
  for(StructNode &node : struct_list ) result+=node.setMap(ctx,max_id);
  
  return result;
 }

bool BodyNode::doLink(LinkContext ctx)
 {
  AndFlag ret;
  
  for(AliasNode &node : alias_list ) ret+=node.doLink(ctx);
  
  for(ConstNode &node : const_list ) ret+=node.doLink(ctx);
  
  for(StructNode &node : struct_list ) ret+=node.doLink(ctx);
  
  return ret;
 }

} // namespace DDL2
} // namespace CCore
