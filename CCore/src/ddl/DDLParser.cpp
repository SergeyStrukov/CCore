/* DDLParser.cpp */ 
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
#include <CCore/inc/ddl/DDLMsgReport.h>

namespace CCore {
namespace DDL {

/* enum AtomClass */

const char * GetTextDesc(AtomClass ac)
 {
  switch( ac )
    {
     case Atom_Nothing   : return "no-atom";
     
     case Atom_Number    : return "Number";
     case Atom_String    : return "String";
     case Atom_FileName  : return "FileName";
     case Atom_Name      : return "Name";
     case Atom_Dots      : return "Dots";
     
     case Atom_int       : return "int";
     case Atom_sint      : return "sint";
     case Atom_uint      : return "uint";
     case Atom_ulen      : return "ulen";
     
     case Atom_sint8     : return "sint8";
     case Atom_sint16    : return "sint16";
     case Atom_sint32    : return "sint32";
     case Atom_sint64    : return "sint64";
     case Atom_uint8     : return "uint8";
     case Atom_uint16    : return "uint16";
     case Atom_uint32    : return "uint32";
     case Atom_uint64    : return "uint64";
     
     case Atom_text      : return "text";
     case Atom_ip        : return "ip";
     case Atom_struct    : return "struct";
     case Atom_type      : return "type";
     case Atom_null      : return "null";
     case Atom_scope     : return "scope";
     case Atom_include   : return "include";
     case Atom_const     : return "const";
     
     case Atom_asterisk  : return "*";
     case Atom_comma     : return ",";
     case Atom_dot       : return ".";
     case Atom_semicolon : return ";";
     case Atom_assign    : return "=";
     case Atom_arrow     : return "->";
     case Atom_plus      : return "+";
     case Atom_minus     : return "-";
     case Atom_address   : return "&";
     case Atom_pound     : return "#";
     case Atom_div       : return "/";
     case Atom_rem       : return "%";
     case Atom_obr       : return "(";
     case Atom_cbr       : return ")";
     case Atom_sq_obr    : return "[";
     case Atom_sq_cbr    : return "]";
     case Atom_fig_obr   : return "{";
     case Atom_fig_cbr   : return "}";
     
     default: return "???";
    }
 }

/* struct Atom */

namespace Private_DDLParser {

inline bool Begin(StrLen &) { return true; }

template <class ... CC>
bool Begin(StrLen &str,char ch,CC ... cc)
 {
  if( !str || *str!=ch ) return false;

  ++str;
  
  return Begin(str,cc...);
 }

inline bool Equal(StrLen str) { return !str; }

template <class ... CC>
bool Equal(StrLen str,char ch,CC ... cc)
 {
  if( !str || *str!=ch ) return false;

  ++str;
  
  return Equal(str,cc...);
 }

} // namespace Private_DDLParser

using namespace Private_DDLParser;

AtomClass Atom::GetWordClass(StrLen str)
 {
  if( !str ) return Atom_Nothing;

  switch( str[0] )
    {
     case 'c' :
      {
       ++str;
       
       if( Equal(str,'o','n','s','t') ) return Atom_const;
      }
     break;
     
     case 'i' :
      {
       ++str;
       
       if( !str ) break;
       
       switch( str[0] )
         {
          case 'n' :
           {
            ++str;
            
            if( !str ) break;
            
            switch( str[0] )
              {
               case 't' :
                {
                 if( str.len==1 ) return Atom_int;
                }
               break;
                
               case 'c' :
                {
                 ++str;
                 
                 if( Equal(str,'l','u','d','e') ) return Atom_include;
                }
               break;
              }
           }
          break;
           
          case 'p' :
           {
            if( str.len==1 ) return Atom_ip;
           }
          break;
         }
      }
     break;
      
     case 's' :
      {
       ++str;
       
       if( !str ) break;
       
       switch( str[0] )
         {
          case 'i' :
           {
            ++str;
            
            if( Begin(str,'n','t') )
              {
               if( !str ) return Atom_sint;
               
               if( Equal(str,'8') ) return Atom_sint8;
               if( Equal(str,'1','6') ) return Atom_sint16;
               if( Equal(str,'3','2') ) return Atom_sint32;
               if( Equal(str,'6','4') ) return Atom_sint64;
              }
           }
          break;
          
          case 'c' :
           {
            ++str;
            
            if( Equal(str,'o','p','e') ) return Atom_scope;
           }
          break;
          
          case 't' :
           {
            ++str;
            
            if( Equal(str,'r','u','c','t') ) return Atom_struct;
           }
          break;
         }
      }
     break; 
      
     case 'u' :
      {
       ++str;
       
       if( !str ) break;
       
       switch( str[0] )
         {
          case 'i' :
           {
            ++str;
            
            if( Begin(str,'n','t') )
              {
               if( !str ) return Atom_uint;
               
               if( Equal(str,'8') ) return Atom_uint8;
               if( Equal(str,'1','6') ) return Atom_uint16;
               if( Equal(str,'3','2') ) return Atom_uint32;
               if( Equal(str,'6','4') ) return Atom_uint64;
              }
           }
          break;
          
          case 'l' :
           {
            ++str;
            
            if( Equal(str,'e','n') ) return Atom_ulen;
           }
          break;
         }
      }
     break;
     
     case 't' :
      {
       ++str;
       
       if( !str ) break;
       
       switch( str[0] )
         {
          case 'e' :
           {
            ++str;
            
            if( Equal(str,'x','t') ) return Atom_text;
           }
          break;
           
          case 'y' :
           {
            ++str;
            
            if( Equal(str,'p','e') ) return Atom_type;
           }
          break;
         }
      }
     break;
     
     case 'n' :
      {
       ++str;
       
       if( Equal(str,'u','l','l') ) return Atom_null;
      }
     break;
    }
  
  return Atom_Name;
 }

AtomClass Atom::GetPunctSymClass(StrLen str)
 {
  if( str.len!=1 ) return Atom_Nothing;

  switch( str[0] )
    {
     case '*' : return Atom_asterisk;
     case ',' : return Atom_comma;
     case ';' : return Atom_semicolon;
     case '=' : return Atom_assign;
     case '+' : return Atom_plus;
     case '-' : return Atom_minus;
     case '&' : return Atom_address;
     case '#' : return Atom_pound;
     case '/' : return Atom_div;
     case '%' : return Atom_rem;
     case '(' : return Atom_obr;
     case ')' : return Atom_cbr;
     case '[' : return Atom_sq_obr;
     case ']' : return Atom_sq_cbr;
     case '{' : return Atom_fig_obr;
     case '}' : return Atom_fig_cbr;
    }
  
  return Atom_Nothing;
 }

AtomClass Atom::GetAtomClass(const Token &token)
 {
  switch( token.tc )
    {
     case Token_Dec :
     case Token_Bin :
     case Token_Hex : return Atom_Number;
     
     case Token_Word : return GetWordClass(token.str);
      
     case Token_PunctSym : return GetPunctSymClass(token.str);
     case Token_PunctArrow : return Atom_arrow;
     case Token_PunctDots : return (token.str.len==1)?Atom_dot:Atom_Dots;
      
     case Token_BString : return Atom_FileName;
      
     case Token_SString :
     case Token_DString : return Atom_String;
      
     default: return Atom_Nothing; 
    }
 }

/* struct ParserContext */

void ParserContext::PretextFile::printPos(PrintBase &out,TextPos pos)
 {
  Printf(out,"pretext#;",pos);
 }

Element_BODY * ParserContext::parseText(FileId *file_id,StrLen text,StrLen pretext)
 {
  Tokenizer pretok(msg,&pretext_file,pretext);
  Tokenizer tok(msg,file_id,text);
  
  Parser parser(this,file_id);

  while( +pretok )
    {
     Atom atom(pretok.next());
     
     if( !atom )
       {
        if( atom.token.tc==Token_Other ) 
          {
           printfError("\nTokenizer error\n");
           
           return 0;
          }
       }
     else
       {
        Parser::Result result;

        while( (result=parser.next(atom))==Parser::ResultRule );
        
        if( result==Parser::ResultAbort || !ok ) 
          {
           printfError("\nParser error\n");
           
           return 0;
          }
       }
    }
  
  while( +tok )
    {
     Atom atom(tok.next());
     
     if( !atom )
       {
        if( atom.token.tc==Token_Other ) 
          {
           printfError("\nTokenizer error\n");
           
           return 0;
          }
       }
     else
       {
        Parser::Result result;

        while( (result=parser.next(atom))==Parser::ResultRule );
        
        if( result==Parser::ResultAbort || !ok ) 
          {
           printfError("\nParser error\n");
           
           return 0;
          }
       }
    }
  
  Parser::Result result;

  while( (result=parser.complete(tok.getPos()))==Parser::ResultRule );
  
  if( result==Parser::ResultAbort || !ok ) 
    {
     printfError("\nParser error\n");
     
     return 0;
    }
  
  return parser.getBody();
 }

Element_BODY * ParserContext::includeFile(FileId *file_id,const Token &file_name)
 {
  File file=openFile(file_id,file_name);

  if( !file ) 
    {
     printfError("\nParserContext error\n");
     
     return 0;
    }
  
  return parseText(file.file_id,file.text);
 }

auto ParserContext::openFile(StrLen) -> File
 {
  printfError("ParserContext : cannot open file, no file system\n");
  
  return Nothing;
 }

auto ParserContext::openFile(FileId *file_id,const Token &file_name) -> File
 {
  printfError("ParserContext #; #; : cannot open file, no file system\n",PrintPos(file_id,file_name.pos),file_name.str);
  
  return Nothing;
 }

ParserResult ParserContext::parseFile(StrLen file_name,StrLen pretext)
 {
  MsgReport report(msg);
  
  try
    {
     ParserResult ret;
     
     ok=true;
     error_cap=ErrorMsgCap;
     
     reset();
     
     {
      File file=openFile(file_name);
     
      if( !file ) 
        {
         printfError("\nParserContext error\n");
         
         return ParserResult();
        }
     
      Element_BODY *elem=parseText(file.file_id,file.text,pretext);
      
      if( !elem ) return ParserResult();
      
      BodyNode *body=&elem->body_node;
      
      if( !complete(body) ) 
        {
         printfError("\nName link error\n");
         
         return ParserResult();
        }
      
      ret.body=body;
      ret.list=expr_list.getList();
      ret.rev_list=expr_list.getRevList();
     }
     
     report.guard();
     
     return ret;
    }
  catch(CatchType)
    {
     report.print("\nFatal error\n");
     
     return ParserResult();
    }
 }

/* class Parser */

void Parser::push(ElementBase *elem,ulen state)
 {
  elem->prev=stack;
  stack=elem;
  
  elem->state=state;
 }

AnyElement Parser::pop()
 {
  ElementBase *elem=stack;
  
  stack=elem->prev;
  
  return AnyElement(elem);
 }

void Parser::shift(const Atom &atom,ulen state)
 {
  push(ctx.create<ElementAtom>(ctx,atom),state);
 }

Element_BODY * Parser::elem_startBody()
 {
  Element_BODY *elem=ctx.create<Element_BODY>();

  elem->startBody(ctx);

  return elem;
 }

Element_BODY * Parser::elem_extBody_SCOPE(Element_BODY *arg1,Element_SCOPE *arg2)
 {
  Element_BODY *elem=ctx.create<Element_BODY>();

  elem->extBody_SCOPE(ctx,arg1,arg2);

  return elem;
 }

Element_BODY * Parser::elem_extBody_INCLUDE(Element_BODY *arg1,Element_INCLUDE *arg2)
 {
  Element_BODY *elem=ctx.create<Element_BODY>();

  elem->extBody_INCLUDE(ctx,arg1,arg2);

  return elem;
 }

Element_BODY * Parser::elem_extBody_TYPE(Element_BODY *arg1,Element_TYPE *arg2)
 {
  Element_BODY *elem=ctx.create<Element_BODY>();

  elem->extBody_TYPE(ctx,arg1,arg2);

  return elem;
 }

Element_BODY * Parser::elem_extBody_CONST(Element_BODY *arg1,Element_CONST *arg2)
 {
  Element_BODY *elem=ctx.create<Element_BODY>();

  elem->extBody_CONST(ctx,arg1,arg2);

  return elem;
 }

Element_BODY * Parser::elem_extBody_STRUCT(Element_BODY *arg1,Element_STRUCT *arg2,ElementAtom *arg3)
 {
  Element_BODY *elem=ctx.create<Element_BODY>();

  elem->extBody_STRUCT(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_SCOPE * Parser::elem_buildScope(ElementAtom *arg1,ElementAtom *arg2,ElementAtom *arg3,Element_BODY *arg4,ElementAtom *arg5)
 {
  Element_SCOPE *elem=ctx.create<Element_SCOPE>();

  elem->buildScope(ctx,arg1,arg2,arg3,arg4,arg5);

  return elem;
 }

Element_INCLUDE * Parser::elem_includeFile(ElementAtom *arg1,ElementAtom *arg2)
 {
  Element_INCLUDE *elem=ctx.create<Element_INCLUDE>();

  elem->includeFile(ctx,arg1,arg2);

  return elem;
 }

Element_TYPE * Parser::elem_defType(ElementAtom *arg1,ElementAtom *arg2,ElementAtom *arg3,Element_TYPEDEF *arg4,ElementAtom *arg5)
 {
  Element_TYPE *elem=ctx.create<Element_TYPE>();

  elem->defType(ctx,arg1,arg2,arg3,arg4,arg5);

  return elem;
 }

Element_CONST * Parser::elem_defConst(Element_TYPEDEF *arg1,ElementAtom *arg2,ElementAtom *arg3,Element_EXPR *arg4,ElementAtom *arg5)
 {
  Element_CONST *elem=ctx.create<Element_CONST>();

  elem->defConst(ctx,arg1,arg2,arg3,arg4,arg5);

  return elem;
 }

Element_RNAME * Parser::elem_startName(ElementAtom *arg1)
 {
  Element_RNAME *elem=ctx.create<Element_RNAME>();

  elem->startName(ctx,arg1);

  return elem;
 }

Element_RNAME * Parser::elem_extName(Element_RNAME *arg1,ElementAtom *arg2,ElementAtom *arg3)
 {
  Element_RNAME *elem=ctx.create<Element_RNAME>();

  elem->extName(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_NAME * Parser::elem_relName(Element_RNAME *arg1)
 {
  Element_NAME *elem=ctx.create<Element_NAME>();

  elem->relName(ctx,arg1);

  return elem;
 }

Element_NAME * Parser::elem_absName(ElementAtom *arg1,Element_RNAME *arg2)
 {
  Element_NAME *elem=ctx.create<Element_NAME>();

  elem->absName(ctx,arg1,arg2);

  return elem;
 }

Element_NAME * Parser::elem_dotName(ElementAtom *arg1,ElementAtom *arg2,Element_RNAME *arg3)
 {
  Element_NAME *elem=ctx.create<Element_NAME>();

  elem->dotName(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_NAME * Parser::elem_dotsName(ElementAtom *arg1,ElementAtom *arg2,Element_RNAME *arg3)
 {
  Element_NAME *elem=ctx.create<Element_NAME>();

  elem->dotsName(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_INAME * Parser::elem_intName(ElementAtom *arg1)
 {
  Element_INAME *elem=ctx.create<Element_INAME>();

  elem->intName(ctx,arg1);

  return elem;
 }

Element_INAME * Parser::elem_sintName(ElementAtom *arg1)
 {
  Element_INAME *elem=ctx.create<Element_INAME>();

  elem->sintName(ctx,arg1);

  return elem;
 }

Element_INAME * Parser::elem_uintName(ElementAtom *arg1)
 {
  Element_INAME *elem=ctx.create<Element_INAME>();

  elem->uintName(ctx,arg1);

  return elem;
 }

Element_INAME * Parser::elem_ulenName(ElementAtom *arg1)
 {
  Element_INAME *elem=ctx.create<Element_INAME>();

  elem->ulenName(ctx,arg1);

  return elem;
 }

Element_INAME * Parser::elem_sint8Name(ElementAtom *arg1)
 {
  Element_INAME *elem=ctx.create<Element_INAME>();

  elem->sint8Name(ctx,arg1);

  return elem;
 }

Element_INAME * Parser::elem_uint8Name(ElementAtom *arg1)
 {
  Element_INAME *elem=ctx.create<Element_INAME>();

  elem->uint8Name(ctx,arg1);

  return elem;
 }

Element_INAME * Parser::elem_sint16Name(ElementAtom *arg1)
 {
  Element_INAME *elem=ctx.create<Element_INAME>();

  elem->sint16Name(ctx,arg1);

  return elem;
 }

Element_INAME * Parser::elem_uint16Name(ElementAtom *arg1)
 {
  Element_INAME *elem=ctx.create<Element_INAME>();

  elem->uint16Name(ctx,arg1);

  return elem;
 }

Element_INAME * Parser::elem_sint32Name(ElementAtom *arg1)
 {
  Element_INAME *elem=ctx.create<Element_INAME>();

  elem->sint32Name(ctx,arg1);

  return elem;
 }

Element_INAME * Parser::elem_uint32Name(ElementAtom *arg1)
 {
  Element_INAME *elem=ctx.create<Element_INAME>();

  elem->uint32Name(ctx,arg1);

  return elem;
 }

Element_INAME * Parser::elem_sint64Name(ElementAtom *arg1)
 {
  Element_INAME *elem=ctx.create<Element_INAME>();

  elem->sint64Name(ctx,arg1);

  return elem;
 }

Element_INAME * Parser::elem_uint64Name(ElementAtom *arg1)
 {
  Element_INAME *elem=ctx.create<Element_INAME>();

  elem->uint64Name(ctx,arg1);

  return elem;
 }

Element_TNAME * Parser::elem_cast_INAME(Element_INAME *arg1)
 {
  Element_TNAME *elem=ctx.create<Element_TNAME>();

  elem->cast_INAME(ctx,arg1);

  return elem;
 }

Element_TNAME * Parser::elem_textName(ElementAtom *arg1)
 {
  Element_TNAME *elem=ctx.create<Element_TNAME>();

  elem->textName(ctx,arg1);

  return elem;
 }

Element_TNAME * Parser::elem_ipName(ElementAtom *arg1)
 {
  Element_TNAME *elem=ctx.create<Element_TNAME>();

  elem->ipName(ctx,arg1);

  return elem;
 }

Element_TYPEDEF * Parser::elem_namedType(Element_NAME *arg1)
 {
  Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

  elem->namedType(ctx,arg1);

  return elem;
 }

Element_TYPEDEF * Parser::elem_baseType(Element_TNAME *arg1)
 {
  Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

  elem->baseType(ctx,arg1);

  return elem;
 }

Element_TYPEDEF * Parser::elem_ptrType(Element_TYPEDEF *arg1,ElementAtom *arg2)
 {
  Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

  elem->ptrType(ctx,arg1,arg2);

  return elem;
 }

Element_TYPEDEF * Parser::elem_arrayType(Element_TYPEDEF *arg1,ElementAtom *arg2,ElementAtom *arg3)
 {
  Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

  elem->arrayType(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_TYPEDEF * Parser::elem_arrayLenType(Element_TYPEDEF *arg1,ElementAtom *arg2,Element_EXPR *arg3,ElementAtom *arg4)
 {
  Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

  elem->arrayLenType(ctx,arg1,arg2,arg3,arg4);

  return elem;
 }

Element_TYPEDEF * Parser::elem_structType(Element_STRUCT *arg1)
 {
  Element_TYPEDEF *elem=ctx.create<Element_TYPEDEF>();

  elem->structType(ctx,arg1);

  return elem;
 }

Element_STRUCT * Parser::elem_buildStruct(ElementAtom *arg1,ElementAtom *arg2,ElementAtom *arg3,Element_SBODY *arg4,ElementAtom *arg5)
 {
  Element_STRUCT *elem=ctx.create<Element_STRUCT>();

  elem->buildStruct(ctx,arg1,arg2,arg3,arg4,arg5);

  return elem;
 }

Element_SBODY * Parser::elem_startSBody()
 {
  Element_SBODY *elem=ctx.create<Element_SBODY>();

  elem->startSBody(ctx);

  return elem;
 }

Element_SBODY * Parser::elem_extSBody_TYPE(Element_SBODY *arg1,Element_TYPE *arg2)
 {
  Element_SBODY *elem=ctx.create<Element_SBODY>();

  elem->extSBody_TYPE(ctx,arg1,arg2);

  return elem;
 }

Element_SBODY * Parser::elem_extSBody_CONST(Element_SBODY *arg1,ElementAtom *arg2,Element_CONST *arg3)
 {
  Element_SBODY *elem=ctx.create<Element_SBODY>();

  elem->extSBody_CONST(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_SBODY * Parser::elem_extSBody_STRUCT(Element_SBODY *arg1,Element_STRUCT *arg2,ElementAtom *arg3)
 {
  Element_SBODY *elem=ctx.create<Element_SBODY>();

  elem->extSBody_STRUCT(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_SBODY * Parser::elem_extSBody_field(Element_SBODY *arg1,Element_TYPEDEF *arg2,ElementAtom *arg3,ElementAtom *arg4)
 {
  Element_SBODY *elem=ctx.create<Element_SBODY>();

  elem->extSBody_field(ctx,arg1,arg2,arg3,arg4);

  return elem;
 }

Element_SBODY * Parser::elem_extSBody_fieldVal(Element_SBODY *arg1,Element_TYPEDEF *arg2,ElementAtom *arg3,ElementAtom *arg4,Element_EXPR *arg5,ElementAtom *arg6)
 {
  Element_SBODY *elem=ctx.create<Element_SBODY>();

  elem->extSBody_fieldVal(ctx,arg1,arg2,arg3,arg4,arg5,arg6);

  return elem;
 }

Element_EXPR * Parser::elem_cast_EXPR_ADD(Element_EXPR_ADD *arg1)
 {
  Element_EXPR *elem=ctx.create<Element_EXPR>();

  elem->cast_EXPR_ADD(ctx,arg1);

  return elem;
 }

Element_EXPR * Parser::elem_emptyExprList(ElementAtom *arg1,ElementAtom *arg2)
 {
  Element_EXPR *elem=ctx.create<Element_EXPR>();

  elem->emptyExprList(ctx,arg1,arg2);

  return elem;
 }

Element_EXPR * Parser::elem_buildExprList(ElementAtom *arg1,Element_ELIST *arg2,ElementAtom *arg3)
 {
  Element_EXPR *elem=ctx.create<Element_EXPR>();

  elem->buildExprList(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_EXPR * Parser::elem_buildNamedExprList(ElementAtom *arg1,Element_NELIST *arg2,ElementAtom *arg3)
 {
  Element_EXPR *elem=ctx.create<Element_EXPR>();

  elem->buildNamedExprList(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_EXPR * Parser::elem_applyEmpty(Element_EXPR *arg1,ElementAtom *arg2,ElementAtom *arg3)
 {
  Element_EXPR *elem=ctx.create<Element_EXPR>();

  elem->applyEmpty(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_EXPR * Parser::elem_applyNamedExprList(Element_EXPR *arg1,ElementAtom *arg2,Element_NELIST *arg3,ElementAtom *arg4)
 {
  Element_EXPR *elem=ctx.create<Element_EXPR>();

  elem->applyNamedExprList(ctx,arg1,arg2,arg3,arg4);

  return elem;
 }

Element_EXPR_ADD * Parser::elem_cast_EXPR_MUL(Element_EXPR_MUL *arg1)
 {
  Element_EXPR_ADD *elem=ctx.create<Element_EXPR_ADD>();

  elem->cast_EXPR_MUL(ctx,arg1);

  return elem;
 }

Element_EXPR_ADD * Parser::elem_opAdd(Element_EXPR_ADD *arg1,ElementAtom *arg2,Element_EXPR_MUL *arg3)
 {
  Element_EXPR_ADD *elem=ctx.create<Element_EXPR_ADD>();

  elem->opAdd(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_EXPR_ADD * Parser::elem_opSub(Element_EXPR_ADD *arg1,ElementAtom *arg2,Element_EXPR_MUL *arg3)
 {
  Element_EXPR_ADD *elem=ctx.create<Element_EXPR_ADD>();

  elem->opSub(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_EXPR_MUL * Parser::elem_cast_EXPR_UN(Element_EXPR_UN *arg1)
 {
  Element_EXPR_MUL *elem=ctx.create<Element_EXPR_MUL>();

  elem->cast_EXPR_UN(ctx,arg1);

  return elem;
 }

Element_EXPR_MUL * Parser::elem_opMul(Element_EXPR_MUL *arg1,ElementAtom *arg2,Element_EXPR_UN *arg3)
 {
  Element_EXPR_MUL *elem=ctx.create<Element_EXPR_MUL>();

  elem->opMul(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_EXPR_MUL * Parser::elem_opDiv(Element_EXPR_MUL *arg1,ElementAtom *arg2,Element_EXPR_UN *arg3)
 {
  Element_EXPR_MUL *elem=ctx.create<Element_EXPR_MUL>();

  elem->opDiv(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_EXPR_MUL * Parser::elem_opRem(Element_EXPR_MUL *arg1,ElementAtom *arg2,Element_EXPR_UN *arg3)
 {
  Element_EXPR_MUL *elem=ctx.create<Element_EXPR_MUL>();

  elem->opRem(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_EXPR_UN * Parser::elem_cast_EXPR_POST(Element_EXPR_POST *arg1)
 {
  Element_EXPR_UN *elem=ctx.create<Element_EXPR_UN>();

  elem->cast_EXPR_POST(ctx,arg1);

  return elem;
 }

Element_EXPR_UN * Parser::elem_opAst(ElementAtom *arg1,Element_EXPR_UN *arg2)
 {
  Element_EXPR_UN *elem=ctx.create<Element_EXPR_UN>();

  elem->opAst(ctx,arg1,arg2);

  return elem;
 }

Element_EXPR_UN * Parser::elem_opAmp(ElementAtom *arg1,Element_EXPR_UN *arg2)
 {
  Element_EXPR_UN *elem=ctx.create<Element_EXPR_UN>();

  elem->opAmp(ctx,arg1,arg2);

  return elem;
 }

Element_EXPR_UN * Parser::elem_opPlus(ElementAtom *arg1,Element_EXPR_UN *arg2)
 {
  Element_EXPR_UN *elem=ctx.create<Element_EXPR_UN>();

  elem->opPlus(ctx,arg1,arg2);

  return elem;
 }

Element_EXPR_UN * Parser::elem_opMinus(ElementAtom *arg1,Element_EXPR_UN *arg2)
 {
  Element_EXPR_UN *elem=ctx.create<Element_EXPR_UN>();

  elem->opMinus(ctx,arg1,arg2);

  return elem;
 }

Element_EXPR_POST * Parser::elem_cast_EXPR_NNPOST(Element_EXPR_NNPOST *arg1)
 {
  Element_EXPR_POST *elem=ctx.create<Element_EXPR_POST>();

  elem->cast_EXPR_NNPOST(ctx,arg1);

  return elem;
 }

Element_EXPR_POST * Parser::elem_cast_Number(ElementAtom *arg1)
 {
  Element_EXPR_POST *elem=ctx.create<Element_EXPR_POST>();

  elem->cast_Number(ctx,arg1);

  return elem;
 }

Element_EXPR_NNPOST * Parser::elem_cast_EXPR_NNPRIM(Element_EXPR_NNPRIM *arg1)
 {
  Element_EXPR_NNPOST *elem=ctx.create<Element_EXPR_NNPOST>();

  elem->cast_EXPR_NNPRIM(ctx,arg1);

  return elem;
 }

Element_EXPR_NNPOST * Parser::elem_opInd(Element_EXPR_POST *arg1,ElementAtom *arg2,Element_EXPR *arg3,ElementAtom *arg4)
 {
  Element_EXPR_NNPOST *elem=ctx.create<Element_EXPR_NNPOST>();

  elem->opInd(ctx,arg1,arg2,arg3,arg4);

  return elem;
 }

Element_EXPR_NNPOST * Parser::elem_opSelect(Element_EXPR_NNPOST *arg1,ElementAtom *arg2,ElementAtom *arg3)
 {
  Element_EXPR_NNPOST *elem=ctx.create<Element_EXPR_NNPOST>();

  elem->opSelect(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_EXPR_NNPOST * Parser::elem_opPtrSelect(Element_EXPR_NNPOST *arg1,ElementAtom *arg2,ElementAtom *arg3)
 {
  Element_EXPR_NNPOST *elem=ctx.create<Element_EXPR_NNPOST>();

  elem->opPtrSelect(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_EXPR_NNPRIM * Parser::elem_cast_EXPR(ElementAtom *arg1,Element_EXPR *arg2,ElementAtom *arg3)
 {
  Element_EXPR_NNPRIM *elem=ctx.create<Element_EXPR_NNPRIM>();

  elem->cast_EXPR(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_EXPR_NNPRIM * Parser::elem_cast_NAME(Element_NAME *arg1)
 {
  Element_EXPR_NNPRIM *elem=ctx.create<Element_EXPR_NNPRIM>();

  elem->cast_NAME(ctx,arg1);

  return elem;
 }

Element_EXPR_NNPRIM * Parser::elem_cast_NNLIT(Element_NNLIT *arg1)
 {
  Element_EXPR_NNPRIM *elem=ctx.create<Element_EXPR_NNPRIM>();

  elem->cast_NNLIT(ctx,arg1);

  return elem;
 }

Element_EXPR_NNPRIM * Parser::elem_opDomain(Element_ITYPE *arg1,ElementAtom *arg2,Element_EXPR *arg3,ElementAtom *arg4)
 {
  Element_EXPR_NNPRIM *elem=ctx.create<Element_EXPR_NNPRIM>();

  elem->opDomain(ctx,arg1,arg2,arg3,arg4);

  return elem;
 }

Element_ELIST * Parser::elem_startExprList(Element_EXPR *arg1)
 {
  Element_ELIST *elem=ctx.create<Element_ELIST>();

  elem->startExprList(ctx,arg1);

  return elem;
 }

Element_ELIST * Parser::elem_extExprList(Element_ELIST *arg1,ElementAtom *arg2,Element_EXPR *arg3)
 {
  Element_ELIST *elem=ctx.create<Element_ELIST>();

  elem->extExprList(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_NEXPR * Parser::elem_nameExpr(ElementAtom *arg1,ElementAtom *arg2,ElementAtom *arg3,Element_EXPR *arg4)
 {
  Element_NEXPR *elem=ctx.create<Element_NEXPR>();

  elem->nameExpr(ctx,arg1,arg2,arg3,arg4);

  return elem;
 }

Element_NELIST * Parser::elem_startNamedExprList(Element_NEXPR *arg1)
 {
  Element_NELIST *elem=ctx.create<Element_NELIST>();

  elem->startNamedExprList(ctx,arg1);

  return elem;
 }

Element_NELIST * Parser::elem_extNamedExprList(Element_NELIST *arg1,ElementAtom *arg2,Element_NEXPR *arg3)
 {
  Element_NELIST *elem=ctx.create<Element_NELIST>();

  elem->extNamedExprList(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_ITYPE * Parser::elem_type_NAME(Element_NAME *arg1)
 {
  Element_ITYPE *elem=ctx.create<Element_ITYPE>();

  elem->type_NAME(ctx,arg1);

  return elem;
 }

Element_ITYPE * Parser::elem_type_INAME(Element_INAME *arg1)
 {
  Element_ITYPE *elem=ctx.create<Element_ITYPE>();

  elem->type_INAME(ctx,arg1);

  return elem;
 }

Element_NNLIT * Parser::elem_cast_null(ElementAtom *arg1)
 {
  Element_NNLIT *elem=ctx.create<Element_NNLIT>();

  elem->cast_null(ctx,arg1);

  return elem;
 }

Element_NNLIT * Parser::elem_cast_String(ElementAtom *arg1)
 {
  Element_NNLIT *elem=ctx.create<Element_NNLIT>();

  elem->cast_String(ctx,arg1);

  return elem;
 }

Element_NNLIT * Parser::elem_buildIP(ElementAtom *arg1,ElementAtom *arg2,ElementAtom *arg3,ElementAtom *arg4,ElementAtom *arg5,ElementAtom *arg6,ElementAtom *arg7)
 {
  Element_NNLIT *elem=ctx.create<Element_NNLIT>();

  elem->buildIP(ctx,arg1,arg2,arg3,arg4,arg5,arg6,arg7);

  return elem;
 }

void Parser::do_startBody()
 {
  Element_BODY *elem=elem_startBody();

  ulen new_state=Element_BODY::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extBody_SCOPE()
 {
  Element_SCOPE *arg2=pop();
  Element_BODY *arg1=pop();

  Element_BODY *elem=elem_extBody_SCOPE(arg1,arg2);

  ulen new_state=Element_BODY::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extBody_INCLUDE()
 {
  Element_INCLUDE *arg2=pop();
  Element_BODY *arg1=pop();

  Element_BODY *elem=elem_extBody_INCLUDE(arg1,arg2);

  ulen new_state=Element_BODY::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extBody_TYPE()
 {
  Element_TYPE *arg2=pop();
  Element_BODY *arg1=pop();

  Element_BODY *elem=elem_extBody_TYPE(arg1,arg2);

  ulen new_state=Element_BODY::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extBody_CONST()
 {
  Element_CONST *arg2=pop();
  Element_BODY *arg1=pop();

  Element_BODY *elem=elem_extBody_CONST(arg1,arg2);

  ulen new_state=Element_BODY::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extBody_STRUCT()
 {
  ElementAtom *arg3=pop();
  Element_STRUCT *arg2=pop();
  Element_BODY *arg1=pop();

  Element_BODY *elem=elem_extBody_STRUCT(arg1,arg2,arg3);

  ulen new_state=Element_BODY::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_buildScope()
 {
  ElementAtom *arg5=pop();
  Element_BODY *arg4=pop();
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  ElementAtom *arg1=pop();

  Element_SCOPE *elem=elem_buildScope(arg1,arg2,arg3,arg4,arg5);

  ulen new_state=Element_SCOPE::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_includeFile()
 {
  ElementAtom *arg2=pop();
  ElementAtom *arg1=pop();

  Element_INCLUDE *elem=elem_includeFile(arg1,arg2);

  ulen new_state=Element_INCLUDE::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_defType()
 {
  ElementAtom *arg5=pop();
  Element_TYPEDEF *arg4=pop();
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  ElementAtom *arg1=pop();

  Element_TYPE *elem=elem_defType(arg1,arg2,arg3,arg4,arg5);

  ulen new_state=Element_TYPE::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_defConst()
 {
  ElementAtom *arg5=pop();
  Element_EXPR *arg4=pop();
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  Element_TYPEDEF *arg1=pop();

  Element_CONST *elem=elem_defConst(arg1,arg2,arg3,arg4,arg5);

  ulen new_state=Element_CONST::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_startName()
 {
  ElementAtom *arg1=pop();

  Element_RNAME *elem=elem_startName(arg1);

  ulen new_state=Element_RNAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extName()
 {
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  Element_RNAME *arg1=pop();

  Element_RNAME *elem=elem_extName(arg1,arg2,arg3);

  ulen new_state=Element_RNAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_relName()
 {
  Element_RNAME *arg1=pop();

  Element_NAME *elem=elem_relName(arg1);

  ulen new_state=Element_NAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_absName()
 {
  Element_RNAME *arg2=pop();
  ElementAtom *arg1=pop();

  Element_NAME *elem=elem_absName(arg1,arg2);

  ulen new_state=Element_NAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_dotName()
 {
  Element_RNAME *arg3=pop();
  ElementAtom *arg2=pop();
  ElementAtom *arg1=pop();

  Element_NAME *elem=elem_dotName(arg1,arg2,arg3);

  ulen new_state=Element_NAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_dotsName()
 {
  Element_RNAME *arg3=pop();
  ElementAtom *arg2=pop();
  ElementAtom *arg1=pop();

  Element_NAME *elem=elem_dotsName(arg1,arg2,arg3);

  ulen new_state=Element_NAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_intName()
 {
  ElementAtom *arg1=pop();

  Element_INAME *elem=elem_intName(arg1);

  ulen new_state=Element_INAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_sintName()
 {
  ElementAtom *arg1=pop();

  Element_INAME *elem=elem_sintName(arg1);

  ulen new_state=Element_INAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_uintName()
 {
  ElementAtom *arg1=pop();

  Element_INAME *elem=elem_uintName(arg1);

  ulen new_state=Element_INAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_ulenName()
 {
  ElementAtom *arg1=pop();

  Element_INAME *elem=elem_ulenName(arg1);

  ulen new_state=Element_INAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_sint8Name()
 {
  ElementAtom *arg1=pop();

  Element_INAME *elem=elem_sint8Name(arg1);

  ulen new_state=Element_INAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_uint8Name()
 {
  ElementAtom *arg1=pop();

  Element_INAME *elem=elem_uint8Name(arg1);

  ulen new_state=Element_INAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_sint16Name()
 {
  ElementAtom *arg1=pop();

  Element_INAME *elem=elem_sint16Name(arg1);

  ulen new_state=Element_INAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_uint16Name()
 {
  ElementAtom *arg1=pop();

  Element_INAME *elem=elem_uint16Name(arg1);

  ulen new_state=Element_INAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_sint32Name()
 {
  ElementAtom *arg1=pop();

  Element_INAME *elem=elem_sint32Name(arg1);

  ulen new_state=Element_INAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_uint32Name()
 {
  ElementAtom *arg1=pop();

  Element_INAME *elem=elem_uint32Name(arg1);

  ulen new_state=Element_INAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_sint64Name()
 {
  ElementAtom *arg1=pop();

  Element_INAME *elem=elem_sint64Name(arg1);

  ulen new_state=Element_INAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_uint64Name()
 {
  ElementAtom *arg1=pop();

  Element_INAME *elem=elem_uint64Name(arg1);

  ulen new_state=Element_INAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_INAME()
 {
  Element_INAME *arg1=pop();

  Element_TNAME *elem=elem_cast_INAME(arg1);

  ulen new_state=Element_TNAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_textName()
 {
  ElementAtom *arg1=pop();

  Element_TNAME *elem=elem_textName(arg1);

  ulen new_state=Element_TNAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_ipName()
 {
  ElementAtom *arg1=pop();

  Element_TNAME *elem=elem_ipName(arg1);

  ulen new_state=Element_TNAME::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_namedType()
 {
  Element_NAME *arg1=pop();

  Element_TYPEDEF *elem=elem_namedType(arg1);

  ulen new_state=Element_TYPEDEF::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_baseType()
 {
  Element_TNAME *arg1=pop();

  Element_TYPEDEF *elem=elem_baseType(arg1);

  ulen new_state=Element_TYPEDEF::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_ptrType()
 {
  ElementAtom *arg2=pop();
  Element_TYPEDEF *arg1=pop();

  Element_TYPEDEF *elem=elem_ptrType(arg1,arg2);

  ulen new_state=Element_TYPEDEF::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_arrayType()
 {
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  Element_TYPEDEF *arg1=pop();

  Element_TYPEDEF *elem=elem_arrayType(arg1,arg2,arg3);

  ulen new_state=Element_TYPEDEF::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_arrayLenType()
 {
  ElementAtom *arg4=pop();
  Element_EXPR *arg3=pop();
  ElementAtom *arg2=pop();
  Element_TYPEDEF *arg1=pop();

  Element_TYPEDEF *elem=elem_arrayLenType(arg1,arg2,arg3,arg4);

  ulen new_state=Element_TYPEDEF::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_structType()
 {
  Element_STRUCT *arg1=pop();

  Element_TYPEDEF *elem=elem_structType(arg1);

  ulen new_state=Element_TYPEDEF::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_buildStruct()
 {
  ElementAtom *arg5=pop();
  Element_SBODY *arg4=pop();
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  ElementAtom *arg1=pop();

  Element_STRUCT *elem=elem_buildStruct(arg1,arg2,arg3,arg4,arg5);

  ulen new_state=Element_STRUCT::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_startSBody()
 {
  Element_SBODY *elem=elem_startSBody();

  ulen new_state=Element_SBODY::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extSBody_TYPE()
 {
  Element_TYPE *arg2=pop();
  Element_SBODY *arg1=pop();

  Element_SBODY *elem=elem_extSBody_TYPE(arg1,arg2);

  ulen new_state=Element_SBODY::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extSBody_CONST()
 {
  Element_CONST *arg3=pop();
  ElementAtom *arg2=pop();
  Element_SBODY *arg1=pop();

  Element_SBODY *elem=elem_extSBody_CONST(arg1,arg2,arg3);

  ulen new_state=Element_SBODY::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extSBody_STRUCT()
 {
  ElementAtom *arg3=pop();
  Element_STRUCT *arg2=pop();
  Element_SBODY *arg1=pop();

  Element_SBODY *elem=elem_extSBody_STRUCT(arg1,arg2,arg3);

  ulen new_state=Element_SBODY::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extSBody_field()
 {
  ElementAtom *arg4=pop();
  ElementAtom *arg3=pop();
  Element_TYPEDEF *arg2=pop();
  Element_SBODY *arg1=pop();

  Element_SBODY *elem=elem_extSBody_field(arg1,arg2,arg3,arg4);

  ulen new_state=Element_SBODY::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extSBody_fieldVal()
 {
  ElementAtom *arg6=pop();
  Element_EXPR *arg5=pop();
  ElementAtom *arg4=pop();
  ElementAtom *arg3=pop();
  Element_TYPEDEF *arg2=pop();
  Element_SBODY *arg1=pop();

  Element_SBODY *elem=elem_extSBody_fieldVal(arg1,arg2,arg3,arg4,arg5,arg6);

  ulen new_state=Element_SBODY::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_EXPR_ADD()
 {
  Element_EXPR_ADD *arg1=pop();

  Element_EXPR *elem=elem_cast_EXPR_ADD(arg1);

  ulen new_state=Element_EXPR::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_emptyExprList()
 {
  ElementAtom *arg2=pop();
  ElementAtom *arg1=pop();

  Element_EXPR *elem=elem_emptyExprList(arg1,arg2);

  ulen new_state=Element_EXPR::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_buildExprList()
 {
  ElementAtom *arg3=pop();
  Element_ELIST *arg2=pop();
  ElementAtom *arg1=pop();

  Element_EXPR *elem=elem_buildExprList(arg1,arg2,arg3);

  ulen new_state=Element_EXPR::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_buildNamedExprList()
 {
  ElementAtom *arg3=pop();
  Element_NELIST *arg2=pop();
  ElementAtom *arg1=pop();

  Element_EXPR *elem=elem_buildNamedExprList(arg1,arg2,arg3);

  ulen new_state=Element_EXPR::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_applyEmpty()
 {
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  Element_EXPR *arg1=pop();

  Element_EXPR *elem=elem_applyEmpty(arg1,arg2,arg3);

  ulen new_state=Element_EXPR::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_applyNamedExprList()
 {
  ElementAtom *arg4=pop();
  Element_NELIST *arg3=pop();
  ElementAtom *arg2=pop();
  Element_EXPR *arg1=pop();

  Element_EXPR *elem=elem_applyNamedExprList(arg1,arg2,arg3,arg4);

  ulen new_state=Element_EXPR::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_EXPR_MUL()
 {
  Element_EXPR_MUL *arg1=pop();

  Element_EXPR_ADD *elem=elem_cast_EXPR_MUL(arg1);

  ulen new_state=Element_EXPR_ADD::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opAdd()
 {
  Element_EXPR_MUL *arg3=pop();
  ElementAtom *arg2=pop();
  Element_EXPR_ADD *arg1=pop();

  Element_EXPR_ADD *elem=elem_opAdd(arg1,arg2,arg3);

  ulen new_state=Element_EXPR_ADD::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opSub()
 {
  Element_EXPR_MUL *arg3=pop();
  ElementAtom *arg2=pop();
  Element_EXPR_ADD *arg1=pop();

  Element_EXPR_ADD *elem=elem_opSub(arg1,arg2,arg3);

  ulen new_state=Element_EXPR_ADD::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_EXPR_UN()
 {
  Element_EXPR_UN *arg1=pop();

  Element_EXPR_MUL *elem=elem_cast_EXPR_UN(arg1);

  ulen new_state=Element_EXPR_MUL::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opMul()
 {
  Element_EXPR_UN *arg3=pop();
  ElementAtom *arg2=pop();
  Element_EXPR_MUL *arg1=pop();

  Element_EXPR_MUL *elem=elem_opMul(arg1,arg2,arg3);

  ulen new_state=Element_EXPR_MUL::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opDiv()
 {
  Element_EXPR_UN *arg3=pop();
  ElementAtom *arg2=pop();
  Element_EXPR_MUL *arg1=pop();

  Element_EXPR_MUL *elem=elem_opDiv(arg1,arg2,arg3);

  ulen new_state=Element_EXPR_MUL::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opRem()
 {
  Element_EXPR_UN *arg3=pop();
  ElementAtom *arg2=pop();
  Element_EXPR_MUL *arg1=pop();

  Element_EXPR_MUL *elem=elem_opRem(arg1,arg2,arg3);

  ulen new_state=Element_EXPR_MUL::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_EXPR_POST()
 {
  Element_EXPR_POST *arg1=pop();

  Element_EXPR_UN *elem=elem_cast_EXPR_POST(arg1);

  ulen new_state=Element_EXPR_UN::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opAst()
 {
  Element_EXPR_UN *arg2=pop();
  ElementAtom *arg1=pop();

  Element_EXPR_UN *elem=elem_opAst(arg1,arg2);

  ulen new_state=Element_EXPR_UN::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opAmp()
 {
  Element_EXPR_UN *arg2=pop();
  ElementAtom *arg1=pop();

  Element_EXPR_UN *elem=elem_opAmp(arg1,arg2);

  ulen new_state=Element_EXPR_UN::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opPlus()
 {
  Element_EXPR_UN *arg2=pop();
  ElementAtom *arg1=pop();

  Element_EXPR_UN *elem=elem_opPlus(arg1,arg2);

  ulen new_state=Element_EXPR_UN::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opMinus()
 {
  Element_EXPR_UN *arg2=pop();
  ElementAtom *arg1=pop();

  Element_EXPR_UN *elem=elem_opMinus(arg1,arg2);

  ulen new_state=Element_EXPR_UN::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_EXPR_NNPOST()
 {
  Element_EXPR_NNPOST *arg1=pop();

  Element_EXPR_POST *elem=elem_cast_EXPR_NNPOST(arg1);

  ulen new_state=Element_EXPR_POST::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_Number()
 {
  ElementAtom *arg1=pop();

  Element_EXPR_POST *elem=elem_cast_Number(arg1);

  ulen new_state=Element_EXPR_POST::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_EXPR_NNPRIM()
 {
  Element_EXPR_NNPRIM *arg1=pop();

  Element_EXPR_NNPOST *elem=elem_cast_EXPR_NNPRIM(arg1);

  ulen new_state=Element_EXPR_NNPOST::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opInd()
 {
  ElementAtom *arg4=pop();
  Element_EXPR *arg3=pop();
  ElementAtom *arg2=pop();
  Element_EXPR_POST *arg1=pop();

  Element_EXPR_NNPOST *elem=elem_opInd(arg1,arg2,arg3,arg4);

  ulen new_state=Element_EXPR_NNPOST::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opSelect()
 {
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  Element_EXPR_NNPOST *arg1=pop();

  Element_EXPR_NNPOST *elem=elem_opSelect(arg1,arg2,arg3);

  ulen new_state=Element_EXPR_NNPOST::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opPtrSelect()
 {
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  Element_EXPR_NNPOST *arg1=pop();

  Element_EXPR_NNPOST *elem=elem_opPtrSelect(arg1,arg2,arg3);

  ulen new_state=Element_EXPR_NNPOST::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_EXPR()
 {
  ElementAtom *arg3=pop();
  Element_EXPR *arg2=pop();
  ElementAtom *arg1=pop();

  Element_EXPR_NNPRIM *elem=elem_cast_EXPR(arg1,arg2,arg3);

  ulen new_state=Element_EXPR_NNPRIM::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_NAME()
 {
  Element_NAME *arg1=pop();

  Element_EXPR_NNPRIM *elem=elem_cast_NAME(arg1);

  ulen new_state=Element_EXPR_NNPRIM::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_NNLIT()
 {
  Element_NNLIT *arg1=pop();

  Element_EXPR_NNPRIM *elem=elem_cast_NNLIT(arg1);

  ulen new_state=Element_EXPR_NNPRIM::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_opDomain()
 {
  ElementAtom *arg4=pop();
  Element_EXPR *arg3=pop();
  ElementAtom *arg2=pop();
  Element_ITYPE *arg1=pop();

  Element_EXPR_NNPRIM *elem=elem_opDomain(arg1,arg2,arg3,arg4);

  ulen new_state=Element_EXPR_NNPRIM::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_startExprList()
 {
  Element_EXPR *arg1=pop();

  Element_ELIST *elem=elem_startExprList(arg1);

  ulen new_state=Element_ELIST::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extExprList()
 {
  Element_EXPR *arg3=pop();
  ElementAtom *arg2=pop();
  Element_ELIST *arg1=pop();

  Element_ELIST *elem=elem_extExprList(arg1,arg2,arg3);

  ulen new_state=Element_ELIST::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_nameExpr()
 {
  Element_EXPR *arg4=pop();
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  ElementAtom *arg1=pop();

  Element_NEXPR *elem=elem_nameExpr(arg1,arg2,arg3,arg4);

  ulen new_state=Element_NEXPR::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_startNamedExprList()
 {
  Element_NEXPR *arg1=pop();

  Element_NELIST *elem=elem_startNamedExprList(arg1);

  ulen new_state=Element_NELIST::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extNamedExprList()
 {
  Element_NEXPR *arg3=pop();
  ElementAtom *arg2=pop();
  Element_NELIST *arg1=pop();

  Element_NELIST *elem=elem_extNamedExprList(arg1,arg2,arg3);

  ulen new_state=Element_NELIST::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_type_NAME()
 {
  Element_NAME *arg1=pop();

  Element_ITYPE *elem=elem_type_NAME(arg1);

  ulen new_state=Element_ITYPE::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_type_INAME()
 {
  Element_INAME *arg1=pop();

  Element_ITYPE *elem=elem_type_INAME(arg1);

  ulen new_state=Element_ITYPE::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_null()
 {
  ElementAtom *arg1=pop();

  Element_NNLIT *elem=elem_cast_null(arg1);

  ulen new_state=Element_NNLIT::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_cast_String()
 {
  ElementAtom *arg1=pop();

  Element_NNLIT *elem=elem_cast_String(arg1);

  ulen new_state=Element_NNLIT::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_buildIP()
 {
  ElementAtom *arg7=pop();
  ElementAtom *arg6=pop();
  ElementAtom *arg5=pop();
  ElementAtom *arg4=pop();
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  ElementAtom *arg1=pop();

  Element_NNLIT *elem=elem_buildIP(arg1,arg2,arg3,arg4,arg5,arg6,arg7);

  ulen new_state=Element_NNLIT::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::doRule(Action::Rule rule)
 {
  switch( rule )
    {
     case Action::Do_startBody : do_startBody(); break;
     case Action::Do_extBody_SCOPE : do_extBody_SCOPE(); break;
     case Action::Do_extBody_INCLUDE : do_extBody_INCLUDE(); break;
     case Action::Do_extBody_TYPE : do_extBody_TYPE(); break;
     case Action::Do_extBody_CONST : do_extBody_CONST(); break;
     case Action::Do_extBody_STRUCT : do_extBody_STRUCT(); break;
     case Action::Do_buildScope : do_buildScope(); break;
     case Action::Do_includeFile : do_includeFile(); break;
     case Action::Do_defType : do_defType(); break;
     case Action::Do_defConst : do_defConst(); break;
     case Action::Do_startName : do_startName(); break;
     case Action::Do_extName : do_extName(); break;
     case Action::Do_relName : do_relName(); break;
     case Action::Do_absName : do_absName(); break;
     case Action::Do_dotName : do_dotName(); break;
     case Action::Do_dotsName : do_dotsName(); break;
     case Action::Do_intName : do_intName(); break;
     case Action::Do_sintName : do_sintName(); break;
     case Action::Do_uintName : do_uintName(); break;
     case Action::Do_ulenName : do_ulenName(); break;
     case Action::Do_sint8Name : do_sint8Name(); break;
     case Action::Do_uint8Name : do_uint8Name(); break;
     case Action::Do_sint16Name : do_sint16Name(); break;
     case Action::Do_uint16Name : do_uint16Name(); break;
     case Action::Do_sint32Name : do_sint32Name(); break;
     case Action::Do_uint32Name : do_uint32Name(); break;
     case Action::Do_sint64Name : do_sint64Name(); break;
     case Action::Do_uint64Name : do_uint64Name(); break;
     case Action::Do_cast_INAME : do_cast_INAME(); break;
     case Action::Do_textName : do_textName(); break;
     case Action::Do_ipName : do_ipName(); break;
     case Action::Do_namedType : do_namedType(); break;
     case Action::Do_baseType : do_baseType(); break;
     case Action::Do_ptrType : do_ptrType(); break;
     case Action::Do_arrayType : do_arrayType(); break;
     case Action::Do_arrayLenType : do_arrayLenType(); break;
     case Action::Do_structType : do_structType(); break;
     case Action::Do_buildStruct : do_buildStruct(); break;
     case Action::Do_startSBody : do_startSBody(); break;
     case Action::Do_extSBody_TYPE : do_extSBody_TYPE(); break;
     case Action::Do_extSBody_CONST : do_extSBody_CONST(); break;
     case Action::Do_extSBody_STRUCT : do_extSBody_STRUCT(); break;
     case Action::Do_extSBody_field : do_extSBody_field(); break;
     case Action::Do_extSBody_fieldVal : do_extSBody_fieldVal(); break;
     case Action::Do_cast_EXPR_ADD : do_cast_EXPR_ADD(); break;
     case Action::Do_emptyExprList : do_emptyExprList(); break;
     case Action::Do_buildExprList : do_buildExprList(); break;
     case Action::Do_buildNamedExprList : do_buildNamedExprList(); break;
     case Action::Do_applyEmpty : do_applyEmpty(); break;
     case Action::Do_applyNamedExprList : do_applyNamedExprList(); break;
     case Action::Do_cast_EXPR_MUL : do_cast_EXPR_MUL(); break;
     case Action::Do_opAdd : do_opAdd(); break;
     case Action::Do_opSub : do_opSub(); break;
     case Action::Do_cast_EXPR_UN : do_cast_EXPR_UN(); break;
     case Action::Do_opMul : do_opMul(); break;
     case Action::Do_opDiv : do_opDiv(); break;
     case Action::Do_opRem : do_opRem(); break;
     case Action::Do_cast_EXPR_POST : do_cast_EXPR_POST(); break;
     case Action::Do_opAst : do_opAst(); break;
     case Action::Do_opAmp : do_opAmp(); break;
     case Action::Do_opPlus : do_opPlus(); break;
     case Action::Do_opMinus : do_opMinus(); break;
     case Action::Do_cast_EXPR_NNPOST : do_cast_EXPR_NNPOST(); break;
     case Action::Do_cast_Number : do_cast_Number(); break;
     case Action::Do_cast_EXPR_NNPRIM : do_cast_EXPR_NNPRIM(); break;
     case Action::Do_opInd : do_opInd(); break;
     case Action::Do_opSelect : do_opSelect(); break;
     case Action::Do_opPtrSelect : do_opPtrSelect(); break;
     case Action::Do_cast_EXPR : do_cast_EXPR(); break;
     case Action::Do_cast_NAME : do_cast_NAME(); break;
     case Action::Do_cast_NNLIT : do_cast_NNLIT(); break;
     case Action::Do_opDomain : do_opDomain(); break;
     case Action::Do_startExprList : do_startExprList(); break;
     case Action::Do_extExprList : do_extExprList(); break;
     case Action::Do_nameExpr : do_nameExpr(); break;
     case Action::Do_startNamedExprList : do_startNamedExprList(); break;
     case Action::Do_extNamedExprList : do_extNamedExprList(); break;
     case Action::Do_type_NAME : do_type_NAME(); break;
     case Action::Do_type_INAME : do_type_INAME(); break;
     case Action::Do_cast_null : do_cast_null(); break;
     case Action::Do_cast_String : do_cast_String(); break;
     case Action::Do_buildIP : do_buildIP(); break;
    }
 }

Parser::Parser(ParserContext *ctx_,FileId *file_id)
 : ctx(ctx_,file_id)
 {
  stack=ctx.create<ElementBase>();
 }

Parser::~Parser() 
 {
 }

auto Parser::next(const Atom &atom) -> Result
 {
  Action action(stack->state,atom.ac);
  
  switch( action.rule )
    {
     case Action::Abort :
      {
       ctx.printf("Parser #; : unexpected atom #;\n",ctx.printPos(atom.token.pos),atom.ac);
      }
     return ResultAbort;
     
     case Action::Shift : shift(atom,action.new_state); return ResultShift;
     
     default: doRule(action.rule);
    }
  
  return ResultRule;
 }

auto Parser::complete(TextPos pos) -> Result
 {
  Action action(stack->state);
  
  switch( action.rule )
    {
     case Action::Abort :
      {
       ctx.printf("Parser #; : unexpected end-of-file\n",ctx.printPos(pos));
      }
     return ResultAbort;
     
     case Action::Shift : return ResultShift;
     
     default: doRule(action.rule);
    }
  
  return ResultRule;
 }

} // namespace DDL
} // namespace CCore
 

