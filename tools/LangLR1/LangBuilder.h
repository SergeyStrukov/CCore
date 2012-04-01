/* LangBuilder.h */
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

#ifndef LangLR1_LangBuilder_h
#define LangLR1_LangBuilder_h

#include "LangParser.h"

namespace App {
namespace LangInput {

/* classes */

struct DescBase;
struct DescPtr;

struct TDesc;
struct NTTDesc;
struct RuleDesc;
struct NTDesc;

struct MixDescPtr;

class Builder;

/* struct DescBase */

struct DescBase
 {
  Token name;
  
  DescBase() {}
  
  explicit DescBase(const Token &name_) : name(name_) {}
 };

/* struct DescPtr */

struct DescPtr
 {
  DescBase *ptr;
  
  DescPtr() : ptr(0) {}
  
  explicit DescPtr(DescBase *ptr_) : ptr(ptr_) {}
  
  StrLen getName() const { return ptr->name.str; }
  
  const Token & getToken() const { return ptr->name; }
  
  friend bool operator < (DescPtr a,DescPtr b) { return StrLess(a.getName(),b.getName()); }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* struct TDesc */

struct TDesc : DescBase
 {
  Lang::Builder::Node *node;
  
  TDesc() : node(0) {}
  
  explicit TDesc(const Token &name) : DescBase(name),node(0) {}
  
  void addTo(Lang::Builder &builder)
   {
    node=builder.addTerminal(name.str);
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* struct NTTDesc */

struct NTTDesc : DescBase
 {
  NTDesc *nt;
  TDesc *t;
  
  NTTDesc() : nt(0),t(0) {}
  
  void set(NTDesc *nt_) { nt=nt_; }
  
  void set(TDesc *t_) { t=t_; }
  
  Lang::Builder::Node * getNode();
  
  void addTo(Lang::Builder::RNode *node)
   {
    node->append(getNode());
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* struct RuleDesc */

struct RuleDesc : DescBase
 {
  DynArray<NTTDesc> str;
  
  RuleDesc() {}
  
  explicit RuleDesc(ToMoveCtor<RuleDesc> obj)
   : DescBase(obj->name),
     str(ObjToMove(obj->str))
   {
   }
  
  void addTo(Lang::Builder::NTNode *node)
   {
    auto rule=node->addRule(name.str);
    
    for(auto p=Range(str); +p ;++p) p->addTo(rule);
   }
  
  // move objects
  
  RuleDesc * objMove(Place<void> place)
   {
    return CtorMove(this,place); 
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"  #; :",name.str);
    
    for(auto p=Range(str); +p ;++p) Printf(out," #;",p->name.str);
    
    Putch(out,'\n');
   }
 };

/* struct NTDesc */

struct NTDesc : DescBase
 {
  DynArray<RuleDesc> rules;
  bool is_start;
  Lang::Builder::NTNode *node;
  
  NTDesc() : is_start(false),node(0) {}
  
  explicit NTDesc(ToMoveCtor<NTDesc> obj)
   : DescBase(obj->name),
     rules(ObjToMove(obj->rules)),
     is_start(obj->is_start),
     node(obj->node)
   {
   }
  
  bool addTo(Lang::Builder &builder)
   {
    node=builder.addNonTerminal(name.str);
    
    if( is_start ) 
      {
       builder.addResult(node);
       
       return true;
      }
    
    return false;
   }
  
  void addRules()
   {
    for(auto p=Range(rules); +p ;++p) p->addTo(node);
   }
  
  // move objects
  
  NTDesc * objMove(Place<void> place)
   {
    return CtorMove(this,place); 
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    if( is_start ) Putobj(out,"-> ");
    
    Printf(out,"#;\n {\n",name.str);
    
    for(auto p=Range(rules); +p ;++p) Printf(out,"#;\n",*p);
    
    Putobj(out," }\n");
   }
 };

inline Lang::Builder::Node * NTTDesc::getNode()
 {
  if( nt ) return nt->node;
  
  return t->node;
 }

/* struct MixDescPtr */

struct MixDescPtr
 {
  DescBase *ptr;
  bool isNT;
  
  MixDescPtr() : ptr(0),isNT(false) {}
  
  explicit MixDescPtr(NTDesc *ptr_) : ptr(ptr_),isNT(true) {}
  
  explicit MixDescPtr(NTTDesc *ptr_) : ptr(ptr_),isNT(false) {}
  
  StrLen getName() const { return ptr->name.str; }
  
  const Token & getToken() const { return ptr->name; }
  
  NTDesc * getNTDesc() const { return static_cast<NTDesc *>(ptr); }
  
  NTTDesc * getNTTDesc() const { return static_cast<NTTDesc *>(ptr); }
  
  bool weakLess(MixDescPtr obj) const { return StrLess(getName(),obj.getName()); }
  
  friend bool operator < (MixDescPtr a,MixDescPtr b) 
   {
    if( auto result=StrCmp(a.getName(),b.getName()) ) return result<0;
    
    return a.isNT > b.isNT ; 
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* class Builder */

class Builder : NoCopy
 {
   FileToMem map;
   Tokenizer tokenizer;
   Parser parser;
   
   DynArray<NTDesc> result;
   
   DynArray<TDesc> terminals;
   
  private:
   
   void parse();
   
   bool link(PtrLen<MixDescPtr> range,NTDesc *nt);
   
   void link(PtrLen<MixDescPtr> range);
   
   bool link();
  
  public:
   
   explicit Builder(StrLen file_name);
   
   ~Builder();
   
   void extract(Lang::Builder &builder);
   
   template <class P>
   void print(P &out) const
    {
     for(auto p=Range(result); +p ;++p) Printf(out,"#;\n",*p);
    }
 };

} // namespace LangInput
} // namespace App
 
#endif
 

