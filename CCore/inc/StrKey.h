/* StrKey.h */ 
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

#ifndef CCore_inc_StrKey_h
#define CCore_inc_StrKey_h

#include <CCore/inc/Cmp.h>
 
namespace CCore {

/* classes */

struct StrKey;

/* struct StrKey */

struct StrKey : CmpComparable<StrKey>
 {
  uint32 hash;
  StrLen str;
  
  StrKey() : hash(0) {}
  
  explicit StrKey(StrLen str);
  
  CmpResult objCmp(const StrKey &obj) const
   {
    if( CmpResult result=LessCmp(hash,obj.hash) ) return result;
      
    return StrCmp(str,obj.str);
   }
 };

} // namespace CCore
 
#endif
 

