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

namespace App {

/* classes */

struct LangBase;

class Lang;

/* struct LangBase */

struct LangBase : NoCopy
 {
  // Atom
  
  struct Atom
   {
    ulen index;
    StrLen name;
   };
  
  // Kind
  
  struct Kind
   {
    ulen index;
    StrLen name;
   };
  
  // Synt
  
  struct Rule;
  
  struct Synt
   {
    ulen index;
    StrLen name;
    
    PtrLen<const Kind> kinds;
    
    PtrLen<const Rule> rules;
    bool is_lang;
    
    ulen hasKinds() const { return kinds.len; }
    
    bool noKinds() const { return !kinds.len; }
   };
  
  // Element
  
  struct Element
   {
    ulen index;
    StrLen name;
    
    AnyPtr_const<Atom,Synt> ptr;
   };
  
  // Cond
  
  struct CmpArgElement
   {
    ulen index;
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
  
  struct Rule
   {
    ulen index;
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
  private:
  
   class CondParser;
   class Builder;
  
  public:
  
   explicit Lang(StrLen file_name);
   
   explicit Lang(const Lang &lang);
   
   ~Lang();
   
   // description
   
   PtrLen<const Atom> getAtoms() const;
   
   ulen getAtomCount() const;
   
   PtrLen<const Synt> getSynts() const;
   
   ulen getSyntCount() const;
   
   PtrLen<const Element> getElements() const;
   
   ulen getElementCount() const;
   
   PtrLen<const Rule> getRules() const;
   
   ulen getRuleCount() const;
 };

} // namespace App

#endif



