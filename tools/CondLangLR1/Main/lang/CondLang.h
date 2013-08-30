/* CondLang.h */
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

#ifndef CondLangLR1_lang_CondLang_h
#define CondLangLR1_lang_CondLang_h

#include "Tools.h"

#include <CCore/inc/AnyPtr.h>
#include <CCore/inc/ElementPool.h>

namespace App {

/* classes */

struct CondLangBase;

class CondLang;

/* struct CondLangBase */

struct CondLangBase : NoCopy
 {
  // AtomDesc
  
  struct AtomDesc : DescBase // index in the atom list 
   { 
    AtomDesc() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#;) #;",index,name);
     }
   }; 
  
  // KindDesc
  
  struct KindDesc : DescBase // index in the kind list of the synt 
   { 
    KindDesc() {}  
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#;) #;",index,name);
     }
   }; 
  
  // SyntDesc
  
  struct RuleDesc;
  
  struct SyntDesc : DescBase // index in the synt list
   {
    PtrLen<const KindDesc> kinds;
    PtrLen<const RuleDesc> rules;
    bool is_lang = false ;
    
    SyntDesc() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#;) #;",index,name);
      
      if( is_lang ) Putobj(out," !");
      
      if( +kinds )
        {
         Putobj(out," { ");
        
         for(auto &kind : kinds ) Printf(out,"#; ",kind);
         
         Putch(out,'}');
        }
     }
   };
  
  // Element
  
  struct Element : NoThrowFlagsBase
   {
    AnyPtr_const<AtomDesc,SyntDesc> ptr;
    
    Element() {}
    
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
  
  // Cond
  
  struct CmpArgElement
   {
    ulen index = MaxULen ; // index of the element in the rule argument list
    
    CmpArgElement() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"@#;",index);
     }
   };
  
  struct CmpArgKind
   {
    KindDesc *kind = 0 ;
    
    CmpArgKind() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#;(#;)",kind->name,kind->index);
     }
   };
  
  using CmpArg = AnyPtr_const<CmpArgElement,CmpArgKind> ;
  
  struct CondAND;
  struct CondOR;
  struct CondNOT;
  struct CondEQ;
  struct CondNE;
  struct CondGT;
  struct CondGE;
  struct CondLT;
  struct CondLE;
  
  using Cond = AnyPtr_const<CondAND,CondOR,CondNOT,CondEQ,CondNE,CondGT,CondGE,CondLT,CondLE> ;
  
  struct CondAND : NoCopy
   {
    Cond a;
    Cond b;
    
    CondAND() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"( #; & #; )",a,b);
     }
   };
  
  struct CondOR : NoCopy
   {
    Cond a;
    Cond b;
    
    CondOR() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"( #; | #; )",a,b);
     }
   };
  
  struct CondNOT : NoCopy
   {
    Cond a;
    
    CondNOT() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"! #;",a);
     }
   };
  
  struct CondEQ : NoCopy
   {
    CmpArg a;
    CmpArg b;
    
    CondEQ() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#; == #;",a,b);
     }
   };
  
  struct CondNE : NoCopy
   {
    CmpArg a;
    CmpArg b;
    
    CondNE() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#; != #;",a,b);
     }
   };
  
  struct CondGT : NoCopy
   {
    CmpArg a;
    CmpArg b;
    
    CondGT() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#; > #;",a,b);
     }
   };
  
  struct CondGE : NoCopy
   {
    CmpArg a;
    CmpArg b;
    
    CondGE() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#; >= #;",a,b);
     }
   };
  
  struct CondLT : NoCopy
   {
    CmpArg a;
    CmpArg b;
    
    CondLT() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#; < #;",a,b);
     }
   };
  
  struct CondLE : NoCopy
   {
    CmpArg a;
    CmpArg b;
    
    CondLE() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#; <= #;",a,b);
     }
   };
  
  // RuleDesc
  
  struct RuleDesc : DescBase // index in the rule list
   {
    SyntDesc *ret = 0 ;
    PtrLen<const Element> args;
    
    KindDesc *kind = 0 ;
    Cond cond;
    
    RuleDesc() {}
    
    ulen getKindIndex() const { return kind?kind->index:0; }
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      if( kind )
        Printf(out,"#;) #;::#; -> #;.#;",index,ret->name,name,ret->name,kind->name);
      else
        Printf(out,"#;) #;::#; -> #;",index,ret->name,name,ret->name);
        
      if( +cond ) Printf(out," if( #; )",cond);
     }
   };
 };

/* class CondLang */

class CondLang : public CondLangBase
 {
   ElementPool pool;
   
   PtrLen<AtomDesc> atoms;
   PtrLen<SyntDesc> synts;
   PtrLen<RuleDesc> rules;
  
  private:
  
   class Builder;
   
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
   
   PtrLen<KindDesc> createKinds(SyntDesc &synt,ulen len)
    {
     PtrLen<KindDesc> ret=pool.createArray<KindDesc>(len);
     
     synt.kinds=Range_const(ret);
     
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
  
   explicit CondLang(StrLen file_name);
   
   ~CondLang();
   
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

} // namespace App

#endif

