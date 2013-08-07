/* BottomLang.cpp */
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

/* class BottomLang */

BottomLang::BottomLang(const CondLang &clang)
 {
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
   
   auto synts=createSynts(range.len);
   
   for(; +synts ;++synts,++range)
     {
      synts->index=range->index;
      synts->name=pool.dup(range->name);
      
      synts->is_lang=range->is_lang;
     }
  }
  
  // rules
  {
   auto range=clang.getRules();
   
   auto rules=createRules(range.len);
   
   for(; +rules ;++rules,++range)
     {
      rules->index=range->index;
      rules->name=pool.dup(range->name);
     }
  }
  
  // synts.rules
  {
   auto range=clang.getSynts();
   
   auto synts=this->synts;
   
   ulen off=0;
   auto rules=getRules();
   
   for(; +synts ;++synts,++range)
     {
      ulen len=range->rules.len;
      
      synts->rules=rules.part(off,len);
      
      off+=len;
     }
  }
  
  // rules.ret rules.args
  {
   auto range=clang.getRules();
   
   auto rules=this->rules;
   
   auto atoms=getAtoms();
   auto synts=getSynts();
   
   for(; +rules ;++rules,++range)
     {
      rules->ret=&(synts[range->ret->index]);
      
      auto arange=range->args;
      
      auto args=createElements(*rules,arange.len);
      
      for(; +args ;++args,++arange)
        {
         arange->apply( [=] (const CondLangBase::AtomDesc *atom) { args->ptr=&(atoms[atom->index]); } , 
                        [=] (const CondLangBase::SyntDesc *synt) { args->ptr=&(synts[synt->index]); } );
        }
     }
  }
  
  pool.shrink_extra();
 }

BottomLang::~BottomLang()
 {
 }
   
} // namespace App

