/* Run.h */
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

#ifndef LangLR1_Run_h
#define LangLR1_Run_h

#include "NonEmptyTest.h"
#include "IsolatedTest.h"
#include "MatrixTable.h"
#include "State.h"
#include "PickRule.h"
#include "SlashQuote.h"

namespace App {

/* consts */ 

const ulen MaxStates = 100000 ;

/* classes */ 

class PrintRule;

class PrintRules;

class PrintRules_rec;

class PrintRuleStr;

class Run;

/* class PrintRule */

class PrintRule
 {
   RIndex rule;
   
  private: 
   
   void GuardRuleList();
  
  public:
   
   explicit PrintRule(RIndex rule_) : rule(rule_) {}
   
   explicit PrintRule(PtrLen<const RIndex> list)
    {
     if( list.len!=1 ) GuardRuleList();
     
     rule=*list;
    }
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"RuleTable+#;",rule);
    }
 };

/* class PrintRules */

class PrintRules
 {
   PtrLen<const RIndex> list;
  
  public:
  
   explicit PrintRules(PtrLen<const RIndex> list_) : list(list_) {}
  
   template <class P>
   void print(P &out) const
    {
     auto p=list;
     
     if( +p )
       {
        Printf(out,"{ #;",PrintRule(*p));
        
        for(++p; +p ;++p) Printf(out,", #;",PrintRule(*p));
         
        Putobj(out," }"); 
       }
     else
       {
        Putobj(out,"{ }");
       }
    }
 };

/* class PrintRules_rec */

class PrintRules_rec
 {
   PtrLen<const RuleRecord> list;
  
  public:
  
   explicit PrintRules_rec(PtrLen<const RuleRecord> list_) : list(list_) {}
  
   template <class P>
   void print(P &out) const
    {
     auto p=list;
     
     if( +p )
       {
        Printf(out,"{ #;",PrintRule(p->rule));
        
        for(++p; +p ;++p) Printf(out,", #;",PrintRule(p->rule));
         
        Putobj(out," }"); 
       }
     else
       {
        Putobj(out,"{ }");
       }
    }
 };

/* class PrintRuleStr */

class PrintRuleStr
 {
   ulen tLim;
   PtrLen<const NTIndex> str;
   
  private: 
  
   ulen getIndex(NTIndex ntt) const
    {
     if( ntt.isTIndex() ) return ntt.getTIndex();
     
     return tLim+ntt.getNIndex();
    }
   
  public:
   
   PrintRuleStr(ulen tLim_,PtrLen<const NTIndex> str_) : tLim(tLim_),str(str_) {}

   template <class P>
   void print(P &out) const
    {
     auto p=str;
     
     if( +p )
       {
        Printf(out,"{ ElementTable+#;",getIndex(*p));
        
        for(++p; +p ;++p) Printf(out,", ElementTable+#;",getIndex(*p));
         
        Putobj(out," }"); 
       }
     else
       {
        Putobj(out,"{ }");
       }
    }
 };

/* class Run */

class Run : NoCopy
 {
   const Lang &lang;
   
   Punct punct;
   
   PrintFile out;
   
   DynArray<State> state_list;
   DynArray<FinalSet> finals;
   
  private: 
   
   template <class T>
   bool sanity();
   
   void puncture(bool do_out);
   
   void way(bool do_out);
   
   void compression();
   
   bool nonLR1();
   
   void stateDDL(bool nonLR1);

   void test(StrLen CCORE_Root);
   
   void parser();
   
   void generator();
   
  public:
  
   explicit Run(const Lang &lang);
   
   ~Run();
   
   int run(StrLen CCORE_Root,bool ext_out=false);
 };

} // namespace App

#endif



