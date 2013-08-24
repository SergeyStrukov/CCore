/* Process.h */
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

#ifndef BFTest_Process_h
#define BFTest_Process_h

#include "DataMap.h"

#include <CCore/inc/AnyPtr.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Random.h>

namespace App {

/* functions */

void Process(StrLen file_name);

/* classes */

class TopGenerator;

class Parser;

class TestParser;

/* class TopGenerator */

class TopGenerator : NoCopy
 {
   Random random;
   PtrLen<TypeDef::Synt *> lang;
   
   DynArray<DynArray<TypeDef::TopRule *> > table;
   
  private: 
  
   template <class T>
   T select(PtrLen<T> range)
    { 
     return range[random.select((uint32)range.len)];
    }
   
   template <class T>
   T * select_ptr(PtrLen<T> range)
    { 
     return range.ptr+random.select((uint32)range.len);
    }
   
   TypeDef::TopRule * defRule(TypeDef::Kind *kind)
    {
     return table[kind->synt->index][kind->index];
    }
   
   void defRule(TypeDef::Kind *kind,TypeDef::TopRule *rule)
    {
     table[kind->synt->index][kind->index]=rule;
    }
   
   bool testRule(TypeDef::TopRule *rule)
    {
     for(auto arg : rule->args )
       if( arg.kind && !defRule(arg.kind) ) return false;
     
     return true;
    }
   
   TypeDef::TopRule * findRule(TypeDef::Kind *kind)
    {
     for(TypeDef::TopRule *rule : kind->rules ) if( testRule(rule) ) return rule;
      
     return 0; 
    }
   
   template <class Proc>
   void gen(TypeDef::TopRule *rule,Proc &proc,ulen cap)
    {
     for(auto arg : rule->args )
       if( arg.atom )
         {
          proc.next_atom(arg.atom);
         }
       else
         {
          gen(arg.kind,proc,cap);
         }
     
     proc.next_rule(rule);
    }
   
   template <class Proc>
   void gen(TypeDef::Kind *kind,Proc &proc,ulen cap)
    {
     if( cap )
       {
        gen(select(kind->rules),proc,cap-1);
       }
     else
       {
        gen(defRule(kind),proc,0);
       }
    }
   
  public:
  
   explicit TopGenerator(const DataMap &data);
   
   ~TopGenerator() {}
   
   template <class Proc>
   void operator () (Proc &proc,ulen cap)
    {
     proc.start();
     
     auto *synt=select(lang);
     
     gen(select_ptr(synt->kinds),proc,cap);
     
     proc.stop();
    }
 };

/* class Parser */

class Parser : NoCopy
 {
   struct Rec : NoThrowFlagsBase
    {
     AnyPtr<TypeDef::Atom,TypeDef::Kind> element;
     TypeDef::State *state;
     
     explicit Rec(TypeDef::State *state_) : state(state_) {}
     
     template <class T>
     Rec(T *ptr,TypeDef::State *state_) : element(ptr),state(state_) {}
    };
  
   DynArray<Rec> stack;
   
   TypeDef::State *start_state;
   PtrLen<TypeDef::Synt *> lang;
   
  private:
   
   void push(TypeDef::State *state) { stack.append_fill(state); }
   
   template <class T>
   void push(T *ptr,TypeDef::State *state) { stack.append_fill(ptr,state); }
   
   TypeDef::State * topState();
   
   Rec * topElements(ulen count);
   
   void pop(ulen len) { stack.shrink(len); }
   
   void check_result();
   
  private: 
   
   static TypeDef::Rule * Find(PtrLen<TypeDef::Final::Action> actions,TypeDef::Atom *atom);
   
   static TypeDef::State * Transition(PtrLen<TypeDef::State::Transition> transitions,TypeDef::Element *element);
   
   static TypeDef::State * Transition(PtrLen<TypeDef::State::Transition> transitions,TypeDef::Atom *atom);
   
   static TypeDef::State * Transition(PtrLen<TypeDef::State::Transition> transitions,TypeDef::Kind *kind);
   
   static bool IsSame(AnyPtr<TypeDef::Atom,TypeDef::Kind> element,const TypeDef::TopRule::Arg &arg);
   
  public:
  
   explicit Parser(const DataMap &data);
   
   ~Parser();
   
   void reset();
   
   void next(TypeDef::Atom *atom,TypeDef::TopRule *rule);
   
   void next(TypeDef::Atom *atom);
 };

/* class TestParser */

class TestParser : NoCopy
 {
   Parser parser;
   
   DynArray<TypeDef::TopRule *> stack;
   
  public: 
   
   explicit TestParser(const DataMap &data);
   
   ~TestParser();
   
   void start();
   
   void next_atom(TypeDef::Atom *atom);
   
   void next_rule(TypeDef::TopRule *rule);
   
   void stop();
 };

} // namespace App

#endif

