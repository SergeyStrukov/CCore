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

namespace App {

/* classes */

struct LangBase;

struct Atom;

struct Synt;

struct Rule;

class Lang;

class BottomLang;

class TopLang;

class ExtLang;

/* struct LangBase */

struct LangBase : NoCopy
 {
  // AtomDesc
  
  struct AtomDesc : DescBase 
   {
    AtomDesc() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#;) #;",index,name);
     }
   };
  
  // SyntDesc
  
  struct RuleDesc;
  
  struct SyntDesc : DescBase
   {
    PtrLen<const RuleDesc> rules;
    bool is_lang = false ;
    
    SyntDesc() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#;) #;",index,name);
      
      if( is_lang ) Putobj(out," !");
     }
   };
  
  // Element
  
  struct Element : NoThrowFlagsBase
   {
    AnyPtr_const<AtomDesc,SyntDesc> ptr;
    
    // constructors
    
    Element() {}
    
    Element(const AtomDesc *atom) : ptr(atom) {}
    
    Element(const SyntDesc *synt) : ptr(synt) {}
    
    // properties
    
    bool operator + () const { return +ptr; }
    
    bool operator ! () const { return !ptr; }
    
    // atoms and synts
    
    template <class AtomFuncInit,class SyntFuncInit>
    void apply(AtomFuncInit atom_func_init,SyntFuncInit synt_func_init) const
     {
      struct Func
       {
        AtomFuncInit atom_func_init;
        SyntFuncInit synt_func_init;
        
        Func(AtomFuncInit atom_func_init_,SyntFuncInit synt_func_init_) : atom_func_init(atom_func_init_),synt_func_init(synt_func_init_) {}
        
        void operator () (const AtomDesc *atom) 
         {  
          FunctorTypeOf<AtomFuncInit> func(atom_func_init);
          
          func(atom);
         }
        
        void operator () (const SyntDesc *synt) 
         {  
          FunctorTypeOf<SyntFuncInit> func(synt_func_init);
          
          func(synt);
         }
       };
      
      ptr.apply( Func(atom_func_init,synt_func_init) );
     }
    
    template <class FuncInit>
    void applyForAtom(FuncInit func_init) const
     {
      ptr.applyFor<AtomDesc>(func_init);
     }
    
    template <class FuncInit>
    void applyForSynt(FuncInit func_init) const
     {
      ptr.applyFor<SyntDesc>(func_init);
     }
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      apply( [&] (const AtomDesc *atom) { Printf(out,"Atom(#;,#;)",atom->index,atom->name); } , 
             [&] (const SyntDesc *synt) { Printf(out,"Synt(#;,#;)",synt->index,synt->name); } );
     }
   };
  
  // RuleDesc
  
  struct RuleDesc : DescBase
   {
    const SyntDesc *ret = 0 ;
    PtrLen<const Element> args;
    
    RuleDesc() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#;) #; -> #;",index,name,ret->name);
     }
   };
 };

/* struct Atom */

struct Atom : NoThrowFlagsBase , CmpComparable<Atom>
 {
  const LangBase::AtomDesc *desc;
  
  // constructors
  
  Atom() : desc(0) {}
  
  Atom(const LangBase::AtomDesc *desc_) : desc(desc_) {}
  
  // properties
  
  bool operator + () const { return desc!=0; }
  
  bool operator ! () const { return desc==0; }
  
  StrLen getName() const { return desc->name; }
  
  ulen getIndex() const { return desc->index; }
  
  // cmp objects
  
  CmpResult objCmp(Atom obj) const { return LessCmp(desc,obj.desc); }
 };

/* struct Synt */

struct Synt : NoThrowFlagsBase , CmpComparable<Synt>
 {
  const LangBase::SyntDesc *desc;
  
  // constructors
  
  Synt() : desc(0) {}
  
  Synt(const LangBase::SyntDesc *desc_) : desc(desc_) {}
  
  // properties
  
  bool operator + () const { return desc!=0; }
  
  bool operator ! () const { return desc==0; }
  
  StrLen getName() const { return desc->name; }
  
  ulen getIndex() const { return desc->index; }
  
  bool isLang() const { return desc->is_lang; }
  
  // rules
  
  template <class FuncInit>
  void apply(FuncInit func_init) const // func(Rule)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    for(auto r=desc->rules; +r ;++r) func(r.ptr);
   }
  
  // cmp objects
  
  CmpResult objCmp(Synt obj) const { return LessCmp(desc,obj.desc); }
 };

/* type Element */

using Element = LangBase::Element ;

/* struct Rule */

