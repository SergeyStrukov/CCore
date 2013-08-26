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

#include <CCore/inc/sys/SysProp.h>

namespace App {

/* functions */

void Process(StrLen file_name)
 {
  Printf(Con,"Load file #.q;\n\n",file_name);
  
  DataMap data(file_name);
  
  data.sanity();
  
  Printf(Con,"Sanity is OK\n\n");
  
  unsigned cpu_count=Sys::GetCpuCount();
  
  const ulen Count = 100000 ;
  const ulen Cap = 20 ;

  if( cpu_count>1 )
    {
     TrackStep_mt track(Count);
    
     RunTasks run;
     
     run.run(cpu_count, [&] () 
                            {
                             TopGenerator gen(data);
    
                             TopTest test(data);
    
                             while( track.step() ) gen(test,Cap);
                            } 
            );
    }
  else
    {
     TopGenerator gen(data);
  
     TopTest test(data);
  
     for(TrackStep track(Count); track.step() ;) gen(test,Cap);
    } 
  
  Printf(Con,"Test is OK\n\n");
  
#if 0  
  
  {
   BottomGenerator gen(data);
   
   const ulen Count = 10000 ;
   const ulen Cap = 20 ;
  
   BottomTest test(data);
  
   for(TrackStep track(Count); track.step() ;) gen(test,Cap);
  }
  
  Printf(Con,"Bottom test is OK\n\n");
  
#endif  
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

/* class TrackStep_mt */

bool TrackStep_mt::step()
 {
  auto val=ind++;
  
  if( val>=count )
    {
     if( val==count )
       {
        Mutex::Lock lock(mutex);
        
        Printf(Con,"step = #;\n\n",val);
        
        flag=true;
        shown=val;
       }
    
     return false;
    }
  
  if( (val%100)==0 )
    {
     Mutex::Lock lock(mutex);
     
     if( !flag || val>shown )
       {
        Printf(Con,"step = #;\r",val);
        
        flag=true;
        shown=val;
       }
    }
  
  return true;
 }

/* class TopGenerator */

TopGenerator::TopGenerator(const DataMap &data) 
 : lang(data.getLang().lang)
 {
  DynArray<TypeDef::Kind *> kind_list(DoReserve,1024);
  
  for(auto &synt : data.getLang().synts )
    for(auto &kind : synt.kinds )
      kind_list.append_copy(&kind);
  
  ulen len=kind_list.getLen();
  
  table.extend_default(len);
  
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

TopGenerator::~TopGenerator()
 {
 }

/* class TopParser */

TypeDef::State * TopParser::topState()
 {
  ulen len=stack.getLen();
  
  if( len==0 )
    {
     Printf(Exception,"App::TopParser::topState() : empty stack");
    }
  
  return stack[len-1].state;
 }

auto TopParser::topElements(ulen count) -> Rec *
 {
  ulen len=stack.getLen();
  
  if( len<=count )
    {
     Printf(Exception,"App::TopParser::topElements(count=#;) : too short stack",count);
    }
  
  return stack.getPtr()+(len-count);
 }

void TopParser::check_result()
 {
  if( stack.getLen()!=2 )
    {
     Printf(Exception,"App::TopParser::check_result() : bad stack");
    }
  
  struct Check
   {
    PtrLen<TypeDef::Synt *> lang;
    
    explicit Check(PtrLen<TypeDef::Synt *> lang_) : lang(lang_) {}
    
    void operator () (TypeDef::Atom *)
     {
      Printf(Exception,"App::TopParser::check_result() : result is atom");
     }
    
    void operator () (TypeDef::Kind *kind)
     {
      auto *synt=kind->synt;
      
      for(auto p=lang; +p ;++p)
        if( synt==*p )
          return;
      
      Printf(Exception,"App::TopParser::check_result() : bad result");
     }
   };
  
  stack[1].element.apply( Check(lang) );
 }

TypeDef::Rule * TopParser::Find(PtrLen<TypeDef::Final::Action> actions,TypeDef::Atom *atom)
 {
  if( !atom )
    {
     if( !actions || actions[0].atom )
       {
        Printf(Exception,"App::TopParser::Find(...) : bad input atom");
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
        Printf(Exception,"App::TopParser::Find(...) : bad input atom");
       }
      
     return actions->rule;
    }
 }

TypeDef::State * TopParser::Transition(PtrLen<TypeDef::State::Transition> transitions,TypeDef::Element *element)
 {
  ulen index=element->index;
  
  Algon::BinarySearch_if(transitions, [=] (const TypeDef::State::Transition &t) { return t.element->index>=index; } );
  
  if( !transitions || transitions->element!=element )
    {
     Printf(Exception,"App::TopParser::Transition(...) : no transition");
    }
   
  return transitions->state;
 }

TypeDef::State * TopParser::Transition(PtrLen<TypeDef::State::Transition> transitions,TypeDef::Atom *atom)
 {
  return Transition(transitions,atom->element);
 }

TypeDef::State * TopParser::Transition(PtrLen<TypeDef::State::Transition> transitions,TypeDef::Kind *kind)
 {
  return Transition(transitions,kind->element);
 }

bool TopParser::IsSame(AnyPtr<TypeDef::Atom,TypeDef::Kind> element,const TypeDef::TopRule::Arg &arg)
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

TopParser::TopParser(const DataMap &data)
 : start_state(data.getLang().states.ptr), 
   lang(data.getLang().lang)
 {
  reset();
 }

TopParser::~TopParser()
 {
 }

void TopParser::reset()
 {
  stack.erase();
  stack.reserve(1024);
  
  push(start_state);
 }

void TopParser::next(TypeDef::Atom *atom,TypeDef::TopRule *rule)
 {
  TypeDef::State *state=topState();
  
  TypeDef::Rule *bottom_rule=Find(state->final->actions,atom);
  
  if( rule->bottom!=bottom_rule )
    {
     Printf(Exception,"App::TopParser::next(...) : rule mismatch");
    }
  
  auto args=rule->args;
  
  auto *ptr=topElements(args.len);

  for(auto p=args; +p ;++p,++ptr)
    {
     if( !IsSame(ptr->element,*p) )
       {
        Printf(Exception,"App::TopParser::next(...) : bad stack");
       }
    }
  
  pop(args.len);
  
  TypeDef::Kind *result=rule->result;
  
  push(result,Transition(topState()->transitions,result));
 }

void TopParser::next(TypeDef::Atom *atom)
 {
  TypeDef::State *state=topState();
  
  TypeDef::Rule *rule=Find(state->final->actions,atom);
  
  if( rule )
    {
     Printf(Exception,"App::TopParser::next(...) : rule mismatch");
    }
  
  if( atom ) 
    push(atom,Transition(state->transitions,atom));
  else
    check_result();
 }

/* class TopTest */

TopTest::TopTest(const DataMap &data)
 : parser(data)
 {
 }
   
TopTest::~TopTest()
 {
 }
   
void TopTest::start()
 {
  stack.erase();
  stack.reserve(1024);
  
  parser.reset();
 }
   
void TopTest::next_atom(TypeDef::Atom *atom)
 {
  for(auto rules=Range(stack); +rules ;++rules) parser.next(atom,*rules);
  
  parser.next(atom);
  
  stack.shrink_all();
 }
   
void TopTest::next_rule(TypeDef::TopRule *rule)
 {
  stack.append_copy(rule);
 }
   
void TopTest::stop()
 {
  next_atom(0);
 }
   
/* class BottomGenerator */

BottomGenerator::BottomGenerator(const DataMap &data)
 : lang(data.getLang().lang)
 {
  auto synts=data.getLang().synts;
  
  table.extend_default(synts.len);
  
  DynArray<TypeDef::Synt *> synt_list(DoReserve,synts.len);
  
  for(auto &synt : synts ) synt_list.append_copy(&synt);
  
  ulen count=0;
  
  while( count<synts.len )
    {
     bool flag=false;
     
     for(ulen ind=count; ind<synts.len ;ind++)
       {
        auto *synt=synt_list[ind];
       
        if( auto *rule=findRule(synt) )
          {
           defRule(synt,rule);
           
           if( ind>count ) Swap(synt_list[ind],synt_list[count]);
           
           count++;
           flag=true;
          }
       }
     
     if( !flag )
       {
        Printf(Exception,"App::BottomGenerator::BottomGenerator(...) : bad lang");
       }
    }
 }

BottomGenerator::~BottomGenerator()
 {
 }

/* class BottomParser */

TypeDef::State * BottomParser::topState()
 {
  ulen len=stack.getLen();
  
  if( len==0 )
    {
     Printf(Exception,"App::BottomParser::topState() : empty stack");
    }
  
  return stack[len-1].state;
 }

auto BottomParser::topElements(ulen count) -> Rec *
 {
  ulen len=stack.getLen();
  
  if( len<=count )
    {
     Printf(Exception,"App::BottomParser::topElements(count=#;) : too short stack",count);
    }
  
  return stack.getPtr()+(len-count);
 }

void BottomParser::check_result()
 {
  if( stack.getLen()!=2 )
    {
     Printf(Exception,"App::BottomParser::check_result() : bad stack");
    }
  
  struct Check
   {
    PtrLen<TypeDef::Synt *> lang;
    
    explicit Check(PtrLen<TypeDef::Synt *> lang_) : lang(lang_) {}
    
    void operator () (TypeDef::Atom *)
     {
      Printf(Exception,"App::BottomParser::check_result() : result is atom");
     }
    
    void operator () (TypeDef::Synt *synt)
     {
      for(auto p=lang; +p ;++p)
        if( synt==*p )
          return;
      
      Printf(Exception,"App::BottomParser::check_result() : bad result");
     }
   };
  
  stack[1].element.apply( Check(lang) );
 }

TypeDef::Rule * BottomParser::Find(TypeDef::State *state,TypeDef::Atom *atom)
 {
  PtrLen<TypeDef::Final::Action> actions=state->final->actions;
  
  if( !atom )
    {
     if( !actions || actions[0].atom )
       {
        Printf(Exception,"App::BottomParser::Find(...) : state #;) : bad input atom (End)",state->index);
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
        Printf(Exception,"App::BottomParser::Find(...) : state #;) : bad input atom #;",state->index,atom->name);
       }
      
     return actions->rule;
    }
 }

TypeDef::State * BottomParser::Transition(PtrLen<TypeDef::State::Transition> transitions,TypeDef::Element *element)
 {
  ulen index=element->index;
  
  Algon::BinarySearch_if(transitions, [=] (const TypeDef::State::Transition &t) { return t.element->index>=index; } );
  
  if( !transitions || transitions->element!=element )
    {
     Printf(Exception,"App::BottomParser::Transition(...) : no transition");
    }
   
  return transitions->state;
 }
   
TypeDef::State * BottomParser::Transition(PtrLen<TypeDef::State::Transition> transitions,TypeDef::Atom *atom)
 {
  return Transition(transitions,atom->element);
 }
   
TypeDef::State * BottomParser::Transition(PtrLen<TypeDef::State::Transition> transitions,TypeDef::Kind *kind)
 {
  return Transition(transitions,kind->element);
 }
   
bool BottomParser::IsSame(AnyPtr<TypeDef::Atom,TypeDef::Synt> element,const TypeDef::Rule::Arg &arg)
 {
  struct Compare
   {
    bool &ret;
    TypeDef::Rule::Arg arg;
    
    Compare(bool &ret_,const TypeDef::Rule::Arg &arg_) : ret(ret_),arg(arg_) {}
    
    void operator () (TypeDef::Atom *atom)
     {
      ret=( arg.atom==atom );
     }
    
    void operator () (TypeDef::Synt *synt)
     {
      ret=( arg.synt==synt );
     }
   };
  
  bool ret=false;
  
  element.apply( Compare(ret,arg) );
  
  return ret;
 }

BottomParser::BottomParser(const DataMap &data)
 : start_state(data.getLang().states.ptr), 
   lang(data.getLang().lang)
 {
  reset();
 }
   
BottomParser::~BottomParser()
 {
 }
   
void BottomParser::reset()
 {
  stack.erase();
  stack.reserve(1024);
  
  push(start_state);
 }
   
bool BottomParser::next(TypeDef::Atom *atom)
 {
  TypeDef::State *state=topState();
  
  TypeDef::Rule *rule=Find(state,atom);
  
  if( rule )
    {
     auto args=rule->args;
    
     auto *ptr=topElements(args.len);

     for(auto p=args; +p ;++p,++ptr)
       {
        if( !IsSame(ptr->element,*p) )
          {
           Printf(Exception,"App::BottomParser::next(...) : bad stack");
          }
       }
    
     pop(args.len);
    
     TypeDef::Kind *result=rule->result;
    
     push(result->synt,Transition(topState()->transitions,result));
     
     return false;
    }
  else
    {
     if( atom ) 
       push(atom,Transition(state->transitions,atom));
     else
       check_result();
     
     return true;
    }
 }
   
/* class BottomTest */

BottomTest::BottomTest(const DataMap &data)
 : parser(data)
 {
 }
   
BottomTest::~BottomTest()
 {
 }
   
void BottomTest::start()
 {
  parser.reset();
 }
   
void BottomTest::next(TypeDef::Atom *atom)
 {
  while( !parser.next(atom) );
 }
   
void BottomTest::stop()
 {
  while( !parser.next(0) );
 }

} // namespace App

