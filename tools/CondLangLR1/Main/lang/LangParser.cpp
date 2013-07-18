/* LangParser.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "LangParser.h"

namespace App {
namespace LangParser {

/* class CharProp */

CharProp::CharProp()
 {
  setSet(GetDigitChars(),Char_Digit);
  setSet(GetCLetterChars(),Char_Letter);
  
  setSet("!,{}()&|=<>:",Char_Punct);
  setSet("/",Char_Comment);
  
  setSet(GetSpaceChars(),Char_Space);
 }

const CharProp CharProp::Object;

/* enum TokenClass */

const char * GetTextDesc(TokenClass tc)
 {
  switch( tc )
    {
     case Token_Punct : return "punct";
     
     case Token_Name : return "name";
     
     case Token_Visible : return "visible";
   
     case Token_Space : return "space";
  
     case Token_ShortComment : return "short comment";
     
     case Token_LongComment : return "long comment";
     
     case Token_END : return "END";
   
     default: return "other";
    }
 }

/* class Tokenizer */

struct Tokenizer::Scan
 {
  ulen len;
  bool ok;
  
  Scan(ulen len_,bool ok_=true) : len(len_),ok(ok_) {}
 };

struct Tokenizer::BadScan : Scan
 {
  explicit BadScan(ulen len) : Scan(len,false) {}
 };
   
ulen Tokenizer::ScanShortComment(StrLen text)
 {
  ulen len=text.len;

  text+=2;
  
  for(; +text && !CharIsEOL(*text) ;++text);

  return len-text.len;
 }
 
auto Tokenizer::ScanLongComment(StrLen text) -> Scan
 {
  ulen len=text.len;

  text+=2;

  for(; text.len>=2 ;++text)
    {
     if( text[0]=='*' && text[1]=='/' )
       {
        return len-text.len+2;
       }
    }

  return BadScan(len);
 }

ulen Tokenizer::ScanLetterDigit(StrLen text)
 {
  ulen len=text.len;

  for(++text; +text && CharIsLetterDigit(*text) ;++text);

  return len-text.len;
 }

ulen Tokenizer::ScanSpace(StrLen text)
 {
  ulen len=text.len;

  for(++text; +text && CharIsSpace(*text) ;++text);

  return len-text.len;
 }
   
ulen Tokenizer::ScanVisible(StrLen text)
 {
  ulen len=text.len;

  for(++text; +text && CharIsVisible(*text) ;++text);

  return len-text.len;
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
  return cut(Token_ShortComment,ScanShortComment(text));
 }
 
Token Tokenizer::next_long_comment()
 {
  auto scan=ScanLongComment(text);
  
  if( scan.ok ) return cut_pos(Token_LongComment,scan.len); 
  
  Printf(Err,"Tokenizer #; : not closed long comment\n\n",pos);
  
  return cut_pos(Token_Other,scan.len);
 }

Token Tokenizer::next_word()
 {
  return cut(Token_Name,ScanLetterDigit(text));
 }

Token Tokenizer::next_punct()
 {
  if( text.len>=2 )
    {
     if( text[1]=='=' )
       {
        char ch=text[0];
        
        if( ch=='=' || ch=='<' || ch=='>' || ch=='!' ) return cut(Token_Punct,2);
       }
    }
  
  return cut(Token_Punct,1);
 }

Token Tokenizer::next_comment()
 {
  if( text.len>=2 )
    {
     if( text[1]=='/' ) return next_short_comment();
     if( text[1]=='*' ) return next_long_comment();
    }
  
  return next_other();
 }

Token Tokenizer::next_space()
 {
  return cut_pos(Token_Space,ScanSpace(text));
 }

Token Tokenizer::next_visible()
 {
  return cut(Token_Visible,ScanVisible(text));
 }

Token Tokenizer::next_other()
 {
  Printf(Err,"Tokenizer #; : unexpected character\n\n",pos);
  
  return cut(Token_Other,1);
 }

Token Tokenizer::next()
 {
  switch( GetCharClass(text[0]) )
    {
     case Char_Letter : return next_word();
     case Char_Punct  : return next_punct();
     case Char_Comment : return next_comment();
     case Char_Space  : return next_space();
     
     default: return next_other();
    }
 }

Token Tokenizer::next_relaxed()
 {
  char ch=text[0];
  
  if( CharIsSpace(ch) ) return next_space();
  
  if( CharIsVisible(ch) ) return next_visible();

  return next_other();
 }

/* struct CondPaserBase */

const CondPaserBase::State CondPaserBase::StateTable[52]=
 {
#include "../Cond/StateTable.gen.cpp"   
 };

} // namespace LangParser
} // namespace App


