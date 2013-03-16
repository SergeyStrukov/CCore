/* DataMap.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ParserGen 1.01
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
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

/* TypeSet */

#include "StateTypes.TypeSet.gen.h"

/* class DataMap */

static const char *Pretext=
  
"type RIndex = uint ;\n"
"type TIndex = uint ;\n"
"type NIndex = uint ;\n"
"type NTIndex = uint ;\n"
"type StateIndex = uint ;\n"
"type FinalIndex = uint ;\n\n"

"struct Final\n"
" {\n"
"  FinalIndex final;\n\n"

"  struct Action { TIndex t; Rule *rule; } [] actions;\n"
" };\n\n"

"struct State\n"
" {\n"
"  StateIndex state;\n\n"

"  struct Transition { NTIndex ntt; State *state; } [] transitions;\n\n"

"  Final *final;\n"
" };\n\n"

"struct Rule\n"
" {\n"
"  RIndex rule;\n"
"  text name;\n"
"  NIndex result;\n"
"  NTIndex[] str;\n"
" };\n\n"

"struct NonTerminal\n"
" {\n"
"  NIndex nt;\n"
"  text name;\n"
"  Rule * [] rules;\n"
" };\n";

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
     
     table_Final=map.takeConst<PtrLen<TypeDef::Final> >("FinalTable");
     table_State=map.takeConst<PtrLen<TypeDef::State> >("StateTable");
     table_NonTerminal=map.takeConst<PtrLen<TypeDef::NonTerminal> >("NonTerminalTable");
     table_Rule=map.takeConst<PtrLen<TypeDef::Rule> >("RuleTable");
     table_TNames=map.takeConst<PtrLen<StrLen> >("TNames");
     
     mem=guard.disarm();
    }
 }
   
DataMap::~DataMap()
 {
  MemFree(mem);
 }

} // namespace App



