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
#include <CCore/inc/Array.h>
#include <CCore/inc/Cmp.h>

namespace App {

/* using */

using namespace CCore;

/* classes */

struct PosStr;

struct OffLen;

struct DescBase;

/* struct PosStr */

struct PosStr
 {
  TextPos pos;
  StrLen str;
  
  PosStr() {}
  
  explicit PosStr(TextPos pos_) : pos(pos_) {}
  
  PosStr(TextPos pos_,StrLen str_) : pos(pos_),str(str_) {}
 };

/* struct OffLen */

struct OffLen : NoThrowFlagsBase
 {
  ulen off;
  ulen len;
  
  OffLen() : off(0),len(0) {}
  
  OffLen(NothingType) : off(0),len(0) {}
  
  OffLen(ulen off_,ulen len_) : off(off_),len(len_) {}
  
  template <class T>
  PtrLen<T> cut(T *base) const { return Range(base+off,len); }
 };

/* struct DescBase */

struct DescBase : NoCopy , NoThrowFlagsBase
 {
  ulen index = MaxULen ;
  StrLen name;
  
  DescBase() {}
  
  bool operator + () const { return index!=MaxULen; }
  
  bool operator ! () const { return index==MaxULen; }
 };

} // namespace App

#endif
