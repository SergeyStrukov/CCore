/* DDL2Token.h */
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

#ifndef CCore_inc_ddl2_DDL2Token_h
#define CCore_inc_ddl2_DDL2Token_h

#include <CCore/inc/ddl2/DDL2ErrorMsg.h>
#include <CCore/inc/ddl2/DDL2Char.h>

namespace CCore {
namespace DDL2 {

/* classes */

//enum TokenClass;

struct Token;

class Tokenizer;

/* enum TokenClass */ 

enum TokenClass
 {
  Token_Dec,
  Token_Bin,
  Token_Hex,
  
  Token_Word,
  Token_QWord,
  
  Token_PunctSym,
  Token_PunctArrow,
  Token_PunctDots,
  
  Token_BString,
  Token_SString,
  Token_DString,
  
  Token_Space,
  
  Token_ShortComment,
  Token_LongComment,

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
 };
 
/* class Tokenizer */ 

class Tokenizer : NoCopy
 {
   ErrorMsg &error;
   FileId *file_id;
  
   TextPos pos;
   StrLen text;

  private:
   
   struct ScanResult;
   struct Scan;
   struct BadScan;

   static ulen ScanShortComment(StrLen text); // >=2
   static ScanResult ScanLongComment(StrLen text); // >=2
   
   static ulen ScanLetterDigit(StrLen text); // >=1
   static ulen ScanSpace(StrLen text); // >=1
   static ulen ScanDots(StrLen text); // >=1
   
   static ScanResult ScanSString(StrLen text); // >=1
   static ScanResult ScanDString(StrLen text); // >=1
   static ScanResult ScanBString(StrLen text); // >=1
   
   static bool IsBin(StrLen text);
   static bool IsHex(StrLen text);
   static bool IsDec(StrLen text);
   
   static bool NotHexWord(StrLen text); // >=1

  private: 
   
   Token cut(TokenClass tc,ulen len);
   Token cut_multiline(TokenClass tc,ulen len);
   
   Token next_error(ulen len,const char *error_text);
   Token next_error_multiline(ulen len,const char *error_text);
   Token next_error(const char *error_text);

   Token next_short_comment();
   Token next_long_comment();
   
   Token next_sstring();
   Token next_dstring();
   Token next_bstring();
   
   Token next_number();
   Token next_word();
   Token next_qword();
   Token next_punct();
   Token next_space();
   Token next_other();

  public:

   Tokenizer(ErrorMsg &error_,FileId *file_id_,StrLen text_) 
    : error(error_),
      file_id(file_id_),
      text(text_) 
    {
    }
 
   ulen operator + () const { return text.len; }
   
   bool operator ! () const { return !text.len; }
 
   Token next();
   
   TextPos getPos() const { return pos; }
 };

} // namespace DDL2
} // namespace CCore

#endif
