/* DDLToken.h */
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

#ifndef CCore_inc_ddl_DDLToken_h
#define CCore_inc_ddl_DDLToken_h

#include <CCore/inc/ddl/DDLChar.h>

namespace CCore {
namespace DDL {

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
   PrintBase &msg;
   FileId *file_id;
  
   TextPos pos;
   StrLen text;

  private:
   
   struct ScanResult
    {
     ulen len;
     bool ok;
    };
   
   struct Scan : ScanResult
    {
     explicit Scan(ulen len_)
      {
       len=len_;
       ok=true;
      }
    };

   struct BadScan : ScanResult
    {
     explicit BadScan(ulen len_)
      {
       len=len_;
       ok=false;
      }
    };

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
   Token cut_pos(TokenClass tc,ulen len);
   
   Token next_error(ulen len,const char *error_text);
   Token next_error_pos(ulen len,const char *error_text);
   Token next_error(const char *error_text);

   Token next_short_comment();
   Token next_long_comment();
   
   Token next_sstring();
   Token next_dstring();
   Token next_bstring();
   
   Token next_number();
   Token next_word();
   Token next_punct();
   Token next_space();
   Token next_other();

  public:

   Tokenizer(PrintBase &msg_,FileId *file_id_,StrLen text_) 
    : msg(msg_),
      file_id(file_id_),
      text(text_) 
    {
    }
 
   ulen operator + () const { return text.len; }
   
   bool operator ! () const { return !text.len; }
 
   Token next();
   
   TextPos getPos() const { return pos; }
 };

} // namespace DDL
} // namespace CCore

#endif
