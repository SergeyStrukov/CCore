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

struct PrintNonTerminal;

struct PrintRule;

struct PrintState;

struct PrintFinal;

struct PrintTransition;

struct PrintAction;

/* struct PrintNonTerminal */

struct PrintNonTerminal : TypeDef::NonTerminal
 {
  PrintNonTerminal(const TypeDef::NonTerminal &obj) : TypeDef::NonTerminal(obj) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"{#;,#;}",nt,name);
    
    for(auto *ptr : rules ) Printf(out,"\n  #;",*ptr);
   }
 };

/* struct PrintRule */

struct PrintRule : TypeDef::Rule
 {
  PrintRule(const TypeDef::Rule &obj) : TypeDef::Rule(obj) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"{#;,#;,#;,#;}",rule,name,result,PrintSet(str));
   }
 };

/* struct PrintState */

struct PrintState : TypeDef::State
 {
  PrintState(const TypeDef::State &obj) : TypeDef::State(obj) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"{#;}",state);

    for(auto transition : transitions ) Printf(out,"\n  #;",transition);
    
    Printf(out,"\n #;",*final);
   }
 };

/* struct PrintFinal */

struct PrintFinal : TypeDef::Final
 {
  PrintFinal(const TypeDef::Final &obj) : TypeDef::Final(obj) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"{#;}",final);

    for(auto action : actions) Printf(out,"\n  #;",action);
   }
 };

/* struct PrintTransition */

struct PrintTransition : TypeDef::State::Transition
 {
  PrintTransition(const TypeDef::State::Transition &obj) : TypeDef::State::Transition(obj) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"{#;} -> #;",ntt,state->state);
   }
 };

/* struct PrintAction */

struct PrintAction : TypeDef::Final::Action
 {
  PrintAction(const TypeDef::Final::Action &obj) : TypeDef::Final::Action(obj) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"{#;} => #;",t,rule->name);
   }
 };

} // namespace App

namespace CCore {

/* print proxy */

template <>
struct PrintProxy<App::TypeDef::NonTerminal>
 {
  typedef App::PrintNonTerminal ProxyType;
 };

template <>
struct PrintProxy<App::TypeDef::Rule>
 {
  typedef App::PrintRule ProxyType;
 };

template <>
struct PrintProxy<App::TypeDef::State>
 {
  typedef App::PrintState ProxyType;
 };

template <>
struct PrintProxy<App::TypeDef::Final>
 {
  typedef App::PrintFinal ProxyType;
 };

template <>
struct PrintProxy<App::TypeDef::State::Transition>
 {
  typedef App::PrintTransition ProxyType;
 };

template <>
struct PrintProxy<App::TypeDef::Final::Action>
 {
  typedef App::PrintAction ProxyType;
 };

} // namespace CCore

namespace App {

/* classes */

class DataMap;

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

