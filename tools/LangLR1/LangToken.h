/* LangToken.h */
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

#ifndef LangLR1_LangToken_h
#define LangLR1_LangToken_h

#include "LangChar.h"

namespace App {
namespace LangInput {

/* classes */ 

//enum TokenClass;

struct Token;

class Tokenizer;

/* enum TokenClass */ 

enum TokenClass
 {
  Token_Word,
  Token_CWord,
  Token_Punct,
  Token_Space,
  Token_Comment,

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
 
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#; #.q;",pos,str);
   }
 };
 
/* class Tokenizer */ 

class Tokenizer : NoCopy
 {
   TextPos pos;
   StrLen text;
   
   DynArray<char> buf;
   ElementPool pool;
   
  private:
   
   struct ScanResult
    {
     ulen len;
     bool ok;
     
     explicit ScanResult(ulen len_,bool ok_=true) : len(len_),ok(ok_) {}
    };

   struct ScanWordResult
    {
     ulen len;
     StrLen name;
     bool ok;
     
     ScanWordResult(ulen len_,StrLen name_) : len(len_),name(name_),ok(true) {}
     
     explicit ScanWordResult(ulen len_) : len(len_),ok(false) {}
    };

   static ulen ScanShortComment(StrLen text);
   static ScanResult ScanLongComment(StrLen text); // >=2
   static ulen ScanSpace(StrLen text);
   
   ScanWordResult scanWord(StrLen text);
   
   Token cut(TokenClass tc,ulen len);
   Token cut_pos(TokenClass tc,ulen len);

   Token next_short_comment();
   Token next_long_comment();
   
   Token next_word();
   Token next_punct();
   Token next_space();
   Token next_other();

  public:

   explicit Tokenizer(StrLen text_) : text(text_),buf(DoReserve,100) {}
 
   ulen operator + () const { return text.len; }
   
   bool operator ! () const { return !text.len; }
 
   Token next();
   
   TextPos getPos() const { return pos; }
 };

} // namespace LangInput
} // namespace App

#endif


