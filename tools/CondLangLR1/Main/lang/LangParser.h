/* LangParser.h */
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

#ifndef CondLangLR1_LangParser_h
#define CondLangLR1_LangParser_h

#include "Tools.h"

#include <CCore/inc/TextTools.h>

namespace App {
namespace LangParser {

/* classes */

//enum CharClass;

//enum TokenClass;

struct Token;

class Tokenizer;

/* enum CharClass */ 

enum CharClass
 {
  Char_Digit,
  Char_Letter,
  Char_Punct,
  Char_Comment,
  Char_Space,

  Char_Other
 };
 
inline bool IsLetterDigit(CharClass cc) { return cc<=Char_Letter; }
 
/* class CharProp */ 

class CharProp : public CharPropTable<CharClass,Char_Other>
 {
  public:

   CharProp();
 
   static const CharProp Object;
 };

/* char functions */ 
 
inline CharClass GetCharClass(char ch) { return CharProp::Object[ch]; }

inline bool CharIsLetterDigit(char ch) { return IsLetterDigit(GetCharClass(ch)); }

//---------------------------------
//                                 
// From CharProp.h and TextTools.h
//
//---------------------------------
//
// bool CharIsEOL(char ch);
//
// bool CharIsSpace(char ch);
//
// bool CharIsVisible(char ch);
//
//---------------------------------

/* enum TokenClass */

enum TokenClass
 {
  Token_Punct,
  Token_Name,
  Token_Visible,
  
  Token_Space,
 
  Token_ShortComment,
  Token_LongComment,
  
  Token_END,
  
  Token_Other
 };

const char * GetTextDesc(TokenClass tc);

/* struct Token */

struct Token
 {
  TokenClass tc;
  TextPos pos;
  StrLen str;

  Token() : tc(Token_Other) {}
 
  Token(TokenClass tc_,TextPos pos_,StrLen str_) : tc(tc_),pos(pos_),str(str_) {}
  
  explicit Token(TextPos pos_) : tc(Token_END),pos(pos_) {}
  
  bool is(char ch) const { return str.len==1 && str[0]==ch ; }
  
  bool is(char ch1,char ch2) const { return str.len==2 && str[0]==ch1 && str[1]==ch2 ; }
 };

/* class Tokenizer */

class Tokenizer : NoCopy
 {
   TextPos pos;
   StrLen text;
   
  private:
   
   struct Scan;
   struct BadScan;
   
   static ulen ScanShortComment(StrLen text); // >=2
   static Scan ScanLongComment(StrLen text); // >=2
   
   static ulen ScanLetterDigit(StrLen text); // >=1
   static ulen ScanSpace(StrLen text); // >=1
   
   static ulen ScanVisible(StrLen text); // >=1
   
  private: 
   
   Token cut(TokenClass tc,ulen len);
   Token cut_pos(TokenClass tc,ulen len);
   
   Token next_short_comment();
   Token next_long_comment();
   
   Token next_word();
   Token next_punct();
   Token next_comment();
   Token next_space();
   Token next_visible();
   Token next_other();
   
  public:
  
   explicit Tokenizer(StrLen text_) : text(text_) {}
   
   ulen operator + () const { return text.len; }
   
   bool operator ! () const { return !text.len; }
 
   Token next();
   
   Token next_relaxed();
   
   TextPos getPos() const { return pos; }
 };

} // namespace LangParser
} // namespace App

#endif
