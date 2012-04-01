/* LangChar.h */
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

#ifndef LangLR1_LangChar_h
#define LangLR1_LangChar_h

#include "Lang.h"

namespace App {
namespace LangInput {

/* classes */

//enum CharClass;

class CharProp;

/* enum CharClass */ 

enum CharClass
 {
  Char_Letter, // Visible \ { " , \ , ` } 
  Char_Punct,  // ":{}"
  Char_Space,  // " \t\f\v\r\n"

  Char_Other
 };
 
/* class CharProp */ 

class CharProp : public CharPropTable<CharClass,Char_Other>
 {
  public:

   CharProp();

   static const CharProp Object;
 };

/* char functions */ 
 
inline CharClass GetCharClass(char ch) { return CharProp::Object[ch]; }

inline bool CharIsLetter(char ch) { return GetCharClass(ch)==Char_Letter; }

} // namespace LangInput
} // namespace App

#endif


