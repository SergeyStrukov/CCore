/* Lang.cpp */
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

/* class Lang */

Lang::Lang(const CondLang &clang)
 {
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
   
   PtrLen<Synt> synts=pool.createArray<Synt>(range.len);
   
   this->synts=synts;
   
   for(; +synts ;++synts,++range)
     {
      synts->index=range->index;
      synts->name=pool.dup(range->name);
      
      synts->is_lang=range->is_lang;
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
   auto range=clang.getRules();
   
   PtrLen<Rule> rules=pool.createArray<Rule>(range.len);
   
   this->rules=rules;
   
   rules->index=0;
   rules->name="<-";
   
   for(++rules,++range; +rules ;++rules,++range)
     {
      rules->index=range->index;
      rules->name=pool.dup(range->name);
     }
  }
  
  // synts.rules
  {
   auto range=clang.getSynts();
   
   PtrLen<Synt> synts=this->synts;
   
   ulen off=1;
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
   
   PtrLen<Rule> rules=this->rules;
   auto synts=getSynts();
   auto elements=getElements();
   
   for(++rules,++range; +rules ;++rules,++range)
     {
      rules->ret=synts[ range->ret.index ];
      
      auto arange=range->args;
      
      PtrLen<Element> args=pool.createArray<Element>(arange.len);
      
      rules->args=Range_const(args);
      
      for(; +args ;++args,++arange)
        {
         *args=elements[ arange->index ];
        }
     }
  }
 }

Lang::~Lang()
 {
 }
   
} // namespace App

