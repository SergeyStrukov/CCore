/* DDL2ParserElements.cpp */
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

#include <CCore/inc/ddl2/DDL2Parser.h>

namespace CCore {
namespace DDL2 {

/* struct Element_BODY */

void Element_BODY::start(ElementContext ctx)
 {
  body_node=ctx.create<BodyNode>();
    
  body_node->start();
 }

void Element_BODY::ext(ElementContext,Element_BODY *elem,Element_SCOPE *elem_scope)
 {
  body_node=*elem;
  
  body_node->add(*elem_scope);
 }

void Element_BODY::ext(ElementContext,Element_BODY *elem,Element_INCLUDE *elem_include)
 {
  body_node=*elem;
  
  if( BodyNode *node=*elem_include ) body_node->add(node);
 }

void Element_BODY::ext(ElementContext,Element_BODY *elem,Element_TYPE *elem_alias)
 {
  body_node=*elem;
  
  body_node->add(*elem_alias);
 }

void Element_BODY::ext(ElementContext,Element_BODY *elem,Element_CONST *elem_const)
 {
  body_node=*elem;
  
  body_node->add(*elem_const);
 }

void Element_BODY::ext(ElementContext,Element_BODY *elem,Element_STRUCT *elem_struct,ElementAtom *)
 {
  body_node=*elem;
  
  body_node->add(*elem_struct);
 }

/* struct Element_SCOPE */

void Element_SCOPE::build(ElementContext ctx,ElementAtom *,ElementAtom *name,ElementAtom *,Element_BODY *elem_body,ElementAtom *)
 {
  scope_node.init(ctx,*name,*elem_body);
 }

/* struct Element_INCLUDE */

void Element_INCLUDE::includeFile(ElementContext ctx,ElementAtom *,ElementAtom *name)
 {
  if( Element_BODY *elem_body=ctx.includeFile(*name) ) 
    body_node=(*elem_body);
  else
    body_node=0;
 }

/* struct Element_TYPE */

void Element_TYPE::build(ElementContext ctx,ElementAtom *,ElementAtom *name,ElementAtom *,Element_TYPEDEF *elem_type,ElementAtom *)
 {
  alias_node.init(ctx,*name,*elem_type);
 }

/* struct Element_CONST */

void Element_CONST::build(ElementContext ctx,Element_TYPEDEF *elem_type,ElementAtom *name,ElementAtom *,Element_EXPR *elem_expr,ElementAtom *)
 {
  const_node.init(ctx,*name,*elem_type,*elem_expr);
 }

/* struct Element_RNAME */

void Element_RNAME::start(ElementContext ctx,ElementAtom *name)
 {
  name_node.init(ctx,*name);
  
  name_list=ctx.create<NameNodeList>();
  
  name_list->init(&name_node);
 }

void Element_RNAME::ext(ElementContext ctx,Element_RNAME *elem,ElementAtom *,ElementAtom *name)
 {
  name_node.init(ctx,*name);

  name_list=*elem;
  
  name_list->add(&name_node);
 }

/* struct Element_NAME */

void Element_NAME::rel(ElementContext,Element_RNAME *elem)
 {
  name_ref.init(NameRefNode::Type_rel,*elem);
 }

void Element_NAME::abs(ElementContext,ElementAtom *,Element_RNAME *elem)
 {
  name_ref.init(NameRefNode::Type_abs,*elem);
 }

void Element_NAME::dot(ElementContext,ElementAtom *,ElementAtom *,Element_RNAME *elem)
 {
  name_ref.init(NameRefNode::Type_this,*elem);
 }

void Element_NAME::dots(ElementContext,ElementAtom *dots,ElementAtom *,Element_RNAME *elem)
 {
  name_ref.init_dots(*dots,*elem);
 }

/* struct Element_RQNAME */

void Element_RQNAME::start_Name(ElementContext ctx,ElementAtom *name)
 {
  name_node.init(ctx,*name);
  
  name_list=ctx.create<NameNodeList>();
  
  name_list->init(&name_node);
 }

void Element_RQNAME::start_QName(ElementContext ctx,ElementAtom *name)
 {
  name_node.init_qname(ctx,*name);
  
  name_list=ctx.create<NameNodeList>();
  
  name_list->init_qname(&name_node);
 }

void Element_RQNAME::ext_Name(ElementContext ctx,Element_RQNAME *elem,ElementAtom *,ElementAtom *name)
 {
  name_node.init(ctx,*name);

  name_list=*elem;
  
  name_list->add(&name_node);
 }

void Element_RQNAME::ext_QName(ElementContext ctx,Element_RQNAME *elem,ElementAtom *,ElementAtom *name)
 {
  name_node.init_qname(ctx,*name);

  name_list=*elem;
  
  name_list->add_qname(&name_node);
 }

/* struct Element_QNAME */

void Element_QNAME::rel(ElementContext,Element_RQNAME *elem)
 {
  name_ref.init(NameRefNode::Type_rel,*elem);
 }

void Element_QNAME::abs(ElementContext,ElementAtom *,Element_RQNAME *elem)
 {
  name_ref.init(NameRefNode::Type_abs,*elem);
 }

void Element_QNAME::dot(ElementContext,ElementAtom *,ElementAtom *,Element_RQNAME *elem)
 {
  name_ref.init(NameRefNode::Type_this,*elem);
 }

void Element_QNAME::dots(ElementContext,ElementAtom *dots,ElementAtom *,Element_RQNAME *elem)
 {
  name_ref.init_dots(*dots,*elem);
 }

/* struct Element_INT_TYPE */

void Element_INT_TYPE::type_int(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_sint;
 }

void Element_INT_TYPE::type_sint(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_sint;
 }

void Element_INT_TYPE::type_uint(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_uint;
 }

void Element_INT_TYPE::type_ulen(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_ulen;
 }

void Element_INT_TYPE::type_sint8(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_sint8;
 }

void Element_INT_TYPE::type_uint8(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_uint8;
 }

void Element_INT_TYPE::type_sint16(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_sint16;
 }

void Element_INT_TYPE::type_uint16(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_uint16;
 }

void Element_INT_TYPE::type_sint32(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_sint32;
 }

void Element_INT_TYPE::type_uint32(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_uint32;
 }

void Element_INT_TYPE::type_sint64(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_sint64;
 }

void Element_INT_TYPE::type_uint64(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_uint64;
 }

/* struct Element_BASE_TYPE */

void Element_BASE_TYPE::cast(ElementContext,Element_INT_TYPE *elem)
 {
  base_type=*elem;
 }

void Element_BASE_TYPE::type_text(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_text;
 }

void Element_BASE_TYPE::type_ip(ElementContext,ElementAtom *)
 {
  base_type=TypeNode::Base::Type_ip;
 }

/* struct Element_TYPEDEF */

void Element_TYPEDEF::type_named(ElementContext ctx,Element_NAME *elem_name)
 {
  type_node.init_ref(ctx,*elem_name);
 }

void Element_TYPEDEF::type_base(ElementContext ctx,Element_BASE_TYPE *elem_base_type)
 {
  type_node.init_base(ctx,*elem_base_type);
 }

void Element_TYPEDEF::type_ptr(ElementContext ctx,Element_TYPEDEF *elem_type,ElementAtom *)
 {
  type_node.init_ptr(ctx,*elem_type);
 }

void Element_TYPEDEF::type_polyptr(ElementContext ctx,ElementAtom *,Element_TYPEDEF_LIST *elem_type_list,ElementAtom *,ElementAtom *)
 {
  type_node.init_polyptr(ctx,*elem_type_list);
 }

void Element_TYPEDEF::type_array(ElementContext ctx,Element_TYPEDEF *elem_type,ElementAtom *,ElementAtom *)
 {
  type_node.init_array(ctx,*elem_type);
 }

void Element_TYPEDEF::type_array_len(ElementContext ctx,Element_TYPEDEF *elem_type,ElementAtom *ops,Element_EXPR *elem_expr,ElementAtom *)
 {
  type_node.init_array_len(ctx,*elem_type,*ops,*elem_expr);
 }

void Element_TYPEDEF::type_struct(ElementContext ctx,Element_STRUCT *elem_struct)
 {
  type_node.init_struct(ctx,*elem_struct);
 }

/* struct Element_TYPEDEF_LIST */

void Element_TYPEDEF_LIST::start(ElementContext ctx,Element_TYPEDEF *elem_type)
 {
  node.init(*elem_type);
  
  type_list=ctx.create<TypeList>();
  
  type_list->init(&node);
 }

void Element_TYPEDEF_LIST::ext(ElementContext,Element_TYPEDEF_LIST *elem,ElementAtom *,Element_TYPEDEF *elem_type)
 {
  node.init(*elem_type);
  
  type_list=*elem;
  
  type_list->add(&node);
 }

/* struct Element_STRUCT */

void Element_STRUCT::build(ElementContext ctx,ElementAtom *,ElementAtom *name,ElementAtom *,Element_SBODY *elem_sbody,ElementAtom *)
 {
  struct_node.init(ctx,*name,*elem_sbody);
 }

/* struct Element_SBODY */

void Element_SBODY::start(ElementContext ctx)
 {
  sbody_node=ctx.create<SBodyNode>();
  
  sbody_node->start();
 }

void Element_SBODY::ext(ElementContext,Element_SBODY *elem,Element_TYPE *elem_type)
 {
  sbody_node=*elem;
  
  sbody_node->add(*elem_type);
 }

void Element_SBODY::ext(ElementContext,Element_SBODY *elem,ElementAtom *,Element_CONST *elem_const)
 {
  sbody_node=*elem;
  
  sbody_node->add(*elem_const);
 }

void Element_SBODY::ext(ElementContext,Element_SBODY *elem,Element_STRUCT *elem_struct,ElementAtom *)
 {
  sbody_node=*elem;
  
  sbody_node->add(*elem_struct);
 }

void Element_SBODY::ext(ElementContext ctx,Element_SBODY *elem,Element_TYPEDEF *elem_type,ElementAtom *name,ElementAtom *)
 {
  sbody_node=*elem;
  
  FieldNode *field_node=ctx.create<FieldNode>();
  
  field_node->init(ctx,*name,*elem_type);

  sbody_node->add(field_node);
 }

void Element_SBODY::ext(ElementContext ctx,Element_SBODY *elem,Element_TYPEDEF *elem_type,ElementAtom *name,ElementAtom *,Element_EXPR *elem_expr,ElementAtom *)
 {
  sbody_node=*elem;

  FieldNode *field_node=ctx.create<FieldNode>();
  
  field_node->init(ctx,*name,*elem_type,*elem_expr);
  
  sbody_node->add(field_node);
 }

/* struct Element_EXPR */

void Element_EXPR::cast(ElementContext ctx,ElementAtom *,Element_EXPR *elem,ElementAtom *)
 {
  expr_node.init(ctx,*elem);
 }

void Element_EXPR::cast(ElementContext ctx,Element_QNAME *elem_name)
 {
  expr_node.init_ref(ctx,*elem_name);
 }

void Element_EXPR::cast(ElementContext ctx,Element_LITERAL *elem_lit)
 {
  expr_node.init_lit(ctx,*elem_lit);
 }

void Element_EXPR::opDomain(ElementContext ctx,Element_ITYPE *elem_type,ElementAtom *ops,Element_EXPR *elem,ElementAtom *)
 {
  expr_node.init_domain(ctx,*ops,*elem,elem_type->base_type,elem_type->name_ref);
 }

void Element_EXPR::opSelect(ElementContext ctx,Element_EXPR *elem,ElementAtom *ops,ElementAtom *field)
 {
  expr_node.init_select(ctx,*ops,*elem,*field);
 }

void Element_EXPR::opPtrSelect(ElementContext ctx,Element_EXPR *elem,ElementAtom *ops,ElementAtom *field)
 {
  expr_node.init_ptr_select(ctx,*ops,*elem,*field);
 }

void Element_EXPR::opInd(ElementContext ctx,Element_EXPR *elem1,ElementAtom *ops,Element_EXPR *elem2,ElementAtom *)
 {
  expr_node.init_ind(ctx,*ops,*elem1,*elem2);
 }

void Element_EXPR::cast(ElementContext ctx,ElementAtom *number)
 {
  expr_node.init_number(ctx,*number);
 }

void Element_EXPR::opAst(ElementContext ctx,ElementAtom *ops,Element_EXPR *elem)
 {
  expr_node.init_deref(ctx,*ops,*elem);
 }

void Element_EXPR::opAmp(ElementContext ctx,ElementAtom *ops,Element_EXPR *elem)
 {
  expr_node.init_address(ctx,*ops,*elem);
 }

void Element_EXPR::opPlus(ElementContext ctx,ElementAtom *ops,Element_EXPR *elem)
 {
  expr_node.init_plus(ctx,*ops,*elem);
 }

void Element_EXPR::opMinus(ElementContext ctx,ElementAtom *ops,Element_EXPR *elem)
 {
  expr_node.init_minus(ctx,*ops,*elem);
 }

void Element_EXPR::opMul(ElementContext ctx,Element_EXPR *elem1,ElementAtom *ops,Element_EXPR *elem2)
 {
  expr_node.init_mul(ctx,*ops,*elem1,*elem2);
 }

void Element_EXPR::opDiv(ElementContext ctx,Element_EXPR *elem1,ElementAtom *ops,Element_EXPR *elem2)
 {
  expr_node.init_div(ctx,*ops,*elem1,*elem2);
 }

void Element_EXPR::opRem(ElementContext ctx,Element_EXPR *elem1,ElementAtom *ops,Element_EXPR *elem2)
 {
  expr_node.init_rem(ctx,*ops,*elem1,*elem2);
 }

void Element_EXPR::opAdd(ElementContext ctx,Element_EXPR *elem1,ElementAtom *ops,Element_EXPR *elem2)
 {
  expr_node.init_add(ctx,*ops,*elem1,*elem2);
 }

void Element_EXPR::opSub(ElementContext ctx,Element_EXPR *elem1,ElementAtom *ops,Element_EXPR *elem2)
 {
  expr_node.init_sub(ctx,*ops,*elem1,*elem2);
 }

void Element_EXPR::emptyExprList(ElementContext ctx,ElementAtom *ops,ElementAtom *)
 {
  expr_node.init_noname_list(ctx,*ops);
 }

void Element_EXPR::buildExprList(ElementContext ctx,ElementAtom *ops,Element_EXPR_LIST *elem_list,ElementAtom *)
 {
  expr_node.init_noname_list(ctx,*ops,*elem_list);
 }

void Element_EXPR::buildNamedExprList(ElementContext ctx,ElementAtom *ops,Element_NAMED_EXPR_LIST *elem_list,ElementAtom *)
 {
  expr_node.init_named_list(ctx,*ops,*elem_list);
 }

void Element_EXPR::applyEmpty(ElementContext ctx,Element_EXPR *elem_expr,ElementAtom *ops,ElementAtom *)
 {
  expr_node.init_apply_named_list(ctx,*ops,*elem_expr);
 }

void Element_EXPR::applyNamedExprList(ElementContext ctx,Element_EXPR *elem_expr,ElementAtom *ops,Element_NAMED_EXPR_LIST *elem_list,ElementAtom *)
 {
  expr_node.init_apply_named_list(ctx,*ops,*elem_expr,*elem_list);
 }

/* struct Element_EXPR_LIST */

void Element_EXPR_LIST::start(ElementContext ctx,Element_EXPR *elem_expr)
 {
  node.init(*elem_expr);
  
  list=ctx.create<ExprList>();
  
  list->init(&node);
 }

void Element_EXPR_LIST::ext(ElementContext,Element_EXPR_LIST *elem,ElementAtom *,Element_EXPR *elem_expr)
 {
  node.init(*elem_expr);
  
  list=*elem;
  
  list->add(&node);
 }

/* struct Element_NAMED_EXPR */

void Element_NAMED_EXPR::build(ElementContext ctx,ElementAtom *,ElementAtom *name,ElementAtom *,Element_EXPR *elem_expr)
 {
  node.init(ctx,*name,*elem_expr);
 }

/* struct Element_NAMED_EXPR_LIST */

void Element_NAMED_EXPR_LIST::start(ElementContext ctx,Element_NAMED_EXPR *elem_item)
 {
  list=ctx.create<NamedExprList>();
  
  list->init(*elem_item);
 }

void Element_NAMED_EXPR_LIST::ext(ElementContext,Element_NAMED_EXPR_LIST *elem,ElementAtom *,Element_NAMED_EXPR *elem_item)
 {
  list=*elem;
  
  list->add(*elem_item);
 }

/* struct Element_ITYPE */

void Element_ITYPE::type_int(ElementContext,Element_INT_TYPE *elem_type)
 {
  base_type=*elem_type;
  name_ref=0;
 }

void Element_ITYPE::type_named(ElementContext,Element_QNAME *elem_name)
 {
  base_type=TypeNode::Base::Type_none;
  name_ref=*elem_name;
 }

/* struct Element_LITERAL */

void Element_LITERAL::cast_null(ElementContext ctx,ElementAtom *lit)
 {
  ptr=ctx.create<LitNull>(*lit);
 }

void Element_LITERAL::cast_String(ElementContext ctx,ElementAtom *lit)
 {
  ptr=ctx.create<LitString>(*lit);
 }

void Element_LITERAL::buildIP(ElementContext ctx,ElementAtom *lit1,ElementAtom *,ElementAtom *lit2,ElementAtom *,ElementAtom *lit3,ElementAtom *,ElementAtom *lit4)
 {
  ptr=ctx.create<LitIP>(*lit1,*lit2,*lit3,*lit4);
 }

} // namespace DDL2
} // namespace CCore

