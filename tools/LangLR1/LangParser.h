/* LangParser.h */
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef LangLR1_LangParser_h
#define LangLR1_LangParser_h

#include "LangToken.h"

namespace App {
namespace LangInput {

/* classes */

//enum AtomClass;

struct Atom;

struct ElementBase;

struct AnyElement;

struct ElementAtom;

struct Element_Body;
struct Element_NT;
struct Element_Rules;
struct Element_Rule;
struct Element_Str;

class Parser;

/* enum AtomClass */

enum AtomClass
 {
  Atom_Nothing,
  
  Atom_Name,
  
  Atom_colon, // :
  Atom_obr,   // {
  Atom_cbr    // }
 };

const char * GetTextDesc(AtomClass ac);

/* struct Atom */

struct Atom
 {
  AtomClass ac;
  Token token;
  
  static AtomClass GetPunctClass(StrLen str);
  
  static AtomClass GetAtomClass(const Token &token);
  
  Atom() : ac(Atom_Nothing) {}
  
  Atom(const Token &token_) : ac(GetAtomClass(token_)),token(token_) {}
  
  bool operator + () const { return ac!=Atom_Nothing; }
  
  bool operator ! () const { return ac==Atom_Nothing; }
  
  template <class P>
  void print(P &out) const
   {
    switch( ac )
      {
       case Atom_Name :
        {
         Printf(out,"#; #.q;",ac,token.str);
        }
       break;
       
       default: 
        {
         Printf(out,"#;",ac);
        }
      }
   }
 };

/* struct ElementBase */

struct ElementBase
 {
  ElementBase *prev;
  ulen state;
  
  ElementBase() : prev(0),state(0) {}
 };

/* struct AnyElement */

struct AnyElement
 {
  ElementBase *elem;
  
  explicit AnyElement(ElementBase *elem_) : elem(elem_) {}
  
  template <class T>
  operator T * () const { return static_cast<T *>(elem); }
 };

/* struct ElementAtom */

struct ElementAtom : ElementBase
 {
  Atom atom;
  
  explicit ElementAtom(const Atom &atom_)
   : atom(atom_)
   {
   }
 };

/* struct Element_Body */

struct Element_Body : ElementBase
 {
  static ulen NextState(ulen state);
  
  Element_Body *prev;
  Element_NT *nt;
  ulen count;
  
  void startBody();
  
  void extBody(Element_Body *prev,Element_NT *nt);
  
  template <class T>
  void extract(DynArray<T> &ret);
 };

/* struct Element_NT */

struct Element_NT : ElementBase
 {
  static ulen NextState(ulen state);
  
  Token name;
  Element_Rules *rules;
  bool is_start;
  
  void buildNT(ElementAtom *name,ElementAtom *,Element_Rules *rules,ElementAtom *);
  
  void buildNT_start(ElementAtom *name,ElementAtom *,ElementAtom *,Element_Rules *rules,ElementAtom *);
  
  template <class T>
  void extract(T &ret);
 };

/* struct Element_Rules */

struct Element_Rules : ElementBase
 {
  static ulen NextState(ulen state);
  
  Element_Rules *prev;
  Element_Rule *rule;
  ulen count;
  
  void startRules();
  
  void extRules(Element_Rules *prev,Element_Rule *rule);
  
  template <class T>
  void extract(DynArray<T> &ret);
 };

/* struct Element_Rule */

struct Element_Rule : ElementBase
 {
  static ulen NextState(ulen state);
  
  Element_Str *str;
  Token name;
  
  void buildRule(Element_Str *str,ElementAtom *,ElementAtom *name);
  
  template <class T>
  void extract(T &ret);
 };

/* struct Element_Str */

struct Element_Str : ElementBase
 {
  static ulen NextState(ulen state);
  
  Element_Str *prev;
  Token name;
  ulen count;
  
  void startStr();
  
  void extStr(Element_Str *prev,ElementAtom *name);
  
