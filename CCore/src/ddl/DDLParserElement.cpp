/* DDLParserElement.cpp */
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
 
#include <CCore/inc/ddl/DDLParser.h>

namespace CCore {
namespace DDL {

/* struct Element_BODY */

void Element_BODY::startBody(ElementContext)
 {
  body_node.start();
 }

void Element_BODY::extBody_SCOPE(ElementContext,Element_BODY *prev_body,Element_SCOPE *elem_scope)
 {
  body_node=prev_body->body_node;
  
  body_node.add(*elem_scope);
 }

void Element_BODY::extBody_INCLUDE(ElementContext,Element_BODY *prev_body,Element_INCLUDE *elem_include)
 {
  body_node=prev_body->body_node;
  
  if( BodyNode *node=*elem_include ) body_node.add(node);
 }

void Element_BODY::extBody_TYPE(ElementContext,Element_BODY *prev_body,Element_TYPE *elem_alias)
 {
  body_node=prev_body->body_node;
  
  body_node.add(*elem_alias);
 }

void Element_BODY::extBody_CONST(ElementContext,Element_BODY *prev_body,Element_CONST *elem_const)
 {
  body_node=prev_body->body_node;
  
  body_node.add(*elem_const);
 }

void Element_BODY::extBody_STRUCT(ElementContext,Element_BODY *prev_body,Element_STRUCT *elem_struct,ElementAtom *)
 {
  body_node=prev_body->body_node;
  
  body_node.add(*elem_struct);
 }

/* struct Element_SCOPE */

void Element_SCOPE::buildScope(ElementContext ctx,ElementAtom *,ElementAtom *name,ElementAtom *,Element_BODY *elem,ElementAtom *)
 {
  scope_node.init(ctx,*name,*elem);
 }

/* struct Element_INCLUDE */

void Element_INCLUDE::includeFile(ElementContext ctx,ElementAtom *,ElementAtom *name)
 {
  Element_BODY *elem=ctx.includeFile(*name);
  
  if( elem ) 
    body_node=*elem;
  else
    body_node=0;
 }

/* struct Element_TYPE */

void Element_TYPE::defType(ElementContext ctx,ElementAtom *,ElementAtom *name,ElementAtom *,Element_TYPEDEF *elem,ElementAtom *)
 {
  alias_node.init(ctx,*name,*elem);
 }

/* struct Element_CONST */

void Element_CONST::defConst(ElementContext ctx,Element_TYPEDEF *elem_type,ElementAtom *name,ElementAtom *,Element_EXPR *elem_expr,ElementAtom *)
 {
  const_node.init(ctx,*name,*elem_type,*elem_expr);
 }

/* struct Element_RNAME */

void Element_RNAME::startName(ElementContext ctx,ElementAtom *name)
 {
  name_node.init(ctx,*name);
  
  name_list.init();
  
  name_list.add(&name_node);
 }

void Element_RNAME::extName(ElementContext ctx,Element_RNAME *elem,ElementAtom *,ElementAtom *name)
 {
  name_node.init(ctx,*name);
  
  name_list=elem->name_list;
  
  name_list.add(&name_node);
 }

/* struct Element_NAME */

void Element_NAME::relName(ElementContext,Element_RNAME *elem)
 {
  name.init(NameRef::Type_rel,*elem);
 }

void Element_NAME::absName(ElementContext,ElementAtom *,Element_RNAME *elem)
 {
  name.init(NameRef::Type_abs,*elem);
 }

void Element_NAME::dotName(ElementContext,ElementAtom *,ElementAtom *,Element_RNAME *elem)
 {
  name.init(NameRef::Type_this,*elem);
 }

void Element_NAME::dotsName(ElementContext,ElementAtom *dots,ElementAtom *,Element_RNAME *elem)
 {
  name.init_dots(*elem,*dots);
 }

/* struct Element_INAME */

void Element_INAME::intName(ElementContext ctx,ElementAtom *)
 {
  init_suint<imp_int>(ctx);
 }

void Element_INAME::sintName(ElementContext ctx,ElementAtom *)
 {
  init_suint<imp_sint>(ctx);
 }

void Element_INAME::uintName(ElementContext ctx,ElementAtom *)
 {
  init_suint<imp_uint>(ctx);
 }

void Element_INAME::ulenName(ElementContext ctx,ElementAtom *)
 {
  init_suint<imp_ulen>(ctx);
 }

void Element_INAME::sint8Name(ElementContext ctx,ElementAtom *)
 {
  init_suint<imp_sint8>(ctx);
 }

void Element_INAME::uint8Name(ElementContext ctx,ElementAtom *)
 {
  init_suint<imp_uint8>(ctx);
 }

void Element_INAME::sint16Name(ElementContext ctx,ElementAtom *)
 {
  init_suint<imp_sint16>(ctx);
 }

void Element_INAME::uint16Name(ElementContext ctx,ElementAtom *)
 {
  init_suint<imp_uint16>(ctx);
 }

void Element_INAME::sint32Name(ElementContext ctx,ElementAtom *)
 {
  init_suint<imp_sint32>(ctx);
 }

void Element_INAME::uint32Name(ElementContext ctx,ElementAtom *)
 {
  init_suint<imp_uint32>(ctx);
 }

void Element_INAME::sint64Name(ElementContext ctx,ElementAtom *)
 {
  init_suint<imp_sint64>(ctx);
 }

void Element_INAME::uint64Name(ElementContext ctx,ElementAtom *)
 {
  init_suint<imp_uint64>(ctx);
 }
  
/* struct Element_TNAME */

void Element_TNAME::cast_INAME(ElementContext,Element_INAME *elem)
 {
  type_node=elem->type_node;
 }

void Element_TNAME::textName(ElementContext ctx,ElementAtom *)
 {
  init<TypeNode_text>(ctx);
 }

void Element_TNAME::ipName(ElementContext ctx,ElementAtom *)
 {
  init<TypeNode_ip>(ctx);
 }

/* struct Element_TYPEDEF */

void Element_TYPEDEF::namedType(ElementContext ctx,Element_NAME *elem)
 {
  init<TypeNode_ref>(ctx,ctx,*elem);
 }

void Element_TYPEDEF::baseType(ElementContext,Element_TNAME *elem)
 {
  type_node=elem->type_node;
 }

void Element_TYPEDEF::ptrType(ElementContext ctx,Element_TYPEDEF *elem,ElementAtom *)
 {
  init<TypeNode_ptr>(ctx,*elem);
 }

void Element_TYPEDEF::arrayType(ElementContext ctx,Element_TYPEDEF *elem,ElementAtom *,ElementAtom *)
 {
  init<TypeNode_array>(ctx,*elem);
 }

void Element_TYPEDEF::arrayLenType(ElementContext ctx,Element_TYPEDEF *elem_type,ElementAtom *obr,Element_EXPR *elem_expr,ElementAtom *)
 {
  init<TypeNode_array_len>(ctx,ctx,*elem_type,*elem_expr,*obr);
 }

void Element_TYPEDEF::structType(ElementContext ctx,Element_STRUCT *elem)
 {
  init<TypeNode_struct>(ctx,*elem);
 }
  
/* struct Element_STRUCT */

void Element_STRUCT::buildStruct(ElementContext ctx,ElementAtom *,ElementAtom *name,ElementAtom *,Element_SBODY *elem,ElementAtom *)
 {
  struct_node.init(ctx,*name,*elem);
 }

/* struct Element_SBODY */

void Element_SBODY::startSBody(ElementContext)
 {
  sbody_node.start();
 }

void Element_SBODY::extSBody_TYPE(ElementContext,Element_SBODY *prev_sbody,Element_TYPE *elem_alias)
 {
  sbody_node=prev_sbody->sbody_node;
  
  sbody_node.add(*elem_alias);
 }

void Element_SBODY::extSBody_CONST(ElementContext,Element_SBODY *prev_sbody,ElementAtom *,Element_CONST *elem_const)
 {
  sbody_node=prev_sbody->sbody_node;
  
  sbody_node.add(*elem_const);
 }

void Element_SBODY::extSBody_STRUCT(ElementContext,Element_SBODY *prev_sbody,Element_STRUCT *elem_struct,ElementAtom *)
 {
  sbody_node=prev_sbody->sbody_node;
  
  sbody_node.add(*elem_struct);
 }

void Element_SBODY::extSBody_field(ElementContext ctx,Element_SBODY *prev_sbody,Element_TYPEDEF *elem_type,ElementAtom *name,ElementAtom *)
 {
  sbody_node=prev_sbody->sbody_node;
  
  FieldNode *node=ctx.create<FieldNode>();
  
  node->init(ctx,*name,*elem_type);
  
  sbody_node.add(node);
 }

void Element_SBODY::extSBody_fieldVal(ElementContext ctx,Element_SBODY *prev_sbody,Element_TYPEDEF *elem_type,ElementAtom *name,ElementAtom *,Element_EXPR *elem_expr,ElementAtom *)
 {
  sbody_node=prev_sbody->sbody_node;
  
  FieldNode *node=ctx.create<FieldNode>();
  
  node->init(ctx,*name,*elem_type,*elem_expr);
  
  sbody_node.add(node);
 }

/* struct Element_EXPR */

void Element_EXPR::cast_EXPR_ADD(ElementContext,Element_EXPR_ADD *elem)
 {
  expr_node=elem->expr_node;
 }

void Element_EXPR::emptyExprList(ElementContext ctx,ElementAtom *ops,ElementAtom *)
 {
  init<ExprNode_noname_list>(ctx,ctx,*ops);
 }

void Element_EXPR::buildExprList(ElementContext ctx,ElementAtom *ops,Element_ELIST *elem,ElementAtom *)
 {
  init<ExprNode_noname_list>(ctx,ctx,*ops,*elem);
 }

void Element_EXPR::buildNamedExprList(ElementContext ctx,ElementAtom *ops,Element_NELIST *elem,ElementAtom *)
 {
  init<ExprNode_named_list>(ctx,ctx,*ops,*elem);
 }

void Element_EXPR::applyEmpty(ElementContext ctx,Element_EXPR *elem,ElementAtom *ops,ElementAtom *)
 {
  init<ExprNode_apply_named_list>(ctx,ctx,*ops,*elem);
 }

void Element_EXPR::applyNamedExprList(ElementContext ctx,Element_EXPR *elem,ElementAtom *ops,Element_NELIST *elem_list,ElementAtom *)
 {
  init<ExprNode_apply_named_list>(ctx,ctx,*ops,*elem,*elem_list);
 }

/* struct Element_EXPR_ADD */

void Element_EXPR_ADD::cast_EXPR_MUL(ElementContext,Element_EXPR_MUL *elem)
 {
  expr_node=elem->expr_node;
 }

void Element_EXPR_ADD::opAdd(ElementContext ctx,Element_EXPR_ADD *elem1,ElementAtom *ops,Element_EXPR_MUL *elem2)
 {
  init<ExprNode_add>(ctx,ctx,*ops,*elem1,*elem2);
 }

void Element_EXPR_ADD::opSub(ElementContext ctx,Element_EXPR_ADD *elem1,ElementAtom *ops,Element_EXPR_MUL *elem2)
 {
  init<ExprNode_sub>(ctx,ctx,*ops,*elem1,*elem2);
 }

/* struct Element_EXPR_MUL */

void Element_EXPR_MUL::cast_EXPR_UN(ElementContext,Element_EXPR_UN *elem)
 {
  expr_node=elem->expr_node;
 }

void Element_EXPR_MUL::opMul(ElementContext ctx,Element_EXPR_MUL *elem1,ElementAtom *ops,Element_EXPR_UN *elem2)
 {
  init<ExprNode_mul>(ctx,ctx,*ops,*elem1,*elem2);
 }

void Element_EXPR_MUL::opDiv(ElementContext ctx,Element_EXPR_MUL *elem1,ElementAtom *ops,Element_EXPR_UN *elem2)
 {
  init<ExprNode_div>(ctx,ctx,*ops,*elem1,*elem2);
 }

void Element_EXPR_MUL::opRem(ElementContext ctx,Element_EXPR_MUL *elem1,ElementAtom *ops,Element_EXPR_UN *elem2)
 {
  init<ExprNode_rem>(ctx,ctx,*ops,*elem1,*elem2);
 }

/* struct Element_EXPR_UN */

void Element_EXPR_UN::cast_EXPR_POST(ElementContext,Element_EXPR_POST *elem)
 {
  expr_node=elem->expr_node;
 }

void Element_EXPR_UN::opAst(ElementContext ctx,ElementAtom *ops,Element_EXPR_UN *elem)
 {
  init<ExprNode_deref>(ctx,ctx,*ops,*elem);
 }

void Element_EXPR_UN::opAmp(ElementContext ctx,ElementAtom *ops,Element_EXPR_UN *elem)
 {
  init<ExprNode_address>(ctx,ctx,*ops,*elem);
 }

void Element_EXPR_UN::opPlus(ElementContext ctx,ElementAtom *ops,Element_EXPR_UN *elem)
 {
  init<ExprNode_plus>(ctx,ctx,*ops,*elem);
 }

void Element_EXPR_UN::opMinus(ElementContext ctx,ElementAtom *ops,Element_EXPR_UN *elem)
 {
  init<ExprNode_minus>(ctx,ctx,*ops,*elem);
 }

/* struct Element_EXPR_POST */

void Element_EXPR_POST::cast_EXPR_NNPOST(ElementContext,Element_EXPR_NNPOST *elem)
 {
  expr_node=elem->expr_node;
 }

void Element_EXPR_POST::cast_Number(ElementContext ctx,ElementAtom *number)
 {
  init<ExprNode_number>(ctx,ctx,*number);
 }

/* struct Element_EXPR_NNPOST */

void Element_EXPR_NNPOST::cast_EXPR_NNPRIM(ElementContext,Element_EXPR_NNPRIM *elem)
 {
  expr_node=elem->expr_node;
 }

void Element_EXPR_NNPOST::opInd(ElementContext ctx,Element_EXPR_POST *elem1,ElementAtom *ops,Element_EXPR *elem2,ElementAtom *)
 {
  init<ExprNode_ind>(ctx,ctx,*ops,*elem1,*elem2);
 }

void Element_EXPR_NNPOST::opSelect(ElementContext ctx,Element_EXPR_NNPOST *elem,ElementAtom *ops,ElementAtom *name)
 {
  init<ExprNode_select>(ctx,ctx,*ops,*elem,*name);
 }

void Element_EXPR_NNPOST::opPtrSelect(ElementContext ctx,Element_EXPR_NNPOST *elem,ElementAtom *ops,ElementAtom *name)
 {
  init<ExprNode_ptr_select>(ctx,ctx,*ops,*elem,*name);
 }

/* struct Element_EXPR_NNPRIM */

void Element_EXPR_NNPRIM::cast_EXPR(ElementContext,ElementAtom *,Element_EXPR *elem,ElementAtom *)
 {
  expr_node=elem->expr_node;
 }

void Element_EXPR_NNPRIM::cast_NAME(ElementContext ctx,Element_NAME *elem)
 {
  init<ExprNode_var>(ctx,ctx,*elem);
 }

void Element_EXPR_NNPRIM::cast_NNLIT(ElementContext,Element_NNLIT *elem)
 {
  expr_node=elem->expr_node;
 }

void Element_EXPR_NNPRIM::opDomain(ElementContext ctx,Element_ITYPE *elem_domain,ElementAtom *ops,Element_EXPR *elem_expr,ElementAtom *)
 {
  init<ExprNode_domain>(ctx,ctx,*ops,*elem_expr,*elem_domain);
 }

/* struct Element_ELIST */

void Element_ELIST::startExprList(ElementContext,Element_EXPR *elem)
 {
  node.init(*elem);
  
  list.init();
  
  list.add(&node);
 }

void Element_ELIST::extExprList(ElementContext,Element_ELIST *elem_list,ElementAtom *,Element_EXPR *elem)
 {
  node.init(*elem);
  
  list=elem_list->list;
  
  list.add(&node);
 }

/* struct Element_NEXPR */

void Element_NEXPR::nameExpr(ElementContext ctx,ElementAtom *,ElementAtom *name,ElementAtom *,Element_EXPR *elem)
 {
  node.init(ctx,*name,*elem);
 }

/* struct Element_NELIST */

void Element_NELIST::startNamedExprList(ElementContext,Element_NEXPR *elem)
 {
  list.init();
  
  list.add(*elem);
 }

void Element_NELIST::extNamedExprList(ElementContext,Element_NELIST *elem_list,ElementAtom *,Element_NEXPR *elem)
 {
  list=elem_list->list;
  
  list.add(*elem);
 }

/* struct Element_ITYPE */

void Element_ITYPE::type_NAME(ElementContext ctx,Element_NAME *elem)
 {
  domain_node.init(ctx,*elem);
 }

void Element_ITYPE::type_INAME(ElementContext,Element_INAME *elem)
 {
  domain_node.init(*elem);
 }

/* struct Element_NNLIT */

void Element_NNLIT::cast_null(ElementContext ctx,ElementAtom *ops)
 {
  init<ExprNode_null>(ctx,ctx,*ops);
 }

void Element_NNLIT::cast_String(ElementContext ctx,ElementAtom *string)
 {
  init<ExprNode_string>(ctx,ctx,*string);
 }

void Element_NNLIT::buildIP(ElementContext ctx,ElementAtom *number1,ElementAtom *,ElementAtom *number2,ElementAtom *,ElementAtom *number3,ElementAtom *,ElementAtom *number4)
 {
  init<ExprNode_ip>(ctx,ctx,*number1,*number2,*number3,*number4);
 }

} // namespace DDL
} // namespace CCore

