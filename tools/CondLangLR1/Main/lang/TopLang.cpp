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

namespace App {

/* class TopLang */

StrLen TopLang::makeName(StrLen name,StrLen ext)
 {
  ulen len=LenAdd(name.len,1,ext.len);
  
  PtrLen<char> ret=pool.createArray_raw<char>(len);
  
  name.copyTo(ret.ptr);
  
  ret[name.len]='.';
  
  ext.copyTo(ret.ptr+1+name.len);
  
  return ret;
 }

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
    ret=kind->kind.index;
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
    
    cond->a.ptr.apply( TestCondArg(args,ret_a) );
    cond->b.ptr.apply( TestCondArg(args,ret_b) );
    
    ret=( ret_a && ret_b );
   }
  
  void operator () (const CondLangBase::CondOR *cond)
   {
    bool ret_a;
    bool ret_b;
    
    cond->a.ptr.apply( TestCondArg(args,ret_a) );
    cond->b.ptr.apply( TestCondArg(args,ret_b) );
    
    ret=( ret_a || ret_b );
   }
  
  void operator () (const CondLangBase::CondNOT *cond)
   {
    bool ret_a;
    
    cond->a.ptr.apply( TestCondArg(args,ret_a) );
    
    ret=( !ret_a );
   }
  
  void operator () (const CondLangBase::CondEQ *cond)
   {
    ulen ret_a;
    ulen ret_b;
    
    cond->a.ptr.apply( EvalCondArg(args,ret_a) );
    cond->b.ptr.apply( EvalCondArg(args,ret_b) );
    
    ret=( ret_a==ret_b );
   }
  
  void operator () (const CondLangBase::CondNE *cond)
   {
    ulen ret_a;
    ulen ret_b;
    
    cond->a.ptr.apply( EvalCondArg(args,ret_a) );
    cond->b.ptr.apply( EvalCondArg(args,ret_b) );
    
    ret=( ret_a!=ret_b );
   }
  
  void operator () (const CondLangBase::CondGT *cond)
   {
    ulen ret_a;
    ulen ret_b;
    
    cond->a.ptr.apply( EvalCondArg(args,ret_a) );
    cond->b.ptr.apply( EvalCondArg(args,ret_b) );
    
    ret=( ret_a>ret_b );
   }
  
  void operator () (const CondLangBase::CondGE *cond)
   {
    ulen ret_a;
    ulen ret_b;
    
    cond->a.ptr.apply( EvalCondArg(args,ret_a) );
    cond->b.ptr.apply( EvalCondArg(args,ret_b) );
    
    ret=( ret_a>=ret_b );
   }
  
  void operator () (const CondLangBase::CondLT *cond)
   {
    ulen ret_a;
    ulen ret_b;
    
    cond->a.ptr.apply( EvalCondArg(args,ret_a) );
    cond->b.ptr.apply( EvalCondArg(args,ret_b) );
    
    ret=( ret_a<ret_b );
   }
  
  void operator () (const CondLangBase::CondLE *cond)
   {
    ulen ret_a;
    ulen ret_b;
    
    cond->a.ptr.apply( EvalCondArg(args,ret_a) );
    cond->b.ptr.apply( EvalCondArg(args,ret_b) );
    
    ret=( ret_a<=ret_b );
   }
 };

bool TopLang::TestCond(PtrLen<const ElementRecExt> args,CondLangBase::Cond cond)
 {
  if( !cond ) return true;
  
  bool ret;
  
  cond.ptr.apply( TestCondArg(args,ret) );
  
  return ret;
 }

ulen TopLang::makeRules(Collector<RuleRec> &collector,CondLangBase::Rule rule)
 {
  ulen ret=0;
  
  StrLen name=pool.dup(rule.name);
  
  DynArray<ElementRecExt> temp(DoCast(rule.args.len),rule.args.ptr);
  
  auto args=Range(temp);
  
  do
    {
     if( TestCond(Range_const(args),rule.cond) )
       {
        collector.append_fill(name,Range_const(args));
      
        ret++;
       }
    }
  while( Next(args) );
  
  return ret;
 }

ulen TopLang::makeRules(Collector<RuleRec> &collector,CondLangBase::Synt synt)
 {
  ulen ret=0;
  
  for(auto rule : synt.rules ) ret+=makeRules(collector,rule);
  
  return ret;
 }

ulen TopLang::makeRules(Collector<RuleRec> &collector,CondLangBase::Synt synt,ulen kind_index)
 {
  ulen ret=0;
  
  for(auto rule : synt.rules ) if( rule.kind.index==kind_index ) ret+=makeRules(collector,rule);
  
  return ret;
 }

TopLang::TopLang(const CondLang &clang)
 {
  Collector<RuleRec> collector;
  DynArray<ulen> map(DoRaw(clang.getSyntCount()));
  
  // atoms
  {
   auto range=clang.getAtoms();
   
   PtrLen<Atom> atoms=pool.createArray<Atom>(range.len);
   
   this->atoms=atoms;

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
   
   for(auto &synt : range ) len=LenAdd(len, synt.hasKinds()?synt.kinds.len:1 );
   
   PtrLen<Synt> synts=pool.createArray<Synt>(len);
   
   this->synts=synts;
   
   ulen index=0;
   ulen map_index=0;
   
   for(; +range ;++range,++map_index)
     if( range->hasKinds() )
       {
        map[map_index]=index;
      
        StrLen name=range->name;
        bool is_lang=range->is_lang;
       
        for(auto &kind : range->kinds )
          {
           synts->rules.len=makeRules(collector,*range,kind.index);
          
           synts->index=index++;
           synts->name=makeName(name,kind.name);
         
           synts->is_lang=is_lang;
          
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
        
        ++synts;
       }
  }
  
  // elements
  {
   ulen len=LenAdd(getAtomCount(),getSyntCount());
   
   PtrLen<Element> elements=pool.createArray<Element>(len);
   
   this->elements=elements;
   
   ulen index=0;

   for(auto &atom : getAtoms() )
     {
      elements->index=index++;
      elements->name=atom.name;
      elements->ptr=&atom;
      
      ++elements;
     }
   
   for(auto &synt : getSynts() )
     {
      elements->index=index++;
      elements->name=synt.name;
      elements->ptr=&synt;
      
      ++elements;
     }
  }
  
  // rules
  {
   auto range=collector.flat();
   
   PtrLen<Rule> rules=pool.createArray<Rule>(LenAdd(range.len,1));
   
   this->rules=rules;
   
   rules[0].index=0;
   rules[0].name="<-";
   
   ulen index=1;
   
   for(++rules; +rules ;++rules,++range)
     {
      rules->index=index++;
      rules->name=range->name;
      
      auto arange=Range_const(range->args);
      
      PtrLen<Element> args=pool.createArray<Element>(arange.len);
      
      rules->args=Range_const(args);
      
      ulen delta=atoms.len;
      
      for(; +args ;++args,++arange)
        {
         ulen index=arange->element_index;
         
         if( index<delta )
           *args=elements[index];
         else
           *args=elements[delta+map[index-delta]+arange->kind_index];
        }
     }
  }
  
  // synt.rules
  {
   PtrLen<Synt> synts=this->synts;
   Rule *base=rules.ptr;
   
   ulen off=1;
   
   for(; +synts ;++synts)
     {
      ulen len=synts->rules.len;
      
      Rule *ptr=base+off;
     
      for(auto &rule : Range(ptr,len) ) rule.ret=*synts;
      
      synts->rules.ptr=ptr;
      
      off+=len;
     }
  }
 }
  
TopLang::~TopLang()
 {
 }

} // namespace App