struct Rule : NoThrowFlagsBase , CmpComparable<Rule>
 {
  const LangBase::RuleDesc *desc;
 
  // constructors
 
  Rule() : desc(0) {}
 
  Rule(const LangBase::RuleDesc *desc_) : desc(desc_) {}
 
  // properties
 
  bool operator + () const { return desc!=0; }
 
  bool operator ! () const { return desc==0; }
 
  StrLen getName() const { return desc->name; }
 
  ulen getIndex() const { return desc->index; }
 
  Synt getRet() const { return desc->ret; }
  
  // elements
  
  template <class FuncInit>
  void apply(FuncInit func_init) const // func(Element)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    for(auto r=desc->args; +r ;++r) func(*r);
   }
  
  template <class AtomFuncInit,class SyntFuncInit>
  void apply(AtomFuncInit atom_func_init,SyntFuncInit synt_func_init) const // atom_func(Atom),synt_func(Synt)
   {
    for(auto r=desc->args; +r ; ++r) r->apply(atom_func_init,synt_func_init);
   }
  
  // cmp objects
  
  CmpResult objCmp(Rule obj) const { return LessCmp(desc,obj.desc); }
 };

/* class Lang */

class Lang : public LangBase
 {
  protected:
  
   ElementPool pool;
 
   PtrLen<AtomDesc> atoms;
   PtrLen<SyntDesc> synts;
   PtrLen<RuleDesc> rules;

  protected:
   
   Lang() {}
   
   ~Lang() {}
   
   PtrLen<AtomDesc> createAtoms(ulen len)
    {
     PtrLen<AtomDesc> ret=pool.createArray<AtomDesc>(len);
     
     atoms=ret;
     
     return ret;
    }
   
   PtrLen<SyntDesc> createSynts(ulen len)
    {
     PtrLen<SyntDesc> ret=pool.createArray<SyntDesc>(len);
     
     synts=ret;
     
     return ret;
    }
   
   PtrLen<RuleDesc> createRules(ulen len)
    {
     PtrLen<RuleDesc> ret=pool.createArray<RuleDesc>(len);
     
     rules=ret;
     
     return ret;
    }
   
   PtrLen<Element> createElements(RuleDesc &rule,ulen len)
    {
     PtrLen<Element> ret=pool.createArray<Element>(len);
     
     rule.args=Range_const(ret);
     
     return ret;
    }
   
  public:
  
   // description
   
   PtrLen<const AtomDesc> getAtoms() const { return Range_const(atoms); }
   
   ulen getAtomCount() const { return atoms.len; }
   
   PtrLen<const SyntDesc> getSynts() const { return Range_const(synts); }
   
   ulen getSyntCount() const { return synts.len; }
   
   PtrLen<const RuleDesc> getRules() const { return Range_const(rules); }
   
   ulen getRuleCount() const { return rules.len; }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"#;\n\n",Title("Atoms"));
     
     for(auto &atom : getAtoms() ) Printf(out,"#;\n",atom);
     
     Printf(out,"\n#;\n\n",Title("Syntax classes"));
     
     for(auto &synt : getSynts() ) 
       {
        Printf(out,"#;\n",synt);
        
        for(auto &rule : synt.rules ) Printf(out,"  Rule(#;)\n",rule.index);
       }
     
     Printf(out,"\n#;\n\n",Title("Rules"));
     
     for(auto &rule : getRules() )
       {
        Printf(out,"#;\n",rule);
        
        for(auto &element : rule.args ) Printf(out,"  #;",element);
        
        Putch(out,'\n');
       }
     
     Printf(out,"\n#;\n",TextDivider());
    }
 };

/* class BottomLang */

class BottomLang : public Lang
 {
  public:
  
   explicit BottomLang(const CondLang &clang);
   
   ~BottomLang();
 };

/* class TopLang */

class TopLang : public Lang
 {
  private:
  
   struct ElementRec : NoThrowFlagsBase
    {
     CondLangBase::Element element;
     ulen element_index;
     ulen kind_index;
    };
   
   struct ElementRecExt : ElementRec
    {
     ulen kind_lim;
     
     explicit ElementRecExt(CondLangBase::Element element_) 
      {
       element=element_;
       element_index=0; // set later
       kind_index=0;
       
       element_.apply( [this] (const CondLangBase::AtomDesc *) { kind_lim=1; } , 
                       [this] (const CondLangBase::SyntDesc *synt) { kind_lim=Max<ulen>(synt->kinds.len,1); } );
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

   ulen makeRules(Collector<RuleRec> &collector,const CondLangBase::RuleDesc &rule);
   
   ulen makeRules(Collector<RuleRec> &collector,const CondLangBase::SyntDesc &synt);
  
   ulen makeRules(Collector<RuleRec> &collector,const CondLangBase::SyntDesc &synt,ulen kind_index);
   
  public:
 
   explicit TopLang(const CondLang &clang);
  
   ~TopLang();
 };

/* class ExtLang */

class ExtLang : public Lang
 {
   ulen original_atom_count;
   
  public:
  
   explicit ExtLang(const Lang &lang);
   
   ~ExtLang();
   
   ulen getOriginalAtomCount() const { return original_atom_count; }
   
   PtrLen<const AtomDesc> getOriginalAtoms() const { return getAtoms().prefix(original_atom_count); }
   
   PtrLen<const AtomDesc> getRuleAtoms() const { return getAtoms().part(original_atom_count); }
 };

} // namespace App

#endif



