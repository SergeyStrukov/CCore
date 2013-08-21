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

type AtomIndex = ulen ;
type SyntIndex = ulen ;
type KindIndex = ulen ;
type ElementIndex = ulen ;
type RuleIndex = ulen ;
type StateIndex = ulen ;
type FinalIndex = ulen ;

struct Lang
 {
  Atom[] atoms;
  Synt[] synts;
  Element[] elements;
  Rule[] rules;
  State[] states;
  Final[] finals;
 };

struct Atom
 {
  AtomIndex index;
  text name;
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
  KindIndex index;
  text name;

  Synt *synt;
 };

struct Element
 {
  ElementIndex index;
  
  Atom *atom;
  Kind *kind;
 };

struct Rule
 {
  RuleIndex index;
  text name;

  Kind *result;

  struct Arg
   {
    Atom *atom;
    Synt *synt;
   };

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

