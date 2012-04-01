/* LangParser.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "LangParser.h"

namespace App {
namespace LangInput {

/* enum AtomClass */

const char * GetTextDesc(AtomClass ac)
 {
  switch( ac )
    {
     case Atom_Nothing : return "no-atom";
     
     case Atom_Name    : return "name";
      
     case Atom_colon   : return ":";
     case Atom_obr     : return "{";
     case Atom_cbr     : return "}";
     
     default: return "???";
    }
 }

/* struct Atom */

AtomClass Atom::GetPunctClass(StrLen str)
 {
  if( str.len!=1 ) return Atom_Nothing;

  switch( str[0] )
    {
     case ':' : return Atom_colon;
     case '{' : return Atom_obr;
     case '}' : return Atom_cbr;
     
     default: return Atom_Nothing;
    }
 }

AtomClass Atom::GetAtomClass(const Token &token)
 {
  switch( token.tc )
    {
     case Token_Word  : 
     case Token_CWord : return Atom_Name;
        
     case Token_Punct : return GetPunctClass(token.str);
        
     default: return Atom_Nothing; 
    }
 }
  
/* struct Element_Body */

ulen Element_Body::NextState(ulen state)
 {
  static const uint8 Table[]=
   {
    1,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0
   };
  
  return Table[state];
 }
  
/* struct Element_NT */

ulen Element_NT::NextState(ulen state)
 {
  static const uint8 Table[]=
   {
    0,3,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0
   };
  
  return Table[state];
 }

/* struct Element_Rules */

ulen Element_Rules::NextState(ulen state)
 {
  static const uint8 Table[]=
   {
    0,0,0,0,
    0,7,8,0,
    0,0,0,0,
    0,0,0,0
   };
  
  return Table[state];
 }
  
/* struct Element_Rule */

ulen Element_Rule::NextState(ulen state)
 {
  static const uint8 Table[]=
   {
    0,0,0,0,
    0,0,0,10,
    10,0,0,0,
    0,0,0,0
   };
  
  return Table[state];
 }
  
/* struct Element_Str */

ulen Element_Str::NextState(ulen state)
 {
  static const uint8 Table[]=
   {
    0,0,0,0,
    0,0,0,11,
    11,0,0,0,
    0,0,0,0
   };
  
  return Table[state];
 }

/* struct Action */

static const uint8 RuleTable[16][5]=
 {
  {2,2,0,0,0},
  {1,1,0,0,0},
  {0,0,1,1,0},
  {3,3,0,0,0},

  {0,0,0,1,0},
  {0,6,6,0,6},
  {0,6,6,0,6},
  {0,9,9,0,1},

  {0,9,9,0,1},
  {4,4,0,0,0},
  {0,7,7,0,7},
  {0,1,1,0,0},

  {5,5,0,0,0},
  {0,10,10,0,0},
  {0,1,0,0,0},
  {0,8,8,0,8}
 };

static const uint8 AtomStateTable[16][5]=
 {
  {0,0,0,0,0},
  {0,2,0,0,0},
  {0,0,4,5,0},
  {0,0,0,0,0},
  
  {0,0,0,6,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,9},
  
  {0,0,0,0,12},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,13,14,0,0},
  
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,15,0,0,0},
  {0,0,0,0,0}
 };

Action::Action(ulen state,AtomClass ac)
 {
  rule=Rule( RuleTable[state][ac] );
  
  if( rule==Shift )
    {
     new_state=AtomStateTable[state][ac];
    }
  else
    {
     new_state=0;
    }
 }
    
/* class Parser */

void Parser::push(ElementBase *elem,ulen state)
 {
  elem->prev=stack;
  stack=elem;
  
  elem->state=state;
 }

AnyElement Parser::pop()
 {
  ElementBase *elem=stack;
  
  stack=elem->prev;
  
  return AnyElement(elem);
 }

void Parser::shift(const Atom &atom,ulen state)
 {
  push(pool.create<ElementAtom>(atom),state);
 }

Element_Body * Parser::elem_startBody()
 {
  Element_Body *ret=pool.create<Element_Body>();
  
  ret->startBody();
  
  return ret;
 }

Element_Body * Parser::elem_extBody(Element_Body *arg1,Element_NT *arg2)
 {
  Element_Body *ret=pool.create<Element_Body>();
  
  ret->extBody(arg1,arg2);
  
  return ret;
 }

Element_NT * Parser::elem_buildNT(ElementAtom *arg1,ElementAtom *arg2,Element_Rules *arg3,ElementAtom *arg4)
 {
  Element_NT *ret=pool.create<Element_NT>();
  
  ret->buildNT(arg1,arg2,arg3,arg4);
  
  return ret;
 }

Element_NT * Parser::elem_buildNT_start(ElementAtom *arg1,ElementAtom *arg2,ElementAtom *arg3,Element_Rules *arg4,ElementAtom *arg5)
 {
  Element_NT *ret=pool.create<Element_NT>();
  
  ret->buildNT_start(arg1,arg2,arg3,arg4,arg5);
  
  return ret;
 }

