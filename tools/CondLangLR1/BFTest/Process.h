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
#include <CCore/inc/Task.h>

namespace App {

/* functions */

void Process(StrLen file_name);

/* classes */

class TrackStep;

class TrackStep_mt;

class RunTasks;

class TopGenerator;

class TopParser;

class TopTest;

/* class TrackStep */

class TrackStep : NoCopy
 {
   ulen count;
   ulen ind;
   
  public:
  
   explicit TrackStep(ulen count_) : count(count_),ind(0) {}
   
   bool step();
 };

/* class TrackStep_mt */

class TrackStep_mt : NoCopy
 {
   Atomic::Type count;
   Atomic ind;
   
   Mutex mutex;
   
   bool flag;
   Atomic::Type shown;
   
  public:
  
   explicit TrackStep_mt(Atomic::Type count_) : count(count_),flag(false) {}
   
   bool step();
 };

/* class RunTasks */

class RunTasks : NoCopy
 {
   AntiSem asem;
   
  public:
   
   RunTasks()
    {
    }
   
   ~RunTasks()
    {
     asem.wait();
    }
   
   template <class FuncInit>
   void run(ulen count,const FuncInit &func_init)
    {
     for(; count ;count--)
       {
        asem.inc();
       
        RunFuncTask(func_init,asem.function_dec());
       }
    }
 };

/* class TopGenerator */

class TopGenerator : NoCopy
 {
   Random random;
   PtrLen<DDL2::MapPtr<TypeDef::Synt> > lang;
   
   DynArray<TypeDef::TopRule *> table;
   
  private: 
  
   template <class T>
   T select(PtrLen<T> range)
    { 
     return range[random.select_uint<ulen>(range.len)];
    }
   
   template <class T>
   T * select_ptr(PtrLen<T> range)
    { 
     return range.ptr+random.select_uint<ulen>(range.len);
    }
   
   TypeDef::TopRule * defRule(TypeDef::Kind *kind)
    {
     return table[kind->kindex];
    }
   
   void defRule(TypeDef::Kind *kind,TypeDef::TopRule *rule)
    {
     table[kind->kindex]=rule;
    }
   
   bool testRule(TypeDef::TopRule *rule)
    {
     for(auto arg : rule->args.getRange() )
       {
        TypeDef::Kind *kind=arg.getPtr().castPtr<TypeDef::Kind>();
        
        if( kind && !defRule(kind) ) return false;
       }
     
     return true;
    }
   
   TypeDef::TopRule * findRule(TypeDef::Kind *kind)
    {
     for(auto rule : kind->rules.getRange() ) if( testRule(rule) ) return rule;
      
     return 0; 
    }
   
   template <class Proc>
   void gen(TypeDef::TopRule *rule,Proc &proc,ulen cap)
    {
     for(auto arg : rule->args.getRange() )
       {
        struct Func
         {
          TopGenerator *obj;
          Proc &proc;
          ulen cap;
          
          Func(TopGenerator *obj_,Proc &proc_,ulen cap_) : obj(obj_),proc(proc_),cap(cap_) {}
          
          void operator () (TypeDef::Atom *atom)
           {
            proc.next_atom(atom);
           }
          
          void operator () (TypeDef::Kind *kind)
           {
            obj->gen(kind,proc,cap);
           }
         };
       
        arg.getPtr().apply(Func(this,proc,cap));
       }
     
     proc.next_rule(rule);
    }
   
   template <class Proc>
   void gen(TypeDef::Kind *kind,Proc &proc,ulen cap)
    {
     if( cap )
       {
        gen(select(kind->rules.getRange()),proc,cap-1);
       }
     else
       {
        gen(defRule(kind),proc,0);
       }
    }
   
  public:
  
   explicit TopGenerator(const DataMap &data);
   
   ~TopGenerator();
   
   template <class Proc>
   void operator () (Proc &proc,ulen cap)
    {
     proc.start();
     
     auto synt=select(lang);
     
     gen(select_ptr(synt->kinds.getRange()),proc,cap);
     
     proc.stop();
    }
 };

/* class TopParser */

class TopParser : NoCopy
 {
   using Element = AnyPtr<TypeDef::Atom,TypeDef::Kind> ;
  
   struct Rec : NoThrowFlagsBase
    {
     Element element;
     TypeDef::State *state;
     
     explicit Rec(TypeDef::State *state_) : state(state_) {}
     
     template <class T>
     Rec(T *ptr,TypeDef::State *state_) : element(ptr),state(state_) {}
    };
  
   DynArray<Rec> stack;
   
   TypeDef::State *start_state;
   PtrLen<DDL2::MapPtr<TypeDef::Synt> > lang;
   
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
   
   static bool IsSame(Element element,Element arg);
   
  public:
  
   explicit TopParser(const DataMap &data);
   
   ~TopParser();
   
   void reset();
   
   void next(TypeDef::Atom *atom,TypeDef::TopRule *rule);
   
   void next(TypeDef::Atom *atom);
 };

/* class TopTest */

class TopTest : NoCopy
 {
   TopParser parser;
   
   DynArray<TypeDef::TopRule *> stack;
   
  public: 
   
   explicit TopTest(const DataMap &data);
   
   ~TopTest();
   
   void start();
   
   void next_atom(TypeDef::Atom *atom);
   
   void next_rule(TypeDef::TopRule *rule);
   
   void stop();
 };

} // namespace App

#endif

