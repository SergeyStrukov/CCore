/* LangToken.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "LangToken.h"

namespace App {
namespace LangInput {

/* enum TokenClass */ 

const char * GetTextDesc(TokenClass tc)
 {
  switch( tc )
    {
     case Token_Word    : return "word";
     case Token_CWord   : return "C-word";
     case Token_Punct   : return "punct";
     case Token_Space   : return "space";
     case Token_Comment : return "comment";

     default: return "other";
    }
 }
 
/* class Tokenizer */ 

ulen Tokenizer::ScanShortComment(StrLen text)
 {
  ulen len=text.len;

  for(; +text && !CharIsEOL(*text) ;++text);

  return len-text.len;
 }
 
auto Tokenizer::ScanLongComment(StrLen text) -> ScanResult
 {
  ulen len=text.len;

  text+=2;

  for(; text.len>=2 ;++text)
    {
     if( text[0]=='*' && text[1]=='/' )
       {
        return ScanResult(len-text.len+2,true);
       }
    }

  return ScanResult(len,false);
 }
 
ulen Tokenizer::ScanSpace(StrLen text)
 {
  ulen len=text.len;

  for(; +text && CharIsSpace(*text) ;++text);

  return len-text.len;
 }

auto Tokenizer::scanWord(StrLen text) -> ScanWordResult
 {
  ulen len=text.len;
  
  buf.shrink_all();
  
  for(; +text ;++text)
    {
     char ch=*text;
     
     if( ch=='`' ) 
       {
        ch=text[1];
        
        if( ch==':' || ch=='{' || ch=='}' || ch=='`' )
          {
           ++text;
           
           buf.append_copy(ch);
          }
        else
          {
           return ScanWordResult(len-text.len+1);
          } 
       }
     else if( CharIsLetter(ch) )
       {
        buf.append_copy(ch);
       }
     else
       {
        break;
       }
    }

  return ScanWordResult(len-text.len,pool.dup(Range_const(buf)));
 }
 
Token Tokenizer::cut(TokenClass tc,ulen len)
 {
  Token ret(tc,pos,text+=len);

  pos.update(len);

  return ret;
 }
 
Token Tokenizer::cut_pos(TokenClass tc,ulen len)
 {
  Token ret(tc,pos,text+=len);
  
  pos.update(ret.str);

  return ret;
 }
 
Token Tokenizer::next_short_comment()
 {
  return cut(Token_Comment,ScanShortComment(text));
 }
 
Token Tokenizer::next_long_comment()
 {
  auto result=ScanLongComment(text);
  
  if( result.ok ) return cut_pos(Token_Comment,result.len);
  
  Printf(Con,"Tokenizer #; : long comment is not closed\n",pos);
  
  return cut_pos(Token_Other,result.len);
 }
 
Token Tokenizer::next_word()
 {
  auto result=scanWord(text);
  
  if( result.ok )
    {
     auto str=result.name;
     
     Token ret=cut((IsCName(str)?Token_CWord:Token_Word),result.len);
     
     ret.str=str;
     
     return ret;
    }
  else
    {
     Printf(Con,"Tokenizer #; : broken word\n",pos);
     
     return cut(Token_Other,result.len);
    }
 }
 
Token Tokenizer::next_punct()
 {
  return cut(Token_Punct,1);
 }
 
Token Tokenizer::next_space()
 {
  return cut_pos(Token_Space,ScanSpace(text));
 }
 
Token Tokenizer::next_other()
 {
  if( *text=='`' ) return next_word();
  
  Printf(Con,"Tokenizer #; '#;' : illegal char\n",pos,CharCode(*text));
  
  return cut(Token_Other,1);
 }
 
Token Tokenizer::next()
 {
  if( text.len>=2 )
    {
     if( text[0]=='/' )
       {
        if( text[1]=='/' ) return next_short_comment();
        if( text[1]=='*' ) return next_long_comment();
       }
    }
  
  switch( GetCharClass(*text) )
    {
     case Char_Letter : return next_word();
     case Char_Punct  : return next_punct();
     case Char_Space  : return next_space();
     case Char_Other  : return next_other();
    }

  return Token();
 }

} // namespace LangInput
} // namespace App


