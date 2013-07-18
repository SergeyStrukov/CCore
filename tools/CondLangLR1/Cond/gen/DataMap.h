/* DataMap.h */
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

#ifndef DataMap_h
#define DataMap_h

#include <CCore/inc/ddl/DDLTypes.h>

namespace App {

/* using */

using namespace CCore;

/* TypeDef */

#include "StateTypes.TypeDef.gen.h"

/* struct TypeDef::Element::Ext */

struct TypeDef::Element::Ext
 {
  static TypeDef::ElementIndex ElementLim;
  static TypeDef::ElementIndex AtomLim;
 };

/* classes */

class DataMap;

/* class DataMap */

class DataMap : NoCopy
 {
   void *mem;

   PtrLen<TypeDef::Element>     table_Element;
   PtrLen<TypeDef::Rule>        table_Rule;
   PtrLen<TypeDef::Final>       table_Final;
   PtrLen<TypeDef::State>       table_State;
   
  public:
  
   explicit DataMap(StrLen file_name);
   
   ~DataMap();
   
   PtrLen<TypeDef::Element> getElements() const { return table_Element; }
   PtrLen<TypeDef::Rule>    getRules() const { return table_Rule; }
   PtrLen<TypeDef::Final>   getFinals() const { return table_Final; }
   PtrLen<TypeDef::State>   getStates() const { return table_State; }
   
   PtrLen<TypeDef::Element> getAtoms() const { return table_Element.prefix(TypeDef::Element::Ext::AtomLim); }
   PtrLen<TypeDef::Element> getNonAtoms() const { return table_Element.part(TypeDef::Element::Ext::AtomLim); }
 };

} // namespace App

#endif

