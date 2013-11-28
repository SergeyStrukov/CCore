/* DDL2Char.cpp */ 
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
 
#include <CCore/inc/ddl2/DDL2Char.h>
 
namespace CCore {
namespace DDL2 {

/* class CharProp */ 

CharProp::CharProp()
 {
  setSet(GetDigitChars(),Char_Digit);
  setSet(GetCLetterChars(),Char_Letter);
  set('?',Char_QMark);
  
  setSet("[]{}();,#=&+-*/%.",Char_Punct);
  
  setSet(GetSpaceChars(),Char_Space);
 }
 
const CharProp CharProp::Object;

/* struct FileId */

void FileId::printPos(PrintBase &out,TextPos pos)
 {
  Putobj(out,pos);
 }
  
} // namespace DDL2
} // namespace CCore
 

