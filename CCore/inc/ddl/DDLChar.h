/* DDLChar.h */ 
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

#ifndef CCore_inc_ddl_DDLChar_h
#define CCore_inc_ddl_DDLChar_h
 
#include <CCore/inc/Printf.h>
#include <CCore/inc/TextTools.h>

namespace CCore {
namespace DDL {

/* classes */ 

//enum CharClass;

class CharProp;

struct FileId;

struct PrintPos;

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

inline bool CharIsHexSuffix(char ch) { return ch=='h' || ch=='H' ; }

inline bool CharIsBinSuffix(char ch) { return ch=='b' || ch=='B' ; }

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
// bool CharIsPrintable(char ch);
//
// bool CharIsBin(char ch);
//
// bool CharIsHex(char ch);
//
// bool CharIsDec(char ch);
//
//---------------------------------

inline char MapDChar(char ch)
 {
  switch( ch )
    {
     case 'b' : return '\b';
     case 't' : return '\t';
     case 'n' : return '\n';
     case 'r' : return '\r';
     case 'v' : return '\v';
     case 'f' : return '\f';
     
     default: return ch; 
    }
 }

/* struct FileId */

struct FileId
 {
  virtual void printPos(PrintBase &out,TextPos pos);
 };

/* struct PrintPos */

struct PrintPos
 {
  FileId *file_id;
  TextPos pos;
  
  PrintPos(FileId *file_id_,TextPos pos_) : file_id(file_id_),pos(pos_) {}
  
  template <class P>
  void print(P &out) const
   {
    file_id->printPos(out,pos);
   }
 };

} // namespace DDL
} // namespace CCore
 
#endif
 

