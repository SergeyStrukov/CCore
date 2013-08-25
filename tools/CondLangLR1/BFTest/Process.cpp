/* Process.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1-BFTest 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "Process.h"

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/algon/BinarySearch.h>

namespace App {

/* functions */

void Process(StrLen file_name)
 {
  Printf(Con,"Load file #.q;\n\n",file_name);
  
  DataMap data(file_name);
  
  data.sanity();
  
  Printf(Con,"Sanity is OK\n\n");
  
  TopGenerator gen(data);
  
  const ulen Count = 10000 ;
  const ulen Cap = 20 ;
  
  TestParser test(data);
  
  for(TrackStep track(Count); track.step() ;) gen(test,Cap);
  
  Printf(Con,"Top test is OK\n\n");
 }

/* class TrackStep */

bool TrackStep::step()
 {
  if( ind>=count )
    {
     Printf(Con,"step = #;\n\n",ind);
    
     return false;
    }

  if( (ind%100)==0 ) Printf(Con,"step = #;\r",ind);
  
  ind++;
  
  return true;
 }

/* class TopGenerator */

TopGenerator::TopGenerator(const DataMap &data) 
 : lang(data.getLang().lang),
   table(data.getLang().synts.len)
 {
  DynArray<TypeDef::Kind *> kind_list(DoReserve,1024);
  
  {
   for(auto &synt : data.getLang().synts )
     {
      for(auto &kind : synt.kinds )
        {
         kind_list.append_fill(&kind);
        }
      
      table[synt.index].extend_default(synt.kinds.len);
     }
  }
  
  ulen len=kind_list.getLen();
  ulen count=0;
  
  while( count<len )
    {
     bool flag=false;
     
     for(ulen ind=count; ind<len ;ind++)
       {
        auto *kind=kind_list[ind];
       
        if( auto *rule=findRule(kind) )
          {
           defRule(kind,rule);
           
           if( ind>count ) Swap(kind_list[ind],kind_list[count]);
           
           count++;
           flag=true;
          }
       }
     
     if( !flag )
       {
        Printf(Exception,"App::TopGenerator::TopGenerator(...) : bad lang");
       }
    }
 }

/* class Parser */

TypeDef::State * Parser::topState()
 {
  ulen len=stack.getLen();
  
  if( len==0 )
    {
     Printf(Exception,"App::Parser::topState() : empty stack");
    }
  
  return stack[len-1].state;
 }

auto Parser::topElements(ulen count) -> Rec *
 {
  ulen len=stack.getLen();
  
  if( len<=count )
    {
     Printf(Exception,"App::Parser::topElements(count=#;) : too short stack",count);
    }
  
  return stack.getPtr()+(len-count);
 }

void Parser::check_result()
 {
  if( stack.getLen()!=2 )
    {
     Printf(Exception,"App::Parser::check_result() : bad stack");
    }
  
  struct Check
   {
    PtrLen<TypeDef::Synt *> lang;
    
    explicit Check(PtrLen<TypeDef::Synt *> lang_) : lang(lang_) {}
    
    void operator () (TypeDef::Atom *)
     {
      Printf(Exception,"App::Parser::check_result() : result is atom");
     }
    
    void operator () (TypeDef::Kind *kind)
     {
      auto *synt=kind->synt;
      
      for(auto p=lang; +p ;++p)
        if( synt==*p )
          return;
      
      Printf(Exception,"App::Parser::check_result() : bad result");
     }
   };
  
  stack[1].element.apply( Check(lang) );
 }

TypeDef::Rule * Parser::Find(PtrLen<TypeDef::Final::Action> actions,TypeDef::Atom *atom)
 {
  if( !atom )
    {
     if( !actions || actions[0].atom )
       {
        Printf(Exception,"App::Parser::Find(...) : bad input atom");
       }
     
     return actions[0].rule;
    }
  else
    {
     if( +actions && !actions[0].atom ) ++actions;
     
     ulen index=atom->index;
     
     Algon::BinarySearch_if(actions, [=] (const TypeDef::Final::Action &action) { return action.atom->index>=index; } );
     
     if( !actions || actions->atom!=atom )
       {
        Printf(Exception,"App::Parser::Find(...) : bad input atom");
       }
      
     return actions->rule;
    }
 }

