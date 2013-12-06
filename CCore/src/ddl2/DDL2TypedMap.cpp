/* DDL2TypedMap.cpp */ 
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
 
#include <CCore/inc/ddl2/DDL2TypedMap.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {
namespace DDL2 {

/* functions */

void GuardBadStructure()
 {
  Printf(Exception,"CCore::DDL::TypedMap : bad structure");
 };

void GuardMapNoConst(StrLen name)
 {
  Printf(Exception,"CCore::DDL::TypedMap : constant #; is not found",name);
 }

void GuardMapBadConstType(StrLen name)
 {
  Printf(Exception,"CCore::DDL::TypedMap : constant #; has an unexpected type",name);
 }

} // namespace DDL2
} // namespace CCore
 

