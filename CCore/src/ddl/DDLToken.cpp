/* DDLToken.cpp */
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

#include <CCore/inc/ddl/DDLToken.h>

namespace CCore {
namespace DDL {

/* enum TokenClass */ 

const char * GetTextDesc(TokenClass tc)
 {
  switch( tc )
    {
     case Token_Dec : return "dec-number";
     case Token_Bin : return "bin-number";
     case Token_Hex : return "hex-number";
     
     case Token_Word : return "word";
     
     case Token_PunctSym : return "punct-symbol";
     case Token_PunctArrow : return "punct-arrow";
     case Token_PunctDots : return "punct-dots";
     
     case Token_BString : return "b-string";
     case Token_SString : return "s-string";
     case Token_DString : return "d-string";
     
     case Token_Space : return "space";
     
     case Token_ShortComment : return "short comment";
     case Token_LongComment : return "long comment";

     default: return "other";
    }
 }
 
/* class Tokenizer */ 

ulen Tokenizer::ScanShortComment(StrLen text)
 {
  ulen len=text.len;

  text+=2;
  
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
        return Scan(len-text.len+2);
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

ulen Tokenizer::ScanDots(StrLen text)
 {
  ulen len=text.len;

  for(++text; +text && *text=='.' ;++text);

  return len-text.len;
 }

auto Tokenizer::ScanSString(StrLen text) -> ScanResult
 {
  ulen len=text.len;
  
  for(++text; +text ;++text)
    if( *text=='\'' )
      {
       return Scan(len-text.len+1);
      }
    else
      {
       if( !CharIsPrintable(*text) ) return BadScan(len-text.len);
      }
  
  return BadScan(len);
 }

auto Tokenizer::ScanDString(StrLen text) -> ScanResult
 {
  ulen len=text.len;
  
  for(++text; +text ;++text)
    if( *text=='"' )
      {
       return Scan(len-text.len+1);
      }
    else if( *text=='\\' )
      {
       ++text;
       
       if( !text ) return BadScan(len);
       
       if( !CharIsPrintable(*text) ) return BadScan(len-text.len);
      }
    else
      {
       if( !CharIsPrintable(*text) ) return BadScan(len-text.len);
      }
  
  return BadScan(len);
 }

auto Tokenizer::ScanBString(StrLen text) -> ScanResult
 {
  ulen len=text.len;
  
  for(++text; +text ;++text)
    if( *text=='>' )
      {
       return Scan(len-text.len+1);
      }
    else
      {
       if( !CharIsPrintable(*text) ) return BadScan(len-text.len);
      }
  
  return BadScan(len);
 }

bool Tokenizer::IsBin(StrLen text)
 {
  for(; +text ;++text) if( !CharIsBin(*text) ) return false;
   
  return true; 
 }

bool Tokenizer::IsHex(StrLen text)
 {
  for(; +text ;++text) if( !CharIsHex(*text) ) return false;
   
  return true; 
 }
 
bool Tokenizer::IsDec(StrLen text)
 {
  for(; +text ;++text) if( !CharIsDec(*text) ) return false;
   
  return true; 
 }

bool Tokenizer::NotHexWord(StrLen text)
 {
  if( !CharIsHexSuffix(text.back(1)) ) return true;
  
  text.len--;
  
  return !IsHex(text);
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
 
Token Tokenizer::next_error(ulen len,const char *error_text)
 {
  Token ret=cut(Token_Other,len);
  
  Printf(msg,"Tokenizer #; #; : #;\n",PrintPos(file_id,ret.pos),ret.str,error_text);
  
  return ret;
 }

Token Tokenizer::next_error_pos(ulen len,const char *error_text)
 {
  Token ret=cut_pos(Token_Other,len);
  
  Printf(msg,"Tokenizer #; : #;\n",PrintPos(file_id,ret.pos),error_text);
  
  return ret;
 }

Token Tokenizer::next_error(const char *error_text)
 {
  Token ret=cut(Token_Other,1);
  
  Printf(msg,"Tokenizer #; \"#;\" : #;\n",PrintPos(file_id,ret.pos),CharCode(*ret.str),error_text);
  
  return ret;
 }

Token Tokenizer::next_short_comment()
 {
  return cut(Token_ShortComment,ScanShortComment(text));
 }
 
Token Tokenizer::next_long_comment()
 {
  auto result=ScanLongComment(text);
  
  if( result.ok ) return cut_pos(Token_LongComment,result.len);
  
  return next_error_pos(result.len,"long comment is not closed");
 }
 
Token Tokenizer::next_sstring()
 {
  auto result=ScanSString(text);
  
  if( result.ok ) return cut(Token_SString,result.len);
  
  return next_error(result.len,"broken '-string is found");
 }

Token Tokenizer::next_dstring()
 {
  auto result=ScanDString(text);
  
  if( result.ok ) return cut(Token_DString,result.len);
  
  return next_error(result.len,"broken \"-string is found");
 }

Token Tokenizer::next_bstring()
 {
  auto result=ScanBString(text);
  
  if( result.ok ) return cut(Token_BString,result.len);
  
  return next_error(result.len,"broken <-string is found");
 }

Token Tokenizer::next_number()
 {
  ulen len=ScanLetterDigit(text);
  
  char ch=text[len-1];
  
  if( CharIsBinSuffix(ch) )
    {
     if( IsBin(text.prefix(len-1)) ) return cut(Token_Bin,len);
     
     return next_error(len,"broken bin number is found");
    }
  else if( CharIsHexSuffix(ch) )
    {
     if( IsHex(text.prefix(len-1)) ) return cut(Token_Hex,len);
     
     return next_error(len,"broken hex number is found");
    }
  else
    {
     if( IsDec(text.prefix(len)) ) return cut(Token_Dec,len);
     
     return next_error(len,"broken dec number is found");
    }
 }
 
Token Tokenizer::next_word()
 {
  ulen len=ScanLetterDigit(text);
  
  if( NotHexWord(text.prefix(len)) ) return cut(Token_Word,len);
  
  return next_error(len,"hex word is found");
 }
 
Token Tokenizer::next_punct()
 {
  if( text.len>=2 )
    {
     if( text[0]=='/' )
       {
        if( text[1]=='/' ) return next_short_comment();
        if( text[1]=='*' ) return next_long_comment();
       }
     
     if( text[0]=='-' && text[1]=='>' ) return cut(Token_PunctArrow,2);
    }
  
  if( text[0]=='.' ) return cut(Token_PunctDots,ScanDots(text));
  
  return cut(Token_PunctSym,1);
 }
 
Token Tokenizer::next_space()
 {
  return cut_pos(Token_Space,ScanSpace(text));
 }
 
Token Tokenizer::next_other()
 {
  switch( text[0] )
    {
     case '\'' : return next_sstring(); 
     case '"'  : return next_dstring();  
     case '<'  : return next_bstring();
    }
  
  return next_error("illegal char is found");
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

} // namespace DDL
} // namespace CCore
