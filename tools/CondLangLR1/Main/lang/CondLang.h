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

struct RecordBase;

struct CondLangBase;

class CondLang;

/* struct RecordBase */

struct RecordBase : NoThrowFlagsBase
 {
  ulen index = MaxULen ;
  StrLen name;
  
  RecordBase() {}
  
  bool operator + () const { return index!=MaxULen; }
  
  bool operator ! () const { return index==MaxULen; }
 };

/* struct CondLangBase */

struct CondLangBase : NoCopy
 {
  // Atom
  
  struct Atom : RecordBase // index in the atom list 
   { 
    Atom() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#;) #;",index,name);
     }
   }; 
  
  // Kind
  
  struct Kind : RecordBase // index in the kind list of the synt 
   { 
    Kind() {}  
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#;) #;",index,name);
     }
   }; 
  
  // Synt
  
  struct Rule;
  
  struct Synt : RecordBase // index in the synt list
   {
    PtrLen<const Kind> kinds;
    PtrLen<const Rule> rules;
    bool is_lang = false ;
    
    Synt() {}
    
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
  
  struct Element : RecordBase // index in the element list , atoms first, synts next
   {
    AnyPtr_const<Atom,Synt> ptr;
    
    Element() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#;) #; -> ",index,name);
      
      struct PrintElementPtr
       {
        P &out;
        
        explicit PrintElementPtr(P &out_) : out(out_) {}
        
        void operator () (const Atom *atom) { Printf(out,"Atom(#;)",atom->index); }
        
        void operator () (const Synt *synt) { Printf(out,"Synt(#;)",synt->index); }
       };
      
      ptr.apply( PrintElementPtr(out) );
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
    Kind kind;
    
    CmpArgKind() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Putobj(out,kind.name);
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
  
  struct CondAND
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
  
  struct CondOR
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
  
  struct CondNOT
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
  
  struct CondEQ
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
  
  struct CondNE
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
  
  struct CondGT
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
  
  struct CondGE
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
  
  struct CondLT
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
  
  struct CondLE
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
  
  // Rule
  
  struct Rule : RecordBase // index in the rule list
   {
    Synt ret;
    PtrLen<const Element> args;
    
    Kind kind;
    Cond cond;
    
    Rule() {}
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      if( index )
        {
         if( +kind )
           Printf(out,"#;) #; -> #;.#;",index,name,ret.name,kind.name);
         else
           Printf(out,"#;) #; -> #;",index,name,ret.name);
        
         if( +cond ) Printf(out," if( #; )",cond);
        }
      else
        {
         Printf(out,"#;) #;",index,name);
        }
     }
   };
 };

/* class CondLang */

class CondLang : public CondLangBase
 {
   ElementPool pool;
   
   PtrLen<Atom> atoms;
   PtrLen<Synt> synts;
   PtrLen<Element> elements;
   PtrLen<Rule> rules;
  
  private:
  
   class Builder;
   
  public:
  
   explicit CondLang(StrLen file_name);
   
   ~CondLang();
   
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
     
     for(auto &atom : getAtoms() ) Printf(out,"#;\n",atom);
     
     Printf(out,"\n#;\n\n",Title("Syntax classes"));
     
     for(auto &synt : getSynts() ) 
       {
        Printf(out,"#;\n",synt);
        
        for(auto &rule : synt.rules ) Printf(out,"  Rule(#;)\n",rule.index);
       }
     
     Printf(out,"\n#;\n\n",Title("Elements"));
     
     for(auto &element : getElements() ) Printf(out,"#;\n",element);
     
     Printf(out,"\n#;\n\n",Title("Rules"));
     
     for(auto &rule : getRules() )
       {
        Printf(out,"#;\n",rule);
        
        if( rule.index )
          {
           for(auto &element : rule.args ) Printf(out,"  #;",element.name);
        
           Putch(out,'\n');
          }
       }
     
     Printf(out,"\n#;\n",TextDivider());
    }
 };

} // namespace App

#endif

