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

struct LangBase;

class Lang;

/* struct LangBase */

struct LangBase : NoCopy
 {
  struct RecordBase : NoThrowFlagsBase
   {
    ulen index = MaxULen ;
    StrLen name;
    
    bool operator + () const { return index!=MaxULen; }
    
    bool operator ! () const { return index==MaxULen; }
   };
  
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
   };
  
  struct CmpArgKind
   {
    Kind kind;
   };
  
  struct CmpArg
   {
    AnyPtr_const<CmpArgElement,CmpArgKind> ptr;
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
   };
  
  struct CondAND
   {
    Cond a;
    Cond b;
   };
  
  struct CondOR
   {
    Cond a;
    Cond b;
   };
  
  struct CondNOT
   {
    Cond a;
   };
  
  struct CondEQ
   {
    CmpArg a;
    CmpArg b;
   };
  
  struct CondNE
   {
    CmpArg a;
    CmpArg b;
   };
  
  struct CondGT
   {
    CmpArg a;
    CmpArg b;
   };
  
  struct CondGE
   {
    CmpArg a;
    CmpArg b;
   };
  
  struct CondLT
   {
    CmpArg a;
    CmpArg b;
   };
  
  struct CondLE
   {
    CmpArg a;
    CmpArg b;
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

/* class Lang */

class Lang : public LangBase
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
  
   explicit Lang(StrLen file_name);
   
   explicit Lang(const Lang &lang);
   
   ~Lang();
   
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
            Printf(out,"#;) #; -> #;.#;\n",rule.index,rule.name,rule.ret.name,rule.kind.name);
          else
            Printf(out,"#;) #; -> #;\n",rule.index,rule.name,rule.ret.name);
        
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

} // namespace App

#endif