Element_Rules * Parser::elem_startRules()
 {
  Element_Rules *ret=pool.create<Element_Rules>();
  
  ret->startRules();
  
  return ret;
 }

Element_Rules * Parser::elem_extRules(Element_Rules *arg1,Element_Rule *arg2)
 {
  Element_Rules *ret=pool.create<Element_Rules>();
  
  ret->extRules(arg1,arg2);
  
  return ret;
 }

Element_Rule * Parser::elem_buildRule(Element_Str *arg1,ElementAtom *arg2,ElementAtom *arg3)
 {
  Element_Rule *ret=pool.create<Element_Rule>();
  
  ret->buildRule(arg1,arg2,arg3);
  
  return ret;
 }

Element_Str * Parser::elem_startStr()
 {
  Element_Str *ret=pool.create<Element_Str>();
  
  ret->startStr();
  
  return ret;
 }

Element_Str * Parser::elem_extStr(Element_Str *arg1,ElementAtom *arg2)
 {
  Element_Str *ret=pool.create<Element_Str>();
  
  ret->extStr(arg1,arg2);
  
  return ret;
 }

void Parser::do_startBody()
 {
  Element_Body *elem=elem_startBody();
  
  ulen new_state=elem->NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extBody()
 {
  Element_NT *arg2=pop();
  Element_Body *arg1=pop();
  
  Element_Body *elem=elem_extBody(arg1,arg2);
  
  ulen new_state=elem->NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_buildNT()
 {
  ElementAtom *arg4=pop();
  Element_Rules *arg3=pop();
  ElementAtom *arg2=pop();
  ElementAtom *arg1=pop();
  
  Element_NT *elem=elem_buildNT(arg1,arg2,arg3,arg4);
  
  ulen new_state=elem->NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_buildNT_start()
 {
  ElementAtom *arg5=pop();
  Element_Rules *arg4=pop();
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  ElementAtom *arg1=pop();
  
  Element_NT *elem=elem_buildNT_start(arg1,arg2,arg3,arg4,arg5);
  
  ulen new_state=elem->NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_startRules()
 {
  Element_Rules *elem=elem_startRules();
  
  ulen new_state=elem->NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extRules()
 {
  Element_Rule *arg2=pop();
  Element_Rules *arg1=pop();
  
  Element_Rules *elem=elem_extRules(arg1,arg2);
  
  ulen new_state=elem->NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_buildRule()
 {
  ElementAtom *arg3=pop();
  ElementAtom *arg2=pop();
  Element_Str *arg1=pop();
  
  Element_Rule *elem=elem_buildRule(arg1,arg2,arg3);
  
  ulen new_state=elem->NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_startStr()
 {
  Element_Str *elem=elem_startStr();
  
  ulen new_state=elem->NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_extStr()
 {
  ElementAtom *arg2=pop();
  Element_Str *arg1=pop();
  
  Element_Str *elem=elem_extStr(arg1,arg2);
  
  ulen new_state=elem->NextState(stack->state);

  push(elem,new_state);
 }

void Parser::doRule(Action::Rule rule)
 {
  switch( rule )
    {
     case Action::Do_startBody : do_startBody(); break;
     case Action::Do_extBody : do_extBody(); break;
     case Action::Do_buildNT : do_buildNT(); break;
     case Action::Do_buildNT_start : do_buildNT_start(); break;
     case Action::Do_startRules : do_startRules(); break;
     case Action::Do_extRules : do_extRules(); break;
     case Action::Do_buildRule : do_buildRule(); break;
     case Action::Do_startStr : do_startStr(); break;
     case Action::Do_extStr : do_extStr(); break;
    }
 }

Parser::Parser()
 {
  stack=pool.create<ElementBase>();
 }

Parser::~Parser() 
 {
 }

auto Parser::next(const Atom &atom) -> Result
 {
  Action action(stack->state,atom.ac);
  
  switch( action.rule )
    {
     case Action::Abort :
      {
       Printf(Con,"Parser #; : unexpected atom #;\n",atom.token.pos,atom.ac);
      }
     return ResultAbort;
     
     case Action::Shift : shift(atom,action.new_state); return ResultShift;
     
     default: doRule(action.rule);
    }
  
  return ResultRule;
 }

auto Parser::complete(TextPos pos) -> Result
 {
  Action action(stack->state);
  
  switch( action.rule )
    {
     case Action::Abort :
      {
       Printf(Con,"Parser #; : unexpected end-of-file\n",pos);
      }
     return ResultAbort;
     
     case Action::Shift : return ResultShift;
     
     default: doRule(action.rule);
    }
  
  return ResultRule;
 }

void Parser::do_next(const Atom &atom)
 {
  Result result;
  
  do
    {
     result=next(atom);
    }
  while( result==ResultRule );
  
  if( result==ResultAbort )
    {
     Printf(Exception,"Parser error");
    }
 }

void Parser::do_complete(TextPos pos)
 {
  Result result;
  
  do
    {
     result=complete(pos);
    }
  while( result==ResultRule );
  
  if( result==ResultAbort )
    {
     Printf(Exception,"Parser error");
    }
 }

} // namespace LangInput
} // namespace App
