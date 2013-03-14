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
#include <CCore/inc/ddl/DDLMap.h>
#include <CCore/inc/ddl/DDLTypedMap.h>

#include <CCore/inc/Exception.h>

namespace App {

/* TypeSet */

#include "StateTypes.TypeSet.gen.h"

#if 0

/* struct DataMap::TypeSet */

struct DataMap::TypeSet : TypeDef , DDL::MapHackPtr
 {
  ulen indexes[6];
  
  TypeSet()
   {
    Range(indexes).set(ulen(-1));
   }
  
  DDL::MapSizeInfo structSizeInfo(DDL::StructNode *struct_node)
   {
    DDL::MapSizeInfo ret;
    
    if( DDL::HasName(struct_node,"NonTerminal") )
      {
       indexes[0]=struct_node->index;
      
       ret.set<NonTerminal>();
       
       DDL::SetFieldOffsets(struct_node,
                            "nt",offsetof(NonTerminal,nt),
                            "name",offsetof(NonTerminal,name),
                            "rules",offsetof(NonTerminal,rules)
                           );
       
       return ret;
      }
     
    if( DDL::HasName(struct_node,"Rule") )
      {
       indexes[1]=struct_node->index;
     
       ret.set<Rule>();
       
       DDL::SetFieldOffsets(struct_node,
                        "rule",offsetof(Rule,rule),
                        "name",offsetof(Rule,name),
                        "result",offsetof(Rule,result),
                        "str",offsetof(Rule,str)
                      );
      
       return ret;
      }
     
    if( DDL::HasName(struct_node,"State") )
      {
       indexes[2]=struct_node->index;
       
       ret.set<State>();
     
       DDL::SetFieldOffsets(struct_node,
                        "state",offsetof(State,state),
                        "transitions",offsetof(State,transitions),
                        "final",offsetof(State,final)
                      );
       
       return ret;
      }
    
    if( DDL::HasName(struct_node,"Final") )
      {
       indexes[3]=struct_node->index;
       
       ret.set<Final>();
     
       DDL::SetFieldOffsets(struct_node,
                        "final",offsetof(Final,final),
                        "actions",offsetof(Final,actions)
                      );
       
       return ret;
      }
    
    if( DDL::HasName(struct_node,"Transition","State") )
      {
       indexes[4]=struct_node->index;
       
       ret.set<State::Transition>();
     
       DDL::SetFieldOffsets(struct_node,
                        "ntt",offsetof(State::Transition,ntt),
                        "state",offsetof(State::Transition,state)
                      );
       
       return ret;
      }
    
    if( DDL::HasName(struct_node,"Action","Final") )
      {
       indexes[5]=struct_node->index;
       
       ret.set<Final::Action>();
     
       DDL::SetFieldOffsets(struct_node,
                        "t",offsetof(Final::Action,t),
                        "rule",offsetof(Final::Action,rule)
                      );
       
       return ret;
      }
    
    Printf(Exception,"Unknown structure");     
    
    return ret;
   }
  
  template <class T> struct IsStruct;
  
  template <class T>
  bool isStruct(DDL::StructNode *struct_node) const
   {
    return IsStruct<T>::Do(indexes,struct_node->index);
   }
 
  void guardFieldTypes(DDL::MapTypeCheck &type_check,DDL::StructNode *struct_node) const
   {
    if( struct_node->index==indexes[0] )
      {
       DDL::GuardFieldTypes<NIndex,StrLen,PtrLen<Rule *> >(*this,type_check,struct_node);
      }
    
    if( struct_node->index==indexes[1] )
      {
       DDL::GuardFieldTypes<RIndex,StrLen,NIndex,PtrLen<NTIndex> >(*this,type_check,struct_node);
      }
    
    if( struct_node->index==indexes[2] )
      {
       DDL::GuardFieldTypes<StateIndex,PtrLen<State::Transition>,Final *>(*this,type_check,struct_node);
      }
    
    if( struct_node->index==indexes[3] )
      {
       DDL::GuardFieldTypes<FinalIndex,PtrLen<Final::Action> >(*this,type_check,struct_node);
      }
    
    if( struct_node->index==indexes[4] )
      {
       DDL::GuardFieldTypes<NTIndex,State *>(*this,type_check,struct_node);
      }
    
    if( struct_node->index==indexes[5] )
      {
       DDL::GuardFieldTypes<TIndex,Rule *>(*this,type_check,struct_node);
      }
   }
 };

template <class T>
struct DataMap::TypeSet::IsStruct
 {
  static bool Do(const ulen *,ulen) { return false; }
 };

template <>
struct DataMap::TypeSet::IsStruct<TypeDef::NonTerminal>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[0]; }
 };

template <>
struct DataMap::TypeSet::IsStruct<TypeDef::Rule>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[1]; }
 };

template <>
struct DataMap::TypeSet::IsStruct<TypeDef::State>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[2]; }
 };

template <>
struct DataMap::TypeSet::IsStruct<TypeDef::Final>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[3]; }
 };

template <>
struct DataMap::TypeSet::IsStruct<TypeDef::State::Transition>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[4]; }
 };

template <>
struct DataMap::TypeSet::IsStruct<TypeDef::Final::Action>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[5]; }
 };

#endif

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



