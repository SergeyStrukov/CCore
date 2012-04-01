/* Lang.cpp */
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

#include "Lang.h"

namespace App {

/* functions */

bool IsCName(StrLen str)
 {
  if( !str ) return false;
  
  if( !IsCFirstChar(*str) ) return false;
  
  for(++str; +str ;++str) if( !IsCNextChar(*str) ) return false;
  
  return true;
 }

bool IsTName(StrLen str)
 {
  if( !str ) return false;
  
  for(; +str ;++str) if( !IsTChar(*str) ) return false; 
   
  return true;
 }

void GuardCName(StrLen cname)
 {
  if( !IsCName(cname) )
    {
     Printf(Exception,"Not a C-name #.q;",cname);
    }
 }

void GuardTName(StrLen tname)
 {
  if( !IsTName(tname) )
    {
     Printf(Exception,"Not a T-name #.q;",tname);
    }
 }

/* class CharProp */ 

const CharProp CharProp::Object;

CharProp::CharProp()
 {
  setSet(GetDigitChars(),Char_Digit);
  setSet(GetCLetterChars(),Char_Letter);
 }
   
/* class Lang */

Lang::Lang(const Builder &builder)
 : name(builder.name)
 {
  ulen strLen=0;
  
  // set limits
  {
   nLim=builder.non_terminals.getLen();
  
   tLim=builder.terminals.getLen()+TIndexFirst;
  
   rLim=RIndexFirst;
  
   for(auto p=Range(builder.non_terminals); +p ;++p)
     {
      rLim+=p->getPtr()->getRules().len;
     }
  }
  
  // set names
  {
   nNames.extend_default(nLim);
  
   for(auto p=getNRange(NIndexFirst); +p ;++p) nNames[*p]=builder.non_terminals[*p-NIndexFirst]->getName();
  
   tNames.extend_default(tLim);
  
   tNames[TIndexEnd]=String("(End)");
  
   for(auto p=getTRange(TIndexFirst); +p ;++p) tNames[*p]=builder.terminals[*p-TIndexFirst]->getName();
  
   rNames.extend_default(rLim);
  
   rNames[RIndexShift]=String("<-");
   
   ulen i=RIndexFirst;
  
   for(auto p=Range(builder.non_terminals); +p ;++p)
     {
      for(auto q=p->getPtr()->getRules(); +q ;++q,++i) 
        {
         rNames[i]=(*q)->getName();
         
         strLen+=(*q)->getStrLen();
        }
     }
  }
  
  // set result
  {
   ulen len=builder.result.getLen();
   
   result.extend_raw(len);
   
   for(ulen i=0; i<len ;i++) result[i]=builder.result[i]->getNIndex();
  }
  
  // set rules
  {
   strLine.extend_raw(strLen);
   
   rules.extend_default(rLim);
   
   nRules.extend_default(nLim);
   
   ulen i=RIndexFirst;
   ulen o=0;
  
   for(auto p=Range(builder.non_terminals); +p ;++p)
     {
      NIndex nt=(*p)->getNIndex();
      ulen off=i;
      
      for(auto q=p->getPtr()->getRules(); +q ;++q,++i) 
        {
         ulen len=(*q)->getStrLen();
         
         PtrLen<NTIndex> out=Range(strLine.getPtr()+o,len);
         
         o+=len;
         
         (*q)->fill(out);
         
         rules[i].init(Range_const(out),RIndex(i),nt);
        }
      
      nRules[nt].init(off,i-off);
     }
  }
 }
   
Lang::~Lang()
 {
 }
   
/* class Lang::Builder */

Lang::Builder::Node::Node(const String &name_,NIndex nt) : name(name_),index(nt) {}

Lang::Builder::Node::Node(const String &name_,TIndex t) : name(name_),index(t) {}

Lang::Builder::Node::~Node() {}

Lang::Builder::NTNode::NTNode(const String &name,NIndex nt) : Node(name,nt),rules(DoReserve,10),index(nt) {}

Lang::Builder::NTNode::~NTNode() {}

Lang::Builder::RNode * Lang::Builder::NTNode::addRule(StrLen cname)
 {
  GuardCName(cname);

  OwnPtr<RNode> ptr(new RNode(cname));
  
  return rules.append_swap(ptr)->getPtr();
 }

Lang::Builder::RNode::RNode(const String &name_) : name(name_),str(DoReserve,10) {}

Lang::Builder::RNode::~RNode() {}

void Lang::Builder::RNode::fill(PtrLen<NTIndex> out) const
 {
  auto ptr=str.getPtr();
  
  for(; +out ;++out,++ptr) *out=(*ptr)->getIndex();
 }

void Lang::Builder::RNode::append(Node *node)
 {
  str.append_copy(node);
 }

Lang::Builder::Builder(StrLen cname)
 : name(cname),
   terminals(DoReserve,100),
   non_terminals(DoReserve,1000)
 {
  GuardCName(cname);
 }
   
Lang::Builder::~Builder()
 {
 }
   
Lang::Builder::Node * Lang::Builder::addTerminal(StrLen tname)
 {
  GuardTName(tname);
  
  TIndex t=TIndex(terminals.getLen()+TIndexFirst);
  
  OwnPtr<Node> ptr(new Node(Stringf("T(#.q;)",tname),t));
  
  return terminals.append_swap(ptr)->getPtr();
 }
   
Lang::Builder::NTNode * Lang::Builder::addNonTerminal(StrLen cname)
 {
  GuardCName(cname);
  
  NIndex nt=NIndex(non_terminals.getLen()+NIndexFirst);
  
  OwnPtr<NTNode> ptr(new NTNode(cname,nt));
  
  return non_terminals.append_swap(ptr)->getPtr();
 }
   
void Lang::Builder::addResult(NTNode *node)
 {
  result.append_copy(node);
 }
   
} // namespace App


