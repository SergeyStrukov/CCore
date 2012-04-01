/* DDLChar.cpp */ 
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
 
#include <CCore/inc/ddl/DDLChar.h>
 
namespace CCore {
namespace DDL {

/* class CharProp */ 

CharProp::CharProp()
 {
  setSet(GetDigitChars(),Char_Digit);
  setSet(GetCLetterChars(),Char_Letter);
  
  setSet("[]{}();,#=&+-*/%.",Char_Punct);
  
  setSet(GetSpaceChars(),Char_Space);
 }
 
const CharProp CharProp::Object;

/* struct FileId */

void FileId::printPos(PrintBase &out,TextPos pos)
 {
  Putobj(out,pos);
 }
  
} // namespace DDL
} // namespace CCore
 