  template <class T>
  void extract(DynArray<T> &ret);
 };

/* struct Element_Body */

inline void Element_Body::startBody()
 {
  prev=0;
  nt=0;
  count=0;
 }

inline void Element_Body::extBody(Element_Body *prev_,Element_NT *nt_)
 {
  prev=prev_;
  nt=nt_;
  count=prev_->count+1;
 }

template <class T>
void Element_Body::extract(DynArray<T> &ret)
 {
  ret.erase();
  ret.extend_default(count);
  
  Element_Body *ptr=this;
  
  for(ulen i=count; i-- ;ptr=ptr->prev) ptr->nt->extract(ret[i]); 
 }

/* struct Element_NT */

inline void Element_NT::buildNT(ElementAtom *name_,ElementAtom *,Element_Rules *rules_,ElementAtom *)
 {
  name=name_->atom.token;
  rules=rules_;
  is_start=false;
 }

inline void Element_NT::buildNT_start(ElementAtom *name_,ElementAtom *,ElementAtom *,Element_Rules *rules_,ElementAtom *)
 {
  name=name_->atom.token;
  rules=rules_;
  is_start=true;
 }

template <class T>
void Element_NT::extract(T &ret)
 {
  ret.name=name;
  ret.is_start=is_start;
  
  rules->extract(ret.rules);
 }

/* struct Element_Rules */

inline void Element_Rules::startRules()
 {
  prev=0;
  rule=0;
  count=0;
 }

inline void Element_Rules::extRules(Element_Rules *prev_,Element_Rule *rule_)
 {
  prev=prev_;
  rule=rule_;
  count=prev_->count+1;
 }

template <class T>
void Element_Rules::extract(DynArray<T> &ret)
 {
  ret.erase();
  ret.extend_default(count);
  
  Element_Rules *ptr=this;
  
  for(ulen i=count; i-- ;ptr=ptr->prev) ptr->rule->extract(ret[i]); 
 }

/* struct Element_Rule */

inline void Element_Rule::buildRule(Element_Str *str_,ElementAtom *,ElementAtom *name_)
 {
  str=str_;
  name=name_->atom.token;
 }

template <class T>
void Element_Rule::extract(T &ret)
 {
  ret.name=name;
  
  str->extract(ret.str);
 }

/* struct Element_Str */

inline void Element_Str::startStr()
 {
  prev=0;
  count=0;
 }

inline void Element_Str::extStr(Element_Str *prev_,ElementAtom *name_)
 {
  prev=prev_;
  name=name_->atom.token;
  count=prev_->count+1;
 }

template <class T>
void Element_Str::extract(DynArray<T> &ret)
 {
  ret.erase();
  ret.extend_default(count);
  
  Element_Str *ptr=this;
  
  for(ulen i=count; i-- ;ptr=ptr->prev) ret[i].name=ptr->name; 
 }

/* struct Action */

struct Action
 {
  enum Rule
   {
    Abort,
    Shift,
    
    Do_startBody,
    Do_extBody,
    Do_buildNT,
    Do_buildNT_start,
    Do_startRules,
    Do_extRules,
    Do_buildRule,
    Do_startStr,
    Do_extStr
   };
  
  Rule rule;
  ulen new_state;
  
  Action(ulen state,AtomClass ac=Atom_Nothing);
 };
    
/* class Parser */

class Parser : NoCopy
 {
   ElementPool pool;
   ElementBase *stack;
  
  private:
  
   void push(ElementBase *elem,ulen state);
  
   AnyElement pop();
  
   void shift(const Atom &atom,ulen state);
  
  private:
   
   Element_Body * elem_startBody();
   Element_Body * elem_extBody(Element_Body *arg1,Element_NT *arg2);
   Element_NT * elem_buildNT(ElementAtom *arg1,ElementAtom *arg2,Element_Rules *arg3,ElementAtom *arg4);
   Element_NT * elem_buildNT_start(ElementAtom *arg1,ElementAtom *arg2,ElementAtom *arg3,Element_Rules *arg4,ElementAtom *arg5);
   Element_Rules * elem_startRules();
   Element_Rules * elem_extRules(Element_Rules *arg1,Element_Rule *arg2);
   Element_Rule * elem_buildRule(Element_Str *arg1,ElementAtom *arg2,ElementAtom *arg3);
   Element_Str * elem_startStr();
   Element_Str * elem_extStr(Element_Str *arg1,ElementAtom *arg2);
   
  private:
   
   void do_startBody();
   void do_extBody();
   void do_buildNT();
   void do_buildNT_start();
   void do_startRules();
   void do_extRules();
   void do_buildRule();
   void do_startStr();
   void do_extStr();
   
   void doRule(Action::Rule rule);
   
  public:
   
   Parser();
   
   ~Parser();
   
   enum Result
    {
     ResultShift,
     ResultRule,
     ResultAbort
    };
   
   Result next(const Atom &atom);
   
   Result complete(TextPos pos);
   
   void do_next(const Atom &atom);
   
   void do_complete(TextPos pos);
   
   Element_Body * getBody() const { return static_cast<Element_Body *>(stack); }
 };

} // namespace LangInput
} // namespace App

#endif


