/* RBTreeBase.h */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_tree_RBTreeBase_h
#define CCore_inc_tree_RBTreeBase_h
 
#include <CCore/inc/Cmp.h>

namespace CCore {

/* functions */ 

void GuardRBTreeCheckFailed(const char *text);

inline void GuardRBTreeCheck(bool cond,const char *text)
 {
  if( !cond ) GuardRBTreeCheckFailed(text);
 }

/* classes */

//enum RBFlag;

/* enum RBFlag */

enum RBFlag
 {
  RBFlag_BlackBlack,
  RBFlag_HiRed,
  RBFlag_LoRed,
  RBFlag_RedRed
 };

inline RBFlag operator | (RBFlag a,RBFlag b) { return RBFlag(unsigned(a)|unsigned(b)); }

inline RBFlag operator |= (RBFlag &a,RBFlag b) { return a=(a|b); }

inline RBFlag operator ^ (RBFlag a,RBFlag b) { return RBFlag(unsigned(a)^unsigned(b)); }

inline RBFlag operator ^= (RBFlag &a,RBFlag b) { return a=(a^b); }

const char * GetTextDesc(RBFlag flag);

} // namespace CCore
 
#endif
 

