/* LangTypes.ddl */
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

type AtomIndex = uint32 ;
type SyntIndex = uint32 ;
type KindIndex = uint32 ;
type ElementIndex = uint32 ;
type RuleIndex = uint32 ;
type StateIndex = uint32 ;
type FinalIndex = uint32 ;

struct Lang
 {
  Atom[] atoms;
  Synt[] synts;
  Synt * [] lang;
  Element[] elements;
  Rule[] rules;
  TopRule[] top_rules;
  State[] states;
  Final[] finals;
 };

struct Atom
 {
  AtomIndex index;
  text name;
  
  Element *element;
 };

struct Synt
 {
  SyntIndex index;
  text name;
  
  Kind[] kinds;
  Rule * [] rules;
 };

struct Kind
 {
  KindIndex kindex; // index among all kinds
  KindIndex index; // index in synt array
  text name;

  Synt *synt;
  
  Element *element;
  
  TopRule * [] rules;
 };

struct Element
 {
  ElementIndex index;
  
  {Atom,Kind} * elem;
 };

struct Rule
 {
  RuleIndex index;
  text name;

  Kind *result;

  type Arg = {Atom,Synt} * ;

  Arg[] args;
 };
 
struct TopRule
 {
  RuleIndex index;
  text name;
  
  Rule *bottom;

  Kind *result;

  type Arg = {Atom,Kind} * ;

  Arg[] args;
 }; 

struct State
 {
  StateIndex index;
  Final *final;

  struct Transition
   {
    Element *element;
    State *state;
   };

  Transition[] transitions;
 };

struct Final
 {
  FinalIndex index;

  struct Action
   {
    Atom *atom; // null for (End)
    Rule *rule; // null for <- ( STOP if atom is (END) )
   };

  Action[] actions;
 };

