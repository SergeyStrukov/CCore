/* TopLang.cpp */
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

#include "Lang.h"

#include <CCore/inc/String.h>

namespace App {

/* class TopLang */

bool TopLang::Next(PtrLen<ElementRecExt> range)
 {
  for(; +range ;++range)
    if( range->inc() )
      return true;
  
  return false;
 }

struct TopLang::EvalCondArg
 {
  PtrLen<const ElementRecExt> args;
  ulen &ret;
  
  EvalCondArg(PtrLen<const ElementRecExt> args_,ulen &ret_) : args(args_),ret(ret_) {}
  
  void operator () (const CondLangBase::CmpArgElement *element)
   {
    ret=args[element->index].kind_index;
   }
  
  void operator () (const CondLangBase::CmpArgKind *kind)
   {
    ret=kind->kind->index;
   }
 };

struct TopLang::TestCondArg
 {
  PtrLen<const ElementRecExt> args;
  bool &ret;
  
  TestCondArg(PtrLen<const ElementRecExt> args_,bool &ret_) : args(args_),ret(ret_) {}
  
  void operator () (const CondLangBase::CondAND *cond)
   {
    bool ret_a;
    bool ret_b;
    
    cond->a.apply( TestCondArg(args,ret_a) );
    cond->b.apply( TestCondArg(args,ret_b) );
    
    ret=( ret_a && ret_b );
   }
  
  void operator () (const CondLangBase::CondOR *cond)
   {
    bool ret_a;
    bool ret_b;
    
    cond->a.apply( TestCondArg(args,ret_a) );
    cond->b.apply( TestCondArg(args,ret_b) );
    
    ret=( ret_a || ret_b );
   }
  
  void operator () (const CondLangBase::CondNOT *cond)
   {
    bool ret_a;
    
    cond->a.apply( TestCondArg(args,ret_a) );
    
    ret=( !ret_a );
   }
  
  void operator () (const CondLangBase::CondEQ *cond)
   {
    ulen ret_a;
    ulen ret_b;
    
    cond->a.apply( EvalCondArg(args,ret_a) );
    cond->b.apply( EvalCondArg(args,ret_b) );
    
    ret=( ret_a==ret_b );
   }
  
  void operator () (const CondLangBase::CondNE *cond)
   {
    ulen ret_a;
    ulen ret_b;
    
    cond->a.apply( EvalCondArg(args,ret_a) );
    cond->b.apply( EvalCondArg(args,ret_b) );
    
    ret=( ret_a!=ret_b );
   }
  
  void operator () (const CondLangBase::CondGT *cond)
   {
    ulen ret_a;
    ulen ret_b;
    
    cond->a.apply( EvalCondArg(args,ret_a) );
    cond->b.apply( EvalCondArg(args,ret_b) );
    
    ret=( ret_a>ret_b );
   }
  
  void operator () (const CondLangBase::CondGE *cond)
   {
    ulen ret_a;
    ulen ret_b;
    
    cond->a.apply( EvalCondArg(args,ret_a) );
    cond->b.apply( EvalCondArg(args,ret_b) );
    
    ret=( ret_a>=ret_b );
   }
  
  void operator () (const CondLangBase::CondLT *cond)
   {
    ulen ret_a;
    ulen ret_b;
    
    cond->a.apply( EvalCondArg(args,ret_a) );
    cond->b.apply( EvalCondArg(args,ret_b) );
    
    ret=( ret_a<ret_b );
   }
  
