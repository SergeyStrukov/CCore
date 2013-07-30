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

#ifndef CondLangLR1_Lang_h
#define CondLangLR1_Lang_h

#include "Tools.h"

#include <CCore/inc/AnyPtr.h>
#include <CCore/inc/ElementPool.h>

namespace App {

/* classes */

struct RecordBase;

struct CondLangBase;

class CondLang;

struct LangBase;

class LangClassBase;

class Lang;

class TopLang;

/* struct RecordBase */

struct RecordBase : NoThrowFlagsBase
 {
  ulen index = MaxULen ;
  StrLen name;
  
  bool operator + () const { return index!=MaxULen; }
  
  bool operator ! () const { return index==MaxULen; }
 };

/* struct CondLangBase */

struct CondLangBase : NoCopy
 {
  // Atom
  
  struct Atom : RecordBase 
   {
   };
  
  // Kind
  
  struct Kind : RecordBase
   {
   };
  
  // Synt
  
  struct Rule;
  
  struct Synt : RecordBase
   {
    PtrLen<const Kind> kinds;
    
    PtrLen<const Rule> rules;
    bool is_lang = false ;
    
    ulen hasKinds() const { return +kinds; }
    
    bool noKinds() const { return !kinds; }
   };
  
  // Element
  
  struct Element : RecordBase
   {
    AnyPtr_const<Atom,Synt> ptr;
   };
  
  // Cond
  
  struct CmpArgElement
   {
    ulen index = MaxULen ;
    
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
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Putobj(out,kind.name);
     }
   };
  
  struct CmpArg
   {
    AnyPtr_const<CmpArgElement,CmpArgKind> ptr;
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      ptr.apply(PrintObj<P>(out));
     }
   };
  
  struct CondAND;
  struct CondOR;
  struct CondNOT;
  struct CondEQ;
  struct CondNE;
  struct CondGT;
  struct CondGE;
  struct CondLT;
  struct CondLE;
  
  struct Cond
   {
    AnyPtr_const<CondAND,CondOR,CondNOT,CondEQ,CondNE,CondGT,CondGE,CondLT,CondLE> ptr;
    
    bool operator + () const { return +ptr; }
    
    bool operator ! () const { return !ptr; }
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      ptr.apply(PrintObj<P>(out));
     };
   };
  
  struct CondAND
   {
    Cond a;
    Cond b;
    
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
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#; <= #;",a,b);
     }
   };
  
  // Rule
  
  struct Rule : RecordBase
   {
    Synt ret;
    PtrLen<const Element> args;
    
    Kind kind;
    Cond cond;
    
    bool hasCond() const { return +cond; }
    
    bool noCond() const { return !cond; }
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
   
   template <class P>
   struct PrintElementPtr
    {
     P &out;
     
     explicit PrintElementPtr(P &out_) : out(out_) {}
     
     void operator () (const Atom *atom) { Printf(out,"Atom(#;)",atom->index); }
     
     void operator () (const Synt *synt) { Printf(out,"Synt(#;)",synt->index); }
    };
  
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
     
     for(auto &atom : getAtoms() ) Printf(out,"#;) #;\n",atom.index,atom.name);
     
     Printf(out,"\n#;\n\n",Title("Syntax classes"));
     
     for(auto &synt : getSynts() ) 
       {
        Printf(out,"#;) #;",synt.index,synt.name);
        
        if( synt.is_lang ) Putobj(out," !");
        
        if( +synt.kinds )
          {
           Putobj(out," { ");
          
           for(auto &kind : synt.kinds ) Printf(out,"#;) #; ",kind.index,kind.name);
           
           Putch(out,'}');
          }
        
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
          if( +rule.kind )
            Printf(out,"#;) #; -> #;.#;",rule.index,rule.name,rule.ret.name,rule.kind.name);
          else
            Printf(out,"#;) #; -> #;",rule.index,rule.name,rule.ret.name);
          
          if( rule.hasCond() )
            {
             Printf(out," if( #; )",rule.cond);
            }
          
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
  
  public:
 
   explicit TopLang(const CondLang &clang);
  
   ~TopLang();
 };

} // namespace App

#endif



