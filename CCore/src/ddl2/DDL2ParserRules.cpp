/* DDL2ParserRules.cpp */
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

/* class Parser */

void Parser::doRule(int rule,unsigned element)
 {
  ElementBase *elem_base;

  switch( rule )
    {
     case 0 :
      {
       Element_BODY *elem=ctx.create<Element_BODY>();


       elem->start(ctx);

       elem_base=elem;
      }
     break;

     case 1 :
      {
       Element_BODY *elem=ctx.create<Element_BODY>();

       Element_SCOPE *arg1=pop();
       Element_BODY *arg0=pop();

       elem->ext(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 2 :
      {
       Element_BODY *elem=ctx.create<Element_BODY>();

       Element_INCLUDE *arg1=pop();
       Element_BODY *arg0=pop();

       elem->ext(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 3 :
      {
       Element_BODY *elem=ctx.create<Element_BODY>();

       Element_TYPE *arg1=pop();
       Element_BODY *arg0=pop();

       elem->ext(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 4 :
      {
       Element_BODY *elem=ctx.create<Element_BODY>();

       Element_CONST *arg1=pop();
       Element_BODY *arg0=pop();

       elem->ext(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 5 :
      {
       Element_BODY *elem=ctx.create<Element_BODY>();

       ElementAtom *arg2=pop();
       Element_STRUCT *arg1=pop();
       Element_BODY *arg0=pop();

       elem->ext(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 6 :
      {
       Element_SCOPE *elem=ctx.create<Element_SCOPE>();

       ElementAtom *arg4=pop();
       Element_BODY *arg3=pop();
       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       ElementAtom *arg0=pop();

       elem->build(ctx,arg0,arg1,arg2,arg3,arg4);

       elem_base=elem;
      }
     break;

     case 7 :
      {
       Element_INCLUDE *elem=ctx.create<Element_INCLUDE>();

       ElementAtom *arg1=pop();
       ElementAtom *arg0=pop();

       elem->includeFile(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 8 :
      {
       Element_TYPE *elem=ctx.create<Element_TYPE>();

       ElementAtom *arg4=pop();
       Element_TYPEDEF *arg3=pop();
       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       ElementAtom *arg0=pop();

       elem->build(ctx,arg0,arg1,arg2,arg3,arg4);

       elem_base=elem;
      }
     break;

     case 9 :
      {
       Element_CONST *elem=ctx.create<Element_CONST>();

       ElementAtom *arg4=pop();
       Element_EXPR *arg3=pop();
       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       Element_TYPEDEF *arg0=pop();

       elem->build(ctx,arg0,arg1,arg2,arg3,arg4);

       elem_base=elem;
      }
     break;

     case 10 :
      {
       Element_RNAME *elem=ctx.create<Element_RNAME>();

       ElementAtom *arg0=pop();

       elem->start(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 11 :
      {
       Element_RNAME *elem=ctx.create<Element_RNAME>();

       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       Element_RNAME *arg0=pop();

       elem->ext(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 12 :
      {
       Element_NAME *elem=ctx.create<Element_NAME>();

       Element_RNAME *arg0=pop();

       elem->rel(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 13 :
      {
       Element_NAME *elem=ctx.create<Element_NAME>();

       Element_RNAME *arg1=pop();
       ElementAtom *arg0=pop();

       elem->abs(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 14 :
      {
       Element_NAME *elem=ctx.create<Element_NAME>();

       Element_RNAME *arg2=pop();
       ElementAtom *arg1=pop();
       ElementAtom *arg0=pop();

       elem->dot(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 15 :
      {
       Element_NAME *elem=ctx.create<Element_NAME>();

       Element_RNAME *arg2=pop();
       ElementAtom *arg1=pop();
       ElementAtom *arg0=pop();

       elem->dots(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 16 :
      {
       Element_RQNAME *elem=ctx.create<Element_RQNAME>();

       ElementAtom *arg0=pop();

       elem->start_Name(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 17 :
      {
       Element_RQNAME *elem=ctx.create<Element_RQNAME>();

       ElementAtom *arg0=pop();

       elem->start_QName(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 18 :
      {
       Element_RQNAME *elem=ctx.create<Element_RQNAME>();

       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       Element_RQNAME *arg0=pop();

       elem->ext_Name(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 19 :
      {
       Element_RQNAME *elem=ctx.create<Element_RQNAME>();

       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       Element_RQNAME *arg0=pop();

       elem->ext_QName(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 20 :
      {
       Element_QNAME *elem=ctx.create<Element_QNAME>();

       Element_RQNAME *arg0=pop();

       elem->rel(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 21 :
      {
       Element_QNAME *elem=ctx.create<Element_QNAME>();

       Element_RQNAME *arg1=pop();
       ElementAtom *arg0=pop();

       elem->abs(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 22 :
      {
       Element_QNAME *elem=ctx.create<Element_QNAME>();

       Element_RQNAME *arg2=pop();
       ElementAtom *arg1=pop();
       ElementAtom *arg0=pop();

       elem->dot(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 23 :
      {
       Element_QNAME *elem=ctx.create<Element_QNAME>();

       Element_RQNAME *arg2=pop();
       ElementAtom *arg1=pop();
       ElementAtom *arg0=pop();

       elem->dots(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 24 :
      {
       Element_INT_TYPE *elem=ctx.create<Element_INT_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_int(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 25 :
      {
       Element_INT_TYPE *elem=ctx.create<Element_INT_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_sint(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 26 :
      {
       Element_INT_TYPE *elem=ctx.create<Element_INT_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_uint(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 27 :
      {
       Element_INT_TYPE *elem=ctx.create<Element_INT_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_ulen(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 28 :
      {
       Element_INT_TYPE *elem=ctx.create<Element_INT_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_sint8(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 29 :
      {
       Element_INT_TYPE *elem=ctx.create<Element_INT_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_uint8(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 30 :
      {
       Element_INT_TYPE *elem=ctx.create<Element_INT_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_sint16(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 31 :
      {
       Element_INT_TYPE *elem=ctx.create<Element_INT_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_uint16(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 32 :
      {
       Element_INT_TYPE *elem=ctx.create<Element_INT_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_sint32(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 33 :
      {
       Element_INT_TYPE *elem=ctx.create<Element_INT_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_uint32(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 34 :
      {
       Element_INT_TYPE *elem=ctx.create<Element_INT_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_sint64(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 35 :
      {
       Element_INT_TYPE *elem=ctx.create<Element_INT_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_uint64(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 36 :
      {
       Element_BASE_TYPE *elem=ctx.create<Element_BASE_TYPE>();

       Element_INT_TYPE *arg0=pop();

       elem->cast(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 37 :
      {
       Element_BASE_TYPE *elem=ctx.create<Element_BASE_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_text(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 38 :
      {
       Element_BASE_TYPE *elem=ctx.create<Element_BASE_TYPE>();

       ElementAtom *arg0=pop();

       elem->type_ip(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 39 :
      {
       Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

       Element_NAME *arg0=pop();

       elem->type_named(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 40 :
      {
       Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

       Element_BASE_TYPE *arg0=pop();

       elem->type_base(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 41 :
      {
       Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

       ElementAtom *arg1=pop();
       Element_TYPEDEF *arg0=pop();

       elem->type_ptr(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 42 :
      {
       Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

       ElementAtom *arg3=pop();
       ElementAtom *arg2=pop();
       Element_TYPEDEF_LIST *arg1=pop();
       ElementAtom *arg0=pop();

       elem->type_polyptr(ctx,arg0,arg1,arg2,arg3);

       elem_base=elem;
      }
     break;

     case 43 :
      {
       Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       Element_TYPEDEF *arg0=pop();

       elem->type_array(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 44 :
      {
       Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

       ElementAtom *arg3=pop();
       Element_EXPR *arg2=pop();
       ElementAtom *arg1=pop();
       Element_TYPEDEF *arg0=pop();

       elem->type_array_len(ctx,arg0,arg1,arg2,arg3);

       elem_base=elem;
      }
     break;

     case 45 :
      {
       Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

       Element_STRUCT *arg0=pop();

       elem->type_struct(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 46 :
      {
       Element_TYPEDEF_LIST *elem=ctx.create<Element_TYPEDEF_LIST>();

       Element_TYPEDEF *arg0=pop();

       elem->start(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 47 :
      {
       Element_TYPEDEF_LIST *elem=ctx.create<Element_TYPEDEF_LIST>();

       Element_TYPEDEF *arg2=pop();
       ElementAtom *arg1=pop();
       Element_TYPEDEF_LIST *arg0=pop();

       elem->ext(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 48 :
      {
       Element_STRUCT *elem=ctx.create<Element_STRUCT>();

       ElementAtom *arg4=pop();
       Element_SBODY *arg3=pop();
       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       ElementAtom *arg0=pop();

       elem->build(ctx,arg0,arg1,arg2,arg3,arg4);

       elem_base=elem;
      }
     break;

     case 49 :
      {
       Element_SBODY *elem=ctx.create<Element_SBODY>();


       elem->start(ctx);

       elem_base=elem;
      }
     break;

     case 50 :
      {
       Element_SBODY *elem=ctx.create<Element_SBODY>();

       Element_TYPE *arg1=pop();
       Element_SBODY *arg0=pop();

       elem->ext(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 51 :
      {
       Element_SBODY *elem=ctx.create<Element_SBODY>();

       Element_CONST *arg2=pop();
       ElementAtom *arg1=pop();
       Element_SBODY *arg0=pop();

       elem->ext(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 52 :
      {
       Element_SBODY *elem=ctx.create<Element_SBODY>();

       ElementAtom *arg2=pop();
       Element_STRUCT *arg1=pop();
       Element_SBODY *arg0=pop();

       elem->ext(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 53 :
      {
       Element_SBODY *elem=ctx.create<Element_SBODY>();

       ElementAtom *arg3=pop();
       ElementAtom *arg2=pop();
       Element_TYPEDEF *arg1=pop();
       Element_SBODY *arg0=pop();

       elem->ext(ctx,arg0,arg1,arg2,arg3);

       elem_base=elem;
      }
     break;

     case 54 :
      {
       Element_SBODY *elem=ctx.create<Element_SBODY>();

       ElementAtom *arg5=pop();
       Element_EXPR *arg4=pop();
       ElementAtom *arg3=pop();
       ElementAtom *arg2=pop();
       Element_TYPEDEF *arg1=pop();
       Element_SBODY *arg0=pop();

       elem->ext(ctx,arg0,arg1,arg2,arg3,arg4,arg5);

       elem_base=elem;
      }
     break;

     case 55 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       ElementAtom *arg2=pop();
       Element_EXPR *arg1=pop();
       ElementAtom *arg0=pop();

       elem->cast(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 56 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       Element_QNAME *arg0=pop();

       elem->cast(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 57 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       Element_LITERAL *arg0=pop();

       elem->cast(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 58 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       ElementAtom *arg3=pop();
       Element_EXPR *arg2=pop();
       ElementAtom *arg1=pop();
       Element_ITYPE *arg0=pop();

       elem->opDomain(ctx,arg0,arg1,arg2,arg3);

       elem_base=elem;
      }
     break;

     case 59 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       Element_EXPR *arg0=pop();

       elem->opSelect(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 60 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       Element_EXPR *arg0=pop();

       elem->opPtrSelect(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 61 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       ElementAtom *arg3=pop();
       Element_EXPR *arg2=pop();
       ElementAtom *arg1=pop();
       Element_EXPR *arg0=pop();

       elem->opInd(ctx,arg0,arg1,arg2,arg3);

       elem_base=elem;
      }
     break;

     case 62 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       ElementAtom *arg0=pop();

       elem->cast(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 63 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       Element_EXPR *arg1=pop();
       ElementAtom *arg0=pop();

       elem->opAst(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 64 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       Element_EXPR *arg1=pop();
       ElementAtom *arg0=pop();

       elem->opAmp(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 65 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       Element_EXPR *arg1=pop();
       ElementAtom *arg0=pop();

       elem->opPlus(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 66 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       Element_EXPR *arg1=pop();
       ElementAtom *arg0=pop();

       elem->opMinus(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 67 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       Element_EXPR *arg2=pop();
       ElementAtom *arg1=pop();
       Element_EXPR *arg0=pop();

       elem->opMul(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 68 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       Element_EXPR *arg2=pop();
       ElementAtom *arg1=pop();
       Element_EXPR *arg0=pop();

       elem->opDiv(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 69 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       Element_EXPR *arg2=pop();
       ElementAtom *arg1=pop();
       Element_EXPR *arg0=pop();

       elem->opRem(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 70 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       Element_EXPR *arg2=pop();
       ElementAtom *arg1=pop();
       Element_EXPR *arg0=pop();

       elem->opAdd(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 71 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       Element_EXPR *arg2=pop();
       ElementAtom *arg1=pop();
       Element_EXPR *arg0=pop();

       elem->opSub(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 72 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       ElementAtom *arg1=pop();
       ElementAtom *arg0=pop();

       elem->emptyExprList(ctx,arg0,arg1);

       elem_base=elem;
      }
     break;

     case 73 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       ElementAtom *arg2=pop();
       Element_EXPR_LIST *arg1=pop();
       ElementAtom *arg0=pop();

       elem->buildExprList(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 74 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       ElementAtom *arg2=pop();
       Element_NAMED_EXPR_LIST *arg1=pop();
       ElementAtom *arg0=pop();

       elem->buildNamedExprList(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 75 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       Element_EXPR *arg0=pop();

       elem->applyEmpty(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 76 :
      {
       Element_EXPR *elem=ctx.create<Element_EXPR>();

       ElementAtom *arg3=pop();
       Element_NAMED_EXPR_LIST *arg2=pop();
       ElementAtom *arg1=pop();
       Element_EXPR *arg0=pop();

       elem->applyNamedExprList(ctx,arg0,arg1,arg2,arg3);

       elem_base=elem;
      }
     break;

     case 77 :
      {
       Element_EXPR_LIST *elem=ctx.create<Element_EXPR_LIST>();

       Element_EXPR *arg0=pop();

       elem->start(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 78 :
      {
       Element_EXPR_LIST *elem=ctx.create<Element_EXPR_LIST>();

       Element_EXPR *arg2=pop();
       ElementAtom *arg1=pop();
       Element_EXPR_LIST *arg0=pop();

       elem->ext(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 79 :
      {
       Element_NAMED_EXPR *elem=ctx.create<Element_NAMED_EXPR>();

       Element_EXPR *arg3=pop();
       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       ElementAtom *arg0=pop();

       elem->build(ctx,arg0,arg1,arg2,arg3);

       elem_base=elem;
      }
     break;

     case 80 :
      {
       Element_NAMED_EXPR_LIST *elem=ctx.create<Element_NAMED_EXPR_LIST>();

       Element_NAMED_EXPR *arg0=pop();

       elem->start(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 81 :
      {
       Element_NAMED_EXPR_LIST *elem=ctx.create<Element_NAMED_EXPR_LIST>();

       Element_NAMED_EXPR *arg2=pop();
       ElementAtom *arg1=pop();
       Element_NAMED_EXPR_LIST *arg0=pop();

       elem->ext(ctx,arg0,arg1,arg2);

       elem_base=elem;
      }
     break;

     case 82 :
      {
       Element_ITYPE *elem=ctx.create<Element_ITYPE>();

       Element_INT_TYPE *arg0=pop();

       elem->type_int(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 83 :
      {
       Element_ITYPE *elem=ctx.create<Element_ITYPE>();

       Element_QNAME *arg0=pop();

       elem->type_named(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 84 :
      {
       Element_LITERAL *elem=ctx.create<Element_LITERAL>();

       ElementAtom *arg0=pop();

       elem->cast_null(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 85 :
      {
       Element_LITERAL *elem=ctx.create<Element_LITERAL>();

       ElementAtom *arg0=pop();

       elem->cast_String(ctx,arg0);

       elem_base=elem;
      }
     break;

     case 86 :
      {
       Element_LITERAL *elem=ctx.create<Element_LITERAL>();

       ElementAtom *arg6=pop();
       ElementAtom *arg5=pop();
       ElementAtom *arg4=pop();
       ElementAtom *arg3=pop();
       ElementAtom *arg2=pop();
       ElementAtom *arg1=pop();
       ElementAtom *arg0=pop();

       elem->buildIP(ctx,arg0,arg1,arg2,arg3,arg4,arg5,arg6);

       elem_base=elem;
      }
     break;

     default: return;
    }

  push(elem_base,Transition(stack->state,element));
 }

} // namespace DDL2
} // namespace CCore