  void operator () (const CondLangBase::CondLE *cond)
   {
    ulen ret_a;
    ulen ret_b;
    
    cond->a.apply( EvalCondArg(args,ret_a) );
    cond->b.apply( EvalCondArg(args,ret_b) );
    
    ret=( ret_a<=ret_b );
   }
 };

bool TopLang::TestCond(PtrLen<const ElementRecExt> args,CondLangBase::Cond cond)
 {
  if( !cond ) return true;
  
  bool ret;
  
  cond.apply( TestCondArg(args,ret) );
  
  return ret;
 }

ulen TopLang::makeRules(Collector<RuleRec> &collector,const CondLangBase::RuleDesc &rule)
 {
  ulen ret=0;
  
  DynArray<ElementRecExt> temp(DoCast(rule.args.len),rule.args.ptr);
  
  {
   ulen index=0; 
    
   for(auto &rec : temp ) rec.element_index=index++;
  }
  
  auto args=Range(temp);
  
  do
    {
     if( TestCond(Range_const(args),rule.cond) )
       {
        collector.append_fill(makeRuleName(rule.name,Range_const(args)),rule.index,Range_const(args));
      
        ret++;
       }
    }
  while( Next(args) );
  
  return ret;
 }

ulen TopLang::makeRules(Collector<RuleRec> &collector,const CondLangBase::SyntDesc &synt)
 {
  ulen ret=0;
  
  for(auto &rule : synt.rules ) ret+=makeRules(collector,rule);
  
  return ret;
 }

ulen TopLang::makeRules(Collector<RuleRec> &collector,const CondLangBase::SyntDesc &synt,ulen kind_index)
 {
  ulen ret=0;
  
  for(auto &rule : synt.rules ) if( rule.kind->index==kind_index ) ret+=makeRules(collector,rule);
  
  return ret;
 }

StrLen TopLang::makeRuleName(StrLen name,PtrLen<const ElementRecExt> args)
 {
  PrintString out;
  
  Putobj(out,name);
  
  for(auto rec : args )
    {
     StrLen extra=rec.getExtraName();
     
     if( +extra ) Printf(out,".#;",extra);
    }
  
  String str=out.close();
  
  return pool.dup(Range(str));
 }

TopLang::TopLang(const CondLang &clang)
 {
  Collector<RuleRec> collector;
  DynArray<ulen> map(DoRaw(clang.getSyntCount()));
  
  // atoms
  {
   auto range=clang.getAtoms();
   
   auto atoms=createAtoms(range.len);
   
   for(; +atoms ;++atoms,++range)
     {
      atoms->index=range->index;
      atoms->name=pool.dup(range->name);
     }
  }
  
  // synts
  {
   auto range=clang.getSynts();
   
   ulen len=0;
   
   for(auto &synt : range ) len=LenAdd(len, Max<ulen>(synt.kinds.len,1) );
   
   auto synts=createSynts(len);
   
   ulen index=0;
   ulen map_index=0;
   
   for(; +range ;++range,++map_index)
     if( +range->kinds )
       {
        map[map_index]=index;
      
        StrLen name=range->name;
        bool is_lang=range->is_lang;
        ulen map_index=range->index;
       
        for(auto &kind : range->kinds )
          {
           synts->rules.len=makeRules(collector,*range,kind.index);
          
           synts->index=index++;
           synts->name=pool.cat(name,StrLen(".",1),kind.name);
         
           synts->is_lang=is_lang;
          
           synts->map_index=map_index;
           
           ++synts;
          }
       }
     else
       {
        map[map_index]=index;
       
        synts->rules.len=makeRules(collector,*range);
      
        synts->index=index++;
        synts->name=pool.dup(range->name);
       
        synts->is_lang=range->is_lang;
        
        synts->map_index=range->index;
        
        ++synts;
       }
  }
  
  // rules
  {
   auto range=collector.flat();
   
   auto rules=createRules(range.len);
   
   auto atoms=getAtoms();
   auto synts=getSynts();
   
   ulen index=0;
   
   for(; +rules ;++rules,++range)
     {
      rules->index=index++;
      rules->name=range->name;
      
      rules->map_index=range->map_index;
      
      auto arange=Range_const(range->args);
      
      auto args=createElements(*rules,arange.len);
      
      for(; +args ;++args,++arange)
        {
         arange->element.apply( [=] (const CondLangBase::AtomDesc *atom) { args->ptr=&(atoms[atom->index]); } , 
                                [=,&map] (const CondLangBase::SyntDesc *synt) { args->ptr=&(synts[map[synt->index]+arange->kind_index]); } );
        }
     }
  }
  
  // synt.rules rules.ret
  {
   auto synts=this->synts;
   auto *ptr=rules.ptr;
   
   for(; +synts ;++synts)
     {
      ulen len=synts->rules.len;
      
      synts->rules.ptr=ptr;
      
      for(auto &rule : Range(ptr,len) ) rule.ret=synts.ptr;
      
      ptr+=len;
     }
  }
  
  pool.shrink_extra();
 }
  
TopLang::~TopLang()
 {
 }

} // namespace App

