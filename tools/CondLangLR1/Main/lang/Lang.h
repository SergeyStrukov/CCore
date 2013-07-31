/* Lang.h */
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

#ifndef CondLangLR1_lang_Lang_h
#define CondLangLR1_lang_Lang_h

#include "CondLang.h"

#include <CCore/inc/Array.h>

namespace App {

/* classes */

struct LangBase;

class LangClassBase;

class Lang;

class TopLang;

/* struct LangBase */

struct LangBase : NoCopy
 {
  // Atom
  
  struct Atom : RecordBase 
   {
   };
  
  // Synt
  
  struct Rule;
  
  struct Synt : RecordBase
   {
    PtrLen<const Rule> rules;
    bool is_lang = false ;
   };
  
  // Element
  
  struct Element : RecordBase
   {
    AnyPtr_const<Atom,Synt> ptr;
   };
  
  // Rule
  
  struct Rule : RecordBase
   {
    Synt ret;
    PtrLen<const Element> args;
   };
 };

/* class LangClassBase */

class LangClassBase : public LangBase
 {
  protected:
  
   ElementPool pool;
 
   PtrLen<Atom> atoms;
   PtrLen<Synt> synts;
   PtrLen<Element> elements;
   PtrLen<Rule> rules;

  private:

   template <class P>
   struct PrintElementPtr
    {
     P &out;
   
     explicit PrintElementPtr(P &out_) : out(out_) {}
   
     void operator () (const Atom *atom) { Printf(out,"Atom(#;)",atom->index); }
   
     void operator () (const Synt *synt) { Printf(out,"Synt(#;)",synt->index); }
    };
   
  protected:
   
   LangClassBase() {}
   
   ~LangClassBase() {}
   
  public:
  
   // description
   
   PtrLen<const Atom> getAtoms() const { return Range_const(atoms); }
   
   ulen getAtomCount() const { return atoms.len; }
   
   PtrLen<const Synt> getSynts() const { return Range_const(synts); }
   
   ulen getSyntCount() const { return synts.len; }
   
   PtrLen<const Element> getElements() const { return Range_const(elements); }
   
   ulen getElementCount() const { return elements.len; }
   
   PtrLen<const Rule> getRules() const { return Range_const(rules); }
   
   ulen getRuleCount() const { return rules.len; }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"#;\n\n",Title("Atoms"));
     
     for(auto &atom : getAtoms() ) Printf(out,"#;) #;\n",atom.index,atom.name);
     
     Printf(out,"\n#;\n\n",Title("Syntax classes"));
     
     for(auto &synt : getSynts() ) 
       {
        Printf(out,"#;) #;",synt.index,synt.name);
        
        if( synt.is_lang ) Putobj(out," !");
        
        Putch(out,'\n');
        
        for(auto &rule : synt.rules ) Printf(out,"  Rule(#;)\n",rule.index);
       }
     
     Printf(out,"\n#;\n\n",Title("Elements"));
     
     for(auto &element : getElements() )
       {
        Printf(out,"#;) #; -> ",element.index,element.name);
        
        element.ptr.apply( PrintElementPtr<P>(out) );
        
        Putch(out,'\n');
       }
     
     Printf(out,"\n#;\n\n",Title("Rules"));
     
     for(auto &rule : getRules() )
       if( rule.index )
         {
          Printf(out,"#;) #; -> #;",rule.index,rule.name,rule.ret.name);
          
          Putch(out,'\n');
        
          for(auto &element : rule.args ) Printf(out,"  #;",element.name);
        
          Putch(out,'\n');
         }
       else
         {
          Printf(out,"#;) #;\n",rule.index,rule.name);
         }
     
     Printf(out,"\n#;\n",TextDivider());
    }
 };

/* class Lang */

class Lang : public LangClassBase
 {
  public:
  
   explicit Lang(const CondLang &clang);
   
   ~Lang();
 };

/* class TopLang */

class TopLang : public LangClassBase
 {
  private:
  
   StrLen makeName(StrLen name,StrLen ext); // name.ext

   struct ElementRec : NoThrowFlagsBase
    {
     ulen element_index;
     ulen kind_index;
    };
   
   struct ElementRecExt : ElementRec
    {
     ulen kind_lim;
     
     struct GetLim
      {
       ulen &ret;
       
       explicit GetLim(ulen &ret_) : ret(ret_) {}
       
       void operator () (const CondLangBase::Atom *) { ret=1; }
       
       void operator () (const CondLangBase::Synt *synt) { ret=synt->hasKinds()?synt->kinds.len:1; }
      };
     
     explicit ElementRecExt(const CondLangBase::Element &element) 
      {
       element_index=element.index;
       kind_index=0;
       
       element.ptr.apply( GetLim(kind_lim) );
      }
     
     bool inc()
      {
       if( ++kind_index>=kind_lim )
         {
          kind_index=0;
          
          return false;
         }
       
       return true;
      }
    };
   
   struct RuleRec : NoThrowFlagsBase
    {
     StrLen name;
     DynArray<ElementRec> args;
     
     RuleRec(StrLen name_,PtrLen<const ElementRecExt> args_) : name(name_),args(DoCast(args_.len),args_.ptr) {}
     
     // swap/move objects
     
     void objSwap(RuleRec &obj)
      {
       Swap(name,obj.name);
       Swap(args,obj.args);
      }
     
     explicit RuleRec(ToMoveCtor<RuleRec> obj)
      : name(obj->name),
        args(ObjToMove(obj->args)) 
      {
      }
     
     RuleRec * objMove(Place<void> place)
      {
       return CtorMove(this,place);
      }
    };
   
   static bool Next(PtrLen<ElementRecExt> range);
   
   struct EvalCondArg;
   struct TestCondArg;
   
   static bool TestCond(PtrLen<const ElementRecExt> args,CondLangBase::Cond cond);

   ulen makeRules(Collector<RuleRec> &collector,CondLangBase::Rule rule);
   
   ulen makeRules(Collector<RuleRec> &collector,CondLangBase::Synt synt);
  
   ulen makeRules(Collector<RuleRec> &collector,CondLangBase::Synt synt,ulen kind_index);
   
  public:
 
   explicit TopLang(const CondLang &clang);
  
   ~TopLang();
 };

} // namespace App

#endif



