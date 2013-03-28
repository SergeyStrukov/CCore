/* StateTypes.ddl */
//----------------------------------------------------------------------------------------
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

type ElementIndex = uint ;
type RuleIndex = uint ;
type FinalIndex = uint ;
type StateIndex = uint ;

struct Element 
 {
  ElementIndex element;

  text name;

  Rule * [] rules; // for non-atoms
 };

struct Rule
 {
  RuleIndex rule;

  text name;

  Element * result; // non-atom
  Element * [] args;
 };

struct Final
 {
  FinalIndex final;

  struct Action { Element *atom; Rule *rule; } [] actions;
 };

struct State
 {
  StateIndex state;

  struct Transition { Element *element; State *state; } [] transitions;

  Final *final;
 };

