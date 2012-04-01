/* Token.h */
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

#ifndef Regen_Token_h
#define Regen_Token_h

#include <CCore/inc/TextTools.h>
#include <CCore/inc/Print.h>

namespace App {

/* using */ 

using namespace CCore;

/* Error */ 

extern ConType Error;
 
/* classes */ 

//enum CharClass;

class CharProp;

//enum TokenClass;

struct Token;

class TokenNumber;

class Tokenizer;

/* enum CharClass */ 

enum CharClass
 {
  Char_Digit,
  Char_Letter,
  
  Char_Punct,
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

/* enum TokenClass */ 

enum TokenClass
 {
  Token_Number,
  Token_Word,
  Token_Punct,
  
  Token_Space,
  Token_ShortComment,
  Token_LongComment,

  Token_Other
 };
 
inline bool IsSignificantToken(TokenClass tc) { return tc<=Token_Punct; }
 
const char * GetTextDesc(TokenClass tc);
 
/* struct Token */ 

struct Token
 {
  TokenClass tc;
  TextPos pos;
  StrLen str;

  Token() : tc(Token_Other) {}
 
  Token(TokenClass tc_,TextPos pos_,StrLen str_) : tc(tc_),pos(pos_),str(str_) {}
 
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#; #.q;",pos,PrintCString(str));
   }
 };
 
/* class TokenNumber */ 

class TokenNumber : NoCopy
 {
   uint32 value;
   
  private: 
   
   static bool SetError(const Token &token);
  
   template <int Base,int Digit(char)>
   bool setBase(const Token &token,StrLen str);

  public: 

   TokenNumber() : value(0) {}
   
   operator uint32() const { return value; }
 
   bool set(const Token &token);
 };
 
/* class Tokenizer */ 

class Tokenizer : NoCopy
 {
   TextPos pos;
   StrLen text;

  private:

   static ulen ScanLetterDigit(StrLen text);
   static ulen ScanShortComment(StrLen text);
   static ulen ScanSpace(StrLen text);
   static ulen ScanLongComment(StrLen text); // text.len>=2

   Token cut(TokenClass tc,ulen len);
   Token cut_pos(TokenClass tc,ulen len);

   Token next_number();
   Token next_word();
   Token next_punct();
   Token next_space();
   Token next_short_comment();
   Token next_long_comment();
   Token next_other();

  public:

   explicit Tokenizer(StrLen text_) : text(text_) {}
 
   ulen operator + () const { return text.len; }
   
   bool operator ! () const { return !text.len; }
 
   Token next();
 };
 
} // namespace App

#endif
