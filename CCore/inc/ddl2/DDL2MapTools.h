/* DDL2MapTools.h */ 
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

#ifndef CCore_inc_ddl2_DDL2MapTools_h
#define CCore_inc_ddl2_DDL2MapTools_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace DDL2 {

/* functions */

void GuardMapTooDeep();

void GuardMapNameDuplication();

void GuardMapStructNameDuplication();

void GuardMapLenOverflow();

inline ulen MapAddLen(ulen a,ulen b) 
 {
  ulen ret=a+b;
  
  if( ret<a ) GuardMapLenOverflow();
  
  return ret;
 }

inline ulen MapMulLen(ulen a,ulen b)
 {
  if( a && b>ulen(-1)/a ) GuardMapLenOverflow();
  
  return a*b;
 }

} // namespace DDL2
} // namespace CCore
 
#endif
 

