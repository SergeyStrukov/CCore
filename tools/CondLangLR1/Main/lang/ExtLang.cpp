/* ExtLang.cpp */
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

/* class ExtLang */

ExtLang::ExtLang(const Lang &lang,ulen map_atom_count)
 {
  original_atom_count=lang.getAtomCount();
  
  // atoms
  {
   ulen len=LenAdd(lang.getAtomCount(),lang.getRuleCount());
   
   auto atoms=createAtoms(len);
   
   ulen index=0;
   
   for(auto &atom : lang.getAtoms() )
     {
      atoms->index=index++;
      atoms->name=pool.dup(atom.name);
      
      atoms->map_index=atom.map_index;
      
      ++atoms;
     }
   
   for(auto &rule : lang.getRules() )
     {
      atoms->index=index++;
      atoms->name=pool.cat(StrLen("@",1),rule.name);
      
      atoms->map_index=rule.map_index+map_atom_count;
      
      ++atoms;
     }
  }
  
  // synts
  {
   ulen len=lang.getSyntCount();
   
   auto synts=createSynts(len);
   
   for(auto &synt : lang.getSynts() )
     {
      synts->index=synt.index;
      synts->name=pool.dup(synt.name);
      
      synts->is_lang=synt.is_lang;
      
      synts->map_index=synt.map_index;
      
      synts->rules.len=synt.rules.len;
     
      ++synts;
     }
  }
  
  // rules
  {
   ulen len=lang.getRuleCount();
   
   auto rules=createRules(len);
   
   auto atoms=getAtoms();
   auto synts=getSynts();
   
   ulen delta=original_atom_count;
   
   for(auto &rule : lang.getRules() )
     {
      rules->index=rule.index;
      rules->name=pool.dup(rule.name);
      
      rules->map_index=rule.map_index;
      
      rules->ret=&(synts[rule.ret->index]);
      
      auto args=createElements(*rules,LenAdd(rule.args.len,1));
      
      for(auto element : rule.args )
        {
         element.apply( [=] (const AtomDesc *atom) { args->ptr=&(atoms[atom->index]); } , 
                        [=] (const SyntDesc *synt) { args->ptr=&(synts[synt->index]); } );
        
         ++args;
        }
      
      args->ptr=&(atoms[rule.index+delta]);
     
      ++rules;
     }
  }
  
  // synts.rules
  {
   auto synts=this->synts;
   
   auto *ptr=rules.ptr;
   
   for(; +synts ;++synts)
     {
      ulen len=synts->rules.len;
      
      synts->rules.ptr=ptr;
      
      ptr+=len;
     }
  }
  
  pool.shrink_extra();
 }

ExtLang::~ExtLang()
 {
 }

} // namespace App

