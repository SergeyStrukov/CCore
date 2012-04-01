/* Lang.h */
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

#ifndef LangLR1_Lang_h
#define LangLR1_Lang_h

#include "Tool.h"

namespace App {

/* functions */

inline bool IsTChar(char ch) { return CharIsVisible(ch) && ch!='"' && ch!='\\' ; }

bool IsCName(StrLen str);

bool IsTName(StrLen str);

void GuardCName(StrLen cname);

void GuardTName(StrLen tname);

/* classes */

//enum CharClass;

class CharProp;

//enum NIndex;

//enum TIndex;

//enum RIndex;

class NTIndex;

struct RuleRecord;

class Lang;

/* enum CharClass */ 

enum CharClass
 {
  Char_Letter,
  Char_Digit,

  Char_Other
 };
 
/* class CharProp */ 

class CharProp : public CharPropTable<CharClass,Char_Other>
 {
  public:

   CharProp();

   static const CharProp Object;
 };

inline bool IsCFirstChar(char ch) { return CharProp::Object[ch]==Char_Letter; }

inline bool IsCNextChar(char ch) { return CharProp::Object[ch]<=Char_Digit; }

/* enum NIndex */ 

enum NIndex : ulen
 {
  NIndexFirst
 };

typedef IndexRange<NIndex> NIndexRange;

/* enum TIndex */ 

enum TIndex : ulen
 {
  TIndexEnd, // "(End)"
  
  TIndexFirst
 };

typedef IndexRange<TIndex> TIndexRange;

/* enum RIndex */ 

enum RIndex : ulen
 {
  RIndexShift, // "<-"
  
  RIndexFirst
 };

typedef IndexRange<RIndex> RIndexRange;

/* class NTIndex */

class NTIndex
 {
   ulen index;
   bool isN;
  
  public: 
  
   explicit NTIndex(NIndex nt) : index(nt),isN(true) {}
  
   explicit NTIndex(TIndex t=TIndexEnd) : index(t),isN(false) {}
  
   bool isNIndex() const { return isN; }
  
   bool isTIndex() const { return !isN; }
  
   NIndex getNIndex() const { return NIndex(index); }
  
   TIndex getTIndex() const { return TIndex(index); }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

/* struct RuleRecord */

struct RuleRecord 
 {
  PtrLen<const NTIndex> str;
  RIndex rule;
  NIndex result;
  
  RuleRecord() : rule(RIndexShift),result(NIndexFirst) {}
  
  RuleRecord(NothingType) : rule(RIndexShift),result(NIndexFirst) {}
  
  void init(PtrLen<const NTIndex> str_,RIndex rule_,NIndex result_)
   {
    str=str_;
    rule=rule_;
    result=result_;
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* class Lang */

class Lang : NoCopy
 {
   String name;
  
   ulen nLim;
   ulen tLim;
   ulen rLim;
   
   DynArray<String> nNames;
   DynArray<String> tNames;
   DynArray<String> rNames;
   
   DynArray<NIndex> result;
   
   DynArray<NTIndex> strLine;
   DynArray<RuleRecord> rules;
   
   DynArray<OffLen> nRules;
   
  public:
   
   class Builder;
  
   explicit Lang(const Builder &builder);
   
   ~Lang();
   
   StrLen getName() const { return Range(name); }
   
   ulen getNIndexLim() const { return nLim; }
   
   ulen getTIndexLim() const { return tLim; }
   
   ulen getRIndexLim() const { return rLim; }
   
   NIndexRange getNRange() const { return NIndexRange(getNIndexLim()); }
   
   TIndexRange getTRange() const { return TIndexRange(getTIndexLim()); }
   
   RIndexRange getRRange() const { return RIndexRange(getRIndexLim()); }
   
   NIndexRange getNRange(NIndex first) const { return NIndexRange(first,getNIndexLim()); }
   
   TIndexRange getTRange(TIndex first) const { return TIndexRange(first,getTIndexLim()); }
   
   RIndexRange getRRange(RIndex first) const { return RIndexRange(first,getRIndexLim()); }
   
   StrLen getTextDesc(NIndex nt) const { return Range(nNames[nt]); }
   
   StrLen getTextDesc(TIndex t) const { return Range(tNames[t]); }
   
   StrLen getTextDesc(RIndex r) const { return Range(rNames[r]); }
   
   PtrLen<const NIndex> getResult() const { return Range(result); }
   
   PtrLen<const RuleRecord> getRules(NIndex nt) const { return nRules[nt].cut(rules.getPtr()); }
   
   RuleRecord getRule(RIndex r) const { return rules[r]; }
 };

/* class Lang::Builder */

class Lang::Builder : NoCopy
 {
  public:
   
   class Node : public MemBase_nocopy
    {
      String name;
      NTIndex index;
     
     public:
      
      Node(const String &name,NIndex nt);
      
      Node(const String &name,TIndex t);
      
      ~Node();
      
      const String & getName() const { return name; }
      
      NTIndex getIndex() const { return index; }
    };
   
   class RNode : public MemBase_nocopy
    {
      String name;
      
      DynArray<Node *> str;
      
     private:
      
      template <class R>
      static void Init(R) {}
      
      template <class R,class T,class ... TT>
      static void Init(R r,T t,TT ... tt)
       {
        *r=t;
        
        ++r;
        
        Init(r,tt...);
       }
    
     public:
      
      explicit RNode(const String &name);
      
      ~RNode();
      
      const String & getName() const { return name; }
      
      ulen getStrLen() const { return str.getLen(); }
      
      void fill(PtrLen<NTIndex> out) const;
      
      void append(Node *node);
      
      template <class ... TT>
      void extend(TT ... tt)
       {
        auto out=str.extend_raw(Meta::TypeListLen<TT...>::Ret);
        
        Init(out,tt...);
       }
    };
   
   class NTNode : public Node
    {
      DynArray<OwnPtr<RNode> > rules;
      NIndex index;
     
     public:
      
      NTNode(const String &name,NIndex nt);
      
      ~NTNode();
      
      RNode * addRule(StrLen cname);
      
      PtrLen<const OwnPtr<RNode> > getRules() const { return Range(rules); }

      NIndex getNIndex() const { return index; }
    };
   
  private:
   
   String name;
   
   DynArray<OwnPtr<Node> > terminals;
   DynArray<OwnPtr<NTNode> > non_terminals;
   
   DynArray<NTNode *> result;
   
   friend class Lang;
  
  public:
   
   explicit Builder(StrLen cname);
   
   ~Builder();
   
   Node * addTerminal(StrLen tname);
   
   NTNode * addNonTerminal(StrLen cname);
   
   void addResult(NTNode *node);
 };

} // namespace App

#endif
