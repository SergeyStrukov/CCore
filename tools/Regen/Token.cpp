/* Token.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Regen 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "Token.h"

namespace App {

/* Error */ 

ConType Error = Con ;
 
/* class CharProp */ 

CharProp::CharProp()
 {
  setSet(GetDigitChars(),Char_Digit);
  setSet(GetCLetterChars(),Char_Letter);
  setSet(":{}.-+*=[]",Char_Punct);
  setSet(GetSpaceChars(),Char_Space);
 }
 
const CharProp CharProp::Object;

/* enum TokenClass */ 

const char * GetTextDesc(TokenClass tc)
 {
  switch( tc )
    {
     case Token_Number       : return "number";
     case Token_Word         : return "word";
     case Token_Punct        : return "punct";
     
     case Token_Space        : return "space";
     case Token_ShortComment : return "short comment";
     case Token_LongComment  : return "long comment";

     default: return "other";
    }
 }
 
/* class TokenNumber */ 

bool TokenNumber::SetError(const Token &token)
 {
  Printf(Error,"Error: invalid number #;\n",token);

  return false;
 }
 
template <int Base,int Digit(char)>
bool TokenNumber::setBase(const Token &token,StrLen str)
 {
  uint32 val=0;

  for(; +str ;++str)
    {
     int dig=Digit(*str);

     if( dig<0 ) return SetError(token);

     const uint32 m=uint32(-1),
                  a=m/Base,
                  b=m%Base;

     if( val>a || ( val==a && (uint32)dig>b ) ) return SetError(token);

     val=Base*val+dig;
    }

  value=val;

  return true;
 }

bool TokenNumber::set(const Token &token)
 {
  StrLen str(token.str);

  if( str.len==0 ) return SetError(token);
  
  switch( str.back(1) )
    {
     case 'b' : str.len--; return setBase<2,CharBinValue>(token,str);

     case 'h' : str.len--; return setBase<16,CharHexValue>(token,str);

     default: return setBase<10,CharDecValue>(token,str);
    }
 }
 
/* class Tokenizer */ 

ulen Tokenizer::ScanLetterDigit(StrLen text)
 {
  ulen len=text.len;

  for(; +text && CharIsLetterDigit(*text) ;++text);

  return len-text.len;
 }
 
ulen Tokenizer::ScanShortComment(StrLen text)
 {
  ulen len=text.len;

  for(; +text && !CharIsEOL(*text) ;++text);

  return len-text.len;
 }
 
ulen Tokenizer::ScanSpace(StrLen text)
 {
  ulen len=text.len;

  for(; +text && CharIsSpace(*text) ;++text);

  return len-text.len;
 }
 
ulen Tokenizer::ScanLongComment(StrLen text)
 {
  ulen len=text.len;

  text+=2;

  for(; text.len>=2 ;++text)
    if( text[0]=='*' && text[1]=='/' )
      {
       return len-text.len+2;
      }

  return len;
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
 
Token Tokenizer::next_number()
 {
  return cut(Token_Number,ScanLetterDigit(text));
 }
 
Token Tokenizer::next_word()
 {
  return cut(Token_Word,ScanLetterDigit(text));
 }
 
Token Tokenizer::next_punct()
 {
  return cut(Token_Punct,1);
 }
 
Token Tokenizer::next_space()
 {
  return cut_pos(Token_Space,ScanSpace(text));
 }
 
Token Tokenizer::next_short_comment()
 {
  return cut(Token_ShortComment,ScanShortComment(text));
 }
 
Token Tokenizer::next_long_comment()
 {
  return cut_pos(Token_LongComment,ScanLongComment(text));
 }
 
Token Tokenizer::next_other()
 {
  if( text.len>=2 && text[0]=='/' )
    {
     if( text[1]=='/' ) return next_short_comment();
     if( text[1]=='*' ) return next_long_comment();
    }

  return cut(Token_Other,1);
 }
 
Token Tokenizer::next()
 {
  switch( GetCharClass(*text) )
    {
     case Char_Digit  : return next_number();
     case Char_Letter : return next_word();
     case Char_Punct  : return next_punct();
     case Char_Space  : return next_space();
     case Char_Other  : return next_other();
    }

  return Token();
 }

} // namespace App
