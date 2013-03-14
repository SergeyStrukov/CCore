/* DataMap.h */
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

#ifndef ParserGen_DataMap_h
#define ParserGen_DataMap_h

#include <CCore/inc/ddl/DDLTypes.h>

#include <CCore/inc/PrintSet.h>

namespace App {

/* using */

using namespace CCore;

/* TypeDef */

#include "StateTypes.TypeDef.gen.h"

/* classes */

class DataMap;

#if 0

/* struct TypeDef */

struct TypeDef
 {
  // types
  
  using RIndex = DDL::imp_uint ;
  using TIndex = DDL::imp_uint ;
  using NIndex = DDL::imp_uint ;
  using NTIndex = DDL::imp_uint ;
  using StateIndex = DDL::imp_uint ;
  using FinalIndex = DDL::imp_uint ;
  
  // structures
  
  struct Rule;
  
  struct Final
   {
    struct Action 
     { 
      TIndex t; 
      Rule *rule;
      
      template <class P>
      void print(P &out) const
       {
        Printf(out,"{#;} => #;",t,rule->name);
       }
     };
    
    FinalIndex final;
    PtrLen<Action> actions;
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"{#;}",final);

      for(auto action : actions) Printf(out,"\n  #;",action);
     }
   };
  
  static_assert( std::is_standard_layout<Final>::value,"Final : non-standard layout");
  static_assert( std::is_standard_layout<Final::Action>::value,"Final::Action : non-standard layout");

  struct State
   {
    struct Transition 
     { 
      NTIndex ntt; 
      State *state;
      
      template <class P>
      void print(P &out) const
       {
        Printf(out,"{#;} -> #;",ntt,state->state);
       }
     };
    
    StateIndex state;
    PtrLen<Transition> transitions;
    Final *final;
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"{#;}",state);

      for(auto transition : transitions ) Printf(out,"\n  #;",transition);
      
      Printf(out,"\n #;",*final);
     }
   };

  static_assert( std::is_standard_layout<State>::value,"State : non-standard layout");
  static_assert( std::is_standard_layout<State::Transition>::value,"State::Transition : non-standard layout");
  
  struct Rule
   {
    RIndex rule;
    StrLen name;
    NIndex result;
    PtrLen<NTIndex> str;
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"{#;,#;,#;,#;}",rule,name,result,PrintSet(str));
     }
   };
  
  static_assert( std::is_standard_layout<Rule>::value,"Rule : non-standard layout");
  
  struct NonTerminal
   {
    NIndex nt;
    StrLen name;
    PtrLen<Rule *> rules;
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"{#;,#;}",nt,name);
      
      for(auto *ptr : rules ) Printf(out,"\n  #;",*ptr);
     }
   };
  
  static_assert( std::is_standard_layout<NonTerminal>::value,"NonTerminal : non-standard layout");
 };

#endif

/* class DataMap */

class DataMap : NoCopy
 {
   void *mem;
   
   PtrLen<TypeDef::Final>       table_Final;
   PtrLen<TypeDef::State>       table_State;
   PtrLen<TypeDef::NonTerminal> table_NonTerminal;
   PtrLen<TypeDef::Rule>        table_Rule;
   PtrLen<StrLen>               table_TNames;
   
   //struct TypeSet;
 
  public:
  
   explicit DataMap(StrLen file_name);
   
   ~DataMap();
   
   PtrLen<TypeDef::Final>       getFinals() { return table_Final; }
   PtrLen<TypeDef::State>       getStates() { return table_State; }
   PtrLen<TypeDef::NonTerminal> getNonTerminals() { return table_NonTerminal; }
   PtrLen<TypeDef::Rule>        getRules() { return table_Rule; }
   PtrLen<StrLen>               getTNames() { return table_TNames; }
 };

} // namespace App

#endif

