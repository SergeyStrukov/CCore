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

/* functions */

ulen ScanName(StrLen text)
 {
  if( +text && GetCharClass(text[0])==Char_Letter ) return TokenizerBase::ScanLetterDigit(text); 
   
  return 0;
 }

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

/* struct TokenizerBase */
   
ulen TokenizerBase::ScanShortComment(StrLen text)
 {
  ulen len=text.len;

  for(text+=2; +text && !CharIsEOL(*text) ;++text);

  return len-text.len;
 }
 
auto TokenizerBase::ScanLongComment(StrLen text) -> Scan
 {
  ulen len=text.len;

  for(text+=2; text.len>=2 ;++text)
    {
     if( text[0]=='*' && text[1]=='/' )
       {
        return len-text.len+2;
       }
    }

  return BadScan(len);
 }

ulen TokenizerBase::ScanLetterDigit(StrLen text)
 {
  return ScanExtraChars(text,CharIsLetterDigit);
 }

ulen TokenizerBase::ScanSpace(StrLen text)
 {
  return ScanExtraChars(text,CharIsSpace<char>);
 }
   
ulen TokenizerBase::ScanVisible(StrLen text)
 {
  return ScanExtraChars(text,CharIsVisible<char>);
 }

/* struct CondPaserBase */

const CondPaserBase::State CondPaserBase::StateTable[52]=
 {
#include "../Cond/StateTable.gen.cpp"   
 };

} // namespace LangParser
} // namespace App


