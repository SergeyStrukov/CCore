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

struct PrintElement;

struct PrintRule;

struct PrintFinal;

struct PrintState;

struct PrintAction;

struct PrintTransition;

/* struct PrintElement */

struct PrintElement : TypeDef::Element
 {
  PrintElement(const TypeDef::Element &obj) : TypeDef::Element(obj) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"( #; , #; )",element,name);
    
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
    if( result )
      {
       Printf(out,"( #; , #; , #; , {",rule,name,result->name);
       
       auto r=args;
       
       if( +r )
         {
          Printf(out," #;",(*r)->name);
          
          for(++r; +r ;++r) Printf(out,", #;",(*r)->name);
         }
       
       Putobj(out," } )");
      } 
    else
      {
       Printf(out,"( #; , #; )",rule,name);
      }
   }
 };

/* struct PrintFinal */

struct PrintFinal : TypeDef::Final
 {
  PrintFinal(const TypeDef::Final &obj) : TypeDef::Final(obj) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"( #; )",final);

    for(auto action : actions ) Printf(out,"\n  #;",action);
   }
 };

/* struct PrintState */

struct PrintState : TypeDef::State
 {
  PrintState(const TypeDef::State &obj) : TypeDef::State(obj) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"( #; )",state);

    for(auto transition : transitions ) Printf(out,"\n  #;",transition);
    
    Printf(out,"\n  #;",*final);
   }
 };

/* struct PrintAction */

struct PrintAction : TypeDef::Final::Action
 {
  PrintAction(const TypeDef::Final::Action &obj) : TypeDef::Final::Action(obj) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#; => #;",atom->name,rule->name);
   }
 };

/* struct PrintTransition */

struct PrintTransition : TypeDef::State::Transition
 {
  PrintTransition(const TypeDef::State::Transition &obj) : TypeDef::State::Transition(obj) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#; -> #;",element->name,state->state);
   }
 };

} // namespace App

namespace CCore {

/* print proxy */

template <>
struct PrintProxy<App::TypeDef::Element>
 {
  typedef App::PrintElement ProxyType;
 };

template <>
struct PrintProxy<App::TypeDef::Rule>
 {
  typedef App::PrintRule ProxyType;
 };

template <>
struct PrintProxy<App::TypeDef::Final>
 {
  typedef App::PrintFinal ProxyType;
 };

template <>
struct PrintProxy<App::TypeDef::State>
 {
  typedef App::PrintState ProxyType;
 };

template <>
struct PrintProxy<App::TypeDef::Final::Action>
 {
  typedef App::PrintAction ProxyType;
 };

template <>
struct PrintProxy<App::TypeDef::State::Transition>
 {
  typedef App::PrintTransition ProxyType;
 };

} // namespace CCore

namespace App {

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
   
   PtrLen<TypeDef::Element> getAtoms() const { return table_Element.prefix(TypeDef::Element::AtomLim); }
   PtrLen<TypeDef::Element> getNonAtoms() const { return table_Element.part(TypeDef::Element::AtomLim); }
 };

} // namespace App

#endif

