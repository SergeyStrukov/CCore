/* DDL2Parser.cpp */
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

#include <CCore/inc/Exception.h>

namespace CCore {
namespace DDL2 {

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
     case Atom_QName     : return "QName";
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

AtomClass Atom::GetWordClass(StrLen str)
 {
  if( !str ) return Atom_Name;

  switch( str[0] )
    {
     case 'c' :
      {
       ++str;

       if( str.len==4 && str[0]=='o' && str[1]=='n' && str[2]=='s' && str[3]=='t' ) return Atom_const; else return Atom_Name;
      }

     case 'i' :
      {
       ++str;

       if( !str ) return Atom_Name;

       switch( str[0] )
         {
          case 'n' :
           {
            ++str;

            if( !str ) return Atom_Name;

            switch( str[0] )
              {
               case 'c' :
                {
                 ++str;

                 if( str.len==4 && str[0]=='l' && str[1]=='u' && str[2]=='d' && str[3]=='e' ) return Atom_include; else return Atom_Name;
                }

               case 't' :
                {
                 ++str;

                 if( str.len==0 ) return Atom_int; else return Atom_Name;
                }

               default: return Atom_Name;
              }
           }

          case 'p' :
           {
            ++str;

            if( str.len==0 ) return Atom_ip; else return Atom_Name;
           }

          default: return Atom_Name;
         }
      }

     case 'n' :
      {
       ++str;

       if( str.len==3 && str[0]=='u' && str[1]=='l' && str[2]=='l' ) return Atom_null; else return Atom_Name;
      }

     case 's' :
      {
       ++str;

       if( !str ) return Atom_Name;

       switch( str[0] )
         {
          case 'c' :
           {
            ++str;

            if( str.len==3 && str[0]=='o' && str[1]=='p' && str[2]=='e' ) return Atom_scope; else return Atom_Name;
           }

          case 'i' :
           {
            ++str;

            if( !str ) return Atom_Name;

            switch( str[0] )
              {
               case 'n' :
                {
                 ++str;

                 if( !str ) return Atom_Name;

                 switch( str[0] )
                   {
                    case 't' :
                     {
                      ++str;

                      if( !str ) return Atom_sint;

                      switch( str[0] )
                        {
                         case '1' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='6' ) return Atom_sint16; else return Atom_Name;
                          }

                         case '3' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='2' ) return Atom_sint32; else return Atom_Name;
                          }

                         case '6' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='4' ) return Atom_sint64; else return Atom_Name;
                          }

                         case '8' :
                          {
                           ++str;

                           if( str.len==0 ) return Atom_sint8; else return Atom_Name;
                          }

                         default: return Atom_Name;
                        }
                     }

                    default: return Atom_Name;
                   }
                }

               default: return Atom_Name;
              }
           }

          case 't' :
           {
            ++str;

            if( str.len==4 && str[0]=='r' && str[1]=='u' && str[2]=='c' && str[3]=='t' ) return Atom_struct; else return Atom_Name;
           }

          default: return Atom_Name;
         }
      }

     case 't' :
      {
       ++str;

       if( !str ) return Atom_Name;

       switch( str[0] )
         {
          case 'e' :
           {
            ++str;

            if( str.len==2 && str[0]=='x' && str[1]=='t' ) return Atom_text; else return Atom_Name;
           }

          case 'y' :
           {
            ++str;

            if( str.len==2 && str[0]=='p' && str[1]=='e' ) return Atom_type; else return Atom_Name;
           }

          default: return Atom_Name;
         }
      }

     case 'u' :
      {
       ++str;

       if( !str ) return Atom_Name;

       switch( str[0] )
         {
          case 'i' :
           {
            ++str;

            if( !str ) return Atom_Name;

            switch( str[0] )
              {
               case 'n' :
                {
                 ++str;

                 if( !str ) return Atom_Name;

                 switch( str[0] )
                   {
                    case 't' :
                     {
                      ++str;

                      if( !str ) return Atom_uint;

                      switch( str[0] )
                        {
                         case '1' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='6' ) return Atom_uint16; else return Atom_Name;
                          }

                         case '3' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='2' ) return Atom_uint32; else return Atom_Name;
                          }

                         case '6' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='4' ) return Atom_uint64; else return Atom_Name;
                          }

                         case '8' :
                          {
                           ++str;

                           if( str.len==0 ) return Atom_uint8; else return Atom_Name;
                          }

                         default: return Atom_Name;
                        }
                     }

                    default: return Atom_Name;
                   }
                }

               default: return Atom_Name;
              }
           }

          case 'l' :
           {
            ++str;

            if( str.len==2 && str[0]=='e' && str[1]=='n' ) return Atom_ulen; else return Atom_Name;
           }

          default: return Atom_Name;
         }
      }

     default: return Atom_Name;
    }
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
     case Token_QWord : return Atom_QName; 
      
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