TypeDef::State * Parser::Transition(PtrLen<TypeDef::State::Transition> transitions,TypeDef::Element *element)
 {
  ulen index=element->index;
  
  Algon::BinarySearch_if(transitions, [=] (const TypeDef::State::Transition &t) { return t.element->index>=index; } );
  
  if( !transitions || transitions->element!=element )
    {
     Printf(Exception,"App::Parser::Transition(...) : no transition");
    }
   
  return transitions->state;
 }

TypeDef::State * Parser::Transition(PtrLen<TypeDef::State::Transition> transitions,TypeDef::Atom *atom)
 {
  return Transition(transitions,atom->element);
 }

TypeDef::State * Parser::Transition(PtrLen<TypeDef::State::Transition> transitions,TypeDef::Kind *kind)
 {
  return Transition(transitions,kind->element);
 }

bool Parser::IsSame(AnyPtr<TypeDef::Atom,TypeDef::Kind> element,const TypeDef::TopRule::Arg &arg)
 {
  struct Compare
   {
    bool &ret;
    TypeDef::TopRule::Arg arg;
    
    Compare(bool &ret_,const TypeDef::TopRule::Arg &arg_) : ret(ret_),arg(arg_) {}
    
    void operator () (TypeDef::Atom *atom)
     {
      ret=( arg.atom==atom );
     }
    
    void operator () (TypeDef::Kind *kind)
     {
      ret=( arg.kind==kind );
     }
   };
  
  bool ret=false;
  
  element.apply( Compare(ret,arg) );
  
  return ret;
 }

Parser::Parser(const DataMap &data)
 : start_state(data.getLang().states.ptr), 
   lang(data.getLang().lang)
 {
  reset();
 }

Parser::~Parser()
 {
 }

void Parser::reset()
 {
  stack.erase();
  stack.reserve(1024);
  
  push(start_state);
 }

void Parser::next(TypeDef::Atom *atom,TypeDef::TopRule *rule)
 {
  TypeDef::State *state=topState();
  
  TypeDef::Rule *bottom_rule=Find(state->final->actions,atom);
  
  if( rule->bottom!=bottom_rule )
    {
     Printf(Exception,"App::Parser::next(...) : rule mismatch");
    }
  
  auto args=rule->args;
  
  auto *ptr=topElements(args.len);

  for(auto p=args; +p ;++p,++ptr)
    {
     if( !IsSame(ptr->element,*p) )
       {
        Printf(Exception,"App::Parser::next(...) : bad stack");
       }
    }
  
  pop(args.len);
  
  TypeDef::Kind *result=rule->result;
  
  push(result,Transition(topState()->transitions,result));
 }

void Parser::next(TypeDef::Atom *atom)
 {
  TypeDef::State *state=topState();
  
  TypeDef::Rule *rule=Find(state->final->actions,atom);
  
  if( rule )
    {
     Printf(Exception,"App::Parser::next(...) : rule mismatch");
    }
  
  if( atom ) 
    push(atom,Transition(state->transitions,atom));
  else
    check_result();
 }

/* class TestParser */

TestParser::TestParser(const DataMap &data)
 : parser(data)
 {
 }
   
TestParser::~TestParser()
 {
 }
   
void TestParser::start()
 {
  stack.erase();
  stack.reserve(1024);
  
  parser.reset();
 }
   
void TestParser::next_atom(TypeDef::Atom *atom)
 {
  for(auto rules=Range(stack); +rules ;++rules) parser.next(atom,*rules);
  
  parser.next(atom);
  
  stack.shrink_all();
 }
   
void TestParser::next_rule(TypeDef::TopRule *rule)
 {
  stack.append_copy(rule);
 }
   
void TestParser::stop()
 {
  next_atom(0);
 }
   
} // namespace App

