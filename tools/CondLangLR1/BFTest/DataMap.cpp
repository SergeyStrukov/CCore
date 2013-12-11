/* DataMap.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1-BFTest 1.00
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
#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/MemAllocGuard.h>

#include <CCore/inc/ddl2/DDL2Engine.h>

#include <CCore/inc/Exception.h>

namespace App {

/* TypeSet */

#include "../LangTypeSet.gen.h"

/* class DataMap */

static const char *Pretext=
  
"  type AtomIndex = uint32 ;"
"  type SyntIndex = uint32 ;"
"  type KindIndex = uint32 ;"
"  type ElementIndex = uint32 ;"
"  type RuleIndex = uint32 ;"
"  type StateIndex = uint32 ;"
"  type FinalIndex = uint32 ;"

"  struct Lang"
"   {"
"    Atom[] atoms;"
"    Synt[] synts;"
"    Synt * [] lang;"
"    Element[] elements;"
"    Rule[] rules;"
"    TopRule[] top_rules;"
"    State[] states;"
"    Final[] finals;"
"   };"

"  struct Atom"
"   {"
"    AtomIndex index;"
"    text name;"
  
"    Element *element;"
"   };"

"  struct Synt"
"   {"
"    SyntIndex index;"
"    text name;"
    
"    Kind[] kinds;"
"    Rule * [] rules;"
"   };"

"  struct Kind"
"   {"
"    KindIndex kindex;"
"    KindIndex index;"
"    text name;"

"    Synt *synt;"
  
"    Element *element;"
  
"    TopRule * [] rules;"
"   };"

"  struct Element"
"   {"
"    ElementIndex index;"
    
"    {Atom,Kind} * elem;"
"   };"

"  struct Rule"
"   {"
"    RuleIndex index;"
"    text name;"

"    Kind *result;"

"    type Arg = {Atom,Synt} * ;"

"    Arg[] args;"
"   };"
   
"  struct TopRule"
"   {"
"    RuleIndex index;"
"    text name;"
    
"    Rule *bottom;"

"    Kind *result;"

"    type Arg = {Atom,Kind} * ;"

"    Arg[] args;"
"   };" 

"  struct State"
"   {"
"    StateIndex index;"
"    Final *final;"

"    struct Transition"
"     {"
"      Element *element;"
"      State *state;"
"     };"

"    Transition[] transitions;"
"   };"

"  struct Final"
"   {"
"    FinalIndex index;"

"    struct Action"
"     {"
"      Atom *atom;"
"      Rule *rule;"
"     };"

"    Action[] actions;"
"   };"
  
;

DataMap::DataMap(StrLen file_name)
 {
  PrintCon out(Con);
  DDL2::FileEngine<FileName,FileToMem> engine(out);

  auto result=engine.process(file_name,Pretext);
   
  out.flush();
   
  if( !result )
    {
     Printf(Exception,"Input file processing error");
    }
  else
    {
     DDL2::TypedMap<TypeSet> map(result);
     MemAllocGuard guard(map.getLen());

     map(guard);

     lang=map.takeConst<TypeDef::Lang>("lang");
      
     mem=guard.disarm();
    }
 }
   
DataMap::~DataMap()
 {
  MemFree(mem);
 }

} // namespace App

