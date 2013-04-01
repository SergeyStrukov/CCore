/* DataMap.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: LR1Track 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "DataMap.h"

#include <CCore/inc/Print.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/MemAllocGuard.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypedMap.h>

#include <CCore/inc/Exception.h>

namespace App {

/* struct TypeDef::Element::Ext */

TypeDef::ElementIndex TypeDef::Element::Ext::ElementLim;
TypeDef::ElementIndex TypeDef::Element::Ext::AtomLim;

/* TypeSet */

#include "ShiftStateTypes.TypeSet.gen.h"

/* class DataMap */

static const char *Pretext=
  
"  type ElementIndex = uint ;"
"  type RuleIndex = uint ;"
"  type FinalIndex = uint ;"
"  type StateIndex = uint ;"

"  struct Element" 
"   {"
"    ElementIndex element;"

"    text name;"

"    Rule * [] rules;"
"   };"

"  struct Rule"
"   {"
"    RuleIndex rule;"

"    text name;"

"    Element * result;"
"    Element * [] args;"
"   };"

"  struct Final"
"   {"
"    FinalIndex final;"

"    struct Action { Element *atom; Rule *rule; } [] actions;"
"   };"

"  struct State"
"   {"
"    StateIndex state;"

"    struct Transition { Element *element; State *state; } [] transitions;"

"    Final *final;"
"   };"
  
"struct ShiftState"
" {"
"  StateIndex state;"

"  struct Transition { Element *element; ShiftState *state; } [] transitions;"

"  State * [] states;"
"  Final * [] finals;"

"  Element * [] shift;"
" };";

DataMap::DataMap(StrLen file_name)
 {
  PrintCon out(Con);
  DDL::FileEngine<DDL::FileName,FileToMem> engine(out);

  auto result=engine.process(file_name,Pretext);
  
  out.flush();
  
  if( !result )
    {
     Printf(Exception,"Input file processing error");
    }
  else
    {
     DDL::TypedMap<TypeSet> map(result.eval,result.body);
     MemAllocGuard guard(map.getLen());

     map(guard);

     TypeDef::Element::Ext::ElementLim=map.takeConst<TypeDef::ElementIndex>("ElementIndexLim");
     TypeDef::Element::Ext::AtomLim=map.takeConst<TypeDef::ElementIndex>("AtomIndexLim");
     
     table_Element=map.takeConst<PtrLen<TypeDef::Element> >("ElementTable");
     table_Rule=map.takeConst<PtrLen<TypeDef::Rule> >("RuleTable");
     table_Final=map.takeConst<PtrLen<TypeDef::Final> >("FinalTable");
     table_State=map.takeConst<PtrLen<TypeDef::State> >("StateTable");
     table_ShiftState=map.takeConst<PtrLen<TypeDef::ShiftState>>("ShiftStateTable");
     
     mem=guard.disarm();
    }
 }
   
DataMap::~DataMap()
 {
  MemFree(mem);
 }

} // namespace App



