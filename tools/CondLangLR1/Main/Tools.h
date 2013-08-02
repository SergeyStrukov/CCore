/* Tools.h */
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

#ifndef CondLangLR1_Tools_h
#define CondLangLR1_Tools_h

#include <CCore/inc/Print.h>
#include <CCore/inc/TextTools.h>

namespace App {

/* using */

using namespace CCore;

/* classes */

struct PosStr;

/* struct PosStr */

struct PosStr
 {
  TextPos pos;
  StrLen str;
  
  PosStr() {}
  
  explicit PosStr(TextPos pos_) : pos(pos_) {}
  
  PosStr(TextPos pos_,StrLen str_) : pos(pos_),str(str_) {}
 };

} // namespace App

#endif
