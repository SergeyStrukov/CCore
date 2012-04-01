/* LangChar.cpp */
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

#include "LangChar.h"

namespace App {
namespace LangInput {

/* class CharProp */ 

CharProp::CharProp()
 {
  setIf( [] (char ch) -> bool { return CharIsVisible(ch) && ch!='"' && ch!='\\' && ch!='`' ; } ,Char_Letter);
  
  setSet(":{}",Char_Punct);
  
  setSet(GetSpaceChars(),Char_Space);
 }
 
const CharProp CharProp::Object;

} // namespace LangInput
} // namespace App

