/* DDL2MapTools.cpp */ 
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
 
#include <CCore/inc/ddl2/DDL2MapTools.h>
 
#include <CCore/inc/Exception.h>

namespace CCore {
namespace DDL2 {

/* functions */

void GuardMapTooDeep()
 {
  Printf(Exception,"CCore::DDL2::(Typed)Map : too deep");
 }

void GuardMapNameDuplication()
 {
  Printf(Exception,"CCore::DDL2::(Typed)Map : const name duplication");
 }

void GuardMapStructNameDuplication()
 {
  Printf(Exception,"CCore::DDL2::Map : struct name duplication");
 }

void GuardMapLenOverflow()
 {
  Printf(Exception,"CCore::DDL2::(Typed)Map : len overflow");
 }

/* class TypeComparer */

CmpResult TypeComparer::operator () (TypeNode *a,TypeNode *b) // TODO
 {
  
 }

} // namespace DDL2
} // namespace CCore
 

