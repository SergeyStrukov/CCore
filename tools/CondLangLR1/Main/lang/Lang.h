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
  // Atom
  
  struct Atom : NoThrowFlagsBase
   {
    ulen index = MaxULen ;
    StrLen name;
   };
  
  // Kind
  
  struct Kind : NoThrowFlagsBase
   {
    ulen index = MaxULen ;
    StrLen name;
   };
  
  // Synt
  
  struct Rule;
  
  struct Synt : NoThrowFlagsBase
   {
    ulen index = MaxULen ;
    StrLen name;
    
    PtrLen<const Kind> kinds;
    
    PtrLen<const Rule> rules;
    bool is_lang = false ;
    
    ulen hasKinds() const { return +kinds; }
    
    bool noKinds() const { return !kinds; }
   };
  
  // Element
  
  struct Element : NoThrowFlagsBase
   {
    ulen index = MaxULen ;
    StrLen name;
    
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
  
  struct Rule : NoThrowFlagsBase
   {
    ulen index = MaxULen ;
    StrLen name;
    
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
 };

} // namespace App

#endif