bool ParserContext::feed(Parser &parser,Tokenizer &tok)
 {
  while( +tok )
    {
     Atom atom(tok.next());
     
     if( !atom )
       {
        if( atom.token.tc==Token_Other ) 
          {
           error("\nTokenizer error");
           
           return false;
          }
       }
     else
       {
        if( parser.next_loop(atom)==Parser::ResultAbort ) 
          {
           error("\nParser error");
           
           return false;
          }
        
        if( +error ) return false;
       }
    }
  
  return true;
 }

bool ParserContext::finish(Parser &parser,Tokenizer &tok)
 {
  if( parser.complete_loop(tok.getPos())==Parser::ResultAbort ) 
    {
     error("\nParser error");
     
     return false;
    }
  
  return !error;
 }

Element_BODY * ParserContext::parseText(FileId *file_id,StrLen text,StrLen pretext)
 {
  Tokenizer pretok(error,&pretext_file,pretext);
  Tokenizer tok(error,file_id,text);
  
  Parser parser(this,file_id);

  if( feed(parser,pretok) && feed(parser,tok) && finish(parser,tok) ) return parser.getBody();
  
  return 0;
 }

Element_BODY * ParserContext::parseText(FileId *file_id,StrLen text)
 {
  Tokenizer tok(error,file_id,text);
  
  Parser parser(this,file_id);
  
  if( feed(parser,tok) && finish(parser,tok) ) return parser.getBody();
  
  return 0;
 }

template <class Func>
BodyNode * ParserContext::do_parseFile(StrLen file_name,Func func)
 {
  ReportExceptionTo<PrintBase> report(error.getMsg());
  
  try
    {
     reset();
     
     File file=openFile(file_name);
     
     if( !file ) 
       {
        error("\nParserContext error");
         
        return 0;
       }
     
     Element_BODY *elem=func(file.file_id,file.text);
       
     if( !elem ) return 0;
     
     BodyNode *ret=complete(*elem);
     
     if( !ret ) return 0;
     
     report.guard();
     
     return ret;
    }
  catch(CatchType)
    {
     report.print("\nFatal error\n");
     
     return 0;
    }
 }

auto ParserContext::openFile(StrLen) -> File
 {
  error("ParserContext : cannot open file, no file system");
  
  return Nothing;
 }

auto ParserContext::openFile(FileId *file_id,const Token &file_name) -> File
 {
  error("ParserContext #; #; : cannot open file, no file system",PrintPos(file_id,file_name.pos),file_name.str);
  
  return Nothing;
 }

ParserContext::ParserContext(PrintBase &msg,ulen mem_cap) 
 : Context(msg,mem_cap)
 {
 }
   
ParserContext::~ParserContext() 
 {
 }
   
BodyNode * ParserContext::parseFile(StrLen file_name,StrLen pretext)
 {
  return do_parseFile(file_name, [=] (FileId *file_id,StrLen text) { return parseText(file_id,text,pretext); } );
 }

BodyNode * ParserContext::parseFile(StrLen file_name)
 {
  return do_parseFile(file_name, [=] (FileId *file_id,StrLen text) { return parseText(file_id,text); } );
 }

Element_BODY * ParserContext::includeFile(FileId *file_id,const Token &file_name)
 {
  File file=openFile(file_id,file_name);

  if( !file ) 
    {
     error("\nInclude file error");
     
     return 0;
    }
  
  return parseText(file.file_id,file.text);
 }

/* class Parser */

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
  unsigned state=stack->state;
  
  Action action(state,atom.ac);
  
  switch( action.rule )
    {
     case Action::Error :
      {
       ctx.error("Parser #; : unexpected atom #;",ctx.printPos(atom.token.pos),atom);
      }
     return ResultAbort;
     
     case Action::Shift : 
      {
       shift(atom,Transition(state,ElementOf(atom.ac))); 
      }
     return ResultShift;
     
     default: 
      {
       doRule(action.rule,action.element);
      }
     return ResultRule;
    }
 }

auto Parser::complete(TextPos pos) -> Result
 {
  Action action(stack->state);
  
  switch( action.rule )
    {
     case Action::Error :
      {
       ctx.error("Parser #; : unexpected end-of-file",ctx.printPos(pos));
      }
     return ResultAbort;
     
     case Action::Shift : return ResultShift;
     
     default: 
      {
       doRule(action.rule,action.element);
      }
     return ResultRule; 
    }
 }

auto Parser::next_loop(const Atom &atom) -> Result
 {
  Result ret;
  
  while( (ret=next(atom))==ResultRule );
  
  return ret;
 }

auto Parser::complete_loop(TextPos pos) -> Result
 {
  Result ret;
  
  while( (ret=complete(pos))==ResultRule );
  
  return ret;
 }

} // namespace DDL2
} // namespace CCore
