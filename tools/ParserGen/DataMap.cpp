/* DataMap.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ParserGen 1.00
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
#include <CCore/inc/ddl/DDLMap.h>

#include <CCore/inc/Exception.h>

namespace App {

/* class DataMap */

DataMap::DataMap(StrLen file_name)
 : desc_NIndex(DDL::TypeTag_uint),
   desc_TIndex(DDL::TypeTag_uint),
   desc_RIndex(DDL::TypeTag_uint),
   desc_NTIndex(DDL::TypeTag_uint),
   desc_StateIndex(DDL::TypeTag_uint),
   desc_text(DDL::TypeTag_text),
   
   desc_State_ptr(desc_State),
   
   desc_Transition(desc_NTIndex,desc_State_ptr),
   
   desc_Rule_ptr(desc_Rule),
   
   desc_Final(desc_TIndex,desc_Rule_ptr),
   
   desc_Transition_array(desc_Transition),
   desc_Final_array(desc_Final),
   
   desc_State(desc_StateIndex,desc_Transition_array,desc_Final_array),
   
   desc_NTIndex_array(desc_NTIndex),
   desc_Rule(desc_RIndex,desc_text,desc_NIndex,desc_NTIndex_array),
   
   desc_Rule_ptr_array(desc_Rule_ptr),
   desc_NonTerminal(desc_NIndex,desc_text,desc_Rule_ptr_array),
   
   desc_StateTable(desc_State),
   desc_NonTerminalTable(desc_NonTerminal),
   desc_RuleTable(desc_Rule),
   desc_TNames(desc_text)
 {
  PrintCon out(Con);
  DDL::FileEngine<DDL::FileName,FileToMem> engine(out);

  auto result=engine.process(file_name);
  
  out.flush();
  
  if( !result )
    {
     Printf(Exception,"Input file processing error");
    }
  else
    {
     DDL::Map map(result.eval,result.body);
     MemAllocGuard guard(map.getLen());

     map(guard);
     
     table_State=map.findConst("StateTable",desc_StateTable);
     table_NonTerminal=map.findConst("NonTerminalTable",desc_NonTerminalTable);
     table_Rule=map.findConst("RuleTable",desc_RuleTable);
     table_TNames=map.findConst("TNames",desc_TNames);
     
     if( !table_State )
       {
        Printf(Exception,"Cannot find StateTable");
       }
     
     if( !table_NonTerminal )
       {
        Printf(Exception,"Cannot find NonTerminalTable");
       }
     
     if( !table_Rule )
       {
        Printf(Exception,"Cannot find RuleTable");
       }
     
     if( !table_TNames )
       {
        Printf(Exception,"Cannot find TNames");
       }
     
     mem=guard.disarm();
    }
 }
   
DataMap::~DataMap()
 {
  MemFree(mem);
 }

} // namespace App



